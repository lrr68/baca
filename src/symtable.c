#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "lang.h"
#include "symtable.h"

/* GLOBAL VARIABLES */
struct cell *symbol_table[TBL_SIZE];

/* FUNCTION DEFINITIONS */
unsigned int
hash(char *str, int mod)
{
    unsigned int hash = 5381;
    int c;

    while ((c = *str++))
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return (hash % mod);
}

void
add_reserved(void)
{
	add_symbol("const", CONSTW);
	add_symbol("int", INT_TK);
	add_symbol("char", CHAR_TK);
	add_symbol("string", STRING_TK);
	add_symbol("double", DOUBLE_TK);
	add_symbol("bool", BOOL_TK);
	add_symbol("def", DEF);
	add_symbol("return", RETURN);
	add_symbol("++", D_PLUS);
	add_symbol("--", D_MINUS);
	add_symbol("+", PLUS);
	add_symbol("-", MINUS);
	add_symbol("*", TIMES);
	add_symbol("/", SLASH);
	add_symbol("+=", PLUS_E);
	add_symbol("-=", MINUS_E);
	add_symbol("*=", TIMES_E);
	add_symbol("/=", SLASH_E);
	add_symbol("\\", B_SLASH);
	add_symbol("%", MOD);
	add_symbol("**", POWER);
	add_symbol("!", FACTO);
	add_symbol("?", TERMIAL);
	add_symbol(":=", EQUALS);
	add_symbol("=", EQUALS);
	add_symbol("!=", DIFF);
	add_symbol("<>", DIFF);
	add_symbol(">", BIGGER);
	add_symbol(">=", BIG_EQ);
	add_symbol("<", SMALLER);
	add_symbol("<=", SML_EQ);
	add_symbol("not", NOT);
	add_symbol("&&", AND);
	add_symbol("and", AND);
	add_symbol("||", OR);
	add_symbol("or", OR);
	add_symbol("&", B_AND);
	add_symbol("|", B_OR);
	add_symbol("==", EQUALITY);
	add_symbol("while", WHILE);
	add_symbol("for", FOR);
	add_symbol("do", DO);
	add_symbol("if", IF);
	add_symbol("then", THEN);
	add_symbol("else", ELSE);
	add_symbol("elif", ELSEIF);
	add_symbol("read", READ);
	add_symbol("input", READ);
	add_symbol("print", PRINT);
	add_symbol("write", PRINT);
	add_symbol(";", SEMICO);
	add_symbol(".", PERIOD);
	add_symbol("(", O_BRACK);
	add_symbol(")", C_BRACK);
	add_symbol("{", O_CURLY);
	add_symbol("}", C_CURLY);
	add_symbol("[", O_BRACE);
	add_symbol("]", C_BRACE);
}

struct cell
*add_symbol(char *lex, Token tk)
{
	unsigned int pos = hash(lex,TBL_SIZE);
	struct cell *cel = (struct cell *) malloc(sizeof(struct cell));
	struct symbol *symb = (struct symbol *) malloc(sizeof(struct symbol));
	symb->tk = tk;
	symb->lex = lex;
	symb->cl = 0;
	symb->type = 0;
	symb->size = 1;
	cel->next = NULL;
	cel->sym = *symb;

	if (symbol_table[pos] == NULL) {
		symbol_table[pos] = cel;
	}else{
		symbol_table[pos]->next = cel;
	}
	return cel;
}

struct cell
*search_symbol(char *needle)
{
	int found = 0;
	unsigned int pos = hash(needle,TBL_SIZE);
	struct cell *ret = NULL;
	struct cell *next = symbol_table[pos];

	while (!found && next != NULL) {
		if (next->sym.lex != NULL && strcmp(next->sym.lex, needle) == 0) {
			found = 1;
			ret = next;
		} else {
			next = next->next;
		}
	}
	return ret;
}

/* prints symbol table */
void
show_table(void)
{
	printf("=============SYMBOL TABLE=============\n");
	for (int i=0; i<TBL_SIZE; ++i) {
		if (symbol_table[i] != NULL) {
			printf("|\t%d\t|-> %s[%d]", i, symbol_table[i]->sym.lex,symbol_table[i]->sym.size);
			struct cell *next = symbol_table[i]->next;
			while (next != NULL){
				printf(" -> %s",next->sym.lex);
				next = next->next;
			}
			printf("\n");
		}
	}
}

void
init_table(void)
{
    add_reserved();
}

/* Clears the linked list recursively
 * testing only
 */
void
clear_list(struct cell *cel)
{
	if (cel != NULL) {
		clear_list(cel->next);
		free(cel);
	}
}

/* Clear the symbol table
 * testing only
 */
void
clear_table(void)
{
	for (int i=0; i<TBL_SIZE; ++i) {
		if (symbol_table[i] != NULL) {
			clear_list(symbol_table[i]->next);
			free(symbol_table[i]);
			symbol_table[i] = NULL;
		}
	}
}
