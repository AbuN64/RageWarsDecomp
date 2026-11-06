#include "Rsp/random_direction_and_affine_math.h"
#include "include_asm.h"
#include "Common/video_dimensions.h"
#include "Common/Lone/hud_reference_viewport_height.h"
#include "Render/material_color_and_fog_views.h"
#include "Common/characterselectionroot.h"
#include "Common/sharedplayer.h"
#include "Common/selectionscreenstate.h"
#include <PR/gbi.h>
#include <platform_sdk.h>
#include "types.h"
#include "Frontend/widget_findwidgetatpoint.h"
#include "Frontend/frontend_drawmodelpreview.h"
#include "Common/shared_gameslot.h"
#include "Frontend/smp_overlay.h"
#include "Common/sharedtrackobjectprefix.h"
#include "Common/sessionhandlerrow.h"
#include "Common/runtime_declarations.h"
#include "Engine/defs.h"
#include "Common/shared_menureply.h"
#include "Menu/g_menuplayerscissorrects.h"
#include "Common/playerprofiles.h"
#include "World/playerprofile.h"
#include "Menu/selection.h"
#include "Menu/Character_unlocks/character_unlocks_symbols.h"
#include "Data/rest_source_records.h"
#include "data_overlay_layouts.h"
#include "Frontend/frontend.h"

#define g_gameSettingsView ((HudStatusShared_Settings *)&g_gameSettings)

#if defined(VERSION_DE)
enum { UNLOCK_MARK = 129 };
#elif defined(VERSION_EU_X)
enum { UNLOCK_MARK = 135 };
#else
enum { UNLOCK_MARK = 131 };
#endif

/* Enables character choices unlocked by active players and highlights the selected profile's unlocked characters. */
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
                    gDPSetScissor(g_displayListCursor++, G_SC_NON_INTERLACE, g_menuPlayerScissorRects[i].left, g_menuPlayerScissorRects[i].top, g_menuPlayerScissorRects[i].right, g_menuPlayerScissorRects[i].bottom);
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
            if (g_profileSlotIndices[j][0] >= 0) {
                found = found || Player_TestAchievementFlag7(&g_localPlayerProfiles[j], g_frontendKeyUnlockEntries[i].key);
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
        } else if (g_gameSettingsView->trialKind == 1 && Defs_TestBit(g_profileUnlockedTrialBits, g_frontendKeyUnlockEntries[i].key) == 1) {
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
extern char k_CharacterUnlocksEncodedWords[4];
#endif

#if defined(VERSION_EU_X)
extern unsigned int k_characterUnlocksFragment[1];
#endif

#if defined(VERSION_EU)
extern unsigned int k_characterUnlocksFragment[1];
#endif

#if defined(VERSION_DE)
extern unsigned int k_characterUnlocksFragment[1];
#endif
#undef g_gameSettingsView

#if defined(VERSION_US_REV1)
extern unsigned int g_characterUnlocksRetainedWord[1];
#endif

#if !(defined(VERSION_DE))
#if defined(VERSION_US_REV1)
float g_characterPreviewPositionTail[11] = {
    -60.0f, -100.0f, -40.0f, -60.0f,
    -100.0f, 29.0f, -95.0f, -70.0f,
    -29.0f, -95.0f, -70.0f,
};
#endif
#endif

#if defined(VERSION_US) || defined(VERSION_US_REV1)
#if defined(VERSION_US_REV1)
CharacterUnlocksPreviewConstantWordsRecord g_characterUnlocksPreviewConstantWords = {
    { 0, 0, -20, -20 },
};
#endif
#endif
#if defined(VERSION_US_REV1)
CharacterPreviewSlotRecord g_characterPreviewSlots[4] = {
    {
        { { 128, 13, 115, 52 } },
        134, 1,
        22,
        { 0.11f, 0.11f, 0.11f, 0.11f, 1.6e+02f, 2.0e+02f, 1.6e+02f, 2.1e+02f },
        { 41.0f, -37.0f, -1.0e+02f, -38.0f, -37.0f, -1.0e+02f, 34.0f, -74.0f, -8.0e+01f, -3.0e+01f, -74.0f, -8.0e+01f },
        { 0, 0, -15, -15 },
    },
    {
        { { 128, 13, 115, 56 } },
        145, 2,
        29,
        { 0.14f, 0.14f, 0.14f, 0.14f, 1.6e+02f, 195.0f, 1.6e+02f, 195.0f },
        { 4.0e+01f, -53.0f, -1.0e+02f, -4.0e+01f, -53.0f, -1.0e+02f, 32.0f, -91.0f, -8.0e+01f, -35.0f, -91.0f, -8.0e+01f },
        { 0, 0, -15, -15 },
    },
    {
        { { 128, 13, 115, 60 } },
        132, 3,
        26,
        { 0.065f, 0.065f, 0.065f, 0.065f, 1.6e+02f, 2.0e+02f, 1.6e+02f, 2.0e+02f },
        { 39.0f, -35.0f, -1.0e+02f, -39.0f, -35.0f, -1.0e+02f, 32.0f, -72.0f, -8.0e+01f, -32.0f, -72.0f, -8.0e+01f },
        { 20, 20, 0, 0 },
    },
    {
        { { 128, 13, 115, 64 } },
        135, 4,
        20,
        { 0.055f, 0.055f, 0.055f, 0.055f, 155.0f, 2.0e+02f, 1.6e+02f, 2.0e+02f },
        { 4.0e+01f, -35.0f, -1.0e+02f, -4.0e+01f, -35.0f, -1.0e+02f, 3.0e+01f, -72.0f, -8.0e+01f, -33.0f, -72.0f, -8.0e+01f },
        { 0, 0, -15, -15 },
    },
};
#endif

#if defined(VERSION_US_REV1)
OverlayScissorRect g_menuPlayerScissorRects[4] = {
    { 18, 15, 52, 94 }, { 232, 15, 267, 94 }, { 18, 128, 52, 206 }, { 232, 128, 267, 206 }
};
#endif

#if defined(VERSION_US_REV1)
struct {
    void * screen;
    s32 firstKind;
} g_selectionScreenAndInitialKind __attribute__((aligned(4))) = {
    0,
    146
};
typedef char g_selectionScreenAndInitialKindSizeCheck[(sizeof(g_selectionScreenAndInitialKind) == 8) ? 1 : -1];
#endif

/* Retained data for this translation unit. */
#if defined(VERSION_US)
char k_CharacterUnlocksEncodedWords[4] =
    "Y_1e";
#endif
#if defined(VERSION_EU_X)
unsigned int k_characterUnlocksFragment[1] = {
    0x0044333C,
};
#endif
#if defined(VERSION_EU)
unsigned int k_characterUnlocksFragment[1] = {
    0x01770178,
};
#endif
#if defined(VERSION_DE)
unsigned int k_characterUnlocksFragment[1] = {
    0x0042148C,
};
#endif
