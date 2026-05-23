#include "FreeRTOS.h"
#include "task.h"
#include "list.h"
#include "genius_log.h"

struct student {
    int id;
    ListItem_t listIterm;
};

static List_t class;

static void list_show(List_t *list)
{
    ListItem_t *pos = listGET_HEAD_ENTRY(list);
    ListItem_t *end = listGET_END_MARKER(list); //&list->xListEnd;

    while (pos != end) {
        struct student *s = listGET_LIST_ITEM_OWNER(pos);
        List_t *c = listLIST_ITEM_CONTAINER(pos);
        osLog("num_of_student is %d, id = %d score = %d", c->uxNumberOfItems,
              s->id, pos->xItemValue);
        pos = listGET_NEXT(pos);
    }
}

static void list_show_2(List_t *list)
{
    int count = list->uxNumberOfItems;

    while (count--) {
        struct student *s;
        listGET_OWNER_OF_NEXT_ENTRY(s, list);
        osLog("num_of_student is %d, id = %d score = %d", list->uxNumberOfItems,
              s->id, s->listIterm.xItemValue);
    }
}

void main(void)
{
    struct student node1, node2, node3;

    vListInitialise(&class);

    vListInitialiseItem(&node1.listIterm);
    node1.id = 1;
    listSET_LIST_ITEM_OWNER(&node1.listIterm, &node1);
    listSET_LIST_ITEM_VALUE(&node1.listIterm, 90);
    vListInsertEnd(&class, &node1.listIterm);

    vListInitialiseItem(&node2.listIterm);
    node2.id = 2;
    listSET_LIST_ITEM_OWNER(&node2.listIterm, &node2);
    listSET_LIST_ITEM_VALUE(&node2.listIterm, 80);
    vListInsertEnd(&class, &node2.listIterm);

    vListInitialiseItem(&node3.listIterm);
    node3.id = 3;
    listSET_LIST_ITEM_OWNER(&node3.listIterm, &node3);
    listSET_LIST_ITEM_VALUE(&node3.listIterm, 100);
    vListInsertEnd(&class, &node3.listIterm);

    list_show(&class);
    list_show_2(&class);

    uxListRemove(&node1.listIterm);
    uxListRemove(&node2.listIterm);
    uxListRemove(&node3.listIterm);

    vListInsert(&class, &node1.listIterm);
    vListInsert(&class, &node2.listIterm);
    vListInsert(&class, &node3.listIterm);
    list_show(&class);
    list_show_2(&class);
}
