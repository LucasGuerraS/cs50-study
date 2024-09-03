#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

int score_sentence(string sentence);
int character_count(string sentence);
int word_count(string sentence);
int sentence_count(string sentence);

int main(void)
{
    // Get sentence
    string sentence = get_string("Text: ");
    // Score sentence
    int score = score_sentence(sentence);
    // Print result
    if (score >= 16) {
        printf("Grade 16+\n");
    } else if (score < 1) {
        printf("Before Grade 1\n");
    } else {
        printf("Grade %i\n", score);
    }
}

int score_sentence(string sentence) {
    float score;
    // Get character count
    int chars = character_count(sentence);
    // Get word count
    int words = word_count(sentence);
    // Get sentence count
    int sents = sentence_count(sentence);
    float L = (100 / (float) words) * (float) chars;
    float S = (100 / (float) words) * (float) sents;
    score = 0.0588 * L - 0.296 * S - 15.8;
    score = round(score);
    return (int) score;
}

int character_count(string sentence) {
    int count = 0;
    for (int i = 0, len = strlen(sentence); i < len; i++) {
        if (isalpha(sentence[i])) {
            count++;
        }
    }
    return count;
}

int word_count(string sentence) {
    int count = 0;
    for (int i = 0, len = strlen(sentence); i < len; i++) {
        if (isblank(sentence[i])) {
            count++;
        }
    }
    return count + 1;
}

int sentence_count(string sentence) {
    int count = 0;
    for (int i = 0, len = strlen(sentence); i < len; i++) {
        int ascii = (int) sentence[i];
        if (ascii == 46 || ascii == 63 || ascii == 33) {
            count++;
        }
    }
    return count;
}