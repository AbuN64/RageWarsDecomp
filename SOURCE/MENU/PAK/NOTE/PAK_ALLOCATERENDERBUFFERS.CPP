#include "include_asm.h"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/RECORDRECAT1C.H"
#include "OVLGAME/RENDER_BUFFER_RESOURCES.H"
#include "TYPES.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "OVLGAME/NOTE_ENCODENOTETEXT.H"
#include "UI/X_FILES/X_PLUS.H"
#include "ENGINE/SCENE_DRAWOPAQUEACTORS.H"
#include "NOTE/NOTE_READNOTEINFO.H"
#include "NOTE/PAK_ALLOCATERENDERBUFFERS.H"

/* Chooses a free extension letter for a new note on the Controller Pak on channel ch: refuses with
   -2 unless the pak is ready, queries each of the 16 notes through Note_ReadNoteInfo (failing with -1
   on error) and marks the letter of every existing note, then writes the first unused letter from
   'A' as the extension, returning 0, or -1 when all 16 letters are taken. */





s32 Note_FindFreeNoteExtension(s32 ch, u8 *ext) {
    char companyCode[8];
    char gameCode[8];
    char gameName[16];
    s32 exists;
    s32 size;
    s32 used;
    s32 i;

    used = 0;
    if (g_controllerPakChannelStates[ch] != 3) {
        return -2;
    }
    for (i = 0; i < 16; i++) {
        if (Note_ReadNoteInfo(ch, i, &exists, gameName, ext, &size, companyCode, gameCode) != 0) {
            return -1;
        }
        if (exists != 0) {
            used |= 1 << (ext[0] - 'A');
        }
    }
    ext[0] = 'A';
    ext[1] = 0;
    ext[2] = 0;
    ext[3] = 0;
    for (i = 0; i < 16 && (used & (1 << i) & 0xFFFF); i++) {
        ext[0]++;
    }
    if (i >= 16) {
        return -1;
    }
    return 0;
}

/* Returns whether entry i of g_controllerPakChannelStatuses is -4 when entry i of the state table g_controllerPakChannelStates is 3,
   otherwise zero. */



s32 Note_NeedsIdRepair(s32 index) {
    if (g_controllerPakChannelStates[index] != 3) {
        return 0;
    }
    return g_controllerPakChannelStatuses[index] == -4;
}

/* Marks the given controller port's 0x70-byte pak record in g_controllerPakChannelRecords present when the port's g_controllerReadStatusBytes status byte is clear and osMotorInit initialises the pak block at offset 8 of the record through g_controllerSiMessageQueue without error, clearing the mark otherwise, and returns the mark.
   Adapted from Scene_GetModelRecordByIndexPointer with the record reached by port index, the status byte guard and the initialisation result stored as a byte flag changed. */



extern char g_controllerSiMessageQueue[];
extern PakRecord g_controllerPakChannelRecords[];


s32 Note_ProbeAccessoryPresence(s32 channel) {
    PakRecord *record = &g_controllerPakChannelRecords[channel];
    s32 result;

    if (g_controllerReadStatusBytes[channel * 4] == 0) {
        record->present = osMotorInit(g_controllerSiMessageQueue, record->pak, channel) == 0;
        result = record->present;
    } else {
        record->present = 0;
        result = 0;
    }
    return result;
}

extern u8 g_controllerPakFilenameAlphabet[];

/* Converts a controller-pak filename through its character table, blanking leading nulls, then trims trailing spaces. */
void Note_DecodeNoteText(u8 *encodedText, u8 *noteText, s32 characterCount) {
    s32 i;
    s32 started;

    for (i = 0; i < characterCount; i++) {
        noteText[i] = 0;
    }

    started = 0;
    for (i = started; i < characterCount; i++, encodedText++) {
        if (*encodedText < 66) {
            if (*encodedText == 0 && !started) {
                noteText[i] = ' ';
            } else {
                noteText[i] = g_controllerPakFilenameAlphabet[*encodedText];
                started = 1;
            }
        } else {
            noteText[i] = '~';
        }
    }

    for (i = characterCount - 1; i >= 0; i--) {
        if (noteText[i] != ' ' && noteText[i] != 0) {
            break;
        }
        noteText[i] = 0;
    }
    noteText[characterCount - 1] = 0;
}

