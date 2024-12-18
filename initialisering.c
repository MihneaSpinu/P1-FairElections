#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"


// Initializes the candidates
void init_candidates(candidate candidate_arr[], int num_of_candidates, char candidate_names[][MAX_NAME_LENGTH],
                     int social_p[], int economic_p[]) {

    for(int i = 0; i < num_of_candidates; i++) {
        strcpy(candidate_arr[i].name, candidate_names[i]);
        candidate_arr[i].social_policy_c = social_p[i];
        candidate_arr[i].economic_policy_c = economic_p[i];
        candidate_arr[i].votes_fptp = 0;
        candidate_arr[i].votes_star = 0;
        candidate_arr[i].votes_rated = 0;
        candidate_arr[i].votes_rcv = 0;
        candidate_arr[i].star_mandates = 0;
        candidate_arr[i].rcv_mandates = 0;
        candidate_arr[i].fptp_mandates = 0;
        candidate_arr[i].rated_mandates = 0;
        candidate_arr[i].general_mandates = 0;
    }
}


// Initializes the states
void init_state(state state_arr[], int num_of_candidates) {

    FILE* f = fopen("state_data.txt", "r");
    if(f == NULL) {
        printf("Error: couldn't open file 'state_data.txt'");
        exit(EXIT_FAILURE);
    }

    for(int i = 0; i < STATES; i++) {
        for(int j = 0; j < num_of_candidates; j++) {
            state_arr[i].candidate_votes_fptp[j] = 0;
            state_arr[i].candidate_votes_star[j] = 0;
            state_arr[i].candidate_votes_rated[j] = 0;
            state_arr[i].candidate_votes_rcv[j] = 0;
        }
        fscanf(f, "%[^,],%d,%d,", state_arr[i].name, &state_arr[i].population, &state_arr[i].electoral_votes);

        for(int j = 0; j < RACES; j++) {
            fscanf(f, "%d,", &state_arr[i].race_distribution[j]);
        }
        for(int j = 0; j < GENDERS; j++) {
            fscanf(f, "%d,", &state_arr[i].gender_distribution[j]);
        }
        for(int j = 0; j < AGES; j++) {
            fscanf(f, "%d,", &state_arr[i].age_distribution[j]);
        }
        for(int j = 0; j < INCOME; j++) {
            fscanf(f, "%d,", &state_arr[i].income_distribution[j]);
        }
        fscanf(f, "\n");
    }
    fclose(f);
}


// Initializes the correct start index for the voters
void init_index(int cumulative_state_population, int start_index[], state state_arr[]) {

    for(int i = 0; i < STATES; i++) {
        start_index[i] = cumulative_state_population;
        cumulative_state_population += state_arr[i].population;
    }
}


// Initializes the voters
void init_voters(voter voter_arr[], state current_state, int start_index, int state, float calc_percent[][4][5]) {

    int social_policy[4][5] = {
        {30, -30, -20, -20, -10},// RACE
        {30, -30},               // GENDER
        {-30, 10, 40},           // INCOME
        {-30, -20, 0, 10, 40}};  // AGE

    int economic_policy[4][5] = {
        {10, -20, -10, -10, 0},  // RACE
        {30, -30},               // GENDER
        {-20, 0, 40},            // INCOME
        {-30, -20, 0, 10, 40}};  // AGE

    for(int i = start_index; i < current_state.population + start_index; i++) {
        voter_arr[i].economic_policy_v = 0;
        voter_arr[i].social_policy_v = 0;
    }

    init_attributes(current_state.race_distribution, RACES, race, start_index, state, voter_arr,
                    current_state.population, calc_percent, social_policy, economic_policy);

    init_attributes(current_state.gender_distribution, GENDERS, gender, start_index, state, voter_arr,
                    current_state.population, calc_percent, social_policy, economic_policy);

    init_attributes(current_state.income_distribution, INCOME, income, start_index, state, voter_arr,
                    current_state.population, calc_percent, social_policy, economic_policy);

    init_attributes(current_state.age_distribution, AGES, age, start_index, state, voter_arr,
                    current_state.population, calc_percent, social_policy, economic_policy);
}


// Initializes the voters attributes
void init_attributes(int distribution[], int attribute_amount, int category, int start_index, int state,
                     voter voter_arr[], int population, float calc_percent[][4][5],
                     int economic_policy[][5], int social_policy[][5]) {

    for(int i = start_index; i < population + start_index; i++) {
        int random = rand() % 1000 + 1;
        for(int attribute = 0; attribute < attribute_amount; attribute++) {
            if(random <= distribution[attribute]) {

                if(category == race)        voter_arr[i].race_v = attribute;
                else if(category == gender) voter_arr[i].gender_v = attribute;
                else if(category == income) voter_arr[i].income_v = attribute;
                else if(category == age)    voter_arr[i].age_v = attribute;

                voter_arr[i].economic_policy_v += economic_policy[category][attribute] + variance();
                voter_arr[i].social_policy_v += social_policy[category][attribute] + variance();
                calc_percent[state][category][attribute]++;
                break;
            }
        }
    }
}