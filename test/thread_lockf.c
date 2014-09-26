#include <limits.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/file.h>
#include <sys/mman.h>
#include "test.h"

static int value[] = { 0 };

//static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; 
static int fd = -1;
static char template[64];

static pthread_t* thread = NULL;

static void cleanup(void)
{
    if(-1 != fd)
        close(fd);
    unlink(template);
}

struct test* prepare(int n)
{
	struct test* test = NULL;
	int i;

    atexit(cleanup);
    sprintf(template, "process_lockf.%d", getpid());
    if(-1 == (fd = mkstemp(template)))
        return NULL;

	if(!(test = malloc(sizeof(*test) * n)))
		return NULL;
	if(!(thread = malloc(sizeof(*thread) * n)))
	{
		free(thread);
		return NULL;
	}
	
	for(i = 0; i < n; i++)
	{
		test[i].id = i;
		test[i].value = value;
	}
	return test;
}

void startroutine(int id, void* (*routine)(void*), void* arg)
{
	pthread_create(thread + id, NULL, routine, arg);
}

void waitroutine(int id)
{
	pthread_join(thread[id], NULL);
}

void lock(int i)
{
	lockf(fd, F_LOCK, 0);
}

void unlock(int i)
{
	lockf(fd, F_ULOCK, 0);
}

