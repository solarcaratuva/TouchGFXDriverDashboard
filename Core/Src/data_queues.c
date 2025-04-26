#include "data_queues.h"

QueueHandle_t canReceivedQueue;

void setupDataQueues() {
  canReceivedQueue= xQueueCreate(1, sizeof(ReceivedCanData_t));
}