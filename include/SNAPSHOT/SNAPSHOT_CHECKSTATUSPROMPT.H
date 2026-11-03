#ifndef SNAPSHOT_SNAPSHOT_CHECKSTATUSPROMPT_H
#define SNAPSHOT_SNAPSHOT_CHECKSTATUSPROMPT_H
struct MenuPakBeginProfileLoad;
s32 Snapshot_CheckStatusPrompt(struct MenuPakBeginProfileLoad *menu, s32 channel, s32 quiet);
void Snapshot_CreateSaveSnapshot(u8 *player);
#endif
