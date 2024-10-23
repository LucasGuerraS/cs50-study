import csv
import sys


def main():

    # Check for command-line usage
    if len(sys.argv) != 3:
        print("Correct usage: python dna.py <DATABASE_PATH> <SEQUENCE_PATH>")
        return
    # Read database file into a variable
    file = open(sys.argv[1], "r")
    # Read file into dictionary
    reader = csv.DictReader(file)
    # Create variable which is a array of dictionaries
    database = []
    # Save all rows into dict
    for row in reader:
        database.append(row)
    file.close()
    # Register field names except name
    file = open(sys.argv[1], "r")
    columns = csv.reader(file).__next__()
    columns.pop(0)
    file.close()
    # Read DNA sequence file into a variable
    seq_file = open(sys.argv[2], "r")
    seq_text = seq_file.read()
    seq_file.close()
    # Find longest match of each STR in DNA sequence
    seq_dict = {}
    for seq in columns:
        seq_dict[seq] = longest_match(seq_text, seq)
    # Check database for matching profiles
    found = False
    for people in database:
        count = 0
        for sq in seq_dict:
            if int(seq_dict[sq]) == int(people[sq]):
                count += 1
        if count == len(columns):
            print(people['name'])
            found = True
    if found == False:
        print("No Match")
    return


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
