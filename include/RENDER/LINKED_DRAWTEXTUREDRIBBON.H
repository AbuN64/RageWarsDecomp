#ifndef RENDER_LINKED_DRAWTEXTUREDRIBBON_H
#define RENDER_LINKED_DRAWTEXTUREDRIBBON_H
#include "TYPES.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/ITEMRECAT20V1.H"
struct TexturedRibbonOwnerView {
    char pad0[0x8];
    char * track;
    char pad8[0x28 - 0x8 - sizeof(char*)];
    f32 phase;
    char pad28[0x3C - 0x28 - sizeof(f32)];
    s32 flags;
    char pad3C[0x40 - 0x3C - sizeof(s32)];
    char * firstSegment;
    char pad40[0x4C - 0x40 - sizeof(char*)];
    f32 length;
    char pad4C[0x50 - 0x4C - sizeof(f32)];
    s32 clearedWord;
};
struct TexturedRibbonSegmentView {
    char pad0[0x10];
    CVector3 position;
    char pad10[0xAC - 0x10 - sizeof(CVector3)];
    f32 segmentLength;
};
struct TexturedRibbonStateView {
    char pad0[0x4];
    char * next;
    char pad4[0x8 - 0x4 - sizeof(char*)];
    f32 value;
    char pad8[0x10 - 0x8 - sizeof(f32)];
    ScalarOrVector3 position;
    char pad10[0x1C - 0x10 - sizeof(ScalarOrVector3)];
    f32 scale;
    char pad1C[0x28 - 0x1C - sizeof(f32)];
    f32 fixedMatrixFirst;
    char pad28[0x68 - 0x28 - sizeof(f32)];
    f32 fixedMatrixSecond;
    char pad68[0xA8 - 0x68 - sizeof(f32)];
    f32 phase;
    char padA8[0xAC - 0xA8 - sizeof(f32)];
    WordOrFloat segmentLength;
    char padAC[0xB0 - 0xAC - sizeof(WordOrFloat)];
    s32 clearedWord;
};
struct TexturedRibbonResourceView {
    unsigned char padding_0[8];
    f32 total;
    unsigned char padding_C[16];
    u8 kind;
};
void *Linked_AppendRibbonSegment(void *effectSystem, void *ribbon, void *local);
struct VertexArena;
struct RibbonActor;
struct GameplayCamera;
void Linked_DrawTexturedRibbon(struct VertexArena *pool, struct RibbonActor *actor, struct GameplayCamera *camera);
struct LinkOwner802A;
void Linked_UpdateLinkedNodeTransforms(struct LinkOwner802A *owner);
struct StateSmpUpdateRibbonLifetime;
s32 Linked_UpdateRibbonLifetime(s32 owner, struct StateSmpUpdateRibbonLifetime *state);
void Linked_UpdateRibbonMatrices(void *ribbon, void *camera);
#endif
