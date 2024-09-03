#include <stdio.h>
#include <cs50.h>
#include <math.h>

long get_card(void);
int get_other_sum(long credit_card);
int get_even_sum(long credit_card);
int get_digits(long credit_card);
int get_first_numbers(long credit_card);

int main(void) {
    long card = get_card();
    int digits = get_digits(card);
    int firsts = get_first_numbers(card);
    int every_other = get_other_sum(card);
    int normal_sum = get_even_sum(card);
    int final_sum = every_other + normal_sum;
    bool isValid = false;
    if (final_sum % 10 == 0) {
        isValid = true;
    }
    if (isValid && (firsts / 10) == 4 && (digits == 16 || digits == 13)) {
        printf("VISA\n");
    } else if (isValid && (firsts == 34 || firsts == 37) && digits == 15) {
        printf("AMEX\n");
        //51, 52, 53, 54 ou 55
    } else if (isValid && (firsts == 51 || firsts == 52 || firsts == 53 || firsts == 54 || firsts == 55) && digits == 16) {
        printf("MASTERCARD\n");
    } else {
        printf("INVALID\n");
    }
}

long get_card(void) {
    return get_long("Enter card number: ");
}

int get_other_sum(long credit_card) {
    int sum = 0;
    do {
        int n = ((credit_card / 10) % 10) * 2;
        if (n >= 10) {
            sum += (n % 10);
            sum += (n / 10);
        } else {
            sum += n;
        }
        credit_card = credit_card / 100;
    }
    while (credit_card > 10);
    return sum;
}

int get_even_sum(long credit_card) {
    int sum = 0;
    do {
        int n = credit_card  % 10;
        sum += n;
        credit_card = credit_card / 100;
    }
    while (credit_card > 0);
    return sum;
}

int get_digits(long credit_card) {
    int digit = 0;
    do {
        digit ++;
        credit_card = credit_card / 10;
    }
    while (credit_card > 0);
    return digit;
}

int get_first_numbers(long credit_card) {
    do {
        credit_card = credit_card / 10;
    }
    while (credit_card > 100);
    return credit_card;
}