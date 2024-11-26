#include <stdio.h>
#include <stdlib.h>
#define STATE_MAX 51
#define POPULATION 1000
#define CANDIDATES 3

void voting_rcv(state, current_state, voter, voters_arr, candidate, candidate_arr) {
   //Initialiser kandidat stemmer, tæller op til 0
   for(int i = 0; i < CANDIDATES; i++) {
       candidate_arr[i].votes[0] = 0;
       candidate_arr[i].eliminated = 0;
   }


   //Første runde: Optæl første valgs stemmer
   for (int i = 0; i < current_state.voters_population; i++) {
       if (voters_arr[i].is_voting == 1) {
           int first_choice = voters_arr[i].rankings[0];  // The first-choice candidate
           candidate_arr[first_choice].votes[0]++;
       }
   }
}
int check_majority(candidate candidate_arr[], int total_voters) {
   for (int i = 0; i < CANDIDATES; i++) {
       if (candidate_arr[i].votes[0] > total_voters / 2) {
           return i;  // Vinderen fundet
       }
   }
   return -1;  // Ingen vinder endnu
}


int find_lowest_votes(candidate candidate_arr[]) {
   int min_votes = INT_MAX;
   int candidate_to_eliminate = -1;


   for (int i = 0; i < CANDIDATES; i++) {
       if (!candidate_arr[i].eliminated && candidate_arr[i].votes[0] < min_votes) {
           min_votes = candidate_arr[i].votes[0];
           candidate_to_eliminate = i;
       }
   }
   return candidate_to_eliminate;
}


void redistribute_votes(voter voters_arr[], candidate candidate_arr[], int eliminated_candidate) {
   for (int i = 0; i < POPULATION; i++) {
       if (voters_arr[i].is_voting == 1) {
           // Find den første ikke-eliminerede kandidat
           for (int j = 0; j < CANDIDATES; j++) {
               int ranked_candidate = voters_arr[i].rankings[j];
               if (ranked_candidate != eliminated_candidate && !candidate_arr[ranked_candidate].eliminated) {
                   // Giv kandidaten en stemme
                   candidate_arr[ranked_candidate].votes[0]++;
                   break;
               }
           }
       }
   }
}


void voting_rcv(state current_state, voter voters_arr[], candidate candidate_arr[]) {
   int total_voters = current_state.voters_population;
   int winner;


   // Loop indtil der er en vinder
   while (1) {
       // Reset stemmer for denne runde
       for (int i = 0; i < CANDIDATES; i++) {
           candidate_arr[i].votes[0] = 0;
       }


       // Første Runde
       for (int i = 0; i < current_state.voters_population; i++) {
           if (voters_arr[i].is_voting == 1) {
               int first_choice = voters_arr[i].rankings[0];  // The first-choice candidate
               candidate_arr[first_choice].votes[0]++;
           }
       }


       // Tjek om der er en flertals vinder
       winner = check_majority(candidate_arr, total_voters);
       if (winner != -1) {
           printf("Winner of RCV: %s\n", candidate_arr[winner].name);
           break;
       }


       // Find kandidaten med mindst stemmer og eliminer
       int eliminated_candidate = find_lowest_votes(candidate_arr);
       candidate_arr[eliminated_candidate].eliminated = 1;


       printf("Eliminating %s\n", candidate_arr[eliminated_candidate].name);


       // Redistribuer stemmer fra eliminerede kandidater
       redistribute_votes(voters_arr, candidate_arr, eliminated_candidate);


       // Tjek om der kun er en kandidat tilbage
       int remaining_candidates = 0;
       for (int i = 0; i < CANDIDATES; i++) {
           if (!candidate_arr[i].eliminated) {
               remaining_candidates++;
           }
       }
       if (remaining_candidates == 1) {
           for (int i = 0; i < CANDIDATES; i++) {
               if (!candidate_arr[i].eliminated) {
                   printf("Winner of RCV: %s\n", candidate_arr[i].name);
                   break;
               }
           }
           break;
       }
   }
}
