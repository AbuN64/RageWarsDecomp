#include "COMMON/RESIDENTSTATE.H"
#include "RENDER/RESIDENT_TEXTURE_MENU_VIEWS.H"
#include "TYPES.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "ENGINE/TEXTLOAD.H"
#include "UI/X_FILES/X_PLUS.H"
#include "ENGINE/TENGINE.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/TEXTURE_REQUEST.H"
#include "COMMON/RESIDENT_EVENT_HANDLER.H"
#include "SCENE/CACHE_ALLOCATERESOURCEAT.H"

/* 80294C64_5.CPP */
#if defined(VERSION_US_REV1)

extern ResidentSlot g_artsendTextureViewerOverridesOff;
extern ResidentEntry g_artsendSelectedTextureResource;

void TextLoad_ResetArtsendTextureState(void) {
    s32 *base = &g_artsendTextureSelection;

    g_artsendTextureViewer.alternateTitle = 0;
    g_artsendTextureViewerState = 0;
    g_artsendTextureSelectionIndex = 0;
    g_artsendTextureFrameSelection = 0;
    *base = 1;
    g_artsendTextureViewerReservedWord = 0;
    g_artsendTextureSelectionChanged = 0;
    *(s32 *)&g_artsendSelectedTextureResource = 0;
    g_artsendTextureResetWordOne = 0;
    g_artsendTextureResetWordTwo = 0;
    g_artsendActionMappingSelection = 0;
    g_artsendTextureViewerEntryTable = 0;
    g_artsendTextureViewerTextureTable = 0;
    g_artsendTextureViewerPaletteTable = 0;
    g_artsendTextureViewerFrameCount = 0;

    XPlus_FillMemory((s32) ((char *)&((struct ArtsendTextureMenuState *)((char *)base - 8))->textureData), 0, 0x2000);
    XPlus_FillMemory((s32) ((char *)&((struct ArtsendTextureMenuState *)((char *)base - 8))->paletteData), 0xFF, 0x100);

    *base = *g_textureResourceSectionRoot;
}
#endif

/* 80294C64_6.CPP */
#if defined(VERSION_US_REV1)
void TextLoad_CloseArtsendTexturePreview(void) { TextLoad_ReleaseArtsendTextureResource(); }
#endif

/* 80294C64_7.CPP */
#if defined(VERSION_US_REV1)
/** Report the global count only while its enable byte is set. */
int TextLoad_IsArtsendTexturePreviewEnabled(void) {
    int result = 0;
    if (g_artsendTextureViewer.alternateTitle != 0) {
        result = g_textureVariationBypassEnabled != 0;
    }
    return result;
}
#endif

/* 80294C64_8.CPP */
#if defined(VERSION_US_REV1)


void TextLoad_ApplyArtsendTextureOverride(s32 resource, s32 **texture) {
    s32 enabled;
    s32 choose;

    if ((g_textureVariationBypassEnabled != 0) && (*texture != 0) && (*(s32 *)&g_artsendTextureViewerOverridesOff == 0)) {
        enabled = 0;
        if (g_artsendTextureViewer.alternateTitle != 0) {
            enabled = (u32)g_textureVariationBypassEnabled > 0U;
        }
        if (enabled != 0) {
            choose = (g_artsendTextureViewerOverridesOff.reservedWord % 10) < 3;
        } else {
            choose = 1;
        }
        if (resource == *(s32 *)&g_artsendSelectedTextureResource) {
            if (choose != 0) {
                *texture = &((SelectionTextLoadApplyArtsendTextureOverride *)&g_artsendSelectedTextureResource)->alternative;
                return;
            }
            *texture = g_artsendTextureViewer.textureOverride;
        }
    }
}
#endif

/* 80294C64_9.CPP */
#if defined(VERSION_US_REV1)

