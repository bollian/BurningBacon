#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>

#include <bbvector.h>
#include <bbtypes.h>

Vector* Vector_init(Vector* const vec, const size_t chunk_size)
{
	vec->length = 0;
	vec->chunk_size = chunk_size;
	vec->capacity = 1; // set to 1 instead of 0 so it's easy to double capacity later
	vec->data = malloc(chunk_size); // capacity 1
	return vec;
}

Vector* Vector_free(Vector* const vec)
{
	free(vec->data);
	vec->data = NULL;
	return vec;
}

void* Vector_setCap(Vector* const vec, const unsigned int cap)
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

void* Vector_setCapExact(Vector* const vec, const unsigned int cap)
{
	void* new_data = realloc(vec->data, cap * vec->chunk_size);
	if (new_data == NULL)
	{
		return NULL;
	}
	vec->data = new_data;
	return vec->data;
}

void* Vector_add(Vector* const vec, const void* const data)
{
	 // make sure we have capacity, we know we will have one more member
	if (Vector_setCap(vec, vec->length + 1))
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

void* Vector_insert(Vector* const vec, const void* const data, const unsigned int index)
{
	if (index <= vec->length && data != NULL)
	{
		// maybe it would be best to put this in the previous if, but I feel it is important to allow
		// the possibility of a different fail state
		if (Vector_setCap(vec, vec->length + 1))
		{
			// Vector_get returns 0 on an index == vec->length
			// we allow insertions at the end of the Vector
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

bool Vector_remove(Vector* const vec, const unsigned int index)
{
	if (index < vec->length)
	{
		void* data_address = Vector_get(vec, index);

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

void* Vector_get(const Vector* const vec, const unsigned int index)
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

void* Vector_find(const Vector* const vec, predicate* pred)
{
	void* tmp;
	for (int x = 0; x < vec->length; ++x)
	{
		tmp = Vector_get(vec, x);
		if (pred(tmp, vec->chunk_size))
		{
			return tmp;
		}
	}
	return NULL;
}

int Vector_findAll(const Vector* const vec, predicate* pred, void*** matches)
{
	void** big_enough = malloc(vec->length * vec->chunk_size);
	int count = 0;
	void* tmp;
	
	for (int x = 0; x < vec->length; ++x)
	{
		tmp = Vector_get(vec, x);
		if (pred(tmp, vec->chunk_size))
		{
			big_enough[count * vec->chunk_size] = tmp;
			++count;
		}
	}
	
	*matches = malloc(count * vec->chunk_size);
	for (int x = 0; x < count; ++x)
	{
		(*matches)[x * vec->chunk_size] = big_enough[x];
	}
	
	free(big_enough);
	return count;
}