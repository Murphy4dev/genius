#ifndef EXTERNEL_LIST_H
#define EXTERNEL_LIST_H

#include <stddef.h>

struct external_list {
    struct external_list *next;
    struct external_list *prev;
    void *owner;
    void *container;
};

struct external_mini_list {
    struct external_list *next;
    struct external_list *prev;
};

#define external_list_entry(ptr, type, member)                                 \
    ((type *)((char *)(ptr) - offsetof(type, member)))

#define external_list_for_each(pos, head)                                      \
    for (pos = (head)->next; pos != (head); pos = pos->next)

#define external_list_for_each_safe(pos, n, head)                              \
    for (pos = (head)->next, n = pos->next; pos != (head);                     \
         pos = n, n = pos->next)

#define external_list_empty(head) ((head)->next == (head))

void external_list_init(struct external_mini_list *head);
void external_list_insert_front(struct external_mini_list *head,
                                struct external_list *list);
void external_list_insert_rear(struct external_mini_list *head,
                               struct external_list *list);
void external_list_delete(struct external_list *list);

#endif
