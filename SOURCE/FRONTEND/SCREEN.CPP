#include "../../sdk/include/LIBC.H"
#include "include_asm.h"
#include "COMMON/LONE/HUD_REFERENCE_VIEWPORT_HEIGHT.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/OSVISCALE.H"
#include "COMMON/NODERECAT2A8.H"
#include "TYPES.H"
#include <ultra64.h>
#include "COMMON/BOOT_TV_TYPE.H"
#include "FRONTEND/SCREEN.H"
#include "FRONTEND/SCREEN_VIDEO_MODE.H"

/* 8040B45C_21.CPP */
/* Selects the video mode and applies framebuffer and display configuration; the mode-to-word-array cast preserves configuration-store and mode-load scheduling. */
s32 Defs_GetMemorySize(); /* extern */
                                 /* extern */
void Frontend_SetVideoModeAndViewports(unsigned, int, int, int, int, int);
extern s32 g_frontendVideoModeVariantBit;
extern s32 g_hudReferenceViewportWidth;
extern s32 g_frontendCurrentVideoModeIndex;
extern FrontendVideoDimensions g_frontendRegionVideoModes[2][5];
extern struct FrontendVideoModeParameters g_frontendDefaultVideoModes[];
extern RecGobjinstSampleBoneTranslation g_frontendVideoModeRenderConfigs[];
extern u8 g_frontendSavedVideoModeIndex;
static inline void set_config(int a,int b,int c,int d,int e) {
        g_frontendViDitherFilterEnabled = a;
        g_geometryAntialiasingEnabled = b;
        g_frontendVideoModeVariantBit = c;
        g_geometryTextureFilterOverride = d;
        g_geometryTexturePerspectiveOverride = e;
}
static inline void set_mode(s32 *videoMode) {
        g_hudReferenceViewportWidth = (s32) videoMode[0];
        g_hudReferenceViewportHeight = (s32) videoMode[1];
        Frontend_SetVideoModeAndViewports(videoMode[0], videoMode[1], videoMode[2], videoMode[3], videoMode[4], videoMode[5]);
}
void Frontend_ApplyVideoMode(void) {
    char *unusedPointer;
    s32 featureCommands;
    s32 unusedValue;
    s32 unusedValue1;
    struct FrontendVideoModeParameters *videoMode;
    videoMode = NULL;
    g_frontendStartupState = 2;
    if (g_frontendCurrentVideoModeIndex == -1) {
        if (Defs_GetMemorySize() != 0x400000) {
            g_frontendCurrentVideoModeIndex = 1;
        } else {
            g_frontendCurrentVideoModeIndex = 0;
        }
        g_frontendSavedVideoModeIndex = (u8)g_frontendCurrentVideoModeIndex;
    }
    switch(g_consoleTvType) {
    case 1: videoMode=&((struct FrontendVideoModeParameters *)g_frontendRegionVideoModes)[g_frontendCurrentVideoModeIndex];break;
    case 0:case 2:videoMode=&g_frontendDefaultVideoModes[g_frontendCurrentVideoModeIndex];break;
    }
    if (videoMode != NULL) {
        RecGobjinstSampleBoneTranslation config=g_frontendVideoModeRenderConfigs[g_frontendCurrentVideoModeIndex];
        set_config(config.x,config.y,config.z,config.pad0,config.pad1);
        set_mode((s32 *)videoMode);
        featureCommands = 128;
        if (g_frontendViDitherFilterEnabled != 0) {
            featureCommands = 64;
        }
        osViSetSpecialFeatures(featureCommands);
        osViSetSpecialFeatures(32);
        osViSetSpecialFeatures(2);
    }
}

extern unsigned short g_frontendVideoModeId;
extern Modep g_frontendVideoMode;
extern Modep g_videoModeLabels[];


/* VI start registers (hStart, vStart) hold the first pixel/line in the high half and the last in the low half. The
   ROM reads the halves through a stack copy, so a little-endian host keeps the low half at the first address. */
typedef union VideoInterval {
    u32 packed;
    struct {
#if defined(__BYTE_ORDER__) && __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
        u16 last, first;
#else
        u16 first, last;
#endif
    } half;
} VideoInterval;
typedef union VideoHorizontal {
    u32 packed;
    struct {
#if defined(__BYTE_ORDER__) && __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
        u32 last : 16; s32 first : 16;
#else
        s32 first : 16; u32 last : 16;
#endif
    } edge;
} VideoHorizontal;
/* Resizes the selected VI mode (table g_videoModeLabels[g_frontendVideoModeId], copied to g_frontendVideoMode) to width x height around its
 * horizontal and field centres moved by (x, y), shrinks the active area by the borders, rescales X and Y, clamps the
 * last pixel and lines to the original mode and applies it. */
