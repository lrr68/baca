#include <string.h>
#include <stdio.h>

#include "scal.h"
#include "codes.h"
#include "lexan.h"
#include "utils.h"

/* GLOBAL VARIABLES */
struct lexical_reg lexreg;
int line = 1;

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

void
lexan(void)
{
	int state = 0;
	int curr_pos = ftell(in_file);
	int lexerr = 0;
	int letter;

	((curr_pos));

	/* clear lexical register lexeme and token */
	lexreg.lex = "";
	lexreg.tk = 0;

	while (state != ACCEPT_LEX && !lexerr && (letter = fgetc(in_file)) != EOF) {

		/* always count the new line */
		if (letter == LINEFEED || letter == CR)
			line++;

		if (state == 0) {
			if (is_white(letter))
				continue;

		} else if (state == 1) {
		} else if (state == 2) {
		} else if (state == 3) {
		} else if (state == 4) {
		} else if (state == 5) {
		} else if (state == 6) {
		} else if (state == 7) {
		} else if (state == 8) {
		} else if (state == 9) {
		} else if (state == 10) {
		} else if (state == 11) {
		} else if (state == 12) {
		}

		curr_pos = ftell(in_file);
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

