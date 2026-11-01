#ifndef SDK_LEO_H
#define SDK_LEO_H
#include "TYPES.H"





typedef struct OSPiHandle_leo {
    struct OSPiHandle_leo *next;
    u8 type;
    u8 latency;
    u8 pageSize;
    u8 relDuration;
    u8 pulse;
    u8 domain;
    u32 baseAddress;
    u32 speed;
    __OSTranxInfo transferInfo;
} OSPiHandle_leo;

extern OSPiHandle_leo *g_currentDiskPeripheralHandle;
extern s32 __osEPiRawStartDma(OSPiHandle_leo *handle, s32 direction, u32 cartAddr, void *dramAddr, u32 size);
extern void __osLeoResume(void);
extern void __osLeoAbnormalResume(void);
#endif
