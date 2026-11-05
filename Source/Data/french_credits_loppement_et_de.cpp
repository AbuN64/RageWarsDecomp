#if defined(VERSION_EU)

#include "Ai/Weapon/weapon.h"


#include "Common/gameplay_camera.h"


#include "include_asm.h"


#include "Common/shared_gameslot.h"


#include "Common/gameplay_transition.h"


#include "Common/pickup_entry_tables.h"


#include "types.h"


#include "Common/weapon_screen_message_operations.h"


#include "Insthdr/insthdr_getactorshadowradius.h"


#include "Pickup/pickup_cancollect.h"


#include "Pickup/pickup_definitions.h"


#include "Pickup/pickup_applyammobundle.h"


#include "Pickup/pickup_trailing_text.h"


#include "Player_updateplayercamera/player_updateplayercamera.h"


#include "Common/animationtriggerdefinition.h"


#include "Ai/weaponselect.h"


#include "Common/ballisticparams.h"


#include "Common/resourceloadstate.h"


#include "Engine/Audio/channel.h"


#include "Common/sharedplayer.h"


#include "Common/menu_abbdc_versions.h"


#include "Common/menu_match_globals.h"


#include "Ui/X_files/x_plus.h"


#include "Common/level_actor.h"


#include "Common/vector4f.h"


#include "Common/Lone/g_languageindex.h"


#include "Common/viewflags.h"


#include "Common/playerprofiles.h"


#include "Common/aiprofile.h"


#include "Common/frag_tag_scores.h"


#include "System/sound_context_music_and_voice_control.h"


#include "itemmenu.h"


#include "World/playerprofile.h"


#include "Common/triple.h"


#include "Common/round_state_variants.h"


#include "Common/runtime_declarations.h"


#include "Common/level_spawn.h"


#include "Pickup/pickup_applyspecialpickup_symbols.h"


#include "Common/track_requesttrackbykey.h"


#include "Common/world.h"


#include "pickup.h"


#include "Engine/session.h"


#include "Menu/Items/Scene/scene_setlevelactorstatebit.h"


#include "Ai/player_death_playerai.h"


#include "Common/response.h"


#include "Data/rest_source_records.h"


#include "Data/Common/g_pickuppowerupdefinitions.h"


#include "Common/Lone/weapon_locked_notice_text.h"


#include "Data/Common/g_pickupweapondefinitions.h"


#include "Data/Common/g_pickuphealthdefinitions.h"


#include "Pickup/g_pickuphealthdefinitions_symbols.h"


#include "Data/Common/g_pickupspecialdefinitions.h"

#if !(defined(VERSION_EU) || defined(VERSION_EU_X))
#include "types.h"
#endif

#if !(defined(VERSION_EU) || defined(VERSION_EU_X))
#include "Common/menu_match_globals.h"
#endif

#if defined(VERSION_DE)
#include "types.h"
#endif


typedef struct Shared_MenuAmountColumn Shared_MenuAmountColumn;


struct Shared_MenuAmountColumn {
    s32 value;
    u8 rest[396];
};


typedef struct SpecialPickupRecipientView SpecialPickupRecipientView;


struct SpecialPickupRecipientView {
    char pad0[0x8];
    CVector3 position; /* passed by value to SoundElement_PlaySoundAtPosition */
    char pad14[0x4];
    struct SpecialPickupActorDefinitionView * definition;
    char pad1C[0x5B8];
    s32 playerIndex;
    struct SpecialPickupPlayerOptions * options;
    void * messageCamera;
    char pad5E0[0x4];
    s32 health;
    char pad5E8[0xC];
    u16 firstBonusCount;
    u16 secondBonusCount;
    u16 ammoBonusCount;
    char pad5FA[0xBEA];
    f32 pickupDelay;
    char pad11E8[0x44];
    s32 reactionFlags;
    f32 reactionDuration;
    char pad1234[0x4];
    s32 reactionTarget;
    u8 tintRed;
    u8 tintGreen;
    u8 tintBlue;
    char pad123F[0x1];
    f32 tintAlpha;
    f32 rightAxisValue;
    char pad1248[0x198];
    s32 pickupExpiryKind;
};


