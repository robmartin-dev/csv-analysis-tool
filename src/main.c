#include <stdio.h>
#include <string.h>

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
		while ((ch = fgetc(file)) != EOF) {
			putc(ch, stdout);
		}
	}
	
	return 0;
}

