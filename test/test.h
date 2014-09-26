#ifndef __test_h__
#define __test_h__ __test_h__

#include <sys/time.h>

//#define DEBUG
#ifdef DEBUG
#define VALUE_MAX (1000)
#else
#define VALUE_MAX (1000 * 1000)
#endif

struct test
{
	int id;
	volatile int* value;
};

struct test* prepare(int n);
void startroutine(int id, void* (*routine)(void*), void* arg);
void waitroutine(int id);
void* loop(void* arg);
void lock(int i);
void unlock(int i);

const char* elapse(struct timeval* begin, struct timeval* end);

#endif/*__test_h__*/
