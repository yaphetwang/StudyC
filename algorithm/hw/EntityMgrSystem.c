#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_ARRAY_SIZE 1000

typedef struct
{
    int entityTypeArray[MAX_ARRAY_SIZE];
    int relationship[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE];
} EntityMgrSystem;

/* 二维数组 尽量不用要，多用struct 包一层 ，更简单容易理解 */

static EntityMgrSystem *EntityMgrSystemCreate(int entityNum)
{
    EntityMgrSystem *sys = (EntityMgrSystem *)malloc(sizeof(EntityMgrSystem) * entityNum);
    if (sys == NULL)
    {
        return NULL;
    }
    memset(sys, 0, sizeof(EntityMgrSystem) * entityNum);
    return sys;
}

static bool EntityMgrSystemAddEntityType(EntityMgrSystem *sys, int entityId, int entityType)
{
    if (sys[entityId].entityTypeArray[entityType] == 1)
    {
        return false;
    }
    else
    {
        sys[entityId].entityTypeArray[entityType] = 1;
    }
    return true;
}

static bool EntityMgrSystemAddRelationship(EntityMgrSystem *sys, int relationshipType, int entityId1, int entityId2)
{
    int entityType1 = sys[entityId1].entityTypeArray[relationshipType];
    int entityType2 = sys[entityId2].entityTypeArray[relationshipType];
    if (entityType1 == 0 || entityType2 == 0)
    {
        return false;
    }

    if (sys[entityId1].relationship[relationshipType][entityId2] == 1 && sys[entityId2].relationship[relationshipType][entityId1] == 1)
    {
        return false;
    }

    sys[entityId1].relationship[relationshipType][entityId2] = 1;
    sys[entityId2].relationship[relationshipType][entityId1] = 1;
    return true;
}

static int *EntityMgrSystemQuery(EntityMgrSystem *sys, int entityId, int *returnSize)
{
    int type_count[MAX_ARRAY_SIZE];
    memset(type_count, 0, sizeof(type_count));
    for (size_t i = 0; i < MAX_ARRAY_SIZE; i++)
    {
        if (sys[entityId].entityTypeArray[i] == 1)
        {
            for (size_t j = 0; j < MAX_ARRAY_SIZE; j++)
            {
                // sys[entityId].relationship[i][j] == 1 ? type_count[i]++ : 0;
                type_count[i] += sys[entityId].relationship[i][j] == 1;
            }
        }
    }

    int type_count_size = 0;
    int max_count = 0;
    for (size_t i = 0; i < MAX_ARRAY_SIZE; i++)
    {
        if (type_count[i] > 0)
        {
            type_count_size++;
            max_count = type_count[i] > max_count ? type_count[i] : max_count;
        }
    }

    int *result = (int *)malloc(sizeof(int) * (type_count_size));
    int index = 0;
    while (max_count > 0)
    {
        for (size_t i = 0; i < MAX_ARRAY_SIZE; i++)
        {
            if (type_count[i] == max_count)
            {
                result[index++] = i;
            }
        }
        max_count--;
    }

    *returnSize = type_count_size;
    return result;
}

int main()
{
    EntityMgrSystem *sys = EntityMgrSystemCreate(10);
    bool result = EntityMgrSystemAddEntityType(sys, 4, 100);
    printf("4, 100:%d\n", result);
    bool result1 = EntityMgrSystemAddEntityType(sys, 3, 100);
    printf("3, 100:%d\n", result1);
    bool result2 = EntityMgrSystemAddEntityType(sys, 5, 101);
    printf("5, 101:%d\n", result2);
    bool result3 = EntityMgrSystemAddEntityType(sys, 4, 101);
    printf("4, 101:%d\n", result3);
    bool result4 = EntityMgrSystemAddRelationship(sys, 100, 4, 3);
    printf("100, 4, 3:%d\n", result4);
    bool result5 = EntityMgrSystemAddRelationship(sys, 101, 5, 4);
    printf("101, 5, 4:%d\n", result5);
    int resultSize;
    int *resultArray = EntityMgrSystemQuery(sys, 4, &resultSize);
    for (int i = 0; i < resultSize; i++)
    {
        printf("%d ", resultArray[i]);
    }
    printf("\n");
    bool result6 = EntityMgrSystemAddEntityType(sys, 3, 100);
    printf("3, 100:%d\n", result6);
    bool result7 = EntityMgrSystemAddEntityType(sys, 3, 101);
    printf("3, 101:%d\n", result7);
    bool result8 = EntityMgrSystemAddRelationship(sys, 101, 4, 3);
    printf("101, 4, 3:%d\n", result8);
    bool result9 = EntityMgrSystemAddEntityType(sys, 1, 103);
    printf("1, 103:%d\n", result9);

    bool result10 = EntityMgrSystemAddRelationship(sys, 103, 1, 4);
    printf("103, 1, 4:%d\n", result10);

    bool result11 = EntityMgrSystemAddEntityType(sys, 4, 103);
    printf("4, 103:%d\n", result11);
    bool result12 = EntityMgrSystemAddRelationship(sys, 103, 1, 4);
    printf("103, 1, 4:%d\n", result12);
    bool result13 = EntityMgrSystemAddRelationship(sys, 103, 4, 1);
    printf("103, 4, 1:%d\n", result13);

    bool result14 = EntityMgrSystemAddEntityType(sys, 5, 103);
    printf("5, 103:%d\n", result14);

    bool result15 = EntityMgrSystemAddRelationship(sys, 103, 5, 1);
    printf("103, 5, 1:%d\n", result15);

    int resultSize2;
    int *resultArray2 = EntityMgrSystemQuery(sys, 4, &resultSize2);
    for (int i = 0; i < resultSize2; i++)
    {
        printf("%d ", resultArray2[i]);
    }
    printf("\n");
}

/*
java角度：

*/