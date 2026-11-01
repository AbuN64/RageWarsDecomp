#ifndef DATA_OVERLAY_LAYOUTS_H
#define DATA_OVERLAY_LAYOUTS_H
#include "TYPES.H"
typedef struct OverlayScissorRect { s32 left, top, right, bottom; } OverlayScissorRect;
typedef struct OverlayTrialWidgetGroup { s32 firstResource, secondResource, optionalResource; } OverlayTrialWidgetGroup;
typedef struct OverlayTrialStage { s32 resource, kind, stage; s32 neighbor[4]; } OverlayTrialStage;
#endif