typedef struct SpecialPickupDefinition SpecialPickupDefinition;


struct SpecialPickupDefinition {
    u8 ** text;
    s16 id;
    s16 sound;
    s16 event;
    char padA[0x2];
};


typedef struct SpecialPickupActorDefinitionView SpecialPickupActorDefinitionView;


struct SpecialPickupActorDefinitionView {
    char pad0[0xC];
    s16 levelProgressId;
};


typedef struct SpecialPickupMatchModeView SpecialPickupMatchModeView;


struct SpecialPickupMatchModeView {
    char pad0[0x24];
    s32 teamMode;
    char pad28[0x2C];
    s32 flagPickupEnabled;
    char pad58[0x1C];
    s32 flagReturnState;
    char pad78[0x8];
    s32 flagCarried;
    s32 flagDropped;
};


typedef struct SpecialPickupPlayerOptions SpecialPickupPlayerOptions;


struct SpecialPickupPlayerOptions {
    char pad0[0x8F];
    u8 carryingFlag;
    u8 flagReturned;
    char pad91[0x1];
    u8 team;
};


typedef struct SpecialPickupLinkedPlayerView SpecialPickupLinkedPlayerView;


struct SpecialPickupLinkedPlayerView {
    char pad0[0x5D8];
    struct SpecialPickupLinkedPlayerOptions * options;
    void * messageCamera;
    char pad5E0[0xBFC];
    f32 bonusDuration;
    char pad11E0[0x4C];
    s32 reactionFlags;
    char pad1230[0x4B0];
    struct SpecialPickupLinkedPlayerView * nextPlayer;
    char pad16E4[0x4];
};


typedef struct SpecialPickupLinkedPlayerOptions SpecialPickupLinkedPlayerOptions;


struct SpecialPickupLinkedPlayerOptions {
    char pad0[0x92];
    u8 team;
};


typedef struct Shared_FullPlayerMenuGlobals Shared_FullPlayerMenuGlobals;


struct Shared_FullPlayerMenuGlobals {
    struct SpecialPickupLinkedPlayerView * entries; /* player records */
    s32 count;
    u8 pad8[0x14];
    struct SpecialPickupLinkedPlayerView * players; /* active players, linked through nextPlayer */
    u8 pad20[0x24];
    union {
        MenuMatchGlobals match; /* g_frontendScreenStatus */
        struct {
            u8 pad0[0x1818];
            SpecialPickupMatchModeView modes; /* g_matchRoundCounters */
        } view;
    } game __attribute__((packed, aligned(4))); /* The menu owner follows the player list directly, so it is not aligned to eight bytes. */
};


typedef Shared_MenuBonusColumn MenuBonusColumn;


typedef Shared_MenuAmountColumn MenuAmountColumn;


typedef Shared_FullPlayerMenuGlobals FullPlayerMenuGlobals;


typedef struct PowerupEntry {
    u8 **text; /* 0x0: pickup message, one per language */
    s16 id; /* 0x4: item id looked up by Pickup_DispatchHandler */
    s16 sound; /* 0x6 */
    s16 event; /* 0x8 */
    s16 reservedA; /* 0xA */
    s16 slot; /* 0xC: row in Player.actions */
    s16 ammoSlot; /* 0xE: Player.ammo index for Player_AddAmmo_PickupApplyspecialpickup */
    s16 ammoCount; /* 0x10 */
    s32 (*handle)(struct Player *player, struct PowerupEntry *entry); /* 0x14 */
} PowerupEntry;

#if !(defined(VERSION_EU) || defined(VERSION_EU_X))
typedef struct PickupPowerupPayloadView PickupPowerupPayloadView;
#endif

#if !(defined(VERSION_EU) || defined(VERSION_EU_X))
typedef struct EffectAmount { char pad[0xC]; f32 amount; } EffectAmount;
#endif

#if !(defined(VERSION_EU) || defined(VERSION_EU_X))
struct PickupPowerupPayloadView { char pad[0x14]; EffectAmount payload; };
#endif

