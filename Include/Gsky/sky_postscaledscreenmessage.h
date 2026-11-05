#ifndef GSKY_SKY_POSTSCALEDSCREENMESSAGE_H
#define GSKY_SKY_POSTSCALEDSCREENMESSAGE_H
#include "Common/vector.h"
struct MenuMatchGlobals;
struct CVector3_t;
void *Gsky_FindNearestCamera(struct MenuMatchGlobals *menuMatchGlobals, struct CVector3_t *zero);
struct CCameraText_t *Gsky_PostScaledScreenMessage(void *owner, void *pool, u8 *text, f32 size);
extern void Gsky_StartEmitter(char *obj, f32 a, f32 b, f32 c, f32 scale, s32 value, CVector3 pos);

#endif
