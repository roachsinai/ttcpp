CC=g++

ifdef debug
	CFLAGS=-g
else
	CFLAGS=
endif

LDIR =./lib

LIBS=-lm

tt.out: tt.cpp
	$(CC) -o $@ $< $(CFLAGS) $(LIBS)

.PHONY: clean
clean:
	rm -f tt.out

.PHONY: run
run:
	./tt.out
