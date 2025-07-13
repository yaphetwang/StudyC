#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_ID_CNT 1001

#define INIT_VAL \
    {            \
        -1, 0}

typedef struct
{
    int num;
    int nextPos;
} NextPosStru;

static int QueryDb(int cacheSize, int *ids, int num)
{
    int db_cnt = 0;

    // 缓存数组初始化
    NextPosStru cache[cacheSize];
    for (int i = 0; i < cacheSize; i++)
    {
        // cache[i].num = -1;
        // cache[i].nextPos = 0;
        // cache[i] = {-1, 0};
        cache[i] = (NextPosStru)INIT_VAL;
    }

    for (int i = 0; i < num; i++)
    {
        int id = ids[i];
        int nextPos = num; // 初始化为num，这里的nextPos是下一个出现的位置
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
                // 命中缓存，更新下一个位置
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
            db_cnt += 1;
            // 放入缓存中
            int index = 0, maxPos = 0;
            bool setRet = false;
            for (int l = 0; l < cacheSize; l++)
            {
                if (cache[l].num == -1)
                {
                    // 找到空位置
                    cache[l].num = id;
                    cache[l].nextPos = nextPos;
                    setRet = true;
                    break;
                }

                if (cache[l].nextPos > maxPos)
                {
                    index = l;
                    maxPos = cache[l].nextPos;
                }
            }
            // 更新缓存,替换缓存数据,下一次出现位置最大的替换掉
            if (!setRet)
            {
                cache[index].num = id;
                cache[index].nextPos = nextPos;
            }
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

    int ret = QueryDb(cacheSize, ids, num);
    printf("%d\n", ret);
    return 0;
}
