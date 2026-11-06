#include "data_overlay_layouts.h"
#include "Engine/scene.h"
#include "Common/menu_options_and_results.h"
#include "Common/shared_gameslot.h"
#include "Common/measured.h"
#include "Common/unresolved_word_access_set.h"
#include "Common/unresolved_word_accesses.h"
#include "Common/aiprofile.h"
#include "Common/runtime_declarations.h"
#include "Common/argb_color.h"
#include "Common/math_helpers.h"
#include "Common/selectionscreenstate.h"
#include "Common/screen.h"
#include "Common/multiplayeroptions.h"
#include "Common/loadout.h"
#include "Common/virtual_pager.h"
#include "Common/group.h"
#include "Common/object_instance_transform_and_render_views.h"
#include "Common/manager.h"
#include "Common/cartridgereadworker.h"
#include "Common/audio_voice_slots.h"
#include "Common/soundvoicepool.h"
#include "Common/lightdata.h"
#include "Common/geometry_blend_and_instance_views.h"
#include "Common/mtx.h"
#include "Common/particle_attachment_and_owner_views.h"
#include "Common/colorentry.h"
#include "Common/worldsortentry.h"
#include "Common/results.h"
#include "Common/round_session.h"
#include "Common/menu_screen_elements.h"
#include "Common/hud_effects.h"
#include "Common/albank_s.h"
#include "Common/sequence_timing.h"
#include "Common/alparam_s.h"
#include "Common/audio_effect_chain.h"
#include "Common/ospihandle_s.h"
#include "include_asm.h"
#include "Common/video_dimensions.h"
#include "Common/Lone/hud_reference_viewport_height.h"
#include "Render/material_color_and_fog_views.h"
#include "types.h"
#include "Common/vector4f.h"
#include "Frontend/resultsoptionsscreen.h"
#include "Common/sharedtrackobjectprefix.h"
#include "Engine/defs.h"
#include "Results/results_updateresultsheading_data.h"
#include "Common/resultsoptionsscreen.h"
#include "Frontend/results_getweaponiconvalue.h"
#include "Pakinterfacescreen/ovl1_j.h"
#include "Frontend/frontend_address_symbols.h"
#include "Frontend/node_findwidgetbyresourceid.h"
#include "Common/access_s8_10f.h"
#include "options.h"
#include "Common/menulistscreen.h"
#include "Frontend/results_refreshtrialcataloguewidgets.h"
#include "Frontend/results_updateresultsheading.h"
#include "Frontend/results_fillprofileweaponrows.h"
#include "Frontend/ctrialcatalogue_showtrialoptionchildren.h"
#include "Render/soundelement_playflatsound.h"
#include "Scene/cache_freememory.h"
#include "Common/shared_menureply.h"
#include "Common/sharedplayer.h"
#include "Common/player_join_requests.h"
#include "Frontend/results_loadtrialcompletionflags.h"
#include "Frontend/frontend_drawmodelpreview.h"
#include "Common/gameplay_settings.h"
#include "Common/world.h"
#include "Common/Lone/g_languageindex.h"
#include "Common/scene_frame_and_effect_updates.h"
#include "Common/triple.h"
#include "Achieve/achieve.h"
#include "Frontend/results.h"
#include "Ui/X_files/x_plus.h"
#include "Ui/X_files/x_stdio.h"
#include "Frontend/key.h"
#include "Common/playerprofiles.h"
#include "Frontend/results_player_panels.h"
#include "Frontend/results_marklinkedtrialsavailable.h"
#include "Defs/defs.h"
#include "Common/sessionhandlerrow.h"
#include "Common/weapon_unlock_presets.h"
#include "Ovlgame/ovlgame_address_symbols.h"
#include "Scene/scene_findtrackedactors.h"
#include "X_files/x_plus.h"
#include "Widget/widget_findwidgetatpoint.h"
#include "Results/results_settrialweaponrow.h"
#include "Ai/playerprofile.h"
#include "Scene/scene_drawtransitioncoloroverlay.h"
#include "Common/shared_optionsscreen.h"
#include "Common/game_session.h"
#include "Common/match_settings.h"
#include "Common/pak_player_panel.h"
#include "Frontend/scenario_result_rows.h"
#include "Frontend/frontend_dispatchresultsevent.h"
#include "Frontend/pakinterface_setscreenphase.h"
#include "Common/weapon_screen_message_operations.h"
#include "Results/frontend_activateresultsaction.h"
#include "Frontend/menuimage.h"
#include "Menu/menu.h"

/* unit RESULTS_ANIMATERESULTSOPTIONSSCREEN.CPP */
#include <platform_sdk.h>
#include "Common/osviscale.h"
#include "Common/ctx.h"
#include "Common/audio_loaddecodedsamples.h"
#include "Common/cheatcode.h"
#include "Common/note_state.h"
#include "Common/frontend_video_mode.h"
#include "Common/archive_chunk_images.h"
#include "Common/texture.h"
#include "Common/label.h"
#include "Common/player_join_requests.h"
#include "Common/characterselectionroot.h"
#include "Common/menu_initializeoptionsscene.h"
#include "Common/weapon_unlock_presets.h"
#include "Common/resultsoptionsscreen.h"
#include "Common/match_settings.h"
#include "Common/menulistscreen.h"
#include "Common/menu_model_preview.h"
#include "Common/player_item_inventory.h"
#include "Common/objb.h"
#include "types.h"
#include "Frontend/results_refreshtrialcataloguewidgets.h"
#include "Frontend/results_fillprofileweaponrows.h"
#include "Frontend/results_loadtrialcompletionflags.h"
#include "Render/soundelement_playflatsound.h"
#include "Results/results_animateresultsoptionsscreen.h"
#include "Sm_xlate/SM_Xlate.h"
#include "Smp/smp_flicker.h"
#include "Tsmos/tsmos_activatecontrollerstate.h"
#include "Frontend/frontend_address_symbols.h"
#include "Frontend/resultsoptionsscreen.h"


s32 Results_AnimateResultsOptionsScreen(void *element, void *eventId, s32 delta) {
    s32 clock;

    if (g_selectionMessageReply.ready == 1) {
        g_selectionMessageReply.ready = 0;
        if (g_selectionMessageReply.value != -1) {
            g_trialCatalogueScreen->item->alpha = 90;
            MarkMenuEventHandled();
            SmXlate_SwitchScreen(g_selectionMessageReply.value);
            return 0;
        }
        g_trialCatalogueScreen->item->alpha = 0xFF;
        g_trialCatalogueScreen->state = 9;
    }
    switch (g_trialCatalogueScreen->state) {
    case 1:
        g_trialCatalogueScreen->leftPanel->x += (u16)g_trialCatalogueScreen->leftStep;
        g_trialCatalogueScreen->rightPanel->x -= (u16)g_trialCatalogueScreen->rightStep;
        if (--g_trialCatalogueScreen->slideFrames > 0) {
            break;
        }
        SoundElement_PlayFlatSound(3705);
        Widget_SetWidgetFlag08(g_trialCatalogueScreen->focusItem, 1);
        SmpFlicker_StartFlicker(g_trialCatalogueScreen->resource, 4);
        g_trialCatalogueScreen->state = 4;
        g_trialCatalogueScreen->slideFrames = 4;
        break;
    case 2:
        g_trialCatalogueScreen->leftPanel->x -= (u16)g_trialCatalogueScreen->leftStep;
        g_trialCatalogueScreen->rightPanel->x += (u16)g_trialCatalogueScreen->rightStep;
        if (--g_trialCatalogueScreen->slideFrames > 0) {
            break;
        }
        g_trialCatalogueScreen->state = 3;
        MarkMenuEventHandled();
        if (g_gameSettings.controllerMode == 4) {
            SmXlate_SwitchScreen(3);
        } else {
            SmXlate_SwitchScreen(7);
        }
        return 0;
    case 3:
        if (g_trialCatalogueScreen->wordA58 == 0) {
            Tsmos_ActivateControllerState();
            g_trialCatalogueScreen->wordA58 = 1;
        }
        break;
    case 4:
        g_trialCatalogueScreen->slideFrames = RW_CLAMP(g_trialCatalogueScreen->slideFrames - 1, 0, g_trialCatalogueScreen->slideFrames);
        if (g_trialCatalogueScreen->slideFrames <= 0 && SmpFlicker_IsFlickerIdle(g_trialCatalogueScreen->resource) != 0) {
            SmpFlicker_RestoreFlickerValue(g_trialCatalogueScreen->resource);
            g_trialCatalogueScreen->state = 3;
        }
        break;
    case 5:
        SoundElement_PlayFlatSound(3704);
        Widget_SetWidgetFlag08(g_trialCatalogueScreen->focusItem, 0);
        switch (g_gameSettings.controllerMode) {
        case 1:
        case 3:
        case 4:
            Results_ShowTrialPreviewBanner();
        }
        Results_HideTrialCatalogueWidgets();
        g_trialCatalogueScreen->state = 2;
        g_trialCatalogueScreen->slideFrames = 4;
        break;
    case 8:
        g_trialCatalogueScreen->state = 3;
        Results_HideTrialCatalogueWidgets();
        Random_SetMenuChoiceResult(11);
        return 0;
    case 9:
        g_trialCatalogueScreen->state = 3;
        Results_LoadTrialCompletionFlags();
        break;
    }
    if (g_trialCatalogueScreen->state == 3) {
        clock = g_trialCatalogueScreen->clock + delta;
        g_trialCatalogueScreen->clock = clock;
        if (g_selectionMessageReply.value == -1) {
            g_trialCatalogueScreen->window->alpha = (u32)(Math_Cosf(clock * 0.005f) * 100.0f + 150.0f);
        }
    }
    return 0;
}

