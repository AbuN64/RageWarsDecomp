#include "UI/QUAG/N64_ENG.H"
#include "COMMON/FRUSTUM.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/AIPROFILE.H"
#include "COMMON/INTEGERSTATE530.H"
#include "COMMON/CALLBACK.H"
#include "COMMON/WIDGETRECAT1A.H"
#include "COMMON/SLOTRECATCV1.H"
#include "COMMON/WIDGETRECAT34.H"
#include <ultra64.h>
#include "TYPES.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "FRONTEND/FRONTEND_OPENRESOURCEARCHIVE.H"
#include "MATH/SMSMNGR_INITIALIZESCREENMANAGER.H"
#include "RESMGR/STREAM.H"
#include "MATH/math_controller_events.H"
#include "UI/SMOS/SM_SMNGR.H"
#include "RESMGR/resmgr_string_memory.H"
#include "MENU.H"
#include "FRONTEND/NODE_FINDWIDGETBYRESOURCEID.H"

/* Refreshes the selected entry and updates its interface state. */


 /* extern */
                               /* extern */


/* Dispatches a pending menu event and clears its pending state. */


 /* extern */

 /* extern */
void Stream_DrainResourceWork(void);

 /* extern */


/* Initialises the interface system for a number of screens: resets the input state and display, allocates and clears the 0x544-byte interface state in g_screenManager with its 64 widget slots, its 900-byte object cache and its screen table, records the screen count, a 4000 limit and the frame duration from N64Eng_GetTimeSeconds, resets the focus and paging fields, and registers fonts 9 and 11. */









extern struct Record *Cache_AllocateMemory(s32 size);


/* Returns the object loaded for an identifier in the current context: reuses a cached entry whose context and identifier match and whose object still carries that identifier, and otherwise loads it through Node_FindWidgetByResourceId, counts the load in g_menuElementLoadCount with its high-water mark in g_menuElementLoadPeak, and records it while the cache holds fewer than 75 entries. */







void SmSmngr_InitializeCurrentScreen(void) {
    s32 (*callback2Value)(s32);
    s32 current;
    s32 value, param;
    current = g_screenManager->current;
    callback2Value = g_screenManager->callback2;
    param = g_screenManager->screens[current].owner;
    if (callback2Value != NULL) {
        value = callback2Value(param);
        ((struct ObjRecAt40V1 *)g_screenManager->screens[current].primary)->value = value;
    }
    DispatchCurrentScreenEvent(1, 3590, 0, 0, 0);
    DispatchCurrentScreenEvent(1, 3591, 0, 0, 0);
    g_screenManager->screens[current].data.readPosition = 0;
    DispatchCurrentScreenEvent(1, 3586, &g_screenManager->screens[current].data, 0, 0);
    StreamBufferFree(&g_screenManager->screens[current].data);
}

int SmSmngr_DeactivateCurrentScreen(int screenOwner) {
 int index,event,result; MenuActorInputView *item; int (*callback)(int,int,int,int);
 index=g_screenManager->current;
 if(index>=0 && g_screenManager->screenChangePending) {
 item=(MenuActorInputView *)g_screenManager->screens[index].focus;
 if(item) Menu_RouteElementEvent(item->input,16,0,0,0);
 event=screenOwner;
 Stream_DrainResourceWork();
 if(g_screenManager->current != -1) {
 callback=g_screenManager->callback;
 if(callback) {
 screenOwner=g_screenManager->handled;
 g_screenManager->handled=0;
 callback(3587,event,0,0);
 result=g_screenManager->handled;
 if(result==1) { g_screenManager->handled=screenOwner; goto done; }
 g_screenManager->handled=screenOwner;
 }
 DispatchCurrentScreenEvent(1,3587,event,0,0);
 }
 done:
 g_screenManager->screenChangePending=0;
 }
 return 1;
}

