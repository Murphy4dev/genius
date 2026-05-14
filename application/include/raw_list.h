#ifndef RAW_LIST_H
#define RAW_LIST_H

#include <stddef.h>

struct raw_list {
    struct raw_list *next;
    struct raw_list *prev;
};

#define raw_list_entry(ptr, type, member) \
    ((type *)((char *)(ptr) - offsetof(type, member)))

#define raw_list_for_each(pos, head) \
    for (pos = (head)->next; pos != (head); pos = pos->next)

#define raw_list_for_each_safe(pos, n, head) \
    for (pos = (head)->next, n = pos->next; pos != (head); pos = n, n = pos->next)

#define raw_list_empty(head) ((head)->next == (head))

void raw_list_init(struct raw_list *head);
void raw_list_insert_front(struct raw_list *head, struct raw_list *list);
void raw_list_insert_rear(struct raw_list *head, struct raw_list *list);
void raw_list_delete(struct raw_list *list);

#endif
