#include <stdio.h>
#include <stdlib.h>
#include "functions.h"

void voting_ranked(state current_state, voter voter_arr[], candidate candidate_arr[]) {
    int total_voters = current_state.population;
    int winner;

    // Beregn politisk afstand for vælgerne til kandidaterne
    get_distance(voter_arr, candidate_arr, total_voters);

    // Loop indtil der er en vinder
    while (1) {
        // Nulstil stemmetælling
        for (int i = 0; i < CANDIDATES; i++) {
            candidate_arr[i].votes_rcv = 0;
        }

        // Første runde: Tæl førstevalgstemmer baseret på mindste afstand
        for (int i = 0; i < total_voters; i++) {
            if (voter_arr[i].is_voting) {
                int closest_candidate = 0;
                double min_distance = voter_arr[i].distance_to[0];

                for (int j = 1; j < CANDIDATES; j++) {
                    if (voter_arr[i].distance_to[j] < min_distance) {
                        closest_candidate = j;
                        min_distance = voter_arr[i].distance_to[j];
                    }
                }

                candidate_arr[closest_candidate].votes_rcv++;
            }
        }

        // Tjek om der er en flertalsvinder
        winner = check_majority(candidate_arr, total_voters);
        if (winner != -1) {
            printf("Winner of Ranked Voting: %s\n", candidate_arr[winner].name);
            break;
        }

        // Find kandidaten med færrest stemmer og eliminér den
        int eliminated_candidate = find_lowest_votes(candidate_arr);
        candidate_arr[eliminated_candidate].eliminated = 1;
        printf("Eliminating %s\n", candidate_arr[eliminated_candidate].name);

        // Redistribuer stemmer fra eliminerede kandidater
        redistribute_votes(voter_arr, candidate_arr, eliminated_candidate);

        // Tjek om der kun er én kandidat tilbage
        int remaining_candidates = 0;
        for (int i = 0; i < CANDIDATES; i++) {
            if (!candidate_arr[i].eliminated) {
                remaining_candidates++;
            }
        }
        if (remaining_candidates == 1) {
            for (int i = 0; i < CANDIDATES; i++) {
                if (!candidate_arr[i].eliminated) {
                    printf("Winner of Ranked Voting: %s\n", candidate_arr[i].name);
                    break;
                }
            }
            break;
        }
    }
}

void ranked_voting(state state_arr[], voter voters_arr[], candidate candidate_arr[]) {
    for (int i = 0; i < STATES; i++) {
        voting_ranked(state_arr[i], voters_arr, candidate_arr);
    }
}

// Hjælpefunktioner
int check_majority(candidate candidate_arr[], int total_voters) {
    for (int i = 0; i < CANDIDATES; i++) {
        if (candidate_arr[i].votes_rcv > total_voters / 2) {
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

void redistribute_votes(voter voter_arr[], candidate candidate_arr[], int eliminated_candidate) {
    for (int i = 0; i < POPULATION; i++) {
        if (voter_arr[i].is_voting) {
            for (int j = 0; j < CANDIDATES; j++) {
                int ranked_candidate = voter_arr[i].distance_to[j];
                if (ranked_candidate != eliminated_candidate && !candidate_arr[ranked_candidate].eliminated) {
                    candidate_arr[ranked_candidate].votes_rcv++;
                    break;
                }
            }
        }
    }
}