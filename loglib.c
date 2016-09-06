
#include <errno.h>
#include <stdlib.h>
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

int addMsg(data_t data)
{
	log_t *newNode;
	int nodeSize;

	nodeSize = sizeof(log_t) + strlen(data.string) + 1;
	if ((newNode = (log_t *)(malloc(nodeSize)) == NULL) /* couldn't add node */
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

void clearLog(void)
{

}

char *getLog(void)
{
	return NULL;
}

int saveLog(char *filename) 
{
	return 0;
}
