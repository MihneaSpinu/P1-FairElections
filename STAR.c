#include <stdio.h>
#include <stdlib.h>
#include "functions.h"

void voting_star(state current_state, voter voters_arr[], candidate candidate_arr[])
{
    // Initialize scores for each candidate
    int scores[CANDIDATES] = {0};

    // Calculate scores based on distances
    for (int i = 0; i < current_state.population; i++)
    {
        for (int j = 0; j < CANDIDATES; j++)
        {
            scores[j] += (10 - voters_arr[i].distance_to_[j]); // Assuming distance is from 0 to 10
        }
    }

    // Find the top two candidates
    int top1 = 0, top2 = 1;
    if (scores[top2] > scores[top1])
    {
        top1 = 1;
        top2 = 0;
    }
    for (int i = 2; i < CANDIDATES; i++)
    {
        if (scores[i] > scores[top1])
        {
            top2 = top1;
            top1 = i;
        }
        else if (scores[i] > scores[top2])
        {
            top2 = i;
        }
    }

    // Runoff between top two candidates
    int votes_top1 = 0, votes_top2 = 0;
    for (int i = 0; i < current_state.population; i++)
    {
        if (voters_arr[i].distance_to_[top1] < voters_arr[i].distance_to_[top2])
        {
            votes_top1++;
        }
        else
        {
            votes_top2++;
        }
    }

    // Determine the winner
    candidate winner = (votes_top1 > votes_top2) ? candidate_arr[top1] : candidate_arr[top2];
    winner.votes_star = (votes_top1 > votes_top2) ? votes_top1 : votes_top2;
    print_results(winner);
}

void star_voting(state state_arr[], voter voters_arr[], candidate candidate_arr[])
{
    for (int i = 0; i < STATES; i++)
    {
        voting_star(state_arr[i], voters_arr, candidate_arr);
    }
}

void print_results(candidate winner)
{
    printf("The winner is: %s\n", winner.name);
    printf("Votes: %d\n", winner.votes_star);
}


/*
int main() {
    srand(time(NULL)); // Seed the random number generator

    // Define the number of voters and candidates
    int total_voters = 10000;
    int total_candidates = CANDIDATES;

    // Initialize voters
    voter voters_arr[total_voters];
    for (int i = 0; i < total_voters; i++) {
        voters_arr[i].is_voting = 1; // All voters are voting
        for (int j = 0; j < total_candidates; j++) {
            voters_arr[i].distance_to_[j] = rand() % 11; // Random distances between 0 and 10
        }
    }

    // Initialize candidates
    candidate candidate_arr[total_candidates];
    for (int i = 0; i < total_candidates; i++) {
        snprintf(candidate_arr[i].name, sizeof(candidate_arr[i].name), "Candidate %d", i + 1);
        candidate_arr[i].votes_star = 0;
    }

    // Initialize states
    state state_arr[STATES];
    for (int i = 0; i < STATES; i++) {
        state_arr[i].population = total_voters;
    }

    // Run the STAR voting system
    voting_star(*state_arr, voters_arr, candidate_arr);

    return 0;
}
*/
