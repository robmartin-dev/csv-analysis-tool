#include "parser.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_COLS 20
#define MAX_FIELD_SIZE 256

void parse_csv(FILE *file) {
	char row_data[MAX_COLS][MAX_FIELD_SIZE];
	int col_idx = 0;
	int ch_idx = 0;
	enum State state = STATE_UNQUOTED;
	int ch;
	while ((ch = fgetc(file)) != EOF) {
		if (state == STATE_UNQUOTED) {
			if (ch == '"') {
				state = STATE_QUOTED;
			} else if (ch == ',') {
				if (col_idx == MAX_COLS) {
					printf("CSV must have a maximum of %d columns", MAX_COLS);
					exit(1);
				}
				row_data[col_idx][ch_idx] = '\0';
				col_idx++;
				ch_idx = 0;
			} else if (ch == '\n') {
				row_data[col_idx][ch_idx] = '\0';
				printf("Row, field 0: %s\n", row_data[0]);
				col_idx = 0;
				ch_idx = 0;
			} else {
				if (ch_idx < MAX_FIELD_SIZE - 1) {
					row_data[col_idx][ch_idx++] = ch;
				}
			}
		} else {
			if (ch == '"') {
				state = STATE_UNQUOTED;
			} else {
				if (ch_idx < MAX_FIELD_SIZE - 1) {
					row_data[col_idx][ch_idx++] = ch;
				}
			}
		}
	}

	if (ch_idx > 0 || col_idx > 0) {
		row_data[col_idx][ch_idx] = '\0';
		printf("Row, field 0: %s\n", row_data[0]);
	}
}
