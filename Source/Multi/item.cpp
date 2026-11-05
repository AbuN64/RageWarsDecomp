#include "types.h"
#include "System/sound_context_music_and_voice_control.h"
#include <platform_sdk.h>
#include <PR/gbi.h>
#include "Common/player_item_inventory.h"
#include "Multi/initial.h"
#include "Common/menu_ui_providers.h"
#include "Common/sessionhandlerrow.h"
#include "Common/weapon_screen_message_operations.h"
#include "Gfx/Text/onscreen_drawscaledmaskedtilegrid.h"
#include "Multi/item.h"
#include "Menu/Pak/menu_createmenufromtemplate.h"

void Multi_DrawPlayerItemAvailability(struct MultiplayerItemAvailabilityView *item, MenuOptionBox *box, s32 direction, struct HolderMultiIsPlayerItemAvailable *context) {
    struct ItemDef *def = item->def;
    s32 type = def->type;
    s32 index = def->index;
    struct PlayerItemInventoryView *player = context->player;
    s32 available = 0;
    switch (type) {
    case 4350:
        if (index >= 0) {
            if (index < 3) {
                available = index < player->count64D;
            } else if (index < 6) {
                available = index - 3;
                available = available < player->count64E;
            }
        }
        break;
    case 4500:
        available = player->flags[index] != 0;
        break;
    }
    if (g_multiplayerItemRenderState != 5) {
        g_multiplayerItemRenderState = 5;
        Onscrn_SetupSpriteMode((s32)(context->fade * (context->alpha * g_playerItemAlphaScale[0])));
    }
    gDPPipeSync(g_displayListCursor++);
    gDPSetCycleType(g_displayListCursor++, G_CYC_2CYCLE);
    if (available) {
        gDPSetEnvColor(g_displayListCursor++, 255, 255, 255, (s32)(context->fade * (context->alpha * g_playerItemAlphaScale[1])));
    } else {
        gDPSetEnvColor(g_displayListCursor++, 50, 50, 50, (s32)(context->fade * (context->alpha * g_playerItemDisabledAlphaScale)));
    }
    OnScreen_DrawSpriteResource(item->resource, 0, box->left, box->top, box->scaleX, box->scaleY, 1);
}

/* Empty item hook. */
void Multi_EmptyItemHook(void) {
}

/* Reports whether an item is available to the player: for item type 0x10FE its index 0-2 must be below the player's count at 0x64D and 3-5 (less three) below the count at 0x64E, and for type 0x1194 the player's flag byte at 0x644 for the index must be set; any other type or index gives zero. */

/* Reports whether an item is available to the player: indices 0-2 and 3-5 of type 0x10FE are checked against the player's two counts, type 0x1194 against its flag table. */
s32 Multi_IsPlayerItemAvailable(struct MultiplayerItemAvailabilityView *item, struct HolderMultiIsPlayerItemAvailable *holder) {
    struct ItemDef *def = item->def;
    s32 type = def->type;
    s32 index = def->index;
    struct PlayerItemInventoryView *player = holder->player;
    s32 result = 0;

    switch (type) {
    case 4350:
        if (index >= 0) {
            if (index < 3) {
                result = index < player->count64D;
            } else if (index < 6) {
                result = index - 3;
                result = result < player->count64E;
            }
        }
        break;
    case 4500:
        result = player->flags[index] != 0;
        break;
    }
    return result;
}

/* Calls SoundElement_DisableMusicGainOverride and then returns what Menu_TryCreateMenu gives for the same three arguments. */
s32 Multi_CreateMenuWithDefaultMusicGain(void *first, void *second, void *third) {
    SoundElement_DisableMusicGainOverride();
    return Menu_TryCreateMenu(first, second, third);
}
