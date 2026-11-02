#include "DATA/REST_SOURCE_RECORDS.H"
extern char g_activeProfileCharacterSelections[];
extern u8 g_encodedCheatCode[];
extern u8*g_optionsSecondListChoiceOneLabels[];
extern char g_playerNameBytes_eu[];
extern char g_playerViewRenderContextPlayerNames_de[];
extern u8 g_profileAchievementProgressRows[][];
extern char g_profileModeOneLabel[];
extern char g_profileSecondConfirmationLabel[];
extern struct Shared_DebugField *g_profileSelectionResources[];
extern char *g_unlockedLevelResultLabel[];
#include "include_asm.h"

/* encodedInserttextentrycharacterWords1Data.CPP */
/* ROM-grounded data: rodata/writable/800E5CA0 */
s32 g_EncodedInserttextentrycharacterWords1[3] = {
    0, 0, 0,
};

/* encodedInserttextentrycharacterHalfwordsData.CPP */
#if !(defined(VERSION_US_REV1))
#if defined(VERSION_DE)
RestEncodedInserttextentrycharacterEncodedHalfwordsLayout468 k_EncodedInserttextentrycharacterEncodedHalfwords = {
    { 0, 0, 0, 0, 0, 0 },
    (void *)&g_encodedCheatCode,
    "big cheat activated\000",
    (void *)((char *)&g_optionsSecondListChoiceOneLabels + 20),
    "janes cheat activated\000\000\000",
    { (void *)((char *)&g_optionsSecondListChoiceOneLabels + 44), (void *)((char *)&g_profileAchievementProgressRows + 437), (void *)&g_playerViewRenderContextPlayerNames_de, (void *)((char *)&g_profileAchievementProgressRows + 137), (void *)((char *)&g_profileAchievementProgressRows + 287), (void *)((char *)&g_profileAchievementProgressRows + 437), (void *)((char *)&g_optionsSecondListChoiceOneLabels + 76), (void *)((char *)&g_optionsSecondListChoiceOneLabels + 80), (void *)((char *)&g_optionsSecondListChoiceOneLabels + 84), (void *)((char *)&g_optionsSecondListChoiceOneLabels + 88) },
    65536,
    0x10000000,
    { 0, 65281, 901, 4457180, 0, 0, 0, 0 },
    0x08000021,
    { 8, 65281 },
    (void *)((char *)&g_profileModeOneLabel + 56),
    { 4464740, 0, 0, 0, 0, 65601, 40, 65281 },
    (void *)&g_unlockedLevelResultLabel,
    { 4464740, 4448656, 0, 0, 0, 65601, 15, 65281 },
    (void *)&g_unlockedLevelResultLabel,
    { 4464740, 4448676, 0, 0, 0, 65601, 35, 65281 },
    (void *)((char *)&g_profileSecondConfirmationLabel + 4),
    { 4464740, 0, 4448696, 0 },
    (void *)((char *)&g_profileSelectionResources + 16),
    { 327680, 4448548, 0, 4462068, 4448564, 262144, 0, 0, 1, 1, 1, 1, 1, 1, 1, -1, 1, 1, 1, -1, 0, 0, 0, 0, 0, 0, 0, 0 },
};
#endif
#if defined(VERSION_EU)
RestEncodedInserttextentrycharacterEncodedHalfwordsLayout469 k_EncodedInserttextentrycharacterEncodedHalfwords = {
    { 0, 0, 0, 0, 0, 0 },
    { (void *)&g_encodedCheatCode, (void *)&g_encodedCheatCode, (void *)&g_encodedCheatCode, (void *)&g_encodedCheatCode },
    "big cheat activated\000",
    { (void *)((char *)&g_encodedCheatCode + 40), (void *)((char *)&g_encodedCheatCode + 40), (void *)((char *)&g_encodedCheatCode + 40), (void *)((char *)&g_encodedCheatCode + 40) },
    "janes cheat activated\000\000\000",
    { (void *)((char *)&g_encodedCheatCode + 76), (void *)((char *)&g_encodedCheatCode + 76), (void *)((char *)&g_encodedCheatCode + 76), (void *)((char *)&g_encodedCheatCode + 76), (void *)&g_playerNameBytes_eu, (void *)&g_playerNameBytes_eu, (void *)&g_playerNameBytes_eu, (void *)&g_playerNameBytes_eu, (void *)((char *)&g_profileAchievementProgressRows + 137), (void *)((char *)&g_profileAchievementProgressRows + 137), (void *)((char *)&g_profileAchievementProgressRows + 137), (void *)((char *)&g_profileAchievementProgressRows + 137), (void *)((char *)&g_profileAchievementProgressRows + 287), (void *)((char *)&g_profileAchievementProgressRows + 287), (void *)((char *)&g_profileAchievementProgressRows + 287), (void *)((char *)&g_profileAchievementProgressRows + 287), (void *)((char *)&g_profileAchievementProgressRows + 437), (void *)((char *)&g_profileAchievementProgressRows + 437), (void *)((char *)&g_profileAchievementProgressRows + 437), (void *)((char *)&g_profileAchievementProgressRows + 437), (void *)((char *)&g_encodedCheatCode + 116), (void *)((char *)&g_encodedCheatCode + 132), (void *)((char *)&g_encodedCheatCode + 148), (void *)((char *)&g_encodedCheatCode + 164) },
    65536,
    0x10000000,
    { 0, 65281, 901, 4460996, 0, 0, 0, 0 },
    0x08000021,
    { 8, 65281 },
    (void *)((char *)&g_profileModeOneLabel + 224),
    { 4468588, 0, 0, 0, 0, 65601, 40, 65281 },
    (void *)&g_unlockedLevelResultLabel,
    { 4468588, 4452140, 0, 0, 0, 65601, 15, 65281 },
    (void *)&g_unlockedLevelResultLabel,
    { 4468588, 4452160, 0, 0, 0, 65601, 35, 65281 },
    (void *)((char *)&g_profileSecondConfirmationLabel + 16),
    { 4468588, 0, 4452180, 0 },
    (void *)((char *)&g_profileSelectionResources + 16),
    { 327680, 4452032, 0, 4465900, 4452048, 262144, 0, 0, 1, 1, 1, 1, 1, 1, 1, -1, 1, 1, 1, -1, 0, 0, 0, 0, 0, 0, 0, 0 },
};
#endif
#if defined(VERSION_EU_X)
RestEncodedInserttextentrycharacterEncodedHalfwordsLayout470 k_EncodedInserttextentrycharacterEncodedHalfwords = {
    { 0, 0, 0, 0, 0, 0 },
    { (void *)&g_encodedCheatCode, (void *)&g_encodedCheatCode, (void *)&g_encodedCheatCode, (void *)&g_encodedCheatCode },
    "big cheat activated\000",
    { (void *)((char *)&g_encodedCheatCode + 40), (void *)((char *)&g_encodedCheatCode + 40), (void *)((char *)&g_encodedCheatCode + 40), (void *)((char *)&g_encodedCheatCode + 40) },
    "janes cheat activated\000\000\000",
    { (void *)((char *)&g_encodedCheatCode + 76), (void *)((char *)&g_encodedCheatCode + 76), (void *)((char *)&g_encodedCheatCode + 76), (void *)((char *)&g_encodedCheatCode + 76), (void *)((char *)&g_activeProfileCharacterSelections + 4), (void *)((char *)&g_activeProfileCharacterSelections + 4), (void *)((char *)&g_activeProfileCharacterSelections + 4), (void *)((char *)&g_activeProfileCharacterSelections + 4), (void *)((char *)&g_profileAchievementProgressRows + 137), (void *)((char *)&g_profileAchievementProgressRows + 137), (void *)((char *)&g_profileAchievementProgressRows + 137), (void *)((char *)&g_profileAchievementProgressRows + 137), (void *)((char *)&g_profileAchievementProgressRows + 287), (void *)((char *)&g_profileAchievementProgressRows + 287), (void *)((char *)&g_profileAchievementProgressRows + 287), (void *)((char *)&g_profileAchievementProgressRows + 287), (void *)((char *)&g_profileAchievementProgressRows + 437), (void *)((char *)&g_profileAchievementProgressRows + 437), (void *)((char *)&g_profileAchievementProgressRows + 437), (void *)((char *)&g_profileAchievementProgressRows + 437), (void *)((char *)&g_encodedCheatCode + 116), (void *)((char *)&g_encodedCheatCode + 132), (void *)((char *)&g_encodedCheatCode + 148), (void *)((char *)&g_encodedCheatCode + 164) },
    65536,
    0x10000000,
    { 0, 65281, 901, 4461300, 0, 0, 0, 0 },
    0x08000021,
    { 8, 65281 },
    (void *)((char *)&g_profileModeOneLabel + 168),
    { 4468892, 0, 0, 0, 0, 65601, 40, 65281 },
    (void *)&g_unlockedLevelResultLabel,
    { 4468892, 4452444, 0, 0, 0, 65601, 15, 65281 },
    (void *)&g_unlockedLevelResultLabel,
    { 4468892, 4452464, 0, 0, 0, 65601, 35, 65281 },
    (void *)((char *)&g_profileSecondConfirmationLabel + 12),
    { 4468892, 0, 4452484, 0 },
    (void *)((char *)&g_profileSelectionResources + 16),
    { 327680, 4452336, 0, 4466204, 4452352, 262144, 0, 0, 1, 1, 1, 1, 1, 1, 1, -1, 1, 1, 1, -1, 0, 0, 0, 0, 0, 0, 0, 0 },
};
#endif
#if defined(VERSION_US)
RestEncodedInserttextentrycharacterEncodedHalfwordsLayout471 k_EncodedInserttextentrycharacterEncodedHalfwords = {
    { 0, 0, 0, 0, 0, 0 },
    (void *)&g_encodedCheatCode,
    "big cheat activated\000",
    (void *)((char *)&g_encodedCheatCode + 28),
    "janes cheat activated\000\000\000",
    (void *)((char *)&g_encodedCheatCode + 52),
    "Proj",
    { (void *)((char *)&g_activeProfileCharacterSelections + 4), (void *)((char *)&g_profileAchievementProgressRows + 137), (void *)((char *)&g_profileAchievementProgressRows + 287), (void *)((char *)&g_profileAchievementProgressRows + 437), (void *)((char *)&g_encodedCheatCode + 84), (void *)((char *)&g_encodedCheatCode + 88), (void *)((char *)&g_encodedCheatCode + 92), (void *)((char *)&g_encodedCheatCode + 96) },
    65536,
    0x10000000,
    { 0, 65281, 901, 4457548, 0, 0, 0, 0 },
    0x08000021,
    { 8, 65281 },
    (void *)((char *)&g_profileModeOneLabel + 56),
    { 4465108, 0, 0, 0, 0, 65601, 40, 65281 },
    (void *)&g_unlockedLevelResultLabel,
    { 4465108, 4448796, 0, 0, 0, 65601, 15, 65281 },
    (void *)&g_unlockedLevelResultLabel,
    { 4465108, 4448816, 0, 0, 0, 65601, 35, 65281 },
    (void *)((char *)&g_profileSecondConfirmationLabel + 4),
    { 4465108, 0, 4448836, 0 },
    (void *)((char *)&g_profileSelectionResources + 16),
    { 327680, 4448688, 0, 4462436, 4448704, 262144, 0, 0, 1, 1, 1, 1, 1, 1, 1, -1, 1, 1, 1, -1, 0, 0, 0, 0, 0, 0, 0, 0 },
};
#endif
#endif

#if defined(VERSION_US_REV1)
void *g_EncodedInserttextentrycharacterWords2[7] = {
    0, 0, 0, 0,
    0, 0, g_EncodedInserttextentrycharacterWords2,
};
#endif
