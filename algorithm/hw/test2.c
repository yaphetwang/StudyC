#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")

#define BUF_LEN 650000
#define MAX_N 102400

int proc(int *arr, int arrLen, int diff)
{
    int count = 0;
    int diffArr[MAX_N] = {0};
    for (size_t i = 0; i < arrLen; i++)
    {
        for (size_t j = i + 1; j < arrLen; j++)
        {
            if ((arr[i] - arr[j]) == diff || (arr[j] - arr[i]) == diff)
            {
                // if (diffArr[arr[i]] == 0 || diffArr[arr[j]] == 0)
                // {
                //     count++;
                //     diffArr[arr[i]] = 1;
                // }

                bool exist = (diffArr[arr[i]] == 0 || diffArr[arr[j]] == 0);
                count += exist;
                diffArr[arr[i]] = exist ? 1 : 0;
            }
        }
    }

    return count;
}

int main()
{
    int diff = 3, arrLen = 5;
    int arr[] = {1, 3, 2, 5, 4};
    int res = proc(arr, arrLen, diff);
    printf("%d\n", res);
    int diff1 = -1, arrLen1 = 3;
    int arr1[] = {1, 2, 3};
    int res1 = proc(arr1, arrLen1, diff1);
    printf("%d\n", res1);

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
