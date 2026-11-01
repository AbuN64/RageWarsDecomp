#include "include_asm.h"
#include "COMMON/STATEPAIR.H"
#include "TYPES.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/INTEGERSTATE530.H"
#include "COMMON/RECORD.H"
#include "COMMON/SLOTRECATCV1.H"
#include "COMMON/TEXTURE.H"
#include "FRONTEND/NODE_GETIMAGETEXTURE.H"
#include "MENU/GFX/GFX_SHUTDOWNFRONTENDSERVICES.H"
#include "UI/TSMOS/TSMOS.H"
#include "RESMGR/FRAME_HEAP_LIFETIME.H"

void Tsmos_ShutdownFrontend(void) {
    extern struct Triple g_frontendShutdownState;
    s32 *selected;
    Menu_DestroyScreenManager();
    Node_CloseResourceArchive();
    ESmem_FreeFrameHeaps();
    Gfx_ShutdownFrontendServices();
    selected = &g_frontendShutdownState.z;
    *selected = 0;
    Tsmos_DeactivateControllerState();
    g_frontendShutdownState.x = 0;
}

extern f32 g_frontendWidgetHorizontalScale, g_frontendWidgetVerticalScale;

void Tsmos_ScaleWidgetTree(Widget *widget, Widget *parent) {
    if (widget != 0) {
        if (widget->next != 0) Tsmos_ScaleWidgetTree(widget->next, parent);
        if (widget->child != 0) Tsmos_ScaleWidgetTree(widget->child, widget);
        if (widget->kind == 8) {
            if (widget->links[0] != 0) Tsmos_ScaleWidgetTree(widget->links[0], widget);
            if (widget->links[2] != 0) Tsmos_ScaleWidgetTree(widget->links[2], widget);
            if (widget->links[1] != 0) Tsmos_ScaleWidgetTree(widget->links[1], widget);
        }
        if (widget->scaled == 0) {
            f32 factorX = g_frontendWidgetHorizontalScale;
            f32 factorY = g_frontendWidgetVerticalScale;
            if (widget->kind == 4) {
                widget->scaleX = factorX;
                widget->scaleY = factorY;
            } else {
                f32 value;
                s32 x, y, width, height;
                value = (f32)widget->x * factorX;
                x = (s32)value;
                value = (f32)widget->y * factorY;
                y = (s32)value;
                value = (f32)widget->width * factorX;
                width = (s32)value;
                value = (f32)widget->height * factorY;
                height = (s32)value;
                widget->x = x;
                widget->y = y;
                widget->width = width;
                widget->height = height;
            }
            widget->scaled = 1;
        }
    }
}

