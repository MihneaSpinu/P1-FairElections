#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "functions.h"

// funktion til at initialisere staterne
void init_state(state state_arr[]) {
    FILE* f = fopen("state_data.txt", "r");
    if (f == NULL) {
        printf("Error: couldn't open file 'state_data.txt'");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < STATES; i++) {

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
void init_candidates(candidate candidate_arr[]) {

    const char* names[100] = {"Donald Trump", "Kamala Harris", "Robert F. Kennedy"};
    int værdipolitik_c[CANDIDATES] = {75, -50, 20};
    int fordelingspolitik_c[CANDIDATES] = {70, -90, -60};

    for (int i = 0; i < CANDIDATES; i++) {
        strcpy(candidate_arr[i].name, names[i]);
        candidate_arr[i].værdipolitik_c = værdipolitik_c[i];
        candidate_arr[i].fordelingspolitik_c = fordelingspolitik_c[i];
        candidate_arr[i].votes_fptp = 0;
        candidate_arr[i].votes_star = 0;
        candidate_arr[i].votes_rated = 0;
        candidate_arr[i].votes_rcv = 0;
        candidate_arr[i].mandates_star = 0;
    }
}

// funktion til at initialisere vælgerne
void init_voters(state state_arr[], voter voter_arr[], state cur_state, int current_i_voter, int state, double calc_percent[][4][5]) {

    for(int i = current_i_voter; i < cur_state.population + current_i_voter; i++) {
        voter_arr[i].fordelingspolitik_v = 0;
        voter_arr[i].værdipolitik_v = 0;
        voter_arr[i].is_voting = 1;
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

    init_attributes(cur_state.population, voter_arr, RACES, calc_percent,
                    cur_state.race_distribution, race, fordelingspolitik, værdipolitik, current_i_voter, state);

    init_attributes(cur_state.population, voter_arr, GENDERS, calc_percent,
                    cur_state.gender_distribution, gender, fordelingspolitik, værdipolitik, current_i_voter, state);

    init_attributes(cur_state.population, voter_arr, INCOME, calc_percent,
                    cur_state.income_distribution, income, fordelingspolitik, værdipolitik, current_i_voter, state);

    init_attributes(cur_state.population, voter_arr, AGES, calc_percent,
                    cur_state.age_distribution, age, fordelingspolitik, værdipolitik, current_i_voter, state);
}

// funktion til at initialisere attributterne for vælgerne
void init_attributes(int state_population, voter voter_arr[], int attribute_amount, double calc_percent[][4][5],
                     int attribute_distribution[], int category, int fordelingspolitik[][5], int værdipolitik[][5],
                     int current_i_voter, int state) {

    for (int i = current_i_voter; i < state_population + current_i_voter; i++) {
        int random = rand() % 1000 + 1;
        for (int attribute = 0; attribute < attribute_amount; attribute++) {
            if (random <= attribute_distribution[attribute]) {
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

// funktion til at printe fordeling af vælgerne
void print_percent(double calc_percent[][4][5], int state_population, int state) {

    const char *voter_attributes[4][5] = {
        {"White", "Black", "Hispanic", "Asian", "Other"},
        {"Male", "Female"},
        {"Low", "Middle", "High"},
        {"Young", "Adult", "Middle aged", "Old", "Elderly"}};

    for (int category = 0; category < 4; category++) {
        printf("\n");
        for (int attribute = 0; attribute < 5; attribute++) {
            if(calc_percent[state][category][attribute] != 0) {
                printf("%s: %.2lf%% (%d)\n", voter_attributes[category][attribute],
                                            calc_percent[state][category][attribute] / state_population * 100,
                                            (int)calc_percent[state][category][attribute]);
            }
        }
    }
}

void get_distance(voter voter_arr[], candidate candidate_arr[], int population) {

    for(int i = 0; i < population; i++) {
        int x_1 = voter_arr[i].fordelingspolitik_v;
        int y_1 = voter_arr[i].værdipolitik_v;

        for(int j = 0; j < CANDIDATES; j++) {
            int x_2 = candidate_arr[j].fordelingspolitik_c;
            int y_2 = candidate_arr[j].værdipolitik_c;

            // Distance = sqrt((x_2 - x_1)^2 + (y_2 - y_1)^2))
            voter_arr[i].distance_to_[j] = sqrt(pow(x_2 - x_1, 2) + pow(y_2 - y_1, 2));

            // RATED
            if (voter_arr[i].distance_to_[j] <= 25) {
                voter_arr[i].ratings[j] = 10;
            } else if (voter_arr[i].distance_to_[j] <= 50) {
                voter_arr[i].ratings[j] = 9;
            } else if (voter_arr[i].distance_to_[j] <= 75) {
                voter_arr[i].ratings[j] = 8;
            } else if (voter_arr[i].distance_to_[j] <= 100) {
                voter_arr[i].ratings[j] = 7;
            } else if (voter_arr[i].distance_to_[j] <= 125) {
                voter_arr[i].ratings[j] = 6;
            }else if (voter_arr[i].distance_to_[j] <= 150) {
                voter_arr[i].ratings[j] = 5;
            } else if (voter_arr[i].distance_to_[j] <= 175) {
                voter_arr[i].ratings[j] = 4;
            } else if (voter_arr[i].distance_to_[j] <= 200) {
                voter_arr[i].ratings[j] = 3;
            } else if (voter_arr[i].distance_to_[j] <= 225) {
                voter_arr[i].ratings[j] = 2;
            } else if (voter_arr[i].distance_to_[j] <= 250) {
                voter_arr[i].ratings[j] = 1;
            } else {
                voter_arr[i].ratings[j] = 0;
            }

        }

        if(i % (population / 10) == 0 && i != 0) {
            printf("%.0lf%% of voters calculated\n", (double)i / population * 100);

        }
    }
}

int variance() {
    return (rand() % (VARIANCE + 1)) - (VARIANCE / 2);
}

void prompt_stats(state state_arr[], double calc_percent[][4][5]) {

    char input[MAX_NAME_LENGTH];

    do {
        printf("\nSee data for state:\n");
        scanf("%s", &input);
        for(int i = 0; i < STATES + 1; i++) {
            if(strcmp(input, state_arr[i].name) == 0) {
                printf("Population: %d\n", state_arr[i].population);
                printf("Electoral votes: %d\n", state_arr[i].electoral_votes);
                print_percent(calc_percent, state_arr[i].population, i);
                break;
            }
        }
    } while(strcmp(input, "q") != 0);

}

void init_percent(double calc_percent[][4][5]) {
    for(int state = 0; state < STATES; state++) {
        for(int category = 0; category < 4; category++) {
            for(int attribute = 0; attribute < 5; attribute++) {
                calc_percent[state][category][attribute] = 0;
            }
        }
    }
}