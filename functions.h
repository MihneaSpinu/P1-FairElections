#ifndef FUNCTIONS_H
#define FUNCTIONS_H

//
//
// DEFINES
#define STATES 49
#define MAX_CANDIDATES 5
#define RACES 5
#define GENDERS 2
#define INCOME 3
#define AGES 5
#define MAX_NAME_LENGTH 21
#define VARIANCE 10
#define POPULATION 2509472

#define CONGRESSIONAL_DISTRICTS 5

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
    double distance_to[MAX_CANDIDATES]; // Rangering af kandidater (ranked)
    int ratings[MAX_CANDIDATES];
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
    int fptp_mandates;
    int rated_mandates;
    int eliminated; // Flag for elimineret kandidat (ranked)
    int total_mandates;

    int congressional_mandates;

} candidate;

typedef struct {
    char name[MAX_NAME_LENGTH];
    int race_distribution[RACES];
    int gender_distribution[GENDERS];
    int income_distribution[INCOME];
    int age_distribution[AGES];
    int candidate_votes_fptp[MAX_CANDIDATES];
    int candidate_votes_star[MAX_CANDIDATES];
    int candidate_votes_rated[MAX_CANDIDATES];
    int candidate_votes_ranked[MAX_CANDIDATES];
    int population;
    int electoral_votes;

    int district_votes[CONGRESSIONAL_DISTRICTS][MAX_CANDIDATES];
    int state_votes[MAX_CANDIDATES];

} state;

//
//
// Initalization functions
void init_state(state state_arr[], int num_of_candidate); //DONE
void init_candidates(candidate candidate_arr[], int num_of_candidates, char candidate_name[][MAX_NAME_LENGTH],
                     int værdi[], int fordeling[]); //DONE
void init_voters(voter voter_arr[], state current_state, int start_index, int state, double calc_percent[][4][5]);
void init_attributes(int distribution[], int attribute_amount, int category, int start_index,
                     int state, voter voter_arr[], int state_population, double calc_percent[][4][5],
                     int fordelingspolitik[][5], int værdipolitik[][5]);
void init_index(int cumulative_state_population, int start_index[], state state_arr[]);

//Congressional functions
void maine_nebraska_congressional(state congressional_arr[], candidate candidate_arr[], int num_of_candidates);
//void init_congressional(state congressional_arr[], int num_of_candidate);

//
//
// Result function
int print_winners(candidate candidate_arr[], int num_of_candidates, int voting_system);

//
//
// Ranked functions
int ranked_choice_voting(int state_population, voter voter_arr[], candidate candidate_arr[], int start_index, state *current_state, int num_of_candidates);
int find_lowest_votes(candidate candidate_arr[], int num_of_candidates);
void distribute_votes(voter voter_arr[], candidate candidate_arr[], int state_population, int start_index, state *current_state, int num_of_candidates);

//
//
// Rated functions
int voting_rated(voter voter_arr[], int population, int start_index, state *current_state, int num_of_candidates);

//
//
// FPTP functions
int first_past_the_post(voter voter_arr[], int state_population, int start_index, state *current_state, int num_of_candidates);

//
//
// STAR functions
int voting_star(int current_state_population, voter voter_arr[], candidate candidate_arr[], int start_index, state *current_state, int num_of_candidates);

//
//
// Misc.
void print_percent(double calc_percent[][4][5], int state_population, int state);
void get_distance(voter voters_arr[], candidate candidate_arr[], int population, int num_of_candidates);
void prompt_stats(state state_arr[], double calc_percent[][4][5], candidate candidate_arr[], int num_of_candidates);
void election_2024();
void get_ratings (voter voter_arr[], int i, int j);
int variance();
double voters_satisfaction(voter current_voter, int winner_index);
double calc_satisfaction(int winner_index, voter voters_arr[], int population);

// Election settings
void scan_election_settings(int *simulation_choice, int *electoral_choice, int *candidate_choice,
                            int *voting_system_choice, int *candidates, char candidate_name[][MAX_NAME_LENGTH],
                            int værdi[MAX_CANDIDATES], int fordeling[MAX_CANDIDATES]);
void check_input_validity(int user_input);
void custom_candidates(int *candidates, char candidate_name[][MAX_NAME_LENGTH], int værdi[], int fordeling[]);


#endif //FUNCTIONS_H
