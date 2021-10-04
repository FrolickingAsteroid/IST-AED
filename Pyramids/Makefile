CC=gcc
CFLAGS= -Wall -std=c11 -O3
DEPS = projectHeader.h
OBJ = main.o maze_maker.o free.o  list_modes.o order.o print.o restriction.o   selection.o

%.o: %.c $(DEPS)
		$(CC) -c -o $@ $< $(CFLAGS)

roap: $(OBJ)
		$(CC) -o $@ $^ $(CFLAGS)

clean :
		-rm *.o $(objects) roap