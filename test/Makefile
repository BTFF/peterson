CFLAGS += -g
LFLAGS +=

all: peterson

peterson: peterson.o
	$(CC) $(LFLAGS) -o $@ $^

clean:
	rm -rf peterson *.o

dep:
	$(CC) $(CFLAGS) -M *.c *.h > .depend

.c.o:
	$(CC) $(CFLAGS) -c $< 

include .depend
