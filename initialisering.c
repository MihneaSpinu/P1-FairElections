#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#include "functions.h"

// funktion til at initialisere staterne
void init_state(state state_arr[]) {
    FILE* f = fopen("state_data.txt", "r");
    if (f == NULL) {
        printf("Error: couldn't open file 'state_data.txt'");
        exit(EXIT_FAILURE);
    }

    for (int s = 0; s < STATES; s++) {

        fscanf(f, "%[^,],%d,%d,", state_arr[s].name, &state_arr[s].population,
                                           &state_arr[s].electoral_votes);
        for(int r = 0; r < RACES; r++) {
            fscanf(f, "%d,", &state_arr[s].race_distribution[r]);
        }
        for(int g = 0; g < GENDERS; g++) {
            fscanf(f, "%d,", &state_arr[s].gender_distribution[g]);
        }
        for(int a = 0; a < AGES; a++) {
            fscanf(f, "%d,", &state_arr[s].age_distribution[a]);
        }
        for(int i = 0; i < INCOME; i++) {
            fscanf(f, "%d,", &state_arr[s].income_distribution[i]);
        }
    }


    for (int s = 0; s < STATES; s++) {
        printf("%s %d %d ", state_arr[s].name, state_arr[s].population,
                                           state_arr[s].electoral_votes);
        for(int r = 0; r < RACES; r++) {
            printf("%d ", state_arr[s].race_distribution[r]);
        }
        for(int g = 0; g < GENDERS; g++) {
            printf("%d ", state_arr[s].gender_distribution[g]);
        }
        for(int a = 0; a < AGES; a++) {
            printf("%d ", state_arr[s].age_distribution[a]);
        }
        for(int i = 0; i < INCOME; i++) {
            printf("%d ", state_arr[s].income_distribution[i]);
        }
        //State,Pop,Mandates,WHITE,BLACK,HISPANIC,ASIAN,OTHER,MALE,FEMALE,18-25,26-34,35-54,55-64,65+,LOWER,MIDDLE,HIGHER
    }


    fclose(f);
}

// funktion til at initialisere kandidaterne
void init_candidates(candidate candidate_arr[]) {

    const char* names[60] = {"Donald Trump", "Kamala Harris", "Robert F. Kennedy"};
    int værdipolitik_c[CANDIDATES] = {10, -10, -50};
    int fordelingspolitik_c[CANDIDATES] = {-70, 70, -50};

    for (int i = 0; i < CANDIDATES; i++) {
        strcpy(candidate_arr[i].name, names[i]);
        candidate_arr[i].værdipolitik_c = værdipolitik_c[i];
        candidate_arr[i].fordelingspolitik_c = fordelingspolitik_c[i];
        candidate_arr[i].votes_fptp = 0;
        candidate_arr[i].votes_star = 0;
        candidate_arr[i].votes_rated = 0;
        candidate_arr[i].votes_rcv = 0;
    }
}

// funktion til at initialisere vælgerne
void init_voters(state state_arr[], voter voter_arr[], state cur_state, int current_i_voter) {

    for(int i = current_i_voter; i < cur_state.population + current_i_voter; i++) {
        voter_arr[i].fordelingspolitik_v = 0;
        voter_arr[i].værdipolitik_v = 0;
        voter_arr[i].is_voting = 1;
    }
    double calc_percent[4][5];
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 5; j++) {
            calc_percent[i][j] = 0;
        }
    }

    int fordelingspolitik[4][5] = {
        {-20, -10, 0, 10, 20},  // RACE
        {-25, 25},               // GENDER
        {-50, 0, 50},    // INCOME
        {-50, -25, 0, 25, 50}};  // AGE

    int værdipolitik[4][5] = {
        {-20, -10, 0, 10, 20},  // RACE
        {-25, 25},               // GENDER
        {-50, 0, 50},    // INCOME
        {-50, -25, 0, 25, 50}};  // AGE

    init_attributes(cur_state.population, voter_arr, RACES, calc_percent,
                    cur_state.race_distribution, race, fordelingspolitik, værdipolitik, current_i_voter);

    init_attributes(cur_state.population, voter_arr, GENDERS, calc_percent,
                    cur_state.gender_distribution, gender, fordelingspolitik, værdipolitik, current_i_voter);

    init_attributes(cur_state.population, voter_arr, INCOME, calc_percent,
                    cur_state.income_distribution, income, fordelingspolitik, værdipolitik, current_i_voter);

    init_attributes(cur_state.population, voter_arr, AGES, calc_percent,
                    cur_state.age_distribution, age, fordelingspolitik, værdipolitik, current_i_voter);
    //print_percent(calc_percent, cur_state.population);
}

// funktion til at initialisere attributterne for vælgerne
void init_attributes(int state_population, voter voter_arr[], int attribute_amount, double calc_percent[][5],
                     int attribute_distribution[], int category, int fordelingspolitik[][5], int værdipolitik[][5], int current_i_voter) {

    for (int i = current_i_voter; i < state_population + current_i_voter; i++) {
        int random = rand() % 1000 + 1;
        for (int j = 0; j < attribute_amount; j++) {
            if (random <= attribute_distribution[j]) {
                if(category == race) {
                    voter_arr[i].race_v = j;
                } else if(category == gender) {
                    voter_arr[i].gender_v = j;
                } else if(category == income) {
                    voter_arr[i].income_v = j;
                } else {
                    voter_arr[i].age_v = j;
                }

                voter_arr[i].fordelingspolitik_v += fordelingspolitik[category][j] + (rand() % (VARIANCE+1) - VARIANCE/2);
                voter_arr[i].værdipolitik_v += værdipolitik[category][j] + (rand() % (VARIANCE+1) - VARIANCE/2);
                calc_percent[category][j]++;
                break;
            }
        }
    }
}

// funktion til at printe fordeling af vælgerne
void print_percent(double calc_percent[][5], int state_population) {
    const char *voter_attributes[4][5] = {
        {"Male", "Female"},
        {"Low", "Middle", "High"},
        {"White", "Black", "Hispanic", "Asian", "Other"},
        {"Young", "Adult", "Middle aged", "Old", "Elderly"}};

    for (int i = 0; i < 4; i++) {
        printf("\n");
        for (int j = 0; j < 5; j++) {
            if (calc_percent[i][j] != 0) {
                printf("%s: %d, %.2lf%\n", voter_attributes[i][j], (int)calc_percent[i][j],
                                           calc_percent[i][j] / state_population * 100);
            }
        }
    }
}
//289 249
void get_distance(voter voter_arr[], candidate candidate_arr[], int population) {

    for(int i = 0; i < population; i++) {
        int x_1 = voter_arr[i].fordelingspolitik_v;
        int y_1 = voter_arr[i].værdipolitik_v;

        for(int j = 0; j < CANDIDATES; j++) {
            int x_2 = candidate_arr[j].fordelingspolitik_c;
            int y_2 = candidate_arr[j].værdipolitik_c;

            // Distance = sqrt((x_2 - x_1)^2 + (y_2 - y_1)^2))
            voter_arr[i].distance_to_[j] = sqrt(pow(x_2 - x_1, 2) + pow(y_2 - y_1, 2));
        }

        if(i % (population / 100) == 0) {
            printf("%.0lf%% of voters calculated\n", (double)i / population * 100);

        }
    }
}
