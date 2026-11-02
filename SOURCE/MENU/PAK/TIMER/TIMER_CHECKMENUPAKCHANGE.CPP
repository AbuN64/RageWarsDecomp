#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/RECORDRECATCV1.H"
#include "TYPES.H"
#include "COMMON/PAK_MENU.H"
#include "COMMON/MENURECAT24.H"

/* Latches g_pakMenuPromptAccepted to one when the record's team value (g_introSelectedItem when g_pakUseScannedChannel is set, otherwise the signed byte at offset 4 of the object at 0x20) is not -1 and both Control_PeekPakChange_Pak and Snapshot_CheckStatusPrompt accept it, then returns g_pakMenuPromptAccepted. */




extern s32 g_pakUseScannedChannel;
extern s32 Snapshot_CheckStatusPrompt(struct Shared_PakMenu *, s32, s32);

static inline s32 Pak_GetMenuChannel(struct Shared_PakMenu *record) {
    if (g_pakUseScannedChannel != 0) {
        return g_introSelectedItem;
    }
    return record->owner->controllerPort;
}

s32 Timer_CheckMenuPakChange(struct Shared_PakMenu *record) {
    if (g_pakMenuPromptAccepted == 0) {
        if (Pak_GetMenuChannel(record) != -1) {
            if (Control_PeekPakChange(Pak_GetMenuChannel(record)) != 0) {
                if (Snapshot_CheckStatusPrompt(record, Pak_GetMenuChannel(record), 0) != 0) {
                    g_pakMenuPromptAccepted = 1;
                }
            }
        }
    }
    return g_pakMenuPromptAccepted;
}
