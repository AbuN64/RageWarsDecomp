#ifndef SYSTEM_TIMED_EFFECT_AND_ITEM_MENU_VIEWS_H
#define SYSTEM_TIMED_EFFECT_AND_ITEM_MENU_VIEWS_H
#include "COMMON/OBJRECAT18V6.H"
#include "COMMON/ITEMRECAT20V1.H"
struct StateFrontendScrollResultsBackward {
    char pad[0xE8];
    s32 count;
};
struct EffectColorContribution {
    char pad0[0x14];
    f32 auxiliaryAlpha;
    char pad14[0x24 - 0x14 - sizeof(f32)];
    f32 alpha;
    char pad24[0x34 - 0x24 - sizeof(f32)];
    f32 red;
    char pad34[0x38 - 0x34 - sizeof(f32)];
    f32 green;
    char pad38[0x3C - 0x38 - sizeof(f32)];
    f32 blue;
};
struct TimedEffectCallbackView {
    char pad0[0x8];
    s32 countdown;
    char pad8[0xC - 0x8 - sizeof(s32)];
    f32 interval;
    char padC[0x10 - 0xC - sizeof(f32)];
    s32 remainingCalls;
    char pad10[0x14 - 0x10 - sizeof(s32)];
    s32 callbackData;
    char pad14[0x18 - 0x14 - sizeof(s32)];
    s32 callback;
};
struct ToggleMenuPlayerInputView {
    char pad0[0x5DC];
    struct View *view; /* 0x5DC: viewport owner used by the toggle-menu renderer */
    char pad5E0[0x6AC - 0x5E0];
    s32 held;
    s32 pressed;
};

struct GameSprite {
    s32 format;
    char *data;
    s32 primaryData;
    s32 secondaryData;
    f32 width;
    f32 height;
    f32 extentX;
    f32 extentY;
    f32 step;
};
typedef struct GameSprite GameSprite;
struct ToggleMenu {
    u8 state;
    u8 timer;
    MenuItem items[4];
    u16 selected;
    s16 blink;
    s32 frame;
};
struct AttachedEffectPoolView {
    char pad0[0x7588];
    char attachedEffectLists;
    char pad7588[0x7594 - 0x7588 - sizeof(char)];
    void * activeAttachedEffects;
};
struct ItemMenuToggleStateView {
    unsigned char padding_0[4];
    s32 state;
    unsigned char padding_8[16];
    s16 transitionStep;
    unsigned char padding_1A[2];
    s32 transitionFrame;
    f32 value;
    s32 extra;
    f32 restoreValue;
    s32 restoreExtra;
};
struct AttachedEffectTimerView {
    char pad0[0x4];
    void * next;
    char pad4[0x8 - 0x4 - sizeof(void*)];
    f32 remainingTime;
    char pad8[0xC - 0x8 - sizeof(f32)];
    f32 interval;
    char padC[0x10 - 0xC - sizeof(f32)];
    s32 remainingCalls;
};
struct ItemMenuCursorState {
    EntryItemMenuAdvanceSelection entries[4];
    char padE0[0xE4 - 0xE0];
    u16 cursor;
};
struct AttachedEffectDetachState {
    u8 pad0[8];
    EffectBoneNode *node;
    u8 padC[0x10];
    void *object;
    u8 pad20[4];
    f32 value;
    u8 pad28[0x14];
    u32 flags;
};
struct EffectCallbackEntryView {
    unsigned char padding_0[24];
    void (*callback)(void *);
};
extern void Fx_AccumulateEffectComponents(EffectColorContribution *contribution);
extern void Fx_AddTimedCallback(s32 ownerAddress, s32 callback, s32 callbackData, s32 remainingCalls, f32 interval);
extern void Fx_ClampScalarRange(f32 *scalarPointer);
#endif
