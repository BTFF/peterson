#include <stdlib.h>
#include <stdio.h>
#include "test.h"

int main(int argc, char** argv)
{
    int i;
    int n = 0;
    struct timeval begin;
    struct timeval end;
	struct test* test;

    if(1 < argc)
        n = strtol(argv[1], NULL, 10);
	if(!(test = prepare(n + 1)))
		return -1;

	lock(n);
	for(i = 0; i < n; i++)
		startroutine(i, loop, test + i);
    if(gettimeofday(&begin, NULL)) return -1;
	unlock(n);
    loop(test + n);
    if(gettimeofday(&end, NULL)) return -1;

    printf("%d\n", *test[n].value);
    printf("%s\n", elapse(&begin, &end));

	for(i = 0; i < n; i++)
		waitroutine(i);

    return -1;
}

