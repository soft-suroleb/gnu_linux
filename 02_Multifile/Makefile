GENERATES = prog prog-a prog-so libout.*
TRASH = *.o *~ o.* output_*
CFLAGS = -Wall

all:	prog prog-a prog-so test

fun.o prog.o:	outlib.h

prog:   const.o fun.o prog.o

.SECONDARY:	libout.a(fun.o const.o)

libout.a:	libout.a(fun.o const.o)

prog-a: prog.o libout.a
	$(CC) $(CFLAGS) $^ -o $@

libout.so: fun.o const.o
	$(CC) $(CFLAGS) $^ -o $@ -shared

prog-so: prog.o libout.so
	$(CC) $(CFLAGS) -L. $< -lout -o $@

test: prog prog-a prog-so
	./prog > output_0 2>&1
	./prog-a > output_a0 2>&1
	./prog-so > output_so0 2>&1
	./prog qwe > output_1
	./prog-a qwe > output_a1
	./prog-so qwe > output_so1
	./prog a b c > output_2
	./prog-a a b c > output_a2
	./prog-so a b c > output_so2
	cmp output_0 output_a0 && cmp output_a0 output_so0
	cmp output_1 output_a1 && cmp output_a1 output_so1
	cmp output_2 output_a2 && cmp output_a2 output_so2

clean:
	rm -f $(TRASH)

distclean: clean
	rm -rf $(GENERATES)
 
