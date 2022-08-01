
/* File generated by gen_cfile.py. Should not be modified. */

#include "TestSlave.h"

/**************************************************************************/
/* Declaration of mapped variables                                        */
/**************************************************************************/
UNS32 pdo_m2s_rx_data = 0x0;		/* Mapped at index 0x2000, subindex 0x00 */
UNS32 pdo_s2m_tx_data = 0x0;		/* Mapped at index 0x2001, subindex 0x00 */
UNS32 sdo_m2s_rx_array[] =		/* Mapped at index 0x2002, subindex 0x01 - 0x0A */
  {
    0x0,	/* 0 */
    0x0,	/* 0 */
    0x0,	/* 0 */
    0x0,	/* 0 */
    0x0,	/* 0 */
    0x0,	/* 0 */
    0x0,	/* 0 */
    0x0,	/* 0 */
    0x0,	/* 0 */
    0x0	/* 0 */
  };
UNS32 sdo_s2m_tx_array[] =		/* Mapped at index 0x2003, subindex 0x01 - 0x0A */
  {
    0x0,	/* 0 */
    0x0,	/* 0 */
    0x0,	/* 0 */
    0x0,	/* 0 */
    0x0,	/* 0 */
    0x0,	/* 0 */
    0x0,	/* 0 */
    0x0,	/* 0 */
    0x0,	/* 0 */
    0x0	/* 0 */
  };
UNS8* sdo_version[] =		/* Mapped at index 0x2004, subindex 0x01 - 0x01 */
  {
    (UNS8*)"power_pm_01.0.0_dsp6745_dev"
  };
UNS32 sdo_version2[] =		/* Mapped at index 0x2005, subindex 0x01 - 0x12 */
  {
    0x65776F70,	/* 1702326128 */
    0x6E755F72,	/* 1853185906 */
    0x72657669,	/* 1919252073 */
    0x5F6C6173,	/* 1600938355 */
    0x302E3130,	/* 808333616 */
    0x645F302E,	/* 1683959854 */
    0x37367073,	/* 926314611 */
    0x645F3534,	/* 1683961140 */
    0x7665,	/* 30309 */
    0x0,	/* 0 */
    0x65776F70,	/* 1702326128 */
    0x6D705F72,	/* 1836081010 */
    0x2E31305F,	/* 774975583 */
    0x5F302E30,	/* 1596993072 */
    0x7474616C,	/* 1953784172 */
    0x5F656369,	/* 1600480105 */
    0x62617473,	/* 1650553971 */
    0x656C	/* 25964 */
  };
UNS32 pdo1_rx2 = 0x0;		/* Mapped at index 0x2006, subindex 0x00 */
UNS32 pdo2_rx1 = 0x0;		/* Mapped at index 0x2007, subindex 0x00 */
UNS32 pdo2_rx2 = 0x0;		/* Mapped at index 0x2008, subindex 0x00 */
UNS32 pdo1_tx2 = 0x0;		/* Mapped at index 0x2009, subindex 0x00 */
UNS32 pdo2_tx1 = 0x0;		/* Mapped at index 0x200A, subindex 0x00 */
UNS32 pdo2_tx2 = 0x0;		/* Mapped at index 0x200B, subindex 0x00 */
UNS16 sdo_cpu_id[] =		/* Mapped at index 0x200C, subindex 0x01 - 0x08 */
  {
    0x0,	/* 0 */
    0x0,	/* 0 */
    0x0,	/* 0 */
    0x0,	/* 0 */
    0x0,	/* 0 */
    0x0,	/* 0 */
    0x0,	/* 0 */
    0x0	/* 0 */
  };

/**************************************************************************/
/* Declaration of value range types                                       */
/**************************************************************************/

#define valueRange_EMC 0x9F /* Type for index 0x1003 subindex 0x00 (only set of value 0 is possible) */
UNS32 TestSlave_valueRangeTest (UNS8 typeValue, void * value)
{
  switch (typeValue) {
    case valueRange_EMC:
      if (*(UNS8*)value != (UNS8)0) return OD_VALUE_RANGE_EXCEEDED;
      break;
  }
  return 0;
}

/**************************************************************************/
/* The node id                                                            */
/**************************************************************************/
/* node_id default value.*/
UNS8 TestSlave_bDeviceNodeId = 0x01;

/**************************************************************************/
/* Array of message processing information */

const UNS8 TestSlave_iam_a_slave = 1;

TIMER_HANDLE TestSlave_heartBeatTimers[1];

