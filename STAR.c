#include <stdlib.h>
#include "functions.h"


int voting_star(int population, voter voter_arr[], candidate candidate_arr[],
                int start_index, state *current_state, int num_of_candidates) {

    // Initialize scores for each candidate
    int *scores = calloc(num_of_candidates, sizeof(int));
    check_memory_allocation(scores);

    // Calculate scores based on distances
    for (int i = start_index; i < population + start_index; i++) {
        for (int j = 0; j < num_of_candidates; j++) {
            scores[j] += voter_arr[i].ratings[j];
        }
    }

    // Find the top two candidates
    int top1 = 0, top2 = 1;
    if (scores[top2] > scores[top1]) {
        top1 = 1;
        top2 = 0;
    }

    for (int i = 2; i < num_of_candidates; i++) {
        if (scores[i] > scores[top1]) {
            top2 = top1;
            top1 = i;
        } else if (scores[i] > scores[top2]) {
            top2 = i;
        }
    }

    // Runoff between top two candidates (fptp)
    int votes_top1 = 0, votes_top2 = 0;
    for (int i = start_index; i < start_index + population; i++) {
        if (voter_arr[i].distance_to[top1] < voter_arr[i].distance_to[top2]) {
            votes_top1++;
            current_state->candidate_votes_star[top1]++;
        } else {
            votes_top2++;
            current_state->candidate_votes_star[top2]++;
        }
    }

    // Determine the winner
    int winner_index = (votes_top1 > votes_top2) ? top1 : top2;
    candidate winner = candidate_arr[winner_index];
    winner.votes_star = (votes_top1 > votes_top2) ? votes_top1 : votes_top2;

    free(scores);
    return winner_index;
}
