#include "MENU/BUILT_MENU.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/TEXTLAYERMETRICS.H"
#include "MENU/OPTION_AND_TEXT_LAYER_VIEWS.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/AIPROFILE.H"
#include "COMMON/S1.H"
#include "TYPES.H"
#include "MENU/PAK/MENU_CREATEMENUFROMTEMPLATE.H"
#include "ENGINE/CACHE/LIST.H"
#include "ENGINE/CACHE/LIST.H"
#include "MENU/PAK/MENU_INITIALIZEMENU.H"
#include "MENU/MENU_CREATEMENUFROMPARAMETERS.H"
extern void Cache_ReleaseResource(void *cache, void *resource);

/* Returns the address sizeof(Profile) bytes into the block at offset 0x20 of an object, or null when the
   object has no block. */

char *Menu_GetObjectDetailData(struct GamePlayerListView *object) {
    char *result = 0;

    if (object->players != 0) {
        result = object->players + sizeof(Profile);
    }
    return result;
}

/* Computes a glyph advance using character widths and special spacing before T. */
f32 Menu_GetGlyphAdvance(s32 ch, u8 next_ch, f32 scale, f32 special_advance) {
    f32 factor;
    s32 cur;
    s32 next_a;
    s32 next_b;

    cur = ch & 0xFF;
    factor = 1.0f;
    switch (cur) {
    case 36:
    case 38:
    case 126:
        return special_advance;
    case 73:
    case 105:
        factor = 0.5f;
    default:
        break;
    case 76:
    case 108:
        next_a = next_ch & 0xFF;
        if ((next_a == 116) || (next_a == 84)) {
            factor = 0.7f;
        }
        break;
    case 65:
    case 97:
        next_b = next_ch & 0xFF;
        if ((next_b == 116) || (next_b == 84)) {
            factor = 0.8f;
        }
        break;
    case 77:
    case 109:
        factor = 1.2f;
        break;
    case 33:
    case 46:
        factor = 0.4f;
        break;
    }
    return factor * scale;
}

/* Sums the glyph advances that Menu_GetGlyphAdvance returns for each character pair of a string at the given scales, stopping at a newline, the end of the string or a null pointer. */

f32 Menu_MeasureLine(u8 *p, f32 sx, f32 sy) {
    f32 total;
    u8 c;

    total = 0.0f;
    while (p != 0 && (c = *p) != 0 && c != '\n') {
        p++;
        total += Menu_GetGlyphAdvance(c, *p, sx, sy);
    }
    return total;
}

/* Returns whether Menu_CreateMenuFromParameters gives a non-zero answer for the third argument. */


s32 Menu_TryCreateMenu(void *first, void *second, void *third) {
    return Menu_CreateMenuFromParameters(third, second) != 0;
}

/* Returns zero. */
s32 Menu_ReturnZeroTemplateHook(void) {
    return 0;
}

/* Returns the word at offset 0x1C of the object that offset 0x14 of a record points to. */

s32 Menu_GetInnerMenuLock(struct Outer *outer) {
    return outer->inner->locked;
}

/* Adjusts a value from controller input and clamps or wraps it between its limits. */

unsigned int Control_IsAButtonPressed(struct ControllerProfile *profile); /* extern */
 /* extern */
 /* extern */

s32 Menu_AdjustValue(MenuValueStepView *menu,s32 value,s32 step,s32 minimum,s32 maximum,s32 wrap) {
 if(((s32 (*)(s32))Control_IsLeftPressed)(menu->flags))value-=step;
 if(((s32 (*)(s32))Control_IsRightPressed)(menu->flags)||Control_IsAButtonPressed(menu->flags))value+=step;
 if(value<minimum) {
  value=minimum;if(wrap)value=maximum;
 } else if(value>maximum) {
  value=maximum;if(wrap)value=minimum;
 }
 return value;
}

/* Steps a menu value left or right with optional range wrapping. */

 /* extern */
 /* extern */

s32 Menu_StepValue(MenuValueStepView *menu, s32 value, s32 step, s32 minimum, s32 maximum, s32 wrap) {
    s32 stepped;
    s32 current;
    s32 result;

    current = value;
    if (((s32 (*)(s32))Control_IsLeftPressed)(menu->flags) != 0) {
        current -= step;
        if (current < minimum) {
            current = minimum;
            if (wrap != 0) {
                current = maximum;
            }
        }
    }
    result = current;
    if (((s32 (*)(s32))Control_IsRightPressed)(menu->flags) != 0) {
        stepped = current + step;
        result = stepped;
        if (maximum < stepped) {
            current = maximum;
            if (wrap != 0) {
                current = minimum;
            }
            result = current;
        }
    }
    return result;
}


void Menu_InitMenuMessageList(void *object) {
    List_InitializeIntrusive(object, 464, 468);
    ((MessageList *)object)->rotation = 0;
}

/* Allocates a block sized for the entries of a list through Cache_AllocateResource, builds it with Menu_InitializeMenu from a zero and three arguments, registers it with List_PrependIntrusive and advances the owner's rotating counter below four, returning the block or zero. Adapted from Menu_AllocateMenu with the list and three values passed as arguments and a zero as the first value changed. */

extern const char g_menuText[];
extern void **Cache_AllocateResource(s32, s32, s32, char *);

