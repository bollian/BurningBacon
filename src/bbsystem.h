#ifndef BURNINGBACON_SYSTEM_H
#define BURNINGBACON_SYSTEM_H

#include <stdbool.h>

extern bool isLittleEndian();

extern char* getTerminalParam(int, char* const * const, const char* const);

#endif // BURNINGBACON_SYSTEM_H