/*
$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$

                               OBJECT DICTIONARY

$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
*/

/* index 0x1000 :   Device Type. */
                    UNS32 TestSlave_obj1000 = 0x0;	/* 0 */
                    subindex TestSlave_Index1000[] = 
                     {
                       { RO, uint32, sizeof (UNS32), (void*)&TestSlave_obj1000 }
                     };

/* index 0x1001 :   Error Register. */
                    UNS8 TestSlave_obj1001 = 0x0;	/* 0 */
                    subindex TestSlave_Index1001[] = 
                     {
                       { RO, uint8, sizeof (UNS8), (void*)&TestSlave_obj1001 }
                     };

/* index 0x1003 :   Pre-defined Error Field */
                    UNS8 TestSlave_highestSubIndex_obj1003 = 0; /* number of subindex - 1*/
                    UNS32 TestSlave_obj1003[] = 
                    {
                      0x0	/* 0 */
                    };
                    ODCallback_t TestSlave_Index1003_callbacks[] = 
                     {
                       NULL,
                       NULL,
                     };
                    subindex TestSlave_Index1003[] = 
                     {
                       { RW, valueRange_EMC, sizeof (UNS8), (void*)&TestSlave_highestSubIndex_obj1003 },
                       { RO, uint32, sizeof (UNS32), (void*)&TestSlave_obj1003[0] }
                     };

/* index 0x1005 :   SYNC COB ID. */
                    UNS32 TestSlave_obj1005 = 0x0;	/* 0 */
                    ODCallback_t TestSlave_Index1005_callbacks[] = 
                     {
                       NULL,
                     };
                    subindex TestSlave_Index1005[] = 
                     {
                       { RW, uint32, sizeof (UNS32), (void*)&TestSlave_obj1005 }
                     };

/* index 0x1006 :   Communication / Cycle Period */
                    UNS32 TestSlave_obj1006 = 0x0;   /* 0 */

/* index 0x100C :   Guard Time */ 
                    UNS16 TestSlave_obj100C = 0x0;   /* 0 */

/* index 0x100D :   Life Time Factor */ 
                    UNS8 TestSlave_obj100D = 0x0;   /* 0 */

/* index 0x1014 :   Emergency COB ID */
                    UNS32 TestSlave_obj1014 = 0x80 + 0x01;   /* 128 + NodeID */

/* index 0x1016 :   Consumer Heartbeat Time */
                    UNS8 TestSlave_highestSubIndex_obj1016 = 0;
                    UNS32 TestSlave_obj1016[]={0};

/* index 0x1017 :   Producer Heartbeat Time. */
                    UNS16 TestSlave_obj1017 = 0x3E8;	/* 1000 */
                    ODCallback_t TestSlave_Index1017_callbacks[] = 
                     {
                       NULL,
                     };
                    subindex TestSlave_Index1017[] = 
                     {
                       { RW, uint16, sizeof (UNS16), (void*)&TestSlave_obj1017 }
                     };

/* index 0x1018 :   Identity. */
                    UNS8 TestSlave_highestSubIndex_obj1018 = 4; /* number of subindex - 1*/
                    UNS32 TestSlave_obj1018_Vendor_ID = 0x0;	/* 0 */
                    UNS32 TestSlave_obj1018_Product_Code = 0x0;	/* 0 */
                    UNS32 TestSlave_obj1018_Revision_Number = 0x0;	/* 0 */
                    UNS32 TestSlave_obj1018_Serial_Number = 0x0;	/* 0 */
                    subindex TestSlave_Index1018[] = 
                     {
                       { RO, uint8, sizeof (UNS8), (void*)&TestSlave_highestSubIndex_obj1018 },
                       { RO, uint32, sizeof (UNS32), (void*)&TestSlave_obj1018_Vendor_ID },
                       { RO, uint32, sizeof (UNS32), (void*)&TestSlave_obj1018_Product_Code },
                       { RO, uint32, sizeof (UNS32), (void*)&TestSlave_obj1018_Revision_Number },
                       { RO, uint32, sizeof (UNS32), (void*)&TestSlave_obj1018_Serial_Number }
                     };

