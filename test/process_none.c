#include <limits.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/file.h>
#include <sys/mman.h>
#include "test.h"

static struct test* test = NULL;

static int value[1] = { 0 };

struct test* prepare(int n)
{
	int i;

	if(!(test = malloc(sizeof(*test) * n)))
		return NULL;

	for(i = 0; i < n; i++)
	{
		test[i].id = i;
		test[i].value = value;
	}
	return test;
}

void startroutine(int id, void* (*routine)(void*), void* arg)
{
}

void waitroutine(int id)
{
}

void lock(int i)
{
}

void unlock(int i)
{
}

