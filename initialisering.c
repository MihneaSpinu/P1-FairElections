#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"

// funktion til at initialisere staterne
void init_state(state state_arr[], int num_of_candidate) {
    FILE* f = fopen("test_state_data.txt", "r");
    if (f == NULL) {
        printf("Error: couldn't open file 'state_data.txt'");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < STATES; i++) {
        for(int j = 0; j < num_of_candidate; j++) {
            state_arr[i].candidate_votes_fptp[j] = 0;
            state_arr[i].candidate_votes_star[j] = 0;
            state_arr[i].candidate_votes_rated[j] = 0;
            state_arr[i].candidate_votes_ranked[j] = 0;
        }
        fscanf(f, "%[^,],%d,%d,", state_arr[i].name, &state_arr[i].population,
                                           &state_arr[i].electoral_votes);
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

// funktion til at initialisere kandidaterne
void init_candidates(candidate candidate_arr[], int num_of_candidates, char candidate_names[][MAX_NAME_LENGTH], int værdi[], int fordeling[]) {
    //
    // const char *names[] = {"Donald Trump", "Kamala Harris"};
    //
    // int værdipolitik_c[] = {25, 30};
    // int fordelingspolitik_c[] = {25, 20};

    for (int i = 0; i < num_of_candidates; i++) {
        strcpy(candidate_arr[i].name, candidate_names[i]);
        candidate_arr[i].værdipolitik_c = værdi[i];
        candidate_arr[i].fordelingspolitik_c = fordeling[i];
        candidate_arr[i].votes_fptp = 0;
        candidate_arr[i].votes_star = 0;
        candidate_arr[i].votes_rated = 0;
        candidate_arr[i].votes_rcv = 0;
        candidate_arr[i].star_mandates = 0;
        candidate_arr[i].rcv_mandates = 0;
        candidate_arr[i].fptp_mandates = 0;
        candidate_arr[i].rated_mandates = 0;
        candidate_arr[i].total_mandates = 0;
    }
}

// funktion til at initialisere vælgerne
void init_voters(voter voter_arr[], state current_state, int start_index, int state, double calc_percent[][4][5]) {

    int fordelingspolitik[4][5] = {
        {50, -50, -50, -50, -50}, // RACE
        {30, -30},               // GENDER
        {-40, 20, 40},           // INCOME
        {-50, -25, 20, 30, 50}}; // AGE

    int værdipolitik[4][5] = {
        {50, -50, -50, -50, -50}, // RACE
        {30, -30},               // GENDER
        {-40, 20, 40},           // INCOME
        {-50, -25, 20, 30, 50}}; // AGE

    for(int i = start_index; i < current_state.population + start_index; i++) {
        voter_arr[i].fordelingspolitik_v = 0;
        voter_arr[i].værdipolitik_v = 0;
    }

    init_attributes(current_state.race_distribution, RACES, race, start_index, state, voter_arr,
                    current_state.population, calc_percent, fordelingspolitik, værdipolitik);

    init_attributes(current_state.gender_distribution, GENDERS, gender, start_index, state, voter_arr,
                    current_state.population, calc_percent, fordelingspolitik, værdipolitik);

    init_attributes(current_state.income_distribution, INCOME, income, start_index, state, voter_arr,
                    current_state.population, calc_percent, fordelingspolitik, værdipolitik);

    init_attributes(current_state.age_distribution, AGES, age, start_index, state, voter_arr,
                    current_state.population, calc_percent, fordelingspolitik, værdipolitik);
}

// funktion til at initialisere attributterne for vælgerne
void init_attributes(int distribution[], int attribute_amount, int category, int start_index, int state,
                     voter voter_arr[], int state_population, double calc_percent[][4][5],
                     int fordelingspolitik[][5], int værdipolitik[][5]) {

    for (int i = start_index; i < state_population + start_index; i++) {
        int random = rand() % 1000 + 1;
        for (int attribute = 0; attribute < attribute_amount; attribute++) {
            if (random <= distribution[attribute]) {
                if(category == race) {
                    voter_arr[i].race_v = attribute;
                } else if(category == gender) {
                    voter_arr[i].gender_v = attribute;
                } else if(category == income) {
                    voter_arr[i].income_v = attribute;
                } else {
                    voter_arr[i].age_v = attribute;
                }

                voter_arr[i].fordelingspolitik_v += fordelingspolitik[category][attribute] + variance();
                voter_arr[i].værdipolitik_v += værdipolitik[category][attribute] + variance();
                calc_percent[state][category][attribute]++;
                break;
            }
        }
    }
}

void init_index(int cumulative_state_population, int start_index[], state state_arr[]) {

    for(int i = 0; i < STATES; i++) {
        start_index[i] = cumulative_state_population;
        cumulative_state_population += state_arr[i].population;
    }
}
/*
void init_congressional(state congressional_arr[], int num_of_candidate) {
    FILE* f = fopen("congressional.txt", "r");
    if (f == NULL) {
        printf("Error: couldn't open file 'congressional.txt'");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < CONGRESSIONAL_DISTRICTS; i++) {
        for(int j = 0; j < num_of_candidate; j++) {
            congressional_arr[i].candidate_votes_fptp[j] = 0;
            congressional_arr[i].candidate_votes_star[j] = 0;
            congressional_arr[i].candidate_votes_rated[j] = 0;
            congressional_arr[i].candidate_votes_ranked[j] = 0;
        }
        fscanf(f, "%[^,],%d,%d,", congressional_arr[i].name, &congressional_arr[i].population,
                                           &congressional_arr[i].electoral_votes);
        for(int j = 0; j < RACES; j++) {
            fscanf(f, "%d,", &congressional_arr[i].race_distribution[j]);
        }
        for(int j = 0; j < GENDERS; j++) {
            fscanf(f, "%d,", &congressional_arr[i].gender_distribution[j]);
        }
        for(int j = 0; j < AGES; j++) {
            fscanf(f, "%d,", &congressional_arr[i].age_distribution[j]);
        }
        for(int j = 0; j < INCOME; j++) {
            fscanf(f, "%d,", &congressional_arr[i].income_distribution[j]);
        }
        fscanf(f, "\n");
    }

    fclose(f);
}*/