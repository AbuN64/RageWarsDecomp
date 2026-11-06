#include "Ui/Quag/N64_Eng.h"
#include "Common/frustum.h"
#include "Common/aiprofile.h"
#include "Common/runtime_declarations.h"
#include "Common/menu_screen_elements.h"
#include "Common/callback.h"
#include "Common/record.h"
#include "Common/widget_tree.h"
#include "Common/archive_chunk_images.h"
#include "Common/widget_texture_retention.h"
#include "types.h"
#include "Common/player_join_requests.h"
#include "Frontend/widget_findwidgetatpoint.h"
#include "Frontend/frontend_openresourcearchive.h"
#include "Ui/Smos/SM_SMngr.h"
#include "Resmgr/stream.h"
#include "Math/math_controller_events.h"
#include "Scene/cache_freememory.h"
#include "menu.h"
#include "Common/rotation_extraction.h"
#include "include_asm.h"
#include "Frontend/node_configurescrolledtablecell.h"
#include "Ui/smsmngr_initializescreenmanager.h"
#include "Frontend/widget_drawtextwidget.h"

/* Moves menu focus and sends leave and enter events through menu and element callbacks. */

static inline s32 send_event(s32 value, s32 event, s32 source, s32 amount, s32 context) {
    ScreenManager *manager;
    s32 locked;
    s32 index;
    s32 minusOne;
    s32 saved;
    s32 result;

    if (Node_IsValidScreenIndex(value) != 0) {
        if (value != g_screenManager->screens[g_screenManager->current].owner) {
            return 0;
        }
    }
    manager = g_screenManager;
    locked = manager->focus;
    index = manager->current;
    minusOne = -1;
    if ((value == locked) || (index == minusOne)) {
        return 0;
    }
    if (g_screenManager->callback != 0) {
        saved = g_screenManager->handled;
        g_screenManager->handled = 0;
        result = g_screenManager->callback(event, source, amount, context);
        if (g_screenManager->handled == 1) {
            g_screenManager->handled = saved;
            return result;
        }
        g_screenManager->handled = saved;
    }
    if (value == g_screenManager->screens[g_screenManager->current].primary->id) {
        result = SmSmngr_DispatchPrimaryScreenEvent(event, source, amount, context);
    } else {
        result = DispatchElementEvent(value, event, source, amount, context);
    }
    return result;
}

typedef s32 (*MenuEventCallback)(s32, s32, s32, s32);

void SmXlate_SwitchScreen(s32);

void Menu_PopScreen(void) {
    s32 index;

    if (g_screenManager->screens[g_screenManager->current].primary != 0) {
        SmSmngr_DeactivateCurrentScreen(g_screenManager->screens[g_screenManager->current - 1].owner);
        StreamBufferFree(&g_screenManager->screens[g_screenManager->current].data);
        {
            Element *element = g_screenManager->screens[g_screenManager->current].primary;
            Node_ReleaseReferencedBuffer(element->id);
        }
    }
    g_screenManager->screens[g_screenManager->current].primary = 0;
    g_screenManager->screens[g_screenManager->current].owner = 0;
    g_screenManager->screens[g_screenManager->current].focus = 0;
    index = g_screenManager->current - 1;
    g_screenManager->current = index;
    if (index < g_screenManager->lowIndex) {
        g_screenManager->lowIndex = index;
    }
}

