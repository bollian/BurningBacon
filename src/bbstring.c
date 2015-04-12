#include <stdbool.h>
#include <string.h>

#include "bbstring.h"

bool strStartsWith(const char* const str, const char* const pre)
{
	int len_str = strlen(str);
	int len_pre = strlen(pre);

	if (len_str < len_pre)
	{
		return false;
	}
	else
	{
		return strncmp(str, pre, len_pre) == 0;
	}
}