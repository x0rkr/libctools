#include "libctools_std.h"
#include <stdlib.h>  
#include <string.h>  

char *strreplace(const char *str, const char *old_sub, const char *new_sub)
{
	if (str == NULL || old_sub == NULL || new_sub == NULL)
	{
		return NULL;
	}
	size_t old_len = strlen(old_sub);
	if (strlen(old_sub) == 0)
	{
		return strdup(str);
	}
	
	int count = 0;
	const char *pos = str;
	const char *next_match;
	
	while ((next_match = strstr(pos, old_sub)) != NULL)
	{
		count++;
		pos = next_match + strlen(old_sub);
	}
	
	size_t new_len = strlen(new_sub);
	size_t total_len = strlen(str) + count * (new_len - old_len) + 1;

	char *result = malloc(total_len);
	if (result == NULL) 
	{
		return NULL;
	}
	
	pos = str;
	char *dst = result;
	while ((next_match =  strstr(pos, old_sub))  != NULL)
	{
		size_t bytes_before = next_match - pos;
		//Move forward
		memcpy(dst, pos, bytes_before);
		dst += bytes_before;
		//copy replacement
		memcpy(dst, new_sub, new_len);
		dst += new_len;
		pos = next_match + old_len;
	}
	strcpy(dst, pos);
		
	return result;

}
