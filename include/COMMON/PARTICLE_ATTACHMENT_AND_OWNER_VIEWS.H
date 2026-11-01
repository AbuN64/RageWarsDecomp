#ifndef COMMON_PARTICLE_ATTACHMENT_AND_OWNER_VIEWS_H
#define COMMON_PARTICLE_ATTACHMENT_AND_OWNER_VIEWS_H
#include "TYPES.H"
#include "COMMON/SHAREDPLAYER.H"
struct ObjParticleInitializeAttachmentsAndSound;
struct ObjParticleInitializeAttachmentsAndSound {
    char pad0[4];
    u16 modelId;
    char pad6[2];
    s32 positionX;
    s32 positionY;
    s32 positionZ;
    char pad14[8];
    CVector3 rotation; /* 0x1C */
    char pad28[0x34];
    u32 flags;
    char pad60[0xB8];
    s32 *effectFlags; /* 0x118 */
    char pad11C[0x10];
    void *effectResource; /* 0x12C */
    s32 effectIndex; /* 0x130 */
    s32 effectCount; /* 0x134 */
    s32 soundHandle;
    char pad13C[0x1D9 - 0x13C];
    u8 active1D9;
};



struct ParticleContactStateLayout;
struct ParticleContactStateLayout {
    Triple first;
    char pad[0xD0 - 0xC];
    Triple second;
};

struct ParticleContactStateLayout;
typedef struct ParticleContactStateLayout ParticleContactStateLayout;

struct ParticleObjectLinkView;
struct ParticleObjectLinkView {
    s8 kind;
    unsigned char padding_1[23];
    s32 *actorDefinition;
    unsigned char padding_1C[64];
    s32 flags;
    unsigned char padding_60[380];
    s32 reservedWord1DC;
    unsigned char padding_1E0[4];
    s32 reservedWord1E4;
};

struct TrailActor;
typedef struct TrailActor TrailActor;




struct ParamsParticleInitializeAttachmentsAndSound;
struct ParamsParticleInitializeAttachmentsAndSound {
    char pad0[6];
    s8 resourceId;
    s8 attachmentIndex;
    char pad8[4];
    s16 soundId;
};



struct ParticleKindFlagsView;
struct ParticleKindFlagsView {
    unsigned char padding_0[4];
    u16 modelId;
    unsigned char padding_6[86];
    s32 flags;
};

struct ObjParticleInitializeAttachmentsAndSound;
typedef struct ObjParticleInitializeAttachmentsAndSound ObjParticleInitializeAttachmentsAndSound;









struct ParticleObjectLinkView;
typedef struct ParticleObjectLinkView ParticleObjectLinkView;





struct ParamsParticleInitializeAttachmentsAndSound;
typedef struct ParamsParticleInitializeAttachmentsAndSound ParamsParticleInitializeAttachmentsAndSound;

struct TrailState;
struct TrailState {
    char pad0[0xC];
    s8 count;
};
struct TrailNode;
struct TrailState;
struct TrailNode {
    char pad0[0x38];
    struct TrailState *state;
};
struct TrailActor;
struct TrailNode;
struct TrailActor {
    char pad0[4];
    u16 model;
    char pad6[2];
    Triple origin;
    char pad14[8];
    Triple position;
    char pad28[0x118 - 0x28];
    struct TrailNode *node;
    char pad11C[0x12C - 0x11C];
    void *owner;
    s32 property;
    s32 type;
    char pad138[0x168 - 0x138];
    Triple end;
};

extern float g_particleAveragePositionConstants;


struct ParticleResourceHandleEntry;
struct ParticleResourceHandleEntry {
    int state;
    void *handle;
    char pad8[0xC];
};








struct ParticleResourceHandleEntry;
typedef struct ParticleResourceHandleEntry ParticleResourceHandleEntry;





struct ParticleKindFlagsView;
typedef struct ParticleKindFlagsView ParticleKindFlagsView;


#endif
