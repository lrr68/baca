#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "scal.h"
#include "codes.h"
#include "lexan.h"
#include "utils.h"

/* GLOBAL VARIABLES */
int state;
int line = 1;
int column = 0;
int eofound = 0;    /* reached EOF ?           */
int been_read = 0;  /* already read next char? */
char *lex_err_msg;  /* error information       */
struct lexical_reg lexreg;

/* FUNCTION DEFINITIONS */
void
init_lexreg(void)
{
	lexreg.pos = 0;
	lexreg.size = 0;
	lexreg.lex = malloc(sizeof(char));
	*lexreg.lex = '\0';
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
			lexreg.tk = TIMES_E;
			lexreg.lex = concatenate(lexreg.lex, (char *) &letter, 1);
			break;
		case '*':
			lexreg.tk = POWER;
			lexreg.lex = concatenate(lexreg.lex, (char *) &letter, 1);
			break;
		default:
			lexreg.tk = TIMES;
			/* read a next token character next lexan call
			 * does not have to read the first character */
			if (!IS_WHITE(letter))
				been_read = letter;
	}
	state = ACCEPT_LEX;
}

void /* reading + or ++ or += */
do_state_2(int letter)
{
	switch (letter) {
		case '+':
			lexreg.tk = D_PLUS;
			lexreg.lex = concatenate(lexreg.lex, (char *) &letter, 1);
			break;
		case '=':
			lexreg.tk = PLUS_E;
			lexreg.lex = concatenate(lexreg.lex, (char *) &letter, 1);
			break;
		default:
			lexreg.tk = PLUS;
			/* read a next token character next lexan call
			 * does not have to read the first character */
			if (!IS_WHITE(letter))
				been_read = letter;
	}
	state = ACCEPT_LEX;
}

void /* reading - or -- or -= */
do_state_3(int letter)
{
	switch (letter) {
		case '-':
			lexreg.tk = D_MINUS;
			lexreg.lex = concatenate(lexreg.lex, (char *) &letter, 1);
			break;
		case '=':
			lexreg.tk = MINUS_E;
			lexreg.lex = concatenate(lexreg.lex, (char *) &letter, 1);
			break;
		default:
			lexreg.tk = MINUS;
			/* read a next token character next lexan call
			 * does not have to read the first character */
			if (!IS_WHITE(letter))
				been_read = letter;
	}
	state = ACCEPT_LEX;
}

void /* reading / or /= or beggining of comment */
do_state_4(int letter)
{
	switch (letter) {
		case '*': /* beggining of comment, discard lexeme */
			state = 5;
			*lexreg.lex = '\0';
			break;
		case '=':
			state = ACCEPT_LEX;
			lexreg.tk = SLASH_E;
			lexreg.lex = concatenate(lexreg.lex, (char *) &letter, 1);
			break;
		default:
			state = ACCEPT_LEX;
			lexreg.tk = SLASH;
			/* read a next token character next lexan call
			 * does not have to read the first character */
			if (!IS_WHITE(letter))
				been_read = letter;
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
			state = 0;
			break;
		default: /* '*' inside */
			state = 5;
	}
}

void /* reading := */
do_state_7(int letter)
{
	switch (letter) {
		case '=':
			state = ACCEPT_LEX;
			lexreg.tk = EQUALS;
			lexreg.lex = concatenate(lexreg.lex, (char *) &letter, 1);
			break;
		default: /* lexeme unidentified */
			lexreg.lex = concatenate(lexreg.lex, (char *) &letter, 1);
			scal_err = ER_LEX_UNID;
	}
}

void /* reading = or == */
do_state_8(int letter)
{
	switch (letter) {
		case '=':
			lexreg.tk = EQUALITY;
			lexreg.lex = concatenate(lexreg.lex, (char *) &letter, 1);
			break;
		default:
			lexreg.tk = EQUALS;
			/* read a next token character next lexan call
			 * does not have to read the first character */
			if (!IS_WHITE(letter))
				been_read = letter;
	}

	state = ACCEPT_LEX;
}

