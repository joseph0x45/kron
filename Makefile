CFLAGS = -Wall -Wextra -Werror -g -pedantic -Wshadow
INCLUDES = -I./include/
LIBS = -lraylib
SRC = ./src/main.c ./src/game.c ./src/player.c
OUT = ./bin/kron.o

all:
	gcc $(CFLAGS) $(INCLUDES) -o $(OUT) $(SRC) $(LIBS)

run:
	./bin/kron.o
