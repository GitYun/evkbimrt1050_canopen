/*
 * canopen_driver.c
 *
 *  Created on: 2022年7月29日
 *      Author: renqingyun
 */

#include "fsl_common.h"
#include "fsl_flexcan.h"
#include "canfestival/mimxrt1052/canfestival.h"

#define CANOPEN_HW_BASE     CAN2

#define CAN_ID_FILTER_TABLE_INIT    \
    { \
        0, 0, 0, 0, 0, 0, 0, 0      \
    }

#define CANOPEN_BUFFER_NUM   32

#define ENDIAN_CONVERT_4B_TO_U32(b0, b1, b2, b3) \
    (((uint32_t)(b0) << 24) | ((uint32_t)(b1) << 16) | ((uint32_t)(b2) << 8) | (uint32_t)(b3))

#define ENDIAN_CONVERT_U32(x)    \
    ENDIAN_CONVERT_4B_TO_U32((uint8_t)(x), (uint8_t)((x) >> 8), (uint8_t)((x) >> 16), (uint8_t)((x) >> 24))

typedef struct {
    flexcan_fifo_transfer_t read;
    flexcan_fifo_transfer_t write;
    flexcan_frame_t rx_frames[CANOPEN_BUFFER_NUM];
} canopen_rx_buffer_t;

static uint32_t g_can_rx_fifo_id_filter_table[] = CAN_ID_FILTER_TABLE_INIT;

static flexcan_handle_t g_can_handle = {0};
static canopen_rx_buffer_t g_canopen_rx_buffer = {{0}, {0}, {0}};

static CO_Data* g_canopen_handle = NULL;

static void can_int_callback(CAN_Type * base,
                             flexcan_handle_t * handle,
                             status_t status,
                             uint32_t result,
                             void * userData);

static bool canopen_rx_buffer_full(void)
{
    uint8_t read_buf_nbr = CANOPEN_BUFFER_NUM - ((int8_t)(g_canopen_rx_buffer.write.frame - g_canopen_rx_buffer.read.frame) + 1);

    return (read_buf_nbr == CANOPEN_BUFFER_NUM) || (read_buf_nbr == 0);
}

CO_Data* getCANOpenDataHandle(void)
{
    return g_canopen_handle;
}

UNS8 canInit(CO_Data * d, uint32_t bitrate)
{
    assert(d != NULL);

    uint8_t ret = 0;
    uint32_t can_src_clk = 0;

    flexcan_config_t cfg = {0};
    flexcan_timing_config_t timing_cfg = {0};
    flexcan_rx_fifo_config_t rx_fifo_cfg = {
        .idFilterTable = &g_can_rx_fifo_id_filter_table[0],
        .idFilterNum = 8, // 8 RX FIFO filters equals 2 (6th-7th) message buffer,
                          // the first 6 (0th-5th) message buffers are occupied by RX FIFO
        .idFilterType = kFLEXCAN_RxFifoFilterTypeA,
        .priority = kFLEXCAN_RxFifoPrioHigh
    };

    g_canopen_handle = d;

    if (CLOCK_IsPllBypassed(CCM_ANALOG, kCLOCK_PllUsb1) == 0) {
        CLOCK_SetMux(kCLOCK_CanMux, 0); // Select pll3_sw_clk / 8 = 60MHz
        CLOCK_SetDiv(kCLOCK_CanDiv, kCLOCK_MiscDivBy3); // Set 60MHz / 3 = 20MHz
    } else {
        CLOCK_SetMux(kCLOCK_CanMux, 1); // Slect osc_clk = 24MHz
        CLOCK_SetDiv(kCLOCK_CanDiv, kCLOCK_MiscDivBy1); // Set 24Mhz / 1 = 24MHz
    }

    FLEXCAN_GetDefaultConfig(&cfg);

    cfg.disableSelfReception = true; // Disable receive frames transmitted by itself
    cfg.enableIndividMask = false; // Disable individual id filter mask
    cfg.maxMbNum = 8 + 32; // 8 mailboxes for RX FIFO, 32 mailboxes for TX message buffer

    if (50u < bitrate && bitrate <= 1000000u) {
        cfg.bitRate = bitrate;
    }

    can_src_clk = CLOCK_GetClockRootFreq(kCLOCK_CanClkRoot);

    if (FLEXCAN_CalculateImprovedTimingValues(CANOPEN_HW_BASE, cfg.bitRate, can_src_clk, &timing_cfg)) {
        memcpy(&cfg.timingConfig, &timing_cfg, sizeof(flexcan_timing_config_t));
    }

    FLEXCAN_Init(CANOPEN_HW_BASE, &cfg, can_src_clk);

    FLEXCAN_SetRxFifoConfig(CANOPEN_HW_BASE, &rx_fifo_cfg, true);

    FLEXCAN_SetRxFifoGlobalMask(CANOPEN_HW_BASE, 0);


    FLEXCAN_TransferCreateHandle(CANOPEN_HW_BASE, &g_can_handle, can_int_callback, NULL);

    g_canopen_rx_buffer.read.frame = &g_canopen_rx_buffer.rx_frames[0];
    g_canopen_rx_buffer.write.frame = &g_canopen_rx_buffer.rx_frames[0];
    FLEXCAN_TransferReceiveFifoNonBlocking(CANOPEN_HW_BASE, &g_can_handle, &g_canopen_rx_buffer.write);
}

