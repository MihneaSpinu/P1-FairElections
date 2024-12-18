#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "functions.h"

int main() {

    srand(time(NULL));

    int simulation_choice,
        electoral_choice,
        candidate_choice,
        voting_system_choice,
        num_of_candidates;

    int social_p[MAX_CANDIDATES],
        economic_p[MAX_CANDIDATES],
        mandates[MAX_CANDIDATES];

    char candidate_name[5][MAX_NAME_LENGTH];
    float calc_percent[STATES][4][5] = {0};

    // SETTINGS
    scan_election_settings(&simulation_choice, &electoral_choice, &candidate_choice,
                           &voting_system_choice, &num_of_candidates, candidate_name,
                           social_p, economic_p);

    // MALLOC ARRAYS
    candidate *candidate_arr = malloc(sizeof(candidate) * num_of_candidates);
    check_memory_allocation((int*)candidate_arr);

    voter *voter_arr = malloc(sizeof(voter) * POPULATION);
    check_memory_allocation((int*)voter_arr);

    state *state_arr = malloc(sizeof(state) * STATES);
    check_memory_allocation((int*)state_arr);

    // INIT CANDIDATES
    printf("\nInitializing the candidates...\n\n");
    init_candidates(candidate_arr, num_of_candidates, candidate_name, social_p, economic_p);

    // INIT STATES
    printf("Initializing the states...\n\n");
    init_state(state_arr, num_of_candidates);

    // START INDEX
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
    get_distance(voter_arr, candidate_arr, POPULATION, num_of_candidates);
    printf("\nCalculating voter ratings...\n");
    get_ratings(voter_arr, num_of_candidates, POPULATION);
    printf("\n");

    // CURRENT US SYSTEM AS IS
    if(voting_system_choice == 1) {
        for(int i = 0; i < STATES; i++) {
            printf("Finding winner in %s...\n", state_arr[i].name);
            if(i == 1 || i == 19) { // ALASKA & MAINE
                int rcv_winner = ranked_choice_voting(state_arr[i].population, voter_arr, candidate_arr,
                                                      start_index[i], &state_arr[i], num_of_candidates);
                candidate_arr[rcv_winner].general_mandates += state_arr[i].electoral_votes;
            } else {
                int fptp_winner = first_past_the_post(voter_arr, state_arr[i].population, start_index[i],
                                                      &state_arr[i], num_of_candidates);
                candidate_arr[fptp_winner].general_mandates += state_arr[i].electoral_votes;
            }
        }

        for(int i = 0; i < num_of_candidates; i++) {
            mandates[i] = candidate_arr[i].general_mandates;
        }
        print_winner(num_of_candidates, "the election", mandates, candidate_arr, "mandates", electoral_choice);
    }

    // ELECTORAL COLLEGE
    if(electoral_choice == 1 && voting_system_choice == 2) {
        for(int i = 0; i < STATES; i++) {
            printf("Finding winners in %s...\n", state_arr[i].name);

            // First Past The Post
            int fptp_winner = first_past_the_post(voter_arr, state_arr[i].population, start_index[i],
                                                  &state_arr[i], num_of_candidates);
            candidate_arr[fptp_winner].fptp_mandates += state_arr[i].electoral_votes;

            // Ranked Choice
            int rcv_winner = ranked_choice_voting(state_arr[i].population, voter_arr, candidate_arr,
                                                  start_index[i], &state_arr[i], num_of_candidates);
            candidate_arr[rcv_winner].rcv_mandates += state_arr[i].electoral_votes;

            // Rated Choice
            int rated_winner = voting_rated(voter_arr, state_arr[i].population, start_index[i],
                                            &state_arr[i], num_of_candidates);
            candidate_arr[rated_winner].rated_mandates += state_arr[i].electoral_votes;

            // STAR Voting
            int star_winner = voting_star(state_arr[i].population, voter_arr, candidate_arr,
                                          start_index[i], &state_arr[i], num_of_candidates);
            candidate_arr[star_winner].star_mandates += state_arr[i].electoral_votes;
        }

        int winner_index;
        for(int i = 0; i < num_of_candidates; i++) {
            mandates[i] = candidate_arr[i].fptp_mandates;
        }
        winner_index = print_winner(num_of_candidates, "first past the post", mandates,
                                    candidate_arr, "mandates", electoral_choice);
        printf("Satisfaction: %.2f out of 100\n",calc_satisfaction(winner_index, voter_arr, POPULATION));

        for(int i = 0; i < num_of_candidates; i++) {
            mandates[i] = candidate_arr[i].rcv_mandates;
        }
        winner_index = print_winner(num_of_candidates, "ranked choice voting", mandates,
                                    candidate_arr, "mandates", electoral_choice);
        printf("Satisfaction: %.2f out of 100\n",calc_satisfaction(winner_index, voter_arr, POPULATION));

        for(int i = 0; i < num_of_candidates; i++) {
            mandates[i] = candidate_arr[i].rated_mandates;
        }
        winner_index = print_winner(num_of_candidates, "rated voting", mandates,
                                    candidate_arr, "mandates", electoral_choice);
        printf("Satisfaction: %.2f out of 100\n",calc_satisfaction(winner_index, voter_arr, POPULATION));

        for(int i = 0; i < num_of_candidates; i++) {
            mandates[i] = candidate_arr[i].star_mandates;
        }
        winner_index = print_winner(num_of_candidates, "star voting", mandates,
                                    candidate_arr, "mandates", electoral_choice);
        printf("Satisfaction: %.2f out of 100\n",calc_satisfaction(winner_index, voter_arr, POPULATION));

        int condorcet_win_index = condorcet_winner(POPULATION, num_of_candidates, voter_arr);
        if (condorcet_win_index == -1) {
            printf("\nThere is no condorcet winner\n");
        }else {
            printf("\nThe condorcet winner is %s\n", candidate_arr[condorcet_win_index].name);
        }

    }

    // NATION WIDE VOTE
    if(electoral_choice == 2) {
        int winner_index;
        printf("Finding winners...\n");

        // FIRST PAST THE POST
        first_past_the_post(voter_arr, POPULATION, 0, &state_arr[0], num_of_candidates);
        for(int i = 0; i < num_of_candidates; i++) {
            mandates[i] = state_arr[0].candidate_votes_fptp[i];
        }
        winner_index = print_winner(num_of_candidates, "first past the post", mandates,
                                    candidate_arr, "votes", electoral_choice);
        printf("Satisfaction: %.2f out of 100\n",calc_satisfaction(winner_index, voter_arr, POPULATION));

        // RANKED CHOICE VOTING
        ranked_choice_voting(POPULATION, voter_arr, candidate_arr, 0, &state_arr[0], num_of_candidates);
        for(int i = 0; i < num_of_candidates; i++) {
            mandates[i] = state_arr[0].candidate_votes_rcv[i];
        }
        winner_index = print_winner(num_of_candidates, "ranked choice voting", mandates,
                                    candidate_arr, "ranked votes", electoral_choice);
        printf("Satisfaction: %.2f out of 100\n",calc_satisfaction(winner_index, voter_arr, POPULATION));

        // RATED VOTING
        voting_rated(voter_arr, POPULATION, 0, &state_arr[0], num_of_candidates);
        for(int i = 0; i < num_of_candidates; i++) {
            mandates[i] = state_arr[0].candidate_votes_rated[i];
        }
        winner_index = print_winner(num_of_candidates, "rated voting", mandates,
                                    candidate_arr, "points", electoral_choice);
        printf("Satisfaction: %.2f out of 100\n",calc_satisfaction(winner_index, voter_arr, POPULATION));

        // STAR VOTING
        voting_star(POPULATION, voter_arr, candidate_arr, 0, &state_arr[0], num_of_candidates);
        for(int i = 0; i < num_of_candidates; i++) {
            mandates[i] = state_arr[0].candidate_votes_star[i];
        }
        winner_index = print_winner(num_of_candidates, "star voting", mandates,
                                    candidate_arr, "votes", electoral_choice);
        printf("Satisfaction: %.2f out of 100\n",calc_satisfaction(winner_index, voter_arr, POPULATION));

        // CONDORCET
        int condorcet_winner_index = condorcet_winner(POPULATION, num_of_candidates, voter_arr);
        if (condorcet_winner_index == -1) {
            printf("There is no condorcet winner\n");
        }else {
            printf("The condorcet winner is %s\n", candidate_arr[condorcet_winner_index].name);
        }
    }

    free(voter_arr);

    prompt_stats(state_arr, calc_percent, candidate_arr, num_of_candidates);

    free(state_arr);
    free(candidate_arr);

    return 0;
}