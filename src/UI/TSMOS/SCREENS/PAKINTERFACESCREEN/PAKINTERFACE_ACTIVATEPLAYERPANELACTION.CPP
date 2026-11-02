#include "COMMON/SCREEN.H"
#include "COMMON/NAME.H"
#include "FRONTEND/PAKMENU.H"
#include "COMMON/RESOURCELOADSTATE.H"
#include "COMMON/ENTRYRECAT6C.H"
#include "COMMON/MESSAGESEMAPHORE.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/MENURECAT24.H"
#include "TYPES.H"
#include "UI/TSMOS/SCREENS/PAKINTERFACESCREEN.H"
#include "FRONTEND/PAKINTERFACE_FINDREADYTRANSFERPLAYER.H"
#include "FRONTEND/FRONTEND_FINDPROFILEOWNER.H"
#include "FRONTEND/FRONTEND_SETPLAYERPROFILELINK.H"
#include "RESMGR/resmgr_string_memory.H"
#include "FRONTEND/NODE_FINDWIDGETBYRESOURCEID.H"

/* Steps player playerEntryId's menu state machine at 0x58 of its 0xB68-byte record in the block g_pakProfileScreenState points to
   on the event SmpOverlay_GetSlotNodeId reports: each state accepts its events, moves to the next state (by the game
   mode at 0x54 where it matters), updates the player's name records, and refreshes the player through
   PAKInterface_RefreshPlayerPanel_PakinterfaceActivateplayerpanelaction. Returns zero. */
extern u8 g_localPlayerProfiles[];
extern u8 g_playerSettings[];

extern s32 SmpOverlay_GetSlotNodeId(s32, s32);
extern void SmpOverlay_SetSlotValue(s32, s32, s32);
extern void PAKInterface_RefreshPlayerPanel(s32);
extern s32 PAKInterface_CheckRecordsNoteCapacity(void *slot, s32 *out);
extern s32 PAKInterface_SavePlayerRecords(s32);
extern void Widget_SetWidgetFlag08(void *object, int enabled);

extern s32 Note_DeleteNote(s32, s32);

extern void Player_InitializeProfile(void *);
extern void Note_ProbeStatus(s32);
extern void PAKInterface_ResolvePlayerPakState(s32);
extern void PAKInterface_RelabelSlotRows(s32);


extern s32 Note_RepairId(s32);

