#ifndef COMMON_ENTRYRECAT8V4_H
#define COMMON_ENTRYRECAT8V4_H
#include "TYPES.H"
#include "COMMON/KEYRECAT1C.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/AUDIO_CALLBACKS.H"
#include "COMMON/RESIDENT_EVENT_HANDLER.H"
#include "COMMON/LOCALDECODERANGE.H"

extern CVector3 Menu_GetTrackStartEye(void);



struct TrackTimedItemEvent;
struct TrackTimedItemEvent {
    f32 time;
    s32 side;
    s32 index;
};

struct RecordMenuProcessTrackItemEvents;
typedef struct RecordMenuProcessTrackItemEvents RecordMenuProcessTrackItemEvents;


struct TrackOverlayIdEntry;
typedef struct TrackOverlayIdEntry TrackOverlayIdEntry;


extern void Track_DrawTrackOverlay();

struct TriggerStateBitDescriptor;
typedef struct TriggerStateBitDescriptor TriggerStateBitDescriptor;

struct TriggerStateBitDescriptor;
struct TriggerStateBitDescriptor {
    char pad0[0xE];
    u8 flags;
    char padF[2];
    u8 kind;
    u8 subkind;
    u8 bitIndex; /* 0x13: persistent trigger bit */
};

struct Tables;
struct Tables {
    char pad0[0x11D0];
    TriggerStateBitDescriptor *items[2];
};





struct TrackOverlayNamedEntry;
struct TrackOverlayNamedEntry {
    s32 id0;
    s32 id4;
    s32 id8;
    s32 flags;
    char pad10[8];
    char name[52];
};

extern void Menu_AssignBit(u8 *bits, s32 n, s32 set);

extern float g_trackStartTargetFallbackX;

struct Tables;
typedef struct Tables Tables;

extern u32 Menu_TestBit(u8 *bits, s32 index);


struct Spline;
typedef struct Spline Spline;

struct TrackOverlayNamedEntry;
typedef struct TrackOverlayNamedEntry TrackOverlayNamedEntry;

extern CVector3 Menu_GetTrackStartTarget(void);

struct SplineNode;
struct SplineNode {
    CVector3 p;
    CVector3 d2p;
    f32 s;
    f32 w;
    f32 d2s;
};

struct SplineNode;
typedef struct SplineNode SplineNode;

struct Spline;
struct Spline {
    s32 nodeSize;
    s32 count;
    SplineNode nodes[1];
};

extern f32 Menu_GetTrackDuration(void);

struct TrackTimedItemEvent;
typedef struct TrackTimedItemEvent TrackTimedItemEvent;

struct TrackOverlayIdEntry;
struct TrackOverlayIdEntry {
    s32 id0;
    s32 id4;
    char pad8[0x44];
};



extern void *CTrackResource_GetRecordPayload(void *value);







extern void *Menu_GetTrackCues(void);

struct RecordMenuProcessTrackItemEvents;
struct RecordMenuProcessTrackItemEvents {
    char pad0[4];
    s32 resource;
    char pad8[0x14];
    f32 time;
    char pad20[0x14];
    f32 endTime;
    char pad38[0x18];
    s32 active;
    char pad54[4];
    s32 pending;
};

extern s32 Menu_GetTrackClipCount(void);




extern f32 g_trackSplineOutputBounds[];


typedef struct ScreenRectangle { char pad0[0x29c]; f32 x,y,width,height; } ScreenRectangle;

typedef struct SplineSource { s32 stride,count; union { char data[0]; CVector3 points[0]; f32 weights[0]; }; } SplineSource;
typedef struct SplineTable { s32 count; } SplineTable;
extern int SetN64_GetRecordBlockSize(int *);
extern void Polytrak2_InitializeOutputPack(void *,s32);
extern char *Polytrak2_AppendOutputPackSection(Pack *,const void *,s32);
typedef union SplineSourceCursor { SplineSource *header; CVector3 *points; f32 *weights; } SplineSourceCursor;

extern char g_Track_BuildTrackResourceSplinesAddress[];
extern const char s_cinemaText[];
extern void *Menu_GetTrackClip(s32);
#endif
