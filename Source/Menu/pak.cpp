#include "Menu/menu_box.h"
#include "Menu/pak_records.h"
#include "Engine/scene.h"
#include "Render/setn64_updatefadetransition.h"
#include "include_asm.h"
#include "Common/Lone/hud_reference_viewport_height.h"
#include "Common/name.h"
#include "Common/triple.h"
#include "types.h"
#include "Common/runtime_declarations.h"
#include "Menu/option_and_text_layer_views.h"
#include "Common/menu_match_globals.h"
#include "Common/menu_abbdc_versions.h"
#include "Menu/Pak/menu_measuremenutext_symbols.h"
#include "Menu/menu_drawanimatedmenusprite.h"
#include "Engine/defs.h"
#include "Menu/menu_measuremenutext.h"
#include "Ai/player_updateplayercamera.h"
#include "Menu/built_menu.h"
#include "Common/game_session.h"
#include "Common/textlayermetrics.h"
#include "Common/Lone/g_languageindex.h"
#include "Common/font_style_and_glyph_operations.h"
#include "Common/menu_ui_providers.h"
#include "Gfx/Text/onscreen_drawscaledmaskedtilegrid.h"
#include "Menu/Pak/menu_drawstyledmenutext_symbols.h"
#include "Common/weapon_screen_message_operations.h"
#include "Menu/Pak/pak_menu_entries.h"
#include "Engine/Instance/gobjinst.h"
#include "Menu/bound.h"
#include "Common/Lone/g_defaultcamerasurfacetype.h"
#include "Common/Lone/menu_tint_alpha.h"
#include "Common/vector4f.h"
#include "Common/menu_text.h"
#include "Menu/pak_menu_entries.h"
#include "Menu/Items/menu_drawanimatedmenusprite.h"
#include "Common/sharedtrackobjectprefix.h"
#include "Menu/g_menucenterfraction.h"
#include "Menu/Pak/pak_menu_entries_symbols.h"
#include "Common/video_dimensions.h"
#include "Common/session_state.h"
#include "Common/world.h"
#include "Engine/Cache/list.h"
#include "Menu/Pak/menu_initializemenu.h"
#include "Menu/menu_createmenufromparameters.h"
#include "Menu/Pak/menu_createmenufromtemplate.h"
#include "Common/cache_allocateresource.h"
#include "Menu/g_menutext.h"
#include "Engine/scene_drawtransitioncoloroverlay.h"
#include "Common/sharedplayer.h"
#include "Common/aiprofile.h"
#include "Common/heap_arena_entry.h"
#include "Common/cache_releaseresource.h"
#include "Common/sessionhandlerrow.h"
#include "Common/member_offset.h"
#include "Common/gameplay_camera.h"
#include "Menu/menu_item_views.h"
#include <PR/gbi.h>
#include <platform_sdk.h>
#include "Common/weapon_marker_and_profile_views.h"
#include "Menu/Pak/menu_drawanimatedmenusprite_symbols.h"
#include "Ai/Player/player_updatefragtagselection_data_player_updatefragtagselection_data.h"
#include "Menu/pak_load.h"

static __inline__ TextBoundsFont *textBoundsFont_menuMeasuremenutext(TextBoundsText *text) {
    s32 style = 0;
    switch ((u32)text->flags & 0x3FE0) {
    case 32: style = 0; break;
    case 64: style = 1; break;
    case 128: style = 2; break;
    case 0x100: style = 3; break;
    case 0x200: style = 4; break;
    case 0x400: style = 5; break;
    case 0x800: style = 6; break;
    case 0x1000: style = 7; break;
    case 0x2000: style = 8; break;
    default: style = 0; break;
    }
    style += MENU_LANGUAGE * 9;
    return &g_menuFontStyles[style];
}

/* Measures a text item into its metrics: size by kind (glyph run, image, three-part composite, box), then the scaled screen
 * rectangle from the item position (284 x 222 virtual screen). */
void Menu_MeasureMenuText(TextBoundsText *text, CItemInfo *metrics) {
    TextBoundsText part;
    CItemInfo first, second, third;
    TextBoundsData *data;
    TextBoundsFont *font;
    TextBoundsRecord23 *box;
    u8 *string;
    s32 count, width;
    f32 size, w, boxW, boxH, sx, sy, x, y;

    data = Menu_GetListContext(text->descriptor->listContextKey);
    metrics->m_ScaleY = g_menuTextDefaultScale;
    metrics->m_ScaleX = g_menuTextDefaultScale;
    switch (text->mode) {
    case 0:
    case 5:
        font = textBoundsFont_menuMeasuremenutext(text);
        if (font->kind == 0) {
            size = font->width;
            if (text->mode == 5) {
                string = Menu_GetDynamicItemText(text);
            } else {
                string = ((u8 **)text->text)[MENU_LANGUAGE];
            }
            w = Menu_MeasureLine(string, size, size);
        } else {
            count = 0;
            if (text->mode == 5) {
                string = Menu_GetDynamicItemText(text);
            } else {
                string = ((u8 **)text->text)[MENU_LANGUAGE];
            }
            while (string != 0 && *string != 0 && *string != '\n') {
                string++;
                count++;
            }
            w = count * font->width;
        }
        metrics->width = w;
        if (text->flags & 0x08000000) {
            metrics->height = g_hudReferenceViewportHeight * g_menuTextScreenHeightScale;
        } else if (font->kind == 2 && g_hudReferenceViewportHeight >= 223) {
            metrics->height = (font->height + g_menuTextFontHeightPadding) * g_hudReferenceViewportHeight * g_menuTextFontHeightScale;
        } else {
            metrics->height = font->height * g_hudReferenceViewportHeight * g_menuTextFontHeightScale;
        }
        metrics->width = metrics->width * g_hudReferenceViewportWidth / 284;
        break;
    case 4:
        font = textBoundsFont_menuMeasuremenutext(text);
        metrics->width = font->width;
        metrics->height = font->height * g_hudReferenceViewportHeight * g_menuTextAlternateFontHeightScale;
        break;
    case 1:
        if ((SetN64_IsModeThirteen() != 0 && (text->flags & 0x40000000)) ||
            (g_frontendScreenStatus.settings.local != 0 && text->flags < 0 && Defs_GetMemorySize() == 0x400000)) {
            metrics->width = 284;
            metrics->height = 222;
        } else {
            OnScreen_GetImageDimensions((s32)text->text, 0, &metrics->width, &metrics->height);
        }
        if ((text->flags & 0x10000000) && (boxW = metrics->width) != 0.0f && (boxH = metrics->height) != 0.0f) {
            sx = data->width / boxW;
            sy = data->height / boxH;
        } else {
            sx = g_hudReferenceViewportWidth * g_menuTextScreenWidthScale;
            sy = g_hudReferenceViewportHeight * g_menuTextAlternateScreenHeightScale;
        }
        metrics->m_ScaleX = sx;
        metrics->m_ScaleY = sy;
        break;
    case 2:
        first = *metrics;
        part = *text;
        part.mode = 0;
        Menu_MeasureMenuText(&part, &first);
        second = *metrics;
        part = *text;
        part.mode = 1;
        part.text = 0;
        Menu_MeasureMenuText(&part, &second);
        third = *metrics;
        part = *text;
        part.mode = 1;
        part.text = 0;
        Menu_MeasureMenuText(&part, &third);
        width = second.width + third.width;
        if (width < first.width) {
            width = first.width;
        }
        metrics->width = width;
        metrics->height = first.height + second.height + (third.height - second.height) / 2;
        break;
    case 3:
        box = text->text;
        metrics->width = box->width * data->width / g_hudReferenceViewportWidth;
        metrics->height = box->height * data->height / g_hudReferenceViewportHeight;
        break;
    default:
        metrics->width = 1;
        metrics->height = 1;
        break;
    }
    x = text->x * g_hudReferenceViewportWidth / 284;
    if (!(text->flags & 0x8000)) {
        if (text->flags & 0x4000) {
            metrics->left = metrics->right + x;
        } else {
            metrics->left = x;
        }
    }
    metrics->right = metrics->left + metrics->width * metrics->m_ScaleX;
    y = text->y * g_hudReferenceViewportHeight / 222;
    if (!(text->flags & 0x20000)) {
        if (text->flags & 0x10000) {
            metrics->m_Top = metrics->m_Bottom + y;
        } else {
            metrics->m_Top = y;
        }
    }
    metrics->m_Bottom = metrics->m_Top + metrics->height * metrics->m_ScaleY;
}

