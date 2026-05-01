#include "FreeRTOS.h"
#include "task.h"
#include <stdio.h>
#include <string.h>

#define TOP_MAX_TASKS 16

static const char *prvTaskStateStr(eTaskState eState)
{
    switch (eState) {
    case eRunning:
        return "R";
    case eReady:
        return "Y";
    case eBlocked:
        return "B";
    case eSuspended:
        return "S";
    case eDeleted:
        return "D";
    default:
        break;
    }

    return "?";
}

void vTopTask(void *pvParameters)
{
    (void)pvParameters;

    TaskStatus_t *pxStats = pvPortMalloc(sizeof(TaskStatus_t) * TOP_MAX_TASKS);
    uint32_t *pulPrevRuntime = pvPortMalloc(sizeof(uint32_t) * TOP_MAX_TASKS);
    configASSERT(pxStats != NULL);
    configASSERT(pulPrevRuntime != NULL);

    memset(pulPrevRuntime, 0, sizeof(uint32_t) * TOP_MAX_TASKS);
    memset(pxStats, 0, sizeof(TaskStatus_t) * TOP_MAX_TASKS);

    TickType_t xLastWakeTime = xTaskGetTickCount();
    uint32_t ulPrevTotalTime = 0;
    BaseType_t xFirstRun = pdTRUE;

    for (;;) {
        vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(1000));

        UBaseType_t uxTaskCount = uxTaskGetNumberOfTasks();

        if (uxTaskCount > TOP_MAX_TASKS) {
            uxTaskCount = TOP_MAX_TASKS;
        }

        uint32_t ulTotalTime;
        UBaseType_t uxFilled =
            uxTaskGetSystemState(pxStats, uxTaskCount, &ulTotalTime);

        if (xFirstRun) {
            for (UBaseType_t i = 0; i < uxFilled; i++) {
                pulPrevRuntime[i] = pxStats[i].ulRunTimeCounter;
            }
            ulPrevTotalTime = ulTotalTime;
            xFirstRun = pdFALSE;
            continue;
        }

        uint32_t ulTotalDelta = ulTotalTime - ulPrevTotalTime;
        ulPrevTotalTime = ulTotalTime;

        /* Count task states */
        UBaseType_t uxRunning = 0, uxReady = 0, uxBlocked = 0, uxSuspended = 0,
                    uxDeleted = 0;

        for (UBaseType_t i = 0; i < uxFilled; i++) {
            switch (pxStats[i].eCurrentState) {
            case eRunning:
                uxRunning++;
                break;
            case eReady:
                uxReady++;
                break;
            case eBlocked:
                uxBlocked++;
                break;
            case eSuspended:
                uxSuspended++;
                break;
            case eDeleted:
                uxDeleted++;
                break;
            default:
                break;
            }
        }

        /* Uptime */
        uint32_t ulSec = xTaskGetTickCount() / configTICK_RATE_HZ;

        /* Header */
        printf("\033[2J\033[H");
        printf("===== FreeRTOS Top =====\n");
        printf("Uptime: %02u:%02u:%02u  Tasks: %u total",
               (unsigned)(ulSec / 3600), (unsigned)((ulSec % 3600) / 60),
               (unsigned)(ulSec % 60), (unsigned)uxFilled);

        if (uxRunning > 0)
            printf(", %u R", (unsigned)uxRunning);
        if (uxReady > 0)
            printf(", %u Y", (unsigned)uxReady);
        if (uxBlocked > 0)
            printf(", %u B", (unsigned)uxBlocked);
        if (uxSuspended > 0)
            printf(", %u S", (unsigned)uxSuspended);
        if (uxDeleted > 0)
            printf(", %u D", (unsigned)uxDeleted);

        printf("\n\n");

        printf("%-16s %4s  %-2s  %3s  %8s  %10s  %5s\n", "Name", "PID", "St",
               "Pri", "StackMin", "Runtime", "CPU%");
        printf("----------------------------------------------------\n");

        for (UBaseType_t i = 0; i < uxFilled; i++) {
            TaskStatus_t *pxT = &pxStats[i];
            uint32_t ulDelta = pxT->ulRunTimeCounter - pulPrevRuntime[i];

            pulPrevRuntime[i] = pxT->ulRunTimeCounter;

            uint32_t ulCpu =
                ulTotalDelta ? ((ulDelta * 100UL) / ulTotalDelta) : 0;

            if (ulCpu > 100) {
                ulCpu = 100;
            }

            printf("%-16s %4u  %-2s  %3u  %8u  %10u  %4u%%\n", pxT->pcTaskName,
                   (unsigned)pxT->xTaskNumber,
                   prvTaskStateStr(pxT->eCurrentState),
                   (unsigned)pxT->uxCurrentPriority,
                   (unsigned)pxT->usStackHighWaterMark, (unsigned)ulDelta,
                   (unsigned)ulCpu);
        }

        printf("\n");
    }
}
