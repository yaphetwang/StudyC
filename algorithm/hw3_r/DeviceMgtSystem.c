#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/*
问题：
C语言 数组中的元素取出来 赋值给结构体，结构体操作完，需要将 该结构体重新 赋值给 数组吗？？？

在 C 语言中，结构体变量赋值是值拷贝（深拷贝），因此是否需要重新赋值回数组取决于你的需求
Point arr[3] = {{1, 2}, {3, 4}, {5, 6}};

情况 1：直接修改结构体（不需要重新赋值）
如果你直接操作的是 数组元素本身（即通过指针或数组下标访问），修改会直接影响原数组，无需重新赋值。
    // 直接修改数组中的结构体
    arr[0].x = 100;   // 修改原数组
    arr[0].y = 200;

情况 2：先取出结构体，修改后再赋值回数组
如果你 先取出结构体赋值给另一个变量，修改后 必须重新赋值回数组，否则原数组不会改变。
    // 1. 取出结构体（值拷贝）
    Point p = arr[0];  // p 是 arr[0] 的副本
    p.x = 100;         // 修改副本，不影响原数组
    p.y = 200;

    // 2. 必须重新赋值回数组
    arr[0] = p;

情况 3：使用指针直接修改（推荐高效方式）
如果不想拷贝整个结构体，可以使用 指针 直接操作数组元素，避免额外赋值。
    Point *p = &arr[0];  // p 指向 arr[0]， 即 获取到该元素的指针 进行操作元素 
    p->x = 100;          // 直接修改原数组
    p->y = 200;

*/

#define PROC_UNIT_NUM 3
#define DEVICE_NUM 1001

typedef struct
{
    int deviceId;
    int memSize;
    int procId;
} DeviceInfo;

typedef struct
{
    int procId;
    int procMemSize;
    DeviceInfo *deviceInfo;
} ProcInfo;

typedef struct
{
    int procNum;
    ProcInfo *procInfo;
} ProcUnit;

typedef struct
{
    ProcUnit procUnit[PROC_UNIT_NUM];
} DeviceMgtSystem;

static DeviceMgtSystem *DeviceMgtSystemCreate(int procNum, int maxMemSize)
{
    DeviceMgtSystem *sys = (DeviceMgtSystem *)malloc(sizeof(DeviceMgtSystem));
    memset(sys, 0, sizeof(DeviceMgtSystem));

    for (int i = 0; i < PROC_UNIT_NUM; i++)
    {
        ProcUnit procUnit = sys->procUnit[i];
        procUnit.procNum = procNum;
        // 需要单独分配内存
        procUnit.procInfo = (ProcInfo *)malloc(sizeof(ProcInfo) * procNum);
        memset(procUnit.procInfo, 0, sizeof(ProcInfo) * procNum);

        for (int i = 0; i < procNum; i++)
        {
            procUnit.procInfo[i].procId = i;
            procUnit.procInfo[i].procMemSize = maxMemSize;
            // 需要单独分配内存
            procUnit.procInfo[i].deviceInfo = (DeviceInfo *)malloc(sizeof(DeviceInfo) * DEVICE_NUM);
            memset(procUnit.procInfo[i].deviceInfo, 0, sizeof(DeviceInfo) * DEVICE_NUM);
        }

        // C语言，数组中的元素取出来设置完之后，要让指针重新指向该元素
        sys->procUnit[i] = procUnit;
    }

    return sys;
}

int ProcCmp(const void *a, const void *b)
{
    ProcInfo *proc_a = (ProcInfo *)a;
    ProcInfo *proc_b = (ProcInfo *)b;
    if (proc_a->procMemSize != proc_b->procMemSize)
    {
        return proc_b->procMemSize - proc_a->procMemSize;
    }
    else
    {
        return proc_a->procId - proc_b->procId;
    }
}

static int DeviceMgtSystemCreateDevice(DeviceMgtSystem *sys, int deviceId, int deviceType, int memSize)
{
    ProcUnit procUnit = sys->procUnit[deviceType - 1];
    qsort(procUnit.procInfo, procUnit.procNum, sizeof(ProcInfo), ProcCmp);
    if (procUnit.procInfo[0].procMemSize < memSize)
    {
        // 这种fail-fast比较好，不容易遗漏临界值
        return -1;
    }

    ProcInfo procInfo = procUnit.procInfo[0];
    procInfo.procMemSize = procInfo.procMemSize - memSize;
    procInfo.deviceInfo[deviceId].deviceId = deviceId;
    procInfo.deviceInfo[deviceId].memSize = memSize;
    procInfo.deviceInfo[deviceId].procId = procInfo.procId;

    procUnit.procInfo[0] = procInfo;
    sys->procUnit[deviceType - 1] = procUnit;

    return procInfo.procId;
}

