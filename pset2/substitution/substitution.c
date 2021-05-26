#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int valid_key(int argc, string argv[]);
void convertor(string key, string input);
void iconvertor(string key, string input);
char littlize(char input);
char capitalize(char input);


int main(int argc, string argv[])
{   

    // valid_key(argc,argv);
    if (valid_key(argc, argv) == 1)
    {
        return 1;
    }

    // string input = get_string("plaintext: ");
    string input = get_string("ciphertext: ");
    // convertor(argv[1], input);
    iconvertor(argv[1], input);
    return 0;
}



int valid_key(int argc, string argv[])
{
    int letter_occurance = -1 ;
    if (argc != 2)
    {
        printf("Enter a one sequence of letters\n");
        return 1;

    }

    if (argv[1][26] != '\0')
    {
        printf("Enter 26 characters!\n");
        return 1;

    }
    for (int i = 0; i < strlen(argv[1]); i++)
    {
        letter_occurance = -1;
        for (int j = 0; j < strlen(argv[1]); j++)
        {
            if (tolower(argv[1][i]) == tolower(argv[1][j]))
            {
                letter_occurance ++;
                if (letter_occurance != 0)
                {
                    printf("Each letter must be typed only once!\n");
                    return 1;
                }
            }
        }
    }
    for (int i = 0; i < strlen(argv[1]); i++)
    {
        if (isalpha(argv[1][i]) == 0)
        {
            printf("%c is not a valid letter!\n", argv[1][i]);
            return 1;
        }
    }
    return 0;
}

void convertor(string key, string input)
{
    char output[strlen(input)];
    strcpy(output, input);
    string Alphabet = "abcdefghijklmnopqrstuvwxyz";
    for (int i = 0; i < strlen(input); i++)
    {
        for (int j = 0; j < strlen(key); j++)
        {
            if (tolower(input[i]) == Alphabet[j])
            {
                output[i] = tolower(key[j]);
            }
        }
        if (isupper(input[i]) != 0)
        {
            output[i] = toupper(output[i]);
        }
    }
    printf("ciphertext: %s\n", output);
}

void iconvertor(string key, string input)
{
    char output[strlen(input)];
    strcpy(output, input);
    string Alphabet = "abcdefghijklmnopqrstuvwxyz";
    for (int i = 0; i < strlen(input); i++)
    {
        for (int j = 0; j < strlen(key); j++)
        {
            if (tolower(input[i]) == tolower(key[j]))
            {
                output[i] = Alphabet[j];
            }
        }
        if (isupper(input[i]) != 0)
        {
            output[i] = toupper(output[i]);
        }
    }
    printf("plaintext: %s\n", output);
}

char littlize(char input) 
{   
    if (input >= 'A' && input <= 'Z')
    {
        char new_char = input + 32;
        return new_char;
    }
    return input;
}

char capitalize(char input) 
{
    if (input >= 'a' && input <= 'z')
    {
        char new_char = input - 32;
        return new_char;
    }
    return input;
}
