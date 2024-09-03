#include <stdio.h>
#include <cs50.h>

long get_initial(void);
long get_final(long initial);
int get_years(long initial, long final);

int main(void) {
    long initial_pop = get_initial();
    long final_pop = get_final(initial_pop);
    int years = get_years(initial_pop, final_pop);
    printf("Years: %i\n", years);
}

long get_initial(void) {
    long initial;
    do {
        initial = get_long("Start size: ");
    }
    while (initial < 9);
    return initial;
}

long get_final(long initial) {
    long final;
    do {
        final = get_long("End size: ");
    }
    while(final < initial);
    return final;
}

int get_years(long initial, long final) {
    int years = 0;
    while (initial < final) {
        initial = initial + (initial / 3) - (initial / 4);
        years ++;
    }
    return years;
}
