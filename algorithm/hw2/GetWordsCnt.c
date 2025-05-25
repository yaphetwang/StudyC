#include <ctype.h>
#include <stdbool.h>


static int GetWordsCnt(char **lines, size_t linesSize)
{
    int cnt = 0;
    char *temp = (char *)malloc(2000);
    memset_s(temp, 2000, 0, 2000);
    int idx = 0;
    for (int i = 0; i < linesSize; i++) {
        int len = strlen(lines[i]);
        for (int j = 0; j < len; j++) {
            if (lines[i][j] != '\0') {
                temp[idx++] = lines[i][j];
            }
            if (j == len - 1 && lines[i][j] != '-') {
                temp[idx++] = ',';
            }
        }
    }

    printf("temp:%s\n", temp);

    bool start = false;
    for (int i = 0; i < 2000; i++) {
        if (!start && islower(temp[i])) {
            start = true;
        }

        if (temp[i] == '-') {
            continue;
        }

        if (start && temp[i] == '\0') {
            cnt++;
            break;
        }

        if (temp[i] == '\0') {
            break;
        }

        if (start && !islower(temp[i])) {
            cnt++;
            start = false;
        }
    }

    return cnt;
}

int main(void)
{
    // char *lines[] = {"engineers , worldwide, ,.courses     part", "y.. .vendors.", ",hell-", "o"};
    // int cnt = GetWordsCnt(lines, 4);
    char *lines[] = {"a -", "aagg-", "-", "aa,b.", "h-", "   ell-", "o-", " ", "world."};
    int cnt = GetWordsCnt(lines, 9);
    printf("cnt:%d\n", cnt);
}
