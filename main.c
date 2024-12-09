#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "functions.h"

int main() {

    srand(time(NULL));

    candidate *candidate_arr = malloc(sizeof(candidate) * CANDIDATES);
    voter *voter_arr = malloc(sizeof(voter) * POPULATION);
    state *state_arr = malloc(sizeof(state) * STATES);
    if(candidate_arr == NULL || voter_arr == NULL || state_arr == NULL) {
        printf("Error allocating memory\n");
        exit(EXIT_FAILURE);
    }

    int fordelingspolitik[4][5] = {
        {50, -50, -50, -50, -50}, // RACE
        {30, -30},              // GENDER
        {-40, 20, 40},           // INCOME
        {-50, -25, 20, 30, 50}}; // AGE

    int værdipolitik[4][5] = {
        {50, -50, -50, -50, -50}, // RACE
        {30, -30},              // GENDER
        {-40, 20, 40},           // INCOME
        {-50, -25, 20, 30, 50}}; // AGE

    double calc_percent[STATES][4][5] = {0};

    printf("Initializing the states...\n");
    init_state(state_arr);

    printf("\nInitializing the candidates...\n\n");
    init_candidates(candidate_arr);

    // START INDEX - inddeler vælgerne på de korrekte pladser i voter arrayet
    int cumulative_state_population = 0, start_index[STATES];
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
            int fptp_winner = first_past_the_post(voter_arr, state_arr[i].population, start_index[i], &state_arr[i]);
            candidate_arr[fptp_winner].fptp_mandates += state_arr[i].electoral_votes;

            // RANKED VOTING
            int rcv_winner = ranked_choice_voting(state_arr[i].population, voter_arr, candidate_arr, start_index[i], &state_arr[i]);
            candidate_arr[rcv_winner].rcv_mandates += state_arr[i].electoral_votes;

            // RATED VOTING
            int rated_winner = voting_rated(voter_arr, state_arr[i].population, start_index[i], &state_arr[i]);
            candidate_arr[rated_winner].rated_mandates += state_arr[i].electoral_votes;

            // STAR VOTING
            int star_winner = voting_star(state_arr[i].population, voter_arr, candidate_arr, start_index[i], &state_arr[i]);
            candidate_arr[star_winner].star_mandates += state_arr[i].electoral_votes;
        }

    for (int i = 0; i < CANDIDATES; i++) {
        printf("\n%s (%d) got \n", candidate_arr[i].name, i + 1);
        printf("FPTP mandates: %d\n", candidate_arr[i].fptp_mandates);
        printf("STAR mandates: %d\n", candidate_arr[i].star_mandates);
        printf("RATED mandates: %d\n", candidate_arr[i].rated_mandates);
        printf("RANKED mandates: %d\n", candidate_arr[i].rcv_mandates);
    }

    //print_winners();
    //determine_fairness();

    prompt_stats(state_arr, calc_percent, candidate_arr);

    free(voter_arr);
    free(state_arr);
    free(candidate_arr);

    return 0;
}

/*
If((age >= old || race == white || gender == male)) && income != high && rand() % 5 == 0)
Voter.income += 1;
*/