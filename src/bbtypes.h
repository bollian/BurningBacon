#include <stdbool.h>
#include <stdint.h>

typedef unsigned char byte;


// Function pointers
typedef bool predicate(void*, size_t);
typedef int comparison(void*, void*, size_t, size_t);