s32 PAKInterface_ActivatePlayerPanelAction(s32 unused0, s32 unused1, s32 playerEntryId) {
    s32 answer;
    s32 i;
    s32 j;
    s32 p;
    s32 event;
    s32 slot;
    s32 other;
    s32 q;
    s32 found;
    u8 *node;
    u8 *next;
    u8 *settings;
    u8 c;
    s32 sub;
    s32 mode;

    MarkMenuEventHandled();
    i = 0;
    p = playerEntryId & 0xFFFF;
    event = SmpOverlay_GetSlotNodeId(g_pakProfileScreenState->root, p);
    switch (g_pakProfileScreenState->players[p].state) {
    case 1:
        switch (event) {
#if defined(VERSION_DE)
        case 720:
#elif defined(VERSION_EU_X)
        case 745:
#else
        case 749:
#endif
            g_pakProfileScreenState->players[p].back = 2;
            g_pakProfileScreenState->players[p].state = 2;
            PAKInterface_RefreshPlayerPanel(p);
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
                g_pakProfileScreenState->players[p].state = 14;
                PAKInterface_RefreshPlayerPanel(p);
                break;
            case 2:
                if (g_pakProfileScreenState->players[p].host == 1) {
                    PAKInterface_BeginLinkedProfileTransfer(p);
                } else {
                    g_pakProfileScreenState->players[p].state = 14;
                }
                PAKInterface_RefreshPlayerPanel(p);
                break;
            case 7:
                g_pakProfileScreenState->players[p].state = 26;
                g_pakProfileScreenState->players[p].next = 1;
                PAKInterface_RefreshPlayerPanel(p);
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
                g_pakProfileScreenState->players[p].state = 14;
                PAKInterface_RefreshPlayerPanel(p);
                break;
            case 7:
                g_pakProfileScreenState->players[p].state = 26;
                g_pakProfileScreenState->players[p].next = 1;
                PAKInterface_RefreshPlayerPanel(p);
                break;
            case 2:
                if (g_pakProfileScreenState->players[p].host == 1) {
                    PAKInterface_BeginLinkedProfileTransfer(p);
                } else {
                    g_pakProfileScreenState->players[p].state = 14;
                }
                PAKInterface_RefreshPlayerPanel(p);
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
            g_pakProfileScreenState->players[p].state = 28;
            PAKInterface_RefreshPlayerPanel(p);
            break;
#if defined(VERSION_DE)
        case 726:
#elif defined(VERSION_EU_X)
        case 734:
#else
        case 702:
#endif
            g_pakProfileScreenState->players[p].back = 2;
            g_pakProfileScreenState->players[p].state = 2;
            PAKInterface_RefreshPlayerPanel(p);
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
            if (PAKInterface_CheckRecordsNoteCapacity(p, &answer) == 0) {
                if (answer == 1) {
                    g_pakProfileScreenState->players[p].state = 12;
                } else {
                    g_pakProfileScreenState->players[p].state = 11;
                }
            } else {
                g_pakProfileScreenState->players[p].back = 2;
                g_pakProfileScreenState->players[p].state = 2;
            }
            PAKInterface_RefreshPlayerPanel(p);
            break;
#if defined(VERSION_DE)
        case 709:
#elif defined(VERSION_EU_X)
        case 749:
#else
        case 753:
#endif
            if (g_pakProfileScreenState->phase == 7) {
                g_pakProfileScreenState->players[p].state = 26;
                g_pakProfileScreenState->players[p].next = 15;
            } else {
                g_pakProfileScreenState->players[p].state = 14;
            }
            PAKInterface_RefreshPlayerPanel(p);
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
            g_pakProfileScreenState->players[p].records[g_pakProfileScreenState->players[p].record].owner = (u8) g_pakProfileScreenState->players[p].record;
            g_pakProfileScreenState->players[p].records[g_pakProfileScreenState->players[p].record].player = p;
            g_pakProfileScreenState->players[p].records[g_pakProfileScreenState->players[p].record].time = g_pakProfileScreenState->players[p].profile;
            if (g_pakProfileScreenState->phase == 7) {
                settings = g_playerSettings;
                g_pakProfileScreenState->players[p].records[g_pakProfileScreenState->players[p].record].setting[0] = settings[123];
                g_pakProfileScreenState->players[p].records[g_pakProfileScreenState->players[p].record].setting[1] = settings[125];
                g_pakProfileScreenState->players[p].records[g_pakProfileScreenState->players[p].record].setting[2] = settings[121];
                g_pakProfileScreenState->players[p].records[g_pakProfileScreenState->players[p].record].setting[3] = settings[122];
                g_pakProfileScreenState->players[p].records[g_pakProfileScreenState->players[p].record].setting[4] = settings[130];
            }
            if (PAKInterface_SavePlayerRecords(p) == 1) {
                switch (g_pakProfileScreenState->phase) {
                case 0:
                    if (PAKInterface_FindEmptyProfileSlot(p) >= 0) {
                        g_pakProfileScreenState->players[p].state = 23;
                    } else {
                        g_pakProfileScreenState->players[p].state = 14;
                    }
                    break;
                case 7:
                    Frontend_SetPlayerProfileLink(p, 0, 0);
                    PAKInterface_LoadLinkedPlayerProfile(0);
                    MarkMenuEventHandled();
                    PAKInterface_BeginScreenExit(9);
                    return 0;
                default:
                    g_pakProfileScreenState->players[p].state = 13;
                    break;
                }
                PAKInterface_RefreshPlayerPanel(p);
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
                g_pakProfileScreenState->players[p].state = 23;
                break;
            case 1:
                g_pakProfileScreenState->players[p].state = 23;
                break;
            case 7:
                g_pakProfileScreenState->players[p].state = 23;
                break;
            default:
                g_pakProfileScreenState->players[p].state = 13;
                break;
            }
            PAKInterface_RefreshPlayerPanel(p);
            break;
        }
        break;
    case 12:
        slot = PAKInterface_FindEmptyProfileSlot(p);
        if (slot >= 0) {
#if defined(VERSION_DE)
            node = Node_FindWidgetByResourceId((void*)g_pakProfileScreenState->players[p].menu, 730);
#elif defined(VERSION_EU_X)
            node = Node_FindWidgetByResourceId((void*)g_pakProfileScreenState->players[p].menu, 690);
#else
            node = Node_FindWidgetByResourceId((void*)g_pakProfileScreenState->players[p].menu, 755);
#endif
            for (j = 0; ((Shared_Item *) node)->flags & 0x10; j++) {
                g_pakProfileScreenState->players[p].records[slot].name[j] = *(u8 *) ((Shared_Item *) node)->label->text;
                next = (u8 *) ((Shared_Item *) node)->next;
                if (next == 0) {
                    break;
                }
                node = next;
            }
            for (j = 6; j > 0; j--) {
                c = g_pakProfileScreenState->players[p].records[slot].name[j];
                if (c != 0 && c != ' ') {
                    break;
                }
                g_pakProfileScreenState->players[p].records[slot].name[j] = 0;
            }
            g_pakProfileScreenState->players[p].state = 16;
            g_pakProfileScreenState->players[p].record = slot;
        } else {
            g_pakProfileScreenState->players[p].state = 3;
        }
        PAKInterface_RefreshPlayerPanel(p);
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
            g_pakProfileScreenState->players[p].state = 4;
            PAKInterface_RefreshPlayerPanel(p);
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
                g_pakProfileScreenState->players[p].state = 14;
                PAKInterface_RefreshPlayerPanel(p);
                break;
            case 2:
                if (g_pakProfileScreenState->players[p].host == 1) {
                    PAKInterface_BeginLinkedProfileTransfer(p);
                } else {
                    g_pakProfileScreenState->players[p].state = 14;
                }
                PAKInterface_RefreshPlayerPanel(p);
                break;
            case 7:
                g_pakProfileScreenState->players[p].state = 26;
                g_pakProfileScreenState->players[p].next = 11;
                PAKInterface_RefreshPlayerPanel(p);
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
                g_pakProfileScreenState->players[p].state = 15;
                break;
            case 2:
                g_pakProfileScreenState->players[p].back = 2;
                g_pakProfileScreenState->players[p].state = 2;
                break;
            case 7:
                g_pakProfileScreenState->players[p].back = 2;
                g_pakProfileScreenState->players[p].state = 2;
                break;
            case 1:
            case 4:
            case 6:
                g_pakProfileScreenState->players[p].state = 14;
                break;
            }
            PAKInterface_RefreshPlayerPanel(p);
            break;
#if defined(VERSION_DE)
        case 743:
#elif defined(VERSION_EU_X)
        case 758:
#else
        case 729:
#endif
            i = g_pakProfileScreenState->players[p].slot;
            if (XPlus_ParseDecimalInteger(g_pakProfileScreenState->players[p].names[i].text) > 0) {
                g_pakProfileScreenState->players[p].state = 8;
                PAKInterface_RefreshPlayerPanel(p);
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
            if (Note_DeleteNote(p, g_pakProfileScreenState->players[p].slot) == 0) {
#if defined(VERSION_EU) || defined(VERSION_EU_X)
                if (XPlus_CompareStringsIgnoreCase((u8 *)g_pakProfileGameNames[g_languageIndex],
#else
                if (XPlus_CompareStringsIgnoreCase((u8 *)g_pakProfileGameNameFixed,
#endif
                                     g_pakProfileScreenState->players[p].names[g_pakProfileScreenState->players[p].slot].code) == 0) {
                    for (j = 0; j < 4; j++) {
                        found = Frontend_FindProfileOwner(g_pakProfileScreenState->players[p].profile, g_pakProfileScreenState->players[p].records[j].owner);
                        if (found != -1) {
                            Player_InitializeProfile(&((Profile *) g_localPlayerProfiles)[found]);
                        }
                    }
                }
                g_pakProfileScreenState->players[p].state = 4;
                PAKInterface_RefreshPlayerPanel(p);
            } else {
                Note_ProbeStatus(p);
                PAKInterface_ResolvePlayerPakState(p);
            }
            break;
#if defined(VERSION_DE)
        case 757:
#elif defined(VERSION_EU_X)
        case 737:
#else
        case 719:
#endif
            g_pakProfileScreenState->players[p].state = 4;
            PAKInterface_RefreshPlayerPanel(p);
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
            i = g_pakProfileScreenState->players[p].choice;
            other = Frontend_FindProfileOwner(g_pakProfileScreenState->players[p].profile, g_pakProfileScreenState->players[p].records[i].owner);
            if (other != -1) {
                Player_InitializeProfile(&((Profile *) g_localPlayerProfiles)[other]);
            }
            Player_InitializeProfile(&g_pakProfileScreenState->players[p].records[i]);
            if (PAKInterface_SavePlayerRecords(p) == 1) {
                if (g_pakProfileScreenState->players[p].sub == 5) {
                    switch (g_pakProfileScreenState->phase) {
                    case 0:
                        g_pakProfileScreenState->players[p].back = 2;
                        g_pakProfileScreenState->players[p].state = 2;
                        g_pakProfileScreenState->players[p].next = 12;
                        g_pakProfileScreenState->players[p].sub = 0;
                        break;
                    case 2:
                        g_pakProfileScreenState->players[p].next = 9;
                        g_pakProfileScreenState->players[p].back = 2;
                        g_pakProfileScreenState->players[p].state = 2;
                        g_pakProfileScreenState->players[p].sub = 3;
                        break;
                    default:
                        g_pakProfileScreenState->players[p].state = 13;
                        break;
                    }
                } else {
                    g_pakProfileScreenState->players[p].state = 13;
                }
                PAKInterface_RefreshPlayerPanel(p);
            }
            break;
#if defined(VERSION_DE)
        case 753:
#elif defined(VERSION_EU_X)
        case 741:
#else
        case 716:
#endif
            g_pakProfileScreenState->players[p].state = 13;
            PAKInterface_RefreshPlayerPanel(p);
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
            slot = PAKInterface_FindEmptyProfileSlot(p);
            if (slot >= 0) {
                XPlus_CopyBytes(&g_pakProfileScreenState->players[p].records[slot],
                                 &g_pakProfileScreenState->players[g_pakProfileScreenState->links[0].player].records[g_pakProfileScreenState->links[0].entry],
                                 400);
                g_pakProfileScreenState->players[p].record = slot;
                g_pakProfileScreenState->players[p].records[slot].owner = slot;
                g_pakProfileScreenState->players[p].records[slot].time = g_pakProfileScreenState->players[p].profile;
            }
            if (PAKInterface_SavePlayerRecords(p) == 1) {
                if (g_pakProfileScreenState->phase == 2) {
                    if (g_pakProfileScreenState->players[p].host == 1) {
                        PAKInterface_BeginLinkedProfileTransfer(p);
                    } else {
                        g_pakProfileScreenState->players[p].state = 14;
                    }
                } else {
                    g_pakProfileScreenState->players[p].state = 13;
                }
                PAKInterface_RefreshPlayerPanel(p);
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
                if (g_pakProfileScreenState->players[p].host == 1) {
                    PAKInterface_BeginLinkedProfileTransfer(p);
                } else {
                    g_pakProfileScreenState->players[p].state = 14;
                }
            } else {
                g_pakProfileScreenState->players[p].state = 13;
            }
            PAKInterface_RefreshPlayerPanel(p);
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
            sub = g_pakProfileScreenState->players[p].sub;
            switch (sub) {
            case 3:
                g_pakProfileScreenState->players[p].state = 17;
                q = ((int (*)(u8 *)) PAKInterface_FindReadyTransferPlayer)((u8 *) g_pakProfileScreenState + p * sizeof(PakProfilePanelState));
                if (q >= 0) {
                    g_pakProfileScreenState->players[q].back = 2;
                    g_pakProfileScreenState->players[q].state = 2;
                    g_pakProfileScreenState->players[q].next = 13;
                    g_pakProfileScreenState->players[q].sub = 3;
                    PAKInterface_RefreshPlayerPanel(q);
                }
                break;
            case 6:
                switch (g_pakProfileScreenState->phase) {
                case 1:
                    g_pakProfileScreenState->players[p].state = 17;
                    q = ((int (*)(u8 *)) PAKInterface_FindReadyTransferPlayer)((u8 *) g_pakProfileScreenState + p * sizeof(PakProfilePanelState));
                    if (q >= 0) {
                        g_pakProfileScreenState->players[q].back = 2;
                        g_pakProfileScreenState->players[q].state = 2;
                        g_pakProfileScreenState->players[q].next = 13;
                        g_pakProfileScreenState->players[q].sub = sub;
                        PAKInterface_RefreshPlayerPanel(q);
                    }
                    break;
                case 7:
                    g_pakProfileScreenState->players[p].state = 26;
                    g_pakProfileScreenState->players[p].next = 13;
                    break;
                }
                break;
            case 0:
                g_pakProfileScreenState->players[p].state = 14;
                break;
            case 5:
                mode = g_pakProfileScreenState->phase;
                switch (mode) {
                case 3:
                    g_pakProfileScreenState->players[p].state = 14;
                    break;
                case 0:
                    g_pakProfileScreenState->players[p].back = 2;
                    g_pakProfileScreenState->players[p].state = 2;
                    g_pakProfileScreenState->players[p].next = 12;
                    g_pakProfileScreenState->players[p].sub = 0;
                    break;
                case 2:
                    g_pakProfileScreenState->players[p].back = mode;
                    g_pakProfileScreenState->players[p].state = mode;
                    g_pakProfileScreenState->players[p].next = 9;
                    g_pakProfileScreenState->players[p].sub = 3;
                    break;
                }
                break;
            }
            PAKInterface_RefreshPlayerPanel(p);
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
        switch (g_pakProfileScreenState->players[p].sub) {
        case 0:
            break;
        case 3:
            if (g_pakProfileScreenState->players[p].used[i] == 1) {
                Frontend_SetPlayerProfileLink(p, i, 0);
                g_pakProfileScreenState->players[p].choice = i;
                g_pakProfileScreenState->players[p].state = 27;
                PAKInterface_RefreshPlayerPanel(p);
            }
            break;
        case 6:
            switch (g_pakProfileScreenState->phase) {
            case 1:
                if (g_pakProfileScreenState->players[p].used[i] == 1) {
                    g_pakProfileScreenState->players[p].choice = i;
                    g_pakProfileScreenState->players[p].state = 22;
                    PAKInterface_RefreshPlayerPanel(p);
                }
                break;
            case 7:
                if (g_pakProfileScreenState->players[p].used[i] == 1) {
                    Frontend_SetPlayerProfileLink(p, i, 0);
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
                if (g_pakProfileScreenState->players[p].used[i] != 2) {
                    g_pakProfileScreenState->players[p].choice = i;
                    g_pakProfileScreenState->players[p].state = 7;
                    PAKInterface_RefreshPlayerPanel(p);
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
        Frontend_SetPlayerProfileLink(p, g_pakProfileScreenState->players[p].choice, i);
        PAKInterface_LoadLinkedPlayerProfile(i);
#if defined(VERSION_DE)
        Widget_SetWidgetFlag08(Node_FindWidgetByResourceId((void*)g_pakProfileScreenState->players[p].notes[g_pakProfileScreenState->players[p].choice], 713), 1);
#elif defined(VERSION_EU_X)
        Widget_SetWidgetFlag08(Node_FindWidgetByResourceId((void*)g_pakProfileScreenState->players[p].notes[g_pakProfileScreenState->players[p].choice], 761), 1);
#else
        Widget_SetWidgetFlag08(Node_FindWidgetByResourceId((void*)g_pakProfileScreenState->players[p].notes[g_pakProfileScreenState->players[p].choice], 689), 1);
#endif
        g_pakProfileScreenState->players[p].used[g_pakProfileScreenState->players[p].choice] = 0;
        g_pakProfileScreenState->links[i].state = 0;
        g_pakProfileScreenState->players[p].port = i;
        PAKInterface_RelabelSlotRows(p);
        g_pakProfileScreenState->players[p].state = 13;
        PAKInterface_RefreshPlayerPanel(p);
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
        if (i != p) {
            SmpOverlay_SetSlotValue(g_pakProfileScreenState->root, p, 1);
            g_pakProfileScreenState->players[i].back = 2;
            g_pakProfileScreenState->players[i].state = 2;
            g_pakProfileScreenState->players[i].next = 9;
            g_pakProfileScreenState->players[i].sub = 3;
            g_pakProfileScreenState->players[i].host = 1;
            PAKInterface_RefreshPlayerPanel(i);
        } else {
            g_pakProfileScreenState->players[p].state = 9;
            PAKInterface_RefreshPlayerPanel(p);
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
            g_pakProfileScreenState->players[p].state = 14;
            PAKInterface_RefreshPlayerPanel(p);
            break;
#if defined(VERSION_DE)
        case 687:
#elif defined(VERSION_EU_X)
        case 713:
#else
        case 744:
#endif
            PAKInterface_CopyActiveProfilesToPakSlots(p);
            if (PAKInterface_SavePlayerRecords(p) == 1) {
                g_pakProfileScreenState->players[p].state = 14;
                PAKInterface_RefreshPlayerPanel(p);
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
                g_pakProfileScreenState->players[p].state = 14;
                PAKInterface_RefreshPlayerPanel(p);
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
            g_pakProfileScreenState->players[p].back = 2;
            g_pakProfileScreenState->players[p].state = 2;
            PAKInterface_RefreshPlayerPanel(p);
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
            g_pakProfileScreenState->players[p].state = 12;
            PAKInterface_RefreshPlayerPanel(p);
            break;
#if defined(VERSION_DE)
        case 697:
#elif defined(VERSION_EU_X)
        case 704:
#else
        case 686:
#endif
            if (g_pakProfileScreenState->phase == 7) {
                g_pakProfileScreenState->players[p].state = 26;
                g_pakProfileScreenState->players[p].next = 23;
            } else {
                g_pakProfileScreenState->players[p].state = 14;
            }
            PAKInterface_RefreshPlayerPanel(p);
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
            g_pakProfileScreenState->players[p].state = 13;
            g_pakProfileScreenState->players[p].sub = 5;
            PAKInterface_RefreshPlayerPanel(p);
            break;
#if defined(VERSION_DE)
        case 701:
#elif defined(VERSION_EU_X)
        case 687:
#else
        case 682:
#endif
            if (g_pakProfileScreenState->players[p].host == 1) {
                PAKInterface_BeginLinkedProfileTransfer(p);
            } else {
                g_pakProfileScreenState->players[p].state = 14;
            }
            PAKInterface_RefreshPlayerPanel(p);
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
            if (g_pakProfileScreenState->players[p].host == 1) {
                PAKInterface_BeginLinkedProfileTransfer(p);
            } else {
                g_pakProfileScreenState->players[p].state = 14;
            }
            PAKInterface_RefreshPlayerPanel(p);
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
            PAKInterface_RefreshPlayerPanel(p);
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
#if defined(VERSION_EU_X)

#else
#endif
    case 28:
        switch (event) {
#if defined(VERSION_DE)
        case 674:
            g_pakProfileScreenState->players[p].back = 2;
            g_pakProfileScreenState->players[p].state = 2;
            PAKInterface_RefreshPlayerPanel(p);
            break;
        case 675:
#elif defined(VERSION_EU_X)
        case 718:
#else
        case 735:
            g_pakProfileScreenState->players[p].back = 2;
            g_pakProfileScreenState->players[p].state = 2;
            PAKInterface_RefreshPlayerPanel(p);
            break;
        case 736:
#endif
            if (Note_RepairId(p) != 0) {
                g_pakProfileScreenState->players[p].state = 29;
                PAKInterface_RefreshPlayerPanel(p);
            } else {
                g_pakProfileScreenState->players[p].back = 2;
                g_pakProfileScreenState->players[p].state = 2;
                PAKInterface_RefreshPlayerPanel(p);
            }
            break;
#if defined(VERSION_EU_X)
        case 719:
            g_pakProfileScreenState->players[p].back = 2;
            g_pakProfileScreenState->players[p].state = 2;
            PAKInterface_RefreshPlayerPanel(p);
            break;
#else
#endif
        }
        break;
#if defined(VERSION_EU_X)
#else

#endif
    case 29:
#if defined(VERSION_DE)
        if (event == 677) {
#elif defined(VERSION_EU_X)
        if (event == 716) {
#else
        if (event == 704) {
#endif
            g_pakProfileScreenState->players[p].back = 2;
            g_pakProfileScreenState->players[p].state = 2;
            PAKInterface_RefreshPlayerPanel(p);
        }
        break;
    }
    return 0;
}
