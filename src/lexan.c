#include <string.h>
#include <stdio.h>

#include "scal.h"
#include "codes.h"
#include "lexan.h"
#include "utils.h"

/* GLOBAL VARIABLES */
int state;
int line = 1;
int eofound = 0;    /* reached EOF ?           */
int been_read = 0;  /* already read next char? */
struct lexical_reg lexreg;

/* FUNCTION DEFINITIONS */
void
init_lexreg(void)
{
	lexreg.pos = 0;
	lexreg.size = 0;
	lexreg.lex = NULL;
	lexreg.type = 0;
	lexreg.tk = 0;
	lexreg.cl = 0;
	lexreg.st_addr = -1;
}

void /* reading * or ** or *= */
do_state_1(int letter)
{
	switch (letter) {
		case '=':
			reglex.tk = TIMES_E;
			reglex = concatenate(reglex.lex, (char *) &letter);
			break;
		case '*':
			reglex.tk = POWER;
			reglex = concatenate(reglex.lex, (char *) &letter);
			break;
		default:
			reglex.tk = TIMES;
			/* read a next token character next lexan call
			 * does not have to read the first character */
			if (!IS_WHITE(letter))
				been_read = 1;
	}
	state = ACCEPT_LEX;
}

void /* reading + or ++ or += */
do_state_2(int letter)
{
	switch (letter) {
		case '+':
			reglex.tk = D_PLUS;
			reglex = concatenate(reglex.lex, (char *) &letter);
			break;
		case '=':
			reglex.tk = PLUS_E;
			reglex = concatenate(reglex.lex, (char *) &letter);
			break;
		default:
			reglex.tk = PLUS;
			/* read a next token character next lexan call
			 * does not have to read the first character */
			if (!IS_WHITE(letter))
				been_read = 1;
	}
	state = ACCEPT_LEX;
}

void /* reading - or -- or -= */
do_state_3(int letter)
{
	switch (letter) {
		case '-':
			reglex.tk = D_MINUS;
			reglex = concatenate(reglex.lex, (char *) &letter);
			break;
		case '=':
			reglex.tk = MINUS_E;
			reglex = concatenate(reglex.lex, (char *) &letter);
			break;
		default:
			reglex.tk = MINUS;
			/* read a next token character next lexan call
			 * does not have to read the first character */
			if (!IS_WHITE(letter))
				been_read = 1;
	}
	state = ACCEPT_LEX;
}

void /* reading / or /= or beggining of comment */
do_state_4(int letter)
{
	switch (letter) {
		case '*':
			state = 5;
			reglex = concatenate(reglex.lex, (char *) &letter);
			break;
		case '=':
			state = ACCEPT_LEX;
			reglex.tk = SLASH_E;
			reglex = concatenate(reglex.lex, (char *) &letter);
			break;
		default:
			state = ACCEPT_LEX;
			reglex.tk = SLASH;
			/* read a next token character next lexan call
			 * does not have to read the first character */
			if (!IS_WHITE(letter))
				been_read = 1;
	}
}

/* reading inside a comment,
 * ignore everything but ending of comment */
void
do_state_5(int letter)
{
	switch (letter) {
		case '*':
			state = 6;
			break;
	}
}

void /* '*' inside a comment or ending of comment */
do_state_6(int letter)
{
	switch (letter) {
		case '/': /* end comment */
			state = ACCEPT_LEX;
			break;
		default: /* '*' inside */
			state = 5;
	}
}

void /* := */
do_state_7(int letter)
{
	switch (letter) {
		case '=':
			state = ACCEPT_LEX;
			reglex.tk = EQUALS;
			reglex = concatenate(reglex.lex, (char *) &letter);
			break;
		default: /* lexeme unidentified */
			reglex = concatenate(reglex.lex, (char *) &letter);
			lexerr = ER_LEX_UNID;
	}
}

void /* = or == */
do_state_8(int letter)
{
	switch (letter) {
		case '=':
			reglex.tk = EQUALITY;
			reglex = concatenate(reglex.lex, (char *) &letter);
			break;
		default:
			reglex.tk = EQUALS;
			/* read a next token character next lexan call
			 * does not have to read the first character */
			if (!IS_WHITE(letter))
				been_read = 1;
	}

	state = ACCEPT_LEX;
}

void /* bitwise or logical and operation */
do_state_9(int letter)
{
	switch (letter) {
		case '&':
			reglex.tk = AND;
			reglex = concatenate(reglex.lex, (char *) &letter);
			break;
		default:
			reglex.tk = B_AND;
			/* read a next token character next lexan call
			 * does not have to read the first character */
			if (!IS_WHITE(letter))
				been_read = 1;
	}

	state = ACCEPT_LEX;
}

