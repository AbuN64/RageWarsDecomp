#include "COMMON/MEMORY_STREAM_BUFFER.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "stdarg.h"
#include "TYPES.H"
#include "MENU/GFX/GFX_FORMATARGUMENTLIST.H"
#include "include_asm.h"
#include "UI/X_FILES/X_STDIO.H"
#include "COMMON/MESSAGESEMAPHORE.H"
#include "COMMON/CARTRIDGEREADWORKER.H"
#include "COMMON/MANAGER.H"
#include "RESMGR/resmgr_stream_io.H"
#include "RESMGR/resmgr_stream_callbacks.H"
#include "SCENE/CACHE_FREEMEMORY.H"
#include "RESMGR/resmgr_string_memory.H"
#include "COMMON/STATEPAIR.H"

/* 802A0888_6.CPP */
#if defined(VERSION_EU_X) || defined(VERSION_US_REV1) || defined(VERSION_US)

u8 *XStdio_FormatScratchBuffer(u8 *fmt0, ...) {
    va_list args;
    va_start(args, fmt0);
    g_stdioFormattedLength = Gfx_FormatArgumentList((u8 *)&g_stdioFormatBuffer, fmt0, args);
    va_end(args);
    return (u8 *)&g_stdioFormatBuffer;
}
#endif

/* 802A0888_7.CPP */
#if defined(VERSION_DE) || defined(VERSION_EU)
#include "stdarg.h"

int *XStdio_FormatGermanScratchBuffer(int format, ...) {
    va_list args;
    va_start(args, format);
    g_stdioFormattedLength = Gfx_FormatArgumentList(&g_stdioFormatBuffer, format, (int)args);
    va_end(args);
    return &g_stdioFormatBuffer;
}
#endif

s32 XStdio_PrintText(s32 fmt0, ...) {
    char *args;

    args = __builtin_next_arg(fmt0);
    g_stdioFormattedLength = Gfx_FormatArgumentList(&g_stdioFormatBuffer, fmt0, (s32) args);
    if (g_stdioScratchCallback != 0) {
        ((s32 (*)(s32 *)) g_stdioScratchCallback)(&g_stdioFormatBuffer);
    }
    return g_stdioFormattedLength;
}

s32 XStdio_PrintTextWithArguments(s32 stream, s32 writeContext, s32 fmt0, ...) {
    char *args;

    args = __builtin_next_arg(fmt0);
    g_stdioFormattedLength = Gfx_FormatArgumentList(&g_stdioFormatBuffer, fmt0, (s32) args);
    ((s32 (*)(s32 *, s32, s32)) g_stdioArgumentWriteCallback)(&g_stdioFormatBuffer, stream, writeContext);
    return g_stdioFormattedLength;
}

/* resmgr_stream_io.CPP */
/* Formats its arguments into the shared buffer g_stdioFormatBuffer and writes the text to the stream through XStdio_WriteStreamNoop in runs, emitting the one-byte k_stdioCarriageReturn before every newline, returning the number of bytes written. */



/* Initializes and dispatches the resource on the first guarded call. */

extern struct CartridgeReadWorker g_cartridgeReadWorker;


extern void Cartridge_ReadChunksAndWait(struct CartridgeReadWorker *worker, u32 source, s32 bytes, void *destination);

/* Callable open entry in the low-address resource callback table. */


/* Callable seek entry in the low-address resource callback table. */

inline static s32 *guard_address(void) {
    return &g_stdioResourceOpenCount;
}

inline static s32 increment_guard(s32 *counter) {
    s32 current = *counter;
    s32 previous = current;
    current++;
    *counter = current;
    return previous;
}

static inline s32 read_resource_word(s32 *word) {
    return *word;
}

static inline void write_resource_word(s32 *word, s32 value) {
    *word = value;
}

static inline void write_resource_buffer(u8 **buffer, void *allocation) {
    *buffer = allocation;
}

static inline void clear_resource_state(void) {
    g_stdioResourceStream.data = 0;
    g_stdioResourceStream.opened = 0;
    g_stdioResourceStream.ready = 0;
}

typedef void (*FuncPtr)(void);

extern ResourceOpenCallback g_stdioOpenCallback;

extern FuncPtr g_stdioCloseCallback;

extern ResourceReadCallback g_stdioReadCallback;

