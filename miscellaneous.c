#include "functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// Funktion til at printe fordelingen af vælgerne ud fra en givet stat
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

// Beregner afstanden fra en givet vælger til hver kandidat
void get_distance(voter voter_arr[], candidate candidate_arr[], int population) {

    for(int i = 0; i < population; i++) {
        int x_1 = voter_arr[i].fordelingspolitik_v;
        int y_1 = voter_arr[i].værdipolitik_v;

        for(int j = 0; j < CANDIDATES; j++) {
            int x_2 = candidate_arr[j].fordelingspolitik_c;
            int y_2 = candidate_arr[j].værdipolitik_c;

            // Distance = sqrt((x_2 - x_1)^2 + (y_2 - y_1)^2))
            voter_arr[i].distance_to[j] = sqrt(pow(x_2 - x_1, 2) + pow(y_2 - y_1, 2));

            // RATED
            int distance_rating[] = {20, 40, 60, 80, 100, 120, 140, 160, 180, 200};
            int ratings[] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
            int k;
            for (k = 0; k < sizeof(distance_rating) / sizeof(distance_rating[0]); k++) {
                if (voter_arr[i].distance_to[j] <= distance_rating[k]) {
                    voter_arr[i].ratings[j] = ratings[k];
                    break;
                }
            }
            if (k == sizeof(distance_rating) / sizeof(distance_rating[0])) {
                voter_arr[i].ratings[j] = ratings[k];
            }
        }

        if((i+1) % (population / 10) == 0 && i != 0) {
            printf("%.0lf%% of voters calculated\n", (double)i / population * 100);

        }
    }
}

// Returnere en range med størrelse VARIANCE centreret omkring 0
int variance() {
    return (rand() % (VARIANCE + 1)) - (VARIANCE / 2);
}

// Printer dataene fra en givet stat
void prompt_stats(state state_arr[], double calc_percent[][4][5]) {

    char input[MAX_NAME_LENGTH];

    do {
        printf("\nSee data for state:\n");
        scanf("%s", &input);
        for(int i = 0; i < STATES; i++) {
            if(strcmp(input, state_arr[i].name) == 0) {
                printf("Population: %d\n", state_arr[i].population);
                printf("Electoral votes: %d\n", state_arr[i].electoral_votes);
                print_percent(calc_percent, state_arr[i].population, i);
                break;
            }
        }
    } while(strcmp(input, "q") != 0);

}

/*
void print_winners(char winner[], int mandates[], char *runner_up[]) {

    printf("%s wins with %d electoral votes\n", winner, mandates[0]);
    printf("\nRunners up:\n");
    for(int i = 0; i < CANDIDATES - 1; i++) {
        printf("%s with %d electoral votes\n", runner_up[i], mandates[i+1]);
    }
}
*/