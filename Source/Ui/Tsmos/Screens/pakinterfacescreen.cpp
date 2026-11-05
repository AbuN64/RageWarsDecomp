#include "Common/screen.h"
#include "include_asm.h"
#include "Frontend/pakmenu.h"
#include "Common/name.h"
#include "types.h"
#include "Render/soundelement_playflatsound.h"
#include "Common/widget_tree.h"
#include "Ui/Tsmos/Screens/pakinterfacescreen.h"
#include "Ui/pakinterface_incrementnamecharacter.h"
#include "Ui/pakinterface_refreshplayerpanel.h"
#include "Ui/smp_overlay.h"
#include "Common/resourceloadstate.h"
#include "Common/pak_player_panel.h"
#include "Common/messagesemaphore.h"
#include "Common/player_message_menu.h"
#include "Frontend/pakinterface_findreadytransferplayer.h"
#include "Frontend/frontend_findprofileowner.h"
#include "Frontend/frontend_setplayerprofilelink.h"
#include "Resmgr/resmgr_string_memory.h"
#include "Frontend/node_findwidgetbyresourceid.h"
#include "Ai/playerprofile.h"
#include "Menu/note_readnotedata.h"
#include "Menu/note_readnoteinfo.h"
#include "Ui/pakinterface_checkrecordsnotecapacity.h"
#include "Ui/pakinterface_relabelslotrows.h"
#include "Ui/pakinterface_resolveplayerpakstate.h"
#include "Ui/pakinterface_saveplayerrecords.h"
#include "Common/pak_preview_selection.h"
#include "Common/playerprofiles.h"
#include "Common/selectionscreenstate.h"
#include "Frontend/pakinterface_updateplayerpanelanimations.h"
#include "Ui/pakinterface_decrementnamecharacter.h"
#include "Rsp/random_direction_and_affine_math.h"
#include "Common/vector4f.h"
#include "Frontend/frontend_checkownedprofileids.h"
#include "Ui/pakinterface_readrecordsnote.h"
#include "Menu/Pak/pak_note_search.h"
#include "Common/runtime_declarations.h"
#include "Common/shared_gameslot.h"
#include "Note/note_readnoteinfo.h"
#include "Menu/pak_allocaterenderbuffers.h"
#include "Ui/ui_address_symbols.h"
#include "Menu/pak_load.h"
#include "Ui/X_files/x_plus.h"
#include "Ui/X_files/x_stdio.h"
#include "Ui/g_noteinfointformat.h"
#include "Menu/menu_item_views.h"
#include "Menu/bound.h"
#include "Common/particle_lighting.h"
#include "Render/material_color_and_fog_views.h"
#include "Common/weapon_marker_and_profile_views.h"
#include "Gobjinst/gobjinst_buildactortransform.h"
#include "Gobjinst/player_drawtintedplayer_data.h"
#include "Data/Ui/event_handler_record.h"
#include "Common/effectrender.h"
#include "Common/rg.h"
#include "Data/Ovl1_j/menu_selecteuropeanpakactionlabel.h"
#include "Frontend/menu_image.h"
#include "Frontend/frontend_confirmequipmentselection.h"
#include "Frontend/player.h"
#include "data_overlay_sn_records.h"
#include "Common/shared_menureply.h"
#include "Scene/cache_freememory.h"
#include "Ui/pakinterface_checkpak.h"
#include "Ui/Tsmos/Screens/pakinterface_getnextplayertochoosename.h"
#include "Ui/pakinterface_resetcontrolbacktocopyplayer.h"
#include "Ui/pakinterface_savegame.h"
#include "Ui/pakinterface_addplayertospecificmiddleslot.h"
#include "Ui/pakinterface_copyspecificmiddleplayertoglobal.h"
#include "Ui/pakinterface_exitscreen.h"
#include "Ui/pakinterface_updatepak.h"
#include "Ui/pakinterface_refreshmiddlenamesforplayername.h"
#include "Ui/Tsmos/Screens/pakinterface_getnplayersjoined.h"
#include "Data/Ovltbl/items_copylocalizedplayernamesuffix.h"
#include "Data/Ovl1_j/screenpointerwordblock.h"
#include "Data/Ovl1_j/g_frontendupdateslidergeometryencodedwords_frontendupdateslidergeometry.h"
#include "Data/Ovl1_j/g_frontendslidertransitionhandlerwords_frontendupdateslidergeometry.h"
#include "Menu/menu_createsoundoptionsscreen.h"
#include "Menu/menu_applysoundsliders.h"
#include "Menu/menu_confirmsoundsliderpopup.h"
#include "Menu/menu_updatesoundoptionsscreen.h"
#include "Data/Ovl1_j/frontend_dispatchnodepairmenuevent_data.h"
#include "Data/rest_source_records.h"
#include "Common/menu_model_preview.h"
#include "Common/shared_optionsscreen.h"
#include "Common/world.h"
#include "Common/ballisticparams.h"
#include "Common/globals.h"
#include "Common/frontend_clock_state.h"
#include "Common/statepair.h"
#include "Resmgr/tsmos_setidletimer.h"
#include "Menu/Misc/cmenuprofile_activatefirstconfirmingplayer.h"
#include "Menu/menu_box.h"
#include "Common/aiprofile.h"
#include "types.h" /* the draft_fields struct headers below spell s32/u16/u8; types.h must precede them */
#include "Common/measured.h"
#include "Common/unresolved_word_access_set.h"
#include "Common/unresolved_word_accesses.h"
#include <platform_sdk.h>
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
#include "Common/osviscale.h"
#include "Common/ctx.h"
#include "Common/audio_loaddecodedsamples.h"
#include "Common/cheatcode.h"
#include "Common/note_state.h"
#include "Common/frontend_video_mode.h"
#include "Common/archive_chunk_images.h"
#include "Common/texture.h"
#include "Common/label.h"
#include "Common/characterselectionroot.h"
#include "Common/weapon_unlock_presets.h"
#include "Common/resultsoptionsscreen.h"
#include "Common/match_settings.h"
#include "Common/objb.h"
#include "Common/argb_color.h"
#include "Common/player_join_requests.h"
#include "Common/menu_initializeoptionsscene.h"
#include "Common/player_item_inventory.h"
#include "Frontend/widget_findwidgetatpoint.h"
#include "Ui/pakinterface_handlenextpanelselection.h"
#include "Common/menu_options_and_results.h"
#include "Ui/pakinterface_updateplayercontrolrows.h"
#include "Frontend/pakinterface_setscreenphase.h"
#include "Common/pak_enter_player_options.h"
#include "../../../../sdk/include/AUDIO/sprintf.H"
#include "Common/gameplay_camera.h"
#include "Common/frontend_resource_load_state.h"
#include "Common/gameplay_transition.h"

/* Cancels the pickup of the player in playerEntryId when that player's panel is in state 12 and selectionPressed is 1:
   sets the panel phase to 2, clears its timer, moves its name cursor back by one, writes 'A' into the name slot under
   the cursor when that slot is empty, makes the player's slot widget opaque and plays sound effect 3700 through
   SoundElement_PlayFlatSound. Panels in state 13 and above are left alone; always returns zero. */

s32 PAKInterface_MoveNameCursorBackward(s32 element, s32 eventId, s32 playerEntryId, s32 selectionPressed) {
    struct ResourceSmpFlickerCreateFlickerWidget *slotWidget;
    PakProfilePanelState *panel;
    u8 *nameSlot;
    s32 index;

    index = playerEntryId & 0xFFFF;
    panel = &g_pakProfileScreenState->players[index];
    if (panel->state == 13 || panel->state >= 14) {
        return 0;
    }
    if (panel->state == 12 && selectionPressed == 1) {
        slotWidget = SmpOverlay_GetSlotValue(g_pakProfileScreenState->root, index);
        panel->namePhase = 2;
        panel->nameTimer = 0;
        if (panel->nameCursor > 0) {
            panel->nameCursor -= 1;
        }
        nameSlot = &panel->name[panel->nameCursor].available;
        if (*nameSlot == 0) {
            *nameSlot = 'A';
        }
        slotWidget->value = 0xFF;
        SoundElement_PlayFlatSound(3700);
    }
    return 0;
}

/* Handles Controller Pak menu confirmations for the active channel, clearing its status on a confirmed state-12 prompt and returning focus to an enabled widget in the list states. */

s32 PAKInterface_HandleNextPanelSelection(s32 unusedWidget, s32 unusedEventId, s32 playerEntryId, s32 selectionPressed, s32 fifth) {
    s32 repeatMagnitude;
    s32 player;
    s32 playerState;
    MenuWidget *nextCharacterWidget;
    MenuWidget *nextChoiceWidget;
    MenuWidget *nextOptionWidget;

    player = playerEntryId & 0xFFFF;
    playerState = g_pakProfileScreenState->players[player].state;
    switch (playerState) {
    case 12:
        repeatMagnitude = XMath_AbsoluteInteger(fifth);
        if (repeatMagnitude < Smos_GetControlRepeatLimit()) {
            g_pakProfileScreenState->players[player].nameTimer = 0;
            g_pakProfileScreenState->players[player].namePhase = 2;
        }
        if (selectionPressed == 1) {
            MarkMenuEventHandled();
            PAKInterface_DecrementNameCharacter(player);
            g_pakProfileScreenState->players[player].namePhase = 0;
            SoundElement_PlayFlatSound(3713);
            return 0;
        }
        return 0;
    case 4:
        if (selectionPressed == 1) {
            MarkMenuEventHandled();
            PAKInterface_ScrollNoteList(player, 1);
            g_pakProfileScreenState->selected[player] = 0;
            SoundElement_PlayFlatSound(3700);
            return 0;
        }
        return 0;
    case 13:
        if ((g_pakProfileScreenState->players[player].sub == 6) && (selectionPressed == 1)) {
            MarkMenuEventHandled();
            nextCharacterWidget = ((MenuWidget *)SmpOverlay_GetSlotValue(g_pakProfileScreenState->root, player))->next;
loop_11:
            if (Widget_ListHasFlag100(nextCharacterWidget) != 0) {
                nextCharacterWidget = nextCharacterWidget->next;
                goto loop_11;
            }
            SmpOverlay_ShowSlotNode((g_pakProfileScreenState->root), player, nextCharacterWidget);
            SoundElement_PlayFlatSound(3700);
            return 0;
        }
        return 0;
    case 22:
        if (selectionPressed == 1) {
            nextChoiceWidget = ((MenuWidget *)SmpOverlay_GetSlotValue(g_pakProfileScreenState->root, player))->next;
loop_16:
            if (Widget_ListHasFlag100(nextChoiceWidget) != 0) {
                nextChoiceWidget = nextChoiceWidget->next;
                goto loop_16;
            }
            SmpOverlay_ShowSlotNode((g_pakProfileScreenState->root), player, nextChoiceWidget);
            PAKInterface_RelabelSlotRows(player);
        }
        goto block_24;
    case 27:
        if (selectionPressed == 1) {
            nextOptionWidget = ((MenuWidget *)SmpOverlay_GetSlotValue(g_pakProfileScreenState->root, player))->next;
loop_21:
            if (Widget_ListHasFlag100(nextOptionWidget) != 0) {
                nextOptionWidget = nextOptionWidget->next;
                goto loop_21;
            }
            SmpOverlay_ShowSlotNode((g_pakProfileScreenState->root), player, nextOptionWidget);
            PAKInterface_UpdatePlayerControlRows(player);
        }
block_24:
        MarkMenuEventHandled();
        break;
    }
    return 0;
}

/* Handles Controller Pak menu confirmations and returns focus to an enabled widget for the active channel. */
s32 PAKInterface_HandlePakMenuConfirm(s32 element, s32 eventId, s32 packedPlayerEvent, s32 pressState, s32 fifth) {
    WidgetReferenceNodeView *node;
    s32 player;

    player = packedPlayerEvent & 0xFFFF;
    switch (g_pakProfileScreenState->players[player].state) {
    case 12:
        if (XMath_AbsoluteInteger(fifth) < Smos_GetControlRepeatLimit()) {
            g_pakProfileScreenState->players[player].nameTimer = 0;
            g_pakProfileScreenState->players[player].namePhase = 2;
        }
        if (pressState == 1) {
            MarkMenuEventHandled();
            g_pakProfileScreenState->players[player].namePhase = pressState;
            PAKInterface_IncrementNameCharacter(player);
            SoundElement_PlayFlatSound(3713);
        }
        return 0;
    case 4:
        if (pressState == 1) {
            MarkMenuEventHandled();
            PAKInterface_ScrollNoteList(player, 0);
            g_pakProfileScreenState->selected[player] = 0;
            SoundElement_PlayFlatSound(3700);
        }
        return 0;
    case 13:
        if (g_pakProfileScreenState->players[player].sub == 6 && pressState == 1) {
            MarkMenuEventHandled();
            node = SmpOverlay_GetSlotValue(g_pakProfileScreenState->root, player);
            node = node->ref2C;
            while (Widget_ListHasFlag100(node) != 0) {
                node = node->ref2C;
            }
            SmpOverlay_ShowSlotNode(g_pakProfileScreenState->root, player, node);
            SoundElement_PlayFlatSound(3700);
        }
        return 0;
    case 22:
        if (pressState == 1) {
            node = SmpOverlay_GetSlotValue(g_pakProfileScreenState->root, player);
            node = node->ref2C;
            while (Widget_ListHasFlag100(node) != 0) {
                node = node->ref2C;
            }
            SmpOverlay_ShowSlotNode(g_pakProfileScreenState->root, player, node);
            PAKInterface_RelabelSlotRows(player);
        }
        MarkMenuEventHandled();
        break;
    case 27:
        if (pressState == 1) {
            node = SmpOverlay_GetSlotValue(g_pakProfileScreenState->root, player);
            node = node->ref2C;
            while (Widget_ListHasFlag100(node) != 0) {
                node = node->ref2C;
            }
            SmpOverlay_ShowSlotNode(g_pakProfileScreenState->root, player, node);
            PAKInterface_UpdatePlayerControlRows(player);
        }
        MarkMenuEventHandled();
        break;
    }
    return 0;
}

/* Handles a cancel event for the player the low half of the third argument names: calls
   MarkMenuEventHandled and, when the block g_pakProfileScreenState points to is in phase 7, returns to screen 3
   through PAKInterface_BeginScreenExit; otherwise by the state of the player's panel in g_pakProfileScreenState: in state 0 it leaves for screen 0x1B unless PAKInterface_CountActivePlayerPanels reports something pending, in
   state 0xC it blanks the character at the cursor of the panel's name, and in
   states 0x16 and 0x1B it closes the keyboard through PAKInterface_RelabelSlotRows or PAKInterface_UpdatePlayerControlRows with -1,
   returns the player to state 0xD and redraws through PAKInterface_RefreshPlayerPanel. Returns zero. */

s32 PAKInterface_HandlePlayerPanelBack(void *element, void *eventId, u16 player) {
    MarkMenuEventHandled();
    if (g_pakProfileScreenState->phase == 7) {
        PAKInterface_BeginScreenExit(3);
        return 0;
    }
    switch (g_pakProfileScreenState->players[player].state) {
    case 0:
        if (PAKInterface_CountActivePlayerPanels() > 0) {
            return 0;
        }
        MarkMenuEventHandled();
        PAKInterface_BeginScreenExit(27);
        return 0;
    case 12:
        MarkMenuEventHandled();
        g_pakProfileScreenState->players[player].name[g_pakProfileScreenState->players[player].nameCursor].available = ' ';
        break;
    case 22:
        MarkMenuEventHandled();
        PAKInterface_RelabelSlotRows(-1);
        g_pakProfileScreenState->players[player].state = 13;
        PAKInterface_RefreshPlayerPanel(player);
        break;
    case 27:
        MarkMenuEventHandled();
        PAKInterface_UpdatePlayerControlRows(-1);
        g_pakProfileScreenState->players[player].state = 13;
        PAKInterface_RefreshPlayerPanel(player);
        break;
    default:
        return 0;
    }
    return 0;
}

/* Steps player playerEntryId's menu state machine in its record of g_pakProfileScreenState
   on the event SmpOverlay_GetSlotNodeId reports: each state accepts its events, moves to the next state (by the game
   mode where it matters), updates the player's name records, and refreshes the player through
   PAKInterface_RefreshPlayerPanel. Returns zero. */

