#include "include_asm.h"
#include "COMMON/ITEMRECAT20V1.H"
#include "TYPES.H"

/* osMotorInit, drafted from ultralib src/io/motor.c (the branch before 2.0J) with its static
   _MakeMotorData, which this library inlines: _MotorStartData, _motorstartbuf, _MotorStopData and _motorstopbuf are
   g_controllerMotorStartCommands, g_controllerMotorStartData, g_controllerMotorStopCommands and g_controllerMotorStopData, and __osMotorinitialized is g_controllerMotorInitialized. */
extern OSPifRam g_controllerMotorStartCommands[4];
extern u8 g_controllerMotorStartData[32];
extern OSPifRam g_controllerMotorStopCommands[4];
extern u8 g_controllerMotorStopData[32];
extern s32 g_controllerMotorInitialized[4];
extern s32 __osContRamRead(OSMesgQueue *mq, int channel, u16 address, u8 *buffer);
extern s32 __osContRamWrite(OSMesgQueue *mq, int channel, u16 address, u8 *buffer, int force);
extern u8 __osContAddressCrc(u16 address);
static inline void _MakeMotorData(int channel, u16 address, u8 *buffer, OSPifRam *mdata)
{
    u8 *ptr = (u8 *)mdata->ramarray;
    __OSContRamReadFormat ramreadformat;
    int i;
    for (i = 0; i < ((s32)(sizeof(mdata->ramarray) / sizeof(mdata->ramarray[0]))); i++) {
        mdata->ramarray[i] = 0;
    }
    mdata->pifstatus = 1;
    ramreadformat.dummy = 0xFF;
    ramreadformat.txsize = 35;
    ramreadformat.rxsize = 1;
    ramreadformat.cmd = 3;
    ramreadformat.address = (address << 0x5) | __osContAddressCrc(address);
    ramreadformat.datacrc = 0xFF;
    for (i = 0; i < ((s32)(sizeof(ramreadformat.data) / sizeof(ramreadformat.data[0]))); i++) {
        ramreadformat.data[i] = *buffer++;
    }
    if (channel != 0) {
        for (i = 0; i < channel; i++) {
            *ptr++ = 0;
        }
    }
    *(__OSContRamReadFormat *)ptr = ramreadformat;
    ptr += sizeof(__OSContRamReadFormat);
    ptr[0] = 0xFE;
}
s32 osMotorInit(OSMesgQueue *mq, OSPfs *pfs, int channel)
{
    int i;
    s32 ret;
    u8 temp[32];
    u8 *startbuf;
    u8 *stopbuf;
    pfs->queue = mq;
    pfs->channel = channel;
    pfs->status = 0;
    pfs->activebank = 128;
    for (i = 0; i < ((s32)(sizeof(temp) / sizeof(temp[0]))); i++) {
        temp[i] = 254;
    }
    ret = __osContRamWrite(mq, channel, 0x400, temp, 0);
    if (ret == 2) {
        ret = __osContRamWrite(mq, channel, 0x400, temp, 0);
    }
    if (ret != 0) {
        return ret;
    }
    ret = __osContRamRead(mq, channel, 0x400, temp);
    if (ret == 2) {
        ret = 4;
    }
    if (ret != 0) {
        return ret;
    }
    if (temp[31] == 254) {
        return 11;
    }
    for (i = 0; i < ((s32)(sizeof(temp) / sizeof(temp[0]))); i++) {
        temp[i] = 128;
    }
    ret = __osContRamWrite(mq, channel, 0x400, temp, 0);
    if (ret == 2) {
        ret = __osContRamWrite(mq, channel, 0x400, temp, 0);
    }
    if (ret != 0) {
        return ret;
    }
    ret = __osContRamRead(mq, channel, 0x400, temp);
    if (ret == 2) {
        ret = 4;
    }
    if (ret != 0) {
        return ret;
    }
    if (temp[31] != 0x80) {
        return 11;
    }
    if (!g_controllerMotorInitialized[channel]) {
        for (i = 0; i < ((s32)(sizeof(g_controllerMotorStartData) / sizeof(g_controllerMotorStartData[0]))); i++) {
            /* Each buffer address is taken where it is used, as -fforce-addr compiles it, so the
               loop optimiser hoists it into a register in this order. */
            startbuf = g_controllerMotorStartData;
            startbuf[i] = 1;
            stopbuf = g_controllerMotorStopData;
            stopbuf[i] = 0;
        }
        _MakeMotorData(channel, 0x600, g_controllerMotorStartData, &g_controllerMotorStartCommands[channel]);
        _MakeMotorData(channel, 0x600, g_controllerMotorStopData, &g_controllerMotorStopCommands[channel]);
        g_controllerMotorInitialized[channel] = 1;
    }
    return 0;
}

#if defined(VERSION_US)
unsigned char g_OsmotorinitTrailingBytes[4] = { 0x00, 0x0B, 0x00, 0x00 };
#endif

#if defined(VERSION_US)
unsigned int k_OsmotorinitEncodedWords[1] = {
    0x0010000B,
};
#endif
