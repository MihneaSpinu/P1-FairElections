#include <stdio.h>
#include <stdlib.h>
#include "functions.h"

int ranked_choice_voting(int state_population, voter voter_arr[], candidate candidate_arr[], int start_index) {

    // Første runde: Tæl førstevalgstemmer baseret på mindste afstand
    for(int i = 0; i < CANDIDATES; i++) {
        candidate_arr[i].eliminated = 0;
    }
    distribute_votes(voter_arr, candidate_arr, state_population, start_index);

    // Loop indtil der er fundet en vinder
    while (1) {

        // Tjek om der er en flertalsvinder
        int winner = check_majority(candidate_arr, state_population);
        if (winner != -1) {
            return winner;
        }

        // Find kandidaten med færrest stemmer og eliminér den
        int eliminated_candidate = find_lowest_votes(candidate_arr);
        candidate_arr[eliminated_candidate].eliminated = 1;

        // Redistribuer stemmer fra eliminerede kandidater
        distribute_votes(voter_arr, candidate_arr, state_population, start_index);

        // Tjek om der kun er én kandidat tilbage
        int remaining_candidates = CANDIDATES;
        for (int i = 0; i < CANDIDATES; i++) {
            if (candidate_arr[i].eliminated) {
                remaining_candidates--;
            }
        }

        if (remaining_candidates == 1) {
            for (int i = 0; i < CANDIDATES; i++) {
                if (!candidate_arr[i].eliminated) {
                    return i;
                }
            }
        }
    }
}

// Hjælpefunktioner
int check_majority(candidate candidate_arr[], int state_population) {
    for (int i = 0; i < CANDIDATES; i++) {
        if (candidate_arr[i].votes_rcv > state_population / 2) {
            return i; // Vinderen fundet
        }
    }
    return -1; // Ingen vinder endnu
}

int find_lowest_votes(candidate candidate_arr[]) {
    int min_votes = INT_MAX;
    int candidate_to_eliminate = -1;

    for (int i = 0; i < CANDIDATES; i++) {
        if (!candidate_arr[i].eliminated && candidate_arr[i].votes_rcv < min_votes) {
            min_votes = candidate_arr[i].votes_rcv;
            candidate_to_eliminate = i;
        }
    }
    return candidate_to_eliminate;
}

void distribute_votes(voter voter_arr[], candidate candidate_arr[], int state_population, int start_index) {

    for(int i = 0; i < CANDIDATES; i++) {
        if(!candidate_arr[i].eliminated) {
            candidate_arr[i].votes_rcv = 0;
        }
    }

    for (int i = start_index; i < state_population + start_index; i++) {
        int closest_candidate;
        double min_distance = INT_MAX;

        for (int j = 0; j < CANDIDATES; j++) {
            if (!candidate_arr[j].eliminated && voter_arr[i].distance_to[j] < min_distance) {
                closest_candidate = j;
                min_distance = voter_arr[i].distance_to[j];
            }
        }
        candidate_arr[closest_candidate].votes_rcv++;
    }
}