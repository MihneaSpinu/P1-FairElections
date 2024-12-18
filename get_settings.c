#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"


// Scans the users input to determine how to simulate the election
void scan_election_settings(int *simulation_choice, int *electoral_choice, int *candidate_choice,
                            int *voting_system_choice, int *candidates, char candidate_name[][MAX_NAME_LENGTH],
                            int social_p[MAX_CANDIDATES], int economic_p[MAX_CANDIDATES]) {

    printf("1) Run 2024 election\n2) Run 2020 election\n3) Run 2016 election\n4) Run custom election\n");
    scanf("%d", simulation_choice);
    check_input_validity(*simulation_choice, 4);

    if(*simulation_choice != 4) {
        *candidates = 2;
        *electoral_choice = 1;
        *voting_system_choice = 1;
        strcpy(candidate_name[0], "Donald Trump");
        social_p[0] = 50, economic_p[0] = 50;
        if(*simulation_choice == 1) {
            strcpy(candidate_name[1], "Kamala Harris");
            social_p[1] = -30, economic_p[1] = -30;
        } else if(*simulation_choice == 2) {
            strcpy(candidate_name[1], "Joe Biden");
            social_p[1] = -20, economic_p[1] = -25;
        } else {
            strcpy(candidate_name[1], "Hillary Clinton");
            social_p[1] = -35, economic_p[1] = -20;
        }
        return;
    }

    printf("\n1) Determine winner by electoral college\n2) Determine winner on national basis\n");
    scanf("%d", electoral_choice);
    check_input_validity(*electoral_choice, 2);

    if(*electoral_choice == 1) {
        printf("\n1) Use current US voting system\n2) Use FPTP, RCV, Ranked & STAR voting systems\n");
        scanf("%d", voting_system_choice);
        check_input_validity(*voting_system_choice, 2);
    } else {
        *voting_system_choice = 2;
    }

    printf("\n1) Use preset candidates\n2) Add your own candidates\n");
    scanf("%d", candidate_choice);
    check_input_validity(*candidate_choice, 2);
    if(*candidate_choice == 2) {
        custom_candidates(candidates, candidate_name, social_p, economic_p);
    }
    if(*candidate_choice == 1) {
        *candidates = 5;
        strcpy(candidate_name[0], "Donald Trump");
        strcpy(candidate_name[1], "Barack Obama");
        strcpy(candidate_name[2], "Joe Biden");
        strcpy(candidate_name[3], "John F. Kennedy");
        strcpy(candidate_name[4], "Richard Nixon");
        social_p[0] = 45,    social_p[1] = -35,    social_p[2] = -27,     social_p[3] = 49,    social_p[4] = 60;
        economic_p[0] = 55,  economic_p[1] = -35,  economic_p[2] = -27,   economic_p[3] = 49,  economic_p[4] = 55;
    }
    if(*candidates < 2) {
        printf("Error: There has to be at least 2 candidates");
        exit(EXIT_FAILURE);
    }
}


// Scans custom candidates from the user, should they have chosen to do so
void custom_candidates(int *candidates, char candidate_name[][MAX_NAME_LENGTH], int social_p[], int economic_p[]) {

    char name[MAX_NAME_LENGTH];

    printf("\n'exit' when done\n");
    for(*candidates = 0; *candidates < MAX_CANDIDATES; (*candidates)++) {
        printf("Choose candidate name and position on political compass: [-100,100]\n");
        scanf("%s", &name);
        if(strcmp(name, "exit") == 0) return;
        strcpy(candidate_name[*candidates], name);

        scanf("%d %d", &social_p[*candidates], &economic_p[*candidates]);
        if(social_p[*candidates] < -100 || social_p[*candidates] > 100 ||
            economic_p[*candidates] > 100 || economic_p[*candidates] < -100) {
            printf("Error: Values out of range (-100,100)");
            exit(EXIT_FAILURE);
        }
    }
}


// Checks if the input is valid
void check_input_validity(int user_input, int choice_amount) {
    if(user_input < 1 || user_input > choice_amount) {
        printf("Error: Invalid input");
        exit(EXIT_FAILURE);
    }
}