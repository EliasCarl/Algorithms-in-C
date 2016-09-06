#include <stdio.h>
#include <stdlib.h>

/* A node */
typedef struct node
{
    int data;
    int key;
    struct node* next;
} node;

/* List head */
node* head = NULL;

node* create_node(int data, int key)
{
    node *new_node = malloc(sizeof(node));
    new_node->data = data;
    new_node->key = key;
    new_node->next = NULL;
    return new_node;
}

void init_list(node* pNode)
{
    if (head != NULL)
    {
        printf("Can't initialize an existing list\n");
    }
    head = pNode;
}

/* Insert a node at the beginning of the list */
void insert_first(node* pNode)
{
    pNode->next = head;
    head = pNode;
}

/* Remove and return first element in the list */
node* pop_first()
{
    /* Store a pointer to the current head */
    node* popped = head;

    /* Make head point to the second element */
    head = head->next;

    /* Returned the previous head */
    return popped;
}

void print_list()
{
    /* A counter for convenient visualization */
    int i = 0;

    node* current = head;
    while (current != NULL)
    {
        node* next = current->next;

        printf("Element: %-2d ", i++);
        printf("[Key: %d, Data: %d ", current->key, current->data);

        /* Some logic for printing NULL string if next == NULL */

        if (next == NULL)
        {
            printf("Next: NULL]\n");
        }
        else
        {
            printf("Next: %d]\n", next->key);
        }

        current = next;
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

    init_list(first_node);
    insert_first(second_node);
    insert_first(third_node);

    print_list();

    printf("\nPopping first...\n\n");
    pop_first();

    print_list();

}
