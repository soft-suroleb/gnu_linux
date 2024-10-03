GENERATES = prog README
TRASH = *.o *~ o.*

all:	prog README

fun.o prog.o:	outlib.h

prog:   const.o fun.o prog.o

README:	prog
	./$< > $@ 2>&1

clean:
	rm -f $(TRASH)

distclean: clean
	rm -rf $(GENERATES)
 