void Frontend_SetVideoViewport(s32 width, s32 height, s32 x, s32 y, s32 borderX, s32 borderY) {
    VideoInterval vertical[2];
    VideoInterval originalVertical[2];
    u16 centerY[2];
    Modep *mode = &g_frontendVideoMode;
    VideoHorizontal horizontal, originalHorizontal;
    u32 scaleY;
    s32 centerX, scaleX;

    Libc_CopyBytes(mode, &g_videoModeLabels[(s16)g_frontendVideoModeId], 80);
    horizontal.packed = mode->comRegs.hStart;
    vertical[0].packed = mode->fldRegs[0].vStart;
    originalHorizontal = horizontal;
    centerX = ((s16)horizontal.edge.last - horizontal.edge.first) / 2 + horizontal.edge.first - x;
    centerY[0] = vertical[0].half.first + ((s16)vertical[0].half.last - (s16)vertical[0].half.first) / 2;
    scaleY = mode->fldRegs[0].yScale;
    horizontal.edge.first = centerX - width / 2 + borderX / 2;
    horizontal.edge.last = centerX + width / 2 - borderX * 2;
    vertical[1].packed = mode->fldRegs[1].vStart;
    centerY[1] = vertical[1].half.first + ((s16)vertical[1].half.last - (s16)vertical[1].half.first) / 2;
    centerY[0] -= y;
    vertical[0].half.first = centerY[0] - height / 2 + borderY / 2;
    vertical[0].half.last = centerY[0] + height / 2 - borderY * 2;
    scaleY &= 0xFFFF0000;
    scaleY |= (((height << 11) /
        ((s16)vertical[0].half.last - (s16)vertical[0].half.first)) & 0xFFFF);
    originalVertical[0].packed = mode->fldRegs[0].vStart;
    centerY[1] -= y;
    vertical[1].half.first = centerY[1] - height / 2 + borderY / 2;
    vertical[0].half.last -= 3;
    vertical[1].half.last = centerY[1] + height / 2 - borderY * 2;
    originalVertical[1].packed = mode->fldRegs[1].vStart;
    vertical[1].half.last -= 3;
    scaleX = (width << 10) / ((s16)horizontal.edge.last - horizontal.edge.first);
    if ((s16)originalVertical[0].half.last < (s16)vertical[0].half.last) vertical[0].half.last = originalVertical[0].half.last;
    if ((s16)originalVertical[1].half.last < (s16)vertical[1].half.last) vertical[1].half.last = originalVertical[1].half.last;
    if ((s16)originalHorizontal.edge.last < (s16)horizontal.edge.last) horizontal.edge.last = originalHorizontal.edge.last;
    mode->fldRegs[0].yScale = scaleY;
    mode->fldRegs[1].yScale = scaleY;
    mode->fldRegs[0].origin = 0;
    mode->fldRegs[1].origin = width * 2;
    mode->comRegs.width = width;
    mode->comRegs.xScale = scaleX;
    mode->comRegs.hStart = horizontal.packed;
    mode->fldRegs[0].vStart = vertical[0].packed;
    mode->fldRegs[1].vStart = vertical[1].packed;
    osViSetMode(mode);
}

/* 8040B45C_22.CPP */
/* Cycles the video mode within the memory budget and chooses dimensions large enough for both active buffers. */
extern int g_frontendActiveVideoModeIndex;
extern int g_frontendKeepCurrentVideoModeOnce;
void Frontend_AdvanceVideoMode(void)
{
  int region = 0;
  int budget;
  int memory;
  int w;
  int h;
  int *mode;
  switch (g_consoleTvType)
  {
    case 0:
    case 2:
      region = 1;
      break;
    case 1:
      break;
  }
  mode = (int *) (&g_frontendRegionVideoModes[region][g_frontendCurrentVideoModeIndex]);
  memory = Defs_GetMemorySize();
  budget = 63072;
  if (memory != 0x400000)
  {
    budget = 172800;
  }
  if (!g_frontendKeepCurrentVideoModeOnce)
  {
    g_frontendCurrentVideoModeIndex = (g_frontendCurrentVideoModeIndex + 1) % g_frontendVideoModeCounts[region];
    while ((mode[0] * mode[1]) > budget)
    {
      g_frontendCurrentVideoModeIndex = (g_frontendCurrentVideoModeIndex + 1) % g_frontendVideoModeCounts[region];
    }
  }
  else
  {
    g_frontendKeepCurrentVideoModeOnce = 0;
  }
  memory = g_frontendRegionVideoModes[region][g_frontendActiveVideoModeIndex].width;
  w = g_frontendRegionVideoModes[region][g_frontendCurrentVideoModeIndex].width;
  if (w < memory)
  {
    w = g_frontendRegionVideoModes[region][g_frontendActiveVideoModeIndex].width;
  }
  g_hudReferenceViewportWidth = w;
  h = g_frontendRegionVideoModes[region][g_frontendCurrentVideoModeIndex].height;
  if (h < g_frontendRegionVideoModes[region][g_frontendActiveVideoModeIndex].height)
  {
    h = g_frontendRegionVideoModes[region][g_frontendActiveVideoModeIndex].height;
  }
  g_hudReferenceViewportHeight = h;
}
/* Stores its argument in g_frontendCurrentVideoModeIndex, which Frontend_GetCurrentVideoModeIndex_de returns, and calls Frontend_ApplyVideoMode. */
void Frontend_ApplyScreenModeValue(s32 value) {
    g_frontendCurrentVideoModeIndex = value;
    Frontend_ApplyVideoMode();
}
/* Gives g_selectionMessageStage the value 0x14 when it is still zero. */
extern s32 g_selectionMessageStage;
void Frontend_StartScreenModeFade(void) {
    if (g_selectionMessageStage == 0) {
        g_selectionMessageStage = 20;
    }
}
/* Detects the storage configuration and updates the cached selection. */
 /* extern */
                                  /* extern */
