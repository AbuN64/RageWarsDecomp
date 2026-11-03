#include "RSP/RANDOM_DIRECTION_AND_AFFINE_MATH.H"
#include "include_asm.h"
#include "COMMON/VIDEO_DIMENSIONS.H"
#include "COMMON/LONE/HUD_REFERENCE_VIEWPORT_HEIGHT.H"
#include "RENDER/MATERIAL_COLOR_AND_FOG_VIEWS.H"
#include "COMMON/CHARACTERSELECTIONROOT.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/SELECTIONSCREENSTATE.H"
#include <PR/gbi.h>
#include <ultra64.h>
#include "TYPES.H"
#include "FRONTEND/WIDGET_FINDWIDGETATPOINT.H"
#include "FRONTEND/FRONTEND_DRAWMODELPREVIEW.H"
#include "COMMON/SHARED_GAMESLOT.H"
#include "FRONTEND/SMP_OVERLAY.H"
#define g_gameSettingsView ((HudStatusShared_Settings *)&g_gameSettings)



extern struct CacheResourceBlockView g_menuPlayerScissorRects[];

extern s32 g_hudReferenceViewportWidth;


extern Gfx *g_displayListCursor;

extern void Preview_DrawModelPreview(struct ModelPreview *self);
extern u8 g_profileCharacterUnlockCounts[][0x190];

/* Enables character choices unlocked by active players and highlights the selected profile's unlocked characters. */
#if defined(VERSION_DE)
enum { UNLOCK_MARK = 129 };
#elif defined(VERSION_EU_X)
enum { UNLOCK_MARK = 135 };
#else
enum { UNLOCK_MARK = 131 };
#endif

extern char g_localPlayerProfiles[][0x190];

extern signed char g_profileSlotIndices[];

extern u8 g_profileUnlockedTrialBits[];

extern s32 g_frontendKeyUnlockEntries[][28];


extern s32 Player_TestAchievementFlag7(void *profile, s32 character);

extern s32 Defs_TestBit(void *bitArray, s32 index);

extern void Defs_SetBitValue(u8 *bits, s32 index, s32 value);

extern void Widget_SetWidgetFlag100(MenuWidget *record, int enable);

/* Cycles player p's choice on the screen g_characterSelectionMenu: dims the item for the current choice at 0x18
   of p's 0x4C8-byte entry (from p's 36-byte layout row g_characterSelectionMenuEntries, cells from 0xC) to alpha 0x50
   through Widget_SetWidgetFlag40_EquipActivateequipmentpanel(0), advances the choice modulo the count byte (at least one) found at
   0x57 plus the index Key_GetCharacterPreviewModel gives for the entry's word at 0x10 in p's 400-byte record of
   g_localPlayerProfiles, highlights the new choice's item with alpha 0x96 and stores it. Written from the
   assembly with the entries as an array member of the screen. */














/* Activates player p's panel on the screen g_characterSelectionMenu: passes p and the frame item id from p's
   36-byte layout row g_characterSelectionMenuEntries to SmpOverlay_ShowSlotById_CharacterUnlocks, takes the row's cursor item into the word at 0x8
   of p's 0x4C8-byte entry, places it two units up and left of the frame item, shows it, sets the
   entry's state at 0x14 to one, redraws through Menu_RefreshPlayerCharacterVariants and hides the row's prompt item. */













/* Resets player p's choice on the screen g_characterSelectionMenu: calls Widget_SetWidgetFlag08_EquipActivateequipmentpanel(1) on the three items in
   option cells from 0x18 of p's 36-byte layout row g_characterSelectionMenuEntries, dims the item of the current choice at 0x18 of
   p's 0x4C8-byte entry to alpha 0x50 through Widget_SetWidgetFlag40_EquipActivateequipmentpanel(0) and resets the choice to 0; unless
   the entry's kind at 0x10 is -1 it then calls Widget_SetWidgetFlag08_EquipActivateequipmentpanel(0) on as many of those cells as the
   count byte (at least one) at 0x57 plus the index Key_GetCharacterPreviewModel gives for the kind in p's
   400-byte record of g_localPlayerProfiles, and highlights the item of the choice with alpha 0x96. Adapted
   from Menu_CyclePlayerCharacterVariant. */













/* Confirms a player's character choice and, once no player is still choosing, fills the match roster and starts the game; scheduler lever: the block-scoped match pointer inside the roster loop places the hoisted match address after the loop constants, as the cartridge does. */










extern CharacterScreenCell g_characterSelectionMenuOptionCells[][9];

