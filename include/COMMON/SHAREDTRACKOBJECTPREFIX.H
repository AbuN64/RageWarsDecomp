#ifndef COMMON_SHAREDTRACKOBJECTPREFIX_H
#define COMMON_SHAREDTRACKOBJECTPREFIX_H
#include "COMMON/SHARED_OPTIONSSCREEN.H"
#include "COMMON/LONE/HUD_REFERENCE_VIEWPORT_HEIGHT.H"
#include "TYPES.H"
#include "COMMON/SHAREDPLAYER.H"


struct SharedTrackObject;




/* The copied prefix is exactly 0x50 bytes. */
#include "MENU/TRACK_TYPES.H"





/* The two adjacent track constants are consumed at base and base+4. */



#include "COMMON/ACCESS_S8_10F.H"
#include "COMMON/TRIPLE.H"
#include "COMMON/GROUP.H"


extern s32 g_hudReferenceViewportWidth;
extern s32 g_cinemaPlaybackFlag;

void OnScreen_SetupTextRendering(void);

void Onscrn_DrawText(void * text, s32 x, s32 y, s32 alpha, s32 centred, s32 shadow, f32 scaleX, f32 scaleY);
#endif