/* index 0x1200 :   Server SDO Parameter. */
                    UNS8 TestSlave_highestSubIndex_obj1200 = 2; /* number of subindex - 1*/
                    UNS32 TestSlave_obj1200_COB_ID_Client_to_Server_Receive_SDO = 0x601;	/* 1537 */
                    UNS32 TestSlave_obj1200_COB_ID_Server_to_Client_Transmit_SDO = 0x581;	/* 1409 */
                    subindex TestSlave_Index1200[] = 
                     {
                       { RO, uint8, sizeof (UNS8), (void*)&TestSlave_highestSubIndex_obj1200 },
                       { RO, uint32, sizeof (UNS32), (void*)&TestSlave_obj1200_COB_ID_Client_to_Server_Receive_SDO },
                       { RO, uint32, sizeof (UNS32), (void*)&TestSlave_obj1200_COB_ID_Server_to_Client_Transmit_SDO }
                     };

/* index 0x1400 :   Receive PDO 1 Parameter. */
                    UNS8 TestSlave_highestSubIndex_obj1400 = 6; /* number of subindex - 1*/
                    UNS32 TestSlave_obj1400_COB_ID_used_by_PDO = 0x201;	/* 513 */
                    UNS8 TestSlave_obj1400_Transmission_Type = 0xFF;	/* 255 */
                    UNS16 TestSlave_obj1400_Inhibit_Time = 0x0;	/* 0 */
                    UNS8 TestSlave_obj1400_Compatibility_Entry = 0x0;	/* 0 */
                    UNS16 TestSlave_obj1400_Event_Timer = 0x0;	/* 0 */
                    UNS8 TestSlave_obj1400_SYNC_start_value = 0x0;	/* 0 */
                    subindex TestSlave_Index1400[] = 
                     {
                       { RO, uint8, sizeof (UNS8), (void*)&TestSlave_highestSubIndex_obj1400 },
                       { RW, uint32, sizeof (UNS32), (void*)&TestSlave_obj1400_COB_ID_used_by_PDO },
                       { RW, uint8, sizeof (UNS8), (void*)&TestSlave_obj1400_Transmission_Type },
                       { RW, uint16, sizeof (UNS16), (void*)&TestSlave_obj1400_Inhibit_Time },
                       { RW, uint8, sizeof (UNS8), (void*)&TestSlave_obj1400_Compatibility_Entry },
                       { RW, uint16, sizeof (UNS16), (void*)&TestSlave_obj1400_Event_Timer },
                       { RW, uint8, sizeof (UNS8), (void*)&TestSlave_obj1400_SYNC_start_value }
                     };

/* index 0x1401 :   Receive PDO 2 Parameter. */
                    UNS8 TestSlave_highestSubIndex_obj1401 = 6; /* number of subindex - 1*/
                    UNS32 TestSlave_obj1401_COB_ID_used_by_PDO = 0x301;	/* 769 */
                    UNS8 TestSlave_obj1401_Transmission_Type = 0x0;	/* 0 */
                    UNS16 TestSlave_obj1401_Inhibit_Time = 0x0;	/* 0 */
                    UNS8 TestSlave_obj1401_Compatibility_Entry = 0x0;	/* 0 */
                    UNS16 TestSlave_obj1401_Event_Timer = 0x0;	/* 0 */
                    UNS8 TestSlave_obj1401_SYNC_start_value = 0x0;	/* 0 */
                    subindex TestSlave_Index1401[] = 
                     {
                       { RO, uint8, sizeof (UNS8), (void*)&TestSlave_highestSubIndex_obj1401 },
                       { RW, uint32, sizeof (UNS32), (void*)&TestSlave_obj1401_COB_ID_used_by_PDO },
                       { RW, uint8, sizeof (UNS8), (void*)&TestSlave_obj1401_Transmission_Type },
                       { RW, uint16, sizeof (UNS16), (void*)&TestSlave_obj1401_Inhibit_Time },
                       { RW, uint8, sizeof (UNS8), (void*)&TestSlave_obj1401_Compatibility_Entry },
                       { RW, uint16, sizeof (UNS16), (void*)&TestSlave_obj1401_Event_Timer },
                       { RW, uint8, sizeof (UNS8), (void*)&TestSlave_obj1401_SYNC_start_value }
                     };

/* index 0x1600 :   Receive PDO 1 Mapping. */
                    UNS8 TestSlave_highestSubIndex_obj1600 = 2; /* number of subindex - 1*/
                    UNS32 TestSlave_obj1600[] = 
                    {
                      0x20000020,	/* 536870944 */
                      0x20060020	/* 537264160 */
                    };
                    subindex TestSlave_Index1600[] = 
                     {
                       { RW, uint8, sizeof (UNS8), (void*)&TestSlave_highestSubIndex_obj1600 },
                       { RW, uint32, sizeof (UNS32), (void*)&TestSlave_obj1600[0] },
                       { RW, uint32, sizeof (UNS32), (void*)&TestSlave_obj1600[1] }
                     };

