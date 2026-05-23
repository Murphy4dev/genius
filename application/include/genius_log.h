#ifndef GENIUS_LOG_H
#define GENIUS_LOG_H

#include "FreeRTOS.h"
#include "semphr.h"
#include "task.h"
#include <stdio.h>

extern SemaphoreHandle_t xLogMutex;

void vLogInit(void);

#define osLog(format, ...)                                                     \
    do {                                                                       \
        BaseType_t _os_sched = xTaskGetSchedulerState();                       \
        if (_os_sched == taskSCHEDULER_RUNNING) {                              \
            xSemaphoreTake(xLogMutex, portMAX_DELAY);                          \
        }                                                                      \
        TickType_t _t = xTaskGetTickCount();                                   \
        printf("[%u:%02u:%02u:%03u][%s:%d]: " format "\n",                     \
               (unsigned)(_t / 3600000UL), (unsigned)((_t / 60000UL) % 60),    \
               (unsigned)((_t / 1000UL) % 60), (unsigned)(_t % 1000UL),        \
               __func__, __LINE__, ##__VA_ARGS__);                             \
        if (_os_sched == taskSCHEDULER_RUNNING) {                              \
            xSemaphoreGive(xLogMutex);                                         \
        }                                                                      \
    } while (0)

#endif /* GENIUS_LOG_H */
