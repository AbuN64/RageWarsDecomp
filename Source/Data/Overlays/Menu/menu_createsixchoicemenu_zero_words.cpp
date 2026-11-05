#if defined(VERSION_DE)

#include "Common/resident_event_handler.h"


#include "Data/Overlays/Menu/linktables_addresses.h"


#include "Menu/event.h"


#include "types.h"


#include "include_asm.h"


#include "Common/format.h"


#include "data_overlay_layouts.h"


#include "Frontend/frontend_handletaboptionsshortcut.h"


#include "Game/frontend_closeoptionspage.h"


#include "Game/frontend_closesettingspage.h"


#include "Game/frontend_creategameoptionsscreen.h"


#include "Game/frontend_handleoptionspageshortcut.h"


#include "Game/game.h"


#include "Game/menu_createlocalizedsettingspage.h"


#include "Menu/menu_animatetaboptionsmenu.h"


#include "Menu/menu_createsettingspage.h"


#include "Menu/menu_finishtaboptionstransition.h"


#include "Menu/menu_openlocalizedgameoptions.h"


#include "options.h"


#include "Frontend/Game/menu_drawclippedwidgetsiblings.h"


#include "Data/Ovltbl/options_createoptionspage_data.h"


#include "Common/aiprofile.h"


#include "Common/ospihandle_s.h"


#include "Common/runtime_declarations.h"


#include "Ui/Tsmos/Smp/smp_list.h"


#include "Ui/Tsmos/Smp/Smp_overlay/smp_overlay.h"


#include "Common/gameplay_transition.h"


#include "Common/audio_loaddecodedsamples.h"


#include "Data/Common/common_resource_link_words.h"


#include "Frontend/controllerpak_message_pool.h"


#include "Data/Character_preview/character_preview.h"


#include "Data/Ovltbl/menu_event_handlers3_us_rev1_data.h"


#include "Data/Ovltbl/frontend_dispatchcompactoptionsevent_data.h"


#include "Data/Ovltbl/frontend_dispatchtaboptionsevent_data.h"


struct {
    void * g_pakActionMenuState;
} k_MenuCreatepakactionmenuZeroWords __attribute__((aligned(4))) = {
    0
};

struct {
    ResidentEventHandlerEntry handlers[6];
    u32 retainedRecordWords[1];
} g_menuCreateChoiceMenuRecord __attribute__((aligned(4))) = {
    { { 3592, 27, (ResidentEventHandler)(void *)&g_Menu_DispatchExtraOptionsEventAddress[404] }, { 3590, 27,
    (ResidentEventHandler)(void *)&g_Menu_DispatchExtraOptionsEventAddress[152] }, { 3587, 27,
    (ResidentEventHandler)(void *)&g_Menu_DispatchExtraOptionsEventAddress[356] }, { 2, 27,
    (ResidentEventHandler)(void *)&g_Menu_DispatchExtraOptionsEventAddress[828] }, { 1, 27,
    (ResidentEventHandler)(void *)&g_Menu_DispatchExtraOptionsEventAddress[656] }, { 0, 0,
    (ResidentEventHandler)0 } },
    { 0x004221F0 }
};
#endif

#if defined(VERSION_EU)

#include "Common/resident_event_handler.h"


#include "Data/Overlays/Menu/linktables_addresses.h"


#include "Menu/event.h"


#include "types.h"


#include "include_asm.h"


#include "Common/format.h"


#include "data_overlay_layouts.h"


#include "Frontend/frontend_handletaboptionsshortcut.h"


#include "Game/frontend_closeoptionspage.h"


#include "Game/frontend_closesettingspage.h"


#include "Game/frontend_creategameoptionsscreen.h"


#include "Game/frontend_handleoptionspageshortcut.h"


#include "Game/game.h"


#include "Game/menu_createlocalizedsettingspage.h"


#include "Menu/menu_animatetaboptionsmenu.h"


#include "Menu/menu_createsettingspage.h"


#include "Menu/menu_finishtaboptionstransition.h"


#include "Menu/menu_openlocalizedgameoptions.h"


#include "options.h"


#include "Frontend/Game/menu_drawclippedwidgetsiblings.h"


#include "Data/Ovltbl/options_createoptionspage_data.h"


#include "Common/aiprofile.h"


#include "Common/ospihandle_s.h"


#include "Common/runtime_declarations.h"


#include "Ui/Tsmos/Smp/smp_list.h"


#include "Ui/Tsmos/Smp/Smp_overlay/smp_overlay.h"


