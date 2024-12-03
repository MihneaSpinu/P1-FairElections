#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "functions.h"

int main() {

    srand(time(NULL));

    int attribute[7];
    for(int i = 0; i < 7; i++) {
        attribute[i] = i;
    }

    candidate candidate_arr[CANDIDATES];
    state state_arr[STATES];
    state current_state;

    voter *voter_arr = malloc(sizeof(voter) * POPULATION);

    // Initialiserer politisk kompas til midten for alle vælgere
    for(int i = 0; i < POPULATION; i++) {
        voter_arr[i].fordelingspolitik_v = 0;
        voter_arr[i].værdipolitik_v = 0;
    }

    for(int i = 0; i < STATES; i++) {

        init_state(state_arr);
        init_voters(current_state, voter_arr, attribute);

        get_distance(voter_arr, candidate_arr, current_state.population);

        /*
        first_past_the_post();
        ranked_choice_voting();
        rated_voting();
        star_voting();
        */
    }

    /*print_winners();*/
    free(voter_arr);

    return 0;
}
