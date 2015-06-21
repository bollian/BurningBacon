#include <stdio.h>
#include <alloca.h>
#include <stdbool.h>

#include <bbvector.h>

int main(int argc, char* argv[])
{
	int test_count = 1;
	bool fail = false;
	
	// --------------------initialization testing-------------------
	vector vec;
	vector_init(&vec, sizeof(int));
	
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
		vector_add(&vec, &x);
		if (*(int*)vector_get(&vec, x) != x)
		{
			printf("ERROR: incorrect value received from vector_get on index %d\n", x);
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
		vector_remove(&vec, 0);
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
	vector_insert(&vec, &x, 0);
	if (vec.length != 1)
	{
		printf("ERROR: vector length was %d after insertion of 1 value\n", vec.length);
		fail = true;
	}
	
	for (x = 1; x < 100; ++x)
	{
		vector_add(&vec, &x);
	}
	for (; x >= 0; --x)
	{
		printf("%d\n", *(int*)vector_insert(&vec, &x, x));
	}
	
	if (vector_insert(&vec, NULL, 0))
	{
		printf("ERROR: Allows insertion from NULL address\n");
		fail = true;
	}
	if (vector_insert(&vec, &x, vec.length + 2))
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
		return ++test_count;
	}
	
	return 0;
}
/*
int main(int argc, char* argv[])
{
	vector vec = { };
	vector_init(&vec, sizeof(int));

	// -------------------add and get testing-----------------------
	int x = 0;
	for (; x < 99; ++x)
	{
		vector_add(&vec, &x);
		printf("%d\n", *(int*)vector_get(&vec, x));
	}

	--x;
	for (; x >= 0; --x)
	{
		printf("%d\n", *(int*)vector_get(&vec, x));
	}

	// ---------------------removal testing------------------------
	for (; x < 99; ++x)
	{
		vector_remove(&vec, 0);
	}
	for (x = 0; x < vec.length; ++x)
	{
		printf("Data: %d\n", *(int*)vector_get(&vec, x));
	}
	printf("Vector Length: %d\n", vec.length);

	// ------------------insertion testing-------------------------
	x = 72;
	vector_insert(&vec, &x, 0);
	printf("Vector Length after insertion: %d\n", vec.length);
	for (x = 1; x < 99; ++x)
	{
		vector_add(&vec, &x);
	}
	for (; x > 0; --x)
	{
		printf("%d\n", *(int*)vector_insert(&vec, &x, x));
	}
	if (vector_insert(&vec, NULL, 0))
	{
		printf("ERROR: Allows insertion from NULL address\n");
	}
	if (vector_insert(&vec, &x, vec.length + 2))
	{
		printf("ERROR: Allows insertions to addresses outside vector bounds\n");
	}
	printf("Length after all insertions: %d\n", vec.length);

	return 0;
}*/