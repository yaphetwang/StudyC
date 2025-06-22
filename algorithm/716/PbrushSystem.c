#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/*
简易画图程序
这个题要求重叠， 两条边重合 是没问题的
*/

#define RECTANGLE_NUM 100

typedef struct
{
    int row;
    int col;
    int width;
    int height;
} PbrushSystem;

static PbrushSystem *PbrushSystemCreate(void)
{
    PbrushSystem *sys = (PbrushSystem *)malloc(sizeof(PbrushSystem) * RECTANGLE_NUM);
    for (int i = 0; i < RECTANGLE_NUM; i++)
    {
        sys[i].row = -1;
        sys[i].col = -1;
        sys[i].width = -1;
        sys[i].height = -1;
    }
    return sys;
}

static bool PbrushSystemDrawRectangle(PbrushSystem *sys, int row, int col, int width, int height)
{
    if (row + height > 100 || col + width > 100)
    {
        return false;
    }

    for (int i = 0; i < RECTANGLE_NUM; i++)
    {
        if (sys[i].row == -1)
        {
            continue;
        }

        // 四个顶点有一个 落到 区域内 都算重叠
        // printf("(%d,%d)", sys[i].row, sys[i].col);
        // printf("(%d,%d)", sys[i].row, sys[i].col + sys[i].width);
        // printf("(%d,%d)", sys[i].row + sys[i].height, sys[i].col);
        // printf("(%d,%d)\n", sys[i].row + sys[i].height, sys[i].col + sys[i].width);

        if (sys[i].row > row && sys[i].row < (row + height) && sys[i].col > col && sys[i].col < (col + width) || sys[i].row > row && sys[i].row < (row + height) && (sys[i].col + sys[i].width) > col && (sys[i].col + sys[i].width) < (col + width) || (sys[i].row + sys[i].height) > row && (sys[i].row + sys[i].height) < (row + height) && sys[i].col > col && sys[i].col < (col + width) || (sys[i].row + sys[i].height) > row && (sys[i].row + sys[i].height) < (row + height) && (sys[i].col + sys[i].width) > col && (sys[i].col + sys[i].width) < (col + width))
        {
            return false;
        }
    }

    for (int i = 0; i < RECTANGLE_NUM; i++)
    {
        if (sys[i].row == -1)
        {
            sys[i].row = row;
            sys[i].col = col;
            sys[i].width = width;
            sys[i].height = height;
            break;
        }
    }

    return true;
}

static int PbrushSystemEraseArea(PbrushSystem *sys, int row, int col, int width, int height)
{
    int cnt = 0;
    for (int i = 0; i < RECTANGLE_NUM; i++)
    {
        if (sys[i].row == -1)
        {
            continue;
        }
        if (sys[i].row > row && sys[i].row < (row + height) && sys[i].col > col && sys[i].col < (col + width) || sys[i].row > row && sys[i].row < (row + height) && (sys[i].col + sys[i].width) > col && (sys[i].col + sys[i].width) < (col + width) || (sys[i].row + sys[i].height) > row && (sys[i].row + sys[i].height) < (row + height) && sys[i].col > col && sys[i].col < (col + width) || (sys[i].row + sys[i].height) > row && (sys[i].row + sys[i].height) < (row + height) && (sys[i].col + sys[i].width) > col && (sys[i].col + sys[i].width) < (col + width))
        {
            sys[i].row = -1;
            sys[i].col = -1;
            sys[i].width = -1;
            sys[i].height = -1;
            cnt++;
        }
    }

    return cnt;
}

static int PbrushSystemQueryArea(PbrushSystem *sys)
{
    int height = 0, width = 0;
    int min_row = 100, max_row = 0, min_col = 100, max_col = 0;
    int is_has = 0;
    for (int i = 0; i < RECTANGLE_NUM; i++)
    {
        if (sys[i].row == -1)
        {
            continue;
        }

        is_has = 1;
        min_row = sys[i].row < min_row ? sys[i].row : min_row;
        min_col = sys[i].col < min_col ? sys[i].col : min_col;

        max_row = (sys[i].row + sys[i].height) > max_row ? (sys[i].row + sys[i].height) : max_row;
        max_col = (sys[i].col + sys[i].width) > max_col ? (sys[i].col + sys[i].width) : max_col;
    }

    if (!is_has)
    {
        return 0;
    }

    // printf("max_row:%d", max_row);
    // printf(" min_row:%d", min_row);
    // printf(" max_col:%d", max_col);
    // printf(" min_col:%d\n", min_col);

    height = max_row - min_row;
    width = max_col - min_col;

    return height * width;
}

static void PbrushSystemFree(PbrushSystem *sys)
{
    free(sys);
}

int main()
{
    PbrushSystem *sys = (PbrushSystem *)PbrushSystemCreate();
    printf("%s\n", "NULL");

    int query_r = PbrushSystemQueryArea(sys);
    printf("%d\n", query_r);

    bool d_r = PbrushSystemDrawRectangle(sys, 0, 1, 5, 4);
    printf("%s\n", d_r ? "true" : "false");

    d_r = PbrushSystemDrawRectangle(sys, 0, 7, 1, 1);
    printf("%s\n", d_r ? "true" : "false");

    d_r = PbrushSystemDrawRectangle(sys, 2, 7, 1, 3);
    printf("%s\n", d_r ? "true" : "false");

    d_r = PbrushSystemDrawRectangle(sys, 5, 3, 2, 2);
    printf("%s\n", d_r ? "true" : "false");

    d_r = PbrushSystemDrawRectangle(sys, 4, 1, 3, 2);
    printf("%s\n", d_r ? "true" : "false");

    query_r = PbrushSystemQueryArea(sys);
    printf("%d\n", query_r);

    int cnt = PbrushSystemEraseArea(sys, 1, 3, 4, 6);
    printf("%d\n", cnt);
    cnt = PbrushSystemEraseArea(sys, 1, 3, 4, 6);
    printf("%d\n", cnt);

    query_r = PbrushSystemQueryArea(sys);
    printf("%d\n", query_r);

    d_r = PbrushSystemDrawRectangle(sys, 2, 8, 93, 1);
    printf("%s\n", d_r ? "true" : "false");
    d_r = PbrushSystemDrawRectangle(sys, 2, 8, 92, 1);
    printf("%s\n", d_r ? "true" : "false");

    PbrushSystemFree(sys);

    return 0;
}