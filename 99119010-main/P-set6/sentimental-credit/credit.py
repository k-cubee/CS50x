from cs50 import get_int
from math import log, floor


def main():
    # Gets the card number from the user
    card_no = get_int("Number: ")
    card_no_cpy = card_no

    # Calculates the amount of digits - 1 in the card number
    power = floor(log(card_no, 10))
    sum_s_to_last = 0
    sum_last = 0

    # Calculates the second to last digits times two and the sum of their digits
    if (power % 2 == 1):
        for i in range(power, -1, -2):
            divisor = 10 ** i
            s_to_last = (card_no // divisor) % 10
            card_no -= ((10 ** i) * s_to_last)
            multiplied_s_to_last = s_to_last * 2

            if multiplied_s_to_last >= 10:
                multiplied_s_to_last = 1 + (multiplied_s_to_last % 10)
            sum_s_to_last += multiplied_s_to_last

        # Calculates the sum of the last digits
        for i in range(power - 1, -2, -2):
            divisor = 10 ** i
            last = (card_no // divisor) % 10
            card_no -= ((10 ** i) * last)
            sum_last += last

    elif (power % 2 == 0):
        npower = power + 1
        card_no = card_no + (10 ** npower)

        for i in range(npower, -1, -2):
            divisor = 10 ** i
            s_to_last = (card_no // divisor) % 10
            card_no -= (10 ** i) * s_to_last
            multiplied_s_to_last = s_to_last * 2

            if multiplied_s_to_last >= 10:
                multiplied_s_to_last = 1 + (multiplied_s_to_last % 10)

            sum_s_to_last += multiplied_s_to_last

        sum_s_to_last -= 2
        card_no += 10 ** npower

        # Calculates the sum of the last digits
        for i in range(npower - 1, -1, -2):
            divisor = 10 ** i
            last = int((card_no / divisor) % 10)
            card_no = card_no - (10 ** i) * last
            sum_last += last

    cdivisor1 = 10 ** power
    cdivisor2 = 10 ** (power - 1)

    # Checks the conditions of the cards
    if (sum_s_to_last + sum_last) % 10 == 0:
        condition1 = (card_no_cpy // cdivisor1) % 10
        conditionp = power + 1
        condition2 = card_no_cpy // cdivisor2

        # Checks for VISA card
        if condition1 == 4 and (conditionp == 16 or conditionp == 13):
            print("VISA")

        # Checks for AMEX card
        elif (condition2 == 34 or condition2 == 37) and conditionp == 15:
            print("AMEX")

        # Checks for MASTER card
        elif (condition2 == 51 or condition2 == 52 or condition2 == 53 or condition2 == 54 or condition2 == 55) and conditionp == 16:
            print("MASTERCARD")

        else:
            print("INVALID")

    else:
        print("INVALID")


main()