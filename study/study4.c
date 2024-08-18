#include <stdio.h>

/* 函数，作用域规则，数组，枚举 */

/* 函数声明 */
int max(int num1, int num2);

/* 全局变量声明 */
int g = 20;

// 宏定义
#define LENGTH(array) (sizeof(array) / sizeof(array[0]))

int main()
{
    /* 局部变量定义 */
    int a = 100;
    int b = 200;
    int ret;

    /* 调用函数来获取最大值 */
    ret = max(a, b);
    printf("Max value is : %d\n", ret);

    /* 局部变量声明 */
    // 在函数内，如果两个名字相同，会使用局部变量值，全局变量不会被使用
    /* 全局变量保存在内存的全局存储区中，占用静态的存储单元；
       局部变量保存在栈中，只有在所在函数被调用时才动态地为变量分配存储单元。
    */
    int g = 10;
    printf("value of g = %d\n", g);

    int array[] = {1, 2, 3, 4, 5};
    int length = sizeof(array) / sizeof(array[0]);
    printf("数组长度为: %d\n", length);
    length = LENGTH(array);
    printf("数组长度为: %d\n", length);

    // 在 C 语言中，数组名表示数组的地址，
    // 即数组首元素的地址。当我们在声明和定义一个数组时，
    // 该数组名就代表着该数组的地址。
    int myArray[5] = {10, 20, 30, 40, 50};
    int *ptr = &myArray[0]; // 或者直接写作 int *ptr = myArray;

    return 0;
}

/* 函数返回两个数中较大的那个数 */
int max(int num1, int num2)
{
    /* 局部变量声明 */
    int result;

    if (num1 > num2)
        result = num1;
    else
        result = num2;

    return result;
}