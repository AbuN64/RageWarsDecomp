#include "COMMON/RESIDENTSTATE.H"
#include "RENDER/RESIDENT_TEXTURE_MENU_VIEWS.H"
#include "TYPES.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/TEXTURE_REQUEST.H"

#if defined(VERSION_US_REV1)





/** Decode a frontend input selector into its current button mask. */
s32 Tengine_QueryArtsendOverride(s32 overrideSelector) {
    if (g_textureVariationBypassEnabled == 0) {
        goto zero;
    }

    {
        s32 sw_outer_value = overrideSelector;
        sw_outer_value -= (257);
        if ((unsigned int)sw_outer_value > 5) {
            goto sw_outer_default;
        }
        switch (sw_outer_value) {
        case 0: goto sw_outer_0x101;
        case 1: goto sw_outer_0x102;
        case 2: goto sw_outer_0x103;
        case 3: goto sw_outer_0x104;
        case 4: goto sw_outer_0x105;
        case 5: goto sw_outer_0x106;
        }
    }
    do {
    sw_outer_0x101:
        return (s32)g_artsendTextureViewer.textureOverride;
    sw_outer_0x102:
        return (s32)g_artsendTextureViewer.paletteOverride;
    sw_outer_0x103:
        return 1 << g_artsendTextureViewer.selector->primaryButton;
    sw_outer_0x104:
        return 1 << g_artsendTextureViewer.selector->secondaryButton;
    sw_outer_0x105:
        {
        s32 sw_inner_value = g_artsendTextureViewer.selector->mode;
        if ((unsigned int)sw_inner_value > 5) {
            goto zero;
        }
        switch (sw_inner_value) {
        case 0: goto sw_inner_0;
        case 1: goto sw_inner_1;
        case 2: goto sw_inner_2;
        case 3: goto sw_inner_1;
        case 4: goto sw_inner_4;
        case 5: goto sw_inner_1;
        }
    }
    do {
        sw_inner_0:
            return 8;
        sw_inner_1:
        sw_inner_3:
        sw_inner_5:
            return 4;
        sw_inner_2:
            return 32;
        sw_inner_4:
            return 16;
    } while (0);
    sw_outer_0x106:
        g_artsendTextureViewer.overridesOff = 1;
zero:
        return 0;
    sw_outer_default:
        return 0;
    } while (0);
}
#endif