char g_frenchCreditsLoppementEtDe[16] = "loppement et de";
#endif

#if defined(VERSION_EU_X)

#include "Ai/Weapon/weapon.h"


#include "Common/gameplay_camera.h"


#include "include_asm.h"


#include "Common/shared_gameslot.h"


#include "Common/gameplay_transition.h"


#include "Common/pickup_entry_tables.h"


#include "types.h"


#include "Common/weapon_screen_message_operations.h"


#include "Insthdr/insthdr_getactorshadowradius.h"


#include "Pickup/pickup_cancollect.h"


#include "Pickup/pickup_definitions.h"


#include "Pickup/pickup_applyammobundle.h"


#include "Pickup/pickup_trailing_text.h"


#include "Player_updateplayercamera/player_updateplayercamera.h"


#include "Common/animationtriggerdefinition.h"


#include "Ai/weaponselect.h"


#include "Common/ballisticparams.h"


#include "Common/resourceloadstate.h"


#include "Engine/Audio/channel.h"


#include "Common/sharedplayer.h"


#include "Common/menu_abbdc_versions.h"


#include "Common/menu_match_globals.h"


#include "Ui/X_files/x_plus.h"


#include "Common/level_actor.h"


#include "Common/vector4f.h"


#include "Common/Lone/g_languageindex.h"


#include "Common/viewflags.h"


#include "Common/playerprofiles.h"


#include "Common/aiprofile.h"


#include "Common/frag_tag_scores.h"


#include "System/sound_context_music_and_voice_control.h"


#include "itemmenu.h"


#include "World/playerprofile.h"


#include "Common/triple.h"


#include "Common/round_state_variants.h"


#include "Common/runtime_declarations.h"


#include "Common/level_spawn.h"


#include "Pickup/pickup_applyspecialpickup_symbols.h"


#include "Common/track_requesttrackbykey.h"


#include "Common/world.h"


#include "pickup.h"


#include "Engine/session.h"


#include "Menu/Items/Scene/scene_setlevelactorstatebit.h"


#include "Ai/player_death_playerai.h"


#include "Common/response.h"


#include "Data/rest_source_records.h"


#include "Data/Common/g_pickuppowerupdefinitions.h"


#include "Common/Lone/weapon_locked_notice_text.h"


#include "Data/Common/g_pickupweapondefinitions.h"


#include "Data/Common/g_pickuphealthdefinitions.h"


#include "Pickup/g_pickuphealthdefinitions_symbols.h"


#include "Data/Common/g_pickupspecialdefinitions.h"

#if !(defined(VERSION_EU) || defined(VERSION_EU_X))
#include "types.h"
#endif

#if !(defined(VERSION_EU) || defined(VERSION_EU_X))
#include "Common/menu_match_globals.h"
#endif

#if defined(VERSION_DE)
#include "types.h"
#endif


typedef struct Shared_MenuAmountColumn Shared_MenuAmountColumn;


struct Shared_MenuAmountColumn {
    s32 value;
    u8 rest[396];
};


typedef struct SpecialPickupRecipientView SpecialPickupRecipientView;


struct SpecialPickupRecipientView {
    char pad0[0x8];
    CVector3 position; /* passed by value to SoundElement_PlaySoundAtPosition */
    char pad14[0x4];
    struct SpecialPickupActorDefinitionView * definition;
    char pad1C[0x5B8];
    s32 playerIndex;
    struct SpecialPickupPlayerOptions * options;
    void * messageCamera;
    char pad5E0[0x4];
    s32 health;
    char pad5E8[0xC];
    u16 firstBonusCount;
    u16 secondBonusCount;
    u16 ammoBonusCount;
    char pad5FA[0xBEA];
    f32 pickupDelay;
    char pad11E8[0x44];
    s32 reactionFlags;
    f32 reactionDuration;
    char pad1234[0x4];
    s32 reactionTarget;
    u8 tintRed;
    u8 tintGreen;
    u8 tintBlue;
    char pad123F[0x1];
    f32 tintAlpha;
    f32 rightAxisValue;
    char pad1248[0x198];
    s32 pickupExpiryKind;
};


