#ifndef COMMON_GROUP_H
#define COMMON_GROUP_H
#include "TYPES.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/ITEMRECAT20V1.H"
struct CollisionSweepWork;
typedef struct CollisionSweepWork CollisionSweepWork;


struct Group;

extern void Cinema_ClearPlaybackFlag(void);

extern void Cinema_RequestSequenceFade(void);


extern void Cinema_ClearPlaybackPauseState(void);

extern int Cinema_HasSequenceResource(void);




struct VectorPair;

struct Group;
typedef struct Group Group;


extern int g_collisionSweepCount;

extern float g_cinemaSequenceTimeScale;






struct VectorPair;
typedef struct VectorPair VectorPair;



struct CollisionSweepWork;






struct CCollisionInfo2_t;

extern s32 Cinema_HasSequenceEnded(void);



struct GameState;
struct GameState {
    s32 busy;
    char pad4[0x18B0];
    s32 paused;
};

extern int Cinema_IsSequenceFlagTwoSet(void);


struct GameState;
typedef struct GameState GameState;


extern int Cinema_IsFadeAllowed(void);

extern void Cinema_EndSequence(void);



extern int g_cinemaLastUpdatedFrame;


extern void Cinema_SetPlaybackFlag(void);

extern int g_collisionPeakSweepCount;

#endif
