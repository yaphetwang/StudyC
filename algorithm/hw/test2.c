#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <winsock2.h>

#define BUF_LEN 650000
#define MAX_N 102400

// 给定一个数组，求满足两个元素相减等于给定差值的所有不同组合的个数
// （1,3）和（3,1）是同一个组合

// 穷举法，元素多的用例会超时
int proc(int *arr, int arrLen, int diff)
{
    int count = 0;
    for (size_t i = 0; i < arrLen; i++)
    {
        for (size_t j = 0; j < arrLen; j++)
        {
            if (j != i && (arr[j] - arr[i]) == diff)
            {
                count++;
            }
        }
    }

    return count;
}

// 升序排序
int cmp(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b);
}

// 排序之后，滑动窗口，差值取绝对值
int proc2(int *arr, int arrLen, int diff)
{
    int count = 0;
    qsort(arr, arrLen, sizeof(int), cmp);

    int l = 0, r = 0;
    int d = abs(diff);
    while (r < arrLen)
    {
        if (arr[r] - arr[l] == d)
        {
            count++;
            r++;
            l++;
        }
        else if (arr[r] - arr[l] < d)
        {
            r++;
        }
        else
        {
            // 右值太大
            l++;
        }
    }

    return count;
}

int main()
{
    int diff = 3, arrLen = 5;
    int arr[] = {1, 3, 2, 5, 4};
    int res = proc2(arr, arrLen, diff);
    printf("proc:%d\n", res);
    int diff1 = -1, arrLen1 = 3;
    int arr1[] = {1, 2, 3};
    int res1 = proc2(arr1, arrLen1, diff1);
    printf("proc:%d\n", res1);

    // int res2 = proc2(arr, arrLen, diff);
    // printf("proc1:%d\n", res2);
    // int res3 = proc2(arr1, arrLen1, diff1);
    // printf("proc1:%d\n", res3);

    // ip地址和二进制相互转换
    // 将ip地址转换为二进制
    // char ip[16] = "192.168.1.1";
    // struct sockaddr_in addr;
    // inet_pton(AF_INET, ip, &addr.sin_addr);
    // unsigned char *ip_bin = (unsigned char *)&addr.sin_addr;
    // printf("ip: %s\n", ip);
    // printf("ip_bin: ");
    // for (int i = 0; i < 4; i++)
    // {
    //     printf("%02x ", ip_bin[i]);
    // }
    // printf("\n");

    char str[] = "apple,banana,cherry";
    char *token;
    char delimiters[] = ",";

    token = strtok(str, delimiters);
    while (token != NULL)
    {
        printf("%s\n", token);
        token = strtok(NULL, delimiters);
    }

    return 0;
}
