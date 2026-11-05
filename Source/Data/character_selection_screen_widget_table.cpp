#if defined(VERSION_US)

#include "Fx/eu_screen_message_setup.h"


#include "Data/rest_source_records.h"


#include "Common/runtime_declarations.h"


#include "include_asm.h"


#include "Data/Rsp/smpframeanim_dispatchevent_data.h"


#include "Ui/Tsmos/Screens/scenariosetupscreen.h"


#include "Data/Rsp/scenariosetup_hidearenacataloguewidgets_data.h"


#include "Data/Gfxdata/audio_decodeframe_data.h"


#include "Fx/sky_postscaledscreenmessage_data.h"


#include "Common/Lone/g_pakdefaultpreviewtypelabel.h"


#include "Common/runtime_declarations.h"


#include "Frontend/options_list_declarations.h"


#include "Menu/pak_load.h"


#include "Data/Rsp/g_bossactivtext.h"


#include "Common/osviscale.h"


#include "types.h"


#include "Data/Rsp/g_characterselectionscreenwidgettable.h"


struct {
    unsigned short firstRowWidgets[8][2];
    struct {
        unsigned int kind;
        unsigned short widgets[8][2];
    } rows[3];
    unsigned int events[39];
} g_characterSelectionScreenWidgetTable = {
    { { 0, 0x007F }, { 0, 0x00C6 }, { 0, 0x00AD }, { 0, 0x00AF }, { 0, 0x00B1 }, { 0, 0x00C4 }, { 0, 0x00C3 }, { 0, 0x00C2 } },
    {
        { 0x00000086, { { 0, 0x007E }, { 0, 0x00A9 }, { 0, 0x0094 }, { 0, 0x0096 }, { 0, 0x0098 }, { 0, 0x00A8 }, { 0, 0x00A7 }, { 0, 0x00A6 } } },
        { 0x0000008D, { { 0, 0x007C }, { 0, 0x00C7 }, { 0, 0x00B3 }, { 0, 0x00B5 }, { 0, 0x00B7 }, { 0, 0x00B9 }, { 0, 0x00BA }, { 0, 0x00BB } } },
        { 0x0000008C, { { 0, 0x007D }, { 0, 0x00AA }, { 0, 0x009C }, { 0, 0x009B }, { 0, 0x009A }, { 0, 0x009E }, { 0, 0x009F }, { 0, 0x009D } } },
    },
    {
        0x00000E07, 0x00000007, 0x00420BC0,
        0x00000E08, 0x00000007, (unsigned int)g_character_UpdateCharacterPreviewEntry,
        0x0000000A, 0x00000007, (unsigned int)g_selection_HandleCharacterVariantCycleEntry,
        0x00000E0A, 0x00000007, (unsigned int)g_menu_RenderPlayerCharacterPreviewsEntry,
        0x00000E06, 0x00000007, (unsigned int)g_cCharacterSelection_OpenCharacterSelectionScreenEntry,
        0x00000E03, 0x00000007, (unsigned int)g_selection_DestroyCharacterSelectionMenuEntry_GSelectionlayouttailusrevone,
        0x00000002, 0x00000007, (unsigned int)g_selection_CancelCharacterConfirmationEntry,
        0x00000001, 0x00000007, (unsigned int)g_selection_ReadSelectionSlotEntry,
        0x00000008, 0x00000007, (unsigned int)g_selection_ReturnCharacterEventZeroAEntry,
        0x00000007, 0x00000007, (unsigned int)g_selection_ReturnCharacterEventZeroBEntry,
        0x00000005, 0x00000007, (unsigned int)g_selection_ReturnCharacterEventZeroCEntry,
        0x00000006, 0x00000007, (unsigned int)g_selection_ReturnCharacterEventZeroDEntry,
        0x00000000, 0x00000000, 0x00000000,
    },
};
#endif
