#include "Common/volume_menu_resources.h"
#include "types.h"
#include "Common/audio_callbacks.h"
#include "Common/measured_storage.h"
#include "Common/runtime_declarations.h"
#if ((defined(VERSION_EU) || defined(VERSION_EU_X)))
#include "Common/shared_gameslot.h"
#endif
#if ((defined(VERSION_EU) || defined(VERSION_EU_X)))
#include "Menu/Pak/menu_createmenufromtemplate.h"
#endif

#if defined(VERSION_EU) || defined(VERSION_EU_X)

s32 Items_AdjustLanguage(void *first, void *second) {
    Shared_Game *game = &g_gameSettings;
    game->language = Menu_AdjustValue(second, game->language, 1, 0, 3, 1);
    return 0;
}
#endif

#if defined(VERSION_EU)
/* opaque address transport */
s32 CItemValue_BindItemValueField(struct ItemValueBindingView *field) {
    field->value = &g_languageMenuAlternateTextTable; /* types.abi.opaque_pointer: field carries an address only */
    return 0;
}
#endif

#if defined(VERSION_EU_X)
            /* size 0x0 */

 /* opaque address transport */
s32 Items_SetLanguageTextTable(struct ItemValueBindingView *field) {
    field->value = g_languageMenuTextTable; /* types.abi.opaque_pointer: field carries an address only */
    return 0;
}
#endif
