#ifndef COMMON_WORLDSORTENTRY_H
#define COMMON_WORLDSORTENTRY_H
#include "COMMON/BOOT_MEMORY_AND_THREAD_BOUNDARIES.H"
#include "TYPES.H"
#include <ultra64.h>
#include <PR/sched.h>
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/RESIDENT_EVENT_HANDLER.H"
typedef struct WorldSortEntry { s32 item; f32 distance; } WorldSortEntry;

struct Def;
struct Def {
    s32 type;
    s32 flags; /* 0x4 */
    char pad8[0x20];
    s16 id;
};
struct Def;

struct LevelActorArrayView;
typedef struct LevelActorArrayView LevelActorArrayView;



extern float g_schedulerVideoYScale;

struct NearbySpecialActorView;

struct Shared_World;





struct Panel;
struct Panel {
    s16 active;
    char pad2[0x20 - 2];
    s16 mode;
    char pad22[0x40 - 0x22];
    char row0[24];
    char row0Slots[32];
    char row1[24];
    char row1Slots[32];
    char elements[0x2E0 - 0xB0];
    s32 clientList;
    s32 audioListHead;
    s32 gfxListHead;
    s32 audioListTail;
    s32 gfxListTail;
    s32 curRSPTask;
    s32 curRDPTask;
    s32 frameCount;
    s32 doAudio;
};


extern int g_schedulerRdpBufferSetFlag;



struct LevelActor;
struct LevelActorArrayView;
struct LevelActorArrayView {
    char pad[0x138];
    struct LevelActor *actors;
    s32 pad13C;
    s32 count;
};

extern float g_sceneImageVectorTolerance;







struct OSScClientWork;
struct OSScClientWork {
    struct OSScClientWork *next;
    OSMesgQueue *queue;
};












struct IntPair;


extern int g_schedulerShutdownPending;




struct OSScClientWork;



struct ImageSet;
struct ImageSet {
    u16 columns;
    u16 rows;
    u16 width;
    u16 height;
};

struct ImageSet;
typedef struct ImageSet ImageSet;


struct OSScClientWork;
typedef struct OSScClientWork OSScClientWork;






struct NearbySpecialActorView;
typedef struct NearbySpecialActorView NearbySpecialActorView;











struct Panel;
typedef struct Panel Panel;









extern f32 g_schedulerAudioDuration;
extern s32 g_schedulerRetraceCount;
#endif
