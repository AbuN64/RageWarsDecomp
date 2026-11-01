#include "COMMON/RESIDENT_EVENT_HANDLER.H"


#if defined(VERSION_US_REV1)
/* Widget IDs occupy the second halfword; kind and event fields remain words. */
struct {
    unsigned short firstRowWidgets[8][2];
    struct {
        unsigned int kind;
        unsigned short widgets[8][2];
    } rows[3];
} g_selectionLayoutTailUsRevOne = {
    { { 0, 0x007F }, { 0, 0x00C6 }, { 0, 0x00AD }, { 0, 0x00AF }, { 0, 0x00B1 }, { 0, 0x00C4 }, { 0, 0x00C3 }, { 0, 0x00C2 } },
    {
        { 0x00000086, { { 0, 0x007E }, { 0, 0x00A9 }, { 0, 0x0094 }, { 0, 0x0096 }, { 0, 0x0098 }, { 0, 0x00A8 }, { 0, 0x00A7 }, { 0, 0x00A6 } } },
        { 0x0000008D, { { 0, 0x007C }, { 0, 0x00C7 }, { 0, 0x00B3 }, { 0, 0x00B5 }, { 0, 0x00B7 }, { 0, 0x00B9 }, { 0, 0x00BA }, { 0, 0x00BB } } },
        { 0x0000008C, { { 0, 0x007D }, { 0, 0x00AA }, { 0, 0x009C }, { 0, 0x009B }, { 0, 0x009A }, { 0, 0x009E }, { 0, 0x009F }, { 0, 0x009D } } },
    },
};

extern char g_cCharacterSelection_OpenCharacterSelectionScreenEntry[];
extern char g_character_UpdateCharacterPreviewEntry[];
extern char g_menu_RenderPlayerCharacterPreviewsEntry[];
extern char g_selection_DestroyCharacterSelectionMenuEntry_GSelectionlayouttailusrevone[];
extern char g_selection_ActivateCharacterSelectionModeEntry[];
extern char g_selection_HandleCharacterVariantCycleEntry[];
extern char g_selection_ReturnCharacterEventZeroAEntry[];
extern char g_selection_ReturnCharacterEventZeroBEntry[];
extern char g_selection_ReturnCharacterEventZeroCEntry[];
extern char g_selection_ReturnCharacterEventZeroDEntry[];
extern char g_selection_CancelCharacterConfirmationEntry[];
extern char g_selection_ReadSelectionSlotEntry[];
#if defined(VERSION_US_REV1)
ResidentEventHandlerEntry g_eventHandlers_us_rev1[13] = {
    { 3591, 7, (ResidentEventHandler)(void *)&g_selection_ActivateCharacterSelectionModeEntry }, { 3592, 7, (ResidentEventHandler)(void *)&g_character_UpdateCharacterPreviewEntry }, { 10, 7, (ResidentEventHandler)(void *)&g_selection_HandleCharacterVariantCycleEntry }, { 3594, 7, (ResidentEventHandler)(void *)&g_menu_RenderPlayerCharacterPreviewsEntry }, { 3590, 7, (ResidentEventHandler)(void *)&g_cCharacterSelection_OpenCharacterSelectionScreenEntry }, { 3587, 7, (ResidentEventHandler)(void *)&g_selection_DestroyCharacterSelectionMenuEntry_GSelectionlayouttailusrevone }, { 2, 7, (ResidentEventHandler)(void *)&g_selection_CancelCharacterConfirmationEntry }, { 1, 7, (ResidentEventHandler)(void *)&g_selection_ReadSelectionSlotEntry },
    { 8, 7, (ResidentEventHandler)(void *)&g_selection_ReturnCharacterEventZeroAEntry }, { 7, 7, (ResidentEventHandler)(void *)&g_selection_ReturnCharacterEventZeroBEntry }, { 5, 7, (ResidentEventHandler)(void *)&g_selection_ReturnCharacterEventZeroCEntry }, { 6, 7, (ResidentEventHandler)(void *)&g_selection_ReturnCharacterEventZeroDEntry }, { 0, 0, (ResidentEventHandler)0 }
};
#endif
#endif
