#include <stdio.h>
#include <limits.h>
#include "functions.h"

int ranked_choice_voting(int state_population, voter voter_arr[], candidate candidate_arr[], int start_index) {

    int remaining_candidates = CANDIDATES;
    for(int i = 0; i < CANDIDATES; i++) {
        candidate_arr[i].eliminated = 0;
    }
    distribute_votes(voter_arr, candidate_arr, state_population, start_index);

    while (remaining_candidates > 1) {

        // Find kandidaten med færrest stemmer og eliminér den
        int eliminated_candidate = find_lowest_votes(candidate_arr);
        candidate_arr[eliminated_candidate].eliminated = 1;
        remaining_candidates--;

        // Redistribuer stemmer fra eliminerede kandidater
        distribute_votes(voter_arr, candidate_arr, state_population, start_index);
    }

    for (int i = 0; i < CANDIDATES; i++) {
        if (!candidate_arr[i].eliminated) {
            return i;
        }
    }
}

// Hjælpefunktioner
int find_lowest_votes(candidate candidate_arr[]) {

    int min_votes = INT_MAX;
    int candidate_to_eliminate;

    for (int i = 0; i < CANDIDATES; i++) {
        if (!candidate_arr[i].eliminated && candidate_arr[i].votes_rcv < min_votes) {
            min_votes = candidate_arr[i].votes_rcv;
            candidate_to_eliminate = i;
        }
    }
    return candidate_to_eliminate;
}

void distribute_votes(voter voter_arr[], candidate candidate_arr[], int state_population, int start_index) {

    int closest_candidate;
    double min_distance;

    for(int i = 0; i < CANDIDATES; i++) {
        if(!candidate_arr[i].eliminated) {
            candidate_arr[i].votes_rcv = 0;
        }
    }

    for (int i = start_index; i < state_population + start_index; i++) {
        min_distance = INT_MAX;
        for (int j = 0; j < CANDIDATES; j++) {
            if (!candidate_arr[j].eliminated && voter_arr[i].distance_to[j] < min_distance) {
                closest_candidate = j;
                min_distance = voter_arr[i].distance_to[j];
            }
        }
        candidate_arr[closest_candidate].votes_rcv++;
    }
}