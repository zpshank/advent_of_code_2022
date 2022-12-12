#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

#define MAX_DEQUE_SIZE 64

typedef struct deque_t {
	int tail;
	int head;
	char values[MAX_DEQUE_SIZE];
} deque_t;

void d_push_left(deque_t* d, char c) {
	// Check for no elements
	if(d->head == d->tail) {
		d->values[d->head] = c;
		d->tail = (d->tail + 1) % MAX_DEQUE_SIZE;
		return;
	}

	d->head -= 1;
	// Check if head needs to wrap around
	if (d->head == -1)
		d->head = MAX_DEQUE_SIZE - 1;

	d->values[d->head] = c;
}

void d_push_right(deque_t* d, char c) {
	d->values[d->tail] = c;
	d->tail = (d->tail + 1) % MAX_DEQUE_SIZE;
}

char d_pop_left(deque_t* d) {
	// Check for no elements
	if(d->head == d->tail)
		return '\0';

	char rc = d->values[d->head];

	d->head = (d->head + 1) % MAX_DEQUE_SIZE;

	return rc;
}

char d_pop_right(deque_t* d) {
	// Check for no elements
	if(d->head == d->tail)
		return '\0';

	int i = d->tail - 1;
	if (i == -1)
		i = MAX_DEQUE_SIZE - 1;

	char rc = d->values[i];

	d->tail = i;

	return rc;
}

void d_print(deque_t* d) {
	if (d->head == d->tail)
		return;

	for (int i = d->head; i != d->tail; i = (i + 1) % MAX_DEQUE_SIZE) {
		printf("[%c] ", d->values[i]);
	}
	printf("\n");
}

void parse_stacks(deque_t stacks[], const char* line) {
	int len = strlen(line);

	for(int i = 0; i < len; i++) {
		char c = line[i];
		if (!isalpha(c)) 
			continue;

		// Reading from top down, so push from "back"
		int idx = ((i / 4) + 1) - 1;
		deque_t* p = &stacks[idx];
		d_push_right(p, c);
	}
}

void handle_command(deque_t stacks[], const char* line) {
	int count, from, to = 0;

	sscanf(line, "move %d from %d to %d\n", &count, &from, &to);

	from--;
	to--;

	deque_t* from_p = &stacks[from];
	deque_t* to_p = &stacks[to];

	for(int i = 0; i < count; i++) {
		char c = d_pop_left(from_p);

		// Check for empty return
		if(c == '\0')
			continue;

		d_push_left(to_p, c);
	}
}

int main(void) {
	FILE* f = fopen("./input", "r");

	deque_t stacks[32] = {0};

	// parse grid
	while(!feof(f)) {
		char line[128] = {0};

		fgets(line, 128, f);

		// Digits only found at end of grid
		if(isdigit(line[1]))
			break;

		parse_stacks(stacks, line);
	}

	// handle commands
	while(!feof(f)) {
		char line[128] = {0};

		fgets(line, 128, f);

		if (line[0] == '\0' || line[0] == '\n')
			continue;

		handle_command(stacks, line);
	}

	for(int i = 0; i < 32; i++) {
		d_print(&stacks[i]);
	}

	for (int i = 0; i < 32; i++) {
		char c = stacks[i].values[stacks[i].head];
		if (c != '\0') {
			printf("%c", c);
		}
	}
	printf("\n");

	return 0;
}
