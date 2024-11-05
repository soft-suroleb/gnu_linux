.PHONY: clean

GENERATES = esub
TRASH = *.o *~ o.* *.out log*
CFLAGS = -Wall

all: esub test

esub: esub.o
	$(CC) $(CFLAGS) -o $@ $^

test:
	echo "DDabcDD" | sed -E "s/a(b)c/\1__\1/" > log_11
	./esub "a(b)c" "\1__\1" "DDabcDD" > log_12
	echo "_abcdef_" | sed -E "s/(a)b(c)d(e)/<\3\2\1>/" > log_21
	./esub "(a)b(c)d(e)" "<\3\2\1>" "_abcdef_" > log_22
	cmp log_11 log_12 && cmp log_21 log_22

clean:
	rm -f $(TRASH)

distclean: clean
	rm -rf $(GENERATES)
