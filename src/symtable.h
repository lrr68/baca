#ifndef _ST_H
#define _ST_H

	/* MACROS */
	#define TBL_SIZE 254
	/*#define DEBUG_TS*/
	#ifdef DEBUG_TS
		#define DEBUGTS(s) printf("TS: %s\n",s); push(s,stack);
	#else
		#define DEBUGTS(s)
	#endif

	/* TYPES */
	struct symbol {
		int size;       /* array size           */
		char *lex;      /* lexeme               */
		int mem_addr;   /* memory address       */
		Type type;      /* int char double bool */
		Token tk;       /* symbol token         */
		Class cl;       /* constant or variable */
	};

	/* Chained list cell */
	struct cell {
		struct cell *next;
		struct symbol sym;
	};

	/* FUNCTION PROTOTYPES */
	Type type_find(char *identificador);
	void clear_table(void);
	void init_table(void);
	void add_reserved(void);
	void clear_list(struct cell *cel);
	struct cell *search_symbol(char *needle);
	struct cell *add_symbol(char *lex, Token tk);
	unsigned int hash(char *str, int mod);

	/* GLOBAL VARIABLES */
	extern struct cell *symbol_table[TBL_SIZE];

#endif
