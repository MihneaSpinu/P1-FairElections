#include <stdio.h>
#include <limits.h>
#include "functions.h"

// Run the first past the post voting system
int first_past_the_post(voter voter_arr[], int state_population, int start_index) {
    int votes_can[CANDIDATES];
    for (int i = 0; i < CANDIDATES; i++) {
        votes_can[i] = 0;
    }
    // Loop through all voters
    for (int i = start_index; i < state_population + start_index; i++) {
        // Check if the voter is voting

            // Find the candidate with the smallest distance to the voter
            int min_distance = INT_MAX;
            int candidate_index = -1;

            // Loop through all candidates
            for (int j = 0; j < CANDIDATES; j++) {
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
            }
    }

    int winner = 0;
    for (int i = 0; i < CANDIDATES; i++) {
        //printf("Candidate %s has %d votes\n", candidate_arr[i].name, votes_can[i]);
        //printf("Candidate %s has %d votes\n", candidate_arr[winner].name, votes_can[winner]);
        if(votes_can[i] > votes_can[winner]) {
            winner = i;
        }
    }
    return winner;
}