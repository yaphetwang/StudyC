#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>

/* 专线配置，这种 标识 一个点 的类型题， 特别适合 二维矩阵（二维数组来做） */

typedef struct
{
    int id1;
    int id2;
} Config;

typedef struct
{
    char opType;
    int id1;
    int id2;
} Cmd;

int cmp(const void *a, const void *b)
{
    Cmd *cmdA = (Cmd *)a;
    Cmd *cmdB = (Cmd *)b;
    if (cmdA->opType != cmdB->opType)
    {
        return cmdB->opType - cmdA->opType;
    }
    else
    {
        return cmdA->id1 - cmdB->id1;
    }
}
/* 方法不行，有些用例过不去 */
static Cmd *GetBatchCmds(const Config *configs, size_t configsSize, const Cmd *batchReqs, size_t batchReqsSize, size_t *returnSize)
{
    Cmd *temp = (Cmd *)malloc(sizeof(Cmd) * batchReqsSize);
    memset(temp, 0, sizeof(Cmd) * batchReqsSize);
    int cnt = 0;
    for (int i = 0; i < configsSize; i++)
    {
        temp[cnt].opType = 'o';
        temp[cnt].id1 = configs[i].id1;
        temp[cnt].id2 = configs[i].id2;
        cnt++;
    }

    Cmd *temp_delete = (Cmd *)malloc(sizeof(Cmd) * batchReqsSize);
    memset(temp_delete, 0, sizeof(Cmd) * batchReqsSize);
    int delete_cnt = 0;

    for (int i = 0; i < batchReqsSize; i++)
    {
        Cmd cmd = batchReqs[i];
        printf("cmd:%c %d %d \n", cmd.opType, cmd.id1, cmd.id2);

        if (cmd.opType == 'a')
        {
            int isExist = 0;
            for (int c = 0; c < cnt; c++)
            {
                if (temp[c].opType == 'i')
                {
                    continue;
                }
                if (temp[c].id1 == cmd.id1 || temp[c].id1 == cmd.id2 || temp[c].id2 == cmd.id1 || temp[c].id2 == cmd.id2)
                {
                    isExist = 1;
                    break;
                }
            }

            if (!isExist)
            {
                temp[cnt++] = cmd;
                printf("add cmd:%c %d %d \n", temp[cnt - 1].opType, temp[cnt - 1].id1, temp[cnt - 1].id2);
            }
        }

        if (cmd.opType == 'd')
        {
            for (int c = 0; c < cnt; c++)
            {
                if (temp[c].id1 == cmd.id1 && temp[c].id2 == cmd.id2)
                {
                    if (temp[c].opType == 'o')
                    {
                        temp_delete[delete_cnt++] = cmd;
                    }
                    temp[c].opType = 'i';
                    printf("delete cmd:%c %d %d \n", temp[c].opType, temp[c].id1, temp[c].id2);
                    break;
                }
            }
        }
    }

    printf("========\n");
    for (int i = 0; i < cnt; i++)
    {
        printf("temp:%c %d %d \n", temp[i].opType, temp[i].id1, temp[i].id2);
    }

    int res_cnt = 0;
    Cmd *res = (Cmd *)malloc(sizeof(Cmd) * batchReqsSize);
    memset(res, 0, sizeof(Cmd) * batchReqsSize);
    for (int i = 0; i < cnt; i++)
    {
        if (temp[i].opType != 'i' && temp[i].opType != 'o')
        {
            res[res_cnt++] = temp[i];
        }
    }

    for (int i = 0; i < delete_cnt; i++)
    {
        res[res_cnt++] = temp_delete[i];
    }

    *returnSize = res_cnt;

    if (res_cnt == 0)
    {
        return res;
    }

    qsort(res, res_cnt, sizeof(Cmd), cmp);
    return res;
}

/* 还是用 二维矩阵 是正解*/
#define ID_LEN 101
static int g_initMap[ID_LEN][ID_LEN] = {0};
static int g_cmdMap[ID_LEN][ID_LEN] = {0};