/* unit RESULTS_RENDERRESULTSOPTIONSPREVIEW.CPP */
#include <PR/gbi.h>
#include <platform_sdk.h>
#include "Common/sessionhandlerrow.h"
#include "Common/menu_screen_elements.h"
#include "Common/resultsoptionsscreen.h"
#include "Frontend/results_refreshtrialcataloguewidgets.h"
#include "Frontend/results_loadtrialcompletionflags.h"
#include "Frontend/results.h"
#include "Results/results_renderresultsoptionspreview.h"
#include "Menu/g_menuplayerscissorrects.h"
#include "Preview/frontend_drawmodelpreview.h"
#include "Defs/defs.h"
#include "Common/playerprofiles.h"

/* Draw callback of the results screen g_trialCatalogueScreen: on draw event 1 in states 3, 8 or 9 it resets
   the fill colour g_menuModelFillEnabled to opaque white, and for each of the one or two viewports clips the
   display list to its rectangle in g_menuPlayerScissorRects (0, then 2 for the lower view), draws the player's panel through Preview_DrawModelPreview and restores the
   full-screen clip. Outside two-player mode (and unless GetMenuScreenOwner reports 0x19) it plays sound
   0x259 past the base at 0xA44 on the twentieth frame, raises the banner blink after six more
   frames, and fades the two banner sprites out by 30 per frame before hiding them. Returns zero. */

/* Loads the stage list of the results screen g_trialCatalogueScreen: clears its two 36-bit sets at 0xA74 and
   0xA79, copies into the first the 36 cleared-stage bits that the player record g_localPlayerProfiles[index at
   0xA5C] keeps for the current mode g_gameControllerMode (at 0x7E, 0x83, 0x88 or 0x8D for modes 1 to 4), and
   refreshes the list through Results_RefreshTrialCatalogueWidgets. */


s32 Results_RenderResultsOptionsPreview(void *element, void *eventId, s32 event) {
    s32 views;
    s32 i;
    s32 alpha;
    s32 k;

    if (event == 1 && (g_trialCatalogueScreen->state == 3 || g_trialCatalogueScreen->state == 8 || g_trialCatalogueScreen->state == 9)) {
        g_menuModelFillEnabled = 0;
        g_menuModelFillColor[0] = 255.0f;
        g_menuModelFillColor[1] = 255.0f;
        g_menuModelFillColor[2] = 255.0f;
        g_menuModelFillColor[3] = 255.0f;
        views = 1;
        if (g_gameSettings.controllerMode == 2) {
            views = 2;
        }
        for (i = 0, k = 0; i < views; i++, k = 2) {
            gDPSetScissor(g_displayListCursor++, G_SC_NON_INTERLACE, g_menuPlayerScissorRects[k].left, g_menuPlayerScissorRects[k].top, g_menuPlayerScissorRects[k].right, g_menuPlayerScissorRects[k].bottom);
            Preview_DrawModelPreview(g_trialCatalogueScreen->panels[i]);
            gDPSetScissor(g_displayListCursor++, G_SC_NON_INTERLACE, 0, 0, SCREEN_WD - 1, SCREEN_HT - 1);
        }
        if (g_gameSettings.controllerMode != 2 && GetMenuScreenOwner() != 25) {
            if (g_trialCatalogueScreen->frames < 20) {
                if (++g_trialCatalogueScreen->frames == 20) {
                    k = g_trialCatalogueScreen->selection;
                    Menu_SetOptionsSceneSelection(k + 601);
                    g_trialCatalogueScreen->blinkDelay = 0;
                }
            }
            if (g_trialCatalogueScreen->blinkDelay != -1) {
                if (++g_trialCatalogueScreen->blinkDelay >= 6) {
                    g_trialCatalogueScreen->blinking = 1;
                    g_trialCatalogueScreen->blinkDelay = -1;
                }
            }
            if (g_trialCatalogueScreen->blinking == 1) {
                alpha = g_trialCatalogueScreen->banner->alpha;
                alpha -= 30;
                if (alpha <= 0) {
                    g_trialCatalogueScreen->blinking = 0;
                    Widget_SetWidgetFlag08(g_trialCatalogueScreen->bannerShadow, 0);
                    Widget_SetWidgetFlag08(g_trialCatalogueScreen->banner, 0);
                    alpha = 0xFF;
                }
                g_trialCatalogueScreen->banner->alpha = alpha;
                g_trialCatalogueScreen->bannerShadow->alpha = alpha;
            }
        }
    }
    return 0;
}

void Results_LoadTrialCompletionFlags(void) {
    s32 i;

    i = 0;
    do {
        Defs_SetBitValue(g_trialCatalogueScreen->owned, i, 0);
        Defs_SetBitValue(g_trialCatalogueScreen->pending, i, 0);
        i++;
    } while (i < 36);
    switch (g_gameSettings.controllerMode) {
    case 1:
        i = 0;
        do {
            Defs_SetBitValue(g_trialCatalogueScreen->owned, i, Defs_TestBit(g_localPlayerProfiles[0].levelFlags[0] + g_trialCatalogueScreen->player * sizeof(g_localPlayerProfiles[0]), i));
            i++;
        } while (i < 36);
        break;
    case 2:
        i = 0;
        do {
            Defs_SetBitValue(g_trialCatalogueScreen->owned, i, Defs_TestBit(g_localPlayerProfiles[0].levelFlags[1] + g_trialCatalogueScreen->player * sizeof(g_localPlayerProfiles[0]), i));
            i++;
        } while (i < 36);
        break;
    case 3:
        i = 0;
        do {
            Defs_SetBitValue(g_trialCatalogueScreen->owned, i, Defs_TestBit(g_localPlayerProfiles[0].levelFlags[2] + g_trialCatalogueScreen->player * sizeof(g_localPlayerProfiles[0]), i));
            i++;
        } while (i < 36);
        break;
    case 4:
        i = 0;
        do {
            Defs_SetBitValue(g_trialCatalogueScreen->owned, i, Defs_TestBit(g_localPlayerProfiles[0].levelFlags[3] + g_trialCatalogueScreen->player * sizeof(g_localPlayerProfiles[0]), i));
            i++;
        } while (i < 36);
        break;
    }
    Results_RefreshTrialCatalogueWidgets();
}


/* Backtracking search over the 36 unlock nodes of g_trialCatalogueStages: while any node is still set in the
   remaining bit set, appends to the -1-terminated path the first remaining node linked to the
   path's last node, clears its bit and recurses, undoing the step when the recursion fails. Every
   exit returns one, so the first linked choice at each depth is always kept. */
s32 Results_FindUnlockPath(u8 *remaining, s32 *path) {
    s32 anyLeft;
    s32 node;
    s32 last;
    s32 linked;

    anyLeft = 0;
    node = 0;
    do {
        if (Defs_TestBit(remaining, node) == 1) {
            anyLeft = 1;
        }
        node++;
    } while (node < 36 && anyLeft == 0);
    if (anyLeft != 0) {
        last = 0;
        while (path[last] != -1) {
            last++;
        }
        last--;
        node = 0;
        while (node < 36) {
            if (Defs_TestBit(remaining, node) == 0) {
                node++;
            } else {
                linked = Results_IsUnlockLinked(g_trialCatalogueStages[path[last]].id, g_trialCatalogueStages[node].id);
                if (linked == 1) {
                    last++;
                    path[last] = node;
                    path[last + 1] = -1;
                    Defs_SetBitValue(remaining, node, 0);
                    if (Results_FindUnlockPath(remaining, path) == linked) {
                        return 1;
                    }
                    Defs_SetBitValue(remaining, node, 1);
                    path[last] = -1;
                    last--;
                }
                node++;
            }
        }
    }
    return 1;
}

/* unit RESULTS_UPDATERESULTSHEADING_DATA.CPP */
#if !(defined(VERSION_US_REV1))
const char g_characterAndTimeFormatText[27] =
    "[CHARACTER]\000%d:%02d\000[TIME]\000";
#endif

#if defined(VERSION_US_REV1)
const char k_ResultsUpdateresultsheadingEncodedBytes[27] =
    "[CHARACTER]\000%d:%02d\000[TIME]";
#endif

/* unit RESULTS_SETTRIALWEAPONROW.CPP */
/* Finds a menu item identifier in three selection tables, falling back to the first item of the second table. */
void Results_SetTrialWeaponRow(u32 row, s32 weaponId, s32 amount) {
    s32 id;
    MenuWidget *element;
    MenuWidget *field;
    s32 value;

    switch (row) {
    case 0:
        id = 479 + ID_SHIFT;
        if (amount == 0) {
            id = 329 + OPTION_SHIFT;
        }
        break;
    case 1:
        id = 480 + ID_SHIFT;
        if (amount == 0) {
            id = 332 + OPTION_SHIFT;
        }
        break;
    case 2:
        id = 481 + ID_SHIFT;
        if (amount == 0) {
            id = 333 + OPTION_SHIFT;
        }
        break;
    case 3:
        id = 482 + ID_SHIFT;
        if (amount == 0) {
            id = 334 + OPTION_SHIFT;
        }
        break;
    case 4:
        id = 483 + ID_SHIFT;
        if (amount == 0) {
            id = 335 + OPTION_SHIFT;
        }
        break;
    default:
        id = 329 + OPTION_SHIFT;
        break;
    }
    element = (MenuWidget *) Node_FindWidgetByResourceId(g_trialCatalogueScreen->root, id);
    Widget_SetWidgetFlag08(Node_FindWidgetByResourceId(element, 331 + OPTION_SHIFT), 0);
    value = Results_GetWeaponIconValue(weaponId);
    field = (MenuWidget *) Node_FindWidgetByResourceId(element, 330 + OPTION_SHIFT);
    field->alpha = 100;
    field->value = value;
}

