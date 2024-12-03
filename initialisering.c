#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "functions.h"

// funktion til at initialisere staterne
void init_state(state state_arr[]) {
    FILE* f = fopen("state_data.txt", "r");
    if (f == NULL) {
        printf("Error: couldn't open file named state_data.txt");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < STATES; i++) {
        fscanf(f, "%[^0-9] %d %d\n", state_arr[i].name, &state_arr[i].population,
                                           &state_arr[i].electoral_votes);

        printf("%s %d %d\n", state_arr[i].name, state_arr[i].population, state_arr[i].electoral_votes);
    }

    fclose(f);
}

// funktion til at initialisere kandidaterne
void init_candidates(candidate candidate_arr[]) {

    const char* names[] = {"Donald Trump", "Kamala Harris", "Robert F. Kennedy"};
    int værdipolitik_c[CANDIDATES] = {-4, 3, -1};
    int fordelingspolitik_c[CANDIDATES] = {4, -3, 2};

    for (int i = 0; i < CANDIDATES; i++)
    {
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
void init_voters(state state_arr[], voter voter_arr[]) {

    for (int i = 0; i < POPULATION; i++) {
        voter_arr[i].fordelingspolitik_v = 0;
        voter_arr[i].værdipolitik_v = 0;
    }

    int fordelingspolitik[4][5] = {
        {-2, -1, 0, 1, 2},  // RACE
        {-2, -1, '\0'},     // GENDER
        {-2, -1, 0, 1, 2},  // INCOME
        {-2, -1, 0, 1, 2}}; // AGE

    int værdipolitik[4][5] = {
        {-2, -1, 0, 1, 2},  // RACE
        {-2, -1, '\0'},     // GENDER
        {-2, -1, 0, 1, 2},  // INCOME
        {-2, -1, 0, 1, 2}}; // AGE

    init_attributes(state_arr[i].population, voter_arr, RACES,
                    state_arr[i].race_distribution, race, fordelingspolitik, værdipolitik);

    init_attributes(state_arr[i].population, voter_arr, GENDERS,
                    state_arr[i].gender_distribution, gender, fordelingspolitik, værdipolitik);

    init_attributes(state_arr[i].population, voter_arr, INCOME,
                    state_arr[i].income_distribution, income, fordelingspolitik, værdipolitik);

    init_attributes(state_arr[i].population, voter_arr, AGES,
                    state_arr[i].age_distribution, age, fordelingspolitik, værdipolitik);
}

// funktion til at initialisere attributterne for vælgerne
void init_attributes(int state_population, voter voter_arr[], int attribute_amount,
                     int distribution[], int attribute_type, int fordelingspolitik[][5], int værdipolitik[][5]) {

    for (int i = 0; i < state_population; i++) {
        int random = rand() % 1000 + 1;
        for (int j = 0; j < attribute_amount; j++) {
            if (random <= distribution[j]) {
                switch(attribute_type) {
                case race:
                    voter_arr[i].race_v = j;
                    voter_arr[i].fordelingspolitik_v += fordelingspolitik[race][j];
                    voter_arr[i].værdipolitik_v += værdipolitik[race][j];
                    break;
                case gender:
                    voter_arr[i].gender_v = j;
                    voter_arr[i].fordelingspolitik_v += fordelingspolitik[gender][j];
                    voter_arr[i].værdipolitik_v += værdipolitik[gender][j];
                    break;
                case income:
                    voter_arr[i].income_v = j;
                    voter_arr[i].fordelingspolitik_v += fordelingspolitik[income][j];
                    voter_arr[i].værdipolitik_v += værdipolitik[income][j];
                    break;
                case age:
                    voter_arr[i].age_v = j;
                    voter_arr[i].fordelingspolitik_v += fordelingspolitik[age][j];
                    voter_arr[i].værdipolitik_v += værdipolitik[age][j];
                    break;
                }
                break;
            }
        }
    }
}

// funktion til at printe fordeling af vælgerne
void print_percent(double calc_percent[][7]) {
    const char *voter_attributes[4][7] = {
        {"Male", "Female", '\0'},
        {"Poor", "Low", "Middle", "High", "Rich"},
        {"White", "Black", "Hispanic", "Asian", "Native American", "Native Hawaiian", "Other"},
        {"Young", "Adult", "Middle aged", "Old", "Elderly"}
    };
    for (int i = 0; i < 4; i++) {
        printf("\n");
        for (int j = 0; j < 7; j++) {
            if (calc_percent[i][j] != 0) {
                printf("%s: %d, %.2lf%\n", voter_attributes[i][j], (int)calc_percent[i][j],
                                           calc_percent[i][j] / POPULATION * 100);
            }
        }
    }
}

void get_distance(voter voter_arr[], candidate candidate_arr[], int state_population) {

    for(int i = 0; i < state_population; i++) {
        int x_1 = voter_arr[i].fordelingspolitik_v;
        int y_1 = voter_arr[i].værdipolitik_v;

        for(int j = 0; j < CANDIDATES; j++) {
            int x_2 = candidate_arr[j].fordelingspolitik_c;
            int y_2 = candidate_arr[j].værdipolitik_c;

            // Distance = sqrt((x_2 - x_1)^2 + (y_2 - y_1)^2))
            voter_arr[i].distance_to_[j] = sqrt(pow(x_2 - x_1, 2) + pow(y_2 - y_1, 2));
        }
    }
}