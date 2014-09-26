#include <limits.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/file.h>
#include <sys/mman.h>
#include "test.h"

static void* shared = NULL;

static int* value = NULL;

static int fd = -1;
static char template[64];

static pid_t* process = NULL;

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

	sprintf(template, "process_flock.%d", getpid());
	if(-1 == (fd = mkstemp(template)))
		return NULL;
	atexit(cleanup);

	if(!(shared = mmap(NULL, sizeof(*value) + sizeof(*test) * n, PROT_READ|PROT_WRITE, MAP_ANON|MAP_SHARED, -1, 0)))
		return NULL;
	value = shared;
	*value = 0;
	test = shared + sizeof(*value);

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
	flock(fd, LOCK_EX);
}

void unlock(int i)
{
	flock(fd, LOCK_UN);
}

