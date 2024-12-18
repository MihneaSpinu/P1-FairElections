#include <stdio.h>
#include <limits.h>
#include "functions.h"


int ranked_choice_voting(int population, voter voter_arr[], candidate candidate_arr[],
                         int start_index, state *current_state, int num_of_candidates) {

    // Resets all candidates' eliminated status
    int remaining_candidates = num_of_candidates;
    for(int i = 0; i < num_of_candidates; i++) {
        candidate_arr[i].eliminated = 0;
    }
    // First round of voting
    distribute_votes(voter_arr, candidate_arr, population, start_index, current_state, num_of_candidates);

    while (remaining_candidates > 1) {

        // Finds the candidate with the lowest votes and eliminates them
        int eliminated_candidate = find_lowest_votes(candidate_arr, num_of_candidates);
        candidate_arr[eliminated_candidate].eliminated = 1;
        remaining_candidates--;

        // Redistributes the votes from the eliminated candidate
        distribute_votes(voter_arr, candidate_arr, population, start_index, current_state, num_of_candidates);
    }

    for (int i = 0; i < num_of_candidates; i++) {
        if (!candidate_arr[i].eliminated) {
            return i;
        }
    }
}

// Finds the candidate with the lowest votes and returns their index
int find_lowest_votes(candidate candidate_arr[], int num_of_candidates) {

    int min_votes = INT_MAX;
    int candidate_to_eliminate;

    for (int i = 0; i < num_of_candidates; i++) {
        if (!candidate_arr[i].eliminated && candidate_arr[i].votes_rcv < min_votes) {
            min_votes = candidate_arr[i].votes_rcv;
            candidate_to_eliminate = i;
        }
    }
    return candidate_to_eliminate;
}


// Distributes the votes
void distribute_votes(voter voter_arr[], candidate candidate_arr[], int state_population,
                      int start_index, state *current_state, int num_of_candidates) {

    int closest_candidate;
    float min_distance;

    for(int i = 0; i < num_of_candidates; i++) {
        if(!candidate_arr[i].eliminated) {
            candidate_arr[i].votes_rcv = 0;
        }
    }

    for (int i = start_index; i < state_population + start_index; i++) {
        min_distance = INT_MAX;
        for (int j = 0; j < num_of_candidates; j++) {
            if (!candidate_arr[j].eliminated && voter_arr[i].distance_to[j] < min_distance) {
                closest_candidate = j;
                min_distance = voter_arr[i].distance_to[j];
            }
        }
        candidate_arr[closest_candidate].votes_rcv++;
        current_state->candidate_votes_rcv[closest_candidate]++;
    }
}