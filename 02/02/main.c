#include <stdlib.h>
#include <stdio.h>

// ROCK: 			A | 0
// PAPER: 		B | 1
// SCISSORS: 	C | 2

// LOSE: 	X | 0
// DRAW: 	Y | 1
// WIN: 	Z | 2

// x-axis: Played
// y-axis: Against
// cell: points

//  |A|B|C
// X|3|0|6
// Y|6|3|0
// Z|0|6|3

const int scores[3][3] = 
{
	{3, 0, 6},
	{6, 3, 0},
	{0, 6, 3}
};

// x-axis: result
// y-axis: id of what you played
// cell: id of what you should play

//  |A|B|C
// X|2|0|1
// Y|0|1|2
// Z|1|2|0

const int should_play[3][3] = 
{
	{2, 0, 1},
	{0, 1, 2},
	{1, 2, 0}
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

	score += scores[played][against];

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
	int result = get_id(line[2]);
	int played = should_play[result][against];
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
