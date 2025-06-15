#include <stdio.h>

/* 各种运算符 */

int main()
{
    /* 位运算符 */
    unsigned int a = 60; /* 60 = 0011 1100 */
    unsigned int b = 13; /* 13 = 0000 1101 */
    int c = 0;

    c = a & b; /* 12 = 0000 1100 */
    printf("Line 1 - c 的值是 %d\n", c);

    c = a | b; /* 61 = 0011 1101 */
    printf("Line 2 - c 的值是 %d\n", c);

    c = a ^ b; /* 49 = 0011 0001 */
    printf("Line 3 - c 的值是 %d\n", c);

    c = ~a; /*-61 = 1100 0011 */
    printf("Line 4 - c 的值是 %d\n", c);

    c = a << 2; /* 240 = 1111 0000 */
    printf("Line 5 - c 的值是 %d\n", c);

    c = a >> 2; /* 15 = 0000 1111 */
    printf("Line 6 - c 的值是 %d\n", c);

    // 判断是否是偶数，与1做 按位与运算，
    // 如果结果为0，则原数为偶数；如果结果为1，则原数为奇数
    int d = 5;
    printf("%d\n", d & 1);

    /* 一些杂项运算符 */
    /* sizeof()	返回变量的大小。
    sizeof(a) 将返回 4，其中 a 是整数。

    & 返回变量的地址。
    &a; 将给出变量的实际地址。

    * 指向一个变量。
    *a; 指针a将指向一个变量。

    ? :	条件表达式	如果条件为真 ? 则值为 X : 否则值为 Y
    */

    int e = 8;
    short f;
    double g;
    int *ptr;

    /* sizeof 运算符实例 */
    printf("Line 1 - 变量 e 的大小 = %lu\n", sizeof(e));
    printf("Line 2 - 变量 f 的大小 = %lu\n", sizeof(f));
    printf("Line 3 - 变量 g 的大小 = %lu\n", sizeof(g));

    // & 和 * 运算符实例
    ptr = &e; /* 'ptr' 现在包含 'e' 的地址 */
    printf("e 的值是 %d\n", e);
    printf("e 的地址值是 %p\n", &e);
    printf("e 的地址是: %p\n", (void *)&e);
    // 打印 *ptr 即是地址对应的变量e的值
    printf("*ptr 是 %d\n", *ptr);

    /* 三元运算符实例 */
    a = 10;
    b = (a == 1) ? 20 : 30;
    printf("b 的值是 %d\n", b);

    b = (a == 10) ? 20 : 30;
    printf("b 的值是 %d\n", b);

    return 0;
}