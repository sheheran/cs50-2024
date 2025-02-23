#include <cs50.h>
#include <stdio.h>

#include <string.h>
// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is jth preference for voter i
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Candidates have name, vote count, eliminated status
typedef struct
{
    string name;
    int votes;
    bool eliminated;
} candidate;

// Array of candidates
candidate candidates[MAX_CANDIDATES];

// Numbers of voters and candidates
int voter_count;
int candidate_count;

// Function prototypes
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    voter_count = get_int("Number of voters: ");
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // Keep querying for votes
    for (int i = 0; i < voter_count; i++)
    {

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            // Record vote, unless it's invalid
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }

        printf("\n");
    }

    // Keep holding runoffs until winner exists
    while (true)
    {
        // Calculate votes given remaining candidates
        tabulate();

        // Check if election has been won
        bool won = print_winner();
        if (won)
        {
            break;
        }

        // Eliminate last-place candidates
        int min = find_min();
        bool tie = is_tie(min);

        // If tie, everyone wins
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }

        // Eliminate anyone with minimum number of votes
        eliminate(min);

        // Reset vote counts back to zero
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}

// Record preference if vote is valid
// As the voter enters their preferences,
// the "vote" function is called to keep track of all of the preferences.
bool vote(int voter, int rank, string name)
{
    //1. In to the preferances[i][j] 2-D array add the "voter" number to [voter][0] position.
    //2. Match the candidate name with their number in the candidate list.
    for(int k=0; k < candidate_count; k++){
        if (strcmp(name, candidates[k].name) == 0) {
    //3. If the provided name is matched with the candidates in the list
    //add the "k" number (candidate number) in to preferance[voter][rank]
            preferences[voter][rank] = k;
            //printf("true\n");
            return true; //Successfully recorded the vote
        }
        // else{
            //printf("false\n");
            //return false;
        // }
    }
    return false;
}

// Tabulate votes for non-eliminated candidates
// Look at all the preferences, compute the current total votes
void tabulate(void)
{
    // 0. Loop through candidates k;
    // if candidates[k].eliminated == true, do nothing;
    // if candidates[k].eliminated == fales, set candidates[k] votes = 0;
    for (int k=0; k < candidate_count; k++){
        if (!candidates[k].eliminated){
            candidates[k].votes = 0;
        }
    }

    // 1. In preference go to voter i; check preference j, Find the candidate k, which match preferance j;
    // 3. Take candidate k, check if candidate is candidates[k].eliminated == true,
    //    if yes go to the next preferance j+1;
    // 2. If candidates[k].eliminated == false, candidates[k].votes = ++1;
    for (int i=0; i < voter_count; i++){
        for (int j=0; j < candidate_count; j++){
            int candidate_index = preferences[i][j];
            //printf("%i\n",preferences[i][j]);
            if (!candidates[candidate_index].eliminated){
                candidates[candidate_index].votes++;
                break;
            }
        }
    }

    return;
}

// Print the winner of the election, if there is one
bool print_winner(void)
{
    // The Majority threshold is 50% (MAX_VOTERS/2);
    float majority = voter_count / 2;
     //printf("%f\n",majority);
    // 1. loop through the candidates;
    // Check if
    // 2. if candidates[k].votes >= 50% (MAX_VOTERS/2) && !candidates[k].eleminated;
    // 3. winner == candidates[k].name;
    for (int k=0; k < candidate_count; k++){
        if (!candidates[k].eliminated && candidates[k].votes > majority){
            printf("%s\n",candidates[k].name);
            return true;
        }
    }
    return false;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    // 0.Take majority as minimum votes;
    int min_votes = MAX_VOTERS/2;
    // 1.loop through the candidates;
    // 2. if !candidates[k+1].eleminated;
    // 3. if candidates[k].votes > candidates[k+1].votes, else loop;
    // 3. eliminated = candidates[k+1].name;
    // 4. min = candidates[k+1].votes;
    for(int k=0; k < candidate_count; k++){
        if(!candidates[k].eliminated){
            if (candidates[k].votes < min_votes){
                min_votes = candidates[k].votes;
            }
        }
    }
    return min_votes;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    // TODO - The initial algorithem is redundent
    // 0. tie_votes = MAX_VOTERS/2;, is_tie = false;
    // int tie_votes = MAX_VOTERS/2;
    // bool is_tie = false;
    // 1.loop through candidates;
    // 4.if !candidates[k].eliminated && candidates[k].votes != tie_votes;
    // 3.tie_votes = candidates[k].votes;
    // 4. if k+1 < candidate_count && !candidates[k+1].eliminated;
    // 5. if (tie_votes != candidates[k+1]);
    // break
    // for(int k = 0; k < candidate_count; k++){
    //     if(!candidates[k].eliminated && tie_votes != candidates[k].votes){
    //         tie_votes = candidates[k].votes;
    //     }
    //     if((k+1 < candidate_count) && (!candidates[k+1].eliminated)){
    //         if (tie_votes != candidates[k+1]){
    //             return false;
    //         }
    //     }
    // }

    int tie_votes = -1;
    for(int k = 0; k < candidate_count; k++){
        if(!candidates[k].eliminated){
            if(tie_votes == -1){
                tie_votes = candidates[k].votes;
            }else if(candidates[k].votes != tie_votes) {
                return false;
            }

        }
    }
    return true;
}

// Eliminate the candidate (or candidates) in last place
void eliminate(int min)
{
    // Find candidate with minimum votes;
    // 0.Take majority as minimum votrs;
    int min_votes = MAX_VOTERS/2;
    //int index_of_min[candidate_count] = 0;
    int i=0;
    // 1.Loop through the candidates;
    // 2.if !candidates[k+1].eliminated;
    // 3.if candidates[k].votes > candidates[k+1].votes, else loop;
    // 4.min = candidates[k+1].votes;
    // 5.update index_of_eliminated;
    for(int k=0; k < candidate_count; k++){
        if(!candidates[k].eliminated){
            if (candidates[k].votes < min_votes){
                min_votes = candidates[k].votes;
            }
        }
    }
    // 6.Loop through the candidates;
    // 7.Check if multiple candidates have minimum votes;
    // 8.After looping through the candidates set candidates[index_of_eliminated] == true;
    for(int index_of_min=0; index_of_min < candidate_count; index_of_min++){
        if(!candidates[index_of_min].eliminated){
            if (candidates[index_of_min].votes == min_votes){
                candidates[index_of_min].eliminated = true;
            }
        }
    }

    return;
}