const unsigned int k_MenuMeasuremenutextEncodedWords[6] = {
    0x3DDD67C9, 0x3F000000, 0x3B939A86, 0x3B939A86, 0x3B66C2B4, 0x3B939A86,
};

/* Menu_DrawStyledMenuText scales colours and the viewport by these named constants:
 * k_menuTextSelectedColorScale (1.25), k_menuTextDimColorScale (0.25),
 * k_menuTextViewportWidthScale and k_menuTextViewportHeightScale (reciprocals of the reference viewport),
 * k_menuTextAlphaMax (255.0) and k_menuTextDrawScale (1.0). g_hudReferenceViewportWidth and
 * g_hudReferenceViewportHeight are variables holding the reference viewport size. */







extern CMenuFontInfo g_menuFontStyles[];

void Onscrn_SetupSpriteMode(s32);

void OnScreen_SetupFillMode(void);

/* unable to generate initializer: unknown type */

void Menu_DrawStyledMenuText(MenuBuildEntry *option, StyledMenuTextEntryView *entry, s32 unusedDirection, StyledMenuTextPanel *menu, void *text, s32 forceTileMode) {
    f32 colorScale;
    s32 scaledRed;
    s32 scaledGreen;
    s32 scaledBlue;
    s32 scaledShadowRed;
    s32 unusedScaledShadowGreen;
    s32 unusedScaledShadowBlue;
    s32 styleIndex;
    s32 red;
    s32 green;
    s32 blue;
    s32 shadowRed;
    s32 renderMode;
    u32 styleFlags;
    u8 shadowOffset;
    CMenuFontInfo *fontInfo;

    shadowOffset = 1;
    if ((SetN64_IsModeThirteen() != 0) && (option->flags & 0x40000000)) {
        menu->shadowEnabled = 0;
    } else if (g_frontendScreenStatus.settings.local != 0 && option->flags < 0 && Defs_GetMemorySize() == 0x400000) {
        menu->shadowEnabled = 0;
    }
    if (option->flags & 0x08000000) {
        if (menu->shadowClearRequest != 0) {
            menu->shadowEnabled = 0;
        }
        Menu_DrawMenuPanel(menu, (TextBoundsText *)option, 1);
        Menu_DrawMenuPanel(menu, (TextBoundsText *)option, 0);
        shadowOffset = 0;
    }
    if (menu->shadowEnabled == 0) {
        shadowOffset = 0;
    }
    styleFlags = option->flags & 0x3FE0;
    styleIndex = 0;
    switch (styleFlags) {
    case 32: styleIndex = 0; break;
    case 64: styleIndex = 1; break;
    case 128: styleIndex = 2; break;
    case 0x100: styleIndex = 3; break;
    case 0x200: styleIndex = 4; break;
    case 0x400: styleIndex = 5; break;
    case 0x800: styleIndex = 6; break;
    case 0x1000: styleIndex = 7; break;
    case 0x2000: styleIndex = 8; break;
    default: styleIndex = 0; break;
    }
#if defined(VERSION_EU) || defined(VERSION_EU_X)
    styleIndex += g_languageIndex * 9;
#endif
    fontInfo = &g_menuFontStyles[styleIndex];
    renderMode = fontInfo->kind;
    if (forceTileMode != 0) {
        renderMode = 6;
    }
    if (g_multiplayerItemRenderState != renderMode) {
        switch (renderMode) {                           /* irregular */
        case 0:
            OnScreen_SetupTextRendering();
            break;
        case 1:
            OnScreen_SetupTextRendering();
            OnScreen_LoadTextTileModeOne();
            break;
        case 2:
            OnScreen_SetupTextRendering();
            OnScreen_LoadTextTileModeTwo();
            break;
        case 6:
            OnScreen_SetupTextRendering();
            OnScreen_LoadTextTileModeOne();
            g_creditsTextDrawingEnabled = 1;
            break;
        }
        g_multiplayerItemRenderState = renderMode;
    }
    if (entry->index == menu->selectedIndex) {
        colorScale = 1.25f;
    } else if (!(option->flags & 0x01000000)) {
        colorScale = 0.25f;
    } else {
        colorScale = 0.9f;
    }
    scaledRed = (s32) ((f32) fontInfo->color0 * colorScale);
    red = 0xFF;
    if (scaledRed < 256) {
        red = scaledRed;
    }
    scaledGreen = (s32) ((f32) fontInfo->color1 * colorScale);
    green = 0xFF;
    if (scaledGreen < 256) {
        green = scaledGreen;
    }
    scaledBlue = (s32) ((f32) fontInfo->color2 * colorScale);
    blue = 0xFF;
    if (scaledBlue < 256) {
        blue = scaledBlue;
    }
    scaledShadowRed = (s32) ((f32) fontInfo->color3 * colorScale);
    shadowRed = 0xFF;
    if (scaledShadowRed < 256) {
        shadowRed = scaledShadowRed;
    }
    OnScreen_SetTextColors(red, green, blue, shadowRed,
        (s32)((f32)fontInfo->color4 * colorScale) > 0xFF ? 0xFF : (s32)((f32)fontInfo->color4 * colorScale),
        (s32)((f32)fontInfo->color5 * colorScale) > 0xFF ? 0xFF : (s32)((f32)fontInfo->color5 * colorScale));
    g_gameSession.hud.shadowX = (s32) fontInfo->shadowOffset;
    g_gameSession.hud.shadowY = (s32) fontInfo->shadowOffset;
    OnScreen_SetTextScale(fontInfo->scaleX * (f32) (g_hudReferenceViewportWidth) * 0.0035211267f, fontInfo->scaleY * (f32) (g_hudReferenceViewportHeight) * 0.0045045046f);
    if (shadowOffset != 0) {
        shadowOffset = fontInfo->shadowOffset;
    }
    Onscrn_DrawText(text, entry->x, entry->y, (s32) (menu->alpha * (menu->fade * 255.0f)), 0, (s32) shadowOffset, 1.0f, 1.0f);
}

void Menu_DrawMenuOptionSprite(MenuOption *option, MenuOptionBox *box, s32 dir, MenuOptionFade *fadeState) {
    s32 boxAlpha;
    f32 right;
    f32 bottom;
    f32 width;
    f32 height;
    s32 *active;

    if (((SetN64_IsModeThirteen() != 0) && (option->flags & 0x40000000)) || ((g_frontendScreenStatus.settings.local != 0) && (option->flags < 0) && (Defs_GetMemorySize() == 0x400000))) {
        fadeState->highlighted = 1;
        if (g_multiplayerItemRenderState != 3) {
            g_multiplayerItemRenderState = 3;
        }
        OnScreen_SetupFillMode();
        width = (f32)box->width * box->scaleX;
        height = (f32)box->height * box->scaleY;
        bottom = (f32)box->top;
        right = (f32)box->left;
        right += width;
        bottom += height;
        active = &g_frontendScreenStatus.status[7];
        if (*active != 0) {
            if (g_frontendScreenStatus.settings.local == 0) {
                boxAlpha = 128;
            } else if (option->flags < 0) {
                boxAlpha = 0xFF;
            } else {
                boxAlpha = 192;
            }
        } else {
            boxAlpha = 128;
        }
        OnScreen_DrawBevelBox(box->left, box->top, (s32)right, (s32)bottom, 1, 0, 0, 0, 0, boxAlpha);
        return;
    }
    if (g_multiplayerItemRenderState != 3) {
        g_multiplayerItemRenderState = 3;
        Onscrn_SetupSpriteMode((s32) (fadeState->fade * (fadeState->alpha * g_menuSpriteAlphaScale)));
    }
    OnScreen_DrawSpriteResource(option->resource, 0, (s16)box->left, (s16)box->top, box->scaleX, box->scaleY, 1);
}

