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
    // debug
    for(int i = 0; i < candidate_count; i++){
        printf("%s has %i votes", candidates[i].name, candidates[i].votes);
    }
    return 0;
}

// Record preference if vote is valid
bool vote(int voter, int rank, string name)
{
    // compare with each candidate
    for(int i = 0; i < candidate_count; i++){
        // if candidate's name is found
        if(strcmp(name, candidates[i].name) == 0){
            // in preferences[i][j] put at rank column of voter's row, put candidate's index
            preferences[voter][rank] = i;
            return true;
        }
    }
    // TODO
    return false;
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    // as soon as i find first active candidate which is in preference
    for(int i = 0; i < voter_count; i++){ // i here indexes through voters in prefeerences
        for(int j = 0; j < candidate_count; j++){ // j here indexes through candidate ranks in preferences
            // if the current candidate in preference is not eliminated, increase it's votes
            if(candidates[preferences[i][j]].eliminated == false){
                candidates[preferences[i][j]].votes++;
                // i'll break out of loop to go for next voter's preferences
                break;
            }
        }
    }
    // TODO
    return;
}

// Print the winner of the election, if there is one
bool print_winner(void)
{
    // storing total votes to later check for >50%
    int total_votes = 0;
    for(int i = 0; i < candidate_count; i++){
        total_votes += candidates[i].votes;
    }

    // if candidate vote count is more than 50% combined, he's the winner
    for(int i = 0; i < candidate_count; i++){
        if(candidates[i].votes > total_votes/2){
            printf("%s\n", candidates[i].name);
            return true;
        }
    }
    // TODO
    return false;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    // store lowest index of uneliminated candidate to count the loop from there
    int lowest_index;
    candidate lowest;
    // check the earliest uneliminated candidate to store in "lowest" candidate to compare lowest votes
    for(lowest_index = 0; lowest_index < candidate_count; lowest_index++){
        // if candidates isn't eliminated
        if(!candidates[lowest_index].eliminated){
            // then store him as lowest voted candidate
            lowest = candidates[lowest_index];
            break;
        }
    }

    // start the loop from first active candidate
    for(int i = lowest_index ; i < candidate_count; i++){
        // if current candidate's votes is lower than lowest's votes, replace lowest with current candidate
        if(candidates[i].votes < lowest.votes && candidates[i].eliminated == false){
            lowest = candidates[i];
        }
    }
    // TODO
    // return the lowest vote count
    return lowest.votes;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    // if all candidates votes are not equal to min and are not eliminated, then it's not tie, else return true
    for(int i = 0; i< candidate_count; i++){
        if(candidates[i].votes != min && candidates[i].eliminated == false){
            // TODO
            return false;
        }
    }
    return true;
}

// Eliminate the candidate (or candidates) in last place
void eliminate(int min)
{
    // loop through candidates
    for(int i = 0; i < candidate_count; i++){
        // if candidates count is equal to "min (returned from find_min())", AND isn't eliminated already
        if(candidates[i].votes == min && candidates[i].eliminated == false){
            // then eliminate him
            candidates[i].eliminated = true;
            // we won't return after eliminating because it's possible there are more than one candidate with lowest count, so we'll have to eliminate them all
        }
    }
    // TODO
    // if not found, just return
    return;
}
