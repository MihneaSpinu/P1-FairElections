#include "functions.h"

int voting_rated(voter voter_arr[], candidate candidate_arr[], int state_population) {

    int votes_can[CANDIDATES];
    for(int i = 0; i < CANDIDATES; i++) {
        votes_can[i] = 0;
    }

    for (int i = 0; i < state_population; i++) {
        for (int j = 0; j < CANDIDATES; j++) {
            votes_can[j] += voter_arr[i].ratings[j];
        }
    }

    int winner = 0;
    for (int i = 0; i < CANDIDATES; i++) {
        //printf("Rated: Candidate %s has %d votes\n", candidate_arr[i].name, votes_can[i]);
        if (votes_can[i] > votes_can[winner]) {
            winner = i;
        }
    }
    return winner;
}