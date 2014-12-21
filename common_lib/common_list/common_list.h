#ifndef __COMMON_LIST_H__
#define __COMMON_LIST_H__
#include <stdio.h>

#define unsigned int uint32_t

typedef struct common_list_struct
{
  struct common_list_struct   *next;
  struct common_list_struct   *prev;
  struct common_list_struct   *head;
  uint32_t                      size;
}
common_list;

#define common_list_entry(node, type, list_member)   \
    ((type *)((char*)(node) - ns_offsetof(type, list_member)))

//Initialize a list header
void common_list_init(common_list *head);

//Returns the length of the list
static inline uint32_t common_list_length(common_list *head)
{
	return head->size;
}

//Get the first list entry in list 'head'.
common_list *common_list_first(common_list *head);

#define COMMON_LIST_FIRST(xxhead)   (void *)common_list_first(xxhead)

//Get the last list entry in list 'head'.
common_list *common_list_last(common_list *head);

#define COMMON_LIST_LAST(xxhead)   (void *)common_list_last(xxhead)

//Get the next list entry following 'entry'.
common_list *common_list_next(common_list *entry);

#define COMMON_LIST_NEXT(xxentry)   (void *)common_list_next(xxentry)

//Get the previous list entry to 'entry'.
common_list *common_list_prev(common_list *entry);

#define COMMON_LIST_PREV(xxentry)   (void *)common_list_prev(xxentry)

//Insert list 'entry' first in the list 'head'.
void common_list_insert_first(common_list *head, common_list *entry);

//Insert list 'entry' last in the list 'head'.
void common_list_insert_last(common_list *head, common_list *entry);

//Insert the new list 'entry' before the entry 'inlist' which is already in a list.
void common_list_insert_before(common_list *inlist, common_list *entry);

//Insert the new list 'entry' after the entry 'inlist' which is already in a list.
void common_list_insert_after(common_list *inlist, common_list *entry);

//Remove list entry pointer to by 'entry' from its list.
void common_list_remove(common_list *entry);

//Unlink 'head' and make the first entry the new 'head'
common_list *common_list_unlink_head(common_list *head);

#endif
