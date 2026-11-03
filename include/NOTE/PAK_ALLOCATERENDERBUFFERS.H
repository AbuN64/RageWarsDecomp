#ifndef NOTE_PAK_ALLOCATERENDERBUFFERS_H
#define NOTE_PAK_ALLOCATERENDERBUFFERS_H
void Note_DecodeNoteText(u8 *encodedText, u8 *noteText, s32 characterCount);
s32 Note_FindFreeNoteExtension(s32 ch, u8 *ext);
#endif
