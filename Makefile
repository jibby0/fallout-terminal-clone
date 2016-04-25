ifeq ($(shell uname -s),Darwin)
	CC = /usr/local/Cellar/gcc/5.3.0/bin/gcc-5 
else
	CC = gcc
endif 

CFLAGS = -std=c99

# DEBUGGING FLAGS
# CFLAGS = -ggdb -Wall -Wextra -pedantic -std=c99

ifeq ($(OS),Windows_NT)
	CFLAGS += -lpdcurses
else
	CFLAGS += -lncurses
endif

FalloutTerminal: main.o print.o intro.o pass.o wordParse.o getline.o getdelim.o
	$(CC) -o $@ $^ $(CFLAGS) 

main.o: main.c intro.c pass.c

intro.o: intro.c print.c

print.o: print.c

pass.o: pass.c print.c

wordParse.o: wordParse.c

getline.o: getline.c 

getdelim.o: getdelim.c

clean:
ifeq ($(OS),Windows_NT)
	del *.o FalloutTerminal.exe
else
	rm -f *.o FalloutTerminal
endif
