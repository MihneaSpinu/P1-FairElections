#include "functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// Box Muller normal distribution funktion
int variance() {
    double x, y, z;
    do {
        x = (double)rand() / RAND_MAX * 2 - 1;
        y = (double)rand() / RAND_MAX * 2 - 1;
        z = x * x + y * y;
    } while (z == 0 || z > 1);
    double h = sqrt(-2 * log(z) / z);


    int variance = x * h * STD_DEVIATION;

    if(variance > STD_DEVIATION * 10) {
        return STD_DEVIATION * 10;
    }
    if(variance < -(STD_DEVIATION * 10)) {
        return -(STD_DEVIATION * 10);
    }
    return variance;
}

// Beregner afstanden fra en givet vælger til hver kandidat
void get_distance(voter voter_arr[], candidate candidate_arr[], int population, int num_of_candidates) {

    for(int i = 0; i < population; i++) {
        int x_1 = voter_arr[i].economic_policy_v;
        int y_1 = voter_arr[i].social_policy_v;

        for(int j = 0; j < num_of_candidates; j++) {
            int x_2 = candidate_arr[j].economic_policy_c;
            int y_2 = candidate_arr[j].social_policy_c;

            // Distance = sqrt((x_2 - x_1)^2 + (y_2 - y_1)^2))
            voter_arr[i].distance_to[j] = sqrt(pow(x_2 - x_1, 2) + pow(y_2 - y_1, 2));
        }

        if(i % ((population-1) / 10) == 0 && i != 0) {
            printf("%.0f%% of voters calculated\n", (float)i / population * 100);
        }
    }
}


void get_ratings (voter voter_arr[], int num_of_candidates, int population) {

    int distance_rating[] = {15, 30, 45, 60, 75, 90, 105, 120, 135, 150};
    int size_of_arr = sizeof(distance_rating) / sizeof(distance_rating[0]);
    int k;
    for (int i = 0; i < population; i++) {
        for (int j = 0; j < num_of_candidates; j++) {
            for (k = 0; k < size_of_arr; k++) {
                if (voter_arr[i].distance_to[j] <= distance_rating[k]) {
                    voter_arr[i].ratings[j] = 10-k;
                    break;
                }
            }
            if (k == size_of_arr) {
                voter_arr[i].ratings[j] = 10-k;
            }
        }
    }
}


double voters_satisfaction(voter current_voter, int winner_index) {

    double normalized_distance = current_voter.distance_to[winner_index] / MAX_DISTANCE;

    // Clamp normalized_distance to [0, 1] to handle unexpected values
    if (normalized_distance < 0.0) normalized_distance = 0.0;
    if (normalized_distance > 1.0) normalized_distance = 1.0;

    // Satisfaction decreases linearly with distance
    return 1.0 - normalized_distance;
}


double calc_satisfaction(int winner_index, voter voters_arr[], int population) {

    double total_satisfaction = 0.0;

    for (int i = 0; i < population; i++) {
        double voter_satisfaction = voters_satisfaction(voters_arr[i], winner_index);
        total_satisfaction += voter_satisfaction;
    }
    return (total_satisfaction / ((double)population)) * 100.0;
}

// Printer dataene fra en givet stat
void prompt_stats(state state_arr[], double calc_percent[][4][5], candidate candidate_arr[], int num_of_candidates) {

    char input[MAX_NAME_LENGTH];

    do {
        printf("\nSee data for state:\n");
        scanf("%s", &input);
        for(int i = 0; i < STATES; i++) {
            if(strcmp(input, state_arr[i].name) == 0) {
                printf("Population: %d\n", state_arr[i].population);
                printf("Electoral votes: %d\n", state_arr[i].electoral_votes);
                for(int j = 0; j < num_of_candidates; j++) {
                    printf("\n%s got:\n", candidate_arr[j].name);
                    printf("%d FPTP votes\n", state_arr[i].candidate_votes_fptp[j]);
                    printf("%d RCV votes\n", state_arr[i].candidate_votes_rcv[j]);
                    printf("%d Rated points\n", state_arr[i].candidate_votes_rated[j]);
                    printf("%d STAR votes\n", state_arr[i].candidate_votes_star[j]);
                }
                print_percent(calc_percent, state_arr[i].population, i);
                break;
            }
        }
    }
    while(strcmp(input, "q") != 0);
}

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


