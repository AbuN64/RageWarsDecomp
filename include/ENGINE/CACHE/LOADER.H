#ifndef ENGINE_CACHE_LOADER_H
#define ENGINE_CACHE_LOADER_H
struct CartridgeReadWorker;
void Cartridge_ReadChunksAndWait(struct CartridgeReadWorker *cartridgeReadWorker, u32 sourceAddress, s32 byteCount, void *extra);
void Cartridge_StartReadWorker(struct CartridgeReadWorker *worker, s32 count);
struct Queue;
void Cartridge_SubmitReadChunks(struct CartridgeReadWorker *worker, u32 source, s32 length, void *destination, struct Queue *queue, s32 value, s32 direct);
#endif
