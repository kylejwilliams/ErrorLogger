
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <time.h>
#include <stdint.h> /* used for ptr -> int conversion */
#include "log.h"
#include "timeformat.h"

void createErrorLog(int numErrors)
{
	srand(0); /* let's always use the same init value for debugging 
				 purposes */
	
	const int NUM_ERROR_MSGS = 5;
	char* errorMsgs[] = 
	{
		"This is not the byte you are looking for.",
		"Something went wrong. Very, very, very wrong.",
		"An error has occurred. (E-82FOO1F8).",
		"Self destruct sequence initiated...",
		"Beep-Boop, Your error has given me sentience"
	};

	int i;
	for (i = 0; i < numErrors; i++)
	{
		int msgIndex = rand() % NUM_ERROR_MSGS;

		char *msg = errorMsgs[msgIndex];
		time_t t = time(NULL);
		
		addMsg(createMsg(t, msg));
	}
}

int main(int argc, char *argv[])
{
	char *filename = "logfile.txt";
	int numErrs = 42; /* number of error messages to include in the list */

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
				numErrs = atoi(optarg);
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
	
	createErrorLog(numErrs);

	int key;
	data_t tmpData;

	key = (intptr_t)accessData();
	if (key < 0)
	{
		printf("Empty list");
		return;
	}
	while ((getData(key, &tmpData) == 0) && (tmpData.string != NULL))
	{
		printf("%s : %s : %s\n",
				argv[0],
				getTime(&tmpData.time),
				tmpData.string);
	}

	clearLog();
	printf("LOG CLEARED\n");

	key = (intptr_t)accessData();
	if (key < 0)
	{
		printf("Empty list");
		return;
	}
	while ((getData(key, &tmpData) == 0) && (tmpData.string != NULL))
	{
		printf("%s : %s : %s\n",
				argv[0],
				getTime(&tmpData.time),
				tmpData.string);
	}

	
	return 0;
}

