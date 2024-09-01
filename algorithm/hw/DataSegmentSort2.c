#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_N 200
#define DATA_BUF_LEN 16
#define OUT_BUF_LEN 512

struct DataSec
{
    int type;
    int index;
    int endFlag;
    int len;
    char data[DATA_BUF_LEN];
};

void Recobine(struct DataSec *dataSec, int n, int dstType, char *outBuf, int outBufLen)
{
    // 遍历前n个数据段即可
    struct DataSec dataTmp[MAX_N];
    int flag = 0;
    int index_count = 0;
    while (flag == 0) // 直到最后一个endFlag==1退出while循环
    {
        for (int i = 0; i < n; i++)
        {
            // 每一次循环只要找到一个符合条件的，就退出for循环，重复的不用管
            if (dataSec[i].type == dstType && dataSec[i].index == index_count)
            {
                dataTmp[index_count] = dataSec[i];
                index_count++;
                flag = dataSec[i].endFlag; // 最后一个才为1
                break;
            }

            if (i == n - 1)
            {
                // 遍历完未找到符合条件的，退出while循环，防止死循环
                flag = -1;
            }
        }
    }

    if (index_count == 0 || flag == -1)
    {
        strcpy(outBuf, "NA");
    }
    else
    {
        for (int i = 0; i < index_count; i++)
        {
            strcat(outBuf, dataTmp[i].data);
        }
    }
}

int main()
{
    int n;
    scanf("%d", &n);

    static struct DataSec dataSec[MAX_N];
    int i;
    for (i = 0; i < n; i++)
    {
        scanf("%d", &dataSec[i].type);
        scanf("%d", &dataSec[i].index);
        scanf("%d", &dataSec[i].endFlag);
        scanf("%d", &dataSec[i].len);
        scanf("%s", dataSec[i].data);
    }

    int dstType;
    scanf("%d", &dstType);

    static char outBuf[OUT_BUF_LEN];
    Recobine(dataSec, n, dstType, outBuf, OUT_BUF_LEN);
    (void)printf("%s\n", outBuf);
    return 0;
}