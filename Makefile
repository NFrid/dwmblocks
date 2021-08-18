PREFIX ?= /usr/local
CC ?= cc
LDFLAGS = -lX11
CFLAGS = -std=gnu99 -pedantic -Wall

output: rootblocks.c rootblocks.h config.h subtosignal.c
	${CC}  rootblocks.c $(LDFLAGS) $(CFLAGS) -o rootblocks
	${CC}  subtosignal.c $(LDFLAGS) $(CFLAGS) -o subtosignal

clean:
	rm -f *.o *.gch rootblocks subtosignal
install: output
	mkdir -p $(DESTDIR)$(PREFIX)/bin
	install -m 0755 rootblocks $(DESTDIR)$(PREFIX)/bin/rootblocks
	install -m 0755 subtosignal $(DESTDIR)$(PREFIX)/bin/subtosignal
uninstall:
	rm -f $(DESTDIR)$(PREFIX)/bin/rootblocks
	rm -f $(DESTDIR)$(PREFIX)/bin/subtosignal
