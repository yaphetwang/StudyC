#include <stdio.h>

// 函数外定义变量 x 和 y
int x;
int y;

int addtwonum()
{
    // 函数内声明变量 x 和 y 为外部变量
    extern int x;
    extern int y;

    // 给外部变量（全局变量）x 和 y 赋值
    x = 1;
    y = 2;
    return x + y;
}

int main()
{
    int x = 10;           // 整型变量 x 初始化为 10
    float pi = 3.14;      // 浮点型变量 pi 初始化为 3.14
    char ch = 'A';        // 字符型变量 ch 初始化为字符 'A'
    int d = 3, f = 5;     // 定义并初始化 d 和 f
    unsigned char z = 22; // 定义并初始化 z

    /* 变量的声明有两种情况：
1、一种是需要建立存储空间的。
例如：int a 在声明的时候就已经建立了存储空间。
2、另一种是不需要建立存储空间的，通过使用extern关键字声明变量名而不定义它。
例如：extern int a 其中变量 a 可以在别的文件中定义的。
除非有 extern 关键字，否则都是变量的定义。 */
    // 声明外部变量
    extern int a;
    extern int b;

    /* 局部变量（在函数内部定义的非静态变量）不会自动初始化为默认值，
    它们的初始值是未定义的（包含垃圾值）。
    因此，在使用局部变量之前，应该显式地为其赋予一个初始值。 */
    int y;
    printf("y = %d\n", y);

    int result = addtwonum(); // 调用函数 addtwonum()
    printf("result = %d\n", result);
    return 0;
}
