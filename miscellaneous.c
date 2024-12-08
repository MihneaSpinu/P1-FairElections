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
            if (voter_arr[i].distance_to[j] <= 25) {
                voter_arr[i].ratings[j] = 10;
            } else if (voter_arr[i].distance_to[j] <= 50) {
                voter_arr[i].ratings[j] = 9;
            } else if (voter_arr[i].distance_to[j] <= 75) {
                voter_arr[i].ratings[j] = 8;
            } else if (voter_arr[i].distance_to[j] <= 100) {
                voter_arr[i].ratings[j] = 7;
            } else if (voter_arr[i].distance_to[j] <= 125) {
                voter_arr[i].ratings[j] = 6;
            }else if (voter_arr[i].distance_to[j] <= 150) {
                voter_arr[i].ratings[j] = 5;
            } else if (voter_arr[i].distance_to[j] <= 175) {
                voter_arr[i].ratings[j] = 4;
            } else if (voter_arr[i].distance_to[j] <= 200) {
                voter_arr[i].ratings[j] = 3;
            } else if (voter_arr[i].distance_to[j] <= 225) {
                voter_arr[i].ratings[j] = 2;
            } else if (voter_arr[i].distance_to[j] <= 250) {
                voter_arr[i].ratings[j] = 1;
            } else {
                voter_arr[i].ratings[j] = 0;
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