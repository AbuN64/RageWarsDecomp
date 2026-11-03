#ifndef GSKY_SKY_POSTSCALEDSCREENMESSAGE_H
#define GSKY_SKY_POSTSCALEDSCREENMESSAGE_H
struct MenuMatchGlobals;
struct CVector3_t;
void *Gsky_FindNearestCamera(struct MenuMatchGlobals *menuMatchGlobals, struct CVector3_t *zero);
struct CCameraText_t *Gsky_PostScaledScreenMessage(void *owner, void *pool, u8 *text, f32 size);
#endif
