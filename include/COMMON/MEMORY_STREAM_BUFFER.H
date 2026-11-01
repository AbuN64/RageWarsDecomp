#ifndef COMMON_MEMORY_STREAM_BUFFER_H
#define COMMON_MEMORY_STREAM_BUFFER_H
#include "TYPES.H"

/* Memory stream buffer, byte cursor, size, open state, and ready flag. */


struct MemoryStreamBuffer;
typedef struct MemoryStreamBuffer MemoryStreamBuffer;


struct MemoryStreamBuffer {
    u8 *data;
    s32 cursor;
    s32 size;
    s32 opened;
    s32 ready;
};
extern MemoryStreamBuffer g_stdioResourceStream;


extern int g_stdioFormattedLength;



extern int g_stdioArgumentWriteCallback;


extern int g_stdioScratchCallback;



extern int g_stdioWriteCallback;




extern int g_stdioResourceOpenCount;
#endif
