#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_WINDOW_NUM 100
#define MAX_DISTANCE 1000

typedef struct
{
    int id;
    int row;
    int col;
    int width;
    int height;
    int levelId;
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
        if (sys->windows[i].id != 0 && sys->windows[i].id == id)
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
    sys->windows[topLevelId].levelId = topLevelId;
    sys->topLevelId++;
    return true;
}

static bool MultiWindowSysDestroyWindow(MultiWindowSys *sys, int id)
{
    for (int i = 0; i < sys->topLevelId; i++)
    {
        if (sys->windows[i].id != 0 && sys->windows[i].id == id)
        {
            memset(&sys->windows[i], 0, sizeof(Window));
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
        if (sys->windows[i].id != 0 && sys->windows[i].id == id)
        {
            sys->windows[topLevelId].id = id;
            sys->windows[topLevelId].row = dstRow;
            sys->windows[topLevelId].col = dstCol;
            sys->windows[topLevelId].width = sys->windows[i].width;
            sys->windows[topLevelId].height = sys->windows[i].height;
            sys->windows[topLevelId].levelId = topLevelId;
            sys->topLevelId++;

            memset(&sys->windows[i], 0, sizeof(Window));
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
        if (sys->windows[i].id != 0 && sys->windows[i].row <= row && (sys->windows[i].row + sys->windows[i].height) > row 
            && sys->windows[i].col <= col && (sys->windows[i].col + sys->windows[i].width) > col)
        {
            sys->windows[topLevelId].id = sys->windows[i].id;
            sys->windows[topLevelId].row = sys->windows[i].row;
            sys->windows[topLevelId].col = sys->windows[i].col;
            sys->windows[topLevelId].width = sys->windows[i].width;
            sys->windows[topLevelId].height = sys->windows[i].height;
            sys->windows[topLevelId].levelId = topLevelId;
            sys->topLevelId++;

            int id = sys->windows[i].id;
            memset(&sys->windows[i], 0, sizeof(Window));

            return id;
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
    ret2 = MultiWindowSysDispatchClickEvent(sys, 10, 7);//边界值
    printf("Dispatch click event at (10, 7): %d\n", ret2);

    return 0;
}
