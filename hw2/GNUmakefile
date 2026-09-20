prog=balloc

include ../GNUmakefile

try: main.o
	gcc -o $@ $< -L. -ldeq -Wl,-rpath=.
