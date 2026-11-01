#include "COMMON/FORMAT.H"
#include "COMMON/RESIDENT_EVENT_HANDLER.H"
#include "DATA_OVERLAY_LAYOUTS.H"

#include "TYPES.H"

#if defined(VERSION_EU_X)
extern char g_Node_SelectPreviousGridRowPackedAddress24[];
extern char g_Node_SelectNextGridRowPackedAddress24[];
extern char g_Node_SelectPreviousGridColumnPackedAddress24[];
extern char g_Node_SelectNextGridColumnPackedAddress24[];
extern char g_Node_DestroyGridListPackedAddress24[];
extern char g_Gfx_BlinkVideoUnlessBypassedPackedAddress24[];
#if defined(VERSION_EU_X)
struct {
    ResidentEventHandlerEntry eventHandlers0[6];
    u8 alignmentFill72[8];
    struct Format pixelFormats[36];
    void * videoCallbacks[2];
    u8 alignmentFill1960[8];
} g_nodeTypedWidgetEventHandlerRecords __attribute__((aligned(4))) = {
    { { 5, 30000, (ResidentEventHandler)(void *)&g_Node_SelectPreviousGridRowPackedAddress24 }, { 6, 30000, (ResidentEventHandler)(void *)&g_Node_SelectNextGridRowPackedAddress24 }, { 7, 30000, (ResidentEventHandler)(void *)&g_Node_SelectPreviousGridColumnPackedAddress24 }, { 8, 30000, (ResidentEventHandler)(void *)&g_Node_SelectNextGridColumnPackedAddress24 }, { 3587, 30000, (ResidentEventHandler)(void *)&g_Node_DestroyGridListPackedAddress24 }, { 0, 0, (ResidentEventHandler)0 } },
    { 0xc2, 0xa0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 },
    { { 0, 0, 0, 0, 0, { 0x0, 0x0, 0x0, 0x0 }, { -8, -8, -8, -8 } }, { 1, 0, 16, 16, 16, { 0xf800, 0x7e0, 0x1f, 0x0 }, { 8, 3, -3, -8 } }, { 2, 0, 16, 16, 16, { 0xf00, 0xf0, 0xf, 0xf000 }, { 4, 0, -4, 8 } }, { 3, 0, 16, 16, 16, { 0xf000, 0xf00, 0xf0, 0xf }, { 8, 4, 0, -4 } }, { 4, 0, 16, 16, 16, { 0x7c00, 0x3e0, 0x1f, 0x8000 }, { 7, 2, -3, 8 } }, { 5, 0, 16, 16, 16, { 0xf800, 0x7c0, 0x3e, 0x1 }, { 8, 3, -2, -7 } }, { 6, 0, 16, 16, 15, { 0x7c00, 0x3e0, 0x1f, 0x0 }, { 7, 2, -3, 7 } }, { 7, 0, 16, 16, 15, { 0xf800, 0x7c0, 0x3e, 0x0 }, { 8, 3, -2, -8 } }, { 8, 0, 24, 24, 24, { 0xff0000, 0xff00, 0xff, 0x0 }, { 16, 8, 0, -8 } }, { 9, 0, 24, 24, 24, { 0xf800, 0x7e0, 0x1f, 0xff0000 }, { 8, 3, -3, 16 } }, { 10, 0, 32, 32, 24, { 0xff000000, 0xff0000, 0xff00, 0x0 }, { 24, 16, 8, -8 } }, { 11, 0, 32, 32, 24, { 0xff0000, 0xff00, 0xff, 0x0 }, { 16, 8, 0, 16 } }, { 12, 0, 32, 32, 32, { 0xff0000, 0xff00, 0xff, 0xff000000 }, { 16, 8, 0, 24 } }, { 13, 0, 32, 32, 32, { 0xff000000, 0xff0000, 0xff00, 0xff }, { 24, 16, 8, 0 } }, { 14, 1, 4, 16, 16, { 0xf800, 0x7e0, 0x1f, 0x0 }, { 8, 3, -3, -8 } }, { 15, 1, 4, 24, 24, { 0xff0000, 0xff00, 0xff, 0x0 }, { 16, 8, 0, -8 } }, { 16, 1, 4, 32, 24, { 0xff0000, 0xff00, 0xff, 0x0 }, { 16, 8, 0, 16 } }, { 17, 1, 4, 32, 24, { 0xff000000, 0xff0000, 0xff00, 0x0 }, { 24, 16, 8, -8 } }, { 18, 1, 4, 32, 32, { 0xff0000, 0xff00, 0xff, 0xff000000 }, { 16, 8, 0, 24 } }, { 19, 1, 4, 32, 32, { 0xff000000, 0xff0000, 0xff00, 0xff }, { 24, 16, 8, 0 } }, { 20, 1, 4, 16, 16, { 0xf800, 0x7c0, 0x3e, 0x1 }, { 8, 3, -2, -7 } }, { 21, 1, 4, 16, 16, { 0x7c00, 0x3e0, 0x1f, 0x8000 }, { 7, 2, -3, 8 } }, { 22, 1, 4, 16, 15, { 0xf800, 0x7c0, 0x3e, 0x0 }, { 8, 3, -2, -8 } }, { 23, 1, 4, 16, 15, { 0x7c00, 0x3e0, 0x1f, 0x0 }, { 7, 2, -3, 7 } }, { 24, 1, 8, 16, 16, { 0xf800, 0x7e0, 0x1f, 0x0 }, { 8, 3, -3, -8 } }, { 25, 1, 8, 24, 24, { 0xff0000, 0xff00, 0xff, 0x0 }, { 16, 8, 0, -8 } }, { 26, 1, 8, 32, 24, { 0xff0000, 0xff00, 0xff, 0x0 }, { 16, 8, 0, 16 } }, { 27, 1, 8, 32, 24, { 0xff000000, 0xff0000, 0xff00, 0x0 }, { 24, 16, 8, -8 } }, { 28, 1, 8, 32, 32, { 0xff0000, 0xff00, 0xff, 0xff000000 }, { 16, 8, 0, 24 } }, { 29, 1, 8, 32, 32, { 0xff000000, 0xff0000, 0xff00, 0xff }, { 24, 16, 8, 0 } }, { 30, 1, 8, 16, 16, { 0xf800, 0x7c0, 0x3e, 0x1 }, { 8, 3, -2, -7 } }, { 31, 1, 8, 16, 16, { 0x7c00, 0x3e0, 0x1f, 0x8000 }, { 7, 2, -3, 8 } }, { 32, 1, 8, 16, 15, { 0xf800, 0x7c0, 0x3e, 0x0 }, { 8, 3, -2, -8 } }, { 33, 1, 8, 16, 15, { 0x7c00, 0x3e0, 0x1f, 0x0 }, { 7, 2, -3, 7 } }, { 34, 0, 4, 4, 4, { 0xf, 0x0, 0x0, 0x0 }, { -4, -8, -8, -8 } }, { 35, 0, 8, 8, 8, { 0xff, 0x0, 0x0, 0x0 }, { 0, -8, -8, -8 } } },
    { (void *)&g_Gfx_BlinkVideoUnlessBypassedPackedAddress24, 0 },
    { 0x0, 0x0, 0x0, 0x89, 0x0, 0x0, 0x0, 0x8a }
};
typedef char g_nodeTypedWidgetEventHandlerRecordsSizeCheck[(sizeof(g_nodeTypedWidgetEventHandlerRecords) == 1968) ? 1 : -1];
#endif
#endif