/* index 0x1601 :   Receive PDO 2 Mapping. */
                    UNS8 TestSlave_highestSubIndex_obj1601 = 2; /* number of subindex - 1*/
                    UNS32 TestSlave_obj1601[] = 
                    {
                      0x20070020,	/* 537329696 */
                      0x20080020	/* 537395232 */
                    };
                    subindex TestSlave_Index1601[] = 
                     {
                       { RW, uint8, sizeof (UNS8), (void*)&TestSlave_highestSubIndex_obj1601 },
                       { RW, uint32, sizeof (UNS32), (void*)&TestSlave_obj1601[0] },
                       { RW, uint32, sizeof (UNS32), (void*)&TestSlave_obj1601[1] }
                     };

/* index 0x1800 :   Transmit PDO 1 Parameter. */
                    UNS8 TestSlave_highestSubIndex_obj1800 = 6; /* number of subindex - 1*/
                    UNS32 TestSlave_obj1800_COB_ID_used_by_PDO = 0x181;	/* 385 */
                    UNS8 TestSlave_obj1800_Transmission_Type = 0x0;	/* 0 */
                    UNS16 TestSlave_obj1800_Inhibit_Time = 0x0;	/* 0 */
                    UNS8 TestSlave_obj1800_Compatibility_Entry = 0x0;	/* 0 */
                    UNS16 TestSlave_obj1800_Event_Timer = 0x0;	/* 0 */
                    UNS8 TestSlave_obj1800_SYNC_start_value = 0x0;	/* 0 */
                    ODCallback_t TestSlave_Index1800_callbacks[] = 
                     {
                       NULL,
                       NULL,
                       NULL,
                       NULL,
                       NULL,
                       NULL,
                       NULL,
                     };
                    subindex TestSlave_Index1800[] = 
                     {
                       { RO, uint8, sizeof (UNS8), (void*)&TestSlave_highestSubIndex_obj1800 },
                       { RW, uint32, sizeof (UNS32), (void*)&TestSlave_obj1800_COB_ID_used_by_PDO },
                       { RW, uint8, sizeof (UNS8), (void*)&TestSlave_obj1800_Transmission_Type },
                       { RW, uint16, sizeof (UNS16), (void*)&TestSlave_obj1800_Inhibit_Time },
                       { RW, uint8, sizeof (UNS8), (void*)&TestSlave_obj1800_Compatibility_Entry },
                       { RW, uint16, sizeof (UNS16), (void*)&TestSlave_obj1800_Event_Timer },
                       { RW, uint8, sizeof (UNS8), (void*)&TestSlave_obj1800_SYNC_start_value }
                     };

/* index 0x1801 :   Transmit PDO 2 Parameter. */
                    UNS8 TestSlave_highestSubIndex_obj1801 = 6; /* number of subindex - 1*/
                    UNS32 TestSlave_obj1801_COB_ID_used_by_PDO = 0x281;	/* 641 */
                    UNS8 TestSlave_obj1801_Transmission_Type = 0x0;	/* 0 */
                    UNS16 TestSlave_obj1801_Inhibit_Time = 0x0;	/* 0 */
                    UNS8 TestSlave_obj1801_Compatibility_Entry = 0x0;	/* 0 */
                    UNS16 TestSlave_obj1801_Event_Timer = 0x0;	/* 0 */
                    UNS8 TestSlave_obj1801_SYNC_start_value = 0x0;	/* 0 */
                    ODCallback_t TestSlave_Index1801_callbacks[] = 
                     {
                       NULL,
                       NULL,
                       NULL,
                       NULL,
                       NULL,
                       NULL,
                       NULL,
                     };
                    subindex TestSlave_Index1801[] = 
                     {
                       { RO, uint8, sizeof (UNS8), (void*)&TestSlave_highestSubIndex_obj1801 },
                       { RW, uint32, sizeof (UNS32), (void*)&TestSlave_obj1801_COB_ID_used_by_PDO },
                       { RW, uint8, sizeof (UNS8), (void*)&TestSlave_obj1801_Transmission_Type },
                       { RW, uint16, sizeof (UNS16), (void*)&TestSlave_obj1801_Inhibit_Time },
                       { RW, uint8, sizeof (UNS8), (void*)&TestSlave_obj1801_Compatibility_Entry },
                       { RW, uint16, sizeof (UNS16), (void*)&TestSlave_obj1801_Event_Timer },
                       { RW, uint8, sizeof (UNS8), (void*)&TestSlave_obj1801_SYNC_start_value }
                     };