void /* bitwise or logical or operation */
do_state_10(int letter)
{
	switch (letter) {
		case '|':
			reglex.tk = OR;
			reglex = concatenate(reglex.lex, (char *) &letter);
			break;
		default:
			reglex.tk = B_OR;
			/* read a next token character next lexan call
			 * does not have to read the first character */
			if (!IS_WHITE(letter))
				been_read = 1;
	}

	state = ACCEPT_LEX;
}

void
do_state_11(int letter)
{
	switch (letter) {
		case '<++>':
			break;
	}
}

void
do_state_12(int letter)
{
	switch (letter) {
		case '<++>':
			break;
	}
}

void
do_state_13(int letter)
{
	switch (letter) {
		case '<++>':
			break;
	}
}

void
do_state_14(int letter)
{
	switch (letter) {
		case '<++>':
			break;
	}
}

void
do_state_15(int letter)
{
	switch (letter) {
		case '<++>':
			break;
	}
}

void
do_state_16(int letter)
{
	switch (letter) {
		case '<++>':
			break;
	}
}

void
do_state_17(int letter)
{
	switch (letter) {
		case '<++>':
			break;
	}
}

void
do_state_18(int letter)
{
	switch (letter) {
		case '<++>':
			break;
	}
}

void
do_state_19(int letter)
{
	switch (letter) {
		case '<++>':
			break;
	}
}

void
do_state_20(int letter)
{
	switch (letter) {
		case '<++>':
			break;
	}
}

void
do_state_21(int letter)
{
	switch (letter) {
		case '<++>':
			break;
	}
}

void
do_state_22(int letter)
{
	switch (letter) {
		case '<++>':
			break;
	}
}

void
do_state_23(int letter)
{
	switch (letter) {
		case '<++>':
			break;
	}
}

void
do_state_24(int letter)
{
	switch (letter) {
		case '<++>':
			break;
	}
}

void
do_state_25(int letter)
{
	switch (letter) {
		case '<++>':
			break;
	}
}

