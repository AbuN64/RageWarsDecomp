#ifndef RESMGR_RESMGR_STRING_MEMORY_H
#define RESMGR_RESMGR_STRING_MEMORY_H
#include "COMMON/MESSAGESEMAPHORE.H"
/* Single-message queue used by the acquire/release helpers. */
typedef struct MessageSemaphore {
    OSMesgQueue queue;
    s32 message;
} MessageSemaphore;
extern s32 XPlus_CompareStringsIgnoreCase(u8 *left, u8 *right);
extern u8 *XPlus_CopyStringBounded(u8 *destination, u8 *source, s32 count);
extern void XPlus_SeedRandomGenerator(int seed);
extern int XPlus_LowercaseCharacter(int character);
extern u8 *XPlus_FindByte(u8 *buffer, s32 value, s32 length);
extern void XPlus_BuildPath(u8 *path, u8 *drive, u8 *directory, u8 *name, u8 *extensionArg);
extern u32 XPlus_UpdateCrc32(u8 *data, u32 length, u32 crc);
extern u8 *XPlus_AppendStringBounded(u8 *destination, u8 *source, s32 count);
extern void XPlus_FormatDecimalInteger(s32 n, char *s);
extern u8 *XPlus_FindLastCharacter(u8 *s, int c);
extern s32 XPlus_CompareMemory(u8 *left, u8 *right, s32 count);
extern void *XPlus_FillBytes(void *destination, int value, u32 count);
extern void *XPlus_CopyBytes(void *destination, const void *source, s32 bytes);
extern s32 XPlus_CompareStrings(const void *a, const void *b);
#endif
