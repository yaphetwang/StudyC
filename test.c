#include <stdio.h>
#include <assert.h>

int main()
{

    /*我的第一个c程序*/
    printf("hello world!");
    printf("ccc!\n");

    unsigned int value = 0x10000;
    printf("value = %d\n", value);
    unsigned int *ptr = &value;
    *ptr -= 10;
    printf("value = %d\n", value);

    /* _Static_assert 是一个编译时的断言，
    用于在编译期间检查某个条件是否为真。
    如果条件为假（即值为0），编译器会报错并显示指定的错误信息
    如果你希望在特定条件下进行断言，你需要确保条件在编译时可以计算为真 */
    _Static_assert(1, "error");
    static_assert(1, "error");

    return 0;
}