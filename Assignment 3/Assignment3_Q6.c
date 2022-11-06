#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 200 // The number digit limitation

typedef struct _btnode
{
    int item;
    struct _btnode *left;
    struct _btnode *right;
} BTNode; // You should not change the definition of BTNode

typedef struct _node
{
    BTNode *item;
    struct _node *next;
} StackNode;

typedef struct _stack
{
    int size;
    StackNode *head;
} Stack;

void deleteTree(BTNode **root);

void createExpTree(BTNode **root, char *prefix);
void printTree(BTNode *node);
void printTreePostfix(BTNode *node);
double computeTree(BTNode *node);

void push(Stack *sPtr, BTNode *item);
int pop(Stack *sPtr);
BTNode *peek(Stack s);
int isEmptyStack(Stack s);

int main()
{
    char prefix[SIZE];
    BTNode *root = NULL;

    // printf("Enter an prefix expression:\n");
    gets(prefix);

    createExpTree(&root, prefix);

    // printf("The Infix Expression:\n");
    printTree(root);
    printf("\n");
    // printf("The Postfix (Reverse Polish) Expression:\n");
    printTreePostfix(root);
    printf("\n");
    // printf("Answer ");
    printf("%.2f\n", computeTree(root));
    deleteTree(&root);
    return 0;
}

void push(Stack *sPtr, BTNode *item)
{
    StackNode *newNode;
    newNode = malloc(sizeof(StackNode));
    newNode->item = item;
    newNode->next = sPtr->head;
    sPtr->head = newNode;
    sPtr->size++;
}

int pop(Stack *sPtr)
{
    if (sPtr == NULL || sPtr->head == NULL)
    {
        return 0;
    }
    else
    {
        StackNode *temp = sPtr->head;
        sPtr->head = sPtr->head->next;
        free(temp);
        sPtr->size--;
        return 1;
    }
}

BTNode *peek(Stack s)
{
    return s.head->item;
}

int isEmptyStack(Stack s)
{
    if (s.size == 0)
        return 1;
    else
        return 0;
}

void deleteTree(BTNode **root)
{
    BTNode *temp;
    if (*root != NULL)
    {
        temp = (*root)->right;
        deleteTree(&((*root)->left));
        free(*root);
        *root = NULL;
        deleteTree(&temp);
    }
}

//

#include <ctype.h>

void createExpTree(BTNode **root, char *prefix)
{
    *root = malloc(sizeof(BTNode));
    char *str = strtok(prefix, " "); // new string, items separated by whitespaces

    if (isdigit(str[0])) // if operand
    {
        (*root)->item = atoi(str);
        (*root)->left = NULL;
        (*root)->right = NULL;
    }
    else // if operator
    {
        (*root)->item = str[0]; // put operator at top
        createExpTree(&(*root)->left, NULL);
        createExpTree(&(*root)->right, NULL);
    }
}

void printTree(BTNode *node)
{
    if (node == NULL)
        return;

    printTree(node->left);                         // go left
    if (node->left == NULL && node->right == NULL) // print middle
        printf("%d ", node->item);
    else
        printf("%c ", (char)(node->item));
    printTree(node->right); // go right
}

void printTreePostfix(BTNode *node)
{
    if (node == NULL)
        return;

    printTreePostfix(node->left);                  // go left
    printTreePostfix(node->right);                 // go right
    if (node->left == NULL && node->right == NULL) // print middle
        printf("%d ", node->item);
    else
        printf("%c ", (char)(node->item));
}

double computeTree(BTNode *node)
{
    if (node == NULL)
        return 0;

    if (node->left == NULL && node->right == NULL) // reached leaf node
        return node->item;

    double l_val = computeTree(node->left);  // go left until reach the bottom
    double r_val = computeTree(node->right); // go right until reach bottom

    switch ((char)node->item)
    {
    case '+':
        return l_val + r_val;
        break;
    case '-':
        return l_val - r_val;
        break;
    case '*':
        return l_val * r_val;
        break;
    case '/':
        return l_val / r_val;
        break;
    }
}