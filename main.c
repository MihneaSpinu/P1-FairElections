#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "functions.h"

int main() {

    srand(time(NULL));

    int simulation_choice,
        electoral_choice,
        candidate_choice,
        voting_system_choice,
        candidates = 0;

    int værdi[5];
    int fordeling[5];
    int mandates[MAX_CANDIDATES];
    char candidate_name[5][MAX_NAME_LENGTH];
    double calc_percent[STATES][4][5] = {0};

    // SETTINGS
    scan_election_settings(&simulation_choice, &electoral_choice, &candidate_choice,
                           &voting_system_choice, &candidates, candidate_name,
                           værdi, fordeling);

    // MALLOC ARRAYS
    candidate *candidate_arr = malloc(sizeof(candidate) * candidates);
    voter *voter_arr = malloc(sizeof(voter) * POPULATION);
    state *state_arr = malloc(sizeof(state) * STATES);
    if(candidate_arr == NULL || voter_arr == NULL || state_arr == NULL) {
        printf("Error allocating memory\n");
        exit(EXIT_FAILURE);
    }
    // INIT CANDIDATES
    printf("\nInitializing the candidates...\n\n");
    init_candidates(candidate_arr, candidates, candidate_name, værdi, fordeling);

    // INIT STATES
    printf("Initializing the states...\n\n");
    init_state(state_arr, candidates);

    // START INDEX - inddeler vælgerne på de korrekte pladser i voter arrayet
    int cumulative_state_population = 0;
    int start_index[STATES];
    init_index(cumulative_state_population, start_index, state_arr);

    // INIT VOTERS
    for (int i = 0; i < STATES; i++) {
        printf("Generating voters for %s...\n", state_arr[i].name);
        init_voters(voter_arr, state_arr[i], start_index[i], i, calc_percent);
    }

    // GET DISTANCE
    printf("\nCalculating voter preference...\n");
    get_distance(voter_arr, candidate_arr, POPULATION, candidates);
    printf("\n");






    // CURRENT US SYSTEM
    if(voting_system_choice == 1) {
        for(int i = 0; i < STATES; i++) {
            printf("Finding winner in %s...\n", state_arr[i].name);
            if(i == 1 || i == 19) { // Alaska & MAINE
                int rcv_winner = ranked_choice_voting(state_arr[i].population, voter_arr, candidate_arr, start_index[i], &state_arr[i], candidates);
                candidate_arr[rcv_winner].general_mandates += state_arr[i].electoral_votes;
            } else {
                int fptp_winner = first_past_the_post(voter_arr, state_arr[i].population, start_index[i], &state_arr[i], candidates);
                candidate_arr[fptp_winner].general_mandates += state_arr[i].electoral_votes;
            }
        }

        for(int i = 0; i < candidates; i++) {
            mandates[i] = candidate_arr[i].general_mandates;
        }
        print_winner(candidates, "the election", mandates, candidate_arr, "mandates", electoral_choice);

        /*
        int winner_index = candidate_arr[0].general_mandates > candidate_arr[1].general_mandates ? 0 : 1;
        double satisfaction = calc_satisfaction(winner_index, voter_arr, POPULATION);
        printf("Satisfaction: %.2lf out of 100", satisfaction);
        */

    }








    //
    if(electoral_choice == 1 && voting_system_choice == 2) {
        for(int i = 0; i < STATES; i++) {
            printf("Finding winners for %s...\n", state_arr[i].name);

            // FPTP FPTP FPTP FPTP FPTP FPTP FPTP FPTP FPTP FPTP FPTP FPTP FPTP FPTP FPTP FPTP FPTP FPTP FPTP FPTP FPTP
            int fptp_winner = first_past_the_post(voter_arr, state_arr[i].population, start_index[i], &state_arr[i], candidates);
            candidate_arr[fptp_winner].fptp_mandates += state_arr[i].electoral_votes;

            // RCV RCV RCV RCV RCV RCV RCV RCV RCV RCV RCV RCV RCV RCV RCV RCV RCV RCV RCV RCV RCV RCV RCV RCV RCV RCV
            int rcv_winner = ranked_choice_voting(state_arr[i].population, voter_arr, candidate_arr, start_index[i], &state_arr[i], candidates);
            candidate_arr[rcv_winner].rcv_mandates += state_arr[i].electoral_votes;

            // RATED RATED RATED RATED RATED RATED RATED RATED RATED RATED RATED RATED RATED RATED RATED RATED RATED
            int rated_winner = voting_rated(voter_arr, state_arr[i].population, start_index[i], &state_arr[i], candidates);
            candidate_arr[rated_winner].rated_mandates += state_arr[i].electoral_votes;

            // STAR STAR STAR STAR STAR STAR STAR STAR STAR STAR STAR STAR STAR STAR STAR STAR STAR STAR STAR STAR STAR
            int star_winner = voting_star(state_arr[i].population, voter_arr, candidate_arr, start_index[i], &state_arr[i], candidates);
            candidate_arr[star_winner].star_mandates += state_arr[i].electoral_votes;
        }

        /*
        char voting_system[][MAX_NAME_LENGTH] = {"FPTP", "RANKED", "RATED", "STAR"};
        int previous_winner[candidates];
        for (int i = 0; i < candidates; i++) {
            previous_winner[i] = 0;
        }
        for(int i = 0; i < 4; i++) {
            int new_winner = print_winners(candidate_arr, candidates, i);
            printf("Winner of %s is %s\n", voting_system[i], candidate_arr[new_winner].name);
            if (!previous_winner[new_winner]) {
                double satisfaction = calc_satisfaction(new_winner, voter_arr, POPULATION);
                printf("Satisfaction: %.2lf\n", satisfaction);
                previous_winner[new_winner] = satisfaction;
            }else {
                printf("%s previuosly calculated to %.2lf\n", candidate_arr[new_winner].name, previous_winner[new_winner]);
            }
        }
        */
        for(int i = 0; i < candidates; i++) {
            mandates[i] = candidate_arr[i].fptp_mandates;
        }
        print_winner(candidates, "first past the post", mandates, candidate_arr, "mandates", electoral_choice);
        for(int i = 0; i < candidates; i++) {
            mandates[i] = candidate_arr[i].rcv_mandates;
        }
        print_winner(candidates, "ranked choice voting", mandates, candidate_arr, "mandates", electoral_choice);
        for(int i = 0; i < candidates; i++) {
            mandates[i] = candidate_arr[i].rated_mandates;
        }
        print_winner(candidates, "rated voting", mandates, candidate_arr, "mandates", electoral_choice);
        for(int i = 0; i < candidates; i++) {
            mandates[i] = candidate_arr[i].star_mandates;
        }
        print_winner(candidates, "star voting", mandates, candidate_arr, "mandates", electoral_choice);

    //determine_fairness();

    }








    // NATION WIDE VOTE
    if(electoral_choice == 2) {
        printf("Finding winners...\n");
        // FPTP FPTP FPTP FPTP FPTP FPTP FPTP FPTP FPTP FPTP FPTP FPTP FPTP FPTP FPTP FPTP FPTP FPTP FPTP FPTP FPTP
        first_past_the_post(voter_arr, POPULATION, 0, &state_arr[0], candidates);
        for(int i = 0; i < candidates; i++) {
            mandates[i] = state_arr[0].candidate_votes_fptp[i];
        }
        print_winner(candidates, "first past the post", mandates, candidate_arr, "votes", electoral_choice);

        // RCV RCV RCV RCV RCV RCV RCV RCV RCV RCV RCV RCV RCV RCV RCV RCV RCV RCV RCV RCV RCV RCV RCV RCV RCV RCV RCV
        ranked_choice_voting(POPULATION, voter_arr, candidate_arr, 0, &state_arr[0], candidates);
        for(int i = 0; i < candidates; i++) {
            mandates[i] = state_arr[0].candidate_votes_rcv[i];
        }
        print_winner(candidates, "ranked choice voting", mandates, candidate_arr, "points", electoral_choice);

        // RATED RATED RATED RATED RATED RATED RATED RATED RATED RATED RATED RATED RATED RATED RATED RATED RATED RATED
        voting_rated(voter_arr, POPULATION, 0, &state_arr[0], candidates);
        for(int i = 0; i < candidates; i++) {
            mandates[i] = state_arr[0].candidate_votes_rated[i];
        }
        print_winner(candidates, "rated voting", mandates, candidate_arr, "points", electoral_choice);

        // STAR STAR STAR STAR STAR STAR STAR STAR STAR STAR STAR STAR STAR STAR STAR STAR STAR STAR STAR STAR STAR
        voting_star(POPULATION, voter_arr, candidate_arr, 0, &state_arr[0], candidates);
        for(int i = 0; i < candidates; i++) {
            mandates[i] = state_arr[0].candidate_votes_star[i];
        }
        print_winner(candidates, "star voting", mandates, candidate_arr, "votes", electoral_choice);
    }





    free(voter_arr);
    free(state_arr);
    free(candidate_arr);

    return 0;
}