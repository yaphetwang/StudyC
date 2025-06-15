#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define NUM_STR_LEN 20
#define MAX_LEN 100

int cmp(const void *a, const void *b)
{
    int *sa = (int *)a;
    int *sb = (int *)b;
    char ta[NUM_STR_LEN];
    char tb[NUM_STR_LEN];
    /* 第一个参数为指针，第二个参数为后续待转化参数格式，后续参数可以是一个或多个（实际值） */
    sprintf(ta, "%d%d", *sa, *sb);
    sprintf(tb, "%d%d", *sb, *sa);
    return strcmp(tb, ta);
}

static void GetResult(int *nums, int cnt, char *output)
{
    qsort(nums, cnt, sizeof(int), cmp);
    int idx = 0;
    for (int i = 0; i < cnt; i++)
    {
        sprintf(output + idx, "%d", nums[i]);
        idx = strlen(output);
    }
}

int main()
{
    int arr[] = {8308, 8308, 830};
    int cnt = sizeof(arr) / sizeof(int);
    char result[MAX_LEN];
    GetResult(arr, cnt, result);
    printf("rlt:%s\n", result);

    int arr1[] = {3, 30, 34, 5, 9};
    int cnt1 = sizeof(arr1) / sizeof(int);
    GetResult(arr1, cnt1, result);
    printf("rlt:%s\n", result);

    int arr2[] = {1};
    int cnt2 = sizeof(arr2) / sizeof(int);
    GetResult(arr2, cnt2, result);
    printf("rlt:%s\n", result);
}