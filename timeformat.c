/*****************************************************************************
 * FILE:		timeformat.c
 * AUTHOR:		Kyle Williams
 * SOURCE:		stackoverflow.com/questions/5141960/get-the-current-time-in-c
 * DATE:		7 September 2016
 * DESCRIPTION:	Contains helper functions to get the current time of execution
 *				and format the string appropriately for display
 ****************************************************************************/

#include "timeformat.h"
#include "string.h"

void formatTime(char* output, int bufferSize)
{
	time_t rawTime;
	struct tm *timeInfo;

	time(&rawTime);
	timeInfo = localtime(&rawTime);

	snprintf(output, bufferSize, "[%d %d %d %d:%d:%d]", 
		timeInfo->tm_mday, 
		timeInfo->tm_mon + 1,
		timeInfo->tm_year + 1900,
		timeInfo->tm_hour,
		timeInfo->tm_min,
		timeInfo->tm_sec);
}

/* returns the current time */
char *getTime(time_t *t) 
{
	char *curTime = asctime(localtime(t));
	curTime[strlen(curTime) - 1] = 0; /* this is to strip off the '\n' 
										 character */
	return curTime;
}
