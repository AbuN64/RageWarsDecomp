#include "include_asm.h"
#include "COMMON/LONE/g_defaultCameraSurfaceType.H"
#include "COMMON/LONE/G_LANGUAGEINDEX.H"
#include "COMMON/LONE/MENU_TINT_ALPHA.H"
#include "COMMON/LONE/HUD_REFERENCE_VIEWPORT_HEIGHT.H"
#include "COMMON/VECTOR4F.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/TEXTLAYERMETRICS.H"
#include "MENU/OPTION_AND_TEXT_LAYER_VIEWS.H"
#include "TYPES.H"
#include "COMMON/MENU_TEXT.H"
#include "COMMON/MENU_UI_PROVIDERS.H"

extern void Menu_MeasureMenuText(struct TextBoundsText *text, struct CItemInfo_t *metrics);
extern void Menu_DrawMenuOptionSprite(struct MenuOption *option, struct MenuOptionBox *box, s32 dir, struct MenuOptionFade *fadeState);
extern void Menu_DrawStyledMenuText(struct MenuTextOwnerView *option, struct StyledMenuTextEntryView *entry, s32 unusedDirection, struct StyledMenuTextPanel *menu, void *text, s32 forceTileMode);

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

#include "COMMON/WORLD.H"
#include "COMMON/OBJECTRECAT28.H"
#include <PR/gbi.h>
#include "COMMON/MATH_HELPERS.H"
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
extern u8 *Scene_FindActorDefinition(void *, s32, s32);
extern void Graphu64_TransformPoint(void *matrix, void *inputPoint, void *transformedPoint);
extern void Gobjinst_InitializeActor(u8 *, s32, s32, s32, u8 *, s32, s32, f32, CVector3, s32, CVector3, CVector3, s32);
extern void Gobjinst_DispatchActorTypeUpdate(char *actor);
extern s32 Cache_GetResourceActivityState(void);
extern void Cache_SetResourceActivityState(unsigned int);
extern void Scene_ChangeInstanceModel(struct SceneModelBankView *modelBank,struct ObjectSceneChangeInstanceModel *draw,s32 modelId,s32 extra);
extern void Gobjinst_RotatePoseMatrixBuffers(void *actorRenderState);
extern void Gobjinst_UpdateActorRootDisplacement(struct Actor36 *actor);
extern void Gobjinst_DrawVisibleCachedActor(void *object, void *camera);
static inline PreviewWidget *pakLoadModel(PakModelEntry *entry, s32 id, s32 variant) {
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
/* Draws a menu entrys 3D preview model: scales it to the menu screen, loads and places the model once,n GAPS-TRIAGE.md HANDOFF.md PLAN-100.md STATUS.md TOOL-GAPS.md TOOLING-INTERIM-HANDOFF.md TYPES-PLAN.md __pycache__ archive attic attic-local backups batch-run-2.log batch-run-3.log batch-run-4.log batch-run-5.log batch-run-6.log batch1-run.log batch_cycle.sh check-batch1.log cmp cmp_acluster-34.out cmp_acluster-5C.out cmp_acluster-60.out cmp_acluster-A8.out cmp_acluster-c494-v2.out cmp_acluster-c494-v3.out cmp_acluster-c494.out cmp_acluster-d1342.out cmp_acluster-da5c2.out cmp_ceb0_reconcile.err cmp_ceb0_reconcile.json cmp_ceb0_reconcile2.out corpus cycle2.log cycle3.log cycle6.log dashboard exp gate gen_data_candidates.py gh-cred.sh gh-out gh-work ghidra-proj ghidra_12.1.4_PUBLIC_20260921.zip ghscripts handoff-archive-2026-10-12-0315.md handoff-archive-2026-10-12-1015.md handoff-archive-2026-10-12-1240.md handoff-archive-2026-10-12-1415.md handoff-archive-2026-10-12-1735.md handoff-archive-2026-10-12-1850.md handoff-archive-2026-10-12-2155.md harvest-ledger.tsv harvest_loop.py landings.tsv lanes logs makecheck-0013.log makecheck-gate2.log next.json night.log night.sh noc-free.json orch parked.txt plan_gen.py queue ref snapshots span_map.py state structs sub_acluster-D134.out sub_acluster-c494.out sub_acluster-c494b.out sub_acluster-c494c.out sub_acluster1.out t_1FD8.s t_8020.s types-census view-debt.txt work pulses the global opacity, picks the selected or idle update for the cursors row, then draws it. */
typedef struct PakMenuCursor {
    s32 selection;
} PakMenuCursor;
void Menu_DrawMenuModel(PakModelEntry *entry, PakMenuCursor *cursor, void *unused, PakModelContext *context) {
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
        link = pakLoadModel(entry, def->model, def->variant);
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
        draw->update = addrLow_Bound_DrawActorWithRedMenuEffect;
    } else {
        draw->update = addrLow_Bound_DrawActorWithMenuLighting;
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

#include "MENU/OBJECT1C8.H"
#include "MENU/MENU_BOX.H"
extern void *Menu_GetListContext(s8 *member);
extern void Menu_StopMenuPulse(struct Object1C8 *object);
extern void Menu_StartMenuPulse(struct Object1C8 *object);
typedef struct MenuBuildState MenuBuildState;
typedef struct MenuBuildEntry MenuBuildEntry;
/* One row of a menu definition's item table (0x24 bytes). */
typedef struct MenuBuildItem {
    s16 type;
    u16 reserved02;
    u32 flags;
    s16 x, y;
    u8 red, green, blue, alpha;
    s32 resource;
    u8 reserved14[8];
    void (*initialize)(MenuBuildEntry *, MenuBuildState *, MessageList *);
    u8 reserved20[4];
} MenuBuildItem;
/* The definition a menu is built from: its item table and count, an optional setup callback and its
   screen position (unit view of struct Dialog). */
typedef struct MenuBuildDefinition {
    MenuBuildItem *items;
    s16 count;
    u16 reserved06;
    void (*initialize)(MenuBuildState *, MessageList *);
    u8 reserved0C[12];
    s16 x, y, kind;
    u16 reserved1E;
    s32 value;
} MenuBuildDefinition;
/* A live menu entry built from one item (0x28 bytes); `extra` points at its private block. */
struct MenuBuildEntry {
    s32 index;
    s16 type;
    u16 reserved06;
    u32 flags;
    s16 x, y;
    u8 red, green, blue, alpha;
    s32 resource;
    MenuBuildItem *definition;
    s32 selection;
    u8 *extra;
    MenuBuildState *menu;
};
/* The menu block: this header, then `count` entries, then the private blocks of the entries that
   need one. */
struct MenuBuildState {
    s16 x, y, kind;
    u16 reserved06;
    void **allocation;
    MenuBuildEntry *entries;
    s32 count;
    MenuBuildDefinition *definition;
    s32 value18, value1C;
    PakMenuInputStateView *input;
    s32 value24;
    u16 state, ownerSlot;
    s32 value2C, value30, value34, value38, value3C;
    void *context;
    MessageList *owner;
    Vtx_t vertices[2][8];
    u8 reserved148[0x90];
};
/* Private block size of an item: type 3 items own 0x480 bytes (inline copy of Menu_GetMenuItemExtraSize). */
static inline s32 menuItemExtraSize(MenuBuildItem *definition) {
    s32 size = 0;
    if (definition->type == 3) size = 1152;
    return size;
}
/* Fills one entry from its item and hands it the next private block (inline copy of
   Menu_InitMenuItemFromDescriptor). */
static inline void initializeMenuEntry(MenuBuildEntry *entry, MenuBuildItem *definition, s32 index, MenuBuildState *menu, u8 **extra) {
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
    if (menuItemExtraSize(definition) != 0) {
        entry->extra = *extra;
        if (definition->type == 3) ((struct MenuItemVisibilityFlagView *)*extra)->flag = 1;
        *extra += menuItemExtraSize(definition);
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
    menu->x = definition->x;
    menu->y = definition->y;
    menu->kind = definition->kind;
    menu->allocation = allocation;
    menu->entries = (MenuBuildEntry *)(menu + 1);
    menu->count = definition->count;
    extra = (u8 *)(menu + 1);
    extra += definition->count * sizeof(MenuBuildEntry);
    i = 0;
    if (definition->count > 0) {
        do {
            initializeMenuEntry(&menu->entries[i], &definition->items[i], i, menu, &extra);
        } while (++i < definition->count);
    }
    menu->definition = definition;
    menu->value18 = value18;
    menu->value1C = value1C;
    menu->input = input;
    menu->value24 = value24;
    menu->state = 0;
    menu->ownerSlot = owner->rotation;
    menu->value2C = 0;
    menu->value30 = 0;
    menu->value34 = 0;
    menu->value38 = 1;
    menu->value3C = 0;
    menu->context = Menu_GetListContext((s8 *)owner);
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
    Menu_StopMenuPulse((struct Object1C8 *)menu);
    Menu_StartMenuPulse((struct Object1C8 *)menu);
    if (definition->initialize != 0) definition->initialize(menu, owner);
    i = menu->count;
    entry = menu->entries;
    while (--i != -1) {
        if (entry->definition->flags & 0x4000000) {
            if (entry->definition->initialize != 0) entry->definition->initialize(entry, menu, owner);
        }
        entry++;
    }
}
