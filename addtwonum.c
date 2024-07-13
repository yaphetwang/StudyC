#include <stdio.h>

/* 如果需要在一个源文件中引用另外一个源文件中定义的变量，
我们只需在引用的文件中将变量加上 extern 关键字的声明即可。 */

/* 外部变量声明,引用testAddTwoNum.c中定义的变量x和y */

extern int x;
extern int y;

int addTwoNum()
{
    return x + y;
}