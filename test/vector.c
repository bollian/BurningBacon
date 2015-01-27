#include <stdio.h>
#include <alloca.h>

#include <bbvector.h>

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
}