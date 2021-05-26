#include <stdio.h>
#include <cs50.h>
// Asking for the name of the user, then greetign him!
int main(void)
{
    string name = get_string("What is your name?:\n");
    printf("hello, %s\n", name);
}