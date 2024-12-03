#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "functions.h"

void init_state(state state_arr[])
{
    FILE* f = fopen("state_data.txt", "r");
    if (f == NULL)
    {
        printf("Error: couldn't open file named state_data.txt");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < STATE_MAX; i++)
    {
        fscanf(f, "%[^0-9] %d %d\n", state_arr[i].name, &state_arr[i].voters_population,
               &state_arr[i].electoral_mandates);
    }
    fclose(f);
}

void init_candidates(candidate candidate_arr[])
{
    const char* names[] = {"Donald Trump", "Kamala Harris", "Robert F. Kennedy"};
    double værdipolitik_c[] = {-4.0, 3, -1};
    double fordelingspolitik_c[] = {4.0, -3, 2};
    for (int i = 0; i < CANDIDATES; i++)
    {
        strcpy(candidate_arr[i].name, names[i]);
        candidate_arr[i].værdipolitik_c = værdipolitik_c[i];
        candidate_arr[i].fordelingspolitik_c = fordelingspolitik_c[i];
        candidate_arr[i].votes_fptp = 0;
        candidate_arr[i].votes_star = 0;
        candidate_arr[i].votes_rated = 0;
        candidate_arr[i].votes_rcv = 0;
    }
}

void init_voters(voter voters_arr[])
{
    int random_age;
    int random_gender;
    int random_race;
    int random_income;

    double male_prc = 0;
    double female_prc = 0;

    double low_prc = 0;
    double middle_prc = 0;
    double high_prc = 0;

    double white_prc = 0;
    double black_prc = 0;
    double hispanic_prc = 0;
    double asian_prc = 0;
    double american_prc = 0;
    double hawaiian_prc = 0;
    double other_prc = 0;

    double young_prc = 0;
    double adult_prc = 0;
    double middle_age_prc = 0;
    double old_prc = 0;
    double elderly_prc = 0;

    for (int i = 0; i < POPULATION; i++)
    {
        // POLITISK INDFLYDELSE SKAL TILFØJES TIL ALLE KATEGORIERNE

        // ALDER: Giver 0 eller 1 som output for køn
        random_gender = rand() % 2;
        voters_arr[i].gender_v = random_gender;
        if (random_gender == 0)
        {
            male_prc++;
        }
        else
        {
            female_prc++;
        }

        // INDKOMST:
        random_income = (rand() % 10) + 1;
        if (random_income <= 1)
        {
            // 20% TJENER LAV
            voters_arr[i].income_v = low;
            low_prc++;
        }
        else if (random_income <= 8)
        {
            // 60% TJENER MIDDEL
            voters_arr[i].income_v = middle;
            middle_prc++;
        }
        else
        {
            // 20% TJENER HØJT
            voters_arr[i].income_v = high;
            high_prc++;
        } // DISSE PROCENTER ER IKKE BASERET PÅ NOGET, BURDE NOK BLIVE ÆNDRET, MÅSKE INDDELT I FLERE KATEGORIER

        // RACE: // LAV MED ARRAY I STEDET
        random_race = (rand() % 1000) + 1;
        if (random_race <= 584)
        {
            // WHITE POPULATION: 58,4
            voters_arr[i].race_v = white;
            white_prc++;
        }
        else if (random_race <= 721)
        {
            //BLACK POPULATION: 13,7%
            voters_arr[i].race_v = black;
            black_prc++;
        }
        else if (random_race <= 916)
        {
            // HISPANIC / LATINO: 19,5%
            voters_arr[i].race_v = hispanic;
            hispanic_prc++;
        }
        else if (random_race <= 980)
        {
            // ASIAN POPULATION 6,4%
            voters_arr[i].race_v = asian;
            asian_prc++;
        }
        else if (random_race <= 993)
        {
            // NATIVE AMERICAN 1,3%
            voters_arr[i].race_v = native_american;
            american_prc++;
        }
        else if (random_race <= 996)
        {
            // NATIVE HAWAIIEN 0,3%
            voters_arr[i].race_v = native_hawaiian;
            hawaiian_prc++;
        }
        else
        {
            voters_arr[i].race_v = other;
            other_prc++;
        }
        // SOURCE: https://www.census.gov/quickfacts/

        random_age = (rand() % 100) + 1;
        if (random_age <= 20)
        {
            voters_arr[i].age_v = young;
            young_prc++;
        }
        else if (random_age <= 40)
        {
            voters_arr[i].age_v = adult;
            adult_prc++;
        }
        else if (random_age <= 60)
        {
            voters_arr[i].age_v = middle_aged;
            middle_age_prc++;
        }
        else if (random_age <= 80)
        {
            voters_arr[i].age_v = old;
            old_prc++;
        }
        else
        {
            voters_arr[i].age_v = elderly;
            elderly_prc++;
        } // SKAL OMFORDELES BASERET PÅ DATA
    }

    printf("Male: %.2lf%\n", (male_prc /= POPULATION) * 100);
    printf("Female: %.2lf%\n", (female_prc /= POPULATION) * 100);

    printf("Low income: %.2lf%\n", (low_prc /= POPULATION) * 100);
    printf("Middle income: %.2lf%\n", (middle_prc /= POPULATION) * 100);
    printf("High income: %.2lf%\n", (high_prc /= POPULATION) * 100);

    printf("White: %.2lf%\n", (white_prc /= POPULATION) * 100);
    printf("Black: %.2lf%\n", (black_prc /= POPULATION) * 100);
    printf("Hispanic: %.2lf%\n", (hispanic_prc /= POPULATION) * 100);
    printf("Asian: %.2lf%\n", (asian_prc /= POPULATION) * 100);
    printf("Native American: %.2lf%\n", (american_prc /= POPULATION) * 100);
    printf("Native Hawaiian: %.2lf%\n", (hawaiian_prc /= POPULATION) * 100);
    printf("Other: %.2lf%\n", (other_prc /= POPULATION) * 100);

    printf("Young: %.2lf%\n", (young_prc /= POPULATION) * 100);
    printf("Adult: %.2lf%\n", (adult_prc /= POPULATION) * 100);
    printf("Middle aged: %.2lf%\n", (middle_age_prc /= POPULATION) * 100);
    printf("Old: %.2lf%\n", (old_prc /= POPULATION) * 100);
    printf("Elderly: %.2lf%\n", (elderly_prc /= POPULATION) * 100);
}
