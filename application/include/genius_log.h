#ifndef GENIUS_LOG_H
#define GENIUS_LOG_H

#include "FreeRTOS.h"
#include "task.h"
#include <stdio.h>

#define osLog(format, ...)                                                     \
    do {                                                                       \
        TickType_t _t = xTaskGetTickCount();                                   \
        printf("[%u:%02u:%02u:%03u] %s:%d " format "\n",                       \
               (unsigned)(_t / 3600000UL), (unsigned)((_t / 60000UL) % 60),    \
               (unsigned)((_t / 1000UL) % 60), (unsigned)(_t % 1000UL),        \
               __func__, __LINE__, ##__VA_ARGS__);                             \
    } while (0)

#endif /* GENIUS_LOG_H */
