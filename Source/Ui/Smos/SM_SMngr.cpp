#include "include_asm.h"
#include "Common/rotation_extraction.h"
#include "Common/frustum.h"
#include "Common/menu_screen_elements.h"
#include "types.h"
#include "Ui/Smos/SM_SMngr.h"
#include "Frontend/widget_findwidgetatpoint.h"
#include "Common/runtime_declarations.h"
#include "Common/callback.h"
#include "Common/screen.h"
#include "Common/shared_menureply.h"
#include "Ui/smsmngr_initializescreenmanager.h"
#include "Ui/smos_screen_events.h"
#include "Ui/Quag/N64_Eng.h"
#include "Math/shared_widgetide.h"
#include "Common/audio_callbacks.h"
#include "Common/triple.h"
#include "Common/aiprofile.h"
#include "Common/widget_tree.h"
#include "Common/archive_chunk_images.h"
#include "Common/widget_texture_retention.h"
#include <platform_sdk.h>
#include "Frontend/frontend_openresourcearchive.h"
#include "Math/smsmngr_initializescreenmanager.h"
#include "Resmgr/stream.h"
#include "Math/math_controller_events.h"
#include "Resmgr/resmgr_string_memory.h"
#include "menu.h"
#include "Frontend/node_findwidgetbyresourceid.h"
#include "Common/selectionscreenstate.h"
#include "Data/rest_source_records.h"
#include "Frontend/frontend.h"

const float k_SmSmngrEncodedWords[2] = {
    4.4765625f, 0.0f,
};

/* Moves the focus of the current screen's selected widget in a direction (5 to 8 following its first, second, third or fourth link) past linked widgets flagged 0x100, and selects the first unflagged one through Menu_SetFocusedElement. */

void MoveMenuFocus(s32 direction) {
    Widget *widget;
    Widget **links;
    s32 id;

    widget = (Widget *)g_screenManager->screens[g_screenManager->current].focus;
    id = -1;
    links = widget->links;
    if (widget == 0 || !(widget->flags & 0x10)) {
        return;
    }
    switch (direction) {
    case 5:
        while (links[0] != 0) {
            widget = links[0];
            if (!(widget->flags & 0x100)) {
                goto found;
            }
            links = widget->links;
        }
        break;
    case 6:
        while (links[1] != 0) {
            widget = links[1];
            links = widget->links;
            if (!(widget->flags & 0x100)) {
                goto found;
            }
        }
        break;
    case 7:
        while (links[2] != 0) {
            widget = links[2];
            links = widget->links;
            if (!(widget->flags & 0x100)) {
                goto found;
            }
        }
        break;
    found:
        id = widget->id;
        break;
    case 8:
        while (links[3] != 0) {
            widget = links[3];
            links = widget->links;
            if (!(widget->flags & 0x100)) {
                goto found;
            }
        }
        break;
    }
    if (id >= 0) {
        Menu_SetFocusedElement(id);
    }
}

static inline s32 eventCategory(u32 event) {
    if (event < 3584) return 0;
    if (event - 4096 < 4096) return 1;
    if (event - 3584 < 512) return 2;
    if (event - 16384 < 16384) return 3;
    return 0;
}

/* Unhandled default events return zero, regardless of previous callback results. */
static inline s32 defaultElementEvent(Element *element, s32 event, s32 argument) {
    s32 result;
    s32 fallbackCategory;
    result = 0;
    fallbackCategory = eventCategory(event);
    switch (fallbackCategory) {
    case 0:
        switch (event) {
        case 5: case 6: case 7: case 8:
            if (argument == 1) MoveMenuFocus(event);
            break;
        case 1:
            if ((element->flags & 0x10) && element->linked_id) {
                MarkMenuEventHandled();
                SmXlate_SwitchScreen(element->linked_id);
            }
            break;
        case 2:
            if (g_screenManager->current > 0) Menu_ReturnToPreviousScreen();
            break;
        case 15:
            result = 0;
            Widget_SetWidgetFlag40(element, 1);
            break;
        case 16:
            result = 0;
            Widget_SetWidgetFlag40(element, 0);
            break;
        default:
            result = 0;
            break;
        }
        break;
    case 1: result = 0; break;
    case 2: result = 0; break;
    case 3: result = 0; break;
    }    return result;
}

