OBJS := cli.o ncurses.o lib.o core.o
NMONEY_LIBS = $(shell pkg-config --libs ncurses)
CFLAGS += -Wall

build: moneycli nmoney
install: install-nmoney install-moneycli
all: build install

moneycli: cli.o core.o lib.o
	$(CC) $(LDFLAGS) -o $@ $^
	-chmod +x $@

nmoney: ncurses.o core.o lib.o
	$(CC) $(LDFLAGS) -o $@ $^ $(NMONEY_LIBS)
	-chmod +x $@

cli.o: src/cli.c src/core.h src/lib.h
	$(CC) $(CFLAGS) -c $<

ncurses.o: src/ncurses.c src/core.h src/lib.h
	$(CC) $(CFLAGS) -c $<


install-moneycli: moneycli
	install -D $< $(DESTDIR)/usr/bin/

install-nmoney: nmoney
	install -D $< $(DESTDIR)/usr/bin/

%.o: src/%.c src/%.h
	$(CC) $(CFLAGS) -c $<

.PHONY: clean
clean:
	-rm -f nmoney moneycli $(OBJS) src/*.gch
