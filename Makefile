PREFIX ?= /usr/local
CC ?= cc
LDFLAGS = -lX11

output: rootblocks.c rootblocks.h config.h
	${CC}  rootblocks.c $(LDFLAGS) -o rootblocks

clean:
	rm -f *.o *.gch rootblocks
install: output
	mkdir -p $(DESTDIR)$(PREFIX)/bin
	install -m 0755 rootblocks $(DESTDIR)$(PREFIX)/bin/rootblocks
uninstall:
	rm -f $(DESTDIR)$(PREFIX)/bin/rootblocks
