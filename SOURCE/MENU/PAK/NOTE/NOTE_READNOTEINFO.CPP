#include "../../../../sdk/include/LIBC.H"
#include "MENU/PAK/pak_note_search.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "RESMGR/resmgr_string_memory.H"
#include "COMMON/LONE/G_LANGUAGEINDEX.H"
#include "include_asm.h"
#include <ultra64.h>
#include "COMMON/ENTRYRECAT0V3.H"
#include "MENU/PAK_DIRECTORY_VIEWS.H"
#include "TYPES.H"
#include "COMMON/VECTOR4F.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "ENGINE/DEFS.H"
#include "NOTE/NOTE_READNOTEDATA.H"
#include "NOTE/NOTE_READNOTEINFO.H"
#include "NOTE/PAK_ALLOCATERENDERBUFFERS.H"

/* Writes a note to the Controller Pak on channel ch: refuses with -2 unless the pak is ready,
   takes the controller lock and, when the pak has no pending error, converts the extension and
   game name to pak font codes, allocates the note rounded up to whole 256-byte blocks through
   osPfsAllocateFile (osPfsAllocateFile), writes the data through osPfsReadWriteFile (Pfs_ReadWriteFile),
   deletes the note again if the write fails, refreshes the pak state through Note_UpdateStatus and
   returns 0 or -1. */





extern OSPfs g_controllerPakFileSystems[];

extern PakDirectory *g_controllerPakNoteLists;

extern u8 g_controllerPakFrontendState;

extern u8 g_controllerPakFilenameAlphabet[66];

extern void Control_ReadControllerStates(void);

extern void Control_ReleasePakLock(void);



extern s32 Pfs_ReadWriteFile(OSPfs* pfs, s32 file_no, u8 flag, int offset, int size_in_bytes, u8* data_buffer);

/* Inline copy of Note_DecodeNoteText: decodes the n pak font codes at src into dst as text (codes from
   0x42 up become '~', leading zero codes blanks), trims trailing blanks and terminates dst. */
static inline void Pak_DecodeNoteName(u8 *src, u8 *dst, s32 n) {
    s32 i;
    u8 *p;
    s32 started;

    for (i = n - 1, p = dst + i; i >= 0; i--) {
        *p-- = 0;
    }
    started = 0;
    for (i = 0; i < n; i++) {
        if (src[i] < 66) {
            if (src[i] == 0 && !started) {
                dst[i] = ' ';
            } else {
                dst[i] = g_controllerPakFilenameAlphabet[src[i]];
                started = 1;
            }
        } else {
            dst[i] = '~';
        }
    }
    for (i = n - 1; i >= 0; i--) {
        if (dst[i] != ' ' && dst[i] != 0) {
            break;
        }
        dst[i] = 0;
    }
    dst[n - 1] = 0;
}

/* Saves data as a Controller Pak note on channel ch and verifies it: refuses with -2 unless the pak
   is ready, then up to four times writes the note through Note_CreateAndWriteNote with the g_pakCompanyCodeFixed
   company code, reads it back into a temporary buffer through an inlined note read, and stops when
   the bytes compare equal or deletes the note through Note_DeleteNote and retries, returning the
   write result. */
#if defined(VERSION_EU) || defined(VERSION_EU_X)
extern u8 *g_pakCompanyCodes[], *g_pakCompanyCodes[];
#endif



extern void **Cache_AllocateResource(s32, s32, s32, char *);

extern void Cache_DrainAndCompactResources(s32);


extern int Cache_GetResourceActivityState(void);

extern void Cache_SetResourceActivityState(unsigned int);



extern s32 Note_CreateAndWriteNote(s32 ch, s32 size, void *data, u8 *game_name, s32 *file_no, u8 *ext_name,
                         u8 *company, u8 *code);

extern s32 Note_DeleteNote(s32 ch, s32 index);

static inline s32 Note_ReadFileIntoBuffer(s32 ch, s32 file_no, void *dst, s32 size) {
    s32 result;
    s32 blocks;
    void **handle;
    void *buf;

    blocks = (size + 0xFF) & ~0xFF;
    if (g_controllerPakChannelStates[ch] != 3) {
        return -2;
    }
    if (Cache_GetResourceActivityState() == 0) {
        Cache_SetResourceActivityState(1);
    }
    handle = Cache_AllocateResource(0, blocks, 35, g_pakReadScratchNoteName);
    buf = *handle;
    ((void (*)(s32))Control_AcquireControllerLock)(1);
    Control_ReadControllerStates();
    result = g_controllerPakChannelStatuses[ch];
    g_controllerPakFrontendState = 2;
    if (result == 0) {
        if ((result = Pfs_ReadWriteFile(&g_controllerPakFileSystems[ch], file_no, 0, 0, blocks, buf)) != 0) {
            result = -1;
        }
        if (result == 0) {
            Libc_CopyBytes(dst, buf, size);
        }
    }
    Control_ReleasePakLock();
    Cache_DrainAndCompactResources(0);
    if (handle != 0) {
        Cache_ReleaseResource(0, handle);
    }
    return result;
}

