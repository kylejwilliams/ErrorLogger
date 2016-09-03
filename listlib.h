
#include <time.h>

typedef struct data_struct
{
	time_t time;
	char *string;
} data_t;

int accessData(void);
int addData(data_t data);
int freeKey(int key);
int getData(int key, data_t *data_p);