/* index 0x1A00 :   Transmit PDO 1 Mapping. */
                    UNS8 TestSlave_highestSubIndex_obj1A00 = 2; /* number of subindex - 1*/
                    UNS32 TestSlave_obj1A00[] = 
                    {
                      0x20010020,	/* 536936480 */
                      0x20090020	/* 537460768 */
                    };
                    subindex TestSlave_Index1A00[] = 
                     {
                       { RW, uint8, sizeof (UNS8), (void*)&TestSlave_highestSubIndex_obj1A00 },
                       { RW, uint32, sizeof (UNS32), (void*)&TestSlave_obj1A00[0] },
                       { RW, uint32, sizeof (UNS32), (void*)&TestSlave_obj1A00[1] }
                     };

/* index 0x1A01 :   Transmit PDO 2 Mapping. */
                    UNS8 TestSlave_highestSubIndex_obj1A01 = 2; /* number of subindex - 1*/
                    UNS32 TestSlave_obj1A01[] = 
                    {
                      0x200A0020,	/* 537526304 */
                      0x200B0020	/* 537591840 */
                    };
                    subindex TestSlave_Index1A01[] = 
                     {
                       { RW, uint8, sizeof (UNS8), (void*)&TestSlave_highestSubIndex_obj1A01 },
                       { RW, uint32, sizeof (UNS32), (void*)&TestSlave_obj1A01[0] },
                       { RW, uint32, sizeof (UNS32), (void*)&TestSlave_obj1A01[1] }
                     };

/* index 0x2000 :   Mapped variable pdo_m2s_rx_data */
                    ODCallback_t pdo_m2s_rx_data_callbacks[] = 
                     {
                       NULL,
                     };
                    subindex TestSlave_Index2000[] = 
                     {
                       { RW, uint32, sizeof (UNS32), (void*)&pdo_m2s_rx_data }
                     };

/* index 0x2001 :   Mapped variable pdo_s2m_tx_data */
                    subindex TestSlave_Index2001[] = 
                     {
                       { RW, uint32, sizeof (UNS32), (void*)&pdo_s2m_tx_data }
                     };

/* index 0x2002 :   Mapped variable sdo_m2s_rx_array */
                    UNS8 TestSlave_highestSubIndex_obj2002 = 10; /* number of subindex - 1*/
                    ODCallback_t sdo_m2s_rx_array_callbacks[] = 
                     {
                       NULL,
                       NULL,
                       NULL,
                       NULL,
                       NULL,
                       NULL,
                       NULL,
                       NULL,
                       NULL,
                       NULL,
                       NULL,
                     };
                    subindex TestSlave_Index2002[] = 
                     {
                       { RO, uint8, sizeof (UNS8), (void*)&TestSlave_highestSubIndex_obj2002 },
                       { RW, uint32, sizeof (UNS32), (void*)&sdo_m2s_rx_array[0] },
                       { RW, uint32, sizeof (UNS32), (void*)&sdo_m2s_rx_array[1] },
                       { RW, uint32, sizeof (UNS32), (void*)&sdo_m2s_rx_array[2] },
                       { RW, uint32, sizeof (UNS32), (void*)&sdo_m2s_rx_array[3] },
                       { RW, uint32, sizeof (UNS32), (void*)&sdo_m2s_rx_array[4] },
                       { RW, uint32, sizeof (UNS32), (void*)&sdo_m2s_rx_array[5] },
                       { RW, uint32, sizeof (UNS32), (void*)&sdo_m2s_rx_array[6] },
                       { RW, uint32, sizeof (UNS32), (void*)&sdo_m2s_rx_array[7] },
                       { RW, uint32, sizeof (UNS32), (void*)&sdo_m2s_rx_array[8] },
                       { RW, uint32, sizeof (UNS32), (void*)&sdo_m2s_rx_array[9] }
                     };

