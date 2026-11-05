#ifndef ENGINE_CACHE_LOADER_H
#define ENGINE_CACHE_LOADER_H
#include "types.h"
struct CartridgeReadRequest;
struct CartridgeReadWorker;
void Cartridge_ReadChunksAndWait(struct CartridgeReadWorker *cartridgeReadWorker, u32 sourceAddress, s32 byteCount, void *extra);
void Cartridge_StartReadWorker(struct CartridgeReadWorker *worker, s32 count);
struct Queue;
void Cartridge_SubmitReadChunks(struct CartridgeReadWorker *worker, u32 source, s32 length, void *destination, struct Queue *queue, s32 value, s32 direct);
#if defined(VERSION_US_REV1)
extern void Libultra_RunDebugLinkCommands(void);
extern s32 __osPiRawStartDma(s32, u32, void *, u32);
extern void Cartridge_ReleaseReadRequest(s32, struct CartridgeReadRequest *);
#endif
#if !(defined(VERSION_US_REV1))
extern s32 __osPiRawStartDma(s32, u32, void *, u32);
extern void Cartridge_ReleaseReadRequest(s32, struct CartridgeReadRequest *);
#endif
struct Queue {
    char pad[0x14];
    s32 items[4];
};

#endif
