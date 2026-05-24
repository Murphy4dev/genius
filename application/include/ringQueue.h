#ifndef __RINGQUEUE__
#define __RINGQUEUE__
struct ringQueue {
    unsigned char *pcHead;
    unsigned char *pcTail;
    unsigned int len;
    unsigned int itemSize;

    unsigned char *pcReadFrom;
    unsigned char *pcWriteTo;
    unsigned int filledCount;
};
struct ringQueue *createRingQueue(unsigned len, unsigned itemSize);
int writeRingQueue(struct ringQueue *Q, void *value);
int readRingQueue(struct ringQueue *Q, void *value);
#endif