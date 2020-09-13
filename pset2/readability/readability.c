#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

int count_letters(string text_cl);
int count_words(string text_cw);
int count_sentences(string text_cs);

int main(void)
{
    string my_text = get_string("Text: ");
    //printf("%i letter(s)\n", count_letters(my_text));
    //printf("%i word(s)\n", count_words(my_text));
    //printf("%i sentence(s)\n", count_sentences(my_text));
    float L = (count_letters(my_text) * 100) / (float) count_words(my_text);
    float S = (count_sentences(my_text) * 100) / (float) count_words(my_text);
    float my_grade = 0.0588 * L - 0.296 * S - 15.8;
    //printf("%f\n", my_grade);
    if (round(my_grade) < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (round(my_grade) >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", (int) round(my_grade));
    }

}

//count letters function
int count_letters(string text_cl)
{
    int cl = 0;
    for (int i = 0; i < strlen(text_cl); i++)
    {
        if ((text_cl[i] >= 'a' && text_cl[i] <= 'z') || (text_cl[i] >= 'A' && text_cl[i] <= 'Z'))
        {
            cl ++;
        }
    }
    return cl;
}

//count words function
int count_words(string text_cw)
{
    int cw = 1;
    for (int i = 0; i < strlen(text_cw); i++)
    {
        if (text_cw[i] == ' ')
        {
            cw ++;
        }
    }
    return cw;
}

//count sentences function
int count_sentences(string text_cs)
{
    int cs = 0;
    for (int i = 0; i < strlen(text_cs); i++)
    {
        if (text_cs[i] == '.' || text_cs[i] == '!' || text_cs[i] == '?')
        {
            cs ++;
        }
    }
    return cs;
}
