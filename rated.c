#include <stdio.h>
#include <stdlib.h>
#include "functions.h"
int voting_rated(voter voter_arr[], candidate candidate_arr[], int population) {
    int votes_can[CANDIDATES] = {0};
#include <stdio.h>
#include <stdlib.h>

    for (int i = 0; i < population; i++) {
        for (int j = 0; j < CANDIDATES; j++) {
            votes_can[j] += voter_arr[i].ratings[j];
        }
    }

    int winner = 0;
    for (int i = 0; i < CANDIDATES; i++) {
        printf("Rated: Candidate %s has %d votes\n", candidate_arr[i].name, votes_can[i]);
        if (votes_can[i] > votes_can[winner]) {
            winner = i;
        }
    }
    return winner;
}






/*
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "functions.h"

int voting_rated(state state_arr[], voter voter_arr[], candidate candidate_arr[]) {
    int votes_can[CANDIDATES] = {0};
    int current_i_voter = 0;
    for (int i = 0; i < STATES; i++) {
        state current_state = state_arr[i];
        for (int j = current_i_voter; j < current_i_voter + current_state.population; j++) {
            for (int k = 0; k < CANDIDATES; k++) {
                if (voter_arr[j].distance_to_[k] <= 28) {
                    votes_can[k] += 10;
                } else if (voter_arr[j].distance_to_[k] <= 56) {
                    votes_can[k] += 9;
                } else if (voter_arr[j].distance_to_[k] <= 84) {
                    votes_can[k] += 8;
                } else if (voter_arr[j].distance_to_[k] <= 112) {
                    votes_can[k] += 7;
                } else if (voter_arr[j].distance_to_[k] <= 140) {
                    votes_can[k] += 6;
                } else if (voter_arr[j].distance_to_[k] <= 168) {
                    votes_can[k] += 5;
                } else if (voter_arr[j].distance_to_[k] <= 196) {
                    votes_can[k] += 4;
                } else if (voter_arr[j].distance_to_[k] <= 224) {
                    votes_can[k] += 3;
                } else if (voter_arr[j].distance_to_[k] <= 252) {
                    votes_can[k] += 2;
                } else {
                    votes_can[k] += 1;
                }
                // Debug statement to check votes_can array after each update
                //printf("Debug: votes_can[%d] = %d\n", k, votes_can[k]);
            }
        }
        current_i_voter += current_state.population;
    }
    int winner = 0;
    for (int i = 0; i < CANDIDATES; i++) {
        printf("Rated: Candidate %s has %d votes\n", candidate_arr[i].name, votes_can[i]);
        if(votes_can[i] > votes_can[winner]) {
            winner = i;
        }
    }
    return winner;
}
*/
#include "functions.h"

int rated_voting()
{
    const char* filenames[] = {"state1.txt", "state2.txt", "state3.txt", /*Add more*/};
    int num_states = sizeof(filenames) / sizeof(filenames[0]);
    state_rated* states = malloc(num_states * sizeof(state_rated));

    if (states == NULL)
    {
        perror("ERROR ALLOCATING MEMORY");
        return EXIT_FAILURE;
    }

    int total_mandates_trump_average = 0;
    int total_mandates_harris_average = 0;

    for (int i = 0; i < num_states; i++)
    {
        FILE* file = fopen(filenames[i], "r");
        if (file == NULL)
        {
            perror("ERROR OPENING FILE");
            free(states);
            return EXIT_FAILURE;
        }

        fscanf(file, "State: %*d\n");
        fscanf(file, "Mandates: %d\n", &states[i].mandates);
        get_votes(file, &states[i].v);
        fclose(file);
    }

    for (int i = 0; i < num_states; i++)
    {
        printf("State %d:\n", i + 1);
        results(&states[i].v);

        double average_trump = average(states[i].v.trump, 10);
        double average_harris = average(states[i].v.harris, 10);

        printf("Average votes for Trump: %.2f\n", average_trump);
        printf("Average votes for Harris: %.2f\n", average_harris);

        if (average_trump > average_harris)
        {
            printf("Average Winner: Trump wins %d mandates\n", states[i].mandates);
            total_mandates_trump_average += states[i].mandates;
        }
        else
        {
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

void get_votes(FILE* f, votes_rated* v)
{
    fscanf(f, "Total votes: %d\n", &v->total);
    for (int i = 0; i < 10; i++)
    {
        fscanf(f, "Trump %*d: %d\n", &v->trump[i]);
        v->trump[i] *= (i + 1) * 0.1;
        fscanf(f, "Harris %*d: %d\n", &v->harris[i]);
        v->harris[i] *= (i + 1) * 0.1;
    }
}

void results(votes_rated* v)
{
    printf("Total votes: %d\n", v->total);
    for (int i = 0; i < 10; i++)
    {
        printf("Rated %d:\n", i + 1);
        printf("  Trump: %d\n", v->trump[i]);
        printf("  Harris: %d\n", v->harris[i]);
    }
}

double average(int votes[], int size)
{
    int sum = 0;
    for (int i = 0; i < size; i++)
    {
        sum += votes[i];
    }
    return sum / (double)size;
}
