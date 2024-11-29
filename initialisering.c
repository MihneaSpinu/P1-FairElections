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
    for (int i = 0; i < STATE_MAX; i++)
    {
        fscanf(f, "%[^0-9] %d %d\n", state_arr[i].name, &state_arr[i].voters_population,
               &state_arr[i].electoral_mandates);
    }
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

void init_voters(voter voters_arr[], double calc_percent[][7]) {

    int income_distr[5], race_distr[7], age_distr[5];
    income income_arr[5];
    race race_arr[7];
    age age_arr[5];

    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 7; j++) {
            calc_percent[i][j] = 0;
        }
    }

    // STARTER HELE TILDELINGSPROCESSEN
    for (int i = 0; i < POPULATION; i++) {

        // KØN:
        int random_gender = rand() % 2;
        voters_arr[i].gender_v = random_gender;
        if (random_gender == 0) {
            calc_percent[0][0]++;
        } else {
            calc_percent[0][1]++;
        }

        // INDKOMST:
        int random_income = rand() % 100 + 1;
        for(int j = 0; j < 5; j++) {
            income_arr[j] = j;
        }

        income_distr[0] = 20, income_distr[1] = 40, income_distr[2] = 60,
        income_distr[3] = 80, income_distr[4] = 100; // SKAL OMFORDELES BASERET PÅ DATA
        for(int j = 0; j < 5; j++) {
            if(random_income <= income_distr[j]) {
                voters_arr[i].income_v = income_arr[j];
                calc_percent[1][j]++;
                break;
            }
        }

        // RACE:
        int random_race = rand() % 1000 + 1;
        for(int j = 0; j < 7; j++) {
            race_arr[j] = j;
        }

        race_distr[0] = 584, race_distr[1] = 721, race_distr[2] = 916, race_distr[3] = 980,
        race_distr[4] = 993, race_distr[5] = 996, race_distr[6] = 1000; // SOURCE: https://www.census.gov/quickfacts/
        for(int j = 0; j < 7; j++) {
            if(random_race <= race_distr[j]) {
                voters_arr[i].race_v = race_arr[j];
                calc_percent[2][j]++;
                break;
            }
        }

        // ALDER:
        int random_age = rand() % 100 + 1;
        for(int j = 0; j < 5; j++) {
            income_arr[j] = j;
        }

        age_distr[0] = 20, age_distr[1] = 40, age_distr[2] = 60,
        age_distr[3] = 80, age_distr[4] = 100; // SKAL OMFORDELES BASERET PÅ DATA
        for(int j = 0; j < 5; j++) {
            if(random_age <= age_distr[j]) {
                voters_arr[i].age_v = age_arr[j];
                calc_percent[3][j]++;
                break;
            }
        }
    }
}


void get_percent(double calc_percent[][7]) {

    char *voter_attributes[4][7] = {{"Male", "Female"},
                                   {"Poor", "Low", "Middle", "High", "Rich"},
                                   {"White", "Black", "Hispanic", "Asian", "Native American", "Native Hawaiian", "Other"},
                                   {"Young", "Adult", "Middle aged", "Old", "Elderly"}};
    for(int i = 0; i < 4; i++) {
        printf("\n");
        for(int j = 0; j < 7; j++) {
            if(calc_percent[i][j] != 0) {
                printf("%s: %.2lf%\n", voter_attributes[i][j], calc_percent[i][j] / POPULATION * 100);
            }
        }
    }
}

// https://www.kff.org/other/state-indicator/distribution-by-sex/?currentTimeframe=0&sortModel=%7B%22colId%22:%22Location%22,%22sort%22:%22asc%22%7D
// https://en.wikipedia.org/wiki/List_of_U.S._states_and_territories_by_race/ethnicity
// https://en.wikipedia.org/wiki/List_of_U.S._states_and_territories_by_income