#ifndef MENU_NOTE_CREATEANDWRITENOTE_H
#define MENU_NOTE_CREATEANDWRITENOTE_H
#include "types.h"
extern s32 Note_UpdateStatus(s32);
extern s32 Note_CreateAndWriteNote(s32 ch, s32 size, void *data, u8 *game_name, s32 *file_no, u8 *ext_name, u8 *company, u8 *code);
#endif
