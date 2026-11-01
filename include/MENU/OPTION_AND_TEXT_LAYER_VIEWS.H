#ifndef MENU_OPTION_AND_TEXT_LAYER_VIEWS_H
#define MENU_OPTION_AND_TEXT_LAYER_VIEWS_H
#include "TYPES.H"
struct MenuValueStepView {
    char pad0[0x20];
    int flags;
};
typedef struct MenuOption {
    u8 unobserved0[8];
    s32 flags;
    u8 unobservedC[8];
    s32 resource;
} MenuOption;
typedef struct MenuOptionFade {
    u8 unobserved0[48];
    f32 fade;
    f32 alpha;
    s32 reservedWord;
    s32 highlighted;
} MenuOptionFade;
struct TextLayerMetrics {
    int entryIndex;
    int width;
    int height;
    int rest[7];
};
struct ParamsPakAllocateMenu {
    char pad[0x14];
    s32 a;
    s32 pad18;
    s32 b;
    s32 c;
    s32 d;
};
struct MenuTemplateParameters {
    char pad[0x18];
    s32 a;
    s32 b;
    s32 c;
    s32 d;
};
struct CMenuFontInfo_t {
    s32 kind;
    char pad0[0x8];
    f32 scaleX;
    f32 scaleY;
    u8 shadowOffset;
    u8 color0;
    u8 color1;
    u8 color2;
    u8 color3;
    u8 color4;
    u8 color5;
    u8 pad1B;
};
struct Outer {
    char pad[0x14];
    struct MenuRules *inner;
};
struct MenuPreviewSelectionView {
    char reserved00[8];
    u32 flags; /* +0x08: 80440838 tests/sets 0x02000000. */
    char reserved0C[0x14];
    struct MenuCharacterPreviewState *state;
};
struct MenuCallbackListOwner {
    char pad[4];
    struct PakMenuVirtualNode *head;
};
struct ObjectPakDrawMenuCharacter {
    char pad[0x17];
    u8 character;
};
struct MenuCreationParameters {
    char pad[0x18];
    struct Dialog *list;
    s32 b;
    s32 c;
    s32 d;
};
struct StyledMenuTextEntryView {
    s32 index;
    char pad0[0x10];
    s32 x;
    char pad14[0x4];
    s32 y;
};
struct TextBoundsData {
    char pad0[0x29C];
    f32 width;
    f32 height;
    f32 x; /* 0x2A4 */
    f32 y; /* 0x2A8 */
};
struct TextBoundsFont {
    s32 kind;
    f32 width;
    f32 height;
    s32 rest[4];
};
struct TextBoundsRecord23 {
    char pad0[0x24];
    s32 width;
    s32 height;
};
#endif
