#include <stdio.h>
#include <stdlib.h>

typedef struct _dbllistnode
{
    int item;
    struct _dbllistnode *next;
    struct _dbllistnode *pre;
} CDblListNode;

typedef struct _dbllinkedlist
{
    int size;
    CDblListNode *head;
} CDblLinkedList;

void insertNode_AtFront(CDblLinkedList *ptrCDLL, int value);
void deleteList(CDblLinkedList *ptrCDLL);
void printList(CDblLinkedList CDLL);

int numMountainPairs(CDblLinkedList CDLL);

int main()
{
    CDblLinkedList himalayas;
    himalayas.head = NULL;
    himalayas.size = 0;

    int item;
    int i, cases;
    int numP;
    scanf("%d", &cases);
    for (i = 0; i < cases; i++)
    {
        while (scanf("%d", &item))
            insertNode_AtFront(&himalayas, item);
        scanf("%*s");

        numP = numMountainPairs(himalayas);
        printList(himalayas);
        printf("%d Pairs.\n", numP);

        deleteList(&himalayas);
    }
    return 0;
}

void insertNode_AtFront(CDblLinkedList *ptrCDLL, int value)
{
    // create a new node
    CDblListNode *newNode;
    newNode = (CDblListNode *)malloc(sizeof(CDblListNode));
    newNode->item = value;

    if (ptrCDLL->size == 0) // first node
    {
        newNode->next = newNode;
        newNode->pre = newNode;
        ptrCDLL->head = newNode;
    }
    else
    {
        newNode->next = ptrCDLL->head;
        newNode->pre = ptrCDLL->head->pre;

        newNode->pre->next = newNode; // update last node next link;
        ptrCDLL->head->pre = newNode;

        ptrCDLL->head = newNode;
    }
    ptrCDLL->size++;
}

void printList(CDblLinkedList CDLL)
{

    if (CDLL.head == NULL)
        return;

    CDblListNode *temp = CDLL.head;
    printf("Current List: ");

    while (temp->next != CDLL.head)
    {
        printf("%d ", temp->item);
        temp = temp->next;
    }
    printf("%d\n", temp->item);
}

void deleteList(CDblLinkedList *ptrCDLL)
{
    if (ptrCDLL->head == NULL)
        return;
    CDblListNode *cur = ptrCDLL->head;
    CDblListNode *temp;

    while (cur->next != ptrCDLL->head)
    {
        temp = cur->next;
        free(cur);
        cur = temp;
    }

    free(cur);
    ptrCDLL->head = NULL;
    ptrCDLL->size = 0;
}

int numMountainPairs(CDblLinkedList CDLL)
{
    CDblListNode *max, *temp1;
    temp1 = max = CDLL.head;
    if (CDLL.head != NULL)
    {
        do
        {
            if (temp1->item > max->item)
                max = temp1;
            temp1 = temp1->next;
        } while (temp1 != CDLL.head);
    }

    CDblListNode *temp2 = CDLL.head;
    int no_of_nodes = 0;
    if (CDLL.head != NULL)
    {
        do
        {
            temp2 = temp2->next;
            no_of_nodes++;
        } while (temp2 != CDLL.head);
    }

    int count = 0;
    CDblListNode *head = CDLL.head;
    CDblListNode *current = CDLL.head;

    while (1)
    {
        int i = 0;
        CDblListNode *traverse = current;

        while (traverse->next->item <= max->item)
        {
            traverse = traverse->next;
            i++;

            if (i == no_of_nodes - 3 || traverse->item > current->item)
                break;
        }

        while (traverse->pre != current)
        {
            if (traverse->item >= current->item)
            {
                count += 1;
            }
            traverse = traverse->pre;
        }
    }

    current = current->next;

    if (current == head)
        break;
}
return no_of_nodes + count;
}