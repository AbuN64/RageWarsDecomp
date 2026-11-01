#ifndef COMMON_PLAYERRECAT64E_H
#define COMMON_PLAYERRECAT64E_H
#include "TYPES.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/AIPROFILE.H"


struct PlayerItemInventoryView;
struct PlayerItemInventoryView {
    char pad[0x644];
    u8 flags[9];
    u8 count64D;
    u8 count64E;
};

struct HolderMultiIsPlayerItemAvailable;
struct PlayerItemInventoryView;

struct Flagged;
struct Flagged {
    u8 pad0[0x58];
    u32 flags;
};
struct Flagged;
struct MultiplayerAvailabilityItem;


struct ItemDef;
struct ItemDef {
    char pad[0x20];
    s16 type;
    s16 index;
};

struct ItemDef;
struct MultiplayerItemAvailabilityView;


struct ControllerPakDialogContext;
typedef struct ControllerPakDialogContext ControllerPakDialogContext;

struct GamePlayerListView;

struct PlayerFrontendCountOpenPlayerSlots;

struct ControllerPortView;
typedef struct ControllerPortView ControllerPortView;

struct ControllerPakDialogContext;

struct MultiplayerAvailabilityItem;
typedef struct MultiplayerAvailabilityItem MultiplayerAvailabilityItem;


struct Shared_PakMenu;




extern const f32 g_playerItemAlphaScale[2];
extern const f32 g_playerItemDisabledAlphaScale;

extern const char g_debugVariableValueFormat[];
extern char g_debugVariableNamedFormat[];
extern const char g_debugVariableUnnamedFormat[];
extern char g_debugVariableValueBuffer[];
extern char g_debugVariableLabelBuffer[];
#endif
