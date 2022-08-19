#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
    // gets the card number from the user
    unsigned long card_no = get_long("Number: ");
    unsigned long card_no_cpy = card_no;

    // calculates the amount of digits - 1 in the card number
    int power = log10(card_no);
    int sum_s_to_last = 0;
    int sum_last = 0;

    // calculates the second to last digits times two and the sum of their digits
    if (power % 2 == 1)
    {
        for (int i = power; i >= 0; i -= 2)
        {
            long divisor = pow(10, i);
            int s_to_last = (card_no / divisor) % 10;
            card_no = card_no - (pow(10, i) * s_to_last);
            int multiplied_s_to_last = s_to_last * 2;

            if (multiplied_s_to_last >= 10)
            {
                multiplied_s_to_last = 1 + (multiplied_s_to_last % 10);
            }
            sum_s_to_last += multiplied_s_to_last;
        }

        // calculates the sum of the last digits
        for (int j = power - 1; j >= 0; j -= 2)
        {
            long divisor = pow(10, j);
            int last = (card_no / divisor) % 10;
            card_no = card_no - (pow(10, j) * last);
            sum_last += last;
        }
    }
    else if (power % 2 == 0)
    {
        int npower = power + 1;
        card_no = card_no + pow(10, npower);
        for (int i = npower; i >= 0; i -= 2)
        {
            long divisor = pow(10, i);
            int s_to_last = (card_no / divisor) % 10;
            card_no = card_no - (pow(10, i) * s_to_last);
            int multiplied_s_to_last = s_to_last * 2;
            if (multiplied_s_to_last >= 10)
            {
                multiplied_s_to_last = 1 + (multiplied_s_to_last % 10);
            }
            sum_s_to_last += multiplied_s_to_last;
        }
        sum_s_to_last -= 2;
        card_no = card_no + pow(10, npower);

        // calculates the sum of the last digits
        for (int j = npower - 1; j >= 0; j -= 2)
        {
            long divisor = pow(10, j);
            int last = (card_no / divisor) % 10;
            card_no = card_no - (pow(10, j) * last);
            sum_last += last;
        }
    }

    // checks the conditions of the cards
    long cdivisor1 = pow(10, power);
    long cdivisor2 = pow(10, power - 1);
    if ((sum_s_to_last + sum_last) % 10 == 0)
    {
        int condition1 = (card_no_cpy / cdivisor1) % 10;
        int conditionp = power + 1;
        int condition2 = card_no_cpy / cdivisor2;

        // checks for VISA card
        if (condition1 == 4 && (conditionp == 16 || conditionp == 13))
        {
            printf("VISA\n");
        }

        // checks for AMEX card
        else if ((condition2 == 34 || condition2 == 37) && conditionp == 15)
        {
            printf("AMEX\n");
        }

        // checks for MASTER card
        else if ((condition2 == 51 || condition2 == 52 || condition2 == 53 || condition2 == 54 || condition2 == 55) && conditionp == 16)
        {
            printf("MASTERCARD\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    // prints INVALID when the card number doesn't end in 0
    else
    {
        printf("INVALID\n");
    }
}