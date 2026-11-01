#include "../../../../sdk/include/LIBC.H"
#include "COMMON/ENTRYRECAT0V3.H"
#include "COMMON/LONE/CONTROLLER_SI_MESSAGE_QUEUE.H"
#include "MENU/PAK_DIRECTORY_VIEWS.H"
#include "TYPES.H"
#include "COMMON/VECTOR4F.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/PAKQUEUESTATE.H"
#include "COMMON/RECORDRECAT1C.H"
#include "MENU/PAK/NOTE_REFRESHNOTES.H"
#include <ultra64.h>

/* Refreshes the cached directory of the Controller Pak on channel ch: when the directory buffer
   exists it reads the state of each of the 16 notes through osPfsFileState (osPfsFileState),
   retrying a failure once and clearing the cached note when it does not exist (5), then reads the
   free space through osPfsFreeBlocks into the buffer on success and returns that result. */







extern OSPfs g_controllerPakFileSystems[];

extern PakDirectory *g_controllerPakNoteLists;




static inline void *pak27(s32 ch) {return &g_controllerPakFileSystems[ch];}

extern u8 g_controllerPakFrontendState;

extern PakRecord g_controllerPakChannelRecords[];

s32 osMotorInit(OSMesgQueue *mq, OSPfs *pfs, int channel);

extern s32 Note_UpdateStatus(s32);

extern u8 g_controllerPakFilenameAlphabet[];



extern int XPlus_UppercaseCharacter(int c);



extern s32 osPfsAllocateFile(OSPfs *pfs, u16 company_code, u32 game_code, u8 *game_name, u8 *ext_name,
                         s32 size, s32 *file_no);

extern s32 Pfs_ReadWriteFile(OSPfs* pfs, s32 file_no, u8 flag, int offset, int size_in_bytes, u8* data_buffer);

static inline void Note_EncodeUppercaseFilename(u8 *dst, u8 *src, s32 n) {
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

extern s32 Note_CreateAndWriteNote(s32 ch, s32 size, void *data, u8 *game_name, s32 *file_no, u8 *ext_name,
                         u8 *company, u8 *code);

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
        pfs=pak27(ch);
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
        if(g_controllerPakChannelStatuses[ch]==-5) goto ready;
        if(g_controllerPakChannelStatuses[ch]==-2) break;
        tries++;
    } while(tries<4);
    goto finish;
ready:
    g_controllerPakChannelStates[ch]=3;
    if(Note_RefreshNotes(ch)!=0) g_controllerPakChannelStatuses[ch]=-4;
    else g_controllerPakChannelStatuses[ch]=0;
finish:
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

s32 Note_CreateAndWriteNote(s32 ch, s32 size, void *data, u8 *game_name, s32 *file_no, u8 *ext_name, u8 *company, u8 *code);

s32 Note_CreateAndWriteNote(s32 ch, s32 size, void *data, u8 *game_name, s32 *file_no, u8 *ext_name,
                  u8 *company, u8 *code) {
    extern s32 osPfsDeleteFile(OSPfs *pfs, u16 company_code, u32 game_code, u8 *game_name, u8 *ext_name);
    extern s32 Note_UpdateStatus(s32 ch);
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
        Note_EncodeUppercaseFilename(ext, ext_name, 4);
        size = (size + 0xFF) & ~0xFF;
        Libc_CopyBytes(name, game_name, 16);
        Note_EncodeUppercaseFilename(name, game_name, 16);
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
