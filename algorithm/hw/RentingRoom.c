#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define CAP 1001;
#define ABS(a) ((a) > 0 ? (a) : -(a));

typedef struct
{
    bool valid;
    int area;
    int price;
    int rooms;
    int addr[2];
} RentingSystem;

int order[3] = {0};

RentingSystem *rs = NULL;

RentingSystem *RentingSystemCreate()
{
    RentingSystem *rentSys = (RentingSystem *)malloc(sizeof(RentingSystem) * CAP);
    memset(rentSys, 0, sizeof(RentingSystem) * CAP);
    return rentSys;
}

bool RentingSystemAddRoom(RentingSystem *obj, int id, int area, int price, int rooms, int *address, int addressSize)
{
    bool res = obj[id].valid ? false : true;
    obj[id].area = area;
    obj[id].price = price;
    obj[id].rooms = rooms;
    obj[id].addr[0] = address[0];
    obj[id].addr[1] = address[1];
    return res;
}

bool RentingSystemDeleteRoom(RentingSystem *obj, int id)
{
    bool res = obj[id].valid ? true : false;
    if (obj[id].valid)
    {
        obj[id].valid = false;
        return true;
    }
    else
    {
        return false;
    }
}

int *RentingSystemQueryRoom(RentingSystem *obj, int area, int price, int rooms, int *address, int addressSize,
                            int **orderBy, int orderBySize, int *retSize)
{

    

}

