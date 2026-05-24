#include "FreeRTOS.h"
#include "task.h"
#include "ringQueue.h"
#include <stdio.h>

static int g_failures = 0;
#define check(cond, msg)                                                       \
    do {                                                                       \
        if (!(cond)) {                                                         \
            printf("  FAIL: %s [%s:%d]\n", msg, __FILE__, __LINE__);           \
            g_failures++;                                                      \
        } else {                                                               \
            printf("  PASS: %s\n", msg);                                       \
        }                                                                      \
    } while (0)

void main(void)
{
    int val, rval;

    /* ── Test 1: write one, read one ── */
    printf("\n== Test 1: single write/read ==\n");
    struct ringQueue *Q = createRingQueue(5, sizeof(int));
    check(Q != NULL, "createRingQueue returns non-NULL");
    check(Q->len == 5, "len == 5");
    check(Q->itemSize == sizeof(int), "itemSize == sizeof(int)");
    check(Q->filledCount == 0, "initial filledCount == 0");
    check(Q->pcWriteTo == Q->pcHead, "pcWriteTo starts at pcHead");

    val = 42;
    check(writeRingQueue(Q, &val) == 0, "write 42 returns 0");
    check(Q->filledCount == 1, "filledCount == 1 after write");

    rval = 0;
    check(readRingQueue(Q, &rval) == 0, "read returns 0");
    check(rval == 42, "read back 42");
    check(Q->filledCount == 0, "filledCount == 0 after read");

    /* ── Test 2: FIFO order ── */
    printf("\n== Test 2: FIFO order ==\n");
    int i;
    for (i = 0; i < 5; i++) {
        int v = i * 10;
        writeRingQueue(Q, &v);
    }
    for (i = 0; i < 5; i++) {
        rval = -1;
        readRingQueue(Q, &rval);
        check(rval == i * 10, "FIFO: value matches write order");
    }

    /* ── Test 3: write on full queue returns -1 ── */
    printf("\n== Test 3: full queue rejects write ==\n");
    for (i = 0; i < 5; i++) {
        int v = i + 100;
        check(writeRingQueue(Q, &v) == 0, "write to fill queue");
    }
    check(Q->filledCount == 5, "filledCount == 5 (full)");
    val = 999;
    check(writeRingQueue(Q, &val) == -1, "write on full queue returns -1");
    check(Q->filledCount == 5, "filledCount unchanged after rejected write");

    /* ── Test 4: read on empty queue returns -1 ── */
    printf("\n== Test 4: empty queue rejects read ==\n");
    for (i = 0; i < 5; i++) {
        readRingQueue(Q, &rval);
    }
    check(Q->filledCount == 0, "queue drained");
    check(readRingQueue(Q, &rval) == -1, "read on empty queue returns -1");
    check(rval == 104, "rval unchanged after rejected read");

    /* ── Test 5: wrap-around ── */
    printf("\n== Test 5: wrap-around ==\n");
    val = 11;
    writeRingQueue(Q, &val);
    val = 22;
    writeRingQueue(Q, &val);
    val = 33;
    writeRingQueue(Q, &val);
    readRingQueue(Q, &rval); /* 11 */
    readRingQueue(Q, &rval); /* 22 */
    val = 44;
    writeRingQueue(Q, &val);
    val = 55;
    writeRingQueue(Q, &val);
    val = 66;
    writeRingQueue(Q, &val);
    val = 77;
    writeRingQueue(Q, &val);
    /* queue: 33 44 55 66 77 (full, pcWriteTo wrapped) */
    check(Q->filledCount == 5, "filledCount == 5 after wrap writes");
    check(writeRingQueue(Q, &val) == -1, "full after wrap");
    int expected[] = {33, 44, 55, 66, 77};
    for (i = 0; i < 5; i++) {
        rval = -1;
        readRingQueue(Q, &rval);
        check(rval == expected[i], "wrap-around: correct value after wrap");
    }

    /* ── Test 6: fill-drain-refill ── */
    printf("\n== Test 6: fill-drain-refill ==\n");
    for (i = 0; i < 5; i++) {
        val = i + 200;
        writeRingQueue(Q, &val);
    }
    for (i = 0; i < 5; i++) {
        rval = -1;
        readRingQueue(Q, &rval);
        check(rval == i + 200, "refill: values correct");
    }
    check(Q->filledCount == 0, "refill: drained");
    check(Q->pcWriteTo == Q->pcReadFrom + Q->itemSize ||
              (Q->pcWriteTo == Q->pcHead &&
               Q->pcReadFrom == Q->pcHead + (Q->len - 1) * Q->itemSize),
          "refill: pcWriteTo and pcReadFrom consistent after drain");

    /* ── Report ── */
    printf("\n========================================\n");
    if (g_failures == 0) {
        printf("All tests PASSED.\n");
    } else {
        printf("%d test(s) FAILED.\n", g_failures);
    }
    printf("========================================\n");
}
