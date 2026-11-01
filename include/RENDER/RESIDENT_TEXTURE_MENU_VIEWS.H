#ifndef RENDER_RESIDENT_TEXTURE_MENU_VIEWS_H
#define RENDER_RESIDENT_TEXTURE_MENU_VIEWS_H
#include "COMMON/OBJRECAT26DD8.H"
#include "RENDER/SEQUENCE_PROMPT_STATE_VIEWS.H"
#include "COMMON/RESIDENTSTATE.H"

extern s32 Simppool_CheckSequencePromptRequest(SequencePromptRequestView *request);

struct ResidentSlot {
    s32 overridesDisabled;
    char pad4[0x21A0 - 0x4];
    s32 reservedWord;
};
struct ResidentEntry {
    s32 resource;
    char pad4[0x2010 - 0x4];
    s32 palette;
};
struct SelectionTextLoadApplyArtsendTextureOverride {
    s32 value;
    char pad4[12];
    s32 alternative; /* 0x10 */
};
/* Frontend action mapping selected by g_artsendActionMappingSelection. */
typedef struct FrontendInputSelector {
    u8 mode;
    u8 reserved1;
    u8 primaryButton;
    u8 secondaryButton;
} FrontendInputSelector;
struct CacheResourceNode;
/* The us-rev1 resident texture menu state (g_artsendTextureViewer, 0x21BC bytes): TextLoad_ResetArtsendTextureState clears it,
   Tengine_LoadSelectedTexture loads the selected entry and Tengine_UpdateArtsendTexturePreview steps the selection. */
struct ArtsendTextureMenuState {
    u8 alternateTitle; /* +0x0 */
    u8 state; /* +0x1 */
    u8 unused0[2];
    s32 reservedWord;
    s32 active; /* +0x8: item count, the selection modulus */
    s32 selectionIndex; /* +0xC */
    s32 selectionValue; /* +0x10 */
    s32 titleWasShown; /* +0x14: set when the selection changed */
    s32 overridesOff; /* +0x18: no texture or palette override while set */
    struct CacheResourceNode *resource; /* +0x1C: the loaded entry */
    FrontendInputSelector *selector; /* +0x20 */
    s32 *textureOverride; /* +0x24 */
    s32 *paletteOverride; /* +0x28 */
    s32 textureData[8192 / 4]; /* +0x2C */
    s32 paletteData[256 / 4]; /* +0x202C */
    s32 *entryTable; /* +0x212C */
    s32 *textureTable; /* +0x2130 */
    s32 *paletteTable; /* +0x2134 */
    char displayData[128]; /* +0x2138 */
    s32 frameCount; /* +0x21B8 */
};
extern struct ArtsendTextureMenuState g_artsendTextureViewer;
struct ArtsendTextureSelection {
    s32 index; /* +0x0: == g_artsendTextureSelectionIndex */
    s32 value; /* +0x4 */
    s32 changed; /* +0x8: == g_artsendTextureSelectionChanged */
};
extern void Simppool_ResetEffectsAndControllers(void);
#endif
