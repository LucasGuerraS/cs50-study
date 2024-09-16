#include <stdio.h>

int main(void)
{
    char *s = "HI!";
    printf("%p\n", &s);
    printf("%c\n", *(s+1));
    printf("%c\n", *(s+2));
}
