#include <stdio.h>
#include <stdlib.h>

#define MAX_N 120

typedef struct _btnode
{
    char id;
    struct _btnode *left;
    struct _btnode *right;
} BTNode;

void buildTree(BTNode **node, char *preO, char *postO);
void inOrder(BTNode *cur);
void preOrder(BTNode *cur);
void postOrder(BTNode *cur);

int main()
{
    char preO[MAX_N];
    char postO[MAX_N];
    scanf("%s", preO);
    scanf("%s", postO);

    BTNode *root = NULL;
    buildTree(&root, preO, postO);
    if (root == NULL)
        printf("error\n");
    preOrder(root);
    printf("\n");
    postOrder(root);
    printf("\n");

    inOrder(root);
    printf("\n");

    return 0;
}
void inOrder(BTNode *cur)
{
    if (cur == NULL)
        return;

    inOrder(cur->left);
    printf("%c", cur->id);
    inOrder(cur->right);
}
void preOrder(BTNode *cur)
{
    if (cur == NULL)
        return;

    printf("%c", cur->id);
    preOrder(cur->left);
    preOrder(cur->right);
}

void postOrder(BTNode *cur)
{
    if (cur == NULL)
        return;

    postOrder(cur->left);
    postOrder(cur->right);
    printf("%c", cur->id);
}

//

#include <string.h>

BTNode *insertBTNode(char c);

void buildTree(BTNode **node, char *preO, char *postO)
{
    char *left_pre = (char *)malloc(sizeof(char) * MAX_N);
    char *left_post = (char *)malloc(sizeof(char) * MAX_N);
    char *right_pre = (char *)malloc(sizeof(char) * MAX_N);
    char *right_post = (char *)malloc(sizeof(char) * MAX_N);

    // preO and postO empty
    if (preO[0] == '\0' || postO[0] == '\0')
        return;

    // first item from preO as head node
    *node = insertBTNode(preO[0]);

    // find length of string
    int len = strlen(preO);

    // only one item in preO/postO
    if (len == 1)
        return;

    // locate in postO the index of second item in preO
    int index = 0;
    while (postO[index] != preO[1])
        index += 1;

    // postorder for left subtree
    int i, j;
    for (i = 0, j = 0; i <= index; i++, j++)
    {
        left_post[i] = postO[j];
    }
    left_post[i + 1] = '\0';

    // preorder for left subtree
    int x, y;
    for (x = 0, y = 1; x <= index; x++, y++)
    {
        left_pre[x] = preO[y];
    }
    left_pre[x + 1] = '\0';

    if (index == len - 2) // if there is no right subtree
    {
        right_post[0] = '\0';
        right_pre[0] = '\0';
    }
    else
    {
        // postorder for right subtree
        int a, b;
        for (a = 0, b = index + 1; b <= len - 2; a++, b++)
        {
            right_post[a] = postO[b];
        }
        right_post[a + 1] = '\0';

        // preorder for right subtree
        int m, n;
        for (m = 0, n = index + 2; n <= len - 1; m++, n++)
        {
            right_pre[m] = preO[n];
        }
        right_pre[m + 1] = '\0';
    }

    // call recursively for left and right
    buildTree(&(*node)->left, left_pre, left_post);
    buildTree(&(*node)->right, right_pre, right_post);
}

BTNode *insertBTNode(char c)
{
    BTNode *newNode = (BTNode *)malloc(sizeof(BTNode));
    newNode->id = c;
    newNode->left = newNode->right = NULL;
    return newNode;
}