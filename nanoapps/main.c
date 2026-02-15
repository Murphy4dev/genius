#include "FreeRTOS.h"
#include "task.h"
#include "uart.h"
#include <stdio.h>
#include <string.h>
#include <trcRecorder.h>

static int count = 0;

void vPeriodicTask(void *pvParameters)
{
    TickType_t xLastWakeTime;

    (void)pvParameters;
    xLastWakeTime = xTaskGetTickCount();
    for (;;) {
        vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(20));
        printf("%s call %d \n", pcTaskGetName(NULL), count++);
    }
}

void main(void)
{
	char name[12] = {0};
    xTraceInitialize();
	xTraceEnable(TRC_START);
	xTraceTimestampSetPeriod(configCPU_CLOCK_HZ/configTICK_RATE_HZ);

    prvUARTInit();
    for (int i = 0; i < 3; i++) {
        snprintf(name, sizeof(name),"%s%d","Periodic_",i);
        xTaskCreate(
            vPeriodicTask,
            name,
            configMINIMAL_STACK_SIZE,
            NULL,
            1,
            NULL
        );
    }
    vTaskStartScheduler();

    for (;;);
}