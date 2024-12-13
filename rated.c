#include <stdlib.h>

#include "functions.h"

int voting_rated(voter voter_arr[], int state_population, int start_index, state *current_state, int num_of_candidates) {

    int *votes_can = calloc(num_of_candidates, sizeof(int));
    check_memory_allocation(votes_can);

    for (int i = start_index; i < state_population + start_index; i++) {
        for (int j = 0; j < num_of_candidates; j++) {
            votes_can[j] += voter_arr[i].ratings[j];
            current_state->candidate_votes_rated[j] += voter_arr[i].ratings[j];
        }
    }



    int winner = 0;
    for (int i = 0; i < num_of_candidates; i++) {
        if (votes_can[i] > votes_can[winner]) {
            winner = i;
        }
    }
    free(votes_can);
    return winner;
}