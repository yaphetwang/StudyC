#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define L_LEN 7
#define P_LEN 101
#define R_LEN 100

typedef struct
{
    int productId;
    int *repoIds;
    size_t repoIdsSize;
} ProductRepos;

typedef struct
{
    int repoId;
    int languageId;
    int line;
} LanguageLine;

typedef struct
{
    ProductRepos pr;
    LanguageLine ll[R_LEN];
} CodeStatsSystem;

static CodeStatsSystem *CodeStatsSystemCreate(const ProductRepos *products, size_t productsSize)
{
    CodeStatsSystem *sys = (CodeStatsSystem *)malloc(sizeof(CodeStatsSystem) * P_LEN);
    memset(sys, 0, sizeof(CodeStatsSystem) * P_LEN);

    for (int i = 0; i < productsSize; i++)
    {
        sys[i].pr = products[i];
    }

    return sys;
}

static int CodeStatsSystemChangeCodeLine(CodeStatsSystem *sys, int repoId, int languageId, int codeLine)
{
    for (int i = 0; i < P_LEN; i++)
    {
        int repoIdsSize = sys[i].pr.repoIdsSize;
        for (int j = 0; j < repoIdsSize; j++)
        {
            if (sys[i].pr.repoIds[j] != repoId)
            {
                continue;
            }

            for (int k = 0; k < R_LEN; k++)
            {
                if (sys[i].ll[k].repoId == 0)
                {
                    sys[i].ll[k].repoId = repoId;
                    sys[i].ll[k].languageId = languageId;
                    sys[i].ll[k].line = codeLine;
                    return sys[i].ll[k].line;
                }

                if (sys[i].ll[k].repoId == repoId && sys[i].ll[k].languageId == languageId)
                {
                    sys[i].ll[k].line += codeLine;
                    return sys[i].ll[k].line;
                }
            }
        }
    }

    return 0;
}

int cmp(const void *a, const void *b)
{
    LanguageLine *la = (LanguageLine *)a;
    LanguageLine *lb = (LanguageLine *)b;
    if (la->line != lb->line)
    {
        return lb->line - la->line;
    }
    else
    {
        return la->languageId - lb->languageId;
    }
}

static int *CodeStatsSystemStatLanguage(CodeStatsSystem *sys, int productId, size_t *returnSize)
{
    int *result = (int *)malloc(sizeof(int) * L_LEN);
    memset(result, 0, sizeof(int) * L_LEN);

    LanguageLine ll[L_LEN] = {0};

    if (productId > 0)
    {
        for (int i = 0; i < P_LEN; i++)
        {
            if (sys[i].pr.productId != productId)
            {
                continue;
            }

            for (int j = 0; j < R_LEN; j++)
            {
                ll[sys[i].ll[j].languageId].languageId = sys[i].ll[j].languageId;
                ll[sys[i].ll[j].languageId].line += sys[i].ll[j].line;
            }
        }
    }
    else
    {
        for (int i = 0; i < P_LEN; i++)
        {
            for (int j = 0; j < R_LEN; j++)
            {
                ll[sys[i].ll[j].languageId].languageId = sys[i].ll[j].languageId;
                ll[sys[i].ll[j].languageId].line += sys[i].ll[j].line;
            }
        }
    }

    index = 0;
    LanguageLine temp[L_LEN] = {0};
    for (int i = 0; i < L_LEN; i++)
    {
        if (ll[i].line > 0)
        {
            temp[index++] = ll[i];
        }
    }

    qsort(temp, index, sizeof(LanguageLine), cmp);

    int resIndex = 0;
    for (int i = 0; i < index; i++)
    {
        result[resIndex++] = temp[i].languageId;
    }

    *returnSize = index;
    return result;
}

int main()
{
}
