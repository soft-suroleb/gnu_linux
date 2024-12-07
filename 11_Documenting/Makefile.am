SUBDIRS = src po

@DX_RULES@

doxygen-doc/man/man1/game.1:	doxygen-doc

man1_MANS = doxygen-doc/man/man1/game.1

all-local:  doxygen-doc

install-data-local:
	mkdir -p $(DESTDIR)/$(docdir)
	cp -a doxygen-doc/html $(DESTDIR)/$(docdir)
