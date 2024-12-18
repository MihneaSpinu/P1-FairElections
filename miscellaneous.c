#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "functions.h"


// Checks if malloc / calloc is able to allocate memory
void check_memory_allocation(int array[]) {
    if(array == NULL) {
        printf("Error: Unable to allocate memory");
        exit(EXIT_FAILURE);
    }
}


// Box Muller normal distribution function
int variance() {
    double x, y, z;
    do {
        x = (double)rand() / RAND_MAX * 2 - 1;
        y = (double)rand() / RAND_MAX * 2 - 1;
        z = x * x + y * y;
    } while (z == 0 || z > 1);
    double h = sqrt(-2 * log(z) / z);

    int variance = x * h * STD_DEVIATION;

    // Sets a hard cap of 10 standard deviations from mean
    if(variance > STD_DEVIATION * 10)    variance = STD_DEVIATION * 10;
    if(variance < -(STD_DEVIATION * 10)) variance = -(STD_DEVIATION * 10);
    return variance;
}


// Calculates the distance from each voter to each candidate
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


// Determines how each voter rates each candidate
void get_ratings (voter voter_arr[], int num_of_candidates, int population) {

    int distance_rating[] = {15, 30, 45, 60, 75, 90, 105, 120, 135, 150};
    int size_of_arr = sizeof(distance_rating) / sizeof(int);
    int k;

    for(int i = 0; i < population; i++) {
        for(int j = 0; j < num_of_candidates; j++) {
            for(k = 0; k < size_of_arr; k++) {
                if(voter_arr[i].distance_to[j] <= distance_rating[k]) {
                    voter_arr[i].ratings[j] = 10-k;
                    break;
                }
            }
            if(k == size_of_arr) {
                voter_arr[i].ratings[j] = 0;
            }
        }
        if(i % ((population-1) / 10) == 0 && i != 0) {
            printf("%.0f%% of voters calculated\n", (float)i / population * 100);
        }
    }
}


// Prints the winner for the given vote type and system
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


// Simulates contingent election
int contingent_election(int num_of_candidates, int mandates[], candidate candidate_arr[], char voting_system[]) {

    int *advanced = calloc(num_of_candidates, sizeof(int));
    check_memory_allocation(advanced);

    int top1 = contingent_top_three(num_of_candidates, advanced, mandates);
    int top2 = contingent_top_three(num_of_candidates, advanced, mandates);
    int top3 = contingent_top_three(num_of_candidates, advanced, mandates);

    int winner = contingent_winner(num_of_candidates, mandates, top1, top2, top3);

    printf("\n%s wins %s by contingent election\n", candidate_arr[winner].name, voting_system);
    for(int i = 0; i < num_of_candidates; i++) {
        printf("%s got %d mandates\n", candidate_arr[i].name, mandates[i]);
    }
    free(advanced);
    return winner;
}


// Finds the top three candidates
int contingent_top_three(int num_of_candidates, int advanced[], int mandates[]) {

    int most_mandates = -1;
    int leading_candidate;
    for(int i = 0; i < num_of_candidates; i++) {
        if(!advanced[i] && mandates[i] > most_mandates) {
            most_mandates = mandates[i];
            leading_candidate = i;
        }
    }
    advanced[leading_candidate] = 1;
    return leading_candidate;
}


// Finds the winner of contingent election
int contingent_winner(int num_of_candidates, int mandates[], int top1, int top2, int top3) {

    int random;
    if(num_of_candidates == 2) {
        random = rand() % (mandates[top1] + mandates[top2]) + 1;
    } else {
        random = rand() % (mandates[top1] + mandates[top2] + mandates[top3]) + 1;
    }

    if(random <= mandates[top1])                  return top1;
    if(random <= mandates[top1] + mandates[top2]) return top2;
    return top3;
}


// Determines the average satisfaction of the voter to the winning candidate
float voters_satisfaction(voter current_voter, int winner_index) {

    float normalized_distance = current_voter.distance_to[winner_index] / MAX_DISTANCE;

    // Hard caps normalized_distance to [0,1] to handle unexpected values
    if(normalized_distance < 0) normalized_distance = 0;
    if(normalized_distance > 1) normalized_distance = 1;

    // Satisfaction decreases linearly with distance
    return 1 - normalized_distance;
}


// Calculates the overall satisfaction of the election depending on the winning candidate
float calc_satisfaction(int winner_index, voter voters_arr[], int population) {

    float total_satisfaction = 0;

    for(int i = 0; i < population; i++) {
        float voter_satisfaction = voters_satisfaction(voters_arr[i], winner_index);
        total_satisfaction += voter_satisfaction;
    }
    return (total_satisfaction / ((float)population)) * 100;
}


// Checks if there is a condorcet winner, returns index of candidate if there is
int condorcet_winner(int population, int num_of_candidates, voter voter_arr[]) {

    int pairwise[num_of_candidates][num_of_candidates];
    for(int i = 0; i < num_of_candidates; i++) {
        for(int j = 0; j < num_of_candidates; j++) {
            pairwise[i][j] = 0;
        }
    }

    // See pairwise candidates
    for(int i = 0; i < population; i++) {
        for(int j = 0; j < num_of_candidates; j++) {
            for(int k = j + 1; k < num_of_candidates; k++) {
                if(voter_arr[i].distance_to[j] < voter_arr[i].distance_to[k]) {
                    pairwise[j][k]++;
                } else {
                    pairwise[k][j]++;
                }
            }
        }
    }

    // Check for condorcet winner
    for(int i = 0; i < num_of_candidates; i++) {
        int is_condorcet = 1;
        for(int j = 0; j < num_of_candidates; j++) {
            if(i != j && pairwise[i][j] <= pairwise[j][i]) {
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


// Prints data for the given state
void prompt_stats(state state_arr[], float calc_percent[][4][5], candidate candidate_arr[], int num_of_candidates) {

    char input[MAX_NAME_LENGTH];
    printf("\n'exit' when done");
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
    while(strcmp(input, "exit") != 0);
}

// Prints the percentage distribution in each state
void print_percent(float calc_percent[][4][5], int population, int state) {

    const char *voter_attributes[4][5] = {
        {"White", "Black", "Hispanic", "Asian", "Other"},
        {"Male", "Female"},
        {"Low", "Middle", "High"},
        {"Young", "Adult", "Middle aged", "Old", "Elderly"}};

    for(int category = 0; category < 4; category++) {
        printf("\n");
        for(int attribute = 0; attribute < 5; attribute++) {
            if(calc_percent[state][category][attribute] != 0) {
                printf("%s: %.2f%% (%d)\n", voter_attributes[category][attribute],
                                             calc_percent[state][category][attribute] / population * 100,
                                             (int)calc_percent[state][category][attribute]);
            }
        }
    }
}