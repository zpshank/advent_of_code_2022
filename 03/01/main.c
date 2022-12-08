#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int get_priority(char c) {

	// Lower case
	if (islower(c)) {
		return c - 'a' + 1;
	}

	// Upper case
	return c - 'A' + 27;
}

char find_duplicate(const char* line) {
	// Compartment length
	int len = strlen(line) / 2;

	for (int i = 0; i < len; i++) {
		for (int j = 0; j < len; j++) {
			if (line[i] == line[j + len]) {
				return line[i];
			}
		}
	}

	return '\0';
}

int main(int argc, char **argv) {

	FILE *f = fopen("./input", "r");

	int sum = 0;

	while(!feof(f)) {
		char line[64] = {0};

		fgets(line, 64, f);

		if (line[0] == '\0') continue;

		char duplicate = find_duplicate(line);
		int priority = get_priority(duplicate);

		sum += priority;

	}

	fclose(f);

	printf("Priority Sum: %d\n", sum);

	return 0;
}
