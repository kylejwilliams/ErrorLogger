
#include <time.h>

/* holds a time value and a pointer to a character string */
typedef struct data_struct
{
	time_t time;
	char *string;
} data_t;

int addMsg(data_t data);		/* inserts a copy of the data item at the end of the list */
void clearLog(void);			/* releases all the storage that has been allocated and empties the list of logged messages */
char *getLog(void);				/* allocates enough space for a string containing the entire log, copies the log into this 
								   string, and returns a pointer to the string */
int saveLog(char *filename);	/* saves the logged messages to a disk file */
