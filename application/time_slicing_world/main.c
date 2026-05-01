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

void vTask1(void *pvParameters)
{
    (void)pvParameters;

    for (;;) {
        do_something(100000000);
        // printf("%s: welcome to freertos \n", pcTaskGetName(NULL));
    }
}

void vTask2(void *pvParameters)
{
    (void)pvParameters;

    for (;;) {
        do_something(100000000);
        // printf("%s: welcome to freertos \n", pcTaskGetName(NULL));
    }
}

void vTask3(void *pvParameters)
{
    (void)pvParameters;

    for (;;) {
        do_something(100000000);
        // printf("%s: welcome to freertos \n", pcTaskGetName(NULL));
    }
}

void main(void)
{
    xTaskCreate(vTask1, "vTask1", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
    xTaskCreate(vTask2, "vTask2", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
    xTaskCreate(vTask3, "vTask3", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
}