void /* reading bitwise or logical and operation */
do_state_9(int letter)
{
	switch (letter) {
		case '&':
			lexreg.tk = AND;
			lexreg.lex = concatenate(lexreg.lex, (char *) &letter, 1);
			break;
		default:
			lexreg.tk = B_AND;
			/* read a next token character next lexan call
			 * does not have to read the first character */
			if (!IS_WHITE(letter))
				been_read = letter;
	}

	state = ACCEPT_LEX;
}

void /* reading bitwise or logical or operation */
do_state_10(int letter)
{
	switch (letter) {
		case '|':
			lexreg.tk = OR;
			lexreg.lex = concatenate(lexreg.lex, (char *) &letter, 1);
			break;
		default:
			lexreg.tk = B_OR;
			/* read a next token character next lexan call
			 * does not have to read the first character */
			if (!IS_WHITE(letter))
				been_read = letter;
	}

	state = ACCEPT_LEX;
}

void /* reading > or >= */
do_state_11(int letter)
{
	switch (letter) {
		case '=':
			lexreg.tk = BIG_EQ;
			lexreg.lex = concatenate(lexreg.lex, (char *) &letter, 1);
			break;
		default:
			lexreg.tk = BIGGER;
			/* read a next token character next lexan call
			 * does not have to read the first character */
			if (!IS_WHITE(letter))
				been_read = letter;
	}
}

void /* reading < or <> or <= */
do_state_12(int letter)
{
	switch (letter) {
		case '>':
			lexreg.tk = DIFF;
			lexreg.lex = concatenate(lexreg.lex, (char *) &letter, 1);
			break;
		case '=':
			lexreg.tk = SML_EQ;
			lexreg.lex = concatenate(lexreg.lex, (char *) &letter, 1);
			break;
		default:
			lexreg.tk = SMALLER;
			/* read a next token character next lexan call
			 * does not have to read the first character */
			if (!IS_WHITE(letter))
				been_read = letter;
	}
}

void /* reading an id starting with '_' */
do_state_13(int letter)
{
	switch (letter) {
		case '_':
			lexreg.lex = concatenate(lexreg.lex, (char *) &letter, 1);
			break;
		case A_TO_Z: /* FALLTHROUGH */
		case '0':    /* FALLTHROUGH */
		case ONE_TO_NINE:
			lexreg.lex = concatenate(lexreg.lex, (char *) &letter, 1);
			state = 14;
			break;
		default:
			scal_err = ER_LEX_UNID;
	}
}

void /* reading second part of an id [a-z0-9_]* */
do_state_14(int letter)
{
	switch (letter) {
		case '_':     /* FALLTHROUGH */
		case '0':     /* FALLTHROUGH */
		case A_TO_Z:  /* FALLTHROUGH */
		case ONE_TO_NINE:
			lexreg.lex = concatenate(lexreg.lex, (char *) &letter, 1);
			break;
		default:
			lexreg.tk = ID;
			state = ACCEPT_LEX;
			/* read a next token character next lexan call
			 * does not have to read the first character */
			if (!IS_WHITE(letter))
				been_read = letter;
	}
}

void /* reading a float starting with a . needs at least 1 number after .*/
do_state_15(int letter)
{
	switch (letter) {
		case '0':    /* FALLTHROUGH */
		case ONE_TO_NINE:
			lexreg.lex = concatenate(lexreg.lex, (char *) &letter, 1);
			state = 16;
			break;

		default:
			scal_err = ER_LEX_UNID;
	}
}

void /* reading remainder of float after . */
do_state_16(int letter)
{
	switch (letter) {
		case '0':    /* FALLTHROUGH */
		case ONE_TO_NINE:
			lexreg.lex = concatenate(lexreg.lex, (char *) &letter, 1);
			break;

		default:
			state = ACCEPT_LEX;
			lexreg.tk = LITERAL;
			lexreg.type = DOUBLE;
			/* read a next token character next lexan call
			 * does not have to read the first character */
			if (!IS_WHITE(letter))
				been_read = letter;
	}
}

