#ifndef BURNINGBACON_VECTOR_H
#define BURNINGBACON_VECTOR_H

#include <stdbool.h>

#include <bbtypes.h>

typedef struct Vector
{
	// the number of elements that can be currently held in the Vector
	unsigned int capacity;
	unsigned int length;
	// the size of each piece of data
	size_t chunk_size;
	void* data;
} Vector;

/**
  * initializes the Vector with a length of 0 and a capacity of 1 (one chunk)
  * accepts the sizeof(data_type) meant to be stored in the Vector
  * returns the address of the Vector, or NULL if the allocation fails
  **/
extern Vector* Vector_init(Vector* const, const size_t);
/**
  * frees the Vector array, does not free the Vector itself
  **/
extern Vector* Vector_free(Vector* const);
/**
  * grows the Vector capacity to atleast the number of chunks provided,
  * following the rule of doubling the capacity every time it is less than the required amount.
  * the resulting capacity can not be less than the current capacity
  * if setCap was unable to reallocate the data to create the required capacity, NULL is returned and the Vector remains unchanged
  * otherwise the address of the newly allocated data is returned
  **/
extern void* Vector_setCap(Vector* const, unsigned int);
/**
  * grows the Vector capacity to exactly the number of chunks provided
  * if the new capacity is less than the current one, any trailing data is freed
  * returns the same as Vector_setCap
  **/
extern void* Vector_setCapExact(Vector* const, const unsigned int);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
  * copies the new data to the end of the Vector, automatically resizing the array as necessary
  * returns the address of the addition or NULL on memory allocation error
  **/
extern void* Vector_add(Vector* const, const void* const);
/**
  * adds buffered data to the end of the Vector
  * third argument is the number of chunks to be added
  * returns the address of the addition
  **/
extern void* Vector_addBuffered(Vector* const, const void* const, const unsigned int);
/**
  * replaces the value at the Vector index with the index after it, following that pattern for all proceding indexes
  * returns true on success, false on failure (index out of range)
  **/
extern bool Vector_remove(Vector* const, const unsigned int);
/**
  * moves all the data at this and greater indexes one index higher, and copies the data into the resulting gap
  * returns the address that the data was copied to, NULL in the case of and index-out-of-bounds or a failed memory allocation
  **/
extern void* Vector_insert(Vector* const, const void* const, const unsigned int);
/**
  * returns the address of the specified index in the Vector, NULL if the index is out of bounds
  **/
extern void* Vector_get(const Vector* const, const unsigned int);
/**
  * returns the first element that matches according to the predicate, NULL if a match isn't found
  **/
extern void* Vector_find(const Vector* const, predicate*);
/**
  * searches the vector for all elements that match according to the predicate
  **/
extern int Vector_findAll(const Vector* const, predicate*, void***);

#endif // BURNINGBACON_VECTOR_H