#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

// Hashes the word (hash function posted on reddit by delipity)
unsigned int hash(const char *word)
{
    char varword[45];
    strcpy(varword,word);
        for (int i = 0; i < sizeof(varword); i++)
        {
            if ((varword[i] >= 'A') && (varword[i] <= 'Z'))
            {
                varword[i] = tolower(varword[i]);
            }
        }
    unsigned int result = 0;
    for (int i = 0, n = strlen(varword); i < n; i++)
    {
        result = (result << 2) ^ varword[i];
    }
    return result % 65536;
}

int main (void){
    FILE *f = fopen("text.txt","r");
    char word[45];
    while (fscanf(f,"%s",word) != EOF){

        printf("%s: ",word);
        printf("%i\n",hash(word));
    }

}






















// #include <stdio.h>
// #include <stdlib.h>

// int main(void)
// {
//     typedef struct node
//     {
//         int number;
//         struct node *next;
//     }
//     node;

//     node* list;
//     node *n = malloc(sizeof(node));
//     if (n != NULL){
//         n-> number = 2;
//         n -> next = NULL;
//     }
//     list = n;

//     n = malloc(sizeof(node));
//     if (n != NULL){
//         n->number = 4;
//         n->next = NULL;
//     }
//     node *tmp = list;
//     while (tmp->next !=NULL){
//         tmp = tmp->next;
//     }
//     tmp->next = n;
//     n = malloc(sizeof(node));
//     if (n != NULL){
//         n->number = 1;
//         n->next = list;
//     }
//     list = n;
//     n = malloc(sizeof(node));
//     if (n != NULL){
//         n->number = 3;
//         n->next = (list->next)->next;
//     }
//     list->next->next = n;
//     tmp = list;
//     int i = 0;
//     // while (i < 0){
//     //     tmp = tmp->next;
//     //     i ++;
//     // }
//     printf("%i\n",tmp->number);
//     // printf("%i\n",(list->next)->number);
//     // printf("%i\n",((list->next)->next)->number);
//     // printf("%i\n",(((list->next)->next)->next)->number);


// }
