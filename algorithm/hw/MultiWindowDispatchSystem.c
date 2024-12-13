#include <stdbool.h>

typedef struct {

} MultiWindowSys;

// 注意：该函数为类构造函数，返回的对象指针将作为其他待实现函数的入参；框架代码在调用该函数后，会输出 null（而非指针）
static MultiWindowSys *MultiWindowSysCreate(void)
{
    return NULL;
}

static bool MultiWindowSysCreateWindow(MultiWindowSys *sys, int id, int row, int col, int width, int height)
{
    return false;
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
