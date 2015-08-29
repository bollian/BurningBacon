#include <stdio.h>
#include <alloca.h>
#include <stdbool.h>

#include <bbvector.h>

bool findZero(void* member, size_t size);

int main(int argc, char* argv[])
{
	int test_count = 1;
	bool fail = false;
	
	// --------------------initialization testing-------------------
	Vector vec;
	Vector_init(&vec, sizeof(int));
	
	if (vec.length != 0 || vec.chunk_size != sizeof(int) || vec.data == NULL)
	{
		return test_count;
	}
	++test_count;
	
	// --------------------add testing and get testing------------------------------
	int x = 0;
	fail = false;
	for (;x < 99; ++x)
	{
		Vector_add(&vec, &x);
		if (*(int*)Vector_get(&vec, x) != x)
		{
			printf("ERROR: incorrect value received from Vector_get on index %d\n", x);
			fail = true;
		}
	}
	if (vec.length != 99)
	{
		printf("ERROR: incorrect vector length of %d after 99 additions\n", vec.length);
		fail = true;
	}
	if (vec.capacity != 128)
	{
		printf("ERROR: incorrect capacity of %d after 99 additions\n", vec.capacity);
	}
	if (fail)
	{
		return test_count;
	}
	++test_count;
	
	// --------------------removal testing--------------------------
	for (x = 0; x < 99; ++x)
	{
		Vector_remove(&vec, 0);
	}
	if (vec.length != 0)
	{
		printf("ERROR: vector exceeded length after complete removal by %d\n", vec.length);
		return test_count;
	}
	++test_count;
	
	// --------------------insertion testing-----------------------
	fail = false;
	x = 72;
	Vector_insert(&vec, &x, 0);
	if (vec.length != 1)
	{
		printf("ERROR: vector length was %d after insertion of 1 value\n", vec.length);
		fail = true;
	}
	
	for (x = 1; x < 100; ++x)
	{
		Vector_add(&vec, &x);
	}
	for (; x >= 0; --x)
	{
		printf("%d\n", *(int*)Vector_insert(&vec, &x, x));
	}
	
	if (Vector_insert(&vec, NULL, 0))
	{
		printf("ERROR: Allows insertion from NULL address\n");
		fail = true;
	}
	if (Vector_insert(&vec, &x, vec.length + 2))
	{
		printf("ERROR: Allows insertions to addresses outside vector bounds\n");
		fail = true;
	}
	
	if (vec.length != 201)
	{
		printf("ERROR: incorrect vector length of %d after total 201 insertions & additions\n", vec.length);
		fail = true;
	}
	if (fail)
	{
		return test_count;
	}
	++test_count;
	
	//-------------------find testing--------------------------
	void* zero = Vector_find(&vec, &findZero);
	if (!zero)
	{
		printf("Zero was not found in the Vector!\n");
		fail = true;
	}
	else if (*(int*)zero != 0)
	{
		printf("The located Zero didn't have a value of 0!\n");
		fail = true;
	}
	
	Vector_free(&vec);
	Vector_init(&vec, sizeof(int));
	int value = 0;
	for (x = 0; x < 6; ++x)
	{
		Vector_add(&vec, &value);
	}
	
	void** all_zeros;
	int count = Vector_findAll(&vec, &findZero, &all_zeros);
	if (count != 6)
	{
		printf("Num of Zeros was %d and not 6!\n", count);
		fail = true;
	}
	else
	{
		for (x = 0; x < count; ++x)
		{
			printf("Index: %d\n", x);
			if (*(int*)(all_zeros[x]) != 0)
			{
				printf("The list of Zeros contained %d at index %d\n", *(int*)(all_zeros[x]), x);
				fail = true;
			}
		}
	}
	if (fail)
	{
		return test_count;
	}
	++test_count;
	
	return 0;
}

bool findZero(void* member, size_t size)
{
	if (size == sizeof(int) && (*(int*)member) == 0)
	{
		return true;
	}
	else
	{
		//if (sizeof())
		return false;
	}
}