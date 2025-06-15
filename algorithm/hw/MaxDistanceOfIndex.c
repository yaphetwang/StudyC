#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// 一串数字，找出绝对值差为1的两个数的最大距离
// 这个跟 下标有关， 还不能直接排序

static int GetMaxDistance(const int *numbers, size_t numbersSize)
{
    int maxDistance = 0;
    for (int i = 0; i < numbersSize; i++)
    {
        for (int j = i + 1; j < numbersSize; j++)
        {
            int distance = abs(numbers[i] - numbers[j]);
            if (distance == 1)
            {
                maxDistance = abs(j - i) > maxDistance ? abs(j - i) : maxDistance;
            }
        }
    }

    return maxDistance;
}

int main(void)
{
    int numbers[] = {6, 4, 2, 5, 1, 3};
    int numbers2[] = {2, 3, 6, 5, 7, 1, 4};
    printf("%d\n", GetMaxDistance(numbers, sizeof(numbers) / sizeof(numbers[0])));
    printf("%d\n", GetMaxDistance(numbers2, sizeof(numbers2) / sizeof(numbers2[0])));
}