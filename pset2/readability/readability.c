#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
// Calculate the suirable grade of a given text.
int count_letters(string input);
int count_words(string input);
int count_sentences(string input);

int main(void)
{

    string text = get_string("Text: ");
    printf("%i letter(s)\n", count_letters(text));
    printf("%i words(s)\n", count_words(text));
    printf("%i sentence(s)\n", count_sentences(text));
    
    // L : the number of letters per 100 words.
    float L = ((float) count_letters(text) / count_words(text)) * 100;
    // S : the number of sentences per 100 words.
    float S = ((float) count_sentences(text) / count_words(text)) * 100;
    float index = 0.0588 * L - 0.296 * S - 15.8;
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else 
    {
        printf("Grade %.0f\n", index);
    }
    
}



// Counts the letters
int count_letters(string input)
{
    int sum = 0;
    for (int i = 0; input[i] != '\0'; i++)
    {
        if (isalpha(input[i]) != 0)
        {
            sum += 1;
        }
    }
    return sum;
}

// Counts the words.
int count_words(string input)
{
    int sum = 1;
    for (int i = 0; input[i] != '\0'; i++)
    {
        if (input[i] == ' ')
        {
            sum += 1;
        }
    }
    return sum;
}

// Counts the sentences.
int count_sentences(string input)
{
    int sum = 0;
    for (int i = 0; input[i] != '\0'; i++)
    {
        if ((input[i] == '.') || (input[i] == '!') || (input[i] == '?'))
        {
            sum += 1;
        }
    }
    return sum;
}