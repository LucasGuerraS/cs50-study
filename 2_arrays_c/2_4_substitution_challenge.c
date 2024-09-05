#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

bool get_sum(string dict);
string encrypt(string original_text, string upper_dict);
bool validate_input(int argc, string argv[]);
string make_upper(string dict);
string make_lower(string dict);

int main(int argc, string argv[])
{
    bool isValid = validate_input(argc, argv);
    if (!isValid) {
        printf("Please provide input according to the expected format\n");
        return 1;
    }
    string str = get_string("plaintext: ");
    string upper = make_upper(argv[1]);
    printf("ciphertext: %s\n", encrypt(str, upper));
    return 0;
}

bool get_sum(string dict) {
    bool isDuplicate = false;
    int seen[128] = {0};
    int len = strlen(dict);
    for (int i = 0; i < len; i++) {
        if (seen[(int)dict[i]] == 1) {
            isDuplicate = true;
            return isDuplicate;
        }
        seen[(int)dict[i]] = 1;
    }
    return isDuplicate;
}

bool validate_input(int argc, string argv[]) {
    bool isValid = true;
    if (argc == 1 || argc > 2) {
        isValid = false;
        return isValid;
    }
    for (int i = 0, n = strlen(argv[1]); i < n; i++) {
        if (!(isalpha(argv[1][i]))) {
            isValid = false;
            return isValid;
        }
    }
    bool seen = get_sum(argv[1]);
    if (seen || strlen(argv[1]) != 26) {
        isValid = false;
        return isValid;
    }
    return isValid;
}

string make_upper(string dict) {
    for (int i = 0, n = strlen(dict); i < n; i++) {
       dict[i] = toupper(dict[i]);
    }
    return dict;
}

string make_lower(string dict) {
    for (int i = 0, n = strlen(dict); i < n; i++) {
        dict[i] = tolower(dict[i]);
    }
    return dict;
}

string encrypt(string original_text, string upper_dict) {
    int original_len = strlen(original_text);
    for (int i = 0; i < original_len; i++) {
        if (isalpha(original_text[i])) {
            if (isupper(original_text[i])) {
                int index = original_text[i] - 65;
                original_text[i] = upper_dict[index];
            } else {
                int index = original_text[i] - 97;
                original_text[i] = tolower(upper_dict[index]);
            }
        }
    }
    return original_text;
}