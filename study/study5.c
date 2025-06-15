#include <stdio.h>
#include <stdbool.h>

// 用例足够使用
#define BUF_LEN 64
#define OUT_BUF_LEN 64
#define MEMORY_LEN 100
#define NO_ALLOCATE 0
#define ALLOCATE 1

int *memory;
// int memory[MEMORY_LEN];

int *memory_index;
// int memory_index[MEMORY_LEN];

void MemPoolInit(void)
{
    memory = (int *)malloc(sizeof(int) * MEMORY_LEN);
    for (int i = 0; i < MEMORY_LEN; i++)
    {
        memory[i] = 0;
    }

    memory_index = (int *)malloc(sizeof(int) * MEMORY_LEN);
    for (int i = 0; i < MEMORY_LEN; i++)
    {
        memory_index[i] = -1;
    }
}

int NextIndex(int index)
{
    for (int i = index; i < MEMORY_LEN; i++)
    {
        if (memory_index[i] > 0)
        {
            return i + memory_index[i];
        }
    }
    return index + 1;
}

void MemPoolDeinit(void)
{
    free(memory);
    free(memory_index);
}

/* 返回分配的内存首地址，失败返回 -1，框架会自动输出"error" */
int MemPoolRequest(int memSize)
{
    if (memSize <= 0)
        return -1;
    int start_index = 0;
    int count = 0;
    int start_i = 0;
    int flag = 0;
    while (flag == 0)
    {
        for (int i = start_i; i < MEMORY_LEN; i++)
        {
            if (memory[i] == NO_ALLOCATE)
            {
                if (count == 0)
                {
                    // 记录起始位置
                    start_index = i;
                }
                count++;
                if (count == memSize)
                {
                    flag = 1;
                    break;
                }

                if (i == MEMORY_LEN - 1)
                {
                    flag = -1;
                }
            }
            else
            {
                if (count == memSize)
                {
                    // 空间够了
                    flag = 1;
                    break;
                }
                else
                {
                    // 找下一段
                    start_index = 0;
                    count = 0;
                    start_i = NextIndex(i); // 下一起始位置
                    if (start_i >= MEMORY_LEN)
                    {
                        flag = -1;
                    }
                    break;
                }
            }
        }
    }

    if (flag == 1 && count == memSize)
    {
        for (int j = start_index; j < start_index + count; j++)
        {
            memory[j] = ALLOCATE;
        }

        memory_index[start_index] = count;

        return start_index;
    }

    return -1;
}

/* 成功返回 true；失败返回 false，框架会自动输出 "error" */
bool MemPoolRelease(int startAddr)
{
    if (startAddr < 0 || startAddr >= MEMORY_LEN)
    {
        return false;
    }
    else
    {
        if (memory_index[startAddr] > 0)
        {
            for (int k = startAddr; k < startAddr + memory_index[startAddr]; k++)
            {
                memory[k] = NO_ALLOCATE;
            }

            // 内存释放后 起始位置记录重置
            memory_index[startAddr] = -1;
            return true;
        }
    }
    return false;
}

int main(void)
{
    MemPoolInit();

    int n;
    if (scanf_s("%d\n", &n) != 1)
    {
        return -1;
    }

    char buf[BUF_LEN];
    for (int i = 0; i < n; i++)
    {
        if (gets_s(buf, sizeof(buf)) == NULL)
        {
            return -1;
        }
        int info = atoi(buf + 8);
        if (buf[2] == 'Q')
        { // REQUEST
            int addr = MemPoolRequest(info);
            if (addr != -1)
            {
                (void)printf("%d\n", addr);
            }
            else
            {
                (void)printf("error\n");
            }
        }
        else
        { // RELEASE
            bool ret = MemPoolRelease(info);
            if (ret == false)
            {
                (void)printf("error\n");
            }
        }
    }

    MemPoolDeinit();
    return 0;
}
