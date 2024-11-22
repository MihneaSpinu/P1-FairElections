// Waiting to be implemented in the main program
// Commented out for now


/*
 *
#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int total;
    int trump[10];
    int harris[10];
} votes;

void get_votes(FILE* f, votes* v);

void results(votes* v);

void median(int votes[], int size, const char* candidate);

void average(int votes[], int size, const char* candidate);

int main(void)
{
    FILE* file = fopen("rated.txt", "r");
    if (file == NULL)
    {
        perror("ERROR OPENING FILE");
        return EXIT_FAILURE;
    }

    votes v;
    get_votes(file, &v);
    fclose(file);

    results(&v);

    median(v.trump, 10, "Trump");
    median(v.harris, 10, "Harris");

    average(v.trump, 10, "Trump");
    average(v.harris, 10, "Harris");

    return 0;
}

void get_votes(FILE* f, votes* v)
{
    fscanf(f, "Total votes: %d\n", &v->total);
    for (int i = 0; i < 10; i++)
    {
        fscanf(f, "Trump %*d: %d\n", &v->trump[i]);
        fscanf(f, "Harris %*d: %d\n", &v->harris[i]);
    }
}

void results(votes* v)
{
    printf("Total votes: %d\n", v->total);
    for (int i = 0; i < 10; i++)
    {
        printf("Rated %d:\n", i + 1);
        printf("  Trump: %d\n", v->trump[i]);
        printf("  Harris: %d\n", v->harris[i]);
    }
}

void median(int votes[], int size, const char* candidate)
{
    for (int i = 0; i < size - 1; i++)
    {
        for (int j = i + 1; j < size; j++)
        {
            if (votes[i] > votes[j])
            {
                int temp = votes[i];
                votes[i] = votes[j];
                votes[j] = temp;
            }
        }
    }

    double median;
    if (size % 2 == 0)
    {
        median = (votes[size / 2 - 1] + votes[size / 2]) / 2.0;
    }
    else
    {
        median = votes[size / 2];
    }

    printf("Median votes for %s: %.2f\n", candidate, median);
}

void average(int votes[], int size, const char* candidate)
{
    int sum = 0;
    for (int i = 0; i < size; i++)
    {
        sum += votes[i];
    }
    double average = sum / (double)size;
    printf("Average votes for %s: %.2f\n", candidate, average);
}

*/