/* Sends an event to element id (-1: the screen owner itself) through the owner, the element and its kind handler;
 * the first that sets the handled flag wins, otherwise the default actions run. */
s32 DispatchElementEvent(s32 id, s32 event, s32 value, s32 argument, s32 context)
{
    Element *element, *owner, *current;
    MenuElementHandler kindHandler, handler;
    s32 result, category, previous;
    s32 direct;
    s32 *handled;

    result = 0;
    element = 0;
    kindHandler = 0;
    direct = 0;
    if (event != 3593) g_menuEventCount++;
    handled = &g_screenManager->handled;
    category = eventCategory(event);
    owner = Node_GetScreenData(GetMenuScreenOwner());
    if (id == -1) {
        direct = 1;
        element = owner;
    }
    if (!direct) {
        element = FindMenuElement(id);
        if (!element) return 0;
        kindHandler = FindKindHandler(element->kind);
        if (!kindHandler) {
            switch (eventCategory(event)) {
            case 0:
                switch (event) {
                case 5: case 6: case 7: case 8:
                    if (argument == 1) MoveMenuFocus(event);
                    break;
                case 1:
                    if ((element->flags & 0x10) && element->linked_id) {
                        MarkMenuEventHandled();
                        SmXlate_SwitchScreen(element->linked_id);
                    }
                    break;
                case 2:
                    if (g_screenManager->current > 0) Menu_ReturnToPreviousScreen();
                    break;
                case 15:
                    Widget_SetWidgetFlag40(element, 1);
                    break;
                case 16:
                    Widget_SetWidgetFlag40(element, 0);
                    break;
                default:
                    return 0;
                }
                break;
            case 1:
                return 0;
            case 2:
                return 0;
            case 3:
                return 0;
            }
            return 0;
        }
    }

    previous = *handled;
    *handled = 0;
    if (owner->handler) result = owner->handler(element, event, value, argument, context);
    if (*handled == 1) { *handled = previous; return result; }
    if (!direct) {
        if (category != 2) {
            if (owner->handler) result = owner->handler(owner, event, value, argument, context);
            if (*handled == 1) { *handled = previous; return result; }
        }
        current = FindMenuElement(id);
        handler = 0;
        if (current) handler = current->handler;
        if (handler) result = handler(element, event, value, argument, context);
        if (*handled == 1) { *handled = previous; return result; }
        if (kindHandler) result = kindHandler(element, event, value, argument, context);
        if (*handled == 1) { *handled = previous; return result; }
    }
    result = defaultElementEvent(element, event, argument);

    *handled = previous;
    return result;
}

static inline s32 Menu_GetDispatchCategory(u32 code) {
    if (code < 3584) return 0;
    if (code - 4096 < 4096) return 1;
    if (code - 3584 < 512) return 2;
    if (code - 16384 < 16384) return 3;
    return 0;
}
static inline s32 Menu_DispatchDefaultEvent(Element *element, s32 event, s32 argument) {
    s32 result = 0;
    switch (Menu_GetDispatchCategory(event)) {
    case 0:
        switch (event) {
        case 5: case 6: case 7: case 8:
            if (argument == 1) MoveMenuFocus(event);
            break;

        case 1:
            if ((element->flags & 0x10) && element->linked_id != 0) {
                MarkMenuEventHandled();
                SmXlate_SwitchScreen(element->linked_id);
            }
            break;
        case 2:
            if (g_screenManager->current > 0) Menu_ReturnToPreviousScreen();
            break;
        case 15: result = 0; Widget_SetWidgetFlag40(element, 1); break;
        case 16: result = 0; Widget_SetWidgetFlag40(element, 0); break;
        default: result = 0; break;
        }
        break;
    case 1:
        result = 0;
        break;
    case 2:
        result = 0;
        break;
    case 3:
        result = 0;
        break;
    }
    return result;
}
static inline void Menu_DispatchChildEvents(Element *element, s32 event, s32 value, s32 argument, s32 context) {
    ScreenManager *tree;
    s32 treeSaved;
    s32 *treeHandled;
    if (element != 0) {
        tree = g_screenManager;
        treeHandled = &tree->handled;
        treeSaved = tree->handled;
        tree->handled = 0;
        if (element->left != 0) Smos_DispatchDescendantScreenEvent(element->left, event, value, argument, context, 1);
        if (tree->handled == 0 && element->right != 0) Smos_DispatchDescendantScreenEvent(element->right, event, value, argument, context, 1);
        *treeHandled = treeSaved;
    }
}
/* Sends an event through the menu callback, the current screen's primary element and (recurse) its child
 * trees, restoring each dispatcher's handled flag; unhandled events get the default actions. */
