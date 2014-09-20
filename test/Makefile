CFLAGS += -g -Wall
LFLAGS +=

all: process_flock process_mutext process_sem thread_flock thread_mutex thread_sem process_lockf process_peterson process_v_sem thread_lockf thread_peterson thread_v_sem

process_flock: process_flock.o test.o
	$(CC) $(LFLAGS) -o $@ $^

process_mutext: process_mutext.o test.o
	$(CC) $(LFLAGS) -o $@ $^

process_sem: process_sem.o test.o
	$(CC) $(LFLAGS) -o $@ $^

process_lockf: process_lockf.o test.o
	$(CC) $(LFLAGS) -o $@ $^

process_peterson: process_peterson.o test.o
	$(CC) $(LFLAGS) -o $@ $^

process_v_sem: process_v_sem.o test.o
	$(CC) $(LFLAGS) -o $@ $^

thread_flock: thread_flock.o test.o
	$(CC) $(LFLAGS) -pthread -o $@ $^

thread_mutex: thread_mutex.o test.o
	$(CC) $(LFLAGS) -pthread -o $@ $^

thread_sem: thread_sem.o test.o
	$(CC) $(LFLAGS) -pthread -o $@ $^

thread_lockf: thread_lockf.o test.o
	$(CC) $(LFLAGS) -pthread -o $@ $^

thread_peterson: thread_peterson.o test.o
	$(CC) $(LFLAGS) -pthread -o $@ $^

thread_v_sem: thread_v_sem.o test.o
	$(CC) $(LFLAGS) -pthread -o $@ $^

clean:
	rm -rf peterson *.o

dep:
	$(CC) $(CFLAGS) -M *.c *.h > .depend

.c.o:
	$(CC) $(CFLAGS) -c $< 

include .depend
