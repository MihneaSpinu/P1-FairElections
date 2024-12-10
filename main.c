#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "functions.h"

int main() {

    srand(time(NULL));
    double calc_percent[STATES][4][5] = {0};

    int candidates;
    int simulation_choice;
    char electoral_choice[2];
    char candidate_name[5][MAX_NAME_LENGTH];
    char name[MAX_NAME_LENGTH];
    int værdi[5];
    int fordeling[5];

    printf("1) Simulate 2024 election\n");
    printf("2) Use preset candidates\n");
    printf("3) Add your own candidates\n");
    scanf("%d", &simulation_choice);
    printf("%d\n", simulation_choice);

    if(simulation_choice == 1) {
        candidates = 2;
        strcpy(candidate_name[0], "Donald Trump");
        strcpy(candidate_name[1], "Kamala Harris");
        værdi[0] = 25;
        værdi[1] = 30;
        fordeling[0] = 25;
        fordeling[1] = 20;
    } else if(simulation_choice == 2) {
        candidates = 5;
        strcpy(candidate_name[0], "Donald Trump");
        strcpy(candidate_name[1], "Kamala Harris");
        strcpy(candidate_name[2], "Robert F. Kennedy");
        strcpy(candidate_name[3], "Elon Musk");
        strcpy(candidate_name[4], "Kanye West");
        værdi[0] = 25;
        værdi[1] = 30;
        værdi[2] = 0;
        værdi[3] = 50;
        værdi[4] = -20;
        fordeling[0] = 25;
        fordeling[1] = 20;
        fordeling[2] = 0;
        fordeling[3] = 50;
        fordeling[4] = -20;
    } else if(simulation_choice == 3) {

        for(candidates = 0; candidates < 5; candidates++) {
            printf("Choose candidate name and position on political compass: (-100,100)\n");
            scanf("%s", &name);
            if(strcmp(name, "exit") == 0) {
                break;
            }
            strcpy(candidate_name[candidates], name);
            scanf("%d %d", &værdi[candidates], &fordeling[candidates]);
            if(værdi[candidates] < -100 || værdi[candidates] > 100 || fordeling[candidates] > 100 || fordeling[candidates] < -100) {
                printf("Values out of range (-100,100)");
                exit(EXIT_FAILURE);
            }
        }
        if(candidates < 2) {
            printf("There has to be at least 2 candidates");
            exit(EXIT_FAILURE);
        }
    } else {
        printf("Invalid input");
        exit(EXIT_FAILURE);
    }

    printf("Simulate with electoral college? (y/n)\n");
    scanf("%s", &electoral_choice);
    printf("%d\n", simulation_choice);

    candidate *candidate_arr = malloc(sizeof(candidate) * candidates); // * candidates
    voter *voter_arr = malloc(sizeof(voter) * POPULATION);
    state *state_arr = malloc(sizeof(state) * STATES);
    if(candidate_arr == NULL || voter_arr == NULL || state_arr == NULL) {
        printf("Error allocating memory\n");
        exit(EXIT_FAILURE);
    }

    printf("Initializing the states...\n");
    init_state(state_arr, candidates);

    // START INDEX - inddeler vælgerne på de korrekte pladser i voter arrayet
    int cumulative_state_population = 0;
    int start_index[STATES];
    init_index(cumulative_state_population, start_index, state_arr);

    printf("\nInitializing the candidates...\n\n");
    init_candidates(candidate_arr, candidates, candidate_name, værdi, fordeling);

    for (int i = 0; i < STATES; i++) {
        printf("Generating voters for %s...\n", state_arr[i].name);
        init_voters(voter_arr, state_arr[i], start_index[i], i, calc_percent);
    }

    printf("\nCalculating voter preference...\n");
    get_distance(voter_arr, candidate_arr, POPULATION, candidates);
    printf("\n");

    if(simulation_choice == 1 && strcmp(electoral_choice, "y") == 0) {
        for(int i = 0; i < STATES; i++) {
            printf("Calculating winners for %s...\n", state_arr[i].name);
            if(i == 19 || i == 27) { // MAINE & NEBRASKA
                int rcv_winner = ranked_choice_voting(state_arr[i].population, voter_arr, candidate_arr, start_index[i], &state_arr[i], candidates);
                candidate_arr[rcv_winner].total_mandates += state_arr[i].electoral_votes;
            } else {
                int fptp_winner = first_past_the_post(voter_arr, state_arr[i].population, start_index[i], &state_arr[i], candidates);
                candidate_arr[fptp_winner].total_mandates += state_arr[i].electoral_votes;
            }
        }
        char winner[MAX_NAME_LENGTH];
        strcpy(winner, candidate_arr[0].total_mandates > candidate_arr[1].total_mandates ? candidate_arr[0].name : candidate_arr[1].name);
        printf("\n%s wins with %d mandates \n", winner, candidate_arr[0].total_mandates > candidate_arr[1].total_mandates ? candidate_arr[0].total_mandates : candidate_arr[1].total_mandates);
    }

    if(simulation_choice == 1 && strcmp(electoral_choice, "n") == 0) {
        printf("Calculating voters");
        int fptp_winner = first_past_the_post(voter_arr, POPULATION, 0, &state_arr[0], candidates);
        printf("\n%s wins \n", candidate_arr[fptp_winner].name);
        for(int i = 0; i < candidates; i++) {
            printf("Candidate %s has %d votes\n", candidate_arr[i].name, state_arr[0].candidate_votes_fptp[i]);
            printf("It would be %d mandates", (int)(((long long)state_arr[0].candidate_votes_fptp[i] * 538) / POPULATION));
        }

    }

    if((simulation_choice == 2 || simulation_choice == 3) && strcmp(electoral_choice, "y") == 0) {
        for(int i = 0; i < STATES; i++) {
            printf("Calculating winners for %s...\n", state_arr[i].name);

            // FIRST PAST THE POST
            int fptp_winner = first_past_the_post(voter_arr, state_arr[i].population, start_index[i], &state_arr[i], candidates);
            candidate_arr[fptp_winner].fptp_mandates += state_arr[i].electoral_votes;
            printf("Found fptp winner\n");

            // RANKED VOTING
            int rcv_winner = ranked_choice_voting(state_arr[i].population, voter_arr, candidate_arr, start_index[i], &state_arr[i], candidates);
            candidate_arr[rcv_winner].rcv_mandates += state_arr[i].electoral_votes;
            printf("Found rcv winner\n");

            // RATED VOTING
            int rated_winner = voting_rated(voter_arr, state_arr[i].population, start_index[i], &state_arr[i], candidates);
            candidate_arr[rated_winner].rated_mandates += state_arr[i].electoral_votes;
            printf("Found rated winner\n");

            // STAR VOTING
            int star_winner = voting_star(state_arr[i].population, voter_arr, candidate_arr, start_index[i], &state_arr[i], candidates);
            candidate_arr[star_winner].star_mandates += state_arr[i].electoral_votes;
            printf("Found star winner\n");
        }

        for (int i = 0; i < candidates; i++) {
            printf("\n%s (%d) got \n", candidate_arr[i].name, i + 1);
            printf("FPTP mandates: %d\n", candidate_arr[i].fptp_mandates);
            printf("STAR mandates: %d\n", candidate_arr[i].star_mandates);
            printf("RATED mandates: %d\n", candidate_arr[i].rated_mandates);
            printf("RANKED mandates: %d\n", candidate_arr[i].rcv_mandates);
        }

        //print_winners();
        //determine_fairness();

        prompt_stats(state_arr, calc_percent, candidate_arr, candidates);
    }
    free(voter_arr);
    free(state_arr);
    free(candidate_arr);

    return 0;
}