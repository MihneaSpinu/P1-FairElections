#ifndef FUNCTIONS_H
#define FUNCTIONS_H


//
//
//Initialiserings-funktioner
#define STATE_MAX 51
#define POPULATION 10000
#define CANDIDATES 3

typedef enum { white, black, hispanic, asian, native_american, native_hawaiian, other } race;
typedef enum { male, female } gender;
typedef enum { poor, low, middle, high, rich } income;
typedef enum { young, adult, middle_aged, old, elderly } age;

//VOTER STRUCT
typedef struct
{
    age age_v; // ung 18-25. voksen 26-39. middelaldrene 40-59. ældre 60-69. gammel 70+?
    gender gender_v; // 0=male, 1=female
    race race_v;
    income income_v; //by level: 0 = poor, 1 = low, 2 = middle, 3 = high, 4 = rich
    int is_voting; //0 = not voting, 1 = voting
    //politics:
    double værdipolitik_v; // Value politics?/policy?
    double fordelingspolitik_v; // Distribution Politics?/policy?
    int rankings[CANDIDATES]; // Rangering af kandidater (ranked)
} voter;

//CANDIDATE STRUCTF
typedef struct
{
    char name[25];
    double værdipolitik_c; // Value politics?/policy?
    double fordelingspolitik_c; // Distribution Politics?/policy?
    int votes_fptp;
    int votes_star;
    int votes_rated;
    int votes_rcv;
    int eliminated; // Flag for elimineret kandidat (ranked)
} candidate;

//STATE STRUCT
typedef struct
{
    char name[20];
    int votes_fptp;
    int votes_star;
    int votes_rated;
    int votes_rcv;
    int voters_population;
    int electoral_mandates;
} state;



//initalization functions
void init_state(state state_arr[]); //DONE
void init_voters(voter voters_arr[]);
void get_percent(double calc_percent[][7]);
void init_candidates(candidate candidate_arr[]); //DONE

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

//
//
// ranked functions
int check_majority(candidate candidate_arr[], int total_voters);
int find_lowest_votes(candidate candidate_arr[]);
void redistribute_votes(voter voters_arr[], candidate candidate_arr[], int eliminated_candidate);
void reset_votes(candidate candidate_arr[]);

void start_ranked_voting(candidate candidate_arr[], voter voters_arr[],int total_voters,int eliminated_candidate);


//
//
// rated functions
typedef struct {
    int total;
    int trump[10];
    int harris[10];
} votes;

void get_votes(FILE *f, votes *v);
void results(votes *v);
double median(int votes[], int size);
double average(int votes[], int size);

//
//
// fptp functions
void print_results(candidate winner);
candidate find_winner_fptp(candidate candidate_arr[]);
void voting_fptp(state current_state, voter voters_arr[], candidate candidate_arr[]);
void start_fptp_voting(state state_arr[], voter voters_arr[], candidate candidate_arr[]);

#endif //FUNCTIONS_H
