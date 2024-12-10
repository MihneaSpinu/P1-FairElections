#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "functions.h"

void scan_election_settings(int *simulation_choice, int *electoral_choice, int *candidate_choice,
                            int *voting_system_choice, int *candidates) {

    char candidate_name[MAX_CANDIDATES][MAX_NAME_LENGTH];
    char name[MAX_NAME_LENGTH];
    int værdi[MAX_CANDIDATES];
    int fordeling[MAX_CANDIDATES];

    printf("1) Run 2024 election\n2) Run custom election\n");
    scanf("%d", simulation_choice);
    check_input_validity(*simulation_choice);
    if(*simulation_choice == 1) {
        return;
    }

    printf("\n1) Determine winner by electoral college\n2) Determine winner by national popular vote\n");
    scanf("%d", electoral_choice);
    check_input_validity(*electoral_choice);

    printf("\n1) Use current US voting system\n2) Use different voting systems\n");
    scanf("%d", voting_system_choice);
    check_input_validity(*voting_system_choice);

    printf("\n1) Use preset candidates\n2) Add your own candidates\n");
    scanf("%d", candidate_choice);
    check_input_validity(*candidate_choice);
    if(*candidate_choice == 2) {
        custom_candidates(&candidates, candidate_name, værdi, fordeling);
    }


    if(*simulation_choice == 1) {
        *candidates = 2;
        strcpy(candidate_name[0], "Donald Trump");
        strcpy(candidate_name[1], "Kamala Harris");
        værdi[0] = 25,      værdi[1] = 30;
        fordeling[0] = 25,  fordeling[1] = 20;
    } else if(*simulation_choice == 2) {
        *candidates = 5;
        strcpy(candidate_name[0], "Donald Trump");
        strcpy(candidate_name[1], "Kamala Harris");
        strcpy(candidate_name[2], "Robert F. Kennedy");
        strcpy(candidate_name[3], "Elon Musk");
        strcpy(candidate_name[4], "Kanye West");
        værdi[0] = 25,      værdi[1] = 30,      værdi[2] = 0,       værdi[3] = 50,      værdi[4] = -20;
        fordeling[0] = 25,  fordeling[1] = 20,  fordeling[2] = 0,   fordeling[3] = 50,  fordeling[4] = -20;
    } else if(*simulation_choice == 3) {

        for(*candidates = 0; *candidates < 5; *candidates++) {
            printf("Choose candidate name and position on political compass: (-100,100)\n");
            scanf("%s", &name);
            if(strcmp(name, "exit") == 0) {
                break;
            }
            strcpy(candidate_name[*candidates], name);
            scanf("%d %d", &værdi[*candidates], &fordeling[*candidates]);

            if(værdi[*candidates] < -100 || værdi[*candidates] > 100 || fordeling[*candidates] > 100 || fordeling[*candidates] < -100) {
                printf("Values out of range (-100,100)");
                exit(EXIT_FAILURE);
            }
        }
        if(*candidates < 2) {
            printf("There has to be at least 2 candidates");
            exit(EXIT_FAILURE);
        }

    } else {
        printf("Invalid input");
        exit(EXIT_FAILURE);
    }
}


void check_input_validity(int user_input) {
    if(user_input != 1 && user_input != 2) {
        printf("Invalid input");
        exit(EXIT_FAILURE);
    }
}

void custom_candidates(int *candidates, char candidate_name[][MAX_NAME_LENGTH], int værdi[], int fordeling[]) {

    char name[MAX_NAME_LENGTH];

    for(*candidates = 0; *candidates < 5; *candidates++) {
        printf("Choose candidate name and position on political compass: (-100,100)\n");
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