const float k_menuDrawMenuOptionSpriteByteMax[1] = {
    255.0f,
};

extern void Menu_MeasureMenuText(struct TextBoundsText *text, struct CItemInfo_t *metrics);
extern void Menu_DrawMenuOptionSprite(struct MenuOption *option, struct MenuOptionBox *box, s32 dir, struct MenuOptionFade *fadeState);
extern void Menu_DrawStyledMenuText(struct MenuBuildEntry *option, struct StyledMenuTextEntryView *entry, s32 unusedDirection, struct StyledMenuTextPanel *menu, void *text, s32 forceTileMode);

#if !(defined(VERSION_DE) || defined(VERSION_US_REV1))
void Menu_DrawLayeredMenuText(LayeredText *source, MenuOptionBox *position, MenuOptionBox *bounds, int flags) {
    LayeredText current;
    TextLayerMetrics first, second, third;
    int center;
    LayeredText *draw;
    center = (bounds->left + bounds->right) / 2;
    current = *source;
    current.mode = 0;
    Menu_MeasureMenuText(&current, &first);
    current = *source;
    current.mode = 1;
    current.text = 0;
    Menu_MeasureMenuText(&current, &second);
    current = *source;
    current.mode = 1;
    current.text = 0;
    Menu_MeasureMenuText(&current, &third);
    current = *source;
    current.text = 0;
    position->top += first.height;
    if (source->flags & 1) {
        position->left = center - (second.width + third.width) / 2;
    }
    position->left += third.width / 2;
    Menu_DrawMenuOptionSprite(&current, position, bounds, flags);
    current = *source;
    current.text = 0;
    position->left += (source->spacing * second.width) / 256 - third.width / 2;
    position->top += second.height / 2 - third.height / 2;
    Menu_DrawMenuOptionSprite(&current, position, bounds, flags);
    current = *source;
    if (source->flags & 1) {
        position->left = center - first.width / 2;
    }
    draw = &current;
    Menu_DrawStyledMenuText(draw, position, bounds, flags, RW_LOCALIZED_TEXT(*draw->text, draw->text, draw->text, g_languageIndex), 0);
}
#endif

#if defined(VERSION_DE) || defined(VERSION_US_REV1)
/* Measures three text layers, positions their labels, and renders the composite text. */
void Menu_DrawLayeredMenuText(LayeredText *source, MenuOptionBox *position, MenuOptionBox *bounds, int flags) {
    LayeredText current;
    TextLayerMetrics first, second, third;
    int center;
    LayeredText *draw;
    center = (bounds->left + bounds->right) / 2;
    current = *source;
    current.mode = 0;
    Menu_MeasureMenuText(&current, &first);
    current = *source;
    current.mode = 1;
    current.text = 0;
    Menu_MeasureMenuText(&current, &second);
    current = *source;
    current.mode = 1;
    current.text = 0;
    Menu_MeasureMenuText(&current, &third);
    current = *source;
    current.text = 0;
    position->top += first.height;
    if (source->flags & 1) {
        position->left = center - (second.width + third.width) / 2;
    }
    position->left += third.width / 2;
    Menu_DrawMenuOptionSprite(&current, position, bounds, flags);
    current = *source;
    current.text = 0;
    position->left += (source->spacing * second.width) / 256 - third.width / 2;
    position->top += second.height / 2 - third.height / 2;
    Menu_DrawMenuOptionSprite(&current, position, bounds, flags);
    current = *source;
    if (source->flags & 1) {
        position->left = center - first.width / 2;
    }
    draw = &current;
    Menu_DrawStyledMenuText(draw, position, bounds, flags, RW_LOCALIZED_TEXT(*draw->text, draw->text, draw->text, g_languageIndex), 0);
}
#endif

typedef struct PakModelDefinition {
    s32 kind, model, variant;
    CVector3 offset, scale;
    u8 reserved24[8];
    f32 rotationSpeed;
} PakModelDefinition;
typedef struct PakModelEntry {
    u8 reserved0[8];
    u32 flags;
    u8 reservedC[8];
    PakModelDefinition *definition;
    u8 reserved18[8];
    MenuCharacterPreviewState *state;
} PakModelEntry;
typedef struct PakModelContext {
    s16 selection;
    u8 reserved2[0x2E];
    f32 fade, alpha;
    u8 reserved38[8];
    MenuModelScreen *screen;
} PakModelContext;
extern Gfx *g_displayListCursor;
extern s32 g_lightingBufferIndex, g_hudReferenceViewportWidth, g_gameLoopFrameCount;
extern f32 literals_Scene_GetPlatformRoutePoint;
extern u8 addrLow_Bound_DrawActorWithRedMenuEffect[], addrLow_Bound_DrawActorWithMenuLighting[];
extern void *XPlus_FillMemory(void *destination, int fillValue, u32 byteCount);


extern void Gobjinst_DispatchActorTypeUpdate(char *actor);
extern s32 Cache_GetResourceActivityState(void);
extern void Cache_SetResourceActivityState(unsigned int);
extern void Scene_ChangeInstanceModel(struct Shared_World *modelBank,struct ObjectSceneChangeInstanceModel *draw,s32 modelId,s32 extra);
extern void Gobjinst_RotatePoseMatrixBuffers(void *actorRenderState);
extern void Gobjinst_UpdateActorRootDisplacement(struct Actor36 *actor);

static inline PreviewWidget *pakLoadModel_menuDrawmenumodel(PakModelEntry *entry, s32 id, s32 variant) {
    MenuCharacterPreviewState *owner = entry->state;
    PreviewWidget *source = (PreviewWidget *)Scene_FindActorDefinition(&g_world, id, variant);
    if (source == 0) {
        owner->active = 0;
        return 0;
    }
    owner->selection = id;
    owner->active = 1;
    owner->model = *source;
    owner->model.x = 0.0f;
    owner->model.y = 0.0f;
    owner->model.dx = 0.0f;
    owner->model.dy = 0.0f;
    owner->model.dz = 0.0f;
    owner->model.depth = 10240.0f;
    owner->size = owner->model.size;
    return &owner->model;
}
/* Draws a menu entry's 3D preview model: scales it to the menu screen, loads and places the model once, pulses the global opacity, picks the selected or idle update for the cursor's row, then draws it. */
typedef struct PakMenuCursor {
    s32 selection;
} PakMenuCursor;
void Menu_DrawMenuModel(PakModelEntry *entry, PakMenuCursor *cursor, void *bounds, PakModelContext *context) {
    CVector3 zero;
    CVector3 offset;
    CVector3 placed;
    CVector3 scaled;
    MenuCharacterPreviewState *widget, *selectedWidget;
    PakModelDefinition *def;
    LevelActor *draw;
    PreviewWidget *link;
    f32 ratioX;
    f32 ratioY;
    f32 wobble, opacity;
    XPlus_FillMemory(&zero, 0, 12);
    selectedWidget = entry->state;
    if (selectedWidget == 0) return;
    widget = selectedWidget;
    def = entry->definition;
    draw = &widget->actor;
    if (widget->active == 0) return;
    gSPMatrix(g_displayListCursor++, &context->screen->matrices[g_lightingBufferIndex], G_MTX_PROJECTION | G_MTX_LOAD | G_MTX_NOPUSH);
    {
        MenuModelScreen *screen = context->screen;
        ratioX = screen->width / (f32)g_hudReferenceViewportWidth;
        ratioY = screen->height;
        scaled.x = def->scale.x * ratioX;
        scaled.z = def->scale.z * ratioX;
        ratioY /= (f32)g_hudReferenceViewportHeight;
        scaled.y = def->scale.y * ratioY;
    }
    widget->size = widget->model.size;
    link = 0;
    if (!(entry->flags & 0x2000000)) {
        link = pakLoadModel_menuDrawmenumodel(entry, def->model, def->variant);
    }
    offset = def->offset;
    offset.y = offset.y - widget->size * scaled.y * 0.8f;
    Graphu64_TransformPoint(&context->screen->camera, &offset, &placed);
    if (link != 0 && !(entry->flags & 0x2000000)) {
        Gobjinst_InitializeActor(draw, -1, def->kind, g_defaultCameraSurfaceType, link, -1, 0,
                         context->screen->heading + RW_PI_F6, placed, 0,
                         def->scale, zero, 0);
        Gobjinst_DispatchActorTypeUpdate(draw);
        entry->flags |= 0x2000000;
    }
    wobble = Gu_Sinf((f32)(u32)((u32)g_gameLoopFrameCount * 10U) * (RW_PI_F6 / 180.0f)) + 1.0f;
    opacity = context->fade * context->alpha;
    g_menuTintAlpha = (s32)(opacity * (wobble * 50.0f + 50.0f));
    if (context->selection == cursor->selection) {
        draw->update = Bound_DrawActorWithRedMenuEffect;
    } else {
        draw->update = Bound_DrawActorWithMenuLighting;
    }
    if (Cache_GetResourceActivityState() == 0) {
        Cache_SetResourceActivityState(1);
    }
    if (widget->selection == 11) {
        Scene_ChangeInstanceModel(&g_world, draw, g_characterModelIds[draw->definition->character], 1);
    }
    if (g_multiplayerItemRenderState != 4) {
        g_multiplayerItemRenderState = 4;
        gDPPipeSync(g_displayListCursor++);
        gDPSetCycleType(g_displayListCursor++, G_CYC_2CYCLE);
        gDPSetTexturePersp(g_displayListCursor++, G_TP_PERSP);
        gDPSetTextureFilter(g_displayListCursor++, G_TF_BILERP);
    }
    draw->scale = scaled;
    draw->position0 = placed;
    draw->referencePosition = placed;
    Gobjinst_RotatePoseMatrixBuffers(draw);
    draw->position0 = placed;
    draw->referencePosition = placed;
    Gobjinst_UpdateActorRootDisplacement(draw);
    draw->yaw = draw->yaw + def->rotationSpeed * literals_Scene_GetPlatformRoutePoint;
    draw->position0 = placed;
    draw->referencePosition = placed;
    Geometry_BeginModelBatch();
    Gobjinst_DrawVisibleCachedActor(draw, context->screen);
    Geometry_FlushModelBatch();
}

