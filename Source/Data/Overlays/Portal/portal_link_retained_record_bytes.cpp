#if defined(VERSION_EU)

#include "Frontend/results_setup_text.h"


#include "Data/Ovltbl/ctrialcatalogue_closetrialoptionsscreen_address.h"


#include "types.h"


#include "Data/Overlays/Portal/linktables_addresses.h"


#include "Common/pak_enter_player_options.h"


#include "Common/runtime_declarations.h"


#include "include_asm.h"


#include "Common/format.h"


#include "Common/resident_event_handler.h"


#include "data_overlay_layouts.h"


#include "data_overlay_sn_records.h"

#if defined(VERSION_EU_X)
#include "Multi/setup_setupnamespinner.h"
#endif


struct {
    u8 retainedRecordWords[12];
} g_portalLinkRetainedRecordBytes __attribute__((aligned(4))) = {
    { 0x00, 0x41, 0x00, 0x42, 0x08, 0x00, 0xFF, 0xEF, 0x00, 0x43, 0x00, 0x44 }
};
#endif