s32 PAKInterface_ActivatePlayerPanelAction(s32 element, s32 eventId, s32 playerEntryId) {
    s32 answer;
    s32 i;
    s32 j;
    s32 playerIndex;
    s32 event;
    s32 slot;
    s32 other;
    s32 transferPlayer;
    s32 found;
    Shared_Item *node;
    u8 *settings;
    u8 character;
    s32 sub;
    s32 mode;

    MarkMenuEventHandled();
    i = 0;
    playerIndex = playerEntryId & 0xFFFF;
    event = SmpOverlay_GetSlotNodeId(g_pakProfileScreenState->root, playerIndex);
    switch (g_pakProfileScreenState->players[playerIndex].state) {
    case 1:
        switch (event) {
#if defined(VERSION_DE)
        case 720:
#elif defined(VERSION_EU_X)
        case 745:
#else
        case 749:
#endif
            g_pakProfileScreenState->players[playerIndex].back = 2;
            g_pakProfileScreenState->players[playerIndex].state = 2;
            PAKInterface_RefreshPlayerPanel(playerIndex);
            break;
#if defined(VERSION_DE)
        case 721:
#elif defined(VERSION_EU_X)
        case 746:
#else
        case 750:
#endif
            switch (g_pakProfileScreenState->phase) {
            case 0:
            case 1:
            case 3:
            case 4:
            case 5:
            case 6:
                g_pakProfileScreenState->players[playerIndex].state = 14;
                PAKInterface_RefreshPlayerPanel(playerIndex);
                break;
            case 2:
                if (g_pakProfileScreenState->players[playerIndex].host == 1) {
                    PAKInterface_BeginLinkedProfileTransfer(playerIndex);
                } else {
                    g_pakProfileScreenState->players[playerIndex].state = 14;
                }
                PAKInterface_RefreshPlayerPanel(playerIndex);
                break;
            case 7:
                g_pakProfileScreenState->players[playerIndex].state = 26;
                g_pakProfileScreenState->players[playerIndex].next = 1;
                PAKInterface_RefreshPlayerPanel(playerIndex);
                break;
            }
            break;
        }
        break;
    case 3:
        switch (event) {
#if defined(VERSION_DE)
        case 728:
#elif defined(VERSION_EU_X)
        case 735:
#else
        case 701:
#endif
            switch (g_pakProfileScreenState->phase) {
            case 0:
            case 1:
            case 3:
            case 4:
            case 5:
            case 6:
                g_pakProfileScreenState->players[playerIndex].state = 14;
                PAKInterface_RefreshPlayerPanel(playerIndex);
                break;
            case 7:
                g_pakProfileScreenState->players[playerIndex].state = 26;
                g_pakProfileScreenState->players[playerIndex].next = 1;
                PAKInterface_RefreshPlayerPanel(playerIndex);
                break;
            case 2:
                if (g_pakProfileScreenState->players[playerIndex].host == 1) {
                    PAKInterface_BeginLinkedProfileTransfer(playerIndex);
                } else {
                    g_pakProfileScreenState->players[playerIndex].state = 14;
                }
                PAKInterface_RefreshPlayerPanel(playerIndex);
                break;
            }
            break;
#if defined(VERSION_DE)
        case 727:
#elif defined(VERSION_EU_X)
        case 733:
#else
        case 700:
#endif
            g_pakProfileScreenState->players[playerIndex].state = 28;
            PAKInterface_RefreshPlayerPanel(playerIndex);
            break;
#if defined(VERSION_DE)
        case 726:
#elif defined(VERSION_EU_X)
        case 734:
#else
        case 702:
#endif
            g_pakProfileScreenState->players[playerIndex].back = 2;
            g_pakProfileScreenState->players[playerIndex].state = 2;
            PAKInterface_RefreshPlayerPanel(playerIndex);
            break;
        }
        break;
    case 15:
        switch (event) {
#if defined(VERSION_DE)
        case 708:
#elif defined(VERSION_EU_X)
        case 748:
#else
        case 752:
#endif
            if (PAKInterface_CheckRecordsNoteCapacity(playerIndex, &answer) == 0) {
                if (answer == 1) {
                    g_pakProfileScreenState->players[playerIndex].state = 12;
                } else {
                    g_pakProfileScreenState->players[playerIndex].state = 11;
                }
            } else {
                g_pakProfileScreenState->players[playerIndex].back = 2;
                g_pakProfileScreenState->players[playerIndex].state = 2;
            }
            PAKInterface_RefreshPlayerPanel(playerIndex);
            break;
#if defined(VERSION_DE)
        case 709:
#elif defined(VERSION_EU_X)
        case 749:
#else
        case 753:
#endif
            if (g_pakProfileScreenState->phase == 7) {
                g_pakProfileScreenState->players[playerIndex].state = 26;
                g_pakProfileScreenState->players[playerIndex].next = 15;
            } else {
                g_pakProfileScreenState->players[playerIndex].state = 14;
            }
            PAKInterface_RefreshPlayerPanel(playerIndex);
            break;
        }
        break;
    case 16:
        switch (event) {
#if defined(VERSION_DE)
        case 694:
#elif defined(VERSION_EU_X)
        case 708:
#else
        case 696:
#endif
            g_pakProfileScreenState->players[playerIndex].records[g_pakProfileScreenState->players[playerIndex].record].owner = (u8) g_pakProfileScreenState->players[playerIndex].record;
            g_pakProfileScreenState->players[playerIndex].records[g_pakProfileScreenState->players[playerIndex].record].player = playerIndex;
            g_pakProfileScreenState->players[playerIndex].records[g_pakProfileScreenState->players[playerIndex].record].time = g_pakProfileScreenState->players[playerIndex].profile;
            if (g_pakProfileScreenState->phase == 7) {
                settings = g_playerSettings;
                g_pakProfileScreenState->players[playerIndex].records[g_pakProfileScreenState->players[playerIndex].record].setting[0] = settings[123];
                g_pakProfileScreenState->players[playerIndex].records[g_pakProfileScreenState->players[playerIndex].record].setting[1] = settings[125];
                g_pakProfileScreenState->players[playerIndex].records[g_pakProfileScreenState->players[playerIndex].record].setting[2] = settings[121];
                g_pakProfileScreenState->players[playerIndex].records[g_pakProfileScreenState->players[playerIndex].record].setting[3] = settings[122];
                g_pakProfileScreenState->players[playerIndex].records[g_pakProfileScreenState->players[playerIndex].record].setting[4] = settings[130];
            }
            if (PAKInterface_SavePlayerRecords(playerIndex) == 1) {
                switch (g_pakProfileScreenState->phase) {
                case 0:
                    if (PAKInterface_FindEmptyProfileSlot(playerIndex) >= 0) {
                        g_pakProfileScreenState->players[playerIndex].state = 23;
                    } else {
                        g_pakProfileScreenState->players[playerIndex].state = 14;
                    }
                    break;
                case 7:
                    Frontend_SetPlayerProfileLink(playerIndex, 0, 0);
                    PAKInterface_LoadLinkedPlayerProfile(0);
                    MarkMenuEventHandled();
                    PAKInterface_BeginScreenExit(9);
                    return 0;
                default:
                    g_pakProfileScreenState->players[playerIndex].state = 13;
                    break;
                }
                PAKInterface_RefreshPlayerPanel(playerIndex);
            }
            break;
#if defined(VERSION_DE)
        case 693:
#elif defined(VERSION_EU_X)
        case 707:
#else
        case 697:
#endif
            switch (g_pakProfileScreenState->phase) {
            case 0:
                g_pakProfileScreenState->players[playerIndex].state = 23;
                break;
            case 1:
                g_pakProfileScreenState->players[playerIndex].state = 23;
                break;
            case 7:
                g_pakProfileScreenState->players[playerIndex].state = 23;
                break;
            default:
                g_pakProfileScreenState->players[playerIndex].state = 13;
                break;
            }
            PAKInterface_RefreshPlayerPanel(playerIndex);
            break;
        }
        break;
    case 12:
        slot = PAKInterface_FindEmptyProfileSlot(playerIndex);
        if (slot >= 0) {
#if defined(VERSION_DE)
            node = (Shared_Item *)Node_FindWidgetByResourceId((void*)g_pakProfileScreenState->players[playerIndex].menu, 730);
#elif defined(VERSION_EU_X)
            node = (Shared_Item *)Node_FindWidgetByResourceId((void*)g_pakProfileScreenState->players[playerIndex].menu, 690);
#else
            node = (Shared_Item *)Node_FindWidgetByResourceId((void*)g_pakProfileScreenState->players[playerIndex].menu, 755);
#endif
            for (j = 0; node->flags & 0x10; j++) {
                g_pakProfileScreenState->players[playerIndex].records[slot].name[j] = ((u8 *)node->label->text)[0];
                if (node->next == 0) {
                    break;
                }
                node = node->next;
            }
            for (j = 6; j > 0; j--) {
                character = g_pakProfileScreenState->players[playerIndex].records[slot].name[j];
                if (character != 0 && character != ' ') {
                    break;
                }
                g_pakProfileScreenState->players[playerIndex].records[slot].name[j] = 0;
            }
            g_pakProfileScreenState->players[playerIndex].state = 16;
            g_pakProfileScreenState->players[playerIndex].record = slot;
        } else {
            g_pakProfileScreenState->players[playerIndex].state = 3;
        }
        PAKInterface_RefreshPlayerPanel(playerIndex);
        break;
    case 11:
        switch (event) {
#if defined(VERSION_DE)
        case 723:
#elif defined(VERSION_EU_X)
        case 728:
#else
        case 722:
#endif
            g_pakProfileScreenState->players[playerIndex].state = 4;
            PAKInterface_RefreshPlayerPanel(playerIndex);
            break;
#if defined(VERSION_DE)
        case 724:
#elif defined(VERSION_EU_X)
        case 727:
#else
        case 723:
#endif
            switch (g_pakProfileScreenState->phase) {
            case 0:
            case 1:
            case 3:
            case 4:
            case 5:
                g_pakProfileScreenState->players[playerIndex].state = 14;
                PAKInterface_RefreshPlayerPanel(playerIndex);
                break;
            case 2:
                if (g_pakProfileScreenState->players[playerIndex].host == 1) {
                    PAKInterface_BeginLinkedProfileTransfer(playerIndex);
                } else {
                    g_pakProfileScreenState->players[playerIndex].state = 14;
                }
                PAKInterface_RefreshPlayerPanel(playerIndex);
                break;
            case 7:
                g_pakProfileScreenState->players[playerIndex].state = 26;
                g_pakProfileScreenState->players[playerIndex].next = 11;
                PAKInterface_RefreshPlayerPanel(playerIndex);
                break;
            }
            break;
        }
        break;
    case 4:
        switch (event) {
#if defined(VERSION_DE)
        case 744:
#elif defined(VERSION_EU_X)
        case 757:
#else
        case 730:
#endif
            switch (g_pakProfileScreenState->phase) {
            case 0:
                g_pakProfileScreenState->players[playerIndex].state = 15;
                break;
            case 2:
                g_pakProfileScreenState->players[playerIndex].back = 2;
                g_pakProfileScreenState->players[playerIndex].state = 2;
                break;
            case 7:
                g_pakProfileScreenState->players[playerIndex].back = 2;
                g_pakProfileScreenState->players[playerIndex].state = 2;
                break;
            case 1:
            case 4:
            case 6:
                g_pakProfileScreenState->players[playerIndex].state = 14;
                break;
            }
            PAKInterface_RefreshPlayerPanel(playerIndex);
            break;
#if defined(VERSION_DE)
        case 743:
#elif defined(VERSION_EU_X)
        case 758:
#else
        case 729:
#endif
            i = g_pakProfileScreenState->players[playerIndex].slot;
            if (XPlus_ParseDecimalInteger(g_pakProfileScreenState->players[playerIndex].names[i].text) > 0) {
                g_pakProfileScreenState->players[playerIndex].state = 8;
                PAKInterface_RefreshPlayerPanel(playerIndex);
            }
            break;
        }
        break;
    case 8:
        switch (event) {
#if defined(VERSION_DE)
        case 756:
#elif defined(VERSION_EU_X)
        case 738:
#else
        case 720:
#endif
            if (Note_DeleteNote(playerIndex, g_pakProfileScreenState->players[playerIndex].slot) == 0) {
#if defined(VERSION_EU) || defined(VERSION_EU_X)
                if (XPlus_CompareStringsIgnoreCase((u8 *)g_pakProfileGameNames[g_languageIndex],
#else
                if (XPlus_CompareStringsIgnoreCase((u8 *)g_pakProfileGameNameFixed,
#endif
                                     g_pakProfileScreenState->players[playerIndex].names[g_pakProfileScreenState->players[playerIndex].slot].code) == 0) {
                    for (j = 0; j < 4; j++) {
                        found = Frontend_FindProfileOwner(g_pakProfileScreenState->players[playerIndex].profile, g_pakProfileScreenState->players[playerIndex].records[j].owner);
                        if (found != -1) {
                            Player_InitializeProfile(&((Profile *) g_localPlayerProfiles)[found]);
                        }
                    }
                }
                g_pakProfileScreenState->players[playerIndex].state = 4;
                PAKInterface_RefreshPlayerPanel(playerIndex);
            } else {
                Note_ProbeStatus(playerIndex);
                PAKInterface_ResolvePlayerPakState(playerIndex);
            }
            break;
#if defined(VERSION_DE)
        case 757:
#elif defined(VERSION_EU_X)
        case 737:
#else
        case 719:
#endif
            g_pakProfileScreenState->players[playerIndex].state = 4;
            PAKInterface_RefreshPlayerPanel(playerIndex);
            break;
        }
        break;
    case 7:
        switch (event) {
#if defined(VERSION_DE)
        case 752:
#elif defined(VERSION_EU_X)
        case 742:
#else
        case 717:
#endif
            i = g_pakProfileScreenState->players[playerIndex].choice;
            other = Frontend_FindProfileOwner(g_pakProfileScreenState->players[playerIndex].profile, g_pakProfileScreenState->players[playerIndex].records[i].owner);
            if (other != -1) {
                Player_InitializeProfile(&((Profile *) g_localPlayerProfiles)[other]);
            }
            Player_InitializeProfile(&g_pakProfileScreenState->players[playerIndex].records[i]);
            if (PAKInterface_SavePlayerRecords(playerIndex) == 1) {
                if (g_pakProfileScreenState->players[playerIndex].sub == 5) {
                    switch (g_pakProfileScreenState->phase) {
                    case 0:
                        g_pakProfileScreenState->players[playerIndex].back = 2;
                        g_pakProfileScreenState->players[playerIndex].state = 2;
                        g_pakProfileScreenState->players[playerIndex].next = 12;
                        g_pakProfileScreenState->players[playerIndex].sub = 0;
                        break;
                    case 2:
                        g_pakProfileScreenState->players[playerIndex].next = 9;
                        g_pakProfileScreenState->players[playerIndex].back = 2;
                        g_pakProfileScreenState->players[playerIndex].state = 2;
                        g_pakProfileScreenState->players[playerIndex].sub = 3;
                        break;
                    default:
                        g_pakProfileScreenState->players[playerIndex].state = 13;
                        break;
                    }
                } else {
                    g_pakProfileScreenState->players[playerIndex].state = 13;
                }
                PAKInterface_RefreshPlayerPanel(playerIndex);
            }
            break;
#if defined(VERSION_DE)
        case 753:
#elif defined(VERSION_EU_X)
        case 741:
#else
        case 716:
#endif
            g_pakProfileScreenState->players[playerIndex].state = 13;
            PAKInterface_RefreshPlayerPanel(playerIndex);
            break;
        }
        break;
    case 9:
        switch (event) {
#if defined(VERSION_DE)
        case 689:
#elif defined(VERSION_EU_X)
        case 683:
#else
        case 713:
#endif
            slot = PAKInterface_FindEmptyProfileSlot(playerIndex);
            if (slot >= 0) {
                XPlus_CopyBytes(&g_pakProfileScreenState->players[playerIndex].records[slot],
                                 &g_pakProfileScreenState->players[g_pakProfileScreenState->links[0].player].records[g_pakProfileScreenState->links[0].entry],
                                 400);
                g_pakProfileScreenState->players[playerIndex].record = slot;
                g_pakProfileScreenState->players[playerIndex].records[slot].owner = slot;
                g_pakProfileScreenState->players[playerIndex].records[slot].time = g_pakProfileScreenState->players[playerIndex].profile;
            }
            if (PAKInterface_SavePlayerRecords(playerIndex) == 1) {
                if (g_pakProfileScreenState->phase == 2) {
                    if (g_pakProfileScreenState->players[playerIndex].host == 1) {
                        PAKInterface_BeginLinkedProfileTransfer(playerIndex);
                    } else {
                        g_pakProfileScreenState->players[playerIndex].state = 14;
                    }
                } else {
                    g_pakProfileScreenState->players[playerIndex].state = 13;
                }
                PAKInterface_RefreshPlayerPanel(playerIndex);
            }
            break;
#if defined(VERSION_DE)
        case 690:
#elif defined(VERSION_EU_X)
        case 684:
#else
        case 712:
#endif
            if (g_pakProfileScreenState->phase == 2) {
                if (g_pakProfileScreenState->players[playerIndex].host == 1) {
                    PAKInterface_BeginLinkedProfileTransfer(playerIndex);
                } else {
                    g_pakProfileScreenState->players[playerIndex].state = 14;
                }
            } else {
                g_pakProfileScreenState->players[playerIndex].state = 13;
            }
            PAKInterface_RefreshPlayerPanel(playerIndex);
            break;
        }
        break;
    case 13:
#if defined(VERSION_DE)
        if (event == 717) {
#elif defined(VERSION_EU_X)
        if (event == 765) {
#else
        if (event == 693) {
#endif
            sub = g_pakProfileScreenState->players[playerIndex].sub;
            switch (sub) {
            case 3:
                g_pakProfileScreenState->players[playerIndex].state = 17;
                transferPlayer = PAKInterface_FindReadyTransferPlayer();
                if (transferPlayer >= 0) {
                    g_pakProfileScreenState->players[transferPlayer].back = 2;
                    g_pakProfileScreenState->players[transferPlayer].state = 2;
                    g_pakProfileScreenState->players[transferPlayer].next = 13;
                    g_pakProfileScreenState->players[transferPlayer].sub = 3;
                    PAKInterface_RefreshPlayerPanel(transferPlayer);
                }
                break;
            case 6:
                switch (g_pakProfileScreenState->phase) {
                case 1:
                    g_pakProfileScreenState->players[playerIndex].state = 17;
                    transferPlayer = PAKInterface_FindReadyTransferPlayer();
                    if (transferPlayer >= 0) {
                        g_pakProfileScreenState->players[transferPlayer].back = 2;
                        g_pakProfileScreenState->players[transferPlayer].state = 2;
                        g_pakProfileScreenState->players[transferPlayer].next = 13;
                        g_pakProfileScreenState->players[transferPlayer].sub = sub;
                        PAKInterface_RefreshPlayerPanel(transferPlayer);
                    }
                    break;
                case 7:
                    g_pakProfileScreenState->players[playerIndex].state = 26;
                    g_pakProfileScreenState->players[playerIndex].next = 13;
                    break;
                }
                break;
            case 0:
                g_pakProfileScreenState->players[playerIndex].state = 14;
                break;
            case 5:
                mode = g_pakProfileScreenState->phase;
                switch (mode) {
                case 3:
                    g_pakProfileScreenState->players[playerIndex].state = 14;
                    break;
                case 0:
                    g_pakProfileScreenState->players[playerIndex].back = 2;
                    g_pakProfileScreenState->players[playerIndex].state = 2;
                    g_pakProfileScreenState->players[playerIndex].next = 12;
                    g_pakProfileScreenState->players[playerIndex].sub = 0;
                    break;
                case 2:
                    g_pakProfileScreenState->players[playerIndex].back = mode;
                    g_pakProfileScreenState->players[playerIndex].state = mode;
                    g_pakProfileScreenState->players[playerIndex].next = 9;
                    g_pakProfileScreenState->players[playerIndex].sub = 3;
                    break;
                }
                break;
            }
            PAKInterface_RefreshPlayerPanel(playerIndex);
            break;
        }
        i = 0;
        switch (event) {
#if defined(VERSION_DE)
        case 715:
#elif defined(VERSION_EU_X)
        case 760:
#else
        case 691:
#endif
            i = 1;
            break;
#if defined(VERSION_DE)
        case 716:
#elif defined(VERSION_EU_X)
        case 764:
#else
        case 688:
#endif
            i = 2;
            break;
#if defined(VERSION_DE)
        case 712:
#elif defined(VERSION_EU_X)
        case 763:
#else
        case 692:
#endif
            i = 3;
            break;
        }
        switch (g_pakProfileScreenState->players[playerIndex].sub) {
        case 0:
            break;
        case 3:
            if (g_pakProfileScreenState->players[playerIndex].used[i] == 1) {
                Frontend_SetPlayerProfileLink(playerIndex, i, 0);
                g_pakProfileScreenState->players[playerIndex].choice = i;
                g_pakProfileScreenState->players[playerIndex].state = 27;
                PAKInterface_RefreshPlayerPanel(playerIndex);
            }
            break;
        case 6:
            switch (g_pakProfileScreenState->phase) {
            case 1:
                if (g_pakProfileScreenState->players[playerIndex].used[i] == 1) {
                    g_pakProfileScreenState->players[playerIndex].choice = i;
                    g_pakProfileScreenState->players[playerIndex].state = 22;
                    PAKInterface_RefreshPlayerPanel(playerIndex);
                }
                break;
            case 7:
                if (g_pakProfileScreenState->players[playerIndex].used[i] == 1) {
                    Frontend_SetPlayerProfileLink(playerIndex, i, 0);
                    PAKInterface_LoadLinkedPlayerProfile(0);
                    MarkMenuEventHandled();
                    PAKInterface_BeginScreenExit(9);
                    return 0;
                }
                break;
            }
            break;
        case 5:
            switch (g_pakProfileScreenState->phase) {
            case 0:
            case 2:
            case 3:
                if (g_pakProfileScreenState->players[playerIndex].used[i] != 2) {
                    g_pakProfileScreenState->players[playerIndex].choice = i;
                    g_pakProfileScreenState->players[playerIndex].state = 7;
                    PAKInterface_RefreshPlayerPanel(playerIndex);
                }
                break;
            }
            break;
        }
        break;
    case 22:
        switch (event) {
#if defined(VERSION_DE)
        case 652:
#elif defined(VERSION_EU_X)
        case 660:
#else
        case 651:
#endif
            i = 0;
            break;
#if defined(VERSION_DE)
        case 654:
#elif defined(VERSION_EU_X)
        case 662:
#else
        case 653:
#endif
            i = 1;
            break;
#if defined(VERSION_DE)
        case 656:
#elif defined(VERSION_EU_X)
        case 664:
#else
        case 655:
#endif
            i = 2;
            break;
#if defined(VERSION_DE)
        case 658:
#elif defined(VERSION_EU_X)
        case 666:
#else
        case 657:
#endif
            i = 3;
            break;
#if defined(VERSION_DE)
        case 651:
#elif defined(VERSION_EU_X)
        case 659:
#else
        case 650:
#endif
            PAKInterface_BeginScreenExit(3);
            return 0;
        }
        Frontend_SetPlayerProfileLink(playerIndex, g_pakProfileScreenState->players[playerIndex].choice, i);
        PAKInterface_LoadLinkedPlayerProfile(i);
#if defined(VERSION_DE)
        Widget_SetWidgetFlag08(Node_FindWidgetByResourceId((void*)g_pakProfileScreenState->players[playerIndex].notes[g_pakProfileScreenState->players[playerIndex].choice], 713), 1);
#elif defined(VERSION_EU_X)
        Widget_SetWidgetFlag08(Node_FindWidgetByResourceId((void*)g_pakProfileScreenState->players[playerIndex].notes[g_pakProfileScreenState->players[playerIndex].choice], 761), 1);
#else
        Widget_SetWidgetFlag08(Node_FindWidgetByResourceId((void*)g_pakProfileScreenState->players[playerIndex].notes[g_pakProfileScreenState->players[playerIndex].choice], 689), 1);
#endif
        g_pakProfileScreenState->players[playerIndex].used[g_pakProfileScreenState->players[playerIndex].choice] = 0;
        g_pakProfileScreenState->links[i].state = 0;
        g_pakProfileScreenState->players[playerIndex].port = i;
        PAKInterface_RelabelSlotRows(playerIndex);
        g_pakProfileScreenState->players[playerIndex].state = 13;
        PAKInterface_RefreshPlayerPanel(playerIndex);
        break;
    case 27:
        switch (event) {
#if defined(VERSION_DE)
        case 661:
#elif defined(VERSION_EU_X)
        case 670:
#else
        case 664:
#endif
            PAKInterface_BeginScreenExit(3);
            return 0;
#if defined(VERSION_DE)
        case 662:
#elif defined(VERSION_EU_X)
        case 671:
#else
        case 665:
#endif
            i = 0;
            break;
#if defined(VERSION_DE)
        case 664:
#elif defined(VERSION_EU_X)
        case 673:
#else
        case 667:
#endif
            i = 1;
            break;
#if defined(VERSION_DE)
        case 666:
#elif defined(VERSION_EU_X)
        case 675:
#else
        case 669:
#endif
            i = 2;
            break;
#if defined(VERSION_DE)
        case 668:
#elif defined(VERSION_EU_X)
        case 677:
#else
        case 671:
#endif
            i = 3;
            break;
        }
        if (i != playerIndex) {
            SmpOverlay_SetSlotValue(g_pakProfileScreenState->root, playerIndex, 1);
            g_pakProfileScreenState->players[i].back = 2;
            g_pakProfileScreenState->players[i].state = 2;
            g_pakProfileScreenState->players[i].next = 9;
            g_pakProfileScreenState->players[i].sub = 3;
            g_pakProfileScreenState->players[i].host = 1;
            PAKInterface_RefreshPlayerPanel(i);
        } else {
            g_pakProfileScreenState->players[playerIndex].state = 9;
            PAKInterface_RefreshPlayerPanel(playerIndex);
        }
        break;
    case 6:
        switch (event) {
#if defined(VERSION_DE)
        case 686:
#elif defined(VERSION_EU_X)
        case 714:
#else
        case 745:
#endif
            g_pakProfileScreenState->players[playerIndex].state = 14;
            PAKInterface_RefreshPlayerPanel(playerIndex);
            break;
#if defined(VERSION_DE)
        case 687:
#elif defined(VERSION_EU_X)
        case 713:
#else
        case 744:
#endif
            PAKInterface_CopyActiveProfilesToPakSlots(playerIndex);
            if (PAKInterface_SavePlayerRecords(playerIndex) == 1) {
                g_pakProfileScreenState->players[playerIndex].state = 14;
                PAKInterface_RefreshPlayerPanel(playerIndex);
            }
            break;
        }
        break;
    case 21:
        switch (event) {
#if defined(VERSION_DE)
        case 680:
#elif defined(VERSION_EU_X)
        case 731:
#else
        case 738:
#endif
            switch (g_pakProfileScreenState->phase) {
            case 0:
            case 1:
            case 2:
            case 3:
            case 4:
            case 5:
                g_pakProfileScreenState->players[playerIndex].state = 14;
                PAKInterface_RefreshPlayerPanel(playerIndex);
                break;
            }
            break;
#if defined(VERSION_DE)
        case 679:
#elif defined(VERSION_EU_X)
        case 730:
#else
        case 739:
#endif
            g_pakProfileScreenState->players[playerIndex].back = 2;
            g_pakProfileScreenState->players[playerIndex].state = 2;
            PAKInterface_RefreshPlayerPanel(playerIndex);
            break;
        }
        break;
    case 23:
        switch (event) {
#if defined(VERSION_DE)
        case 696:
#elif defined(VERSION_EU_X)
        case 703:
#else
        case 685:
#endif
            g_pakProfileScreenState->players[playerIndex].state = 12;
            PAKInterface_RefreshPlayerPanel(playerIndex);
            break;
#if defined(VERSION_DE)
        case 697:
#elif defined(VERSION_EU_X)
        case 704:
#else
        case 686:
#endif
            if (g_pakProfileScreenState->phase == 7) {
                g_pakProfileScreenState->players[playerIndex].state = 26;
                g_pakProfileScreenState->players[playerIndex].next = 23;
            } else {
                g_pakProfileScreenState->players[playerIndex].state = 14;
            }
            PAKInterface_RefreshPlayerPanel(playerIndex);
            break;
        }
        break;
    case 24:
        switch (event) {
#if defined(VERSION_DE)
        case 702:
#elif defined(VERSION_EU_X)
        case 688:
#else
        case 683:
#endif
            g_pakProfileScreenState->players[playerIndex].state = 13;
            g_pakProfileScreenState->players[playerIndex].sub = 5;
            PAKInterface_RefreshPlayerPanel(playerIndex);
            break;
#if defined(VERSION_DE)
        case 701:
#elif defined(VERSION_EU_X)
        case 687:
#else
        case 682:
#endif
            if (g_pakProfileScreenState->players[playerIndex].host == 1) {
                PAKInterface_BeginLinkedProfileTransfer(playerIndex);
            } else {
                g_pakProfileScreenState->players[playerIndex].state = 14;
            }
            PAKInterface_RefreshPlayerPanel(playerIndex);
            break;
        }
        break;
    case 25:
#if defined(VERSION_DE)
        if (event == 699) {
#elif defined(VERSION_EU_X)
        if (event == 701) {
#else
        if (event == 747) {
#endif
            if (g_pakProfileScreenState->players[playerIndex].host == 1) {
                PAKInterface_BeginLinkedProfileTransfer(playerIndex);
            } else {
                g_pakProfileScreenState->players[playerIndex].state = 14;
            }
            PAKInterface_RefreshPlayerPanel(playerIndex);
        }
        break;
    case 26:
        switch (event) {
#if defined(VERSION_DE)
        case 704:
#elif defined(VERSION_EU_X)
        case 698:
#else
        case 679:
#endif
            g_pakProfileScreenState->players[0].back = 2;
            g_pakProfileScreenState->players[0].state = 2;
            g_pakProfileScreenState->players[0].next = 13;
            g_pakProfileScreenState->players[0].sub = 6;
            PAKInterface_RefreshPlayerPanel(playerIndex);
            break;
#if defined(VERSION_DE)
        case 705:
#elif defined(VERSION_EU_X)
        case 699:
#else
        case 680:
#endif
            Player_InitializeProfileSlot(0);
            MarkMenuEventHandled();
            PAKInterface_BeginScreenExit(9);
            return 0;
        }
        break;
    case 28:
        switch (event) {
#if defined(VERSION_DE)
        case 674:
            g_pakProfileScreenState->players[playerIndex].back = 2;
            g_pakProfileScreenState->players[playerIndex].state = 2;
            PAKInterface_RefreshPlayerPanel(playerIndex);
            break;
        case 675:
#elif defined(VERSION_EU_X)
        case 718:
#else
        case 735:
            g_pakProfileScreenState->players[playerIndex].back = 2;
            g_pakProfileScreenState->players[playerIndex].state = 2;
            PAKInterface_RefreshPlayerPanel(playerIndex);
            break;
        case 736:
#endif
            if (Note_RepairId(playerIndex) != 0) {
                g_pakProfileScreenState->players[playerIndex].state = 29;
                PAKInterface_RefreshPlayerPanel(playerIndex);
            } else {
                g_pakProfileScreenState->players[playerIndex].back = 2;
                g_pakProfileScreenState->players[playerIndex].state = 2;
                PAKInterface_RefreshPlayerPanel(playerIndex);
            }
            break;
#if defined(VERSION_EU_X)
        case 719:
            g_pakProfileScreenState->players[playerIndex].back = 2;
            g_pakProfileScreenState->players[playerIndex].state = 2;
            PAKInterface_RefreshPlayerPanel(playerIndex);
            break;
#else
#endif
        }
        break;
    case 29:
#if defined(VERSION_DE)
        if (event == 677) {
#elif defined(VERSION_EU_X)
        if (event == 716) {
#else
        if (event == 704) {
#endif
            g_pakProfileScreenState->players[playerIndex].back = 2;
            g_pakProfileScreenState->players[playerIndex].state = 2;
            PAKInterface_RefreshPlayerPanel(playerIndex);
        }
        break;
    }
    return 0;
}

extern const char g_modeToken[7];

/* Updates the selected player's setup panel and its linked controls. */
#include "types.h"
#include "Frontend/pakmenu.h"
#include "Common/selectionscreenstate.h"
#include "Ui/Tsmos/Screens/pakinterfacescreen.h"
#include "Frontend/widget_findwidgetatpoint.h"
/* menu_setup_versions.h declares this scalar only cart-guarded; the slot-error scalar is real in every cart */
#include "Common/runtime_declarations.h"
#include "Frontend/smp_overlay.h"
typedef struct SetupTextNode SetupTextNode;
typedef struct SetupRosterChoice SetupRosterChoice;
typedef struct SetupRosterSlot SetupRosterSlot;
typedef struct SetupCharacterState SetupCharacterState;
typedef struct SetupLinkedLabel SetupLinkedLabel;
typedef struct SetupRosterRecord SetupRosterRecord;
struct SetupTextNode {
    char pad0[0x34];
    s32 stringTableIndex;
    void* nameText;
};
struct SetupRosterChoice {
    char pad0[0x64];
    void* reservedPointer;
    char pad64[0xADC];
    s32 selectedChoice;
};
struct SetupRosterSlot {
    char pad0[0x64];
    void* reservedPointer1;
    char pad64[0xAC8];
    s32 selectedRosterIndex;
};
struct SetupCharacterState {
    char pad0[0xBA0];
    s32 animationState;
    s32 animationFrame;
};
struct SetupLinkedLabel {
    char pad0[0x8];
    MenuWidget * textNode;
    char pad8[0x4];
    u8 alpha;
    char pad10[0x27];
    void* nextLabel;
};
struct SetupRosterRecord {
    char pad0[0x64];
    void* reservedPointer2;
    char pad64[0xB1C];
    s32 rosterRecord;
};

int Control_IsControllerConnected(int);
u8 * XPlus_CopyString(u8 *, u8 *);
char * Node_GetStringByIndex(s32);

void Random_ReplaceTextOccurrences(char *, char *, char *);
void PAKInterface_BuildProfileSlotList(s32);
void PAKInterface_RelabelSlotRows(s32);
void PAKInterface_LoadNoteList(s32);
void PAKInterface_LabelActiveProfileRows(s32);
s32 PAKInterface_CountPendingPlayerPanels(void);
void PAKInterface_BeginScreenExit(s32);
void Frontend_StartMenuImageTransition(s32 *record);

/* The slot-error scalar is real external storage in every ROM version. */

void PAKInterface_RefreshPlayerPanel(s32 playerIndex) {

    s32 text_node;

    s32 itemIndex;

    s32 slot_active;

    s32 unusedValue;
    s32 characterIndex;
    s32 slotLabelId;

    s32 selectionOrLabel;
    s32 playerLinkOffset;

    s8 *replacement;
    s8 *panelTemplate;
    u16 unusedValue1;
    u16 statusPanelResourceId;
    u16 slotLabelResourceId;
    u32 panelState;
    u32 screenPhase;
    u32 exitPhase;
    void *previousPanel;
    SlotSelectionWidget *idlePanel;
    SlotSelectionWidget *notePanelOrLabel;
    SetupRosterSlot *unusedPointer;
    SlotSelectionWidget *linkedProfilePanel;
    SlotSelectionWidget *stateElevenPanel;
    SlotSelectionWidget *nameEntryPanel;
    SlotSelectionWidget *profileListPanel;
    SlotSelectionWidget *readyPanel;
    SlotSelectionWidget *createProfilePanel;
    SlotSelectionWidget *recordPanel;
    SetupRosterRecord *unusedPointer1;
    SlotSelectionWidget *missingSavePanel;
    SlotSelectionWidget *stateTwentyThreePanel;
    SlotSelectionWidget *fullProfilesPanel;
    SlotSelectionWidget *unavailableProfilesPanel;
    SlotSelectionWidget *stateTwentySixPanel;
    SlotSelectionWidget *stateTwentyEightPanel;
    SlotSelectionWidget *stateTwentyNinePanel;
    SlotSelectionWidget *pakErrorPanel;
    SlotSelectionWidget *statusPanel;
    SlotSelectionWidget *pakUnavailablePanel;
    SlotSelectionWidget *noteListPanel;
    SlotSelectionWidget *activeProfilesPanel;
    SlotSelectionWidget *chosenProfilePanel;
    SetupRosterChoice *unusedPointer2;
    SetupCharacterState *unusedPointer3;
    void *unusedPointer4;
    void *panelSprite;
    void *panelWidget;

    previousPanel = g_pakProfileScreenState->players[playerIndex].menuWidget;
    if (previousPanel != 0) {
        Widget_SetWidgetFlag08((SlotSelectionWidget *) previousPanel, 0);
    }
    Widget_SetWidgetFlag40(SmpOverlay_GetSlotValue(g_pakProfileScreenState->root, playerIndex), 0);
    /* the published B6E8 takes the controller handle as a plain scalar */
    SmpOverlay_ShowSlotById((s32) g_pakProfileScreenState->windowAddress, playerIndex, SETUP_LABEL_ID);
    panelState = g_pakProfileScreenState->players[playerIndex].state;
    switch (panelState) {
    case 0:

        idlePanel = Node_FindWidgetByResourceId(g_pakProfileScreenState->players[playerIndex].sprite, PANEL_ROOT_ID);
        g_pakProfileScreenState->players[playerIndex].menuWidget = idlePanel;
        Widget_SetWidgetFlag08(idlePanel, 1);
        text_node = (s32)Node_FindWidgetByResourceId(g_pakProfileScreenState->players[playerIndex].menuWidget, PANEL_TEXT_ID);
        ((SetupTextNode *)text_node)->nameText = g_pakProfileScreenState->players[playerIndex].nameText;
        screenPhase = g_pakProfileScreenState->phase;

        switch (screenPhase) {
        case 1:
        case 7:
            replacement = Node_GetStringByIndex(MODE_PROFILE_SELECT_ID);
            panelTemplate = Node_GetStringByIndex(((SetupTextNode *)text_node)->stringTableIndex);
            break;
        case 2:
            replacement = Node_GetStringByIndex(MODE_PAK_EVENT_ID);
            panelTemplate = Node_GetStringByIndex(((SetupTextNode *)text_node)->stringTableIndex);
            break;
        case 3:
            replacement = Node_GetStringByIndex(MODE_TIMED_RESET_ID);
            panelTemplate = Node_GetStringByIndex(((SetupTextNode *)text_node)->stringTableIndex);
            break;
        case 4:
        case 6:
            replacement = Node_GetStringByIndex(MODE_PAK_DIALOG_ID);
            panelTemplate = Node_GetStringByIndex(((SetupTextNode *)text_node)->stringTableIndex);
            break;
        case 5:
            replacement = Node_GetStringByIndex(MODE_POST_RESULTS_ID);
            panelTemplate = Node_GetStringByIndex(((SetupTextNode *)text_node)->stringTableIndex);
            break;
        case 0:
        default:
            replacement = Node_GetStringByIndex(MODE_DEFAULT_ID);
            panelTemplate = Node_GetStringByIndex(((SetupTextNode *)text_node)->stringTableIndex);
            break;
        }

        XPlus_CopyString((&g_pakProfileScreenState->players[playerIndex])->nameText, panelTemplate);
        Random_ReplaceTextOccurrences((&g_pakProfileScreenState->players[playerIndex])->nameText, g_modeToken, replacement);
        playerLinkOffset = playerIndex * 8;
        if (g_pakProfileScreenState->phase == 6) {
            Widget_SetWidgetFlag08(Node_FindWidgetByResourceId(g_pakProfileScreenState->players[playerIndex].menuWidget, MODE_HIDE_ID), 0);
            playerLinkOffset = playerIndex * 8;
        }
        break;
    case 1:

        pakErrorPanel = Node_FindWidgetByResourceId(g_pakProfileScreenState->players[playerIndex].sprite, UI_CASE_1_2EC);
        g_pakProfileScreenState->players[playerIndex].menuWidget = pakErrorPanel;
        Widget_SetWidgetFlag08(pakErrorPanel, 1);
        SmpOverlay_ShowSlotNode(g_pakProfileScreenState->root, playerIndex, Node_FindWidgetByResourceId(g_pakProfileScreenState->players[playerIndex].menuWidget, UI_CASE_1_2EE));
        playerLinkOffset = playerIndex * 8;
        break;
    case 2:

        panelSprite = g_pakProfileScreenState->players[playerIndex].sprite;
        statusPanelResourceId = UI_CASE_2_2D4;
block_36:
        statusPanel = Node_FindWidgetByResourceId(panelSprite, statusPanelResourceId);
        g_pakProfileScreenState->players[playerIndex].menuWidget = statusPanel;
        Widget_SetWidgetFlag08(statusPanel, 1);
        playerLinkOffset = playerIndex * 8;
        break;
    case 3:

        pakUnavailablePanel = Node_FindWidgetByResourceId(g_pakProfileScreenState->players[playerIndex].sprite, UI_CASE_3_2BB);
        g_pakProfileScreenState->players[playerIndex].menuWidget = pakUnavailablePanel;
        Widget_SetWidgetFlag08(pakUnavailablePanel, 1);
        SmpOverlay_ShowSlotNode(g_pakProfileScreenState->root, playerIndex, Node_FindWidgetByResourceId(g_pakProfileScreenState->players[playerIndex].menuWidget, UI_CASE_3_2BC));
        break;
    case 4:

        noteListPanel = Node_FindWidgetByResourceId(g_pakProfileScreenState->players[playerIndex].sprite, UI_CASE_4_2D5);
        g_pakProfileScreenState->players[playerIndex].menuWidget = noteListPanel;
        Widget_SetWidgetFlag08(noteListPanel, 1);
        SmpOverlay_ShowSlotNode(g_pakProfileScreenState->root, playerIndex, Node_FindWidgetByResourceId(g_pakProfileScreenState->players[playerIndex].menuWidget, UI_CASE_4_2DA));
        PAKInterface_LoadNoteList(playerIndex);
        playerLinkOffset = playerIndex * 8;
        break;
    case 22:
        /* the panel slot is untyped storage; the hub types the E8D8 argument as the item */
        Widget_SetWidgetFlag08((SlotSelectionWidget *) g_pakProfileScreenState->players[playerIndex].menuWidget, 1);
        selectionOrLabel = 0;
        while (g_pakProfileScreenState->links[selectionOrLabel].state == 0) {
            selectionOrLabel += 1;
        }
        slotLabelId = SLOT_DEFAULT_ID;
        if (selectionOrLabel == 1) {
            goto case22_one;
        }
        if (selectionOrLabel >= 2) {
            goto case22_check_two;
        }
        if (selectionOrLabel == 0) {
            goto case22_selected;
        }
        goto case22_default;
case22_check_two:
        if (selectionOrLabel == 2) {
            goto case22_two;
        }
case22_check_three:
        if (selectionOrLabel == 3) {
            goto case22_three;
        }
case22_default:
        slotLabelId = SLOT_DEFAULT_ID;
        goto case22_selected;
case22_one:
        slotLabelId = PAK_SLOT_LABEL_ID(1);
        goto case22_selected;
case22_two:
        slotLabelId = PAK_SLOT_LABEL_ID(2);
        goto case22_selected;
case22_three:
        slotLabelId = PAK_SLOT_LABEL_ID(3);
case22_selected:
        SmpOverlay_ShowSlotById((s32) g_pakProfileScreenState->windowAddress, playerIndex, slotLabelId);
        PAKInterface_RelabelSlotRows(playerIndex);
        playerLinkOffset = playerIndex * 8;
        break;
    case 6:

        activeProfilesPanel = Node_FindWidgetByResourceId(g_pakProfileScreenState->players[playerIndex].sprite, UI_CASE_6_2E4);
        g_pakProfileScreenState->players[playerIndex].menuWidget = activeProfilesPanel;
        Widget_SetWidgetFlag08(activeProfilesPanel, 1);
        SmpOverlay_ShowSlotNode(g_pakProfileScreenState->root, playerIndex, Node_FindWidgetByResourceId(g_pakProfileScreenState->players[playerIndex].menuWidget, UI_CASE_6_2E8));
        PAKInterface_LabelActiveProfileRows(playerIndex);
        playerLinkOffset = playerIndex * 8;
        break;
    case 7:

        chosenProfilePanel = Node_FindWidgetByResourceId(g_pakProfileScreenState->players[playerIndex].sprite, UI_CASE_7_2CA);
        g_pakProfileScreenState->players[playerIndex].menuWidget = chosenProfilePanel;
        Widget_SetWidgetFlag08(chosenProfilePanel, 1);
        SmpOverlay_ShowSlotNode(g_pakProfileScreenState->root, playerIndex, Node_FindWidgetByResourceId(g_pakProfileScreenState->players[playerIndex].menuWidget, UI_CASE_7_2CC));

        panelWidget = g_pakProfileScreenState->players[playerIndex].menuWidget;
        selectionOrLabel = g_pakProfileScreenState->players[playerIndex].chosen;
        slotLabelResourceId = UI_CASE_7_2CB;

        (((MenuWidget *)(Node_FindWidgetByResourceId(panelWidget, slotLabelResourceId)))->text) = (&g_pakProfileScreenState->players[playerIndex])->slots[selectionOrLabel];
        goto block_84;
    case 8:

        notePanelOrLabel = Node_FindWidgetByResourceId(g_pakProfileScreenState->players[playerIndex].sprite, UI_CASE_8_2CE);
        g_pakProfileScreenState->players[playerIndex].menuWidget = notePanelOrLabel;
        Widget_SetWidgetFlag08(notePanelOrLabel, 1);
        SmpOverlay_ShowSlotNode(g_pakProfileScreenState->root, playerIndex, Node_FindWidgetByResourceId(g_pakProfileScreenState->players[playerIndex].menuWidget, UI_CASE_8_2CF));

        selectionOrLabel = g_pakProfileScreenState->players[playerIndex].slot;
        notePanelOrLabel = Node_FindWidgetByResourceId(g_pakProfileScreenState->players[playerIndex].menuWidget, UI_CASE_8_2CB);

        ((MenuWidget *)notePanelOrLabel)->text = g_pakProfileScreenState->players[playerIndex].names[selectionOrLabel].code;
        goto block_84;
    case 9:

        linkedProfilePanel = Node_FindWidgetByResourceId(g_pakProfileScreenState->players[playerIndex].sprite, UI_CASE_9_2C6);
        g_pakProfileScreenState->players[playerIndex].menuWidget = linkedProfilePanel;
        Widget_SetWidgetFlag08(linkedProfilePanel, 1);
        SmpOverlay_ShowSlotNode(g_pakProfileScreenState->root, playerIndex, Node_FindWidgetByResourceId(g_pakProfileScreenState->players[playerIndex].menuWidget, UI_CASE_9_2C8));
        ((MenuWidget *)Node_FindWidgetByResourceId(g_pakProfileScreenState->players[playerIndex].menuWidget, UI_CASE_9_2C7))->text = g_pakProfileScreenState->players[g_pakProfileScreenState->links[0].player].slots[g_pakProfileScreenState->links[0].entry];
        goto block_84;
    case 10:

        statusPanel = Node_FindWidgetByResourceId(g_pakProfileScreenState->players[playerIndex].sprite, UI_CASE_10_2A4);
        g_pakProfileScreenState->players[playerIndex].menuWidget = statusPanel;
        Widget_SetWidgetFlag08(statusPanel, 1);
        playerLinkOffset = playerIndex * 8;
        break;
    case 11:

        stateElevenPanel = Node_FindWidgetByResourceId(g_pakProfileScreenState->players[playerIndex].sprite, UI_CASE_11_2D1);
        g_pakProfileScreenState->players[playerIndex].menuWidget = stateElevenPanel;
        Widget_SetWidgetFlag08(stateElevenPanel, 1);
        SmpOverlay_ShowSlotNode(g_pakProfileScreenState->root, playerIndex, Node_FindWidgetByResourceId(g_pakProfileScreenState->players[playerIndex].menuWidget, UI_CASE_11_2D2));
        break;
    case 12:

        nameEntryPanel = Node_FindWidgetByResourceId(g_pakProfileScreenState->players[playerIndex].sprite, UI_CASE_12_2F2);
        g_pakProfileScreenState->players[playerIndex].menuWidget = nameEntryPanel;
        Widget_SetWidgetFlag08(nameEntryPanel, 1);
        itemIndex = 0;
        selectionOrLabel = (s32)Node_FindWidgetByResourceId(g_pakProfileScreenState->players[playerIndex].menuWidget, UI_CASE_12_2F3);
        SmpOverlay_ShowSlotNode(g_pakProfileScreenState->root, playerIndex, (void *)selectionOrLabel);

        g_pakProfileScreenState->players[playerIndex].nameCursor = 0;

        do {
            if (itemIndex == 0) {
                g_pakProfileScreenState->players[playerIndex].name[itemIndex].available = 65;
            } else {
                g_pakProfileScreenState->players[playerIndex].name[itemIndex].available = 0;
            }
            g_pakProfileScreenState->players[playerIndex].name[itemIndex].slot = 0;
            itemIndex++;
        } while (itemIndex < 7);

        g_pakProfileScreenState->players[playerIndex].nameTimer = 0;
        g_pakProfileScreenState->players[playerIndex].namePhase = 2;
        characterIndex = 0;
        do {
            ((SetupLinkedLabel *)selectionOrLabel)->alpha = 0xFF;
            text_node = (s32)((SetupLinkedLabel *)selectionOrLabel)->textNode;
            ((MenuWidget *)text_node)->text = &g_pakProfileScreenState->players[playerIndex].name[characterIndex].available;
            selectionOrLabel = (s32)((SetupLinkedLabel *)selectionOrLabel)->nextLabel;
            characterIndex += 1;
        } while (selectionOrLabel != 0);
        playerLinkOffset = playerIndex * 8;
        break;
    case 13:

        profileListPanel = Node_FindWidgetByResourceId(g_pakProfileScreenState->players[playerIndex].sprite, UI_CASE_13_2AF);
        g_pakProfileScreenState->players[playerIndex].menuWidget = profileListPanel;
        Widget_SetWidgetFlag08(profileListPanel, 1);
        SmpOverlay_ShowSlotNode(g_pakProfileScreenState->root, playerIndex, Node_FindWidgetByResourceId(g_pakProfileScreenState->players[playerIndex].menuWidget, UI_CASE_13_2B6));
        PAKInterface_BuildProfileSlotList(playerIndex);
        playerLinkOffset = playerIndex * 8;
        break;
    case 14:
    case 17:
        SmpOverlay_ShowSlotById((s32) g_pakProfileScreenState->windowAddress, playerIndex, SETUP_LABEL_ID);
        SmpOverlay_SetSlotValue(g_pakProfileScreenState->root, playerIndex, 1);

        readyPanel = Node_FindWidgetByResourceId(g_pakProfileScreenState->players[playerIndex].sprite, UI_CASE_17_2A5);
        g_pakProfileScreenState->players[playerIndex].menuWidget = readyPanel;
        Widget_SetWidgetFlag08(readyPanel, 1);
        if (PAKInterface_CountPendingPlayerPanels() == 0) {
            exitPhase = g_pakProfileScreenState->phase;
            if (exitPhase == 4) {
                goto mode_default;
            }
            if ((s32)exitPhase < 5) {
                goto mode_default;
            }
            if (exitPhase == 5) {
                goto mode_five;
            }
            if (exitPhase == 6) {
                goto mode_six;
            }
            goto mode_default;
mode_five:
            Tsmos_DeactivateControllerState();
            Frontend_StartMenuImageTransition(g_pakProfileScreenState->menu);
            goto mode_end;
mode_six:
            {
                PAKInterface_BeginScreenExit(29);
                if (g_pakProfileOperationPhase == 1) {
                    g_pakProfileControllerPort -= 1;
                }
                if (g_pakProfileOperationPhase == 0) {
                    g_pakProfileControllerPort = -1;
                }
                goto mode_end;
            }
mode_default:
            PAKInterface_BeginScreenExit(27);
mode_end:;
        }
        playerLinkOffset = playerIndex * 8;
        break;
    case 15:

        createProfilePanel = Node_FindWidgetByResourceId(g_pakProfileScreenState->players[playerIndex].sprite, UI_CASE_15_2EF);
        g_pakProfileScreenState->players[playerIndex].menuWidget = createProfilePanel;
        Widget_SetWidgetFlag08(createProfilePanel, 1);
        SmpOverlay_ShowSlotNode(g_pakProfileScreenState->root, playerIndex, Node_FindWidgetByResourceId(g_pakProfileScreenState->players[playerIndex].menuWidget, UI_CASE_15_2F1));
        break;
    case 16:

        recordPanel = Node_FindWidgetByResourceId(g_pakProfileScreenState->players[playerIndex].sprite, UI_CASE_16_2B7);
        g_pakProfileScreenState->players[playerIndex].menuWidget = recordPanel;
        Widget_SetWidgetFlag08(recordPanel, 1);
        SmpOverlay_ShowSlotNode(g_pakProfileScreenState->root, playerIndex, Node_FindWidgetByResourceId(g_pakProfileScreenState->players[playerIndex].menuWidget, UI_CASE_16_2B9));
        slotLabelResourceId = UI_CASE_16_2BA;

        panelWidget = g_pakProfileScreenState->players[playerIndex].menuWidget;
        selectionOrLabel = g_pakProfileScreenState->players[playerIndex].record;
block_61:

        (((MenuWidget *)(Node_FindWidgetByResourceId(panelWidget, slotLabelResourceId)))->text) = (&g_pakProfileScreenState->players[playerIndex])->slots[selectionOrLabel];
        goto block_84;
    case 21:

        missingSavePanel = Node_FindWidgetByResourceId(g_pakProfileScreenState->players[playerIndex].sprite, UI_CASE_21_2E1);
        g_pakProfileScreenState->players[playerIndex].menuWidget = missingSavePanel;
        Widget_SetWidgetFlag08(missingSavePanel, 1);
        SmpOverlay_ShowSlotNode(g_pakProfileScreenState->root, playerIndex, Node_FindWidgetByResourceId(g_pakProfileScreenState->players[playerIndex].menuWidget, UI_CASE_21_2E2));
        break;
    case 23:

        stateTwentyThreePanel = Node_FindWidgetByResourceId(g_pakProfileScreenState->players[playerIndex].sprite, UI_CASE_23_2AC);
        g_pakProfileScreenState->players[playerIndex].menuWidget = stateTwentyThreePanel;
        Widget_SetWidgetFlag08(stateTwentyThreePanel, 1);
        SmpOverlay_ShowSlotNode(g_pakProfileScreenState->root, playerIndex, Node_FindWidgetByResourceId(g_pakProfileScreenState->players[playerIndex].menuWidget, UI_CASE_23_2AE));
        break;
    case 24:

        fullProfilesPanel = Node_FindWidgetByResourceId(g_pakProfileScreenState->players[playerIndex].sprite, UI_CASE_24_2A9);
        g_pakProfileScreenState->players[playerIndex].menuWidget = fullProfilesPanel;
        Widget_SetWidgetFlag08(fullProfilesPanel, 1);
        SmpOverlay_ShowSlotNode(g_pakProfileScreenState->root, playerIndex, Node_FindWidgetByResourceId(g_pakProfileScreenState->players[playerIndex].menuWidget, UI_CASE_24_2AA));
        break;
    case 25:

        unavailableProfilesPanel = Node_FindWidgetByResourceId(g_pakProfileScreenState->players[playerIndex].sprite, UI_CASE_25_2EA);
        g_pakProfileScreenState->players[playerIndex].menuWidget = unavailableProfilesPanel;
        Widget_SetWidgetFlag08(unavailableProfilesPanel, 1);
        SmpOverlay_ShowSlotNode(g_pakProfileScreenState->root, playerIndex, Node_FindWidgetByResourceId(g_pakProfileScreenState->players[playerIndex].menuWidget, UI_CASE_25_2EB));
        break;
    case 26:

        stateTwentySixPanel = Node_FindWidgetByResourceId(g_pakProfileScreenState->players[playerIndex].sprite, UI_CASE_26_2A6);
        g_pakProfileScreenState->players[playerIndex].menuWidget = stateTwentySixPanel;
        Widget_SetWidgetFlag08(stateTwentySixPanel, 1);
        SmpOverlay_ShowSlotNode(g_pakProfileScreenState->root, playerIndex, Node_FindWidgetByResourceId(g_pakProfileScreenState->players[playerIndex].menuWidget, UI_CASE_26_2A7));
        break;
case27_found:
        SmpOverlay_ShowSlotById((s32) g_pakProfileScreenState->windowAddress, playerIndex, slotLabelId);
        goto case27_done;
    case 27:
        Widget_SetWidgetFlag08((SlotSelectionWidget *) g_pakProfileScreenState->players[playerIndex].menuWidget, 1);
        itemIndex = 0;

        SmpOverlay_ShowSlotById((s32) g_pakProfileScreenState->windowAddress, playerIndex, PAK_CHECK_LABEL_ID(0));
        do {
loop_69:
        if (itemIndex == 1) {
            goto case27_one;
        }
        if (itemIndex >= 2) {
            goto case27_check_two;
        }
        if (itemIndex == 0) {
            goto case27_zero;
        }
        slotLabelId = CHECK_DEFAULT_ID;
        goto case27_selected;
case27_check_two:
        if (itemIndex == 2) {
            goto case27_two;
        }
        slotLabelId = CHECK_DEFAULT_ID;
        goto case27_selected;
case27_zero:
        slotLabelId = PAK_CHECK_LABEL_ID(0);
        goto case27_selected;
case27_one:
        slotLabelId = PAK_CHECK_LABEL_ID(1);
        goto case27_selected;
case27_two:
        slotLabelId = PAK_CHECK_LABEL_ID(2);
case27_selected:
        slot_active = Control_IsControllerConnected(itemIndex);
        itemIndex += 1;
        if (slot_active == 1) {
            goto case27_found;
        }
        } while (itemIndex < 4);
case27_done:
        PAKInterface_UpdatePlayerControlRows(playerIndex);
        playerLinkOffset = playerIndex * 8;
        break;
    case 28:

        stateTwentyEightPanel = Node_FindWidgetByResourceId(g_pakProfileScreenState->players[playerIndex].sprite, UI_CASE_28_2DE);
        g_pakProfileScreenState->players[playerIndex].menuWidget = stateTwentyEightPanel;
        Widget_SetWidgetFlag08(stateTwentyEightPanel, 1);
        SmpOverlay_ShowSlotNode(g_pakProfileScreenState->root, playerIndex, Node_FindWidgetByResourceId(g_pakProfileScreenState->players[playerIndex].menuWidget, UI_CASE_28_2DF));
        break;
    case 29:

        stateTwentyNinePanel = Node_FindWidgetByResourceId(g_pakProfileScreenState->players[playerIndex].sprite, UI_CASE_29_2BF);
        g_pakProfileScreenState->players[playerIndex].menuWidget = stateTwentyNinePanel;
        Widget_SetWidgetFlag08(stateTwentyNinePanel, 1);
        SmpOverlay_ShowSlotNode(g_pakProfileScreenState->root, playerIndex, Node_FindWidgetByResourceId(g_pakProfileScreenState->players[playerIndex].menuWidget, UI_CASE_29_2C0));
        playerLinkOffset = playerIndex * 8;
        break;
    default:
block_84:
        playerLinkOffset = playerIndex * 8;
        break;
    }
    ((SetupLinkedLabel *)g_pakProfileScreenState->players[playerIndex].menuWidget)->alpha = 150;
}

/* Animates the four pak player panels: an idle panel pulses its labels, a panel in name entry bobs its slot value and
   steps the name character after six frames of the spin phase, and a panel browsing notes bobs the selected note
   label; every player's animation clock (selected[player] of the screen state) then advances by phaseStep. */
void PAKInterface_UpdatePlayerPanelAnimations(s32 phaseStep) {
    ResourceSmpFlickerCreateFlickerWidget *animatedLabel;
    PakProfilePanelState *panel;
    f32 bobValue;
    s32 player;

    for (player = 0; player < 4; player++) {
        panel = &g_pakProfileScreenState->players[player];
        switch (panel->state) {
        case 0:
            PAKInterface_PulseIdlePanelLabels(player);
            break;
        case 12:
            animatedLabel = SmpOverlay_GetSlotValue(g_pakProfileScreenState->root, player);
            bobValue = (Math_Cosf((f32)player + ((f32)g_pakProfileScreenState->selected[player] * 0.005f)) * 100.0f) + 150.0f;
            animatedLabel->value = bobValue;
            switch (panel->namePhase) {
            case 0:
                panel->nameTimer += 1;
                if (panel->nameTimer >= 6) {
                    PAKInterface_DecrementNameCharacter(player);
                }
                break;
            case 1:
                panel->nameTimer += 1;
                if (panel->nameTimer >= 6) {
                    PAKInterface_IncrementNameCharacter(player);
                }
                break;
            case 2:
                break;
            }
            break;
        case 4:
            animatedLabel = (ResourceSmpFlickerCreateFlickerWidget *)panel->labels[panel->slot - panel->scroll];
            bobValue = (Math_Cosf((f32)player + ((f32)g_pakProfileScreenState->selected[player] * 0.005f)) * 100.0f) + 150.0f;
            animatedLabel->value = bobValue;
            break;
        }
        g_pakProfileScreenState->selected[player] += phaseStep;
    }
}

/* Updates a player menu state from controller status, available saves, and the current menu phase. */

void PAKInterface_ResolvePlayerPakState(s32 player)
{
  s32 random;
  s32 done = 1;
  s32 result;
  s32 status = Note_GetStatus(player);
  short one = done;
  do
  {
    switch (status)
    {
      case -4:

      case -3:

      case -1:
        g_pakProfileScreenState->players[player].state = 3;
        break;

      case 0:
        if (g_pakProfileScreenState->phase == 6)
      {
        g_pakProfileScreenState->players[player].state = g_pakProfileScreenState->players[player].next;
      }
      else
#if defined(VERSION_EU) || defined(VERSION_EU_X)
        if (Note_FindNoteByName(((g_pakProfileGameNames)[g_languageIndex]), player, &result) == one)
#else
        if (Note_FindNoteByName((g_pakProfileGameNameFixed), player, &result) == one)
#endif
      {
        if (PAKInterface_ReadRecordsNote(player, result) == one)
        {
          g_pakProfileScreenState->players[player].state = g_pakProfileScreenState->players[player].next;
          switch (g_pakProfileScreenState->phase)
          {
            case 0:
              if (PAKInterface_FindEmptyProfileSlot(player) == (-1))
            {
              g_pakProfileScreenState->players[player].state = 24;
            }
              break;

            case 7:
              if (PAKInterface_AreProfileSlotsEmpty(player) == one)
            {
              g_pakProfileScreenState->players[player].state = 15;
            }
              break;

            case 2:
              if (PAKInterface_AreProfileSlotsEmpty(player) == one)
            {
              g_pakProfileScreenState->players[player].state = 25;
            }
            else
              if ((g_pakProfileScreenState->players[player].host == one) && (PAKInterface_FindEmptyProfileSlot(player) == (-1)))
            {
              g_pakProfileScreenState->players[player].state = 24;
            }
              break;

            case 5:
              if (Frontend_CheckOwnedProfileIds(player) == 0)
            {
              g_pakProfileScreenState->players[player].state = 21;
            }
              break;

          }

        }
      }
      else
      {
        switch (g_pakProfileScreenState->phase)
        {
          case 0:

          case 1:

          case 7:
            random = Graphu64_NextRandom();
            g_pakProfileScreenState->players[player].state = 15;
            g_pakProfileScreenState->players[player].profile = (random % 9999999) + 1;
            break;

          case 5:
            g_pakProfileScreenState->players[player].state = 21;
            break;

          case 4:
            g_pakProfileScreenState->players[player].state = g_pakProfileScreenState->players[player].next;
            break;

          case 2:

          case 3:
            g_pakProfileScreenState->players[player].state = 25;
            break;

        }

      }
        break;

      case -5:

      case -2:

      default:
        g_pakProfileScreenState->players[player].state = one;
        break;

    }

  }
  while (done == 0);
  PAKInterface_RefreshPlayerPanel(player);
}

#if defined(VERSION_DE) || defined(VERSION_US) || defined(VERSION_US_REV1)
extern const unsigned char g_noteInfoIntFormat[3];
#endif

/* Builds a player's controller pak note list: each of the sixteen notes gets its name (a default when unnamed), its size and a numbered label with the extension when it has one, or empty entries once the pak cannot be read; then the free and used page counts are formatted into their menu items, and on any read failure the slot is marked failed instead of opening the note menu. */
#if defined(VERSION_DE)
enum { PAK_RESOURCE_2D7 = 750, PAK_RESOURCE_2D8 = 749, PAK_RESOURCE_2DB = 746, PAK_RESOURCE_2DC = 745, PAK_RESOURCE_2DD = 747 };
#elif defined(VERSION_EU)

enum { PAK_RESOURCE_2D7 = 727, PAK_RESOURCE_2D8 = 728, PAK_RESOURCE_2DB = 731, PAK_RESOURCE_2DC = 732, PAK_RESOURCE_2DD = 733 };
#elif defined(VERSION_EU_X)

enum { PAK_RESOURCE_2D7 = 753, PAK_RESOURCE_2D8 = 751, PAK_RESOURCE_2DB = 754, PAK_RESOURCE_2DC = 755, PAK_RESOURCE_2DD = 756 };
#else
enum { PAK_RESOURCE_2D7 = 727, PAK_RESOURCE_2D8 = 728, PAK_RESOURCE_2DB = 731, PAK_RESOURCE_2DC = 732, PAK_RESOURCE_2DD = 733 };
#endif

#if !defined(VERSION_EU) && !defined(VERSION_EU_X)
static const char controller_pak_note_label_format[] = "%d.%s.%s";
#endif

void PAKInterface_LoadNoteList(s32 player)
{
    char name[24];
    u8 ext[8];
    char extra1[8];
    char extra2[8];
    s32 status;
    s32 size;
    s32 failed;
    s32 i;
    Label *item;
    s32 note_status;

#if defined(VERSION_EU) || defined(VERSION_EU_X)
    GameLocalizationState *settings;

#else
#endif
    failed = 0;
    for (i = 0; i < 16 && failed == 0; i++) {
        note_status = Note_ReadNoteInfo(player, i, &status, name, ext, &size, extra1, extra2);

#if defined(VERSION_EU) || defined(VERSION_EU_X)
        settings = (GameLocalizationState *)&g_gameSettings;

#else
#endif
        if (note_status == 0) {
            if (status == 1) {
                if (Note_ContainsInvalidNameByte(name, 16) == 1) {
#if defined(VERSION_EU)
                    XPlus_CopyString(name, ((g_pakDefaultNoteNamesLocalized)[settings->language]));
#elif defined(VERSION_EU_X)
                    XPlus_CopyString(name, ((g_pakUnnamedNoteTextsEuX)[settings->language]));
#else
                    XPlus_CopyString(name, (g_pakDefaultNoteNameFixed));
#endif
                }
                XPlus_CopyString(g_pakProfileScreenState->players[player].noteTexts[i].name, name);
                XStdio_FormatBuffer(g_pakProfileScreenState->players[player].noteTexts[i].size,
#if defined(VERSION_EU) || defined(VERSION_EU_X)
s_pakNoteSizeFormatEuropean,
#else
g_noteInfoIntFormat,
#endif
 size);
                if (ext[0] != 0) {
                    XStdio_FormatBuffer(g_pakProfileScreenState->players[player].noteTexts[i].label,
#if defined(VERSION_EU) || defined(VERSION_EU_X)
s_pakNoteExtendedLabelFormatEuropean,
#else
controller_pak_note_label_format,
#endif
 i + 1,
                                  g_pakProfileScreenState->players[player].noteTexts[i].name, ext);
                    continue;
                }
                goto numbered;
            }
        } else {
            failed = 1;
        }
#if defined(VERSION_EU)
        XPlus_CopyString(g_pakProfileScreenState->players[player].noteTexts[i].name, ((g_slotEmptyNameByLanguageEu)[settings->language]));
#elif defined(VERSION_EU_X)
        XPlus_CopyString(g_pakProfileScreenState->players[player].noteTexts[i].name, ((g_slotEmptyNameByLanguageEuX)[settings->language]));
#else
        XPlus_CopyString(g_pakProfileScreenState->players[player].noteTexts[i].name, ((char *)g_slotRankNamePointers_Empty[0]));
#endif
        XStdio_FormatBuffer(g_pakProfileScreenState->players[player].noteTexts[i].size,
#if defined(VERSION_EU) || defined(VERSION_EU_X)
s_pakNoteSizeFormatEuropean,
#else
g_noteInfoIntFormat,
#endif
 0);
    numbered:
        XStdio_FormatBuffer(g_pakProfileScreenState->players[player].noteTexts[i].label,
#if defined(VERSION_EU) || defined(VERSION_EU_X)
s_pakNoteLabelFormatEuropean,
#else
s_pakNoteSizeFormatEuropean,
#endif
 i + 1,
                      g_pakProfileScreenState->players[player].noteTexts[i].name);
    }
    if (failed == 0) {
        /* the hub EC30 returns the item view; Label is this unit's text-bearing view of it */
        item = (Label *)Node_FindWidgetByResourceId(g_pakProfileScreenState->players[player].menuWidget, PAK_RESOURCE_2D8);
        if (Note_GetFreePages(player, &size) == 0) {
            XStdio_FormatBuffer(g_pakProfileScreenState->players[player].freeText,
#if defined(VERSION_EU) || defined(VERSION_EU_X)
s_pakNoteSizeFormatEuropean,
#else
g_noteInfoIntFormat,
#endif
 size);
            item->text = g_pakProfileScreenState->players[player].freeText;
            item = (Label *)Node_FindWidgetByResourceId(g_pakProfileScreenState->players[player].menuWidget, PAK_RESOURCE_2D7);
            size = PAKInterface_GetRecordsNoteSize();
            XStdio_FormatBuffer(g_pakProfileScreenState->players[player].usedText,
#if defined(VERSION_EU) || defined(VERSION_EU_X)
s_pakNoteSizeFormatEuropean,
#else
g_noteInfoIntFormat,
#endif
 Note_BytesToPakPages(size));
            item->text = g_pakProfileScreenState->players[player].usedText;
        } else {
            failed = 1;
        }
    }
    if (failed == 1) {
        g_pakProfileScreenState->players[player].state = failed;
        PAKInterface_RefreshPlayerPanel(player);
        return;
    }
    g_pakProfileScreenState->players[player].slot = -1;
    g_pakProfileScreenState->players[player].scroll = 0;
    g_pakProfileScreenState->players[player].labels[0] = Node_FindWidgetByResourceId(g_pakProfileScreenState->players[player].menuWidget, PAK_RESOURCE_2DB);
    g_pakProfileScreenState->players[player].labels[1] = Node_FindWidgetByResourceId(g_pakProfileScreenState->players[player].menuWidget, PAK_RESOURCE_2DC);
    g_pakProfileScreenState->players[player].labels[2] = Node_FindWidgetByResourceId(g_pakProfileScreenState->players[player].menuWidget, PAK_RESOURCE_2DD);
    PAKInterface_ScrollNoteList(player, 1);
}

#if !(defined(VERSION_US_REV1))
#if defined(VERSION_DE) || defined(VERSION_US)
const char s_pakNoteLabelFormat[6] =
    "%d.%s";
#endif
#if defined(VERSION_EU) || defined(VERSION_EU_X)
const char s_pakNoteLabelFormat[3] =
    "%d";
#endif
#endif

#if defined(VERSION_US_REV1)

#endif

/* PAKInterface_PulseIdlePanelLabels reads floats at +0, +4, +8 and +12.
 * The aliases for phase and bias keep their original addresses. */
typedef struct PakPanelPulseConstants {
    f32 phaseScale;
    f32 amplitude;
    f32 bias;
    f32 unsignedConversionThreshold;
} PakPanelPulseConstants;
typedef char PakPanelPulseConstantsSize[(sizeof(PakPanelPulseConstants) == 16) ? 1 : -1];
const PakPanelPulseConstants g_pakIdlePanelPulseConstants = {
    0.0033333334140479565f, 100.0f, 150.0f, 2147483648.0f,
};

/* Enters the selected menu state and resolves the default destination from the game mode. */

void PAKInterface_BeginScreenExit(s32 focusEntry) {
    s32 unusedExitResult;

    Tsmos_DeactivateControllerState();
    g_pakProfileScreenState->ready = 5;
    g_pakProfileScreenState->timer = 4;
    g_pakProfileScreenState->focus = focusEntry;
    if (focusEntry == -2) {
        switch(g_gameSettings.controllerMode) {
        case 0:g_pakProfileScreenState->focus=7;break;
        case 2:g_pakProfileScreenState->focus=7;break;
        case 1:g_pakProfileScreenState->focus=9;break;
        case 3:g_pakProfileScreenState->focus=7;break;
        case 4:g_pakProfileScreenState->focus=10;break;
        }
    }
}

#if defined(VERSION_US)
extern char k_PakinterfaceBeginscreenexitData[4];
#endif

#if defined(VERSION_EU_X)
extern unsigned int g_pakBeginScreenExitUnreferencedWordsEuX[1];
#endif

#if defined(VERSION_EU)
extern unsigned int g_pakBeginScreenExitUnreferencedWordsEu[1];
#endif

#if defined(VERSION_DE)
extern unsigned int g_pakBeginScreenExitUnreferencedWordsDe[1];
#endif

/* Does nothing. Nothing in the cartridge image calls it or stores its address as a word. */
void PAKInterface_ReturnWithoutAction(void) {
}

#if defined(VERSION_EU)
/* Picks the label for each of the eight option rows (ids 2..9): the row's enabled text when its flag is set, else its disabled text. */
typedef struct { s32 id; u8 pad4[0x10]; char ***text; } OptionRowEu;
s32 Items_SelectOptionRowLabel(OptionRowEu *row) {
    switch (row->id) {
    default:
    case 2:
        if (g_pakScreenOptionRowEnabledFlags[0]) {
            row->text = g_europeanMenuToggleRowTexts[0][0];
        } else {
            row->text = g_europeanMenuToggleRowTexts[0][1];
        }
        break;
    case 3:
        if (g_pakScreenOptionRowEnabledFlags[1]) {
            row->text = g_europeanMenuToggleRowTexts[1][0];
        } else {
            row->text = g_europeanMenuToggleRowTexts[1][1];
        }
        break;
    case 4:
        if (g_pakScreenOptionRowEnabledFlags[2]) {
            row->text = g_europeanMenuToggleRowTexts[2][0];
        } else {
            row->text = g_europeanMenuToggleRowTexts[2][1];
        }
        break;
    case 5:
        if (g_pakScreenOptionRowEnabledFlags[3]) {
            row->text = g_europeanMenuToggleRowTexts[3][0];
        } else {
            row->text = g_europeanMenuToggleRowTexts[3][1];
        }
        break;
    case 6:
        if (g_pakScreenOptionRowEnabledFlags[4]) {
            row->text = g_europeanMenuToggleRowTexts[4][0];
        } else {
            row->text = g_europeanMenuToggleRowTexts[4][1];
        }
        break;
    case 7:
        if (g_pakScreenOptionRowEnabledFlags[5]) {
            row->text = g_europeanMenuToggleRowTexts[5][0];
        } else {
            row->text = g_europeanMenuToggleRowTexts[5][1];
        }
        break;
    case 8:
        if (g_pakScreenOptionRowEnabledFlags[6]) {
            row->text = g_europeanMenuToggleRowTexts[6][0];
        } else {
            row->text = g_europeanMenuToggleRowTexts[6][1];
        }
        break;
    case 9:
        if (g_pakScreenOptionRowEnabledFlags[8]) {
            row->text = g_europeanMenuToggleRowTexts[7][0];
        } else {
            row->text = g_europeanMenuToggleRowTexts[7][1];
        }
        break;
    }
    return 0;
}
#endif
#if defined(VERSION_EU_X)
#include "types.h"
#include "Ui/ui_address_symbols.h"
#endif

#if !(defined(VERSION_US))
#if !(defined(VERSION_DE) || defined(VERSION_EU) || defined(VERSION_EU_X) || defined(VERSION_US))

#endif
#endif
#if defined(VERSION_EU_X)

#endif
#if defined(VERSION_EU)

#endif
#if defined(VERSION_DE) || defined(VERSION_US)
#if defined(VERSION_US)

#endif
#endif

#if defined(VERSION_EU) || defined(VERSION_EU_X)
/* Typed view of the storage a menu binding points at; the binding's type code selects the member. */
typedef union BoundStorageView {
    void *raw;
    f32 *asF32;
    s8 *asS8;
    s16 *asS16;
    s32 *asS32;
    u8 *asU8;
    u16 *asU16;
    u32 *asU32;
} BoundStorageView;

/* Reads the number a menu item is bound to, converting its stored scalar type to float. */
f32 Bound_ReadBoundValue(MenuBindingItemView *item) {
    Binding *binding = item->binding;
    BoundStorageView storage;
    storage.raw = binding->storage();

    switch (binding->type) {
    case 0: return *storage.asF32;
    case 3: return *storage.asS8;
    case 4: return *storage.asS16;
    case 1: case 2: case 5: return *storage.asS32;
    case 6: return *storage.asU8;
    case 7: return *storage.asU16;
    case 8: return *storage.asU32;
    default: return 0.0f;
    }
}

/* Writes a numeric menu value through its bound storage callback using the selected scalar type. */
void Bound_WriteBoundValue(MenuBindingItemView *item, f32 value) {
    Binding *binding = item->binding;
    BoundStorageView storage;
    storage.raw = binding->storage();

    switch (binding->type) {
    case 0: *storage.asF32 = value; return;
    case 3: *storage.asS8 = (s32)value; return;
    case 4: *storage.asS16 = (s32)value; return;
    case 1: case 2: case 5: *storage.asS32 = (s32)value; return;
    case 6: *storage.asU8 = (u32)value; return;
    case 7: *storage.asU16 = (u32)value; return;
    case 8: *storage.asU32 = (u32)value; return;
    }
}
#endif
/* Calls Gobjinst_DrawMaskedModelWithLighting with its three arguments and the table g_defaultParticleLighting as the fourth. */

#if defined(VERSION_EU) || defined(VERSION_EU_X)
void Bound_DrawActorWithMenuLighting(void *first, void *second, void *third) {
    Gobjinst_DrawMaskedModelWithLighting(first, second, third, &g_defaultParticleLighting);
}
#endif

#if defined(VERSION_EU) || defined(VERSION_EU_X)
void Bound_DrawActorWithRedMenuEffect(ObjectItemsDrawActorWithRedMenuEffect *object, void *context, void *lookup) {
 g_menuModelFillEnabled=3;
 object->view[g_lightingBufferIndex]=g_defaultParticleLighting;
 g_menuModelFillColor[0]=(255.0f);
 g_menuModelFillColor[1]=0;
 g_menuModelFillColor[2]=0;
 g_menuModelFillColor[4]=0;
 g_menuModelFillColor[3]=(float)(g_menuTintAlpha/2);
 Gobjinst_DrawActorModelWithViewEffects(object,context,lookup);
 g_menuModelFillEnabled=0;
}
#endif
#if defined(VERSION_EU_X)

#endif
#if defined(VERSION_EU)

#endif

#if defined(VERSION_US)
unsigned int g_InitialOpentrackpreviewmenuTrailingWordUs[1] = {
    0x000A080C,
};
#endif
#if defined(VERSION_US_REV1)
EventHandlerRecord g_playerSettingsCreateEventRecord[1] = {
    { 3590, 5, g_Player_InitPlayerSettingsScreenAddress },
};
EventHandlerRecord g_playerSettingsEventHandlerRecords[7] = {
    { 3587, 5, g_Player_FreePlayerSettingsScreenAddress },
    { 10, 5, g_playerSettingsUnhandledEventCallbackAddress },
    { 2, 5, g_Player_CancelPlayerSettingsEntryAddress },
    { 1, 5, g_Player_ConfirmPlayerSettingsEntryAddress },
    { 8, 94, g_Player_SelectNextPlayerSettingsEntryAddress },
    { 7, 94, g_Player_SelectPreviousPlayerSettingsEntryAddress },
    { 0, 0, 0 },
};
EventHandlerRecord g_alternatePlayerSettingsEventHandlerRecords[9] = {
    { 3591, 12, g_alternatePlayerSettingsUnhandledEventCallbackAddress },
    { 3592, 12, g_alternatePlayerSettingsUnhandledEventCallbackAddressUsRev1Alternate },
    { 3590, 12, g_Player_BuildItemLabelListAddress },
    { 3587, 12, g_Player_FreeAlternatePlayerSettingsScreenAddress },
    { 2, 12, g_Player_CancelAlternatePlayerSettingsEntryAddress },
    { 1, 12, g_Player_ConfirmAlternatePlayerSettingsEntryAddress },
    { 8, 454, g_Player_SelectNextAlternatePlayerSettingsEntryAddress },
    { 7, 454, g_Player_SelectPreviousAlternatePlayerSettingsEntryAddress },
    { 0, 0, 0 },
};
extern char g_playerSettingsPackedTextFragment[4];
#endif


#if defined(VERSION_DE) || defined(VERSION_US)
#if defined(VERSION_US)
s32 Items_SelectToggleRowTextGerman(TextBoundsText *textRow) {
    s32 toggleRow;

    toggleRow = textRow->value;
    switch (toggleRow) {
    case 2:
    default:
        if (g_gameSettings.menuToggles[0] != 0) {
            textRow->text = &g_menuToggleChargeDartRifleEnabledText;
        } else {
            textRow->text = &g_menuToggleChargeDartRifleDisabledText;
        }
        break;
    case 3:
        if (g_gameSettings.menuToggles[1] != 0) {
            textRow->text = &g_menuToggleFirestormEnabledText;
        } else {
            textRow->text = &g_menuToggleFirestormDisabledText;
        }
        break;
    case 4:
        if (g_gameSettings.menuToggles[2] != 0) {
            textRow->text = &g_menuToggleAssaultRifleEnabledText;
        } else {
            textRow->text = &g_menuToggleAssaultRifleDisabledText;
        }
        break;
    case 5:
        if (g_gameSettings.menuToggles[3] != 0) {
            textRow->text = &g_menuTogglePlasmaRifleEnabledText;
        } else {
            textRow->text = &g_menuTogglePlasmaRifleDisabledText;
        }
        break;
    case 6:
        if (g_gameSettings.menuToggles[4] != 0) {
            textRow->text = &g_menuToggleCerebralBoreEnabledText;
        } else {
            textRow->text = &g_menuToggleCerebralBoreDisabledText;
        }
        break;
    case 7:
        if (g_gameSettings.menuToggles[5] != 0) {
            textRow->text = &g_menuToggleGrenadeLauncherEnabledText;
        } else {
            textRow->text = &g_menuToggleGrenadeLauncherDisabledText;
        }
        break;
    case 8:
        if (g_gameSettings.menuToggles[6] != 0) {
            textRow->text = &g_menuToggleScorpionLauncherEnabledText;
        } else {
            textRow->text = &g_menuToggleScorpionLauncherDisabledText;
        }
        break;
    case 9:
        if (g_gameSettings.menuToggles[8] != 0) {
            textRow->text = &g_menuToggleTorpedoLauncherEnabledText;
        } else {
            textRow->text = &g_menuToggleTorpedoLauncherDisabledText;
        }
        break;
    }
    return 0;
}
#endif
#endif

#if defined(VERSION_US)
/* Four player widget lists (19 slots each, last list omits its final slot),
 * fifteen 16-byte equipment choices and thirteen 12-byte event records.
 * Equip_LoadEquipmentSelections reads the choice at +8 with stride 16;
 * Player_CreateFourPlayerResults reads each widget id at +2, stride 4. */
typedef struct EquipmentChoiceRecord {
    u32 widgetId;
    u32 resourceId;
    s32 choice;
    const void *label;
} EquipmentChoiceRecord;
typedef struct EquipmentAndResultsMenuRecords {
    u32 widgetIds[75];
    EquipmentChoiceRecord choices[15];
    EventHandlerRecord eventHandlers[13];
} EquipmentAndResultsMenuRecords;
typedef char EquipmentChoiceRecordSize[(sizeof(EquipmentChoiceRecord) == 16) ? 1 : -1];
typedef char EquipmentMenuRecordsSize[(sizeof(EquipmentAndResultsMenuRecords) == 696) ? 1 : -1];
EquipmentAndResultsMenuRecords g_equipmentAndPlayerSettingsMenuDataEuX = {
    {
        0x00000132, 0x000000EA, 0x000000EB, 0x000000EC, 0x000000ED, 0x000000EE, 0x000000EF, 0x00000122,
        0x00000121, 0x00000120, 0x0000011F, 0x0000011E, 0x000000DE, 0x000000E0, 0x000000E2, 0x000000E4,
        0x000000E6, 0x000000E8, 0x000000F7, 0x00000133, 0x00000111, 0x00000112, 0x00000113, 0x00000114,
        0x00000115, 0x00000116, 0x00000128, 0x00000129, 0x0000012A, 0x0000012B, 0x0000012C, 0x000000FB,
        0x000000FD, 0x000000FF, 0x00000101, 0x00000103, 0x00000105, 0x000000CF, 0x00000134, 0x000000F0,
        0x000000F1, 0x000000F2, 0x000000F3, 0x000000F4, 0x000000F5, 0x00000131, 0x00000130, 0x0000012F,
        0x0000012E, 0x0000012D, 0x000000D3, 0x000000D5, 0x000000D7, 0x000000D9, 0x000000DB, 0x000000DD,
        0x000000F9, 0x00000135, 0x00000117, 0x00000118, 0x00000119, 0x0000011A, 0x0000011B, 0x0000011C,
        0x00000123, 0x00000124, 0x00000125, 0x00000126, 0x00000127, 0x00000106, 0x00000108, 0x0000010A,
        0x0000010C, 0x0000010E, 0x00000110,
    },
    {
        { 0x00000098, 0x00001397, 0x0000000A, g_weaponLockedNoticeText + 52 },
        { 0x000000AD, 0x00001396, 0x0000000C, g_weaponLockedNoticeText + 60 },
        { 0x000000AF, 0x000013AD, 0x0000000B, g_weaponLockedNoticeText + 56 },
        { 0x000000B3, 0x000013A9, 0x00000001, g_weaponLockedNoticeText + 16 },
        { 0x000000A2, 0x0000139B, 0x0000000F, g_weaponLockedNoticeText + 72 },
        { 0x0000009A, 0x000013A1, 0x0000000D, g_weaponLockedNoticeText + 64 },
        { 0x0000009B, 0x000013A2, 0x00000009, g_weaponLockedNoticeText + 48 },
        { 0x00000099, 0x0000139A, 0x00000008, g_weaponLockedNoticeText + 44 },
        { 0x000000AA, 0x0000138D, 0x0000000E, g_weaponLockedNoticeText + 68 },
        { 0x000000AE, 0x0000138F, 0x00000007, g_weaponLockedNoticeText + 40 },
        { 0x000000B0, 0x0000138C, 0x00000002, g_weaponLockedNoticeText + 20 },
        { 0x000000A9, 0x000013A7, 0x00000005, g_weaponLockedNoticeText + 32 },
        { 0x000000AB, 0x0000139E, 0x00000003, g_weaponLockedNoticeText + 24 },
        { 0x000000AC, 0x00001393, 0x00000006, g_weaponLockedNoticeText + 36 },
        { 0x000000B1, 0x0000138B, 0x00000004, g_weaponLockedNoticeText + 28 },
    },
    {
        { 0x00000E07, 0x00000008, (void *)&Player_StartFourPlayerResults },
        { 0x00000E08, 0x00000008, (void *)&Player_UpdateFourPlayerResults },
        { 0x00000E0A, 0x00000008, (void *)&Player_DrawFourPlayerResults },
        { 0x00000E06, 0x00000008, (void *)&Player_CreateFourPlayerResults },
        { 0x00000E03, 0x00000008, (void *)&Frontend_FreeEquipmentScreen },
        { 0x0000000A, 0x00000008, (void *)&Frontend_RestoreEquipmentSelections },
        { 0x00000002, 0x00000008, (void *)&Frontend_CancelEquipmentSelection },
        { 0x00000001, 0x00000008, (void *)&Frontend_ConfirmEquipmentSelection },
        { 0x00000007, 0x00007530, (void *)&Frontend_SelectPreviousEquipmentChoice },
        { 0x00000005, 0x00007530, (void *)&Frontend_SelectPreviousEquipmentColumn },
        { 0x00000008, 0x00007530, (void *)&Frontend_SelectNextEquipmentChoice },
        { 0x00000006, 0x00007530, (void *)&Frontend_SelectNextEquipmentColumn },
        { 0x00000000, 0x00000000, 0x00000000 },
    },
};
#endif
#if defined(VERSION_US_REV1)
EventHandlerRecord g_titleButtonEventHandlerRecords[7] = {
    { 3592, 30, g_Menu_UpdateTitleButtonScreenAddress },
    { 3590, 30, g_Menu_CreateTitleButtonScreenAddress },
    { 3591, 30, g_Menu_WrapTitleButtonScreenNodesAddress },
    { 3587, 30, g_Menu_FreeTitleButtonScreenAddress },
    { 1, 30, g_Menu_HandleTitleButtonChoiceAddress },
    { 2, 30, g_Menu_CancelTitleButtonScreenAddress },
    { 0, 0, 0 },
};
#endif

#if VERSION_US
/* Retained SN/Psy-Q object records, little endian. This is link metadata,
 * not a native menu record array. Code payloads retain their exact bytes.
 * The code payload continues in the following function. */
typedef struct SnFileName47Record { u8 opcode; SnLe16 file; u8 nameLength; u8 name[47]; } SnFileName47Record;
typedef struct SnFileName42Record { u8 opcode; SnLe16 file; u8 nameLength; u8 name[42]; } SnFileName42Record;
typedef struct SnFileName22Record { u8 opcode; SnLe16 file; u8 nameLength; u8 name[22]; } SnFileName22Record;
typedef struct SnFileName46Record { u8 opcode; SnLe16 file; u8 nameLength; u8 name[46]; } SnFileName46Record;
typedef struct SnFileName45Record { u8 opcode; SnLe16 file; u8 nameLength; u8 name[45]; } SnFileName45Record;
typedef struct SnFileName43Record { u8 opcode; SnLe16 file; u8 nameLength; u8 name[43]; } SnFileName43Record;
typedef struct SnFileName52Record { u8 opcode; SnLe16 file; u8 nameLength; u8 name[52]; } SnFileName52Record;
typedef struct SnFileName39Record { u8 opcode; SnLe16 file; u8 nameLength; u8 name[39]; } SnFileName39Record;
typedef struct SnFileName41Record { u8 opcode; SnLe16 file; u8 nameLength; u8 name[41]; } SnFileName41Record;
typedef struct SnFileName51Record { u8 opcode; SnLe16 file; u8 nameLength; u8 name[51]; } SnFileName51Record;
typedef struct SnFileName44Record { u8 opcode; SnLe16 file; u8 nameLength; u8 name[44]; } SnFileName44Record;
typedef struct SnFileName50Record { u8 opcode; SnLe16 file; u8 nameLength; u8 name[50]; } SnFileName50Record;
typedef struct SnFileName40Record { u8 opcode; SnLe16 file; u8 nameLength; u8 name[40]; } SnFileName40Record;
typedef struct SnFileName34Record { u8 opcode; SnLe16 file; u8 nameLength; u8 name[34]; } SnFileName34Record;
typedef struct SnFileName48Record { u8 opcode; SnLe16 file; u8 nameLength; u8 name[48]; } SnFileName48Record;
typedef struct SnFileName29Record { u8 opcode; SnLe16 file; u8 nameLength; u8 name[29]; } SnFileName29Record;
typedef struct SnFileName24Record { u8 opcode; SnLe16 file; u8 nameLength; u8 name[24]; } SnFileName24Record;
typedef struct SnFileName38Record { u8 opcode; SnLe16 file; u8 nameLength; u8 name[38]; } SnFileName38Record;
typedef struct SnFileName54Record { u8 opcode; SnLe16 file; u8 nameLength; u8 name[54]; } SnFileName54Record;
typedef struct SnFileName36Record { u8 opcode; SnLe16 file; u8 nameLength; u8 name[36]; } SnFileName36Record;
typedef struct SnFileName23Record { u8 opcode; SnLe16 file; u8 nameLength; u8 name[23]; } SnFileName23Record;
typedef struct SnFileName65Record { u8 opcode; SnLe16 file; u8 nameLength; u8 name[65]; } SnFileName65Record;
typedef struct SnFileName21Record { u8 opcode; SnLe16 file; u8 nameLength; u8 name[21]; } SnFileName21Record;
typedef struct SnFileName28Record { u8 opcode; SnLe16 file; u8 nameLength; u8 name[28]; } SnFileName28Record;
typedef struct SnFileName30Record { u8 opcode; SnLe16 file; u8 nameLength; u8 name[30]; } SnFileName30Record;
typedef struct SnFileName25Record { u8 opcode; SnLe16 file; u8 nameLength; u8 name[25]; } SnFileName25Record;
typedef struct SnFileName26Record { u8 opcode; SnLe16 file; u8 nameLength; u8 name[26]; } SnFileName26Record;
typedef struct SnSectionSwitchRecord { u8 opcode; SnLe16 section; } SnSectionSwitchRecord;
typedef struct SnCodeBlock4Record { u8 opcode; SnLe16 codeSize; u8 code[4]; } SnCodeBlock4Record;
typedef struct SnCodeBlock130Record { u8 opcode; SnLe16 codeSize; u8 code[130]; } SnCodeBlock130Record;
typedef struct SnCodeSizeRecord { u8 opcode; SnLe16 codeSize; } SnCodeSizeRecord;
typedef struct SnObjectRecords {
    u8 retainedCodeTail[261];
    SnFileName47Record record0;
    SnFileName42Record record1;
    SnFileName47Record record2;
    SnFileName22Record record3;
    SnFileName47Record record4;
    SnFileName46Record record5;
    SnFileName45Record record6;
    SnFileName46Record record7;
    SnFileName43Record record8;
    SnFileName52Record record9;
    SnFileName39Record record10;
    SnFileName39Record record11;
    SnFileName41Record record12;
    SnFileName39Record record13;
    SnFileName43Record record14;
    SnFileName52Record record15;
    SnFileName51Record record16;
    SnFileName52Record record17;
    SnFileName43Record record18;
    SnFileName44Record record19;
    SnFileName43Record record20;
    SnFileName50Record record21;
    SnFileName50Record record22;
    SnFileName50Record record23;
    SnFileName43Record record24;
    SnFileName43Record record25;
    SnFileName43Record record26;
    SnFileName40Record record27;
    SnFileName43Record record28;
    SnFileName34Record record29;
    SnFileName43Record record30;
    SnFileName39Record record31;
    SnFileName48Record record32;
    SnFileName43Record record33;
    SnFileName48Record record34;
    SnFileName39Record record35;
    SnFileName43Record record36;
    SnFileName29Record record37;
    SnFileName24Record record38;
    SnFileName29Record record39;
    SnFileName43Record record40;
    SnFileName42Record record41;
    SnFileName41Record record42;
    SnFileName42Record record43;
    SnFileName43Record record44;
    SnFileName43Record record45;
    SnFileName43Record record46;
    SnFileName38Record record47;
    SnFileName54Record record48;
    SnFileName38Record record49;
    SnFileName36Record record50;
    SnFileName41Record record51;
    SnFileName36Record record52;
    SnFileName38Record record53;
    SnFileName43Record record54;
    SnFileName40Record record55;
    SnFileName42Record record56;
    SnFileName23Record record57;
    SnFileName42Record record58;
    SnFileName65Record record59;
    SnFileName45Record record60;
    SnFileName65Record record61;
    SnFileName45Record record62;
    SnFileName65Record record63;
    SnFileName47Record record64;
    SnFileName46Record record65;
    SnFileName41Record record66;
    SnFileName46Record record67;
    SnFileName47Record record68;
    SnFileName65Record record69;
    SnFileName42Record record70;
    SnFileName47Record record71;
    SnFileName48Record record72;
    SnFileName47Record record73;
    SnFileName42Record record74;
    SnFileName44Record record75;
    SnFileName42Record record76;
    SnFileName65Record record77;
    SnFileName44Record record78;
    SnFileName44Record record79;
    SnFileName44Record record80;
    SnFileName65Record record81;
    SnFileName44Record record82;
    SnFileName44Record record83;
    SnFileName23Record record84;
    SnFileName44Record record85;
    SnFileName44Record record86;
    SnFileName42Record record87;
    SnFileName47Record record88;
    SnFileName42Record record89;
    SnFileName44Record record90;
    SnFileName46Record record91;
    SnFileName23Record record92;
    SnFileName24Record record93;
    SnFileName23Record record94;
    SnFileName46Record record95;
    SnFileName44Record record96;
    SnFileName46Record record97;
    SnFileName44Record record98;
    SnFileName65Record record99;
    SnFileName44Record record100;
    SnFileName42Record record101;
    SnFileName41Record record102;
    SnFileName40Record record103;
    SnFileName41Record record104;
    SnFileName45Record record105;
    SnFileName41Record record106;
    SnFileName43Record record107;
    SnFileName43Record record108;
    SnFileName43Record record109;
    SnFileName43Record record110;
    SnFileName43Record record111;
    SnFileName41Record record112;
    SnFileName42Record record113;
    SnFileName41Record record114;
    SnFileName42Record record115;
    SnFileName39Record record116;
    SnFileName36Record record117;
    SnFileName39Record record118;
    SnFileName44Record record119;
    SnFileName39Record record120;
    SnFileName21Record record121;
    SnFileName39Record record122;
    SnFileName22Record record123;
    SnFileName39Record record124;
    SnFileName42Record record125;
    SnFileName44Record record126;
    SnFileName43Record record127;
    SnFileName46Record record128;
    SnFileName24Record record129;
    SnFileName28Record record130;
    SnFileName24Record record131;
    SnFileName30Record record132;
    SnFileName24Record record133;
    SnFileName25Record record134;
    SnFileName24Record record135;
    SnFileName22Record record136;
    SnFileName24Record record137;
    SnFileName26Record record138;
    SnFileName24Record record139;
    SnFileName22Record record140;
    SnFileName24Record record141;
    SnFileName28Record record142;
    SnFileName24Record record143;
    SnFileName23Record record144;
    SnFileName23Record record145;
    SnFileName22Record record146;
    SnFileName23Record record147;
    SnFileName23Record record148;
    SnFileName23Record record149;
    SnFileName23Record record150;
    SnFileName24Record record151;
    SnFileName26Record record152;
    SnFileName24Record record153;
    SnFileName24Record record154;
    SnFileName24Record record155;
    SnFileName26Record record156;
    SnFileName24Record record157;
    SnFileName22Record record158;
    SnFileName24Record record159;
    SnFileName23Record record160;
    SnFileName25Record record161;
    SnFileName23Record record162;
    SnFileName24Record record163;
    SnFileName30Record record164;
    SnFileName24Record record165;
    SnFileName46Record record166;
    SnFileName47Record record167;
    SnFileName46Record record168;
    SnFileName43Record record169;
    SnFileName44Record record170;
    SnFileName65Record record171;
    SnSectionSwitchRecord record172;
    SnSectionSwitchRecord record173;
    SnSectionSwitchRecord record174;
    SnSectionSwitchRecord record175;
    SnSectionSwitchRecord record176;
    SnCodeBlock4Record record177;
    SnSectionSwitchRecord record178;
    SnSectionSwitchRecord record179;
    SnCodeBlock4Record record180;
    SnSectionSwitchRecord record181;
    SnCodeBlock130Record record182;
    SnSectionSwitchRecord record183;
    SnCodeSizeRecord record184;
} SnObjectRecords;
SnObjectRecords g_frontendMenuResourceWordsUs __attribute__((aligned(1))) = {
    { 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x0E, 0x0D, 0x5C, 0x80, 0x0E, 0x0D, 0x74, 0x80, 0x0E, 0x0D, 0x8C, 0x80, 0x0E, 0x0D, 0xA4, 0xB5, 0x00, 0x2E, 0x43, 0x3A, 0x5C, 0x50, 0x72, 0x6F, 0x6A, 0x65, 0x63, 0x74, 0x73, 0x5C, 0x44, 0x4D, 0x5C, 0x6E, 0x36, 0x34, 0x5C, 0x53, 0x6F, 0x75, 0x72, 0x63, 0x65, 0x5C, 0x45, 0x4E, 0x47, 0x49, 0x4E, 0x45, 0x5C, 0x43, 0x41, 0x43, 0x48, 0x45, 0x5C, 0x53, 0x59, 0x53, 0x52, 0x43, 0x2E, 0x48 },
    { 28, SN_LE16(180), 47, { 0x43, 0x3A, 0x5C, 0x50, 0x72, 0x6F, 0x6A, 0x65, 0x63, 0x74, 0x73, 0x5C, 0x44, 0x4D, 0x5C, 0x6E, 0x36, 0x34, 0x5C, 0x53, 0x6F, 0x75, 0x72, 0x63, 0x65, 0x5C, 0x45, 0x4E, 0x47, 0x49, 0x4E, 0x45, 0x5C, 0x43, 0x41, 0x43, 0x48, 0x45, 0x5C, 0x4C, 0x4F, 0x41, 0x44, 0x45, 0x52, 0x2E, 0x48 } },
    { 28, SN_LE16(179), 42, { 0x43, 0x3A, 0x5C, 0x50, 0x72, 0x6F, 0x6A, 0x65, 0x63, 0x74, 0x73, 0x5C, 0x44, 0x4D, 0x5C, 0x6E, 0x36, 0x34, 0x5C, 0x53, 0x6F, 0x75, 0x72, 0x63, 0x65, 0x5C, 0x45, 0x4E, 0x47, 0x49, 0x4E, 0x45, 0x5C, 0x54, 0x48, 0x52, 0x44, 0x50, 0x52, 0x49, 0x2E, 0x48 } },
    { 28, SN_LE16(178), 47, { 0x43, 0x3A, 0x5C, 0x50, 0x72, 0x6F, 0x6A, 0x65, 0x63, 0x74, 0x73, 0x5C, 0x44, 0x4D, 0x5C, 0x6E, 0x36, 0x34, 0x5C, 0x53, 0x6F, 0x75, 0x72, 0x63, 0x65, 0x5C, 0x45, 0x4E, 0x47, 0x49, 0x4E, 0x45, 0x5C, 0x43, 0x41, 0x43, 0x48, 0x45, 0x5C, 0x4C, 0x4F, 0x41, 0x44, 0x45, 0x52, 0x2E, 0x48 } },
    { 28, SN_LE16(177), 22, { 0x43, 0x3A, 0x5C, 0x4E, 0x36, 0x34, 0x5C, 0x49, 0x4E, 0x43, 0x4C, 0x55, 0x44, 0x45, 0x5C, 0x50, 0x52, 0x5C, 0x4F, 0x53, 0x2E, 0x48 } },
    { 28, SN_LE16(176), 47, { 0x43, 0x3A, 0x5C, 0x50, 0x72, 0x6F, 0x6A, 0x65, 0x63, 0x74, 0x73, 0x5C, 0x44, 0x4D, 0x5C, 0x6E, 0x36, 0x34, 0x5C, 0x53, 0x6F, 0x75, 0x72, 0x63, 0x65, 0x5C, 0x45, 0x4E, 0x47, 0x49, 0x4E, 0x45, 0x5C, 0x43, 0x41, 0x43, 0x48, 0x45, 0x5C, 0x4C, 0x4F, 0x41, 0x44, 0x45, 0x52, 0x2E, 0x48 } },
    { 28, SN_LE16(175), 46, { 0x43, 0x3A, 0x5C, 0x50, 0x72, 0x6F, 0x6A, 0x65, 0x63, 0x74, 0x73, 0x5C, 0x44, 0x4D, 0x5C, 0x6E, 0x36, 0x34, 0x5C, 0x53, 0x6F, 0x75, 0x72, 0x63, 0x65, 0x5C, 0x45, 0x4E, 0x47, 0x49, 0x4E, 0x45, 0x5C, 0x43, 0x41, 0x43, 0x48, 0x45, 0x5C, 0x53, 0x59, 0x53, 0x52, 0x43, 0x2E, 0x48 } },
    { 28, SN_LE16(174), 45, { 0x43, 0x3A, 0x5C, 0x50, 0x72, 0x6F, 0x6A, 0x65, 0x63, 0x74, 0x73, 0x5C, 0x44, 0x4D, 0x5C, 0x6E, 0x36, 0x34, 0x5C, 0x53, 0x6F, 0x75, 0x72, 0x63, 0x65, 0x5C, 0x45, 0x4E, 0x47, 0x49, 0x4E, 0x45, 0x5C, 0x43, 0x41, 0x43, 0x48, 0x45, 0x5C, 0x48, 0x45, 0x41, 0x50, 0x2E, 0x48 } },
    { 28, SN_LE16(173), 46, { 0x43, 0x3A, 0x5C, 0x50, 0x72, 0x6F, 0x6A, 0x65, 0x63, 0x74, 0x73, 0x5C, 0x44, 0x4D, 0x5C, 0x6E, 0x36, 0x34, 0x5C, 0x53, 0x6F, 0x75, 0x72, 0x63, 0x65, 0x5C, 0x45, 0x4E, 0x47, 0x49, 0x4E, 0x45, 0x5C, 0x43, 0x41, 0x43, 0x48, 0x45, 0x5C, 0x53, 0x59, 0x53, 0x52, 0x43, 0x2E, 0x48 } },
    { 28, SN_LE16(172), 43, { 0x43, 0x3A, 0x5C, 0x50, 0x72, 0x6F, 0x6A, 0x65, 0x63, 0x74, 0x73, 0x5C, 0x44, 0x4D, 0x5C, 0x6E, 0x36, 0x34, 0x5C, 0x53, 0x6F, 0x75, 0x72, 0x63, 0x65, 0x5C, 0x45, 0x4E, 0x47, 0x49, 0x4E, 0x45, 0x5C, 0x47, 0x45, 0x4F, 0x4D, 0x45, 0x54, 0x52, 0x59, 0x2E, 0x48 } },
    { 28, SN_LE16(171), 52, { 0x43, 0x3A, 0x5C, 0x50, 0x72, 0x6F, 0x6A, 0x65, 0x63, 0x74, 0x73, 0x5C, 0x44, 0x4D, 0x5C, 0x6E, 0x36, 0x34, 0x5C, 0x53, 0x6F, 0x75, 0x72, 0x63, 0x65, 0x5C, 0x45, 0x4E, 0x47, 0x49, 0x4E, 0x45, 0x5C, 0x49, 0x4E, 0x53, 0x54, 0x41, 0x4E, 0x43, 0x45, 0x5C, 0x47, 0x4F, 0x42, 0x4A, 0x49, 0x4E, 0x53, 0x54, 0x2E, 0x48 } },
    { 28, SN_LE16(170), 39, { 0x43, 0x3A, 0x5C, 0x50, 0x72, 0x6F, 0x6A, 0x65, 0x63, 0x74, 0x73, 0x5C, 0x44, 0x4D, 0x5C, 0x6E, 0x36, 0x34, 0x5C, 0x53, 0x6F, 0x75, 0x72, 0x63, 0x65, 0x5C, 0x41, 0x49, 0x5C, 0x57, 0x45, 0x41, 0x50, 0x4F, 0x4E, 0x41, 0x49, 0x2E, 0x48 } },
    { 28, SN_LE16(169), 39, { 0x43, 0x3A, 0x5C, 0x50, 0x72, 0x6F, 0x6A, 0x65, 0x63, 0x74, 0x73, 0x5C, 0x44, 0x4D, 0x5C, 0x6E, 0x36, 0x34, 0x5C, 0x53, 0x6F, 0x75, 0x72, 0x63, 0x65, 0x5C, 0x41, 0x49, 0x5C, 0x50, 0x4C, 0x41, 0x59, 0x45, 0x52, 0x41, 0x49, 0x2E, 0x48 } },
    { 28, SN_LE16(168), 41, { 0x43, 0x3A, 0x5C, 0x50, 0x72, 0x6F, 0x6A, 0x65, 0x63, 0x74, 0x73, 0x5C, 0x44, 0x4D, 0x5C, 0x6E, 0x36, 0x34, 0x5C, 0x53, 0x6F, 0x75, 0x72, 0x63, 0x65, 0x5C, 0x45, 0x4E, 0x47, 0x49, 0x4E, 0x45, 0x5C, 0x43, 0x50, 0x50, 0x55, 0x36, 0x34, 0x2E, 0x48 } },
    { 28, SN_LE16(167), 39, { 0x43, 0x3A, 0x5C, 0x50, 0x72, 0x6F, 0x6A, 0x65, 0x63, 0x74, 0x73, 0x5C, 0x44, 0x4D, 0x5C, 0x6E, 0x36, 0x34, 0x5C, 0x53, 0x6F, 0x75, 0x72, 0x63, 0x65, 0x5C, 0x41, 0x49, 0x5C, 0x50, 0x4C, 0x41, 0x59, 0x45, 0x52, 0x41, 0x49, 0x2E, 0x48 } },
    { 28, SN_LE16(166), 43, { 0x43, 0x3A, 0x5C, 0x50, 0x72, 0x6F, 0x6A, 0x65, 0x63, 0x74, 0x73, 0x5C, 0x44, 0x4D, 0x5C, 0x6E, 0x36, 0x34, 0x5C, 0x53, 0x6F, 0x75, 0x72, 0x63, 0x65, 0x5C, 0x45, 0x4E, 0x47, 0x49, 0x4E, 0x45, 0x5C, 0x50, 0x41, 0x52, 0x54, 0x49, 0x43, 0x4C, 0x45, 0x2E, 0x48 } },
    { 28, SN_LE16(165), 52, { 0x43, 0x3A, 0x5C, 0x50, 0x72, 0x6F, 0x6A, 0x65, 0x63, 0x74, 0x73, 0x5C, 0x44, 0x4D, 0x5C, 0x6E, 0x36, 0x34, 0x5C, 0x53, 0x6F, 0x75, 0x72, 0x63, 0x65, 0x5C, 0x45, 0x4E, 0x47, 0x49, 0x4E, 0x45, 0x5C, 0x49, 0x4E, 0x53, 0x54, 0x41, 0x4E, 0x43, 0x45, 0x5C, 0x41, 0x49, 0x4E, 0x53, 0x54, 0x48, 0x44, 0x52, 0x2E, 0x48 } },
    { 28, SN_LE16(164), 51, { 0x43, 0x3A, 0x5C, 0x50, 0x72, 0x6F, 0x6A, 0x65, 0x63, 0x74, 0x73, 0x5C, 0x44, 0x4D, 0x5C, 0x6E, 0x36, 0x34, 0x5C, 0x53, 0x6F, 0x75, 0x72, 0x63, 0x65, 0x5C, 0x45, 0x4E, 0x47, 0x49, 0x4E, 0x45, 0x5C, 0x49, 0x4E, 0x53, 0x54, 0x41, 0x4E, 0x43, 0x45, 0x5C, 0x49, 0x4E, 0x53, 0x54, 0x48, 0x44, 0x52, 0x2E, 0x48 } },
    { 28, SN_LE16(163), 52, { 0x43, 0x3A, 0x5C, 0x50, 0x72, 0x6F, 0x6A, 0x65, 0x63, 0x74, 0x73, 0x5C, 0x44, 0x4D, 0x5C, 0x6E, 0x36, 0x34, 0x5C, 0x53, 0x6F, 0x75, 0x72, 0x63, 0x65, 0x5C, 0x45, 0x4E, 0x47, 0x49, 0x4E, 0x45, 0x5C, 0x49, 0x4E, 0x53, 0x54, 0x41, 0x4E, 0x43, 0x45, 0x5C, 0x41, 0x49, 0x4E, 0x53, 0x54, 0x48, 0x44, 0x52, 0x2E, 0x48 } },
    { 28, SN_LE16(162), 43, { 0x43, 0x3A, 0x5C, 0x50, 0x72, 0x6F, 0x6A, 0x65, 0x63, 0x74, 0x73, 0x5C, 0x44, 0x4D, 0x5C, 0x6E, 0x36, 0x34, 0x5C, 0x53, 0x6F, 0x75, 0x72, 0x63, 0x65, 0x5C, 0x45, 0x4E, 0x47, 0x49, 0x4E, 0x45, 0x5C, 0x50, 0x41, 0x52, 0x54, 0x49, 0x43, 0x4C, 0x45, 0x2E, 0x48 } },
    { 28, SN_LE16(161), 44, { 0x43, 0x3A, 0x5C, 0x50, 0x72, 0x6F, 0x6A, 0x65, 0x63, 0x74, 0x73, 0x5C, 0x44, 0x4D, 0x5C, 0x6E, 0x36, 0x34, 0x5C, 0x53, 0x6F, 0x75, 0x72, 0x63, 0x65, 0x5C, 0x45, 0x4E, 0x47, 0x49, 0x4E, 0x45, 0x5C, 0x47, 0x44, 0x59, 0x4E, 0x4C, 0x49, 0x47, 0x48, 0x54, 0x2E, 0x48 } },
    { 28, SN_LE16(160), 43, { 0x43, 0x3A, 0x5C, 0x50, 0x72, 0x6F, 0x6A, 0x65, 0x63, 0x74, 0x73, 0x5C, 0x44, 0x4D, 0x5C, 0x6E, 0x36, 0x34, 0x5C, 0x53, 0x6F, 0x75, 0x72, 0x63, 0x65, 0x5C, 0x45, 0x4E, 0x47, 0x49, 0x4E, 0x45, 0x5C, 0x50, 0x41, 0x52, 0x54, 0x49, 0x43, 0x4C, 0x45, 0x2E, 0x48 } },
    { 28, SN_LE16(159), 50, { 0x43, 0x3A, 0x5C, 0x50, 0x72, 0x6F, 0x6A, 0x65, 0x63, 0x74, 0x73, 0x5C, 0x44, 0x4D, 0x5C, 0x6E, 0x36, 0x34, 0x5C, 0x53, 0x6F, 0x75, 0x72, 0x63, 0x65, 0x5C, 0x45, 0x4E, 0x47, 0x49, 0x4E, 0x45, 0x5C, 0x55, 0x4E, 0x49, 0x43, 0x4F, 0x4C, 0x5C, 0x43, 0x4F, 0x4C, 0x4C, 0x49, 0x4E, 0x46, 0x4F, 0x2E, 0x48 } },
    { 28, SN_LE16(158), 50, { 0x43, 0x3A, 0x5C, 0x50, 0x72, 0x6F, 0x6A, 0x65, 0x63, 0x74, 0x73, 0x5C, 0x44, 0x4D, 0x5C, 0x6E, 0x36, 0x34, 0x5C, 0x53, 0x6F, 0x75, 0x72, 0x63, 0x65, 0x5C, 0x45, 0x4E, 0x47, 0x49, 0x4E, 0x45, 0x5C, 0x55, 0x4E, 0x49, 0x43, 0x4F, 0x4C, 0x5C, 0x42, 0x45, 0x48, 0x41, 0x56, 0x49, 0x4F, 0x52, 0x2E, 0x48 } },
    { 28, SN_LE16(157), 50, { 0x43, 0x3A, 0x5C, 0x50, 0x72, 0x6F, 0x6A, 0x65, 0x63, 0x74, 0x73, 0x5C, 0x44, 0x4D, 0x5C, 0x6E, 0x36, 0x34, 0x5C, 0x53, 0x6F, 0x75, 0x72, 0x63, 0x65, 0x5C, 0x45, 0x4E, 0x47, 0x49, 0x4E, 0x45, 0x5C, 0x55, 0x4E, 0x49, 0x43, 0x4F, 0x4C, 0x5C, 0x43, 0x4F, 0x4C, 0x4C, 0x49, 0x4E, 0x46, 0x4F, 0x2E, 0x48 } },
    { 28, SN_LE16(156), 43, { 0x43, 0x3A, 0x5C, 0x50, 0x72, 0x6F, 0x6A, 0x65, 0x63, 0x74, 0x73, 0x5C, 0x44, 0x4D, 0x5C, 0x6E, 0x36, 0x34, 0x5C, 0x53, 0x6F, 0x75, 0x72, 0x63, 0x65, 0x5C, 0x45, 0x4E, 0x47, 0x49, 0x4E, 0x45, 0x5C, 0x50, 0x41, 0x52, 0x54, 0x49, 0x43, 0x4C, 0x45, 0x2E, 0x48 } },
    { 28, SN_LE16(155), 43, { 0x43, 0x3A, 0x5C, 0x50, 0x72, 0x6F, 0x6A, 0x65, 0x63, 0x74, 0x73, 0x5C, 0x44, 0x4D, 0x5C, 0x6E, 0x36, 0x34, 0x5C, 0x53, 0x6F, 0x75, 0x72, 0x63, 0x65, 0x5C, 0x45, 0x4E, 0x47, 0x49, 0x4E, 0x45, 0x5C, 0x50, 0x41, 0x52, 0x54, 0x54, 0x59, 0x50, 0x45, 0x2E, 0x48 } },
    { 28, SN_LE16(154), 43, { 0x43, 0x3A, 0x5C, 0x50, 0x72, 0x6F, 0x6A, 0x65, 0x63, 0x74, 0x73, 0x5C, 0x44, 0x4D, 0x5C, 0x6E, 0x36, 0x34, 0x5C, 0x53, 0x6F, 0x75, 0x72, 0x63, 0x65, 0x5C, 0x45, 0x4E, 0x47, 0x49, 0x4E, 0x45, 0x5C, 0x50, 0x41, 0x52, 0x54, 0x49, 0x43, 0x4C, 0x45, 0x2E, 0x48 } },
    { 28, SN_LE16(153), 40, { 0x43, 0x3A, 0x5C, 0x50, 0x72, 0x6F, 0x6A, 0x65, 0x63, 0x74, 0x73, 0x5C, 0x44, 0x4D, 0x5C, 0x6E, 0x36, 0x34, 0x5C, 0x53, 0x6F, 0x75, 0x72, 0x63, 0x65, 0x5C, 0x45, 0x4E, 0x47, 0x49, 0x4E, 0x45, 0x5C, 0x53, 0x43, 0x45, 0x4E, 0x45, 0x2E, 0x48 } },
    { 28, SN_LE16(152), 43, { 0x43, 0x3A, 0x5C, 0x50, 0x72, 0x6F, 0x6A, 0x65, 0x63, 0x74, 0x73, 0x5C, 0x44, 0x4D, 0x5C, 0x6E, 0x36, 0x34, 0x5C, 0x53, 0x6F, 0x75, 0x72, 0x63, 0x65, 0x5C, 0x45, 0x4E, 0x47, 0x49, 0x4E, 0x45, 0x5C, 0x52, 0x4F, 0x4D, 0x53, 0x54, 0x52, 0x55, 0x43, 0x2E, 0x48 } },
    { 28, SN_LE16(151), 34, { 0x43, 0x3A, 0x5C, 0x50, 0x72, 0x6F, 0x6A, 0x65, 0x63, 0x74, 0x73, 0x5C, 0x44, 0x4D, 0x5C, 0x6E, 0x36, 0x34, 0x5C, 0x53, 0x6F, 0x75, 0x72, 0x63, 0x65, 0x5C, 0x53, 0x54, 0x59, 0x50, 0x45, 0x53, 0x2E, 0x48 } },
    { 28, SN_LE16(150), 43, { 0x43, 0x3A, 0x5C, 0x50, 0x72, 0x6F, 0x6A, 0x65, 0x63, 0x74, 0x73, 0x5C, 0x44, 0x4D, 0x5C, 0x6E, 0x36, 0x34, 0x5C, 0x53, 0x6F, 0x75, 0x72, 0x63, 0x65, 0x5C, 0x45, 0x4E, 0x47, 0x49, 0x4E, 0x45, 0x5C, 0x52, 0x4F, 0x4D, 0x53, 0x54, 0x52, 0x55, 0x43, 0x2E, 0x48 } },
    { 28, SN_LE16(149), 39, { 0x43, 0x3A, 0x5C, 0x50, 0x72, 0x6F, 0x6A, 0x65, 0x63, 0x74, 0x73, 0x5C, 0x44, 0x4D, 0x5C, 0x6E, 0x36, 0x34, 0x5C, 0x53, 0x6F, 0x75, 0x72, 0x63, 0x65, 0x5C, 0x45, 0x4E, 0x47, 0x49, 0x4E, 0x45, 0x5C, 0x41, 0x4E, 0x49, 0x4D, 0x2E, 0x48 } },
    { 28, SN_LE16(148), 48, { 0x43, 0x3A, 0x5C, 0x50, 0x72, 0x6F, 0x6A, 0x65, 0x63, 0x74, 0x73, 0x5C, 0x44, 0x4D, 0x5C, 0x6E, 0x36, 0x34, 0x5C, 0x53, 0x6F, 0x75, 0x72, 0x63, 0x65, 0x5C, 0x45, 0x4E, 0x47, 0x49, 0x4E, 0x45, 0x5C, 0x41, 0x4E, 0x49, 0x4D, 0x5C, 0x41, 0x4E, 0x49, 0x4D, 0x53, 0x54, 0x52, 0x43, 0x2E, 0x48 } },
    { 28, SN_LE16(147), 43, { 0x43, 0x3A, 0x5C, 0x50, 0x72, 0x6F, 0x6A, 0x65, 0x63, 0x74, 0x73, 0x5C, 0x44, 0x4D, 0x5C, 0x6E, 0x36, 0x34, 0x5C, 0x53, 0x6F, 0x75, 0x72, 0x63, 0x65, 0x5C, 0x45, 0x4E, 0x47, 0x49, 0x4E, 0x45, 0x5C, 0x47, 0x52, 0x41, 0x50, 0x48, 0x55, 0x36, 0x34, 0x2E, 0x48 } },
    { 28, SN_LE16(146), 48, { 0x43, 0x3A, 0x5C, 0x50, 0x72, 0x6F, 0x6A, 0x65, 0x63, 0x74, 0x73, 0x5C, 0x44, 0x4D, 0x5C, 0x6E, 0x36, 0x34, 0x5C, 0x53, 0x6F, 0x75, 0x72, 0x63, 0x65, 0x5C, 0x45, 0x4E, 0x47, 0x49, 0x4E, 0x45, 0x5C, 0x41, 0x4E, 0x49, 0x4D, 0x5C, 0x41, 0x4E, 0x49, 0x4D, 0x53, 0x54, 0x52, 0x43, 0x2E, 0x48 } },
    { 28, SN_LE16(145), 39, { 0x43, 0x3A, 0x5C, 0x50, 0x72, 0x6F, 0x6A, 0x65, 0x63, 0x74, 0x73, 0x5C, 0x44, 0x4D, 0x5C, 0x6E, 0x36, 0x34, 0x5C, 0x53, 0x6F, 0x75, 0x72, 0x63, 0x65, 0x5C, 0x45, 0x4E, 0x47, 0x49, 0x4E, 0x45, 0x5C, 0x41, 0x4E, 0x49, 0x4D, 0x2E, 0x48 } },
    { 28, SN_LE16(144), 43, { 0x43, 0x3A, 0x5C, 0x50, 0x72, 0x6F, 0x6A, 0x65, 0x63, 0x74, 0x73, 0x5C, 0x44, 0x4D, 0x5C, 0x6E, 0x36, 0x34, 0x5C, 0x53, 0x6F, 0x75, 0x72, 0x63, 0x65, 0x5C, 0x45, 0x4E, 0x47, 0x49, 0x4E, 0x45, 0x5C, 0x52, 0x4F, 0x4D, 0x53, 0x54, 0x52, 0x55, 0x43, 0x2E, 0x48 } },
    { 28, SN_LE16(143), 29, { 0x43, 0x3A, 0x5C, 0x50, 0x72, 0x6F, 0x6A, 0x65, 0x63, 0x74, 0x73, 0x5C, 0x44, 0x4D, 0x5C, 0x6E, 0x36, 0x34, 0x5C, 0x50, 0x49, 0x4D, 0x50, 0x45, 0x51, 0x55, 0x53, 0x2E, 0x48 } },
    { 28, SN_LE16(142), 24, { 0x43, 0x3A, 0x5C, 0x50, 0x72, 0x6F, 0x6A, 0x65, 0x63, 0x74, 0x73, 0x5C, 0x44, 0x4D, 0x5C, 0x6E, 0x36, 0x34, 0x5C, 0x45, 0x51, 0x55, 0x2E, 0x48 } },
    { 28, SN_LE16(141), 29, { 0x43, 0x3A, 0x5C, 0x50, 0x72, 0x6F, 0x6A, 0x65, 0x63, 0x74, 0x73, 0x5C, 0x44, 0x4D, 0x5C, 0x6E, 0x36, 0x34, 0x5C, 0x50, 0x49, 0x4D, 0x50, 0x45, 0x51, 0x55, 0x53, 0x2E, 0x48 } },
    { 28, SN_LE16(140), 43, { 0x43, 0x3A, 0x5C, 0x50, 0x72, 0x6F, 0x6A, 0x65, 0x63, 0x74, 0x73, 0x5C, 0x44, 0x4D, 0x5C, 0x6E, 0x36, 0x34, 0x5C, 0x53, 0x6F, 0x75, 0x72, 0x63, 0x65, 0x5C, 0x45, 0x4E, 0x47, 0x49, 0x4E, 0x45, 0x5C, 0x52, 0x4F, 0x4D, 0x53, 0x54, 0x52, 0x55, 0x43, 0x2E, 0x48 } },
    { 28, SN_LE16(139), 42, { 0x43, 0x3A, 0x5C, 0x50, 0x72, 0x6F, 0x6A, 0x65, 0x63, 0x74, 0x73, 0x5C, 0x44, 0x4D, 0x5C, 0x6E, 0x36, 0x34, 0x5C, 0x53, 0x6F, 0x75, 0x72, 0x63, 0x65, 0x5C, 0x45, 0x4E, 0x47, 0x49, 0x4E, 0x45, 0x5C, 0x47, 0x52, 0x45, 0x47, 0x49, 0x4F, 0x4E, 0x2E, 0x48 } },
    { 28, SN_LE16(138), 41, { 0x43, 0x3A, 0x5C, 0x50, 0x72, 0x6F, 0x6A, 0x65, 0x63, 0x74, 0x73, 0x5C, 0x44, 0x4D, 0x5C, 0x6E, 0x36, 0x34, 0x5C, 0x53, 0x6F, 0x75, 0x72, 0x63, 0x65, 0x5C, 0x45, 0x4E, 0x47, 0x49, 0x4E, 0x45, 0x5C, 0x56, 0x49, 0x53, 0x53, 0x59, 0x53, 0x2E, 0x48 } },
    { 28, SN_LE16(137), 42, { 0x43, 0x3A, 0x5C, 0x50, 0x72, 0x6F, 0x6A, 0x65, 0x63, 0x74, 0x73, 0x5C, 0x44, 0x4D, 0x5C, 0x6E, 0x36, 0x34, 0x5C, 0x53, 0x6F, 0x75, 0x72, 0x63, 0x65, 0x5C, 0x45, 0x4E, 0x47, 0x49, 0x4E, 0x45, 0x5C, 0x47, 0x52, 0x45, 0x47, 0x49, 0x4F, 0x4E, 0x2E, 0x48 } },
    { 28, SN_LE16(136), 43, { 0x43, 0x3A, 0x5C, 0x50, 0x72, 0x6F, 0x6A, 0x65, 0x63, 0x74, 0x73, 0x5C, 0x44, 0x4D, 0x5C, 0x6E, 0x36, 0x34, 0x5C, 0x53, 0x6F, 0x75, 0x72, 0x63, 0x65, 0x5C, 0x45, 0x4E, 0x47, 0x49, 0x4E, 0x45, 0x5C, 0x52, 0x4F, 0x4D, 0x53, 0x54, 0x52, 0x55, 0x43, 0x2E, 0x48 } },
    { 28, SN_LE16(135), 43, { 0x43, 0x3A, 0x5C, 0x50, 0x72, 0x6F, 0x6A, 0x65, 0x63, 0x74, 0x73, 0x5C, 0x44, 0x4D, 0x5C, 0x6E, 0x36, 0x34, 0x5C, 0x53, 0x6F, 0x75, 0x72, 0x63, 0x65, 0x5C, 0x45, 0x4E, 0x47, 0x49, 0x4E, 0x45, 0x5C, 0x54, 0x45, 0x58, 0x54, 0x4C, 0x4F, 0x41, 0x44, 0x2E, 0x48 } },
    { 28, SN_LE16(134), 43, { 0x43, 0x3A, 0x5C, 0x50, 0x72, 0x6F, 0x6A, 0x65, 0x63, 0x74, 0x73, 0x5C, 0x44, 0x4D, 0x5C, 0x6E, 0x36, 0x34, 0x5C, 0x53, 0x6F, 0x75, 0x72, 0x63, 0x65, 0x5C, 0x45, 0x4E, 0x47, 0x49, 0x4E, 0x45, 0x5C, 0x52, 0x4F, 0x4D, 0x53, 0x54, 0x52, 0x55, 0x43, 0x2E, 0x48 } },
    { 28, SN_LE16(133), 38, { 0x43, 0x3A, 0x5C, 0x50, 0x72, 0x6F, 0x6A, 0x65, 0x63, 0x74, 0x73, 0x5C, 0x44, 0x4D, 0x5C, 0x6E, 0x36, 0x34, 0x5C, 0x53, 0x6F, 0x75, 0x72, 0x63, 0x65, 0x5C, 0x41, 0x49, 0x5C, 0x41, 0x49, 0x53, 0x54, 0x52, 0x55, 0x43, 0x2E, 0x48 } },
    { 28, SN_LE16(132), 54, { 0x43, 0x3A, 0x5C, 0x50, 0x72, 0x6F, 0x6A, 0x65, 0x63, 0x74, 0x73, 0x5C, 0x44, 0x4D, 0x5C, 0x6E, 0x36, 0x34, 0x5C, 0x53, 0x6F, 0x75, 0x72, 0x63, 0x65, 0x5C, 0x45, 0x4E, 0x47, 0x49, 0x4E, 0x45, 0x5C, 0x41, 0x55, 0x44, 0x49, 0x4F, 0x5C, 0x4C, 0x4F, 0x4F, 0x50, 0x53, 0x4F, 0x55, 0x4E, 0x44, 0x50, 0x4F, 0x4F, 0x4C, 0x2E, 0x48 } },
    { 28, SN_LE16(131), 38, { 0x43, 0x3A, 0x5C, 0x50, 0x72, 0x6F, 0x6A, 0x65, 0x63, 0x74, 0x73, 0x5C, 0x44, 0x4D, 0x5C, 0x6E, 0x36, 0x34, 0x5C, 0x53, 0x6F, 0x75, 0x72, 0x63, 0x65, 0x5C, 0x41, 0x49, 0x5C, 0x41, 0x49, 0x53, 0x54, 0x52, 0x55, 0x43, 0x2E, 0x48 } },
    { 28, SN_LE16(130), 36, { 0x43, 0x3A, 0x5C, 0x50, 0x72, 0x6F, 0x6A, 0x65, 0x63, 0x74, 0x73, 0x5C, 0x44, 0x4D, 0x5C, 0x6E, 0x36, 0x34, 0x5C, 0x53, 0x6F, 0x75, 0x72, 0x63, 0x65, 0x5C, 0x41, 0x49, 0x5C, 0x47, 0x50, 0x41, 0x54, 0x48, 0x2E, 0x48 } },
    { 28, SN_LE16(129), 41, { 0x43, 0x3A, 0x5C, 0x50, 0x72, 0x6F, 0x6A, 0x65, 0x63, 0x74, 0x73, 0x5C, 0x44, 0x4D, 0x5C, 0x6E, 0x36, 0x34, 0x5C, 0x53, 0x6F, 0x75, 0x72, 0x63, 0x65, 0x5C, 0x45, 0x4E, 0x47, 0x49, 0x4E, 0x45, 0x5C, 0x43, 0x50, 0x50, 0x55, 0x36, 0x34, 0x2E, 0x48 } },
    { 28, SN_LE16(128), 36, { 0x43, 0x3A, 0x5C, 0x50, 0x72, 0x6F, 0x6A, 0x65, 0x63, 0x74, 0x73, 0x5C, 0x44, 0x4D, 0x5C, 0x6E, 0x36, 0x34, 0x5C, 0x53, 0x6F, 0x75, 0x72, 0x63, 0x65, 0x5C, 0x41, 0x49, 0x5C, 0x47, 0x50, 0x41, 0x54, 0x48, 0x2E, 0x48 } },
    { 28, SN_LE16(127), 38, { 0x43, 0x3A, 0x5C, 0x50, 0x72, 0x6F, 0x6A, 0x65, 0x63, 0x74, 0x73, 0x5C, 0x44, 0x4D, 0x5C, 0x6E, 0x36, 0x34, 0x5C, 0x53, 0x6F, 0x75, 0x72, 0x63, 0x65, 0x5C, 0x41, 0x49, 0x5C, 0x41, 0x49, 0x53, 0x54, 0x52, 0x55, 0x43, 0x2E, 0x48 } },
    { 28, SN_LE16(126), 43, { 0x43, 0x3A, 0x5C, 0x50, 0x72, 0x6F, 0x6A, 0x65, 0x63, 0x74, 0x73, 0x5C, 0x44, 0x4D, 0x5C, 0x6E, 0x36, 0x34, 0x5C, 0x53, 0x6F, 0x75, 0x72, 0x63, 0x65, 0x5C, 0x45, 0x4E, 0x47, 0x49, 0x4E, 0x45, 0x5C, 0x52, 0x4F, 0x4D, 0x53, 0x54, 0x52, 0x55, 0x43, 0x2E, 0x48 } },
    { 28, SN_LE16(125), 40, { 0x43, 0x3A, 0x5C, 0x50, 0x72, 0x6F, 0x6A, 0x65, 0x63, 0x74, 0x73, 0x5C, 0x44, 0x4D, 0x5C, 0x6E, 0x36, 0x34, 0x5C, 0x53, 0x6F, 0x75, 0x72, 0x63, 0x65, 0x5C, 0x45, 0x4E, 0x47, 0x49, 0x4E, 0x45, 0x5C, 0x53, 0x43, 0x45, 0x4E, 0x45, 0x2E, 0x48 } },
    { 28, SN_LE16(124), 42, { 0x43, 0x3A, 0x5C, 0x50, 0x72, 0x6F, 0x6A, 0x65, 0x63, 0x74, 0x73, 0x5C, 0x44, 0x4D, 0x5C, 0x6E, 0x36, 0x34, 0x5C, 0x53, 0x6F, 0x75, 0x72, 0x63, 0x65, 0x5C, 0x45, 0x4E, 0x47, 0x49, 0x4E, 0x45, 0x5C, 0x54, 0x45, 0x4E, 0x47, 0x49, 0x4E, 0x45, 0x2E, 0x48 } },
    { 28, SN_LE16(123), 23, { 0x43, 0x3A, 0x5C, 0x4E, 0x36, 0x34, 0x5C, 0x49, 0x4E, 0x43, 0x4C, 0x55, 0x44, 0x45, 0x5C, 0x53, 0x54, 0x44, 0x44, 0x45, 0x46, 0x2E, 0x48 } },
    { 28, SN_LE16(122), 42, { 0x43, 0x3A, 0x5C, 0x50, 0x72, 0x6F, 0x6A, 0x65, 0x63, 0x74, 0x73, 0x5C, 0x44, 0x4D, 0x5C, 0x6E, 0x36, 0x34, 0x5C, 0x53, 0x6F, 0x75, 0x72, 0x63, 0x65, 0x5C, 0x45, 0x4E, 0x47, 0x49, 0x4E, 0x45, 0x5C, 0x54, 0x45, 0x4E, 0x47, 0x49, 0x4E, 0x45, 0x2E, 0x48 } },
    { 28, SN_LE16(121), 65, { 0x43, 0x3A, 0x5C, 0x50, 0x52, 0x4F, 0x4A, 0x45, 0x43, 0x54, 0x53, 0x5C, 0x44, 0x4D, 0x5C, 0x4E, 0x36, 0x34, 0x5C, 0x53, 0x4F, 0x55, 0x52, 0x43, 0x45, 0x5C, 0x55, 0x49, 0x5C, 0x54, 0x53, 0x4D, 0x4F, 0x53, 0x5C, 0x53, 0x43, 0x52, 0x45, 0x45, 0x4E, 0x53, 0x5C, 0x50, 0x41, 0x4B, 0x49, 0x4E, 0x54, 0x45, 0x52, 0x46, 0x41, 0x43, 0x45, 0x53, 0x43, 0x52, 0x45, 0x45, 0x4E, 0x2E, 0x43, 0x50, 0x50 } },
    { 28, SN_LE16(120), 45, { 0x43, 0x3A, 0x5C, 0x50, 0x72, 0x6F, 0x6A, 0x65, 0x63, 0x74, 0x73, 0x5C, 0x44, 0x4D, 0x5C, 0x6E, 0x36, 0x34, 0x5C, 0x53, 0x6F, 0x75, 0x72, 0x63, 0x65, 0x5C, 0x55, 0x49, 0x5C, 0x58, 0x5F, 0x46, 0x49, 0x4C, 0x45, 0x53, 0x5C, 0x58, 0x5F, 0x4D, 0x41, 0x54, 0x48, 0x2E, 0x48 } },
    { 28, SN_LE16(119), 65, { 0x43, 0x3A, 0x5C, 0x50, 0x52, 0x4F, 0x4A, 0x45, 0x43, 0x54, 0x53, 0x5C, 0x44, 0x4D, 0x5C, 0x4E, 0x36, 0x34, 0x5C, 0x53, 0x4F, 0x55, 0x52, 0x43, 0x45, 0x5C, 0x55, 0x49, 0x5C, 0x54, 0x53, 0x4D, 0x4F, 0x53, 0x5C, 0x53, 0x43, 0x52, 0x45, 0x45, 0x4E, 0x53, 0x5C, 0x50, 0x41, 0x4B, 0x49, 0x4E, 0x54, 0x45, 0x52, 0x46, 0x41, 0x43, 0x45, 0x53, 0x43, 0x52, 0x45, 0x45, 0x4E, 0x2E, 0x43, 0x50, 0x50 } },
    { 28, SN_LE16(118), 45, { 0x43, 0x3A, 0x5C, 0x50, 0x72, 0x6F, 0x6A, 0x65, 0x63, 0x74, 0x73, 0x5C, 0x44, 0x4D, 0x5C, 0x6E, 0x36, 0x34, 0x5C, 0x53, 0x6F, 0x75, 0x72, 0x63, 0x65, 0x5C, 0x55, 0x49, 0x5C, 0x58, 0x5F, 0x46, 0x49, 0x4C, 0x45, 0x53, 0x5C, 0x58, 0x5F, 0x50, 0x4C, 0x55, 0x53, 0x2E, 0x48 } },
    { 28, SN_LE16(117), 65, { 0x43, 0x3A, 0x5C, 0x50, 0x52, 0x4F, 0x4A, 0x45, 0x43, 0x54, 0x53, 0x5C, 0x44, 0x4D, 0x5C, 0x4E, 0x36, 0x34, 0x5C, 0x53, 0x4F, 0x55, 0x52, 0x43, 0x45, 0x5C, 0x55, 0x49, 0x5C, 0x54, 0x53, 0x4D, 0x4F, 0x53, 0x5C, 0x53, 0x43, 0x52, 0x45, 0x45, 0x4E, 0x53, 0x5C, 0x50, 0x41, 0x4B, 0x49, 0x4E, 0x54, 0x45, 0x52, 0x46, 0x41, 0x43, 0x45, 0x53, 0x43, 0x52, 0x45, 0x45, 0x4E, 0x2E, 0x43, 0x50, 0x50 } },
    { 28, SN_LE16(116), 47, { 0x43, 0x3A, 0x5C, 0x50, 0x72, 0x6F, 0x6A, 0x65, 0x63, 0x74, 0x73, 0x5C, 0x44, 0x4D, 0x5C, 0x6E, 0x36, 0x34, 0x5C, 0x53, 0x6F, 0x75, 0x72, 0x63, 0x65, 0x5C, 0x55, 0x49, 0x5C, 0x58, 0x5F, 0x46, 0x49, 0x4C, 0x45, 0x53, 0x5C, 0x58, 0x5F, 0x4D, 0x45, 0x4D, 0x4F, 0x52, 0x59, 0x2E, 0x48 } },
    { 28, SN_LE16(115), 46, { 0x43, 0x3A, 0x5C, 0x50, 0x72, 0x6F, 0x6A, 0x65, 0x63, 0x74, 0x73, 0x5C, 0x44, 0x4D, 0x5C, 0x6E, 0x36, 0x34, 0x5C, 0x53, 0x6F, 0x75, 0x72, 0x63, 0x65, 0x5C, 0x45, 0x4E, 0x47, 0x49, 0x4E, 0x45, 0x5C, 0x43, 0x41, 0x43, 0x48, 0x45, 0x5C, 0x43, 0x41, 0x43, 0x48, 0x45, 0x2E, 0x48 } },
    { 28, SN_LE16(114), 41, { 0x43, 0x3A, 0x5C, 0x50, 0x72, 0x6F, 0x6A, 0x65, 0x63, 0x74, 0x73, 0x5C, 0x44, 0x4D, 0x5C, 0x6E, 0x36, 0x34, 0x5C, 0x53, 0x6F, 0x75, 0x72, 0x63, 0x65, 0x5C, 0x45, 0x4E, 0x47, 0x49, 0x4E, 0x45, 0x5C, 0x53, 0x45, 0x54, 0x4E, 0x36, 0x34, 0x2E, 0x48 } },
    { 28, SN_LE16(113), 46, { 0x43, 0x3A, 0x5C, 0x50, 0x72, 0x6F, 0x6A, 0x65, 0x63, 0x74, 0x73, 0x5C, 0x44, 0x4D, 0x5C, 0x6E, 0x36, 0x34, 0x5C, 0x53, 0x6F, 0x75, 0x72, 0x63, 0x65, 0x5C, 0x45, 0x4E, 0x47, 0x49, 0x4E, 0x45, 0x5C, 0x43, 0x41, 0x43, 0x48, 0x45, 0x5C, 0x43, 0x41, 0x43, 0x48, 0x45, 0x2E, 0x48 } },
    { 28, SN_LE16(112), 47, { 0x43, 0x3A, 0x5C, 0x50, 0x72, 0x6F, 0x6A, 0x65, 0x63, 0x74, 0x73, 0x5C, 0x44, 0x4D, 0x5C, 0x6E, 0x36, 0x34, 0x5C, 0x53, 0x6F, 0x75, 0x72, 0x63, 0x65, 0x5C, 0x55, 0x49, 0x5C, 0x58, 0x5F, 0x46, 0x49, 0x4C, 0x45, 0x53, 0x5C, 0x58, 0x5F, 0x4D, 0x45, 0x4D, 0x4F, 0x52, 0x59, 0x2E, 0x48 } },
    { 28, SN_LE16(111), 65, { 0x43, 0x3A, 0x5C, 0x50, 0x52, 0x4F, 0x4A, 0x45, 0x43, 0x54, 0x53, 0x5C, 0x44, 0x4D, 0x5C, 0x4E, 0x36, 0x34, 0x5C, 0x53, 0x4F, 0x55, 0x52, 0x43, 0x45, 0x5C, 0x55, 0x49, 0x5C, 0x54, 0x53, 0x4D, 0x4F, 0x53, 0x5C, 0x53, 0x43, 0x52, 0x45, 0x45, 0x4E, 0x53, 0x5C, 0x50, 0x41, 0x4B, 0x49, 0x4E, 0x54, 0x45, 0x52, 0x46, 0x41, 0x43, 0x45, 0x53, 0x43, 0x52, 0x45, 0x45, 0x4E, 0x2E, 0x43, 0x50, 0x50 } },
    { 28, SN_LE16(110), 42, { 0x43, 0x3A, 0x5C, 0x50, 0x72, 0x6F, 0x6A, 0x65, 0x63, 0x74, 0x73, 0x5C, 0x44, 0x4D, 0x5C, 0x6E, 0x36, 0x34, 0x5C, 0x53, 0x6F, 0x75, 0x72, 0x63, 0x65, 0x5C, 0x55, 0x49, 0x5C, 0x54, 0x53, 0x4D, 0x4F, 0x53, 0x5C, 0x54, 0x53, 0x4D, 0x4F, 0x53, 0x2E, 0x48 } },
    { 28, SN_LE16(109), 47, { 0x43, 0x3A, 0x5C, 0x50, 0x72, 0x6F, 0x6A, 0x65, 0x63, 0x74, 0x73, 0x5C, 0x44, 0x4D, 0x5C, 0x6E, 0x36, 0x34, 0x5C, 0x53, 0x6F, 0x75, 0x72, 0x63, 0x65, 0x5C, 0x55, 0x49, 0x5C, 0x54, 0x53, 0x4D, 0x4F, 0x53, 0x5C, 0x54, 0x53, 0x43, 0x52, 0x45, 0x44, 0x44, 0x41, 0x54, 0x41, 0x2E, 0x48 } },
    { 28, SN_LE16(108), 48, { 0x43, 0x3A, 0x5C, 0x50, 0x72, 0x6F, 0x6A, 0x65, 0x63, 0x74, 0x73, 0x5C, 0x44, 0x4D, 0x5C, 0x6E, 0x36, 0x34, 0x5C, 0x53, 0x6F, 0x75, 0x72, 0x63, 0x65, 0x5C, 0x55, 0x49, 0x5C, 0x54, 0x53, 0x4D, 0x4F, 0x53, 0x5C, 0x54, 0x53, 0x43, 0x52, 0x45, 0x44, 0x44, 0x41, 0x54, 0x41, 0x55, 0x2E, 0x48 } },
    { 28, SN_LE16(107), 47, { 0x43, 0x3A, 0x5C, 0x50, 0x72, 0x6F, 0x6A, 0x65, 0x63, 0x74, 0x73, 0x5C, 0x44, 0x4D, 0x5C, 0x6E, 0x36, 0x34, 0x5C, 0x53, 0x6F, 0x75, 0x72, 0x63, 0x65, 0x5C, 0x55, 0x49, 0x5C, 0x54, 0x53, 0x4D, 0x4F, 0x53, 0x5C, 0x54, 0x53, 0x43, 0x52, 0x45, 0x44, 0x44, 0x41, 0x54, 0x41, 0x2E, 0x48 } },
    { 28, SN_LE16(106), 42, { 0x43, 0x3A, 0x5C, 0x50, 0x72, 0x6F, 0x6A, 0x65, 0x63, 0x74, 0x73, 0x5C, 0x44, 0x4D, 0x5C, 0x6E, 0x36, 0x34, 0x5C, 0x53, 0x6F, 0x75, 0x72, 0x63, 0x65, 0x5C, 0x55, 0x49, 0x5C, 0x54, 0x53, 0x4D, 0x4F, 0x53, 0x5C, 0x54, 0x53, 0x4D, 0x4F, 0x53, 0x2E, 0x48 } },
    { 28, SN_LE16(105), 44, { 0x43, 0x3A, 0x5C, 0x50, 0x72, 0x6F, 0x6A, 0x65, 0x63, 0x74, 0x73, 0x5C, 0x44, 0x4D, 0x5C, 0x6E, 0x36, 0x34, 0x5C, 0x53, 0x6F, 0x75, 0x72, 0x63, 0x65, 0x5C, 0x55, 0x49, 0x5C, 0x53, 0x4D, 0x4F, 0x53, 0x5C, 0x53, 0x4D, 0x5F, 0x53, 0x4D, 0x4E, 0x47, 0x52, 0x2E, 0x48 } },
    { 28, SN_LE16(104), 42, { 0x43, 0x3A, 0x5C, 0x50, 0x72, 0x6F, 0x6A, 0x65, 0x63, 0x74, 0x73, 0x5C, 0x44, 0x4D, 0x5C, 0x6E, 0x36, 0x34, 0x5C, 0x53, 0x6F, 0x75, 0x72, 0x63, 0x65, 0x5C, 0x55, 0x49, 0x5C, 0x54, 0x53, 0x4D, 0x4F, 0x53, 0x5C, 0x54, 0x53, 0x4D, 0x4F, 0x53, 0x2E, 0x48 } },
    { 28, SN_LE16(103), 65, { 0x43, 0x3A, 0x5C, 0x50, 0x52, 0x4F, 0x4A, 0x45, 0x43, 0x54, 0x53, 0x5C, 0x44, 0x4D, 0x5C, 0x4E, 0x36, 0x34, 0x5C, 0x53, 0x4F, 0x55, 0x52, 0x43, 0x45, 0x5C, 0x55, 0x49, 0x5C, 0x54, 0x53, 0x4D, 0x4F, 0x53, 0x5C, 0x53, 0x43, 0x52, 0x45, 0x45, 0x4E, 0x53, 0x5C, 0x50, 0x41, 0x4B, 0x49, 0x4E, 0x54, 0x45, 0x52, 0x46, 0x41, 0x43, 0x45, 0x53, 0x43, 0x52, 0x45, 0x45, 0x4E, 0x2E, 0x43, 0x50, 0x50 } },
    { 28, SN_LE16(102), 44, { 0x43, 0x3A, 0x5C, 0x50, 0x72, 0x6F, 0x6A, 0x65, 0x63, 0x74, 0x73, 0x5C, 0x44, 0x4D, 0x5C, 0x6E, 0x36, 0x34, 0x5C, 0x53, 0x6F, 0x75, 0x72, 0x63, 0x65, 0x5C, 0x55, 0x49, 0x5C, 0x53, 0x4D, 0x4F, 0x53, 0x5C, 0x53, 0x4D, 0x5F, 0x44, 0x4C, 0x49, 0x53, 0x54, 0x2E, 0x48 } },
    { 28, SN_LE16(101), 44, { 0x43, 0x3A, 0x5C, 0x50, 0x72, 0x6F, 0x6A, 0x65, 0x63, 0x74, 0x73, 0x5C, 0x44, 0x4D, 0x5C, 0x6E, 0x36, 0x34, 0x5C, 0x53, 0x6F, 0x75, 0x72, 0x63, 0x65, 0x5C, 0x55, 0x49, 0x5C, 0x53, 0x4D, 0x4F, 0x53, 0x5C, 0x53, 0x4D, 0x44, 0x53, 0x50, 0x4C, 0x53, 0x54, 0x2E, 0x48 } },
    { 28, SN_LE16(100), 44, { 0x43, 0x3A, 0x5C, 0x50, 0x72, 0x6F, 0x6A, 0x65, 0x63, 0x74, 0x73, 0x5C, 0x44, 0x4D, 0x5C, 0x6E, 0x36, 0x34, 0x5C, 0x53, 0x6F, 0x75, 0x72, 0x63, 0x65, 0x5C, 0x55, 0x49, 0x5C, 0x53, 0x4D, 0x4F, 0x53, 0x5C, 0x53, 0x4D, 0x5F, 0x44, 0x4C, 0x49, 0x53, 0x54, 0x2E, 0x48 } },
    { 28, SN_LE16(99), 65, { 0x43, 0x3A, 0x5C, 0x50, 0x52, 0x4F, 0x4A, 0x45, 0x43, 0x54, 0x53, 0x5C, 0x44, 0x4D, 0x5C, 0x4E, 0x36, 0x34, 0x5C, 0x53, 0x4F, 0x55, 0x52, 0x43, 0x45, 0x5C, 0x55, 0x49, 0x5C, 0x54, 0x53, 0x4D, 0x4F, 0x53, 0x5C, 0x53, 0x43, 0x52, 0x45, 0x45, 0x4E, 0x53, 0x5C, 0x50, 0x41, 0x4B, 0x49, 0x4E, 0x54, 0x45, 0x52, 0x46, 0x41, 0x43, 0x45, 0x53, 0x43, 0x52, 0x45, 0x45, 0x4E, 0x2E, 0x43, 0x50, 0x50 } },
    { 28, SN_LE16(98), 44, { 0x43, 0x3A, 0x5C, 0x50, 0x72, 0x6F, 0x6A, 0x65, 0x63, 0x74, 0x73, 0x5C, 0x44, 0x4D, 0x5C, 0x6E, 0x36, 0x34, 0x5C, 0x53, 0x6F, 0x75, 0x72, 0x63, 0x65, 0x5C, 0x55, 0x49, 0x5C, 0x53, 0x4D, 0x4F, 0x53, 0x5C, 0x53, 0x4D, 0x5F, 0x49, 0x4D, 0x50, 0x52, 0x54, 0x2E, 0x48 } },
    { 28, SN_LE16(97), 44, { 0x43, 0x3A, 0x5C, 0x50, 0x72, 0x6F, 0x6A, 0x65, 0x63, 0x74, 0x73, 0x5C, 0x44, 0x4D, 0x5C, 0x6E, 0x36, 0x34, 0x5C, 0x53, 0x6F, 0x75, 0x72, 0x63, 0x65, 0x5C, 0x55, 0x49, 0x5C, 0x53, 0x4D, 0x4F, 0x53, 0x5C, 0x53, 0x4D, 0x44, 0x53, 0x50, 0x4C, 0x53, 0x54, 0x2E, 0x48 } },
    { 28, SN_LE16(96), 23, { 0x43, 0x3A, 0x5C, 0x4E, 0x36, 0x34, 0x5C, 0x49, 0x4E, 0x43, 0x4C, 0x55, 0x44, 0x45, 0x5C, 0x41, 0x53, 0x53, 0x45, 0x52, 0x54, 0x2E, 0x48 } },
    { 28, SN_LE16(95), 44, { 0x43, 0x3A, 0x5C, 0x50, 0x72, 0x6F, 0x6A, 0x65, 0x63, 0x74, 0x73, 0x5C, 0x44, 0x4D, 0x5C, 0x6E, 0x36, 0x34, 0x5C, 0x53, 0x6F, 0x75, 0x72, 0x63, 0x65, 0x5C, 0x55, 0x49, 0x5C, 0x53, 0x4D, 0x4F, 0x53, 0x5C, 0x53, 0x4D, 0x44, 0x53, 0x50, 0x4C, 0x53, 0x54, 0x2E, 0x48 } },
    { 28, SN_LE16(94), 44, { 0x43, 0x3A, 0x5C, 0x50, 0x72, 0x6F, 0x6A, 0x65, 0x63, 0x74, 0x73, 0x5C, 0x44, 0x4D, 0x5C, 0x6E, 0x36, 0x34, 0x5C, 0x53, 0x6F, 0x75, 0x72, 0x63, 0x65, 0x5C, 0x55, 0x49, 0x5C, 0x53, 0x4D, 0x4F, 0x53, 0x5C, 0x53, 0x4D, 0x5F, 0x49, 0x4D, 0x50, 0x52, 0x54, 0x2E, 0x48 } },
    { 28, SN_LE16(93), 42, { 0x43, 0x3A, 0x5C, 0x50, 0x72, 0x6F, 0x6A, 0x65, 0x63, 0x74, 0x73, 0x5C, 0x44, 0x4D, 0x5C, 0x6E, 0x36, 0x34, 0x5C, 0x53, 0x6F, 0x75, 0x72, 0x63, 0x65, 0x5C, 0x55, 0x49, 0x5C, 0x51, 0x55, 0x41, 0x47, 0x5C, 0x51, 0x5F, 0x56, 0x52, 0x41, 0x4D, 0x2E, 0x48 } },
    { 28, SN_LE16(92), 47, { 0x43, 0x3A, 0x5C, 0x50, 0x72, 0x6F, 0x6A, 0x65, 0x63, 0x74, 0x73, 0x5C, 0x44, 0x4D, 0x5C, 0x6E, 0x36, 0x34, 0x5C, 0x53, 0x6F, 0x75, 0x72, 0x63, 0x65, 0x5C, 0x55, 0x49, 0x5C, 0x58, 0x5F, 0x46, 0x49, 0x4C, 0x45, 0x53, 0x5C, 0x58, 0x5F, 0x42, 0x49, 0x54, 0x4D, 0x41, 0x50, 0x2E, 0x48 } },
    { 28, SN_LE16(91), 42, { 0x43, 0x3A, 0x5C, 0x50, 0x72, 0x6F, 0x6A, 0x65, 0x63, 0x74, 0x73, 0x5C, 0x44, 0x4D, 0x5C, 0x6E, 0x36, 0x34, 0x5C, 0x53, 0x6F, 0x75, 0x72, 0x63, 0x65, 0x5C, 0x55, 0x49, 0x5C, 0x51, 0x55, 0x41, 0x47, 0x5C, 0x51, 0x5F, 0x56, 0x52, 0x41, 0x4D, 0x2E, 0x48 } },
    { 28, SN_LE16(90), 44, { 0x43, 0x3A, 0x5C, 0x50, 0x72, 0x6F, 0x6A, 0x65, 0x63, 0x74, 0x73, 0x5C, 0x44, 0x4D, 0x5C, 0x6E, 0x36, 0x34, 0x5C, 0x53, 0x6F, 0x75, 0x72, 0x63, 0x65, 0x5C, 0x55, 0x49, 0x5C, 0x53, 0x4D, 0x4F, 0x53, 0x5C, 0x53, 0x4D, 0x5F, 0x49, 0x4D, 0x50, 0x52, 0x54, 0x2E, 0x48 } },
    { 28, SN_LE16(89), 46, { 0x43, 0x3A, 0x5C, 0x50, 0x72, 0x6F, 0x6A, 0x65, 0x63, 0x74, 0x73, 0x5C, 0x44, 0x4D, 0x5C, 0x6E, 0x36, 0x34, 0x5C, 0x53, 0x6F, 0x75, 0x72, 0x63, 0x65, 0x5C, 0x55, 0x49, 0x5C, 0x58, 0x5F, 0x46, 0x49, 0x4C, 0x45, 0x53, 0x5C, 0x58, 0x5F, 0x53, 0x54, 0x44, 0x49, 0x4F, 0x2E, 0x48 } },
    { 28, SN_LE16(88), 23, { 0x43, 0x3A, 0x5C, 0x4E, 0x36, 0x34, 0x5C, 0x49, 0x4E, 0x43, 0x4C, 0x55, 0x44, 0x45, 0x5C, 0x53, 0x54, 0x44, 0x41, 0x52, 0x47, 0x2E, 0x48 } },
    { 28, SN_LE16(87), 24, { 0x43, 0x3A, 0x5C, 0x4E, 0x36, 0x34, 0x5C, 0x49, 0x4E, 0x43, 0x4C, 0x55, 0x44, 0x45, 0x5C, 0x56, 0x41, 0x2D, 0x4D, 0x49, 0x50, 0x53, 0x2E, 0x48 } },
    { 28, SN_LE16(86), 23, { 0x43, 0x3A, 0x5C, 0x4E, 0x36, 0x34, 0x5C, 0x49, 0x4E, 0x43, 0x4C, 0x55, 0x44, 0x45, 0x5C, 0x53, 0x54, 0x44, 0x41, 0x52, 0x47, 0x2E, 0x48 } },
    { 28, SN_LE16(85), 46, { 0x43, 0x3A, 0x5C, 0x50, 0x72, 0x6F, 0x6A, 0x65, 0x63, 0x74, 0x73, 0x5C, 0x44, 0x4D, 0x5C, 0x6E, 0x36, 0x34, 0x5C, 0x53, 0x6F, 0x75, 0x72, 0x63, 0x65, 0x5C, 0x55, 0x49, 0x5C, 0x58, 0x5F, 0x46, 0x49, 0x4C, 0x45, 0x53, 0x5C, 0x58, 0x5F, 0x53, 0x54, 0x44, 0x49, 0x4F, 0x2E, 0x48 } },
    { 28, SN_LE16(84), 44, { 0x43, 0x3A, 0x5C, 0x50, 0x72, 0x6F, 0x6A, 0x65, 0x63, 0x74, 0x73, 0x5C, 0x44, 0x4D, 0x5C, 0x6E, 0x36, 0x34, 0x5C, 0x53, 0x6F, 0x75, 0x72, 0x63, 0x65, 0x5C, 0x55, 0x49, 0x5C, 0x53, 0x4D, 0x4F, 0x53, 0x5C, 0x53, 0x4D, 0x5F, 0x49, 0x4D, 0x50, 0x52, 0x54, 0x2E, 0x48 } },
    { 28, SN_LE16(83), 46, { 0x43, 0x3A, 0x5C, 0x50, 0x72, 0x6F, 0x6A, 0x65, 0x63, 0x74, 0x73, 0x5C, 0x44, 0x4D, 0x5C, 0x6E, 0x36, 0x34, 0x5C, 0x53, 0x6F, 0x75, 0x72, 0x63, 0x65, 0x5C, 0x55, 0x49, 0x5C, 0x58, 0x5F, 0x46, 0x49, 0x4C, 0x45, 0x53, 0x5C, 0x58, 0x5F, 0x43, 0x4F, 0x4C, 0x4F, 0x52, 0x2E, 0x48 } },
    { 28, SN_LE16(82), 44, { 0x43, 0x3A, 0x5C, 0x50, 0x72, 0x6F, 0x6A, 0x65, 0x63, 0x74, 0x73, 0x5C, 0x44, 0x4D, 0x5C, 0x6E, 0x36, 0x34, 0x5C, 0x53, 0x6F, 0x75, 0x72, 0x63, 0x65, 0x5C, 0x55, 0x49, 0x5C, 0x53, 0x4D, 0x4F, 0x53, 0x5C, 0x53, 0x4D, 0x5F, 0x49, 0x4D, 0x50, 0x52, 0x54, 0x2E, 0x48 } },
    { 28, SN_LE16(81), 65, { 0x43, 0x3A, 0x5C, 0x50, 0x52, 0x4F, 0x4A, 0x45, 0x43, 0x54, 0x53, 0x5C, 0x44, 0x4D, 0x5C, 0x4E, 0x36, 0x34, 0x5C, 0x53, 0x4F, 0x55, 0x52, 0x43, 0x45, 0x5C, 0x55, 0x49, 0x5C, 0x54, 0x53, 0x4D, 0x4F, 0x53, 0x5C, 0x53, 0x43, 0x52, 0x45, 0x45, 0x4E, 0x53, 0x5C, 0x50, 0x41, 0x4B, 0x49, 0x4E, 0x54, 0x45, 0x52, 0x46, 0x41, 0x43, 0x45, 0x53, 0x43, 0x52, 0x45, 0x45, 0x4E, 0x2E, 0x43, 0x50, 0x50 } },
    { 28, SN_LE16(80), 44, { 0x43, 0x3A, 0x5C, 0x50, 0x72, 0x6F, 0x6A, 0x65, 0x63, 0x74, 0x73, 0x5C, 0x44, 0x4D, 0x5C, 0x6E, 0x36, 0x34, 0x5C, 0x53, 0x6F, 0x75, 0x72, 0x63, 0x65, 0x5C, 0x55, 0x49, 0x5C, 0x53, 0x4D, 0x4F, 0x53, 0x5C, 0x53, 0x4D, 0x5F, 0x58, 0x4C, 0x41, 0x54, 0x45, 0x2E, 0x48 } },
    { 28, SN_LE16(79), 42, { 0x43, 0x3A, 0x5C, 0x50, 0x72, 0x6F, 0x6A, 0x65, 0x63, 0x74, 0x73, 0x5C, 0x44, 0x4D, 0x5C, 0x6E, 0x36, 0x34, 0x5C, 0x53, 0x6F, 0x75, 0x72, 0x63, 0x65, 0x5C, 0x45, 0x4E, 0x47, 0x49, 0x4E, 0x45, 0x5C, 0x43, 0x4F, 0x4E, 0x54, 0x52, 0x4F, 0x4C, 0x2E, 0x48 } },
    { 28, SN_LE16(78), 41, { 0x43, 0x3A, 0x5C, 0x50, 0x72, 0x6F, 0x6A, 0x65, 0x63, 0x74, 0x73, 0x5C, 0x44, 0x4D, 0x5C, 0x6E, 0x36, 0x34, 0x5C, 0x53, 0x6F, 0x75, 0x72, 0x63, 0x65, 0x5C, 0x45, 0x4E, 0x47, 0x49, 0x4E, 0x45, 0x5C, 0x52, 0x55, 0x4D, 0x42, 0x4C, 0x45, 0x2E, 0x48 } },
    { 28, SN_LE16(77), 40, { 0x43, 0x3A, 0x5C, 0x50, 0x72, 0x6F, 0x6A, 0x65, 0x63, 0x74, 0x73, 0x5C, 0x44, 0x4D, 0x5C, 0x6E, 0x36, 0x34, 0x5C, 0x53, 0x6F, 0x75, 0x72, 0x63, 0x65, 0x5C, 0x45, 0x4E, 0x47, 0x49, 0x4E, 0x45, 0x5C, 0x43, 0x55, 0x52, 0x56, 0x45, 0x2E, 0x48 } },
    { 28, SN_LE16(76), 41, { 0x43, 0x3A, 0x5C, 0x50, 0x72, 0x6F, 0x6A, 0x65, 0x63, 0x74, 0x73, 0x5C, 0x44, 0x4D, 0x5C, 0x6E, 0x36, 0x34, 0x5C, 0x53, 0x6F, 0x75, 0x72, 0x63, 0x65, 0x5C, 0x45, 0x4E, 0x47, 0x49, 0x4E, 0x45, 0x5C, 0x52, 0x55, 0x4D, 0x42, 0x4C, 0x45, 0x2E, 0x48 } },
    { 28, SN_LE16(75), 45, { 0x43, 0x3A, 0x5C, 0x50, 0x72, 0x6F, 0x6A, 0x65, 0x63, 0x74, 0x73, 0x5C, 0x44, 0x4D, 0x5C, 0x6E, 0x36, 0x34, 0x5C, 0x53, 0x6F, 0x75, 0x72, 0x63, 0x65, 0x5C, 0x45, 0x4E, 0x47, 0x49, 0x4E, 0x45, 0x5C, 0x43, 0x41, 0x43, 0x48, 0x45, 0x5C, 0x4C, 0x49, 0x53, 0x54, 0x2E, 0x48 } },
    { 28, SN_LE16(74), 41, { 0x43, 0x3A, 0x5C, 0x50, 0x72, 0x6F, 0x6A, 0x65, 0x63, 0x74, 0x73, 0x5C, 0x44, 0x4D, 0x5C, 0x6E, 0x36, 0x34, 0x5C, 0x53, 0x6F, 0x75, 0x72, 0x63, 0x65, 0x5C, 0x45, 0x4E, 0x47, 0x49, 0x4E, 0x45, 0x5C, 0x52, 0x55, 0x4D, 0x42, 0x4C, 0x45, 0x2E, 0x48 } },
    { 28, SN_LE16(73), 43, { 0x43, 0x3A, 0x5C, 0x50, 0x72, 0x6F, 0x6A, 0x65, 0x63, 0x74, 0x73, 0x5C, 0x44, 0x4D, 0x5C, 0x6E, 0x36, 0x34, 0x5C, 0x53, 0x6F, 0x75, 0x72, 0x63, 0x65, 0x5C, 0x45, 0x4E, 0x47, 0x49, 0x4E, 0x45, 0x5C, 0x47, 0x52, 0x41, 0x50, 0x48, 0x55, 0x36, 0x34, 0x2E, 0x48 } },
    { 28, SN_LE16(72), 43, { 0x43, 0x3A, 0x5C, 0x50, 0x72, 0x6F, 0x6A, 0x65, 0x63, 0x74, 0x73, 0x5C, 0x44, 0x4D, 0x5C, 0x6E, 0x36, 0x34, 0x5C, 0x53, 0x6F, 0x75, 0x72, 0x63, 0x65, 0x5C, 0x45, 0x4E, 0x47, 0x49, 0x4E, 0x45, 0x5C, 0x52, 0x4F, 0x4D, 0x4D, 0x4F, 0x44, 0x45, 0x4C, 0x2E, 0x48 } },
    { 28, SN_LE16(71), 43, { 0x43, 0x3A, 0x5C, 0x50, 0x72, 0x6F, 0x6A, 0x65, 0x63, 0x74, 0x73, 0x5C, 0x44, 0x4D, 0x5C, 0x6E, 0x36, 0x34, 0x5C, 0x53, 0x6F, 0x75, 0x72, 0x63, 0x65, 0x5C, 0x45, 0x4E, 0x47, 0x49, 0x4E, 0x45, 0x5C, 0x47, 0x52, 0x41, 0x50, 0x48, 0x55, 0x36, 0x34, 0x2E, 0x48 } },
    { 28, SN_LE16(70), 43, { 0x43, 0x3A, 0x5C, 0x50, 0x72, 0x6F, 0x6A, 0x65, 0x63, 0x74, 0x73, 0x5C, 0x44, 0x4D, 0x5C, 0x6E, 0x36, 0x34, 0x5C, 0x53, 0x6F, 0x75, 0x72, 0x63, 0x65, 0x5C, 0x45, 0x4E, 0x47, 0x49, 0x4E, 0x45, 0x5C, 0x52, 0x4F, 0x4D, 0x4D, 0x4F, 0x44, 0x45, 0x4C, 0x2E, 0x48 } },
    { 28, SN_LE16(69), 43, { 0x43, 0x3A, 0x5C, 0x50, 0x72, 0x6F, 0x6A, 0x65, 0x63, 0x74, 0x73, 0x5C, 0x44, 0x4D, 0x5C, 0x6E, 0x36, 0x34, 0x5C, 0x53, 0x6F, 0x75, 0x72, 0x63, 0x65, 0x5C, 0x45, 0x4E, 0x47, 0x49, 0x4E, 0x45, 0x5C, 0x47, 0x52, 0x41, 0x50, 0x48, 0x55, 0x36, 0x34, 0x2E, 0x48 } },
    { 28, SN_LE16(68), 41, { 0x43, 0x3A, 0x5C, 0x50, 0x72, 0x6F, 0x6A, 0x65, 0x63, 0x74, 0x73, 0x5C, 0x44, 0x4D, 0x5C, 0x6E, 0x36, 0x34, 0x5C, 0x53, 0x6F, 0x75, 0x72, 0x63, 0x65, 0x5C, 0x45, 0x4E, 0x47, 0x49, 0x4E, 0x45, 0x5C, 0x52, 0x55, 0x4D, 0x42, 0x4C, 0x45, 0x2E, 0x48 } },
    { 28, SN_LE16(67), 42, { 0x43, 0x3A, 0x5C, 0x50, 0x72, 0x6F, 0x6A, 0x65, 0x63, 0x74, 0x73, 0x5C, 0x44, 0x4D, 0x5C, 0x6E, 0x36, 0x34, 0x5C, 0x53, 0x6F, 0x75, 0x72, 0x63, 0x65, 0x5C, 0x45, 0x4E, 0x47, 0x49, 0x4E, 0x45, 0x5C, 0x43, 0x4F, 0x4E, 0x54, 0x52, 0x4F, 0x4C, 0x2E, 0x48 } },
    { 28, SN_LE16(66), 41, { 0x43, 0x3A, 0x5C, 0x50, 0x72, 0x6F, 0x6A, 0x65, 0x63, 0x74, 0x73, 0x5C, 0x44, 0x4D, 0x5C, 0x6E, 0x36, 0x34, 0x5C, 0x53, 0x6F, 0x75, 0x72, 0x63, 0x65, 0x5C, 0x45, 0x4E, 0x47, 0x49, 0x4E, 0x45, 0x5C, 0x43, 0x50, 0x50, 0x55, 0x36, 0x34, 0x2E, 0x48 } },
    { 28, SN_LE16(65), 42, { 0x43, 0x3A, 0x5C, 0x50, 0x72, 0x6F, 0x6A, 0x65, 0x63, 0x74, 0x73, 0x5C, 0x44, 0x4D, 0x5C, 0x6E, 0x36, 0x34, 0x5C, 0x53, 0x6F, 0x75, 0x72, 0x63, 0x65, 0x5C, 0x45, 0x4E, 0x47, 0x49, 0x4E, 0x45, 0x5C, 0x43, 0x4F, 0x4E, 0x54, 0x52, 0x4F, 0x4C, 0x2E, 0x48 } },
    { 28, SN_LE16(64), 39, { 0x43, 0x3A, 0x5C, 0x50, 0x72, 0x6F, 0x6A, 0x65, 0x63, 0x74, 0x73, 0x5C, 0x44, 0x4D, 0x5C, 0x6E, 0x36, 0x34, 0x5C, 0x53, 0x6F, 0x75, 0x72, 0x63, 0x65, 0x5C, 0x45, 0x4E, 0x47, 0x49, 0x4E, 0x45, 0x5C, 0x44, 0x45, 0x46, 0x53, 0x2E, 0x48 } },
    { 28, SN_LE16(63), 36, { 0x43, 0x3A, 0x5C, 0x50, 0x72, 0x6F, 0x6A, 0x65, 0x63, 0x74, 0x73, 0x5C, 0x44, 0x4D, 0x5C, 0x6E, 0x36, 0x34, 0x5C, 0x53, 0x6F, 0x75, 0x72, 0x63, 0x65, 0x5C, 0x47, 0x41, 0x4D, 0x45, 0x54, 0x59, 0x50, 0x45, 0x2E, 0x48 } },
    { 28, SN_LE16(62), 39, { 0x43, 0x3A, 0x5C, 0x50, 0x72, 0x6F, 0x6A, 0x65, 0x63, 0x74, 0x73, 0x5C, 0x44, 0x4D, 0x5C, 0x6E, 0x36, 0x34, 0x5C, 0x53, 0x6F, 0x75, 0x72, 0x63, 0x65, 0x5C, 0x45, 0x4E, 0x47, 0x49, 0x4E, 0x45, 0x5C, 0x44, 0x45, 0x46, 0x53, 0x2E, 0x48 } },
    { 28, SN_LE16(61), 44, { 0x43, 0x3A, 0x5C, 0x50, 0x72, 0x6F, 0x6A, 0x65, 0x63, 0x74, 0x73, 0x5C, 0x44, 0x4D, 0x5C, 0x6E, 0x36, 0x34, 0x5C, 0x53, 0x6F, 0x75, 0x72, 0x63, 0x65, 0x5C, 0x45, 0x4E, 0x47, 0x49, 0x4E, 0x45, 0x5C, 0x54, 0x55, 0x52, 0x4F, 0x4B, 0x54, 0x49, 0x4D, 0x45, 0x2E, 0x48 } },
    { 28, SN_LE16(60), 39, { 0x43, 0x3A, 0x5C, 0x50, 0x72, 0x6F, 0x6A, 0x65, 0x63, 0x74, 0x73, 0x5C, 0x44, 0x4D, 0x5C, 0x6E, 0x36, 0x34, 0x5C, 0x53, 0x6F, 0x75, 0x72, 0x63, 0x65, 0x5C, 0x45, 0x4E, 0x47, 0x49, 0x4E, 0x45, 0x5C, 0x44, 0x45, 0x46, 0x53, 0x2E, 0x48 } },
    { 28, SN_LE16(59), 21, { 0x43, 0x3A, 0x5C, 0x4E, 0x36, 0x34, 0x5C, 0x49, 0x4E, 0x43, 0x4C, 0x55, 0x44, 0x45, 0x5C, 0x50, 0x53, 0x59, 0x51, 0x2E, 0x48 } },
    { 28, SN_LE16(58), 39, { 0x43, 0x3A, 0x5C, 0x50, 0x72, 0x6F, 0x6A, 0x65, 0x63, 0x74, 0x73, 0x5C, 0x44, 0x4D, 0x5C, 0x6E, 0x36, 0x34, 0x5C, 0x53, 0x6F, 0x75, 0x72, 0x63, 0x65, 0x5C, 0x45, 0x4E, 0x47, 0x49, 0x4E, 0x45, 0x5C, 0x44, 0x45, 0x46, 0x53, 0x2E, 0x48 } },
    { 28, SN_LE16(57), 22, { 0x43, 0x3A, 0x5C, 0x4E, 0x36, 0x34, 0x5C, 0x49, 0x4E, 0x43, 0x4C, 0x55, 0x44, 0x45, 0x5C, 0x50, 0x52, 0x5C, 0x4F, 0x53, 0x2E, 0x48 } },
    { 28, SN_LE16(56), 39, { 0x43, 0x3A, 0x5C, 0x50, 0x72, 0x6F, 0x6A, 0x65, 0x63, 0x74, 0x73, 0x5C, 0x44, 0x4D, 0x5C, 0x6E, 0x36, 0x34, 0x5C, 0x53, 0x6F, 0x75, 0x72, 0x63, 0x65, 0x5C, 0x45, 0x4E, 0x47, 0x49, 0x4E, 0x45, 0x5C, 0x44, 0x45, 0x46, 0x53, 0x2E, 0x48 } },
    { 28, SN_LE16(55), 42, { 0x43, 0x3A, 0x5C, 0x50, 0x72, 0x6F, 0x6A, 0x65, 0x63, 0x74, 0x73, 0x5C, 0x44, 0x4D, 0x5C, 0x6E, 0x36, 0x34, 0x5C, 0x53, 0x6F, 0x75, 0x72, 0x63, 0x65, 0x5C, 0x45, 0x4E, 0x47, 0x49, 0x4E, 0x45, 0x5C, 0x43, 0x4F, 0x4E, 0x54, 0x52, 0x4F, 0x4C, 0x2E, 0x48 } },
    { 28, SN_LE16(54), 44, { 0x43, 0x3A, 0x5C, 0x50, 0x72, 0x6F, 0x6A, 0x65, 0x63, 0x74, 0x73, 0x5C, 0x44, 0x4D, 0x5C, 0x6E, 0x36, 0x34, 0x5C, 0x53, 0x6F, 0x75, 0x72, 0x63, 0x65, 0x5C, 0x55, 0x49, 0x5C, 0x53, 0x4D, 0x4F, 0x53, 0x5C, 0x53, 0x4D, 0x5F, 0x58, 0x4C, 0x41, 0x54, 0x45, 0x2E, 0x48 } },
    { 28, SN_LE16(53), 43, { 0x43, 0x3A, 0x5C, 0x50, 0x72, 0x6F, 0x6A, 0x65, 0x63, 0x74, 0x73, 0x5C, 0x44, 0x4D, 0x5C, 0x6E, 0x36, 0x34, 0x5C, 0x53, 0x6F, 0x75, 0x72, 0x63, 0x65, 0x5C, 0x55, 0x49, 0x5C, 0x51, 0x55, 0x41, 0x47, 0x5C, 0x51, 0x5F, 0x49, 0x4E, 0x50, 0x55, 0x54, 0x2E, 0x48 } },
    { 28, SN_LE16(52), 46, { 0x43, 0x3A, 0x5C, 0x50, 0x72, 0x6F, 0x6A, 0x65, 0x63, 0x74, 0x73, 0x5C, 0x44, 0x4D, 0x5C, 0x6E, 0x36, 0x34, 0x5C, 0x53, 0x6F, 0x75, 0x72, 0x63, 0x65, 0x5C, 0x55, 0x49, 0x5C, 0x58, 0x5F, 0x46, 0x49, 0x4C, 0x45, 0x53, 0x5C, 0x58, 0x5F, 0x54, 0x59, 0x50, 0x45, 0x53, 0x2E, 0x48 } },
    { 28, SN_LE16(51), 24, { 0x43, 0x3A, 0x5C, 0x4E, 0x36, 0x34, 0x5C, 0x49, 0x4E, 0x43, 0x4C, 0x55, 0x44, 0x45, 0x5C, 0x55, 0x4C, 0x54, 0x52, 0x41, 0x36, 0x34, 0x2E, 0x48 } },
    { 28, SN_LE16(50), 28, { 0x43, 0x3A, 0x5C, 0x4E, 0x36, 0x34, 0x5C, 0x49, 0x4E, 0x43, 0x4C, 0x55, 0x44, 0x45, 0x5C, 0x50, 0x52, 0x5C, 0x55, 0x4C, 0x54, 0x52, 0x41, 0x4C, 0x4F, 0x47, 0x2E, 0x48 } },
    { 28, SN_LE16(49), 24, { 0x43, 0x3A, 0x5C, 0x4E, 0x36, 0x34, 0x5C, 0x49, 0x4E, 0x43, 0x4C, 0x55, 0x44, 0x45, 0x5C, 0x55, 0x4C, 0x54, 0x52, 0x41, 0x36, 0x34, 0x2E, 0x48 } },
    { 28, SN_LE16(48), 30, { 0x43, 0x3A, 0x5C, 0x4E, 0x36, 0x34, 0x5C, 0x49, 0x4E, 0x43, 0x4C, 0x55, 0x44, 0x45, 0x5C, 0x50, 0x52, 0x5C, 0x55, 0x4C, 0x54, 0x52, 0x41, 0x45, 0x52, 0x52, 0x4F, 0x52, 0x2E, 0x48 } },
    { 28, SN_LE16(47), 24, { 0x43, 0x3A, 0x5C, 0x4E, 0x36, 0x34, 0x5C, 0x49, 0x4E, 0x43, 0x4C, 0x55, 0x44, 0x45, 0x5C, 0x55, 0x4C, 0x54, 0x52, 0x41, 0x36, 0x34, 0x2E, 0x48 } },
    { 28, SN_LE16(46), 25, { 0x43, 0x3A, 0x5C, 0x4E, 0x36, 0x34, 0x5C, 0x49, 0x4E, 0x43, 0x4C, 0x55, 0x44, 0x45, 0x5C, 0x50, 0x52, 0x5C, 0x55, 0x43, 0x4F, 0x44, 0x45, 0x2E, 0x48 } },
    { 28, SN_LE16(45), 24, { 0x43, 0x3A, 0x5C, 0x4E, 0x36, 0x34, 0x5C, 0x49, 0x4E, 0x43, 0x4C, 0x55, 0x44, 0x45, 0x5C, 0x55, 0x4C, 0x54, 0x52, 0x41, 0x36, 0x34, 0x2E, 0x48 } },
    { 28, SN_LE16(44), 22, { 0x43, 0x3A, 0x5C, 0x4E, 0x36, 0x34, 0x5C, 0x49, 0x4E, 0x43, 0x4C, 0x55, 0x44, 0x45, 0x5C, 0x50, 0x52, 0x5C, 0x53, 0x50, 0x2E, 0x48 } },
    { 28, SN_LE16(43), 24, { 0x43, 0x3A, 0x5C, 0x4E, 0x36, 0x34, 0x5C, 0x49, 0x4E, 0x43, 0x4C, 0x55, 0x44, 0x45, 0x5C, 0x55, 0x4C, 0x54, 0x52, 0x41, 0x36, 0x34, 0x2E, 0x48 } },
    { 28, SN_LE16(42), 26, { 0x43, 0x3A, 0x5C, 0x4E, 0x36, 0x34, 0x5C, 0x49, 0x4E, 0x43, 0x4C, 0x55, 0x44, 0x45, 0x5C, 0x50, 0x52, 0x5C, 0x52, 0x41, 0x4D, 0x52, 0x4F, 0x4D, 0x2E, 0x48 } },
    { 28, SN_LE16(41), 24, { 0x43, 0x3A, 0x5C, 0x4E, 0x36, 0x34, 0x5C, 0x49, 0x4E, 0x43, 0x4C, 0x55, 0x44, 0x45, 0x5C, 0x55, 0x4C, 0x54, 0x52, 0x41, 0x36, 0x34, 0x2E, 0x48 } },
    { 28, SN_LE16(40), 22, { 0x43, 0x3A, 0x5C, 0x4E, 0x36, 0x34, 0x5C, 0x49, 0x4E, 0x43, 0x4C, 0x55, 0x44, 0x45, 0x5C, 0x50, 0x52, 0x5C, 0x47, 0x55, 0x2E, 0x48 } },
    { 28, SN_LE16(39), 24, { 0x43, 0x3A, 0x5C, 0x4E, 0x36, 0x34, 0x5C, 0x49, 0x4E, 0x43, 0x4C, 0x55, 0x44, 0x45, 0x5C, 0x55, 0x4C, 0x54, 0x52, 0x41, 0x36, 0x34, 0x2E, 0x48 } },
    { 28, SN_LE16(38), 28, { 0x43, 0x3A, 0x5C, 0x4E, 0x36, 0x34, 0x5C, 0x49, 0x4E, 0x43, 0x4C, 0x55, 0x44, 0x45, 0x5C, 0x50, 0x52, 0x5C, 0x4C, 0x49, 0x42, 0x41, 0x55, 0x44, 0x49, 0x4F, 0x2E, 0x48 } },
    { 28, SN_LE16(37), 24, { 0x43, 0x3A, 0x5C, 0x4E, 0x36, 0x34, 0x5C, 0x49, 0x4E, 0x43, 0x4C, 0x55, 0x44, 0x45, 0x5C, 0x55, 0x4C, 0x54, 0x52, 0x41, 0x36, 0x34, 0x2E, 0x48 } },
    { 28, SN_LE16(36), 23, { 0x43, 0x3A, 0x5C, 0x4E, 0x36, 0x34, 0x5C, 0x49, 0x4E, 0x43, 0x4C, 0x55, 0x44, 0x45, 0x5C, 0x50, 0x52, 0x5C, 0x4D, 0x42, 0x49, 0x2E, 0x48 } },
    { 28, SN_LE16(35), 23, { 0x43, 0x3A, 0x5C, 0x4E, 0x36, 0x34, 0x5C, 0x49, 0x4E, 0x43, 0x4C, 0x55, 0x44, 0x45, 0x5C, 0x50, 0x52, 0x5C, 0x41, 0x42, 0x49, 0x2E, 0x48 } },
    { 28, SN_LE16(34), 22, { 0x43, 0x3A, 0x5C, 0x4E, 0x36, 0x34, 0x5C, 0x49, 0x4E, 0x43, 0x4C, 0x55, 0x44, 0x45, 0x5C, 0x50, 0x52, 0x5C, 0x4F, 0x53, 0x2E, 0x48 } },
    { 28, SN_LE16(33), 23, { 0x43, 0x3A, 0x5C, 0x4E, 0x36, 0x34, 0x5C, 0x49, 0x4E, 0x43, 0x4C, 0x55, 0x44, 0x45, 0x5C, 0x50, 0x52, 0x5C, 0x41, 0x42, 0x49, 0x2E, 0x48 } },
    { 28, SN_LE16(32), 23, { 0x43, 0x3A, 0x5C, 0x4E, 0x36, 0x34, 0x5C, 0x49, 0x4E, 0x43, 0x4C, 0x55, 0x44, 0x45, 0x5C, 0x50, 0x52, 0x5C, 0x4D, 0x42, 0x49, 0x2E, 0x48 } },
    { 28, SN_LE16(31), 23, { 0x43, 0x3A, 0x5C, 0x4E, 0x36, 0x34, 0x5C, 0x49, 0x4E, 0x43, 0x4C, 0x55, 0x44, 0x45, 0x5C, 0x50, 0x52, 0x5C, 0x47, 0x42, 0x49, 0x2E, 0x48 } },
    { 28, SN_LE16(30), 23, { 0x43, 0x3A, 0x5C, 0x4E, 0x36, 0x34, 0x5C, 0x49, 0x4E, 0x43, 0x4C, 0x55, 0x44, 0x45, 0x5C, 0x50, 0x52, 0x5C, 0x4D, 0x42, 0x49, 0x2E, 0x48 } },
    { 28, SN_LE16(29), 24, { 0x43, 0x3A, 0x5C, 0x4E, 0x36, 0x34, 0x5C, 0x49, 0x4E, 0x43, 0x4C, 0x55, 0x44, 0x45, 0x5C, 0x55, 0x4C, 0x54, 0x52, 0x41, 0x36, 0x34, 0x2E, 0x48 } },
    { 28, SN_LE16(28), 26, { 0x43, 0x3A, 0x5C, 0x4E, 0x36, 0x34, 0x5C, 0x49, 0x4E, 0x43, 0x4C, 0x55, 0x44, 0x45, 0x5C, 0x50, 0x52, 0x5C, 0x53, 0x50, 0x54, 0x41, 0x53, 0x4B, 0x2E, 0x48 } },
    { 28, SN_LE16(27), 24, { 0x43, 0x3A, 0x5C, 0x4E, 0x36, 0x34, 0x5C, 0x49, 0x4E, 0x43, 0x4C, 0x55, 0x44, 0x45, 0x5C, 0x55, 0x4C, 0x54, 0x52, 0x41, 0x36, 0x34, 0x2E, 0x48 } },
    { 28, SN_LE16(26), 24, { 0x43, 0x3A, 0x5C, 0x4E, 0x36, 0x34, 0x5C, 0x49, 0x4E, 0x43, 0x4C, 0x55, 0x44, 0x45, 0x5C, 0x50, 0x52, 0x5C, 0x52, 0x4D, 0x4F, 0x4E, 0x2E, 0x48 } },
    { 28, SN_LE16(25), 24, { 0x43, 0x3A, 0x5C, 0x4E, 0x36, 0x34, 0x5C, 0x49, 0x4E, 0x43, 0x4C, 0x55, 0x44, 0x45, 0x5C, 0x55, 0x4C, 0x54, 0x52, 0x41, 0x36, 0x34, 0x2E, 0x48 } },
    { 28, SN_LE16(24), 26, { 0x43, 0x3A, 0x5C, 0x4E, 0x36, 0x34, 0x5C, 0x49, 0x4E, 0x43, 0x4C, 0x55, 0x44, 0x45, 0x5C, 0x50, 0x52, 0x5C, 0x52, 0x45, 0x47, 0x49, 0x4F, 0x4E, 0x2E, 0x48 } },
    { 28, SN_LE16(23), 24, { 0x43, 0x3A, 0x5C, 0x4E, 0x36, 0x34, 0x5C, 0x49, 0x4E, 0x43, 0x4C, 0x55, 0x44, 0x45, 0x5C, 0x55, 0x4C, 0x54, 0x52, 0x41, 0x36, 0x34, 0x2E, 0x48 } },
    { 28, SN_LE16(22), 22, { 0x43, 0x3A, 0x5C, 0x4E, 0x36, 0x34, 0x5C, 0x49, 0x4E, 0x43, 0x4C, 0x55, 0x44, 0x45, 0x5C, 0x50, 0x52, 0x5C, 0x4F, 0x53, 0x2E, 0x48 } },
    { 28, SN_LE16(21), 24, { 0x43, 0x3A, 0x5C, 0x4E, 0x36, 0x34, 0x5C, 0x49, 0x4E, 0x43, 0x4C, 0x55, 0x44, 0x45, 0x5C, 0x55, 0x4C, 0x54, 0x52, 0x41, 0x36, 0x34, 0x2E, 0x48 } },
    { 28, SN_LE16(20), 23, { 0x43, 0x3A, 0x5C, 0x4E, 0x36, 0x34, 0x5C, 0x49, 0x4E, 0x43, 0x4C, 0x55, 0x44, 0x45, 0x5C, 0x50, 0x52, 0x5C, 0x52, 0x43, 0x50, 0x2E, 0x48 } },
    { 28, SN_LE16(19), 25, { 0x43, 0x3A, 0x5C, 0x4E, 0x36, 0x34, 0x5C, 0x49, 0x4E, 0x43, 0x4C, 0x55, 0x44, 0x45, 0x5C, 0x50, 0x52, 0x5C, 0x52, 0x34, 0x33, 0x30, 0x30, 0x2E, 0x48 } },
    { 28, SN_LE16(18), 23, { 0x43, 0x3A, 0x5C, 0x4E, 0x36, 0x34, 0x5C, 0x49, 0x4E, 0x43, 0x4C, 0x55, 0x44, 0x45, 0x5C, 0x50, 0x52, 0x5C, 0x52, 0x43, 0x50, 0x2E, 0x48 } },
    { 28, SN_LE16(17), 24, { 0x43, 0x3A, 0x5C, 0x4E, 0x36, 0x34, 0x5C, 0x49, 0x4E, 0x43, 0x4C, 0x55, 0x44, 0x45, 0x5C, 0x55, 0x4C, 0x54, 0x52, 0x41, 0x36, 0x34, 0x2E, 0x48 } },
    { 28, SN_LE16(16), 30, { 0x43, 0x3A, 0x5C, 0x4E, 0x36, 0x34, 0x5C, 0x49, 0x4E, 0x43, 0x4C, 0x55, 0x44, 0x45, 0x5C, 0x50, 0x52, 0x5C, 0x55, 0x4C, 0x54, 0x52, 0x41, 0x54, 0x59, 0x50, 0x45, 0x53, 0x2E, 0x48 } },
    { 28, SN_LE16(15), 24, { 0x43, 0x3A, 0x5C, 0x4E, 0x36, 0x34, 0x5C, 0x49, 0x4E, 0x43, 0x4C, 0x55, 0x44, 0x45, 0x5C, 0x55, 0x4C, 0x54, 0x52, 0x41, 0x36, 0x34, 0x2E, 0x48 } },
    { 28, SN_LE16(14), 46, { 0x43, 0x3A, 0x5C, 0x50, 0x72, 0x6F, 0x6A, 0x65, 0x63, 0x74, 0x73, 0x5C, 0x44, 0x4D, 0x5C, 0x6E, 0x36, 0x34, 0x5C, 0x53, 0x6F, 0x75, 0x72, 0x63, 0x65, 0x5C, 0x55, 0x49, 0x5C, 0x58, 0x5F, 0x46, 0x49, 0x4C, 0x45, 0x53, 0x5C, 0x58, 0x5F, 0x54, 0x59, 0x50, 0x45, 0x53, 0x2E, 0x48 } },
    { 28, SN_LE16(13), 47, { 0x43, 0x3A, 0x5C, 0x50, 0x72, 0x6F, 0x6A, 0x65, 0x63, 0x74, 0x73, 0x5C, 0x44, 0x4D, 0x5C, 0x6E, 0x36, 0x34, 0x5C, 0x53, 0x6F, 0x75, 0x72, 0x63, 0x65, 0x5C, 0x55, 0x49, 0x5C, 0x58, 0x5F, 0x46, 0x49, 0x4C, 0x45, 0x53, 0x5C, 0x58, 0x5F, 0x54, 0x41, 0x52, 0x47, 0x45, 0x54, 0x2E, 0x48 } },
    { 28, SN_LE16(12), 46, { 0x43, 0x3A, 0x5C, 0x50, 0x72, 0x6F, 0x6A, 0x65, 0x63, 0x74, 0x73, 0x5C, 0x44, 0x4D, 0x5C, 0x6E, 0x36, 0x34, 0x5C, 0x53, 0x6F, 0x75, 0x72, 0x63, 0x65, 0x5C, 0x55, 0x49, 0x5C, 0x58, 0x5F, 0x46, 0x49, 0x4C, 0x45, 0x53, 0x5C, 0x58, 0x5F, 0x54, 0x59, 0x50, 0x45, 0x53, 0x2E, 0x48 } },
    { 28, SN_LE16(11), 43, { 0x43, 0x3A, 0x5C, 0x50, 0x72, 0x6F, 0x6A, 0x65, 0x63, 0x74, 0x73, 0x5C, 0x44, 0x4D, 0x5C, 0x6E, 0x36, 0x34, 0x5C, 0x53, 0x6F, 0x75, 0x72, 0x63, 0x65, 0x5C, 0x55, 0x49, 0x5C, 0x51, 0x55, 0x41, 0x47, 0x5C, 0x51, 0x5F, 0x49, 0x4E, 0x50, 0x55, 0x54, 0x2E, 0x48 } },
    { 28, SN_LE16(10), 44, { 0x43, 0x3A, 0x5C, 0x50, 0x72, 0x6F, 0x6A, 0x65, 0x63, 0x74, 0x73, 0x5C, 0x44, 0x4D, 0x5C, 0x6E, 0x36, 0x34, 0x5C, 0x53, 0x6F, 0x75, 0x72, 0x63, 0x65, 0x5C, 0x55, 0x49, 0x5C, 0x53, 0x4D, 0x4F, 0x53, 0x5C, 0x53, 0x4D, 0x5F, 0x58, 0x4C, 0x41, 0x54, 0x45, 0x2E, 0x48 } },
    { 28, SN_LE16(9), 65, { 0x43, 0x3A, 0x5C, 0x50, 0x52, 0x4F, 0x4A, 0x45, 0x43, 0x54, 0x53, 0x5C, 0x44, 0x4D, 0x5C, 0x4E, 0x36, 0x34, 0x5C, 0x53, 0x4F, 0x55, 0x52, 0x43, 0x45, 0x5C, 0x55, 0x49, 0x5C, 0x54, 0x53, 0x4D, 0x4F, 0x53, 0x5C, 0x53, 0x43, 0x52, 0x45, 0x45, 0x4E, 0x53, 0x5C, 0x50, 0x41, 0x4B, 0x49, 0x4E, 0x54, 0x45, 0x52, 0x46, 0x41, 0x43, 0x45, 0x53, 0x43, 0x52, 0x45, 0x45, 0x4E, 0x2E, 0x43, 0x50, 0x50 } },
    { 6, SN_LE16(2) },
    { 6, SN_LE16(2) },
    { 6, SN_LE16(3) },
    { 6, SN_LE16(2) },
    { 6, SN_LE16(3) },
    { 2, SN_LE16(4), { 0x00, 0x00, 0x00, 0x00 } },
    { 6, SN_LE16(2) },
    { 6, SN_LE16(3) },
    { 2, SN_LE16(4), { 0x00, 0x00, 0x00, 0x00 } },
    { 6, SN_LE16(1) },
    { 2, SN_LE16(130), { 0x43, 0x3A, 0x2F, 0x50, 0x72, 0x6F, 0x6A, 0x65, 0x63, 0x74, 0x73, 0x2F, 0x44, 0x4D, 0x2F, 0x6E, 0x36, 0x34, 0x2F, 0x53, 0x6F, 0x75, 0x72, 0x63, 0x65, 0x2F, 0x55, 0x69, 0x2F, 0x54, 0x73, 0x6D, 0x6F, 0x73, 0x2F, 0x53, 0x63, 0x72, 0x65, 0x65, 0x6E, 0x73, 0x2F, 0x50, 0x41, 0x4B, 0x49, 0x6E, 0x74, 0x65, 0x72, 0x66, 0x61, 0x63, 0x65, 0x53, 0x63, 0x72, 0x65, 0x65, 0x6E, 0x2E, 0x63, 0x70, 0x70, 0x00, 0x00, 0x00, 0x50, 0x41, 0x4B, 0x49, 0x6E, 0x74, 0x65, 0x72, 0x66, 0x61, 0x63, 0x65, 0x53, 0x63, 0x72, 0x65, 0x65, 0x6E, 0x20, 0x3D, 0x3D, 0x20, 0x4E, 0x55, 0x4C, 0x4C, 0x00, 0x00, 0x50, 0x41, 0x4B, 0x49, 0x6E, 0x74, 0x65, 0x72, 0x66, 0x61, 0x63, 0x65, 0x53, 0x63, 0x72, 0x65, 0x65, 0x6E, 0x20, 0x21, 0x3D, 0x20, 0x4E, 0x55, 0x4C, 0x4C, 0x00, 0x00, 0x46, 0x41, 0x4C, 0x53, 0x45, 0x00 } },
    { 6, SN_LE16(2) },
    { 2, SN_LE16(1356) },
};
typedef char MenuResourceStreamSize[(sizeof(SnObjectRecords) == 7843) ? 1 : -1];
#endif

















#if VERSION_US
/* Typed Psy-Q records surrounding OnAccept pieces eight and nine. */
struct {
    u8 precedingRecordFragment[10];
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record1;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record2;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record3;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record4;
    struct { u8 opcode; SnLe16 section; } record5;
    struct { u8 opcode; SnLe16 codeSize; } record6;
} k_LibsnEnumeratememoryrangesEncodedWords __attribute__((aligned(1))) = {
    { 0x00, 0x2C, 0x04, 0x02, 0x00, 0x00, 0x44, 0x70, 0x00, 0x00 },
    { 10, 8, SN_LE16(16), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(28820) } } },
    { 10, 8, SN_LE16(20), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(28756) } } },
    { 10, 8, SN_LE16(24), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(28820) } } },
    { 10, 8, SN_LE16(28), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(28772) } } },
    { 6, SN_LE16(2) },
    { 2, SN_LE16(2164) },
};
#endif

