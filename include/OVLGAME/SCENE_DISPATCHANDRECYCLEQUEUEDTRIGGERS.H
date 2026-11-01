#ifndef OVLGAME_SCENE_DISPATCHANDRECYCLEQUEUEDTRIGGERS_H
#define OVLGAME_SCENE_DISPATCHANDRECYCLEQUEUEDTRIGGERS_H
#include "TYPES.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/TRIGGER_AND_FLOAT_VALUE_OPERATIONS.H"
#include "COMMON/LEVEL.H"
#include "COMMON/ENTRYRECAT0V3.H"
struct Level {
    char pad0[0x11C0];
    s32 counts[2];
    char pad11C8[8];
    ItemOvlSceneDispatchSelectedEntityKinds *items[2];
};
struct SceneFrameItemBank {
    s32 reservedWord;
    s32 count;
    struct SceneFrameItemReference items[1];
};
struct Ent {
    u32 kind;
    char pad4[0x24];
    f32 scaledValueA;
    char pad2C[4];
    f32 scaledValueB;
    f32 scaledValueC;
    char pad38[0x18];
    f32 scaledValueD;
    f32 scaledValueE;
    f32 scaledValueF;
    char pad5C[0x90];
    f32 scaledKind11ValueA;
    f32 scaledKind11ValueB;
};
struct ParticleEffectRelocationFrame {
    s32 reservedWord;
    s32 count;
    char pad8[0xC];
    ParticleEffectRelocationSlot slots[1];
};
struct PieceGroup {
    s32 reservedWord;
    s32 count;
    Piece pieces[1];
};
struct SceneTriggerQueueOwner {
    char pad0[0x6C];
    void *modelBankData;
    char pad70[0xC];
    void *frameResourceData;
    char pad80[0x1158];
    struct EntryOvlSceneDispatchAndRecycleQueuedTriggers *active;
    char pad11DC[0x10];
    struct EntryOvlSceneDispatchAndRecycleQueuedTriggers *spare;
};
/** Release every active entry of owner and move it onto the spare list. */
void Scene_DispatchAndRecycleQueuedTriggers(SceneTriggerQueueOwner *owner);
#endif