typedef struct SpecialPickupDefinition SpecialPickupDefinition;


struct SpecialPickupDefinition {
    u8 ** text;
    s16 id;
    s16 sound;
    s16 event;
    char padA[0x2];
};


typedef struct SpecialPickupActorDefinitionView SpecialPickupActorDefinitionView;


struct SpecialPickupActorDefinitionView {
    char pad0[0xC];
    s16 levelProgressId;
};


typedef struct SpecialPickupMatchModeView SpecialPickupMatchModeView;


struct SpecialPickupMatchModeView {
    char pad0[0x24];
    s32 teamMode;
    char pad28[0x2C];
    s32 flagPickupEnabled;
    char pad58[0x1C];
    s32 flagReturnState;
    char pad78[0x8];
    s32 flagCarried;
    s32 flagDropped;
};


typedef struct SpecialPickupPlayerOptions SpecialPickupPlayerOptions;


struct SpecialPickupPlayerOptions {
    char pad0[0x8F];
    u8 carryingFlag;
    u8 flagReturned;
    char pad91[0x1];
    u8 team;
};


typedef struct SpecialPickupLinkedPlayerView SpecialPickupLinkedPlayerView;


struct SpecialPickupLinkedPlayerView {
    char pad0[0x5D8];
    struct SpecialPickupLinkedPlayerOptions * options;
    void * messageCamera;
    char pad5E0[0xBFC];
    f32 bonusDuration;
    char pad11E0[0x4C];
    s32 reactionFlags;
    char pad1230[0x4B0];
    struct SpecialPickupLinkedPlayerView * nextPlayer;
    char pad16E4[0x4];
};


typedef struct SpecialPickupLinkedPlayerOptions SpecialPickupLinkedPlayerOptions;


struct SpecialPickupLinkedPlayerOptions {
    char pad0[0x92];
    u8 team;
};


typedef struct Shared_FullPlayerMenuGlobals Shared_FullPlayerMenuGlobals;


struct Shared_FullPlayerMenuGlobals {
    struct SpecialPickupLinkedPlayerView * entries; /* player records */
    s32 count;
    u8 pad8[0x14];
    struct SpecialPickupLinkedPlayerView * players; /* active players, linked through nextPlayer */
    u8 pad20[0x24];
    union {
        MenuMatchGlobals match; /* g_frontendScreenStatus */
        struct {
            u8 pad0[0x1818];
            SpecialPickupMatchModeView modes; /* g_matchRoundCounters */
        } view;
    } game __attribute__((packed, aligned(4))); /* The menu owner follows the player list directly, so it is not aligned to eight bytes. */
};


typedef Shared_MenuBonusColumn MenuBonusColumn;


typedef Shared_MenuAmountColumn MenuAmountColumn;


typedef Shared_FullPlayerMenuGlobals FullPlayerMenuGlobals;


typedef struct PowerupEntry {
    u8 **text; /* 0x0: pickup message, one per language */
    s16 id; /* 0x4: item id looked up by Pickup_DispatchHandler */
    s16 sound; /* 0x6 */
    s16 event; /* 0x8 */
    s16 reservedA; /* 0xA */
    s16 slot; /* 0xC: row in Player.actions */
    s16 ammoSlot; /* 0xE: Player.ammo index for Player_AddAmmo_PickupApplyspecialpickup */
    s16 ammoCount; /* 0x10 */
    s32 (*handle)(struct Player *player, struct PowerupEntry *entry); /* 0x14 */
} PowerupEntry;

#if !(defined(VERSION_EU) || defined(VERSION_EU_X))
typedef struct PickupPowerupPayloadView PickupPowerupPayloadView;
#endif

#if !(defined(VERSION_EU) || defined(VERSION_EU_X))
typedef struct EffectAmount { char pad[0xC]; f32 amount; } EffectAmount;
#endif

#if !(defined(VERSION_EU) || defined(VERSION_EU_X))
struct PickupPowerupPayloadView { char pad[0x14]; EffectAmount payload; };
#endif

char g_frenchCreditsLoppementEtDe[16] = "loppement et de";
#endif