/* reading a general number not starting with 0,
 * may be integer or float */
void
do_state_17(int letter)
{
	switch (letter) {
		case '0':    /* FALLTHROUGH */
		case ONE_TO_NINE:
			lexreg.lex = concatenate(lexreg.lex, (char *) &letter, 1);
			break;
		case '.':
			lexreg.lex = concatenate(lexreg.lex, (char *) &letter, 1);
			state = 18;
			break;
		default:
			lexreg.tk = LITERAL;
			state = ACCEPT_LEX;
			lexreg.type = INT;
			/* read a next token character next lexan call
			 * does not have to read the first character */
			if (!IS_WHITE(letter))
				been_read = letter;
	}
}

 /* reading floating part of a number.
  * must have at least 1 number */
void
do_state_18(int letter)
{
	switch (letter) {
		case '0':    /* FALLTHROUGH */
		case ONE_TO_NINE:
			lexreg.lex = concatenate(lexreg.lex, (char *) &letter, 1);
			state = 19;
			break;
		default:
			lexreg.lex = concatenate(lexreg.lex, (char *) &letter, 1);
			scal_err = ER_LEX_UNID;
	}
}

void /* reading remainder of floating part of the number */
do_state_19(int letter)
{
	switch (letter) {
		case '0':    /* FALLTHROUGH */
		case ONE_TO_NINE:
			lexreg.lex = concatenate(lexreg.lex, (char *) &letter, 1);
			break;
		default:
			state = ACCEPT_LEX;
			lexreg.tk = LITERAL;
			lexreg.type = DOUBLE;
			/* read a next token character next lexan call
			 * does not have to read the first character */
			if (!IS_WHITE(letter))
				been_read = letter;
	}
}

/* reading a number starting with 0,
 * may be binary, octal, decimal, duodecimal or hexadecimal */
void
do_state_20(int letter)
{
	switch (letter) {
		case 'b': /* BINARY */
			lexreg.lex = concatenate(lexreg.lex, (char *) &letter, 1);
			state = 21;
			break;
		case 'o': /* OCTAL */
			lexreg.lex = concatenate(lexreg.lex, (char *) &letter, 1);
			state = 22;
			break;
		case 'd': /* DUODECIMAL */
			lexreg.lex = concatenate(lexreg.lex, (char *) &letter, 1);
			state = 23;
			break;
		case 'x': /* HEXADECIMAL */
			lexreg.lex = concatenate(lexreg.lex, (char *) &letter, 1);
			state = 24;
			break;
		case '0': /* DECIMAL */
		case ONE_TO_NINE:
			lexreg.lex = concatenate(lexreg.lex, (char *) &letter, 1);
			state = 17;
			break;
		default:
			scal_err = ER_LEX_UNID;
	}
}

void /* reading a binary value */
do_state_21(int letter)
{
	switch (letter) {
		case '0': /* FALLTHROUGH */
		case '1':
			lexreg.lex = concatenate(lexreg.lex, (char *) &letter, 1);
			break;
		default:
			state = ACCEPT_LEX;
			lexreg.tk = LITERAL;
			lexreg.type = INT;
			/* read a next token character next lexan call
			 * does not have to read the first character */
			if (!IS_WHITE(letter))
				been_read = letter;
	}
}

void /* reading a octal number */
do_state_22(int letter)
{
	switch (letter) {
		case '0': /* FALLTHROUGH */
		case '1': /* FALLTHROUGH */
		case '2': /* FALLTHROUGH */
		case '3': /* FALLTHROUGH */
		case '4': /* FALLTHROUGH */
		case '5': /* FALLTHROUGH */
		case '6': /* FALLTHROUGH */
		case '7': /* FALLTHROUGH */
			lexreg.lex = concatenate(lexreg.lex, (char *) &letter, 1);
			break;
		default:
			state = ACCEPT_LEX;
			lexreg.tk = LITERAL;
			lexreg.type = INT;
			/* read a next token character next lexan call
			 * does not have to read the first character */
			if (!IS_WHITE(letter))
				been_read = letter;
	}
}

