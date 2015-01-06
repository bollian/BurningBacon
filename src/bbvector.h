#ifndef BURNINGBACON_VECTOR_H
#define BURNINGBACON_VECTOR_H

typedef struct vector
{
	unsigned int capacity;
	unsigned int length;
	unsigned int chunk_size;
	void* data;
} vector;

// functions dealing with memory management
void vector_init(vector* const, const unsigned int);
void vector_free(vector* const);
void vector_setCap(vector* const, unsigned int);

// functions dealing with data management

/**
  * copies the new data to the end of the array
  * vec: the vector to be added to
  * data: the addresses of the data to be added
  * length: sizeof(*data)
  **/
void vector_add(vector* const, const void* const);

void vector_remove(vector* const, const unsigned int);
void vector_insert(vector* const, void*, const unsigned int);
void* vector_get(const vector* const, const unsigned int);

#endif // BURNINGBACON_VECTOR_H