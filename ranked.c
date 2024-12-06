#include <stdio.h>
#include <stdlib.h>
#include "functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

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
                int ranked_candidate = voter_arr[i].distance_to_[j];
                if (ranked_candidate != eliminated_candidate && !candidate_arr[ranked_candidate].eliminated) {
                    candidate_arr[ranked_candidate].votes_rcv++;
                    break;
                }
            }
        }
    }
}

#include "functions.h"

void clear_votes(candidate candidate_arr[]) {
    for (int i = 0; i < CANDIDATES; i++) {
        candidate_arr[i].votes_rcv = 0;
    }
}

void redistribute_votes(voter voter_arr[], candidate candidate_arr[], int total_voters) {
    for (int i = 0; i < total_voters; i++) {
        if (voter_arr[i].is_voting == 1) {
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
        printf("Tie detected for elimination! Resolving tie...\n");
        // Skal måske have lavet noget til hvis 1 kandidat skal elimineres men 2 har samme antal stemmer
    }

    return candidate_to_eliminate;
}

void eliminate_candidate(candidate candidate_arr[], int candidate_to_eliminate) {
    candidate_arr[candidate_to_eliminate].eliminated = 1;
    printf("Eliminating %s\n", candidate_arr[candidate_to_eliminate].name);
}

int check_majority(candidate candidate_arr[], int total_voters) {
    for (int i = 0; i < CANDIDATES; i++) {
        if (candidate_arr[i].votes_rcv > total_voters / 2) {
            return i;
        }
    }
    return -1;
}

// Starts ranked-choice voting
void start_ranked_voting(state state_arr[], voter voter_arr[], candidate candidate_arr[], int index) {
    int total_voters = state_arr[index].population;
    int eliminated_candidate = -1;
    int winner = -1;

    while (1) {
        clear_votes(candidate_arr);

        for (int i = 0; i < total_voters; i++) {
            if (voter_arr[i].is_voting == 1) {
                for (int j = 0; j < CANDIDATES; j++) {
                    int choice = voter_arr[i].distance_to_[j];
                    if (!candidate_arr[choice].eliminated) {
                        candidate_arr[choice].votes_rcv++;
                        break;
                    }
                }
            }
        }

        winner = check_majority(candidate_arr, total_voters);
        if (winner != -1) {
            printf("Winner of RCV: %s\n", candidate_arr[winner].name);
            break;
        }

        eliminated_candidate = find_lowest_votes(candidate_arr);
        eliminate_candidate(candidate_arr, eliminated_candidate);

        clear_votes(candidate_arr);
        redistribute_votes(voter_arr, candidate_arr, total_voters);

        int remaining_candidates = 0;
        for (int i = 0; i < CANDIDATES; i++) {
            if (!candidate_arr[i].eliminated) {
                remaining_candidates++;
            }
        }
        if (remaining_candidates == 1) {
            for (int i = 0; i < CANDIDATES; i++) {
                if (!candidate_arr[i].eliminated) {
                    printf("Winner of RCV: %s\n", candidate_arr[i].name);
                    break;
                }
            }
            break;
        }
    }

    printf("Ranked Voting Results:\n");
    for (int i = 0; i < CANDIDATES; i++) {
        printf("Candidate %s: %d votes\n", candidate_arr[i].name, candidate_arr[i].votes_rcv);
    }
}

void voting_rcv(state state_arr[], voter voter_arr[], candidate candidate_arr[], int index) {
    int total_voters = state_arr[index].population;
    int winner = -1;

    while (1) {
        clear_votes(candidate_arr);

        for (int i = 0; i < total_voters; i++) {
            if (voter_arr[i].is_voting == 1) {
                int first_choice = voter_arr[i].distance_to_[0];
                candidate_arr[first_choice].votes_rcv++;
            }
        }

        winner = check_majority(candidate_arr, total_voters);
        if (winner != -1) {
            printf("Winner of RCV: %s\n", candidate_arr[winner].name);
            break;
        }

        int eliminated_candidate = find_lowest_votes(candidate_arr);
        eliminate_candidate(candidate_arr, eliminated_candidate);
        clear_votes(candidate_arr);
        redistribute_votes(voter_arr, candidate_arr, total_voters);

        int remaining_candidates = 0;
        for (int i = 0; i < CANDIDATES; i++) {
            if (!candidate_arr[i].eliminated) {
                remaining_candidates++;
            }
        }
        if (remaining_candidates == 1) {
            for (int i = 0; i < CANDIDATES; i++) {
                if (!candidate_arr[i].eliminated) {
                    printf("Winner of RCV: %s\n", candidate_arr[i].name);
                    break;
                }
            }
            break;
        }
    }
}
