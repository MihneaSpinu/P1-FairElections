#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "functions.h"


int main()
{
    srand(time(NULL));

    int distance;
    int attribute[7];
    for (int i = 0; i < 7; i++)
    {
        attribute[i] = i;
    }

    candidate candidate_array[CANDIDATES];
    state state_array[STATES];

    FILE* fil;
    state current_state;

    voter* voters_arr = malloc(sizeof(voter) * POPULATION);

    // Initialiserer politisk kompas til midten for alle vælgere
    for (int i = 0; i < POPULATION; i++)
    {
        voters_arr[i].fordelingspolitik_v = 0;
        voters_arr[i].værdipolitik_v = 0;
    }

    for (int i = 0; i < STATES; i++)
    {
        init_state(state_array);
        init_voters(current_state, voters_arr, attribute);

        calculate_distance();

        first_past_the_post();
        ranked_choice_voting();
        rated_voting();
        voting_star();
    }

    /*print_winners();*/
    free(voters_arr);

    return 0;
}