int print_winner(int num_of_candidates, char voting_system[], int mandates[],
                  candidate candidate_arr[], char score_type[], int electoral_choice) {

    int winner = 0;
    for(int i = 0; i < num_of_candidates; i++) {
        if(mandates[winner] < mandates[i]) {
            winner = i;
        }
    }

    if(electoral_choice == 1 && mandates[winner] < 270) {
        return contingent_election(num_of_candidates, mandates, candidate_arr, voting_system);
    }
    printf("\n%s wins %s with %d %s\n", candidate_arr[winner].name, voting_system, mandates[winner], score_type);
    mandates[winner] = -1;
    for(int i = 0; i < num_of_candidates; i++) {
        if(mandates[i] != -1) {
            printf("%s got %d %s\n", candidate_arr[i].name, mandates[i], score_type);
        }
    }
    return winner;
}


int contingent_election(int num_of_candidates, int mandates[], candidate candidate_arr[], char voting_system[]) {

    int *advanced = calloc(num_of_candidates, sizeof(int));
    check_memory_allocation(advanced);
    int most_mandates = -1;
    int top1, top2, top3;
    int i;

    for(i = 0; i < num_of_candidates; i++) {
        if(mandates[i] > most_mandates) {
            most_mandates = mandates[i];
            top1 = i;
        }
    }
    advanced[top1] = 1;
    most_mandates = -1;

    for(i = 0; i < num_of_candidates; i++) {
        if(!advanced[i] && mandates[i] > most_mandates) {
            most_mandates = mandates[i];
            top2 = i;
        }
    }
    advanced[top2] = 1;
    most_mandates = -1;

    for(i = 0; i < num_of_candidates; i++) {
        if(!advanced[i] && mandates[i] > most_mandates) {
            most_mandates = mandates[i];
            top3 = i;
        }
    }

    int winner;
    int random = rand() % (mandates[top1] + mandates[top2] + mandates[top3]) + 1;
    if(random <= mandates[top1]) {
        winner = top1;
    } else if(random <= mandates[top1] + mandates[top2]) {
        winner = top2;
    } else {
        winner = top3;
    }
    printf("\n%s wins %s by contingent election\n", candidate_arr[winner].name, voting_system);
    for(int j = 0; j < num_of_candidates; j++) {
        printf("%s got %d mandates\n", candidate_arr[j].name, mandates[j]);
    }
    free(advanced);
    return winner;
}


int condorcet_winner(int num_voters, int num_candidates, voter voter_arr[]) {
    int pairwise[num_candidates][num_candidates];
    for (int i = 0; i < num_candidates; i++) {
        for (int j = 0; j < num_candidates; j++) {
            pairwise[i][j] = 0;
        }
    }
    //see pairwise candidates
    for (int i = 0; i < num_voters; i++) {
        for (int j = 0; j < num_candidates; j++) {
            for (int k = j + 1; k < num_candidates; k++) {
                if (voter_arr[i].distance_to[j] < voter_arr[i].distance_to[k]) {
                    pairwise[j][k]++;
                } else {
                    pairwise[k][j]++;
                }
            }
        }
    }
    //check for cordocet winner
    for (int i = 0; i < num_candidates; i++) {
        int is_condorcet = 1;
        for (int j = 0; j < num_candidates; j++) {
            if (i != j && pairwise[i][j] <= pairwise[j][i]) {
                is_condorcet = 0;
                break;
            }
        }
        if(is_condorcet) {
            return i;
        }
    }
    return -1; // No Condorcet winner
}

void check_memory_allocation(int array[]) {
    if(array == NULL) {
        printf("Error allocating memory");
        exit(EXIT_FAILURE);
    }
}