void canCLose(void)
{
    FLEXCAN_DisableMbInterrupts(CANOPEN_HW_BASE, (0xFFFFFFFFllu << 32 | 0xFFFFFFFFu));
    FLEXCAN_DisableInterrupts(CANOPEN_HW_BASE, 0xFFFFFFFFu);

    FLEXCAN_Deinit(CANOPEN_HW_BASE);
}

UNS8 canSend(CAN_PORT notused, Message * m)
{
    assert(m != NULL);

    uint8_t ret = 0;
    uint8_t first_vaild_mb = 0;
    uint8_t max_mb = (uint8_t)((CANOPEN_HW_BASE->MCR & CAN_MCR_MAXMB_MASK) >> CAN_MCR_MAXMB_SHIFT) + 1;

    if (0 != (CANOPEN_HW_BASE->MCR & CAN_MCR_RFEN_MASK)) {
        first_vaild_mb = (uint8_t)((CANOPEN_HW_BASE->CTRL2 & CAN_CTRL2_RFFN_MASK) >> CAN_CTRL2_RFFN_SHIFT);
        first_vaild_mb = (first_vaild_mb + 1) * 2 + 6;
    }

    first_vaild_mb += 1;

    if (first_vaild_mb < max_mb) {
        uint8_t mb_idx = 0;
        flexcan_frame_t can_tx_frame = {
            .format = (uint8_t)kFLEXCAN_FrameFormatStandard,
            .type = m->rtr,
            .length = m->len,
            .id = FLEXCAN_ID_STD(m->cob_id),
            .dataWord0 = ENDIAN_CONVERT_U32(((uint32_t *)m->data)[0]),
            .dataWord1 = ENDIAN_CONVERT_U32(((uint32_t *)m->data)[1]),
        };
        flexcan_mb_transfer_t can_mb_xfer = {.frame = &can_tx_frame, .mbIdx = first_vaild_mb};

        while (can_mb_xfer.mbIdx < max_mb) {
            if (kStatus_Success == FLEXCAN_TransferSendNonBlocking(CANOPEN_HW_BASE, &g_can_handle, &can_mb_xfer)) {
                ret = 1;
                break;
            }

            ++can_mb_xfer.mbIdx;
        }
    }

    return ret;
}

UNS8 canReceive(Message * m)
{
    assert(m != NULL);

    uint8_t ret = 0;

    if (g_canopen_rx_buffer.read.frame != g_canopen_rx_buffer.write.frame) {
        flexcan_frame_t* rx_frame = g_canopen_rx_buffer.read.frame;

        m->cob_id = (uint16_t)((rx_frame->id & CAN_ID_STD_MASK) >> CAN_ID_STD_SHIFT);
        m->rtr = rx_frame->type;
        m->len = rx_frame->length;
        ((uint32_t *)m->data)[0] = ENDIAN_CONVERT_U32(rx_frame->dataWord0);
        ((uint32_t *)m->data)[1] = ENDIAN_CONVERT_U32(rx_frame->dataWord1);

        if (g_canopen_rx_buffer.read.frame < &g_canopen_rx_buffer.rx_frames[CANOPEN_BUFFER_NUM - 1]) {
            ++g_canopen_rx_buffer.read.frame;
        } else {
            g_canopen_rx_buffer.read.frame = &g_canopen_rx_buffer.rx_frames[0];
        }

        ret = 1;
    }

    return ret;
}

UNS8 canChangeBaudRate(CAN_PORT port, char* baud)
{
    canClose();

    return canInit(g_canopen_handle, *(uint32_t *)baud);
}

static void can_int_callback(CAN_Type * base,
                             flexcan_handle_t * handle,
                             status_t status,
                             uint32_t result,
                             void * userData)
{
    switch (status)
    {
        case kStatus_FLEXCAN_RxFifoIdle:
            if (!canopen_rx_buffer_full()) {
                if (g_canopen_rx_buffer.write.frame < &g_canopen_rx_buffer.rx_frames[CANOPEN_BUFFER_NUM]) {
                    ++g_canopen_rx_buffer.write.frame;
                } else {
                    g_canopen_rx_buffer.write.frame = &g_canopen_rx_buffer.rx_frames[0];
                }

                FLEXCAN_TransferReceiveFifoNonBlocking(CANOPEN_HW_BASE, &g_can_handle, &g_canopen_rx_buffer.write);
            }
        break;

        case kStatus_FLEXCAN_TxIdle:

        break;

        default:

        break;
    }
}
