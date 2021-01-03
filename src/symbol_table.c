#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "lexan.h"
#include "symbol_table.h"
#include "utils.h"

/* GLOBAL VARIABLES */
struct Cell *symbol_table[TBL_SIZE];

/* FUNCTION DEFINITIONS */
void
add_reserved(void)
{
}

struct Cell
*add_symbol(char *lex, Token tk)
{
	unsigned int pos = hash(lex,TBL_SIZE);
	struct Cell *cel = (struct Cell *) malloc(sizeof(struct Cell));
	struct Symbol *simb = (struct Symbol *) malloc(sizeof(struct Symbol));
	simb->tk = tk;
	simb->lex = lex;
	simb->cl = 0;
	simb->type = 0;
	simb->size = 1;
	cel->next = NULL;
	cel->symbol = *simb;

	if (symbol_table[pos] == NULL) {
		symbol_table[pos] = cel;
	}else{
		symbol_table[pos]->next = cel;
	}
	return cel;
}

struct Cell
*search_symbol(char *needle)
{
	int found = 0;
	unsigned int pos = hash(needle,TBL_SIZE);
	struct Cell *ret = NULL;
	struct Cell *next = symbol_table[pos];

	while (!found && next != NULL) {
		if (next->symbol.lex != NULL && strcmp(next->symbol.lex, needle) == 0) {
			found = 1;
			ret = next;
		} else {
			next = next->next;
		}
	}
	return ret;
}

/* printa a tabela de symbols */
void
show_table(void)
{
	printf("=============SYMBOL TABLE=============\n");
	for (int i=0; i<TBL_SIZE; ++i) {
		if (symbol_table[i] != NULL) {
			printf("|\t%d\t|-> %s[%d]", i, symbol_table[i]->symbol.lex,symbol_table[i]->symbol.size);
			struct Cell *next = symbol_table[i]->next;
			while (next != NULL){
				printf(" -> %s",next->symbol.lex);
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
clear_list(struct Cell *cel)
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
