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

    printf("Initializing the state array...\n");
    init_state(state_arr);

    printf("Initializing the candidate array...\n");
    init_candidates(candidate_arr);

    int current_i_voter = 0;
    for (int i = 0; i < STATES; i++) {
        printf("Generating voters for %s...\n", state_arr[i].name);
        init_voters(state_arr, voter_arr, state_arr[i], current_i_voter);
        current_i_voter += state_arr[i].population;
    }

    printf("Calculating voter preference...\n");
    get_distance(voter_arr, candidate_arr, POPULATION);

    current_i_voter = 0;
    for(int i = 0; i < STATES; i++) {
        printf("Calculating winner for %s...\n", state_arr[i].name);
        int fptp_winner = first_past_the_post(voter_arr, candidate_arr, state_arr[i].population, current_i_voter);
        candidate_arr[fptp_winner].votes_fptp += state_arr[i].electoral_votes;
        //ranked_choice_voting();
        //rated_voting();
        int star_winner = voting_star(state_arr[i].population, voter_arr, candidate_arr, current_i_voter);
        candidate_arr[star_winner].mandates_star += state_arr[i].electoral_votes;
        current_i_voter += state_arr[i].population;
    }

    for (int i = 0; i < CANDIDATES; i++) {
        printf("\n%s (%d) got \n%d FPTP votes\n%d STAR votes\n", candidate_arr[i].name, i + 1, candidate_arr[i].votes_fptp, candidate_arr[i].mandates_star);
    }

    //print_winners();
    //determine_fairness();

    free(voter_arr);
    free(state_arr);

    return 0;
}

/*
If((age >= old || race == white || gender == male)) && income != high && rand() % 5 == 0)
Voter.income += 1;
*/