/** Pass the variadic tail address to the formatter and retain its result. */
s32 XStdio_FormatBuffer(void *goal, s32 fmt0, ...) {
    s32 result;
    char *args;

    args = __builtin_next_arg(fmt0);
    result = Gfx_FormatArgumentList(goal, fmt0, (s32)args);
    g_stdioFormattedLength = result;
    return result;
}

s32 XStdio_PrintStream(void *stream, const char *format, ...) {
    unsigned char *run;
    unsigned char *p;
    s32 length;
    s32 total;

    Gfx_FormatArgumentList((u8 *)&g_stdioFormatBuffer, format, __builtin_next_arg(format));
    run = (u8 *)&g_stdioFormatBuffer;
    p = run;
    length = 0;
    total = 0;
    for (; *p != 0; p++, length++) {
        if (*p == '\n') {
            if (length > 0) {
                XStdio_WriteStreamNoop(run, 1, length, stream);
                total += length;
                length = 0;
                run = p;
            }
            XStdio_WriteStreamNoop(&k_stdioCarriageReturn, 1, 1, stream);
            total++;
        }
    }
    if (length > 0) {
        XStdio_WriteStreamNoop(run, 1, length, stream);
        total += length;
    }
    return total;
}

void XStdio_InitializeStreams(void) {
    void *v0;
    s32 one;

    if (increment_guard(guard_address()) != 0) {
        return;
    }
    g_stdioResourceReadyCookie = 0x12345678;
    one = 1;
    if (read_resource_word(&g_stdioResourceStream.ready) != one) {
#if defined(VERSION_DE)
        g_stdioResourceStream.size = 572161;
#elif defined(VERSION_EU_X)
        g_stdioResourceStream.size = 590725;
#else
        g_stdioResourceStream.size = 569925;
#endif
        v0 = Cache_AllocateMemory(read_resource_word(&g_stdioResourceStream.size));
        write_resource_buffer(&g_stdioResourceStream.data, v0);
        Cartridge_ReadChunksAndWait(&g_cartridgeReadWorker, 0x200000, read_resource_word(&g_stdioResourceStream.size), v0);
        write_resource_word(&g_stdioResourceStream.opened,0);
        g_stdioResourceStream.ready = one;
    }
    XStdio_SetStreamCallbacks((ResourceOpenCallback)&g_stdioResourceOpenRomEntry, (s32) &g_stdioResourceCloseRomEntry, (ResourceReadCallback)&g_stdioResourceReadRomEntry, (s32) &g_stdioResourceWriteRomEntry, (ResourceSeekCallback)&g_stdioResourceSeekRomEntry, (s32) &g_stdioResourceTellRomEntry, (s32) &g_stdioResourceEndRomEntry);
}

void XStdio_ShutdownStreams(void) {
    g_stdioResourceOpenCount--;
    if (g_stdioResourceStream.data != 0) {
        Cache_FreeMemory(g_stdioResourceStream.data);
    }
    clear_resource_state();
}

/* Forward both open arguments and return the callback's stream handle. */
s32 XStdio_OpenStream(const void *name, const void *mode) {
    return g_stdioOpenCallback(name, mode);
}

void XStdio_CloseStream(void) {
    g_stdioCloseCallback();
}

s32 XStdio_ReadStream(void *destination, s32 elementSize, s32 count, s32 handle) {
    s32 totalBytes;
    s32 result;

    totalBytes = elementSize * count;
    if (totalBytes == 0) {
        return 0;
    }
    result = g_stdioReadCallback(handle, destination, totalBytes);
    return result / elementSize;
}

/* resmgr_stream_callbacks.CPP */


extern ResourceSeekCallback g_stdioSeekCallback;
extern FuncPtr g_stdioTellCallback;
extern FuncPtr g_stdioEndCallback;


/* Allocates the resource once and marks its five-word state ready. */


/** Return the constant false result used by callers at VRAM 0x802A1F50. */
s32 XStdio_WriteStreamNoop(const unsigned char *data, s32 size, s32 count, void *stream) {
    return 0;
}

/** Return the zero status used by callers. */
int XStdio_ReadUnavailable(void) {
    return 0;
}

/* Forward every seek argument and return the configured callback status. */
s32 XStdio_SeekStream(s32 handle, s32 offset, s32 origin) {
    return g_stdioSeekCallback(handle, offset, origin);
}

void XStdio_QueryStreamPosition(void) {
    g_stdioTellCallback();
}

void XStdio_QueryStreamEnd(void) {
    extern FuncPtr g_stdioEndCallback;
    g_stdioEndCallback();
}

