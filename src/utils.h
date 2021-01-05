#ifndef _UTILS_H
#define _UTILS_H

	/* MACROS */
	#define IS_NUMBER(x) (48 <= x && x <= 57)
	#define IS_LETTER(x) (97 <= x && x <= 122)
	#define IS_WHITE(x)  (x == 9 || x == 10 || x == 13 || x == 32)

	/* FUNCTION PROTOTYPES */
	int str2int(char *srt);
	char *shorten(char *str);
	char *remove_white(char *str);
	char *remove_quotes(char *str);
	char *remove_comment(char *str);
	char *concatenate(char *beggining, char *end);

#endif
