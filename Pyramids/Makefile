CC=gcc
CFLAGS= -Wall -std=c99 -O3
DEPS = projectHeader.h queue.h
OBJ = main.o maze_maker.o modes.o print.o restrictions.o queue_func.o

%.o: %.c $(DEPS)
		$(CC) -c -o $@ $< $(CFLAGS)

roap: $(OBJ)
		$(CC) -o $@ $^ $(CFLAGS)

clean :
		-rm *.o $(objects) roap