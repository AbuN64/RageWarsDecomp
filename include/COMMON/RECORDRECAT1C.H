#ifndef COMMON_RECORDRECAT1C_H
#define COMMON_RECORDRECAT1C_H
#include "TYPES.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/ITEMRECAT20V1.H"
struct Body;
struct Character;
struct Controller;
struct Controls;
struct Ctrl;
struct Held;
struct Mode;
struct Model;
struct Mount;
struct PakStatusProfile;
struct Record;
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

struct MenuPakBeginProfileLoad;
typedef struct MenuPakBeginProfileLoad MenuPakBeginProfileLoad;


struct DialogPlayerState;
struct RenderBufferResources;


struct OwnerPakBeginProfileLoad;
struct OwnerPakBeginProfileLoad {
    char pad0[0x328];
    s32 flags;
};
struct MenuPakBeginProfileLoad;
struct OwnerPakBeginProfileLoad;


struct MenuPakConfirmProfileOrDeleteNote;

struct RenderBufferResources;

struct RenderBufferResources;

struct ControllerButtonFlagsView;


struct DialogPlayerState;


struct DialogPlayerState;

struct PakRecord;
struct PakRecord {
    u8 present;
    char pad[7];
    char pak[104];
};


struct MenuPakConfirmProfileOrDeleteNote;
typedef struct MenuPakConfirmProfileOrDeleteNote MenuPakConfirmProfileOrDeleteNote;

struct PakRecord;
typedef struct PakRecord PakRecord;

extern int Note_AllocateRenderBuffers(struct RenderBufferResources * record);
#endif