#if VERSION_US
struct {
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record7;
    struct { u8 opcode; SnLe16 offset; } record8;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record9;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record10;
    struct { u8 opcode; SnLe16 offset; } record11;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record12;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record13;
    struct { u8 opcode; SnLe16 offset; } record14;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record15;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record16;
    struct { u8 opcode; SnLe16 offset; } record17;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record18;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record19;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record20;
    struct { u8 opcode; SnLe16 offset; } record21;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record22;
    struct { u8 opcode; SnLe16 offset; } record23;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record24;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record25;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record26;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record27;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record28;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; SnLe16 symbol; } expression; } record29;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record30;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record31;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record32;
    struct { u8 opcode; SnLe16 offset; } record33;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record34;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record35;
    struct { u8 opcode; SnLe16 offset; } record36;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record37;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record38;
    struct { u8 opcode; SnLe16 offset; } record39;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record40;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record41;
    struct { u8 opcode; SnLe16 offset; } record42;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record43;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record44;
    struct { u8 opcode; SnLe16 offset; } record45;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record46;
    struct { u8 opcode; SnLe16 offset; } record47;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record48;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record49;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record50;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record51;
    struct { u8 opcode; SnLe16 offset; } record52;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record53;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record54;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record55;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record56;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record57;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record58;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record59;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record60;
    struct { u8 opcode; SnLe16 offset; } record61;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record62;
    struct { u8 opcode; SnLe16 offset; } record63;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record64;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record65;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record66;
    struct { u8 opcode; SnLe16 offset; } record67;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record68;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record69;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record70;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record71;
    struct { u8 opcode; SnLe16 offset; } record72;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record73;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record74;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record75;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record76;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record77;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record78;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record79;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record80;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record81;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record82;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record83;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record84;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record85;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record86;
    struct { u8 opcode; SnLe16 offset; } record87;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record88;
    struct { u8 opcode; SnLe16 offset; } record89;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record90;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record91;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record92;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record93;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record94;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record95;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; SnLe16 symbol; } expression; } record96;
    struct { u8 opcode; SnLe16 offset; } record97;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record98;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record99;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record100;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record101;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record102;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record103;
    struct { u8 opcode; SnLe16 offset; } record104;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record105;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record106;
    struct { u8 opcode; SnLe16 offset; } record107;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record108;
    struct { u8 opcode; SnLe16 offset; } record109;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record110;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record111;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record112;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record113;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record114;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record115;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record116;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record117;
    struct { u8 opcode; SnLe16 offset; } record118;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record119;
    struct { u8 opcode; SnLe16 offset; } record120;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record121;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record122;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record123;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record124;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record125;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record126;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record127;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record128;
    struct { u8 opcode; SnLe16 offset; } record129;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record130;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record131;
    struct { u8 opcode; SnLe16 offset; } record132;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record133;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record134;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record135;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record136;
    struct { u8 opcode; SnLe16 offset; } record137;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record138;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record139;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record140;
    struct { u8 opcode; SnLe16 offset; } record141;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record142;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record143;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record144;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record145;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record146;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record147;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record148;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record149;
    struct { u8 opcode; SnLe16 offset; } record150;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record151;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record152;
    struct { u8 opcode; SnLe16 offset; } record153;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record154;
    struct { u8 opcode; SnLe16 offset; } record155;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record156;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record157;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record158;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record159;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record160;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record161;
    struct { u8 opcode; SnLe16 offset; } record162;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record163;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record164;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record165;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record166;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record167;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record168;
    struct { u8 opcode; SnLe16 offset; } record169;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record170;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record171;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record172;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record173;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record174;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record175;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record176;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record177;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record178;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record179;
    struct { u8 opcode; SnLe16 offset; } record180;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record181;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record182;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record183;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record184;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record185;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record186;
    struct { u8 opcode; SnLe16 offset; } record187;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record188;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record189;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record190;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record191;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record192;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record193;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record194;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record195;
    struct { u8 opcode; SnLe16 offset; } record196;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record197;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record198;
    struct { u8 opcode; SnLe16 offset; } record199;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record200;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record201;
    struct { u8 opcode; SnLe16 offset; } record202;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record203;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record204;
    struct { u8 opcode; SnLe16 offset; } record205;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record206;
    struct { u8 opcode; SnLe16 offset; } record207;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record208;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record209;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; SnLe16 symbol; } expression; } record210;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record211;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; SnLe16 symbol; } expression; } record212;
    struct { u8 opcode; SnLe16 offset; } record213;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record214;
    struct { u8 opcode; SnLe16 offset; } record215;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record216;
    struct { u8 opcode; SnLe16 offset; } record217;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record218;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record219;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record220;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record221;
    struct { u8 opcode; SnLe16 codeSize; } record222;
} g_pakOnAcceptRecordTail __attribute__((aligned(1))) = {
    { 52, SN_LE16(0), 3 },
    { 50, SN_LE16(4) },
    { 10, 92, SN_LE16(4), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(28820) } } },
    { 52, SN_LE16(12), 3 },
    { 50, SN_LE16(20) },
    { 10, 92, SN_LE16(20), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(28820) } } },
    { 52, SN_LE16(28), 3 },
    { 50, SN_LE16(36) },
    { 10, 92, SN_LE16(36), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(28820) } } },
    { 52, SN_LE16(44), 3 },
    { 50, SN_LE16(52) },
    { 10, 92, SN_LE16(52), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(28820) } } },
    { 52, SN_LE16(60), 3 },
    { 10, 92, SN_LE16(64), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(64660) } } },
    { 50, SN_LE16(72) },
    { 10, 92, SN_LE16(76), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(31464) } } },
    { 50, SN_LE16(84) },
    { 10, 92, SN_LE16(84), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(28820) } } },
    { 52, SN_LE16(92), 9 },
    { 52, SN_LE16(108), 4 },
    { 10, 96, SN_LE16(110), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(114), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 92, SN_LE16(128), { 2, SN_LE16(422) } },
    { 52, SN_LE16(136), 3 },
    { 10, 96, SN_LE16(138), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(142), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 50, SN_LE16(192) },
    { 10, 96, SN_LE16(194), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(198), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 50, SN_LE16(248) },
    { 10, 96, SN_LE16(250), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(254), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 50, SN_LE16(304) },
    { 10, 96, SN_LE16(306), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(310), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 50, SN_LE16(360) },
    { 10, 96, SN_LE16(362), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(366), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 50, SN_LE16(416) },
    { 10, 92, SN_LE16(420), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(32704) } } },
    { 50, SN_LE16(428) },
    { 10, 92, SN_LE16(428), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(29232) } } },
    { 52, SN_LE16(436), 3 },
    { 10, 96, SN_LE16(438), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(442), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 50, SN_LE16(492) },
    { 10, 92, SN_LE16(496), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(32704) } } },
    { 52, SN_LE16(504), 2 },
    { 10, 92, SN_LE16(504), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(31452) } } },
    { 52, SN_LE16(512), 159 },
    { 10, 92, SN_LE16(540), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(29464) } } },
    { 52, SN_LE16(548), 3 },
    { 10, 96, SN_LE16(550), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(554), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 50, SN_LE16(604) },
    { 10, 92, SN_LE16(608), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(32704) } } },
    { 50, SN_LE16(616) },
    { 10, 92, SN_LE16(616), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(29464) } } },
    { 52, SN_LE16(624), 3 },
    { 10, 92, SN_LE16(628), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(66520) } } },
    { 50, SN_LE16(636) },
    { 10, 92, SN_LE16(640), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(61412) } } },
    { 52, SN_LE16(660), 2 },
    { 10, 96, SN_LE16(662), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(666), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 50, SN_LE16(716) },
    { 10, 92, SN_LE16(720), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(32704) } } },
    { 52, SN_LE16(728), 2 },
    { 10, 92, SN_LE16(728), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(29464) } } },
    { 52, SN_LE16(736), 2 },
    { 10, 92, SN_LE16(736), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(31452) } } },
    { 52, SN_LE16(744), 4 },
    { 10, 92, SN_LE16(772), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(29812) } } },
    { 52, SN_LE16(780), 3 },
    { 10, 96, SN_LE16(782), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(786), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 92, SN_LE16(812), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(29548) } } },
    { 52, SN_LE16(820), 13 },
    { 10, 96, SN_LE16(822), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(826), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 50, SN_LE16(876) },
    { 10, 92, SN_LE16(880), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(32704) } } },
    { 50, SN_LE16(888) },
    { 10, 92, SN_LE16(888), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(29672) } } },
    { 52, SN_LE16(896), 3 },
    { 10, 96, SN_LE16(898), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(0) } } },
    { 10, 98, SN_LE16(902), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(0) } } },
    { 10, 96, SN_LE16(910), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(124) } } },
    { 10, 98, SN_LE16(914), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(124) } } },
    { 10, 92, SN_LE16(916), { 2, SN_LE16(376) } },
    { 50, SN_LE16(936) },
    { 10, 92, SN_LE16(936), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(29672) } } },
    { 52, SN_LE16(944), 2 },
    { 10, 92, SN_LE16(944), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(29812) } } },
    { 52, SN_LE16(952), 3 },
    { 10, 96, SN_LE16(954), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(958), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 50, SN_LE16(1008) },
    { 10, 96, SN_LE16(1010), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(1014), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 50, SN_LE16(1064) },
    { 10, 92, SN_LE16(1068), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(32704) } } },
    { 50, SN_LE16(1076) },
    { 10, 92, SN_LE16(1076), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(29812) } } },
    { 52, SN_LE16(1084), 2 },
    { 10, 92, SN_LE16(1084), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(31452) } } },
    { 52, SN_LE16(1092), 3 },
    { 10, 92, SN_LE16(1120), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(30168) } } },
    { 52, SN_LE16(1128), 3 },
    { 10, 96, SN_LE16(1130), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(1134), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 50, SN_LE16(1184) },
    { 10, 92, SN_LE16(1188), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(32704) } } },
    { 50, SN_LE16(1196) },
    { 10, 92, SN_LE16(1196), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(30168) } } },
    { 52, SN_LE16(1204), 3 },
    { 10, 96, SN_LE16(1206), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(1210), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 92, SN_LE16(1228), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(30084) } } },
    { 52, SN_LE16(1236), 3 },
    { 10, 96, SN_LE16(1238), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(1242), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 50, SN_LE16(1292) },
    { 10, 96, SN_LE16(1294), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(1298), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 50, SN_LE16(1348) },
    { 10, 92, SN_LE16(1348), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(30148) } } },
    { 52, SN_LE16(1356), 4 },
    { 10, 96, SN_LE16(1358), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(1362), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 50, SN_LE16(1412) },
    { 10, 92, SN_LE16(1412), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(30148) } } },
    { 52, SN_LE16(1420), 2 },
    { 10, 92, SN_LE16(1424), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(32704) } } },
    { 50, SN_LE16(1432) },
    { 10, 92, SN_LE16(1432), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(30168) } } },
    { 52, SN_LE16(1440), 2 },
    { 10, 92, SN_LE16(1440), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(31452) } } },
    { 52, SN_LE16(1448), 3 },
    { 10, 92, SN_LE16(1476), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(30504) } } },
    { 52, SN_LE16(1484), 3 },
    { 10, 96, SN_LE16(1486), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(1490), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 50, SN_LE16(1540) },
    { 10, 96, SN_LE16(1542), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(1546), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 50, SN_LE16(1596) },
    { 10, 92, SN_LE16(1600), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(32704) } } },
    { 50, SN_LE16(1608) },
    { 10, 92, SN_LE16(1608), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(30504) } } },
    { 52, SN_LE16(1616), 3 },
    { 10, 96, SN_LE16(1618), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(1622), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 52, SN_LE16(1680), 2 },
    { 10, 92, SN_LE16(1684), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(67732) } } },
    { 50, SN_LE16(1692) },
    { 10, 92, SN_LE16(1692), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(30484) } } },
    { 52, SN_LE16(1700), 2 },
    { 10, 96, SN_LE16(1702), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(1706), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 52, SN_LE16(1756), 2 },
    { 10, 92, SN_LE16(1760), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(32704) } } },
    { 50, SN_LE16(1768) },
    { 10, 92, SN_LE16(1768), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(30504) } } },
    { 52, SN_LE16(1776), 2 },
    { 10, 92, SN_LE16(1776), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(31452) } } },
    { 52, SN_LE16(1784), 3 },
    { 10, 92, SN_LE16(1800), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(30696) } } },
    { 52, SN_LE16(1808), 3 },
    { 10, 96, SN_LE16(1810), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(1814), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 52, SN_LE16(1872), 3 },
    { 10, 92, SN_LE16(1876), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(67732) } } },
    { 50, SN_LE16(1884) },
    { 10, 92, SN_LE16(1884), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(30676) } } },
    { 52, SN_LE16(1892), 2 },
    { 10, 96, SN_LE16(1894), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(1898), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 52, SN_LE16(1948), 2 },
    { 10, 92, SN_LE16(1952), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(32704) } } },
    { 50, SN_LE16(1960) },
    { 10, 92, SN_LE16(1960), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(30696) } } },
    { 52, SN_LE16(1968), 2 },
    { 10, 92, SN_LE16(1968), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(31452) } } },
    { 52, SN_LE16(1976), 3 },
    { 10, 92, SN_LE16(2004), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(30876) } } },
    { 52, SN_LE16(2012), 7 },
    { 10, 96, SN_LE16(2014), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(2018), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 50, SN_LE16(2028) },
    { 10, 96, SN_LE16(2030), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(2034), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 50, SN_LE16(2044) },
    { 10, 96, SN_LE16(2046), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(2050), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 50, SN_LE16(2060) },
    { 10, 96, SN_LE16(2062), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(2066), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 50, SN_LE16(2076) },
    { 10, 92, SN_LE16(2080), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(32704) } } },
    { 50, SN_LE16(2088) },
    { 10, 92, SN_LE16(2088), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(30876) } } },
    { 52, SN_LE16(2096), 11 },
    { 10, 92, SN_LE16(2100), { 2, SN_LE16(423) } },
    { 52, SN_LE16(2108), 3 },
    { 10, 92, SN_LE16(2108), { 2, SN_LE16(402) } },
    { 50, SN_LE16(2116) },
    { 10, 92, SN_LE16(2120), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(64660) } } },
    { 50, SN_LE16(2128) },
    { 10, 92, SN_LE16(2132), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(31464) } } },
    { 50, SN_LE16(2140) },
    { 10, 92, SN_LE16(2140), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(30876) } } },
    { 52, SN_LE16(2148), 2 },
    { 10, 92, SN_LE16(2148), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(31452) } } },
    { 52, SN_LE16(2156), 3 },
    { 2, SN_LE16(1316) }
};
#endif



