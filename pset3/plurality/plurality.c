#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
}
candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(string name)
{
    for (int cc = 0; cc < candidate_count; cc++)
    {
        if (strcmp(name, candidates[cc].name) == 0)
        {
            candidates[cc].votes ++;
            //printf("votes: %i\n", candidates[cc].votes);
            return true;
        }
    }
    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    for (int ccw = 0; ccw < candidate_count; ccw++)
    {
        for (int ccwi = 0; ccwi < candidate_count - 1; ccwi++)
        {
            if (candidates[ccwi].votes > candidates[ccwi + 1].votes)
            {
                int tmp_votes = candidates[ccwi].votes;
                candidates[ccwi].votes = candidates[ccwi + 1].votes;
                candidates[ccwi + 1].votes = tmp_votes;

                string tmp_name = candidates[ccwi].name;
                candidates[ccwi].name = candidates[ccwi + 1].name;
                candidates[ccwi + 1].name = tmp_name;
                //printf("ccw:%i, ccwi:%i, name:%s, vote: %i ", ccw, ccwi, candidates[ccwi].name, candidates[ccwi].votes);
            }
        }
    }
    if (candidates[candidate_count - 1].votes > candidates[candidate_count - 2].votes)
    {
        printf("%s\n", candidates[candidate_count - 1].name);
    }
    else
    {
        for (int ccwp = 0; ccwp < candidate_count; ccwp++)
        {
            if (candidates[ccwp].votes == candidates[candidate_count - 1].votes)
            {
                printf("%s\n", candidates[ccwp].name);
            }
        }
    }
    return;
}

