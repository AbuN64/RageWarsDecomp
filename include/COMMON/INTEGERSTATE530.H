#ifndef COMMON_INTEGERSTATE530_H
#define COMMON_INTEGERSTATE530_H
#include "TYPES.H"
#include "COMMON/CALLBACK.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/AIPROFILE.H"
#include "COMMON/RESIDENT_EVENT_HANDLER.H"



extern void Menu_ReturnToPreviousScreen(void);


typedef s32 (*MenuElementHandler)(void *element, s32 event, s32 eventPayload, s32 eventValue, s32 eventExtra);

struct Element;
struct ScreenEventTreeNode;
struct Element {
    char pad0[4];
    struct ScreenEventTreeNode *left; /* 0x4 */
    struct ScreenEventTreeNode *right; /* 0x8 */
    s16 id;
    u16 kind;
    u16 reservedHalfword10;
    u16 flags;
    u8 unobserved14[0x3C - 0x14];
    s32 linked_id;
    MenuElementHandler handler;
};

struct ScreenManager;
typedef struct ScreenManager ScreenManager;




struct Element;
typedef struct Element Element;




extern void Menu_PopScreen(void);

/* Draw providers use several existing aggregate declarations. Registration
 * stores these functions; this type does not prescribe a call signature. */
typedef void (*MenuDrawHandler)();

struct MenuHandlerEntry {
    s32 id;
    MenuElementHandler default_handler;
    MenuElementHandler override_handler;
    MenuDrawHandler draw_handler;
    s32 flags;
};


extern void Menu_SetKindEventHandler(s32 id, s32 mode, MenuElementHandler handler);


extern int g_dispatchingScreenOwner;

struct MenuObjectContextEntry;
struct MenuObjectContextEntry {
    s32 id;
    struct Element *object;
    s32 context;
};
struct MenuObjectContextEntry;

extern void Menu_DestroyScreenManager(void);

struct Widget;
struct Widget {
    struct Widget *parent;
    struct Widget *next;
    struct Widget *child;
    s16 id;
    u16 kind;
    u16 reservedHalfword10;
    u16 flags;
    s16 x, y, width, height;
    s16 offsetX, offsetY;
    f32 scaleX, scaleY;
    s32 scaled;
    struct Widget *links[4];
};

struct Screen;
struct Widget;
struct Screen {
    char pad0[8];
    struct Widget *focus;
    char padC[0x1C - 0xC];
};
struct Screen;

extern int g_screenDrawWidth;



extern double g_menuTimeTickScale;


struct ScreenManager;



struct ScreenManager;

extern s32 Menu_InvokeKindEventHandler(void *widget, s32 event, s32 itemId, s32 value, s32 context);

extern unsigned int Menu_GetScreenStackDepth(void);

extern int g_screenDrawHeight;



extern void Menu_SetPagingEnabled(s32 enabled);

struct ScreenManager;

extern double g_screenManagerFrameScale;

extern float g_menuDefaultEventWord;


struct ObjRecAt40V1;


extern MenuElementHandler FindKindHandler(s32 kind);

struct MenuDrawEventArgs;

extern int s_smackFormat;


struct Element;
struct EntrySmosSetFocusedElement;
struct EntrySmosSetFocusedElement {
    struct Element *primary;
    s32 owner;
    struct Element *focus;
    StreamBuffer data;
};
typedef struct EntrySmosSetFocusedElement ScreenEntry;
struct EntrySmosSetFocusedElement;
struct ScreenManager;



extern int g_menuElementLoadPeak;

extern void Menu_SetKindHandlerFlags(s32 kind, s32 flags);


extern void Menu_DrawScreenStack(void);

struct ScreenManager;
struct ScreenManager {
    s32 (*callback)(s32 event, s32, s32, s32);
    s32 current;
    s32 lowIndex;
    ScreenEntry *screens;
    s32 (*callback2)(s32);
    s32 limit;
    s32 screenCount;
    struct MenuHandlerEntry handlers[64];
    char pad51C[0x4];
    s32 handled;
    s32 frames;
    s32 focus;
    s32 paging;
    s32 screenChangePending;
    s32 eventArgument0;
    s32 eventArgument1;
    struct MenuObjectContextEntry *cache;
    s32 cacheCount;
};
extern ScreenManager *g_screenManager;

