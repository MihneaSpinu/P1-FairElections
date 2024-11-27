#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "functions.h"

int main(void)
{
    srand(time(NULL));
    //fair elections
    //Initialize state (by attributes)
    /*
    state state_array[STATE_MAX];
    init_state(state_array);
    /*for (int i = 0; i < STATE_MAX; i++)
    {
        printf("%s %d %d\n", state_array[i].name, state_array[i].voters_population, state_array[i].electoral_mandates);
    }
    */

    //Initialize voters (by attributes) (political compass)
    voter voters_array[POPULATION];
    init_voters(voters_array);

    /*
    //Initialize candidates (by attributes)

    //Initialize voters (by attributes) (political compass)

    for (int i = 0; i < POPULATION; i++)
    {
        printf("G: %d A: %d I: %d R: %d\n", voters_array[i].gender_v, voters_array[i].age_v,
               voters_array[i].income_v, voters_array[i].race_v);
    }

    //Initialize candidates(by attributes)
    candidate candidate_array[CANDIDATES];
    init_candidates(candidate_array);

    //for-loop
    //for each state
    for (int i = 0; i < STATE_MAX; i++)
    {
        //collect votes from each state do it for each voting system
        state current_state = state_array[i];
        voting_fptp(current_state, voters_array, candidate_array);
        voting_star(current_state, voters_array, candidate_array);
        voting_rated(current_state, voters_array, candidate_array);
        voting_rcv(current_state, voters_array, candidate_array);
    }

    //for each voting system
    //find the winner of each
    for (int i = 0; i < 4; i++)
    {
        candidate winner_fptp = find_winner_fptp();
        candidate winner_star = find_winner_star();
        candidate winner_rated = find_winner_rated();
        candidate winner_rcv = find_winner_rcv();
    }

    candidate* candidate_arr = 0;
    voter* voters_arr = 0;
    int total_voters = 0;
    int eliminated_candidate = 0;
    start_ranked_voting(candidate_arr, voters_arr, total_voters,eliminated_candidate);

    //start_fptp_voting(state_array, voters_array, candidate_array);

    //show the result of the vote
    print_results();
    */

    return 0;
}
