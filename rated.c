#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int total;
    int trump[10];
    int harris[10];
} votes;

void get_votes(FILE *f, votes *v);

void results(votes *v);

double median(int votes[], int size);

double average(int votes[], int size);

int main(void) {

    FILE *file = fopen("rated.txt", "r");
    if (file == NULL) {
        perror("ERROR OPENING FILE");
        return EXIT_FAILURE;
    }

    votes v;
    get_votes(file, &v);
    fclose(file);

    results(&v);

    double median_trump = median(v.trump, 10);
    double median_harris = median(v.harris, 10);

    printf("Median votes for Trump: %.2f\n", median_trump);
    printf("Median votes for Harris: %.2f\n", median_harris);

    double average_trump = average(v.trump, 10);
    double average_harris = average(v.harris, 10);

    printf("Average votes for Trump: %.2f\n", average_trump);
    printf("Average votes for Harris: %.2f\n", average_harris);

    if (median_trump > median_harris) {
        printf("Median Winner: Trump\n");
    } else {
        printf("Median Winner: Harris\n");
    }

    if (average_trump > average_harris) {
        printf("Average Winner: Trump\n");
    } else {
        printf("Average Winner: Harris\n");
    }

    return 0;
}

void get_votes(FILE *f, votes *v) {
    fscanf(f, "Total votes: %d\n", &v->total);
    for (int i = 0; i < 10; i++) {
        fscanf(f, "Trump %*d: %d\n", &v->trump[i]);
        v->trump[i] *= (i + 1) * 0.1;
        fscanf(f, "Harris %*d: %d\n", &v->harris[i]);
        v->harris[i] *= (i + 1) * 0.1;
    }
}

void results(votes *v) {
    printf("Total votes: %d\n", v->total);
    for (int i = 0; i < 10; i++) {
        printf("Rated %d:\n", i + 1);
        printf("  Trump: %d\n", v->trump[i]);
        printf("  Harris: %d\n", v->harris[i]);
    }
}

double median(int votes[], int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = i + 1; j < size; j++) {
            if (votes[i] > votes[j]) {
                int temp = votes[i];
                votes[i] = votes[j];
                votes[j] = temp;
            }
        }
    }

    if (size % 2 == 0) {
      return (votes[size / 2 - 1] + votes[size / 2]) / 2.0;
    } else {
       return votes[size / 2];
    }
}

double average(int votes[], int size) {
    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum += votes[i];
    }
    return sum / (double)size;
}