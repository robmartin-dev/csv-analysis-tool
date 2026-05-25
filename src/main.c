#include <stdio.h>
#include <string.h>

enum State {
	STATE_UNQUOTED,
	STATE_QUOTED
};

int main(int argc, char **argv) {
	if (argc == 1) {
		printf("No arguments provided\n");
		return 1;
	}

	if (!strcmp(argv[1], "preview")) {
		if (argc != 3) {
			printf("Usage: %s preview [filename]\n", argv[0]);
			return 1;
		}

		FILE *file = fopen(argv[2], "r");
		if (file == NULL) {
			printf("File could not be opened\n");
			return 1;
		}	

		int ch;
		enum State state = STATE_UNQUOTED;
		int new_row = 1;
		int new_field = 1;
		while ((ch = fgetc(file)) != EOF) {
			if (new_row) {
				putc('\n', stdout);
				putc('{', stdout);
				new_row = 0;
			}
			if (new_field) {
				putc('[', stdout);
				new_field = 0;
			}
			if (state == STATE_UNQUOTED) {
				if (ch == '"') {
					state = STATE_QUOTED;
				} else if (ch == ',') {
					putc(']', stdout);
					new_field = 1;
				} else if (ch == '\n') {
					putc(']', stdout);
					putc('}', stdout);
					new_row = 1;
					new_field = 1;
				} else {
					putc(ch, stdout);
				}
			} else {
				if (ch == '"') {
					state = STATE_UNQUOTED;
				} else {
					putc(ch, stdout);
				}
			}
		}
	}
	
	return 0;
}

