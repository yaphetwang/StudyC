#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/*
简易画图程序
图形 使用二维矩阵(二维数组) 来标注 每一个点， 是否重叠利用二维矩阵 来判断
*/

#define RECTANGLE_NUM 100

static int area[RECTANGLE_NUM][RECTANGLE_NUM] = {0};
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
    // row,col 区间是 [0,99]
    if (row >= RECTANGLE_NUM || col >= RECTANGLE_NUM)
    {
        return false;
    }

    int temp[RECTANGLE_NUM][RECTANGLE_NUM] = {0};
    int isAllValid = 1;

    for (int r = row; r < row + height; r++)
    {
        for (int c = col; c < col + width; c++)
        {
            if (r >= RECTANGLE_NUM || c >= RECTANGLE_NUM)
            {
                isAllValid = 0; // 超出边界
                break;
            }
            if (area[r][c] == 1)
            {
                isAllValid = 0; // 有重叠
                break;
            }

            temp[r][c] = 1;
        }
        if (isAllValid == 0)
        {
            break;
        }
    }
    if (isAllValid == 0)
    {
        return false;
    }

    // for (int i = 0; i < RECTANGLE_NUM; i++)
    // {
    //     if (sys[i].row == -1)
    //     {
    //         continue;
    //     }
    //     // 四个顶点有一个 落到 区域内 都算重叠,  这样判断不行
    //     // printf("(%d,%d)", sys[i].row, sys[i].col);
    //     // printf("(%d,%d)", sys[i].row, sys[i].col + sys[i].width);
    //     // printf("(%d,%d)", sys[i].row + sys[i].height, sys[i].col);
    //     // printf("(%d,%d)\n", sys[i].row + sys[i].height, sys[i].col + sys[i].width);
    //     if (sys[i].row > row && sys[i].row < (row + height) && sys[i].col > col && sys[i].col < (col + width) || sys[i].row > row && sys[i].row < (row + height) && (sys[i].col + sys[i].width) > col && (sys[i].col + sys[i].width) < (col + width) || (sys[i].row + sys[i].height) > row && (sys[i].row + sys[i].height) < (row + height) && sys[i].col > col && sys[i].col < (col + width) || (sys[i].row + sys[i].height) > row && (sys[i].row + sys[i].height) < (row + height) && (sys[i].col + sys[i].width) > col && (sys[i].col + sys[i].width) < (col + width))
    //     {
    //         return false;
    //     }
    // }

    for (int r = row; r < row + height; r++)
    {
        for (int c = col; c < col + width; c++)
        {
            if (temp[r][c])
            {
                area[r][c] = 1;
            }
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

static void SearchArea(PbrushSystem *sys, int curRow, int curCol)
{
    for (int i = 0; i < RECTANGLE_NUM; i++)
    {
        if (sys[i].row == -1)
        {
            continue;
        }

        //  范围以 左上角顶点 来判断 左闭右开 [0,1)
        if (curRow < sys[i].row || curRow >= sys[i].row + sys[i].height)
        {
            continue;
        }

        if (curCol < sys[i].col || curCol >= sys[i].col + sys[i].width)
        {
            continue;
        }

        // 找到一个图形区域 即可， 后面还有其他点 来匹配其他图形，直到匹配完所有重叠的
        for (int r = sys[i].row; r < sys[i].row + sys[i].height; r++)
        {
            for (int c = sys[i].col; c < sys[i].col + sys[i].width; c++)
            {
                area[r][c] = 0;
            }
        }

        // 先清理area 再重新初始化
        sys[i].row = -1;
        sys[i].col = -1;
        sys[i].height = -1;
        sys[i].width = -1;
    }
}

static int PbrushSystemEraseArea(PbrushSystem *sys, int row, int col, int width, int height)
{
    int cnt = 0;
    for (int r = row; r < row + height; r++)
    {
        for (int c = col; c < col + width; c++)
        {
            if (r >= RECTANGLE_NUM || c >= RECTANGLE_NUM)
            {
                continue;
            }

            if (area[r][c] == 0)
            {
                continue;
            }

            // 有一个点重叠, 找 这个点 出现在哪个图形 区域里
            SearchArea(sys, r, c);
            cnt++;
        }
    }

    return cnt;
}

static int PbrushSystemQueryArea(PbrushSystem *sys)
{
    int height = 0, width = 0;
    int min_row = RECTANGLE_NUM, max_row = 0, min_col = RECTANGLE_NUM, max_col = 0;
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