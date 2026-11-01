#ifndef COMMON_ROUND_STATE_VARIANTS_H
#define COMMON_ROUND_STATE_VARIANTS_H
#include "TYPES.H"
#include "COMMON/MENU_MATCH_GLOBALS.H"
extern void TextLoad_ResetArtsendTextureState(void), Tengine_UpdateArtsendTexturePreview(void);
extern s32 g_roundExtraStateUsRev1;
extern f32 g_roundTransitionTimerUsRev1, g_roundTransitionTimerDe;
extern void InitFrontendMenus(void), Tsmos_InitializeEuropeanFrontend(void);
static inline void resetRoundExtra(void) {
#if defined(VERSION_US_REV1)
TextLoad_ResetArtsendTextureState();
#endif
}
static inline void clearRoundExtra(void) {
#if defined(VERSION_US_REV1)
g_roundExtraStateUsRev1 = 0;
#endif
}
static inline f32 roundTimerConstant(void) {
#if defined(VERSION_US_REV1)
return g_roundTransitionTimerUsRev1;
#else
return g_roundTransitionTimerDe;
#endif
}
/* Round transitions share the platform's player gate and localized messages. */
#if defined(VERSION_DE)
static inline void stopRoundPlatform(void) { InitFrontendMenus(); }
static inline s32 gameplayTransitionEnabled(u8 flag) { return flag; }
extern u8 *g_gameplayResetMessage, *g_pickupEffectClearedText;
static inline u8 *gameplayResetMessage(u8 language) { return g_gameplayResetMessage; }
static inline u8 *gameplayReleaseMessage(u8 language) { return g_pickupEffectClearedText; }
static inline void *gameplayMessageContext(s32 *context) { return &g_frontendScreenStatus; }
#elif defined(VERSION_EU)
static inline void stopRoundPlatform(void) { Tsmos_InitializeEuropeanFrontend(); }
static inline s32 gameplayTransitionEnabled(u8 flag) { return 1; }
extern u8 *g_gameplayResetMessagesEu[], *g_pickupEffectClearedText[];
static inline u8 *gameplayResetMessage(u8 language) { return g_gameplayResetMessagesEu[language]; }
static inline u8 *gameplayReleaseMessage(u8 language) { return g_pickupEffectClearedText[language]; }
static inline void *gameplayMessageContext(s32 *context) { return context; }
#elif defined(VERSION_EU_X)
static inline void stopRoundPlatform(void) { InitFrontendMenus(); }
static inline s32 gameplayTransitionEnabled(u8 flag) { return flag; }
extern u8 *g_gameplayResetMessagesEuX[], *g_pickupEffectClearedText[];
static inline u8 *gameplayResetMessage(u8 language) { return g_gameplayResetMessagesEuX[language]; }
static inline u8 *gameplayReleaseMessage(u8 language) { return g_pickupEffectClearedText[language]; }
static inline void *gameplayMessageContext(s32 *context) { return context; }
#else
static inline void stopRoundPlatform(void) { InitFrontendMenus(); }
static inline s32 gameplayTransitionEnabled(u8 flag) { return 1; }
extern u8 *g_gameplayResetMessage, *g_pickupEffectClearedText;
static inline u8 *gameplayResetMessage(u8 language) { return g_gameplayResetMessage; }
static inline u8 *gameplayReleaseMessage(u8 language) { return g_pickupEffectClearedText; }
static inline void *gameplayMessageContext(s32 *context) { return &g_frontendScreenStatus; }
#endif
#endif
