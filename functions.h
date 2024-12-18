#ifndef FUNCTIONS_H
#define FUNCTIONS_H

//
//
// DEFINES
#define STATES 51
#define MAX_CANDIDATES 8
#define RACES 5
#define GENDERS 2
#define INCOME 3
#define AGES 5
#define MAX_NAME_LENGTH 21
#define STD_DEVIATION 5
#define POPULATION 250947200
#define MAX_DISTANCE 200

//
//
// ENUMS
enum { race, gender, income, age };
typedef enum: unsigned char { white, black, hispanic, asian, other } race_e;
typedef enum: unsigned char { male, female } gender_e;
typedef enum: unsigned char { low, middle, high } income_e;
typedef enum: unsigned char { young, adult, middle_aged, old, elderly } age_e;

//
//
// STRUCTS
typedef struct {
    float distance_to[MAX_CANDIDATES];
    float social_policy_v;
    float economic_policy_v;
    int ratings[MAX_CANDIDATES];
    age_e age_v;
    gender_e gender_v;
    race_e race_v;
    income_e income_v;
} voter;

typedef struct {
    char name[MAX_NAME_LENGTH];
    int social_policy_c;
    int economic_policy_c;
    int votes_fptp;
    int votes_star;
    int votes_rated;
    int votes_rcv;
    int star_mandates;
    int rcv_mandates;
    int fptp_mandates;
    int rated_mandates;
    int general_mandates;
    int eliminated; // Flag for elimineret kandidat (ranked)
} candidate;

typedef struct {
    char name[MAX_NAME_LENGTH];
    int race_distribution[RACES];
    int gender_distribution[GENDERS];
    int income_distribution[INCOME];
    int age_distribution[AGES];
    int candidate_votes_fptp[MAX_CANDIDATES];
    int candidate_votes_rcv[MAX_CANDIDATES];
    int candidate_votes_rated[MAX_CANDIDATES];
    int candidate_votes_star[MAX_CANDIDATES];
    int population;
    int electoral_votes;
} state;

//
//
// Initalization functions
void init_state(state state_arr[], int num_of_candidates);
void init_candidates(candidate candidate_arr[], int num_of_candidates, char candidate_name[][MAX_NAME_LENGTH],
                     int social_p[], int economic_p[]);
void init_voters(voter voter_arr[], state current_state, int start_index, int state, float calc_percent[][4][5]);
void init_attributes(int distribution[], int attribute_amount, int category, int start_index,
                     int state, voter voter_arr[], int population, float calc_percent[][4][5],
                     int economic_policy[][5], int social_policy[][5]);
void init_index(int cumulative_state_population, int start_index[], state state_arr[]);

//
//
// Result functions
int print_winner(int num_of_candidates, char voting_system[], int mandates[],
                  candidate candidate_arr[], char vote_type[], int electoral_choice);
int contingent_election(int num_of_candidates, int mandates[], candidate candidate_arr[], char voting_system[]);
int contingent_top_three(int num_of_candidates, int advanced[], int mandates[]);
int contingent_winner(int num_of_candidates, int mandates[], int top1, int top2, int top3);
int condorcet_winner(int num_voters, int num_candidates, voter voter_arr[]);

//
//
// Ranked functions
int ranked_choice_voting(int population, voter voter_arr[], candidate candidate_arr[],
                         int start_index, state *current_state, int num_of_candidates);
int find_lowest_votes(candidate candidate_arr[], int num_of_candidates);
void distribute_votes(voter voter_arr[], candidate candidate_arr[], int population,
                      int start_index, state *current_state, int num_of_candidates);

//
//
// Rated functions
int voting_rated(voter voter_arr[], int population, int start_index, state *current_state, int num_of_candidates);

//
//
// FPTP functions
int first_past_the_post(voter voter_arr[], int population, int start_index,
                        state *current_state, int num_of_candidates);

//
//
// STAR functions
int voting_star(int population, voter voter_arr[], candidate candidate_arr[],
                int start_index, state *current_state, int num_of_candidates);

//
//
// Election settings
void scan_election_settings(int *simulation_choice, int *electoral_choice, int *candidate_choice,
                            int *voting_system_choice, int *candidates, char candidate_name[][MAX_NAME_LENGTH],
                            int social_p[MAX_CANDIDATES], int economic_p[MAX_CANDIDATES]);
void check_input_validity(int user_input, int choice_amount);
void custom_candidates(int *candidates, char candidate_name[][MAX_NAME_LENGTH], int værdi[], int fordeling[]);

//
//
// Misc.
void print_percent(float calc_percent[][4][5], int population, int state);
void get_distance(voter voters_arr[], candidate candidate_arr[], int population, int num_of_candidates);
void prompt_stats(state state_arr[], float calc_percent[][4][5], candidate candidate_arr[], int num_of_candidates);
void get_ratings (voter voter_arr[], int num_of_candidates, int population);
int variance();
float voters_satisfaction(voter current_voter, int winner_index);
float calc_satisfaction(int winner_index, voter voters_arr[], int population);
void check_memory_allocation(void *array);

#endif //FUNCTIONS_H