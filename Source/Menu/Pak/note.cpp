#include "Menu/track.h"
#include <PR/os_motor.h>
#include "../../../sdk/include/LIBC.H"
#include "Common/note_state.h"
#include "Common/Lone/controller_si_message_queue.h"
#include "Menu/pak_directory_views.h"
#include "types.h"
#include "Common/vector4f.h"
#include "Common/runtime_declarations.h"
#include "Common/pakqueuestate.h"
#include "Common/pak_profile_load.h"
#include "Menu/Pak/note_refreshnotes.h"
#include <platform_sdk.h>
#include "PR/os_pfs.h"
#include "Common/cache_allocateresource.h"
#include "Menu/note_createandwritenote.h"
#include "Menu/g_controllerpakfilenamealphabet.h"
#include "Ui/x_plus.h"
#include "Menu/Pak/Note/note_createandwritenote_symbols.h"
#include "include_asm.h"
#include "Data/rest_source_records.h"
#include "Menu/Pak/pak_note_search.h"
#include "Resmgr/resmgr_string_memory.h"
#include "Common/Lone/g_languageindex.h"
#include "Engine/defs.h"
#include "Note/note_readnotedata.h"
#include "Note/note_readnoteinfo.h"
#include "Note/pak_allocaterenderbuffers.h"
#include "Common/resourcelockstate.h"
#include "Common/globals.h"
#include "Common/shared_menureply.h"
#include "Menu/note_readnoteinfo.h"
#include "Menu/Pak/Note/note_readnoteinfo_symbols.h"
#include "Ui/X_files/x_plus.h"
#include "Common/cache_releaseresource.h"
#include "Menu/Pak/Note/pak_probestatus_symbols.h"
#include "Menu/Pak/note_getnotepagecount.h"
#include "Menu/pak_allocaterenderbuffers.h"
#include "Menu/Pak/Note/note_readnotedata_symbols.h"
#include "Ovlgame/render_buffer_resources.h"
#include "Ovlgame/note_encodenotetext.h"
#include "Engine/scene_drawopaqueactors.h"
#include "Engine/cache_allocateresourceat.h"
#include "Menu/Pak/Note/pak_allocaterenderbuffers_symbols.h"
#include "Common/effectrender.h"
#include "Common/sessionhandlerrow.h"
#include "Common/triple.h"
#include "Common/display.h"
#include "Common/sharedplayer.h"
#include "Ovlgame/note_releaserenderbuffers.h"

/* Refreshes the cached directory of the Controller Pak on channel ch: when the directory buffer
   exists it reads the state of each of the 16 notes through osPfsFileState (osPfsFileState),
   retrying a failure once and clearing the cached note when it does not exist (5), then reads the
   free space through osPfsFreeBlocks into the buffer on success and returns that result. */
static inline void *pak27_noteCreateandwritenote(s32 ch) {return &g_controllerPakFileSystems[ch];}


static inline void Note_EncodeUppercaseFilename_noteCreateandwritenote(u8 *dst, u8 *src, s32 n) {
    s32 i;
    s32 j;

    for (i = 0; i < n; i++) {
        src[i] = XPlus_UppercaseCharacter(src[i]);
        for (j = 0; j < 66; j++) {
            if (src[i] == g_controllerPakFilenameAlphabet[j]) {
                dst[i] = j;
                break;
            }
        }
        if (j == 66) {
            dst[i] = 0;
        }
    }
}

s32 Note_RefreshNotes(s32 ch) {
    s32 i;
    s32 result;
    s32 free;

    if (g_controllerPakNoteLists != 0) {
        for (i = 0; i < 16; i++) {
            result = osPfsFileState(&g_controllerPakFileSystems[ch], i, &g_controllerPakNoteLists[ch].notes[i]);
            if (result != 0 && result != 5) {
                result = osPfsFileState(&g_controllerPakFileSystems[ch], i, &g_controllerPakNoteLists[ch].notes[i]);
            }
            if (result == 5) {
                g_controllerPakNoteLists[ch].notes[i].file_size = 0;
                g_controllerPakNoteLists[ch].notes[i].game_code = 0;
                g_controllerPakNoteLists[ch].notes[i].company_code = 0;
                g_controllerPakNoteLists[ch].notes[i].ext_name[0] = 0;
                g_controllerPakNoteLists[ch].notes[i].game_name[0] = 0;
            }
        }
    }
    result = osPfsFreeBlocks(&g_controllerPakFileSystems[ch], &free);
    if (result == 0) {
        g_controllerPakNoteLists[ch].free = free;
    }
    return result;
}

