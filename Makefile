CC = gcc
CFLAGS = -Wall -Wextra -Werror -g

all:
	$(CC) $(CFLAGS) src/main.c src/parser.c -o mytool

clean:
	rm -f mytool
