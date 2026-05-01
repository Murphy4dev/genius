#include "FreeRTOS.h"
#include "task.h"
#include <stdio.h>
#include <string.h>

static void do_something(uint32_t ulCount)
{
    for (uint32_t i = 0; i < ulCount; i++) {
        __asm volatile("NOP");
    }
}

void vHelloworldTask(void *pvParameters)
{
    TickType_t xLastWakeTime;

    (void)pvParameters;
    xLastWakeTime = xTaskGetTickCount();
    for (;;) {
        do_something(100000000);
        // printf("%s: welcome to freertos \n", pcTaskGetName(NULL));
    }
    vTaskDelete(NULL);
}

void main(void)
{
    xTaskCreate(vHelloworldTask, "hello_world", configMINIMAL_STACK_SIZE, NULL,
                1, NULL);
}