#include "Common/gameplay_transition.h"


#include "Common/audio_loaddecodedsamples.h"


#include "Data/Common/common_resource_link_words.h"


#include "Frontend/controllerpak_message_pool.h"


#include "Data/Character_preview/character_preview.h"


#include "Data/Ovltbl/menu_event_handlers3_us_rev1_data.h"


#include "Data/Ovltbl/frontend_dispatchcompactoptionsevent_data.h"


#include "Data/Ovltbl/frontend_dispatchtaboptionsevent_data.h"


struct {
    void * g_pakActionMenuState;
} k_MenuCreatepakactionmenuZeroWords __attribute__((aligned(4))) = {
    0
};

struct {
    ResidentEventHandlerEntry handlers[6];
    u32 retainedRecordWords[1];
} g_menuCreateChoiceMenuRecord __attribute__((aligned(4))) = {
    { { 3592, 27, (ResidentEventHandler)(void *)&addrLow_Menu_UpdatePakActionMenu }, { 3590, 27,
    (ResidentEventHandler)(void *)&addrLow_Menu_CreatePakActionMenu }, { 3587, 27,
    (ResidentEventHandler)(void *)&addrLow_Menu_DestroyPakActionMenu }, { 2, 27,
    (ResidentEventHandler)(void *)&addrLow_Menu_CancelPakActionMenu }, { 1, 27,
    (ResidentEventHandler)(void *)&addrLow_Menu_ChoosePakActionOption }, { 0, 0, (ResidentEventHandler)0 } },
    { 0x40013000 }
};
#endif

#if defined(VERSION_EU_X)

#include "Common/resident_event_handler.h"


#include "Data/Overlays/Menu/linktables_addresses.h"


#include "Menu/event.h"


#include "types.h"


#include "include_asm.h"


#include "Common/format.h"


#include "data_overlay_layouts.h"


#include "Frontend/frontend_handletaboptionsshortcut.h"


#include "Game/frontend_closeoptionspage.h"


#include "Game/frontend_closesettingspage.h"


#include "Game/frontend_creategameoptionsscreen.h"


#include "Game/frontend_handleoptionspageshortcut.h"


#include "Game/game.h"


#include "Game/menu_createlocalizedsettingspage.h"


#include "Menu/menu_animatetaboptionsmenu.h"


#include "Menu/menu_createsettingspage.h"


#include "Menu/menu_finishtaboptionstransition.h"


#include "Menu/menu_openlocalizedgameoptions.h"


#include "options.h"


#include "Frontend/Game/menu_drawclippedwidgetsiblings.h"


#include "Data/Ovltbl/options_createoptionspage_data.h"


#include "Common/aiprofile.h"


#include "Common/ospihandle_s.h"


#include "Common/runtime_declarations.h"


#include "Ui/Tsmos/Smp/smp_list.h"


#include "Ui/Tsmos/Smp/Smp_overlay/smp_overlay.h"


#include "Common/gameplay_transition.h"


#include "Common/audio_loaddecodedsamples.h"


#include "Data/Common/common_resource_link_words.h"


#include "Frontend/controllerpak_message_pool.h"


#include "Data/Character_preview/character_preview.h"


#include "Data/Ovltbl/menu_event_handlers3_us_rev1_data.h"


#include "Data/Ovltbl/frontend_dispatchcompactoptionsevent_data.h"


#include "Data/Ovltbl/frontend_dispatchtaboptionsevent_data.h"


struct {
    void * g_pakActionMenuState;
} k_MenuCreatepakactionmenuZeroWords __attribute__((aligned(4))) = {
    0
};

struct {
    ResidentEventHandlerEntry handlers[6];
    u32 retainedRecordWords[1];
} g_menuCreateChoiceMenuRecord __attribute__((aligned(4))) = {
    { { 3592, 27, (ResidentEventHandler)(void *)&g_Menu_DispatchExtraOptionsEventAddress[404] }, { 3590, 27,
    (ResidentEventHandler)(void *)&g_Menu_DispatchExtraOptionsEventAddress[152] }, { 3587, 27,
    (ResidentEventHandler)(void *)&g_Menu_DispatchExtraOptionsEventAddress[356] }, { 2, 27,
    (ResidentEventHandler)(void *)&g_Menu_DispatchExtraOptionsEventAddress[828] }, { 1, 27,
    (ResidentEventHandler)(void *)&g_Menu_DispatchExtraOptionsEventAddress[656] }, { 0, 0,
    (ResidentEventHandler)0 } },
    { 0x00000007 }
};
#endif
