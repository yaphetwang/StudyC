#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <float.h>

/*
C语言 二维数组 排序
1. 对二维数组的某一行排序
int compare_asc(const void *a, const void *b) {
    return (*(int *)a - *(int *)b); // 
}
    int arr[3][4] = {
        {9, 5, 3, 7},
        {2, 8, 1, 6},
        {4, 0, 2, 9}
    };

    int row = 1; // 对第 2 行（索引 1）排序
    int cols = sizeof(arr[0]) / sizeof(arr[0][0]); // 计算列数
    // 对指定行排序
    qsort(arr[row], cols, sizeof(int), compare_asc);
2. 对二维数组的某一列排序
由于 C 语言的二维数组是按行存储的，直接对列排序较复杂。需要 提取列数据 → 排序 → 写回：
    int col = 2; // 对第 3 列（索引 2）排序
    int rows = sizeof(arr) / sizeof(arr[0]); // 计算行数

    // 1. 提取指定列数据到临时数组
    int temp[rows];
    for (int i = 0; i < rows; i++) {
        temp[i] = arr[i][col]; 
    }

    // 2. 对临时数组排序
    qsort(temp, rows, sizeof(int), compare_asc);

    // 3. 将排序后的数据写回原列, 进行更新
    for (int i = 0; i < rows; i++) {
        arr[i][col] = temp[i];
    }
3. 按某列排序所有行（类似 Excel 按列排序表）
如果想根据某一列的值对整个二维数组的行重新排序（例如此题中按 第 1 列排序所有行）：

总结
需求	           方法
对某一行排序	    qsort(arr[row], cols, sizeof(int), compare)
对某一列排序	    提取列 → 排序 → 写回
按某列排序所有行	自定义比较函数，用 qsort 排序行（需处理指针）
*/

/*
float 类型转换成 字符数组：：：：：：：：：
1. 使用 sprintf()（最常用）
    float num = 3.14159f;
    char str[20]; // 确保足够大，避免缓冲区溢出

    // 转换为字符串（默认保留6位小数）
    sprintf(str, "%f", num);
    printf("字符串: %s\n", str); // 输出: "3.141590"

    // 控制小数位数（如保留2位）
    sprintf(str, "%.2f", num);
    printf("字符串: %s\n", str); // 输出: "3.14"
2. 使用 snprintf()（安全推荐）
    float num = 123.456f;
    char str[10];

    // 安全转换，限制写入长度
    snprintf(str, sizeof(str), "%.2f", num);
    printf("字符串: %s\n", str); // 输出: "123.46"（自动截断）
*/

/*
计算数组长度：：：：：：：：：：：：：：：
场景	       正确方法	                                      错误方法
静态一维数组	sizeof(arr) / sizeof(arr[0])	              sizeof(arr)（返回字节数）
动态数组	   手动记录长度（如 int n）	                       用 sizeof（返回指针大小）
函数参数	   额外传递长度参数	                               依赖 sizeof（会退化指针）
多维数组	   分层计算（如 行 = sizeof(arr)/sizeof(arr[0])）  直接 sizeof（无意义）
关键原则：

sizeof 只在 编译时已知大小的数组 上有效。

动态数组和函数参数必须 显式传递长度。
*/

/*
题目：



*/

#define NUM 3
#define RES_LEN 20

int sort_col; // 全局变量，存储要排序的列

// 比较函数（按第 sort_col 列排序）
int compare_col(const void *a, const void *b)
{
    float *row_a = (float *)a;
    float *row_b = (float *)b;
    return row_b[sort_col] - row_a[sort_col];
}

static char *PhoneCaseInventoryManage(float demand, int cnt, float *inventory, float *price, char *output)
{
    float count = 0.00f;
    // int inventorySize = sizeof(inventory) / sizeof(float); 指针类型无法通过sizeof计算数组长度
    // cnt 其实就是 inventory的长度
    float k[cnt][NUM];
    for (int i = 0; i < cnt; i++)
    {
        k[i][0] = price[i] / inventory[i];
        k[i][1] = inventory[i];
        k[i][2] = price[i];
    }

    int sort_col = 0; // 按第 1 列（索引 0）排序所有行
    int rows = sizeof(k) / sizeof(k[0]);
    int cols = sizeof(k[0]) / sizeof(k[0][0]);

    qsort(k, rows, sizeof(k[0]), compare_col);

    for (int i = 0; i < cnt; i++)
    {
        if (demand >= k[i][1])
        {
            count += k[i][2];
            demand -= k[i][1];
            continue;
        }

        count += demand * (k[i][2] / k[i][1]);
        break;
    }

    char *res = (char *)malloc(sizeof(char) * RES_LEN);
    sprintf(res, "%f", count);
    sprintf(output, "%.2f", count);
    return res;
}

int main()
{
    float demand = 20.00f;
    float inventory[] = {18.00f, 15.00f, 10.00f};
    float price[] = {75.00f, 72.00f, 45.00f};

    char res[RES_LEN] = {0};
    PhoneCaseInventoryManage(demand, 3, inventory, price, res);
    printf("%s", res);
}