CC=gcc

PROGS=h1 h2 h3 h4 h5 h6 h7 h8 h9 h10

# Linux defaults:
CFLAGS=-ggdb -pedantic -Wall
#CFLAGS=-O4 -Wall
LDFLAGS=-s

all:	$(PROGS)

h1:	h1.o
	$(CC) $(LDFLAGS) -o $@ $<

h2:	h2.o
	$(CC) $(LDFLAGS) -o $@ $<

h3:	h3.o
	$(CC) $(LDFLAGS) -o $@ $<

h4:	h4.o
	$(CC) $(LDFLAGS) -o $@ $<

h5:	h5.o
	$(CC) $(LDFLAGS) -o $@ $<

h6:	h6.o
	$(CC) $(LDFLAGS) -o $@ $<

h7:	h7.o
	$(CC) $(LDFLAGS) -o $@ $<

h8:	h8.o
	$(CC) $(LDFLAGS) -o $@ $<

h9:	h9.o
	$(CC) $(LDFLAGS) -o $@ $<

h10:	h10.o
	$(CC) $(LDFLAGS) -o $@ $<

%.o:	%.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:	objclean
	for b in $(PROGS); do if [ -f "$$b" ]; then rm "$$b"; fi done

objclean:
	for obj in h*.o; do if [ -f "$$obj" ]; then rm "$$obj"; fi done
