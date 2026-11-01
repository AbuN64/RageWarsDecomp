#ifndef COMMON_OWNERRECAT8V1_H
#define COMMON_OWNERRECAT8V1_H
#include "TYPES.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/AIPROFILE.H"
struct MenuMultiUserOwnerView;
typedef struct MenuMultiUserOwnerView MenuMultiUserOwnerView;

struct NodeMenuCreateOverlayNode;
typedef struct NodeMenuCreateOverlayNode NodeMenuCreateOverlayNode;

extern s32 SmpOverlay_DispatchSlotEvent(void *actor, s32 event, s32 itemId, s32 value, s32 context);

struct RecordSmpButtonEnsureButtonWrapper;
struct RecordSmpButtonEnsureButtonWrapper {
    s32 words_00[3];
    s16 resource;
    u16 kind;
    s32 words_10[2];
    s16 width;
    s16 reservedWord;
    s32 words_1C[4];
    s32 fields_2C[5];
    s32 reservedWord1;
};

struct Mixer;
typedef struct Mixer Mixer;

struct sm_dlmultiuser_t;
typedef struct sm_dlmultiuser_t sm_dlmultiuser;

struct NodeMenuCreateOverlayNode;
struct MenuOverlayOwnerView;
struct NodeMenuCreateOverlayNode {
    s32 words_00[3];
    s16 tag;
    s16 kind;
    s8 alpha; /* 0x10 */
    u8 reserved11;
    s16 flags;
    s32 words_14[12];
    struct MenuOverlayOwnerView *owner;
    s32 value;
    s32 words_4C[8];
    s32 reservedWord;
};

struct MenuOverlayOwnerView {
    s32 words_00[2];
    struct NodeMenuCreateOverlayNode *root;
    s32 words_0C[14];
    struct NodeMenuCreateOverlayNode *overlay;
};

struct MenuCountedSlotValueArrayView;
struct MenuCountedSlotValueArrayView {
    char pad0[0x48];
    s32 count;
    char pad4C[0x5C - 0x4C];
    s32 values[1];
};

struct MenuOverlayTargetView;
struct MenuOverlayTargetView {
    char pad[0x12];
    u16 flags;
    char pad14[0x38 - 0x14];
    void *target;
};

struct MenuOverlayTargetView;

extern void SmpButton_WrapButtonWidget(s32 widgetId);

struct MenuSlotValueArrayView;
struct MenuSlotValueArrayView {
    char pad[0x5C];
    s32 values[1];
};

extern void SmpButton_RegisterButtonClass(void);

struct NodeMenuShowSlotById;
typedef struct NodeMenuShowSlotById NodeMenuShowSlotById;

struct Child;
struct Child {
    char pad[0x12];
    u16 flags;
    char pad14[0x34 - 0x14];
    void *target;
};

struct MenuCountedSlotValueArrayView;
extern s32 SmpOverlay_CountUsedSlots(struct MenuCountedSlotValueArrayView *object);

struct MenuOverlayOwnerView;
typedef struct MenuOverlayOwnerView MenuOverlayOwnerView;

struct MenuObjectSlotArrayView;
struct MenuActorInputView;
struct MenuObjectSlotArrayView {
    char pad[0x4C];
    struct MenuActorInputView *entries[1];
};

struct MenuListTargetView;
struct MenuListTargetView {
    char pad[0x12];
    u16 flags;
    char pad14[0x2C - 0x14];
    void *target;
};

struct NodeMenuShowSlotById;
struct NodeMenuShowSlotById {
    s32 words_00[3];
    s16 id;
};

struct sm_dlmultiuser_t;
struct sm_dlmultiuser_t {
    s32 words_00[17];
    void *root;
    s32 NUsers;
    NodeMenuShowSlotById *shown[4];
    s32 locked[4];
    s32 shared;
};

struct sm_dlmultiuser_t;
struct MenuMultiUserOwnerView;
struct MenuMultiUserOwnerView {
    s32 words_00[2];
    struct sm_dlmultiuser_t *context;
};

struct RecordSmpButtonWrapButtonWidget;
struct RecordSmpButtonWrapButtonWidget {
    s32 words_00[3];
    s16 resource;
    s16 kind;
    s32 words_10[2];
    s16 width;
    s16 reservedWord2;
    s32 words_1C[4];
    s32 fields_2C[5];
    s32 reservedWord3;
};

extern s32 SmpButton_DispatchButtonEvent(void *actor, s32 event, s32 itemId, s32 value, s32 context);

struct MenuListTargetView;

struct RecordSmpButtonWrapButtonWidget;
typedef struct RecordSmpButtonWrapButtonWidget RecordSmpButtonWrapButtonWidget;

extern void SmpOverlay_RegisterOverlayClass(void);

struct Mixer;
struct Mixer {
    char pad[0x4C];
    MenuActorInputView *handlers[4];
    int muted[4];
};

extern void SmpOverlay_ShowSlotNodeById(sm_dlmultiuser *context, s32 index, s32 id);

struct RecordSmpButtonEnsureButtonWrapper;
typedef struct RecordSmpButtonEnsureButtonWrapper RecordSmpButtonEnsureButtonWrapper;

struct Key;
struct MenuKeyListView;
struct SmpButtonOwnerView;
struct MenuKeyListView {
    char pad0[0x44];
    struct SmpButtonOwnerView *owner;
    struct Key entries[(0x110 - 0x48) / 20];
    s32 index;
    s32 count;
};

struct MenuTextTargetView;
struct MenuTextTargetView {
    char pad[0x12];
    u16 flags;
    char pad14[0x30 - 0x14];
    void *target;
};

struct MenuTextTargetView;

struct Child;
#endif