MenuBuildState *Menu_OpenDialog(void *parent, MenuBuildDefinition *list, s32 player, s32 controller, s32 d) {
    struct MenuCreationOwnerView *owner;
    s32 size = list->count * sizeof(MenuBuildEntry) + sizeof(MenuBuildState);
    s32 i;
    void **block;
    MenuBuildState *first;

    for (i = 0; i < list->count; i++) {
        s32 extra = 0;
        if (list->items[i].type == 3) {
            extra = 1152;
        }
        size += extra;
    }
    block = Cache_AllocateResource(0, size, 59, g_menuText);
    if (block == 0) {
        return 0;
    }
    first = *block;
    if (first == 0) {
        return 0;
    }
    Menu_InitializeMenu(first, block, list, 0, player, (PakMenuInputStateView *)controller, d, parent);
    List_PrependIntrusive(parent, first);
    owner = parent;
    if (++owner->menuFlags >= 4) {
        owner->menuFlags = 0;
    }
    return first;
}

/* Allocates a block sized for the entries of a list (forty bytes each plus 0x480 for every entry of type three, over a 0x1D8 header) through Cache_AllocateResource, builds it with Menu_InitializeMenu from four parameters, registers it with List_PrependIntrusive and advances the owner's rotating counter below four, returning the block or zero. */

MenuBuildState *Menu_CreateMenuFromTemplate(struct MenuCreationOwnerView *owner, struct MenuTemplateParameters *params, MenuBuildDefinition *list) {
    s32 a = params->a;
    s32 b = params->b;
    s32 c = params->c;
    s32 d = params->d;
    s32 size = list->count * sizeof(MenuBuildEntry) + sizeof(MenuBuildState);
    s32 i;
    void **block;
    MenuBuildState *first;

    for (i = 0; i < list->count; i++) {
        s32 extra = 0;
        if (list->items[i].type == 3) {
            extra = 1152;
        }
        size += extra;
    }
    block = Cache_AllocateResource(0, size, 59, g_menuText);
    if (block == 0) {
        return 0;
    }
    first = *block;
    if (first == 0) {
        return 0;
    }
    Menu_InitializeMenu(first, block, list, a, b, (PakMenuInputStateView *)c, d, owner);
    List_PrependIntrusive(owner, first);
    if (++owner->menuFlags >= 4) {
        owner->menuFlags = 0;
    }
    return first;
}

/* Allocates a block sized for the entries of a list through Cache_AllocateResource, builds it with Menu_InitializeMenu from four parameters, registers it with List_PrependIntrusive and advances the owner's rotating counter below four, returning the block or zero. Adapted from Menu_CreateMenuFromTemplate with the first parameter read from offset 0x14 instead of 0x18. */

MenuBuildState *Menu_AllocateMenu(struct MenuCreationOwnerView *owner, struct ParamsPakAllocateMenu *params, MenuBuildDefinition *list) {
    s32 a = params->a;
    s32 b = params->b;
    s32 c = params->c;
    s32 d = params->d;
    s32 size = list->count * sizeof(MenuBuildEntry) + sizeof(MenuBuildState);
    s32 i;
    void **block;
    MenuBuildState *first;

    for (i = 0; i < list->count; i++) {
        s32 extra = 0;
        if (list->items[i].type == 3) {
            extra = 1152;
        }
        size += extra;
    }
    block = Cache_AllocateResource(0, size, 59, g_menuText);
    if (block == 0) {
        return 0;
    }
    first = *block;
    if (first == 0) {
        return 0;
    }
    Menu_InitializeMenu(first, block, list, a, b, (PakMenuInputStateView *)c, d, owner);
    List_PrependIntrusive(owner, first);
    if (++owner->menuFlags >= 4) {
        owner->menuFlags = 0;
    }
    return first;
}

/* Tears down every node of one list: walks it from the head, saving the successor at 0x1D4 first,
   skips nodes of kind 2 while the list is not the global one at g_matchEndingTeamWheelClose and that list's flag at
   0x10 is set, and for each remaining node asks Menu_UpdateMenuEntries whether it may go; when it may, calls
   the node's optional handler at 0xC of its table at 0x14, clears the three words at 0xB0, 0xB4 and
   0xBC of the state it owns at 0x20, unlinks it with List_RemoveIntrusive and releases its handle at 0x8
   through Cache_ReleaseResource. */
extern MessageList g_matchEndingTeamWheelClose;
extern s32 Menu_UpdateMenuEntries(MenuBuildState *menu, void *context);

void Menu_UpdateDialogList(MessageList *list) {
    MenuBuildState *node;
    MenuBuildState *next;
    PakMenuInputStateView *state;

    node = (MenuBuildState *)list->head;
    while (node != 0) {
        next = node->next;
        if (!((node->state == 2) && (list != &g_matchEndingTeamWheelClose) && (g_matchEndingTeamWheelClose.flag != 0))) {
            if (Menu_UpdateMenuEntries(node, list) != 0) {
                if (node->definition->finalize != 0) {
                    node->definition->finalize(node, list);
                }
                state = node->input;
                state->buttons = 0;
                state->pressedButtons = 0;
                state->history1 = 0;
                List_RemoveIntrusive(list, node);
                Cache_ReleaseResource(0, node->allocation);
            }
        }
        node = next;
    }
}

void Menu_DispatchMenuListCallback(struct MenuCallbackListOwner *owner) {
    struct PakMenuVirtualNode *node = owner->head;

    while (node != 0) {
        ((void (*)(struct PakMenuVirtualNode *, struct MenuCallbackListOwner *))node->vtable[4])(node, owner);
        node = node->next;
    }
}

int Menu_CountLiveNodes(struct CMenu_t **head) {
    MenuBuildState *node = (MenuBuildState *)*head;
    int count = 0;
    while (node != 0) {
        if (node->state != 4) {
            count++;
        }
        node = node->next;
    }
    return count;
}
