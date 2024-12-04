#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "functions.h"

int main() {

    srand(time(NULL));

    candidate candidate_arr[CANDIDATES];
    voter *voter_arr = malloc(sizeof(voter) * POPULATION);
    state *state_arr = malloc(sizeof(state) * STATES);
    if(voter_arr == NULL || state_arr == NULL) {
        printf("Error allocating memory\n");
        exit(EXIT_FAILURE);
    }

    init_state(state_arr);
    init_voters(state_arr, voter_arr);
    get_distance(voter_arr, candidate_arr, POPULATION);

    first_past_the_post(voter_arr, candidate_arr, state_arr[i].population);
    ranked_choice_voting();
    rated_voting();
    voting_star(state_arr, voter_arr, candidate_arr);

    print_winners();
    determine_fairness();

    free(voter_arr);
    free(state_arr);

    return 0;
}