#if defined(VERSION_DE) || defined(VERSION_US)
#ifdef VERSION_US
struct {
    u8 precedingRecordFragment[5];
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record1;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record2;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record3;
    u8 followingRecordFragment[6];
} g_playerNameSuffixLinkerRecordFragment __attribute__((aligned(4))) = {
    { 0x00, 0xAC, 0x7D, 0x00, 0x00 },
    { 52, SN_LE16(896), 42 },
    { 10, 92, SN_LE16(896), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(63148) } } },
    { 52, SN_LE16(912), 2 },
    { 0x0A, 0x5C, 0x90, 0x03, 0x02, 0x92 }
};
typedef char PlayerNameSuffixLinkerRecordFragmentSizeCheck[(sizeof(g_playerNameSuffixLinkerRecordFragment) == 32) ? 1 : -1];
#if defined(VERSION_US)
struct {
    u8 precedingRecordFragment[1];
    struct { u8 opcode; SnLe16 offset; } record0;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record1;
    struct { u8 opcode; SnLe16 offset; } record2;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record3;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record4;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record5;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record6;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; SnLe16 symbol; } expression; } record7;
    struct { u8 opcode; SnLe16 offset; } record8;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record9;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record10;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record11;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record12;
    struct { u8 opcode; SnLe16 offset; } record13;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record14;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record15;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; SnLe16 symbol; } expression; } record16;
    struct { u8 opcode; SnLe16 offset; } record17;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record18;
    struct { u8 opcode; SnLe16 offset; } record19;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record20;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record21;
    struct { u8 opcode; SnLe16 offset; } record22;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record23;
    struct { u8 opcode; SnLe16 offset; } record24;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record25;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record26;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; SnLe16 symbol; } expression; } record27;
    struct { u8 opcode; SnLe16 offset; } record28;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record29;
    struct { u8 opcode; SnLe16 offset; } record30;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record31;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record32;
    struct { u8 opcode; SnLe16 offset; } record33;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record34;
    struct { u8 opcode; SnLe16 offset; } record35;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record36;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record37;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record38;
    struct { u8 opcode; SnLe16 offset; } record39;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record40;
    struct { u8 opcode; SnLe16 section; } record41;
    struct { u8 opcode; SnLe16 codeSize; u8 codeFragment[158]; } record42;
} k_ItemsCopylocalizedplayernamesuffixEncodedWords __attribute__((aligned(4))) = {
    { 0x01 },
    { 50, SN_LE16(920) },
    { 10, 92, SN_LE16(924), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(64660) } } },
    { 50, SN_LE16(932) },
    { 10, 92, SN_LE16(936), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(32184) } } },
    { 52, SN_LE16(944), 3 },
    { 10, 92, SN_LE16(944), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(32172) } } },
    { 52, SN_LE16(952), 5 },
    { 10, 92, SN_LE16(952), { 2, SN_LE16(402) } },
    { 50, SN_LE16(960) },
    { 10, 96, SN_LE16(962), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(966), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 96, SN_LE16(970), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(974), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 50, SN_LE16(1080) },
    { 10, 92, SN_LE16(1080), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(32172) } } },
    { 52, SN_LE16(1088), 4 },
    { 10, 92, SN_LE16(1088), { 2, SN_LE16(402) } },
    { 50, SN_LE16(1096) },
    { 10, 92, SN_LE16(1100), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(52984) } } },
    { 50, SN_LE16(1108) },
    { 10, 96, SN_LE16(1110), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(1114), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 50, SN_LE16(1164) },
    { 10, 92, SN_LE16(1168), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(32704) } } },
    { 50, SN_LE16(1176) },
    { 10, 92, SN_LE16(1176), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(32172) } } },
    { 52, SN_LE16(1184), 3 },
    { 10, 92, SN_LE16(1184), { 2, SN_LE16(402) } },
    { 50, SN_LE16(1192) },
    { 10, 92, SN_LE16(1196), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(53760) } } },
    { 50, SN_LE16(1204) },
    { 10, 96, SN_LE16(1206), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(1210), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 50, SN_LE16(1260) },
    { 10, 92, SN_LE16(1264), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(32704) } } },
    { 50, SN_LE16(1272) },
    { 10, 92, SN_LE16(1272), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(32172) } } },
    { 52, SN_LE16(1280), 35 },
    { 10, 92, SN_LE16(1284), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(32184) } } },
    { 50, SN_LE16(1292) },
    { 52, SN_LE16(1316), 0 },
    { 6, SN_LE16(3) },
    { 2, SN_LE16(168), { 0x00, 0x00, 0x0E, 0x07, 0x00, 0x00, 0x00, 0x13, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0E, 0x0A, 0x00, 0x00, 0x00, 0x13, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0E, 0x08, 0x00, 0x00, 0x00, 0x13, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0E, 0x06, 0x00, 0x00, 0x00, 0x13, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0E, 0x03, 0x00, 0x00, 0x00, 0x13, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x13, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x13, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x00, 0x13, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0B, 0x00, 0x00, 0x00, 0x13, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x13, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x13, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x13, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x13, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 } }
};
typedef char k_ItemsCopylocalizedplayernamesuffixDataSizeCheck[(sizeof(k_ItemsCopylocalizedplayernamesuffixEncodedWords) == 496) ? 1 : -1];
#endif
#endif
#endif



