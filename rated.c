#include <stdio.h>
#include <stdlib.h>
#include "functions.h"
int voting_rated(voter voter_arr[], candidate candidate_arr[], int population) {
    int votes_can[CANDIDATES] = {0};

    for (int i = 0; i < population; i++) {
        for (int j = 0; j < CANDIDATES; j++) {
            votes_can[j] += voter_arr[i].ratings[j];
        }
    }

    int winner = 0;
    for (int i = 0; i < CANDIDATES; i++) {
        printf("Rated: Candidate %s has %d votes\n", candidate_arr[i].name, votes_can[i]);
        if (votes_can[i] > votes_can[winner]) {
            winner = i;
        }
    }
    return winner;
}






/*
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "functions.h"

int voting_rated(state state_arr[], voter voter_arr[], candidate candidate_arr[]) {
    int votes_can[CANDIDATES] = {0};
    int current_i_voter = 0;
    for (int i = 0; i < STATES; i++) {
        state current_state = state_arr[i];
        for (int j = current_i_voter; j < current_i_voter + current_state.population; j++) {
            for (int k = 0; k < CANDIDATES; k++) {
                if (voter_arr[j].distance_to_[k] <= 28) {
                    votes_can[k] += 10;
                } else if (voter_arr[j].distance_to_[k] <= 56) {
                    votes_can[k] += 9;
                } else if (voter_arr[j].distance_to_[k] <= 84) {
                    votes_can[k] += 8;
                } else if (voter_arr[j].distance_to_[k] <= 112) {
                    votes_can[k] += 7;
                } else if (voter_arr[j].distance_to_[k] <= 140) {
                    votes_can[k] += 6;
                } else if (voter_arr[j].distance_to_[k] <= 168) {
                    votes_can[k] += 5;
                } else if (voter_arr[j].distance_to_[k] <= 196) {
                    votes_can[k] += 4;
                } else if (voter_arr[j].distance_to_[k] <= 224) {
                    votes_can[k] += 3;
                } else if (voter_arr[j].distance_to_[k] <= 252) {
                    votes_can[k] += 2;
                } else {
                    votes_can[k] += 1;
                }
                // Debug statement to check votes_can array after each update
                //printf("Debug: votes_can[%d] = %d\n", k, votes_can[k]);
            }
        }
        current_i_voter += current_state.population;
    }
    int winner = 0;
    for (int i = 0; i < CANDIDATES; i++) {
        printf("Rated: Candidate %s has %d votes\n", candidate_arr[i].name, votes_can[i]);
        if(votes_can[i] > votes_can[winner]) {
            winner = i;
        }
    }
    return winner;
}
*/