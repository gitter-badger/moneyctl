OBJS := cli.o ncurses.o lib.o core.o
NMONEYLIBS = $(shell pkg-config --libs ncurses)

build: moneycli nmoney
install: install-nmoney install-moneycli
all: build install

moneycli: lib.o core.o cli.o
	$(CC) $(LDFLAGS) $^ -o $@

nmoney: lib.o core.o ncurses.o
	$(CC) $(LDFLAGS) $^ -o $@ $(NMONEYLIBS)
	-chmod +x $@

cli.o: src/cli.c src/lib.h src/core.h
	$(CC) $(CFLAGS) -c $^

ncurses.o: src/ncurses.c src/core.h src/lib.h
	$(CC) $(CFLAGS) -c $^


install-moneycli: moneycli
	install -D $< $(DESTDIR)/usr/bin/

install-nmoney: nmoney
	install -D $< $(DESTDIR)/usr/bin/

%.o: src/%.c src/%.h
	$(CC) $(CFLAGS) -c $^

.PHONY: clean
clean:
	-rm -f nmoney moneycli $(OBJS) src/*.gch
