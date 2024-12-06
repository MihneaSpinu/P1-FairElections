#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "functions.h"

int main() {
    srand(time(NULL));
    //Erklæring af arrays
    candidate candidate_arr[CANDIDATES];
    voter *voter_arr = malloc(sizeof(voter) * POPULATION);
    state *state_arr = malloc(sizeof(state) * STATES);
    if(voter_arr == NULL || state_arr == NULL) {
        printf("Error allocating memory\n");
        exit(EXIT_FAILURE);
    }

    double calc_percent[STATES][4][5];
    init_percent(calc_percent);

    printf("Initializing the states...\n");

    printf("Initializing the voter array...\n");
    init_state(state_arr);

    printf("\nInitializing the candidates...\n\n");

    printf("Initializing the candidate array...\n");
    init_candidates(candidate_arr);


    //Initialisering af voters fra hver stat
    int current_i_voter = 0;
    for (int i = 0; i < STATES; i++) {
        printf("Generating voters for %s...\n", state_arr[i].name);
        init_voters(state_arr, voter_arr, state_arr[i], current_i_voter, i, calc_percent);
        current_i_voter += state_arr[i].population;
    }

    printf("\nCalculating voter preference...\n");
    get_distance(voter_arr, candidate_arr, POPULATION);

    current_i_voter = 0;
    for(int i = 0; i < STATES; i++) {
        printf("Calculating winners for voter %s...\n", state_arr[i].name);
        int rated_winner = voting_rated(voter_arr, candidate_arr, state_arr[i].population);
        candidate_arr[rated_winner].votes_rated += state_arr[i].electoral_votes;
        printf("Calculating winners for %s...\n", state_arr[i].name);

        // FIRST PAST THE POST
        int fptp_winner = first_past_the_post(voter_arr, candidate_arr, state_arr[i].population, current_i_voter);
        candidate_arr[fptp_winner].votes_fptp += state_arr[i].electoral_votes;

        //rcv_voting();
        candidate_arr[fptp_winner].mandates_fptp += state_arr[i].electoral_votes;
        //ranked_choice_voting();
        //rated_voting();

        // STAR VOTING
        int star_winner = voting_star(state_arr[i].population, voter_arr, candidate_arr, current_i_voter);
        candidate_arr[star_winner].mandates_star += state_arr[i].electoral_votes;


        int star_winner = voting_star(state_arr[i].population, voter_arr, candidate_arr, current_i_voter);
        candidate_arr[star_winner].mandates_star += state_arr[i].electoral_votes;
        current_i_voter += state_arr[i].population;
    }

    for (int i = 0; i < CANDIDATES; i++) {
        printf("\n%s (%d) got \n", candidate_arr[i].name, i + 1);
        printf("FPTP mandates: %d\n", candidate_arr[i].votes_fptp);
        printf("STAR mandates: %d\n", candidate_arr[i].mandates_star);
        printf("Candidate %d: %s\n", i, candidate_arr[i].name);
        //printf("FPTP mandates: %d\n", candidate_arr[i].votes_fptp);
        printf("Rated mandates: %d\n", candidate_arr[i].votes_rated);
        printf("FPTP mandates: %d\n", candidate_arr[i].mandates_fptp);
        printf("Star Voting mandates: %d\n", candidate_arr[i].mandates_star);
    }

    start_ranked_voting(state_arr, voter_arr, candidate_arr, 0);

    //print_winners();
    //determine_fairness();

    prompt_stats(state_arr, calc_percent);




    free(voter_arr);
    free(state_arr);

    return 0;
}

/*
If((age >= old || race == white || gender == male)) && income != high && rand() % 5 == 0)
Voter.income += 1;
*/