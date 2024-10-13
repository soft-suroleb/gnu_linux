.PHONY: clean

GENERATES = range log_* log
TRASH = *.o *~ o.* *.out
CFLAGS = -Wall -O0 -g

all: range test

usage.o:	usage.h

range: range.o usage.o
	$(CC) $(CFLAGS) -o range $^

test:
	gdb --args range 1 12 < script_1.gdb 2>&1 | grep "@@@" > log_1
	gdb --args range -100 100 3 < script_2.gdb 2>&1 | grep "@@@" > log_2
	cmp standart_1 log_1 && cmp standart_2 log_2

clean:
	rm -f $(TRASH)

distclean: clean
	rm -rf $(GENERATES)
