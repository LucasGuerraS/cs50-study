def main():
    sentece = get_string("Text: ")
    score = score_sentence(sentece)
    if score >= 16:
        print("Grade 16+")
    elif score < 1:
        print("Before Grade 1")
    else:
        print(f"Grade {score}")


def get_string(text):
    while True:
        try:
            sentence = input(text)
            return sentence

        except:
            print("Enter a valid string")


def score_sentence(sentence):
    chars = character_count(sentence)
    words = word_count(sentence)
    sents = sentence_count(sentence)
    L = (100 / float(words)) * float(chars)
    S = (100 / float(words)) * float(sents)
    return int(round(0.0588 * L - 0.296 * S - 15.8))


def character_count(sentence: str):
    count = 0
    for char in sentence:
        if char.isalpha():
            count += 1
    return count


def word_count(sentence: str):
    return len(sentence.split())


def sentence_count(sentence: str):
    count = 0
    for char in sentence:
        if char in ".!?":
            count += 1
    return count


main()