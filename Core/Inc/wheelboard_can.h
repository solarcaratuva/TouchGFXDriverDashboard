#ifndef __WHEELBOARD_CAN_H__
#define __WHEELBOARD_CAN_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include "fdcan.h"

extern FDCAN_RxHeaderTypeDef 	RxHeader;
extern char 				RxData[8];

void FDCAN_Config(void);

// len must be part of the group FDCAN_data_length_code found in stm32u5xx_hal_fdcan.h
// thread safe
void send_can_message(uint32_t id, uint32_t len, uint8_t *data);

#ifdef __cplusplus
}
#endif

#endif /* __WHEELBOARD_CAN_H__ */