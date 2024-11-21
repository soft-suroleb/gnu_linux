.PHONY: clean

GENERATES = move
TRASH = *.o *~ o.* *.out log* *in* *out* *.so
CFLAGS = -Wall

all: move protect.so test

move: move.o
	$(CC) $(CFLAGS) -o $@ $^

protect.so: protect.c
	$(CC) $(CFLAGS) -shared -fPIC $^ -o $@ -ldl

test:
	sh test.sh

clean:
	rm -f $(TRASH)

distclean: clean
	rm -rf $(GENERATES)
