CC = gcc
CFLAGS = -Wall -Wextra -pedantic -std=c99

ifeq ($(OS),Windows_NT)
	CFLAGS += -lpdcurses
else
	CFLAGS += -lncurses
endif

FalloutTerminal: main.o print.o intro.o pass.o
	$(CC) -o $@ $^ $(CFLAGS) 

main.o: main.c intro.c pass.c

intro.o: intro.c print.c

print.o: print.c

pass.o: pass.c print.c

clean:
	rm -f *.o FalloutTerminal
	#TODO conditional for Windows
