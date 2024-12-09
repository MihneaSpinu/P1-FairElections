#ifndef FUNCTIONS_H
#define FUNCTIONS_H

//
//
// DEFINES
#define STATES 51
#define CANDIDATES 5
#define RACES 5
#define GENDERS 2
#define INCOME 3
#define AGES 5
#define MAX_NAME_LENGTH 21
#define VARIANCE 0
#define POPULATION 250947200

//
//
// ENUMS
typedef enum { race, gender, income, age } categories_e;
typedef enum: unsigned char { white, black, hispanic, asian, other } race_e;
typedef enum: unsigned char { male, female } gender_e;
typedef enum: unsigned char { low, middle, high } income_e;
typedef enum: unsigned char { young, adult, middle_aged, old, elderly } age_e;

//
//
// STRUCTS
typedef struct {
    age_e age_v;
    gender_e gender_v;
    race_e race_v;
    income_e income_v;
    int værdipolitik_v;
    int fordelingspolitik_v;
    double distance_to[CANDIDATES]; // Rangering af kandidater (ranked)
    int ratings[CANDIDATES];
} voter;

typedef struct {
    char name[MAX_NAME_LENGTH];
    int værdipolitik_c;
    int fordelingspolitik_c;
    int votes_fptp;
    int votes_star;
    int votes_rated;
    int votes_rcv;
    int star_mandates;
    int rcv_mandates;
    int eliminated; // Flag for elimineret kandidat (ranked)

} candidate;

typedef struct {
    char name[MAX_NAME_LENGTH];
    int race_distribution[RACES];
    int gender_distribution[GENDERS];
    int income_distribution[INCOME];
    int age_distribution[AGES];
    int population;
    int electoral_votes;
} state;

//
//
// Initalization functions
void init_state(state state_arr[]); //DONE
void init_candidates(candidate candidate_arr[]); //DONE
void init_voters(voter voter_arr[], state current_state, int start_index, int state,
                 double calc_percent[][4][5], int fordelingspolitik[][5], int værdipolitik[][5]);
void init_attributes(int distribution[], int attribute_amount, int category, int start_index,
                     int state, voter voter_arr[], int state_population, double calc_percent[][4][5],
                     int fordelingspolitik[][5], int værdipolitik[][5]);
void init_index(int cumulative_state_population, int start_index[], state state_arr[]);

//
//
// Voting system functions
int first_past_the_post(voter voter_arr[], int state_population, int start_index);
void voting_rcv(state state_arr[], voter voters_arr[], candidate candidate_arr[]);

//
//
// Result function
void print_winners();

//
//
// Ranked functions
int ranked_choice_voting(int state_population, voter voter_arr[], candidate candidate_arr[], int start_index);
int check_majority(candidate candidate_arr[], int state_population);
int find_lowest_votes(candidate candidate_arr[]);
void distribute_votes(voter voter_arr[], candidate candidate_arr[], int state_population, int start_index);
void reset_votes(candidate candidate_arr[]);

//
//
// Rated functions
int voting_rated(voter voter_arr[], int population, int start_index);

//
//
// FPTP functions
void print_results(candidate winner);
candidate find_winner_fptp(candidate candidate_arr[]);
void voting_fptp(state current_state, voter voters_arr[], candidate candidate_arr[]);
void start_fptp_voting(state state_arr[], voter voters_arr[], candidate candidate_arr[]);

//
//
// STAR functions
int voting_star(int current_state_population, voter voter_arr[], candidate candidate_arr[], int start_index);

//
//
// Misc.
void print_percent(double calc_percent[][4][5], int state_population, int state);
void get_distance(voter voters_arr[], candidate candidate_arr[], int population);
int variance();
void prompt_stats(state state_arr[], double calc_percent[][4][5]);


#endif //FUNCTIONS_H
