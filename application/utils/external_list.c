#include "external_list.h"

void external_list_init(struct external_mini_list *head)
{
    if (!head)
        return;

    head->next = head;
    head->prev = head;
}

void external_list_insert_front(struct external_mini_list *head,
                                struct external_list *list)
{
    struct external_list *front;

    if (!head || !list)
        return;

    front = head->next;
    list->next = front;
    list->prev = head;
    front->prev = list;
    head->next = list;
}

void external_list_insert_rear(struct external_mini_list *head,
                               struct external_list *list)
{
    struct external_list *rear;

    if (!head || !list)
        return;

    rear = head->prev;
    list->next = head;
    list->prev = rear;
    head->prev = list;
    rear->next = list;
}

void external_list_delete(struct external_list *list)
{
    struct external_list *front;
    struct external_list *rear;

    if (!list)
        return;

    front = list->next;
    rear = list->prev;
    front->prev = rear;
    rear->next = front;
}