s32 Note_UpdateStatus(s32 ch) {
    s32 tries;
    s32 result;
    void *pfs;
    OSPfs *base;
    if(g_controllerReadStatusBytes[ch*4] != 0) {
        g_controllerPakChannelStatuses[ch]=-2;
        return 0;
    }
    tries=0;
    do {
        pfs=pak27_noteCreateandwritenote(ch);
        result=osPfsInitPak(g_controllerSiMessageQueue,pfs,ch);
        switch(result) {
        case 0: case 2:
            g_controllerPakChannelStatuses[ch]=-5;
            break;
        case 1:
            g_controllerPakChannelStatuses[ch]=-2;
            break;
        case 4: case 11:
            g_controllerPakChannelStatuses[ch]=-3;
            break;
        case 10:
            g_controllerPakChannelStatuses[ch]=-4;
            break;
        }
        if(g_controllerPakChannelStatuses[ch]==-5) {
            goto refresh_ready_notes;
        }
        if(g_controllerPakChannelStatuses[ch]==-2) break;
        tries++;
    } while(tries<4);
    goto status_result;
refresh_ready_notes:
    {
        g_controllerPakChannelStates[ch]=3;
        if(Note_RefreshNotes(ch)!=0) g_controllerPakChannelStatuses[ch]=-4;
        else g_controllerPakChannelStatuses[ch]=0;
    }
status_result:
    return g_controllerPakChannelStatuses[ch]==0 || g_controllerPakChannelStatuses[ch]==-4;
}

void Note_ProbeAllChannels(void) {
    s32 channel;
    s32 present;
    PakRecord *record;
    Control_AcquireControllerLock(1);
    Control_ReadControllerStates();
    g_controllerPakFrontendState = 2;
    for (channel = 0; channel < 4; channel++) {
        record = &g_controllerPakChannelRecords[channel];
        if (g_controllerReadStatusBytes[channel * 4] != 0) {
            present = 0;
            record->present = 0;
        } else {
            record->present = osMotorInit(g_controllerSiMessageQueue, record->pak, channel) == 0;
            present = record->present;
        }
        if (present) g_controllerPakChannelStates[channel] = 2;
        else if (Note_UpdateStatus(channel) != 0) g_controllerPakChannelStates[channel] = 3;
        else g_controllerPakChannelStates[channel] = 1;
    }
    Control_ReleasePakLock();
}


s32 Note_CreateAndWriteNote(s32 ch, s32 size, void *data, u8 *game_name, s32 *file_no, u8 *ext_name,
                  u8 *company, u8 *code) {
    s32 result;
    u8 name[16];
    u8 ext[4];
    u16 company_code;
    u32 game_code;
    OSPfs *pfs;
    s32 offset;

    if (g_controllerPakChannelStates[ch] != 3) {
        return -2;
    }
    ((void (*)(s32))Control_AcquireControllerLock)(1);
    Control_ReadControllerStates();
    result = g_controllerPakChannelStatuses[ch];
    g_controllerPakFrontendState = 2;
    if (result == 0) {
        Note_EncodeUppercaseFilename_noteCreateandwritenote(ext, ext_name, 4);
        size = (size + 0xFF) & ~0xFF;
        Libc_CopyBytes(name, game_name, 16);
        Note_EncodeUppercaseFilename_noteCreateandwritenote(name, game_name, 16);
        pfs = &g_controllerPakFileSystems[ch];
        company_code = (company[0] << 8) | company[1];
        game_code = (code[0] << 24) | (code[1] << 16) | (code[2] << 8) | code[3];
        result = osPfsAllocateFile(pfs, company_code, game_code, name, ext, size, file_no);
        if (result != 0) {
            result = -1;
        }
        offset = 0;
        if (result == 0) {
            result = Pfs_ReadWriteFile(pfs, *file_no, 1, offset, size, data);
            if (result != 0) {
                osPfsDeleteFile(pfs, company_code, game_code, name, ext);
                result = -1;
            }
        }
        Note_UpdateStatus(ch);
    }
    Control_ReleasePakLock();
    return result;
}

