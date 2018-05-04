CC=gcc

PROGS=h1 h2 h3 h4

# Linux defaults:
CFLAGS=-ggdb -pedantic -Wall
#CFLAGS=-O4 -Wall
LDFLAGS=-s -lm

all:	$(PROGS)

h1:	h1.o
	$(CC) $(LDFLAGS) -o $@ $<

h2:	h2.o
	$(CC) $(LDFLAGS) -o $@ $<

h3:	h3.o
	$(CC) $(LDFLAGS) -o $@ $<

h4:	h4.o
	$(CC) $(LDFLAGS) -o $@ $<

%.o:	%.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:	objclean
	for b in $(PROGS); do if [ -f "$$b" ]; then rm "$$b"; fi done

objclean:
	for obj in h*.o; do if [ -f "$$obj" ]; then rm "$$obj"; fi done
