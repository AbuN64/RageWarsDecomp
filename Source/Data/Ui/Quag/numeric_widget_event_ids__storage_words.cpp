#if defined(VERSION_US_REV1)

#include "Common/rotation_extraction.h"


#include "Common/gfx_initializefrontendservices.h"


#include "types.h"


#include "Common/vector4f.h"


#include "Menu/widget_records.h"


#include "Common/sharedtrackobjectprefix.h"


#include "Common/menu_screen_elements.h"


#include "Common/record.h"


#include "Common/texture.h"


#include "Ui/Quag/N64_Eng.h"


#include "Menu/Gfx/rect.h"


#include "Math/smsmngr_initializescreenmanager.h"


#include "Menu/gfx.h"


#include "Common/resident_event_handler.h"


#include "Common/sharedplayer.h"


#include "Common/aiprofile.h"


#include "Common/runtime_declarations.h"


#include "Common/widget_tree.h"


#include "Common/statepair.h"


#include "Common/shared_menureply.h"


#include "Render/soundelement_playflatsound.h"


#include "include_asm.h"


#include "Scene/cache_freememory.h"


#include "Frontend/frontend_openresourcearchive.h"


#include "Ui/smos.h"


#include "Frontend/widget_drawtextwidget.h"


#include "Frontend/widget_findwidgetatpoint.h"


#include "Ui/n64eng.h"


#include "Data/Ui/numeric_widget_event_table.h"


#include "Ui/ui_address_symbols.h"


#include "Data/Ui/ribbon_blend_resource_data.h"


#include "System/engine_data_source.h"


#include "Data/rest_source_records.h"


EventHandlerRecord g_numericWidgetEventIds_StorageWords[9] = {
    { 3591, 30000, N64Eng_SetLinkedCommand100_Address },
    { 15, 30000, N64Eng_SetLinkedCommand200_Address },
    { 16, 30000, N64Eng_SetLinkedCommand100WithSound_Address },
    { 8, 30000, N64Eng_HandleNumericIncrement_Address },
    { 7, 30000, N64Eng_HandleNumericDecrement_Address },
    { 3587, 30000, N64Eng_FreeNumericWidget_Address },
    { 11, 30000, N64Eng_CancelSelectionRepeat_Address },
    { 3592, 30000, TickSelectionRepeat_Address },
    { 0, 0, 0 },
};

char s_petrText[4] =
    "Petr";
#endif
