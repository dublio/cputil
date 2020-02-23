PREFIX ?= /usr/local
BIN_DIR=$(PREFIX)/bin
MAN_DIR=$(PREFIX)/man

cputil: cputil.o
	gcc -o cputil cputil.o -lpthread

clean:
	rm -f cputil.o cputil

install:
	install -D -s cputil $(BIN_DIR)/cputil
	install -m 644 cputil.1 $(MAN_DIR)/man1

uninstall:
	-rm $(BIN_DIR)/cputil
	-rm $(MAN_DIR)/man1/cputil.1
