#include <stdio.h>
#include <limits.h>
#include "functions.h"

// Run the first past the post voting system
int first_past_the_post(voter voter_arr[], candidate candidate_arr[], int total_voters, int current_i_voter, state *current_state) {
    int votes_can[CANDIDATES];
    for (int i = 0; i < CANDIDATES; i++) {
        votes_can[i] = 0;
    }
    // Loop through all voters
    for (int i = current_i_voter; i < total_voters + current_i_voter; i++) {
        // Check if the voter is voting
        if (voter_arr[i].is_voting) {
            // Find the candidate with the smallest distance to the voter
            int min_distance = INT_MAX;
            int candidate_index = -1;

            // Loop through all candidates
            for (int j = 0; j < CANDIDATES; j++) {
                // Check if the candidate is eliminated
                if (voter_arr[i].distance_to_[j] < min_distance) {
                    // Update the candidate with the smallest distance
                    min_distance = voter_arr[i].distance_to_[j];
                    candidate_index = j;
                }
            }

            // Increment the votes for the candidate
            if (candidate_index != -1) {
                votes_can[candidate_index]++;
                current_state->candidate_votes_fptp[candidate_index]++;
            }
        }
    }
    int winner = 0;
    for (int i = 0; i < CANDIDATES; i++) {
        //printf("Candidate %s has %d votes\n", candidate_arr[i].name, votes_can[i]);
        //printf("Candidate %s has %d votes\n", candidate_arr[winner].name, votes_can[winner]);
        if(votes_can[i] > votes_can[winner]) {
            winner = i;
        }
    }
    return winner;
}


/*
int main() {
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
        candidate_arr[i].votes_fptp = 0;
    }

    // Run the first past the post voting system
    first_past_the_post(voters_arr, candidate_arr, total_voters);

    // Print the results
    for (int i = 0; i < total_candidates; i++) {
        printf("Candidate %d: %s, Votes: %d\n", i + 1, candidate_arr[i].name, candidate_arr[i].votes_fptp);
    }

    return 0;
}
*/

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
