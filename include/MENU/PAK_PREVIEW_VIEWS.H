#ifndef MENU_PAK_PREVIEW_VIEWS_H
#define MENU_PAK_PREVIEW_VIEWS_H
#include "TYPES.H"
struct PakControllerRequestView {
    char pad[0x20];
    struct ControllerButtonFlagsView *inner;
};
struct PakPreviewSelectionView {
    char pad[0xC];
    struct TargetPakDisablePreviewSelection *target;
};
struct PakChannelResultView {
    char pad[0x1C];
    s32 result;
    struct PakMenuSlot *inner;
};
/* The pak preview block g_controllerPakSnapshotPayload: a position, a packed value and the colour depth. */
struct PakPreview {
    char pad0[0xC];
    f32 x;
    f32 y;
    f32 z;
    char pad18[0x1C - 0x18];
    s32 value; /* shown shifted down eight bits */
    char pad20[0x24 - 0x20];
    s32 handle;
    char pad28[0x90 - 0x28];
    unsigned int depth;
};
struct PakSelectedPromptView {
    char pad[0x1C];
    s32 first;
    s32 second;
    void *resource;
};
#endif
