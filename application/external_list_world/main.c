#include "external_list.h"
#include "genius_log.h"
#include <stdio.h>

struct student { // TCB
    struct external_list list;
    int id;
    int score;
};

static struct class { // xLIST
    char *name;
    int num_of_student;
    struct external_mini_list head;
};

static struct class class_1 = {
    .name = "class 1",
    .num_of_student = 0,
};

static struct student node1 = {
    .id = 1,
    .score = 70,
    .list.owner = &node1,
    .list.container = &class_1,
};

static struct student node2 = {
    .id = 2,
    .score = 80,
    .list.owner = &node2,
    .list.container = &class_1,
};
static struct student node3 = {
    .id = 3,
    .score = 75,
    .list.owner = &node3,
    .list.container = &class_1,
};

static void list_show(struct external_list *list_head)
{
    struct external_list *pos;

    if (!list_head)
        return;

    if (external_list_empty(list_head)) {
        printf("list is empty\n");
        return;
    }
    for (pos = list_head->next; pos != list_head; pos = pos->next) {
        struct student *s = (struct student *)pos->owner;
        struct class *c = (struct class *)pos->container;
        printf("%s: %d student, id = %d score = %d \n", c->name,
               c->num_of_student, s->id, s->score);
    }
    printf("\n");
}

void main(void)
{
    external_list_init(&class_1.head);
    printf("insert node1 from front\n");
    external_list_insert_front(&class_1.head, &node1.list);
    class_1.num_of_student++;
    list_show(&class_1.head);

    printf("insert node2 from front\n");
    external_list_insert_front(&class_1.head, &node2.list);
    class_1.num_of_student++;
    list_show(&class_1.head);

    printf("insert node3 from rear\n");
    external_list_insert_rear(&class_1.head, &node3.list);
    class_1.num_of_student++;
    list_show(&class_1.head);

    printf("delete node2\n");
    external_list_delete(&node2.list);
    class_1.num_of_student--;
    list_show(&class_1.head);
}
