prefix ?= /usr/local
bindir ?= $(prefix)/bin
mandir ?= $(prefix)/man

cputil: cputil.o
	gcc $(CFLAGS) -o cputil cputil.o -lpthread

clean:
	rm -f cputil.o cputil

install:
	install -m 755 -d $(bindir)
	install -pm 755 cputil $(bindir)/cputil
	install -m 755 -d $(mandir)/man1
	install -pm 644 cputil.1 $(mandir)/man1

uninstall:
	-rm $(bindir)/cputil
	-rm $(mandir)/man1/cputil.1
