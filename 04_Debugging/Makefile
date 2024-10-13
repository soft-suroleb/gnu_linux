.PHONY: clean

GENERATES = range
TRASH = *.o *~ o.* *.out
CFLAGS = -Wall

all: range

usage.o:	usage.h

range: range.o usage.o
	$(CC) $(CFLAGS) -o range -O0 -g $^

clean:
	rm -f $(TRASH)
