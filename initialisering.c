#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"

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

void init_voters(state current_state, voter voters_arr[], int attribute[]) {

    init_attributes(current_state.population, voters_arr, attribute, RACES, current_state.race_distribution); // RACE
    init_attributes(current_state.population, voters_arr, attribute, GENDERS, current_state.gender_distribution); // GENDER
    init_attributes(current_state.population, voters_arr, attribute, INCOME, current_state.income_distribution); // INCOME
    init_attributes(current_state.population, voters_arr, attribute, AGES, current_state.age_distribution); // AGE

}

void init_attributes(int state_population, voter voters_arr[], int attribute[], int attribute_amount, int distribution[]) {

    for (int i = 0; i < state_population; i++) {

        int random = rand() % 1000 + 1;
        for(int j = 0; j < attribute_amount; j++) {
            if(random <= distribution[j]) {
                voters_arr[i].race_v = attribute[j]; // ??????????????????????????
                break;
            }
        }
    }
}


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