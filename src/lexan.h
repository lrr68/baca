#ifndef _LEXAN_H
#define _LEXAN_H

	#define IS_TOKEN(a, b) (strcmp(a, b) == 0)

	/* TYPES */
	typedef enum {
		ID,
		CONSTW,
		CONSTV,
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

	/* GLOBAL VARIABLES */
	extern char *read_lex; /* lexeme read */
	extern int line;       /* line number */

	void lexan(void);
	Token token_id(const char *t);

#endif
