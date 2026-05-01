#include "FreeRTOS.h"
#include "task.h"
#include <stdio.h>
#include <string.h>

static TaskHandle_t *pxTaskHandle = NULL;

static void vDoSomething(uint32_t ulCount)
{
    for (uint32_t i = 0; i < ulCount; i++) {
        __asm volatile("NOP");
    }
}

void vHelloWorldTask(void *pvParameters)
{
    const char *pcTaskName = pvParameters ? (const char *)pvParameters : "NULL";
    for (;;) {
        vDoSomething(100000000);
        printf("%s: welcome to freertos \n", pcTaskName);
    }
}

void main(void)
{
    xTaskCreate(vHelloWorldTask, "helloWorld", configMINIMAL_STACK_SIZE,
                "helloWorld", configMAX_PRIORITIES - 1, pxTaskHandle);
}