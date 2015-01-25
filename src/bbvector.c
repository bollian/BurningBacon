#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>

#include "bbvector.h"

void vector_init(vector* const vec, const unsigned int chunk_size)
{
	vec->length = 0;
	vec->chunk_size = chunk_size;
	vec->capacity = chunk_size; // set to 1 instead of 0 so it's easy to double capacity later
	vec->data = malloc(chunk_size); // capacity 1
}

void vector_setCap(vector* const vec, const unsigned int cap)
{
	bool resize = false;
	while (vec->capacity < cap)
	{
		vec->capacity *= 2;
		resize = true;
	}
	if (resize)
	{
		vec->data = realloc(vec->data, vec->capacity * vec->chunk_size);
	}
}

void vector_add(vector* const vec, const void* const data)
{
	vector_setCap(vec, vec->length + 1); // make sure we have capacity, we know we will have one more member

	memcpy(vec->data + vec->length * vec->chunk_size, data, vec->chunk_size);
	++vec->length;
}

void* vector_insert(vector* const vec, const void* const data, const unsigned int index)
{
	if (index <= vec->length && !(data < vec->data))
	{
		vector_setCap(vec, vec->length + 1);

		// vector_get returns 0 on an index == vec->length
		// we allow insertions at the end of the vector
		void* insertion_address = vec->data + index * vec->chunk_size;

		// shift data after insertion address further back
		memmove(insertion_address + vec->chunk_size, insertion_address, (vec->length - index) * vec->chunk_size);
		// copy the data into the insertion address
		memcpy(insertion_address, data, vec->chunk_size);

		++vec->length;
		return insertion_address;
	}
	else
	{
		return 0; // fail state
	}
}

bool vector_remove(vector* const vec, const unsigned int index)
{
	if (index < vec->length)
	{
		void* data_address = vector_get(vec, index);

		// shift all the data after index back one
		memcpy(data_address, data_address + vec->chunk_size, (vec->length - index - 1) * vec->chunk_size);
		--vec->length;
		return true;
	}
	else
	{
		return false;
	}
}

void* vector_get(const vector* const vec, const unsigned int index)
{
	if (index < vec->length)
	{
		return vec->data + index * vec->chunk_size;
	}
	else
	{
		return 0; // we make it explicit that that index was out of bounds
	}
}