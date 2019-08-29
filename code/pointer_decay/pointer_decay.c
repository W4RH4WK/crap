#include <stdio.h>

#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof(arr[0]))

void fun(int arr[10])
{
	printf("%ld\n", ARRAY_SIZE(arr));
}

int main()
{
	int arr[10];
	printf("%ld\n", ARRAY_SIZE(arr));
	fun(arr);
}
