#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/* 高可靠在线视频 */

#define ALLOCATE_NUM 1001

typedef struct
{
    int userId;
    int time;
    int videoType;
    int useVideoType;
    int isOccupy;
} Allocate;

typedef struct
{
    int *channels;
    int *usedChannels; // 已经使用的通道数，下标都是videoType 0 1 2
    int *charge;
    Allocate allocates[ALLOCATE_NUM];
} VideoService;

static VideoService *VideoServiceCreate(const int *channels, size_t channelsSize, const int *charge, size_t chargeSize)
{
    VideoService *sys = (VideoService *)malloc(sizeof(VideoService));
    memset(sys, 0, sizeof(VideoService));

    sys->channels = (int *)malloc(sizeof(int) * channelsSize);
    memcpy(sys->channels, channels, sizeof(size_t) * channelsSize);

    sys->charge = (int *)malloc(sizeof(int) * chargeSize);
    memcpy(sys->charge, charge, sizeof(size_t) * chargeSize);

    sys->usedChannels = (int *)malloc(sizeof(int) * channelsSize);
    memset(sys->usedChannels, 0, sizeof(int) * channelsSize);

    memset(sys->allocates, 0, sizeof(Allocate) * ALLOCATE_NUM);
    return sys;
}

static bool VideoServiceAllocateChannel(VideoService *sys, int time, int userId, int videoType)
{
}

// 来一个释放的方法，递归调用一下

static int VideoServiceFreeChannel(VideoService *sys, int time, int userId)
{
}

static int VideoServiceQueryChannel(VideoService *sys, int userId)
{
    if (sys->allocates[userId].isOccupy)
    {
        return sys->allocates[userId].useVideoType;
    }
    return -1;
}

static int VideoServiceFree(VideoService *sys)
{
    free(sys);
}