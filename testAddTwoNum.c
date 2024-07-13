#include <stdio.h>

/*定义两个全局变量*/
int x = 1;
int y = 2;
/* 定义函数 */
int addTwoNum();
int main(void)
{
    int result = addTwoNum();
    printf("The sum of %d and %d is %d\n", x, y, result);
    printf("result 为: %d\n",result);
    return 0;
}