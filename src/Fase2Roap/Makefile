CC=gcc
CFLAGS= -Wall -std=c99 -O3 -Im
DEPS = projectHeader.h queue.h graph.h heapPQ.h fase1.h
OBJ = main.o maze_maker.o auxiliar.o print.o restrictions.o queue_func.o control.o heapPQ.o graph.o auxiliar_fase1.o filePrint_fase1.o

%.o: %.c $(DEPS)
		$(CC) -c -o $@ $< $(CFLAGS)

roap: $(OBJ)
		$(CC) -o $@ $^ $(CFLAGS)

clean :
		-rm *.o $(objects) roap