s32 XStdio_ReadCharacter(s32 stream) {
    u8 readByte;
    s32 result;

    if (g_stdioReadCallback(stream, &readByte, 1) != 0) {
        result = readByte;
    } else {
        result = -1;
    }
    return result;
}

int XStdio_WriteUnavailable(void) {
    return 0;
}

s32 *XStdio_FormatScratchArgumentList(s32 fmt0, s32 argumentList) {
    g_stdioFormattedLength = Gfx_FormatArgumentList(&g_stdioFormatBuffer, fmt0, argumentList);
    return &g_stdioFormatBuffer;
}

void XStdio_SetStreamCallbacks(ResourceOpenCallback openCallback, s32 closeCallback, ResourceReadCallback readCallback, s32 writeCallback, ResourceSeekCallback seekCallback, FuncPtr tellCallback, FuncPtr endCallback) {
    g_stdioOpenCallback = openCallback;
    g_stdioCloseCallback = (FuncPtr)closeCallback;
    g_stdioReadCallback = readCallback;
    g_stdioWriteCallback = writeCallback;
    g_stdioSeekCallback = seekCallback;
    g_stdioTellCallback = tellCallback;
    g_stdioEndCallback = endCallback;
}

void XStdio_LoadMemoryStream(void) {
    void *buffer;
    MemoryStreamBuffer *stream;
    if (g_stdioResourceStream.ready != 1) {
#if defined(VERSION_DE)
        g_stdioResourceStream.size = 572161;
        buffer = Cache_AllocateMemory(572161);
#elif defined(VERSION_EU) || defined(VERSION_US) || defined(VERSION_US_REV1)
        g_stdioResourceStream.size = 569925;
        buffer = Cache_AllocateMemory(569925);
#elif defined(VERSION_EU_X)
        g_stdioResourceStream.size = 590725;
        buffer = Cache_AllocateMemory(590725);
#endif
        g_stdioResourceStream.data = buffer;
        Cartridge_ReadChunksAndWait(&g_cartridgeReadWorker, 0x200000, g_stdioResourceStream.size, buffer);
        stream = &g_stdioResourceStream;
        stream->opened = 0;
        g_stdioResourceStream.ready = 1;
    }
}

void XStdio_FreeMemoryStream(void) {
    if (g_stdioResourceStream.data != 0) {
        Cache_FreeMemory(g_stdioResourceStream.data);
    }
    g_stdioResourceStream.data = 0;
    g_stdioResourceStream.opened = 0;
    g_stdioResourceStream.ready = 0;
}

/* Reset the memory stream and return its single valid handle. */
s32 XStdio_OpenMemoryStream(const void *name, const void *mode) {
    const u8 *modeCursor = mode;
    while (*modeCursor != 0) {
        modeCursor++;
    }
    modeCursor++;
    g_stdioResourceStream.cursor = 0;
    g_stdioResourceStream.opened = 1;
    return 1;
}

/** Clear the global word at VRAM 0x800D2BBC. */

void XStdio_CloseMemoryStream(void) {
    g_stdioResourceStream.opened = 0;
}

s32 XStdio_ReadMemoryStream(s32 handle, void *destination, s32 bytes) {
    MemoryStreamBuffer *stream = &g_stdioResourceStream;
    XPlus_CopyBytes(destination, stream->data + stream->cursor, bytes);
    stream->cursor = stream->cursor + bytes;
    return 1;
}

/** Return the false result used by callers at VRAM 0x802A21EC. */
int XStdio_WriteMemoryStreamNoop(void) {
    return 0;
}

s32 XStdio_SeekMemoryStream(s32 handle, s32 offset, s32 origin) {

    if (origin == 0) {
        g_stdioResourceStream.cursor = 0;
    }
    g_stdioResourceStream.cursor = g_stdioResourceStream.cursor + offset;
    return 0;
}

/** Return the first global state word. */
unsigned int XStdio_TellMemoryStream(void) {
    return g_stdioResourceStream.cursor;
}

/* resmgr_stream_status.CPP */
int XStdio_IsMemoryStreamAtEnd(void) {
    return g_stdioResourceStream.cursor == g_stdioResourceStream.size;
}

/** Store two values in the paired global words. */
void XStdio_SetTextOutputCallbacks(int first, int second) {
    g_stdioScratchCallback = first;
    g_stdioArgumentWriteCallback = second;
}

