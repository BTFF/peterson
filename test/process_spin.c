#include <limits.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/mman.h>
#include "test.h"

static void* shared = NULL;

static int* value = NULL;

static volatile int* spin = NULL;

static pid_t* process = NULL;

struct test* prepare(int n)
{
	struct test* test = NULL;
	void* p;
	int i;

	if(!(p = mmap(NULL, sizeof(*value) + sizeof(*spin) + sizeof(*test) * n, PROT_READ|PROT_WRITE, MAP_ANON|MAP_SHARED, -1, 0)))
		return NULL;
	shared = p;
	value = p;
	p += sizeof(*value);
	spin = p;
	p += sizeof(*spin);
	test = p;

	*value = 0;
	*spin = 0;

	if(!(process = malloc(sizeof(*process) * n)))
		return NULL;
	
	for(i = 0; i < n; i++)
	{
		process[i] = -1;
		test[i].id = i;
		test[i].value = value;
	}
	return test;
}

void startroutine(int id, void* (*routine)(void*), void* arg)
{
	process[id] = fork();
	if(0 == process[id]) /* child */
	{
		routine(arg);
		exit(0);
	}
	else
	if(0 > process[id])
		printf("startroutine failed\n");
}

void waitroutine(int id)
{
	waitpid(process[id], NULL, 0);
}

void lock(int i)
{
    volatile int* p = spin;
    while(!__sync_bool_compare_and_swap(p, 0, 1))
    {
        //while(*p)
            //_mm_pause();
            //__sync_synchronize();
    }
}

void unlock(int i)
{
    int volatile* p = spin;
    asm volatile ("");
    *p = 0;
}