void Frontend_UpdateScreenMode(void) {
    if (g_frontendCurrentVideoModeIndex == -1) {
        if (Defs_GetMemorySize() != 0x400000) {
            g_frontendCurrentVideoModeIndex = 1;
        } else {
            g_frontendCurrentVideoModeIndex = 0;
        }
        g_frontendSavedVideoModeIndex = (u8)g_frontendCurrentVideoModeIndex;
    }
    if ((g_selectionMessageStage < 5) && (g_frontendActiveVideoModeIndex != g_frontendCurrentVideoModeIndex)) {
        Frontend_ApplyVideoMode();
        g_frontendActiveVideoModeIndex = g_frontendCurrentVideoModeIndex;
    }
}
/* Returns the palette for the current screen mode g_frontendCurrentVideoModeIndex: modes 1, 2 and 3 have their own, mode 0
   and anything else use the first. */
extern int g_frontendScreenModePaletteDefault;
extern int g_frontendScreenModePaletteOne;
extern int g_frontendScreenModePaletteTwo;
extern int g_frontendScreenModePaletteThree;
int *Frontend_GetScreenModePalette(void) {
    switch (g_frontendCurrentVideoModeIndex) {
    case 0:
    default:
        return &g_frontendScreenModePaletteDefault;
    case 1:
        return &g_frontendScreenModePaletteOne;
    case 2:
        return &g_frontendScreenModePaletteTwo;
    case 3:
        return &g_frontendScreenModePaletteThree;
    }
}
/* Requests a new value when no change is pending: if g_selectionMessageStage is zero and the value differs from
   g_frontendCurrentVideoModeIndex, remembers the old value in g_frontendActiveVideoModeIndex, stores the new one, sets g_frontendKeepCurrentVideoModeOnce and starts
   the 0x14-tick countdown g_selectionMessageStage. */
void Frontend_RequestScreenMode(s32 value) {
    if (g_selectionMessageStage == 0 && value != g_frontendCurrentVideoModeIndex) {
        g_frontendKeepCurrentVideoModeOnce = 1;
        g_frontendActiveVideoModeIndex = g_frontendCurrentVideoModeIndex;
        g_frontendCurrentVideoModeIndex = value;
        g_selectionMessageStage = 20;
    }
}
/* Returns the word held in g_frontendCurrentVideoModeIndex. */
s32 Frontend_GetScreenMode(void) {
    return g_frontendCurrentVideoModeIndex;
}
/* Selects the video mode and resets viewport dimensions on the linked views. */
extern int g_consoleTvType, g_frontendVideoModeVariantBit;
extern unsigned int VideoModeIds[3][8];
struct VideoViewList {
    FrontendScreenViewport *head;
    char reserved[0x1C];
    FrontendScreenViewport defaultView;
};
extern struct VideoViewList g_gameplayCameraList;

void Frontend_SetVideoModeAndViewports(unsigned width, int viewportHeight, int offsetX, int offsetY, int borderX, int borderY) {
    int flags = 0;
    int region = 0;
    FrontendScreenViewport *node;
    float height;

    switch (g_consoleTvType) {
    case 0: region = 1; break;
    case 1: break;
    case 2: region = 2; break;
    }
    if (width > 320) flags |= 4;
    if (g_frontendVideoModeVariantBit) flags |= 2;
    if (width > 320) flags |= 1;
    g_frontendVideoModeId = VideoModeIds[region][flags];
    Frontend_SetVideoViewport(width, viewportHeight, offsetX, offsetY, borderX, borderY);
    node = &g_gameplayCameraList.defaultView;
    if (node) {
        node->width = g_hudReferenceViewportWidth;
        height = g_hudReferenceViewportHeight;
        node->x = 0;
        node->y = 0;
        node->height = height;
    }
    node = g_gameplayCameraList.head;
    while (node) {
        node->x = 0;
        node->y = 0;
        node->width = g_hudReferenceViewportWidth;
        node->height = g_hudReferenceViewportHeight;
        node = node->next;
    }
}