extern s32 Note_CreateAndWriteNote(s32 ch, s32 size, void *data, u8 *game_name, s32 *file_no, u8 *ext_name, u8 *company, u8 *code);

/* Reports note index of the Controller Pak on channel ch from the cached directory: refuses with -2
   unless the pak is ready, clears the exists flag for an empty slot, and otherwise returns its size
   in 256-byte blocks, its company and game codes as terminated byte strings, and its game name and
   extension decoded from pak font codes with trailing blanks trimmed. */
s32 Note_ReadNoteInfo(s32 ch, s32 index, s32 *exists, u8 *name, u8 *ext, s32 *size, u8 *company,
                  u8 *code) {
    if (g_controllerPakChannelStates[ch] != 3) {
        return -2;
    }
    if (g_controllerPakNoteLists[ch].notes[index].file_size == 0) {
        *exists = 0;
    } else {
        *exists = 1;
    *size = g_controllerPakNoteLists[ch].notes[index].file_size >> 8;
    Libc_CopyBytes(company, &g_controllerPakNoteLists[ch].notes[index].company_code, 2);
    Libc_CopyBytes(code, &g_controllerPakNoteLists[ch].notes[index].game_code, 4);
    Pak_DecodeNoteName(g_controllerPakNoteLists[ch].notes[index].game_name, name, 17);
    Pak_DecodeNoteName(g_controllerPakNoteLists[ch].notes[index].ext_name, ext, 4);
    code[4] = 0;
    company[2] = 0;
    }
    return 0;
}

s32 Note_DeleteNote(s32 ch, s32 index) {

    extern s32 Note_UpdateStatus(s32 ch);
    s32 result;

    if (g_controllerPakChannelStates[ch] != 3) {
        return -2;
    }
    ((void (*)(s32))Control_AcquireControllerLock)(1);
    Control_ReadControllerStates();
    result = g_controllerPakChannelStatuses[ch];
    g_controllerPakFrontendState = 2;
    if (result == 0) {
        result = osPfsDeleteFile(&g_controllerPakFileSystems[ch], g_controllerPakNoteLists[ch].notes[index].company_code,
                               g_controllerPakNoteLists[ch].notes[index].game_code,
                               g_controllerPakNoteLists[ch].notes[index].game_name,
                               g_controllerPakNoteLists[ch].notes[index].ext_name);
        if (result != 0) {
            result = -1;
        }
        Note_UpdateStatus(ch);
    }
    Control_ReleasePakLock();
    return result;
}

s32 Note_SaveNote(s32 ch, s32 size, void *data, u8 *name, u8 *ext, u8 *code) {
    s32 result;
    s32 file_no;
    void **handle;
    void *buf;
    s32 blocks;
    s32 tries;

    blocks = (size + 0xFF) & ~0xFF;
    if (g_controllerPakChannelStates[ch] != 3) {
        return -2;
    }
    handle = Cache_AllocateResource(0, blocks, 35, g_pakWriteScratchNoteName);
    buf = *handle;
    for (tries = 0; tries < 4; tries++) {
        result = Note_CreateAndWriteNote(ch, size, data, name, &file_no, ext, RW_LOCALIZED_TEXT(g_pakCompanyCodeFixed, g_pakCompanyCodes, g_pakCompanyCodes, g_languageIndex), code);
        if (result != 0) {
            break;
        }
        if (Note_ReadFileIntoBuffer(ch, file_no, buf, blocks) == 0 && Defs_CompareMemory(buf, data, size) == 0) {
            break;
        }
        if (Note_DeleteNote(ch, file_no) != 0) {
            break;
        }
    }
    Cache_DrainAndCompactResources(0);
    if (handle != 0) {
        Cache_ReleaseResource(0, handle);
    }
    return result;
}


/* Inline copy of Note_GetNoteGameName: points *gameName at note's encoded game name in the cached
   directory of channel's pak and returns 0, or returns -2 (leaving *gameName untouched) unless that
   pak is ready. */
static inline s32 Pak_PeekNoteGameName(s32 channel, s32 note, u8 **gameName) {
    if (g_controllerPakChannelStates[channel] != 3) {
        return -2;
    }
    *gameName = g_controllerPakNoteLists[channel].notes[note].game_name;
    return 0;
}

/* Searches the 16 notes of the Controller Pak on channel for one whose decoded game name equals name:
   stores its index in *noteIndex (when given) and returns 1, or returns 0 when none matches. */
s32 Note_FindNoteByName(void *name, s32 channel, s32 *noteIndex) {
    u8 decodedName[16];
    u8 *encodedName;
    s32 note;

    for (note = 0; note < 16; note++) {
        Pak_PeekNoteGameName(channel, note, &encodedName);
        Pak_DecodeNoteName(encodedName, decodedName, 16);
        if (XPlus_CompareStrings(decodedName, name) == 0) {
            if (noteIndex != NULL) {
                *noteIndex = note;
            }
            return 1;
        }
    }
    return 0;
}