/* Private block size of an item: type 3 items own 0x480 bytes (inline copy of Menu_GetMenuItemExtraSize). */
static inline s32 menuItemExtraSize_menuDrawmenumodel(MenuBuildItem *definition) {
    s32 size = 0;
    if (definition->type == 3) size = 1152;
    return size;
}
/* Fills one entry from its item and hands it the next private block (inline copy of
   Menu_InitMenuItemFromDescriptor). */
static inline void initializeMenuEntry_menuDrawmenumodel(MenuBuildEntry *entry, MenuBuildItem *definition, s32 index, MenuBuildState *menu, u8 **extra) {
    entry->index = index;
    entry->type = definition->type;
    entry->flags = definition->flags | 0x1800000;
    entry->x = definition->x;
    entry->y = definition->y;
    entry->red = definition->red;
    entry->green = definition->green;
    entry->blue = definition->blue;
    entry->alpha = definition->alpha;
    entry->resource = definition->resource;
    entry->definition = definition;
    entry->selection = -1;
    entry->menu = menu;
    if (menuItemExtraSize_menuDrawmenumodel(definition) != 0) {
        entry->extra = *extra;
        if (definition->type == 3) ((struct MenuItemVisibilityFlagView *)*extra)->flag = 1;
        *extra += menuItemExtraSize_menuDrawmenumodel(definition);
    }
}
/* Builds a menu in MENU's block from DEFINITION: copies the header, builds one entry per item with
   the private blocks packed after the entry array, stores the arguments, resets the eight highlight
   vertices of both banks from the default corner table, clears the input words, runs the definition's setup
   callback and then the setup callback of every entry whose item asks for one (flag 0x4000000). */
void Menu_InitializeMenu(MenuBuildState *menu, void **allocation, MenuBuildDefinition *definition, s32 value18, s32 value1C, PakMenuInputStateView *input, s32 value24, MessageList *owner) {
    u8 *extra;
    MenuBuildEntry *entry;
    s32 i, bank;
    menu->selected = definition->x;
    menu->y = definition->y;
    menu->kind = definition->kind;
    menu->allocation = allocation;
    menu->entries = (MenuBuildEntry *)(menu + 1);
    menu->count = definition->count;
    /* Per-entry extra data follows the entry array in the same allocation. */
    extra = (u8 *)&menu->entries[definition->count];
    i = 0;
    if (definition->count > 0) {
        do {
            initializeMenuEntry_menuDrawmenumodel(&menu->entries[i], &definition->items[i], i, menu, &extra);
        } while (++i < definition->count);
    }
    menu->definition = definition;
    menu->value18 = value18;
    menu->value1C = value1C;
    menu->input = input;
    menu->value24 = value24;
    menu->state = 0;
    menu->ownerSlot = owner->rotation;
    menu->fade = 0;
    menu->openA = 0;
    menu->openB = 0;
    menu->value38 = 1;
    menu->value3C = 0;
    menu->context = Menu_GetListContext(owner);
    menu->owner = owner;
    for (bank = 0; bank < 2; bank++) {
        for (i = 0; i < 8; i++) {
            menu->vertices[bank][i].ob[0] = g_menuBoxCorners[i].x;
            menu->vertices[bank][i].ob[1] = g_menuBoxCorners[i].y;
            menu->vertices[bank][i].ob[2] = g_menuBoxCorners[i].z;
            menu->vertices[bank][i].cn[0] = g_menuBoxCorners[i].red;
            menu->vertices[bank][i].cn[1] = g_menuBoxCorners[i].green;
            menu->vertices[bank][i].cn[2] = g_menuBoxCorners[i].blue;
            menu->vertices[bank][i].cn[3] = 0xFF;
            menu->vertices[bank][i].tc[0] = 0;
            menu->vertices[bank][i].tc[1] = 0;
        }
    }
    input->buttons = 0;
    input->pressedButtons = 0;
    input->history1 = 0;
    Menu_StopMenuPulse(menu);
    Menu_StartMenuPulse(menu);
    if (definition->initialize != 0) definition->initialize(menu, owner);
    i = menu->count;
    entry = menu->entries;
    while (--i != -1) {
        if (entry->definition->flags & 0x4000000) {
            if (entry->definition->activate != 0) entry->definition->activate(entry, menu, owner);
        }
        entry++;
    }
}

#if defined(VERSION_DE) || defined(VERSION_EU) || defined(VERSION_EU_X) || defined(VERSION_US)
const f32 g_pakMenuAnimationLimits[4] = {
    1.0f, 0.4f, 1.0f, 0.4f,
};
#endif

/* An entry stores its four neighbour steps in the colour bytes: red, green, blue and alpha hold the
   relative index to move to for directions 16, 17, 18 and 19. */
static s8 *MenuEntry_StepLink_pakMenuEntries(MenuBuildEntry *entry, u8 dir) {
    switch (dir) {
    case 16:
        return (s8 *)&entry->red;
    case 17:
        return (s8 *)&entry->green;
    case 18:
        return (s8 *)&entry->blue;
    default:
        return (s8 *)&entry->alpha;
    }
}

/* The flag an entry needs before arrival from the given direction records the way back. */
static u32 MenuEntry_ReverseLinkFlag_pakMenuEntries(u8 dir) {
    switch (dir) {
    case 16:
        return 0x80000;
    case 17:
        return 0x40000;
    case 18:
        return 0x200000;
    default:
        return 0x100000;
    }
}

/* Moves a menu cursor in one direction (16 to 19) by the step stored on the current entry, wrapping at either
   end. When the new entry allows it, it records the step back (direction 16 <-> 17, 18 <-> 19). The move repeats
   until the cursor reaches an entry flagged 0x1800000 whose definition can be activated. */
