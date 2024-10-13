#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define WEEK_LEN 7
#define MAX_ALARMS 100

// 闹钟系统， 添加闹钟（id>0, weekdays 1-7,typeId 0,1,2）,检索闹钟

typedef struct
{
    int id;
    int weekdays[WEEK_LEN];
    int hour;
    int minute;
    int typeId;
} Alarm;

bool addAlarm(Alarm *alarms, int id, int *weekdays, int dayCount, int hour, int minute, int typeId)
{
    if (alarms[id].id != 0)
    {
        return false;
    }

    alarms[id].id = id;
    memcpy(alarms[id].weekdays, weekdays, dayCount * sizeof(int));
    alarms[id].hour = hour;
    alarms[id].minute = minute;
    alarms[id].typeId = typeId;
    return true;
}

bool deleteAlarm(Alarm *alarms, int id)
{
}

int cmpAlarms(const void *a, const void *b)
{
    Alarm *alarmA = (Alarm *)a;
    Alarm *alarmB = (Alarm *)b;

    if (alarmA->minute != alarmB->minute)
    {
        return (alarmA->minute - alarmB->minute);
    }
    else if (alarmA->typeId != alarmB->typeId)
    {
        return (alarmA->typeId - alarmB->typeId);
    }
    else
    {
        return (alarmA->id - alarmB->id);
    }
}

int *queryAlarms(Alarm *alarms, int weekday, int hour, int startMinute, int endMinute, int *numResults)
{
    int *res = (int *)malloc(MAX_ALARMS * sizeof(int));
    int count = 0;
    Alarm temp[MAX_ALARMS] = {0};
    for (int i = 0; i < MAX_ALARMS; i++)
    {
        if (alarms[i].id == 0)
        {
            continue;
        }
        bool match = false;
        for (size_t j = 0; j < WEEK_LEN; j++)
        {
            if (alarms[i].weekdays[j] == weekday)
            {
                match = true;
                break;
            }
        }
        if (!match)
        {
            continue;
        }
        if (alarms[i].hour != hour)
        {
            continue;
        }
        if (alarms[i].minute < startMinute || alarms[i].minute > endMinute)
        {
            continue;
        }
        temp[count++] = alarms[i];
    }

    // 排序
    qsort(temp, count, sizeof(Alarm), cmpAlarms);
    // 结果
    int index = 0;
    for (int i = 0; i < count; i++)
    {
        if (temp[i].id != 0)
        {
            res[index++] = temp[i].id;
        }
    }

    *numResults = index;
    return res;
}

int main()
{
    Alarm *alarms = (Alarm *)malloc(MAX_ALARMS * sizeof(Alarm));
    memset(alarms, 0, MAX_ALARMS * sizeof(Alarm));

    // add some alarms
    int weekdays[] = {1, 2, 3, 4, 5};
    int dayCount = sizeof(weekdays) / sizeof(int);
    bool result = addAlarm(alarms, 1, weekdays, dayCount, 8, 30, 1);
    printf("1, 8:00:%d\n", result);

    printf("alarms:id:%d\n", alarms[0].id);
    printf("alarms:weekdays:");
    for (size_t i = 0; i < WEEK_LEN; i++)
    {
        printf("%d ", alarms[0].weekdays[i]);
    }
    printf("\n");

    printf("alarms:hour:%d\n", alarms[0].hour);
    printf("alarms:minute:%d\n", alarms[0].minute);
    printf("alarms:typeId:%d\n", alarms[0].typeId);

    int weekdays1[] = {4, 5};
    int dayCount1 = sizeof(weekdays1) / sizeof(int);
    result = addAlarm(alarms, 2, weekdays1, dayCount1, 9, 30, 1);
    printf("2, 9:30:%d\n", result);

    int weekdays2[] = {6, 7};
    int dayCount2 = sizeof(weekdays2) / sizeof(int);
    result = addAlarm(alarms, 3, weekdays2, dayCount2, 10, 0, 2);
    printf("3, 10:00:%d\n", result);

    int weekdays3[] = {1, 3, 5, 7};
    int dayCount3 = sizeof(weekdays3) / sizeof(int);
    result = addAlarm(alarms, 4, weekdays3, dayCount3, 8, 30, 0);
    printf("4, 11:30:%d\n", result);

    int weekdays4[] = {2, 4, 6};
    int dayCount4 = sizeof(weekdays4) / sizeof(int);
    result = addAlarm(alarms, 5, weekdays4, dayCount4, 12, 0, 0);
    printf("5, 12:00:%d\n", result);

    int weekdays5[] = {1, 2, 4, 6};
    int dayCount5 = sizeof(weekdays5) / sizeof(int);
    result = addAlarm(alarms, 6, weekdays5, dayCount5, 13, 30, 2);
    printf("6, 13:30:%d\n", result);

    int weekdays6[] = {1, 2, 5, 6};
    int dayCount6 = sizeof(weekdays6) / sizeof(int);
    result = addAlarm(alarms, 7, weekdays6, dayCount6, 14, 0, 0);
    printf("7, 14:00:%d\n", result);

    int weekdays7[] = {1, 3, 5, 6};
    int dayCount7 = sizeof(weekdays7) / sizeof(int);
    result = addAlarm(alarms, 8, weekdays7, dayCount7, 15, 30, 1);
    printf("8, 15:30:%d\n", result);

    int weekdays8[] = {2, 3, 5, 6};
    int dayCount8 = sizeof(weekdays8) / sizeof(int);
    result = addAlarm(alarms, 9, weekdays8, dayCount8, 16, 0, 2);
    printf("9, 16:00:%d\n", result);

    int weekdays9[] = {1, 2, 3, 4, 5, 6, 7};
    int dayCount9 = sizeof(weekdays9) / sizeof(int);
    result = addAlarm(alarms, 10, weekdays9, dayCount9, 17, 30, 1);
    printf("10, 17:30:%d\n", result);

    // query alarms
    int numResults = 0;
    int *res = (int *)queryAlarms(alarms, 1, 8, 0, 60, &numResults);
    printf("query alarms on Monday 8:00-9:00\n");
    for (int i = 0; i < numResults; i++)
    {
        printf("%d ", res[i]);
    }
    printf("\n");

    return 0;
}