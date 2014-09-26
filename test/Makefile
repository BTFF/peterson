CFLAGS += -v -g -Wall
LFLAGS +=
OBJS = test.o main.o

all: process_none process_spin process_flock process_mutex process_sem thread_flock thread_spin thread_mutex thread_sem process_lockf process_peterson process_v_sem thread_lockf thread_peterson thread_v_sem thread_fcntl

process_none: process_none.o $(OBJS)
	$(CC) $(LFLAGS) -o $@ $^

process_spin: process_spin.o $(OBJS)
	$(CC) $(LFLAGS) -o $@ $^

process_flock: process_flock.o $(OBJS)
	$(CC) $(LFLAGS) -o $@ $^

#process_mutex: process_mutex.o $(OBJS)
	#$(CC) $(LFLAGS) -o $@ $^

process_sem: process_sem.o $(OBJS)
	$(CC) $(LFLAGS) -o $@ $^

process_lockf: process_lockf.o $(OBJS)
	$(CC) $(LFLAGS) -o $@ $^

process_peterson: process_peterson.o $(OBJS) ../peterson.o
	$(CC) $(LFLAGS) -o $@ $^

process_v_sem: process_v_sem.o $(OBJS)
	$(CC) $(LFLAGS) -o $@ $^

thread_spin: thread_spin.o $(OBJS) 
	$(CC) $(LFLAGS) -pthread -o $@ $^

thread_flock: thread_flock.o $(OBJS)
	$(CC) $(LFLAGS) -pthread -o $@ $^

thread_mutex: thread_mutex.o $(OBJS) 
	$(CC) $(LFLAGS) -pthread -o $@ $^

thread_sem: thread_sem.o $(OBJS)
	$(CC) $(LFLAGS) -pthread -o $@ $^

thread_lockf: thread_lockf.o $(OBJS)
	$(CC) $(LFLAGS) -pthread -o $@ $^

thread_peterson: thread_peterson.o $(OBJS) ../peterson.o
	$(CC) $(LFLAGS) -pthread -o $@ $^

thread_v_sem: thread_v_sem.o $(OBJS)
	$(CC) $(LFLAGS) -pthread -o $@ $^

thread_fcntl: thread_fcntl.o $(OBJS)
	$(CC) $(LFLAGS) -pthread -o $@ $^

clean:
	rm -rf peterson *.o

dep:
	$(CC) $(CFLAGS) -M *.c *.h > .depend

.c.o:
	$(CC) $(CFLAGS) -c $< 

include .depend
