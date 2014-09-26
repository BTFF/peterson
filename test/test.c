#include <stdio.h>
#include "test.h"

void* loop(void* arg)
{
	struct test* test = arg;
    while(*test->value < VALUE_MAX)
    {
		lock(test->id);
        if(*test->value < VALUE_MAX)
            ++*test->value;
#ifdef DEBUG
		printf("id: %d value: %d\n", test->id, *test->value);
		fflush(stdout);
#endif
		unlock(test->id);
    }
	return test;
}

const char* elapse(struct timeval* begin, struct timeval* end)
{
	static char string[80];
	struct timeval elapse;
	if(end->tv_usec >= begin->tv_usec)
	{
		elapse.tv_sec = end->tv_sec - begin->tv_sec; 
		elapse.tv_usec = end->tv_usec - begin->tv_usec;
	}
	else
	{
		elapse.tv_sec = end->tv_sec - 1 - begin->tv_sec; 
		elapse.tv_usec = end->tv_usec + 1000 * 1000 - begin->tv_usec;
	}
	sprintf(string, "%d.%06d", (int)elapse.tv_sec, elapse.tv_usec);
	return string;
}
