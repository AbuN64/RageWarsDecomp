#ifndef COMMON_SHARED_OPTIONSSCREEN_H
#define COMMON_SHARED_OPTIONSSCREEN_H
#include "COMMON/GAMEPLAY_SETTINGS.H"
#include "COMMON/SHARED_GAMESLOT.H"

#include "COMMON/ITEMRECAT20V1.H"
#include "TYPES.H"
#include "MENU/OPTIONS_TYPES.H"

typedef struct Shared_MenuReply Shared_MenuReply;
struct Shared_MenuReply {
    s32 value;
    s32 ready;
};
typedef struct Shared_MenuObject Shared_MenuObject;
struct Shared_MenuObject {
    u8 reservedBeforePlayerSettings[0x1310];
    Shared_PlayerSettingsRecord playerSettings[8];
    u8 reservedWord;
    u8 language;
    u8 reservedTail[0x2E];
};
typedef struct Shared_MenuData Shared_MenuData;
struct Shared_MenuData {
    union {
        struct {
            u8 reservedBeforeTransientPlayers[0x20];
            void *transientPlayers;
            u8 reservedBeforeResetMode[0xC];
            s32 sessionOptionResetMode;
            u8 reservedAfterResetMode[0x14];
            Shared_MenuObject object;
            s32 stage;
            u32 reservedBeforePause[6];
            s32 pause;
        };
        struct {
            u8 reserved0000[0x5DC];
            struct MenuCreationOwnerView dialogOwner; /* g_matchEndingTeamWheelClose */
            u8 reserved05F2[0x1288 - 0x5DC - sizeof(struct MenuCreationOwnerView)];
            Shared_Game game; /* g_gameSettings; language at root + 0x1809 */
        };
    };
};

#include "COMMON/SHAREDPLAYER.H"
typedef void (*Shared_ContextCallback)(void *);
typedef void (*Shared_MenuVoidCallback)(void);
struct SharedTrackObject;
#include "COMMON/KEYRECAT1C.H"
typedef struct Shared_MenuContext Shared_MenuContext;
struct Shared_MenuContext {
    void *owner;
    void *resource;
    u32 unknown08;
    Shared_MenuVoidCallback onClose;
    Shared_MenuVoidCallback callback10;
    u32 reservedWord1;
    struct SharedTrackObject *target;
    f32 time;
    f32 time20;
    f32 time24;
    f32 clipStart;
    f32 clipEnd;
    f32 start;
    f32 end;
    s32 active;
    s32 state3C;
    u32 sequenceStarted;
    s32 initialized44;
    s32 closed;
    s32 pendingStartFlag;
    s32 sequenceAdvanceRequested;
    s32 pending;
    s32 pendingTrackId;
    u32 noPendingTrackRequests;
    u32 fadeRequested;
    f32 fade;
    TrackResourceEntry spec; /* 0x68..0xB3 */
    s32 sequenceEndRequested;
    s32 mode; /* 0xB8 */
    u32 reservedElements[7];
    s32 targetD8;
    s32 resourceDC;
    s32 requestE0;
    Shared_ContextCallback callbackE4;
    Shared_MenuVoidCallback callbackE8;
    u32 reservedWord2;
    CVector3 position;
    f32 yaw;
    f32 response; /* 0x100 */
    s32 loopBounds[5];
    char messages[5][0x28];
    s32 messageCount;
};
/* The context the camera and menu code works on. */
extern Shared_MenuContext *g_cinemaSequenceState;
#endif
