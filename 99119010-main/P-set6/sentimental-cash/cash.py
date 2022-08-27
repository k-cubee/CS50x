from cs50 import get_float


def main():
    # Ask how many cents the customer is owed
    cents = get_cents()

    # Calculate the number of quarters to give the customer
    quarters = calculate_quarters(cents)
    cents = cents - quarters * 25

    # Calculate the number of dimes to give the customer
    dimes = calculate_dimes(cents)
    cents = cents - dimes * 10

    # Calculate the number of pennies to give the customer
    nickels = calculate_nickels(cents)
    cents = cents - nickels * 5

    # Sum coins
    pennies = calculate_pennies(cents)
    cents = cents - pennies

    # Print total number of coins to give the customer
    coins = quarters + dimes + nickels + pennies
    print(coins)
    return 0
    

def get_cents():
    while True:
        total = round(get_float("Change owed: "), 2)
        if total > 0:
            break
    change = int(round(total, 2) * 100)
    return change


def calculate_quarters(cents):
    quarters = cents // 25
    return quarters


def calculate_dimes(cents):
    dimes = cents // 10
    return dimes


def calculate_nickels(cents):
    nickels = cents // 5
    return nickels


def calculate_pennies(cents):
    pennies = cents // 1
    return pennies


main()