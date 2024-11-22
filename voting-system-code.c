// Waiting to be implemented in the main program
// Commented out for now

/*
 *
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define STATE_MAX 50
#define POPULATION 1000
#define CANDIDATES 10

/**
 * Struct representing a voter.
 #1#
typedef struct
{
    int age; // Age of the voter (18-100)
    int gender_v; // Gender of the voter (0=male, 1=female)
    int race_v; // Race of the voter
    int income; // Income level of the voter (0=low, 1=middle, 2=high)
    int is_voting; // Voting status (0=not voting, 1=voting)
    int værdipolitik_v; // Value politics preference
    int fordelingspolitik_v; // Distribution politics preference
} voter;

/**
 * Struct representing a candidate.
 #1#
typedef struct
{
    char name[25]; // Name of the candidate
    int værdipolitik_c; // Value politics stance
    int fordelingspolitik_c; // Distribution politics stance
    int votes_fptp; // Number of votes received in First-Past-The-Post system
} candidate;

/**
 * Struct representing a state.
 #1#
typedef struct
{
    int votes_fptp; // Total votes in First-Past-The-Post system
    int voters_population; // Population of voters in the state
    int electoral_mandates; // Number of electoral mandates
} state;

/**
 * Initialize states with default values.
 * @param state_arr Array of states to initialize
 #1#
void init_state(state state_arr[]);

/**
 * Initialize voters with random values.
 * @param voters_arr Array of voters to initialize
 #1#
void init_voters(voter voters_arr[]);

/**
 * Initialize candidates with default names and random values.
 * @param candidate_arr Array of candidates to initialize
 #1#
void init_candidates(candidate candidate_arr[]);

/**
 * Simulate voting in a state using First-Past-The-Post system.
 * @param current_state The state where voting is simulated
 * @param voters_arr Array of voters participating in the election
 * @param candidate_arr Array of candidates participating in the election
 #1#
void voting_fptp(state current_state, voter voters_arr[], candidate candidate_arr[]);

/**
 * Find the winner of the election using First-Past-The-Post system.
 * @param candidate_arr Array of candidates
 * @return The winning candidate
 #1#
candidate find_winner_fptp(candidate candidate_arr[]);

/**
 * Print the election results.
 * @param winner The winning candidate
 #1#
void print_results(candidate winner);

/**
 * Print all candidates and their votes.
 * @param candidate_arr Array of candidates
 #1#
void print_test(candidate* candidate_arr);

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

void voting_fptp(state current_state, voter voters_arr[], candidate candidate_arr[])
{
    for (int i = 0; i < current_state.voters_population; i++)
    {
        if (voters_arr[i].is_voting == 1)
        {
            int vote = rand() % CANDIDATES;
            candidate_arr[vote].votes_fptp++;
        }
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

void print_test(candidate candidate_arr[])
{
    for (int i = 0; i < CANDIDATES; i++)
    {
        printf("Candidate: %s, Votes: %d\n", candidate_arr[i].name, candidate_arr[i].votes_fptp);
    }
}

void print_results(candidate winner)
{
    printf("The winner is: %s\n", winner.name);
    printf("Votes: %d\n", winner.votes_fptp);
}

*/

