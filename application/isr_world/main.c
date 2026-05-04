#include "FreeRTOS.h"
#include "task.h"
#include "genius_log.h"
#include "CMSDK_CM3.h"

static TaskHandle_t xNotifyTask;

void TIMER0_Handler(void)
{
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;

    CMSDK_TIMER0->INTCLEAR = 1;

    vTaskNotifyGiveFromISR(xNotifyTask, &xHigherPriorityTaskWoken);
    portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}

static void vNotifyTask(void *pvParameters)
{
    (void)pvParameters;
    for (;;) {
        ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
        osLog("%s woken by ISR notify", pcTaskGetName(NULL));
    }
}

void main(void)
{
    xTaskCreate(vNotifyTask, "notify", configMINIMAL_STACK_SIZE, NULL,
                configMAX_PRIORITIES - 3, &xNotifyTask);

    CMSDK_TIMER0->RELOAD = configCPU_CLOCK_HZ / configTICK_RATE_HZ * 500;
    CMSDK_TIMER0->CTRL = (1 << 3) | (1 << 0);

    NVIC_SetPriority(TIMER0_IRQn, configMAX_SYSCALL_INTERRUPT_PRIORITY);
    NVIC_EnableIRQ(TIMER0_IRQn);

    osLog("Timer0 ISR configured, will notify task every 500ms");
}
