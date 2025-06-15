#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define LANGUAGE_NUM 7
#define PRODUCT_NUM 101
#define REPO_NUM 1000

typedef struct
{
    int languageId;
    int lines;
} LanguageLines;

typedef struct
{
    int repoId;
    int productId; // 这两个参数 用不到，可以删除
    LanguageLines languageLines[LANGUAGE_NUM];
} ReposLanguage;

typedef struct
{
    int productId;
    int *repoIds; // 这是个坑，要单独分配内存
    int repoIdsSize;
    ReposLanguage reposLanguage[REPO_NUM];
} ProductRepos;

typedef struct
{
    ProductRepos productRepos[PRODUCT_NUM];
} CodeStatsSystem;

static CodeStatsSystem *CodeStatsSystemCreate(const ProductRepos *products, int productsSize)
{
    CodeStatsSystem *sys = (CodeStatsSystem *)malloc(sizeof(CodeStatsSystem));
    memset(sys, 0, sizeof(CodeStatsSystem));

    for (int i = 0; i < productsSize; i++)
    {
        sys->productRepos[i] = products[i];
        sys->productRepos[i].repoIds = (int *)malloc(sizeof(int) * sys->productRepos[i].repoIdsSize);
        memset(sys->productRepos[i].repoIds, 0, sizeof(int) * sys->productRepos[i].repoIdsSize);
        memcpy(sys->productRepos[i].repoIds, products[i].repoIds, sizeof(int) * products[i].repoIdsSize);
        // for (int j = 0; j < sys->productRepos[i].repoIdsSize; j++)
        // {
        //     // 没有单独取出来元素，而是直接操作
        //     sys->productRepos[i].repoIds[j] = products[i].repoIds[j];
        // }
    }

    return sys;
}

// 这个题 做到 一个元素也不单独取出来
static int CodeStatsSystemChangeCodelines(CodeStatsSystem *sys, int repoId, int languageId, int codeline)
{
    for (int i = 0; i < PRODUCT_NUM; i++)
    {
        int repoIdsSize = sys->productRepos[i].repoIdsSize;
        for (int j = 0; j < repoIdsSize; j++)
        {
            if (sys->productRepos[i].repoIds[j] == repoId)
            {
                sys->productRepos[i].reposLanguage[repoId].repoId = repoId;
                sys->productRepos[i].reposLanguage[repoId].productId = sys->productRepos[i].productId;
                sys->productRepos[i].reposLanguage[repoId].languageLines[languageId].languageId = languageId;
                sys->productRepos[i].reposLanguage[repoId].languageLines[languageId].lines += codeline;
                return sys->productRepos[i].reposLanguage[repoId].languageLines[languageId].lines;
            }
        }
    }

    return 0;
}

int LanguageLinesCmp(const void *a, const void *b)
{
    LanguageLines *l_a = (LanguageLines *)a;
    LanguageLines *l_b = (LanguageLines *)b;
    if (l_a->lines != l_b->lines)
    {
        return l_b->lines - l_a->lines;
    }
    else
    {
        return l_a->languageId - l_b->languageId;
    }
}

