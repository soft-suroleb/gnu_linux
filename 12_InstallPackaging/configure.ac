#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([Guess the number game], [0.0.2], [bozin2002@yandex.ru], [game])
AM_INIT_AUTOMAKE([foreign])
LT_INIT([disable-static])
DX_INIT_DOXYGEN([game])

AM_GNU_GETTEXT([external])
AM_GNU_GETTEXT_VERSION([0.21])

AC_CONFIG_MACRO_DIRS([m4])
AC_CONFIG_SRCDIR([src/game.c])
AC_CONFIG_HEADERS([config.h])
AC_SUBST(GETTEXT_PACKAGE, "$PACKAGE")
ALL_LINGUAS="ru"

# Joint pkgconfig library/include tests
PKG_CHECK_MODULES([CHECK],[check])

# Checks for programs.
AC_PROG_CC
IT_PROG_INTLTOOL
AC_PROG_LIBTOOL

# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS([libintl.h locale.h stdlib.h])

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.
AC_CHECK_FUNCS([setlocale])

AC_CONFIG_FILES([Makefile po/Makefile.in src/Makefile Doxyfile lib/Makefile tests/Makefile])
AC_OUTPUT
