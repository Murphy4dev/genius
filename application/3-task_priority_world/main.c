#include "FreeRTOS.h"
#include "task.h"
#include <stdio.h>
#include <string.h>

static TaskHandle_t pxTask1Handle;
static TaskHandle_t pxTask2Handle;

static void vDoSomething(uint32_t ulCount)
{
    for (uint32_t i = 0; i < ulCount; i++) {
        __asm volatile("NOP");
    }
}

void vTask1(void *pvParameters)
{
    const char *pcTaskName = pvParameters ? (const char *)pvParameters : "NULL";
    for (;;) {
        vDoSomething(100000000);
        printf("%s priority:%d \n", pcTaskName, uxTaskPriorityGet(NULL));
    }
}

void vTask2(void *pvParameters)
{
    const char *pcTaskName = pvParameters ? (const char *)pvParameters : "NULL";
    for (;;) {
        vDoSomething(100000000);
        printf("%s priority:%d \n", pcTaskName, uxTaskPriorityGet(NULL));
        vTaskPrioritySet(pxTask1Handle, 5);
    }
}

void main(void)
{
    xTaskCreate(vTask1, "vTask1", configMINIMAL_STACK_SIZE, "vTask1", 3,
                &pxTask1Handle);
    xTaskCreate(vTask2, "vTask2", configMINIMAL_STACK_SIZE, "vTask2", 4,
                &pxTask2Handle);
}