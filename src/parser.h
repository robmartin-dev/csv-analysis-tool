#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>

enum State {
	STATE_UNQUOTED,
	STATE_QUOTED
};

void parse_csv(FILE *file);

#endif