int Results_GetWeaponIconValue(int id) {
 int i;
 for(i=0;i<8;i++) if(g_loadoutWeaponIds[i*4]==id) return g_loadoutWeaponItems[i].resource;
 for(i=0;i<4;i++) if(g_trialBonusWeaponIds[i*4]==id) return g_loadoutBonusWeaponItems[i*4];
 for(i=0;i<3;i++) if(g_trialSpecialWeaponIds[i*4]==id) return g_loadoutSpecialWeaponItems[i*4];
 return g_loadoutBonusWeaponItems[0];
}

/* unit CTRIALCATALOGUE_SHOWTRIALOPTIONCHILDREN.CPP */
#define g_gameSettingsView ((u8 *)&g_gameSettings)

#if defined(VERSION_DE)
enum { RESULTS_OPTION_329 = 327, RESULTS_OPTION_331 = 329, RESULTS_OPTION_332 = 330, RESULTS_OPTION_333 = 331, RESULTS_OPTION_334 = 332, RESULTS_OPTION_335 = 333 };
#elif defined(VERSION_EU_X)
enum { RESULTS_OPTION_329 = 333, RESULTS_OPTION_331 = 335, RESULTS_OPTION_332 = 336, RESULTS_OPTION_333 = 337, RESULTS_OPTION_334 = 338, RESULTS_OPTION_335 = 339 };
#else
enum { RESULTS_OPTION_329 = 329, RESULTS_OPTION_331 = 331, RESULTS_OPTION_332 = 332, RESULTS_OPTION_333 = 333, RESULTS_OPTION_334 = 334, RESULTS_OPTION_335 = 335 };
#endif

/* The window table stores word-valued resource identifiers: the key is the word cast to 16 bits. The halfword at
   word+2 (the table symbol g_trialCatalogueStageIdLowHalves) is only its low half on big-endian MIPS. */
#define entryWindowKey(index) ((u16)g_trialCatalogueStages[index].id)



/* Opens the five option windows of screen g_trialCatalogueScreen: for each of options 0 to 4 it picks window
   0x149, 0x14C, 0x14D, 0x14E or 0x14F through k_trialOptionWindowIdJumpTable, opens it under the screen's parent at
   0x970, opens its 0x14B child and shows that through Widget_SetWidgetFlag08_EquipActivateequipmentpanel. The loop walks the table with
   its own pointer, as the cartridge's strength-reduced dispatch does. */
void CTrialCatalogue_ShowTrialOptionChildren(void) {
    s32 id = 0;
    s32 option;

    for (option = 0; option < 5; option++) {
        switch (option) {
        case 0:
            id = RESULTS_OPTION_329;
            break;
        case 1:
            id = RESULTS_OPTION_332;
            break;
        case 2:
            id = RESULTS_OPTION_333;
            break;
        case 3:
            id = RESULTS_OPTION_334;
            break;
        case 4:
            id = RESULTS_OPTION_335;
            break;
        }
        Widget_SetWidgetFlag08(Node_FindWidgetByResourceId(Node_FindWidgetByResourceId(g_trialCatalogueScreen->parent, id), RESULTS_OPTION_331), 1);
    }
}

/* Releases the object g_trialCatalogueScreen holds through Cache_FreeMemory, calls Tsmos_ActivateControllerState, clears g_trialCatalogueScreen, calls
   Cinema_ReleaseSequenceContext_FrontendHandletaboptionsshortcut and returns zero. */
s32 CTrialCatalogue_CloseTrialOptionsScreen(void) {
    Cache_FreeMemory(g_trialCatalogueScreen);
    Tsmos_ActivateControllerState();
    g_trialCatalogueScreen = 0;
    Cinema_ReleaseSequenceContext();
    return 0;
}

/* On event 3 with value 0, calls MarkMenuEventHandled, sets the word at offset 0x988 of the object
   g_trialCatalogueScreen points to to 8 and the byte at 0x10 of its item at 0xA50 to 0x5A, and plays sound
   0xE7C through SoundElement_PlayFlatSound. Returns zero. */
s32 CTrialCatalogue_HandleTrialOptionRelease(void *first, void *second, u32 event, s32 value) {
    ResultsOptionsScreen *state;

    if ((event >> 16) == 3 && value == 0) {
        MarkMenuEventHandled();
        state = g_trialCatalogueScreen;
        state->state = 8;
        state->item->alpha = 90;
        SoundElement_PlayFlatSound(3708);
    }
    return 0;
}

/* Moves the menu cursor on event 1: when the current slot's successor in the 28-byte slot table
   (word at g_trialCatalogueNeighbors[1]) exists and Defs_TestBit reports it set in the menu's flags at 0xA74, it
   plays sound 0xE7D, shades the old window 0x46 or 0xAA by whether the old slot is set in the
   flags at 0xA79, opens the successor's window (halfword at g_trialCatalogueStageIdLowHalves) under parent, refreshes
   through Results_RefreshTrialSelectionLabel and, by the mode byte at 0xD of g_gameSettings, through Results_ShowTrialPreviewBanner and
   Results_UpdateResultsHeading unless the mode is 2 and Results_RefreshTrialCharacterPreview when it is 4; returns zero. */
s32 CTrialCatalogue_SelectNeighborAbove(void *parent, s32 eventId, s32 eventPayload, s32 event) {
    s32 next;
    s32 set;
    u8 *options;

    MarkMenuEventHandled();
    if (event != 1) {
        return 0;
    }
    next = g_trialCatalogueNeighbors[1][g_trialCatalogueScreen->selection * 7];
    if (next == -1) {
        return 0;
    }
    set = Defs_TestBit(g_trialCatalogueScreen->owned, next);
    if (set != 1) {
        return 0;
    }
    SoundElement_PlayFlatSound(3709);
    if (Defs_TestBit(g_trialCatalogueScreen->pending, g_trialCatalogueScreen->selection) == set) {
        g_trialCatalogueScreen->window->alpha = 70;
    } else {
        g_trialCatalogueScreen->window->alpha = 170;
    }
    g_trialCatalogueScreen->selection = next;
    g_trialCatalogueScreen->window = Node_FindWidgetByResourceId(parent, entryWindowKey(next));
    Results_RefreshTrialSelectionLabel();
    options = g_gameSettingsView;
    if (options[13] != 2) {
        Results_ShowTrialPreviewBanner();
        g_trialCatalogueScreen->frames = 0;
        Results_UpdateResultsHeading();
    }
    if (options[13] == 4) {
        Results_RefreshTrialCharacterPreview();
    }
    return 0;
}

/* Moves the menu cursor on event 1: when the current slot's successor in the 28-byte slot table
   (word at g_trialCatalogueNeighbors[2]) exists and Defs_TestBit reports it set in the menu's flags at 0xA74, it
   plays sound 0xE7D, shades the old window 0x46 or 0xAA by whether the old slot is set in the
   flags at 0xA79, opens the successor's window (halfword at g_trialCatalogueStageIdLowHalves) under parent, refreshes
   through Results_RefreshTrialSelectionLabel and, by the mode byte at 0xD of g_gameSettings, through Results_ShowTrialPreviewBanner and
   Results_UpdateResultsHeading unless the mode is 2 and Results_RefreshTrialCharacterPreview when it is 4; returns zero. */
s32 CTrialCatalogue_SelectNeighborBelow(void *parent, s32 eventId, s32 eventPayload, s32 event) {
    s32 next;
    s32 set;
    u8 *options;

    MarkMenuEventHandled();
    if (event != 1) {
        return 0;
    }
    next = g_trialCatalogueNeighbors[2][g_trialCatalogueScreen->selection * 7];
    if (next == -1) {
        return 0;
    }
    set = Defs_TestBit(g_trialCatalogueScreen->owned, next);
    if (set != 1) {
        return 0;
    }
    SoundElement_PlayFlatSound(3709);
    if (Defs_TestBit(g_trialCatalogueScreen->pending, g_trialCatalogueScreen->selection) == set) {
        g_trialCatalogueScreen->window->alpha = 70;
    } else {
        g_trialCatalogueScreen->window->alpha = 170;
    }
    g_trialCatalogueScreen->selection = next;
    g_trialCatalogueScreen->window = Node_FindWidgetByResourceId(parent, entryWindowKey(next));
    Results_RefreshTrialSelectionLabel();
    options = g_gameSettingsView;
    if (options[13] != 2) {
        Results_ShowTrialPreviewBanner();
        g_trialCatalogueScreen->frames = 0;
        Results_UpdateResultsHeading();
    }
    if (options[13] == 4) {
        Results_RefreshTrialCharacterPreview();
    }
    return 0;
}

/* Moves the menu cursor on event 1: when the current slot's successor in the 28-byte slot table
   (word at g_trialCatalogueNeighbors[0]) exists and Defs_TestBit reports it set in the menu's flags at 0xA74, it
   plays sound 0xE7D, shades the old window 0x46 or 0xAA by whether the old slot is set in the
   flags at 0xA79, opens the successor's window (halfword at g_trialCatalogueStageIdLowHalves) under parent, refreshes
   through Results_RefreshTrialSelectionLabel and, by the mode byte at 0xD of g_gameSettings, through Results_ShowTrialPreviewBanner and
   Results_UpdateResultsHeading unless the mode is 2 and Results_RefreshTrialCharacterPreview when it is 4; returns zero. */
