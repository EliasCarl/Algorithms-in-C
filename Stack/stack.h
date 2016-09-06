typedef struct node
{
    int value;
    int key;
    struct node* next;
} node;

void initialize(node*);
void insert_beginning(node*);
void print_list();
node* pop();
