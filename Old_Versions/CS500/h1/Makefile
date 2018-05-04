CC=gcc

PROGS=h1 h2 h3 h4 h5

# Linux defaults:
CFLAGS=-ggdb -pedantic -Wall
#CFLAGS=-O4 -Wall
#LDFLAGS=-s

all:	$(PROGS)

h1:	h1.o
h2:	h2.o
h3:	h3.o
h4:	h4.o
h5:	h5.o
	$(CC) $(LDFLAGS) -o $@ $<

%.o:	%.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:	objclean
	for b in $(PROGS); do if [ -f "$$b" ]; then rm "$$b"; fi done

objclean:
	for obj in h?.o; do if [ -f "$$obj" ]; then rm "$$obj"; fi done
