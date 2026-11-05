#include "Data/rest_source_records.h"
#include "include_asm.h"
#include "Frontend/join_player_names.h"
#include "Common/triple.h"
#include "Menu2/character_preview_definitions_symbols.h"
#include "Menu/menu_event_handlers.h"
#include "types.h"
#include "Menu2/g_selectionstateandfirstkind_symbols.h"

#if !(defined(VERSION_US_REV1))
#if defined(VERSION_DE)
const unsigned char g_characterPreviewVerticalOffset[3] = {
    0x42, 0x20, 0x00,
};
#endif
#endif

#if defined(VERSION_DE)
CharacterPreviewDefinitionsDataLayout g_characterPreviewDefinitionsData = {
    { -6e+01f, -1e+02f, -4e+01f, -6e+01f, -1e+02f, 29.0f, -95.0f, -7e+01f, -29.0f, -95.0f, -7e+01f, 0.0f, 0.0f },
    { { { -20, -20 }, (void *)&g_characterNames[1], { 132, 1, 22 }, { 0.11f, 0.11f, 0.11f, 0.11f, 1.6e+02f, 2e+02f, 1.6e+02f, 2.1e+02f, 41.0f, -37.0f, -1e+02f, -38.0f, -37.0f, -1e+02f, 34.0f, -74.0f, -8e+01f, -3e+01f, -74.0f, -8e+01f, 0.0f, 0.0f } }, { { -15, -15 }, (void *)&g_characterNames[2], { 143, 2, 29 }, { 0.14f, 0.14f, 0.14f, 0.14f, 1.6e+02f, 195.0f, 1.6e+02f, 195.0f, 4e+01f, -53.0f, -1e+02f, -4e+01f, -53.0f, -1e+02f, 32.0f, -91.0f, -8e+01f, -35.0f, -91.0f, -8e+01f, 0.0f, 0.0f } } },
    { -15, -15 },
    (void *)&g_characterNames[3],
    { 130, 3, 26 },
    { 0.065f, 0.065f, 0.065f, 0.065f, 1.6e+02f, 2e+02f, 1.6e+02f, 2e+02f, 39.0f, -35.0f, -1e+02f, -39.0f, -35.0f, -1e+02f, 32.0f, -72.0f, -8e+01f, -32.0f, -72.0f, -8e+01f },
    { 20, 20, 0, 0 },
    { { (void *)&g_characterNames[4], { 133, 4, 20 }, { 0.055f, 0.055f, 0.055f, 0.055f, 155.0f, 2e+02f, 1.6e+02f, 2e+02f, 4e+01f, -35.0f, -1e+02f, -4e+01f, -35.0f, -1e+02f, 3e+01f, -72.0f, -8e+01f, -33.0f, -72.0f, -8e+01f, 0.0f, 0.0f }, { -15, -15 } }, { (void *)&g_characterNames[5], { 138, 5, 32 }, { 0.15f, 0.15f, 0.15f, 0.15f, 1.6e+02f, 2e+02f, 1.6e+02f, 2e+02f, 4e+01f, -6e+01f, -1e+02f, -4e+01f, -6e+01f, -1e+02f, 29.0f, -95.0f, -7e+01f, -29.0f, -95.0f, -7e+01f, 0.0f, 0.0f }, { -20, -20 } }, { (void *)&g_characterNames[6], { 140, 6, 23 }, { 0.08f, 0.08f, 0.08f, 0.08f, 1.6e+02f, 2e+02f, 1.6e+02f, 2e+02f, 42.0f, -45.0f, -1e+02f, -38.0f, -45.0f, -1e+02f, 38.0f, -81.0f, -88.0f, -33.0f, -81.0f, -88.0f, 0.0f, 0.0f }, { -15, -15 } }, { (void *)&g_characterNames[7], { 139, 7, 27 }, { 0.065f, 0.065f, 0.065f, 0.065f, 1.6e+02f, 2e+02f, 1.6e+02f, 2e+02f, 4e+01f, -36.0f, -1e+02f, -4e+01f, -36.0f, -1e+02f, 33.0f, -71.0f, -8e+01f, -33.0f, -71.0f, -8e+01f, 0.0f, 0.0f }, { -15, -15 } }, { (void *)&g_characterNames[8], { 135, 8, 25 }, { 0.13f, 0.13f, 0.13f, 0.13f, 1.6e+02f, 2e+02f, 1.6e+02f, 2e+02f, 39.0f, -58.0f, -1e+02f, -41.0f, -58.0f, -1e+02f, 32.0f, -95.0f, -8e+01f, -34.0f, -95.0f, -8e+01f, 0.0f, 0.0f }, { -15, -15 } }, { (void *)&g_characterNames[9], { 128, 9, 24 }, { 0.06f, 0.06f, 0.06f, 0.06f, 1.6e+02f, 205.0f, 1.6e+02f, 205.0f, 39.0f, -2e+01f, -1e+02f, -41.0f, -2e+01f, -1e+02f, 31.0f, -55.0f, -8e+01f, -33.0f, -55.0f, -8e+01f, 0.0f, 0.0f }, { -15, -15 } }, { (void *)&g_characterNames[10], { 142, 10, 28 }, { 0.13f, 0.13f, 0.13f, 0.13f, 2e+02f, 245.0f, 2e+02f, 245.0f, 4e+01f, -6e+01f, -1e+02f, -4e+01f, -6e+01f, -1e+02f, 43.0f, -95.0f, -8e+01f, -21.0f, -95.0f, -8e+01f, 0.0f, 0.0f }, { -10, -10 } }, { (void *)&g_characterNames[11], { 134, 11, 33 }, { 0.21f, 0.21f, 0.21f, 0.21f, 1.6e+02f, 2e+02f, 1.6e+02f, 2e+02f, 42.0f, -62.0f, -1e+02f, -41.0f, -62.0f, -1e+02f, 36.0f, -103.0f, -8e+01f, -36.0f, -103.0f, -8e+01f, 0.0f, 0.0f }, { -15, -15 } }, { (void *)&g_characterNames[0x30], { 136, 12, 34 }, { 0.19f, 0.19f, 0.19f, 0.19f, 2.2e+02f, 2.6e+02f, 2.2e+02f, 2.6e+02f, 45.0f, -58.0f, -1e+02f, -34.0f, -6e+01f, -1e+02f, 53.0f, -97.0f, -8e+01f, -13.0f, -97.0f, -8e+01f, 0.0f, 0.0f }, { -10, -10 } }, { (void *)&g_characterNames[0x34], { 141, 13, 31 }, { 0.14f, 0.14f, 0.14f, 0.14f, 2.2e+02f, 2.7e+02f, 2.2e+02f, 275.0f, 48.0f, -55.0f, -1e+02f, -33.0f, -58.0f, -1e+02f, 54.0f, -92.0f, -8e+01f, -11.0f, -91.0f, -8e+01f, 0.0f, 0.0f }, { -10, -10 } }, { (void *)&g_characterNames[0x38], { 126, 14, 21 }, { 0.14f, 0.14f, 0.14f, 0.14f, 1.6e+02f, 2e+02f, 1.6e+02f, 2e+02f, 4e+01f, -58.0f, -1e+02f, -41.0f, -58.0f, -1e+02f, 32.0f, -96.0f, -8e+01f, -33.0f, -96.0f, -8e+01f, 0.0f, 0.0f }, { -15, -15 } }, { (void *)&g_characterNames[0x3C], { 137, 17, 30 }, { 0.085f, 0.085f, 0.085f, 0.085f, 143.0f, 215.0f, 143.0f, 215.0f, 45.0f, -36.0f, -1e+02f, -56.0f, -34.0f, -1e+02f, 37.0f, -71.0f, -9e+01f, -48.0f, -71.0f, -9e+01f, 0.0f, 0.0f }, { -15, -15 } }, { (void *)&g_characterNames[0x40], { 131, 18, 36 }, { 0.09f, 0.09f, 0.09f, 0.09f, 1.7e+02f, 2.1e+02f, 1.7e+02f, 2.1e+02f, 4e+01f, 2.0f, -1e+02f, -4e+01f, 2.0f, -1e+02f, 32.0f, -33.0f, -8e+01f, -31.0f, -33.0f, -8e+01f, 0.0f, 0.0f }, { -15, -15 } } },
    (void *)&g_characterNames[0x44],
    { 18, 15, 52, 94, 232, 15, 267, 94, 18, 128, 52, 206, 232, 128, 267, 206, 107, 108, 109, 110, 102, 112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130, 131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144, 111, 146, 147, 148, 106, 104, 105, 103, 150, 151, 149, 145, 125, 196 }
};
#endif

