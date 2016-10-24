CFLAGS := -g -std=c99 -Wall -Wformat=2
CFLAGS += -Wshadow -Wpointer-arith -Wunreachable-code
CFLAGS += -Wconversion -Wno-sign-conversion -Wbad-function-cast
CFLAGS += -Werror


all: pila.o cola.o paste more dc strutil.o
include deps.mk

run: main
	valgrind --leak-check=full --track-origins=yes --show-reachable=yes ./main
