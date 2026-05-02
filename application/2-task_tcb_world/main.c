#include "FreeRTOS.h"
#include "task.h"
#include <stdio.h>
#include <string.h>

#define portSTART_ADDRESS_MASK ((StackType_t)0xfffffffeUL)
static TaskHandle_t pxTask1Handle;

static void vDoSomething(uint32_t ulCount)
{
    for (uint32_t i = 0; i < ulCount; i++) {
        __asm volatile("NOP");
    }
}

static void vtask1Task(void *pvParameters)
{
    const char *pcTaskName = pvParameters ? (const char *)pvParameters : "NULL";
    for (;;) {
        vDoSomething(500000000);
    }
}

void main(void)
{
    xTaskCreate(vtask1Task, "task1", configMINIMAL_STACK_SIZE,
                "pvParameters-task1", configMAX_PRIORITIES - 1, &pxTask1Handle);

    printf("vtask1Task = 0x%x pvParameters = 0x%x \n",
           ((StackType_t)vtask1Task) & portSTART_ADDRESS_MASK,
           "pvParameters-task1");

    printf("main finish \n");
}