def main():

    card = get_card()

    digits = len(str(card))

    firsts = get_first_numbers(card)

    every_other = get_other_sum(card)

    normal_sum = get_even_sum(card)

    final_sum = every_other + normal_sum

    isValid = False

    if final_sum % 10 == 0:
        isValid = True

    if isValid and (firsts // 10) == 4 and (digits == 16 or digits == 13):
        print("VISA")
    elif isValid and (firsts == 34 or firsts == 37) and digits == 15:
        print("AMEX")
    elif (isValid and (firsts == 51 or firsts == 52 or firsts == 53 or firsts == 54 or firsts == 55) and digits == 16):
        print("MASTERCARD")
    else:
        print("INVALID")


def get_card():
    # Get a valid input from user
    while True:
        try:
            h = input("Number: ")
            return int(h)

        except ValueError:
            print("Please enter a valid integer")


def get_other_sum(card):
    sum = 0
    while card > 10:
        n = ((card // 10) % 10) * 2
        if n >= 10:
            sum += n % 10
            sum += n // 10
        else:
            sum += n
        card = int(card / 100)
    return sum


def get_even_sum(card):
    sum = 0
    while card > 0:
        n = card % 10
        sum += n
        card = card // 100
    return sum


def get_first_numbers(card):
    while card > 100:
        card = card // 10
    return card


main()
