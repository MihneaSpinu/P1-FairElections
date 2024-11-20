#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define STATE_MAX 51
#define POPULATION 1000
#define CANDIDATES 3

typedef enum {white, black, hispanic, asian, native_american, native_hawaiian, other} race;
typedef enum {male, female} gender;
typedef enum {low, middle, high} income;
typedef enum  {young, adult, middle_aged, old, elderly} age;

//VOTER STRUCT
typedef struct {
    age age_v; // ung 18-25. voksen 26-39. middelaldrene 40-59. ældre 60-69. gammel 70+?
    gender gender_v; // 0=male, 1=female
    race race_v;
    income income_v;//by level: 0 = low, 1 = middle, 2 = high
    int is_voting; //0 = not voting, 1 = voting
    //politics:
    int værdipolitik_v; // Value politics?/policy?
    int fordelingspolitik_v;// Distribution Politics?/policy?
}voter;

//CANDIDATE STRUCT
typedef struct {
    char name[25];
    int værdipolitik_c; // Value politics?/policy?
    int fordelingspolitik_c;// Distribution Politics?/policy?
    int votes_fptp;
    int votes_star;
    int votes_rated;
    int votes_rcv;
}candidate;

//STATE STRUCT
typedef struct {
    int votes_fptp;
    int votes_star;
    int votes_rated;
    int votes_rcv;
    int voters_population;
    int electoral_mandates;
}state;
//initalization functions
void init_state(state state_arr[]);
void init_voters(voter voters_arr[]);
void init_candidates(candidate candidate_arr[]);

//Voting system code
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

int main(void) {
    /*
    //fair elections
    //Initialize state (by attributes)
    state state_array[STATE_MAX];
    init_state(state_array);
    */
    //Initialize voters (by attributes) (political compass)
    srand(time(NULL));
    voter voters_array[POPULATION];
    init_voters(voters_array);

    for(int i = 0; i < POPULATION; i++) {
        printf("G: %d A: %d I: %d R: %d\n", voters_array[i].gender_v, voters_array[i].age_v,
                                            voters_array[i].income_v, voters_array[i].race_v);
    }
    /*
    //Initialize candidates (by attributes)
    candidate candidate_array[CANDIDATES];
    init_candidates(candidate_array);

    //for-loop for each state
    for(int i = 0; i < STATE_MAX; i++) {
        //collect votes from each state
        //do it for each voting system
        state current_state = state_array[i];
        voting_fptp(current_state, voters_array, candidate_array);
        voting_star(current_state, voters_array, candidate_array);
        voting_rated(current_state, voters_array, candidate_array);
        voting_rcv(current_state, voters_array, candidate_array);
    }

    //for each voting system
    //find the winner of each
    for(int i = 0; i < 4; i++) {
        candidate winner_fptp = find_winner_fptp();
        candidate winner_star = find_winner_star();
        candidate winner_rated = find_winner_rated();
        candidate winner_rcv = find_winner_rcv();
    }

    //show the result of the vote
    print_results();
    */
    return 0;
}

void init_voters(voter voters_arr[]) {

    int random_age;
    int random_gender;
    int random_race;
    int random_income;

    for(int i = 0; i < POPULATION; i++) {

        // POLITISK INDFLYDELSE SKAL TILFØJES TIL ALLE KATEGORIERNE

        // ALDER: Giver 0 eller 1 som output for køn
        random_gender = rand() % 2;
        voters_arr[i].gender_v = random_gender;
        // voters_arr[i].gender_v = rand() % 2; <- simplificering

        // INDKOMST:
        random_income = (rand() % 10) + 1;
        if(random_income <= 2) { // 20% TJENER LAV
            voters_arr[i].income_v = low;
        } else if(random_income <= 8) { // 60% TJENER MIDDEL
            voters_arr[i].income_v = middle;
        } else { // 20% TJENER HØJT
            voters_arr[i].income_v = high;
        } // DISSE PROCENTER ER IKKE BASERET PÅ NOGET, BURDE NOK BLIVE ÆNDRET, MÅSKE INDDELT I FLERE KATEGORIER

        // RACE:
        random_race = (rand() % 1000) + 1;
        if(random_race <= 584) { // WHITE POPULATION: 58,4
            voters_arr[i].race_v = white;
        } else if(random_race <= 721) { //BLACK POPULATION: 13,7%
            voters_arr[i].race_v = black;
        } else if(random_race <= 916) { // HISPANIC / LATINO: 19,5%
            voters_arr[i].race_v = hispanic;
        } else if(random_race <= 980) { // ASIAN POPULATION 6,4%
            voters_arr[i].race_v = asian;
        } else if(random_race <= 993) { // NATIVE AMERICAN 1,3%
            voters_arr[i].race_v = native_american;
        } else if(random_race <= 996) { // NATIVE HAWAIIEN 0,3%
            voters_arr[i].race_v = native_hawaiian;
        } else { // ALT DETTE GIVER 99,6 TIL SAMMEN (uden other)
            voters_arr[i].race_v = other;
        }
        // SOURCE: https://www.census.gov/quickfacts/

        random_age = (rand() % 100) + 1;
        if(random_age <= 20) {
            voters_arr[i].age_v = young;
        } else if(random_age <= 40) {
            voters_arr[i].age_v = adult;
        } else if(random_age <= 60) {
            voters_arr[i].age_v = middle_aged;
        } else if(random_age <= 80) {
            voters_arr[i].age_v = old;
        } else {
            voters_arr[i].age_v = elderly;
        } // SKAL OMFORDELES BASERET PÅ DATA



    }







}