#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

#include "functions.h"

// Run the first past the post voting system
int first_past_the_post(voter voter_arr[], int state_population, int start_index, state *current_state, int num_of_candidates) {

    int *votes_can = calloc(num_of_candidates, sizeof(int));
    check_memory_allocation(votes_can);

    // Loop through all voters
    for (int i = start_index; i < state_population + start_index; i++) {
        // Find the candidate with the smallest distance to the voter
        int min_distance = INT_MAX;
        int candidate_index = -1;

        // Loop through all candidates
        for (int j = 0; j < num_of_candidates; j++) {
            // Check if the candidate is eliminated
            if (voter_arr[i].distance_to[j] < min_distance) {
                // Update the candidate with the smallest distance
                min_distance = voter_arr[i].distance_to[j];
                candidate_index = j;
            }
        }

        // Increment the votes for the candidate
        if (candidate_index != -1) {
            votes_can[candidate_index]++;
            current_state->candidate_votes_fptp[candidate_index]++;
        }
    }

    int winner = 0;
    for (int i = 0; i < num_of_candidates; i++) {
        if(votes_can[i] > votes_can[winner]) {
            winner = i;
        }
    }
    free(votes_can);
    return winner;
}