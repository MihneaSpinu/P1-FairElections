#include <assert.h>
#include <stdio.h>'
#include <stdlib.h>
#include <math.h>
#include <time.h>
#define DELTA 0.001

#include "functions.h"
void test_1();
void init_test(voter voter_arr[], candidate candidate_arr[]);
int are_floats_equal(float a, float b);
int main(void) {
    test_1();
    return 0;
}

void test_1() {
    state test_state;
    voter voter_arr[5];
    candidate candidate_arr[3];
    init_test(voter_arr, candidate_arr);
    get_distance(voter_arr, candidate_arr, 5, 3);
    assert(are_floats_equal(voter_arr[0].distance_to[0], 55.172f));
    assert(are_floats_equal(voter_arr[0].distance_to[1], 58.0f));
    assert(are_floats_equal(voter_arr[0].distance_to[2], 14.866f));
    assert(are_floats_equal(voter_arr[1].distance_to[0], 49.497f));
    assert(are_floats_equal(voter_arr[1].distance_to[1], 63.639f));
    assert(are_floats_equal(voter_arr[1].distance_to[2], 20.518f));
    assert(are_floats_equal(voter_arr[2].distance_to[0], 72.801f));
    assert(are_floats_equal(voter_arr[2].distance_to[1], 60.828f));
    assert(are_floats_equal(voter_arr[2].distance_to[2], 35.228f));
    assert(are_floats_equal(voter_arr[3].distance_to[0], 72.112f));
    assert(are_floats_equal(voter_arr[3].distance_to[1], 44.722f));
    assert(are_floats_equal(voter_arr[3].distance_to[2], 14.866f));
    assert(are_floats_equal(voter_arr[4].distance_to[0], 91.923f));
    assert(are_floats_equal(voter_arr[4].distance_to[1], 21.213f));
    assert(are_floats_equal(voter_arr[4].distance_to[2], 21.932f));

    int winner_fptp = first_past_the_post(voter_arr, 5, 0, &test_state,3);
    assert(winner_fptp == 2);
    int winner_ranked = ranked_choice_voting(5, voter_arr, candidate_arr, 0,&test_state,3);
    assert(winner_ranked == 2);
    int winner_rated = voting_rated(voter_arr, 5, 0, &test_state, 3);
    assert(winner_rated == 2);
    int winner_star = voting_star(5, voter_arr, candidate_arr, 0, &test_state, 3);
    assert(winner_star == 2);
    int cordocet_win_index = condorcet_winner(5, 3, voter_arr);
    printf("Index of cordocet winner %d", cordocet_win_index);
}

void init_test(voter voter_arr[], candidate candidate_arr[]) {
    voter_arr[0].værdipolitik_v = 12;
    voter_arr[1].værdipolitik_v = 15;
    voter_arr[2].værdipolitik_v = 30;
    voter_arr[3].værdipolitik_v = -10;
    voter_arr[4].værdipolitik_v = -15;
    voter_arr[0].fordelingspolitik_v = 10;
    voter_arr[1].fordelingspolitik_v = 15;
    voter_arr[2].fordelingspolitik_v = -20;
    voter_arr[3].fordelingspolitik_v = 10;
    voter_arr[4].fordelingspolitik_v = -15;
    candidate_arr[0].fordelingspolitik_c = 50;
    candidate_arr[1].fordelingspolitik_c = -30;
    candidate_arr[2].fordelingspolitik_c = 0;
    candidate_arr[0].værdipolitik_c = 50;
    candidate_arr[1].værdipolitik_c = -30;
    candidate_arr[2].værdipolitik_c = 1;
}
int are_floats_equal(float a, float b) {
    // Compare the absolute difference with the threshold
    return fabs((double)a - (double)b) < DELTA;
}
