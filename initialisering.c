#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "functions.h"

// funktion til at initialisere staterne
void init_state(state state_arr[])
{
    FILE* f = fopen("state_data.txt", "r");
    if (f == NULL)
    {
        printf("Error: couldn't open file named state_data.txt");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < STATES; i++)
    {
        fscanf(f, "%[^0-9] %d %d\n", state_arr[i].name, &state_arr[i].population,
               &state_arr[i].electoral_votes);
    }
    printf("%s %d %d", state_arr[0].name, state_arr[0].population, state_arr[0].electoral_votes);
    fclose(f);
}

// funktion til at initialisere kandidaterne
void init_candidates(candidate candidate_arr[])
{
    const char* names[] = {"Donald Trump", "Kamala Harris", "Robert F. Kennedy"};
    double værdipolitik_c[] = {-4.0, 3, -1};
    double fordelingspolitik_c[] = {4.0, -3, 2};
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
void init_voters(state current_state, voter voters_arr[], int attribute[]) {
    init_attributes(current_state.population, voters_arr, attribute, RACES, current_state.race_distribution, 0); // RACE
    init_attributes(current_state.population, voters_arr, attribute, GENDERS, current_state.gender_distribution, 1); // GENDER
    init_attributes(current_state.population, voters_arr, attribute, INCOME, current_state.income_distribution, 2); // INCOME
    init_attributes(current_state.population, voters_arr, attribute, AGES, current_state.age_distribution, 3); // AGE
}

// funktion til at initialisere attributterne for vælgerne
void init_attributes(int state_population, voter voters_arr[], int attribute[], int attribute_amount, int distribution[], int attribute_type) {
    for (int i = 0; i < state_population; i++) {
        int random = rand() % 1000 + 1;
        for (int j = 0; j < attribute_amount; j++) {
            if (random <= distribution[j]) {
                switch (attribute_type) {
                case 0:
                    voters_arr[i].race_v = attribute[j];
                    break;
                case 1:
                    voters_arr[i].gender_v = attribute[j];
                    break;
                case 2:
                    voters_arr[i].income_v = attribute[j];
                    break;
                case 3:
                    voters_arr[i].age_v = attribute[j];
                    break;
                }
                break;
            }
        }
    }
}

// funktion til at printe fordeling af vælgerne
void print_percent(double calc_percent[][7]) {

    char *voter_attributes[4][7] = {{"Male", "Female"},
                                   {"Poor", "Low", "Middle", "High", "Rich"},
                                   {"White", "Black", "Hispanic", "Asian", "Native American", "Native Hawaiian", "Other"},
                                   {"Young", "Adult", "Middle aged", "Old", "Elderly"}};
    for(int i = 0; i < 4; i++) {
        printf("\n");
        for(int j = 0; j < 7; j++) {
            if(calc_percent[i][j] != 0) {
                printf("%s: %d, %.2lf%\n", voter_attributes[i][j], (int)calc_percent[i][j], calc_percent[i][j] / POPULATION * 100);
            }
        }
    }
}

void get_distance(voter voters_arr[], candidate candidate_arr[], int state_population) {

    for(int i = 0; i < state_population; i++) {
        int x_1 = voters_arr[i].fordelingspolitik_v;
        int y_1 = voters_arr[i].værdipolitik_v;

        for(int j = 0; j < CANDIDATES; j++) {
            int x_2 = candidate_arr[j].fordelingspolitik_c;
            int y_2 = candidate_arr[j].værdipolitik_c;

            // Distance = sqrt((x_2 - x_1)^2 + (y_2 - y_1)^2))
            voters_arr[i].distance_to_[j] = sqrt(pow(x_2 - x_1, 2) + pow(y_2 - y_1, 2));
        }
    }
}