void
lexan(void)
{
	int lexerr = 0;
	int letter;

	/* clear state */
	state = 0;

	/* clear lexical register lexeme and token */
	if (lexreg.lex != NULL)
		free(lexreg.lex);

	lexreg.tk = 0;

	if (been_read && !eofound) {
		been_read = 0;
		goto skip_read;
	}

	while (state != ACCEPT_LEX && !lexerr && (letter = fgetc(in_file)) != EOF) {
skip_read:
		/* always count the new line */
		if (letter == LINEFEED || letter == CR)
			line++;

		switch (state) {
			case 0: /* reconizes first characters and single character lexemes */

				/* white space does not matter here */
				if (IS_WHITE(letter))
					continue;

				switch (letter) {
					case '*':
						state = 1;
						reglex = concatenate(reglex.lex, (char *) &letter);
						break;

					case '+':
						state = 2;
						reglex = concatenate(reglex.lex, (char *) &letter);
						break;

					case '-':
						state = 3;
						reglex = concatenate(reglex.lex, (char *) &letter);
						break;

					case '/':
						state = 4;
						reglex = concatenate(reglex.lex, (char *) &letter);
						break;

					case ':':
						state = 7;
						reglex = concatenate(reglex.lex, (char *) &letter);
						break;

					case '=':
						state = 8;
						reglex = concatenate(reglex.lex, (char *) &letter);
						break;

					case '&':
						state = 9;
						reglex = concatenate(reglex.lex, (char *) &letter);
						break;

					case '|':
						state = 10;
						reglex = concatenate(reglex.lex, (char *) &letter);
						break;

					case '>':
						state = 11;
						reglex = concatenate(reglex.lex, (char *) &letter);
						break;

					case '<':
						state = 12;
						reglex = concatenate(reglex.lex, (char *) &letter);
						break;

					case '_':
						state = 13;
						reglex = concatenate(reglex.lex, (char *) &letter);
						break;

					case A_TO_Z:
						state = 15;
						reglex = concatenate(reglex.lex, (char *) &letter);
						break;

					case '.':
						state = 16;
						reglex = concatenate(reglex.lex, (char *) &letter);
						break;

					case 1_TO_9:
						state = 18;
						reglex = concatenate(reglex.lex, (char *) &letter);
						break;

					case '0':
						state = 21;
						reglex = concatenate(reglex.lex, (char *) &letter);
						break;

					case '%':
						reglex.tk = MOD;
						state = ACCEPT_LEX;
						reglex = concatenate(reglex.lex, (char *) &letter);
						break;
					case '?':
						reglex.tk = TERMIAL;
						state = ACCEPT_LEX;
						reglex = concatenate(reglex.lex, (char *) &letter);
						break;
					case ';':
						reglex.tk = SEMICO;
						state = ACCEPT_LEX;
						reglex = concatenate(reglex.lex, (char *) &letter);
						break;
					case '(':
						reglex.tk = O_BRACK;
						state = ACCEPT_LEX;
						reglex = concatenate(reglex.lex, (char *) &letter);
						break;
					case ')':
						reglex.tk = C_BRACK;
						state = ACCEPT_LEX;
						reglex = concatenate(reglex.lex, (char *) &letter);
						break;
					case '[':
						reglex.tk = O_BRACE;
						state = ACCEPT_LEX;
						reglex = concatenate(reglex.lex, (char *) &letter);
						break;
					case ']':
						reglex.tk = C_BRACE;
						state = ACCEPT_LEX;
						reglex = concatenate(reglex.lex, (char *) &letter);
						break;
					case '{':
						reglex.tk = O_CURLY;
						state = ACCEPT_LEX;
						reglex = concatenate(reglex.lex, (char *) &letter);
						break;
					case '}':
						reglex.tk = C_CURLY;
						state = ACCEPT_LEX;
						reglex = concatenate(reglex.lex, (char *) &letter);
						break;
				}

				break;

			case 1:
				do_state_1(letter, &state);
				break;

			case 2:
				do_state_2(letter, &state);
				break;

			case 3:
				do_state_3(letter, &state);
				break;

			case 4:
				do_state_4(letter, &state);
				break;

			case 5:
				do_state_5(letter, &state);
				break;

			case 6:
				do_state_6(letter, &state);
				break;

			case 7:
				do_state_7(letter, &state);
				break;

			case 8:
				do_state_8(letter, &state);
				break;

			case 9:
				do_state_9(letter, &state);
				break;

			case 10:
				do_state_10(letter, &state);
				break;

			case 11:
				do_state_11(letter, &state);
				break;

			case 12:
				do_state_12(letter, &state);
				break;

			case 13:
				do_state_13(letter, &state);
				break;

			case 14:
				do_state_14(letter, &state);
				break;

			case 15:
				do_state_15(letter, &state);
				break;

			case 16:
				do_state_16(letter, &state);
				break;

			case 17:
				do_state_17(letter, &state);
				break;

			case 18:
				do_state_18(letter, &state);
				break;

			case 19:
				do_state_19(letter, &state);
				break;

			case 20:
				do_state_20(letter, &state);
				break;

			case 21:
				do_state_21(letter, &state);
				break;

			case 22:
				do_state_22(letter, &state);
				break;

			case 23:
				do_state_23(letter, &state);
				break;

			case 24:
				do_state_24(letter, &state);
				break;

			case 25:
				do_state_25(letter, &state);
				break;

		}
	}

	if (letter == EOF)
		eofound = 1;

	DEBUGLEX("LEX: lexeme:%s token:%d type:%d size: %d\n",lexreg.lex,lexreg.tk,lexreg.type,lexreg.size);
}

/* Identifies reserved words */
Token
token_id(const char *t)
{
	Token r = ID;
	if (IS_TOKEN(t, "const"))
		r = CONSTW;

	else if (IS_TOKEN(t, "int"))
		r = INT_TK;

	else if (IS_TOKEN(t, "double"))
		r = DOUBLE_TK;

	else if (IS_TOKEN(t, "char"))
		r = CHAR_TK;

	else if (IS_TOKEN(t, "string"))
		r = STRING_TK;

	else if (IS_TOKEN(t, "bool"))
		r = BOOL_TK;

	else if (IS_TOKEN(t, "not"))
		r = NOT;

	else if (IS_TOKEN(t, "and"))
		r = AND;

	else if (IS_TOKEN(t, "or"))
		r = OR;

	else if (IS_TOKEN(t, "while"))
		r = WHILE;

	else if (IS_TOKEN(t, "for"))
		r = FOR;

	else if (IS_TOKEN(t, "do"))
		r = DO;

	else if (IS_TOKEN(t, "if"))
		r = IF;

	else if (IS_TOKEN(t, "then"))
		r = THEN;

	else if (IS_TOKEN(t, "else"))
		r = ELSE;

	else if (IS_TOKEN(t, "elif"))
		r = ELSEIF;

	else if (IS_TOKEN(t, "read") || IS_TOKEN(t, "input"))
		r = READ;

	else if (IS_TOKEN(t, "print") || IS_TOKEN(t, "write"))
		r = PRINT;

	return r;
}

