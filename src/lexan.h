#ifndef _LEXAN_H
#define _LEXAN_H

	#define IS_TOKEN(a, b) (strcmp(a, b) == 0)
	#define ACCEPT_LEX 20

	/*#define DEBUG_LEX*/
	#ifdef DEBUG_LEX
		#define DEBUGLEX(...) printf(__VA_ARGS__);
	#else
		#define DEBUGLEX(...)
	#endif


	/* TYPES */
	typedef enum {
		ER_LEX = 1,
		ER_LEX_EOF,
		ER_LEX_INVD,
		ER_LEX_UNID,
	} LexErr;

	typedef enum {
		ID = 1,
		CONSTW,
		CONSTV,
		INT_TK,
		CHAR_TK,
		STRING_TK,
		DOUBLE_TK,
		BOOL_TK,
		D_PLUS,
		D_MINUS,
		PLUS,
		MINUS,
		TIMES,
		SLASH,
		B_SLASH,
		MOD,
		POWER,
		FACTO,
		TERMIAL,
		EQUALS,
		DIFF,
		BIGGER,
		BIG_EQ,
		SMALLER,
		SML_EQ,
		NOT,
		AND,
		OR,
		B_AND,
		B_OR,
		EQUALITY,
		WHILE,
		FOR,
		DO,
		IF,
		THEN,
		ELSE,
		ELSEIF,
		READ,
		PRINT,
	} Token;

	typedef enum {
		INT = 1,
		CHAR,
		STR,
		DOUBLE,
		BOOL,
	} Type;

	typedef enum {
		CONST = 1,
		VAR,
	} Class;

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
	extern int line;                  /* line number      */
	extern char *read_lex;            /* lexeme read      */
	extern struct lexical_reg lexreg; /* lexical register */

	/* FUNCTION PROTOTYPES */
	void lexan(void);
	void init_lexreg(void);
	Token token_id(const char *t);

#endif