s32 CTrialCatalogue_SelectNeighborLeft(void *parent, s32 eventId, s32 eventPayload, s32 event) {
    s32 next;
    s32 set;
    u8 *options;

    MarkMenuEventHandled();
    if (event != 1) {
        return 0;
    }
    next = g_trialCatalogueNeighbors[0][g_trialCatalogueScreen->selection * 7];
    if (next == -1) {
        return 0;
    }
    set = Defs_TestBit(g_trialCatalogueScreen->owned, next);
    if (set != 1) {
        return 0;
    }
    SoundElement_PlayFlatSound(3709);
    if (Defs_TestBit(g_trialCatalogueScreen->pending, g_trialCatalogueScreen->selection) == set) {
        g_trialCatalogueScreen->window->alpha = 70;
    } else {
        g_trialCatalogueScreen->window->alpha = 170;
    }
    g_trialCatalogueScreen->selection = next;
    g_trialCatalogueScreen->window = Node_FindWidgetByResourceId(parent, entryWindowKey(next));
    Results_RefreshTrialSelectionLabel();
    options = g_gameSettingsView;
    if (options[13] != 2) {
        Results_ShowTrialPreviewBanner();
        g_trialCatalogueScreen->frames = 0;
        Results_UpdateResultsHeading();
    }
    if (options[13] == 4) {
        Results_RefreshTrialCharacterPreview();
    }
    return 0;
}

/* Moves the menu cursor on event 1: when the current slot's successor in the 28-byte slot table
   (word at g_trialCatalogueNeighborZero) exists and Defs_TestBit reports it set in the menu's flags at 0xA74, it
   plays sound 0xE7D, shades the old window 0x46 or 0xAA by whether the old slot is set in the
   flags at 0xA79, opens the successor's window (halfword at g_trialCatalogueStageIdLowHalves) under parent, refreshes
   through Results_RefreshTrialSelectionLabel and, by the mode byte at 0xD of g_gameSettings, through Results_ShowTrialPreviewBanner and
   Results_UpdateResultsHeading unless the mode is 2 and Results_RefreshTrialCharacterPreview when it is 4; returns zero. */
s32 CTrialCatalogue_SelectNeighborRight(void *parent, s32 eventId, s32 eventPayload, s32 event) {
    s32 next;
    s32 set;
    u8 *options;

    MarkMenuEventHandled();
    if (event != 1) {
        return 0;
    }
    next = g_trialCatalogueNeighborZero[g_trialCatalogueScreen->selection * 7];
    if (next == -1) {
        return 0;
    }
    set = Defs_TestBit(g_trialCatalogueScreen->owned, next);
    if (set != 1) {
        return 0;
    }
    SoundElement_PlayFlatSound(3709);
    if (Defs_TestBit(g_trialCatalogueScreen->pending, g_trialCatalogueScreen->selection) == set) {
        g_trialCatalogueScreen->window->alpha = 70;
    } else {
        g_trialCatalogueScreen->window->alpha = 170;
    }
    g_trialCatalogueScreen->selection = next;
    g_trialCatalogueScreen->window = Node_FindWidgetByResourceId(parent, entryWindowKey(next));
    Results_RefreshTrialSelectionLabel();
    options = g_gameSettingsView;
    if (options[13] != 2) {
        Results_ShowTrialPreviewBanner();
        g_trialCatalogueScreen->frames = 0;
        Results_UpdateResultsHeading();
    }
    if (options[13] == 4) {
        Results_RefreshTrialCharacterPreview();
    }
    return 0;
}

/* Calls MarkMenuEventHandled and Results_HideTrialCatalogueWidgets, passes the two words after the identifier in the
   28-byte entry g_trialCatalogueScreen's selection at 0xA44 picks from g_trialCatalogueStages to Random_SetSelectedStage, then
   calls Random_SetMenuChoiceResult with 0x19. Returns zero. */
s32 CTrialCatalogue_ExitTrialCatalogue(void) {
    MarkMenuEventHandled();
    Results_HideTrialCatalogueWidgets();
    Random_SetMenuChoiceResult(14);
    return 0;
}

s32 CTrialCatalogue_ConfirmTrialStage(void) {
    s32 selection;

    MarkMenuEventHandled();
    Results_HideTrialCatalogueWidgets();
    selection = g_trialCatalogueScreen->selection;
    Random_SetSelectedStage(g_trialCatalogueStages[selection].first, g_trialCatalogueStages[selection].second);
    Random_SetMenuChoiceResult(25);
    return 0;
}

/* Calls the handler registered for event (tables g_trialCatalogueEventIds, g_trialCatalogueEventKinds, g_trialCatalogueEventHandlers). A row matches when its event equals event and its kind equals the actor's kind or is the any-kind wildcard 0x7530. Returns the handler's result, or zero when no row matches. */
s32 CTrialCatalogue_DispatchCatalogueEvent(void *eventObject, s32 eventId, s32 eventPayload, s32 eventValue, s32 eventExtra) {
    TrialCatalogueEventHandlerFn *entry;
    s32 index;
    s32 wildcard;
    s32 actor_kind;
    s32 table_kind;
    MenuWidget *actor;

    if (g_trialCatalogueEventHandlers != 0) {
        wildcard = 30000;
        entry = &g_trialCatalogueEventHandlers;
        index = 0;
        do {
            if (g_trialCatalogueEventIds[index].value == eventId) {
                actor = eventObject;
                actor_kind = actor->resource;
                table_kind = g_trialCatalogueEventKinds[index].value;
                if ((table_kind == actor_kind) || (table_kind == wildcard)) {
                    return (*entry)(eventObject, eventId, eventPayload, eventValue, eventExtra);
                }
            }
            entry += 3;
            index++;
        } while (*entry != 0);
    }
    return 0;
}

/* Calls the handler registered for event (tables g_trialOptionsEventIds, g_trialOptionsEventKinds, g_trialOptionsEventHandlers). A row matches when its event equals event and its kind equals the actor's kind or is the any-kind wildcard 0x7530. Returns the handler's result, or zero when no row matches. */
s32 CTrialCatalogue_DispatchOptionsEvent(void *eventObject, s32 eventId, s32 eventPayload, s32 eventValue, s32 eventExtra) {
    TrialOptionsEventHandlerFn *entry;
    s32 index;
    s32 wildcard;
    s32 actor_kind;
    s32 table_kind;
    struct MenuWidget *actor;

    if (g_trialOptionsEventHandlers != 0) {
        wildcard = 30000;
        entry = &g_trialOptionsEventHandlers;
        index = 0;
        do {
            if (g_trialOptionsEventIds[index].value == eventId) {
                actor = eventObject;
                actor_kind = actor->resource;
                table_kind = g_trialOptionsEventKinds[index].value;
                if ((table_kind == actor_kind) || (table_kind == wildcard)) {
                    return (*entry)(eventObject, eventId, eventPayload, eventValue, eventExtra);
                }
            }
            entry += 3;
            index++;
        } while (*entry != 0);
    }
    return 0;
}

/* unit RESULTS_CREATERESULTSOPTIONSSCREEN.CPP */
/* The resource ids of this screen are numbered per version: de two lower than us, eu-x four higher
   (the same 11 ids at 19 sites, checked word by word against each ROM). */
static inline s32 resultsRes(s32 id) {
#if defined(VERSION_DE)
    return id - 2;
#elif defined(VERSION_EU_X)
    return id + 4;
#else
    return id;
#endif
}

#if defined(VERSION_US) || defined(VERSION_US_REV1) || defined(VERSION_EU) || defined(VERSION_DE) || defined(VERSION_EU_X)
#include "Common/runtime_declarations.h"
#include "Common/resident_event_handler.h"
#include "Common/shared_menureply.h"
#include "Common/animation.h"
#include "Common/menu_overlay.h"
#include "Common/menu_initializeoptionsscene.h"
#include "Common/resultsoptionsscreen.h"
#include "types.h"
#include "Render/soundelement_playflatsound.h"
#include "Frontend/smp_overlay.h"
#include "Results/results_createresultsoptionsscreen.h"
#include "Frontend/frontend_address_symbols.h"
void Defs_SetBitValue(u8 *bits, s32 bitIndex, s32 found);
void Results_SelectSuggestedTrial(void);
void Frontend_InitMenuImage(s32 *record, s32 first, s32 second, s32 third, s32 fourth);

/* The option block at g_gameOptions: its byte 5 is the screen mode, also read as g_gameControllerMode elsewhere. */
struct GameOptions {
    s32 word0;
    u8 byte4;
    u8 mode;
};
/* Builds the results options screen into g_trialCatalogueScreen: slides its two side panels in over four frames,
   finds the first active player, clears the pending flags of the eight status records, and runs the
   per-mode setup selected by the option byte. Returns zero. */
