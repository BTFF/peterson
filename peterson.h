#ifndef __peterson_h__
#define __peterson_h__ __peterson_h__

/* Peterson's Algorithm N-Process tournament version  */

struct peterson
{
	int n;
	int bit;
	void* flag_turn;
};

int peterson_flag_turn_size(int n);
void peteron_initial(struct peterson* peterson, int n, void* flag_turn);
void peterson_lock(struct peteron* peteron, int id);
void peterson_unlock(struct peterson* peterson, int id);

#endif/*__peterson_h__*/
