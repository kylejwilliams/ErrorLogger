
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "log.h"

#define TRAV_INIT_SIZE 8

typedef struct list_struct
{
	data_t item;
	struct list_struct *next;
} log_t;

static log_t endList;
static log_t *headPtr = NULL;
static log_t *tailPtr = NULL;
static log_t **travPtrs = NULL;
static int travPtrs_size = 0;

/* creates a new error log message that may be added to the list */
data_t createMsg(time_t time, char *string)
{
	data_t datum;
	datum.time = time;
	datum.string = string;

	return datum;
}
/* inserts a copy of the data item at the end of the list  */
int addMsg(data_t data)
{
	log_t *newNode;
	int nodeSize;

	nodeSize = sizeof(log_t) + strlen(data.string) + 1;
	if ((newNode = (log_t *)malloc(nodeSize)) == NULL) /* couldn't add node */
		return -1;
	
	newNode->item.time = data.time;
	newNode->item.string = (char *)newNode + sizeof(log_t);
	strcpy(newNode->item.string, data.string);
	newNode->next = NULL;

	if (headPtr == NULL)
		headPtr = newNode;
	else
		tailPtr->next = newNode;
	
	tailPtr = newNode;
	return 0;
}

/* releases all the storage that has been allocated and empties the list of 
 * logged messages  */
void clearLog(void)
{
	log_t *temp;
	while (headPtr != NULL)
	{
		temp = headPtr;
		headPtr = temp->next;
		free(temp);
	}
}

/* allocates enough space for a string containing the entire log, copies the 
 * log into this string, and returns a pointer to the string */
char *getLog(void)
{
	return NULL;
}

/* saves the logged messages to a disk file */
int saveLog(char *filename) 
{
	FILE *fp;

	fp = fopen(filename, "w");
	fprintf(fp, "%s", getLog());
	fclose(fp);

	return 0;
}

/* return a nonnegative key if successful */
int accessData(void)
{
	int i;
	log_t **newPtrs;

	if (headPtr == NULL) /* Can't access a completely empty list */
	{
		errno = EINVAL;
		return -1;
	}

	if (travPtrs_size == 0) /* first traversal */
	{
		travPtrs = (log_t **)calloc(TRAV_INIT_SIZE, sizeof(log_t *));

		if (travPtrs == NULL) return -1; /* couldn't allocate space for 
											traversal keys */

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

	newPtrs = realloc(travPtrs, 2 * travPtrs_size * sizeof(log_t *));

	if (newPtrs == NULL) return -1; /* couldn't expand the array of traversal
									   keys */

	travPtrs = newPtrs;
	travPtrs[travPtrs_size] = headPtr;
	travPtrs_size *= 2;

	return travPtrs_size / 2;
}

int getData(int key, data_t *data_p)
{
	log_t *t;
	
	if ( (key < 0) || (key >= travPtrs_size) || (travPtrs[key] == NULL) )
	{
		errno = EINVAL;
		return -1;
	}

	if (travPtrs[key] == &endList)
	{
		data_p->string = NULL;
		travPtrs[key] = NULL;
		return 0; /* reaching end of list natural condition; not an error */
	}

	t = travPtrs[key];
	data_p->string = (char *)malloc(strlen(t->item.string) + 1);
	if (data_p->string == NULL) return -1; /* couldn't allocate space for 
											  returning string */

	data_p->time = t->item.time;
	strcpy(data_p->string, t->item.string);
	if (t->next == NULL) travPtrs[key] = &endList;
	else travPtrs[key] = t->next;

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
