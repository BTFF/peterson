#include <stdio.h>
#include <linux/kernel.h>
#include "peterson.h"

/* Peterson's Algorithm N-Process tournament version */

struct flag_turn
{
	int flag[2];
	int turn;
};

enum { FLASE = -1, TRUE = 1 };

static inline offset(int bit, int current_bit, int id)
{
	int offset;
	for(offset = 0, bit--, mask = 1 << bit; bit > current_bit; bit--, mask >>= 1, offset++)
		if(mask & id)
			offset += (mask >> 1) - 1;
	return offset;
}

int flag_turn_size(int n)
{
	int bit;
	for(bit = 0; (1 << bit) <= n; bit++);
	return sizeof(struct flag_turn) * (offset(bit, 0, n - 1) + 1);
}

void peteron_initial(struct peterson* peterson, int n, void* flag_turn)
{
	for(peterson->bit = 0; (1 << peterson->bit) <= n; peterson->bit++);
	peterson->n = n;
	peterson->flag_turn = flag_turn;
}

void peterson_lock(struct peteron* peteron, int id)
{
	int bit;
	int mask;
	volatile struct flag_turn* node;

	for(bit = 0, mask = 1; bit < peterson->bit; bit++, mask <<= 1)
	{
		int my_turn = mask & id;
		node = peterson->flag_turn;
		node += offset(peterson->bit, bit, id);
		node->flag[my_turn] = TRUE;
		node->turn = !my_turn;
		barrier();
		while(TRUE == node->flag[!my_turn] && node->turn == !my_turn)
			sched_yield();
	}
}

void peterson_unlock(struct peterson* peterson, int id)
{
	int bit;
	int mask;
	volatile struct flag_turn* node;

	for(bit = peterson->bit - 1, mask = 1 << (peterson->bit - 1); bit >= 0; bit--, mask >>= 1)
	{
		int my_turn = mask & id;
		node = peterson->flag_turn;
		node += offset(peterson->bit, bit, id);
		node->flag[my_turn] = FALSE;
	}
}

int main(int argc, char** argv)
{
	int peterson_bit = 8;
	int bit;
	int id;

	for(id = 0; id < 256; id++)
	{
		printf("id: %d\t");
		for(bit = 0; bit < peterson_bit; bit++)
			printf("bit: %d\t offset: %d\t", bit, offset(peterson_bit, bit, id));
		printf("\n");
	}
	return 1;
}

