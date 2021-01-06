#ifndef _CODES_H
#define _CODES_H

	#define LINEFEED 10
	#define CR       13

	/* TYPES */
	typedef enum {
		ID = 1,
		CONSTW,
		LITERAL,
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
		PLUS_E,
		MINUS_E,
		TIMES_E,
		SLASH_E,
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
		SEMICO,
		PERIOD,
		O_BRACK,
		C_BRACK,
		O_CURLY,
		C_CURLY,
		O_BRACE,
		C_BRACE,
		DEF,
		RETURN,
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

#endif
