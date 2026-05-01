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

static void vFunction(void)
{
    volatile int a = 100;
    TaskStatus_t xTaskStatus;

    vTaskGetInfo(NULL, &xTaskStatus, pdFALSE, eInvalid);
    StackType_t *pxStacBottom = xTaskStatus.pxStackBase;
    StackType_t *pxStackTop = pxStacBottom + configMINIMAL_STACK_SIZE;

    printf("%s: addr of a is 0x%x, stack [0x%x:0x%x]\r\n", pcTaskGetName(NULL),
           (unsigned int)&a, (unsigned int)pxStacBottom,
           (unsigned int)pxStackTop);
}

void vTask1(void *pvParameters)
{
    (void)pvParameters;
    for (;;) {
        vFunction();
        vDoSomething(500000000);
    }
}

void vTask2(void *pvParameters)
{
    (void)pvParameters;
    for (;;) {
        vFunction();
        vDoSomething(500000000);
    }
}

void main(void)
{
    xTaskCreate(vTask1, "vTask1", configMINIMAL_STACK_SIZE, "vTask1",
                configMAX_PRIORITIES - 1, &pxTask1Handle);
    xTaskCreate(vTask2, "vTask2", configMINIMAL_STACK_SIZE, "vTask2",
                configMAX_PRIORITIES - 1, &pxTask2Handle);
}