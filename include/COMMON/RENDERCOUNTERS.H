#ifndef COMMON_RENDERCOUNTERS_H
#define COMMON_RENDERCOUNTERS_H
#include "TYPES.H"
/* The session clock and round counters at g_matchRoundCounters. */
typedef struct CGameStatus_t {
    f32 m_GameTimeFifteenth, m_GameTimeSeconds, m_GameTimeMinutes, m_GameTimeHours; /* +0..+C: SetN64_AdvanceGameClock */
    f32 m_GameOverTimer; /* +0x10: Multi_DecreaseGameOverTimer counts it down by g_frameElapsedTime */
    f32 timeLimit;
    s32 mode;
    s32 elapsed;
    s32 state;
    s32 teams;
    s32 round;
    s32 scores[5];
    s32 counts[5];
    s32 m_bFragTagOn;
    s32 m_FragTagLimit; /* +0x58: Random_InitGameStatus_Rendercounters stores its third argument here */
    s32 m_FragTagPlayerPos;
    s32 m_FragTagPlayerChosen;
    s32 m_FragTagSelectionType; /* +0x64: SetN64_StartRound stores 3 */
    s32 m_FragTagFlipTimer; /* +0x68 */
    s32 mask;
    s32 m_nFragTagSkin; /* +0x70: lw in Player_BeginJump, lbu at +0x73 in Player_DrawTintedPlayer_Rendercounters */
    s32 m_FragTagMode;
    s32 m_bCTFOn;
    s32 otherLimit;
    s32 m_CTFPlayerWithFlag;
    s32 m_CTFMode;
    s32 first, m_bCreditsSeenOnce;
    s32 m_bPhoenixRoomActive; /* +0x90 */
    s32 m_EndOfGameWarp;
    s32 enabled; /* +0x98 */
    s32 m_nTalsetLives;
    s32 m_nBastilleShield; /* +0xA0 */
    s32 m_nBastilleTimer; /* +0xA4 */
    s32 humanWon;
    s32 transitionActive; /* +0xAC: SetN64_DrawSessionWithRoundTimeout */
} CGameStatus;
#endif
