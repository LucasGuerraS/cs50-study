#include <stdio.h>
#include <cs50.h>

int get_ranged_int(void);

int main(void) {
    int height = get_ranged_int();
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < ((height * 2) + 1); j++) {
            if (j == height) {
                printf("  ");
            }
            else if (i + j >= height - 1 && j < height) {
                printf("#");
            }
            else if (i - j >= -height - 1  && j > height) {
                printf("#");
            } else {
                if (j < height - 1) {
                    printf(" ");
                }
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
