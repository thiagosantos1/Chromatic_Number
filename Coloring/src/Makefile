CC     = gcc
HDR1   = ../include/findcolor.h
OPT    = -g -Wall
CFLAGS = -c -I../include
LIBS   = -lcoloring -lpthread 
OBJS   = makegraph.o greedy.o bipartite.o exhaust_search.o rand_search.o

all: chromatic libcoloring.a

chromatic: main.o libcoloring.a
	$(CC) -L../lib $(OPT) -o ../bin/$@ main.o $(LIBS)
main.o: main.c $(HDR1)
	$(CC) $(CFLAGS) $(OPT) main.c
greedy.o: greedy.c $(HDR1)
	$(CC) $(CFLAGS) $(OPT) greedy.c
bipartite.o: bipartite.c $(HDR1)
	$(CC) $(CFLAGS) $(OPT) bipartite.c
makegraph.o: makegraph.c $(HDR1)
	$(CC) $(CFLAGS) $(OPT) makegraph.c
exhaust_search.o: exhaust_search.c $(HDR1)
	$(CC) $(CFLAGS) $(OPT) exhaust_search.c
rand_search.o: rand_search.c $(HDR1)
	$(CC) $(CFLAGS) $(OPT) rand_search.c
libcoloring.a: $(OBJS)
	ar rcs ../lib/$@ $(OBJS)

clean:
	rm -f *.o ../lib/*.a ../bin/chromatic
