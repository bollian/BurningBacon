#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>

#include "bbvector.h"

void vector_init(vector* const vec, const unsigned int chunk_size)
{
	vec->length = 0;
	vec->chunk_size = chunk_size;
	vec->capacity = 1; // set to 1 instead of 0 so it's easy to double capacity later
	vec->data = malloc(chunk_size); // capacity 1
}

void vector_add(vector* const vec, const void* const data)
{
	// resize operation (changes vec->capacity, not vec->length)
	bool resize = false;
	while (vec->length == vec->capacity)
	{
		// more dramatic resizing, prevents frequent reallocation for repeated function calls when lots of data
		vec->capacity *= 2;
		resize = true;
	}
	if (resize)
	{
		vec->data = realloc(vec->data, vec->chunk_size * vec->capacity);
	}

	memcpy(vec->data + vec->length * vec->chunk_size, data, vec->chunk_size);
	++vec->length;
}

void vector_remove(vector* const vec, const unsigned int index)
{
	if (index < (vec->length))
	{
		void* data_address = vector_get(vec, index);

		// shift all the data after index back one
		memcpy(data_address, data_address + vec->chunk_size, (vec->length - index - 1) * vec->chunk_size);
		--vec->length;
	}
}

void* vector_get(const vector* const vec, const unsigned int index)
{
	if (index < vec->length)
	{
		return (char*)vec->data + (index * vec->chunk_size);
	}
	else
	{
		return 0; // we make it explicit that that index was out of bounds
	}
}