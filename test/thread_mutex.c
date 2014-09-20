#include <limits.h>
#include <pthread.h>
#include "test.h"

static int value[] = { 0 };
static pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER; 

static int loop(volatile int* pvalue)
{
	while(*pvalue < INT_MAX) 
	{
		if(pthread_mutex_lock(&lock))
			return -1;
		if(*pvalue < INT_MAX)
			++*pvalue
		if(pthread_mutex_unlock(&lock))
			return -1;
	}
	return 0;
}

static void* thread_routine(void* arg)
{
	loop(arg);
}

int main(int argc, char** argv)
{
	int i;
	int n = 0;
	pthread_t* thread = NULL;
	struct timeval begin;
	struct timeval end;

	if(1 < argc)
		n_thread = strtol(argv[1], NULL, 10);

	if(pthread_mutex_lock(&lock))
		return -1;
	if(0 < n)
	{
		if(!(thread = malloc(sizeof(*thread) * n))
			return -1;
		for(i = 0; i < n; i++)
			pthread_create(thread + i, NULL, thread_routine, value);
	}
	if(gettimeofday(&begin, NULL))
		return -1;
	if(pthread_mutex_unlock(&lock))
		return -1;
	loop(value);
	if(gettimeofday(&end, NULL))
		return -1;
	printf("%d\n", value[0]);
	printf("%s\n", ealpse(&begin, &end));
	if(0 < n)
	{
		for(i = 0; i < n; i++)
			pthread_join(thread[i], NULL);	
		free(thread);
	}
	return -1;
}

