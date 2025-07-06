#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/* SQL解析执行，简易数据库系统 */

#define TABLE_ID_NUM 10001
#define TABLE_DATA_CNT 1000

typedef struct
{
    int tableId;
    int colNum;
    char *keys;
    int *values[TABLE_DATA_CNT]; // 指针数组，数组里面每个指针指向对应行
    int valuesId;                // values 下标
} Table;

typedef struct
{
    Table tables[TABLE_ID_NUM];
} MiniDb;

typedef struct
{
    int *values;
    int valuesSize;
} IntArray;

static MiniDb *MiniDbInit()
{
    MiniDb *sys = (MiniDb *)malloc(sizeof(MiniDb));
    if (sys != NULL)
    {
        memset(sys, 0, sizeof(MiniDb));
        memset(sys->tables, 0, sizeof(Table) * TABLE_DATA_CNT);
    }
    return sys;
}

static void MiniDbCreate(MiniDb *sys, int tableId, int colNum, const char *keys)
{
    if (sys->tables[tableId].tableId != 0)
    {
        return;
    }

    sys->tables[tableId].tableId = tableId;
    sys->tables[tableId].colNum = colNum;
    int keysLen = strlen(keys);
    sys->tables[tableId].keys = (char *)malloc(sizeof(char) * keysLen);
    strcpy(sys->tables[tableId].keys, keys);
    printf("keys:%s\n", sys->tables[tableId].keys);
    memset(sys->tables[tableId].values, 0, sizeof(int *) * TABLE_DATA_CNT);
    sys->tables[tableId].valuesId = 0;
}

static void MiniDbInsert(MiniDb *sys, int tableId, const int *values, size_t valuesSize)
{
    Table table = sys->tables[tableId];
    int colNum = table.colNum;
    int keysLen = strlen(table.keys);
    int valuesId = table.valuesId;
    int keyConf = 0;
    for (int i = 0; i < valuesId; i++)
    {
        // 每一行 判断 是否 主键冲突
        int keyCnt = 0;
        for (int k = 0; k < keysLen; k++)
        {
            char key = table.keys[k];
            int keyInt = key - 'a';
            keyCnt += (table.values[i][keyInt] == values[keyInt]);
        }

        if (keyCnt == keysLen)
        {
            keyConf = 1;
            break;
        }
    }

    printf("valuesId:%d\n", valuesId);
    printf("keyConf:%d\n", keyConf);
    if (keyConf == 0)
    {
        table.values[valuesId] = (int *)malloc(sizeof(int) * valuesSize);
        memcpy(table.values[valuesId], values, sizeof(int) * valuesSize);
        table.valuesId++;
        sys->tables[tableId] = table;
    }

    printf("tableId:%d ", table.tableId);
    printf("colNum:%d ", table.colNum);
    printf("keys:%s ", table.keys);
    printf("valuesId:%d\n", table.valuesId);
    for (int i = 0; i < table.valuesId; i++)
    {
        for (int v = 0; v < table.colNum; v++)
        {
            printf("value:%d ", table.values[i][v]);
        }
        printf("\n");
    }
}

typedef struct
{
    int *cols;
    int colsSize;
} CmpCol;

static CmpCol cmpCol = {0};

int Cmp(const void *a, const void *b)
{
    IntArray *intA = (IntArray *)a;
    IntArray *intB = (IntArray *)b;
    for (int i = 0; i < cmpCol.colsSize; i++)
    {
        if (intA->values[cmpCol.cols[i]] != intB->values[cmpCol.cols[i]])
        {
            return intA->values[cmpCol.cols[i]] - intB->values[cmpCol.cols[i]];
        }
    }

    return 0;
}

