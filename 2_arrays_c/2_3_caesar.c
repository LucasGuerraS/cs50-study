#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const int BA = 65;
const int SA = 97;
const int BZ = 90;
const int SZ = 122;

string ceasar(int skip, string sentence);

int main(int argc, string argv[])
{
    if (argc == 1 || argc > 2) {
        printf("Please provide 1 numeric argument in the command line\n");
        return 1;
    }
    for (int i = 0, n = strlen(argv[1]); i < n; i++) {
        if ((isalpha(argv[1][i]))) {
            printf("Use: ./caesar key\n");
            return 1;
        }
    }
    string str = get_string("plaintext: ");
    int amount = atoi(argv[1]) % 26;
    printf("ciphertext: %s\n", ceasar(amount, str));
    return 0;
}

string ceasar(int skip, string sentence) {
    for (int i = 0, n = strlen(sentence); i < n; i++) {
        if (isalpha(sentence[i])) {
            int jump = sentence[i] + skip;
            if (islower(sentence[i])) {
                if (jump > 122) {
                    jump -= 26;
                }
            } else {
                if  (jump > 90) {
                    jump -= 26;
                }
            }
            sentence[i] = (char) jump;
        }
    }
    return sentence;
}