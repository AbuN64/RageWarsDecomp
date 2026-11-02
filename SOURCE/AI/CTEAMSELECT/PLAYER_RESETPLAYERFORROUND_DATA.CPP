#include "COMMON/VECTOR4F.H"
#include "MENU/TEAMMENU.H"
#include "TYPES.H"
#include "COMMON/TRIPLE.H"
#include "AI/CTEAMSELECT.H"
#include <PR/gbi.h>
#include <ultra64.h>
#include "COMMON/WEAPON_SCREEN_MESSAGE_OPERATIONS.H"
#include "COMMON/SESSIONHANDLERROW.H"

/* 80217388_10.CPP */
/** Reset the team menu: closed, no cursor or hover, and its four team slots fanned 30 degrees apart. */
void TeamSelect_ResetTeamWheel(TeamMenu *menu) {
    s32 i;

    menu->state = 0;
    menu->unused = 0;
    menu->open = 0;
    menu->reset = 0;
    menu->spin = 0;
    menu->cursor = -1;
    menu->count = 4;
    menu->hover = -1;
    for (i = 0; i < 4; i++) {
        menu->slots[i].angle = -(i * g_teamWheelResetAngleStep);
        menu->slots[i].unused2 = 0;
        menu->slots[i].scale = g_teamWheelInitialSlotScale;
    }
}

/* 80217388_11.CPP */
extern void Cteamselect_DrawTeamWheel(s32 menu, s32 unused1, s32 player);

void TeamSelect_DrawTeamWheelSprites(s32 menu, s32 unused1, s32 player) {
    Gfx *cmd;

    Onscrn_SetupSpriteMode(0xFF);
    gDPSetTextureFilter(g_displayListCursor++, G_TF_BILERP);
    Cteamselect_DrawTeamWheel(menu, unused1, player);
}

/** Reset a record and mark its word at offset 0x6C as invalid. */
void TeamSelect_CloseTeamWheel(void *record) {
    TeamMenu *menu = record;
    menu->state = 0;
    menu->unused = 0;
    menu->cursor = -1;
    menu->open = 0;
}
