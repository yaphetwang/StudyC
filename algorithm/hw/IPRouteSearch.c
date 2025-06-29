#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_N 10001
#define BUF_LEN 32
#define B_LEN 8

/*
输入：
192.168.0.3
6
10.166.50.0/23
192.0.0.0/8
10.255.255.255/32
192.168.0.1/24
127.0.0.0/8
192.168.0.0/24
输出：
192.168.0.1/24

输入：
10.110.32.77
2
127.0.0.1/8
0.0.0.0/0
输出：
0.0.0.0/0
*/

// 无用函数，没有实现
static void RouterSearch(char *dstIP, char **ipTable, int ipTableCnt, char *outBuf, int MaxOutBufLen)
{
    bool found = false;
    int maxMaskLen = 0;

    for (size_t i = 0; i < ipTableCnt; i++)
    {
        char *ip = ipTable[i];
        // strchr()函数查找字符串中第一个出现的指定字符
        char *mask = strchr(ip, '/');
        if (mask == NULL)
        {
            continue;
        }
        *mask = '\0';
        char *maskStr = mask + 1;
        int maskLen = atoi(maskStr);

        if (maskLen > maxMaskLen)
        {
            // 比较dstIP和ip
        }
    }

    if (!found)
    {
        strcpy(outBuf, "empty");
    }
}

// 取ip地址 二进制表示中第n位的值
unsigned char GetN(unsigned int ips[], int n)
{
    return (ips[n / 8] >> (7 - n % 8)) & 1;
}

// 比对两个ip地址二进制表示前n位是否相同
bool compareIp(unsigned int ips1[], unsigned int ips2[], int n)
{
    for (size_t i = 0; i < n; i++)
    {
        if (GetN(ips1, i) != GetN(ips2, i))
        {
            return false;
        }
    }

    return true;
}

// 第二种方法，纯手工计算ip地址的二进制表示，然后比较前n位是否相同
// 计算一个整数的二进制表示
char *getBinary(int num)
{
    // malloc()函数分配一块内存，返回一个指针，指向这块内存的首地址, 也是有下标的
    char *b = (char *)malloc(sizeof(char) * B_LEN);
    memset(b, '0', sizeof(char) * B_LEN);
    // char tmp[B_LEN] = {'0'}; 一定要初始化，特别是数组不一定全部填充的情况
    int len = B_LEN;
    while (num != 0)
    {
        int d = num % 2;
        num = num / 2;
        b[--len] = d + '0';
        // b[--len] = d; 这样也可以，for循环打印使用%d
    }
    // for (size_t j = 0; j < B_LEN; j++)
    // {
    //     b[j] = tmp[j];
    // }
    return b;
}

// 计算一个ip地址的二进制表示
char *getIpBinary(int ips[])
{
    char *b = (char *)malloc(sizeof(char) * B_LEN * 4);
    memset(b, '0', B_LEN * 4);
    int index = 0;
    for (size_t i = 0; i < 4; i++)
    {
        char *tmp = getBinary(ips[i]);
        // strcat_s(b, B_LEN * 4, tmp); //这样不可以，有不可预期的值
        // strncat_s(b, B_LEN * 4, tmp, B_LEN); //这样不可以
        // strcat(b, tmp); // 这样不可以
        for (size_t j = 0; j < B_LEN; j++)
        {
            b[index++] = tmp[j];
        }
    }

    return b;
}

bool compareIp2(unsigned int ips1[], unsigned int ips2[], int n)
{
    char *b1 = (char *)getIpBinary(ips1);
    char *b2 = (char *)getIpBinary(ips2);

    for (size_t i = 0; i < 32; i++)
    {
        printf("%c", b1[i]);
    }

    for (size_t i = 0; i < 32; i++)
    {
        printf("%c", b2[i]);
    }

    for (size_t i = 0; i < n; i++)
    {
        if (b1[i] != b2[i])
        {
            return false;
        }
    }

    return true;
}

static void RouterSearch1(char *dstIP, char **ipTable, int ipTableCnt, char *outBuf, int MaxOutBufLen)
{
    strcpy_s(outBuf, MaxOutBufLen, "empty");
    unsigned int dst[4];
    if (sscanf(dstIP, "%u.%u.%u.%u", &dst[0], &dst[1], &dst[2], &dst[3]) != 4)
    {
        return;
    }

    int maxM = -1;
    for (size_t i = 0; i < ipTableCnt; i++)
    {
        unsigned int tmp[4];
        int mskLen;
        sscanf(ipTable[i], "%u.%u.%u.%u/%d", &tmp[0], &tmp[1], &tmp[2], &tmp[3], &mskLen);
        // if (mskLen > maxM && compareIp(dst, tmp, mskLen))
        if (mskLen > maxM && compareIp2(dst, tmp, mskLen))
        {
            maxM = mskLen;
            strcpy_s(outBuf, MaxOutBufLen, ipTable[i]);
        }
    }
}

int main()
{
    // static char dstIp[BUF_LEN];
    // if (scanf("%s\n", dstIp) == 0)
    // {
    //     return -1;
    // }

    // int n = 0;
    // if (scanf("%d\n", &n) != 1)
    // {
    //     return -1;
    // }

    // static char ipTableBuf[MAX_N][BUF_LEN];
    // static char *ipTable[MAX_N];
    // for (size_t i = 0; i < n; i++)
    // {
    //     if (scanf("%s\n", ipTableBuf[i]) == 0)
    //     {
    //         return -1;
    //     }
    //     ipTable[i] = ipTableBuf[i];
    // }

    // char outBuf[BUF_LEN] = {0};
    // RouterSearch1(dstIp, ipTable, n, outBuf, BUF_LEN);
    // printf("%s\n", outBuf);

    int num = 192;
    char *res = (char *)getBinary(num);
    // printf("%s\n", res);
    for (size_t i = 0; i < B_LEN; i++)
    {
        printf("%c", res[i]);
    }
    printf("\n");

    int ips[4] = {192, 168, 0, 3};
    char *ipBinary = (char *)getIpBinary(ips);
    // printf("%s\n", ipBinary); //好奇怪，为什么打印出来多余的字符
    for (size_t i = 0; i < B_LEN * 4; i++)
    {
        printf("%c", ipBinary[i]);
    }
    printf("\n");

    return 0;
}