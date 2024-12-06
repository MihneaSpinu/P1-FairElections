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

    int fordelingspolitik[4][5] = {
        {50, -50, -50, -30, 0}, // RACE
        {30, -30},              // GENDER
        {-60, 0, 40},           // INCOME
        {-50, -25, 0, 25, 50}}; // AGE

    int værdipolitik[4][5] = {
        {50, -50, -50, -30, 0}, // RACE
        {30, -30},              // GENDER
        {-60, 0, 40},           // INCOME
        {-50, -25, 0, 25, 50}}; // AGE

    double calc_percent[STATES][4][5] = {0};

    printf("Initializing the states...\n");
    init_state(state_arr);

    printf("\nInitializing the candidates...\n\n");
    init_candidates(candidate_arr);

    // START INDEX - inddeler vælgerne på de korrekte pladser i voter arrayet
    int cumulative_state_population = 0,
        start_index[STATES];
    init_index(cumulative_state_population, start_index, state_arr);

    for (int i = 0; i < STATES; i++) {
        printf("Generating voters for %s...\n", state_arr[i].name);
        init_voters(voter_arr, state_arr[i], start_index[i], i, calc_percent, fordelingspolitik, værdipolitik);
    }

    printf("\nCalculating voter preference...\n");
    get_distance(voter_arr, candidate_arr, POPULATION);
    printf("\n");

    for(int i = 0; i < STATES; i++) {
        printf("Calculating winners for %s...\n", state_arr[i].name);

        // FIRST PAST THE POST
        int fptp_winner = first_past_the_post(voter_arr, candidate_arr, state_arr[i].population, start_index[i]);
        candidate_arr[fptp_winner].votes_fptp += state_arr[i].electoral_votes;

        //voting_ranked(state_arr[i], voter_arr, candidate_arr);

        // RATED VOTING
        int rated_winner = voting_rated(voter_arr, candidate_arr, state_arr[i].population);
        candidate_arr[rated_winner].votes_rated += state_arr[i].electoral_votes;

        // STAR VOTING
        int star_winner = voting_star(state_arr[i].population, voter_arr, candidate_arr, start_index[i]);
        candidate_arr[star_winner].mandates_star += state_arr[i].electoral_votes;
    }

    for (int i = 0; i < CANDIDATES; i++) {
        printf("\n%s (%d) got \n", candidate_arr[i].name, i + 1);
        printf("FPTP mandates: %d\n", candidate_arr[i].votes_fptp);
        printf("STAR mandates: %d\n", candidate_arr[i].mandates_star);
        printf("RATED mandates: %d\n", candidate_arr[i].votes_rated);
        printf("RANKED mandates: %d\n", candidate_arr[i].votes_rcv);
    }

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