static void init(const Config *configs, size_t configsSize)
{
    for (int i = 0; i < configsSize; i++)
    {
        g_initMap[configs[i].id1][configs[i].id2] = 1;
        g_initMap[configs[i].id2][configs[i].id1] = 1;
        g_cmdMap[configs[i].id1][configs[i].id2] = 1;
        g_cmdMap[configs[i].id2][configs[i].id1] = 1;
    }
}

static int IsIdFree(int id)
{
    for (int i = 0; i < ID_LEN; i++)
    {
        if (g_cmdMap[id][i] == 1)
        {
            return 0;
        }
    }
    return 1;
}

static Cmd *GetBatchCmds2(const Config *configs, size_t configsSize, const Cmd *batchReqs, size_t batchReqsSize, size_t *returnSize)
{
    init(configs, configsSize);
    for (int i = 0; i < batchReqsSize; i++)
    {
        if (batchReqs[i].opType == 'a')
        {
            if (IsIdFree(batchReqs[i].id1) && IsIdFree(batchReqs[i].id2))
            {
                g_cmdMap[batchReqs[i].id1][batchReqs[i].id2] = 1;
                g_cmdMap[batchReqs[i].id2][batchReqs[i].id1] = 1;
            }
        }

        if (batchReqs[i].opType == 'd')
        {
            if (g_cmdMap[batchReqs[i].id1][batchReqs[i].id2] == 1 &&
                g_cmdMap[batchReqs[i].id2][batchReqs[i].id1] == 1)
            {
                g_cmdMap[batchReqs[i].id1][batchReqs[i].id2] = 0;
                g_cmdMap[batchReqs[i].id2][batchReqs[i].id1] = 0;
            }
        }
    }

    int resCnt = 0;
    Cmd *res = (Cmd *)calloc(ID_LEN, sizeof(Cmd));
    // 先统计删除的
    for (int i = 0; i < ID_LEN; i++)
    {
        for (int j = 0; j < ID_LEN; j++)
        {
            if (g_initMap[i][j] == 1 && g_cmdMap[i][j] == 0)
            {
                res[resCnt].opType = 'd';
                res[resCnt].id1 = i < j ? i : j;
                res[resCnt].id2 = i < j ? j : i;
                resCnt++;
                g_initMap[i][j] = 0;
                g_initMap[j][i] = 0;
            }
        }
    }

    // 后统计新增的
    for (int i = 0; i < ID_LEN; i++)
    {
        for (int j = 0; j < ID_LEN; j++)
        {
            if (g_initMap[i][j] == 0 && g_cmdMap[i][j] == 1)
            {
                res[resCnt].opType = 'a';
                res[resCnt].id1 = i < j ? i : j;
                res[resCnt].id2 = i < j ? j : i;
                resCnt++;
                g_initMap[i][j] = 1;
                g_initMap[j][i] = 1;
            }
        }
    }

    *returnSize = resCnt;
    return res;
}

int main()
{
    Config configs[2] = {{2, 3}, {4, 5}};
    Cmd cmds[7] = {{'a', 0, 1}, {'a', 5, 6}, {'d', 0, 1}, {'d', 1, 2}, {'a', 0, 6}, {'d', 4, 5}, {'a', 1, 4}};
    size_t returnSize = 0;
    Cmd *res = (Cmd *)GetBatchCmds2(configs, 2, cmds, 7, &returnSize);
    for (int i = 0; i < returnSize; i++)
    {
        printf("[%c %d %d] \n", res[i].opType, res[i].id1, res[i].id2);
    }

    Config configs1[2] = {{2, 3}, {4, 5}};
    Cmd cmds1[7] = {{'a', 10, 20}, {'a', 50, 60}, {'d', 50, 60}, {'d', 10, 20}};
    Cmd *res1 = (Cmd *)GetBatchCmds2(configs1, 0, cmds1, 4, &returnSize);
    if (returnSize == 0)
    {
        printf("%s", "[]");
    }
    for (int i = 0; i < returnSize; i++)
    {
        printf("%c %d %d \n", res1[i].opType, res1[i].id1, res1[i].id2);
    }
}