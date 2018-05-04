CC=gcc

PROGS=q1 q2 q3

# Linux defaults:
CFLAGS=-ggdb -pedantic -Wall
#CFLAGS=-O4 -Wall
LDFLAGS=-s -lm

all:	$(PROGS)

q1:	q1.o
	$(CC) $(LDFLAGS) -o $@ $<

q2:	q2.o
	$(CC) $(LDFLAGS) -o $@ $<

q3:	q3.o
	$(CC) $(LDFLAGS) -o $@ $<

%.o:	%.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:	objclean
	for b in $(PROGS); do if [ -f "$$b" ]; then rm "$$b"; fi done

objclean:
	for obj in q*.o; do if [ -f "$$obj" ]; then rm "$$obj"; fi done
