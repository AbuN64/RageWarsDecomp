#include "COMMON/GAMEPLAY_CAMERA.H"
#include "include_asm.h"
#include "COMMON/LONE/G_LANGUAGEINDEX.H"
#include "MENU/OBJECT1C8.H"
#include "COMMON/ITEMRECAT20V1.H"
#include <PR/gbi.h>
#include <ultra64.h>
#include "COMMON/FONT_STYLE_AND_GLYPH_OPERATIONS.H"
#include "TYPES.H"
#include "COMMON/CACHE_RELEASERESOURCE.H"
#include "COMMON/SESSIONHANDLERROW.H"
#include "MENU/ITEMS/MENU_DRAWANIMATEDMENUSPRITE.H"
#include "ENGINE/CACHE/LIST.H"
#include "GFX/TEXT/ONSCREEN_DRAWSCALEDMASKEDTILEGRID.H"

/* Removes every item from a list until its head is null, running each item's optional callback, clearing three words of its state, unlinking it through List_RemoveIntrusive and releasing its resource through Cache_ReleaseResource. Adapted from Items_DestroyMenu_MenuDrawanimatedmenusprite with its body wrapped as an inline helper called in a loop over the list head changed. */










static inline void remove_item(struct ListPakClearMenuItemList *list, struct MenuResourceItemView *item) {
    struct MenuItemInputStateView *state;

    if (item->handlers->callback != 0) {
        item->handlers->callback(item, list);
    }
    state = item->state;
    state->a = 0;
    state->b = 0;
    state->c = 0;
    List_RemoveIntrusive(list, item);
    Cache_ReleaseResource(0, item->resource);
}

#if defined(VERSION_EU) || defined(VERSION_EU_X)
#endif

/* Hands Menu_MeasureLine a target and the scale twice: the target is what Menu_GetDynamicItemText returns for
   an object of kind 5, otherwise the word the pointer at offset 0x14 addresses. */


#if defined(VERSION_DE) || defined(VERSION_EU) || defined(VERSION_EU_X) || defined(VERSION_US) || defined(VERSION_US_REV1)
extern u8 *Menu_GetDynamicItemText(struct TextBoundsText *);
#else
extern void * Menu_GetGermanDynamicItemText(struct MenuItemTargetView *);
#endif

extern f32 Menu_MeasureLine(u8 *p, f32 sx, f32 sy);

/* Draws a pulsing sprite for an active menu element: when the word at 0x1CC is set, it takes the frame at 0x1C8 folded back after 23, sets up drawing through OnScreen_SetupTextRendering and Geometry_SetModePreset, emits a yellow environment and primitive colour to the display list and draws sprite 0x67 at the owner's rectangle scaled to the screen through OnScreen_DrawSpriteResource. Adapted from Playerai_DrawHudSprite1FB. */



extern s32 Geometry_SetModePreset(s32);

/* Selects the descriptor for a single masked category bit; on eu and eu-x the slot is
   additionally offset by nine descriptors per local player, read from the byte after g_frontendSavedVideoModeIndex. */

extern char g_menuFontStyles[];


/* Steps a pointer back 0x554 bytes: callers pass the pointer held at offset 0x44 of an object and
   get back the start of the structure whose member at offset 0x554 it addresses. */
void *Menu_GetListContext(s8 *member) {
    return member - ((char *)&((GameplayCamera *)0)->messageList - (char *)0);
}

void Menu_ClearMenuItemList(struct ListPakClearMenuItemList *list) {
    struct MenuResourceItemView *item;

loop:
    item = list->head;
    if (item != 0) {
        remove_item(list, item);
        goto loop;
    }
}

void Menu_MeasureMenuItemText(struct MenuItemTargetView *object, f32 scale) {
    void *target;

    if (object->kind == 5) {
        target =
#if defined(VERSION_DE) || defined(VERSION_EU) || defined(VERSION_EU_X) || defined(VERSION_US) || defined(VERSION_US_REV1)
Menu_GetDynamicItemText
#else
Menu_GetGermanDynamicItemText
#endif
(object);
    } else {

#if defined(VERSION_EU) || defined(VERSION_EU_X)
        target = object->target[g_languageIndex];
#else
        target = *object->target;
#endif
    }
    Menu_MeasureLine(target, scale, scale);
}

