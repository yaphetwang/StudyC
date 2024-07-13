#include <stdio.h>

int main()
{

    int arr[] = {64, 34, 25, 12, 22, 11, 90};
    printf("%d \n", sizeof(arr));
    printf("%d \n", sizeof(*arr));
    // 指向数组的第一个元素
    int *q = arr;
    printf("%d \n", *q);
    // 指向下一个元素
    q++;
    printf("%d \n", *q);

    // 数组名本身就是一个指向数组第一个元素的指针
    printf("%d\n", *(q + 1));

    int *p;
    printf("p: %zu\n", sizeof(p));
}