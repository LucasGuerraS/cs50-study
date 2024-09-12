#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
    int strength;
} pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
void merge_sort(pair arr[], int left, int right);
void merge(pair arr[], int left, int middle, int right);
bool has_cycle(int winner, int looser);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
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
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    // Iterate candidates[] and if candidate exists add vote to ranks[rank] and return true
    for (int i = 0; i < candidate_count; i++) {
        if (strcmp(name, candidates[i]) == 0) {
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // Iterate ranks and add +1 to preferences based on ranking for each iteraton
    for (int i = 0; i < candidate_count - 1; i++) {
         // ranks[i] = current candidate
         // Inner loop to go from i + 1 until end of the array including the last index
         for (int j = i + 1; j < candidate_count; j++) {
            preferences[ranks[i]][ranks[j]]++;
         }
    }
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // Iterate preferences and compare candidate i with candidate j and see if there's a winner
    for (int i = 0; i < candidate_count; i++) {
        for (int j = 0; j < candidate_count; j++) {
            if (preferences[i][j] > preferences[j][i]) {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pairs[pair_count].strength = preferences[i][j];
                pair_count++;
            }
        }
    }
}

void merge(pair arr[], int left, int middle, int right) {

    // Declare helper variables
    int i, j, k;

    // Define length of left and right halves
    int num_left = middle - left + 1;
    int num_right = right - middle;

    // Create helper arrays
    pair l[num_left], r[num_right];


    // Populate helper arrays
    for (i = 0; i < num_left; i++) {
        l[i] = arr[left + i];
    }
    for (j = 0; j < num_right; j++) {
        r[j] = arr[middle + 1 + j];
    }

    // Redefine helper variables
    i = 0;
    j = 0;
    k = left;
    // Merge helper arrays int original array based on strength
    while (i < num_left && j < num_right) {
        if (l[i].strength <= r[j].strength) {
            arr[k] = l[i];
            i++;
        }
        else {
            arr[k] = r[j];
            j++;
        }
        k++;
    }

    // Add elements that were no iterated to original arr
    while (i < num_left) {
        arr[k] = l[i];
        i++;
        k++;
    }

    // Add elements that were no iterated to original arr
    while (j < num_right) {
        arr[k] = r[j];
        j++;
        k++;
    }
}

void merge_sort(pair arr[], int left, int right) {
    if (left < right) {

        // Get middle index
        int middle = left + (right - left) / 2;

        // Sort both halves of the array
        merge_sort(arr, left, middle);
        merge_sort(arr, middle + 1, right);

        // Merge halves of the array
        merge(arr, left, middle, right);
    }
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // Use Merge Sort to sort candidates by strength
    merge_sort(pairs, 0, pair_count - 1);
    for (int i = 0; i < pair_count; i++) {
        printf("%i\n", pairs[i].strength);
    }
}

bool has_cycle(int winner, int loser) {
    if (locked[loser][winner] == true) {
        return true;
    }
    for (int i = 0; i < candidate_count; i++) {
        if (locked[loser][i] == true && has_cycle(winner, i)) {
            return true;
        }
    }
    return false;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++) {
        if (!has_cycle(pairs[i].winner, pairs[i].loser)) {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }
}

// Print the winner of the election
void print_winner(void)
{
    for (int i = 0; i < candidate_count; i++) {
        int count = 0;
        for (int j = 0; j < candidate_count; j++) {
            if (locked[j][i] == false) {
                count++;
            }
            if (count == 3) {
                printf("%s\n", candidates[i]);
            }
        }
    }
}