#include "include_asm.h"
#include "Common/gameplay_transition.h"
#include "types.h"
#if ((defined(VERSION_EU)))
#include "Ovlgame/confirming_controller.h"
#endif
#if ((defined(VERSION_EU)))
#include "Ai/Player/player_placeplayerforround.h"
#endif
#if ((defined(VERSION_EU)))
#include "Ovlgame/match.h"
#endif
#if ((defined(VERSION_EU)))
#include "Common/game_session.h"
#endif

#if !(defined(VERSION_US_REV1))

#endif

#if defined(VERSION_US_REV1)

#endif





#if defined(VERSION_EU_X)

#endif
#if defined(VERSION_EU)

#endif

#if defined(VERSION_EU) || defined(VERSION_EU_X)

#endif

#if defined(VERSION_EU)
s32 Items_ForwardRulesLock(void *entry, MenuRules *rules) {
    Player_PlacePlayerForRound(rules->locked);
    return 1;
}

/* Pak/option page handler: while g_sessionOptionResetMode is 1 it runs Match_ResetMatchControllerState on the session, otherwise it clears the
   flag word at 0x5D0 of the record at 0x1C of its second argument. Returns one. */
s32 Items_HandleSessionOptionPage(void *entry, void **menu) {
    if (g_sessionOptionResetMode == 1) {
        Match_ResetMatchControllerState(&g_gameSession);
    } else {
        ((Player *)menu[7])->actorState = 0;
    }
    return 1;
}
#endif

/* Retained data for this translation unit. */
#if !(defined(VERSION_US_REV1))
const char k_cmenuprofileUpdategamespeedlabelDataConstantWords[4] =
    "%3d\000";
#endif
#if defined(VERSION_US_REV1)
const char k_cmenuprofileUpdategamespeedlabelDataTextBytes[4] =
    "%3d";
#endif

const float k_confirmingInitmatchcountersDataFloatConstantWords[2] = {
    9.0e+02f, -1.0f,
};

const float k_cmenuProfileAdjustGameSpeedFactorUnit[1] = {
    1.0f,
};
#if defined(VERSION_EU_X)
const unsigned int k_cmenuprofileFormatprofilequantitylabelDataConstantWords[3] = {
    0x00419F50, 0x00000000, 0x00000000,
};
#endif
#if defined(VERSION_EU)
const unsigned int k_cmenuprofileFormatprofilequantitylabelDataLinkGapWords[3] = {
    0xAE6A0154, 0xCA7C382A, 0xC97B0805,
};
#endif
#if defined(VERSION_EU) || defined(VERSION_EU_X)
const char k_cmenuprofileFormatprofilequantitylabelDataTextBytes[5] =
    "%02d";
#endif
