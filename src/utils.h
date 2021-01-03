#ifndef _UTILS_H
#define _UTILS_H

	/* FUNCTION PROTOTYPES */
	unsigned int hash(char *str, int mod);
	int str2int(char *srt);
	int is_letter(char l);
	int is_digit(char l);
	int is_white(char l);
	char *shorten(char *str);
	char *concat(char *beggining, char *end);
	char *remove_quotes(char *str);
	char *remove_white(char *str);
	char *remove_comment(char *str);

#endif
