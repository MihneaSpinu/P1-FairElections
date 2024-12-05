#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

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
