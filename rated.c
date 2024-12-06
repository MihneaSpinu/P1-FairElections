#include <stdio.h>
#include <stdlib.h>
#include "functions.h"
int voting_rated(voter voter_arr[], candidate candidate_arr[], int population, state *current_state) {
    int votes_can[CANDIDATES] = {0};

    for (int i = 0; i < population; i++) {
        for (int j = 0; j < CANDIDATES; j++) {
            votes_can[j] += voter_arr[i].ratings[j];
            current_state->candidate_votes_rated[j] += voter_arr[i].ratings[j];
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