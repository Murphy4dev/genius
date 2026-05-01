#include "FreeRTOS.h"
#include "task.h"
#include <stdio.h>
#include <string.h>

static void vDoSomething(uint32_t ulCount)
{
    for (uint32_t i = 0; i < ulCount; i++) {
        __asm volatile("NOP");
    }
}

void main(void)
{
    for (;;) {
        vDoSomething(100000000);
        printf("%s: welcome to freertos \n", "main");
    }
}