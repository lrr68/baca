#ifndef _SCAL_H
#define _SCAL_H

	/* TYPES */
	typedef enum {
		ER_LEX_EOF = 1,
		ER_LEX_UNID,
		ER_SYN_NE,
	} ScalErr;

	/* FUNCTION PROTOTYPES */
	void scal_abort();

	/* GLOBAL VARIABLES */
	extern FILE *in_file;    /* input file */
	extern ScalErr scal_err; /* error code */

#endif
