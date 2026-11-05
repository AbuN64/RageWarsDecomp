#include "include_asm.h"
#include "Common/statepair.h"
#include "types.h"
#include "Ui/g_frontendshutdownstate.h"
#include "Common/sharedplayer.h"
#include "Common/runtime_declarations.h"
#include "Common/menu_screen_elements.h"
#include "Common/record.h"
#include "Common/archive_chunk_images.h"
#include "Common/texture.h"
#include "Frontend/node_getimagetexture.h"
#include "Menu/Gfx/gfx_shutdownfrontendservices.h"
#include "Ui/Tsmos/TSMOS.h"
#include "Resmgr/frame_heap_lifetime.h"
#include "Common/triple.h"

void Tsmos_ShutdownFrontend(void) {
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