/* index 0x2003 :   Mapped variable sdo_s2m_tx_array */
                    UNS8 TestSlave_highestSubIndex_obj2003 = 10; /* number of subindex - 1*/
                    subindex TestSlave_Index2003[] = 
                     {
                       { RO, uint8, sizeof (UNS8), (void*)&TestSlave_highestSubIndex_obj2003 },
                       { RW, uint32, sizeof (UNS32), (void*)&sdo_s2m_tx_array[0] },
                       { RW, uint32, sizeof (UNS32), (void*)&sdo_s2m_tx_array[1] },
                       { RW, uint32, sizeof (UNS32), (void*)&sdo_s2m_tx_array[2] },
                       { RW, uint32, sizeof (UNS32), (void*)&sdo_s2m_tx_array[3] },
                       { RW, uint32, sizeof (UNS32), (void*)&sdo_s2m_tx_array[4] },
                       { RW, uint32, sizeof (UNS32), (void*)&sdo_s2m_tx_array[5] },
                       { RW, uint32, sizeof (UNS32), (void*)&sdo_s2m_tx_array[6] },
                       { RW, uint32, sizeof (UNS32), (void*)&sdo_s2m_tx_array[7] },
                       { RW, uint32, sizeof (UNS32), (void*)&sdo_s2m_tx_array[8] },
                       { RW, uint32, sizeof (UNS32), (void*)&sdo_s2m_tx_array[9] }
                     };

/* index 0x2004 :   Mapped variable sdo_version */
                    UNS8 TestSlave_highestSubIndex_obj2004 = 1; /* number of subindex - 1*/
                    subindex TestSlave_Index2004[] = 
                     {
                       { RO, uint8, sizeof (UNS8), (void*)&TestSlave_highestSubIndex_obj2004 },
                       { RO, visible_string, 27, (void*)&sdo_version[0] }
                     };

/* index 0x2005 :   Mapped variable sdo_version2 */
                    UNS8 TestSlave_highestSubIndex_obj2005 = 18; /* number of subindex - 1*/
                    subindex TestSlave_Index2005[] = 
                     {
                       { RO, uint8, sizeof (UNS8), (void*)&TestSlave_highestSubIndex_obj2005 },
                       { RW, uint32, sizeof (UNS32), (void*)&sdo_version2[0] },
                       { RW, uint32, sizeof (UNS32), (void*)&sdo_version2[1] },
                       { RW, uint32, sizeof (UNS32), (void*)&sdo_version2[2] },
                       { RW, uint32, sizeof (UNS32), (void*)&sdo_version2[3] },
                       { RW, uint32, sizeof (UNS32), (void*)&sdo_version2[4] },
                       { RW, uint32, sizeof (UNS32), (void*)&sdo_version2[5] },
                       { RW, uint32, sizeof (UNS32), (void*)&sdo_version2[6] },
                       { RW, uint32, sizeof (UNS32), (void*)&sdo_version2[7] },
                       { RW, uint32, sizeof (UNS32), (void*)&sdo_version2[8] },
                       { RW, uint32, sizeof (UNS32), (void*)&sdo_version2[9] },
                       { RW, uint32, sizeof (UNS32), (void*)&sdo_version2[10] },
                       { RW, uint32, sizeof (UNS32), (void*)&sdo_version2[11] },
                       { RW, uint32, sizeof (UNS32), (void*)&sdo_version2[12] },
                       { RW, uint32, sizeof (UNS32), (void*)&sdo_version2[13] },
                       { RW, uint32, sizeof (UNS32), (void*)&sdo_version2[14] },
                       { RW, uint32, sizeof (UNS32), (void*)&sdo_version2[15] },
                       { RW, uint32, sizeof (UNS32), (void*)&sdo_version2[16] },
                       { RW, uint32, sizeof (UNS32), (void*)&sdo_version2[17] }
                     };

/* index 0x2006 :   Mapped variable pdo1_rx2 */
                    ODCallback_t pdo1_rx2_callbacks[] = 
                     {
                       NULL,
                     };
                    subindex TestSlave_Index2006[] = 
                     {
                       { RW, uint32, sizeof (UNS32), (void*)&pdo1_rx2 }
                     };

/* index 0x2007 :   Mapped variable pdo2_rx1 */
                    ODCallback_t pdo2_rx1_callbacks[] = 
                     {
                       NULL,
                     };
                    subindex TestSlave_Index2007[] = 
                     {
                       { RW, uint32, sizeof (UNS32), (void*)&pdo2_rx1 }
                     };

/* index 0x2008 :   Mapped variable pdo2_rx2 */
                    ODCallback_t pdo2_rx2_callbacks[] = 
                     {
                       NULL,
                     };
                    subindex TestSlave_Index2008[] = 
                     {
                       { RW, uint32, sizeof (UNS32), (void*)&pdo2_rx2 }
                     };

/* index 0x2009 :   Mapped variable pdo1_tx2 */
                    subindex TestSlave_Index2009[] = 
                     {
                       { RW, uint32, sizeof (UNS32), (void*)&pdo1_tx2 }
                     };