void Menu_MoveMenuCursor(MenuBuildState *menu, u8 dir) {
    MenuBuildEntry *entry;
    s32 old;

    entry = &menu->entries[menu->selected];
    do {
        old = menu->selected;
        menu->selected += *MenuEntry_StepLink_pakMenuEntries(entry, dir);
        if (menu->selected < 0) {
            menu->selected = menu->count - 1;
        } else if (menu->selected >= menu->count) {
            menu->selected = 0;
        }
        entry = &menu->entries[menu->selected];
        old -= menu->selected;
        if (dir >= 16 && dir <= 19 && (entry->flags & MenuEntry_ReverseLinkFlag_pakMenuEntries(dir))) {
            *MenuEntry_StepLink_pakMenuEntries(entry, dir ^ 1) = old;
        }
    } while ((entry->flags & 0x1800000) != 0x1800000 || entry->definition->activate == 0);
}

/* Update entry callbacks, animate opening/closing, and handle the selected entry. */
s32 Menu_UpdateMenuEntries(MenuBuildState *menu, void *context) {
    s32 closeRequested = 0;
    MenuBuildEntry *entry;
    s32 i;
    s32 selectionFlags;
    s32 allowRepeat;
    s32 buttons;
    s32 state;
    MenuBuildItemCallback callback;
    MenuBuildHoldCallback hold = menu->definition->hold;
    if (hold != 0) {
        closeRequested = hold(menu, context);
    }
    i = menu->count;
    entry = menu->entries;
    while (--i != -1) {
        callback = entry->definition->update;
        if (callback != 0) {
            callback(entry, menu, context);
        }
        entry++;
    }
    entry = menu->entries + menu->selected;
    menu->fade += literals_Scene_GetPlatformRoutePoint;
    selectionFlags = entry->flags & 0x400000;
    Menu_StepSpriteFrame(menu);
    switch (menu->state) {
    case 0:
        menu->openA += literals_Scene_GetPlatformRoutePoint;
        if (menu->openA >= g_pakMenuAnimationLimits[0]) {
            menu->openA = g_pakMenuAnimationLimits[0];
            menu->state = 1;
        }
        break;
    case 1:
        menu->openB += literals_Scene_GetPlatformRoutePoint * g_menuPanelOpenRate;
        if (menu->openB >= g_menuPanelOpenLimit) {
            menu->openB = g_menuPanelOpenLimit;
            menu->state = 2;
        }
        break;
    case 3:
        menu->openB -= literals_Scene_GetPlatformRoutePoint * g_menuPanelCloseRate;
        if (menu->openB <= 0.0f) {
            menu->openB = 0.0f;
            menu->state = 4;
        }
        break;
    case 4:
        menu->openA -= literals_Scene_GetPlatformRoutePoint;
        if (menu->openA <= 0.0f) {
            menu->openA = 0.0f;
            return 1;
        }
        break;
    }
    state = menu->state;
    if (state >= 3) {
        return 0;
    }
    if (state < 0) {
        return 0;
    }
    if (closeRequested != 0) {
        menu->state = 4;
    }
    if (entry->flags & 8) {
        return 0;
    }
    allowRepeat = 1;
    if (entry->type == 2) {
        buttons = menu->input->buttons;
        if (buttons & 0x20202) {
            allowRepeat = 0;
            entry->selection -= 2;
            if (entry->selection < 0) {
                entry->selection = 0;
            }
        } else if (buttons & 0x40101) {
            entry->selection += 2;
            allowRepeat = 0;
            if (entry->selection >= 256) {
                entry->selection = 0xFF;
            }
        }
    }
    if (selectionFlags == 0) {
        if (Control_IsLeftPressed(menu->input) != 0) {
            Menu_MoveMenuCursor(menu, 16);
        }
        if (Control_IsRightPressed(menu->input) != 0) {
            Menu_MoveMenuCursor(menu, 17);
        }
    } else if (menu->input->buttons & 0x60303) {
        allowRepeat = 0;
    }
    if (allowRepeat != 0) {
        if (Control_IsNavUp(menu->input) != 0) {
            Menu_MoveMenuCursor(menu, 18);
        }
        if (Control_IsNavDown(menu->input) != 0) {
            Menu_MoveMenuCursor(menu, 19);
        }
    }
    if (menu->state != 2) {
        return 0;
    }
    if (Control_IsAButtonPressed(menu->input) != 0 ||
        (Control_IsLeftPressed(menu->input) != 0 && selectionFlags != 0) ||
        (Control_IsRightPressed(menu->input) != 0 && selectionFlags != 0)) {
        callback = entry->definition->activate;
        if (callback != 0 && callback(entry, menu, context) == 0) {
            return 0;
        }
        menu->state = 3;
    }
    return 0;
}

/* Lay out visible menu entries and draw their callbacks with a pulsing selection highlight. */
void Menu_DrawMenuEntries(struct MenuStyle *menu, s8 *member) {
    CItemInfo bounds, metrics, placed;
    TextBoundsData *data;
    TextBoundsText *entry;
    s32 i;
    f32 centerX, centerY, top, bottom, alpha;

    data = Menu_GetListContext(member);
    bounds.left = 1024;
    bounds.right = -1024;
    bounds.m_Top = 1024;
    bounds.m_Bottom = -1024;
    metrics.width = 0;
    metrics.height = 0;
    metrics.left = 0;
    metrics.right = 0;
    metrics.m_Top = 0;
    metrics.m_Bottom = 0;
    for (i = 0; i < menu->count; i++) {
        entry = &menu->entries[i];
        if (entry->flags & 0x800000) {
            if (entry->flags & 0x20000000) {
                metrics.left = 1024;
                metrics.right = -1024;
                metrics.m_Top = 1024;
                metrics.m_Bottom = -1024;
                metrics.width = 0;
                metrics.height = 0;
            } else {
                Menu_MeasureMenuText(entry, &metrics);
            }
            bounds.left = bounds.left < metrics.left ? bounds.left : metrics.left;
            bounds.right = bounds.right > metrics.right ? bounds.right : metrics.right;
            bounds.m_Top = bounds.m_Top < metrics.m_Top ? bounds.m_Top : metrics.m_Top;
            bounds.m_Bottom = bounds.m_Bottom > metrics.m_Bottom ? bounds.m_Bottom : metrics.m_Bottom;
        }
    }
    bounds.width = bounds.right - bounds.left;
    bounds.height = bounds.m_Bottom - bounds.m_Top;
    if (bounds.width < 0 || bounds.height < 0) {
        return;
    }
    centerX = data->x + data->width * 0.5f + menu->x;
    centerY = data->y + data->height * 0.5f + menu->y;
    bounds.left = centerX - bounds.width / 2;
    bounds.right = centerX + bounds.width / 2;
    bounds.m_Top = centerY - bounds.height / 2;
    bounds.m_Bottom = centerY + bounds.height / 2;
    metrics.width = 0;
    metrics.height = 0;
    metrics.left = 0;
    metrics.right = 0;
    metrics.m_Top = 0;
    metrics.m_Bottom = 0;
    g_multiplayerItemRenderState = -1;
    for (i = 0; i < menu->count; i++) {
        entry = &menu->entries[i];
        if (entry->flags & 0x800000) {
            metrics.entryIndex = i;
            if (entry->flags & 0x20000000) {
                Menu_MeasureMenuText(entry, &metrics);
                metrics.width = 0;
                metrics.height = 0;
                metrics.left = data->x;
                metrics.right = 0;
                metrics.m_Top = data->y;
                metrics.m_Bottom = 0;
            } else {
                Menu_MeasureMenuText(entry, &metrics);
            }
            placed = metrics;
            if (!(entry->flags & 0x20000000)) {
                placed.left += bounds.left;
                placed.right += bounds.left;
                placed.m_Top += bounds.m_Top;
                placed.m_Bottom += bounds.m_Top;
            }
            if (entry->flags & 1) {
                placed.left = centerX - metrics.width / 2;
                placed.right = placed.left + metrics.width;
            }
            if (entry->flags & 2) {
                placed.left = bounds.left;
                placed.right = placed.left + metrics.width;
            }
            if (entry->flags & 4) {
                placed.right = bounds.right;
                placed.left = placed.right - metrics.width;
            }
            if (entry->flags & 0x800000) {
                if (menu->state == i && entry->mode != 3 && !(entry->flags & 8)) {
                    top = placed.m_Top;
                    bottom = placed.m_Bottom;
                    /* Preserve the highlight extent calculation and its float rounding. */
                    bottom = top + (bottom - top);
                    OnScreen_SetupFillMode();
                    alpha = menu->alpha * menu->fade *
                        ((Gu_Sinf((f32)(g_gameLoopFrameCount * 10) * 0.017453294f) + 1.0f) * 50.0f + 50.0f);
                    if (entry->flags & 0x10) {
                        OnScreen_DrawBevelBox(placed.left - 4, top, placed.right + 4, bottom, 0, 0, 255, 0, 10, (u8)alpha);
                    } else {
                        OnScreen_DrawBevelBox(placed.left - 4, top, placed.right + 4, bottom, 0, 0, 255, 0, 10, (u8)alpha);
                    }
                    g_multiplayerItemRenderState = -1;
                }
                entry->handlers->draw(entry, &placed, &bounds, menu);
            }
        }
    }
}

