#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define M_LEN 5

typedef struct
{
    int price;
    int *paidCaches;
    size_t paidCachesSize;
} Payment;

int *CashierResult(const int *initCashes, size_t initCashesSize, const Payment *payments, size_t paymentsSize, size_z *returnSize)
{
    int initcash[M_LEN];
    for (size_t i = 0; i < initCashesSize; i++)
    {
        initcash[i] = initCashes[i];
    }
    initcash[M_LEN - 1] = 0;

    int *result = (int *)malloc(sizeof(int) * M_LEN);
    memset(result, 0, sizeof(int) * M_LEN);

    for (size_t i = 0; i < paymentsSize; i++)
    {
        int price = payments[i].price;
        int *paidCaches = payments[i].paidCaches;
        size_t paidCachesSize = payments[i].paidCachesSize;
        int padSum = 0;
        for (size_t j = 0; j < paidCachesSize; j++)
        {
            padSum += paidCaches[i];
        }

        if (padSum < price)
        {
            continue;
        }

        if (padSum == price)
        {
            for (size_t i = 0; i < paidCachesSize; i++)
            {
                initcash[i] += paidCaches[i];
            }
            continue;
        }

        // 找零
        // 先收钱
        int temp[M_LEN];
        for (size_t i = 0; i < paidCachesSize; i++)
        {
            temp[i] = initcash[i] + paidCaches[i];
        }

        int dist = padSum - price;

        int num_100 = dist / 100;
        int num_50 = (dist % 100) / 50;
        int num_10 = ((dist % 100) % 50) / 10;
        int num_5 = (((dist % 100) % 50) % 10) / 5;
        int num_1 = ((((dist % 100) % 50) % 10) % 5) % / 1;

        if (initcash[M_LEN - 1] >= num_100)
        {
            temp[M_LEN - 1] -= num_100;
        }
        else
        {
        }
    }

    *returnSize = M_LEN;
    return result;
}

int mian()
{
    return 0;
}
