#include <stdlib.h>
#include <stdio.h>

// ROCK:     A | X | 0
// PAPER:    B | Y | 1
// SCISSORS: C | Z | 2

//  |A|B|C
// X|3|0|6
// Y|6|3|0
// Z|0|6|3

const int outcomes[3][3] = 
{
	{3, 0, 6},
	{6, 3, 0},
	{0, 6, 3}
};

int get_id(char c) {
	switch(c) {
		case 'A':
		case 'X':
			return 0;
		case 'B':
		case 'Y':
			return 1;
		case 'C':
		case 'Z':
			return 2;
	}

	return -1;
}

int determine_score(int played, int against) {
	int score = 0;

	score += played + 1;

	score += outcomes[played][against];

	return score;
}

int get_line(FILE* f, char *out) {
	int rc = 0;
	char c = fgetc(f);
	while (c != '\n' && c != -1 && c != '\0') {
		out[rc] = c;
		c = fgetc(f);
		rc++;
	}
	return rc;
}

int get_next_score(FILE* f) {
	char line[4] = {0};
	get_line(f, line);

	if (line[0] == 0) {
		return 0;
	}

	int against = get_id(line[0]);
	int played = get_id(line[2]);
	int score = determine_score(played, against);

	return score;
}


int main(void) {
	FILE* f = fopen("./input", "r");

	int total = 0;

	while(!feof(f)) {
		total += get_next_score(f);
	}

	printf("Total Score: %d\n", total);

	return 0;
}