s32 DispatchCurrentScreenEvent(s32 recurse, s32 event, s32 value, s32 argument, s32 context)
{
    ScreenManager *table = g_screenManager;
    s32 *handledFlag = &table->handled;
    Element *element = table->screens[table->current].primary;
    MenuElementHandler handler;
    s32 result = 0;
    s32 saved, handled;
    if (table->callback != 0) {
        saved = table->handled;
        table->handled = 0;
        result = table->callback(event, value, argument, context);
        handled = table->handled;
        table->handled = saved;
        if (handled == 1) return result;
    }
    handler = g_screenManager->screens[g_screenManager->current].primary->handler;
    if (handler != 0) {
        saved = *handledFlag;
        *handledFlag = 0;
        result = handler(element, event, value, argument, context);
        if (*handledFlag == 1) {
            *handledFlag = saved;
            return result;
        }
        *handledFlag = saved;
    }
    if (recurse != 0) {
        saved = *handledFlag;
        *handledFlag = 0;
        Menu_DispatchChildEvents(element, event, value, argument, context);
        if (*handledFlag == 1) {
            *handledFlag = saved;
            return result;
        }
        *handledFlag = saved;
    }
    result = Menu_DispatchDefaultEvent(element, event, argument);
    return result;
}

/* Sends an event to every screen from lowIndex to the current one: the menu callback first, then each screen's
 * primary element handler, its child trees (recurse) and the default actions, restoring the handled flags. */
s32 DispatchScreenRangeEvent(s32 recurse, s32 event, s32 value, void *argument, s32 context) {
    ScreenManager *table = g_screenManager;
    s32 *handledFlag = &table->handled;
    Element *element;
    MenuElementHandler handler;
    s32 result = 0;
    s32 saved;
    s32 first, last;
    if (table->callback != 0) {
        saved = table->handled;
        table->handled = 0;
        result = table->callback(event, value, (s32)argument, context);
        if (table->handled == 1) {
            table->handled = saved;
            return result;
        }
        table->handled = saved;
    }
    first = g_screenManager->lowIndex;
    last = g_screenManager->current;
    for (; first <= last; first++) {
        switch (event) {
        case 3585:
        case 3586:
            value = (intptr_t)&g_screenManager->screens[first].data;
            break;
        }
        element = g_screenManager->screens[first].primary;
        handler = element->handler;
        if (handler != 0) {
            saved = *handledFlag;
            *handledFlag = 0;
            result = handler(element, event, value, (s32)argument, context);
            if (*handledFlag == 1) {
                *handledFlag = saved;
                return result;
            }
            *handledFlag = saved;
        }
        if (recurse != 0) {
            g_dispatchingScreenOwner = g_screenManager->screens[first].owner;
            saved = *handledFlag;
            *handledFlag = 0;
            Menu_DispatchChildEvents(element, event, value, (s32)argument, context);
            g_dispatchingScreenOwner = -1;
            if (*handledFlag == 1) {
                *handledFlag = saved;
                return result;
            }
            *handledFlag = saved;
        }
        result = Menu_DispatchDefaultEvent(element, event, (s32)argument);
    }
    return result;
}