static int *CodeStatsSystemStatLanguage(CodeStatsSystem *sys, int productId, int *returnSize)
{
    int *result = (int *)malloc(sizeof(int) * LANGUAGE_NUM);
    memset(result, 0, sizeof(int) * LANGUAGE_NUM);

    LanguageLines lines[LANGUAGE_NUM] = {0};

    if (productId != 0)
    {
        for (int i = 0; i < PRODUCT_NUM; i++)
        {
            if (sys->productRepos[i].productId != productId)
            {
                continue;
            }
            int repoIdsSize = sys->productRepos[i].repoIdsSize;
            for (int j = 0; j < repoIdsSize; j++)
            {
                int repoId = sys->productRepos[i].repoIds[j];
                for (int lidx = 0; lidx < LANGUAGE_NUM; lidx++)
                {
                    LanguageLines ll = sys->productRepos[i].reposLanguage[repoId].languageLines[lidx];
                    lines[ll.languageId].languageId = ll.languageId;
                    lines[ll.languageId].lines += ll.lines;
                }
            }
        }
    }
    else
    {
        for (int i = 0; i < PRODUCT_NUM; i++)
        {
            int repoIdsSize = sys->productRepos[i].repoIdsSize;
            for (int j = 0; j < repoIdsSize; j++)
            {
                int repoId = sys->productRepos[i].repoIds[j];
                for (int lidx = 0; lidx < LANGUAGE_NUM; lidx++)
                {
                    LanguageLines ll = sys->productRepos[i].reposLanguage[repoId].languageLines[lidx];
                    lines[ll.languageId].languageId = ll.languageId;
                    lines[ll.languageId].lines += ll.lines;
                }
            }
        }
    }

    int idx = 0;
    LanguageLines temp[LANGUAGE_NUM] = {0};

    for (int i = 0; i < LANGUAGE_NUM; i++)
    {
        if (lines[i].lines > 0)
        {
            temp[idx++] = lines[i];
        }
    }

    qsort(temp, idx, sizeof(LanguageLines), LanguageLinesCmp);

    int res_idx = 0;
    for (int i = 0; i < idx; i++)
    {
        result[res_idx++] = temp[i].languageId;
    }

    *returnSize = idx;
    return result;
}

static void CodeStatsSystemFree(CodeStatsSystem *sys)
{
    free(sys);
}

int main()
{

    ProductRepos ProductRepos[3] = {0};
    ProductRepos[0].productId = 10;
    int repoIds0[] = {102, 101};
    ProductRepos[0].repoIds = repoIds0;
    ProductRepos[0].repoIdsSize = 2;

    ProductRepos[1].productId = 12;
    int repoIds1[] = {122};
    ProductRepos[1].repoIds = repoIds1;
    ProductRepos[1].repoIdsSize = 1;

    ProductRepos[2].productId = 22;
    int repoIds2[] = {221};
    ProductRepos[2].repoIds = repoIds2;
    ProductRepos[2].repoIdsSize = 1;

    CodeStatsSystem *sys = (CodeStatsSystem *)CodeStatsSystemCreate(ProductRepos, 3);
    printf("%s\n", "NULL");
    int result1 = CodeStatsSystemChangeCodelines(sys, 221, 3, 500);
    printf("%d\n", result1);

    int result2 = CodeStatsSystemChangeCodelines(sys, 102, 2, 1900);
    printf("%d\n", result2);

    int result3 = CodeStatsSystemChangeCodelines(sys, 101, 1, 2000);
    printf("%d\n", result3);

    int result4 = CodeStatsSystemChangeCodelines(sys, 101, 2, 200);
    printf("%d\n", result4);

    int returnSize = 0;
    int *result = (int *)CodeStatsSystemStatLanguage(sys, 10, &returnSize);
    for (int i = 0; i < returnSize; i++)
    {
        printf("%d ", result[i]);
        if (i == returnSize - 1)
        {
            printf("\n");
        }
    }

    result = (int *)CodeStatsSystemStatLanguage(sys, 22, &returnSize);
    for (int i = 0; i < returnSize; i++)
    {
        printf("%d ", result[i]);
        if (i == returnSize - 1)
        {
            printf("\n");
        }
    }

    int result5 = CodeStatsSystemChangeCodelines(sys, 102, 3, 2000);
    printf("%d\n", result5);

    int result6 = CodeStatsSystemChangeCodelines(sys, 102, 2, -100);
    printf("%d\n", result6);

    result = (int *)CodeStatsSystemStatLanguage(sys, 0, &returnSize);
    for (int i = 0; i < returnSize; i++)
    {
        printf("%d ", result[i]);
        if (i == returnSize - 1)
        {
            printf("\n");
        }
    }
}