CFLAGS = -Wall -Wextra -Werror -g -pedantic -Wshadow
ALL_CFLAGS = -Wall -Wextra -Werror -pedantic -g -O0 -std=c11 -Wshadow -Wformat -Wuninitialized -Wconversion -Wnull-dereference -fstack-protector -fsanitize=address
LIBS = -lraylib

all:
	gcc $(CFLAGS) -o ./bin/kron.o ./src/main.c $(LIBS)

run:
	./bin/kron
