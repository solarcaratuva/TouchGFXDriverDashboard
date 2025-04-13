#include "fdcan.h"
#include "wheelboard_can.h"
#include <stdint.h>

FDCAN_RxHeaderTypeDef 	RxHeader;
FDCAN_TxHeaderTypeDef 	TxHeader;

char 				RxData[8];
char 				TxData[8];

void FDCAN_Config(void)
{
  FDCAN_FilterTypeDef sFilterConfig;

  /* Configure Rx filter */
  sFilterConfig.IdType 			= FDCAN_STANDARD_ID;
  sFilterConfig.FilterIndex 	= 0;
  sFilterConfig.FilterType 		= FDCAN_FILTER_MASK;
  sFilterConfig.FilterConfig 	= FDCAN_FILTER_TO_RXFIFO0;
  sFilterConfig.FilterID1 		= 0x00000000;

  if (HAL_FDCAN_ConfigFilter(&hfdcan1, &sFilterConfig) != HAL_OK)
  {
    /* Filter configuration Error */
    Error_Handler();
  }

  /* Start the FDCAN module */
  if (HAL_FDCAN_Start(&hfdcan1) != HAL_OK)
  {
    /* Start Error */
    Error_Handler();
  }

  // Enables CAN callback
  if (HAL_FDCAN_ActivateNotification(&hfdcan1, FDCAN_IT_RX_FIFO0_NEW_MESSAGE, 0) != HAL_OK)
  {
    /* Notification Error */
    Error_Handler();
  }

  /* Prepare Tx Header */
  TxHeader.Identifier 			= 12;
  TxHeader.IdType 				= FDCAN_STANDARD_ID;
  TxHeader.TxFrameType 			= FDCAN_DATA_FRAME;
  TxHeader.DataLength 			= FDCAN_DLC_BYTES_8;
  TxHeader.ErrorStateIndicator 	= FDCAN_ESI_ACTIVE;
  TxHeader.BitRateSwitch 		= FDCAN_BRS_OFF;
  TxHeader.FDFormat 			= FDCAN_CLASSIC_CAN;
  TxHeader.TxEventFifoControl 	= FDCAN_NO_TX_EVENTS;
  TxHeader.MessageMarker 		= 0;
}

void send_can_message(void)
{
    if (HAL_FDCAN_AddMessageToTxFifoQ(&hfdcan1, &TxHeader, TxData) != HAL_OK)
    {
        // Transmission error handling
        Error_Handler();
    }
}

// TODO: Does this work?
void HAL_FDCAN_RxFifo0Callback(FDCAN_HandleTypeDef *hfdcan1, uint32_t RxFifo0ITs)
{
  if((RxFifo0ITs & FDCAN_IT_RX_FIFO0_NEW_MESSAGE) != RESET)
  {
    /* Retreive Rx messages from RX FIFO0 */
    if (HAL_FDCAN_GetRxMessage(hfdcan1, FDCAN_RX_FIFO0, &RxHeader, RxData) != HAL_OK)
    {
    /* Reception Error */
    Error_Handler();
    }

    if (HAL_FDCAN_ActivateNotification(hfdcan1, FDCAN_IT_RX_FIFO0_NEW_MESSAGE, 0) != HAL_OK)
    {
      /* Notification Error */
      Error_Handler();
    }
  }
}