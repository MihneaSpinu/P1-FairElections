#include <limits.h>
#include <stdio.h>
#include "functions.h"

// Funktion til at nulstille alle kandidaters stemmer
void clear_votes(candidate candidate_arr[]) {
    for (int i = 0; i < CANDIDATES; i++) {
        candidate_arr[i].votes_rcv = 0;
    }
}

// Tjek om en kandidat har flertal
int check_majority(candidate candidate_arr[], int total_voters) {
    for (int i = 0; i < CANDIDATES; i++) {
        if (candidate_arr[i].votes_rcv > total_voters / 2) {
            return i;
        }
    }
    return -1;
}

// Find kandidaten med færrest stemmer
int find_lowest_votes(candidate candidate_arr[]) {
    int min_votes = INT_MAX;
    int candidate_to_eliminate = -1;
    int tie_count = 0;

    for (int i = 0; i < CANDIDATES; i++) {
        if (!candidate_arr[i].eliminated) {
            if (candidate_arr[i].votes_rcv < min_votes) {
                min_votes = candidate_arr[i].votes_rcv;
                candidate_to_eliminate = i;
                tie_count = 1;
            } else if (candidate_arr[i].votes_rcv == min_votes) {
                tie_count++;
            }
        }
    }

    if (tie_count > 1) {
        printf("Uafgjort opdaget til eliminering! Løser uafgjort...\n");
        // Implementér løsning af uafgjort hvis nødvendigt
    }

    return candidate_to_eliminate;
}

// Eliminer en kandidat
void eliminate_candidate(candidate candidate_arr[], int candidate_to_eliminate) {
    candidate_arr[candidate_to_eliminate].eliminated = 1;
    printf("Eliminerer %s\n", candidate_arr[candidate_to_eliminate].name);
}

// Redistribuér stemmer for eliminerede kandidater
void redistribute_votes(voter voter_arr[], candidate candidate_arr[], int total_voters) {
    for (int i = 0; i < total_voters; i++) {
        if (voter_arr[i].is_voting) {
            for (int j = 0; j < CANDIDATES; j++) {
                int choice = voter_arr[i].distance_to_[j];
                if (!candidate_arr[choice].eliminated) {
                    candidate_arr[choice].votes_rcv++;
                    break;
                }
            }
        }
    }
}

// Gennemfør ranked-choice-afstemning for en enkelt stat
int voting_ranked(state current_state, voter voter_arr[], candidate candidate_arr[]) {
    int total_voters = current_state.population;

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
                double min_distance = voter_arr[i].distance_to_[0];

                for (int j = 1; j < CANDIDATES; j++) {
                    if (voter_arr[i].distance_to_[j] < min_distance) {
                        closest_candidate = j;
                        min_distance = voter_arr[i].distance_to_[j];
                    }
                }

                candidate_arr[closest_candidate].votes_rcv++;
            }
        }

        // Tjek om der er en flertalsvinder
        int winner = check_majority(candidate_arr, total_voters);
        if (winner != -1) {
            return winner; // Returnér vinderens indeks
        }

        // Find kandidaten med færrest stemmer og eliminér den
        int eliminated_candidate = find_lowest_votes(candidate_arr);
        candidate_arr[eliminated_candidate].eliminated = 1;
        printf("Eliminerer %s\n", candidate_arr[eliminated_candidate].name);

        // Redistribuer stemmer fra eliminerede kandidater
        redistribute_votes(voter_arr, candidate_arr, total_voters);

        // Tjek om der kun er én kandidat tilbage
        int remaining_candidates = 0;
        int last_candidate_index = -1;

        for (int i = 0; i < CANDIDATES; i++) {
            if (!candidate_arr[i].eliminated) {
                remaining_candidates++;
                last_candidate_index = i;
            }
        }

        if (remaining_candidates == 1) {
            return last_candidate_index; // Returnér indekset for den sidste kandidat
        }
    }
}

// Start ranked-choice-afstemning på tværs af alle stater
void ranked_voting(state state_arr[], voter voter_arr[], candidate candidate_arr[]) {
    for (int i = 0; i < STATES; i++) {
        printf("Behandler stat %d:\n", i + 1);
        int winner = voting_ranked(state_arr[i], voter_arr, candidate_arr);
        printf("Vinder af Ranked Voting i stat %d: %s\n", i + 1, candidate_arr[winner].name);
    }
}
