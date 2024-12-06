#include <stdio.h>
#include "functions.h"

int voting_star(int current_state_population, voter voter_arr[], candidate candidate_arr[], int current_i_voter) {

    // Initialize scores for each candidate
    int scores[CANDIDATES] = {0};

    // Calculate scores based on distances
    for (int i = current_i_voter; i < current_state_population + current_i_voter; i++) {
        for (int j = 0; j < CANDIDATES; j++) {
            scores[j] += (100 - voter_arr[i].distance_to_[j]); // Assuming distance is from 0 to 10
        }
    }

    // Find the top two candidates
    int top1 = 0, top2 = 1;
    if (scores[top2] > scores[top1]) {
        top1 = 1;
        top2 = 0;
    }

    for (int i = 2; i < CANDIDATES; i++) {
        if (scores[i] > scores[top1]) {
            top2 = top1;
            top1 = i;
        } else if (scores[i] > scores[top2]) {
            top2 = i;
        }
    }

    // Runoff between top two candidates
    int votes_top1 = 0, votes_top2 = 0;
    for (int i = current_i_voter; i < current_i_voter + current_state_population; i++) {
        if (voter_arr[i].distance_to_[top1] < voter_arr[i].distance_to_[top2]) {
            votes_top1++;
        } else {
            votes_top2++;
        }
    }

    // Determine the winner
    int winner_index = (votes_top1 > votes_top2) ? top1 : top2;
    candidate winner = candidate_arr[winner_index];
    winner.votes_star = (votes_top1 > votes_top2) ? votes_top1 : votes_top2;
    //print_results(winner);
    return winner_index;

}

void print_results(candidate winner) {
    printf("The winner is: %s\n", winner.name);
    printf("Votes: %d\n", winner.votes_star);
}