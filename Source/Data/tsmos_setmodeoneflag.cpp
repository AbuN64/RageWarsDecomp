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

Gfx g_FxDrawboundedparticlequadsBlock[12] = {
    gsSPSetOtherMode(G_SETOTHERMODE_H, 14, 2, 0x00000000),
    gsSPTexture(0x8000, 0x8000, 0, 0, 1),
    gsSPGeometryMode(0x060400, 0x00000000),
    gsSPGeometryMode(0x000000, 0x00210004),
    gsDPSetCombineLERP(0, 0, 0, 0, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsSPSetOtherMode(G_SETOTHERMODE_L, 3, 29, 0xC8104B50),
    gsMoveWd(4, 0x0004, 0x00000001),
    gsMoveWd(4, 0x000C, 0x00000001),
    gsMoveWd(4, 0x0014, 0x0000FFFF),
    gsMoveWd(4, 0x001C, 0x0000FFFF),
    gsSPVertex(g_particleQuadVertices, 4, 0),
    gsSPEndDisplayList(),
};

Gfx g_FxDrawboundedparticlequads[11] = {
    gsSPSetOtherMode(G_SETOTHERMODE_H, 14, 2, 0x00000000),
    gsSPTextureL(0x8000, 0x8000, 0, 0xFF, 0, 1),
    gsSPGeometryMode(0x060400, 0x00000000),
    gsSPGeometryMode(0x000000, 0x00210004),
    gsDPSetCombineLERP(0, 0, 0, 0, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsSPSetOtherMode(G_SETOTHERMODE_L, 3, 29, 0xC8104E50),
    gsMoveWd(4, 0x0004, 0x00000001),
    gsMoveWd(4, 0x000C, 0x00000001),
    gsMoveWd(4, 0x0014, 0x0000FFFF),
    gsMoveWd(4, 0x001C, 0x0000FFFF),
    gsSPEndDisplayList(),
};

Gfx g_fxDrawredparticlequadDataConstant[12] = {
    gsSPSetOtherMode(G_SETOTHERMODE_H, 14, 2, 0x00000000),
    gsSPTexture(0x8000, 0x8000, 0, 0, 1),
    gsSPGeometryMode(0x060400, 0x00000000),
    gsSPGeometryMode(0x000000, 0x00210004),
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsSPSetOtherMode(G_SETOTHERMODE_L, 3, 29, 0xC8104B50),
    gsMoveWd(4, 0x0004, 0x00000001),
    gsMoveWd(4, 0x000C, 0x00000001),
    gsMoveWd(4, 0x0014, 0x0000FFFF),
    gsMoveWd(4, 0x001C, 0x0000FFFF),
    gsSPVertex(g_particleQuadVertices, 4, 0),
    gsSPEndDisplayList(),
};

s32 g_TsmosSetmodeoneflag[1] = {
    1,
};

s32 g_TsmosUpdatefrontend[2] = {
    0, 1,
};

CommonEncodedWordsBlock1Layout k_commonFragment = {
    "..\000\000Invi",
    { 5.0f, 0.0f, 0.0f, 0.0f, 0.0f, -5.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 5.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.5450846f, 4.7552824f, 0.0f, 0.0f, 0.0f, -4.0450845f, 2.938926f, 0.0f, 0.0f, 0.0f, -4.0450845f, -2.938926f, 0.0f, 0.0f, 0.0f, 1.5450846f, -4.7552824f, 0.0f, 0.0f, 0.0f, 5.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },
    { (void *)&g_tlbMissExceptionVector, 0, 0, 0, 0, (void *)&g_tlbMissExceptionVector, (void *)&g_tlbMissExceptionVector, 0, 0, 0, 0, (void *)&g_tlbMissExceptionVector, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },
};

char g_evementSexysteveText[20] = "EVEMENT sexysteve";

#endif

#include "Data/Ui/ribbon_blend_resource_data.h"

/* The six key selections follow the resource header in every build. */
extern char g_ribbonBlendResources[];
int g_ribbonBlendResourceTable[6] = {
    (int)(g_ribbonBlendResources + 0x0C),
    (int)(g_ribbonBlendResources + 0x34),
    (int)(g_ribbonBlendResources + 0x5C),
    (int)(g_ribbonBlendResources + 0xD4),
    (int)(g_ribbonBlendResources + 0x14C),
    (int)(g_ribbonBlendResources + 0x174),
};