const char g_pakPakStateNoteName[16] = "Mempak pakstate";

const char g_pakReadScratchNoteName[22] = "Mempak read temp data";

/* The string occupies 23 bytes. Keep its following retained byte in the
 * same object's storage: us 800DB9AF=53, eu-x 800E853F=7c,
 * de 800DCCFF=70, us-rev1 800E0D2F=6c. These are not string characters. */
#if defined(VERSION_EU)
const char s_mempakWriteTempDataText[23] = "Mempak write temp data\000";
#endif
#if defined(VERSION_US)
const char s_mempakWriteTempDataText[24] = "Mempak write temp data\000S";
#endif
#if defined(VERSION_EU_X)
const char s_mempakWriteTempDataText[24] = "Mempak write temp data\000|";
#endif
#if defined(VERSION_DE)
const char s_mempakWriteTempDataText[24] = "Mempak write temp data\000p";
#endif
#if defined(VERSION_US_REV1)
const char g_pakWriteScratchNoteName[24] = "Mempak write temp data\000l";
#endif

const char s_bufferText[9] = "Z-Buffer";

const char g_displayBufferText[15] = "Display Buffer";

const char s_colorAndDepthBuffersText[31] = "color frame buffers + z buffer";

const char g_displayListsText[14] = "display lists";

const char s_fifoText[5] = "fifo";

/* Eleven-byte text and the same object's retained final byte, when present:
 * eu-x 800E859F=38, de 800DCD5F=63, us-rev1 800E0D8F=40. */
#if defined(VERSION_EU_X)
const char g_audioHeapText[12] = "audio heap\0008";
#elif defined(VERSION_DE)
const char g_audioHeapText[12] = "audio heap\000c";
#elif defined(VERSION_US_REV1)
const char g_audioHeapText[12] = "audio heap\000@";
#else
const char g_audioHeapText[11] = "audio heap";
#endif

s32 g_controllerPakFilenameLeadingZeroWords[3] = {
    0, 0, 0,
};
u8 g_controllerPakFilenameAlphabet[] = {
    0x00, 0x7E, 0x7E, 0x7E, 0x7E, 0x7E, 0x7E, 0x7E, 0x7E, 0x7E, 0x7E, 0x7E, 0x7E, 0x7E, 0x7E, 0x20, 0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37,
    0x38, 0x39, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4A, 0x4B, 0x4C, 0x4D, 0x4E, 0x4F, 0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56,
    0x57, 0x58, 0x59, 0x5A, 0x21, 0x22, 0x23, 0x27, 0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F, 0x3A, 0x3D, 0x3F, 0x40,
#if defined(VERSION_DE)
    0x00, 0x6D,
#endif
#if defined(VERSION_EU)
    0x00, 0x20,
#endif
#if defined(VERSION_EU_X) || defined(VERSION_US_REV1)
    0x00, 0x12,
#endif
#if defined(VERSION_US)
    0x00, 0x5F,
#endif
};
/* bytes live in the preceding array */
s32 g_controllerPakFilenameAlphabetCountWord[1] = {
    2,
};
#if defined(VERSION_EU_X) || defined(VERSION_US_REV1)
s32 g_controllerPakFilenameAlphabetLimitWords[3] = {
    11264, 512, 1,
};
#endif
#if defined(VERSION_EU)
s32 k_gControllerpakfilenamealphabetFragment[3] = {
    11264, 512, 2865184,
};
#endif
#if defined(VERSION_DE) || defined(VERSION_US)
s32 k_GControllerpakfilenamealphabetEncodedWords[3] = {
    11264, 512, 0,
};
#endif
s32 g_controllerPakFilenameAlphabetTrailingWords[8] = {
    0, 0, 0, 0, 0, 0,
    -1, 0,
};

/* Inline copy of Note_DecodeNoteText: decodes the n pak font codes at src into dst as text (codes from
   0x42 up become '~', leading zero codes blanks), trims trailing blanks and terminates dst. */
