OBJS := cli.o ncurses.o lib.o core.o
MONEYCTL_LIBS = $(shell pkg-config --libs glib-2.0)
MONEYCTL_INCLUDE = $(shell pkg-config --cflags glib-2.0)
NMONEY_LIBS = $(shell pkg-config --libs ncurses)
CFLAGS += -std=gnu11 -Wall

build: moneycli nmoney
install: install-nmoney install-moneycli
all: build install

moneycli: cli.o core.o lib.o
	$(CC) $(LDFLAGS) -o $@ $^ $(MONEYCTL_LIBS)
	-chmod +x $@

nmoney: ncurses.o core.o lib.o
	$(CC) $(LDFLAGS) -o $@ $^ $(NMONEY_LIBS) $(MONEYCTL_LIBS)
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
	$(CC) $(CFLAGS) -c $< $(MONEYCTL_INCLUDE)

.PHONY: clean
clean:
	-rm -f nmoney moneycli $(OBJS) src/*.gch
