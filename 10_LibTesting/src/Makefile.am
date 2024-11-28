CFLAGS = -std=c99 -Wall -Wextra
if COND_GCOV
CFLAGS  += -O0 -g -fprofile-arcs -ftest-coverage
else
CFLAGS  += -O3 -g3
endif

lib_LTLIBRARIES = libbuf.la
libbuf_la_SOURCES = buf.c buf.h
libbuf_la_LIBADD = -lm

gcov:
	gcov -o .libs buf -t -k -b | egrep -v '[[:digit:]]:[ /][*]'
