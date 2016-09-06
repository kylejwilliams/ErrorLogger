
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>

/*
 * cmd line args:
 *	-h				a usefule message describing the function of all the command line 
 *					arguments should be displayed.
 *	-help			see '-h'
 *	-n x			set a variable in your program to the integer x. The value of this 
 *					variable should be logged every time your program is run using the 
 *					logging utility above. The default value of this variable should be 42.
 *	-l filename		set the name of the log file. Default name is logfile.txt
 */
int main(int argc, char *argv[])
{
	char *filename = "logfile.txt";
	int myVar = 42;
	char helpMsg[] = "--insert an arbitrary help msg here--";

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
				printf("    -n x           Sets a variable within the program to x. Default value is '42'\n");
				printf("    -l filename    Sets the name of the logfile. Default name is 'logfile.txt'\n");
				return 0;
				break;

			case 'l':
				filename = optarg;
				break;

			case 'n':
				myVar = atoi(optarg);
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

	printf("this is the filename: %s\n", filename);
	printf("this is the int var:  %d\n", myVar);

	return 0;
}
