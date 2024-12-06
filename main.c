#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "functions.h"

int main() {
    srand(time(NULL));

    candidate candidate_arr[CANDIDATES];
    voter *voter_arr = malloc(sizeof(voter) * POPULATION);
    state *state_arr = malloc(sizeof(state) * STATES);
    if(voter_arr == NULL || state_arr == NULL) {
        printf("Error allocating memory\n");
        exit(EXIT_FAILURE);
    }
    printf("Initializing the voter array...\n");
    init_state(state_arr);
    printf("Initializing the candidate array...\n");
    init_candidates(candidate_arr);
    int current_i_voter = 0;
    for (int i = 0; i < STATES; i++) {
        printf("Initializing the voter array for %s...\n", state_arr[i].name);
        init_voters(state_arr, voter_arr, state_arr[i], current_i_voter);
        current_i_voter += state_arr[i].population;
    }
    printf("Calculating the distance from voters to candidates...\n");
    get_distance(voter_arr, candidate_arr, POPULATION);

    current_i_voter = 0;
    printf("Calculate winners for each state..\n");
    for(int i = 0; i < STATES; i++) {
        printf("Calculating winners for voter %s...\n", state_arr[i].name);
        int rated_winner = voting_rated(voter_arr, candidate_arr, state_arr[i].population);
        candidate_arr[rated_winner].votes_rated += state_arr[i].electoral_votes;
        current_i_voter += state_arr[i].population;
    }
    for (int i = 0; i < CANDIDATES; i++) {
        printf("Candidate %d: %s\n", i, candidate_arr[i].name);
        //printf("FPTP mandates: %d\n", candidate_arr[i].votes_fptp);
        printf("Rated mandates: %d\n", candidate_arr[i].votes_rated);
    }

    free(voter_arr);
    free(state_arr);

    return 0;
}