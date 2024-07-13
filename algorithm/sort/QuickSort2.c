#include <stdio.h>

// 分区函数
int partition(int arr[], int left, int right)
{
    // 选择第一个元素作为基准
    int pivot = arr[left];
    while (left < right)
    {
        while (left < right && arr[right] >= pivot)
        {
            // 大于基准值，往前(左)走，直到找到一个小于基准值的
            right--;
        }
        if (left < right)
        {
            arr[left] = arr[right];
        }

        while (left < right && arr[left] <= pivot)
        {
            // 小于基准值，往后走，直到找到一个大于基准值的
            left++;
        }
        if (left < right)
        {
            arr[right] = arr[left];
        }
    }

    // 直到 left==right 结束，将基准值赋值
    arr[left] = pivot;
    return left;
}

// 快速排序函数
void quickSort(int arr[], int left, int right)
{
    if (left < right)
    {
        // pi是分区索引，arr[pi]已经排好序
        int pi = partition(arr, left, right);

        // 分别对pi左右两边的子数组进行排序
        quickSort(arr, left, pi - 1);
        quickSort(arr, pi + 1, right);
    }
}

// 打印数组
void printArray(int arr[], int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main()
{
    int arr[] = {10, 7, 8, 9, 1, 5};
    int n = sizeof(arr) / sizeof(arr[0]);
    printf("原始数组: \n");
    printArray(arr, n);
    quickSort(arr, 0, n - 1);
    printf("排序后的数组: \n");
    printArray(arr, n);
    return 0;
}
