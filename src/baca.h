#ifndef _baca_H
#define _baca_H

	/* TYPES */
	typedef enum {
		ER_LEX_EOF = 1,
		ER_LEX_UNID,
		ER_SYN_NE,
	} BacaErr;

	/* FUNCTION PROTOTYPES */
	void baca_abort();

	/* GLOBAL VARIABLES */
	extern FILE *in_file;    /* input file */
	extern BacaErr baca_err; /* error code */

#endif
