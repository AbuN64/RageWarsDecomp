#include "include_asm.h"
#include "COMMON/OBJRECAT3CV2.H"
#include "COMMON/FRUSTUM.H"
#include "COMMON/INTEGERSTATE530.H"
#include "TYPES.H"
#include "UI/SMOS/SM_SMNGR.H"
#include "FRONTEND/WIDGET_FINDWIDGETATPOINT.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/CALLBACK.H"

/* 800CA60C_5.CPP */
/* ROM-grounded us-rev1 data; explicit withholding in other holders. */
const float k_SmSmngrEncodedWords[2] = {
    4.4765625f, 0.0f,
};

/* 80297CD0.CPP */
/* Moves the focus of the current screen's selected widget in a direction (5 to 8 following its first, second, third or fourth link) past linked widgets flagged 0x100, and selects the first unflagged one through Menu_SetFocusedElement. */

extern void Menu_SetFocusedElement(s32 id, Widget **links, s32 direction);

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
        Menu_SetFocusedElement(id, links, direction);
    }
}

extern Element *FindMenuElement(s32);
extern void MarkMenuEventHandled(void);
extern void SmXlate_SwitchScreen(s32);

static inline s32 eventCategory(u32 event) {
    if (event < 3584) return 0;
    if (event - 4096 < 4096) return 1;
    if (event - 3584 < 512) return 2;
    if (event - 16384 < 16384) return 3;
    return 0;
}

/* Unhandled default events return zero, regardless of earlier callback results. */
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

extern void Smos_DispatchDescendantScreenEvent(ScreenEventTreeNode *, s32, s32, s32, s32, s32);
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
            value = (s32)&g_screenManager->screens[first].data;
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
