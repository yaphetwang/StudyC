#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define L_LEN 100
#define B_LEN 100

/* 0 <= recordId,labId <= 1000 */

typedef struct
{
    int startTime;
    int endTime;
} Booking;

typedef struct
{
    int recordId;
    int fromTime;
    int toTime;
} Booked;

/* 可在Booked结构体里增加一个属性labId，表示该记录属于哪个实验室，
这样预约数组是统一的，不需要再为每个实验室维护一个预约数组，
考虑到实验室数量可能很多，可以节省内存。
不过一般函数参数是BookingSystem *sys，所以还是一个实验室维护一个预约数组。 */

typedef struct
{
    int labId;
    Booking bookings[B_LEN];
    Booked booked[B_LEN];
} BookingSystem;

BookingSystem *BookingSystemCreate()
{
    BookingSystem *sys = (BookingSystem *)malloc(sizeof(BookingSystem) * L_LEN);
    memset(sys, 0, sizeof(BookingSystem) * L_LEN);
    for (int i = 0; i < L_LEN; i++)
    {
        sys[i].labId = -1;
        for (int j = 0; j < B_LEN; j++)
        {
            sys[i].booked[j].recordId = -1;
        }
    }

    return sys;
}

int BookingSystemAddBooking(BookingSystem *sys, int labId, int startTime, int endTime)
{
    for (int i = 0; i < L_LEN; i++)
    {
        // 找到空闲的位置
        if (sys[i].labId == -1)
        {
            sys[i].labId = labId;
            sys[i].bookings[0].startTime = startTime;
            sys[i].bookings[0].endTime = endTime;
            return 1;
        }

        // 找到对应的实验室
        if (sys[i].labId == labId)
        {
            for (int j = 0; j < B_LEN; j++)
            {
                if (sys[i].bookings[j].startTime < endTime || startTime < sys[i].bookings[j].endTime)
                {
                    return 0;
                }
            }

            // 实验室没有冲突，可以添加预约
            for (int j = 0; j < B_LEN; j++)
            {
                if (sys[i].bookings[j].endTime == startTime)
                {
                    sys[i].bookings[j].endTime = endTime;
                    return 1;
                }
                else if (endTime == sys[i].bookings[j].startTime)
                {
                    sys[i].bookings[j].startTime = startTime;
                    return 1;
                }
                else
                {
                    if (sys[i].bookings[j].startTime == 0)
                    {
                        sys[i].bookings[j].startTime = startTime;
                        sys[i].bookings[j].endTime = endTime;
                        return 1;
                    }
                }
            }
        }
    }
}

int BookingSystemBook(BookingSystem *sys, int recordId, int fromTime, int toTime)
{
    /*数组 从左到右 检查每一个实验室，先检查是否在开放时间段内，不在返回0， 在的话，再检查是否已经预约， 未预约的话，则预约返回1，否则返回0*/
}

int BookingSystemCancel(BookingSystem *sys, int recordId)
{
}

void BookingSystemDestroy(BookingSystem *sys)
{
    free(sys);
}

int main()
{
}