#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "functions.h"

void start_fptp_voting(state state_arr[], voter voters_arr[], candidate candidate_arr[])
{
    for (int i = 0; i < STATES; i++)
    {
        state current_state = state_arr[i];
        voting_fptp(current_state, voters_arr, candidate_arr);
    }
    candidate winner = find_winner_fptp(candidate_arr);
    print_results(winner);
}

void voting_fptp(state current_state, voter voters_arr[], candidate candidate_arr[])
{
    for (int i = 0; i < current_state.population; i++)
    {
            int vote = rand() % CANDIDATES;
            candidate_arr[vote].votes_fptp++;
    }
}

candidate find_winner_fptp(candidate candidate_arr[])
{
    candidate winner = candidate_arr[0];
    for (int i = 1; i < CANDIDATES; i++)
    {
        if (candidate_arr[i].votes_fptp > winner.votes_fptp)
        {
            winner = candidate_arr[i];
        }
    }
    return winner;
}

void print_results(candidate winner)
{
    printf("The winner is: %s\n", winner.name);
    printf("Votes: %d\n", winner.votes_fptp);
}





/*
 * Mine varianter til test
 *
 *
int main(void)
{
    srand(time(NULL)); // Seed the random number generator

    state state_arr[STATE_MAX];
    voter voters_arr[POPULATION];
    candidate candidate_arr[CANDIDATES];

    // Initialize states, voters, and candidates
    init_state(state_arr);
    init_voters(voters_arr);
    init_candidates(candidate_arr);

    // Simulate voting in the first state
    voting_fptp(state_arr[0], voters_arr, candidate_arr);

    // Find and print the winner
    candidate winner = find_winner_fptp(candidate_arr);
    print_results(winner); // Print the winner
    print_test(candidate_arr); // Print all candidates and their votes

return 0;
}

void print_test(candidate candidate_arr[])
{
    for (int i = 0; i < CANDIDATES; i++)
    {
        printf("Candidate: %s, Votes: %d\n", candidate_arr[i].name, candidate_arr[i].votes_fptp);
    }
}

void init_state(state state_arr[])
{
    for (int i = 0; i < STATE_MAX; i++)
    {
        state_arr[i].votes_fptp = 0;
        state_arr[i].voters_population = POPULATION; // Set the population for each state
        state_arr[i].electoral_mandates = 0;
    }
}

void init_voters(voter voters_arr[])
{
    for (int i = 0; i < POPULATION; i++)
    {
        voters_arr[i].age = rand() % 83 + 18;
        voters_arr[i].gender_v = rand() % 2;
        voters_arr[i].race_v = rand() % 5; // Assuming 5 races
        voters_arr[i].income = rand() % 3;
        voters_arr[i].is_voting = rand() % 2;
        voters_arr[i].værdipolitik_v = rand() % 3;
        voters_arr[i].fordelingspolitik_v = rand() % 3;
    }
}

void init_candidates(candidate candidate_arr[])
{
    for (int i = 0; i < CANDIDATES; i++)
    {
        candidate_arr[i].votes_fptp = 0;
        snprintf(candidate_arr[i].name, sizeof(candidate_arr[i].name), "Candidate %d", i + 1);
        candidate_arr[i].værdipolitik_c = rand() % 3;
        candidate_arr[i].fordelingspolitik_c = rand() % 3;
    }
}
*/