/* index 0x200A :   Mapped variable pdo2_tx1 */
                    subindex TestSlave_Index200A[] = 
                     {
                       { RW, uint32, sizeof (UNS32), (void*)&pdo2_tx1 }
                     };

/* index 0x200B :   Mapped variable pdo2_tx2 */
                    subindex TestSlave_Index200B[] = 
                     {
                       { RW, uint32, sizeof (UNS32), (void*)&pdo2_tx2 }
                     };

/* index 0x200C :   Mapped variable sdo_cpu_id */
                    UNS8 TestSlave_highestSubIndex_obj200C = 8; /* number of subindex - 1*/
                    subindex TestSlave_Index200C[] = 
                     {
                       { RO, uint8, sizeof (UNS8), (void*)&TestSlave_highestSubIndex_obj200C },
                       { RW, uint16, sizeof (UNS16), (void*)&sdo_cpu_id[0] },
                       { RW, uint16, sizeof (UNS16), (void*)&sdo_cpu_id[1] },
                       { RW, uint16, sizeof (UNS16), (void*)&sdo_cpu_id[2] },
                       { RW, uint16, sizeof (UNS16), (void*)&sdo_cpu_id[3] },
                       { RW, uint16, sizeof (UNS16), (void*)&sdo_cpu_id[4] },
                       { RW, uint16, sizeof (UNS16), (void*)&sdo_cpu_id[5] },
                       { RW, uint16, sizeof (UNS16), (void*)&sdo_cpu_id[6] },
                       { RW, uint16, sizeof (UNS16), (void*)&sdo_cpu_id[7] }
                     };

/**************************************************************************/
/* Declaration of pointed variables                                       */
/**************************************************************************/

const indextable TestSlave_objdict[] = 
{
  { (subindex*)TestSlave_Index1000,sizeof(TestSlave_Index1000)/sizeof(TestSlave_Index1000[0]), 0x1000},
  { (subindex*)TestSlave_Index1001,sizeof(TestSlave_Index1001)/sizeof(TestSlave_Index1001[0]), 0x1001},
  { (subindex*)TestSlave_Index1005,sizeof(TestSlave_Index1005)/sizeof(TestSlave_Index1005[0]), 0x1005},
  { (subindex*)TestSlave_Index1017,sizeof(TestSlave_Index1017)/sizeof(TestSlave_Index1017[0]), 0x1017},
  { (subindex*)TestSlave_Index1018,sizeof(TestSlave_Index1018)/sizeof(TestSlave_Index1018[0]), 0x1018},
  { (subindex*)TestSlave_Index1200,sizeof(TestSlave_Index1200)/sizeof(TestSlave_Index1200[0]), 0x1200},
  { (subindex*)TestSlave_Index1400,sizeof(TestSlave_Index1400)/sizeof(TestSlave_Index1400[0]), 0x1400},
  { (subindex*)TestSlave_Index1401,sizeof(TestSlave_Index1401)/sizeof(TestSlave_Index1401[0]), 0x1401},
  { (subindex*)TestSlave_Index1600,sizeof(TestSlave_Index1600)/sizeof(TestSlave_Index1600[0]), 0x1600},
  { (subindex*)TestSlave_Index1601,sizeof(TestSlave_Index1601)/sizeof(TestSlave_Index1601[0]), 0x1601},
  { (subindex*)TestSlave_Index1800,sizeof(TestSlave_Index1800)/sizeof(TestSlave_Index1800[0]), 0x1800},
  { (subindex*)TestSlave_Index1801,sizeof(TestSlave_Index1801)/sizeof(TestSlave_Index1801[0]), 0x1801},
  { (subindex*)TestSlave_Index1A00,sizeof(TestSlave_Index1A00)/sizeof(TestSlave_Index1A00[0]), 0x1A00},
  { (subindex*)TestSlave_Index1A01,sizeof(TestSlave_Index1A01)/sizeof(TestSlave_Index1A01[0]), 0x1A01},
  { (subindex*)TestSlave_Index2000,sizeof(TestSlave_Index2000)/sizeof(TestSlave_Index2000[0]), 0x2000},
  { (subindex*)TestSlave_Index2001,sizeof(TestSlave_Index2001)/sizeof(TestSlave_Index2001[0]), 0x2001},
  { (subindex*)TestSlave_Index2002,sizeof(TestSlave_Index2002)/sizeof(TestSlave_Index2002[0]), 0x2002},
  { (subindex*)TestSlave_Index2003,sizeof(TestSlave_Index2003)/sizeof(TestSlave_Index2003[0]), 0x2003},
  { (subindex*)TestSlave_Index2004,sizeof(TestSlave_Index2004)/sizeof(TestSlave_Index2004[0]), 0x2004},
  { (subindex*)TestSlave_Index2005,sizeof(TestSlave_Index2005)/sizeof(TestSlave_Index2005[0]), 0x2005},
  { (subindex*)TestSlave_Index2006,sizeof(TestSlave_Index2006)/sizeof(TestSlave_Index2006[0]), 0x2006},
  { (subindex*)TestSlave_Index2007,sizeof(TestSlave_Index2007)/sizeof(TestSlave_Index2007[0]), 0x2007},
  { (subindex*)TestSlave_Index2008,sizeof(TestSlave_Index2008)/sizeof(TestSlave_Index2008[0]), 0x2008},
  { (subindex*)TestSlave_Index2009,sizeof(TestSlave_Index2009)/sizeof(TestSlave_Index2009[0]), 0x2009},
  { (subindex*)TestSlave_Index200A,sizeof(TestSlave_Index200A)/sizeof(TestSlave_Index200A[0]), 0x200A},
  { (subindex*)TestSlave_Index200B,sizeof(TestSlave_Index200B)/sizeof(TestSlave_Index200B[0]), 0x200B},
  { (subindex*)TestSlave_Index200C,sizeof(TestSlave_Index200C)/sizeof(TestSlave_Index200C[0]), 0x200C},
};