void Menu_DrawScreenStack(void) {
    MenuDrawEventArgs args;
    struct WidgetRect first;
    struct WidgetRect basis;
    s32 delta;
    s32 index;
    s32 now;

    args.word0 = g_screenManager->eventArgument0;
    args.word4 = g_screenManager->eventArgument1;
    args.byte14 = 0xFF;
    args.word8 = 0;
    args.wordC = g_menuDefaultEventWord;
    args.word10 = g_menuDefaultEventWord;
    args.word18 = g_screenManager->eventArgument0;
    g_menuEventCount = 0;
    args.word20 = g_screenManager->eventArgument1;
    args.word1C = g_screenDrawWidth - 1;
    args.word24 = g_screenDrawHeight - 1;

    now = (s32)(N64Eng_GetTimeSeconds() * g_menuTimeTickScale);
    if (s_menuLastDrawTick == 0) {
        s_menuLastDrawTick = now;
    }
    delta = now - s_menuLastDrawTick;
    s_menuLastDrawTick = now;
    DispatchScreenRangeEvent(0, 3594, 0, &args, delta);

    /* Each screen from the lowest to the current one is drawn; the screen table is read again
       for every use, since a draw may move it. */
    index = g_screenManager->lowIndex;
    if (g_screenManager->current >= index) {
        s32 offset = index * sizeof(ScreenEntry);

        do {
            index++;
            N64Eng_RenderNoop();
            Widget_DrawVisibleWidgetClipped(((ScreenEntry *)(offset + (s32)g_screenManager->screens))->primary,
                                            *(sm_dldc *)&args);
            Widget_ResetTextClipBounds();
            N64Eng_ResetRenderState();
            Widget_ComputeWidgetBounds(&first, &basis,
                                       ((ScreenEntry *)(offset + (s32)g_screenManager->screens))->primary, &args);
            offset += sizeof(ScreenEntry);
        } while (g_screenManager->current >= index);
    }
    DispatchScreenRangeEvent(0, 3594, 1, 0, delta);
    g_menuElementLoadCount = 0;
}

void Menu_SetFocusedElement(s32 id) {
    Element *previous;

    if (FindKindHandler(FindMenuElement(id)->kind) == 0) {
        return;
    }
    previous = g_screenManager->screens[g_screenManager->current].focus;
    if (previous != 0) {
        send_event(previous->id, 16,0,0,0);
    }
    g_screenManager->screens[g_screenManager->current].focus = FindMenuElement(id);
    send_event(id, 15,0,0,0);
}

void Menu_DestroyScreenManager(void) {
    ScreenManager *manager;
    s32 lowIndex;
    s32 one;

    manager = g_screenManager;
    lowIndex = manager->lowIndex;
    if (manager->current >= lowIndex) {
        one = 1;
        do {
            manager->screenChangePending = one;
            Menu_PopScreen();
            manager = g_screenManager;
        } while (manager->current >= lowIndex);
    }
    if (g_screenManager->callback != 0) {
        g_screenManager->callback(3589, 0, 0, 0);
    }
    if (g_screenManager->cache != 0) {
        Cache_FreeMemory(g_screenManager->cache);
    }
    Cache_FreeMemory(g_screenManager->screens);
    Cache_FreeMemory(g_screenManager);
    g_screenManager = 0;
    Controller_FreeControllerContext();
    Node_NoOperation();
    Node_ClearResourceInitializationFlag();
}

void Menu_SetEventCallback(MenuEventCallback callback) {
    g_screenManager->callback = callback;
    if (callback != 0) {
        callback(3588, 0, 0, 0);
    }
}

void Menu_SetPagingEnabled(s32 enabled) {
    if (enabled != 0) {
        g_screenManager->paging = (s32) (g_screenManager->paging | 1);
        return;
    }
    g_screenManager->paging = (s32) (g_screenManager->paging & ~1);
}

void Menu_SetScreenOwnerOverride(int screenOwner) {
    g_menuScreenOwnerOverride = screenOwner;
}

s32 Menu_RouteElementEvent(s32 value, s32 event, s32 source, s32 control, s32 extra) {
    ScreenManager *manager;
    s32 blockedValue;
    s32 index;
    s32 minusOne;
    s32 saved;
    s32 result;
    Element *element;

    if (Node_IsValidScreenIndex(value) != 0) {
        if (value != g_screenManager->screens[g_screenManager->current].owner) {
            return 0;
        }
    }
    manager = g_screenManager;
    blockedValue = manager->focus;
    index = manager->current;
    minusOne = -1;
    if ((value == blockedValue) || (index == minusOne)) {
        return 0;
    }
    if (g_screenManager->callback != 0) {
        saved = g_screenManager->handled;
        g_screenManager->handled = 0;
        result = g_screenManager->callback(event, source, control, extra);
        if (g_screenManager->handled == 1) {
            g_screenManager->handled = saved;
            return result;
        }
        g_screenManager->handled = saved;
    }
    element = g_screenManager->screens[g_screenManager->current].primary;
    if (value == element->id) {
        result = SmSmngr_DispatchPrimaryScreenEvent(event, source, control, extra);
    } else {
        result = DispatchElementEvent(value, event, source, control, extra);
    }
    return result;
}

void MarkMenuEventHandled(void) {
    ScreenManager *object = g_screenManager;
    object->handled = 1;
}

