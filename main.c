#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "functions.h"

int main() {

    srand(time(NULL));
    double calc_percent[STATES][4][5] = {0};

    int simulation_choice,
        electoral_choice,
        candidate_choice,
        voting_system_choice,
        candidates = 0;
    char candidate_name[5][MAX_NAME_LENGTH];
    int værdi[5];
    int fordeling[5];

    scan_election_settings(&simulation_choice, &electoral_choice, &candidate_choice,
                           &voting_system_choice, &candidates, candidate_name,
                           værdi, fordeling);

    printf("Allocating the arrays...\n");
    candidate *candidate_arr = (candidate *)malloc(sizeof(candidate) * candidates);
    voter *voter_arr = (voter *)malloc(sizeof(voter) * POPULATION);
    state *state_arr = (state *)malloc(sizeof(state) * STATES);
    if(candidate_arr == NULL || voter_arr == NULL || state_arr == NULL) {
        printf("Error allocating memory\n");
        exit(EXIT_FAILURE);
    }
    printf("\nInitializing the candidates...\n\n");
    init_candidates(candidate_arr, candidates, candidate_name, værdi, fordeling);

    printf("Initializing the states...\n\n");
    init_state(state_arr, candidates);

    // START INDEX - inddeler vælgerne på de korrekte pladser i voter arrayet
    int cumulative_state_population = 0;
    int start_index[STATES];
    init_index(cumulative_state_population, start_index, state_arr);

    for (int i = 0; i < STATES; i++) {
        printf("Generating voters for %s...\n", state_arr[i].name);
        init_voters(voter_arr, state_arr[i], start_index[i], i, calc_percent);
    }

    printf("\nCalculating voter preference...\n");
    get_distance(voter_arr, candidate_arr, POPULATION, candidates);
    printf("\n");

    if(electoral_choice == 1 && voting_system_choice == 1) {
        for(int i = 0; i < STATES; i++) {
            printf("Calculating winners for %s...\n", state_arr[i].name);
            if(i == 1 || i == 19) { // Alaska & MAINE
                int rcv_winner = ranked_choice_voting(state_arr[i].population, voter_arr, candidate_arr, start_index[i], &state_arr[i], candidates);
                candidate_arr[rcv_winner].general_mandates += state_arr[i].electoral_votes;
            } else {
                int fptp_winner = first_past_the_post(voter_arr, state_arr[i].population, start_index[i], &state_arr[i], candidates);
                candidate_arr[fptp_winner].general_mandates += state_arr[i].electoral_votes;
            }
        }
        char winner[MAX_NAME_LENGTH];
        int winner_mandates = candidate_arr[0].general_mandates > candidate_arr[1].general_mandates ? candidate_arr[0].general_mandates : candidate_arr[1].general_mandates;
        int winner_index = candidate_arr[0].general_mandates > candidate_arr[1].general_mandates ? 0 : 1;
        strcpy(winner, candidate_arr[0].general_mandates > candidate_arr[1].general_mandates ? candidate_arr[0].name : candidate_arr[1].name);
        printf("\n%s wins with %d mandates \n", winner, winner_mandates);
        double satisfaction = calc_satisfaction(winner_index, voter_arr, POPULATION);
        printf("Satisfaction: %.2lf out of 100", satisfaction);
    }

    if(electoral_choice == 2) {
        printf("Calculating voters");
        int fptp_winner = first_past_the_post(voter_arr, POPULATION, 0, &state_arr[0], candidates);
        printf("\n%s wins \n", candidate_arr[fptp_winner].name);
        for(int i = 0; i < candidates; i++) {
            printf("Candidate %s has %d votes\n", candidate_arr[i].name, state_arr[0].candidate_votes_fptp[i]);
            printf("It would be %d mandates\n", (int)(((long long)state_arr[0].candidate_votes_fptp[i] * 538) / POPULATION));
        }

    }

    if(electoral_choice == 1 && voting_system_choice == 2) {
        for(int i = 0; i < STATES; i++) {
            printf("Calculating winners for %s...\n", state_arr[i].name);

            // FIRST PAST THE POST
            int fptp_winner = first_past_the_post(voter_arr, state_arr[i].population, start_index[i], &state_arr[i], candidates);
            candidate_arr[fptp_winner].fptp_mandates += state_arr[i].electoral_votes;

            // RANKED VOTING
            int rcv_winner = ranked_choice_voting(state_arr[i].population, voter_arr, candidate_arr, start_index[i], &state_arr[i], candidates);
            candidate_arr[rcv_winner].rcv_mandates += state_arr[i].electoral_votes;

            // RATED VOTING
            int rated_winner = voting_rated(voter_arr, state_arr[i].population, start_index[i], &state_arr[i], candidates);
            candidate_arr[rated_winner].rated_mandates += state_arr[i].electoral_votes;

            // STAR VOTING
            int star_winner = voting_star(state_arr[i].population, voter_arr, candidate_arr, start_index[i], &state_arr[i], candidates);
            candidate_arr[star_winner].star_mandates += state_arr[i].electoral_votes;
        }
        char voting_system[][MAX_NAME_LENGTH] = {"FPTP", "RANKED", "RATED", "STAR"};
        int previus_winner[candidates];
        for (int i = 0; i < candidates; i++) {
            previus_winner[i] = 0;
        }
        for(int i = 0; i < 4; i++) {
            int new_winner = print_winners(candidate_arr, candidates, i);
            printf("Winner of %s is %s\n", voting_system[i], candidate_arr[new_winner].name);
            if (!previus_winner[new_winner]) {
                double satisfaction = calc_satisfaction(new_winner, voter_arr, POPULATION);
                printf("Satisfaction: %.2lf\n", satisfaction);
                previus_winner[new_winner] = satisfaction;
            }else {
                printf("%s previuosly calculated to %.2lf\n", candidate_arr[new_winner].name, previus_winner[new_winner]);
            }
        }
        for (int i = 0; i < candidates; i++) {
            printf("\n%s (%d) got \n", candidate_arr[i].name, i + 1);
            printf("FPTP mandates: %d\n", candidate_arr[i].fptp_mandates);
            printf("STAR mandates: %d\n", candidate_arr[i].star_mandates);
            printf("RATED mandates: %d\n", candidate_arr[i].rated_mandates);
            printf("RANKED mandates: %d\n", candidate_arr[i].rcv_mandates);
        }
        //determine_fairness();

        prompt_stats(state_arr, calc_percent, candidate_arr, candidates);
    }
    free(voter_arr);
    free(state_arr);
    free(candidate_arr);

    return 0;
}