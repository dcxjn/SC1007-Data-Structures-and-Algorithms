#include <stdio.h>
#include <stdlib.h>

#define SIZE 1000 // The size of the array

enum ExpType
{
    OPT,
    OPERAND
};

typedef struct _stackNode
{
    char item;
    struct _stackNode *next;
} StackNode;

typedef struct _stack
{
    int size;
    StackNode *head;
} Stack;

void push(Stack *sPtr, char item);
int pop(Stack *sPtr);
char peek(Stack s);
int isEmptyStack(Stack s);

typedef struct _listnode
{
    int item;
    enum ExpType type;
    struct _listnode *next;
} ListNode;

typedef struct _linkedlist
{
    int size;
    ListNode *head;
} LinkedList;

void insertNode(LinkedList *llPtr, int item, enum ExpType type);
int deleteNode(LinkedList *llPtr);
void removeAllNodes(LinkedList *llPtr);
int isEmptyLinkedList(LinkedList ll);

void in2PreLL(char *infix, LinkedList *inExpLL);

void printExpLL(LinkedList inExp);

int main()
{
    char infix[SIZE];

    // printf("Enter an infix expression:\n");
    scanf("%[^\n]%*c", infix);

    LinkedList inExpLL;
    inExpLL.head = NULL;
    inExpLL.size = 0;

    in2PreLL(infix, &inExpLL);

    printExpLL(inExpLL);

    removeAllNodes(&inExpLL);
    return 0;
}

void printExpLL(LinkedList inExpLL)
{
    ListNode *temp = NULL;
    temp = inExpLL.head;
    while (temp != NULL)
    {
        if (temp->type == OPERAND)
            printf(" %d ", temp->item);
        else
            printf(" %c ", (char)(temp->item));
        temp = temp->next;
    }
    printf("\n");
}

void insertNode(LinkedList *LLPtr, int item, enum ExpType type)
{
    ListNode *newNode;
    newNode = malloc(sizeof(ListNode));
    if (newNode == NULL)
        exit(0);

    newNode->item = item;
    newNode->type = type;
    newNode->next = LLPtr->head;
    LLPtr->head = newNode;
    LLPtr->size++;
}

int deleteNode(LinkedList *LLPtr)
{
    if (LLPtr == NULL || LLPtr->size == 0)
    {
        return 0;
    }
    else
    {
        ListNode *temp = LLPtr->head;
        LLPtr->head = LLPtr->head->next;

        free(temp);
        LLPtr->size--;
        return 1;
    }
}

int isEmptyLinkedList(LinkedList ll)
{
    if (ll.size == 0)
        return 1;
    else
        return 0;
}

void removeAllNodes(LinkedList *LLPtr)
{
    while (deleteNode(LLPtr))
        ;
}

void push(Stack *sPtr, char item)
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

char peek(Stack s)
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

#include <string.h>
#include <ctype.h>
int precedence(char operator);

int precedence(char operator)
{
    if (operator== '*' || operator== '/')
        return 2;
    else if (operator== '+' || operator== '-')
        return 1;
    else
        return 0;
}

void in2PreLL(char *infix, LinkedList *inExpLL)
{
    Stack s;
    s.head = NULL;
    s.size = 0;

    int i, j = 0;
    int len = strlen(infix);
    char c;
    char next;
    char prefix[SIZE];

    for (i = len - 1; i >= 0; i--)
    {
        c = infix[i];
        if (c != '\0')
        {
            switch (c)
            {
            case '*': // operators
            case '/':
            case '+':
            case '-':
                while (!isEmptyStack(s) && precedence(peek(s)) > precedence(c))
                {
                    prefix[j++] = ' ';
                    prefix[j++] = peek(s);
                    pop(&s);
                }
                push(&s, c);
                break;
            case ')':
                push(&s, c);
                push(&s, ' ');
                break;
            case '(':
                while (peek(s) != ')')
                {
                    prefix[j++] = ' ';
                    prefix[j++] = peek(s);
                    pop(&s);
                }
                pop(&s);
                break;
            default: // operand
                if (isdigit(infix[i + 1]) == 0)
                {
                    prefix[j++] = ' ';
                }
                prefix[j++] = c;
            }
        }
    }

    while (!isEmptyStack(s)) // add remaining operators to expression
    {
        prefix[j++] = ' ';
        prefix[j++] = peek(s);
        pop(&s);
    }
    prefix[j] = '\0';

    int k = 0;
    while (prefix[k] != '\0')
    {
        int num = 0;
        int count = 1;

        if (prefix[k] == ' ')
        {
            k++;
        }
        else if (isdigit(prefix[k]) == 0)
        {
            insertNode(inExpLL, prefix[k], OPT);
            k++;
        }
        else
        {
            while (prefix[k])
            {
                num += (prefix[k] - '0') * count;
                count *= 10;
                k++;

                if (prefix[k] == ' ')
                {
                    insertNode(inExpLL, num, OPERAND);
                    k++;
                    break;
                }
            }
        }
    }
}
