#ifndef OVLGAME_OVLGAME_INITIALIZEPLAYERPOOL_H
#define OVLGAME_OVLGAME_INITIALIZEPLAYERPOOL_H
#include "TYPES.H"
struct PlayerPoolModeStateView {
    char pad0[0x74];
    s32 fragTagMode;
    char pad74[0x84 - 0x74 - sizeof(s32)];
    s32 ctfMode;
};
struct PlayerSpawnActivationActor {
    char pad[0x2E8];
    char firstEffect[368]; /* 0x2E8 */
    char secondEffect[384]; /* 0x458 */
    struct Part *part;
};
/* A 0x44-byte record: three leading words, two lists of 0x16DC/0x16E0-linked nodes, four trailing words. */
struct MenuPlayerPoolRecord {
    s32 m_pmePlayers;
    s32 m_Players;
    s32 word8;
    IntrusiveList m_FreeList;
    IntrusiveList m_ActiveList;
    s32 m_bEnteredAdonSaveLocation;
    s32 m_bAdonSaveLocationMenuEnabled;
    s32 m_TeamTriangleTimer;
    s32 m_TriangleSpin;
};
#endif
