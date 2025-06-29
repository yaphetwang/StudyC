#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>

#define B_LEN 8

// 计算一个整数的二进制表示 整数范围 0-255
char *getBinary(int num)
{
    // 处理字符串 ，一定要多给一位， 留给结束符  '\0'
    char *b = (char *)malloc(sizeof(char) * (B_LEN + 1));
    memset(b, 0, sizeof(char) * B_LEN);
    b[B_LEN] = '\0';
    printf("b: %s\n", b);
    int len = B_LEN;
    while (num != 0)
    {
        int d = num % 2;
        num = num / 2;
        b[--len] = d + '0';
    }

    printf("b: %s\n", b);
    return b;
}

static char *GetIpv4Data(const uint8_t *data, size_t dataSize)
{
    for (int i = 0; i < dataSize; i++)
    {
        printf("%x \n", data[i]);
    }

    char *res = (char *)malloc(sizeof(char) * 20);
    memset(res, 0, sizeof(char) * 20);

    // 取标识
    char identStr[8] = {0};
    sprintf(identStr, "%x%x", data[4], data[5]);
    int ident = strtol(identStr, NULL, 16);
    char ident_r[8] = {0};
    sprintf(ident_r, "%d", ident);
    strcat(res, ident_r);
    printf("ident_r:%s\n", ident_r);
    strcat(res, ",");

    // 取标志
    char signStr[9] = {0};
    snprintf(signStr, sizeof(signStr), "%d%d%d%d%d%d%d%d",
             (data[6] >> 7) & 1,
             (data[6] >> 6) & 1,
             (data[6] >> 5) & 1,
             (data[6] >> 4) & 1,
             (data[6] >> 3) & 1,
             (data[6] >> 2) & 1,
             (data[6] >> 1) & 1,
             data[6] & 1);
    printf("signStr:%s\n", signStr);

    char sign_r[8] = {0};
    strncat(sign_r, signStr, 3);
    int sign = strtol(sign_r, NULL, 2);
    char sign_res[8] = {0};
    sprintf(sign_res, "%d", sign);
    strcat(res, sign_res);
    return res;
}

int main()
{
    uint8_t data[7] = {0x45, 0x00, 0x10, 0x3C, 0x37, 0x21, 0xA0};
    char *res = (char *)GetIpv4Data(data, sizeof(data) / sizeof(uint8_t));
    printf("%s\n", res);

    uint8_t value = 0xA0; // 2个16进制字符 转成8位二进制
    char binary[9] = {0};
    snprintf(binary, sizeof(binary), "%d%d%d%d%d%d%d%d",
             (value >> 7) & 1,
             (value >> 6) & 1,
             (value >> 5) & 1,
             (value >> 4) & 1,
             (value >> 3) & 1,
             (value >> 2) & 1,
             (value >> 1) & 1,
             value & 1);

    printf("binary: %s\n", binary); // 输出 "10100000"

    // uint8_t value = 0x5;  一个16进制字符 转成4位二进制
    // char binary[5];
    // snprintf(binary, sizeof(binary), "%d%d%d%d",
    //     (value >> 3) & 1,
    //     (value >> 2) & 1,
    //     (value >> 1) & 1,
    //     value & 1);
    // printf("binary: %s\n", binary); // 输出 "0101"

    uint8_t u = 0xA0;
    char str[8] = {0};
    sprintf(str, "%x", u);
    int binary_int = strtol(str, NULL, 16);
    printf("binary_int: %d\n", binary_int);
    char *binary_str = (char *)getBinary(binary_int);
    printf("binary_str: %s\n", binary_str);

    return 0;
}