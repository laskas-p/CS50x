from cs50 import get_string


def main():
    my_text = get_string("Text: ")
    # printf("%i letter(s)\n", count_letters(my_text));
    # printf("%i word(s)\n", count_words(my_text));
    # printf("%i sentence(s)\n", count_sentences(my_text));
    L = (count_letters(my_text) * 100) / float(count_words(my_text))
    S = (count_sentences(my_text) * 100) / float(count_words(my_text))
    my_grade = 0.0588 * L - 0.296 * S - 15.8
    # printf("%f\n", my_grade);
    if round(my_grade) < 1:
        print("Before Grade 1")
    elif round(my_grade) >= 16:
        print("Grade 16+")
    else:
        print(f"Grade {round(my_grade)}")


# count letters function
def count_letters(text_cl):
    cl = 0
    for i in range(len(text_cl)):
        if (text_cl[i] >= 'a' and text_cl[i] <= 'z') or (text_cl[i] >= 'A' and text_cl[i] <= 'Z'):
            cl += 1
    return cl


# count words function
def count_words(text_cw):
    cw = 1
    for i in range(len(text_cw)):
        if text_cw[i] == " ":
            cw += 1
    return cw


# count sentences function
def count_sentences(text_cs):
    cs = 0
    for i in range(len(text_cs)):
        if (text_cs[i] == '.' or text_cs[i] == '!' or text_cs[i] == '?'):
            cs += 1
    return cs


main()