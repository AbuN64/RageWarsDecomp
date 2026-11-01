#include "COMMON/GAMEPLAY_TRANSITION.H"
#include "COMMON/INTEGERSTATE1250.H"
#include "TYPES.H"

extern u8 *XPlus_CopyString(u8 *, u8 *);
extern void Gsky_PostScaledScreenMessage(void *, s32, void *, f32);
#include "COMMON/MENU_MATCH_GLOBALS.H"




void Playerai_PostMessageHistoryEntry(void *player, u8 *message, f32 size) {
    s32 count;
    s32 messageCameraAddress;

    count = ((Shared_ActorView *)player)->messageIndex + 1;
    ((Shared_ActorView *)player)->messageIndex = count;
    if (count == 5) {
        ((Shared_ActorView *)player)->messageIndex = 0;
    }
    XPlus_CopyString(((Shared_ActorView *)player)->messageHistory[((Shared_ActorView *)player)->messageIndex], message);
    messageCameraAddress = (s32)((Shared_ActorView *)player)->message;
    if (messageCameraAddress != 0) {
        Gsky_PostScaledScreenMessage(&g_frontendScreenStatus, messageCameraAddress,
                      ((Shared_ActorView *)player)->messageHistory[((Shared_ActorView *)player)->messageIndex],
                      size);
    }
}