/* The font a text entry's style bits select (the switch of Menu_DrawStyledMenuText). */
static __inline__ TextBoundsFont *textBoundsFont_pakMenuEntries(TextBoundsText *text) {
    s32 style = 0;
    switch ((u32)text->flags & 0x3FE0) {
    case 32: style = 0; break;
    case 64: style = 1; break;
    case 128: style = 2; break;
    case 0x100: style = 3; break;
    case 0x200: style = 4; break;
    case 0x400: style = 5; break;
    case 0x800: style = 6; break;
    case 0x1000: style = 7; break;
    case 0x2000: style = 8; break;
    default: style = 0; break;
    }
    return &g_menuFontStyles[style];
}
/* Draws the dark backing panel behind a menu: as wide as the screen, centred on the menu's anchor, and as
 * tall as a fraction of the screen height less a margin. The relative pass places it above the anchor, the
 * other below. Measures every entry first and draws nothing when the menu has no extent. */
void Menu_DrawMenuPanel(StyledMenuTextPanel *menu, TextBoundsText *text, s32 relative) {
    TextBoundsData *data = menu->data;
    TextBoundsFont *font = textBoundsFont_pakMenuEntries(text);
    CItemInfo panel;
    CItemInfo bounds;
    s32 i;
    f32 centerX;
    f32 height;
    s32 top;
    panel.left = 1024;
    panel.right = -1024;
    panel.m_Top = 1024;
    panel.m_Bottom = -1024;
    bounds.width = 0;
    bounds.height = 0;
    bounds.left = 0;
    bounds.right = 0;
    bounds.m_Top = 0;
    bounds.m_Bottom = 0;
    for (i = 0; i < menu->count; i++) {
        Menu_MeasureMenuText(&menu->entries[i], &bounds);
        panel.left = panel.left < bounds.left ? panel.left : bounds.left;
        panel.right = panel.right > bounds.right ? panel.right : bounds.right;
        panel.m_Top = panel.m_Top < bounds.m_Top ? panel.m_Top : bounds.m_Top;
        panel.m_Bottom = panel.m_Bottom > bounds.m_Bottom ? panel.m_Bottom : bounds.m_Bottom;
    }
    panel.width = panel.right - panel.left;
    panel.height = panel.m_Bottom - panel.m_Top;
    if (panel.width < 0 || panel.height < 0) {
        return;
    }
    centerX = data->x + data->width * 0.5f + menu->x;
    panel.width = SCREEN_WD;
    panel.left = centerX - panel.width / 2;
    panel.right = centerX + panel.width / 2;
    height = SCREEN_HT * 0.21621622f;
    if (SCREEN_HT >= 223) {
        height -= 13.0f;
    } else {
        height -= 9.0f;
    }
    if (relative != 0) {
        top = data->y + (f32)SCREEN_HT + menu->y - height;
    } else {
        top = data->y + menu->y;
    }
    panel.m_Top = top;
    panel.m_Bottom = top + height;
    panel.height = panel.m_Bottom - panel.m_Top;
    OnScreen_SetupFillMode();
    OnScreen_DrawBevelBox(panel.left, panel.m_Top, panel.right, panel.m_Bottom, 1, 0, 0, 0, 0, (u8)(u32)(menu->alpha * 192.0f));
}

const char g_menuText[5] =
    "menu\000";

/* Loads a preview model into the widget state, resets its motion and remembers its original size. */






void *Menu_CreateMenuFromParameters(struct MessageList *owner, struct MenuCreationParameters *params) {
    struct Dialog *list = params->list;
    s32 a;
    s32 b;
    s32 c;
    s32 d;
    s32 size;
    s32 i;
    void **block;
    void *first;

    if (list != 0) {
        a = list->value;
        b = params->b;
        c = params->c;
        d = params->d;
        size = list->count * 40 + 472;
        for (i = 0; i < list->count; i++) {
            s32 extra = 0;
            if (list->entries[i].type == 3) {
                extra = 1152;
            }
            size += extra;
        }
        block = Cache_AllocateResource(0, size, 59, g_menuText);
        if (block == 0) {
            return 0;
        }
        first = *block;
        if (first != 0) {
            Menu_InitializeMenu(first, block, list, a, b, c, d, owner);
            List_PrependIntrusive(owner, first);
            if (++owner->rotation >= 4) {
                owner->rotation = 0;
            }
            return first;
        }
    }
    return 0;
}

extern u8 *Menu_GetDynamicItemText(struct TextBoundsText *);
extern void Menu_DrawStyledMenuText(struct MenuBuildEntry *option, struct StyledMenuTextEntryView *entry, s32 unusedDirection, struct StyledMenuTextPanel *menu, void *text, s32 forceTileMode);
int Menu_CountLineChars(LayeredText *item) {
    u8 *p;
    int len;

    len = 0;
    if (item->mode == 5) {
        p = Menu_GetDynamicItemText(item);
    } else {

#if defined(VERSION_EU) || defined(VERSION_EU_X)
p = item->text[g_languageIndex];
#else
p = *item->text;
#endif

    }
    while (p != 0 && *p != 0 && *p != '\n') {
        p++;
        len++;
    }
    return len;
}

void Menu_DrawMenuItemLabel(struct Field *object, s32 second, s32 third, s32 fourth) {

#if defined(VERSION_EU) || defined(VERSION_EU_X)
Menu_DrawStyledMenuText(object, second, third, fourth, object->text[g_languageIndex], 0);
#else
Menu_DrawStyledMenuText(object, second, third, fourth, *object->text, 0);
#endif

}

void Menu_DrawLocalizedMenuItemText(struct Field *object, s32 second, s32 third, s32 fourth) {

#if defined(VERSION_EU) || defined(VERSION_EU_X)
Menu_DrawStyledMenuText(object, second, third, fourth, object->text[g_languageIndex], 0);
#else
Menu_DrawStyledMenuText(object, second, third, fourth, *object->text, 0);
#endif

}

void Menu_DrawMenuCharacter(struct ObjectPakDrawMenuCharacter *object, s32 second, s32 third, s32 fourth) {
    u8 text[2];

    text[0] = object->character;
    text[1] = 0;
    Menu_DrawStyledMenuText(object, second, third, fourth, text, 0);
}

void Menu_DrawDynamicMenuText(LayeredText *object, s32 second, s32 third, s32 fourth) {
#if defined(VERSION_DE)
    Menu_DrawStyledMenuText(object, second, third, fourth, Menu_GetDynamicItemText(object), 1);
#else
    Menu_DrawStyledMenuText(object, second, third, fourth,
#if defined(VERSION_EU) || defined(VERSION_EU_X) || defined(VERSION_US) || defined(VERSION_US_REV1)
Menu_GetDynamicItemText
#else
Menu_GetGermanDynamicItemText
#endif
(object), 1);
#endif
}

