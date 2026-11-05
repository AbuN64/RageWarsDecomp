#ifndef MENU_NOTE_READNOTEDATA_H
#define MENU_NOTE_READNOTEDATA_H
#include "types.h"
extern s32 Note_ReadNoteData(s32 slot, s32 noteIndex, s32 destination, s32 length);
extern s32 Note_RepairId(s32);
extern s32 Note_CountFreeNotes(s32 ch, s32 *noteCount);
extern s32 Note_GetFreePages(s32 ch, s32 *freeSpace);
extern s32 Note_RepairIdIfNeeded(s32 ch);
#endif