/* Clears the two words at offsets 0x1C8 and 0x1CC of an object; Menu_StartMenuPulse_MenuDrawanimatedmenusprite, which follows it,
   tests the word at 0x1CC. */


void Menu_StopMenuPulse(struct Object1C8 *object) {
    object->second = 0;
    object->first = 0;
}

/* Starts a one-shot state: when the word at offset 0x1CC is clear it sets it and clears the word
   at 0x1C8; Menu_StopMenuPulse_MenuDrawanimatedmenusprite clears both. */


void Menu_StartMenuPulse(struct Object1C8 *object) {
    if (object->second == 0) {
        object->second = 1;
        object->first = 0;
    }
}

/* Advances the counter at offset 0x1C8 of an object by the step at 0x1CC and clears both once
   the counter reaches 0x30. */


void Menu_StepSpriteFrame(struct Object1C8 *object) {
    object->first += object->second;
    if (object->first >= 48) {
        object->first = 0;
        object->second = 0;
    }
}

/* Folds the counter at offset 0x1C8 of an object into a triangle wave: values below 0x18 are
   returned as they are and the rest as 0x2F less the value. */


s32 Menu_GetMirroredMenuFrame(struct MenuItemCountView *object) {
    s32 count = object->count;

    if (count < 24) {
        return count;
    }
    return 47 - count;
}

void Menu_DrawAnimatedMenuSprite(MenuSpriteElement *e) {
    s32 frame;
    Gfx *gfx;
    Shared_HudView *o;
    f32 w;
    f32 h;

    if (e->active != 0) {
        if (e->frame < 24) {
            frame = e->frame;
        } else {
            frame = 47 - e->frame;
        }
        OnScreen_SetupTextRendering();
        Geometry_SetModePreset(21);
        o = e->owner;
        gfx = g_displayListCursor++;
        w = o->width;
        h = o->height;
        gDPSetEnvColor(gfx, 255, 0, 0, 255);
        gfx = g_displayListCursor++;
        gDPSetPrimColor(gfx, 0, 0, 224, 0, 0, 255);
        OnScreen_DrawSpriteResource(103, frame, e->owner->x, e->owner->y,
                      w / (f32)g_hudReferenceViewportWidth * 5.0f, h / (f32)g_hudReferenceViewportHeight * 4.0f, 1);
    }
}

/* Returns 0x480 when the halfword a record starts with is 3, otherwise zero. */
s32 Menu_GetMenuItemExtraSize(s16 *record) {
    if (*record == 3) {
        return 1152;
    }
    return 0;
}

/* Sets the word at offset 0x478 of the second argument when the halfword the first starts with
   is 3. */


void Menu_EnableMenuItemExtra(s16 *record, struct MenuItemVisibilityFlagView *object) {
    if (*record == 3) {
        object->flag = 1;
    }
}

/* Initializes a widget from its descriptor and reserves extra state for type three widgets. */





void Menu_InitMenuItemFromDescriptor(CMenuItem *w, WidgetDescriptor *d, char **arena, int id, int arg) {
 int size; char *extra;
 w->id=id; w->type=d->type; w->flags=d->flags|0x1800000;
 w->x=d->x; w->y=d->y; w->r=d->r; w->g=d->g; w->b=d->b; w->a=d->a;
 w->value=d->value; w->desc=d; w->index=-1; w->m_pMenu=arg;
 size=0; if(d->type==3) size=1152;
 if(size) {
 w->extra=*arena;
 extra=*arena; if(d->type==3) ((struct MenuItemVisibilityFlagView *)(extra))->flag=1;
 { int step=0; if(d->type==3) step=1152;
 *arena+=step; }
 }
}

void *Menu_GetWidgetStyle(MenuItemFlagsView *widget) {
 s32 index=0;
 switch(widget->flags & 0x3fe0) {
 case 32: break;
 case 64: index=1; break;
 case 128: index=2; break;
 case 0x100: index=3; break;
 case 0x200: index=4; break;
 case 0x400: index=5; break;
 case 0x800: index=6; break;
 case 0x1000: index=7; break;
 case 0x2000: index=8; break;
 default: index=0; break;
 }
#if defined(VERSION_EU) || defined(VERSION_EU_X)
 index += (&g_frontendSavedVideoModeIndex)[1] * 9;
#endif
 return g_menuFontStyles+index*28;
}
