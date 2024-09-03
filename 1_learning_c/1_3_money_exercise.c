#include <stdio.h>
#include <cs50.h>
#include <math.h>

int get_value(void);

int main(void) {
    int count = 0;
    int value = get_value();
    do {
        if ((value - 25) >= 0) {
            count++;
            value = value - 25;
        }
        else if ((value - 10) >= 0) {
            count++;
            value = value - 10;
        }
        else if ((value - 5) >= 0) {
            count++;
            value = value - 5;
        }
        else if ((value - 1) >= 0) {
            count++;
            value = value - 1;
        }
    }
    while (value > 0);
    printf("Value: %i\n", count);
}

int get_value(void) {
    float n;
    do {
        n = get_float("Valor devido: ");
    }
    while(n < 0);
    return (int) round(n * 100);
}
