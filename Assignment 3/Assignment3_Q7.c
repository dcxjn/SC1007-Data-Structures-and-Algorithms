#include <stdio.h>
#include <stdlib.h>

typedef struct _btnode
{
    int nodeV;
    struct _btnode *left;
    struct _btnode *right;
} BTNode;

typedef struct _queuenode
{
    BTNode *node;
    struct _queuenode *next;
} QueueNode;

typedef struct _queue
{
    int size;
    QueueNode *head;
    QueueNode *tail;
} Queue;

void printBTNode(BTNode *root, int space, int left);
// Prototypes of Interface functions for Queue structure
void enqueue(Queue *qPtr, BTNode *node);
int dequeue(Queue *qPtr);
BTNode *getFront(Queue q);
int isEmptyQueue(Queue q);

int twoNodesCost(BTNode *node, int nodeV1, int nodeV2);

int main()
{
    BTNode *root = (BTNode *)malloc(sizeof(BTNode));

    Queue q;
    q.head = NULL;
    q.tail = NULL;
    q.size = 0;

    BTNode *node;
    enqueue(&q, root);

    int nodeV;
    char opL, opR;

    while (!isEmptyQueue(q))
    {
        scanf("%d %c %c", &nodeV, &opL, &opR);
        node = getFront(q);
        dequeue(&q);
        node->nodeV = nodeV;

        if (opL != '@')
        {
            node->left = (BTNode *)malloc(sizeof(BTNode));
            enqueue(&q, node->left);
        }
        else
            node->left = NULL;
        if (opR != '@')
        {
            node->right = (BTNode *)malloc(sizeof(BTNode));
            enqueue(&q, node->right);
        }
        else
            node->right = NULL;
    }

    int v1, v2;
    scanf("%d %d", &v1, &v2);
    int cost = twoNodesCost(root, v1, v2);

    printBTNode(root, 0, 0);

    printf("Distance is %d\n", cost);
    return 0;
}

void enqueue(Queue *qPtr, BTNode *node)
{
    QueueNode *newNode;
    newNode = malloc(sizeof(QueueNode));
    newNode->node = node;
    newNode->next = NULL;

    if (isEmptyQueue(*qPtr))
        qPtr->head = newNode;
    else
        qPtr->tail->next = newNode;

    qPtr->tail = newNode;
    qPtr->size++;
}

int dequeue(Queue *qPtr)
{
    if (qPtr == NULL || qPtr->head == NULL)
    { // Queue is empty or NULL pointer
        return 0;
    }
    else
    {
        QueueNode *temp = qPtr->head;
        qPtr->head = qPtr->head->next;
        if (qPtr->head == NULL) // Queue is emptied
            qPtr->tail = NULL;

        free(temp);
        qPtr->size--;
        return 1;
    }
}

BTNode *getFront(Queue q)
{
    return q.head->node;
}

int isEmptyQueue(Queue q)
{
    if (q.size == 0)
        return 1;
    else
        return 0;
}
void printBTNode(BTNode *root, int space, int left)
{
    if (root != NULL)
    {

        int i;
        for (i = 0; i < space - 1; i++)
            printf("|\t");

        if (i < space)
        {
            if (left == 1)
                printf("|---");
            else
                printf("|___");
        }

        printf("%d\n", root->nodeV);

        space++;
        printBTNode(root->left, space, 1);
        printBTNode(root->right, space, 0);
    }
}

//

#include <string.h>

BTNode *findLCA(BTNode *node, int nodeV1, int nodeV2);
int findPath(char *path, BTNode *root, int item);
int pathCost(char *path);

int twoNodesCost(BTNode *node, int nodeV1, int nodeV2)
{
    BTNode *LCA = findLCA(node, nodeV1, nodeV2);

    char *pathV1 = (char *)malloc(sizeof(char) * 120);
    char *pathV2 = (char *)malloc(sizeof(char) * 120);
    char *pathLCA = (char *)malloc(sizeof(char) * 120);

    findPath(pathV1, node, nodeV1);
    findPath(pathV2, node, nodeV2);
    findPath(pathLCA, node, LCA->nodeV);

    int costV1 = pathCost(pathV1);
    int costV2 = pathCost(pathV2);
    int costLCA = pathCost(pathLCA);

    int cost;

    if (LCA->nodeV != nodeV1 && LCA->nodeV == nodeV2)
        return cost = costV1 - costV2 + LCA->nodeV;
    else if (LCA->nodeV == nodeV1 && LCA->nodeV != nodeV2)
        return cost = costV2 - costV1 + LCA->nodeV;
    else if (LCA->nodeV == nodeV1 && LCA->nodeV == nodeV2)
        return cost = LCA->nodeV;
    else
        return cost = costV1 + costV2 - 2 * costLCA + LCA->nodeV;
}

BTNode *findLCA(BTNode *node, int nodeV1, int nodeV2)
{
    if (node == NULL)
        return NULL;

    if (node->nodeV == nodeV1 || node->nodeV == nodeV2)
    {
        return node;
    }
    else
    {
        BTNode *left = findLCA(node->left, nodeV1, nodeV2);
        BTNode *right = findLCA(node->right, nodeV1, nodeV2);

        if (left != NULL && right != NULL)
            return node;
        else if (left != NULL)
            return left;
        else
            return right;
    }
}

int findPath(char *path, BTNode *root, int item)
{
    if (root == NULL)
        return 0;

    // append node's value to path
    char *c = (char *)malloc(sizeof(char) * 10);
    c[0] = root->nodeV + '0';
    c[1] = '\0';
    strcat(path, c);

    // if it is the required node
    if (root->nodeV == item)
        return 1;

    // check whether the required node lies in the left subtree or right subtree
    if (findPath(path, root->left, item) || findPath(path, root->right, item))
        return 1;

    // required node does not lie in either left or right subtree of the current node,
    // remove current node's value from path
    path[strlen(path) - 1] = '\0';
    return 0;
}

int pathCost(char *path)
{
    int cost = 0;
    for (int x = 0; path[x] != '\0'; x++)
    {
        cost += (path[x] - '0');
    }
    return cost;
}