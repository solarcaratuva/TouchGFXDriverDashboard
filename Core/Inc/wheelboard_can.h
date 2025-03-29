#ifndef __WHEELBOARD_CAN_H__
#define __WHEELBOARD_CAN_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "fdcan.h"

extern FDCAN_RxHeaderTypeDef 	RxHeader;
extern FDCAN_TxHeaderTypeDef 	TxHeader;

extern char 				RxData[8];
extern char 				TxData[8];

void FDCAN_Config(void);

void send_can_message(void);

#ifdef __cplusplus
}
#endif

#endif /* __WHEELBOARD_CAN_H__ */