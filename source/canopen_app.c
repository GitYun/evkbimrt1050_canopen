/*
 * canopen_app.c
 *
 *  Created on: 2022年7月30日
 *      Author: renqingyun
 */

#include "fsl_debug_console.h"
#include "fsl_flexcan.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"

#include "canfestival/mimxrt1052/canfestival.h"
#include "TestSlave.h"

static void canopen_init(CO_Data* co_data);

static UNS32 rpdo1_data_handler(CO_Data *d, const indextable *table, uint8_t b_subindex);
static UNS32 rpdo2_data_handler(CO_Data *d, const indextable *table, uint8_t b_subindex);

static UNS32 sdo_param_handler(CO_Data *d, const indextable *table, uint8_t b_subindex);

static UNS32 sdo_param_refresh_for_read(CO_Data *d);


static uint32_t g_rpdo_data = 0;
static uint32_t g_rsdo_array[10] = {0};


int main(void)
{
    Message canopen_rx_msg = {0};

    /* Initialize board hardware. */
    BOARD_ConfigMPU();
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitDebugConsole();

    canopen_init(&TestSlave_Data);

    for (;;) {
        if (canReceive(&canopen_rx_msg) > 0) {
            canDispatch(&TestSlave_Data, &canopen_rx_msg);
        }
    }
}

static void canopen_init(CO_Data* co_data)
{
    uint8_t i = 0;
    UNS32 error = 0;

    printf("CANOpen Initial...\r\n");

    canInit(co_data, 1000000u);
    initTimer();

    error |= RegisterSetODentryCallBack(co_data, 0x2000, 0, rpdo1_data_handler);
    error |= RegisterSetODentryCallBack(co_data, 0x2006, 0, rpdo1_data_handler);
    error |= RegisterSetODentryCallBack(co_data, 0x2007, 0, rpdo2_data_handler);
    error |= RegisterSetODentryCallBack(co_data, 0x2008, 0, rpdo2_data_handler);

    for (i = 1; i <= 10; ++i)
    {
        error |= RegisterSetODentryCallBack(co_data, 0x2002, i, sdo_param_handler);
    }

    if (error != 0)
    {
        printf("CANOpen register callback occur error: 0x%04x", error);
        while (1)
        {
            // error
        }
    }

    setNodeId(co_data, 0x01);
    setState(co_data, Initialisation);
    setState(co_data, Operational);

    printf("CANOpen Start Node ID: %d\r\n", 0x01);
}

void sdo_param_update_for_read(void)
{
    CO_Data* d = getCANOpenDataHandle();

    sdo_param_refresh_for_read(d);
}

static UNS32 rpdo1_data_handler(CO_Data *d, const indextable *table, uint8_t b_subindex)
{
    static uint8_t rpdo_cnt = 0;
    uint32_t value = *(uint32_t *)table->pSubindex[b_subindex].pObject;

    switch (table->index)
    {
    /* rpdo1 */
    case 0x2000:
        g_rpdo_data = value;
        pdo_s2m_tx_data = g_rpdo_data;
        printf("RPDO1, 0x2000: %d\n\r\n", value);
        ++rpdo_cnt;
        break;

    case 0x2006:
        pdo1_tx2 = value;
        pdo1_tx2 &= 0x00FFFFFF;
        pdo1_tx2 |= 0x11000000;
        ++rpdo_cnt;
        printf("RPDO1, 0x2006: %d\n\r\n", value);
        break;

    default:
        break;
    }

    if (rpdo_cnt >= 2)
    {
        rpdo_cnt = 0;
        d->PDO_status[0].last_message.cob_id = 0; // force send
        sendOnePDOevent(d, 0);
    }

    return OD_SUCCESSFUL;
}

static UNS32 rpdo2_data_handler(CO_Data *d, const indextable *table, uint8_t b_subindex)
{
    static uint8_t rpdo2_cnt = 0;
    uint32_t value = *(uint32_t *)table->pSubindex[b_subindex].pObject;

    switch (table->index)
    {
    /* rpdo2 1*/
    case 0x2007:
        pdo2_tx1 = value;
        ++rpdo2_cnt;
        printf("RPDO2, 0x2007: %d\n\r\n", value);
        break;

    /* rpdo2 2*/
    case 0x2008:
        pdo2_tx2 = value;
        pdo2_tx2 &= 0x00FFFFFF;
        pdo2_tx2 |= 0x22000000;
        ++rpdo2_cnt;
        printf("RPDO2, 0x2008: %d\n\r\n", value);
        break;

    default:
        break;
    }

    if (rpdo2_cnt >= 2)
    {
        rpdo2_cnt = 0;
        d->PDO_status[1].last_message.cob_id = 0; // force send
        sendOnePDOevent(d, 0);
    }

    return OD_SUCCESSFUL;
}

static UNS32 sdo_param_handler(CO_Data *d, const indextable *table, uint8_t b_subindex)
{
    uint32_t value = *(uint32_t *)table->pSubindex[b_subindex].pObject;

    g_rsdo_array[b_subindex - 1] = value;

    sdo_s2m_tx_array[b_subindex - 1] = value;

    printf("RSDO: (0x2002, %d) = 0x%08x\n\r\n", b_subindex, value);

    return OD_SUCCESSFUL;
}

// SDO refresh parameter for read
static UNS32 sdo_param_refresh_for_read(CO_Data *d)
{
    uint8_t i = 0;
    const indextable* table = NULL;
    uint32_t error_code = OD_SUCCESSFUL;
    ODCallback_t* callback = NULL;

    table = scanIndexOD(d, 0x2003, &error_code, &callback);

    if (error_code == OD_SUCCESSFUL)
    {
        for (i = 0; i < *(uint8_t *)table->pSubindex[0].pObject; ++i)
        {
            *(uint32_t *)table->pSubindex[i + 1].pObject = g_rsdo_array[i];
        }
    }

    return OD_SUCCESSFUL;
}
