NAME=cencurses
PKGS=ncurses
PREFIX = /usr/local
MANPREFIX := ${PREFIX}/share/man
CFLAGS := -g -std=c99 -O3 -finline-functions -flto -funroll-loops -Wall -Wno-deprecated-declarations $(shell pkg-config --cflags ${PKGS})
LDFLAGS := $(shell pkg-config --libs ${PKGS})
