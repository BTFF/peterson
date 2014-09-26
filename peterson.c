#include <stdio.h>
#include "peterson.h"

/* Peterson's Algorithm N-Process tournament version */

struct flag_turn
{
	int flag[2];
	int turn;
};

enum { FALSE = -1, TRUE = 1 };

static inline int offset(int bit, int current_bit, int id)
{
	int offset;
	int mask;
	for(offset = 0, bit--, mask = 1 << bit; bit > current_bit; bit--, mask >>= 1, offset++)
		if(mask & id)
			offset += mask - 1;
	return offset;
}

int peterson_flag_turn_size(int n)
{
	int bit;
	for(bit = 0; (1 << bit) <= n; bit++);
	return sizeof(struct flag_turn) * (offset(bit, 0, n - 1) + 1);
}

void peterson_initial(struct peterson* peterson, int n, void* flag_turn)
{
	for(peterson->bit = 0; (1 << peterson->bit) <= n; peterson->bit++);
	peterson->n = n;
	peterson->flag_turn = flag_turn;
}

void peterson_lock(struct peterson* peterson, int id)
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
		__sync_synchronize();
		while(TRUE == node->flag[!my_turn] && node->turn == !my_turn);
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
	__sync_synchronize();
}
/*
int main(int argc, char** argv)
{
	int peterson_bit = 4;
	int bit;
	int id;

	for(id = 0; id < 16; id++)
	{
		printf("id: %d\n", id);
		for(bit = peterson_bit - 1; bit >= 0; bit--)
		{
			printf("bit: %d\t offset: %d\n", bit, offset(peterson_bit, bit, id));
			fflush(stdout);
		}
		printf("\n");
	}
	return 1;
}
*/
