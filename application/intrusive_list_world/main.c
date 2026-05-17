#include "raw_list.h"
#include "genius_log.h"
#include <stdio.h>

struct student {
    struct raw_list list;
    int id;
    int score;
};

static struct raw_list head;
static struct student node1 = {
    .id = 1,
    .score = 70,
};
static struct student node2 = {
    .id = 2,
    .score = 80,
};
static struct student node3 = {
    .id = 3,
    .score = 75,
};

static void list_show(struct raw_list *list_head)
{
    struct raw_list *pos;

    if (!list_head)
        return;

    if (raw_list_empty(list_head)) {
        printf("list is empty\n");
        return;
    }
    for (pos = list_head->next; pos != list_head; pos = pos->next) {
        struct student *s =
            (struct student *)pos; // raw_list_entry(pos, struct student, list);
        printf("id = %d score = %d \n", s->id, s->score);
    }
    printf("\n");
}

void main(void)
{
    raw_list_init(&head);
    printf("insert node1 from front\n");
    raw_list_insert_front(&head, &node1.list);
    list_show(&head);

    printf("insert node2 from front\n");
    raw_list_insert_front(&head, &node2.list);
    list_show(&head);

    printf("insert node3 from rear\n");
    raw_list_insert_rear(&head, &node3.list);
    list_show(&head);

    printf("delete node2\n");
    raw_list_delete(&node2.list);
    list_show(&head);
}
