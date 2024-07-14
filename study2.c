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

// #define定义常量
#define PI 3.14159
#define NEWLINE '\n'
// 定义静态全局变量
static int count = 10;
/* 函数声明 */
static void func1(void);

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

    // 输出常量
    printf("PI = %f\n", PI);
    printf("NEWLINE = %c\n", NEWLINE);

    // const 定义常量
    const int C = 100;
    printf("C = %d\n", C);

    // auto 存储类是所有局部变量默认的存储类。
    // 定义在函数中的变量默认为 auto 存储类，
    // 这意味着它们在函数开始时被创建，在函数结束时被销毁。
    // auto 只能用在函数内，即 auto 只能修饰局部变量。

    // static 存储类,
    // 静态变量在程序中只被初始化一次，即使函数被调用多次，该变量的值也不会重置。
    // static 只能用在全局变量或静态局部变量，
    // 即 static 只能修饰全局变量和静态局部变量。
    // 当 static 修饰全局变量时，会使变量的作用域限制在声明它的文件内
    while (count--)
    {
        func1();
    }

    return 0;
}

static void func1(void)
{
    /* 'thingy' 是 'func1' 的 静态 局部变量 - 只初始化一次
     * 每次调用函数 'func1' 'thingy' 值不会被重置为5。 */
    static int thingy = 5;
    thingy++;
    printf(" thingy 为 %d ， count 为 %d\n", thingy, count);
}