extern int XPlus_UppercaseCharacter(int);
extern u8 g_controllerPakFilenameAlphabet[66];

/* Maps input bytes through a lookup table and stores results. */
void Note_EncodeNoteText(u8 *text, s8 *encodedText, s32 characterCount) {
    s32 i;
    s8 *encodedCursor;
    s32 j;
    u8 *textCursor;
    int alphabetSize;

    i = 0;
    if (characterCount > 0) {
        alphabetSize = 66;
        encodedCursor = encodedText;
        textCursor = text;
        do {
            *textCursor = XPlus_UppercaseCharacter(*textCursor);
            for (j = 0; j < 66; j += 1) {
                if (*textCursor == g_controllerPakFilenameAlphabet[j]) {
                    *encodedCursor = (s8)j;
                    break;
                }
            }
            if (j == alphabetSize) {
                *encodedCursor = 0;
            }
            encodedCursor += 1;
            i += 1;
            textCursor += 1;
        } while (i < characterCount);
    }
}

/* Returns one when a tilde appears among the first n + 1 bytes of a string, otherwise zero. */
s32 Note_ContainsInvalidNameByte(u8 *text, s32 count) {
    do {
        if (*text++ == '~') {
            return 1;
        }
    } while (--count != -1);
    return 0;
}

/* Rounds a byte count up to whole 256-byte units; PAKInterface_CheckRecordsNoteCapacity passes it the 0x648-byte size
   that PAKInterface_GetRecordsNoteSize_PakAllocaterenderbuffers returns. */
u32 Note_BytesToPakPages(u32 bytes) {
    return (bytes + 0xFF) >> 8;
}

/* Computes the CRC-32 with polynomial 0xEDB88320 of byteCount bytes at data, continuing from the running value initialCrc, from a 256-entry table built on the stack. Adapted from XPlus_UpdateCrc32. */

u32 Note_Crc32(u8 *data, u32 byteCount, u32 initialCrc) {
    u32 table[256];
    u32 i;
    u32 j;
    u32 value;
    u32 shifted;
    u8 *end;

    for (i = 0; i < 256; i++) {
        value = i;
        for (j = 0; j < 8; j++) {
            shifted = value >> 1;
            if (value & 1) {
                shifted ^= 0xEDB88320U;
            }
            value = shifted;
        }
        table[i] = value;
    }

    end = data + byteCount;
    initialCrc = ~initialCrc;
    while (data < end) {
        initialCrc = table[(initialCrc ^ *data++) & 0xFF] ^ ((initialCrc >> 8) & 0xFFFFFF);
    }
    return ~initialCrc;
}

/* Returns the word held in g_controllerPakProbeActive. */

s32 Note_HasScratchBuffer(void) {
    return g_controllerPakProbeActive;
}

#include <ultra64.h>
#include "COMMON/EFFECTRENDER.H"
#include "COMMON/CACHE_ALLOCATERESOURCE.H"
#include "COMMON/SESSIONHANDLERROW.H"
#include "COMMON/TRIPLE.H"
#include "COMMON/DISPLAY.H"
#include "COMMON/SHAREDPLAYER.H"
typedef struct CacheResourceBlockView Handle;
extern void Cache_ReleaseResource(void *cacheContext, void *resource);
extern u32 Defs_GetMemorySize(void);
extern Handle *Cache_AllocateResourceAt(void *heap, u32 address, u32 size, char *name);
extern const char s_bufferText[9];  /* "Z-Buffer" */
extern char s_displayBufferText[15];    /* "Display Buffer" */
extern char s_colorFramesAndZBufferText[31];    /* "color frame buffers + z buffer" */
extern char s_displayListsText[14];    /* "display lists" */
extern const char s_fifoText[5];     /* "fifo" */
extern char s_audioHeapText[11];    /* "audio heap" */
/* Rebuilds the render buffers held by the record: releases every handle it holds and clears it, then
   claims the frame buffers at the top of RDRAM (three 0x54600-byte buffers below the 1 MB z-buffer when
   the expansion pak gives 6 MB or more; otherwise the count in g_renderFrameBufferCount plus one 0x1ECC0-byte buffer,
   the extra one holding the z-buffer, below 4 MB), clears them, allocates the display lists, the RSP fifo
   and the audio heap, publishes their addresses in the render globals and marks the record ready. */
