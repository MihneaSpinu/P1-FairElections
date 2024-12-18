#include <limits.h>
#include <stdlib.h>
#include "functions.h"


// Run the first past the post voting system
int first_past_the_post(voter voter_arr[], int population, int start_index,
                        state *current_state, int num_of_candidates) {

    int *candidate_votes = calloc(num_of_candidates, sizeof(int));
    check_memory_allocation(candidate_votes);

    // Loop through all voters
    for(int i = start_index; i < population + start_index; i++) {
        // Find the candidate with the smallest distance to the voter
        int min_distance = INT_MAX;
        int closest_candidate = -1;

        // Loop through all candidates
        for(int j = 0; j < num_of_candidates; j++) {
            // Check if the candidate is eliminated
            if(voter_arr[i].distance_to[j] < min_distance) {
                // Update the candidate with the smallest distance
                min_distance = voter_arr[i].distance_to[j];
                closest_candidate = j;
            }
        }

        // Increment the votes for the candidate
        if(closest_candidate != -1) {
            candidate_votes[closest_candidate]++;
            current_state->candidate_votes_fptp[closest_candidate]++;
        }
    }

    int winner = 0;
    for(int i = 0; i < num_of_candidates; i++) {
        if(candidate_votes[i] > candidate_votes[winner]) {
            winner = i;
        }
    }
    free(candidate_votes);
    return winner;
}