void TextLoad_ApplyArtsendPaletteOverride(s32 resource, s32 **palette) {
    s32 paletteOverrideEnabled;
    s32 paletteOverrideSelected;

    if ((g_textureVariationBypassEnabled != 0) && (*palette != 0)) {
        if (*(s32 *)&g_artsendTextureViewerOverridesOff != 0) {
            return;
        }
        paletteOverrideEnabled = 0;
        if (g_artsendTextureViewer.alternateTitle != 0) {
            paletteOverrideEnabled = (u32)g_textureVariationBypassEnabled > 0U;
        }
        if (paletteOverrideEnabled != 0) {
            paletteOverrideSelected = (g_artsendTextureViewerOverridesOff.reservedWord % 10) < 3;
        } else {
            paletteOverrideSelected = 1;
        }
        if (resource == *(s32 *)&g_artsendSelectedTextureResource) {
            if (paletteOverrideSelected != 0) {
                *palette = &g_artsendSelectedTextureResource.palette;
                return;
            }
            *palette = g_artsendTextureViewer.paletteOverride;
        }
    }
}

void TextLoad_SelectNextArtsendTexture(void) {
    s32 requestedTexture;

    if (g_artsendNextTextureHoldCount++ >= 3) {
        requestedTexture = g_artsendTextureSelection.index + 1;
        g_artsendNextTextureHoldCount = 0;
        g_artsendTextureSelection.changed = 1;
        g_artsendTextureSelection.index = requestedTexture;
        g_artsendTextureSelection.index = requestedTexture % g_artsendTextureSelection.count;
    }
}
#endif

/* 80294C64_10.CPP */
#if defined(VERSION_US_REV1)

void TextLoad_SelectPreviousArtsendTexture(void) {
    s32 requestedTexture;
    s32 positiveTexture;
    s32 wrappedTexture;
    s32 *p;
    s32 old;

    old = g_artsendPreviousTextureHoldCount++;
    if (old >= 3) {
        p = &g_artsendTextureViewer.selectionIndex;
        requestedTexture = p[0] - 1;
        positiveTexture = requestedTexture + p[-1];
        wrappedTexture = positiveTexture % p[-1];
        p[2] = 1;
        *(volatile s32 *)&p[0] = requestedTexture;
        p[0] = wrappedTexture;
        if ((f32) wrappedTexture < 0.0f) {
            wrappedTexture = -wrappedTexture;
        }
        p[0] = wrappedTexture;
        g_artsendPreviousTextureHoldCount = 0;
    }
}

void TextLoad_ReleaseArtsendTextureResource(void) {
    if (g_artsendTextureViewer.resource != 0) {
        Cache_UnlockResource(0, g_artsendTextureViewer.resource);
    }
    g_artsendTextureViewer.resource = 0;
    g_artsendTextureViewer.textureOverride = 0;
    g_artsendTextureViewer.paletteOverride = 0;
    g_artsendTextureViewer.selector = 0;
}

/** Reset the record's fields, marking slot 1 active. */
void TextLoad_InitializeArtsendPreviewState(void) {
    struct ArtsendTextureMenuState *object = &g_artsendTextureViewer;

    object->alternateTitle = 0;
    object->state = 0;
    object->selectionIndex = 0;
    object->selectionValue = 0;
    object->active = 1;
    object->reservedWord = 0;
    object->titleWasShown = 0;
    object->resource = 0;
    object->textureOverride = 0;
    object->paletteOverride = 0;
    object->selector = 0;
    object->entryTable = 0;
    object->textureTable = 0;
    object->paletteTable = 0;
    object->frameCount = 0;
}

void TextLoad_DecreaseArtsendSelectionValue(void) {
    s32 *ptr;
    s32 old;
    s32 count;

    ptr = &g_artsendPreviousFrameHoldCount;
    old = (*ptr)++;
    if (old >= 3) {
        count = g_artsendTextureViewer.selectionValue;
        g_artsendTextureViewer.titleWasShown = 1;
        g_artsendPreviousFrameHoldCount = 0;
        g_artsendTextureViewer.selectionValue = count - 1;
    }
}

