#include <stdio.h>
#include <stdlib.h>

#include "stack.h"

node* head = NULL;

node* create_node(int value, int key)
{
    node *new_node = malloc(sizeof(node));
    new_node->value = value;
    new_node->key = key;
    new_node->next = NULL;
    return new_node;
}

void initialize(node* node)
{
    if (head != NULL)
    {
        printf("Can't initialize an existing list\n");
    }
    head = node;
}

void insert_beginning(node* node)
{
    node->next = head;
    head = node;
}

node* pop()
{
    node* popped = head;
    head = head->next;
    return popped;
}

void print_list()
{
    /* A counter for convenient visualization */
    int i = 0;

    node* current = head;
    while (current != NULL)
    {
        printf("Element: %-2d ", i++);
        printf("[Key: %d, Data: %d ", current->key, current->value);

        /* Some logic for printing NULL string if next == NULL */
        if (current->next == NULL)
        {
            printf("Next: NULL]\n");
        }
        else
        {
            printf("Next: %d]\n", current->next->key);
        }

        current = current->next;
    } 
}

int main(void)
{
    /*
     * Create some test nodes.
     */

    node* first_node = create_node(132,1);
    node* second_node = create_node(541,2);
    node* third_node = create_node(230,3);

    /*
     * Some testing...
     */

    initialize(first_node);
    insert_beginning(second_node);
    insert_beginning(third_node);

    print_list();

    printf("\nPopping first...\n\n");
    pop();

    print_list();

}
