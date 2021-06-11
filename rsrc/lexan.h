#ifndef _LEXAN_H
#define _LEXAN_H

	#define IS_TOKEN(a, b) (strcmp(a, b) == 0)
	#define ACCEPT_LEX 26
	#define A_TO_Z 'a': case 'b': case 'c': case 'd': \
			  case 'e': case 'f': case 'g': case 'h': \
			  case 'i': case 'j': case 'k': case 'l': \
			  case 'm': case 'n': case 'o': case 'p': \
			  case 'q': case 'r': case 's': case 't': \
			  case 'u': case 'v': case 'w': case 'x': \
			  case 'y': case 'z': case 'A': case 'B': \
			  case 'C': case 'D': case 'E': case 'F': \
			  case 'G': case 'H': case 'I': case 'J': \
			  case 'K': case 'L': case 'M': case 'N': \
			  case 'O': case 'P': case 'Q': case 'R': \
			  case 'S': case 'T': case 'U': case 'V': \
			  case 'W': case 'X': case 'Y': case 'Z'

	#define ONE_TO_NINE '1': case '2': case '3': \
                   case '4': case '5': case '6': \
			       case '7': case '8': case '9'

	/*#define DEBUG_LEX*/
	#ifdef DEBUG_LEX
		#define DEBUGLEX(...) printf(__VA_ARGS__);
	#else
		#define DEBUGLEX(...)
	#endif

	/* TYPES */
	struct lexical_reg {
		int pos;                     /* array access position, 0 if not array                      */
		int size;                    /* size of the variable, arrays have size > 1                 */
		char *lex;                   /* current read lexeme of the current command being read      */
		Type type;                   /* current type of the expression or id being interpreted     */
		Token tk;                    /* token of the current lexeme being read                     */
		Class cl;                    /* Class of the current read id                               */
		int st_addr;                 /* address of the current id on the symble table              */
	};

	/* GLOBAL VARIABLES */
	extern int line;                  /* line number       */
	extern int column;                /* column number     */
	extern int eofound;               /* reached EOF ?     */
	extern char *lex_err_msg;         /* error information */
	extern struct lexical_reg lexreg; /* lexical register  */

	/* FUNCTION PROTOTYPES */
	void lexan(void);
	void init_lexreg(void);
	Token token_id(const char *t);

#endif