#if VERSION_US
struct {
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record16;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record17;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record18;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record19;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record20;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record21;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record22;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record23;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record24;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record25;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record26;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record27;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record28;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record29;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record30;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record31;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record32;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record33;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record34;
    struct { u8 opcode; SnLe16 section; } record35;
    struct { u8 opcode; SnLe16 codeSize; u8 code[81]; } record36;
    struct { u8 opcode; SnLe16 section; } record37;
    struct { u8 opcode; SnLe16 codeSize; } record38;
} g_pakInterfaceProcRecords __attribute__((aligned(1))) = {
    { 52, SN_LE16(0), 5 },
    { 52, SN_LE16(0), 0 },
    { 52, SN_LE16(32), 14 },
    { 10, 96, SN_LE16(58), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(16) } } },
    { 10, 98, SN_LE16(66), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(16) } } },
    { 10, 92, SN_LE16(76), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(32536) } } },
    { 10, 96, SN_LE16(106), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(8) } } },
    { 10, 98, SN_LE16(114), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(8) } } },
    { 10, 96, SN_LE16(158), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(12) } } },
    { 10, 98, SN_LE16(166), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(12) } } },
    { 10, 96, SN_LE16(198), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(12) } } },
    { 10, 98, SN_LE16(206), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(12) } } },
    { 10, 92, SN_LE16(220), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(32516) } } },
    { 10, 96, SN_LE16(258), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(16) } } },
    { 10, 98, SN_LE16(266), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(16) } } },
    { 10, 92, SN_LE16(300), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(32548) } } },
    { 10, 92, SN_LE16(320), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(32244) } } },
    { 10, 92, SN_LE16(332), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(32548) } } },
    { 52, SN_LE16(364), 0 },
    { 6, SN_LE16(1) },
    { 2, SN_LE16(81), { 0x61, 0x6E, 0x4D, 0x6F, 0x64, 0x65, 0x20, 0x3E, 0x3D, 0x20, 0x50, 0x41, 0x4B, 0x49, 0x4E, 0x54, 0x45, 0x52, 0x46, 0x41, 0x43, 0x45, 0x5F, 0x53, 0x43, 0x52, 0x45, 0x45, 0x4E, 0x4D, 0x4F, 0x44, 0x45, 0x5F, 0x43, 0x52, 0x45, 0x41, 0x54, 0x45, 0x20, 0x26, 0x26, 0x20, 0x61, 0x6E, 0x4D, 0x6F, 0x64, 0x65, 0x20, 0x3C, 0x20, 0x50, 0x41, 0x4B, 0x49, 0x4E, 0x54, 0x45, 0x52, 0x46, 0x41, 0x43, 0x45, 0x5F, 0x53, 0x43, 0x52, 0x45, 0x45, 0x4E, 0x4D, 0x4F, 0x44, 0x45, 0x5F, 0x45, 0x4E, 0x44, 0x00 } },
    { 6, SN_LE16(2) },
    { 2, SN_LE16(132) },
};
#endif



