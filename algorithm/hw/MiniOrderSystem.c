#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define SYSTEM_LEN 1000
#define GOODS_LEN 1000
#define GOOD_LEN 10

typedef struct
{
    char good[GOOD_LEN];
} GOOD;

typedef struct
{
    int customerId;
    GOOD goods[GOODS_LEN];
} OrderSystem;

typedef struct
{
    int customerId;
    int count;
} OrderCount;

int equal(char *str1, char *str2)
{
    // 由于str2 是二维char数组取出的，是字符串，长度不为GOOD_LEN，该函数不能用
    for (size_t i = 0; i < GOOD_LEN; i++)
    {
        if (str1[i] != str2[i])
        {
            return 1;
        }
    }
    return 0;
}

int equal2(char *str1, char *str2)
{
    // strcmp 相同返回0
    return strcmp(str1, str2);
}

static OrderSystem *OrderSystemCreate()
{
    OrderSystem *os = (OrderSystem *)malloc(sizeof(OrderSystem) * SYSTEM_LEN);
    memset(os, 0, sizeof(OrderSystem) * SYSTEM_LEN);
    return os;
}

static void OrderSystemOrder(OrderSystem *os, int customerId, char **goods, size_t goodsSize)
{
    for (size_t i = 0; i < SYSTEM_LEN; i++)
    {
        // 找到空闲位置
        if (os[i].customerId == 0)
        {
            os[i].customerId = customerId;
            int index = 0;
            for (size_t j = 0; j < goodsSize; j++)
            {
                char *good = goods[j];
                strcpy(os[i].goods[index++].good, good);
            }
            break;
        }

        if (os[i].customerId == customerId)
        {
            for (size_t j = 0; j < goodsSize; j++)
            {
                // 取出商品
                char *good = goods[j];
                for (size_t k = 0; k < GOODS_LEN; k++)
                {
                    if (os[i].goods[k].good[0] == 0)
                    {
                        strcpy(os[i].goods[k].good, good);
                        break;
                    }
                }
            }
            break;
        }
    }
}

static void OrderSystemDeliver(OrderSystem *os, char **goods, size_t goodsSize)
{
    for (size_t j = 0; j < goodsSize; j++)
    {
        char *good = goods[j];

        // 找出哪个客户先添加该商品，先循环商品位置
        for (size_t k = 0; k < GOODS_LEN; k++)
        {
            int match = 0;
            for (size_t i = 0; i < SYSTEM_LEN; i++)
            {
                if (os[i].goods[k].good[0] != 0 && equal2(os[i].goods[k].good, good) == 0)
                {
                    memset(os[i].goods[k].good, 0, GOOD_LEN);
                    match = 1;
                    break;
                }
            }
            if (match)
            {
                break;
            }
        }
    }
}

int cmp(const void *a, const void *b)
{
    OrderCount *orderCount1 = (OrderCount *)a;
    OrderCount *orderCount2 = (OrderCount *)b;
    if (orderCount1->count != orderCount2->count)
    {
        return (orderCount2->count - orderCount1->count);
    }
    else
    {
        return (orderCount1->customerId - orderCount2->customerId);
    }
}

static int OrderSystemQuery(OrderSystem *os)
{
    // for (size_t i = 0; i < SYSTEM_LEN; i++)
    // {
    //     if (os[i].customerId > 0)
    //     {
    //         for (size_t j = 0; j < GOODS_LEN; j++)
    //         {
    //             if (os[i].goods[j].good[0] != 0)
    //             {
    //                 for (size_t k = 0; k < GOOD_LEN; k++)
    //                 {
    //                     printf("%c", os[i].goods[j].good[k]);
    //                 }
    //                 printf(" ");
    //             }
    //         }
    //         printf("\n");
    //     }
    // }

    OrderCount orderCounts[SYSTEM_LEN] = {0};
    int index = 0;

    for (size_t i = 0; i < SYSTEM_LEN; i++)
    {
        if (os[i].customerId != 0)
        {
            int count = 0;
            GOOD *goods = os[i].goods;
            for (size_t k = 0; k < GOODS_LEN; k++)
            {
                if (os[i].goods[k].good[0] != 0)
                {
                    count++;
                }
            }

            orderCounts[index].customerId = os[i].customerId;
            orderCounts[index].count = count;
            index++;
        }
    }

    qsort(orderCounts, index, sizeof(OrderCount), cmp);

    if (orderCounts[0].count == 0)
    {
        return -1;
    }

    return orderCounts[0].customerId;
}

static void OrderSystemFree(OrderSystem *os)
{
    free(os);
}

int main()
{

    OrderSystem *os = OrderSystemCreate();
    // printf("null ");
    // OrderSystemOrder(os, 99, (char *[]){"gd1000"}, 1);
    // printf("null ");
    // OrderSystemOrder(os, 88, (char *[]){"gd666", "gd555"}, 2);
    // printf("null ");
    // OrderSystemOrder(os, 99, (char *[]){"gd666"}, 1);
    // printf("null ");

    // int res = OrderSystemQuery(os);
    // printf("%d ", res);

    // OrderSystemDeliver(os, (char *[]){"gd666"}, 1);
    // printf("null ");

    // int res1 = OrderSystemQuery(os);
    // printf("%d ", res1);

    printf("null ");
    OrderSystemOrder(os, 101, (char *[]){"food", "clothes", "trans", "clothes"}, 4);
    printf("null ");
    OrderSystemOrder(os, 102, (char *[]){"house", "entertain"}, 2);
    printf("null ");

    OrderSystemDeliver(os, (char *[]){"clothes", "house"}, 2);
    printf("null ");
    OrderSystemDeliver(os, (char *[]){"entertain", "trans"}, 2);
    printf("null ");

    OrderSystemOrder(os, 102, (char *[]){"house"}, 1);
    printf("null ");

    int res = OrderSystemQuery(os);
    printf("%d ", res);

    return 0;
}