extern unsigned char g_profileCharacterSelections[];

extern void SmpOverlay_SetSlotValue(void *, int, int);

extern void Preview_SetPreviewTransformUpdate(struct Object49C *object, s32 value);

extern void SmXlate_SwitchScreen(s32);

/* Chooses a different enabled random character, updates its preview and selects an available costume. */











extern s_CharacterData g_frontendKeyEntries[];


extern s32 Widget_ListHasFlag100(struct WidgetNode *node);


/* Counts how many of the four 0x4C8-byte entries g_characterSelectionMenu points to are in state 1 or 2. */




/* Draw callback of the four-player screen g_characterSelectionMenu: on draw event 1 in state 3 it clips the display list to each joined or ready player's viewport in g_menuPlayerScissorRects and draws that panel through Preview_DrawModelPreview, in the flash fill (mode 3) while the panel's flash counter runs down and in opaque white otherwise, then restores the full-screen clip and the white fill; returns zero. */
s32 Menu_RenderPlayerCharacterPreviews(void *unusedObject, void *unusedContext, s32 event)
{
    s32 i;
    if (event == 1 && g_characterSelectionMenu->phase == 3) {
        g_menuModelFillEnabled = 0;
        g_menuModelFillColor[0] = 255.0f;
        g_menuModelFillColor[1] = 255.0f;
        g_menuModelFillColor[2] = 255.0f;
        g_menuModelFillColor[3] = 255.0f;
        for (i = 0; i < 4; i++) {
            if (g_characterSelectionMenu->players[i].selectionState == 1 || g_characterSelectionMenu->players[i].selectionState == 3) {
                if (g_characterSelectionMenu->players[i].kind != -1) {
                    gDPSetScissor(g_displayListCursor++, G_SC_NON_INTERLACE, g_menuPlayerScissorRects[i].first, g_menuPlayerScissorRects[i].second, g_menuPlayerScissorRects[i].third, g_menuPlayerScissorRects[i].fourth);
                    if (g_characterSelectionMenu->players[i].tintFramesLeft > 0) {
                        g_menuModelFillColor[0] = 150.0f;
                        g_menuModelFillColor[1] = 0.0f;
                        g_menuModelFillColor[2] = 0.0f;
                        g_menuModelFillColor[3] = 100.0f;
                        g_menuModelFillColor[4] = 100.0f;
                        g_menuModelFillEnabled = 3;
                        g_characterSelectionMenu->players[i].tintFramesLeft--;
                    } else {
                        g_menuModelFillEnabled = 0;
                        g_menuModelFillColor[0] = 255.0f;
                        g_menuModelFillColor[1] = 255.0f;
                        g_menuModelFillColor[2] = 255.0f;
                        g_menuModelFillColor[3] = 255.0f;
                    }
                    Preview_DrawModelPreview(g_characterSelectionMenu->players[i].model);
                }
            }
        }
        g_menuModelFillEnabled = 0;
        gDPSetScissor(g_displayListCursor++, G_SC_NON_INTERLACE, 0, 0, SCREEN_WD - 1, SCREEN_HT - 1);
        g_menuModelFillColor[0] = 255.0f;
        g_menuModelFillColor[1] = 255.0f;
        g_menuModelFillColor[2] = 255.0f;
        g_menuModelFillColor[3] = 255.0f;
    }
    return 0;
}

void Menu_RefreshCharacterUnlocks(void) {
    u8 bits[4];
    s32 i;
    s32 j;
    s32 found;
    MenuWidget *widget;
    MenuWidget *mark;

    for (i = 0; i < 17; i++) {
        found = 0;
        for (j = 0; j < 4 && !found; j++) {
            if (g_profileSlotIndices[j * 400] >= 0) {
                found = found || Player_TestAchievementFlag7(g_localPlayerProfiles[j], g_frontendKeyUnlockEntries[i][0]);
            }
        }
        if (g_gameSettingsView->trialKind == 0 || g_gameSettingsView->trialKind == 2) {
            if (g_gameSettingsView->flags & 0x8000000) {
                found = 1;
            }
        }
        Defs_SetBitValue(bits, i, found);
    }
    if (g_gameSettingsView->trialKind == 1) {
        Defs_SetBitValue(bits, 11, 0);
        Defs_SetBitValue(bits, 12, 0);
        Defs_SetBitValue(bits, 13, 0);
        Defs_SetBitValue(bits, 14, 0);
    }
    if (g_gameSettingsView->trialKind == 0 || g_gameSettingsView->trialKind == 2) {
        Defs_SetBitValue(bits, 1, 1);
    }
    for (i = 0; i < 17; i++) {
        widget = Node_FindWidgetByResourceId(g_characterSelectionMenu->screen, (u16)g_frontendKeyEntries[i].id);
        Widget_SetWidgetFlag100(widget, 0);
        if (!Defs_TestBit(bits, i)) {
            if (widget) {
                Widget_SetWidgetFlag100(widget, 1);
                Widget_SetWidgetFlag08(widget, 0);
            }
        } else if (g_gameSettingsView->trialKind == 1 && Defs_TestBit(g_profileUnlockedTrialBits, g_frontendKeyUnlockEntries[i][0]) == 1) {
            mark = Node_FindWidgetByResourceId(widget, UNLOCK_MARK);
            Widget_SetWidgetFlag08(mark, 1);
            mark->alpha = 50;
        }
    }
}

