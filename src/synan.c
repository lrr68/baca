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
void id_or_array(void);
void id_list(void);
void type(void);
void exprs(void);

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

/* starts the syntax analyzer
 * this function implements the S symbol on the grammar
 * */
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

	} while (!eofound);
}

/* function definition
 * def type() id(id_list()) { ... return exprs ;}
 */
void
def(void)
{
	tokenmatch(DEF);

	type();

	tokenmatch(IDENTIFIER);
	tokenmatch(O_BRACK);

	id_list();

	tokenmatch(C_BRACK);
	tokenmatch(O_CURLY);

	do {

		comm();

	} while (lexreg.tk != RETURN || lexreg.tk != C_CURLY);


	/* returns something */
	if (lexreg.tk == RETURN) {
		lexan();
		if (lexreg.tk != SEMICO) {
			exprs();
			tokenmatch(SEMICO);
		}
	}

	tokenmatch(C_CURLY);
}

/* variable or constant declaration
 * const? type() id (:=|= exprs)? ;
 */
void
decl(void)
{
	if (lexreg.tk == CONST_TK) {
		lexan();
		lexreg.cl = CONST;
	}

	type();

	id_or_array();

	if (lexreg.tk == EQUALS) {
		tokenmatch(EQUALS);
		exprs();
	}

	tokenmatch(SEMICO);
}

void
comm(void)
{
	return;
}

void
id_or_array(void)
{
	return;
}

void
id_list(void)
{
	return;
}

void
type(void)
{
	return;
}

void
exprs(void)
{
	return;
}
