#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "functions.h"

void scan_election_settings(int *simulation_choice, int *electoral_choice, int *candidate_choice,
                            int *voting_system_choice, int *candidates, char candidate_name[][MAX_NAME_LENGTH],
                            int værdi[MAX_CANDIDATES], int fordeling[MAX_CANDIDATES]) {

    printf("1) Run 2024 election\n2) Run 2020 election\n3) Run 2016 election\n4) Run custom election\n");
    scanf("%d", simulation_choice);
    check_input_validity(*simulation_choice, 4);

    if(*simulation_choice != 4) {
        *candidates = 2;
        *electoral_choice = 1;
        *voting_system_choice = 1;
        strcpy(candidate_name[0], "Donald Trump");
        værdi[0] = 50, fordeling[0] = 50;
        if(*simulation_choice == 1) {
            strcpy(candidate_name[1], "Kamala Harris");
            værdi[1] = -30, fordeling[1] = -30;
        } else if(*simulation_choice == 2) {
            strcpy(candidate_name[1], "Joe Biden");
            værdi[1] = -20, fordeling[1] = -25;
        } else {
            strcpy(candidate_name[1], "Hillary Clinton");
            værdi[1] = -35, fordeling[1] = -20;
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
        custom_candidates(candidates, candidate_name, værdi, fordeling);
    }
    if(*candidate_choice == 1) {
        *candidates = 5;
        strcpy(candidate_name[0], "Donald Trump");
        strcpy(candidate_name[1], "Barack Obama");
        strcpy(candidate_name[2], "Joe Biden");
        strcpy(candidate_name[3], "John F. Kennedy");
        strcpy(candidate_name[4], "Richard Nixon");
        værdi[0] = 50,      værdi[1] = -30,      værdi[2] = -15,       værdi[3] = 20,      værdi[4] = 60;
        fordeling[0] = 50,  fordeling[1] = -30,  fordeling[2] = -15,   fordeling[3] = 10,  fordeling[4] = 40;
    }
    if(*candidates < 2) {
        printf("There has to be at least 2 candidates");
        exit(EXIT_FAILURE);
    }
}


void check_input_validity(int user_input, int choice_amount) {
    if(user_input < 1 || user_input > choice_amount) {
        printf("Invalid input");
        exit(EXIT_FAILURE);
    }
}

void custom_candidates(int *candidates, char candidate_name[][MAX_NAME_LENGTH], int værdi[], int fordeling[]) {

    char name[MAX_NAME_LENGTH];

    for(*candidates = 0; *candidates < 5; (*candidates)++) {
        printf("Choose candidate name and position on political compass: [-100,100]\n");
        scanf("%s", &name);
        if(strcmp(name, "exit") == 0) return;
        strcpy(candidate_name[*candidates], name);

        scanf("%d %d", &værdi[*candidates], &fordeling[*candidates]);

        if(værdi[*candidates] < -100 || værdi[*candidates] > 100 || fordeling[*candidates] > 100 || fordeling[*candidates] < -100) {
            printf("Values out of range (-100,100)");
            exit(EXIT_FAILURE);
        }
    }
}