void TextLoad_IncreaseArtsendSelectionValue(void) {
    s32 *ptr;
    s32 old;
    s32 count;

    ptr = &g_artsendNextFrameHoldCount;
    old = (*ptr)++;
    if (old >= 3) {
        count = g_artsendTextureViewer.selectionValue;
        g_artsendTextureViewer.titleWasShown = 1;
        g_artsendNextFrameHoldCount = 0;
        g_artsendTextureViewer.selectionValue = count + 1;
    }
}

void TextLoad_SelectPreviousArtsendPage(void) {
    s32 requestedPage;
    s32 positivePage;
    s32 wrappedPage;
    s32 *p;
    s32 old;

    old = g_artsendPreviousPageHoldCount++;
    if (old >= 3) {
        p = &g_artsendTextureViewer.selectionIndex;
        requestedPage = p[0] - 5;
        positivePage = requestedPage + p[-1];
        wrappedPage = positivePage % p[-1];
        *(volatile s32 *)&p[0] = requestedPage;
        p[0] = wrappedPage;
        if ((f32) wrappedPage < 0.0f) {
            wrappedPage = -wrappedPage;
        }
        p[0] = wrappedPage;
        p[2] = 1;
        g_artsendPreviousPageHoldCount = 0;
    }
}
#endif

/* 80294C64_11.CPP */
#if defined(VERSION_US_REV1)
/** Return the texture override pointer of the menu state. */

/* Handles one held press of the menu "next page" key: g_artsendNextPageHoldCount counts the held presses, and on the
 * fourth one the selection index g_artsendTextureViewer.selectionIndex is stepped up by five modulo the menu item count; the
 * pre-modulo index store is retained as the original emitted it, and the change flag word at +8 from
 * the index is set. Ported verbatim from the legacy branch source (byte-exact in that build). */

void TextLoad_SelectNextArtsendPage(void) {
    s32 requestedPage;
    s32 pageCount;
    s32 wrappedPage;
    s32 *p;
    s32 old;

    old = g_artsendNextPageHoldCount++;
    if (old >= 3) {
        p = &g_artsendTextureViewer.selectionIndex;
        requestedPage = p[0] + 5;
        pageCount = p[-1];
        wrappedPage = requestedPage % pageCount;
        g_artsendNextPageHoldCount = 0;
        p[2] = 1;
        *(volatile s32 *)&p[0] = requestedPage;
        p[0] = wrappedPage;
    }
}

int TextLoad_GetArtsendTextureOverride(void) {
    return (int)g_artsendTextureViewer.textureOverride;
}

int TextLoad_GetArtsendPaletteOverride(void) {
    return (int)g_artsendTextureViewer.paletteOverride;
}

/** Compute a bit mask from the byte at offset 2 of the global record. */
int TextLoad_GetArtsendPrimaryButtonMask(void) {
    return 1 << g_artsendTextureViewer.selector->primaryButton;
}

int TextLoad_GetArtsendSecondaryButtonMask(void) {
    unsigned char shift = g_artsendTextureViewer.selector->secondaryButton;
    return 1 << shift;
}

/** Return the mode mask selected by the global record's leading byte. */
int TextLoad_GetArtsendModeMask(void) {
    {
        int sw_mode_value = g_artsendTextureViewer.selector->mode;
        if ((unsigned int)sw_mode_value > 5) {
            goto sw_mode_default;
        }
        switch (sw_mode_value) {
        case 0: goto sw_mode_0;
        case 1: goto sw_mode_1;
        case 2: goto sw_mode_2;
        case 3: goto sw_mode_1;
        case 4: goto sw_mode_4;
        case 5: goto sw_mode_1;
        }
    }
    do {
    sw_mode_0:
        return 8;
    sw_mode_1:
    sw_mode_3:
    sw_mode_5:
        return 4;
    sw_mode_2:
        return 32;
    sw_mode_4:
        return 16;
    sw_mode_default:
        return 0;

    } while (0);
}
#endif
