#include <stdio.h>
#include <stdlib.h>

#include "functions.h"

int main(void) {
    const char *filenames[] = {"state1.txt", "state2.txt", "state3.txt", /*Add more*/};
    int num_states = sizeof(filenames) / sizeof(filenames[0]);
    state_rated *states = malloc(num_states * sizeof(state_rated));

    if (states == NULL) {
        perror("ERROR ALLOCATING MEMORY");
        return EXIT_FAILURE;
    }

    int total_mandates_trump_average = 0;
    int total_mandates_harris_average = 0;

    for (int i = 0; i < num_states; i++) {
        FILE *file = fopen(filenames[i], "r");
        if (file == NULL) {
            perror("ERROR OPENING FILE");
            free(states);
            return EXIT_FAILURE;
        }

        fscanf(file, "State: %*d\n");
        fscanf(file, "Mandates: %d\n", &states[i].mandates);
        get_votes(file, &states[i].v);
        fclose(file);
    }

    for (int i = 0; i < num_states; i++) {
        printf("State %d:\n", i + 1);
        results(&states[i].v);

        double average_trump = average(states[i].v.trump, 10);
        double average_harris = average(states[i].v.harris, 10);

        printf("Average votes for Trump: %.2f\n", average_trump);
        printf("Average votes for Harris: %.2f\n", average_harris);

        if (average_trump > average_harris) {
            printf("Average Winner: Trump wins %d mandates\n", states[i].mandates);
            total_mandates_trump_average += states[i].mandates;
        } else {
            printf("Average Winner: Harris wins %d mandates\n", states[i].mandates);
            total_mandates_harris_average += states[i].mandates;
        }
    }

    printf("\nTotal mandates based on average:\n");
    printf("Trump: %d\n", total_mandates_trump_average);
    printf("Harris: %d\n", total_mandates_harris_average);

    free(states);
    return 0;
}

void get_votes(FILE *f, votes_rated *v) {
    fscanf(f, "Total votes: %d\n", &v->total);
    for (int i = 0; i < 10; i++) {
        fscanf(f, "Trump %*d: %d\n", &v->trump[i]);
        v->trump[i] *= (i + 1) * 0.1;
        fscanf(f, "Harris %*d: %d\n", &v->harris[i]);
        v->harris[i] *= (i + 1) * 0.1;
    }
}

void results(votes_rated *v) {
    printf("Total votes: %d\n", v->total);
    for (int i = 0; i < 10; i++) {
        printf("Rated %d:\n", i + 1);
        printf("  Trump: %d\n", v->trump[i]);
        printf("  Harris: %d\n", v->harris[i]);
    }
}

double average(int votes[], int size) {
    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum += votes[i];
    }
    return sum / (double)size;
}