#include <string.h>
#include "ringQueue.h"
#include "FreeRTOS.h"

struct ringQueue *createRingQueue(unsigned len, unsigned itemSize)
{
    struct ringQueue *queue = (struct ringQueue *)pvPortMalloc(
        sizeof(struct ringQueue) + len * itemSize);

    if (!queue)
        return NULL;

    queue->len = len;
    queue->itemSize = itemSize;
    queue->pcHead = (unsigned char *)queue + sizeof(struct ringQueue);
    queue->pcTail = queue->pcHead + len * itemSize;

    queue->filledCount = 0;
    queue->pcWriteTo = queue->pcHead; // next empty slot to write
    queue->pcReadFrom = queue->pcHead + (len - 1) * itemSize;

    return queue;
}

int writeRingQueue(struct ringQueue *Q, void *value)
{
    if (!Q || !value || Q->filledCount >= Q->len)
        return -1;

    memcpy(Q->pcWriteTo, (unsigned char *)value, Q->itemSize);
    Q->filledCount++;
    Q->pcWriteTo = Q->pcWriteTo + Q->itemSize;
    if (Q->pcWriteTo == Q->pcTail)
        Q->pcWriteTo = Q->pcHead;
    return 0;
}

int readRingQueue(struct ringQueue *Q, void *value)
{
    if (!Q || !value || Q->filledCount == 0)
        return -1;

    Q->pcReadFrom = Q->pcReadFrom + Q->itemSize;
    if (Q->pcReadFrom == Q->pcTail)
        Q->pcReadFrom = Q->pcHead;
    memcpy((unsigned char *)value, Q->pcReadFrom, Q->itemSize);
    Q->filledCount--;

    return 0;
}