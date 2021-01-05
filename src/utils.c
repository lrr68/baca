#include <string.h>
#include <stdlib.h>

/* FUNCTION DEFINITIONS */

/* ************************** *
      STRING MANIPULATION
 * ************************** */

int
str2int(char *str)
{
	int l = strlen(str);
	int val = 1; /* position value */
	int ret = 0;

	/* from the end (less significative position)
	 * multiplies each position by val (which is multiplied by 10 every iteraction)
	 * the value of position - 48 (ascii str to number ratio)
	 */
	for (int i = l-1; i >= 0; --i) {
		ret += (str[i]-48) * val;
		val*=10;
	}
	return ret;
}

/* remove str's last character */
char *
shorten(char *str)
{
	char *ret;
	int len = strlen(str);

	if (len > 1)
		return str;

	ret = (char *) malloc(sizeof(char) * len);

	for (int i=0; i<len-1; ++i)
		ret[i] = str[i];

	ret[len]='\0';

	return ret;
}

/* remove whitespace outside strings */
char *
remove_white(char *str)
{
	char *ret;
	int t = strlen(str);
	int c = 0;
	int concat = 0;

	ret = (char *)malloc(sizeof(char) * t);

	for (int i=0; i<t; ++i) {

		/* if is string do not concatenate until end of string */
		if (str[i] == '"')
			concat = !concat; /* toogle */

		/* concatenates non white or whites that should be concatenated */
		if ( !IS_WHITE(str[i]) || concat)
			ret[c++] = str[i];

	}
	/* end string */
	ret[c] = '\0';

	return (char *)realloc(ret,strlen(ret));
}

/* remove quotes and spaces outside them */
char *
remove_quotes(char *str)
{
	char *ret;
	int i;
	int c = 0;              /* ret counter      */
	int inside = 0;         /* is inside quotes */
	int len = strlen(str);

	ret = (char *) malloc(sizeof(char) * (len-2));

	for (i = 0; i<len; ++i) {
		if (str[i] == '"') {
			inside = !inside;
			continue;
		}
		if (inside)
			ret[c++] = str[i];
	}

	return ret;
}

char *
remove_comment(char *str)
{
	char *ret;
	int t = strlen(str);
	int c = 0;
	int concat = 1;

	ret = (char *)malloc(sizeof(char));

	for (int i=1; i<t; ++i) {
		/* if beggining of comment do not concat until end of comment */
		if (str[i-1] == '/' && str[i] == '*') {
			concat = 0;
		} else if (str[i-1] == '*' && str[i] == '/') {
			concat = 1;
			continue;
		} else if ( i<t && str[i] == '/' && str[i+1] == '*') {
			concat = 0;
		}
		if (concat)
			ret[c++] = str[i];
	}

	return ret;
}


char *
concatenate(char *str, const char *suffix)
{
	int l_str = strlen(str);
	int l_suffix = strlen(suffix);

	str = realloc(str, sizeof(char) * (l_str + l_suffix + 1));

	strncpy(&str[l_str], suffix, l_suffix);
	str[l_str + l_suffix] = '\0';

	return str;
}