PreviewWidget *Menu_SelectPreviewModel(MenuPreviewSelectionView *widget,int selection,int kind) {
 MenuCharacterPreviewState *state=widget->state;
 PreviewWidget *model=Scene_FindActorDefinition(&g_world,selection,kind);
 if(!model){state->active=0;return 0;}
 state->selection=selection;
 state->active=1;
 state->model=*model;
 state->model.x=0;state->model.y=0;
 state->model.dx=0;state->model.dy=0;state->model.dz=0;
 state->model.depth=(10240.0f);
 state->size=state->model.size;
 return &state->model;
}

/* Returns the address sizeof(Profile) bytes into the block in an object, or null when the
   object has no block. */

char *Menu_GetObjectDetailData(struct MenuBuildEntry *object) {
    char *result = 0;

    if (object->extra != 0) {
        result = (char *)object->extra + sizeof(Profile);
    }
    return result;
}

/* Computes a glyph advance using character widths and special spacing before T. */
f32 Menu_GetGlyphAdvance(s32 ch, u8 nextCh, f32 scale, f32 specialAdvance) {
    f32 factor;
    s32 cur;
    s32 nextA;
    s32 nextB;

    cur = ch & 0xFF;
    factor = 1.0f;
    switch (cur) {
    case 36:
    case 38:
    case 126:
        return specialAdvance;
    case 73:
    case 105:
        factor = 0.5f;
    default:
        break;
    case 76:
    case 108:
        nextA = nextCh & 0xFF;
        if ((nextA == 116) || (nextA == 84)) {
            factor = 0.7f;
        }
        break;
    case 65:
    case 97:
        nextB = nextCh & 0xFF;
        if ((nextB == 116) || (nextB == 84)) {
            factor = 0.8f;
        }
        break;
    case 77:
    case 109:
        factor = 1.2f;
        break;
    case 33:
    case 46:
        factor = 0.4f;
        break;
    }
    return factor * scale;
}

/* Sums the glyph advances that Menu_GetGlyphAdvance returns for each character pair of a string at the given scales, stopping at a newline, the end of the string or a null pointer. */
f32 Menu_MeasureLine(u8 *p, f32 sx, f32 sy) {
    f32 total;
    u8 c;

    total = 0.0f;
    while (p != 0 && (c = *p) != 0 && c != '\n') {
        p++;
        total += Menu_GetGlyphAdvance(c, *p, sx, sy);
    }
    return total;
}

/* Returns whether Menu_CreateMenuFromParameters gives a non-zero answer for the third argument. */
s32 Menu_TryCreateMenu(void *first, void *second, void *third) {
    return Menu_CreateMenuFromParameters(third, second) != 0;
}

/* Returns zero. */
s32 Menu_ReturnZeroTemplateHook(void) {
    return 0;
}

/* Returns the locked flag of the inner menu an outer record points to. */
s32 Menu_GetInnerMenuLock(struct Outer *outer) {
    return outer->inner->locked;
}

/* Adjusts a value from controller input and clamps or wraps it between its limits. */
unsigned int Control_IsAButtonPressed(struct ControllerProfile *profile); /* extern */
s32 Menu_AdjustValue(MenuValueStepView *menu,s32 value,s32 step,s32 minimum,s32 maximum,s32 wrap) {
 if(((s32 (*)(s32))Control_IsLeftPressed)(menu->flags))value-=step;
 if(((s32 (*)(s32))Control_IsRightPressed)(menu->flags)||Control_IsAButtonPressed(menu->flags))value+=step;
 if(value<minimum) {
  value=minimum;if(wrap)value=maximum;
 } else if(value>maximum) {
  value=maximum;if(wrap)value=minimum;
 }
 return value;
}

/* Steps a menu value left or right with optional range wrapping. */

s32 Menu_StepValue(MenuValueStepView *menu, s32 value, s32 step, s32 minimum, s32 maximum, s32 wrap) {
    s32 stepped;
    s32 current;
    s32 result;

    current = value;
    if (((s32 (*)(s32))Control_IsLeftPressed)(menu->flags) != 0) {
        current -= step;
        if (current < minimum) {
            current = minimum;
            if (wrap != 0) {
                current = maximum;
            }
        }
    }
    result = current;
    if (((s32 (*)(s32))Control_IsRightPressed)(menu->flags) != 0) {
        stepped = current + step;
        result = stepped;
        if (maximum < stepped) {
            current = maximum;
            if (wrap != 0) {
                current = minimum;
            }
            result = current;
        }
    }
    return result;
}

void Menu_InitMenuMessageList(void *object) {
    List_InitializeIntrusive(object, 464, 468);
    ((MessageList *)object)->rotation = 0;
}

/* Allocates a block sized for the entries of a list through Cache_AllocateResource, builds it with Menu_InitializeMenu from a zero and three arguments, registers it with List_PrependIntrusive and advances the owner's rotating counter below four, returning the block or zero. */
MenuBuildState *Menu_OpenDialog(void *parent, MenuBuildDefinition *list, s32 player, s32 controller, s32 d) {
    struct MessageList *owner;
    s32 size = list->count * sizeof(MenuBuildEntry) + sizeof(MenuBuildState);
    s32 i;
    void **block;
    MenuBuildState *first;

    for (i = 0; i < list->count; i++) {
        s32 extra = 0;
        if (list->items[i].type == 3) {
            extra = 1152;
        }
        size += extra;
    }
    block = Cache_AllocateResource(0, size, 59, g_menuText);
    if (block == 0) {
        return 0;
    }
    first = *block;
    if (first == 0) {
        return 0;
    }
    Menu_InitializeMenu(first, block, list, 0, player, (PakMenuInputStateView *)controller, d, parent);
    List_PrependIntrusive(parent, first);
    owner = parent;
    if (++owner->rotation >= 4) {
        owner->rotation = 0;
    }
    return first;
}

/* Allocates a block sized for the entries of a list (forty bytes each plus 0x480 for every entry of type three, over a 0x1D8 header) through Cache_AllocateResource, builds it with Menu_InitializeMenu from four parameters, registers it with List_PrependIntrusive and advances the owner's rotating counter below four, returning the block or zero. */

MenuBuildState *Menu_CreateMenuFromTemplate(struct MessageList *owner, struct MenuTemplateParameters *params, MenuBuildDefinition *list) {
    s32 a = params->a;
    s32 b = params->b;
    s32 c = params->c;
    s32 d = params->d;
    s32 size = list->count * sizeof(MenuBuildEntry) + sizeof(MenuBuildState);
    s32 i;
    void **block;
    MenuBuildState *first;

    for (i = 0; i < list->count; i++) {
        s32 extra = 0;
        if (list->items[i].type == 3) {
            extra = 1152;
        }
        size += extra;
    }
    block = Cache_AllocateResource(0, size, 59, g_menuText);
    if (block == 0) {
        return 0;
    }
    first = *block;
    if (first == 0) {
        return 0;
    }
    Menu_InitializeMenu(first, block, list, a, b, (PakMenuInputStateView *)c, d, owner);
    List_PrependIntrusive(owner, first);
    if (++owner->rotation >= 4) {
        owner->rotation = 0;
    }
    return first;
}

/* Allocates a block sized for the entries of a list through Cache_AllocateResource, builds it with Menu_InitializeMenu from four parameters, registers it with List_PrependIntrusive and advances the owner's rotating counter below four, returning the block or zero. Adapted from Menu_CreateMenuFromTemplate with the first parameter read from offset 0x14 instead of 0x18. */

MenuBuildState *Menu_AllocateMenu(struct MessageList *owner, struct ParamsPakAllocateMenu *params, MenuBuildDefinition *list) {
    s32 a = params->a;
    s32 b = params->b;
    s32 c = params->c;
    s32 d = params->d;
    s32 size = list->count * sizeof(MenuBuildEntry) + sizeof(MenuBuildState);
    s32 i;
    void **block;
    MenuBuildState *first;

    for (i = 0; i < list->count; i++) {
        s32 extra = 0;
        if (list->items[i].type == 3) {
            extra = 1152;
        }
        size += extra;
    }
    block = Cache_AllocateResource(0, size, 59, g_menuText);
    if (block == 0) {
        return 0;
    }
    first = *block;
    if (first == 0) {
        return 0;
    }
    Menu_InitializeMenu(first, block, list, a, b, (PakMenuInputStateView *)c, d, owner);
    List_PrependIntrusive(owner, first);
    if (++owner->rotation >= 4) {
        owner->rotation = 0;
    }
    return first;
}

