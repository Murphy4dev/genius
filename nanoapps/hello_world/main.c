#include "FreeRTOS.h"
#include "task.h"
#include "uart.h"
#include <stdio.h>
#include <string.h>
#include <trcRecorder.h>

void vHelloworldTask(void *pvParameters)
{
    TickType_t xLastWakeTime;

    (void)pvParameters;
    xLastWakeTime = xTaskGetTickCount();
    for (;;) {
        vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(500));
        printf("%s: welcome to freertos !!! \n", pcTaskGetName(NULL));
    }
}

void main(void)
{
    xTraceInitialize();
	xTraceEnable(TRC_START);
	xTraceTimestampSetPeriod(configCPU_CLOCK_HZ/configTICK_RATE_HZ);

    prvUARTInit();

    xTaskCreate(
        vHelloworldTask,
        "hello_world",
        configMINIMAL_STACK_SIZE,
        NULL,
        1,
        NULL
    );

    vTaskStartScheduler();
    for (;;) {
        // will never reach heer normally
    }
}