#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_WINDOW_NUM 1000
#define MAX_DISTANCE 1000

typedef struct
{
    int id;
    int row;
    int col;
    int width;
    int height;
} Window;

typedef struct
{
    int topLevelId;
    Window *windows;
} MultiWindowSys;

// 注意：该函数为类构造函数，返回的对象指针将作为其他待实现函数的入参；框架代码在调用该函数后，会输出 null（而非指针）
static MultiWindowSys *MultiWindowSysCreate(void)
{
    MultiWindowSys *sys = (MultiWindowSys *)malloc(sizeof(MultiWindowSys));
    if (sys == NULL)
    {
        return NULL;
    }

    memset(sys, 0, sizeof(MultiWindowSys));
    // 指针变量需要单独分配内存初始化
    sys->windows = (Window *)malloc(MAX_WINDOW_NUM * sizeof(Window));
    memset(sys->windows, 0, MAX_WINDOW_NUM * sizeof(Window));
    sys->topLevelId = 0;

    return sys;
}

static bool MultiWindowSysCreateWindow(MultiWindowSys *sys, int id, int row, int col, int width, int height)
{
    int topLevelId = sys->topLevelId;
    for (int i = 0; i < topLevelId; i++)
    {
        if (sys->windows[i].id == id)
        {
            return false;
        }
    }

    if (row < 0 || col < 0 || row >= MAX_DISTANCE || col >= MAX_DISTANCE)
    {
        return false;
    }

    sys->windows[topLevelId].id = id;
    sys->windows[topLevelId].row = row;
    sys->windows[topLevelId].col = col;
    sys->windows[topLevelId].width = width;
    sys->windows[topLevelId].height = height;
    sys->topLevelId++;
    return true;
}

static bool MultiWindowSysDestroyWindow(MultiWindowSys *sys, int id)
{
    for (int i = 0; i < sys->topLevelId; i++)
    {
        if (sys->windows[i].id == id)
        {
            for (int j = i; j < sys->topLevelId - 1; j++)
            {
                sys->windows[j] = sys->windows[j + 1];
            }
            sys->topLevelId--;

            return true;
        }
    }

    return false;
}

static bool MultiWindowSysMoveWindow(MultiWindowSys *sys, int id, int dstRow, int dstCol)
{
    if (dstRow < 0 || dstCol < 0 || dstRow >= MAX_DISTANCE || dstCol >= MAX_DISTANCE)
    {
        return false;
    }

    int topLevelId = sys->topLevelId;
    for (int i = 0; i < topLevelId; i++)
    {
        if (sys->windows[i].id == id)
        {
            // Window temp = {id, dstRow, dstCol, sys->windows[i].width, sys->windows[i].height};
            Window temp = sys->windows[i];
            temp.row = dstRow;
            temp.col = dstCol;

            for (int j = i; j < sys->topLevelId - 1; j++)
            {
                sys->windows[j] = sys->windows[j + 1];
            }

            sys->windows[topLevelId - 1] = temp;
            return true;
        }
    }

    return false;
}

static int MultiWindowSysDispatchClickEvent(MultiWindowSys *sys, int row, int col)
{
    int topLevelId = sys->topLevelId;
    for (int i = topLevelId - 1; i >= 0; i--)
    {
        if (sys->windows[i].row <= row && (sys->windows[i].row + sys->windows[i].height) > row && sys->windows[i].col <= col && (sys->windows[i].col + sys->windows[i].width) > col)
        {
            Window temp = sys->windows[i];

            for (int j = i; j < sys->topLevelId - 1; j++)
            {
                sys->windows[j] = sys->windows[j + 1];
            }

            sys->windows[topLevelId - 1] = temp;
            return sys->windows[topLevelId - 1].id;
        }
    }
    return -1;
}

static void MultiWindowSysFree(MultiWindowSys *sys)
{
    free(sys);
}

int main()
{
    MultiWindowSys *sys = MultiWindowSysCreate();
    // bool ret = MultiWindowSysCreateWindow(sys, 2, 70, 80, 15, 17);
    // printf("Create window %d: %d\n", 2, ret);
    // ret = MultiWindowSysCreateWindow(sys, 1, 0, 10, 999, 100);
    // printf("Create window %d: %d\n", 1, ret);
    // ret = MultiWindowSysMoveWindow(sys, 2, 5, 6);
    // printf("Move window %d: %d\n", 2, ret);
    // int ret2 = MultiWindowSysDispatchClickEvent(sys, 20, 20);
    // printf("Dispatch click event at (20, 20): %d\n", ret2);
    // ret = MultiWindowSysDestroyWindow(sys, 2);
    // printf("Destroy window %d: %d\n", 2, ret);

    bool ret = MultiWindowSysCreateWindow(sys, 1, 3, 4, 9, 7);
    printf("Create window %d: %d\n", 2, ret);
    ret = MultiWindowSysCreateWindow(sys, 2, 7, 8, 11, 7);
    printf("Create window %d: %d\n", 1, ret);
    ret = MultiWindowSysCreateWindow(sys, 3, 12, 6, 6, 5);
    printf("Create window %d: %d\n", 1, ret);
    ret = MultiWindowSysMoveWindow(sys, 2, 950, 1000);
    printf("Move window %d: %d\n", 2, ret);
    int ret2 = MultiWindowSysDispatchClickEvent(sys, 7, 8);
    printf("Dispatch click event at (7, 8): %d\n", ret2);
    ret2 = MultiWindowSysDispatchClickEvent(sys, 7, 7);
    printf("Dispatch click event at (7, 7): %d\n", ret2);
    ret2 = MultiWindowSysDispatchClickEvent(sys, 7, 8);
    printf("Dispatch click event at (7, 8): %d\n", ret2);
    ret2 = MultiWindowSysDispatchClickEvent(sys, 10, 7); // 边界值
    printf("Dispatch click event at (10, 7): %d\n", ret2);

    char ch = 'a';
    int int_a = *(int *)&ch;
    printf("%d\n", int_a);

    return 0;
}