void Menu_SetElementUserData(s32 elementId, s32 userData) {
    ((ObjRecAt40V1 *)FindMenuElement(elementId))->value = userData;
}

void Menu_SetKindEventHandler(s32 id, s32 mode, MenuElementHandler handler)
{
    s32 index = -1;
    s32 i;
    struct MenuHandlerEntry *entry = &g_screenManager->handlers[0];

    for (i = 0; i < 64; i++, entry++) {
        if (entry->id == id) {
            index = i;
            break;
        }
    }
    entry = &g_screenManager->handlers[index];
    if (mode == 1) {
        entry->default_handler = handler;
        entry->override_handler = 0;
        return;
    }
    entry->override_handler = handler;
}

/* The twenty-byte table owns callable values at +4 and +8. The override
 * takes precedence; an absent identifier yields no handler. */
MenuElementHandler FindKindHandler(s32 id)
{
    s32 i;
    s32 *key;
    struct MenuHandlerEntry *entry;

    key = &g_screenManager->handlers[0].id;
    entry = &g_screenManager->handlers[0];
    for (i = 0; i < 64; i++) {
        if (*key == id) {
            if (entry->override_handler != 0) {
                return entry->override_handler;
            }
            return entry->default_handler;
        }
        entry++;
        key += 5;
    }
    return 0;
}

s32 Menu_GetElementHandlerFlags(s32 kind)
{
  s32 count;
  struct MenuHandlerEntry *ptr;
  count = 0;
  ptr = g_screenManager->handlers;
  loop:
  if ((ptr->id) != kind)
  {
    goto not_found;
  }

  return ptr->flags;
  not_found:
  count += 1;

  ptr += 1;
  if (count < 64)
  {
    if (ptr)
    {
      goto loop;
    }
    else
    {
      goto loop;
    }
  }
  return 0;
}

void Menu_SetKindHandlerFlags(s32 kind, s32 flags) {
    s32 i;
    struct MenuHandlerEntry *handler;
    i = 0;
    handler = g_screenManager->handlers;
    do {
        if (handler->id == kind) {
            handler->flags = flags;
        }
        i += 1;
        handler++;
    } while (i < 64);
}

void Menu_ReturnToPreviousScreen(void) {
    if (g_screenManager->current > 0) {
        SmXlate_SwitchScreen(Menu_GetPreviousScreenOwner(0));
    }
}

s32 Menu_InvokeKindEventHandler(void *elementStorage, s32 event, s32 source, s32 parameter, s32 value)
{
    Element *element = elementStorage;
    MenuElementHandler handler;

    handler = FindKindHandler(element->kind);
    if (handler != 0) {
        return handler(elementStorage, event, source, parameter, value);
    }
    return 0;
}

s32 GetMenuScreenOwner(void) {
    s32 result;
    s32 screenIndex;
    result = g_dispatchingScreenOwner;
    if (result < 0) {
        screenIndex = g_screenManager->current;
        if (screenIndex < 0) {
            return -1;
        }
        result = g_screenManager->screens[screenIndex].owner;
    }
    return result;
}

s32 Menu_GetPreviousScreenOwner(s32 screenOwner) {
    s32 idx;
    s32 countMinus1;
    countMinus1 = g_screenManager->current - 1;
    idx = countMinus1 - screenOwner;
    if (idx >= 0) {
        return g_screenManager->screens[idx].owner;
    }
    return -1;
}

/** Return the number of screens on the screen stack (the current index plus one). */
unsigned int Menu_GetScreenStackDepth(void) {
    return g_screenManager->current + 1;
}

/** Return the screen that currently holds the input focus. */
unsigned int Menu_GetBlockedScreenOwner(void) {
    return g_screenManager->focus;
}

s32 Menu_GetFocusedElementId(void) {
    Element *ptr;
    ptr = g_screenManager->screens[g_screenManager->current].focus;
    if (ptr != 0) {
        return ptr->id;
    }
    return -1;
}

void Menu_SetScreenDrawOrigin(int x, int y) {
    g_screenManager->eventArgument0 = x;
    g_screenManager->eventArgument1 = y;
}

void Menu_GetScreenDrawOrigin(s32 *xOut, s32 *yOut) {
    *xOut = g_screenManager->eventArgument0;
    *yOut = g_screenManager->eventArgument1;
}