#if VERSION_US
struct {
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record39;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record40;
    struct { u8 opcode; SnLe16 offset; } record41;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record42;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record43;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record44;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record45;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record46;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; SnLe16 symbol; } expression; } record47;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record48;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record49;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record50;
    struct { u8 opcode; SnLe16 offset; } record51;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record52;
    struct { u8 opcode; SnLe16 section; } record53;
    struct { u8 opcode; SnLe16 codeSize; u8 code[138]; } record54;
    struct { u8 opcode; SnLe16 section; } record55;
} g_pakInterfaceInitialModeRecords __attribute__((aligned(1))) = {
    { 52, SN_LE16(0), 6 },
    { 52, SN_LE16(0), 0 },
    { 50, SN_LE16(20) },
    { 10, 92, SN_LE16(48), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(32668) } } },
    { 10, 96, SN_LE16(58), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(0) } } },
    { 10, 98, SN_LE16(62), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(0) } } },
    { 10, 96, SN_LE16(70), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(856) } } },
    { 10, 98, SN_LE16(74), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(856) } } },
    { 10, 92, SN_LE16(76), { 2, SN_LE16(376) } },
    { 52, SN_LE16(96), 2 },
    { 10, 96, SN_LE16(102), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(0) } } },
    { 10, 98, SN_LE16(106), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(0) } } },
    { 50, SN_LE16(108) },
    { 52, SN_LE16(132), 0 },
    { 6, SN_LE16(1) },
    { 2, SN_LE16(138), { 0x00, 0x00, 0x00, 0x61, 0x6E, 0x55, 0x73, 0x65, 0x72, 0x20, 0x3E, 0x3D, 0x30, 0x20, 0x26, 0x26, 0x20, 0x61, 0x6E, 0x55, 0x73, 0x65, 0x72, 0x20, 0x3C, 0x20, 0x50, 0x41, 0x4B, 0x49, 0x4E, 0x54, 0x45, 0x52, 0x46, 0x41, 0x43, 0x45, 0x5F, 0x4D, 0x41, 0x58, 0x5F, 0x55, 0x53, 0x45, 0x52, 0x53, 0x00, 0x00, 0x00, 0x70, 0x4F, 0x62, 0x6A, 0x65, 0x63, 0x74, 0x00, 0x70, 0x54, 0x65, 0x78, 0x74, 0x4F, 0x62, 0x6A, 0x65, 0x63, 0x74, 0x20, 0x21, 0x3D, 0x20, 0x4E, 0x55, 0x4C, 0x4C, 0x00, 0x70, 0x54, 0x65, 0x78, 0x74, 0x53, 0x74, 0x72, 0x69, 0x6E, 0x67, 0x00, 0x5B, 0x4D, 0x4F, 0x44, 0x45, 0x5D, 0x00, 0x00, 0x70, 0x4F, 0x62, 0x6A, 0x65, 0x63, 0x74, 0x2D, 0x3E, 0x70, 0x43, 0x68, 0x69, 0x6C, 0x64, 0x72, 0x65, 0x6E, 0x2D, 0x3E, 0x54, 0x79, 0x70, 0x65, 0x20, 0x3D, 0x3D, 0x20, 0x53, 0x4D, 0x5F, 0x4F, 0x54, 0x5F, 0x54, 0x45, 0x58, 0x54, 0x00 } },
    { 6, SN_LE16(2) }
};


