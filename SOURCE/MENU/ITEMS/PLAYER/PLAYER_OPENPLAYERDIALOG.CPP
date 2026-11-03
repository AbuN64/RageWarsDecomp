#include "COMMON/SHARED_OPTIONSSCREEN.H"
#include "MENU/OBJECT1C8.H"
#include "TYPES.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/MENURECAT24.H"
#include "MENU/ITEMS/PLAYER_OPENPLAYERDIALOG.H"
#include "MENU/PAK/TIMER_CANCELPENDINGOPERATION.H"
#include "AI/PLAYER/PLAYER_GETAMMOCAPACITY.H"
#include "MENU/PAK/MENU_CREATEMENUFROMTEMPLATE.H"

/* Loads the owner at offset 0x1C of the second argument into g_playerViewRenderContext through Player_GetPlayerIndexDe,
   calls Timer_ClearTimerFlag, and hands the owner, its word at 0x698 and a zero with the resource
   g_playerMenuDialogRomResource to Menu_OpenDialog for the block 0x5DC bytes into g_playerViewRenderContext. Returns one. */




extern char g_playerViewRenderContext[];



s32 Player_OpenPlayerDialog(void *unused, struct MenuItemOwnerLinkView *holder) {
    struct MenuItemControllerView *owner = holder->owner;

    Player_GetPlayerIndex(g_playerViewRenderContext, owner);
    Timer_ClearTimerFlag();
    Menu_OpenDialog(&((Shared_MenuData *)g_playerViewRenderContext)->dialogOwner, g_playerMenuDialogRomResource, owner, owner->value, 0);
    return 1;
}
