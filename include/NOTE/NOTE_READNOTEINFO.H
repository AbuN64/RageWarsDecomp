#ifndef NOTE_NOTE_READNOTEINFO_H
#define NOTE_NOTE_READNOTEINFO_H
s32 Note_ReadNoteInfo(s32 ch, s32 index, s32 *exists, u8 *name, u8 *ext, s32 *size, u8 *company, u8 *code);
s32 Note_SaveNote(s32 ch, s32 size, void *data, u8 *name, u8 *ext, u8 *code);
#endif
