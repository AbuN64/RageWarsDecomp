#include "RESMGR/resmgr_string_memory.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "FRONTEND/PAKMENU.H"
#include "COMMON/NAME.H"
#include "TYPES.H"
#include "UI/TSMOS/SCREENS/PAKINTERFACESCREEN.H"

/* Copies the records player p owns into p's block record: for each of the four 400-byte records of
   g_localPlayerProfiles whose byte 0xE is clear and whose owner byte 0xD is p, when the matching 150-byte
   status record at 0xD0 of g_gameSettings has byte 0x78 equal to one and byte 0x91 clear, copies the whole record
   through XPlus_CopyBytes into slot [byte 0xC] of the 400-byte slots at 0x18 of p's 2920-byte
   record at 0x58 of the block g_pakProfileScreenState points to. */





extern u8 g_localPlayerProfiles[];
extern s8 g_profileSlotIndices[];
extern s8 g_profileSlotEnabledFlags[];




extern struct MatchSetupGlobals g_gameSettings;

void PAKInterface_CopyActiveProfilesToPakSlots(s32 player) {
    struct MatchSetupGlobals *globals;
    s32 i;
    s32 size;

    size = 400;
    globals = &g_gameSettings;
    for (i = 0; i < 4; i++) {
        if (g_profileSlotEnabledFlags[i * 400] == 0 && g_profileSlotIndices[i * 400] == player &&
            globals->status[i].active == 1 && globals->status[i].m_IsBot == 0) {
            XPlus_CopyBytes(g_pakProfileScreenState->players[player].slots[g_profileSlotResetFlags[i * 400]],
                          &g_localPlayerProfiles[i * 400], size);
        }
    }
}