/* Tears down every node of one list: walks it from the head, remembering each node's successor first,
   skips nodes in state 2 unless the list is the global one at g_matchEndingTeamWheelClose or the global list's flag is clear,
   and for each remaining node asks Menu_UpdateMenuEntries whether it may go. A node that may go has its
   optional finalize handler called, its input button state cleared, and is unlinked with List_RemoveIntrusive and
   its allocation released through Cache_ReleaseResource. */
void Menu_UpdateDialogList(MessageList *list) {
    MenuBuildState *node;
    MenuBuildState *next;
    PakMenuInputStateView *state;

    node = (MenuBuildState *)list->head;
    while (node != 0) {
        next = node->next;
        if (!((node->state == 2) && (list != &g_matchEndingTeamWheelClose) && (g_matchEndingTeamWheelClose.flag != 0))) {
            if (Menu_UpdateMenuEntries(node, list) != 0) {
                if (node->definition->finalize != 0) {
                    node->definition->finalize(node, list);
                }
                state = node->input;
                state->buttons = 0;
                state->pressedButtons = 0;
                state->history1 = 0;
                List_RemoveIntrusive(list, node);
                Cache_ReleaseResource(0, node->allocation);
            }
        }
        node = next;
    }
}

void Menu_DispatchMenuListCallback(struct MenuCallbackListOwner *owner) {
    struct PakMenuVirtualNode *node = owner->head;

    while (node != 0) {
        ((void (*)(struct PakMenuVirtualNode *, struct MenuCallbackListOwner *))node->vtable[4])(node, owner);
        node = node->next;
    }
}

int Menu_CountLiveNodes(struct CMenu_t **head) {
    MenuBuildState *node = (MenuBuildState *)*head;
    int count = 0;
    while (node != 0) {
        if (node->state != 4) {
            count++;
        }
        node = node->next;
    }
    return count;
}

/* Removes every item from a list until its head is null, running each item's optional callback, clearing three words of its state, unlinking it through List_RemoveIntrusive and releasing its resource through Cache_ReleaseResource. */

/* Returns the GameplayCamera that contains the given messageList member: callers pass the
   address of that member and get back the start of the enclosing structure. */
void *Menu_GetListContext(void *member) {
    return (char *)member - MEMBER_OFFSET(GameplayCamera, messageList);
}

void Menu_ClearMenuItemList(struct ListPakClearMenuItemList *list) {
    struct MenuResourceItemView *item;
    struct MenuItemInputStateView *state;

next_item:
    {
        item = list->head;
        if (item == 0) {
            return;
        }
        if (item->handlers->callback != 0) {
            item->handlers->callback(item, list);
        }
        state = item->state;
        state->a = 0;
        state->b = 0;
        state->c = 0;
        List_RemoveIntrusive(list, item);
        Cache_ReleaseResource(0, item->resource);
        goto next_item;
    }
}

void Menu_MeasureMenuItemText(struct MenuItemTargetView *object, f32 scale) {
    void *target;

    if (object->kind == 5) {
        target =
#if defined(VERSION_DE) || defined(VERSION_EU) || defined(VERSION_EU_X) || defined(VERSION_US) || defined(VERSION_US_REV1)
Menu_GetDynamicItemText
#else
Menu_GetGermanDynamicItemText
#endif
(object);
    } else {

#if defined(VERSION_EU) || defined(VERSION_EU_X)
        target = object->target[g_languageIndex];
#else
        target = *object->target;
#endif
    }
    Menu_MeasureLine(target, scale, scale);
}

/* Clears the pulse frame and the pulse-active flag of a menu entry; Menu_StartMenuPulse tests the flag. */
void Menu_StopMenuPulse(MenuBuildState *object) {
    object->pulseActive = 0;
    object->pulseFrame = 0;
}

/* Starts the one-shot pulse: when the pulse-active flag is clear it sets the flag and clears the pulse frame;
   Menu_StopMenuPulse clears both. */
void Menu_StartMenuPulse(MenuBuildState *object) {
    if (object->pulseActive == 0) {
        object->pulseActive = 1;
        object->pulseFrame = 0;
    }
}

/* Advances the pulse frame by the pulse-active step and clears both fields once the frame
   reaches 0x30. */
void Menu_StepSpriteFrame(MenuBuildState *object) {
    object->pulseFrame += object->pulseActive;
    if (object->pulseFrame >= 48) {
        object->pulseFrame = 0;
        object->pulseActive = 0;
    }
}

/* Folds the counter in an object into a triangle wave: values below 0x18 are
   returned as they are and the rest as 0x2F less the value. */
s32 Menu_GetMirroredMenuFrame(MenuBuildState *object) {
    s32 count = object->pulseFrame;

    if (count < 24) {
        return count;
    }
    return 47 - count;
}

void Menu_DrawAnimatedMenuSprite(MenuBuildState *e) {
    s32 frame;
    Gfx *gfx;
    Shared_HudView *o;
    f32 w;
    f32 h;

    if (e->pulseActive != 0) {
        if (e->pulseFrame < 24) {
            frame = e->pulseFrame;
        } else {
            frame = 47 - e->pulseFrame;
        }
        OnScreen_SetupTextRendering();
        Geometry_SetModePreset(21);
        o = e->context;
        gfx = g_displayListCursor++;
        w = o->width;
        h = o->height;
        gDPSetEnvColor(gfx, 255, 0, 0, 255);
        gfx = g_displayListCursor++;
        gDPSetPrimColor(gfx, 0, 0, 224, 0, 0, 255);
        OnScreen_DrawSpriteResource(103, frame, ((Shared_HudView *)e->context)->x, ((Shared_HudView *)e->context)->y,
                      w / (f32)g_hudReferenceViewportWidth * 5.0f, h / (f32)g_hudReferenceViewportHeight * 4.0f, 1);
    }
}

/* Returns 0x480 when the halfword a record starts with is 3, otherwise zero. */
s32 Menu_GetMenuItemExtraSize(s16 *record) {
    if (*record == 3) {
        return 1152;
    }
    return 0;
}

/* Sets a field of the second argument when the halfword the first starts with
   is 3. */
void Menu_EnableMenuItemExtra(s16 *record, struct MenuItemVisibilityFlagView *object) {
    if (*record == 3) {
        object->flag = 1;
    }
}

/* Initializes a widget from its descriptor and reserves extra state for type three widgets. */
void Menu_InitMenuItemFromDescriptor(CMenuItem *w, WidgetDescriptor *d, char **arena, int id, int arg) {
 int size; char *extra;
 w->id=id; w->type=d->type; w->flags=d->flags|0x1800000;
 w->x=d->x; w->y=d->y; w->r=d->r; w->g=d->g; w->b=d->b; w->a=d->a;
 w->value=d->value; w->desc=d; w->index=-1; w->m_pMenu=arg;
 size=0; if(d->type==3) size=1152;
 if(size) {
 w->extra=*arena;
 extra=*arena; if(d->type==3) ((struct MenuItemVisibilityFlagView *)(extra))->flag=1;
 { int step=0; if(d->type==3) step=1152;
 *arena+=step; }
 }
}

void *Menu_GetWidgetStyle(MenuItemFlagsView *widget) {
 s32 index=0;
 switch(widget->flags & 0x3fe0) {
 case 32: break;
 case 64: index=1; break;
 case 128: index=2; break;
 case 0x100: index=3; break;
 case 0x200: index=4; break;
 case 0x400: index=5; break;
 case 0x800: index=6; break;
 case 0x1000: index=7; break;
 case 0x2000: index=8; break;
 default: index=0; break;
 }
#if defined(VERSION_EU) || defined(VERSION_EU_X)
 index += g_languageIndex * 9;
#endif
 return &g_menuFontStyles[index];
}

#if defined(VERSION_US_REV1)
const float k_MenuPakFloatPairs[4] = {
    1.0f, 0.4f, 1.0f, 0.4f,
};
#endif
