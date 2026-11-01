#ifndef MENU_PAK_MENU_ISTRACKREQUESTITEM_H
#define MENU_PAK_MENU_ISTRACKREQUESTITEM_H
#include "COMMON/ENTRYRECAT0V3.H"
extern int Menu_RequestTrackBundle(void);
extern f32 Menu_BlendCubic(f32 from, f32 to, f32 t);
extern s32 Menu_GetCinemaSequenceCount(void);
extern void CTrackResource_AccessResourceSection(void);
extern f32 Menu_BlendLinear(f32 from, f32 to, f32 weight);
#endif
