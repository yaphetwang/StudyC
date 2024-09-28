#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_N 10001
#define BUF_LEN 32

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
*/

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

int main()
{
    static char dstIp[BUF_LEN];
    if (scanf(dstIp, "%s", dstIp) == 0)
    {
        return -1;
    }

    int n = 0;
    if (scanf("%d", &n) != 1)
    {
        return -1;
    }

    static char ipTableBuf[MAX_N][BUF_LEN];
    static char *ipTable[MAX_N];
    for (size_t i = 0; i < n; i++)
    {
        if (scanf(ipTableBuf[i], "%s", ipTableBuf[i]) == 0)
        {
            return -1;
        }
        ipTable[i] = ipTableBuf[i];
    }

    char outBuf[BUF_LEN] = {0};
    RouterSearch(dstIp, ipTable, n, outBuf, BUF_LEN);
    printf("%s\n", outBuf);

    return 0;
}