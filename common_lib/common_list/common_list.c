#include "common_list.h"

#define COMMON_LIST_ASSERT

#ifdef COMMON_LIST_DEBUG
#define print printf
#else
#define print
#endif

void common_list_init(common_list *head)
{
	head->next = head;
	head->prev = head;
	head->head = head;
	head->size = 0;
}

#ifdef COMMON_LIST_ASSERT
bool common_list_assert(common_list *head, common_list *entry)
{
	if(head == NULL && entry == NULL)
		return false;
	
	if(entry != NULL)
	{
		if(head == NULL)
			head = entry->head;
		if(entry->head == NULL || entry->next == NULL || entry->prev == NULL 
			|| entry->head != head)
			return false;
		if(head->size > 0)
		{
			if(entry->head == entry || entry->next == entry || entry->prev == entry 
				|| entry->prev->next != entry || entry->next->prev != entry)
				return false;
		}
	}

	if(head != NULL)
	{
		if(head->head != head || head->next == NULL || head->prev == NULL 
			|| head->size == 0 || (head->next == head && head->prev == head))
			return false;
	}
	
	return true;
}
#else
bool common_list_assert(common_list *head, common_list *entry)
{
	if(head == NULL && entry == NULL)
		return false;
	else
		return ture;
}
#endif

common_list *common_list_first(common_list *head)
{
	if(common_list_assert(head, NULL) == false)
	{
		print("common_list is fail !\n");
		return NULL;
	}
	
	if(head->next != head)
		return head->next;
	else
		return NULL;
}

common_list *common_list_last(common_list *head)
{
	if(common_list_assert(head, NULL) == false)
	{
		print("common_list is fail !\n");
		return NULL;
	}

	if(head->prev != head)
		return head->prev;
	else
		return NULL;
}

common_list *common_list_next(common_list *entry)
{
	if(common_list_assert(NULL, entry) == false)
	{
		print("common_list is fail !\n");
		return NULL;
	}

	if(entry->next != entry->head)
		return entry->next;
	else
		return NULL;
}

common_list *common_list_prev(common_list *entry)
{
	if(common_list_assert(NULL, entry) == false)
	{
		print("common_list is fail !\n");
		return NULL;
	}

	if(entry->prev != entry->head)
		return entry->prev;
	else
		return NULL;
}

void common_list_insert_first(common_list *head, common_list *entry)
{
	if(head == NULL || entry == NULL)
		return;

	entry->next = head->next;
	entry->prev = head;
	entry->next->prev = entry;
	entry->prev->next = entry;

	entry->head = head;
	head->size++;

	if(common_list_assert(head, entry) == false)
	{
		print("common_list is fail !\n");
		return;
	}
	return;
}

void common_list_insert_last(common_list *head, common_list *entry)
{
	if(head == NULL || entry ==NULL)
		return;

    entry->prev = head->prev;
    entry->next = head;
    entry->next->prev = entry;
    entry->prev->next = entry;

    entry->head = head;
    head->size++;

    if(common_list_assert(head, entry) == false)
	{
		print("common_list is fail !\n");
		return;
	}
	return;
}

void common_list_insert_before(common_list *inlist, common_list *entry)
{
	if(inlist == NULL || entry == NULL)
		return;

    if(common_list_assert(NULL, inlist) == false)
	{
		print("common_list is fail !\n");
		return;
	}

    entry->next = inlist;
    entry->prev = inlist->prev;

    entry->next->prev = entry;
    entry->prev->next = entry;

    entry->head = inlist->head;
    entry->head->size++;

    if(common_list_assert(NULL, entry) == false)
	{
		print("common_list is fail !\n");
		return;
	}
	return;
}

void common_list_insert_after(common_list *inlist, common_list *entry)
{
	if(inlist == NULL || entry == NULL)
		return;

    if(common_list_assert(NULL, inlist) == false)
	{
		print("common_list is fail !\n");
		return;
	}

    entry->prev = inlist;
    entry->next = inlist->next;

    entry->next->prev = entry;
    entry->prev->next = entry;

    entry->head = inlist->head;
    entry->head->size++;

    if(common_list_assert(NULL, entry) == false)
	{
		print("common_list is fail !\n");
		return;
	}
	return;

}

void common_list_remove(common_list *entry)
{
    if(common_list_assert(NULL, entry) == false)
	{
		print("common_list is fail !\n");
		return;
	}
    if(!(entry->head->size > 0))
		return;

    entry->next->prev = entry->prev;
    entry->prev->next = entry->next;

    entry->head->size--;
    entry->head = NULL;
	return;
}

common_list *common_list_unlink_head(common_list *head)
{
    common_list   *new_head = NULL;

    if(common_list_assert(head, NULL) == false)
	{
		print("common_list is fail !\n");
		return NULL;
	}

    new_head = head->next;
    if(new_head == head)
        return NULL;

    new_head->head = new_head;
    new_head->size = head->size - 1;
    new_head->prev = head->prev;
    new_head->prev->next = new_head;

    /* Restore the head pointer for all the members. */
    for(head = new_head->next; head != new_head; head = head->next)
        head->head = new_head;

    if(common_list_assert(new_head, NULL) == false)
	{
		print("common_list is fail !\n");
		return NULL;
	}
    return new_head;
}


