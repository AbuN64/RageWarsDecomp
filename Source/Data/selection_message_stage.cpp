#if defined(VERSION_EU)

#include "Data/rest_source_records.h"


#include "include_asm.h"


#include "Common/residentstate.h"


#include "Common/runtime_declarations.h"


#include "Data/Common/common_resource_link_words.h"


#include <PR/gbi.h>


#include "Common/effectcontribution.h"


#include "Common/osviscale.h"


#include "types.h"


#include "Data/Common/g_tlbmissexceptionvector.h"


#include "Data/Common/pickup_dispatchhandler_data.h"


#include "Menu_label_slots/menu_label_slots.h"


#include "Data/Common/g_pickupammodefinitions.h"


#include "Common/gameplay_transition.h"

#if defined(VERSION_US_REV1)
struct PickupLifeDefinition {
    unsigned int labelSlot;
    unsigned short id;
    unsigned short sharedFlag;
    unsigned short reserved8[2];
    unsigned short lifePoints;
    unsigned short reserved14;
    unsigned int applyEntry;
};
#endif

int g_selectionMessageStage = 0;

int g_frontendKeepCurrentVideoModeOnce = 0;

int g_frontendViDitherFilterEnabled = 0;
#endif

#if defined(VERSION_EU_X)

#include "Data/rest_source_records.h"


#include "include_asm.h"


#include "Common/residentstate.h"


#include "Common/runtime_declarations.h"


#include "Data/Common/common_resource_link_words.h"


#include <PR/gbi.h>


#include "Common/effectcontribution.h"


#include "Common/osviscale.h"


#include "types.h"


#include "Data/Common/g_tlbmissexceptionvector.h"


#include "Data/Common/pickup_dispatchhandler_data.h"


#include "Menu_label_slots/menu_label_slots.h"


#include "Data/Common/g_pickupammodefinitions.h"


#include "Common/gameplay_transition.h"

#if defined(VERSION_US_REV1)
struct PickupLifeDefinition {
    unsigned int labelSlot;
    unsigned short id;
    unsigned short sharedFlag;
    unsigned short reserved8[2];
    unsigned short lifePoints;
    unsigned short reserved14;
    unsigned int applyEntry;
};
#endif

int g_selectionMessageStage = 0;

int g_frontendKeepCurrentVideoModeOnce = 0;

int g_frontendViDitherFilterEnabled = 0;
#endif

#if defined(VERSION_US_REV1)

#include "Data/rest_source_records.h"


#include "include_asm.h"


#include "Common/residentstate.h"


#include "Common/runtime_declarations.h"


#include "Data/Common/common_resource_link_words.h"


#include <PR/gbi.h>


#include "Common/effectcontribution.h"


#include "Common/osviscale.h"


#include "types.h"


#include "Data/Common/g_tlbmissexceptionvector.h"


#include "Data/Common/pickup_dispatchhandler_data.h"


#include "Menu_label_slots/menu_label_slots.h"


#include "Data/Common/g_pickupammodefinitions.h"


#include "Common/gameplay_transition.h"

#if defined(VERSION_US_REV1)
struct PickupLifeDefinition {
    unsigned int labelSlot;
    unsigned short id;
    unsigned short sharedFlag;
    unsigned short reserved8[2];
    unsigned short lifePoints;
    unsigned short reserved14;
    unsigned int applyEntry;
};
#endif

int g_selectionMessageStage = 0;

int g_frontendKeepCurrentVideoModeOnce = 0;

int g_frontendViDitherFilterEnabled = 0;
#endif
