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
} candidate;

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
    // Loop through array of candidates and find candidate ny other result after loop is finished with no candidate will return false
    for (int i = 0; i < candidate_count; i++) {
        if (strcmp(name, candidates[i].name) == 0) {
            candidates[i].votes++;
            return true;
        }
    }
    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    // Loop through the array of candidates and store in a aux candidate array the most voted candidates (first loop defines highest votes and second iter populates winners)
    int highest = 0;
    int highest_c = 0;
    for (int i = 0; i < candidate_count; i++) {
        if (candidates[i].votes > highest) {
            highest_c = 0;
            highest = candidates[i].votes;
            highest_c ++;
        }
        else if (candidates[i].votes == highest) {
            highest_c ++;
        }
    }
    for (int i = 0, n = 0; i < candidate_count; i++) {
        if (candidates[i].votes == highest) {
            printf("%s\n", candidates[i].name);
        }
    }
}
