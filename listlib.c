/*****************************************************************************
 * FILE:		listlib.h
 * DESCRIPTION:	A list object implementation
 * AUTHOR:		Kyle Williams 
 * SOURCE:		[Robbins, Robbins, pg. 44-45]
 * DATE:		02 September 2016
 ****************************************************************************/

#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include "listlib.h"

#define TRAV_INIT_SIZE 8

typedef struct list_struct
{
	data_t item;
	struct list_struct *next;
} list_t;

static list_t endList;
static list_t *headPtr = NULL;
static list_t *tailPtr = NULL;
static list_t **travPtrs = NULL;
static int travPtrs_size = 0;

/* retrun a nonnegative key if successful */
int accessData(void)
{
	int i;
	list_t **newPtrs;
	
	if (headPtr == NULL) /* Can't access a completely empty list */
	{
		errno = EINVAL;
		return -1;
	}

	if (travPtrs_size == 0) /* first traversal */
	{
		travPtrs = (list_t **)calloc(TRAV_INIT_SIZE, sizeof(list_t *));

		if (travPtrs == NULL) /* couldn't allocate space for traversal keys */
			return -1;
		
		travPtrs[0] = headPtr;
		travPtrs_size = TRAV_INIT_SIZE;
		return 0;
	}

	for (i = 0; i < travPtrs_size; i++) /* look for an empty slot for key */
	{
		if (travPtrs[i] == NULL)
		{
			travPtrs[i] = headPtr;
			return i;
		}
	}

	newPtrs = realloc(travPtrs, 2*travPtrs_size*sizeof(list_t *));
	
	if (newPtrs == NULL)	/* couldn't expand the array of traversal keys */
		return -1;
	
	travPtrs = newPtrs;
	travPtrs[travPtrs_size] = headPtr;
	travPtrs_size *= 2;

	return travPtrs_size / 2;
}

/* allocate node for data and add to end of list */
int addData(data_t data)
{
	list_t *newNode;
	int nodeSize;
	
	nodeSize = sizeof(list_t) + strlen(data.string) + 1;
	if ((newNode = (list_t *)(malloc(nodeSize)) == NULL) /* couldn't add node */
		return -1;
	
	newNode->item.time = data.time;
	newNode->item.string = (char *)newNode + sizeof(list_t);
	strcpy(newNode->item.string, data.string);
	newNode->next = NULL;

	if (headPtr == NULL)
		headPtr = newNode;
	else
		tailPtr->next = newNode;
	
	tailPtr = newNode;
	return 0;
}

/* copy next item and set data_p->string */
int getData(int key, data_t *data_p) 
{
	list_t *t;

	if ( (key < 0) || (key >= travPtrs_size) || (travPtrs[key] == NULL) )
	{
		errno = EINVAL;
		return -1;
	}

	if (travPtrs[key] == &endList) /* end of list, set data_p->string to NULL */
	{
		data_p->string = NULL;
		travPtrs[key] = NULL;
		return 0; /* reaching end of list natural condition, not an error */
	}

	t = travPtrs[key];
	data_p->string = (char *)malloc(strlen(t->item.string) + 1);
	if (data_p->string == NULL) /* couldn't allocate space for returning string */
		return -1;
	
	data_p->time = t->item.time;
	strcpy(data_p->string, t->item.string);
	if (t->next == NULL)
		travPtrs[key] = &endlist;
	else
		travPtrs[key] = t->next;
	
	return 0;
}

/* free list entry corresponding to key */
int freeKey(int key) 
{
	if ( (key < 0) || (key >= travPtrs_size) ) /* key out of range */
	{
		errno = EINVAL;
		return -1;
	}

	travPtrs[key] = NULL;
	return 0;
}
