#ifndef DATA_QUEUES_H__
#define DATA_QUEUES_H__

#ifdef __cplusplus
extern "C" {
#endif
#include "FreeRTOS.h"
#include "queue.h"

extern QueueHandle_t canReceivedQueue;

typedef struct {
  int test;
} ReceivedCanData_t;

void setupDataQueues();

#ifdef __cplusplus
}
#endif

#endif /* DATA_QUEUES_H__ */