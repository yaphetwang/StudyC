#include <stdio.h>

// 函数声明
void bubbleSort(int arr[], int n);
void printArray(int arr[], int n);

// 主函数
int main() {
    int arr[] = {10, 7, 8, 9, 1, 5, 4};
    int n = sizeof(arr) / sizeof(arr[0]);
    printf("原始数组: \n");
    printArray(arr, n);
    bubbleSort(arr, n);
    printf("排序后的数组: \n");
    printArray(arr, n);
    return 0;
}

// 冒泡排序函数
void bubbleSort(int arr[], int n) {
    int i, j;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                // 交换 arr[j] 和 arr[j + 1]
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// 打印数组函数
void printArray(int arr[], int n) {
    int i;
    for (i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}