s32 Results_CreateResultsOptionsScreen(MenuWidget *rootWidget) {
    ResultsOptionsScreen *screen;
    s32 i;
    s32 d;
    s32 mode;
    MenuWidget *wLeft;
    MenuWidget *wRight;
    MenuWidget *wHead;
    MenuWidget *wItem;
    screen = Cache_AllocateMemory(2688);
    g_trialCatalogueScreen = screen;
    screen->root = rootWidget;
    g_trialCatalogueScreen->nodes = SmpOverlay_CreateOverlayNode(rootWidget, 4);
    SmpOverlay_ShowSlotById(rootWidget, 0, resultsRes(318));
    SmpOverlay_ShowSlotById(rootWidget, 1, resultsRes(318));
    SmpOverlay_ShowSlotById(rootWidget, 2, resultsRes(318));
    SmpOverlay_ShowSlotById(rootWidget, 3, resultsRes(318));
    for (i = 0; i < 36; i++) {
        Defs_SetBitValue(g_trialCatalogueScreen->owned, i, 0);
        Defs_SetBitValue(g_trialCatalogueScreen->pending, i, 0);
    }
    g_trialCatalogueScreen->state = 1;
    g_trialCatalogueScreen->slideFrames = 4;
    wLeft = Node_FindWidgetByResourceId(rootWidget, resultsRes(325));
    g_trialCatalogueScreen->leftPanel = wLeft;
    wLeft->x -= wLeft->width;
    g_trialCatalogueScreen->leftStep = g_trialCatalogueScreen->leftPanel->width / 4;
    d = g_trialCatalogueScreen->leftPanel->width - g_trialCatalogueScreen->leftStep * 4;
    g_trialCatalogueScreen->leftPanel->x += d;
    wRight = Node_FindWidgetByResourceId(rootWidget, resultsRes(324));
    g_trialCatalogueScreen->rightPanel = wRight;
    wRight->x += wRight->width;
    g_trialCatalogueScreen->rightStep = g_trialCatalogueScreen->rightPanel->width / 4;
    d = g_trialCatalogueScreen->rightPanel->width - g_trialCatalogueScreen->rightStep * 4;
    g_trialCatalogueScreen->rightPanel->x -= d;
    g_trialCatalogueScreen->resource = SmpFlicker_CreateFlickerWidget(resultsRes(321), 110);
    wHead = Node_FindWidgetByResourceId(rootWidget, resultsRes(319));
    g_trialCatalogueScreen->focusItem = wHead;
    Widget_SetWidgetFlag08(wHead, 0);
    g_trialCatalogueScreen->owner = (void *)Node_FindWidgetByResourceId(rootWidget, resultsRes(340));
    g_trialCatalogueScreen->item155 = Node_FindWidgetByResourceId(rootWidget, resultsRes(341));
    g_trialCatalogueScreen->player = 0;
    for (i = 0; i < 4; i++) {
        if (((struct Status *)g_playerSettings)[i].active == 1) {
            g_trialCatalogueScreen->player = i;
            break;
        }
    }
    for (i = 0; i < 8; i++) {
        if (((struct Status *)g_playerSettings)[i].pendingClear == 1) {
            ((struct Status *)g_playerSettings)[i].active = 0;
            ((struct Status *)g_playerSettings)[i].pendingClear = 0;
        }
    }
    Results_LoadTrialCompletionFlags();
    Results_SelectSuggestedTrial();
    g_trialCatalogueScreen->window = Node_FindWidgetByResourceId(rootWidget, (u16)g_trialCatalogueStages[g_trialCatalogueScreen->selection].id);
    Results_RefreshTrialSelectionLabel();
    g_selectionMessageReply.ready = 0;
    g_selectionMessageReply.value = -1;
    Frontend_InitMenuImage((s32 *)g_trialCatalogueScreen, 103, 0, 0, 0);
    wItem = Node_FindWidgetByResourceId(rootWidget, resultsRes(337));
    g_trialCatalogueScreen->item = wItem;
    wItem->alpha = 0xFF;
    g_trialCatalogueScreen->modeFlag = 0;
    mode = g_gameOptions.mode;
    if (mode < 5) {
        if (mode >= 3) {
            g_trialCatalogueScreen->modeFlag = 1;
            Results_RefreshTrialCharacterPreview(g_trialCatalogueScreen);
        }
    }
    g_trialCatalogueScreen->blinking = 0;
    g_trialCatalogueScreen->frames = 0;
    g_trialCatalogueScreen->blinkDelay = -1;
    switch (g_gameOptions.mode) {
    case 1:
    case 3:
    case 4:
        g_trialCatalogueScreen->bannerShadow = Node_FindWidgetByResourceId(rootWidget, resultsRes(317));
        Menu_InitializeOptionsScene();
        g_trialCatalogueScreen->banner = Node_FindWidgetByResourceId(rootWidget, resultsRes(327));
        Node_FindWidgetByResourceId(rootWidget, resultsRes(328))->alpha = 110;
        break;
    case 2:
        break;
    }
    switch (g_gameOptions.mode) {
    case 1:
        Results_FillProfileWeaponRows();
        break;
    case 3:
        Results_FillSelectedPlayerWeaponRows();
        break;
    case 2:
        Results_FillTwoPlayerWeaponRows();
        break;
    }
    if (g_gameOptions.mode != 2) {
        Results_UpdateResultsHeading();
    }
    SoundElement_PlayFlatSound(3704);
    return 0;
}
#endif

/* Shows the models of the first two active players on the results screen: switches the controller
   state over, then for each active player looks up the player's portrait record from the player's
   kind and starts a model preview in the next preview slot of the screen. The first model uses
   layout 0 of the record and the second layout 2 (uniform scale, position, distance and light).
   Returns zero. */
s32 Results_ShowResultsPlayerModels(void) {
    s32 shown;
    s32 layout;
    s32 previewOffset;
    s32 row;
    s32 i;
    CVector3 scale;
    struct Status *status;
    s32 statusOffset;

    Tsmos_SetMenuModelFlag(1);
    Tsmos_DeactivateControllerState();
    shown = 0;
    layout = 0;
    i = 0;
    statusOffset = 0;
    previewOffset = 32;
    g_trialCatalogueScreen->wordA58 = 0;
next:
    status = (struct Status *)((char *)g_playerSettings + statusOffset);
    if (status->active == 1) {
        shown++;
        row = Key_FindKeyIndex(status->kind);
        scale.x = g_characterPortraitRecords[row].scale[layout];
        scale.y = g_characterPortraitRecords[row].scale[layout];
        scale.z = g_characterPortraitRecords[row].scale[layout];
        Preview_InitModelPreview((char *)g_trialCatalogueScreen + previewOffset, 9, status->kind + 911, 75, 24000, scale,
                      g_characterPortraitRecords[row].position[layout], g_characterPortraitRecords[row].distance[layout],
                      g_characterPortraitRecords[row].light[layout]);
        previewOffset += 1192;
        layout = 2;
        if (shown >= layout) {
            goto done;
        }
    }
    i++;
    statusOffset += sizeof(struct Status);
    if (i < 4) {
        goto next;
    }
done:
    return 0;
}

/* unit RESULTS_REFRESHTRIALCATALOGUEWIDGETS.CPP */
#include <platform_sdk.h>
#include "Common/osviscale.h"
#include "Common/ctx.h"
#include "Common/audio_loaddecodedsamples.h"
#include "Common/cheatcode.h"
#include "Common/note_state.h"
#include "Common/frontend_video_mode.h"
#include "Common/archive_chunk_images.h"
#include "Common/texture.h"
#include "Common/label.h"
#include "Common/player_join_requests.h"
#include "Common/characterselectionroot.h"
#include "Common/menu_initializeoptionsscene.h"
#include "Common/weapon_unlock_presets.h"
#include "Common/match_settings.h"
#include "Common/menu_model_preview.h"
#include "Common/player_item_inventory.h"
#include "Common/objb.h"
#include "types.h"
#include "Common/measured.h"
#include "Common/unresolved_word_access_set.h"
#include "Common/unresolved_word_accesses.h"
#include "Common/shared_gameslot.h"
#include "Common/selectionscreenstate.h"
#include "Common/resident_event_handler.h"
#include "Common/scene_frame_and_effect_updates.h"
#include "Frontend/results_refreshtrialcataloguewidgets.h"
#include "Frontend/results_marklinkedtrialsavailable.h"
#include "Achieve/achieve.h"
#include "Frontend/results.h"

/* Hides every model named by the sixty-four 12-byte entries of g_arenaCompatibilityTable: for each entry it looks
   up the first and second identifier in the current screen's context at 0x970 through Node_FindWidgetByResourceId
   and disables the object with Widget_SetWidgetFlag08_EquipActivateequipmentpanel, and does the same for the third identifier unless it
   is -1. The identifiers are passed as their low halfword, and the loop walks a manual byte offset
   so the table address is not hoisted. */
/* Read the optional resource as the low half of its word value on every host. */
void Results_HideTrialCatalogueWidgets(void) {
    s32 absentResource;
    s32 byteOffset;
    s32 index;

    /* The ROM indexes the table by a byte offset on every pass, so the table address is not hoisted out of the loop. */
#define CATALOGUE_PAIR_AT(offset) ((struct Pair *)((u8 *)g_arenaCompatibilityTable + (offset)))
    index = 0;
    absentResource = -1;
    byteOffset = index;
    do {
        Widget_SetWidgetFlag08(Node_FindWidgetByResourceId(g_trialCatalogueScreen->root, CATALOGUE_PAIR_AT(byteOffset)->a & 0xFFFF), 0);
        Widget_SetWidgetFlag08(Node_FindWidgetByResourceId(g_trialCatalogueScreen->root, CATALOGUE_PAIR_AT(byteOffset)->b & 0xFFFF), 0);
        if (CATALOGUE_PAIR_AT(byteOffset)->c.id != absentResource) {
            Widget_SetWidgetFlag08(Node_FindWidgetByResourceId(g_trialCatalogueScreen->root, (u16)CATALOGUE_PAIR_AT(byteOffset)->c.id), 0);
        }
        index += 1;
        byteOffset += sizeof(struct Pair);
    } while (index < 64);
#undef CATALOGUE_PAIR_AT
}


