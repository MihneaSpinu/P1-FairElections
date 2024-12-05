// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <time.h>
//
// #include "functions.h"
//
// void start_ranked_voting(candidate candidate_arr[], voter voter_arr[], int total_voters, int eliminated_candidate) {
//
//     check_majority(candidate_arr, total_voters);
//     find_lowest_votes(candidate_arr);
//     redistribute_votes(voter_arr, candidate_arr, eliminated_candidate);
//     reset_votes(candidate_arr);
// }
//
// // Reset stemmer for kandidater
// void reset_votes(candidate candidate_arr[])
// {
//     for (int i = 0; i < CANDIDATES; i++)
//     {
//         candidate_arr[i].votes_rcv = 0;
//     }
// }
//
// // Ranked Choice Voting (RCV) funktion
// void voting_rcv(state state_arr[], voter voter_arr[], candidate candidate_arr[]) {
//
//     int total_voters = state_arr[i].population; // kan kaldes med population
//     int winner;
//
//     // Loop indtil der er en vinder
//     while (1) {
//         reset_votes(candidate_arr);
//
//         // Første runde: Tæl første valgstemmer
//         for (int i = 0; i < total_voters; i++) {
//             if (voter_arr[i].is_voting == 1) {
//                 int first_choice = voter_arr[i].distance_to_[0]; // Første valg
//                 candidate_arr[first_choice].votes_rcv++;
//             }
//         }
//
//         // Tjek om der er en flertalsvinder
//         winner = check_majority(candidate_arr, total_voters);
//         if (winner != -1) {
//             printf("Winner of RCV: %s\n", candidate_arr[winner].name);
//             break;
//         }
//
//         // Find kandidaten med mindst stemmer og eliminér den
//         int eliminated_candidate = find_lowest_votes(candidate_arr);
//         candidate_arr[eliminated_candidate].eliminated = 1;
//         printf("Eliminating %s\n", candidate_arr[eliminated_candidate].name);
//
//         // Redistribuer stemmer fra eliminerede kandidater
//         redistribute_votes(voter_arr, candidate_arr, eliminated_candidate);
//
//         // Tjek om der kun er én kandidat tilbage
//         int remaining_candidates = 0;
//         for (int i = 0; i < CANDIDATES; i++) {
//             if (!candidate_arr[i].eliminated) {
//                 remaining_candidates++;
//             }
//         }
//         if (remaining_candidates == 1) {
//             for (int i = 0; i < CANDIDATES; i++) {
//                 if (!candidate_arr[i].eliminated) {
//                     printf("Winner of RCV: %s\n", candidate_arr[i].name);
//                     break;
//                 }
//             }
//             break;
//         }
//     }
// }
//
// // Tjek om der er en flertalsvinder
// int check_majority(candidate candidate_arr[], int total_voters) {
//
//     for (int i = 0; i < CANDIDATES; i++) {
//         if (candidate_arr[i].votes_rcv > total_voters / 2) {
//             return i; // Vinderen fundet
//         }
//     }
//     return -1; // Ingen vinder endnu
// }
//
// // Find kandidat med færrest stemmer
// int find_lowest_votes(candidate candidate_arr[]) {
//
//     int min_votes = INT_MAX;
//     int candidate_to_eliminate = -1;
//
//     for (int i = 0; i < CANDIDATES; i++) {
//         if (!candidate_arr[i].eliminated && candidate_arr[i].votes_rcv < min_votes) {
//             min_votes = candidate_arr[i].votes_rcv;
//             candidate_to_eliminate = i;
//         }
//     }
//     return candidate_to_eliminate;
// }
//
// // Redistribuer stemmer fra eliminerede kandidater
// void redistribute_votes(voter voter_arr[], candidate candidate_arr[], int eliminated_candidate) {
//
//     for (int i = 0; i < POPULATION; i++) {
//         if (voter_arr[i].is_voting == 1) {
//             for (int j = 0; j < CANDIDATES; j++) {
//                 int ranked_candidate = voter_arr[i].distance_to_[j];
//                 if (ranked_candidate != eliminated_candidate && !candidate_arr[ranked_candidate].eliminated) {
//                     candidate_arr[ranked_candidate].votes_rcv++;
//                     break;
//                 }
//             }
//         }
//     }
// }
//