struct {
    struct { u8 opcode; SnLe16 codeSize; } record0;
} k_LinktablesWritableUsTail __attribute__((aligned(1))) = {
    { 2, SN_LE16(452) }
};
typedef char k_LinktablesWritableWordsUsTailSizeCheck[(sizeof(k_LinktablesWritableUsTail) == 3) ? 1 : -1];
#endif

#if defined(VERSION_US)
struct {
    u32 reserved[3];
} k_resourcePagerReservedRecord = {
    { 0x6A0402B3, 0x010A5C6C, 0x0402AB01 }
};
#endif

#if defined(VERSION_DE) || defined(VERSION_US)
#ifdef VERSION_US
struct {
    u8 precedingRecordFragment[5];
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record1;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record2;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; SnLe16 symbol; } expression; } record3;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record4;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record5;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record6;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record7;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record8;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record9;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record10;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; SnLe16 symbol; } expression; } record11;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record12;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record13;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record14;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record15;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record16;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe32 constant; } left; struct { u8 opcode; SnLe16 symbol; } right; } expression; } record17;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe32 constant; } left; struct { u8 opcode; SnLe16 symbol; } right; } expression; } record18;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; SnLe16 symbol; } expression; } record19;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; SnLe16 symbol; } expression; } record20;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; SnLe16 symbol; } expression; } record21;
    struct { u8 opcode; SnLe16 offset; } record22;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record23;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record24;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record25;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record26;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; SnLe16 symbol; } expression; } record27;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record28;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record29;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record30;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record31;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record32;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record33;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record34;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; SnLe16 symbol; } expression; } record35;
    struct { u8 opcode; SnLe16 offset; } record36;
    struct { u8 opcode; SnLe16 offset; SnLe32 line; } record37;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record38;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record39;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record40;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record41;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record42;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; SnLe16 symbol; } expression; } record43;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record44;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record45;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record46;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record47;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record48;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; SnLe16 symbol; } expression; } record49;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record50;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; SnLe16 symbol; } expression; } record51;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record52;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record53;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record54;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record55;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record56;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; SnLe16 symbol; } expression; } record57;
    struct { u8 opcode; SnLe16 offset; } record58;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record59;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record60;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record61;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record62;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record63;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; SnLe16 symbol; } expression; } record64;
    struct { u8 opcode; SnLe16 offset; } record65;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record66;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record67;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record68;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record69;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; SnLe16 symbol; } expression; } record70;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record71;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record72;
    struct { u8 opcode; SnLe16 offset; } record73;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; SnLe16 symbol; } expression; } record74;
    struct { u8 opcode; SnLe16 offset; } record75;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record76;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record77;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record78;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record79;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; SnLe16 symbol; } expression; } record80;
    struct { u8 opcode; SnLe16 offset; } record81;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record82;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record83;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record84;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record85;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record86;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record87;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record88;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record89;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record90;
    struct { u8 opcode; SnLe16 offset; } record91;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record92;
    struct { u8 opcode; SnLe16 offset; } record93;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record94;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record95;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record96;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record97;
    struct { u8 opcode; SnLe16 offset; } record98;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record99;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record100;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record101;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record102;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record103;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; SnLe16 symbol; } expression; } record104;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record105;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record106;
    struct { u8 opcode; SnLe16 offset; } record107;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record108;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record109;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record110;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record111;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record112;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record113;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; SnLe16 symbol; } expression; } record114;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record115;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record116;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record117;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; SnLe16 symbol; } expression; } record118;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record119;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record120;
    struct { u8 opcode; SnLe16 offset; } record121;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record122;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record123;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record124;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record125;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record126;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record127;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; SnLe16 symbol; } expression; } record128;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record129;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record130;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record131;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; SnLe16 symbol; } expression; } record132;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record133;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record134;
    struct { u8 opcode; SnLe16 offset; } record135;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record136;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record137;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record138;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record139;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record140;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record141;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; SnLe16 symbol; } expression; } record142;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record143;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record144;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record145;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record146;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record147;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record148;
    struct { u8 opcode; SnLe16 offset; } record149;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record150;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record151;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record152;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record153;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record154;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record155;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; SnLe16 symbol; } expression; } record156;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record157;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record158;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record159;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record160;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record161;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record162;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record163;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record164;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record165;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record166;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record167;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record168;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record169;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record170;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record171;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record172;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record173;
    struct { u8 opcode; SnLe16 offset; } record174;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record175;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record176;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record177;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record178;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record179;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record180;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record181;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record182;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record183;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record184;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record185;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record186;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record187;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record188;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record189;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record190;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record191;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record192;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record193;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record194;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record195;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record196;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record197;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record198;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record199;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record200;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record201;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record202;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record203;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record204;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record205;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record206;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record207;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record208;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record209;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record210;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record211;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record212;
    struct { u8 opcode; SnLe16 offset; } record213;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record214;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record215;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record216;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record217;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; SnLe16 symbol; } expression; } record218;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record219;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record220;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record221;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record222;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record223;
    struct { u8 opcode; SnLe16 offset; SnLe32 line; } record224;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record225;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record226;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record227;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record228;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record229;
    u8 followingRecordFragment[6];
} k_VhandlerHandleresourcepagerequestEncodedWords __attribute__((aligned(4))) = {
    { 0x00, 0x04, 0x00, 0x00, 0x00 },
    { 10, 96, SN_LE16(1238), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(1884) } } },
    { 10, 98, SN_LE16(1242), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(1884) } } },
    { 10, 92, SN_LE16(1248), { 2, SN_LE16(439) } },
    { 52, SN_LE16(1256), 2 },
    { 10, 96, SN_LE16(1298), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(1302), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 96, SN_LE16(1394), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(1398), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 96, SN_LE16(1450), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(1900) } } },
    { 10, 98, SN_LE16(1454), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(1900) } } },
    { 10, 92, SN_LE16(1460), { 2, SN_LE16(439) } },
    { 52, SN_LE16(1468), 2 },
    { 10, 92, SN_LE16(1468), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(56424) } } },
    { 52, SN_LE16(1476), 4 },
    { 10, 96, SN_LE16(1518), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(1522), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 96, SN_LE16(1570), { 44, { 0, SN_LE32(159121) }, { 2, SN_LE16(388) } } },
    { 10, 98, SN_LE16(1574), { 44, { 0, SN_LE32(159121) }, { 2, SN_LE16(388) } } },
    { 10, 96, SN_LE16(1590), { 2, SN_LE16(435) } },
    { 10, 98, SN_LE16(1598), { 2, SN_LE16(435) } },
    { 10, 92, SN_LE16(1600), { 2, SN_LE16(427) } },
    { 50, SN_LE16(1608) },
    { 10, 96, SN_LE16(1650), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(1654), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 96, SN_LE16(1706), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(1884) } } },
    { 10, 98, SN_LE16(1710), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(1884) } } },
    { 10, 92, SN_LE16(1716), { 2, SN_LE16(439) } },
    { 52, SN_LE16(1724), 2 },
    { 10, 96, SN_LE16(1766), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(1770), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 96, SN_LE16(1862), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(1866), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 96, SN_LE16(1918), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(1900) } } },
    { 10, 98, SN_LE16(1922), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(1900) } } },
    { 10, 92, SN_LE16(1928), { 2, SN_LE16(439) } },
    { 50, SN_LE16(1936) },
    { 56, SN_LE16(1944), SN_LE32(4968) },
    { 10, 92, SN_LE16(1956), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(54584) } } },
    { 52, SN_LE16(1964), 45 },
    { 52, SN_LE16(1976), 2 },
    { 10, 96, SN_LE16(1978), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(1982), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 92, SN_LE16(2032), { 2, SN_LE16(381) } },
    { 52, SN_LE16(2044), 2 },
    { 10, 96, SN_LE16(2058), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(0) } } },
    { 10, 98, SN_LE16(2062), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(0) } } },
    { 10, 96, SN_LE16(2070), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(1776) } } },
    { 10, 98, SN_LE16(2074), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(1776) } } },
    { 10, 92, SN_LE16(2076), { 2, SN_LE16(376) } },
    { 52, SN_LE16(2096), 2 },
    { 10, 92, SN_LE16(2108), { 2, SN_LE16(440) } },
    { 52, SN_LE16(2124), 2 },
    { 10, 96, SN_LE16(2166), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(2170), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 96, SN_LE16(2186), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(1884) } } },
    { 10, 98, SN_LE16(2190), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(1884) } } },
    { 10, 92, SN_LE16(2196), { 2, SN_LE16(439) } },
    { 50, SN_LE16(2204) },
    { 10, 96, SN_LE16(2250), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(2254), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 52, SN_LE16(2268), 2 },
    { 10, 96, SN_LE16(2270), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(2274), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 92, SN_LE16(2324), { 2, SN_LE16(381) } },
    { 50, SN_LE16(2336) },
    { 10, 96, SN_LE16(2350), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(0) } } },
    { 10, 98, SN_LE16(2354), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(0) } } },
    { 10, 96, SN_LE16(2362), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(1776) } } },
    { 10, 98, SN_LE16(2366), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(1776) } } },
    { 10, 92, SN_LE16(2368), { 2, SN_LE16(376) } },
    { 52, SN_LE16(2388), 3 },
    { 10, 92, SN_LE16(2388), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(60016) } } },
    { 50, SN_LE16(2400) },
    { 10, 92, SN_LE16(2404), { 2, SN_LE16(441) } },
    { 50, SN_LE16(2416) },
    { 10, 96, SN_LE16(2458), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(2462), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 96, SN_LE16(2478), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(1884) } } },
    { 10, 98, SN_LE16(2482), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(1884) } } },
    { 10, 92, SN_LE16(2488), { 2, SN_LE16(439) } },
    { 50, SN_LE16(2496) },
    { 10, 96, SN_LE16(2542), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(2546), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 52, SN_LE16(2560), 2 },
    { 10, 92, SN_LE16(2560), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(57056) } } },
    { 52, SN_LE16(2568), 2 },
    { 52, SN_LE16(2576), 4 },
    { 52, SN_LE16(2592), 2 },
    { 10, 96, SN_LE16(2594), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(2598), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 50, SN_LE16(2648) },
    { 10, 92, SN_LE16(2652), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(32704) } } },
    { 50, SN_LE16(2660) },
    { 10, 92, SN_LE16(2660), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(57920) } } },
    { 52, SN_LE16(2668), 7 },
    { 10, 96, SN_LE16(2670), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(2674), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 50, SN_LE16(2724) },
    { 10, 96, SN_LE16(2726), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(2730), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 52, SN_LE16(2776), 3 },
    { 10, 96, SN_LE16(2778), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(2782), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 92, SN_LE16(2832), { 2, SN_LE16(381) } },
    { 10, 96, SN_LE16(2842), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(2846), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 50, SN_LE16(2892) },
    { 10, 96, SN_LE16(2894), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(2898), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 96, SN_LE16(2954), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(0) } } },
    { 10, 98, SN_LE16(2958), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(0) } } },
    { 10, 96, SN_LE16(2966), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(1908) } } },
    { 10, 98, SN_LE16(2970), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(1908) } } },
    { 10, 92, SN_LE16(2972), { 2, SN_LE16(376) } },
    { 52, SN_LE16(2992), 2 },
    { 10, 96, SN_LE16(2994), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(2998), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 92, SN_LE16(3048), { 2, SN_LE16(381) } },
    { 10, 96, SN_LE16(3058), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(3062), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 50, SN_LE16(3108) },
    { 10, 96, SN_LE16(3110), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(3114), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 96, SN_LE16(3170), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(0) } } },
    { 10, 98, SN_LE16(3174), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(0) } } },
    { 10, 96, SN_LE16(3182), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(2000) } } },
    { 10, 98, SN_LE16(3186), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(2000) } } },
    { 10, 92, SN_LE16(3188), { 2, SN_LE16(376) } },
    { 52, SN_LE16(3208), 2 },
    { 10, 96, SN_LE16(3210), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(3214), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 92, SN_LE16(3264), { 2, SN_LE16(381) } },
    { 10, 96, SN_LE16(3274), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(3278), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 50, SN_LE16(3324) },
    { 10, 96, SN_LE16(3326), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(3330), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 96, SN_LE16(3386), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(0) } } },
    { 10, 98, SN_LE16(3390), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(0) } } },
    { 10, 96, SN_LE16(3398), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(2092) } } },
    { 10, 98, SN_LE16(3402), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(2092) } } },
    { 10, 92, SN_LE16(3404), { 2, SN_LE16(376) } },
    { 52, SN_LE16(3424), 2 },
    { 10, 92, SN_LE16(3432), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(57944) } } },
    { 52, SN_LE16(3440), 2 },
    { 52, SN_LE16(3464), 0 },
    { 52, SN_LE16(3464), 3 },
    { 52, SN_LE16(3464), 0 },
    { 50, SN_LE16(3488) },
    { 52, SN_LE16(3488), 6 },
    { 10, 92, SN_LE16(3516), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(58044) } } },
    { 10, 96, SN_LE16(3526), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(0) } } },
    { 10, 98, SN_LE16(3530), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(0) } } },
    { 10, 96, SN_LE16(3538), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(940) } } },
    { 10, 98, SN_LE16(3542), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(940) } } },
    { 10, 92, SN_LE16(3544), { 2, SN_LE16(376) } },
    { 52, SN_LE16(3564), 3 },
    { 52, SN_LE16(3580), 2 },
    { 10, 96, SN_LE16(3582), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(3586), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 52, SN_LE16(3644), 2 },
    { 10, 96, SN_LE16(3646), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(3650), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 96, SN_LE16(3694), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(3698), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 52, SN_LE16(3752), 2 },
    { 10, 96, SN_LE16(3754), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(3758), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 96, SN_LE16(3810), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(3814), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 52, SN_LE16(3872), 2 },
    { 10, 96, SN_LE16(3874), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(3878), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 50, SN_LE16(3940) },
    { 10, 96, SN_LE16(3942), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(3946), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 96, SN_LE16(3990), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(3994), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 92, SN_LE16(4048), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(58592) } } },
    { 52, SN_LE16(4056), 2 },
    { 10, 96, SN_LE16(4058), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(4062), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 52, SN_LE16(4112), 3 },
    { 10, 92, SN_LE16(4112), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(59052) } } },
    { 52, SN_LE16(4120), 3 },
    { 10, 96, SN_LE16(4122), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(4126), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 52, SN_LE16(4180), 2 },
    { 10, 96, SN_LE16(4182), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(4186), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 96, SN_LE16(4230), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(4234), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 52, SN_LE16(4288), 2 },
    { 10, 96, SN_LE16(4290), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(4294), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 96, SN_LE16(4350), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(4354), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 96, SN_LE16(4398), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(4402), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 52, SN_LE16(4464), 3 },
    { 10, 96, SN_LE16(4466), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(4470), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 96, SN_LE16(4514), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(4518), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 52, SN_LE16(4572), 16 },
    { 10, 92, SN_LE16(4592), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(59452) } } },
    { 52, SN_LE16(4600), 3 },
    { 10, 96, SN_LE16(4602), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(4606), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 52, SN_LE16(4676), 3 },
    { 10, 96, SN_LE16(4678), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(4682), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 50, SN_LE16(4748) },
    { 10, 96, SN_LE16(4762), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(0) } } },
    { 10, 98, SN_LE16(4766), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(0) } } },
    { 10, 96, SN_LE16(4774), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(1776) } } },
    { 10, 98, SN_LE16(4778), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(1776) } } },
    { 10, 92, SN_LE16(4780), { 2, SN_LE16(376) } },
    { 52, SN_LE16(4800), 3 },
    { 10, 96, SN_LE16(4846), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(4850), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 96, SN_LE16(4858), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(4862), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 56, SN_LE16(4952), SN_LE32(5118) },
    { 10, 92, SN_LE16(4964), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(59056) } } },
    { 52, SN_LE16(4972), 15 },
    { 10, 96, SN_LE16(4974), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(4978), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 52, SN_LE16(5028), 2 },
    { 0x0A, 0x60, 0xA6, 0x13, 0x2C, 0x04 }
};
typedef char k_VhandlerHandleresourcepagerequestDataSizeCheck[(sizeof(k_VhandlerHandleresourcepagerequestEncodedWords) == 2300) ? 1 : -1];
#endif
#if defined(VERSION_US)
unsigned int g_VhandlerHandleresourcepagerequestEncodedWordSingle[1] = {
    0x03000004,
};
#endif
#ifdef VERSION_US
struct {
    u8 precedingRecordFragment[3];
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record1;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; SnLe16 symbol; } expression; } record2;
    struct { u8 opcode; SnLe16 offset; } record3;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record4;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record5;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record6;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record7;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record8;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record9;
    struct { u8 opcode; SnLe16 offset; } record10;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record11;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record12;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record13;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record14;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record15;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record16;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; SnLe16 symbol; } expression; } record17;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record18;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record19;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; SnLe16 symbol; } expression; } record20;
    struct { u8 opcode; SnLe16 offset; } record21;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record22;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; SnLe16 symbol; } expression; } record23;
    struct { u8 opcode; SnLe16 offset; } record24;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record25;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record26;
    struct { u8 opcode; SnLe16 offset; } record27;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; SnLe16 symbol; } expression; } record28;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record29;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record30;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record31;
    struct { u8 opcode; SnLe16 offset; } record32;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record33;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record34;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record35;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record36;
    struct { u8 opcode; SnLe16 offset; } record37;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record38;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record39;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record40;
    struct { u8 opcode; SnLe16 offset; } record41;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record42;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record43;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record44;
    struct { u8 opcode; SnLe16 offset; } record45;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record46;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record47;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record48;
    struct { u8 opcode; SnLe16 offset; } record49;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record50;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record51;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record52;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record53;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record54;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record55;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; SnLe16 symbol; } expression; } record56;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record57;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record58;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record59;
    struct { u8 opcode; SnLe16 offset; } record60;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record61;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record62;
    struct { u8 opcode; SnLe16 offset; } record63;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record64;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; SnLe16 symbol; } expression; } record65;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record66;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record67;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record68;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record69;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record70;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record71;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; SnLe16 symbol; } expression; } record72;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record73;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record74;
    struct { u8 opcode; SnLe16 offset; } record75;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record76;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record77;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record78;
    struct { u8 opcode; SnLe16 offset; } record79;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record80;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record81;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record82;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record83;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record84;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record85;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; SnLe16 symbol; } expression; } record86;
    struct { u8 opcode; SnLe16 offset; u8 lineDelta; } record87;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record88;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record89;
    struct { u8 opcode; SnLe16 offset; } record90;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record91;
    struct { u8 opcode; u8 patchKind; SnLe16 offset; struct { u8 opcode; struct { u8 opcode; SnLe16 section; } left; struct { u8 opcode; SnLe32 constant; } right; } expression; } record92;
} g_VhandlerHandleresourcepagerequestEncodedWords __attribute__((aligned(4))) = {
    { 0x00, 0x00, 0x00 },
    { 10, 98, SN_LE16(5034), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 92, SN_LE16(5084), { 2, SN_LE16(381) } },
    { 50, SN_LE16(5096) },
    { 10, 96, SN_LE16(5142), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(5146), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 52, SN_LE16(5196), 13 },
    { 52, SN_LE16(5220), 0 },
    { 52, SN_LE16(5220), 3 },
    { 52, SN_LE16(5220), 0 },
    { 50, SN_LE16(5244) },
    { 52, SN_LE16(5244), 4 },
    { 10, 92, SN_LE16(5272), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(59800) } } },
    { 10, 96, SN_LE16(5282), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(0) } } },
    { 10, 98, SN_LE16(5286), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(0) } } },
    { 10, 96, SN_LE16(5294), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(940) } } },
    { 10, 98, SN_LE16(5298), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(940) } } },
    { 10, 92, SN_LE16(5300), { 2, SN_LE16(376) } },
    { 52, SN_LE16(5320), 2 },
    { 52, SN_LE16(5328), 2 },
    { 10, 92, SN_LE16(5340), { 2, SN_LE16(440) } },
    { 50, SN_LE16(5352) },
    { 52, SN_LE16(5364), 2 },
    { 10, 92, SN_LE16(5376), { 2, SN_LE16(442) } },
    { 50, SN_LE16(5388) },
    { 52, SN_LE16(5400), 3 },
    { 10, 92, SN_LE16(5400), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(60016) } } },
    { 50, SN_LE16(5412) },
    { 10, 92, SN_LE16(5416), { 2, SN_LE16(441) } },
    { 52, SN_LE16(5428), 3 },
    { 10, 92, SN_LE16(5460), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(59964) } } },
    { 52, SN_LE16(5468), 2 },
    { 50, SN_LE16(5476) },
    { 10, 92, SN_LE16(5476), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(59976) } } },
    { 52, SN_LE16(5484), 2 },
    { 52, SN_LE16(5496), 5 },
    { 10, 92, SN_LE16(5504), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(59992) } } },
    { 50, SN_LE16(5512) },
    { 52, SN_LE16(5536), 0 },
    { 52, SN_LE16(5536), 3 },
    { 52, SN_LE16(5536), 0 },
    { 50, SN_LE16(5548) },
    { 52, SN_LE16(5548), 5 },
    { 52, SN_LE16(5556), 2 },
    { 10, 92, SN_LE16(5564), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(60052) } } },
    { 50, SN_LE16(5572) },
    { 52, SN_LE16(5592), 0 },
    { 52, SN_LE16(5592), 21 },
    { 52, SN_LE16(5592), 0 },
    { 50, SN_LE16(5612) },
    { 52, SN_LE16(5612), 4 },
    { 10, 92, SN_LE16(5640), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(60168) } } },
    { 10, 96, SN_LE16(5650), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(0) } } },
    { 10, 98, SN_LE16(5654), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(0) } } },
    { 10, 96, SN_LE16(5662), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(940) } } },
    { 10, 98, SN_LE16(5666), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(940) } } },
    { 10, 92, SN_LE16(5668), { 2, SN_LE16(376) } },
    { 52, SN_LE16(5688), 2 },
    { 10, 96, SN_LE16(5730), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(5734), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 50, SN_LE16(5748) },
    { 10, 96, SN_LE16(5750), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(5754), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 50, SN_LE16(5764) },
    { 52, SN_LE16(5772), 2 },
    { 10, 92, SN_LE16(5784), { 2, SN_LE16(421) } },
    { 52, SN_LE16(5792), 3 },
    { 10, 96, SN_LE16(5794), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(5798), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 96, SN_LE16(5802), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(5806), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 52, SN_LE16(5856), 3 },
    { 10, 92, SN_LE16(5868), { 2, SN_LE16(443) } },
    { 10, 96, SN_LE16(5878), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(5882), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 50, SN_LE16(5888) },
    { 52, SN_LE16(5912), 0 },
    { 52, SN_LE16(5912), 3 },
    { 52, SN_LE16(5912), 0 },
    { 50, SN_LE16(5932) },
    { 52, SN_LE16(5932), 4 },
    { 10, 92, SN_LE16(5960), { 44, { 4, SN_LE16(2) }, { 0, SN_LE32(60488) } } },
    { 10, 96, SN_LE16(5970), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(0) } } },
    { 10, 98, SN_LE16(5974), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(0) } } },
    { 10, 96, SN_LE16(5982), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(940) } } },
    { 10, 98, SN_LE16(5986), { 44, { 4, SN_LE16(1) }, { 0, SN_LE32(940) } } },
    { 10, 92, SN_LE16(5988), { 2, SN_LE16(376) } },
    { 52, SN_LE16(6008), 2 },
    { 10, 96, SN_LE16(6010), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(6014), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 50, SN_LE16(6024) },
    { 10, 96, SN_LE16(6066), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } },
    { 10, 98, SN_LE16(6070), { 44, { 4, SN_LE16(3) }, { 0, SN_LE32(4) } } }
};
typedef char g_VhandlerHandleresourcepagerequestDataSizeCheck[(sizeof(g_VhandlerHandleresourcepagerequestEncodedWords) == 716) ? 1 : -1];
#endif
#if defined(VERSION_US)
unsigned int g_VhandlerHandleresourcepagerequestEncodedWordsTriple[3] = {
    0x32C41734, 0xCC17020A, 0x5CD81702,
};
#endif
#endif

#if defined(VERSION_US_REV1)
EventHandlerRecord g_achieveResultsScreenCreateHandler[1] = {
    { 3590, 18, g_Achieve_CreateResultsScreenAddress },
};
EventHandlerRecord g_achieveResultsScreenEventHandlers[5] = {
    { 3587, 18, g_CPlayerPreview_CloseSelectionMessageScreenAddress },
    { 2, 18, g_Achieve_AcknowledgeResultsEventAddress },
    { 1, 18, g_Achieve_HandleResultsMenuChoiceAddress },
    { 3594, 18, g_Achieve_UpdateResultsScreenAddress },
    { 0, 0, 0 },
};
extern char g_frontendScreenRetainedTextFragment[12];
#endif

#if defined(VERSION_US_REV1)
EventHandlerRecord g_FrontendUpdateslidergeometryData[1] = {
    { 3590, 6, (void *)&Menu_CreateSoundOptionsScreen },
};
EventHandlerRecord g_frontendSliderEventHandlerWords[4] = {
    { 3587, 6, (void *)&Menu_FreeSoundOptionsScreen },
    { 2, 6, (void *)&Menu_CancelSoundOptionsScreen },
    { 1, 6, (void *)&Menu_ConfirmSoundOptionsScreen },
    { 0, 0, 0 },
};
EventHandlerRecord g_frontendSliderTransitionHandlerWords[7] = {
    { 3591, 13, (void *)&Menu_SoundSliderReturnZero },
    { 3592, 13, (void *)&Menu_ApplySoundSliders },
    { 3590, 13, (void *)&Menu_CreateSoundSliders },
    { 3587, 13, (void *)&Menu_FreeSoundSliders },
    { 2, 13, (void *)&Menu_CancelSoundSliderPopup },
    { 1, 13, (void *)&Menu_ConfirmSoundSliderPopup },
    { 0, 0, 0 },
};
#endif

#if defined(VERSION_US_REV1)
extern unsigned int g_FrontendDispatchnodepairmenueventData[2];
EventHandlerRecord g_menuNodePairEventHandlers[4] = {
    { 3590, 33, (void *)0x00439F10 },
    { 2, 33, g_frontend_CancelNodePairMenuEntry },
    { 1, 33, g_frontend_UpdateTimedTransitionEntry },
    { 0, 0, 0 },
};
#endif

#if defined(VERSION_US_REV1)

#endif

#if defined(VERSION_US_REV1)
extern char g_firstPlayerName[];
/* Initialize the pulse screen, its shared menu state, and player profiles. */
s32 Frontend_CreateProfileResetScreen(MenuWidget *tree) {
    s32 i;
    Shared_Game *settings;
    Shared_PlayerSettingsRecord *record;
    Shared_MenuObject *object;

    g_profileResetScreen = Cache_AllocateMemory(sizeof(*g_profileResetScreen));
    object = &g_playerViewRenderContext.object;
    Pools_ResetActorPools(object, 0);
    Player_InitializePlayerPool(&g_playerViewRenderContext, 0, 0);
    Scene_LoadLevelResources(&g_world, 0, 0);
    if (Cache_GetResourceActivityState() == 0) {
        Cache_SetResourceActivityState(1);
    }
    Frontend_RequestScreenMode(0);
    i = 7;
    Tsmos_DeactivateControllerState();
    record = &object->playerSettings[7];
    do {
        record->enabled = 0;
        i--;
        record--;
    } while (i >= 0);
    g_profileResetScreen->widget = Node_FindWidgetByResourceId(tree, 919);
    g_profileResetScreen->phase = 0;
    settings = &g_gameSettings;
    settings->laps = 10;
    settings->players = 10;
    for (i = 0; i < 4; i++) {
        Player_InitializeProfile(&g_localPlayerProfiles[i]);
    }
    Tsmos_SetIdleTimer(0.0f);
    return 0;
}

#endif



/* Marks a player's record as ready for the next round: clears its pending counters, and on mode 1 advances its tier, gives the newly reached tier its default entry and flags the acquired handle for the notice sent to 0xE74. */

s32 PAKInterface_MoveNameCursorForward(s32 unusedA, s32 unusedB, s32 index, s32 mode)
{
  s32 slot = index & 0xFFFF;
  s32 offset = slot * 2920;
  void *handle;
  if ((g_pakProfileScreenState->players[slot].state) == 12)
  {
    handle = SmpOverlay_GetSlotValue((s32)g_pakProfileScreenState->list, slot);
    g_pakProfileScreenState->players[slot].nameTimer = 0;
    g_pakProfileScreenState->players[slot].namePhase = 2;
    if (mode == 1)
    {
      s32 tier = (g_pakProfileScreenState->players[slot].nameCursor) + 1;
      if (tier < 7)
      {
        g_pakProfileScreenState->players[slot].nameCursor = tier;
      }
      {
        if (g_pakProfileScreenState->players[slot].name[g_pakProfileScreenState->players[slot].nameCursor].available == 0) {
          g_pakProfileScreenState->players[slot].name[g_pakProfileScreenState->players[slot].nameCursor].available = 65;
        }
      }
      ((struct WidgetFlagsView *)(handle))->alpha = 0xFF;
      SoundElement_PlayFlatSound(3700);
    }
  }
 do { return 0; } while (0);
}

/* Initializes four player-menu slots and selects the first available child node. */

#if defined(VERSION_DE)
enum { PAK_SLOT_RESOURCE_688 = 716, PAK_SLOT_RESOURCE_689 = 713, PAK_SLOT_RESOURCE_690 = 714, PAK_SLOT_RESOURCE_691 = 715, PAK_SLOT_RESOURCE_692 = 712, PAK_SLOT_RESOURCE_694 = 718 };
#elif defined(VERSION_EU)
enum { PAK_SLOT_RESOURCE_688 = 688, PAK_SLOT_RESOURCE_689 = 689, PAK_SLOT_RESOURCE_690 = 690, PAK_SLOT_RESOURCE_691 = 691, PAK_SLOT_RESOURCE_692 = 692, PAK_SLOT_RESOURCE_694 = 694 };

#elif defined(VERSION_EU_X)
enum { PAK_SLOT_RESOURCE_688 = 764, PAK_SLOT_RESOURCE_689 = 761, PAK_SLOT_RESOURCE_690 = 762, PAK_SLOT_RESOURCE_691 = 760, PAK_SLOT_RESOURCE_692 = 763, PAK_SLOT_RESOURCE_694 = 766 };

#else
enum { PAK_SLOT_RESOURCE_688 = 688, PAK_SLOT_RESOURCE_689 = 689, PAK_SLOT_RESOURCE_690 = 690, PAK_SLOT_RESOURCE_691 = 691, PAK_SLOT_RESOURCE_692 = 692, PAK_SLOT_RESOURCE_694 = 694 };

#endif
void PAKInterface_BuildProfileSlotList(s32 player) {
 s32 i;
 MenuWidget *label,*value;
 g_pakProfileScreenState->players[player].chosen=0;
 /* the hub EC30 returns the item view; nodes[] hold this unit's MenuWidget storage */
 g_pakProfileScreenState->players[player].nodes[0]=(MenuWidget *)Node_FindWidgetByResourceId(g_pakProfileScreenState->players[player].menuWidget,PAK_SLOT_RESOURCE_694);
 g_pakProfileScreenState->players[player].nodes[1]=(MenuWidget *)Node_FindWidgetByResourceId(g_pakProfileScreenState->players[player].menuWidget,PAK_SLOT_RESOURCE_691);
 g_pakProfileScreenState->players[player].nodes[2]=(MenuWidget *)Node_FindWidgetByResourceId(g_pakProfileScreenState->players[player].menuWidget,PAK_SLOT_RESOURCE_688);
 g_pakProfileScreenState->players[player].nodes[3]=(MenuWidget *)Node_FindWidgetByResourceId(g_pakProfileScreenState->players[player].menuWidget,PAK_SLOT_RESOURCE_692);
 for(i=0;i<4;i++) {
  g_pakProfileScreenState->players[player].used[i]=2;
  g_pakProfileScreenState->players[player].nodes[i]->alpha=255;
  label=(MenuWidget *)Node_FindWidgetByResourceId(g_pakProfileScreenState->players[player].nodes[i],PAK_SLOT_RESOURCE_689);
  Widget_SetWidgetFlag100(g_pakProfileScreenState->players[player].nodes[i],0);
  value=(MenuWidget *)Node_FindWidgetByResourceId(g_pakProfileScreenState->players[player].nodes[i],PAK_SLOT_RESOURCE_690);
  if(g_pakProfileScreenState->players[player].records[i].player!=-1) {
   value->text=g_pakProfileScreenState->players[player].records[i].name;
   g_pakProfileScreenState->players[player].used[i]=1;
   if(g_pakProfileScreenState->phase==1) {
    Widget_SetWidgetFlag08(Node_FindWidgetByResourceId(g_pakProfileScreenState->players[player].nodes[i],PAK_SLOT_RESOURCE_689),0);
    if(Frontend_FindProfileOwner(g_pakProfileScreenState->players[player].profile,g_pakProfileScreenState->players[player].records[i].owner)!=-1) {
     g_pakProfileScreenState->players[player].used[i]=0;
     Widget_SetWidgetFlag100(g_pakProfileScreenState->players[player].nodes[i],1);
     Widget_SetWidgetFlag08(Node_FindWidgetByResourceId(g_pakProfileScreenState->players[player].nodes[i],PAK_SLOT_RESOURCE_689),1);
    }
   }
#if defined(VERSION_EU)
  } else {value->text=((g_slotEmptyNameByLanguageEu)[g_languageIndex]);Widget_SetWidgetFlag08((SlotSelectionWidget *)label,0);}
#elif defined(VERSION_EU_X)
  } else {value->text=((g_slotEmptyNameByLanguageEuX)[g_languageIndex]);Widget_SetWidgetFlag08((SlotSelectionWidget *)label,0);}
#else
  } else {value->text=(g_slotRankNamePointers_Empty[0]);Widget_SetWidgetFlag08((SlotSelectionWidget *)label,0);}
