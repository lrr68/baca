#include "string.h"

#include "lexan.h"

void
lexan(void)
{

}

Token
token_id(const char *t)
{
	Token r = ID;
	if (IS_TOKEN(t, "++"))
		r = D_PLUS;
	else if (IS_TOKEN(t, "const"))
		r = CONSTW;
	else if (IS_TOKEN(t, "--"))
		r = D_MINUS;
	else if (IS_TOKEN(t, "+"))
		r = PLUS;
	else if (IS_TOKEN(t, "-"))
		r = MINUS;
	else if (IS_TOKEN(t, "*"))
		r = TIMES;
	else if (IS_TOKEN(t, "\\"))
		r = B_SLASH;
	else if (IS_TOKEN(t, "%"))
		r = MOD;
	else if (IS_TOKEN(t, "**"))
		r = POWER;
	else if (IS_TOKEN(t, "!"))
		r = FACTO;
	else if (IS_TOKEN(t, "?"))
		r = TERMIAL;
	else if (IS_TOKEN(t, ":=") || IS_TOKEN(t, "="))
		r = EQUALS;
	else if (IS_TOKEN(t, "!="))
		r = DIFF;
	else if (IS_TOKEN(t, ">"))
		r = BIGGER;
	else if (IS_TOKEN(t, ">="))
		r = BIG_EQ;
	else if (IS_TOKEN(t, "<"))
		r = SMALLER;
	else if (IS_TOKEN(t, "<="))
		r = SML_EQ;
	else if (IS_TOKEN(t, "not"))
		r = NOT;
	else if (IS_TOKEN(t, "and") || IS_TOKEN(t, "&&"))
		r = AND;
	else if (IS_TOKEN(t, "or") || IS_TOKEN(t, "||"))
		r = OR;
	else if (IS_TOKEN(t, "&"))
		r = B_AND;
	else if (IS_TOKEN(t, "|"))
		r = B_OR;
	else if (IS_TOKEN(t, "=="))
		r = EQUALITY;
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
	else if (IS_TOKEN(t, "print"))
		r = PRINT;

	return r;
}
