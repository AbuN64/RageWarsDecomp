#ifndef COMMON_SHAREDTRACKOBJECTPREFIX_H
#define COMMON_SHAREDTRACKOBJECTPREFIX_H
#include "Common/shared_optionsscreen.h"
#include "Common/Lone/hud_reference_viewport_height.h"
#include "types.h"
#include "Common/sharedplayer.h"


struct SharedTrackObject;




/* The copied prefix is exactly 0x50 bytes. */
#include "Menu/track_types.h"





/* The two adjacent track constants are consumed at base and base+4. */



#include "Common/access_s8_10f.h"
#include "Common/triple.h"
#include "Common/group.h"


extern s32 g_hudReferenceViewportWidth;
extern s32 g_cinemaPlaybackFlag;

void OnScreen_SetupTextRendering(void);

void Onscrn_DrawText(void * text, s32 x, s32 y, s32 alpha, s32 centred, s32 shadow, f32 scaleX, f32 scaleY);
#endif
