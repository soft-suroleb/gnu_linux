TESTS = dummy
bin_PROGRAMS = dummy upstream

check_PROGRAMS = dummy upstream

%.c: %.ts
	checkmk $< > $@

AM_CFLAGS = -I$(top_builddir)/src @CHECK_CFLAGS@
LDADD = $(top_builddir)/src/libbuf.la @CHECK_LIBS@
