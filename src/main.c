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
		char field_buffer[256];
		int buf_idx = 0;
		enum State state = STATE_UNQUOTED;
		int new_row = 0;
		int new_field = 0;
		putc('{', stdout);
		while ((ch = fgetc(file)) != EOF) {
			if (state == STATE_UNQUOTED) {
				if (ch == '"') {
					state = STATE_QUOTED;
				} else if (ch == ',') {
					field_buffer[buf_idx] = '\0';
					new_field = 1;
				} else if (ch == '\n') {
					field_buffer[buf_idx] = '\0';
					putc('}', stdout);
					new_row = 1;
					new_field = 1;
				} else {
					field_buffer[buf_idx++] = ch;
				}
			} else {
				if (ch == '"') {
					state = STATE_UNQUOTED;
				} else {
					field_buffer[buf_idx++] = ch;
				}
			}

			if (new_row) {
				putc('\n', stdout);
				putc('{', stdout);
				new_row = 0;
			}
			if (new_field) {
				printf("[%s] ", field_buffer);
				buf_idx = 0;
				new_field = 0;
			}
		}
	}
	
	return 0;
}

