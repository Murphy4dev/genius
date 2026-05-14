#include "raw_list.h"
#include "genius_log.h"
#include <stdio.h>

static struct raw_list head;
static struct raw_list node1;
static struct raw_list node2;
static struct raw_list node3;

static void raw_list_show(struct raw_list *head)
{
    struct raw_list *pos;

    if (!head)
        return;

    if (head->next == head) {
        osLog("list is empty");
        return;
    }
    osLog("head:0x%x", head);
    for (pos = head->next; pos != head; pos = pos->next) {
        osLog("pos:0x%x", pos);
    }
    printf("\n");
}

void main(void)
{
    osLog("node1:0x%x,node2:0x%x,node3:0x%x\n", &node1, &node2, &node3);

    raw_list_init(&head);
    osLog("insert node1 from front");
    raw_list_insert_front(&head, &node1);
    raw_list_show(&head);

    osLog("insert node2 from front");
    raw_list_insert_front(&head, &node2);
    raw_list_show(&head);

    osLog("insert node3 from rear");
    raw_list_insert_rear(&head, &node3);
    raw_list_show(&head);

    osLog("delete node2");
    raw_list_delete(&node2);
    raw_list_show(&head);
}
