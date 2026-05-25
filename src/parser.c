#include "parser.h"
#include <stdio.h>
#include <string.h>

void parse_csv(FILE *file) {
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
