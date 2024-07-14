#include <stdio.h>

/* 如果需要在一个源文件中引用另外一个源文件中定义的变量，
我们只需在引用的文件中将变量加上 extern 关键字的声明即可。 */

/* 外部变量声明,引用testAddTwoNum.c中定义的变量x和y */
/* extern 关键字用于声明已经在testAddTwoNum.c文件中定义的 x和y */
extern int x;
extern int y;

/* extern 存储类用于定义在其他文件中声明的全局变量或函数。
当使用 extern 关键字时，不会为变量分配任何存储空间，
而只是指示编译器该变量在其他文件中定义。
extern 存储类用于提供一个全局变量的引用，
全局变量对所有的程序文件都是可见的。
当您使用 extern 时，对于无法初始化的变量，
编译器会把变量名指向一个之前定义过的存储位置。
extern 修饰符通常用于当有两个或多个文件共享相同的全局变量或函数的时候
*/

int addTwoNum()
{
    return x + y;
}