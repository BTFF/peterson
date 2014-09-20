#include "test.h"

const char* elapse(struct timeval* begin, struct timeval* end)
{
	static char string[80];
	struct timevale elapse;
	if(end->tv_usec >= begin->tv_usec)
	{
		elapse.tv_sec = end->tv_sec - begin->tv_sec; 
		elapse.tv_usec = end->tv_usec - begin->tv_usec;
	}
	else
	{
		elapse.tv_sec = end->tv_sec + 1000 * 1000 - begin->tv_sec; 
		elapse.tv_usec = end->tv_usec - 1 - begin->tv_usec;
	}
	sprintf(string, "%d.%06d", elapse.tv_sec, elapse.tv_usec);
}
