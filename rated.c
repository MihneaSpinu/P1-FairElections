#include "functions.h"

int voting_rated(voter voter_arr[], int state_population, int start_index) {

    int votes_can[CANDIDATES];
    for(int i = 0; i < CANDIDATES; i++) {
        votes_can[i] = 0;
    }

    for (int i = start_index; i < state_population + start_index; i++) {
        for (int j = 0; j < CANDIDATES; j++) {
            get_ratings(voter_arr, i, j);
        }
    }

    for (int i = start_index; i < state_population + start_index; i++) {
        for (int j = 0; j < CANDIDATES; j++) {
            votes_can[j] += voter_arr[i].ratings[j];

        }
    }



    int winner = 0;
    for (int i = 0; i < CANDIDATES; i++) {
        if (votes_can[i] > votes_can[winner]) {
            winner = i;
        }
    }
    return winner;
}