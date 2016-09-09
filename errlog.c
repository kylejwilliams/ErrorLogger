
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <time.h>
#include <stdint.h> /* used for ptr -> int conversion */
#include "log.h"
#include "timeformat.h"

/*
 * cmd line args:
 *	-h				a usefule message describing the function of all the 
 *					command line arguments should be displayed.
 *	-help			see '-h'
 *	-n x			set the number of error messages to log to the list to 
 *					the integer x. The value of this variable should be logged 
 *					every time your program is run using the logging utility 
 *					above. The default value of this variable should be 42.
 *	-l filename		set the name of the log file. Default name is logfile.txt
 */
int main(int argc, char *argv[])
{
	char *filename = "logfile.txt";
	int errIter = 42; /* number of error messages to include in the list */

	int opt; /* holds the current command line argument */
	const char *short_opt = "n:l:h";
	struct option long_opt[] = 
	{
		{ "help", no_argument, NULL, 'h' }
	};

	while ((opt = getopt_long(argc, argv, short_opt, long_opt, NULL)) != -1)
	{
		switch (opt)
		{
			case -1:
			case 0:
				break;

			case 'h':
				printf("Usage: %s [OPTIONS]\n", argv[0]);
				printf("    -h, --help     Prints this help and exit\n");
				printf("    -n x           Sets a variable within the "
					   "program to x. Default value is '42'\n");
				printf("    -l filename    Sets the name of the logfile. "
					   "Default name is 'logfile.txt'\n");
				return 0;
				break;

			case 'l':
				filename = optarg;
				break;

			case 'n':
				errIter = atoi(optarg);
				break;

			case ':':
			case '?':
				printf("Try '%s --help' for more information.\n", argv[0]);
				return -2;

			default:
				printf("%s: invalid option -- %c\n", argv[0], opt);
				printf("Try '%s -- help' for more information.\n", argv[0]);
				return -2;
		}
	};
	
	//const int buffSize = 22; /* longest string: "[31 12 2016 23:59:59]" = 21 
	//							chars, plus one for '\0' */
	//char timeStr[buffSize];
	//formatTime(timeStr, buffSize);
	char *errMsg = "this is a test error message";
	time_t errTime = time(NULL);
	data_t tmpData = createMsg(errTime, errMsg);

	addMsg(tmpData);

	int key;
	if ( (key = (intptr_t)accessData()) >= 0)
	{
		getData(key, &tmpData);
		printf("%s : %s : %s\n", 
				argv[0], 
				getTime(&tmpData.time), 
				tmpData.string);
	}

		
	
	return 0;
}

