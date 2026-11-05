#if defined(VERSION_US)

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

unsigned short g_fxDrawBoundedParticleQuadsHalfwords[48] = {
    0xE300, 0x1001, 0x0000, 0x0000, 0xD700, 0x0002, 0x8000, 0x8000, 0xD9F9, 0xFBFF, 0x0000, 0x0000,
    0xD9FF, 0xFFFF, 0x0021, 0x0004, 0xFCFF, 0x97FF, 0xFFFF, 0xFE38, 0xE200, 0x001C, 0xC810, 0x4B50,
    0xDB04, 0x0004, 0x0000, 0x0001, 0xDB04, 0x000C, 0x0000, 0x0001, 0xDB04, 0x0014, 0x0000, 0xFFFF,
    0xDB04, 0x001C, 0x0000, 0xFFFF, 0x0100, 0x4008, 0x8014, 0x08E0, 0xDF00, 0x0000, 0x0000, 0x0000,
};
#endif
