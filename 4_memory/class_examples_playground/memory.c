#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int *n = malloc(4);
    *n = 50;
    printf("%p\n", n);
}