void SmSmngr_InitializeScreenManager(s32 screenCount, s32 value) {
    s32 i;
    f64 frames;

    g_dispatchingScreenOwner = -1;
    N64Eng_GetScreenSize(&g_screenDrawWidth, &g_screenDrawHeight);
    Node_InitializeResourceState();
    Node_SetDisplayClipBounds(g_screenDrawWidth, g_screenDrawHeight);
    Controller_AllocateControllerContext();
    g_menuEventCount = 0;
    g_screenManager = Cache_AllocateMemory(1348);
    XPlus_FillBytes(g_screenManager, 0, 1348);
    g_screenManager->callback2 = (s32 (*)(s32))value;
    g_screenManager->limit = 4000;
    {
        struct MenuHandlerEntry *slot = g_screenManager->handlers;
        s32 *ids = &g_screenManager->handlers[0].id;
        for (i = 0; i < 64; slot++, i++, ids += 5) {
            slot->override_handler = 0;
            *ids = -1;
            slot->default_handler = 0;
            slot->draw_handler = 0;
        }
    }
    g_screenManager->cache = Cache_AllocateMemory(900);
    XPlus_FillBytes(g_screenManager->cache, 0, 900);
    g_screenManager->cacheCount = 0;
    frames = N64Eng_GetTimeSeconds() * g_screenManagerFrameScale;
    g_screenManager->screenCount = screenCount;
    g_screenManager->frames = frames;
    g_screenManager->screens = Cache_AllocateMemory(screenCount * 28);
    XPlus_FillBytes(g_screenManager->screens, 0, screenCount * 28);
    g_menuScreenOwnerOverride = 0;
    g_screenManager->current = -1;
    g_screenManager->focus = -1;
    g_screenManager->eventArgument0 = 0;
    g_screenManager->eventArgument1 = 0;
    g_screenManager->paging = 1;
    SmSmngr_RegisterElementHandlers(9, Menu_KindNineDrawHandlerAddress, Menu_KindNineEventHandlerAddress, 1);
    SmSmngr_RegisterElementHandlers(11, Menu_KindElevenDrawHandlerAddress, Menu_KindElevenEventHandlerAddress, 1);
}

Element *FindMenuElement(s32 id) {
    Element *object;
    s32 context;
    s32 i;

    context = (s32)Node_GetScreenData(GetMenuScreenOwner());
    for (i = 0; i < g_screenManager->cacheCount; i++) {
        if (g_screenManager->cache[i].context == context && g_screenManager->cache[i].id == id
            && g_screenManager->cache[i].object != 0 && g_screenManager->cache[i].object->id == id) {
            return g_screenManager->cache[i].object;
        }
    }
    object = (Element *)Node_FindWidgetByResourceId((struct Tree *)context, id & 0xFFFF);
    g_menuElementLoadCount++;
    if (g_menuElementLoadPeak < g_menuElementLoadCount) {
        g_menuElementLoadPeak = g_menuElementLoadCount;
    }
    if (g_screenManager->cacheCount < 75) {
        g_screenManager->cache[g_screenManager->cacheCount].id = id;
        g_screenManager->cache[g_screenManager->cacheCount].object = object;
        g_screenManager->cache[g_screenManager->cacheCount].context = context;
        g_screenManager->cacheCount++;
    }
    return object;
}

/* Registers a widget handler under an identifier, reusing its slot or the first free one, or clears that slot when no handler is given. */
void SmSmngr_RegisterElementHandlers(s32 id, MenuElementHandler eventHandler, MenuDrawHandler draw_handler, s32 flags) {
    s32 slot = -1;
    s32 i;

    for (i = 0; i < 64; i++) {
        if (g_screenManager->handlers[i].id == id) {
            slot = i;
            break;
        }
        if (g_screenManager->handlers[i].id == -1 && slot == -1) {
            slot = i;
        }
    }
    if (eventHandler != 0) {
        g_screenManager->handlers[slot].id = id;
        g_screenManager->handlers[slot].default_handler = eventHandler;
        g_screenManager->handlers[slot].draw_handler = draw_handler;
        g_screenManager->handlers[slot].override_handler = 0;
        g_screenManager->handlers[slot].flags = flags;
    } else {
        g_screenManager->handlers[slot].id = -1;
        g_screenManager->handlers[slot].default_handler = 0;
        g_screenManager->handlers[slot].draw_handler = 0;
        g_screenManager->handlers[slot].override_handler = 0;
    }
}
