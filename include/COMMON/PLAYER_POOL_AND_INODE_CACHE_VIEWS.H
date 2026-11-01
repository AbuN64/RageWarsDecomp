#ifndef COMMON_PLAYER_POOL_AND_INODE_CACHE_VIEWS_H
#define COMMON_PLAYER_POOL_AND_INODE_CACHE_VIEWS_H
#include "TYPES.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/ITEMRECAT20V1.H"


struct __OSInodeCache;
struct __OSInodeCache {
    __OSInode inode;
    u8 bank;
    u8 map[256];
};

typedef struct CPlayerPool_t CPlayerPool;
/* Player_ResetMenuPool_GameSession clears0x44 and initializes lists+C,+20. */
struct CPlayerPool_t {
    void *m_pmePlayers;
    char *m_Players;
    s32 count;
    IntrusiveList m_FreeList;
    IntrusiveList m_ActiveList;
    s32 m_bEnteredAdonSaveLocation, m_bAdonSaveLocationMenuEnabled, m_TeamTriangleTimer, m_TriangleSpin;
};


extern void __osContGetInitData_pfs(u8 *valid, ControllerInitStatusBytes *data);

struct PlayerPoolModeStateView;
typedef struct PlayerPoolModeStateView PlayerPoolModeStateView;


struct __OSPackId;
struct __OSPackId {
    u32 repaired;
    u32 random;
    u64 serial_mid;
    u64 serial_low;
    u16 deviceid;
    u8 banks;
    u8 version;
    u16 checksum;
    u16 inverted_checksum;
};


struct __OSInodeCache;
typedef struct __OSInodeCache __OSInodeCache;



struct Body;
struct Character;
struct Controller;
struct Controls;
struct Ctrl;
struct Held;
struct Mode;
struct Model;
struct Mount;
struct Profile;
struct Rider;
struct Settings;
struct Shared_Body;
struct Shared_Hud;
struct Shared_Model;
struct Shared_Profile;
struct Shared_StateInfo;
struct Shared_Voice;
struct StateInfo;
struct TeamInfo;
struct View;
struct PlayerCharacterKindView;

extern u16 Pfs_SumBytes(u8 *bytes, s32 count);

struct PlayerSettingsRecordView;
typedef struct PlayerSettingsRecordView PlayerSettingsRecordView;

struct __OSPackId;
typedef struct __OSPackId __OSPackId;

struct PlayerSettingsRecordView;
struct PlayerSettingsRecordView {
    char pad0[0x7F];
    signed char slot;
    char pad80;
    u8 team;
    char pad82[0xF];
    u8 computer;
};



struct Body;
struct Character;
struct Controller;
struct Controls;
struct Ctrl;
struct Held;
struct Mode;
struct Model;
struct Mount;
struct Profile;
struct PlayerSettingsRecordView;
struct Rider;
struct Settings;
struct Shared_Body;
struct Shared_Hud;
struct Shared_Model;
struct Shared_Profile;
struct Shared_StateInfo;
struct Shared_Voice;
struct StateInfo;
struct TeamInfo;
struct View;


struct PlayerPoolModeStateView;

struct CPlayerPool_t;


struct IntPair;

struct PlayerSpawnActivationActor;
struct Part;




struct MenuPlayerPoolRecord;

extern short g_playerStateDialogGroups[];

s32 Control_IsSnapshotActive(void);

extern s32 Pfs_ComputeIdChecksums(u16 *ptr, u16 *csum, u16 *icsum);
extern s32 __osGetId(OSPfs *pfs);
#endif