int Note_AllocateRenderBuffers(struct RenderBufferResources *record) {
    u32 megabyte = 0x100000;
    u32 bufferBytes;
    u32 memoryEnd;
    Handle *zBuffer;
    Handle *frameBuffers;
    Handle *buffers;
    u32 i;
    s32 j;
    s32 k;

    if (record->displayLists != NULL) {
        Cache_ReleaseResource(NULL, record->displayLists);
    }
    if (record->fifo != NULL) {
        Cache_ReleaseResource(NULL, record->fifo);
    }
    if (record->zBuffer != NULL) {
        Cache_ReleaseResource(NULL, record->zBuffer);
    }
    if (record->audioHeap != NULL) {
        Cache_ReleaseResource(NULL, record->audioHeap);
    }
    for (j = 0; j < 3; j++) {
        if (record->frameBuffers[j] != NULL) {
            Cache_ReleaseResource(NULL, record->frameBuffers[j]);
        }
    }
    record->ready = 0;
    record->displayLists = NULL;
    record->fifo = NULL;
    record->zBuffer = NULL;
    record->audioHeap = NULL;
    for (k = 2; k >= 0; k--) {
        record->frameBuffers[k] = NULL;
    }

    if (Defs_GetMemorySize() >= 6 * megabyte) {
        bufferBytes = 345600;
        memoryEnd = Defs_GetMemorySize() | 0x80000000;
        g_renderFrameBufferCount = 3;
        zBuffer = Cache_AllocateResourceAt(NULL, memoryEnd - megabyte, 345600, s_bufferText);
        frameBuffers = Cache_AllocateResourceAt(NULL, memoryEnd - 2 * megabyte, g_renderFrameBufferCount * bufferBytes,
                                                s_displayBufferText);
        XPlus_FillMemory(frameBuffers->data, 0, 1036800);
        XPlus_FillMemory(zBuffer->data, 0, 345600);
        record->zBuffer = zBuffer;
        record->frameBuffers[0] = frameBuffers;
        g_depthImageBuffer = record->zBuffer->data;
        for (i = 0; i < g_renderFrameBufferCount; i++) {
            g_colorImageBuffers[i] = (u8 *)frameBuffers->data + i * bufferBytes;
        }
    } else {
        bufferBytes = 126144;
        memoryEnd = 0x80400000;
        buffers = Cache_AllocateResourceAt(NULL, memoryEnd - (g_renderFrameBufferCount + 1) * bufferBytes,
                                           (g_renderFrameBufferCount + 1) * bufferBytes, s_colorFramesAndZBufferText);
        record->frameBuffers[0] = buffers;
        for (i = 0; i < g_renderFrameBufferCount; i++) {
            g_colorImageBuffers[i] = (u8 *)buffers->data + bufferBytes * i;
        }
        g_depthImageBuffer = (u8 *)buffers->data + bufferBytes * i;
    }
    for (i = 0; i < g_renderFrameBufferCount; i++) {
        XPlus_FillMemory(g_colorImageBuffers[i], 0, bufferBytes);
    }
    XPlus_FillMemory(g_depthImageBuffer, 0, bufferBytes);

    record->displayLists = Cache_AllocateResource(0, (g_displayListCapacityUsRev1 + g_secondaryDisplayListCapacity) * 2 * sizeof(Gfx), 35, s_displayListsText);
    record->fifo = Cache_AllocateResource(0, 0x8000, 35, s_fifoText);
    record->audioHeap = Cache_AllocateResource(0, 0x22000, 35, s_audioHeapText);
    g_graphicsMicrocodeTextSize = 0x8000;
    g_audioContextHeapBytes = 0x22000;
    g_displayListBufferZero = record->displayLists->data;
    g_secondaryDisplayListBufferZero = g_displayListBufferZero + g_displayListCapacityUsRev1;
    g_displayListBufferOne = g_secondaryDisplayListBufferZero + g_secondaryDisplayListCapacity;
    g_secondaryDisplayListBufferOne = g_displayListBufferOne + g_displayListCapacityUsRev1;
    g_graphicsMicrocodeDataSize = record->fifo->data;
    g_audioContextHeapBuffer = (u8 *)record->audioHeap->data;
    for (i = 0; i < g_renderFrameBufferCount; i++) {
    }
    record->ready = 1;
    return 1;
}