/* Returns the index of the trial catalogue stage whose value equals resourceKey, or zero when none does. */
static inline s32 Results_FindTrialCatalogueStageIndex(s32 resourceKey) {
    s32 index;

    for (index = 0; index < 36; index++) {
        if (g_trialCatalogueStages[index].id == resourceKey) {
            return index;
        }
    }
    return 0;
}

void Results_RefreshTrialCatalogueWidgets(void) {
    u8 availableFlags[8];
    Preset *unlockedPreset;
    SlotSelectionWidget *widget;
    s32 entryIndex, unlockSlot, unlockIndex;
    s32 unlockValue;
    s32 resourceKey;
    Shared_Game *playerSettings, *settings;
    u8 opacity;
    Results_HideTrialCatalogueWidgets();
    for (entryIndex = 0; entryIndex < 36; entryIndex++) {
        Defs_SetBitValue(availableFlags, entryIndex, 0);
    }
    Defs_SetBitValue(availableFlags, 0, 1);
    settings = &g_gameSettings;
    if (settings->controllerMode == 1) {
        playerSettings = settings;
        for (entryIndex = 0; entryIndex < 36; entryIndex++) {
            unlockedPreset = Achieve_CopyPreset(entryIndex, 0, (s8)playerSettings->playerSettings[g_trialCatalogueScreen->player].character);
            unlockValue = unlockedPreset->bytes[1];
            if (unlockValue > 0) Defs_SetBitValue(availableFlags, unlockValue - 1, 1);
            for (unlockSlot = 0; unlockSlot < 3; unlockSlot++) {
                unlockValue = *((u8 *)unlockedPreset + unlockSlot + 2);
                if (unlockValue > 0) Defs_SetBitValue(availableFlags, unlockValue - 1, 1);
            }
        }
    } else {
        for (entryIndex = 0; entryIndex < 36; entryIndex++) {
            Defs_SetBitValue(availableFlags, entryIndex, 1);
        }
    }
    for (entryIndex = 0; entryIndex < 64; entryIndex++) {
        resourceKey = g_arenaCompatibilityTable[entryIndex].a;
        unlockIndex = Results_FindTrialCatalogueStageIndex(resourceKey);
        if (Defs_TestBit((s32)availableFlags, unlockIndex) == 1) {
            widget = Node_FindWidgetByResourceId(g_trialCatalogueScreen->parent, (u16)g_arenaCompatibilityTable[entryIndex].a);
            Widget_SetWidgetFlag08(widget, 1);
            widget->alpha = 20;
            resourceKey = g_arenaCompatibilityTable[entryIndex].b;
            unlockIndex = Results_FindTrialCatalogueStageIndex(resourceKey);
            if (Defs_TestBit((s32)availableFlags, unlockIndex) == 1) {
                widget = Node_FindWidgetByResourceId(g_trialCatalogueScreen->parent, (u16)g_arenaCompatibilityTable[entryIndex].b);
                Widget_SetWidgetFlag08(widget, 1);
                widget->alpha = 20;
                if (g_arenaCompatibilityTable[entryIndex].c.id != -1) {
                    widget = Node_FindWidgetByResourceId(g_trialCatalogueScreen->parent, (u16)g_arenaCompatibilityTable[entryIndex].c.id);
                    Widget_SetWidgetFlag08(widget, 1);
                    widget->alpha = 20;
                }
            }
        }
    }
    for (entryIndex = 0; entryIndex < 36; entryIndex++) {
        if (Defs_TestBit((s32)g_trialCatalogueScreen->owned, entryIndex) == 1) ((void (*)(s32))Results_MarkLinkedTrialsAvailable)(entryIndex);
    }
    for (entryIndex = 0; entryIndex < 36; entryIndex++) {
        if (Defs_TestBit((s32)g_trialCatalogueScreen->pending, entryIndex) == 1) Defs_SetBitValue(g_trialCatalogueScreen->owned, entryIndex, 1);
    }
    for (entryIndex = 0; entryIndex < 64; entryIndex++) {
        opacity = 170;
        resourceKey = g_arenaCompatibilityTable[entryIndex].a;
        unlockIndex = Results_FindTrialCatalogueStageIndex(resourceKey);
        if (Defs_TestBit((s32)g_trialCatalogueScreen->owned, unlockIndex) == 1) {
            widget = Node_FindWidgetByResourceId(g_trialCatalogueScreen->parent, (u16)g_arenaCompatibilityTable[entryIndex].a);
            if (Defs_TestBit((s32)g_trialCatalogueScreen->pending, unlockIndex) == 1) { widget->alpha = 70; opacity = 70; }
            else widget->alpha = 170;
            resourceKey = g_arenaCompatibilityTable[entryIndex].b;
            unlockIndex = Results_FindTrialCatalogueStageIndex(resourceKey);
            if (Defs_TestBit((s32)g_trialCatalogueScreen->owned, unlockIndex) == 1) {
                widget = Node_FindWidgetByResourceId(g_trialCatalogueScreen->parent, (u16)g_arenaCompatibilityTable[entryIndex].b);
                if (Defs_TestBit((s32)g_trialCatalogueScreen->pending, unlockIndex) == 1) { widget->alpha = 70; opacity = 70; }
                else widget->alpha = 170;
                if (g_arenaCompatibilityTable[entryIndex].c.id != -1) {
                    widget = Node_FindWidgetByResourceId(g_trialCatalogueScreen->parent, (u16)g_arenaCompatibilityTable[entryIndex].c.id);
                    widget->alpha = opacity;
                }
            }
        }
    }
}

/* Updates the selected player's appearance and creates its results-screen model. */
#include "types.h"
#include "Frontend/frontend_drawmodelpreview.h"
#include "Defs/defs.h"
#include "Results/results_fillprofileweaponrows.h"
#include "Scene/scene_findtrackedactors.h"
#include "Frontend/frontend.h"

typedef struct PreviewRecord { char pad[4]; u8 kind; } PreviewRecord;



void Results_RefreshTrialCharacterPreview(void) {
    CVector3 scale;
    s32 record;
    s32 index;
    u8 kind;
    Shared_PlayerSettingsRecord *entry;
    Shared_Game *settings = (Shared_Game *)&g_gameSettings;
    if (settings->controllerMode == 4) {
        record = g_trialCatalogueScreen->selection;
        entry = &((Shared_Game *)&g_gameSettings)->playerSettings[g_trialCatalogueScreen->player];
        Results_FillTrialPresetWeaponRows(record);
        kind = ((PreviewRecord *)Scene_GetBlLevelData(&g_world, record))->kind;
        entry->character = kind;
        index = Key_FindKeyIndex((s8)kind);
        scale.x = g_characterPortraitRecords[index].scale[0];
        scale.y = g_characterPortraitRecords[index].scale[0];
        scale.z = g_characterPortraitRecords[index].scale[0];
        Preview_InitModelPreview((ModelPreview *)g_trialCatalogueScreen->panels, 9, entry->character + 911, 75, 24000, scale,
                         g_characterPortraitRecords[index].position[0], g_characterPortraitRecords[index].distance[0],
                         g_characterPortraitRecords[index].light[0]);
    }
}

/* unit RESULTS_UPDATERESULTSHEADING.CPP */
#if defined(VERSION_EU) || defined(VERSION_EU_X)
#define RES_TIMEFMT g_resultsBestTimeFormatEuro
#define RES_TIMEPOST g_resultsBestTimePlaceholderEuro
#define RES_HEAD3 ((char *)g_resultsTimeTrialHeadingTranslations[g_languageIndex])
#define RES_HEAD4 ((char *)g_resultsFragFestHeadingTranslations[settings->language])
#define RES_NAME(m) (((char **)g_resultCharacterHeadingTranslations[m].name)[settings->language])
#else
#define RES_TIMEFMT g_resultsBestTimeFormat
#define RES_TIMEPOST g_resultsBestTimePlaceholder
#define RES_HEAD3 g_resultsTimeTrialHeadingText
#define RES_HEAD4 g_resultsFragFestHeadingText
#define RES_NAME(m) (g_resultCharacterHeadings[m].name->text)
#endif
/* Writes the heading of the results screen g_trialCatalogueScreen into item 0x153: in one-player mode the
   label 0x69 followed by the name of the character in the player's status record; in three-player
   mode the label 0x3D with the stage's best time as minutes and seconds in item 0x156 (the record's
   time when set, else the stage default from Achieve_CopyPreset) and the heading g_resultsTimeTrialHeadingText; in
   four-player mode the heading g_resultsFragFestHeadingText. */

/* The results screen item and phrase ids renumber on the de cartridge: its heading item is 0x151,
   its name phrase 0x6B, its time phrase 0x3F and its time item 0x154; on eu-x 0x157, 0x6C, 0x40 and
   0x15A. eu and eu-x pick the heading and character name strings by language (RES_* above). */
#if defined(VERSION_DE)
enum { HEADING_ITEM = 337, NAME_PHRASE = 107, TIME_PHRASE = 63, TIME_ITEM = 340 };
#elif defined(VERSION_EU_X)
enum { HEADING_ITEM = 343, NAME_PHRASE = 108, TIME_PHRASE = 64, TIME_ITEM = 346 };
#else
enum { HEADING_ITEM = 339, NAME_PHRASE = 105, TIME_PHRASE = 61, TIME_ITEM = 342 };
#endif


