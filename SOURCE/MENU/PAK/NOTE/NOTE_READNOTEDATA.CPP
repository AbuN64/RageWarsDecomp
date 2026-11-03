#include "../../../../sdk/include/LIBC.H"
#include "COMMON/ENTRYRECAT0V3.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "MENU/PAK_DIRECTORY_VIEWS.H"
#include "COMMON/ITEMRECAT20V1.H"
#include <ultra64.h>
#include "TYPES.H"
#include "MENU/PAK/NOTE_GETNOTEPAGECOUNT.H"
#include "NOTE/NOTE_READNOTEDATA.H"
extern void Cache_ReleaseResource(void *cache, void *resource);

/* Loads a page-aligned resource into the selected device slot and reports the result. */






extern u8 g_controllerPakFrontendState;


extern void **Cache_AllocateResource(s32, s32, s32, char *);


extern void Cache_DrainAndCompactResources(s32);

extern void Cache_SetResourceActivityState(unsigned int);

extern int Cache_GetResourceActivityState(void);

extern void Control_ReadControllerStates(void);

extern void Control_ReleasePakLock(void);



extern s32 Pfs_ReadWriteFile(OSPfs* pfs, s32 file_no, u8 flag, int offset, int size_in_bytes, u8* data_buffer);

/* For a player slot whose state g_controllerPakChannelStates is 3, writes its score (the first word of its 0x204-byte
   record in g_controllerPakNoteLists divided by 256, or 0 when the flag g_controllerPakChannelStatuses is set) and returns the flag;
   other states return -2. */




/* Refreshes a controller slot and resolves its pending device state. */
void Control_ReadControllerStates(void);

 /* extern */
 /* extern */
void Control_ReleasePakLock(void);

 /* extern */
s32 Note_UpdateStatus(s32);

 /* extern */


/* Reports the address of the field at offset 0xE of entry j in record i of the table g_controllerPakNoteLists
   points to, returning zero, or returns -2 when record i's state in g_controllerPakChannelStates is not 3. */







/* Reports the address of the field at offset 0xA of entry j in record i of the table g_controllerPakNoteLists
   points to, returning zero, or returns -2 when record i's state in g_controllerPakChannelStates is not 3. */







/* Reports through the third argument the size in 256-byte units, per Note_BytesToPakPages, of entry j of
   record i in the table g_controllerPakNoteLists points to, returning zero, or returns -2 when record i's state in
   g_controllerPakChannelStates is not 3. */







extern u32 Note_BytesToPakPages(u32);

extern PakDirectory *g_controllerPakNoteLists;

extern OSPfs g_controllerPakFileSystems[];

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
