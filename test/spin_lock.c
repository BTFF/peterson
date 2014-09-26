void spin_lock(int* p)
{
	while(!__sync_bool_compare_and_swap(p, 0, 1));
}

void spin_unlock(int volatile* p)
{
	asm volatile ("");
	*p = 0;
}
