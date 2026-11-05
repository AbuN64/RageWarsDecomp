#ifndef OVLGAME_MENU_HANDLESESSIONOPTIONPAGE_H
#define OVLGAME_MENU_HANDLESESSIONOPTIONPAGE_H
#include "Ovlgame/confirming_controller.h"
struct Holder;
extern s32 Menu_HandleSessionOptionPage(void *menuOwner, struct Holder *holder);
struct Holder {
    char pad[0x1C];
    struct MusicPreviewOwnerView *owner;
};

#endif
