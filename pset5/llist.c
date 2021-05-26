#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct node{
    int number;
    struct node *next;
}
node;

// typedef enum { false, true } bool;

node* create(int number);
bool find (node* head, int val);
node* multiple_creation(int numbers[], int items_num);
void print_llist (node* head);
void destroy (node* head);

node* list;




int main (void){

    list = create(0);
    int arr[] = {1,2,3,4,5};
    list->next = multiple_creation(arr,5);
    destroy(list);
    print_llist(list);

    // printf("%i\n",list->number);
    // printf("%i\n",list->next->number);
    // printf("%i\n",list->next->next->number);
    // printf("%s", find(list,3) ? "true" : "false");

}

node* create(int number){
    node* n = malloc(sizeof(node));
    if (n == NULL){
        printf("OUT OF Memory");
        return NULL;
    }
        n->number = number;
        n->next = NULL;
        return n;
}
node* multiple_creation(int numbers[], int items_num){
    int i = 0;
    node *start;
    start = create(numbers[i]);
    node *tmp = start;
    i++;
    while ( i < items_num){
        tmp->next =create(numbers[i]);
        tmp = tmp->next;
        i++;

    }
    return start;
}

bool find (node* head, char* val){
    node* search = head;
    while (search != NULL){
        if (search -> number == val){
        return true;
        }
        search = search->next;
    }
    return false;
}

void print_llist (node* head){
    for (node*tmp = head; tmp != NULL; tmp = tmp->next){
        printf("%i\n",tmp->number);
    }
}

void destroy (node* head){
    while (head != NULL){
        node *tmp = head->next;
        free (head);
        head = tmp;
    }
}