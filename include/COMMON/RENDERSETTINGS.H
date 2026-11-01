#ifndef COMMON_RENDERSETTINGS_H
#define COMMON_RENDERSETTINGS_H
#include "TYPES.H"
#include "COMMON/SHAREDPLAYER.H"
/* The session's render settings at +0x26D8C: Ovlgame_InitializeRenderDirection normalises the light direction and sets ready. */
typedef struct RenderSettings {
    u8 reserved0[0x14];
    CVector3 direction; /* +0x14 */
    s32 ready; /* +0x20 */
} RenderSettings;
#endif
