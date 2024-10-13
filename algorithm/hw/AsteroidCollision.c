#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/**
 * 精简版 栈 解法
 */
int *asteroidCollision(int *asteroids, int asteroidsSize, int *returnSize)
{
    int *stack = (int *)malloc(asteroidsSize * sizeof(int));
    memset(stack, 0, asteroidsSize * sizeof(int));
    int top = 0;

    for (int i = 0; i < asteroidsSize; i++)
    {
        bool live = true;
        while (live && top > 0 && stack[top - 1] > 0 && asteroids[i] < 0)
        {
            live = stack[top - 1] < -asteroids[i];
            if (stack[top - 1] <= -asteroids[i])
            {
                top--;
            }
        }

        if (live)
        {
            stack[top++] = asteroids[i];
        }
    }

    *returnSize = top;

    return stack;
}

/**
 * 笨拙版本  栈 解法
 */
int *asteroidCollision2(int *asteroids, int asteroidsSize, int *returnSize)
{
    int *stack = (int *)malloc(asteroidsSize * sizeof(int));
    memset(stack, 0, asteroidsSize * sizeof(int));
    int top = 0;

    *returnSize = top;

    return stack;
}

int main()
{
    int asteroids[] = {5, 10, -5};
    int asteroids1[] = {8, -8};
    int asteroids2[] = {10, 2, -5};
    int asteroids3[] = {-2, -1, 1, 2};
    int asteroidsSize = sizeof(asteroids) / sizeof(asteroids[0]);
    int *returnSize = malloc(sizeof(int));
    int *result = (int *)asteroidCollision(asteroids, asteroidsSize, returnSize);
    for (int i = 0; i < (*returnSize); i++)
    {
        printf("%d ", result[i]);
    }
    printf("\n");
    free(result);
    return 0;
}