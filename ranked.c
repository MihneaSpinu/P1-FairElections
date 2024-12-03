#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "functions.h"

void start_ranked_voting(candidate candidate_arr[], voter voters_arr[],int total_voters,int eliminated_candidate)
{
    check_majority(candidate_arr, total_voters);
    find_lowest_votes(candidate_arr);
    redistribute_votes( voters_arr, candidate_arr, eliminated_candidate);
    reset_votes(candidate_arr);
}

// Reset stemmer for kandidater
void reset_votes(candidate candidate_arr[])
{
    for (int i = 0; i < CANDIDATES; i++)
    {
        candidate_arr[i].votes_rcv = 0;
    }
}

// Ranked Choice Voting (RCV) funktion
void voting_rcv(state current_state, voter voters_arr[], candidate candidate_arr[])
{
    int total_voters = current_state.population;
    int winner;

    // Loop indtil der er en vinder
    while (1)
    {
        reset_votes(candidate_arr);

        // Første runde: Tæl første valgstemmer
        for (int i = 0; i < total_voters; i++)
        {
            if (voters_arr[i].is_voting == 1)
            {
                int first_choice = voters_arr[i].rankings[0]; // Første valg
                candidate_arr[first_choice].votes_rcv++;
            }
        }

        // Tjek om der er en flertalsvinder
        winner = check_majority(candidate_arr, total_voters);
        if (winner != -1)
        {
            printf("Winner of RCV: %s\n", candidate_arr[winner].name);
            break;
        }

        // Find kandidaten med mindst stemmer og eliminér den
        int eliminated_candidate = find_lowest_votes(candidate_arr);
        candidate_arr[eliminated_candidate].eliminated = 1;
        printf("Eliminating %s\n", candidate_arr[eliminated_candidate].name);

        // Redistribuer stemmer fra eliminerede kandidater
        redistribute_votes(voters_arr, candidate_arr, eliminated_candidate);

        // Tjek om der kun er én kandidat tilbage
        int remaining_candidates = 0;
        for (int i = 0; i < CANDIDATES; i++)
        {
            if (!candidate_arr[i].eliminated)
            {
                remaining_candidates++;
            }
        }
        if (remaining_candidates == 1)
        {
            for (int i = 0; i < CANDIDATES; i++)
            {
                if (!candidate_arr[i].eliminated)
                {
                    printf("Winner of RCV: %s\n", candidate_arr[i].name);
                    break;
                }
            }
            break;
        }
    }
}

// Tjek om der er en flertalsvinder
int check_majority(candidate candidate_arr[], int total_voters)
{
    for (int i = 0; i < CANDIDATES; i++)
    {
        if (candidate_arr[i].votes_rcv > total_voters / 2)
        {
            return i; // Vinderen fundet
        }
    }
    return -1; // Ingen vinder endnu
}

// Find kandidat med færrest stemmer
int find_lowest_votes(candidate candidate_arr[])
{
    int min_votes = INT_MAX;
    int candidate_to_eliminate = -1;

    for (int i = 0; i < CANDIDATES; i++)
    {
        if (!candidate_arr[i].eliminated && candidate_arr[i].votes_rcv < min_votes)
        {
            min_votes = candidate_arr[i].votes_rcv;
            candidate_to_eliminate = i;
        }
    }
    return candidate_to_eliminate;
}

// Redistribuer stemmer fra eliminerede kandidater
void redistribute_votes(voter voters_arr[], candidate candidate_arr[], int eliminated_candidate)
{
    for (int i = 0; i < POPULATION; i++)
    {
        if (voters_arr[i].is_voting == 1)
        {
            for (int j = 0; j < CANDIDATES; j++)
            {
                int ranked_candidate = voters_arr[i].rankings[j];
                if (ranked_candidate != eliminated_candidate && !candidate_arr[ranked_candidate].eliminated)
                {
                    candidate_arr[ranked_candidate].votes_rcv++;
                    break;
                }
            }
        }
    }
}




/*
 *int main(void) {
    state state_array[STATE_MAX];
    init_state(state_array);

    // Initialize voters
    srand(time(NULL));
    voter voters_array[POPULATION];
    init_voters(voters_array);

    // Initialize candidates
    candidate candidate_array[CANDIDATES];
    init_candidates(candidate_array);

    // Loop for each state and voting system
    for (int i = 0; i < STATE_MAX; i++) {
        state current_state = state_array[i];

        // Call RCV for the current state
        voting_rcv(current_state, voters_array, candidate_array);
    }

    return 0;
}
*/

/*
// Initialisering af state data
void init_state(state state_arr[])
{
    // Placeholder for at indlæse data fra fil
    for (int i = 0; i < STATE_MAX; i++)
    {
        sprintf(state_arr[i].name, "State_%d", i + 1);
        state_arr[i].voters_population = POPULATION;
        state_arr[i].electoral_mandates = 10; // Eksempelværdi
    }
}

// Initialisering af vælgere
void init_voters(voter voters_arr[])
{
    // Initialisering af vælgere med tilfældige værdier
    for (int i = 0; i < POPULATION; i++)
    {
        voters_arr[i].is_voting = rand() % 2; // 0 = not voting, 1 = voting
        for (int j = 0; j < CANDIDATES; j++)
        {
            voters_arr[i].rankings[j] = rand() % CANDIDATES; // Randomize rankings for candidates
        }
    }
}

// Initialisering af kandidater
void init_candidates(candidate candidate_arr[])
{
    const char* names[] = {"Donald Trump", "Kamala Harris", "Robert F. Kennedy"};
    double values[] = {-4.0, 3.0, -1.0};

    for (int i = 0; i < CANDIDATES; i++)
    {
        strcpy(candidate_arr[i].name, names[i]);
        candidate_arr[i].værdipolitik_c = values[i];
        candidate_arr[i].fordelingspolitik_c = values[i];
        candidate_arr[i].votes_rcv = 0;
        candidate_arr[i].eliminated = 0;
    }
}
*/