void /* reading a duodecimal number */
do_state_23(int letter)
{
	switch (letter) {
		case '0':    /* FALLTHROUGH */
		case ONE_TO_NINE: /* FALLTHROUGH */
		case 'D':    /* FALLTHROUGH */
		case 'E':    /* FALLTHROUGH */
		case 'd':    /* FALLTHROUGH */
		case 'e':    /* FALLTHROUGH */
			lexreg.lex = concatenate(lexreg.lex, (char *) &letter, 1);
			break;
		default:
			state = ACCEPT_LEX;
			lexreg.tk = LITERAL;
			lexreg.type = INT;
			/* read a next token character next lexan call
			 * does not have to read the first character */
			if (!IS_WHITE(letter))
				been_read = letter;
	}
}

void /* reading a hexadecimal number */
do_state_24(int letter)
{
	switch (letter) {
		case '0':    /* FALLTHROUGH */
		case ONE_TO_NINE: /* FALLTHROUGH */
		case 'a':    /* FALLTHROUGH */
		case 'b':    /* FALLTHROUGH */
		case 'c':    /* FALLTHROUGH */
		case 'd':    /* FALLTHROUGH */
		case 'e':    /* FALLTHROUGH */
		case 'f':    /* FALLTHROUGH */
		case 'A':    /* FALLTHROUGH */
		case 'B':    /* FALLTHROUGH */
		case 'C':    /* FALLTHROUGH */
		case 'D':    /* FALLTHROUGH */
		case 'E':    /* FALLTHROUGH */
		case 'F':    /* FALLTHROUGH */
			lexreg.lex = concatenate(lexreg.lex, (char *) &letter, 1);
			break;
		default:
			state = ACCEPT_LEX;
			lexreg.tk = LITERAL;
			lexreg.type = INT;
			/* read a next token character next lexan call
			 * does not have to read the first character */
			if (!IS_WHITE(letter))
				been_read = letter;
	}
}