#endif
 }
 label=SmpOverlay_GetSlotValue(g_pakProfileScreenState->root,player);
 while(Widget_ListHasFlag100(label))label=label->next;
 SmpOverlay_ShowSlotNode(g_pakProfileScreenState->root,player,label);
}

/* Relabels the four slot rows of the block g_pakProfileScreenState points to: for each row item (0x28B, 0x28D,
   0x28F, then 0x291) of the block's window it calls Widget_SetWidgetFlag100_MenuRefreshextraoptionlocks(0) and points the text of the item's label
   at player p's chosen slot (the chosen index of p's panel, slots of 400 bytes) when p is not -1 and SmpOverlay_GetSlotValue
   reports this row as p's focus in the list, otherwise at the row's record in g_localPlayerProfiles
   when its owner is not negative, or at nothing. */
/* The first row item's id: eu-x numbers its items 9 higher and de 1 higher, as each cartridge's
   own bytes show; us, us-rev1 and eu share 0x28B. */
void PAKInterface_RelabelSlotRows(s32 player) {
    struct ItemFrontendRelabelSlotRows *item;
    struct WidgetLabelTextView *label;
    s32 id;
    s32 i;
    for (i = 0; i < 4; i++) {
        switch (i) {
        case 0:
#if defined(VERSION_DE)
            id = 652;
#elif defined(VERSION_EU) || defined(VERSION_US) || defined(VERSION_US_REV1)
            id = 651;
#elif defined(VERSION_EU_X)
            id = 660;
#endif
            break;
        case 1:
#if defined(VERSION_DE)
            id = 652 + 2;
#elif defined(VERSION_EU) || defined(VERSION_US) || defined(VERSION_US_REV1)
            id = 651 + 2;
#elif defined(VERSION_EU_X)
            id = 660 + 2;
#endif
            break;
        case 2:
#if defined(VERSION_DE)
            id = 652 + 4;
#elif defined(VERSION_EU) || defined(VERSION_US) || defined(VERSION_US_REV1)
            id = 651 + 4;
#elif defined(VERSION_EU_X)
            id = 660 + 4;
#endif
            break;
        default:
#if defined(VERSION_DE)
            id = 652 + 6;
#elif defined(VERSION_EU) || defined(VERSION_US) || defined(VERSION_US_REV1)
            id = 651 + 6;
#elif defined(VERSION_EU_X)
            id = 660 + 6;
#endif
            break;
        }
        item = Node_FindWidgetByResourceId(g_pakProfileScreenState->window, id);
        Widget_SetWidgetFlag100(item, 0);
        label = item->label;
        if (player != -1 && item == SmpOverlay_GetSlotValue(g_pakProfileScreenState->list, player)) {
            label->text = g_pakProfileScreenState->players[player].slots[g_pakProfileScreenState->players[player].chosen];
        } else if (g_profileSlotIndices[i][0] >= 0) {
            label->text = &g_localPlayerProfiles[i];
        } else {
            label->text = 0;
        }
    }
}

/* Updates the four player control rows, their visibility, and the selected player label. */
void PAKInterface_UpdatePlayerControlRows(s32 player) {
    struct Shared_Item *item;
    struct WidgetLabelTextView *label;
    u16 id;
    s32 i;
    i = 0;
    do {
        if (i == 1) goto row_one;
        if (i < 2) {
            if (i == 0) goto row_zero;
#if defined(VERSION_DE)
            id = 662 + 6;
#elif defined(VERSION_EU) || defined(VERSION_US) || defined(VERSION_US_REV1)
            id = 665 + 6;
#elif defined(VERSION_EU_X)
            id = 671 + 6;
#endif
            goto row_done;
        }
        if (i == 2) goto row_two;
#if defined(VERSION_DE)
        id = 662 + 6;
#elif defined(VERSION_EU) || defined(VERSION_US) || defined(VERSION_US_REV1)
        id = 665 + 6;
#elif defined(VERSION_EU_X)
        id = 671 + 6;
#endif
        goto row_done;
    row_zero:
#if defined(VERSION_DE)
        id = 662;
#elif defined(VERSION_EU) || defined(VERSION_US) || defined(VERSION_US_REV1)
        id = 665;
#elif defined(VERSION_EU_X)
        id = 671;
#endif
        goto row_done;
    row_one:
#if defined(VERSION_DE)
        id = 662 + 2;
#elif defined(VERSION_EU) || defined(VERSION_US) || defined(VERSION_US_REV1)
        id = 665 + 2;
#elif defined(VERSION_EU_X)
        id = 671 + 2;
#endif
        goto row_done;
    row_two:
#if defined(VERSION_DE)
        id = 662 + 4;
#elif defined(VERSION_EU) || defined(VERSION_US) || defined(VERSION_US_REV1)
        id = 665 + 4;
#elif defined(VERSION_EU_X)
        id = 671 + 4;
#endif
    row_done:
        item = Node_FindWidgetByResourceId(g_pakProfileScreenState->window, id);
        if (Control_IsControllerConnected(i) == 1) {
            Widget_SetWidgetFlag100(item, 0);
        } else {
            Widget_SetWidgetFlag100(item, 1);
        }
        label = item->label;
        if (player != -1 && item == SmpOverlay_GetSlotValue(g_pakProfileScreenState->list, player)) {
            label->text = g_pakProfileScreenState->players[player].slots[g_pakProfileScreenState->players[player].chosen];
        } else {
            label->text = 0;
        }
        i += 1;
    } while (i < 4);
}

#if defined(VERSION_DE)
enum { PAK_LIST_FIELD = 748 };
#elif defined(VERSION_EU_X)
enum { PAK_LIST_FIELD = 752 };
#else
enum { PAK_LIST_FIELD = 726 };
#endif

/* Moves the note list cursor of a player: direction 1 steps the cursor forward while it is below 15 and scrolls the list so
   the cursor stays within the three visible rows (the scroll position is at most 13); any other direction steps the
   cursor and the scroll position back while they are positive. Then sets the three row labels to alpha 0xFF with the note
   names starting at the scroll position, and points item PAK_LIST_FIELD of the player's window at the code of the note
   under the cursor. */

void PAKInterface_ScrollNoteList(s32 player, s32 direction) {
    s32 i;
    s32 cursor;

    if (direction == 1) {
        if (g_pakProfileScreenState->players[player].slot < 15) {
            g_pakProfileScreenState->players[player].slot++;
            if (g_pakProfileScreenState->players[player].slot >= g_pakProfileScreenState->players[player].scroll + 3) {
                if (g_pakProfileScreenState->players[player].scroll + 3 < 15) {
                    g_pakProfileScreenState->players[player].scroll++;
                } else {
                    g_pakProfileScreenState->players[player].scroll = 13;
                }
            }
        }
    } else if (g_pakProfileScreenState->players[player].slot > 0) {
        g_pakProfileScreenState->players[player].slot--;
        if (g_pakProfileScreenState->players[player].scroll > 0 &&
            g_pakProfileScreenState->players[player].slot - g_pakProfileScreenState->players[player].scroll < 0) {
            g_pakProfileScreenState->players[player].scroll--;
        }
    }
    for (i = 0; i < 3; i++) {
        g_pakProfileScreenState->players[player].labels[i]->alpha = 0xFF;
        g_pakProfileScreenState->players[player].labels[i]->text =
            g_pakProfileScreenState->players[player].displayNames[g_pakProfileScreenState->players[player].scroll + i].text;
    }
    cursor = g_pakProfileScreenState->players[player].slot;
    Node_FindWidgetByResourceId(g_pakProfileScreenState->players[player].menuWidget, PAK_LIST_FIELD)->text =
        g_pakProfileScreenState->players[player].displayNames[cursor].code;
}

#include "Common/pak_save_text.h"
#include "Menu/Pak/pak_note_search.h"
#include "Note/note_readnoteinfo.h"
#include "Note/pak_allocaterenderbuffers.h"
#include "Menu/note_readnotedata.h"
#include "Menu/note_readnoteinfo.h"
#include "Menu/pak_allocaterenderbuffers.h"
#include "Ui/pakinterface_refreshplayerpanel.h"
#include "Ui/X_files/x_plus.h"

/* The save view of the menu block: the four staged player records, then the profile and
 * checksum stored behind them, written to the pak as one note. */
static __inline__ PakMenuController *pakRecordSave(void) {
    return g_pakProfileScreenState;
}
/* The note's game code is read through the settings view in the PAL releases. */
#if defined(VERSION_EU) || defined(VERSION_EU_X)
#define RECORDS_NOTE_CODE (g_pakLegacySnapshotGameNames[rw_pak_settings()->language])
#else
#define RECORDS_NOTE_CODE RW_PAK_GAME_CODE
#endif
/* Replace or create the selected port's four-profile Controller Pak note: delete the old note if
 * there is one, else check that a free note and enough pages exist; then stage the port's records,
 * profile and CRC and save them. On failure the port's panel goes back to state 2. */
s32 PAKInterface_SavePlayerRecords(s32 channel)
{
    char extension[8];
    char name[16];
    struct { s32 note, fits, freePages, freeNotes; } space;
    s32 status, required;
    Profile *staged, *data;
    s32 i;
    u32 checksum;
    s32 success = 0;
    if (Note_FindNoteByName(rw_pak_save_name(), channel, &space.note) == 1) {
        success = Note_DeleteNote(channel, space.note) == 0;
    } else {
        space.fits = 0;
        status = Note_GetFreePages(channel, &space.freePages);
        if (status == 0) {
            status = Note_CountFreeNotes(channel, &space.freeNotes);
            if (status == 0) {
                required = Note_BytesToPakPages(PAKInterface_GetRecordsNoteSize());
                if (space.freeNotes == 0 || space.freePages < required) space.fits = 0;
                else space.fits = 1;
            }
        }
        /* Dead store kept from the original: flow deletes it, but it stops jump threading of
         * the two status tests above into the one below (ROM keeps both branches). */
        required = 0;
        if (status == 0 && space.fits == 1) success = 1;
    }
    if (success == 1) {
        success = 0;
        if (Note_FindFreeNoteExtension(channel, extension) == 0) {
            staged = pakRecordSave()->packet.saved;
            XPlus_CopyBytes(staged, pakRecordSave()->players[channel].records, 1600);
            pakRecordSave()->packet.savedProfile = pakRecordSave()->players[channel].profile;
            checksum = Note_Crc32(staged, 1600, 7);
            pakRecordSave()->packet.checksum = checksum;
            data = pakRecordSave()->packet.saved;
            for (i = 0; i < 16; i++) name[i] = 0;
            XPlus_CopyString(name, RW_PAK_RECORD_TITLE);
            if (Note_SaveNote(channel, 1608, data, name, extension, RECORDS_NOTE_CODE) == 0) success = 1;
        }
    }
    if (!success) {
        pakRecordSave()->players[channel].back = 2;
        pakRecordSave()->players[channel].state = 2;
        PAKInterface_RefreshPlayerPanel(channel);
    }
    return success;
}

/* Receives player p's save packet through Note_ReadNoteData into the note buffer of the
   records g_pakProfileScreenState points to and, when Note_Crc32 checksums the save area to the
   checksum stored after it, copies the save area into the player's panel records and the trailing word into the panel's
   profile word, returning 1; otherwise it reports the failure through
   Note_DeleteNote, marks both the panel's state and back state as 2 and returns 0. */

s32 PAKInterface_ReadRecordsNote(s32 player, s32 channel) {
    PakSavePacket *packet;
    s32 received;

    received = 0;
    packet = &g_pakProfileScreenState->packet;
    if (Note_ReadNoteData(player, channel, packet, 1608) == 0) {
        if (Note_Crc32(packet, 1600, 7) == packet->checksum) {
            XPlus_CopyBytes(g_pakProfileScreenState->players[player].slots, &g_pakProfileScreenState->packet, 1600);
            received = 1;
            g_pakProfileScreenState->players[player].profile = g_pakProfileScreenState->packet.savedProfile;
        } else {
            Note_DeleteNote(player, channel);
        }
    } else {
        Note_DeleteNote(player, channel);
    }
    if (received == 0) {
        g_pakProfileScreenState->players[player].back = 2;
        g_pakProfileScreenState->players[player].state = 2;
    }
    return received;
}

/* Returns the first of the four players in g_pakProfileScreenState whose player state is 14, provided every player
   is idle (0), finished (17) or in state 14; otherwise, or when none is in state 14, returns -1. */

int PAKInterface_FindReadyTransferPlayer(void) {
    int i;
    int state;

    for (i = 0; i < 4; i++) {
        state = g_pakProfileScreenState->players[i].state;
        if (state != 0 && state != 17 && state != 14) {
            return -1;
        }
    }
    for (i = 0; i < 4; i++) {
        if (g_pakProfileScreenState->players[i].state == 14) {
            return i;
        }
    }
    return -1;
}

/* Reorders the four 400-byte player records g_localPlayerProfiles by the players' choices: copies all four to
   the buffer at 0x2E28 of the block g_pakProfileScreenState points to and resets each through Player_InitializeProfile,
   copies back the record each player chose (index at 0xB28 of its 2920-byte record at 0x58) into
   that player's place, and then places every unchosen buffered record whose owner byte 0xD is not
   negative into the first place whose owner byte is still negative, all through XPlus_CopyBytes. */

void PAKInterface_ReassignLocalProfiles(void) {
    s32 used[4];
    s32 size;
    s32 chosen;
    s32 i;
    s32 j;

    size = 400;
    XPlus_CopyBytes(g_pakProfileScreenState->packet.saved, g_localPlayerProfiles, 1600);
    for (i = 0; i < 4; i++) {
        Player_InitializeProfile(&g_localPlayerProfiles[i]);
        used[i] = 0;
    }
    for (i = 0; i < 4; i++) {
        chosen = g_pakProfileScreenState->players[i].port;
        if (chosen >= 0) {
            XPlus_CopyBytes(&g_localPlayerProfiles[i], &g_pakProfileScreenState->packet.saved[chosen], size);
            used[chosen] = 1;
        }
    }
    for (i = 0; i < 4; i++) {
        if (used[i] != 0 || g_pakProfileScreenState->packet.saved[i].player < 0) {
            continue;
        }
        for (j = 0; j < 4; j++) {
            if (g_localPlayerProfiles[j].owner < 0) {
                XPlus_CopyBytes(&g_localPlayerProfiles[j], &g_pakProfileScreenState->packet.saved[i], size);
                break;
            }
        }
    }
}

/* Places player p's chosen record into a free place: when the flag word for the chosen slot (chosen index of the player's panel, flags per slot) is 1, it takes the first of
   the four 12-byte places at 0x2DF8 of the block g_pakProfileScreenState points to whose id is -1, records it in
   the entry PAKInterface_FindEmptyPlayerLink returns (id 0, value the place, word 8 set to 1), copies the chosen
   400-byte slot from 0x18 of the player's record into that place of g_localPlayerProfiles through
   XPlus_CopyBytes, marks p as its owner at 0xD, clears the player's word at 0x4 and relabels through
   PAKInterface_RelabelSlotRows(-1), returning 1; otherwise it returns 0. */

s32 PAKInterface_JoinChosenProfile(s32 player) {
    struct RecordPAKInterfaceReassignLocalProfiles *record;
    s32 chosen;
    s32 place;
    s32 found;
    s32 entry;
    s32 result;
    s32 i;

    chosen = g_pakProfileScreenState->players[player].chosen;
    result = 0;
    if (g_pakProfileScreenState->players[player].used[chosen] == 1) {
        found = -1;
        for (i = 0; i < 4 && found == -1; i++) {
            if (g_pakProfileScreenState->links[i].player == -1) {
                found = i;
            }
        }
        place = found;
        if (place >= 0) {
            entry = PAKInterface_FindEmptyPlayerLink();
            if (entry >= 0) {
                g_pakProfileScreenState->links[entry].player = 0;
                g_pakProfileScreenState->links[entry].entry = place;
                g_pakProfileScreenState->links[entry].state = 1;
            }
            record = &g_localPlayerProfiles[found];
            XPlus_CopyBytes(record, g_pakProfileScreenState->players[player].slots[chosen], 400);
            record->owner = player;
            g_pakProfileScreenState->players[player].sub = 0;
            place = -1;
            PAKInterface_RelabelSlotRows(place);
            result = 1;
        }
    }
    return result;
}

/* Copies the profiles a player owns into the player's pak slots: for each of the four local player profiles that is not
   disabled and is owned by the player, when the matching match setup status entry is active and not a bot, copies the
   whole 400-byte profile through XPlus_CopyBytes into the player's pak slot that the profile's slot index names. */

void PAKInterface_CopyActiveProfilesToPakSlots(s32 player) {
    struct MatchSetupGlobals *globals;
    s32 i;
    s32 size;

    size = 400;
    globals = (MatchSetupGlobals *)&g_gameSettings;
    for (i = 0; i < 4; i++) {
        if (g_profileSlotEnabledFlags[i * 400] == 0 && g_profileSlotIndices[i][0] == player &&
            globals->status[i].active == 1 && globals->status[i].m_IsBot == 0) {
            XPlus_CopyBytes(g_pakProfileScreenState->players[player].slots[g_profileSlotResetFlags[i * 400]],
                          &g_localPlayerProfiles[i], size);
        }
    }
}

/* Labels player p's roster rows: for each of the four 400-byte records of g_localPlayerProfiles whose
   hidden flag is clear and whose owner is p, when the matching status record of g_gameSettings is marked in use
   and not locked, points the text of the next row item (0x2BA, 0x2E5, 0x2E6, then 0x2E7) of the menu window of
   p's panel in g_pakProfileScreenState at that record. Adapted from PAKInterface_CopyActiveProfilesToPakSlots with the copy
   replaced by the row label. */
void PAKInterface_LabelActiveProfileRows(s32 player) {
    struct MatchSetupGlobals *globals;
    s32 row;
    s32 id;
    s32 i;
    row = 0;
    globals = (MatchSetupGlobals *)&g_gameSettings;
    for (i = 0; i < 4; i++) {
        switch (row) {
        case 0:
#if defined(VERSION_DE)
            id = 682;
#elif defined(VERSION_EU) || defined(VERSION_US) || defined(VERSION_US_REV1)
            id = 698;
#elif defined(VERSION_EU_X)
            id = 706;
#endif
            break;
        case 1:
#if defined(VERSION_DE)
            id = 683;
#elif defined(VERSION_EU) || defined(VERSION_US) || defined(VERSION_US_REV1)
            id = 741;
#elif defined(VERSION_EU_X)
            id = 710;
#endif
            break;
        case 2:
#if defined(VERSION_DE)
            id = 684;
#elif defined(VERSION_EU) || defined(VERSION_US) || defined(VERSION_US_REV1)
            id = 742;
#elif defined(VERSION_EU_X)
            id = 711;
#endif
            break;
        default:
#if defined(VERSION_DE)
            id = 684 + 1;
#elif defined(VERSION_EU) || defined(VERSION_US) || defined(VERSION_US_REV1)
            id = 742 + 1;
#elif defined(VERSION_EU_X)
            id = 711 + 1;
#endif
            break;
        }
        if (g_profileSlotEnabledFlags[i * 400] == 0 && g_profileSlotIndices[i][0] == player &&
            globals->status[i].active == 1 && globals->status[i].m_IsBot == 0) {
            Node_FindWidgetByResourceId(g_pakProfileScreenState->players[player].menuWidget, id)->text = &g_localPlayerProfiles[i];
            row++;
        }
    }
}

/* Marks the initiating player's panel as transferring (state 17) and clears its host, then sets the linked player's panel
   to state 2 with its next state 13 and refreshes both the linked player's panel and the control rows. */
void PAKInterface_BeginLinkedProfileTransfer(s32 player) {
    s32 linkedPlayer = g_pakProfileScreenState->links[0].player;

    SmpOverlay_SetSlotValue(g_pakProfileScreenState->root, linkedPlayer, 0);
    g_pakProfileScreenState->players[player].state = 17;
    g_pakProfileScreenState->players[player].host = 0;
    g_pakProfileScreenState->players[linkedPlayer].back = 2;
    g_pakProfileScreenState->players[linkedPlayer].state = 2;
    g_pakProfileScreenState->players[linkedPlayer].next = 13;
    g_pakProfileScreenState->players[linkedPlayer].sub = 3;
    PAKInterface_RefreshPlayerPanel(linkedPlayer);
    PAKInterface_UpdatePlayerControlRows(-1);
}

/* Advances the selected name character, wrapping past Z to a space. */
void PAKInterface_IncrementNameCharacter(s32 player) {
    u8 value;

    g_pakProfileScreenState->selected[player] = 0;
    SmpOverlay_GetSlotValue(g_pakProfileScreenState->root, player);
    if (g_pakProfileScreenState->players[player].name[g_pakProfileScreenState->players[player].nameCursor].available == 0) {
        g_pakProfileScreenState->players[player].name[g_pakProfileScreenState->players[player].nameCursor].available = 65;
    }
    value = g_pakProfileScreenState->players[player].name[g_pakProfileScreenState->players[player].nameCursor].available;
    value++;
    if (value >= 91) {
        value = 32;
    }
    g_pakProfileScreenState->players[player].name[g_pakProfileScreenState->players[player].nameCursor].available = value;
}

/* Steps the selected name character of an entry back by one, wrapping below the printable range to 'Z'. */
void PAKInterface_DecrementNameCharacter(s32 player) {
    u8 value;

    g_pakProfileScreenState->selected[player] = 0;
    SmpOverlay_GetSlotValue(g_pakProfileScreenState->root, player);
    if (g_pakProfileScreenState->players[player].name[g_pakProfileScreenState->players[player].nameCursor].available == 0) {
        g_pakProfileScreenState->players[player].name[g_pakProfileScreenState->players[player].nameCursor].available = 65;
    }
    value = g_pakProfileScreenState->players[player].name[g_pakProfileScreenState->players[player].nameCursor].available;
    value--;
    if (value < 32) {
        value = 90;
    }
    g_pakProfileScreenState->players[player].name[g_pakProfileScreenState->players[player].nameCursor].available = value;
}

/* Stores its argument in g_pakProfileRequestedPhase. */


void PAKInterface_SetScreenPhase(s32 value) {
    g_pakProfileRequestedPhase = value;
}

/* Pulses the labels of player index's idle panel: takes the cosine of index plus the player's animation clock
   (selected[index]) scaled by g_pakPanelPulsePhaseScale, maps it through the next two constants to an unsigned
   alpha value and stores it as the alpha of the panel window's two label widgets. */

void PAKInterface_PulseIdlePanelLabels(s32 index) {
    float pulse;
    u32 alpha;
    MenuWidget *window = g_pakProfileScreenState->players[index].sprite;
    pulse = Math_Cosf((float)index + (float)g_pakProfileScreenState->selected[index] * g_pakPanelPulsePhaseScale)
        * (*(&g_pakPanelPulsePhaseScale + 1)) + g_pakPanelPulseUnsignedThreshold;
    if (pulse >= (*(&g_pakPanelPulseUnsignedThreshold + 1))) {
        goto large;
    }
    alpha = (s32)pulse;
    goto converted;
large:
    alpha = (s32)(pulse - (*(&g_pakPanelPulseUnsignedThreshold + 1)));
    alpha |= 0x80000000;
converted:
#if defined(VERSION_DE)
    Node_FindWidgetByResourceId(window, 740)->alpha = alpha;
#elif defined(VERSION_EU) || defined(VERSION_US) || defined(VERSION_US_REV1)
    Node_FindWidgetByResourceId(window, 706)->alpha = alpha;
#elif defined(VERSION_EU_X)
    Node_FindWidgetByResourceId(window, 725)->alpha = alpha;
#endif
#if defined(VERSION_DE)
    Node_FindWidgetByResourceId(window, 741)->alpha = alpha;
#elif defined(VERSION_EU) || defined(VERSION_US) || defined(VERSION_US_REV1)
    Node_FindWidgetByResourceId(window, 707)->alpha = alpha;
#elif defined(VERSION_EU_X)
    Node_FindWidgetByResourceId(window, 724)->alpha = alpha;
#endif
}

/* Marks entry i of the player settings records g_playerSettingsRecords and sets the back and state words
   of entry i of the player records g_pakProfileScreenState points to to 2. */

void PAKInterface_EnablePlayerPanel(s32 index) {
    g_gameSettings.playerSettings[index].enabled = 1;
    g_pakProfileScreenState->players[index].back = 2;
    g_pakProfileScreenState->players[index].state = 2;
}

/* Returns the index of the first of a player's four 400-byte entries in the game g_pakProfileScreenState whose
   state byte is -1, or -1 when all are in use. */





int PAKInterface_FindEmptyProfileSlot(int player) {
    int result;
    int i;

    result = -1;
    for (i = 0; i < 4 && result == -1; i++) {
        if (g_pakProfileScreenState->players[player].records[i].player == -1) {
            result = i;
        }
    }
    return result;
}

/* Returns 1 when all four of a player's 400-byte entries in the game g_pakProfileScreenState have state byte -1 at
   0x7D, stopping with 0 at the first in use. */





int PAKInterface_AreProfileSlotsEmpty(int player) {
    int result;
    int i;

    result = 1;
    for (i = 0; i < 4 && result == 1; i++) {
        if (g_pakProfileScreenState->players[player].records[i].player != -1) {
            result = 0;
        }
    }
    return result;
}

/* Returns the index of the first of the four player link slots of g_pakProfileScreenState
   points to whose first word is -1, meaning free, or -1 when none is. */

s32 PAKInterface_FindEmptyPlayerLink(void) {
    s32 found = -1;
    s32 i;

    for (i = 0; i < 4; i++) {
        if (found != -1) {
            break;
        }
        if (g_pakProfileScreenState->links[i].player == -1) {
            found = i;
        }
    }
    return found;
}

/* Returns the index of the first of the four player link slots of g_pakProfileScreenState whose
   id and value words match the arguments, or -1 when none does. */

int PAKInterface_FindPlayerProfileLink(int id, int value) {
    int result;
    int i;

    result = -1;
    for (i = 0; i < 4 && result == -1; i++) {
        if (g_pakProfileScreenState->links[i].player == id && g_pakProfileScreenState->links[i].entry == value) {
            result = i;
        }
    }
    return result;
}

/* Releases the first of the four player link slots of g_pakProfileScreenState whose id and value match
   the arguments, marking its id -1 and its state 2, and returns whether one was found. */

int PAKInterface_RemovePlayerProfileLink(int id, int value) {
    int found;
    int i;

    found = 0;
    for (i = 0; i < 4 && found == 0; i++) {
        if (g_pakProfileScreenState->links[i].player == id && g_pakProfileScreenState->links[i].entry == value) {
            found = 1;
            g_pakProfileScreenState->links[i].player = -1;
            g_pakProfileScreenState->links[i].state = 2;
        }
    }
    return found;
}

/* Takes a free slot from PAKInterface_FindEmptyPlayerLink and fills it with two values, marking it set, as
   Frontend_SetPlayerProfileLink does for an index; returns one, or zero when no slot is free. */






s32 PAKInterface_AddPlayerProfileLink(s32 first, s32 second) {
    s32 result = 0;
    s32 index = PAKInterface_FindEmptyPlayerLink();
    s32 taken;

    if (index >= 0) {
        taken = 1;
        result = taken;
        g_pakProfileScreenState->links[index].player = first;
        g_pakProfileScreenState->links[index].entry = second;
        g_pakProfileScreenState->links[index].state = result;
    }
    taken = result;
    return taken;
}

/* Returns 1 when all four player link slots of g_pakProfileScreenState hold -1 in
   their id word, stopping at the first that does not. */

int PAKInterface_ArePlayerLinksEmpty(void) {
    int result;
    int i;

    result = 1;
    for (i = 0; i < 4 && result == 1; i++) {
        if (g_pakProfileScreenState->links[i].player != -1) {
            result = 0;
        }
    }
    return result;
}

/* Reads two values and reports whether the first reaches the rounded object size when the second is nonzero. */

s32 PAKInterface_CheckRecordsNoteCapacity(void *slot, s32 *out)
{
    s32 a, b;
    s32 ret;
    s32 val;

    *out = 0;

    ret = Note_GetFreePages(slot, &a);
    if (ret == 0) {
        ret = Note_CountFreeNotes(slot, &b);
        if (ret == 0) {
            val = Note_BytesToPakPages(PAKInterface_GetRecordsNoteSize());
            if (b == 0) {
                *out = 0;
            } else if (a < val) {
                *out = 0;
            } else {
                *out = 1;
            }
        }
    }

    return ret;
}

/* Returns the size in bytes (1608) PAKInterface_CheckRecordsNoteCapacity passes on to Note_BytesToPakPages for the object it
   creates when it has none. */
s32 PAKInterface_GetRecordsNoteSize(void) {
    return 1608;
}

/* Builds the save packet of the panel of player index: copies the panel's 1600-byte save area into the packet through
   XPlus_CopyBytes, copies the panel's saved-profile word into the packet and stores in the packet checksum what Note_Crc32
   computes over the 1600 bytes with seed 7. */

void PAKInterface_BuildSavePacket(s32 index) {
    PakSavePacket *packet = &g_pakProfileScreenState->packet;

    XPlus_CopyBytes(packet, g_pakProfileScreenState->players[index].records, 1600);
    packet->savedProfile = g_pakProfileScreenState->players[index].profile;
    packet->checksum = Note_Crc32(packet, 1600, 7);
}

/* Copies the 1600-byte save packet of g_pakProfileScreenState back into the save area of the panel of player index through
   XPlus_CopyBytes, then copies the packet's saved-profile word into that panel. */

void PAKInterface_RestoreSavePacket(s32 index) {
    XPlus_CopyBytes(g_pakProfileScreenState->players[index].records, &g_pakProfileScreenState->packet, 1600);
    g_pakProfileScreenState->players[index].profile = g_pakProfileScreenState->packet.savedProfile;
}

/* Counts how many of the four player entries of g_pakProfileScreenState have a state that is not zero, 0xE or 0x11.
   Adapted from PAKInterface_CountActivePlayerPanels with the extra 0xE and 0x11 exclusions changed. */

s32 PAKInterface_CountPendingPlayerPanels(void) {
    s32 count = 0;
    s32 i;

    for (i = 0; i < 4; i++) {
        if (g_pakProfileScreenState->players[i].state != 0 && g_pakProfileScreenState->players[i].state != 14 && g_pakProfileScreenState->players[i].state != 17) {
            count++;
        }
    }
    return count;
}

/* Counts how many of the four player entries of g_pakProfileScreenState have a state that is neither zero nor 0x11.
   Adapted from PAKInterface_CountActivePlayerPanels with the extra 0x11 exclusion changed. */

s32 PAKInterface_CountUnfinishedPlayerPanels(void) {
    s32 count = 0;
    s32 i;

    for (i = 0; i < 4; i++) {
        if (g_pakProfileScreenState->players[i].state != 0 && g_pakProfileScreenState->players[i].state != 17) {
            count++;
        }
    }
    return count;
}

/* Counts how many of the four player panels of g_pakProfileScreenState have a non-zero state. */

s32 PAKInterface_CountActivePlayerPanels(void) {
    s32 count = 0;
    s32 i;

    for (i = 0; i < 4; i++) {
        if (g_pakProfileScreenState->players[i].state != 0) {
            count++;
        }
    }
    return count;
}

typedef struct { char pad[12]; s8 profileEntryIndex, linkedPlayerIndex; char rest[386]; } MatchProfile58;

void PAKInterface_LoadAllLinkedProfiles(void) {
    s32 i = 0; s32 none = -1;
    do {
        s32 player = g_pakProfileScreenState->links[i].player;
        s32 entry = g_pakProfileScreenState->links[i].entry;
        MatchProfile58 *dst = &g_localPlayerProfiles[i];
        if (player != none) { XPlus_CopyBytes(dst, g_pakProfileScreenState->players[player].slots[entry], 400); dst->profileEntryIndex = entry; }
        else { dst->linkedPlayerIndex = player; }
        i++;
    } while (i < 4);
}

/* Copies the block's chosen 400-byte record for the place at slot linkIndex into g_localPlayerProfiles[linkIndex]: when
   the place is claimed (id != -1), copies the owning player's chosen slot into the record and marks
   the record's owned-slot byte, then always stamps the record's place-id byte. */

void PAKInterface_LoadLinkedPlayerProfile(s32 linkIndex) {
    MatchProfile58 *record;
    s32 place;
    s32 owner;

    place = g_pakProfileScreenState->links[linkIndex].player;
    owner = g_pakProfileScreenState->links[linkIndex].entry;
    record = &g_localPlayerProfiles[linkIndex];
    if (place != -1) {
        XPlus_CopyBytes(record, g_pakProfileScreenState->players[place].slots[owner], 400);
        record->profileEntryIndex = owner;
    }
    record->linkedPlayerIndex = place;
}

#if !(defined(VERSION_US_REV1))
/* Toggles bit 0 of the game settings flags and returns 0. */
s32 Pak_ToggleTextChoice(void) {
    g_gameSettings.flags ^= 1;
    return 0;
}
#endif

#if defined(VERSION_EU)
#include "Common/menu_model_preview.h"
#include "Common/shared_worldfunc.h"
#include "Common/world.h"
#include "Common/selectionscreenstate.h"
#include "Resmgr/tsmos_setidletimer.h"
#include "Ai/playerprofile.h"
#include "Common/shared_menureply.h"
#include "Common/globals.h"
#include "Frontend/screen.h"
s32 Frontend_CreateProfileResetScreenEuropean(MenuWidget *tree) {
    s32 i;
    Shared_Game *settings;
    Shared_PlayerSettingsRecord *record;
    Shared_MenuObject *object;

    g_profileResetScreen = Cache_AllocateMemory(sizeof(*g_profileResetScreen));
    object = &g_playerViewRenderContext.object;
    Pools_ResetActorPools(object, 0);
    Player_InitializePlayerPool(&g_playerViewRenderContext, 0, 0);
    Scene_LoadLevelResources(&g_world, 0, 0);
    if (Cache_GetResourceActivityState() == 0) {
        Cache_SetResourceActivityState(1);
    }
    Frontend_RequestScreenMode(0);
    i = 7;
    Tsmos_DeactivateControllerState();
    record = &object->playerSettings[7];
    do {
        record->enabled = 0;
        i--;
        record--;
    } while (i >= 0);
    g_profileResetScreen->widget = Node_FindWidgetByResourceId(tree, 919);
    g_profileResetScreen->phase = 0;
    settings = &g_gameSettings;
    settings->laps = 10;
    settings->players = 10;
    for (i = 0; i < 4; i++) {
        Player_InitializeProfile(&g_localPlayerProfiles[i]);
    }
    Tsmos_SetIdleTimer(0.0f);
    return 0;
}
#endif

#if defined(VERSION_EU)
#include "types.h"
#include "Ovlgame/confirming_controller.h"
#include "Frontend/frontend.h"
#endif

#if defined(VERSION_US)
extern unsigned int g_itemsHandlesessionoptionpageLinkGapWords[12];
#endif

/* Retained data for this translation unit. */
#if defined(VERSION_US_REV1)
const char s_pakNoteIndexAndNameFormatUsRev1[6] =
    "%d.%s";
#endif
#if defined(VERSION_EU) || defined(VERSION_EU_X)
const char s_pakNoteDottedFormat[9] =
    "%d.%s.%s\000";
#endif
#if defined(VERSION_EU) || defined(VERSION_EU_X)
const char g_PAKInterface_LoadNoteListConstantsDe[6] =
    "%d.%s";
#endif
#if !(defined(VERSION_US))
#if !(defined(VERSION_DE) || defined(VERSION_EU) || defined(VERSION_EU_X) || defined(VERSION_US))
const float k_initialDataFloatConstants[1] = {
    120.0f,
};
#endif
#endif
#if defined(VERSION_EU_X)
const unsigned int g_pakInitialUnreferencedWordsEuX[3] = {
    0x00007530, 0x0041AEC0, 0x00000E03,
};
#endif
#if defined(VERSION_EU)
const unsigned int g_pakInitialUnreferencedWordsEu[3] = {
    0x484A0800, 0x4A05174D, 0xE9171C7C,
};
#endif
#if defined(VERSION_DE) || defined(VERSION_US)
#if defined(VERSION_US)
const unsigned int k_InitialZeroWords[1] = {
    0x00000000,
};
#endif
#endif
#if defined(VERSION_EU_X)
const unsigned int g_pakBoundUnreferencedWordsEuX[1] = {
    0x0041D280,
};
#endif
#if defined(VERSION_EU)
const unsigned int g_pakBoundUnreferencedWordsEu[1] = {
    0x4BBE0F47,
};
#endif
#if defined(VERSION_US)
char k_PakinterfaceBeginscreenexitData[4] =
    "_DEA";
#endif
#if defined(VERSION_EU_X)
unsigned int g_pakBeginScreenExitUnreferencedWordsEuX[1] = {
    0x0000003E,
};
#endif
#if defined(VERSION_EU)
unsigned int g_pakBeginScreenExitUnreferencedWordsEu[1] = {
    0x8C180FE8,
};
#endif
#if defined(VERSION_DE)
unsigned int g_pakBeginScreenExitUnreferencedWordsDe[1] = {
    0x004360AC,
};
#endif
#if defined(VERSION_US_REV1)
char g_playerSettingsPackedTextFragment[4] =
    "LL_S";
#endif
#if defined(VERSION_US_REV1)
char g_frontendScreenRetainedTextFragment[12] = "RE_WAR_CRYeq";
#endif
#if defined(VERSION_US_REV1)
unsigned int g_FrontendDispatchnodepairmenueventData[2] = {
    0x000B0000, 0x00000011,
};
#endif
#if defined(VERSION_US)
unsigned int g_itemsHandlesessionoptionpageLinkGapWords[12] = {
    0x41444745, 0x3C01800E, 0xC420D010, 0x3C018014, 0xE42007F0, 0x8C84000C, 0x3C03FBFF, 0x8C820030,
    0x3463FFFF, 0x00431024, 0x03E00008, 0xAC820030,
};
#endif

const char g_modeToken[7] =
    "[MODE]\000";
#if defined(VERSION_DE) || defined(VERSION_US) || defined(VERSION_US_REV1)
const unsigned char g_noteInfoIntFormat[3] = {
    0x25, 0x64, 0x00,
};
#endif
