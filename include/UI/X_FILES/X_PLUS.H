#ifndef UI_X_FILES_X_PLUS_H
#define UI_X_FILES_X_PLUS_H
#include "COMMON/MESSAGESEMAPHORE.H"
extern void XPlus_PartitionSortRange(char *base, char *max);
extern void XPlus_SortArray(char *base, s32 n, s32 size, s32 (*compare)(char *a, char *b));
extern void XPlus_SplitPath(u8 *path, u8 *drive, u8 *dir, u8 *name, u8 *ext);
extern void * XPlus_FillMemory(void *destination, int fillValue, u32 byteCount);

extern char *XPlus_MoveMemory(char *dst, const char *src, s32 n);
extern f64 XPlus_ParseDecimalDouble(u8 *);
extern void XPlus_SeedRandomGenerator(int seed);
extern u8 *XPlus_CopyStringBounded(u8 *destination, u8 *source, s32 count);
extern u8 *XPlus_AppendStringBounded(u8 *destination, u8 *source, s32 count);
extern s32 XPlus_CompareStrings(const void *leftString, const void *rightString);
extern s32 XPlus_CompareStringsBounded(u8 *a, u8 *b, s32 count);
extern s32 XPlus_CompareStringsIgnoreCase(u8 *a, u8 *b);
extern u8 *XPlus_FindLastCharacter(u8 *s, int c);
extern u8 *XPlus_LowercaseString(u8 *string);
extern int XPlus_LowercaseCharacter(int c);
extern s32 XPlus_ParseDecimalInteger(u8 *s);
extern void XPlus_FormatDecimalInteger(s32 n, char *s);
extern void *XPlus_CopyBytes(void *destination, const void *source, s32 bytes);
extern void *XPlus_FillBytes(void *destination, int value, u32 count);
extern u8 *XPlus_FindByte(u8 *buffer, s32 value, s32 length);
extern s32 XPlus_CompareMemory(u8 *a, u8 *b, s32 count);
extern u32 XPlus_UpdateCrc32(u8 *data, u32 length, u32 crc);
extern void XPlus_BuildPath(u8 *path, u8 *drive, u8 *directory, u8 *name, u8 *extensionArg);
extern void XPlus_InitializeSemaphore(void *messageSemaphore);
extern void XPlus_AcquireSemaphore(s32);
extern void XPlus_ReleaseSemaphore(s32 *);
#endif
