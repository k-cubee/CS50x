import csv
import sys


def main():

    # Check for command-line usage
    if len(sys.argv) != 3:
        sys.exit("Usage: python dna.py data.csv sequence.txt")

    # Read database file into a variable
    database_for_str = open(sys.argv[1], "r")
    database_for_names = open(sys.argv[1], "r")

    # Read DNA sequence file into a variable
    sequence = open(sys.argv[2], "r")
    reader_for_str = csv.reader(database_for_str)
    reader_for_names = csv.DictReader(database_for_names)
    str_list = next(reader_for_str)
    str_list.remove("name")
    sample = sequence.read()
    str_count = {}
    humans = []
    for row in reader_for_names:
        row.update({"count": 0})
        humans.append(row)

    # Find longest match of each STR in DNA sequence
    for str in str_list:
        str_count[str] = longest_match(sample, str)
        # Check database for matching profiles
        for check in humans:
            if int(check[str]) == str_count[str]:
                check["count"] += 1
            if check["count"] == len(str_list):
                sequence.close()
                database_for_str.close()
                database_for_names.close()
                sys.exit(check["name"])

    # Close files and exit
    sequence.close()
    database_for_str.close()
    database_for_names.close()
    sys.exit("No match")


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
