#include "FreeRTOS.h"
#include "task.h"
#include <stdio.h>
#include <string.h>
#include "genius_log.h"

static TaskHandle_t pxTask1Handle;
static TaskHandle_t pxTask2Handle;

void vTask1(void *pvParameters)
{
    (void)pvParameters;
    for (;;) {
        ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
        osLog("%s call", pcTaskGetName(NULL));
    }
}

void vTask2(void *pvParameters)
{
    (void)pvParameters;
    for (;;) {
        vTaskDelay(pdTICKS_TO_MS(250));
        osLog("%s send notify to %s", pcTaskGetName(NULL),
              pcTaskGetName(pxTask1Handle));
        xTaskNotifyGive(pxTask1Handle);
    }
}

void main(void)
{
    xTaskCreate(vTask1, "vTask1", configMINIMAL_STACK_SIZE, "vTask1",
                configMAX_PRIORITIES - 3, &pxTask1Handle);
    xTaskCreate(vTask2, "vTask2", configMINIMAL_STACK_SIZE, "vTask2",
                configMAX_PRIORITIES - 3, &pxTask2Handle);
}