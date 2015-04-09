#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>

#include "bbvector.h"

void* vector_init(vector* const vec, const unsigned int chunk_size)
{
	vec->length = 0;
	vec->chunk_size = chunk_size;
	vec->capacity = 1; // set to 1 instead of 0 so it's easy to double capacity later
	vec->data = malloc(chunk_size); // capacity 1
	return vec->data;
}

void vector_free(vector* const vec)
{
	free(vec->data);
	vec->data = NULL;
}

void* vector_setCap(vector* const vec, const unsigned int cap)
{
	bool resize = false;
	unsigned int new_cap = vec->capacity; // in case we aren't able to realloc vec->data
	while (new_cap < cap)
	{
		new_cap *= 2;
		resize = true;
	}
	if (resize)
	{
		void* new_data = realloc(vec->data, new_cap * vec->chunk_size);
		if (new_data == NULL)
		{
			return NULL;
		}
		else
		{
			vec->data = new_data;
			vec->capacity = new_cap;
			return new_data;
		}
	}
}

void* vector_setCapExact(vector* const vec, const unsigned int cap)
{
	void* new_data = realloc(vec->data, cap * vec->chunk_size);
	if (new_data == NULL)
	{
		return NULL;
	}
	vec->data = new_data;
	return vec->data;
}

void* vector_add(vector* const vec, const void* const data)
{
	 // make sure we have capacity, we know we will have one more member
	if (vector_setCap(vec, vec->length + 1))
	{
		void* addition_address = vec->data + vec->length * vec->chunk_size;
		memcpy(addition_address, data, vec->chunk_size);
		++vec->length;

		return addition_address;
	}
	else
	{
		return NULL;
	}
}

void* vector_insert(vector* const vec, const void* const data, const unsigned int index)
{
	if (index <= vec->length && data != NULL)
	{
		// maybe it would be best to put this in the previous if, but I feel it is important to allow
		// the possibility of a different fail state
		if (vector_setCap(vec, vec->length + 1))
		{
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
			return NULL;
		}
	}
	else
	{
		return NULL; // fail state
	}
}

bool vector_remove(vector* const vec, const unsigned int index)
{
	if (index < vec->length)
	{
		void* data_address = vector_get(vec, index);

		// shift all the data after index back one
		memmove(data_address, data_address + vec->chunk_size, (vec->length - index - 1) * vec->chunk_size);
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
		return NULL; // we make it explicit that that index was out of bounds
	}
}