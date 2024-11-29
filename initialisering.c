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
    income_e income_arr[5];
    race_e race_arr[7];
    age_e age_arr[5];

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

/*
void init_voters(state current_state, voter voters_arr[]);
void init_race(state current_state, voter voters_arr[], int i);
void init_gender(state current_state, voter voters_arr[], int i);
void init_income(state current_state, voter voters_arr[], int i);
void init_age(state current_state, voter voters_arr[], int i);
void print_winner();

int main() {

    voter voters_arr[POPULATION];

    int race_dis[7], gender_dis[2], income_dis[5], age_dis[5],
        population,
        electoral_votes;

    FILE *fil;

    for(int i = 0; i < STATES; i++) {

        for(int j = 0; j < RACES; j++) {
            race_dis[j] = fscanf(fil, "%[^ ]");
        }
        for(int j = 0; j < GENDERS; j++) {
            gender_dis[j] = fscanf(fil, "%[^ ]");
        }
        for(int j = 0; j < INCOME; j++) {
            income_dis[j] = fscanf(fil, "%[^ ]");
        }
        for(int j = 0; j < AGES; j++) {
            age_dis[j] = fscanf(fil, "%[^ ]");
        }

        population = fscanf(fil, "%[^ ]");
        electoral_votes = fscanf(fil, "%[^ ]");

        state current_state = {race_dis[0], race_dis[1], race_dis[2], race_dis[3], race_dis[4], race_dis[5], race_dis[6],
                               gender_dis[0], gender_dis[1],
                               income_dis[0], income_dis[1], income_dis[2], income_dis[3], income_dis[4],
                               age_dis[0], age_dis[1], age_dis[2], age_dis[3], age_dis[4],
                               population, electoral_votes};

        printf("%s is voting...\n", current_state.name[i])
        init_voters(current_state, voters_arr);
        political_compass_placement();
        calculate_distance();

        fptp(current_state, distance);
        rcv(current_state, distance);
        star(current_state, distance);
        ranked(current_state, distance);

    }

    print_winner(); // for hver valgsystem
}

void init_voters(state current_state, voter voters_arr[]) {

    for (int i = 0; i < current_state.population; i++) {
        init_race(current_state, voters_arr, i);
        init_gender(current_state, voters_arr, i);
        init_income(current_state, voters_arr, i);
        init_age(current_state, voters_arr, i);
    }
}

void init_race(state current_state, voter voters_arr[], int i) {

    race_e race_arr[7];
    int random_race = rand() % 1000 + 1;
    for(int j = 0; j < RACES; j++) {
        race_arr[j] = j;
    }

    for(int j = 0; j < RACES; j++) {
        if(random_race <= current_state.race_distribution[j]) {
            voters_arr[i].race_v = race_arr[j];
            break;
        }
    }
}

void init_gender(state current_state, voter voters_arr[], int i) {

    gender_e gender_arr[2];
    int random_gender = rand() % 2;
    for(int j = 0; j < GENDERS; j++) {
        gender_arr[j] = j;
    }

    for(int j = 0; j < GENDERS; j++) {
        if(random_gender <= current_state.gender_distribution[j]) {
            voters_arr[i].gender_v = gender_arr[j];
            break;
        }
    }
}

void init_income(state current_state, voter voters_arr[], int i) {

    income_e income_arr[5];
    int random_income = rand() % 100 + 1;
    for(int j = 0; j < INCOME; j++) {
        income_arr[j] = j;
    }

    for(int j = 0; j < INCOME; j++) {
        if(random_income <= current_state.income_distribution[j]) {
            voters_arr[i].income_v = income_arr[j];
            break;
        }
    }
}

void init_age(state current_state, voter voters_arr[], int i) {

    age_e age_arr[5];
    int random_age = rand() % 100 + 1;
    for(int j = 0; j < AGES; j++) {
        age_arr[j] = j;
    }

    for(int j = 0; j < AGES; j++) {
        if(random_age <= current_state.age_distribution[j]) {
            voters_arr[i].age_v = age_arr[j];
            break;
        }
    }
}
*/


