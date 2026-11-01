#ifndef COMMON_ENTRYRECAT0V3_H
#define COMMON_ENTRYRECAT0V3_H
#include "TYPES.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/RESIDENT_EVENT_HANDLER.H"

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