void Menu_CyclePlayerCharacterVariant(s32 player) {
    MenuWidget *item;
    s32 choice;
    s32 count;

    choice = g_characterSelectionMenu->players[player].choice;
    item = Node_FindWidgetByResourceId(g_characterSelectionMenu->screen, g_characterSelectionMenuEntries[player].cells[choice].id);
    Widget_SetWidgetFlag40(item, 0);
    item->alpha = 80;
    count = g_profileCharacterUnlockCounts[player][Key_GetCharacterPreviewModel(g_characterSelectionMenu->players[player].kind)];
    if (count <= 0) {
        count = 1;
    }
    choice = (choice + 1) % count;
    item = Node_FindWidgetByResourceId(g_characterSelectionMenu->screen, g_characterSelectionMenuEntries[player].cells[choice].id);
    Widget_SetWidgetFlag40(item, 1);
    item->alpha = 150;
    g_characterSelectionMenu->players[player].choice = choice;
}

void Menu_ShowPlayerCharacterSelection(s32 player) {
    MenuWidget *frame;

    SmpOverlay_ShowSlotById(g_characterSelectionMenu->screen, player, (s16)g_characterSelectionMenuEntries[player].kind);
    g_characterSelectionMenu->players[player].highlight = Node_FindWidgetByResourceId(g_characterSelectionMenu->screen, g_characterSelectionMenuEntries[player].cursor);
    frame = Node_FindWidgetByResourceId(g_characterSelectionMenu->screen, (u16)g_characterSelectionMenuEntries[player].kind);
    g_characterSelectionMenu->players[player].highlight->x = frame->x - 2;
    g_characterSelectionMenu->players[player].highlight->y = frame->y - 2;
    Widget_SetWidgetFlag08(g_characterSelectionMenu->players[player].highlight, 1);
    g_characterSelectionMenu->players[player].selectionState = 1;
    Menu_RefreshPlayerCharacterVariants(player);
    Widget_SetWidgetFlag08(Node_FindWidgetByResourceId(g_characterSelectionMenu->screen, g_characterSelectionMenuEntries[player].title), 0);
}

void Menu_RefreshPlayerCharacterVariants(s32 player) {
    MenuWidget *item;
    s32 count;
    s32 i;

    for (i = 0; i < 3; i++) {
        Widget_SetWidgetFlag08(Node_FindWidgetByResourceId(g_characterSelectionMenu->screen, g_characterSelectionMenuEntries[player].options[i].id), 1);
    }
    item = Node_FindWidgetByResourceId(g_characterSelectionMenu->screen,
                         g_characterSelectionMenuEntries[player].cells[g_characterSelectionMenu->players[player].choice].id);
    Widget_SetWidgetFlag40(item, 0);
    item->alpha = 80;
    g_characterSelectionMenu->players[player].choice = 0;
    if (g_characterSelectionMenu->players[player].kind == -1) {
        return;
    }
    count = g_profileCharacterUnlockCounts[player][Key_GetCharacterPreviewModel(g_characterSelectionMenu->players[player].kind)];
    if (count <= 0) {
        count = 1;
    }
    for (i = 0; i < count; i++) {
        Widget_SetWidgetFlag08(Node_FindWidgetByResourceId(g_characterSelectionMenu->screen, g_characterSelectionMenuEntries[player].options[i].id), 0);
    }
    item = Node_FindWidgetByResourceId(g_characterSelectionMenu->screen,
                         g_characterSelectionMenuEntries[player].cells[g_characterSelectionMenu->players[player].choice].id);
    Widget_SetWidgetFlag40(item, 1);
    item->alpha = 150;
}

