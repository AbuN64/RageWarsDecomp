#ifndef LIBULTRA_OS_PI_DEVICE_MANAGER_OPERATIONS_H
#define LIBULTRA_OS_PI_DEVICE_MANAGER_OPERATIONS_H
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/OSPIHANDLE_S.H"
#include "TYPES.H"
extern void System_PeripheralManagerThreadEntry(void*);
extern s32 System_PeripheralExtendedDmaEntry(struct OSPiHandle_s*, s32, u32, void*, u32);
extern s32 System_PeripheralRawDmaEntry(s32, u32, void*, u32);
extern struct OSThread_s g_peripheralManagerThread;
extern char g_peripheralManagerThreadStack[0x1000];
extern OSMesgQueue g_peripheralManagerAccessQueue;
extern void*g_peripheralAccessMessages[1];
#endif
