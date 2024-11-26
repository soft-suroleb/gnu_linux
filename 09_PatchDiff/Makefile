.PHONY: clean

GENERATES = maze_orig maze_v1 maze_v2 maze_v3
TRASH = *.o *~ o.* *.out log* maze_v*
CFLAGS = -Wall

all: source bin run

source: maze_v1.c maze_v2.c maze_v3.c

maze_v1.c: maze_orig.c v_0_1.patch
	patch -o $@ $^

maze_v2.c: maze_v1.c v_0_2.patch
	patch -o $@ $^

maze_v3.c: maze_v2.c v_0_3.patch
	patch -o $@ $^

bin: maze_orig maze_v1 maze_v2 maze_v3

maze_orig: maze_orig.c
	$(CC) $(CFLAGS) -o $@ $^

maze_v1: maze_v1.c
	$(CC) $(CFLAGS) -o $@ $^

maze_v2: maze_v2.c
	$(CC) $(CFLAGS) -o $@ $^

maze_v3: maze_v3.c
	$(CC) $(CFLAGS) -o $@ $^

run:
	./maze_orig
	./maze_v1 8
	./maze_v2 " @" 8
	./maze_v3 42 " @" 8

clean:
	rm -f $(TRASH)

distclean: clean
	rm -rf $(GENERATES)
