#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/* 浏览历史 */

#define URL_LEN 32
#define PAGE_COUNT 20

typedef struct
{
    char homepage[URL_LEN];
    int maxCount;
    char pages[PAGE_COUNT][URL_LEN];
    int ptr;
    int count;
} BrowserHistorySys;

static BrowserHistorySys *BrowserHistorySysCreate(const char *homepage, int maxCount)
{
    BrowserHistorySys *sys = (BrowserHistorySys *)malloc(sizeof(BrowserHistorySys));
    sys->maxCount = maxCount;
    memset(sys->homepage, 0, URL_LEN);
    strcpy(sys->homepage, homepage);
    memset(sys->pages, 0, sizeof(sys->pages));
    strcpy(sys->pages[0], homepage);
    sys->ptr = 1;
    sys->count = 1;
    return sys;
}

static int BrowserHistorySysVisit(BrowserHistorySys *sys, const char *url)
{
    // 当前页
    if (strcmp(sys->homepage, url) == 0)
    {
        return sys->count;
    }

    for (int i = sys->ptr; i < sys->count; i++)
    {
        memset(sys->pages[i], 0, sizeof(URL_LEN));
    }

    strcpy(sys->homepage, url);

    if (sys->ptr == sys->maxCount)
    {
        // 满了，整体左移一位，url放最后一位
        for (int i = 0; i < sys->ptr - 1; i++)
        {
            strcpy(sys->pages[i], sys->pages[i + 1]);
        }
        strcpy(sys->pages[sys->ptr - 1], url);
    }
    else
    {
        strcpy(sys->pages[sys->ptr++], url);
    }

    sys->count = sys->ptr;
    return sys->count;
}

static char *BrowserHistorySysBack(BrowserHistorySys *sys)
{
    char *res = (char *)malloc(URL_LEN);
    if (sys->ptr == 1)
    {
        strcpy(res, sys->homepage);
    }
    else
    {
        sys->ptr--;
        strcpy(res, sys->pages[sys->ptr - 1]);
        strcpy(sys->homepage, sys->pages[sys->ptr - 1]);
    }
    return res;
}

static char *BrowserHistorySysForward(BrowserHistorySys *sys)
{
    char *res = (char *)malloc(URL_LEN);
    if (sys->ptr == sys->count)
    {
        strcpy(res, sys->homepage);
    }
    else
    {
        sys->ptr++;
        strcpy(res, sys->pages[sys->ptr - 1]);
        strcpy(sys->homepage, sys->pages[sys->ptr - 1]);
    }
    return res;
}

static void BrowserHistorySysFree(BrowserHistorySys *sys)
{
    free(sys);
}

int main()
{
    // BrowserHistorySys *sys = (BrowserHistorySys *)BrowserHistorySysCreate("w3.huawei.com", 10);
    // printf("%s\n", "null");
    // int cnt = BrowserHistorySysVisit(sys, "google.com");
    // printf("%d\n", cnt);

    // char *url = (char *)BrowserHistorySysBack(sys);
    // printf("%s\n", url);

    // url = (char *)BrowserHistorySysForward(sys);
    // printf("%s\n", url);

    // url = (char *)BrowserHistorySysForward(sys);
    // printf("%s\n", url);

    // cnt = BrowserHistorySysVisit(sys, "baidu.com");
    // printf("%d\n", cnt);

    // cnt = BrowserHistorySysVisit(sys, "youtube.com");
    // printf("%d\n", cnt);

    // url = (char *)BrowserHistorySysBack(sys);
    // printf("%s\n", url);

    // cnt = BrowserHistorySysVisit(sys, "baidu.com");
    // printf("%d\n", cnt);

    // url = (char *)BrowserHistorySysBack(sys);
    // printf("%s\n", url);

    // cnt = BrowserHistorySysVisit(sys, "mails.huawei.com");
    // printf("%d\n", cnt);

    BrowserHistorySys *sys = (BrowserHistorySys *)BrowserHistorySysCreate("www.huawei.com", 3);
    printf("%s\n", "null");
    int cnt = BrowserHistorySysVisit(sys, "w3.huawei.com");
    printf("%d\n", cnt);
    cnt = BrowserHistorySysVisit(sys, "w4.huawei.com");
    printf("%d\n", cnt);

    char *url = (char *)BrowserHistorySysBack(sys);
    printf("%s\n", url);

    cnt = BrowserHistorySysVisit(sys, "www.huawei.com");
    printf("%d\n", cnt);

    cnt = BrowserHistorySysVisit(sys, "w5.huawei.com");
    printf("%d\n", cnt);

    cnt = BrowserHistorySysVisit(sys, "w6.huawei.com");
    printf("%d\n", cnt);
}