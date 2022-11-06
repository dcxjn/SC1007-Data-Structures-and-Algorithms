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
    CDblListNode *temp = CDLL.head;
    int nodecount = 0;
    if (CDLL.head != NULL)
    {
        do
        {
            temp = temp->next;
            nodecount++;
        } while (temp != CDLL.head);
    }

    if (nodecount < 2)
        return 0;
    else if (nodecount == 2)
        return 1;
    else if (nodecount == 3)
        return 3;

    CDblListNode *head = CDLL.head;
    CDblListNode *current = CDLL.head;

    int totalcount = 0;

    do // loop to change current
    {
        CDblListNode *compare = current->pre->pre; // update compare everytime current is shifted

        do // loop to change compare
        {
            int count = 0;

            int min;
            if (current->item < compare->item)
            {
                min = current->item;
            }
            else
            {
                min = compare->item;
            }

            CDblListNode *traverse1 = current->pre;
            while (1) // check left side first
            {
                if (traverse1->item > min)
                    break;

                traverse1 = traverse1->pre;

                if (traverse1 == compare)
                {
                    count += 1;
                    break;
                }
            }

            if (count == 0) // if visible pair is found, do not execute right side traversal
            {
                CDblListNode *traverse2 = current->next;
                while (1)
                {
                    if (traverse2->item > min)
                        break;

                    traverse2 = traverse2->next;

                    if (traverse2 == compare)
                    {
                        count += 1;
                        break;
                    }
                }
            }

            totalcount += count;
            compare = compare->pre;

        } while (compare != current->next); // stop when compare goes to node

        current = current->pre; // shift current

    } while (current != head); // stop when current goes back to original node

    return nodecount + totalcount / 2;
}