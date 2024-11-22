#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define STATE_MAX 51
#define POPULATION 1000
#define CANDIDATES 3
typedef enum {white, black, hispanic, asian, native_american, native_hawaiian, other} race;
typedef enum {male, female} gender;

//struct for voters
typedef struct {
    int age; // 18-100
    gender gender_v; // 0=male, 1=female
    race race_v;
    int income;//by level: 0 = low, 1 = middle, 2 = high
    int is_voting; //0 = not voting, 1 = voting
    //politics:
    double værdipolitik_v; // Value politics?/policy?
    double fordelingspolitik_v;// Distribution Politics?/policy?
}voter;
//struct for candidates
typedef struct {
    char name[25];
    double værdipolitik_c; // Value politics?/policy?
    double fordelingspolitik_c;// Distribution Politics?/policy?
    int votes_fptp;
    int votes_star;
    int votes_rated;
    int votes_rcv;
}candidate;
//struct for state
typedef struct {
    char name[20];
    int votes_fptp;
    int votes_star;
    int votes_rated;
    int votes_rcv;
    int voters_population;
    int electoral_mandates;
}state;
//initalization functions
void init_state(state state_arr[]);//DONE
void init_voters(voter voters_arr[]);
void init_candidates(candidate candidate_arr[]);//DONE

//Voting system functions
void voting_fptp(state current_state, voter voters_arr[], candidate candidate_arr[]);
void voting_star(state current_state, voter voters_arr[], candidate candidate_arr[]);
void voting_rated(state current_state, voter voters_arr[], candidate candidate_arr[]);
void voting_rcv(state current_state, voter voters_arr[], candidate candidate_arr[]);

//winner functions
candidate find_winner_fptp();
candidate find_winner_star();
candidate find_winner_rated();
candidate find_winner_rcv();

//result function
void print_results();

int main(void)
{
    //fair elections
    //Initialize state (by attributes)
    state state_array[STATE_MAX];
    init_state(state_array);
    // for (int i = 0; i < STATE_MAX; i++) {
    //     printf("%s %d %d\n", state_array[i].name, state_array[i].voters_population, state_array[i].electoral_mandates);
    // }
    // //Initialize voters (by attributes) (political compass)
    // voter voters_array[POPULATION];
    // init_voters(voters_array);
    // //Initialize candidates (by attributes)
    candidate candidate_array[CANDIDATES];
    init_candidates(candidate_array);
    // for(int i = 0; i < CANDIDATES; i++) {
    //     printf("Candidate %d: %s %lf %lf\n", i, candidate_array[i].name, candidate_array[i].værdipolitik_c, candidate_array[i].fordelingspolitik_c);
    // }

    //for-loop for each state
    // for(int i = 0; i < STATE_MAX; i++) {
    //     //collect votes from each state
    //     //do it for each voting system
    //     state current_state = state_array[i];
    //     voting_fptp(current_state, voters_array, candidate_array);
    //     voting_star(current_state, voters_array, candidate_array);
    //     voting_rated(current_state, voters_array, candidate_array);
    //     voting_rcv(current_state, voters_array, candidate_array);
    // }

    //for each voting system
    //find the winner of each
    // for(int i = 0; i < 4; i++) {
    //     candidate winner_fptp = find_winner_fptp();
    //     candidate winner_star = find_winner_star();
    //     candidate winner_rated = find_winner_rated();
    //     candidate winner_rcv = find_winner_rcv();
    // }

    // //show the result of the vote
    // print_results();

    return 0;
}

void init_state(state state_arr[]) {
    FILE *f = fopen("state_data.txt", "r");
    if (f == NULL) {
        printf("Error: couldn't open file named state_data.txt");
        exit(EXIT_FAILURE);
    }
    for(int i = 0; i < STATE_MAX; i++) {
        fscanf(f,"%[^0-9] %d %d\n", state_arr[i].name, &state_arr[i].voters_population, &state_arr[i].electoral_mandates);
    }
    fclose(f);
}

void init_candidates(candidate candidate_arr[]) {
    const char *names[] = {"Donald Trump", "Kamala Harris", "Robert F. Kennedy"};
    double værdipolitik_c[] = {-4.0, 3, -1};
    double fordelingspolitik_c[] = {4.0, -3, 2};
    for(int i = 0; i < CANDIDATES; i++) {
        strcpy(candidate_arr[i].name, names[i]);
        candidate_arr[i].værdipolitik_c = værdipolitik_c[i];
        candidate_arr[i].fordelingspolitik_c = fordelingspolitik_c[i];
        candidate_arr[i].votes_fptp = 0;
        candidate_arr[i].votes_star = 0;
        candidate_arr[i].votes_rated = 0;
        candidate_arr[i].votes_rcv = 0;
    }
}