#include <limits.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/mman.h>
#include "test.h"
#include "../peterson.h"

static void* shared = NULL;

static int* value = NULL;

static void* flag_turn = NULL;
static struct peterson* peterson = NULL;

static pid_t* process = NULL;

struct test* prepare(int n)
{
	struct test* test = NULL;
	int i;

	if(!(shared = mmap(NULL, peterson_flag_turn_size(n) + sizeof(*peterson) + sizeof(*value) + sizeof(*test) * n, PROT_READ|PROT_WRITE, MAP_ANON|MAP_SHARED, -1, 0)))
		return NULL;
	flag_turn = shared;
	peterson = shared + peterson_flag_turn_size(n);
	peterson_initial(peterson, n, flag_turn);

	value = shared + peterson_flag_turn_size(n) + sizeof(*peterson);
	*value = 0;
	test = shared + peterson_flag_turn_size(n) + sizeof(*peterson)  + sizeof(*value);

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
	peterson_lock(peterson, i);
}

void unlock(int i)
{
	peterson_unlock(peterson, i);
}

