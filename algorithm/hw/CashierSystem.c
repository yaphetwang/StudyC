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

int *CashierResult(const int *initCashes, size_t initCashesSize, const Payment *payments, size_t paymentsSize, size_t *returnSize)
{
    int *initCash = (int *)malloc(sizeof(int) * M_LEN);
    memset(initCash, 0, sizeof(int) * M_LEN);
    for (int i = 0; i < initCashesSize; i++)
    {
        initCash[i] = initCashes[i];
    }
    initCash[M_LEN - 1] = 0;

    int type[] = {1, 5, 10, 50, 100};
    for (int i = 0; i < paymentsSize; i++)
    {
        int price = payments[i].price;
        int *paidCaches = payments[i].paidCaches;
        size_t paidCachesSize = payments[i].paidCachesSize;
        int padSum = 0;
        for (int j = 0; j < paidCachesSize; j++)
        {
            padSum += paidCaches[j] * type[j];
        }

        if (padSum < price)
        {
            continue;
        }

        if (padSum == price)
        {
            for (int i = 0; i < paidCachesSize; i++)
            {
                initCash[i] += paidCaches[i];
            }
            continue;
        }

        // 找零 先收钱
        int temp[M_LEN] = {0};
        for (int i = 0; i < paidCachesSize; i++)
        {
            temp[i] = initCash[i] + paidCaches[i];
        }

        int dist = padSum - price;
        for (int i = M_LEN - 1; i >= 0; i--)
        {
            while (dist >= type[i] && temp[i] > 0)
            {
                temp[i] -= 1;
                dist -= type[i];
            }

            if (dist == 0)
            {
                break;
            }
        }
        if (dist > 0)
        {
            continue;
        }
        else
        {
            for (int i = 0; i < paidCachesSize; i++)
            {
                initCash[i] = temp[i];
            }
        }
    }

    *returnSize = M_LEN;
    return initCash;
}

int main()
{
    int initCashes[] = {5, 2, 5, 1};

    Payment *payments = malloc(sizeof(Payment) * 3);
    payments[0].price = 47;
    payments[0].paidCaches = (int *)malloc(sizeof(int) * 5);
    payments[0].paidCaches[0] = 0;
    payments[0].paidCaches[1] = 0;
    payments[0].paidCaches[2] = 0;
    payments[0].paidCaches[3] = 0;
    payments[0].paidCaches[4] = 1;
    payments[0].paidCachesSize = 5;
    payments[1].price = 2;
    payments[1].paidCaches = (int *)malloc(sizeof(int) * 5);
    payments[1].paidCaches[0] = 0;
    payments[1].paidCaches[1] = 1;
    payments[1].paidCaches[2] = 0;
    payments[1].paidCaches[3] = 0;
    payments[1].paidCaches[4] = 0;
    payments[1].paidCachesSize = 5;
    payments[2].price = 1;
    payments[2].paidCaches = (int *)malloc(sizeof(int) * 5);
    payments[2].paidCaches[0] = 1;
    payments[2].paidCaches[1] = 0;
    payments[2].paidCaches[2] = 0;
    payments[2].paidCaches[3] = 1;
    payments[2].paidCaches[4] = 0;
    payments[2].paidCachesSize = 5;

    size_t initCashesSize = sizeof(initCashes) / sizeof(initCashes[0]);
    size_t num = 0;
    int *result = (int *)CashierResult(initCashes, initCashesSize, payments, 3, &num);
    for (size_t i = 0; i < num; i++)
    {
        printf("%d ", result[i]);
    }

    // int initCashes[] = {544, 940, 902, 153};

    // Payment *payments = malloc(sizeof(Payment) * 4);
    // payments[0].price = 257;
    // payments[0].paidCaches = (int *)malloc(sizeof(int) * 5);
    // payments[0].paidCaches[0] = 477;
    // payments[0].paidCaches[1] = 35;
    // payments[0].paidCaches[2] = 48;
    // payments[0].paidCaches[3] = 504;
    // payments[0].paidCaches[4] = 35;
    // payments[0].paidCachesSize = 5;
    // payments[1].price = 897;
    // payments[1].paidCaches = (int *)malloc(sizeof(int) * 5);
    // payments[1].paidCaches[0] = 280;
    // payments[1].paidCaches[1] = 725;
    // payments[1].paidCaches[2] = 896;
    // payments[1].paidCaches[3] = 448;
    // payments[1].paidCaches[4] = 3;
    // payments[1].paidCachesSize = 5;
    // payments[2].price = 744;
    // payments[2].paidCaches = (int *)malloc(sizeof(int) * 5);
    // payments[2].paidCaches[0] = 934;
    // payments[2].paidCaches[1] = 707;
    // payments[2].paidCaches[2] = 50;
    // payments[2].paidCaches[3] = 596;
    // payments[2].paidCaches[4] = 368;
    // payments[2].paidCachesSize = 5;
    // payments[3].price = 228;
    // payments[3].paidCaches = (int *)malloc(sizeof(int) * 5);
    // payments[3].paidCaches[0] = 257;
    // payments[3].paidCaches[1] = 56;
    // payments[3].paidCaches[2] = 86;
    // payments[3].paidCaches[3] = 935;
    // payments[3].paidCaches[4] = 872;
    // payments[3].paidCachesSize = 5;

    // size_t initCashesSize = sizeof(initCashes) / sizeof(initCashes[0]);
    // size_t num = 0;
    // int *result = (int *)CashierResult(initCashes, initCashesSize, payments, 4, &num);
    // for (size_t i = 0; i < num; i++)
    // {
    //     printf("%d ", result[i]);
    // }

    return 0;
}
