#include "raw_list.h"

void raw_list_init(struct raw_list *head)
{
    if (!head)
        return;

    head->next = head;
    head->prev = head;
}

void raw_list_insert_front(struct raw_list *head, struct raw_list *list)
{
    struct raw_list *front;

    if (!head || !list)
        return;

    front = head->next;
    list->next = front;
    list->prev = head;
    front->prev = list;
    head->next = list;
}

void raw_list_insert_rear(struct raw_list *head, struct raw_list *list)
{
    struct raw_list *rear;

    if (!head || !list)
        return;

    rear = head->prev;
    list->next = head;
    list->prev = rear;
    head->prev = list;
    rear->next = list;
}

void raw_list_delete(struct raw_list *list)
{
    struct raw_list *front;
    struct raw_list *rear;

    if (!list)
        return;

    front = list->next;
    rear = list->prev;
    front->prev = rear;
    rear->next = front;
}
