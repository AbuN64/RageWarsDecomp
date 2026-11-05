#include "Menu/pak_records.h"
#include "Common/session_state.h"
#include "Menu/menu_item_views.h"
#include "types.h"
#include "Common/runtime_declarations.h"
#include "Menu/bound.h"
#include "Common/particle_lighting.h"
#include "include_asm.h"
#include "Render/material_color_and_fog_views.h"
#include "Common/weapon_marker_and_profile_views.h"
#include "Common/cache_releaseresource.h"
#include "Menu/Items/items_invokehandlerandclearitemstate.h"
#include "Menu/Pak/menu_initializemenu.h"
#include "Engine/Cache/list.h"
#include "Menu/Items/items_createmenu.h"
#include "Gobjinst/gobjinst_buildactortransform.h"
#include "Gobjinst/player_drawtintedplayer_data.h"
#include "Menu/Pak/menu_createmenufromtemplate.h"
#include "Common/cache_allocateresource.h"
#include "Menu/g_menutext.h"
#include "Menu/identifier.h"
#include "Menu/Items/items_symbols.h"
#include "Menu/pak_load.h"

#if defined(VERSION_DE) || defined(VERSION_US)
f32 Bound_ReadBoundValue(MenuBindingItemView *item) {
 Binding *v = item->binding;
 void *p = v->storage();
 switch(v->type) {
 default: return 0.0f;
 case 0: return *(f32 *)p;
 case 3: return *(s8 *)p;
 case 4: return *(s16 *)p;
 case 1: case 2: case 5: return *(s32 *)p;
 case 6: return *(u8 *)p;
 case 7: return *(u16 *)p;
 case 8: return *(u32 *)p;
 }
}
/* Writes a numeric menu value through its bound storage callback using the selected scalar type. */
void Bound_WriteBoundValue(MenuBindingItemView *item,float value) {
 float *storage;
 struct Binding *binding;
 unsigned int *word;
 binding=item->binding;
 storage=binding->storage();

 switch(binding->type) {
 case 0:*(float *)storage=value;return;
 case 3:*(signed char *)storage=(int)value;return;
 case 4:*(short *)storage=(int)value;return;
 case 1:case 2:case 5:*(int *)storage=(int)value;return;
 case 6:*(unsigned char *)storage=(unsigned int)value;return;
 case 7:*(unsigned short *)storage=(unsigned int)value;return;
 case 8:word=(unsigned int *)storage;*word=(unsigned int)value;return;
 }
}
#endif
/* Calls Gobjinst_DrawMaskedModelWithLighting with its three arguments and the table g_defaultParticleLighting as the fourth. */
#if defined(VERSION_DE) || defined(VERSION_US)
void Bound_DrawActorWithMenuLighting(void *first, void *second, void *third) {
    Gobjinst_DrawMaskedModelWithLighting(first, second, third, &g_defaultParticleLighting);
}
#endif

#if defined(VERSION_DE) || defined(VERSION_US)
void Bound_DrawActorWithRedMenuEffect(ObjectItemsDrawActorWithRedMenuEffect *object, void *context, void *lookup) {
 g_menuModelFillEnabled=3;
 object->view[g_lightingBufferIndex]=g_defaultParticleLighting;
 g_menuModelFillColor[0]=(255.0f);
 g_menuModelFillColor[1]=0;
 g_menuModelFillColor[2]=0;
 g_menuModelFillColor[4]=0;
 g_menuModelFillColor[3]=(float)(g_menuTintAlpha/2);
 Gobjinst_DrawActorModelWithViewEffects(object,context,lookup);
 g_menuModelFillEnabled=0;
}
#endif
#if defined(VERSION_US)
char k_BoundEncodedWords[4] =
    "quR";
#endif
#if defined(VERSION_DE)
unsigned int k_boundFragment[1] = {
    0x00443518,
};
#endif

/* Runs the optional callback in an object's handler table, then clears the three input
   state words the object owns. */
void Items_InvokeHandlerAndClearItemState(struct MenuItemCallbackAndStateView *object) {
    struct MenuItemInputStateView *state;

    if (object->handlers->callback != 0) {
        ((void (*)(struct MenuItemCallbackAndStateView *))object->handlers->callback)(object);
    }
    state = object->state;
    state->a = 0;
    state->b = 0;
    state->c = 0;
}

/* Allocates a block sized for the entries of a list through Cache_AllocateResource, builds it with Menu_InitializeMenu from four arguments, registers it with List_PrependIntrusive and advances the owner's rotating counter below four, returning the block or zero. Adapted from Menu_AllocateMenu with the list and all four values passed as arguments instead of read from a parameter block changed. */

extern void **Cache_AllocateResource(s32, s32, s32, char *);
extern const char g_menuText[];

void *Items_CreateMenu(struct MessageList *owner, struct Dialog *list, s32 a, s32 b, s32 c, s32 d) {
    s32 size = list->count * 40 + 472;
    s32 i;
    void **block;
    void *first;

    for (i = 0; i < list->count; i++) {
        s32 extra = 0;
        if (list->entries[i].type == 3) {
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
    Menu_InitializeMenu(first, block, list, a, b, c, d, owner);
    List_PrependIntrusive(owner, first);
    if (++owner->rotation >= 4) {
        owner->rotation = 0;
    }
    return first;
}

/* Removes an item from a list: runs the item's optional callback in its handler table
   with the item and the list, clears three words of its input state, unlinks it through
   List_RemoveIntrusive and releases its resource through Cache_ReleaseResource. */
void Items_DestroyMenu(void *list, struct MenuResourceItemView *item) {
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

#if defined(VERSION_US_REV1)
/* Does nothing. Nothing in the cartridge image calls it or stores its address as a word. */
void Items_MenuCreationNoOpUsRevisionOne(void) {
}
#endif

#if defined(VERSION_EU)
/* Picks the label for each of the eight option rows (ids 2..9): the first text when the row's flag is set, else the second. */
typedef struct { s32 id; u8 pad4[0x10]; char ***text; } OptionRowEu;
#endif
