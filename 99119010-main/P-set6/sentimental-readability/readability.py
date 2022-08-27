def main():
    # Asks the user for the text
    text = input("Text: ")

    # Initialzes letter_count, word_count and sentence_count
    letter_count = 0
    word_count = 0
    sentence_count = 0

    # Goes through the text
    for i in text:
        # If text[i] is an alphabet, then increments letter_count by 1
        if i.isalpha() == True:
            letter_count += 1

        # If a space is encountered, then increments word_count by 1
        if i == ' ':
            word_count += 1

        # If line endings are encountered, then increments sentence_count by 1
        if i == '.' or i == '!' or i == '?':
            sentence_count += 1

    # Adds word_count by 1 since the final word won't have a space after it
    word_count += 1

    # Calculates how many letters there are per 100 words
    L = (letter_count / word_count) * 100

    # Calculates how many sentences there are per 100 words
    S = (sentence_count / word_count) * 100
    index = 0.0588 * L - 0.296 * S - 15.8

    # Calculates the index according to the formula
    rounded_index = round(index)

    if index > 16:
        print("Grade 16+")

    elif index < 1:
        print("Before Grade 1")

    else:
        print(f"Grade {rounded_index}")


main()