#if defined(VERSION_DE)
/* Selection state pointer followed by the first layout row's word-sized kind. */
struct {
    void * screen;
    s32 firstKind;
} g_selectionScreenAndInitialKind __attribute__((aligned(4))) = {
    0,
    144
};
typedef char g_selectionScreenAndInitialKindSizeCheck[(sizeof(g_selectionScreenAndInitialKind) == 8) ? 1 : -1];
/* Widget IDs occupy the second halfword; kind and event fields remain words. */
struct {
    unsigned short firstRowWidgets[8][2];
    struct {
        unsigned int kind;
        unsigned short widgets[8][2];
    } rows[3];
    unsigned int events[39];
} g_characterSelectionMenuLayout_de = {
    { { 0, 0x007D }, { 0, 0x00C4 }, { 0, 0x00AB }, { 0, 0x00AD }, { 0, 0x00AF }, { 0, 0x00C2 }, { 0, 0x00C1 }, { 0, 0x00C0 } },
    {
        { 0x00000084, { { 0, 0x007C }, { 0, 0x00A7 }, { 0, 0x0092 }, { 0, 0x0094 }, { 0, 0x0096 }, { 0, 0x00A6 }, { 0, 0x00A5 }, { 0, 0x00A4 } } },
        { 0x0000008B, { { 0, 0x007A }, { 0, 0x00C5 }, { 0, 0x00B1 }, { 0, 0x00B3 }, { 0, 0x00B5 }, { 0, 0x00B7 }, { 0, 0x00B8 }, { 0, 0x00B9 } } },
        { 0x0000008A, { { 0, 0x007B }, { 0, 0x00A8 }, { 0, 0x009A }, { 0, 0x0099 }, { 0, 0x0098 }, { 0, 0x009C }, { 0, 0x009D }, { 0, 0x009B } } },
    },
    {
        0x00000E07, 0x00000007, (unsigned int)g_selection_ActivateCharacterSelectionModeEntry,
        0x00000E08, 0x00000007, (unsigned int)g_character_UpdateCharacterPreviewEntry,
        0x0000000A, 0x00000007, (unsigned int)g_selection_HandleCharacterVariantCycleEntry,
        0x00000E0A, 0x00000007, (unsigned int)g_menu_RenderPlayerCharacterPreviewsEntry,
        0x00000E06, 0x00000007, (unsigned int)Character_CreateSelectionMenuGerman,
        0x00000E03, 0x00000007, (unsigned int)g_selection_DestroyCharacterSelectionMenuEntry,
        0x00000002, 0x00000007, (unsigned int)g_selection_CancelCharacterConfirmationEntry,
        0x00000001, 0x00000007, (unsigned int)g_selection_ReadSelectionSlotEntry,
        0x00000008, 0x00000007, (unsigned int)g_selection_ReturnCharacterEventZeroAEntry,
        0x00000007, 0x00000007, (unsigned int)g_selection_ReturnCharacterEventZeroBEntry,
        0x00000005, 0x00000007, (unsigned int)g_selection_ReturnCharacterEventZeroCEntry,
        0x00000006, 0x00000007, (unsigned int)g_selection_ReturnCharacterEventZeroDEntry,
        0x00000000, 0x00000000, 0x00000000,
    },
};
#endif
