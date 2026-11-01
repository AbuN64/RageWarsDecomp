#include "COMMON/FORMAT.H"
#include "COMMON/RESIDENT_EVENT_HANDLER.H"
#include "DATA_OVERLAY_LAYOUTS.H"

#include "TYPES.H"

#if defined(VERSION_DE)
extern char g_node_SelectPreviousGridRowEntry[];
extern char g_node_SelectNextGridRowEntry[];
extern char g_node_SelectPreviousGridColumnEntry[];
extern char g_node_SelectNextGridColumnEntry[];
extern char g_node_DestroyGridListEntry[];
extern char g_gfx_BlinkVideoUnlessBypassedEntry[];
#if defined(VERSION_DE)
struct {
    ResidentEventHandlerEntry eventHandlers0[6];
    u8 alignmentFill72[8];
    struct Format pixelFormats[36];
    char text1952[16];
} g_nodeDispatchTypedWidgetEventTable_de __attribute__((aligned(4))) = {
    { { 5, 30000, (ResidentEventHandler)(void *)&g_node_SelectPreviousGridRowEntry }, { 6, 30000, (ResidentEventHandler)(void *)&g_node_SelectNextGridRowEntry }, { 7, 30000, (ResidentEventHandler)(void *)&g_node_SelectPreviousGridColumnEntry }, { 8, 30000, (ResidentEventHandler)(void *)&g_node_SelectNextGridColumnEntry }, { 3587, 30000, (ResidentEventHandler)(void *)&g_node_DestroyGridListEntry }, { 0, 0, (ResidentEventHandler)0 } },
    { 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 },
    { { 0, 0, 0, 0, 0, { 0x0, 0x0, 0x0, 0x0 }, { -8, -8, -8, -8 } }, { 1, 0, 16, 16, 16, { 0xf800, 0x7e0, 0x1f, 0x0 }, { 8, 3, -3, -8 } }, { 2, 0, 16, 16, 16, { 0xf00, 0xf0, 0xf, 0xf000 }, { 4, 0, -4, 8 } }, { 3, 0, 16, 16, 16, { 0xf000, 0xf00, 0xf0, 0xf }, { 8, 4, 0, -4 } }, { 4, 0, 16, 16, 16, { 0x7c00, 0x3e0, 0x1f, 0x8000 }, { 7, 2, -3, 8 } }, { 5, 0, 16, 16, 16, { 0xf800, 0x7c0, 0x3e, 0x1 }, { 8, 3, -2, -7 } }, { 6, 0, 16, 16, 15, { 0x7c00, 0x3e0, 0x1f, 0x0 }, { 7, 2, -3, 7 } }, { 7, 0, 16, 16, 15, { 0xf800, 0x7c0, 0x3e, 0x0 }, { 8, 3, -2, -8 } }, { 8, 0, 24, 24, 24, { 0xff0000, 0xff00, 0xff, 0x0 }, { 16, 8, 0, -8 } }, { 9, 0, 24, 24, 24, { 0xf800, 0x7e0, 0x1f, 0xff0000 }, { 8, 3, -3, 16 } }, { 10, 0, 32, 32, 24, { 0xff000000, 0xff0000, 0xff00, 0x0 }, { 24, 16, 8, -8 } }, { 11, 0, 32, 32, 24, { 0xff0000, 0xff00, 0xff, 0x0 }, { 16, 8, 0, 16 } }, { 12, 0, 32, 32, 32, { 0xff0000, 0xff00, 0xff, 0xff000000 }, { 16, 8, 0, 24 } }, { 13, 0, 32, 32, 32, { 0xff000000, 0xff0000, 0xff00, 0xff }, { 24, 16, 8, 0 } }, { 14, 1, 4, 16, 16, { 0xf800, 0x7e0, 0x1f, 0x0 }, { 8, 3, -3, -8 } }, { 15, 1, 4, 24, 24, { 0xff0000, 0xff00, 0xff, 0x0 }, { 16, 8, 0, -8 } }, { 16, 1, 4, 32, 24, { 0xff0000, 0xff00, 0xff, 0x0 }, { 16, 8, 0, 16 } }, { 17, 1, 4, 32, 24, { 0xff000000, 0xff0000, 0xff00, 0x0 }, { 24, 16, 8, -8 } }, { 18, 1, 4, 32, 32, { 0xff0000, 0xff00, 0xff, 0xff000000 }, { 16, 8, 0, 24 } }, { 19, 1, 4, 32, 32, { 0xff000000, 0xff0000, 0xff00, 0xff }, { 24, 16, 8, 0 } }, { 20, 1, 4, 16, 16, { 0xf800, 0x7c0, 0x3e, 0x1 }, { 8, 3, -2, -7 } }, { 21, 1, 4, 16, 16, { 0x7c00, 0x3e0, 0x1f, 0x8000 }, { 7, 2, -3, 8 } }, { 22, 1, 4, 16, 15, { 0xf800, 0x7c0, 0x3e, 0x0 }, { 8, 3, -2, -8 } }, { 23, 1, 4, 16, 15, { 0x7c00, 0x3e0, 0x1f, 0x0 }, { 7, 2, -3, 7 } }, { 24, 1, 8, 16, 16, { 0xf800, 0x7e0, 0x1f, 0x0 }, { 8, 3, -3, -8 } }, { 25, 1, 8, 24, 24, { 0xff0000, 0xff00, 0xff, 0x0 }, { 16, 8, 0, -8 } }, { 26, 1, 8, 32, 24, { 0xff0000, 0xff00, 0xff, 0x0 }, { 16, 8, 0, 16 } }, { 27, 1, 8, 32, 24, { 0xff000000, 0xff0000, 0xff00, 0x0 }, { 24, 16, 8, -8 } }, { 28, 1, 8, 32, 32, { 0xff0000, 0xff00, 0xff, 0xff000000 }, { 16, 8, 0, 24 } }, { 29, 1, 8, 32, 32, { 0xff000000, 0xff0000, 0xff00, 0xff }, { 24, 16, 8, 0 } }, { 30, 1, 8, 16, 16, { 0xf800, 0x7c0, 0x3e, 0x1 }, { 8, 3, -2, -7 } }, { 31, 1, 8, 16, 16, { 0x7c00, 0x3e0, 0x1f, 0x8000 }, { 7, 2, -3, 8 } }, { 32, 1, 8, 16, 15, { 0xf800, 0x7c0, 0x3e, 0x0 }, { 8, 3, -2, -8 } }, { 33, 1, 8, 16, 15, { 0x7c00, 0x3e0, 0x1f, 0x0 }, { 7, 2, -3, 7 } }, { 34, 0, 4, 4, 4, { 0xf, 0x0, 0x0, 0x0 }, { -4, -8, -8, -8 } }, { 35, 0, 8, 8, 8, { 0xff, 0x0, 0x0, 0x0 }, { 0, -8, -8, -8 } } },
    "\000A\\ \000\000\000\000        "
};
typedef char g_nodeDispatchTypedWidgetEventTable_deSizeCheck[(sizeof(g_nodeDispatchTypedWidgetEventTable_de) == 1968) ? 1 : -1];
#endif
#endif
