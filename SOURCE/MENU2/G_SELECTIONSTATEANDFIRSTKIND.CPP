#include "TYPES.H"
#if defined(VERSION_DE)
/* 800E4200_2.CPP */
/* Selection state pointer followed by the first layout row's word-sized kind. */
struct {
    void * screen;
    s32 firstKind;
} g_selectionStateAndFirstKind __attribute__((aligned(4))) = {
    0,
    144
};
typedef char g_selectionStateAndFirstKindSizeCheck[(sizeof(g_selectionStateAndFirstKind) == 8) ? 1 : -1];
/* 800E0288.CPP */
extern char addrLow_Character_CreateSelectionMenuGerman[];
extern char g_character_UpdateCharacterPreviewEntry[];
extern char g_menu_RenderPlayerCharacterPreviewsEntry[];
extern char g_selection_DestroyCharacterSelectionMenuEntry[];
extern char g_selection_ActivateCharacterSelectionModeEntry[];
extern char g_selection_HandleCharacterVariantCycleEntry[];
extern char g_selection_ReturnCharacterEventZeroAEntry[];
extern char g_selection_ReturnCharacterEventZeroBEntry[];
extern char g_selection_ReturnCharacterEventZeroCEntry[];
extern char g_selection_ReturnCharacterEventZeroDEntry[];
extern char g_selection_CancelCharacterConfirmationEntry[];
extern char g_selection_ReadSelectionSlotEntry[];
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
        0x00000E06, 0x00000007, (unsigned int)addrLow_Character_CreateSelectionMenuGerman,
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
