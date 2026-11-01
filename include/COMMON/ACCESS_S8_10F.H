#ifndef COMMON_ACCESS_S8_10F_H
#define COMMON_ACCESS_S8_10F_H
#include "TYPES.H"
#include "COMMON/GROUP.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/VECTOR4F.H"
#include "COMMON/ITEMRECAT20V1.H"
extern float g_cinemaTimeScale;



extern void Cinema_SetLetterboxState(void *letterboxEnabled);



extern f32 Cinema_GetSequenceResponse();

struct CollisionState;

struct UnicolMotionSettings;
typedef struct UnicolMotionSettings UnicolMotionSettings;



extern void Cinema_ClearResponse(void);

struct Access_s32_C4;
typedef struct Access_s32_C4 Access_s32_C4;


extern void Cinema_ClearMessageCount(void);

struct UnicolMotionSettings;



extern float k_cinemaResponseThreshold_de;





extern float Cinema_GetScaledSequenceValue(void);


extern float g_actorVisibilityProbeHeightScale;







extern float k_cinemaInactiveResponse_de;

extern void Cinema_ReleaseSequenceContext(void);




struct ActorHorizontalMovementView;
typedef struct ActorHorizontalMovementView ActorHorizontalMovementView;







extern void * g_cinemaLetterboxEnabled;

extern void Cinema_ResetViewport(void);

struct Access_s32_C4;


struct Access_s32_D0;


struct Access_s32_D0;
typedef struct Access_s32_D0 Access_s32_D0;







struct HorizontalMovementSurfaceView;





extern unsigned int Cinema_GetSequenceProperty(void);



struct CollisionState;
typedef struct CollisionState CollisionState;


struct ActorHorizontalMovementView;

struct HorizontalMovementSurfaceView;
typedef struct HorizontalMovementSurfaceView HorizontalMovementSurfaceView;




extern float g_cinemaTrackScalarScale;


extern float g_resetActorFloorDirectionY;






#endif
