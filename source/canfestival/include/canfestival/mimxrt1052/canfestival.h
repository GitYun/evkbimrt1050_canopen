/*
This file is part of CanFestival, a library implementing CanOpen Stack.

Copyright (C): Edouard TISSERANT and Francis DUPIN
AVR Port: Andreas GLAUSER and Peter CHRISTEN

See COPYING file for copyrights details.

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/


#ifndef __CAN_CANFESTIVAL__
#define __CAN_CANFESTIVAL__

#include "applicfg.h"
#include "data.h"

// ---------  to be called by user app ---------

/**
 * @brief CANOpen timer initialization
 * @author yun (renqingyun@crprobot.com)
 * @date 2022-01-17
 * @version 0.1
 */
void initTimer(void);

/**
 * @brief CANOpen timer de-initialization
 * @author yun (renqingyun@crprobot.com)
 * @date 2022-01-17
 * @version 0.1
 */
void clearTimer(void);

/**
 * @brief canopen timer interrupt callback function or OS tick period callback function
 * @author yun (renqingyun@crprobot.com)
 * @date 2022-01-17
 * @version 0.1
 */
void timerElapsed(void);

/**
 * @brief Get CANOpen data handle
 * @author yun (renqingyun@crprobot.com)
 * @date 2022-01-17
 * @version 0.1
 * @return CO_Data* Pointer to a @ref CO_Data instance
 */
CO_Data* getCANOpenDataHandle(void);

/**
 * @brief CAN low-level(hardware) initialization
 * @author yun (renqingyun@crprobot.com)
 * @date 2022-01-17
 * @version 0.1
 * @param d CANOpen
 * @param bitrate
 * @return unsigned char
 */
UNS8 canInit(CO_Data * d, uint32_t bitrate);

/**
 * @brief
 * @author yun (renqingyun@crprobot.com)
 * @date 2022-01-17
 * @version 0.1
 */
void canClose(void);

/**
 * @brief Send a CAN message
 * @author yun (renqingyun@crprobot.com)
 * @date 2022-01-14
 * @version 0.1
 * @param notused not used in current version
 * @param m Pointer to a @ref Message instace
 * @return UNS8 1 - success, 0 - failed
 */
UNS8 canSend(CAN_PORT notused, Message *m);

/**
 * @brief Recevice a CAN message
 * @author yun (renqingyun@crprobot.com)
 * @date 2022-01-17
 * @version 0.1
 * @param m Pointer to a @ref Message instance, this version not used
 * @return unsigned char The number of byte received
 */
UNS8 canReceive(Message *m);

/**
 * @brief Set a standard CAN-ID filter by index internal filter list
 * @author yun (renqingyun@crprobot.com)
 * @date 2022-01-17
 * @version 0.1
 * @param index The index of internal filter list
 * @param can_id Standard CAN-ID
 * @param can_id_mask Standard CAN-ID mask
 */
void canSIDFilterSet(uint8_t index, uint16_t can_id, uint16_t can_id_mask);

/**
 * @brief LSS(Layer Setting Services) need to change node buad rate
 * @author yun (renqingyun@crprobot.com)
 * @date 2022-01-17
 * @version 0.1
 * @param port Poniter to a @ref CAN_PORT instace, not used for a CAN chip
 * @param baud The new baudrate to update the node baudrate
 * @return UNS8 1 - success, 0 - failed
 * @note LSS only provided by master node, and use LSS service need define the macro 'CO_ENABLE_LSS'
 */
UNS8 canChangeBaudRate(CAN_PORT port, char* baud);

#endif

