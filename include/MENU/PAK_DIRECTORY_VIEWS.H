#ifndef MENU_PAK_DIRECTORY_VIEWS_H
#define MENU_PAK_DIRECTORY_VIEWS_H
#include "TYPES.H"
#include "COMMON/ENTRYRECAT0V3.H"
struct PakDirectoryEntryKindView {
    char pad[0x11];
    unsigned char kind;
    unsigned char subtype;
};
struct Device {
    s8 pad0[0x68];
};
struct PakDirectory {
    s32 free;
    NoteState notes[16];
};
#endif
