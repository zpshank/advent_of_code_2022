#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void split(char *left_out, char* right_out, const char* s, char c) {
	size_t s_len = strlen(s);

	// Pointer to character location
	char *char_p = strchr(s, c);
	
	int left_len = char_p - s;
	strncpy(left_out, s, left_len);

	int right_len = s_len - left_len - 1;
	strncpy(right_out, char_p + 1, right_len);
}

void get_range(int* range_out, const char *s) {
	size_t s_len = strlen(s);

	char left[16] = {0};
	char right[16] = {0};

	split(left, right, s, '-');

	range_out[0] = atoi(left);
	range_out[1] = atoi(right);
};

int are_assignments_redundant(const char* s) {
	char left[16] = {0};
	char right[16] = {0};

	split(left, right, s, ',');
	
	int range_left[2] = {0};
	int range_right[2] = {0};

	get_range(range_left, left);
	get_range(range_right, right);

	// Check for redundancy
	return (range_left[0] >= range_right[0] && range_left[1] <= range_right[1])
		|| (range_right[0] >= range_left[0] && range_right[1] <= range_left[1]);
}

int main(void) {

	FILE* f = fopen("./input", "r");

	int redundant_assignments = 0;

	while (!feof(f)) {
		char line[32] = {0};

		fgets(line, 32, f);

		if (line[0] == '\0') continue;

		redundant_assignments += are_assignments_redundant(line);
	}

	printf("Redundant Assignment Count: %d\n", redundant_assignments);

	return 0;
}
