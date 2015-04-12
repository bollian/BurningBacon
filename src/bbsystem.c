#include <stdint.h>
#include <string.h>

#include "bbsystem.h"
#include "bbstring.h"

bool isLittleEndian()
{
	uint16_t n = 1;

	return (*(char*)&n) == 1;
}

char* getTerminalParam(int argc, char* const * const argv, const char* const flag)
{
	const int flag_length = strlen(flag);

	for (int i = 1; i < argc; ++i)
	{
		switch (strcmp(flag, argv[i]))
		{
		case 0:
			if (i != argc)
			return argv[i + 1];
			break;
		case 1:
			if (strStartsWith(argv[i], flag) && argv[i][flag_length] == '=')
			{
				return argv[i] + flag_length + 1;
			}
			break;
		}
	}
	return NULL;
}