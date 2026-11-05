#ifndef COMMON_NOTE_STATE_H
#define COMMON_NOTE_STATE_H
extern int g_controllerPakChannelStates[];
extern int g_controllerPakChannelStatuses[];
#include "types.h"
#include "Common/runtime_declarations.h"
#include "Common/resident_event_handler.h"

struct SceneFrameItemReference;
struct SceneFrameItemReference {
    char data[32];
};


struct PakDirectoryEntryKindView;
typedef struct PakDirectoryEntryKindView PakDirectoryEntryKindView;




struct NoteState;
struct NoteState {
    u32 file_size;
    u32 game_code;
    u16 company_code;
    char ext_name[4];
    char game_name[16];
    char pad[2];
};



extern unsigned char * g_pakCompanyCodeFixed;
extern char *g_pakLegacySnapshotGameNameFixed; /* Controller Pak game code "NRWE" */





struct SceneFrameItemReference;

struct PakDirectory;
typedef struct PakDirectory PakDirectory;

struct Device;
typedef struct Device Device;

struct PakDirectoryEntryKindView;

struct Device;

struct NoteState;
typedef struct NoteState NoteState;

struct PakDirectory;






extern void Note_FreeScratchBuffer(void);

void Note_AllocateScratchBuffer(void);
#endif
