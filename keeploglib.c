
#include <stdio.h>
#include <stdlib.h>
#include <listlib.h>

/* execute cmd; store cmd and time in history list */
int runProc(char *cmd)
{
	data_t execute;

	if (time(&(execute.time)) == -1)
		return -1;
	
	execute.string = cmd;
	
	if (system(cmd) == -1) /* command could not be executed at all */
		return -1;
	
	return addData(execute);
}

/* output the history list of the file f */
void showHistory(FILE *f)
{
	data_t data;
	int key;

	key = accessData();
	if (key == -1)
	{
		fprintf(f, "No history\n");
		return;
	}

	while (!getData(key, &data) && (data.string != NULL))
	{
		fprintf(f, "Command: %s\nTIME: %s\n", data.string, ctime(&(data.time)));
		free(data.string);
	}
}
