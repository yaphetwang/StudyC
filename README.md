# StudyC

# 根据 数据的格式 将一个或多个数据 格式化输出到 字符串中
sprintf(identStr, "%x%x", data[4], data[5]);
sprintf(ident_r, "%d", ident);

# 这些函数 的字符串参数是指针类型， 可以通过指针 来指定从指定的位置 开始操作
strcpy，strncpy，strcat，strncat，sprintf
strncat(str1, str2, 3);
strcpy(str1, str2 + 2);

# 将一个数字（0-255） 转换成八位二进制
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

# 字符串转换成 数字
1. int num2 = atoi(str);  废弃用法
2. 按字符串中数据格式 转成 十进制数
int ident = strtol(identStr, NULL, 16); 
3. sscanf
char ss[] = "PSH t 400";
sscanf_s(ss, "%s %c %c", cal, strlen(cal), &stack_idx_c, 1, &num_c, 1);
输出: PSH t 4
sscanf_s(ss, "%s %c %d", cal, strlen(cal), &stack_idx_c, 1, &num);
输出: PSH t 400

注意: %s 碰到 空格，结束符 会停止

%[^|]

# isupper islower toupper tolower

# abs



