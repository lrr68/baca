#include <errno.h>
#include <getopt.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "lang.h"
#include "synan.h"
#include "symtable.h"
#include "scal.h"
#include "lexan.h"

/* GLOBAL VARIABLES */
FILE *in_file;      /* input file      */
char *in_file_name; /* input file name */
ScalErr scal_err;   /* error code      */

/* FUNCTION DEFINITIONS */
void
scal_abort()
{
	switch (scal_err) {
		case ER_LEX_UNID:
			printf("Character not expected at line %d, col %d\n", line, column);
			break;
		case ER_LEX_EOF:
			printf("Unexpected EOF at line %d", line);
			break;
		case ER_SYN_NE:
			printf("Token [%s] not expected at line %d, col %d", lexreg.lex, line, column);
	}

	exit(-(scal_err));
}

void
start_scal(void)
{
}

void
help(void)
{
	printf("scal [-h] [-i]\n");
	printf("     -h print this help text and exit\n");
	printf("     -i interpret file\n");
	printf("     -  interpret from stdin\n");
}

int
main(int argc, char *argv[])
{
	char c;
	int open_file = 0;
	int interactive = 1;

	/* TODO: treat - to interpret form stdin */
	while ((c = getopt(argc,argv,"hi:")) != -1) {
		switch (c) {
			case 'h':                           /* add note */
				interactive = 0;
				help();
				return 0;
			case 'i':
				open_file = 1;
				interactive = 0;
				in_file_name = optarg;
				break;
			case '?':
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

	/* initialize symbol table */
	init_table();
	/* initialize the lexical register */
	init_lexreg();

	/* interactive mode */
	if (interactive) {
		start_scal();
		return 0;
	}

	/* non interactive mode */
	if (open_file) {
		if ((in_file = fopen(in_file_name, "r")) == NULL) {
			fprintf(stderr, "Error opening file at %s: %s\n", in_file_name, strerror(errno));
			exit(-errno);
		}
	} else {
		in_file = stdin;
	}

	start_synan();

	return 0;
}
