#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define STATE_MAX 51
#define POPULATION 10000
#define CANDIDATES 3

/*
// Her laver jeg listen til stemmerne og rækkefølgen
typedef struct
{
    age age_v;
    gender gender_v;
    race race_v;
    income income_v;
    int is_voting; //0 = De stemmer ikke, 1 = stemmer
    double værdipolitik_v;
    double fordelingspolitik_v;
    int ranked_prefences[CANDIDATES]; //Indeks af kandidater i præferencerækkefølge
} voter;


//Nu vil jeg lave funktionen til at genere alle vælgernes præferencer
void generate_ranked_preferences(voter *v, candidate candidate_arr[]) {
    double distances[CANDIDATES];
    for(int i = 0; i < CANDIDATES; i++) {
        distances[i] = fabs(v->værdipolitik_v - candidate_arr[i].værdipolitik_v) + fabs(
                           v->fordelingspolitik_v - candidate_arr[i].fordelingspolitik_v);
    }
    int ranked[CANDIDATES] = {0, 1, 2};
    for (int i = 0; i < CANDIDATES - 1; i++) {
        for(int j = 0; j < CANDIDATES - i - 1; j++) {
            if(distances[ranked[j]] > distances[ranked[j + 1]]) {
                int temp = ranked[j];
                ranked[j] = ranked[j + 1];
                ranked[j + 1] = temp;
            }
        }
    }
    for(int i = 0; i < CANDIDATES; i++) {
        v->rannked_preferences[i] = ranked[i];
    }
}

//Nu skaber jeg hovedfunktionen for RCV
void voting_rcv(state current_state, voter voters_arr[], candidate candidate_arr[]) {
    int active_candidates[CANDIDATES];
    for(int i = 0; i < CANDIDATES; i++) {
        active_candidates[i] = 1; //Sørger for alle kandidater er aktive fra starten
    }
    int total_votes[CANDIDATES] = {0}; //Sørger for alle kandidater started med 0 stemmer
    int majority = current_state.voters_population / 2;

    while(1) {
        memset(total_votes, 0, sizeof(total_votes)); //Nulstiller stemmeoptællingen

        //Førstevalgs stemmer
        for(int i = 0; i < POPULATION; i++) {
            if(!voters_arr[i].is_voting) continue;

            for(int j = 0; j < CANDIDATES; j++) {
                int choice = voters_arr[i].ranked_preferences[j];
                if(active_candidates[choice]) {
                    total_votes[choice]++;
                    break;
                }
            }
        }
        //Tjekker kort om en kandidat har flertal
        for(int i = 0; i < CANDIDATES; i++) {
            if(total_votes[i] > majority) {
                candidate_arr[i].votes_rcv++;
                printf("Winner %s with %d votes/n", candidate_arr[i].name, total_votes[i]);
            }
        }
        //Hvis ingen flertal så fjerne vi kandidaten med færrest stemmer
        int min_votes = INT_MAX, min_candidate = -1;
        for(int i = 0; i < CANDIDATES; i++) {
            if(active_candidates[i] && total_votes[i] < min_votes) {
                min_votes = total_votes[i];
                min_candidate = i;
            }
        }
        if(min_candidate != -1) {
            active_candidates[min_candidate] = 0;
            printf("Eliminating: %s/n", candidate_arr[min_candidate].name);
        }
    }

}
*/

/*Her er koden til at implementere min fil i main
voting_rcv(current_state, voters_array, candidate_array);
*/