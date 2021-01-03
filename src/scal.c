/* HEADERS */
#include <errno.h>
#include <getopt.h>
#include <stdlib.h>
#include <stdio.h>

void
start_scal(void)
{
}

void
help(void)
{
	printf("scal [-h]\n");
	printf("     -h print this help text and exit\n");
}

int
main(int argc, char *argv[])
{
	char c;
	int interactive = 1;

	while ((c = getopt(argc,argv,"h")) != -1) {
		switch (c) {
			case 'h':                           /* add note */
				interactive = 0;
				help();
				return 0;
			case '?': /* leaving here for future reference */
				interactive = 0;
				if (optopt == 'i')
					printf("No file specified\n");
				else
					help();
				break;
			default:
				interactive = 0;
				help();
				return 0;
		}
	}

	if (interactive)
		start_scal();

	return 0;
}