const indextable * TestSlave_scanIndexOD (UNS16 wIndex, UNS32 * errorCode, ODCallback_t **callbacks)
{
	int i;
	*callbacks = NULL;
	switch(wIndex){
		case 0x1000: i = 0;break;
		case 0x1001: i = 1;break;
		case 0x1005: i = 2;*callbacks = TestSlave_Index1005_callbacks; break;
		case 0x1017: i = 3;*callbacks = TestSlave_Index1017_callbacks; break;
		case 0x1018: i = 4;break;
		case 0x1200: i = 5;break;
		case 0x1400: i = 6;break;
		case 0x1401: i = 7;break;
		case 0x1600: i = 8;break;
		case 0x1601: i = 9;break;
		case 0x1800: i = 10;*callbacks = TestSlave_Index1800_callbacks; break;
		case 0x1801: i = 11;*callbacks = TestSlave_Index1801_callbacks; break;
		case 0x1A00: i = 12;break;
		case 0x1A01: i = 13;break;
		case 0x2000: i = 14;*callbacks = pdo_m2s_rx_data_callbacks; break;
		case 0x2001: i = 15;break;
		case 0x2002: i = 16;*callbacks = sdo_m2s_rx_array_callbacks; break;
		case 0x2003: i = 17;break;
		case 0x2004: i = 18;break;
		case 0x2005: i = 19;break;
		case 0x2006: i = 20;*callbacks = pdo1_rx2_callbacks; break;
		case 0x2007: i = 21;*callbacks = pdo2_rx1_callbacks; break;
		case 0x2008: i = 22;*callbacks = pdo2_rx2_callbacks; break;
		case 0x2009: i = 23;break;
		case 0x200A: i = 24;break;
		case 0x200B: i = 25;break;
		case 0x200C: i = 26;break;
		default:
			*errorCode = OD_NO_SUCH_OBJECT;
			return NULL;
	}
	*errorCode = OD_SUCCESSFUL;
	return &TestSlave_objdict[i];
}

/* 
 * To count at which received SYNC a PDO must be sent.
 * Even if no pdoTransmit are defined, at least one entry is computed
 * for compilations issues.
 */
s_PDO_status TestSlave_PDO_status[2] = {s_PDO_status_Initializer,s_PDO_status_Initializer};

const quick_index TestSlave_firstIndex = {
  5, /* SDO_SVR */
  0, /* SDO_CLT */
  6, /* PDO_RCV */
  8, /* PDO_RCV_MAP */
  10, /* PDO_TRS */
  12 /* PDO_TRS_MAP */
};

const quick_index TestSlave_lastIndex = {
  5, /* SDO_SVR */
  0, /* SDO_CLT */
  7, /* PDO_RCV */
  9, /* PDO_RCV_MAP */
  11, /* PDO_TRS */
  13 /* PDO_TRS_MAP */
};

const UNS16 TestSlave_ObjdictSize = sizeof(TestSlave_objdict)/sizeof(TestSlave_objdict[0]); 

CO_Data TestSlave_Data = CANOPEN_NODE_DATA_INITIALIZER(TestSlave);
