#include <stdlib.h>
#include "functions.h"


int voting_rated(voter voter_arr[], int population, int start_index,
                 state *current_state, int num_of_candidates) {

    int *candidate_votes = calloc(num_of_candidates, sizeof(int));
    check_memory_allocation(candidate_votes);

    for (int i = start_index; i < population + start_index; i++) {
        for (int j = 0; j < num_of_candidates; j++) {
            candidate_votes[j] += voter_arr[i].ratings[j];
            current_state->candidate_votes_rated[j] += voter_arr[i].ratings[j];
        }
    }

    int winner = 0;
    for (int i = 0; i < num_of_candidates; i++) {
        if (candidate_votes[i] > candidate_votes[winner]) {
            winner = i;
        }
    }
    free(candidate_votes);
    return winner;
}