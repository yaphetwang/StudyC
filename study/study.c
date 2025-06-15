#include <stdio.h>

/* 指针 */

int main()
{

    int arr[] = {64, 34, 25, 12, 22, 11, 90};
    printf("数组长度:%lu \n", sizeof(arr));
    printf("数组第一个元素长度%lu \n", sizeof(*arr));
    // 指向数组的第一个元素
    int *q = arr;
    printf("%d \n", *q);
    // 指向下一个元素
    q++;
    printf("%d \n", *q);

    // 数组名本身就是一个指向数组第一个元素的指针
    printf("%d\n", *(q + 1));

    int *p;
    printf("p指针指向的变量类型字节长度: %zu\n", sizeof(*p));
    printf("p指针类型字节长度: %zu\n", sizeof(p));
}