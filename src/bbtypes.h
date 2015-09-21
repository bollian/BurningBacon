#ifndef BURNINGBACON_TYPES_H_
#define BURNINGBACON_TYPES_H_

#include <stdbool.h>
#include <unistd.h>

// Function pointers
typedef bool predicate(void*, size_t);
typedef int comparison(void*, void*, size_t, size_t);

#endif // BURNINGBACON_TYPES_H_
