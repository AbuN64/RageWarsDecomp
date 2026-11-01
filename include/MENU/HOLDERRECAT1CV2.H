#ifndef MENU_HOLDERRECAT1CV2_H
#define MENU_HOLDERRECAT1CV2_H
#include "TYPES.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/TEXTLAYERMETRICS.H"
/* A player's option record: the record an owner holds at 0x5D8, or the defaults g_playerPartnerNameFallback. */
struct PlayerOptions;
struct PlayerOptions {
    char text[121]; /* +0x00: shown as the name when there is no owner */
    u8 option79;
    u8 option7A;
    s8 option7B;
    u8 option7C;
    u8 option7D;
    u8 option7E;
    char pad7F[0x82 - 0x7F];
    u8 flag82;
};
extern struct PlayerOptions g_playerPartnerNameFallback;
struct PlayerSettingsTextHolder;
struct PlayerSettingsOwnerView;
struct PlayerSettingsTextHolder {
    char pad[0x1C];
    struct PlayerSettingsOwnerView *owner;
};
struct SceneMaskLabelItem;
struct SceneMaskLabelItem {
    char pad0[8];
    u32 flags;
    char padC[8];
    void *table;
};

struct SceneMaskLabelItem;
typedef struct SceneMaskLabelItem SceneMaskLabelItem;

#if defined(VERSION_DE) || defined(VERSION_US) || defined(VERSION_US_REV1)
s32 Items_FormatPackedGameOption(struct LayeredText *field);
#endif

extern u8 *g_packedGameOptionZeroText[];
extern u8 *g_packedGameOptionSixteenText[];
extern char g_fmtDec2Pad[];
#endif