static inline void Pak_DecodeNoteName_noteReadnoteinfo(u8 *src, u8 *dst, s32 n) {
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
static inline s32 Note_ReadFileIntoBuffer_noteReadnoteinfo(s32 ch, s32 file_no, void *dst, s32 size) {
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
    Pak_DecodeNoteName_noteReadnoteinfo(g_controllerPakNoteLists[ch].notes[index].game_name, name, 17);
    Pak_DecodeNoteName_noteReadnoteinfo(g_controllerPakNoteLists[ch].notes[index].ext_name, ext, 4);
    code[4] = 0;
    company[2] = 0;
    }
    return 0;
}

s32 Note_DeleteNote(s32 ch, s32 index) {

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
        if (Note_ReadFileIntoBuffer_noteReadnoteinfo(ch, file_no, buf, blocks) == 0 && Defs_CompareMemory(buf, data, size) == 0) {
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
static inline s32 Pak_PeekNoteGameName_noteReadnoteinfo(s32 channel, s32 note, u8 **gameName) {
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
        Pak_PeekNoteGameName_noteReadnoteinfo(channel, note, &encodedName);
        Pak_DecodeNoteName_noteReadnoteinfo(encodedName, decodedName, 16);
        if (XPlus_CompareStrings(decodedName, name) == 0) {
            if (noteIndex != NULL) {
                *noteIndex = note;
            }
            return 1;
        }
    }
    return 0;
}

/* Releases the save buffer and clears its global state. */
void Note_AllocateScratchBuffer(void) {
    struct CacheResourceNode *block;
    s32 buffer;

    block = Cache_AllocateResource(0, 2064, 35, &g_pakPakStateNoteName);
    buffer = block->data;
    g_controllerPakProbeResource = (s32 *)block;
    g_controllerPakNoteLists = buffer;
    XPlus_FillMemory((void *)buffer, 0, 2064);
    g_controllerPakProbeActive = 1;
}

void Note_FreeScratchBuffer(void) {
    Cache_DrainAndCompactResources(0);
    if (g_controllerPakProbeResource) {
        Cache_ReleaseResource(0, g_controllerPakProbeResource);
        g_controllerPakProbeResource = 0;
        g_controllerPakNoteLists = 0;
    }
    g_controllerPakProbeActive = 0;
}

/* Probes the Controller Pak slot for kind and records its state: 2 when the probe succeeds, otherwise 3 or 1 depending on Note_UpdateStatus. */
void Note_ProbeStatus(s32 kind)
{
    PakRecord *cur;
    s32 ready;

    ((void (*)(s32))Control_AcquireControllerLock)(1);
    Control_ReadControllerStates();
    g_controllerPakFrontendState = 2;

    cur = g_controllerPakChannelRecords + kind;
    if (g_controllerReadStatusBytes[kind * 4] != 0) {
        cur->present = 0;
        ready = 0;
    } else {
        cur->present = osMotorInit(g_controllerSiMessageQueue, cur->pak, kind) == 0;
        ready = cur->present;
    }

    if (ready != 0) {
        g_controllerPakChannelStates[kind] = 2;
    } else if (Note_UpdateStatus(kind) != 0) {
        g_controllerPakChannelStates[kind] = 3;
    } else {
        g_controllerPakChannelStates[kind] = 1;
    }
    Control_ReleasePakLock();
}

/* Returns entry i of g_controllerPakChannelStatuses when entry i of the state table g_controllerPakChannelStates is 3, otherwise -2. */
s32 Note_GetStatus(s32 index) {
    if (g_controllerPakChannelStates[index] != 3) {
        return -2;
    }
    return g_controllerPakChannelStatuses[index];
}

/* Returns whether entry i of the word table g_controllerPakChannelStates equals 2. */
s32 Note_IsChannelReady(s32 index) {
    return g_controllerPakChannelStates[index] == 2;
}

/* Refreshes a controller slot and resolves its pending device state. */



/* Reports through the third argument the size in 256-byte units, per Note_BytesToPakPages, of entry j of
   record i in the table g_controllerPakNoteLists points to, returning zero, or returns -2 when record i's state in
   g_controllerPakChannelStates is not 3. */
s32 Note_ReadNoteData(s32 slot, s32 noteIndex, s32 destination, s32 length)
{
  s32 size;
  s32 *buf;
  s32 zero;
  s32 one;
  s32 addr;
  s32 result;
  size = (length + 0xFF) & (~0xFF);
  one = 1;
  zero = 0;
  if (g_controllerPakChannelStates[slot] != 3)
  {
    return -2;
  }
  if (Cache_GetResourceActivityState() == 0)
  {
    Cache_SetResourceActivityState(one);
  }
  buf = Cache_AllocateResource(0, size, 35, g_pakReadScratchNoteName);
  addr = *buf;
  ((void (*)(s32))Control_AcquireControllerLock)(1);
  Control_ReadControllerStates();
  result = g_controllerPakChannelStatuses[slot];
  g_controllerPakFrontendState = 2;
  if (result == 0)
  {
    result = Pfs_ReadWriteFile(&g_controllerPakFileSystems[slot], noteIndex, zero, zero, size, addr);
    if (result != zero)
    {
      result = -1;
    }
    if (result == 0)
    {
      Libc_CopyBytes(destination, addr, length);
    }
  }
  Control_ReleasePakLock();
  Cache_DrainAndCompactResources(zero);
  if (buf != ((void *) 0))
  {
    Cache_ReleaseResource(0, buf);
  }
  return result;
}

/* Counts empty Controller Pak note slots on channel ch when the pak is ready and returns its error status, or -2 when not ready. */
s32 Note_CountFreeNotes(s32 ch, s32 *count) {
    s32 i;

    if (g_controllerPakChannelStates[ch] != 3) {
        return -2;
    }
    *count = 0;
    if (g_controllerPakChannelStatuses[ch] == 0) {
        for (i = 0; i < 16; i++) {
            if (g_controllerPakNoteLists[ch].notes[i].file_size == 0) {
                (*count)++;
            }
        }
    }
    return g_controllerPakChannelStatuses[ch];
}

int Note_GetFreePages(int slot, int *score) {
    if (g_controllerPakChannelStates[slot] != 3) {
        return -2;
    }
    if (g_controllerPakChannelStatuses[slot] == 0) {
        *score = g_controllerPakNoteLists[slot].free / 256;
    } else {
        *score = 0;
    }
    return g_controllerPakChannelStatuses[slot];
}

s32 Note_RepairIdIfNeeded(s32 channel) {
    s32 channelOffset;
    s32 result;
    channelOffset = channel * 4;
    if (g_controllerPakChannelStates[channel] != 3) {
        return -2;
    }
    ((void (*)(s32))Control_AcquireControllerLock)(1);
    Control_ReadControllerStates();
    result = g_controllerPakChannelStatuses[channel];
    g_controllerPakFrontendState = 2;
    if (result == -4) {
        result = osPfsRepairId(&g_controllerPakFileSystems[channel]);
        if (result != 0) {
            result = -1;
        }
        Note_UpdateStatus(channel);
    }
    Control_ReleasePakLock();
    return result;
}

s32 Note_RepairId(s32 channel) {
    s32 result;
    if (g_controllerPakChannelStates[channel] != 3) {
        return -2;
    }
    ((void (*)(s32))Control_AcquireControllerLock)(1);
    Control_ReadControllerStates();
    g_controllerPakFrontendState = 2;
    result = osPfsRepairId(&g_controllerPakFileSystems[channel]);
    if (result != 0) {
        result = -1;
    }
    Note_UpdateStatus(channel);
    Control_ReleasePakLock();
    return result;
}

s32 Note_GetNoteGameName(s32 index, s32 entry, char **out) {
    if (g_controllerPakChannelStates[index] != 3) {
        return -2;
    }
    *out = g_controllerPakNoteLists[index].notes[entry].game_name;
    return 0;
}

s32 Note_GetNoteExtension(s32 index, s32 entry, char **out) {
    if (g_controllerPakChannelStates[index] != 3) {
        return -2;
    }
    *out = g_controllerPakNoteLists[index].notes[entry].ext_name;
    return 0;
}

s32 Note_GetNotePageCount(s32 index, s32 entry, s32 *out) {
    if (g_controllerPakChannelStates[index] != 3) {
        return -2;
    }
    *out = Note_BytesToPakPages(g_controllerPakNoteLists[index].notes[entry].file_size);
    return 0;
}

/* Chooses a free extension letter for a new note on the Controller Pak on channel ch: refuses with
   -2 unless the pak is ready, queries each of the 16 notes through Note_ReadNoteInfo (failing with -1
   on error) and marks the letter of every existing note, then writes the first free letter from
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

/* Marks the given controller port's pak record in g_controllerPakChannelRecords present when the port's g_controllerReadStatusBytes status byte is clear and osMotorInit initialises the record's pak block through g_controllerSiMessageQueue without error, clearing the mark otherwise, and returns the mark.
   */
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

/* Converts a controller-pak filename through its character table, blanking leading nulls, then trims trailing spaces. */
void Note_DecodeNoteText(const char *encodedText, u8 *noteText, s32 characterCount) {
    s32 i;
    s32 started;

    for (i = 0; i < characterCount; i++) {
        noteText[i] = 0;
    }

    started = 0;
    for (i = started; i < characterCount; i++, encodedText++) {
        if (*(const u8 *)encodedText < 66) {
            if (*(const u8 *)encodedText == 0 && !started) {
                noteText[i] = ' ';
            } else {
                noteText[i] = g_controllerPakFilenameAlphabet[*(const u8 *)encodedText];
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

/* Computes the CRC-32 with polynomial 0xEDB88320 of byteCount bytes at data, continuing from the running value initialCrc, from a 256-entry table built on the stack. */
u32 Note_Crc32(const void *data, u32 byteCount, u32 initialCrc) {
    u32 table[256];
    u32 i;
    u32 j;
    u32 value;
    u32 shifted;
    const u8 *cursor = (const u8 *)data;
    const u8 *end;

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

    end = cursor + byteCount;
    initialCrc = ~initialCrc;
    while (cursor < end) {
        initialCrc = table[(initialCrc ^ *cursor++) & 0xFF] ^ ((initialCrc >> 8) & 0xFFFFFF);
    }
    return ~initialCrc;
}

/* Returns the word held in g_controllerPakProbeActive. */
s32 Note_HasScratchBuffer(void) {
    return g_controllerPakProbeActive;
}

typedef struct CacheResourceNode Handle;
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
        memoryEnd = Defs_GetMemorySize() | 0x80000000U;
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
        memoryEnd = 0x80400000U; /* Cached address immediately above base N64 RDRAM. */
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

    record->displayLists = Cache_AllocateResource(0, (g_primaryDisplayListCapacity + g_secondaryDisplayListCapacity) * 2 * sizeof(Gfx), 35, s_displayListsText);
    record->fifo = Cache_AllocateResource(0, 0x8000, 35, s_fifoText);
    record->audioHeap = Cache_AllocateResource(0, 0x22000, 35, s_audioHeapText);
    g_graphicsMicrocodeTextSize = 0x8000;
    g_audioContextHeapBytes = 0x22000;
    g_primaryDisplayListBufferZero = record->displayLists->data;
    g_secondaryDisplayListBufferZero = g_primaryDisplayListBufferZero + g_primaryDisplayListCapacity;
    g_primaryDisplayListBufferAlternate = g_secondaryDisplayListBufferZero + g_secondaryDisplayListCapacity;
    g_secondaryDisplayListBufferAlternate = g_primaryDisplayListBufferAlternate + g_primaryDisplayListCapacity;
    g_graphicsMicrocodeDataSize = record->fifo->data;
    g_audioContextHeapBuffer = (u8 *)record->audioHeap->data;
    for (i = 0; i < g_renderFrameBufferCount; i++) {
    }
    record->ready = 1;
    return 1;
}

/* Clears the render buffer record: the ready flag, the display lists, the FIFO, the Z buffer, the
   audio heap and the three frame buffers (last to first). */
void Note_ClearRenderRecord(struct RenderBufferResources *record) {
    s32 i;
    record->ready = 0;
    record->displayLists = 0;
    record->fifo = 0;
    record->zBuffer = 0;
    record->audioHeap = 0;
    for (i = 2; i >= 0; i--) {
        record->frameBuffers[i] = 0;
    }
}
/* Releases every resource handle the render buffer record holds and clears the record. */
void Note_ReleaseRenderBuffers(struct RenderBufferResources *record) {
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
}
