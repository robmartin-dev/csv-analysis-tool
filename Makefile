CC = gcc
CFLAGS = -Wall -Wextra -Werror -g

all:
	$(CC) $(CFLAGS) src/main.c -o mytool

clean:
	rm -f mytool
