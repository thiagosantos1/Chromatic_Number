CC     = gcc
HDR1   = ../include/findcolor.h
OPT    = -g -Wall
CFLAGS = -c -I../include
LIBS   = -lcoloring -lpthread
OBJS   = makegraph.o greedy.o utils.o bipartite.o

all: colortest libcoloring.a

colortest: colortest.o libcoloring.a
	$(CC) -L../lib $(OPT) -o ../bin/$@ colortest.o $(LIBS)
colortest.o: colortest.c $(HDR1)
	$(CC) $(CFLAGS) $(OPT) colortest.c
greedy.o: greedy.c $(HDR1)
	$(CC) $(CFLAGS) $(OPT) greedy.c
bipartite.o: bipartite.c $(HDR1)
	$(CC) $(CFLAGS) $(OPT) bipartite.c
utils.o: greedy.c $(HDR1)
	$(CC) $(CFLAGS) $(OPT) utils.c
makegraph.o: makegraph.c $(HDR1)
	$(CC) $(CFLAGS) $(OPT) makegraph.c
libcoloring.a: $(OBJS)
	ar rcs ../lib/$@ $(OBJS)
clean:
	rm -f *.o ../lib/*.a ../bin/colortest
