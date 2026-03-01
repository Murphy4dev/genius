#include "FreeRTOS.h"
#include "task.h"
#include <stdio.h>
#include <string.h>

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