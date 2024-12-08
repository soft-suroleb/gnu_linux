TESTS = dummy
bin_PROGRAMS = dummy

check_PROGRAMS = dummy

%.c: %.ts
	checkmk $< > $@

AM_CFLAGS = -I$(top_builddir)/lib @CHECK_CFLAGS@
LDADD = $(top_builddir)/lib/libgame.la @CHECK_LIBS@