void
lexan(void)
{
	int letter;
	int zero_column = 0;  /* should zero the column ? */

	scal_err = 0;

	/* clear state */
	state = 0;

	/* clear lexical register lexeme and token */
	*lexreg.lex = '\0';

	lexreg.tk = 0;

	if (been_read && !eofound) {
		letter = been_read;
		been_read = 0;
		goto skip_read;
	}

	while (state != ACCEPT_LEX && !scal_err && (letter = fgetc(in_file)) != EOF) {
		column++;
skip_read:
		if (zero_column)
			column = 0;

		/* always count the new line */
		if (letter == LINEFEED || letter == CR) {
			line++;
 			/* only zeroes column after lexeme was read so
			 * we save the current offset to it "zeroes" to the right position */
			zero_column = column;
		}

		switch (state) {
			case 0: /* reconizes first characters and single character lexemes */

				/* white space does not matter here */
				if (IS_WHITE(letter))
					continue;

				switch (letter) {
					case '*':
						state = 1;
						lexreg.lex = concatenate(lexreg.lex, (char *) &letter, 1);
						break;

					case '+':
						state = 2;
						lexreg.lex = concatenate(lexreg.lex, (char *) &letter, 1);
						break;

					case '-':
						state = 3;
						lexreg.lex = concatenate(lexreg.lex, (char *) &letter, 1);
						break;

					case '/':
						state = 4;
						lexreg.lex = concatenate(lexreg.lex, (char *) &letter, 1);
						break;

					case ':':
						state = 7;
						lexreg.lex = concatenate(lexreg.lex, (char *) &letter, 1);
						break;

					case '=':
						state = 8;
						lexreg.lex = concatenate(lexreg.lex, (char *) &letter, 1);
						break;

					case '&':
						state = 9;
						lexreg.lex = concatenate(lexreg.lex, (char *) &letter, 1);
						break;

					case '|':
						state = 10;
						lexreg.lex = concatenate(lexreg.lex, (char *) &letter, 1);
						break;

					case '>':
						state = 11;
						lexreg.lex = concatenate(lexreg.lex, (char *) &letter, 1);
						break;

					case '<':
						state = 12;
						lexreg.lex = concatenate(lexreg.lex, (char *) &letter, 1);
						break;

					case '_':
						state = 13;
						lexreg.lex = concatenate(lexreg.lex, (char *) &letter, 1);
						break;

					case A_TO_Z:
						state = 14;
						lexreg.lex = concatenate(lexreg.lex, (char *) &letter, 1);
						break;

					case '.':
						state = 15;
						lexreg.lex = concatenate(lexreg.lex, (char *) &letter, 1);
						break;

					case ONE_TO_NINE:
						state = 17;
						lexreg.lex = concatenate(lexreg.lex, (char *) &letter, 1);
						break;

					case '0':
						state = 20;
						lexreg.lex = concatenate(lexreg.lex, (char *) &letter, 1);
						break;

					case '%':
						lexreg.tk = MOD;
						state = ACCEPT_LEX;
						lexreg.lex = concatenate(lexreg.lex, (char *) &letter, 1);
						break;
					case '?':
						lexreg.tk = TERMIAL;
						state = ACCEPT_LEX;
						lexreg.lex = concatenate(lexreg.lex, (char *) &letter, 1);
						break;
					case ';':
						lexreg.tk = SEMICO;
						state = ACCEPT_LEX;
						lexreg.lex = concatenate(lexreg.lex, (char *) &letter, 1);
						break;
					case '(':
						lexreg.tk = O_BRACK;
						state = ACCEPT_LEX;
						lexreg.lex = concatenate(lexreg.lex, (char *) &letter, 1);
						break;
					case ')':
						lexreg.tk = C_BRACK;
						state = ACCEPT_LEX;
						lexreg.lex = concatenate(lexreg.lex, (char *) &letter, 1);
						break;
					case '[':
						lexreg.tk = O_BRACE;
						state = ACCEPT_LEX;
						lexreg.lex = concatenate(lexreg.lex, (char *) &letter, 1);
						break;
					case ']':
						lexreg.tk = C_BRACE;
						state = ACCEPT_LEX;
						lexreg.lex = concatenate(lexreg.lex, (char *) &letter, 1);
						break;
					case '{':
						lexreg.tk = O_CURLY;
						state = ACCEPT_LEX;
						lexreg.lex = concatenate(lexreg.lex, (char *) &letter, 1);
						break;
					case '}':
						lexreg.tk = C_CURLY;
						state = ACCEPT_LEX;
						lexreg.lex = concatenate(lexreg.lex, (char *) &letter, 1);
						break;
				}

				break;

			case 1:
				do_state_1(letter);
				break;

			case 2:
				do_state_2(letter);
				break;

			case 3:
				do_state_3(letter);
				break;

			case 4:
				do_state_4(letter);
				break;

			case 5:
				do_state_5(letter);
				break;

			case 6:
				do_state_6(letter);
				break;

			case 7:
				do_state_7(letter);
				break;

			case 8:
				do_state_8(letter);
				break;

			case 9:
				do_state_9(letter);
				break;

			case 10:
				do_state_10(letter);
				break;

			case 11:
				do_state_11(letter);
				break;

			case 12:
				do_state_12(letter);
				break;

			case 13:
				do_state_13(letter);
				break;

			case 14:
				do_state_14(letter);
				break;

			case 15:
				do_state_15(letter);
				break;

			case 16:
				do_state_16(letter);
				break;

			case 17:
				do_state_17(letter);
				break;

			case 18:
				do_state_18(letter);
				break;

			case 19:
				do_state_19(letter);
				break;

			case 20:
				do_state_20(letter);
				break;

			case 21:
				do_state_21(letter);
				break;

			case 22:
				do_state_22(letter);
				break;

			case 23:
				do_state_23(letter);
				break;

			case 24:
				do_state_24(letter);
				break;
		}
	}

	if (letter == EOF)
		eofound = 1;

	if (scal_err) {
		lex_err_msg = concatenate(lex_err_msg, (char *) &letter, 1);
		scal_abort(scal_err);
	}


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

