#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_WINDOW_NUM 100

typedef struct
{
    int row;
    int col;
    int width;
    int height;
} Window;

typedef struct
{
    int numWindows;
    Window *windows;
    int windowIds[MAX_WINDOW_NUM];
    int topIndex;
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
    memset(sys->windows, 0, MAX_WINDOW_NUM * sizeof(Window);

    return sys;
}

static bool MultiWindowSysCreateWindow(MultiWindowSys *sys, int id, int row, int col, int width, int height)
{
    int topIndex = sys->topIndex;
    for (int i = 0; i < topIndex; i++)
    {
        if (sys->windowIds[i] == id)
        {
            return false;
        }
    }

    if (row < 0 || col < 0 || row >= 1000 || col >= 1000)
    {
        return false;
    }

    sys->windows[sys->numWindows] row = row;
    sys->windows[sys->numWindows] col = col;
    sys->windows[sys->numWindows] width = width;
    sys->windows[sys->numWindows] height = height;
    sys->windowIds[sys->topIndex] = id;
    sys->topIndex++;
    sys->numWindows++;
    return true;
}

static bool MultiWindowSysDestroyWindow(MultiWindowSys *sys, int id)
{
    return false;
}

static bool MultiWindowSysMoveWindow(MultiWindowSys *sys, int id, int dstRow, int dstCol)
{
    return false;
}

static int MultiWindowSysDispatchClickEvent(MultiWindowSys *sys, int row, int col)
{
    return 0;
}

static void MultiWindowSysFree(MultiWindowSys *sys)
{
}
