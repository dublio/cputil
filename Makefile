PREFIX ?= /usr/local
BIN_DIR=$(PREFIX)/bin
cputil: cputil.o
	gcc -o cputil cputil.o -lpthread

clean:
	rm -f cputil.o cputil

install:
	install -D -s cputil $(BIN_DIR)/cputil

uninstall:
	-rm $(BIN_DIR)/cputil
