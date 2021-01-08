#include <stdio.h>

#include "lang.h"
#include "lexan.h"
#include "baca.h"
#include "lang.h"

/* FUNCTION PROTOTYPES */
int tokenmatch(Token t);
void start_synan(void);
void def(void);
void decl(void);
void comm(void);

/* FUNCTION DEFINITIONS */
int
tokenmatch(Token t)
{
	if (lexreg.tk != t) {
		baca_err = ER_SYN_NE;
		baca_abort();
	}

	lexan();
	return 1;
}

/* starts the syntax analyzer */
void
start_synan(void)
{
	do {

		lexan();
		switch (lexreg.tk) {
			/* FUNCTION */
			case DEF:
				def();
				break;

			/* DECLARATIONS */
			case CONST:     /* FALLTHROUGH */
			case INT_TK:    /* FALLTHROUGH */
			case DOUBLE_TK: /* FALLTHROUGH */
			case CHAR_TK:   /* FALLTHROUGH */
			case BOOL_TK:   /* FALLTHROUGH */
			case STRING_TK: /* FALLTHROUGH */
			case VOID_TK:
				decl();
				break;

			/* COMMAND */
			default:
				comm();
				break;
		}

	} while (!eofound && !baca_err);
}

void
def(void)
{
	return;
}

void
decl(void)
{
	return;
}

void
comm(void)
{
	return;
}
