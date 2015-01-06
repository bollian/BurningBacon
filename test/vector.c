#include <stdio.h>

#include <bbvector.h>

int main(int argc, char* argv[])
{
	vector vec = { };
	vector_init(&vec, sizeof(int));

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

	for (; x < 99; ++x)
	{
		vector_remove(&vec, 0);
	}
	for (x = 0; x < vec.length; ++x)
	{
		printf("Data: %d\n", *(int*)vector_get(&vec, x));
	}
	printf("Vector Length: %d\n", vec.length);

	return 0;
}