static IntArray *MiniDbSelect(MiniDb *sys, int tableId, char **conditions, size_t conditionsSize, size_t *returnValSize)
{
    IntArray *res = (IntArray *)malloc(sizeof(IntArray) * 100);
    memset(res, 0, sizeof(IntArray) * 100);
    int count = 0;

    Table table = sys->tables[tableId];
    int colNum = table.colNum;

    int valuesId = table.valuesId;
    for (int i = 0; i < valuesId; i++)
    {
        // 每一行 根据查询条件判断
        int cnt = 0;
        for (int c = 0; c < conditionsSize; c++)
        {
            int idx = conditions[c][0] - 'a';
            char valStr[6] = {0};
            strcpy(valStr, conditions[c] + 2);
            int val = strtol(valStr, NULL, 10);
            cnt += (table.values[i][idx] == val);
        }

        if (cnt == conditionsSize)
        {
            res[count].valuesSize = colNum;
            res[count].values = (int *)malloc(sizeof(int) * colNum);
            memcpy(res[count].values, table.values[i], sizeof(int) * colNum);
            count++;
        }
    }

    // 根据主键排序
    int keysLen = strlen(table.keys);
    cmpCol.colsSize = keysLen;
    cmpCol.cols = (int *)malloc(sizeof(int) * keysLen);
    for (int i = 0; i < keysLen; i++)
    {
        cmpCol.cols[i] = table.keys[i] - 'a';
    }
    qsort(res, count, sizeof(IntArray), Cmp);

    *returnValSize = count;
    return res;
}

static void MiniDbFree(MiniDb *sys)
{
    free(sys);
}

int main()
{
    // MiniDb *sys = (MiniDb *)MiniDbInit();
    // printf("%s\n", "null");
    // MiniDbCreate(sys, 1, 3, "a");
    // printf("%s\n", "null");
    // int value[] = {2, 3, 7};
    // MiniDbInsert(sys, 1, value, 3);
    // printf("%s\n", "null");
    // int value1[] = {4, 5, 6};
    // MiniDbInsert(sys, 1, value1, 3);
    // printf("%s\n", "null");
    // int value2[] = {3, 4, 6};
    // MiniDbInsert(sys, 1, value2, 3);
    // printf("%s\n", "null");

    // char *conditions[] = {"b=5", "c=6"};
    // size_t returnValSize = 0;
    // IntArray *res = (IntArray *)MiniDbSelect(sys, 1, conditions, 2, &returnValSize);
    // for (int i = 0; i < returnValSize; i++)
    // {
    //     for (int j = 0; j < res[i].valuesSize; j++)
    //     {
    //         printf("%d ", res[i].values[j]);
    //     }
    //     printf("\n");
    // }

    MiniDb *sys = (MiniDb *)MiniDbInit();
    printf("%s\n", "null");
    MiniDbCreate(sys, 2, 4, "ba");
    printf("%s\n", "null");

    int value[] = {9, 23, 47, 41};
    MiniDbInsert(sys, 2, value, 4);
    printf("%s\n", "null");

    MiniDbCreate(sys, 3, 3, "ca");
    printf("%s\n", "null");

    int value1[] = {10, 20, 47, 99};
    MiniDbInsert(sys, 2, value1, 4);
    printf("%s\n", "null");
    int value2[] = {10, 23, 47, 58};
    MiniDbInsert(sys, 2, value2, 4);
    printf("%s\n", "null");

    int value3[] = {9, 555, 47};
    MiniDbInsert(sys, 3, value3, 3);
    printf("%s\n", "null");

    int value4[] = {9, 23, 47};
    MiniDbInsert(sys, 3, value4, 3);
    printf("%s\n", "null");

    char *conditions[] = {"c=47"};
    size_t returnValSize = 0;
    IntArray *res = (IntArray *)MiniDbSelect(sys, 2, conditions, 1, &returnValSize);
    if (returnValSize == 0)
    {
        printf("%s\n", "[]");
    }
    for (int i = 0; i < returnValSize; i++)
    {
        for (int j = 0; j < res[i].valuesSize; j++)
        {
            printf("%d ", res[i].values[j]);
        }
        printf("\n");
    }

    char *conditions1[] = {"a=9", "b=555"};
    res = (IntArray *)MiniDbSelect(sys, 2, conditions1, 2, &returnValSize);
    if (returnValSize == 0)
    {
        printf("%s\n", "[]");
    }
    for (int i = 0; i < returnValSize; i++)
    {
        for (int j = 0; j < res[i].valuesSize; j++)
        {
            printf("%d ", res[i].values[j]);
        }
        printf("\n");
    }

    char *conditions2[] = {"a=9", "b=555"};
    res = (IntArray *)MiniDbSelect(sys, 3, conditions2, 1, &returnValSize);
    if (returnValSize == 0)
    {
        printf("%s\n", "[]");
    }
    for (int i = 0; i < returnValSize; i++)
    {
        for (int j = 0; j < res[i].valuesSize; j++)
        {
            printf("%d ", res[i].values[j]);
        }
        printf("\n");
    }
    return 0;
}