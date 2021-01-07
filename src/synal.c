#include <scal.h>
#include <lang.h>

/* starts the syntax analyzer */
void
start_synal(void)
{
	do {

		lexan();
		switch (reglex.tk) {
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

	} while (!eofound && !scal_err);
}
