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

char find_badge(const char* first, const char* second, const char* third) {
	// Compartment length
	int len = strlen(first);

	for (int i = 0; i < len; i++) {

		// Find first instance of character in second and third
		//
		// If not found, returns NULL
		char *s = strchr(second, first[i]);
		char *t = strchr(third, first[i]);

		if (s != NULL && t != NULL) return first[i];
	}

	return '\0';
}

int main(int argc, char **argv) {

	FILE *f = fopen("./input", "r");

	int sum = 0;

	while(!feof(f)) {
		char first[64] = {0};
		char second[64] = {0};
		char third[64] = {0};

		fgets(first, 64, f);
		fgets(second, 64, f);
		fgets(third, 64, f);

		if (first[0] == '\0') continue;

		char badge = find_badge(first, second, third);
		int priority = get_priority(badge);

		sum += priority;
	}

	fclose(f);

	printf("Priority Sum: %d\n", sum);

	return 0;
}