static inline s32 menuCategory(s32 event) {
    s32 category;
    if ((u32)event < 3584) category=0;
    else if ((u32)(event-4096)<4096) category=1;
    else if ((u32)(event-3584)<512) category=2;
    else if ((u32)(event-16384)<16384) category=3;
    else category=0;
    return category;
}
s32 SmSmngr_DispatchPrimaryScreenEvent(s32 event,s32 value,s32 amount,s32 context) {
    s32 *handled;
    Element *element;
    Element *focus;
    s32 result;
    s32 category;
    s32 saved;
    s32 focusId;
    s32 ticks;
    MenuElementHandler handler;
    handled=&g_screenManager->handled;
    element=g_screenManager->screens[g_screenManager->current].primary;
    result=0;
    GetMenuScreenOwner();
    category=menuCategory(event);
    switch(category) {
    case 0:
        focus=g_screenManager->screens[g_screenManager->current].focus;
        focusId=focus ? focus->id : -1;
        result=DispatchElementEvent(focusId,event,value,amount,context);
        break;
    case 2:
        if(event==3592) {
            ticks=(s32)(N64Eng_GetTimeSeconds()*g_primaryScreenEventTickScale);
            value=ticks-g_screenManager->frames;
            amount=ticks;
            g_screenManager->frames=amount;
        }
        saved=*handled;
        *handled=0;
        /* This dispatch passes a scalar event word as its fourth ABI argument. */
        ((void (*)(s32,s32,s32,s32,s32))DispatchScreenRangeEvent)(1,event,value,amount,context);
        *handled=saved;
        break;
    case 1:
    case 3:
        saved=*handled;
        *handled=0;
        handler=g_screenManager->screens[g_screenManager->current].primary->handler;
        if(handler != 0)
            result=handler(element,event,value,amount,context);
        if(*handled==0) {
            value=0;
            category=menuCategory(event);
            switch(category) {
            case 0:
                switch(event) {
                case 5: case 6: case 7: case 8:
                    if(amount==1) MoveMenuFocus(event);
                    result=value;
                    break;
                case 1:
                    result=value;
                    if(element->flags & 0x10) {
                        if(element->linked_id) {
                            MarkMenuEventHandled();
                            SmXlate_SwitchScreen(element->linked_id);
                        }
                    }
                    break;
                case 2:
                    result=value;
                    if(g_screenManager->current>0) Menu_ReturnToPreviousScreen();
                    break;
                case 15:
                    value=0;
                    Widget_SetWidgetFlag40(element,1);
                    result=value;
                    break;
                case 16:
                    value=0;
                    Widget_SetWidgetFlag40(element,value);
                    result=value;
                    break;
                case 3: case 4: case 9: case 10: case 11: case 12: case 13: case 14:
                    value=0;
                    break;
                default:
                    value=0;
                    result=value;
                    break;
                }
                break;
            case 1: value=0; break;
            case 2: value=0; break;
            case 3: value=0; break;
            default: break;
            }
            result=value;
        }
        *handled=saved;
        break;
    }
    return result;
}

/* Refreshes the selected entry and updates its interface state. */


/* Dispatches a pending menu event and clears its pending state. */


void Stream_DrainResourceWork(void);


/* Initialises the interface system for a number of screens: resets the input state and display, allocates and clears the interface state in g_screenManager with its 64 widget slots, its 900-byte object cache and its screen table, records the screen count, a 4000 limit and the frame duration from N64Eng_GetTimeSeconds, resets the focus and paging fields, and registers fonts 9 and 11. */

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
 int index,event,result; MenuWidget *item; int (*callback)(int,int,int,int);
 index=g_screenManager->current;
 if(index>=0 && g_screenManager->screenChangePending) {
 item=(MenuWidget *)g_screenManager->screens[index].focus;
 if(item) Menu_RouteElementEvent(item->resource,16,0,0,0);
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

const float g_SmSmngr_InitializeScreenManagerConstants[2] = {
    4.4765625f, 0.0f,
};

#ifdef VERSION_DE
float s_smackFormat[4] = {
    0.0f, 3.1415927f, 0.0f, -3.1415927f,
};
#endif
#ifdef VERSION_EU
RestSmackFormat s_smackFormat = {
    { 0, 0 },
    { -1.0f, -0.70710677f }
};
#endif
#ifdef VERSION_EU_X
char s_smackFormat[16] = "\000\000\000\000re\000\000Energy r";
#endif
#ifdef VERSION_US
RestSmackFormatVariant2 s_smackFormat = {
    0,
    "quR\000",
    { 14223616, 1048587 }
};
#endif
#ifdef VERSION_US_REV1
char s_smackFormat[16] = "\000\000\000\000\000\000\000\000Smack %s";
#endif
