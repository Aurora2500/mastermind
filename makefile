.PHONY: all clean install uninstall

installpath=$(HOME)/.local/bin

all: mastermind

mastermind: mastermind.o
	cc mastermind.o -o mastermind

mastermind.o: mastermind.c
	cc -c mastermind.c

clean:
	rm mastermind.o mastermind

install: all
	cp mastermind $(installpath)

uninstall:
	rm "$(installpath)/mastermind"
