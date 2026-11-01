#include "COMMON/NAME.H"
#include "FRONTEND/PAKMENU.H"
#include "TYPES.H"
#include "UI/TSMOS/SCREENS/PAKINTERFACESCREEN.H"

/* Labels player p's roster rows: for each of the four 400-byte records of g_localPlayerProfiles whose byte
   0xE is clear and whose owner byte 0xD is p, when the matching 150-byte status record at 0xD0 of
   g_gameSettings has byte 0x78 equal to one and byte 0x91 clear, points the text at 0x38 of the next
   row item (0x2BA, 0x2E5, 0x2E6, then 0x2E7) of the window at 0xC of p's 2920-byte record at 0x58
   of the block g_pakProfileScreenState points to at that record. Adapted from PAKInterface_CopyActiveProfilesToPakSlots with the copy
   replaced by the row label. */
extern u8 g_localPlayerProfiles[];
extern s8 g_profileSlotIndices[];
extern s8 g_profileSlotEnabledFlags[];
extern struct MatchSetupGlobals g_gameSettings;
extern struct Label *Node_FindWidgetByResourceId(void *, s32);
void PAKInterface_LabelActiveProfileRows(s32 player) {
    struct MatchSetupGlobals *globals;
    s32 row;
    s32 id;
    s32 i;
    row = 0;
    globals = &g_gameSettings;
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
        if (g_profileSlotEnabledFlags[i * 400] == 0 && g_profileSlotIndices[i * 400] == player &&
            globals->status[i].active == 1 && globals->status[i].m_IsBot == 0) {
            Node_FindWidgetByResourceId(g_pakProfileScreenState->players[player].menuWidget, id)->text = &g_localPlayerProfiles[i * 400];
            row++;
        }
    }
}