static bool DeviceMgtSystemDeleteDevice(DeviceMgtSystem *sys, int deviceId)
{
    for (int i = 0; i < PROC_UNIT_NUM; i++)
    {
        ProcUnit procUnit = sys->procUnit[i];
        for (int j = 0; j < procUnit.procNum; j++)
        {
            ProcInfo procInfo = procUnit.procInfo[j];
            for (int d = 0; d < DEVICE_NUM; d++)
            {
                if (procInfo.deviceInfo[d].deviceId == deviceId)
                {
                    procInfo.procMemSize = procInfo.procMemSize + procInfo.deviceInfo[d].memSize;
                    procInfo.deviceInfo[d].procId = 0;
                    procInfo.deviceInfo[d].memSize = 0;
                    procInfo.deviceInfo[d].deviceId = 0;

                    // C语言，数组中的元素如果取出来， 那么设置完之后，要让指针重新指向该元素
                    procUnit.procInfo[j] = procInfo;
                    sys->procUnit[i] = procUnit;
                    return true;
                }
            }
        }
    }

    return false;
}

int DeviceCmp(const void *a, const void *b)
{
    DeviceInfo *device_a = (DeviceInfo *)a;
    DeviceInfo *device_b = (DeviceInfo *)b;
    if (device_a->memSize != device_b->memSize)
    {
        return device_b->memSize - device_a->memSize;
    }
    else if (device_a->procId != device_b->procId)
    {
        return device_a->procId - device_b->procId;
    }
    else
    {
        return device_a->deviceId - device_b->deviceId;
    }
}

static DeviceInfo *DeviceMgtSystemQueryDevice(DeviceMgtSystem *sys, int deviceType, size_t *returnSize)
{
    DeviceInfo *result = (DeviceInfo *)malloc(sizeof(DeviceInfo) * DEVICE_NUM);
    memset(result, 0, sizeof(DeviceInfo) * DEVICE_NUM);
    int idx = 0;

    ProcUnit procUnit = sys->procUnit[deviceType - 1];
    for (int i = 0; i < procUnit.procNum; i++)
    {
        ProcInfo procInfo = procUnit.procInfo[i];
        for (int d = 0; d < DEVICE_NUM; d++)
        {
            if (procInfo.deviceInfo[d].deviceId != 0)
            {
                // memcpy(&result[idx], &procInfo.deviceInfo[d], sizeof(DeviceInfo)); //结构体数组 单个元素cpy 需要给指针
                result[idx] = procInfo.deviceInfo[d];
                // result[idx].deviceId = procInfo.deviceInfo[d].deviceId;
                // result[idx].memSize = procInfo.deviceInfo[d].memSize;
                // result[idx].procId = procInfo.deviceInfo[d].procId;
                idx++;
            }
        }
    }

    qsort(result, idx, sizeof(DeviceInfo), DeviceCmp);

    *returnSize = idx;
    return result;
}

static void DeviceMgtSystemFree(DeviceMgtSystem *sys)
{
    free(sys);
}

int main()
{
    // 第一个用例
    DeviceMgtSystem *sys = DeviceMgtSystemCreate(2, 200);
    printf("%s\n", "NULL");
    int result1 = DeviceMgtSystemCreateDevice(sys, 8, 1, 50);
    printf("%d\n", result1);

    int result2 = DeviceMgtSystemCreateDevice(sys, 12, 1, 30);
    printf("%d\n", result2);

    int result3 = DeviceMgtSystemCreateDevice(sys, 3, 1, 30);
    printf("%d\n", result3);

    size_t returnSize = 0;
    DeviceInfo *device = (DeviceInfo *)DeviceMgtSystemQueryDevice(sys, 1, &returnSize);
    for (int i = 0; i < returnSize; i++)
    {
        printf("%d,", device[i].deviceId);
        printf("%d,", device[i].memSize);
        printf("%d\n", device[i].procId);
    }

    int result4 = DeviceMgtSystemCreateDevice(sys, 15, 1, 30);
    printf("%d\n", result4);

    device = (DeviceInfo *)DeviceMgtSystemQueryDevice(sys, 1, &returnSize);
    for (int i = 0; i < returnSize; i++)
    {
        printf("%d,", device[i].deviceId);
        printf("%d,", device[i].memSize);
        printf("%d\n", device[i].procId);
    }

    bool delete10 = DeviceMgtSystemDeleteDevice(sys, 10);
    printf("%s\n", delete10 ? "true" : "false");
}