struct MenuDrawEventArgs;
typedef struct MenuDrawEventArgs MenuDrawEventArgs;


struct Widget;
typedef struct Widget Widget;



/* Callable low-address aliases of the native code providers. The cartridge
 * registers these entry addresses, not overlay file ranges or data objects. */
/* N64Eng_DispatchNumericWidgetEvent_Address: N64Eng_DispatchNumericWidgetEvent */
extern s32 N64Eng_DispatchNumericWidgetEvent_Address(void *, s32, s32, s32, s32);
/* N64Eng_DrawNumericWidgetChildren_Address: N64Eng_DrawNumericWidgetChildren */
extern void N64Eng_DrawNumericWidgetChildren_Address();
/* Menu_KindNineDrawHandlerAddress: second return stub in Menu_ReturnStubPairGerman (+8) */
extern s32 Menu_KindNineDrawHandlerAddress(void *, s32, s32, s32, s32);
/* Menu_KindNineEventHandlerAddress: Menu_DrawClippedWidgetSiblings */
extern void Menu_KindNineEventHandlerAddress();
/* Menu_KindElevenDrawHandlerAddress: Node_DispatchTypedWidgetEvent */
extern s32 Menu_KindElevenDrawHandlerAddress(void *, s32, s32, s32, s32);
/* Menu_KindElevenEventHandlerAddress: Node_DrawGridListCells */
extern void Menu_KindElevenEventHandlerAddress();
/* g_SmpFrameAnim_DispatchEventAddress: SmpFrameAnim_DispatchEvent */
extern s32 g_SmpFrameAnim_DispatchEventAddress(void *, s32, s32, s32, s32);
/* g_SmpFrameAnim_IgnoreEventAddress: SmpFrameAnim_IgnoreEvent */
extern void g_SmpFrameAnim_IgnoreEventAddress();
/* g_SmpFlicker_DispatchEventAddress: SmpFlicker_DispatchEvent */
extern s32 g_SmpFlicker_DispatchEventAddress(void *, s32, s32, s32, s32);
/* g_SmpFlicker_IgnoreEventAddress: SmpFlicker_IgnoreEvent */
extern void g_SmpFlicker_IgnoreEventAddress();
/* g_SmpSlider_DispatchTransitionEventAddress: SmpSlider_DispatchTransitionEvent */
extern s32 g_SmpSlider_DispatchTransitionEventAddress(void *, s32, s32, s32, s32);
/* g_SmpSlider_IgnoreFormattedMessageAddress: SmpSlider_IgnoreFormattedMessage */
extern void g_SmpSlider_IgnoreFormattedMessageAddress();
/* g_SmpSlider_DispatchSliderEventAddress: SmpSlider_DispatchSliderEvent */
extern s32 g_SmpSlider_DispatchSliderEventAddress(void *, s32, s32, s32, s32);
/* g_SmpSlider_DrawSliderWidgetAddress: SmpSlider_DrawSliderWidget_Integerstate530 */
extern void g_SmpSlider_DrawSliderWidgetAddress();
/* g_SmpButton_DispatchListEventAddress: SmpButton_DispatchListEvent */
extern s32 g_SmpButton_DispatchListEventAddress(void *, s32, s32, s32, s32);
/* g_SmpButton_DrawListWidgetAddress: SmpButton_DrawListWidget_Integerstate530 */
extern void g_SmpButton_DrawListWidgetAddress();
/* g_SmpButton_DispatchButtonEventAddress: SmpButton_DispatchButtonEvent */
extern s32 g_SmpButton_DispatchButtonEventAddress(void *, s32, s32, s32, s32);
/* g_SmpButton_DrawButtonWidgetAddress: SmpButton_DrawButtonWidget_Integerstate530 */
extern void g_SmpButton_DrawButtonWidgetAddress();
/* g_SmpOverlay_DispatchSlotEventAddress: SmpOverlay_DispatchSlotEvent */
extern s32 g_SmpOverlay_DispatchSlotEventAddress(void *, s32, s32, s32, s32);
/* g_SmpOverlay_DrawOverlayWidgetAddress: SmpOverlay_DrawOverlayWidget_FrontendOpenresourcearchive */
extern void g_SmpOverlay_DrawOverlayWidgetAddress();

extern s32 GetMenuScreenOwner(void);
#endif
