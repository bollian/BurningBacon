#ifndef BURNINGBACON_VECTOR_H
#define BURNINGBACON_VECTOR_H

#include <stdbool.h>

typedef struct vector
{
	unsigned int capacity;
	unsigned int length;
	// the size of each piece of data
	unsigned int chunk_size;
	void* data;
} vector;

/**
  * initializes the vector with a length of 0 and a capacity of 1 (one chunk)
  * returns the address of the vector array, or NULL if the allocation fails
  **/
extern void* vector_init(vector* const, const unsigned int);
/**
  * frees the vector array, does not free the vector itself
  **/
extern void vector_free(vector* const);
/**
  * grows the vector capacity to atleast the number provided,
  * following the rule of doubling the capacity every time it is less than the required amount.
  * the resulting capacity can not be less than the current capacity
  * if setCap was unable to reallocate the data to create the required capacity, NULL is returned and the vector remains unchanged
  * otherwise the address of the newly allocated data is returned
  **/
extern void* vector_setCap(vector* const, unsigned int);
extern void* vector_setCapExact(vector* const, const unsigned int);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
  * copies the new data to the end of the vector, automatically resizing the array as necessary
  * returns the address of the addition or NULL on memory allocation error
  **/
extern void* vector_add(vector* const, const void* const);
/**
  * replaces the value at the vector index with the index after it, following that pattern for all proceding indexes
  * returns true on success, false on failure (index out of range)
  **/
extern bool vector_remove(vector* const, const unsigned int);
/**
  * moves all the data at this and greater indexes one index higher, and copies the data into the resulting gap
  * returns the address that the data was copied to, NULL in the case of and index-out-of-bounds or a failed memory allocation
  **/
extern void* vector_insert(vector* const, const void* const, const unsigned int);
/**
  * returns the address of the specified index in the vector, NULL if the index is out of bounds
  **/
extern void* vector_get(const vector* const, const unsigned int);

#endif // BURNINGBACON_VECTOR_H