#include <stdio.h>
#include <stdlib.h>

int comp(const void *a, const void *b) {
	int x = *(const int *)a;
	int y = *(const int *)b;

	if (x < y) return 1;
	if (x > y) return -1;
	return 0;
}

int get_next_number(FILE* f) {
	int i = 0;
	char line[14] = {0};
	char next = fgetc(f);
	while (next != '\n' && next != '\0' && next != EOF) {
		line[i] = next;
		next = fgetc(f);
		i++;
	}

	if (i == 0) {
		return -1;
	}

	return atoi(line);
}

int get_next_sum(FILE* f) {
	int sum = 0;
	int next = get_next_number(f);
	while (next != -1) {
		sum += next;
		next = get_next_number(f);
	}
	return sum;
}

int main(void) {

	FILE *f = fopen("./input", "r");

	const int MAX_SUM_COUNT = 1000;
	int sums[MAX_SUM_COUNT] = {0};

	int i = 0;
	while (!feof(f)) {
		sums[i] = get_next_sum(f);
		i++;
	}
	fclose(f);

	qsort(sums, MAX_SUM_COUNT, sizeof(int), comp);

	printf("Max Sum[0]: %d\n", sums[0]);
	printf("Max Sum[1]: %d\n", sums[1]);
	printf("Max Sum[2]: %d\n", sums[2]);

	printf("Total: %d\n", sums[0] + sums[1] + sums[2]);

	return 0;

}
