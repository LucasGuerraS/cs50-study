#include <stdio.h>
#include <cs50.h>

int get_ranged_int(void);

int main(void) {
    int height = get_ranged_int();
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < height; j++) {
            if (i + j >= height - 1) {
                printf("#");
            } else {
                printf(" ");
            }
        }
        printf("\n");
    }
}

int get_ranged_int(void) {
    int n;
    do {
        n = get_int("Height: ");
    }
    while(n < 1 || n > 8);
    return n;
}
