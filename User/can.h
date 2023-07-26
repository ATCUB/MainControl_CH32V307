/*_CAN_H_*/
#ifndef _CAN_H_
#define _CAN_H_

#include "debug.h"

void CAN_Test_Mode_Init( u8 tsjw, u8 tbs2, u8 tbs1, u16 brp, u8 mode );
u8 CAN_Send_Msg( int32_t msg, u8 speed );
u8 CAN_Receive_Msg( u8 *buf );



























#endif /*_CAN_H_*/
