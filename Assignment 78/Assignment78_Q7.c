#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int **M;

int max(int a, int b)
{
    if (a > b)
        return a;
    else
        return b;
}

int bottom_up_dp(int n, int *s, int *v, int C)
{
    for (int i = 1; i <= n; i++)
        for (int j = 0; j <= C; j++)
        {
            if (s[i] > j) // item larger than current capacity
                M[i][j] = M[i - 1][j];
            else
                M[i][j] = max(M[i - 1][j], M[i - 1][j - s[i]] + v[i]);
        }

    return M[n][C];
}

int main()
{
    int n, C;
    int function;
    int *s;
    int *v;
    int i, j;
    printf("Enter the number of items n:\n");
    scanf("%d", &n);
    printf("Enter the capacity C:\n");
    scanf("%d", &C);
    s = (int *)malloc(sizeof(int) * (n + 1));
    v = (int *)malloc(sizeof(int) * (n + 1));

    M = (int **)malloc(sizeof(int *) * (n + 1));

    for (int i = 0; i <= n; i++)
        M[i] = (int *)malloc(sizeof(int) * (C + 1));

    for (int j = 0; j <= C; j++)
        M[0][j] = 0;

    printf("Enter the sizes of items (as a list, separate by spacing:\n");
    for (i = 1; i <= n; i++)
        scanf("%d", &s[i]);
    s[0] = 0;

    printf("Enter the values of items (as a list, separate by spacing:\n");
    for (i = 1; i <= n; i++)
        scanf("%d", &v[i]);
    v[0] = 0;

    printf("The maximum value is: %d \n", bottom_up_dp(n, s, v, C));
}