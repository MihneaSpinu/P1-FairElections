#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "functions.h"

int main() {

    srand(time(NULL));

    int distance;
    int attribute[7];
    for(int i = 0; i < 7; i++) {
        attribute[i] = i;
    }

    candidate candidate_array[CANDIDATES];
    state state_array[STATES];

    FILE *fil;
    state current_state;

    voter *voters_arr = malloc(sizeof(voter) * POPULATION);

    for(int i = 0; i < STATES; i++) {


        init_state(state_array);
        init_voters(current_state, voters_arr, attribute);

        /*
        political_compass();
        calculate_distance();

        first_past_the_post();
        ranked_choice_voting();
        rated_voting();
        star_voting();
        */

    }

    /*print_winners();*/
    free(voters_arr);

    return 0;
}