void Menu_ApplySlotValueGfx(int player, int choice) {
    int i;
    int j;
    int count;
    ListScreenRecord *slot;
    int kind;

    g_characterSelectionMenu->players[player].selectionState = 3;
    SmpOverlay_SetSlotValue(g_characterSelectionMenu->slotOverlay, player, 1);
    g_characterSelectionMenu->players[player].tintFramesLeft = 1;
    for (i = 0; i < 3; i++) {
        Widget_SetWidgetFlag08(Node_FindWidgetByResourceId(g_characterSelectionMenu->screen, g_characterSelectionMenuOptionCells[player][i].id), 1);
    }
    g_characterSelectionMenu->players[player].kind = choice;
    Key_FindCharacterPreviewRow(choice);
    Preview_SetPreviewTransformUpdate(g_characterSelectionMenu->players[player].model, 0);

    count = 0;
    for (j = 0; j < 4; j++) {
        if (g_characterSelectionMenu->players[j].selectionState == 1 || g_characterSelectionMenu->players[j].selectionState == 2) {
            count++;
        }
    }
    if (count != 0) {
        return;
    }

    slot = g_gameSettingsView->roster;
    for (i = 0; i < 8; i++) {
        slot[i].active = 0;
        if (g_characterSelectionMenu->players[i].selectionState == 3) {
            slot[i].m_IsBot = 0;
            slot[i].active = 1;
            slot[i].m_nController = i;
            kind = Key_GetCharacterPreviewModel(g_characterSelectionMenu->players[i].kind);
            slot[i].m_nCharacter = kind;
            if (g_gameSettingsView->trialKind == 1) {
                g_profileCharacterSelections[i * 400] = kind;
            }
            slot[i].variant = (u8)g_characterSelectionMenu->players[i].choice;
        }
    }
    SmXlate_SwitchScreen(g_gameSettingsView->trialKind == 1 ? 10 : 8);
}

void Menu_RandomizeCharacterPreview(s32 player) {
    s32 tries;
    s32 done;
    s32 id;
    s32 kind;
    s32 index;
    s32 costumes;

    tries = 0;
    done = 0;
    do {
        id = g_frontendKeyEntries[Graphu64_NextRandom() % 17].id;
        if (Widget_ListHasFlag100(Node_FindWidgetByResourceId(g_characterSelectionMenu->screen, (u16)id)) == 0 && g_characterSelectionMenu->players[player].kind != id) {
            done = 1;
        } else if (++tries > 5000) {
#if defined(VERSION_DE)
            id = 144;
#elif defined(VERSION_EU_X)
            id = 150;
#else
            id = 146;
#endif
            done = 1;
        }
    } while (!done);
    g_characterSelectionMenu->players[player].kind = id;
    kind = Key_GetCharacterPreviewModel(id);
    index = Key_FindCharacterPreviewRow(g_characterSelectionMenu->players[player].kind);
    {
        CVector3 scale;
        scale.x = g_frontendKeyEntries[index].scale[player];
        scale.y = g_frontendKeyEntries[index].scale[player];
        scale.z = g_frontendKeyEntries[index].scale[player];
        Preview_InitModelPreview(g_characterSelectionMenu->players[player].model, 9, kind + 911, 75, 24000, scale,
                      g_frontendKeyEntries[index].m_vPos[player], g_frontendKeyEntries[index].m_fRotY[player],
                      g_frontendKeyEntries[index].flags[player]);
    }
    costumes = g_profileCharacterUnlockCounts[player][kind];
    if (costumes <= 0) {
        costumes = 1;
    }
    g_characterSelectionMenu->players[player].choice = Graphu64_NextRandom() % costumes;
}

s32 Menu_CountPendingCharacterSelections(void) {
    s32 count = 0;
    s32 i;

    for (i = 0; i < 4; i++) {
        if ((u32) (g_characterSelectionMenu->players[i].selectionState - 1) < 2) {
            count++;
        }
    }
    return count;
}

#if defined(VERSION_US)
char k_CharacterUnlocksEncodedWords[4] =
    "Y_1e";
#endif

#if defined(VERSION_EU_X)
unsigned int k_CharacterUnlocksEncodedWordsBlock2[1] = {
    0x0044333C,
};
#endif

#if defined(VERSION_EU)
unsigned int k_CharacterUnlocksEncodedWordsBlock3[1] = {
    0x01770178,
};
#endif

#if defined(VERSION_DE)
unsigned int k_CharacterUnlocksEncodedWordsBlock1[1] = {
    0x0042148C,
};
#endif
