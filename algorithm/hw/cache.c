#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_ID_CNT 1001

typedef struct
{
    int num;
    int nextPos;
} NextPosStru;

static int QueryDb(int cacheSize, int num, int *ids)
{
    int db_cnt = 0;

    NextPosStru cache[cacheSize];

    for (int i = 0; i < num; i++)
    {
        int id = ids[i];
        int nextPos = 0; // 这里的nextPos是下一个出现的位置
        for (int j = i + 1; j < num; j++)
        {
            // 找下一个出现的位置
            if (ids[j] == id)
            {
                nextPos = j;
                break;
            }
        }

        // 检查缓存
        bool isHit = false;
        for (int k = 0; k < cacheSize; k++)
        {
            if (cache[k].num == id)
            {
                // 命中缓存
                cache[k].nextPos = nextPos;
                isHit = true;
                break;
            }
        }
        if (isHit)
        {
            continue;
        }
        else
        {
            // 未命中缓存，需要查询数据库
            db_cnt++;
            // 缓存数据
            for (int k = 0; k < cacheSize - 1; k++)
            {
                cache[k] = cache[k + 1];
            }
            cache[cacheSize - 1].num = id;
            cache[cacheSize - 1].nextPos = nextPos;
        }
    }

    return db_cnt;
}

int main()
{
    int cacheSize;
    if (scanf_s("%d", &cacheSize) != 1)
    {
        return -1;
    }
    int num;
    if (scanf_s("%d", &num) != 1)
    {
        return -1;
    }

    int ids[MAX_ID_CNT]; // 数组名就是一个指针
    for (int i = 0; i < num; i++)
    {
        if (scanf_s("%d", &ids[i]) != 1)
        {
            return -1;
        }
    }

    int ret = QueryDb(cacheSize, num, ids);
    printf("%d\n", ret);
    return 0;
}
