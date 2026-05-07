#include "FreeRTOS.h"
#include "semphr.h"

static StaticSemaphore_t xLogMutexBuffer;
SemaphoreHandle_t xLogMutex = NULL;

void vLogInit(void)
{
    xLogMutex = xSemaphoreCreateMutexStatic(&xLogMutexBuffer);
}