void Results_UpdateResultsHeading(void) {
    Shared_Game *settings;
    struct Label *item;
    s32 time;
    u8 best;
    char buffer[32];

    ((struct Label *) Node_FindWidgetByResourceId(g_trialCatalogueScreen->parent, HEADING_ITEM))->text = g_trialCatalogueScreen->heading;
    settings = &g_gameSettings;
    switch (settings->controllerMode) {
    case 1:
        XPlus_CopyString(g_trialCatalogueScreen->heading, Node_GetStringByIndex(NAME_PHRASE));
        Random_ReplaceTextOccurrences(g_trialCatalogueScreen->heading, g_characterAndTimeFormatText,
                      RES_NAME(Key_FindKeyIndex(settings->playerSettings[g_trialCatalogueScreen->player].character)));
        break;
    case 3:
        XPlus_CopyString(g_trialCatalogueScreen->time, Node_GetStringByIndex(TIME_PHRASE));
        item = (struct Label *) Node_FindWidgetByResourceId(g_trialCatalogueScreen->parent, TIME_ITEM);
        Widget_SetWidgetFlag08(item, 1);
        item->text = g_trialCatalogueScreen->time;
        time = g_localPlayerProfiles[g_trialCatalogueScreen->player].times[g_trialCatalogueScreen->selection];
        if (time > 0) {
            XStdio_FormatBuffer(buffer, RES_TIMEFMT, time / 60, time % 60);
        } else {
            best = ((struct ResultsHeadingStage *) Achieve_CopyPreset(g_trialCatalogueScreen->selection, 3, 0))->time;
            XStdio_FormatBuffer(buffer, RES_TIMEFMT, (u8)(best / 60), (u8)(best % 60));
        }
        Random_ReplaceTextOccurrences(g_trialCatalogueScreen->time, RES_TIMEPOST, buffer);
        XPlus_CopyString(g_trialCatalogueScreen->heading, RES_HEAD3);
        break;
    case 4:
        XPlus_CopyString(g_trialCatalogueScreen->heading, RES_HEAD4);
        break;
    }
}

/* unit RESULTS_MARKLINKEDTRIALSAVAILABLE.CPP */
#undef g_gameSettingsView
#define g_gameSettingsView (*(struct GameSettingsModeStatusView *)&g_gameSettings)

/* Grants unowned unlocks for the completed game using its mode and player kind. */


void Results_MarkLinkedTrialsAvailable(void *trialBits) {
    struct GameSettingsModeStatusView *globals;
    struct TableFrontendMarkLinkedTrialsAvailable *table;
    unsigned int category;
    s32 kind;
    s32 value;
    s32 i;

    category=(uintptr_t)&g_gameSettingsView;
    globals=(struct GameSettingsModeStatusView *)category;
    switch (globals->mode) {
    case 1:
        kind = globals->status[g_trialCatalogueScreen->player].kind;
        category = 0;
        break;
    case 2:
        category = 1;
        kind = 0;
        break;
    case 3:
        category = 3;
        kind = 0;
        break;
    case 4:
        category = 2;
        kind = 0;
        break;
    default:
        kind = (s8)(&g_activeProfileCharacterSelections)[g_trialCatalogueScreen->player * 150];
        table = Achieve_CopyPreset(trialBits, 0, kind);
        goto preset_selected;
    }
    table = Achieve_CopyPreset(trialBits, category, kind);
preset_selected:
    if ((value = table->first) > 0) {

        if (Defs_TestBit(g_trialCatalogueScreen->owned, value-1) == 0) {
            Defs_SetBitValue(g_trialCatalogueScreen->pending, value-1, 1);
        }
    }
    for (i = 0; i < 3; i++) {
        if ((value = table->items[i]) > 0) {

            if (Defs_TestBit(g_trialCatalogueScreen->owned, value-1) == 0) {
                Defs_SetBitValue(g_trialCatalogueScreen->pending, value-1, 1);
            }
        }
    }
}

/* unit RESULTS_SELECTSUGGESTEDTRIAL.CPP */
void Results_SelectSuggestedTrial(void) {
    CGameStatus *state;
    Shared_Game *config;
    Preset *preset;
    s32 value, choice, i;
    g_trialCatalogueScreen->selection = g_selectedLevelId;
    if (g_trialCatalogueScreen->selection >= 37) g_trialCatalogueScreen->selection = 0;
    if (Defs_TestBit(g_trialCatalogueScreen->owned, g_trialCatalogueScreen->selection) != 0) {
        state = &g_gameSettings.counters;
        if (state->humanWon != 0) {
            config = &g_gameSettings;
            switch (config->controllerMode) {
            case 1:
                preset = Achieve_CopyPreset(g_trialCatalogueScreen->selection, 0, config->slots[g_trialCatalogueScreen->player].kind);
                break;
            case 2:
                preset = Achieve_CopyPreset(g_trialCatalogueScreen->selection, 1, 0);
                break;
            case 3:
                preset = Achieve_CopyPreset(g_trialCatalogueScreen->selection, 3, 0);
                break;
            case 4:
                preset = Achieve_CopyPreset(g_trialCatalogueScreen->selection, 2, 0);
                break;
            default:
                preset = Achieve_CopyPreset(g_trialCatalogueScreen->selection, 0, g_gameSettings.playerSettings[g_trialCatalogueScreen->player].character);
                break;
            }
            choice = 0;
            if ((value = preset->bytes[1]) > 0) {
                choice = value - 1;
            } else {
                for (i = 0; i < 3; i++) {
                    if ((value = (preset->bytes + i)[2]) > 0) {
                        choice = value - 1;
                        break;
                    }
                }
            }
            if (choice >= 37) choice = 0;
            g_trialCatalogueScreen->selection = choice;
        }
    }
}

/* unit RESULTS_FILLPROFILEWEAPONROWS.CPP */
/* Formats the name of entry g_trialCatalogueScreen's word at 0xA44 into a local 0x40-byte buffer through
   Scene_CopyLevelName from g_world_AchieveUpdateresultsscreen, passes the length XPlus_UppercaseString measures to XPlus_CopyString_ResultsFillprofileweaponrows for the
   text object at offset 0xA04, and points word 0x38 of the object at 0x998 to that text object. */






extern void Scene_CopyLevelName(struct Shared_World *world, s32 type, void *levelName, s32 maximumBytes);

extern u8 *XPlus_UppercaseString(u8 *string);

extern u8 *XPlus_CopyString(u8 *destination, u8 *source);

/* Returns the index of the entry among the 0x24 28-byte entries of g_trialCatalogueStages whose identifier
   matches, or zero when none does. */




/* Returns one when the two arguments are equal or when any of the sixty-four 12-byte pairs of g_arenaCompatibilityTable holds exactly that ordered pair, zero otherwise.
   Adapted from Key_GetCharacterPreviewModel with the single-key slot scan changed to an ordered-pair lookup over 64 twelve-byte entries. */




/* Sets the byte at offset 0x10 of the two objects at offsets 0xA64 and 0xA60 of the structure g_trialCatalogueScreen
   points to to 0xFF, shows both through Widget_SetWidgetFlag08_EquipActivateequipmentpanel and clears the word at 0xA68. */







extern void Widget_SetWidgetFlag08(void *object, int enabled);

/* Reports every set entry of each ready slot to the handler, stopping after two slots. */







extern void Results_SetTrialWeaponRow(u32, s32, s32);

/* Rebuilds the item list for the player g_trialCatalogueScreen selects: clears it through CTrialCatalogue_ShowTrialOptionChildren, looks
   up that player's model in g_world_AchieveUpdateresultsscreen, and for each of the model's eight slot ids at 0x4C that is
   at least 0x4C3 adds the nonzero id less 0x4C3 as the next row through Results_SetTrialWeaponRow when
   Player_HasProfileUnlockFlag accepts it for the player's 400-byte record in g_localPlayerProfiles. */












extern s32 Player_HasProfileUnlockFlag(u8 *profileBytes, s32 unlockIndex);

/* Rebuilds the weapon menu for the player g_trialCatalogueScreen selects: clears it through CTrialCatalogue_ShowTrialOptionChildren, then
   for each of the 0x16 weapon ids (excluding id 0) whose owned flag in g_gameSettings (offset 0x11C,
   player stride 0x96) is set, appends a row through Results_SetTrialWeaponRow. */







extern void Results_SetTrialWeaponRow(u32 row, s32 weaponId, s32 amount);

/* Enumerates the eight item identifiers of the record Scene_GetBlLevelData finds for a key and registers each nonzero identifier above 0x4C3 through Results_SetTrialWeaponRow, translated by 0x4C3 and numbered in order. */







extern void Results_SetTrialWeaponRow(u32 slot, s32 item, s32 amount);

void Results_RefreshTrialSelectionLabel(void) {
    char buffer[64];

    Scene_CopyLevelName(&g_world, g_trialCatalogueScreen->selection, buffer, 63);
    XPlus_CopyString(g_trialCatalogueScreen->text, XPlus_UppercaseString(buffer));
    g_trialCatalogueScreen->owner->text = g_trialCatalogueScreen->text;
}

/* Returns the index of the entry among the 0x24 28-byte entries of g_trialCatalogueStages whose identifier
   matches, or zero when none does. */
s32 Results_FindTrialValueIndex(s32 id) {
    s32 i;

    for (i = 0; i < 36; i++) {
        if (g_trialCatalogueStages[i].id == id) {
            return i;
        }
    }
    return 0;
}

