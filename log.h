
#include <time.h>

/* holds a time value and a pointer to a character string */
typedef struct data_struct
{
	time_t time;
	char *string;
} data_t;

/* creates a new error log meessage that may be added to the list */
data_t createMsg(time_t time, char *string);	

/* inserts a copy of the data item at the end of the list */
int addMsg(data_t data);

/* releases all the storage that has been allocated and empties the list of 
 * logged messages */
void clearLog(void);

/* allocates enough space for a string containing the entire log, copies the 
 * log into this string, and returns a pointer to the string */
char *getLog(void);						

/* saves the logged messages to a disk file */
int saveLog(char *filename);

/* Attempts to read the current head of the list. returns a nonnegative key 
 * if successful */
int accessData(void);					

/* copy next item and set data_p->string */
int getData(int key, data_t *data_p);	

/* free list entry corresponding to key */
int freeKey(int key);
