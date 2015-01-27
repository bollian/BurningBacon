#include <stdint.h>

#include "bbsystem.h"

bool isLittleEndian()
{
	uint16_t n = 1;

	return (*(char*)&n) == 1;
}