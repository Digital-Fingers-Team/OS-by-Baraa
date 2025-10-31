# Minimal compositor build

CC=gcc
CFLAGS=-I/usr/include/wlroots-0.15 -I/usr/include/pixman-1 -I/usr/include/libdrm
LDFLAGS=-lwlroots-0.15 -lwayland-server -lxkbcommon

all: compositor

compositor: main.c
	$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS)

clean:
	rm -f compositor
