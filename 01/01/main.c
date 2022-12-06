#include <stdio.h>
#include <stdlib.h>

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

    int max_index = 0;
    int max_sum = get_next_sum(f);
    int next_sum = max_sum;

    int i = 0;
    while (!feof(f)) {
        next_sum = get_next_sum(f);
        if (next_sum > max_sum) {
            max_sum = next_sum;
            max_index = i;
        }
        i++;
    }

    printf("Max Elf: %d, Max Sum: %d\n", max_index, max_sum);

    fclose(f);

    return 0;

}
