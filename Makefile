cc = gcc
cflags = -std=c99 -Wall -Wextra -Wpedantic -lX11 -g
objs = sbar.o functions.o
install_directory = /usr/local/bin

all: sbar

sbar: $(objs)
	$(cc) $(cflags) $^ -o sbar

%.o: %.c
	$(cc) $(cflags) -c $^

install: sbar
	cp sbar $(install_directory)/sbar

uninstall:
	rm -f $(install_directory)/sbar

clean:
	rm -f sbar
	rm -f *.o

.PHONY: all install uninstall clean