/* Returns one when the two arguments are equal or when any of the sixty-four 12-byte pairs of g_arenaCompatibilityTable holds exactly that ordered pair, zero otherwise. */
s32 Results_IsUnlockLinked(s32 a, s32 b) {
    s32 i;

    if (a == b) {
        return 1;
    }
    for (i = 0; i < 64; i++) {
        if (g_arenaCompatibilityTable[i].a == a && g_arenaCompatibilityTable[i].b == b) {
            return 1;
        }
    }
    return 0;
}

/* Makes the banner and its shadow of the screen g_trialCatalogueScreen points to fully opaque (alpha 0xFF), shows both
   through Widget_SetWidgetFlag08 and clears the blinking flag. */
void Results_ShowTrialPreviewBanner(void) {
    (g_trialCatalogueScreen->banner)->alpha = 0xFF;
    (g_trialCatalogueScreen->bannerShadow)->alpha = 0xFF;
    Widget_SetWidgetFlag08(g_trialCatalogueScreen->bannerShadow, 1);
    Widget_SetWidgetFlag08(g_trialCatalogueScreen->banner, 1);
    g_trialCatalogueScreen->blinking = 0;
}

/* Reports every set entry of each ready slot to the handler, stopping after two slots. */
void Results_FillTwoPlayerWeaponRows(void) {
    Shared_Game *st;
    s32 n;
    s32 k;
    s32 i;
    Shared_Game *base;
    s32 j;

    k = 0;
    st = &g_gameSettings;
    for (n = 0; n < 4; n++) {
        if (st->playerSettings[n].enabled == 1) {
            j = 0;
            for (i = 0; i < 22; i++) {
                if (((base = &g_gameSettings)->playerSettings[n].weapons[i] == 1) && (i != 0)) {
                    Results_SetTrialWeaponRow(j, i, k);
                    j++;
                }
            }
            k++;
            if (k >= 2) {
                return;
            }
        }
    }
}

/* Rebuilds the item list for the player g_trialCatalogueScreen selects: clears it through CTrialCatalogue_ShowTrialOptionChildren, looks
   up that player's model in g_world_AchieveUpdateresultsscreen, and for each of the model's eight slot ids at 0x4C that is
   at least 0x4C3 adds the nonzero id less 0x4C3 as the next row through Results_SetTrialWeaponRow when
   Player_HasProfileUnlockFlag accepts it for the player's 400-byte record in g_localPlayerProfiles. */
void Results_FillProfileWeaponRows(void) {
    struct Model *model;
    s32 player;
    s32 id;
    s32 row;
    s32 i;

    CTrialCatalogue_ShowTrialOptionChildren();
    player = g_trialCatalogueScreen->player;
    model = Scene_FindActorDefinition(&g_world, 11, g_gameSettings.playerSettings[player].character);
    row = 0;
    for (i = 0; i < 8; i++) {
        id = model->slots[i];
        if (id >= 1219) {
            id -= 1219;
            if (Player_HasProfileUnlockFlag(&g_localPlayerProfiles[player], id) == 1 && id != 0) {
                Results_SetTrialWeaponRow(row, id, 0);
                row++;
            }
        }
    }
}

/* Rebuilds the weapon menu for the player g_trialCatalogueScreen selects: clears it through CTrialCatalogue_ShowTrialOptionChildren, then
   for each of the 0x16 weapon ids (excluding id 0) whose owned flag in g_gameSettings (offset 0x11C,
   player stride 0x96) is set, appends a row through Results_SetTrialWeaponRow. */
void Results_FillSelectedPlayerWeaponRows(void) {
    s32 count;
    s32 weapon;
    s32 base;

    CTrialCatalogue_ShowTrialOptionChildren();
    count = 0;
    base = g_trialCatalogueScreen->player * 150;
    for (weapon = 0; weapon < 22; weapon++) {
        if (((ProfileWeaponOwnedView *)(weapon + base + (u8 *)&g_gameSettings))->owned == 1) {
            if (weapon != 0) {
                Results_SetTrialWeaponRow(count, weapon, 0);
                count += 1;
            }
        }
    }
}

/* Enumerates the eight item identifiers of the record Scene_GetBlLevelData finds for a key and registers each nonzero identifier above 0x4C3 through Results_SetTrialWeaponRow, translated by 0x4C3 and numbered in order. */
void Results_FillTrialPresetWeaponRows(s32 key) {
    RecordFrontendFillTrialPresetWeaponRows *record;
    s32 count;
    s32 i;
    s32 item;

    CTrialCatalogue_ShowTrialOptionChildren();
    record = Scene_GetBlLevelData(&g_world, key);
    count = 0;
    for (i = 0; i < 8; i++) {
        item = record->items[i];
        if (item >= 1219) {
            item -= 1219;
            if (item != 0) {
                Results_SetTrialWeaponRow(count, item, 0);
                count++;
            }
        }
    }
}

/* unit FRONTEND_ACTIVATERESULTSACTION.CPP */
/* Handles the answer on the screen g_matchResultBadgeScreen. */


s32 Frontend_ActivateResultsAction(void) {
    s32 *paused;
    MarkMenuEventHandled();
    if (Frontend_GetMenuImageState(g_matchResultBadgeScreen) == 1) {
        return 0;
    }
    paused = &g_simpleObjectPauseState;
    *paused = 0;
    switch (Menu_GetFocusedElementId()) {
#if defined(VERSION_DE)
    case 565 - 2:
#elif defined(VERSION_EU) || defined(VERSION_US) || defined(VERSION_US_REV1)
    case 569 - 2:
#elif defined(VERSION_EU_X)
    case 574 - 2:
#endif
        if (((Shared_MenuData *)((u8 *)paused - offsetof(Shared_MenuData, pause)))->game.controllerMode == 0) {
            Frontend_StartMenuImageTransition(g_matchResultBadgeScreen);
            g_matchResultBadgeScreen->active = 0;
        } else {
            g_resultReplayPending = 0;
            g_resultExitPending = 0;
            SmXlate_SwitchScreen(15);
        }
        break;
#if defined(VERSION_DE)
    case 565 - 1:
#elif defined(VERSION_EU) || defined(VERSION_US) || defined(VERSION_US_REV1)
    case 569 - 1:
#elif defined(VERSION_EU_X)
    case 574 - 1:
#endif
        PAKInterface_SetScreenPhase(5);
        SmXlate_SwitchScreen(19);
        break;
#if defined(VERSION_DE)
    case 565 + 3:
#elif defined(VERSION_EU) || defined(VERSION_US) || defined(VERSION_US_REV1)
    case 569 + 3:
#elif defined(VERSION_EU_X)
    case 574 + 3:
#endif
        if (ScenarioSetup_IsCupSelected() == 1) {
            Random_SetMenuChoiceResult(33);
            return 0;
        }
        if (((Shared_MenuData *)((u8 *)paused - offsetof(Shared_MenuData, pause)))->game.controllerMode == 0) {
            SmXlate_SwitchScreen(20);
        } else {
            SmXlate_SwitchScreen(15);
        }
        break;
    default:
        return 0;
    }
    return 0;
}

s32 Frontend_ConsumeResultsEvent(void) {
    MarkMenuEventHandled();
    return 0;
}

/* When the fourth argument is one, calls MarkMenuEventHandled and, while the scroll position of
   the screen g_matchResultBadgeScreen points to is positive, decrements it and calls ScenarioSetup_FillResultRows. Returns zero. */
s32 Frontend_ScrollResultsBackward(void *first, void *second, void *third, s32 fourth) {
    MatchScoreScreen *state;

    if (fourth == 1) {
        MarkMenuEventHandled();
        state = g_matchResultBadgeScreen;
        if (state->first > 0) {
            state->first--;
            ScenarioSetup_FillResultRows();
            return 0;
        }
    }
    return 0;
}

/* When the fourth argument is one, calls MarkMenuEventHandled and, while the scroll position of
   the screen g_matchResultBadgeScreen points to is more than four below its scroll limit, advances it and calls
   ScenarioSetup_FillResultRows. Returns zero. */
s32 Frontend_ScrollResultsForward(void *first, void *second, void *third, s32 fourth) {
    MatchScoreScreen *state;
    s32 position;

    if (fourth == 1) {
        MarkMenuEventHandled();
        state = g_matchResultBadgeScreen;
        position = state->first;
        if (position + 4 < state->count) {
            state->first = position + 1;
            ScenarioSetup_FillResultRows();
            return 0;
        }
    }
    return 0;
}

/* Calls the handler registered for eventId (tables g_resultsEventIds, g_resultsEventKinds, g_resultsEventHandlers). A row matches when its event equals eventId and its kind equals the actor's kind or is the any-kind wildcard 0x7530. Returns the handler's result, or zero when no row matches. */
s32 Frontend_DispatchResultsEvent(void *eventObject, s32 eventId, s32 eventPayload, s32 eventValue, s32 eventExtra) {
    ResultsEventHandler *entry;
    s32 index;
    s32 wildcard;
    s32 actor_kind;
    s32 table_kind;
    struct MenuWidget *actor;

    if (g_resultsEventHandlers != 0) {
        wildcard = 30000;
        entry = &g_resultsEventHandlers;
        index = 0;
        do {
            if (g_resultsEventIds[index].value == eventId) {
                actor = eventObject;
                actor_kind = actor->resource;
                table_kind = g_resultsEventKinds[index].value;
                if ((table_kind == actor_kind) || (table_kind == wildcard)) {
                    return (*entry)(eventObject, eventId, eventPayload, eventValue, eventExtra);
                }
            }
            entry += 3;
            index++;
        } while (*entry != 0);
    }
    return 0;
}
