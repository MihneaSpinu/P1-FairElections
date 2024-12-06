#ifndef FUNCTIONS_H
#define FUNCTIONS_H

//
//
// DEFINES
#define STATES 51
#define CANDIDATES 3
#define RACES 5
#define GENDERS 2
#define INCOME 3
#define AGES 5
#define MAX_NAME_LENGTH 21
#define VARIANCE 20

#define POPULATION 250947173 // VIRKER MED POPULATION + 173 (250947000 + 173) DETTE ER MINDSTE GRÆNSEN
                             // STOPPER VED GET_DISTANCE FUNKTIONEN (SOM TAGER POPULATION SOM INPUT)
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
    int is_voting;
    int værdipolitik_v;
    int fordelingspolitik_v;
    double distance_to_[CANDIDATES]; // Rangering af kandidater (ranked)
    int ratings[CANDIDATES]; // Rated
} voter;

typedef struct {
    char name[MAX_NAME_LENGTH];
    int værdipolitik_c;
    int fordelingspolitik_c;
    int mandates_fptp;
    int votes_star;
    int mandates_star;
    int mandates_rated;
    int mandates_rcv;
    int votes_rated;
    int votes_rcv;
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
void init_voters(state state_arr[], voter voter_arr[], state cur_state, int current_i_voter, int state, double calc_percent[STATES][4][5]);
void init_attributes(int state_population, voter voter_arr[], int attribute_amount, double calc_percent[STATES][4][5], int distribution[],
                     int attribute_type, int fordelingspolitik[][5], int værdipolitik[][5], int current_i_voter, int state);
//
//
// Voting system functions
int first_past_the_post(voter voter_arr[], candidate candidate_arr[], int total_voters, int current_i_voter);
int voting_star(int current_state_population, voter voter_arr[], candidate candidate_arr[], int current_i_voter);
int voting_rated(voter voter_arr[], candidate candidate_arr[], int population);
void voting_rcv(state state_arr[], voter voters_arr[], candidate candidate_arr[]);

//
//
// Winner functions
candidate find_winner_fptp();
candidate find_winner_star();
candidate find_winner_rated();
candidate find_winner_rcv();

//
//
// Result function
void print_winners();

//
//
// Ranked functions
void start_ranked_voting(state state_arr[], voter voter_arr[], candidate candidate_arr[], int index);
int find_lowest_votes(candidate candidate_arr[]);
void redistribute_votes(voter voter_arr[], candidate candidate_arr[], int total_voters);
int check_majority(candidate candidate_arr[], int total_voters);
void eliminate_candidate(candidate candidate_arr[], int candidate_to_eliminate);
void clear_votes(candidate candidate_arr[]);
//
//
// Rated functions
typedef struct {
    int total;
    int trump[10];
    int harris[10];
} votes_rated;

typedef struct {
    int mandates;
    votes_rated v;
} state_rated;

void get_votes(FILE *f, votes_rated *v);
void results(votes_rated *v);
//double median(int votes[], int size);
double average(int votes[], int size);

//
//
// FPTP functions
void print_results(candidate winner);
candidate find_winner_fptp(candidate candidate_arr[]);
void voting_fptp(state current_state, voter voters_arr[], candidate candidate_arr[]);
void start_fptp_voting(state state_arr[], voter voters_arr[], candidate candidate_arr[]);

//
//
// Misc.
void print_percent(double calc_percent[][4][5], int state_population, int state);
void get_distance(voter voters_arr[], candidate candidate_arr[], int population);
//void get_distance_and_rate(voter voter_arr[], candidate candidate_arr[], int population);
int variance();
void init_percent(double calc_percent[][4][5]);
void prompt_stats(state state_arr[], double calc_percent[][4][5]);

//
//
// // STAR functions
// int voting_star(state state_arr[], voter voters_arr[], candidate candidate_arr[], int current_i_voter);
// STAR functions

#endif //FUNCTIONS_H
