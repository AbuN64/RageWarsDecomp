
#if defined(VERSION_EU_X)
extern char g_Selection_CharacterSelectionEvent0E06HandlerPackedAddress24[];
extern char g_Character_UpdateCharacterPreviewPackedAddress24[];
extern char g_Menu_RenderPlayerCharacterPreviewsPackedAddress24[];
extern char g_Selection_DestroyCharacterSelectionMenuPackedAddress24[];
extern char g_Selection_ActivateCharacterSelectionModePackedAddress24[];
extern char g_Selection_HandleCharacterVariantCyclePackedAddress24[];
extern char g_Selection_ReturnCharacterEventZeroAPackedAddress24[];
extern char g_Selection_ReturnCharacterEventZeroBPackedAddress24[];
extern char g_Selection_ReturnCharacterEventZeroCPackedAddress24[];
extern char g_Selection_ReturnCharacterEventZeroDPackedAddress24[];
extern char g_Selection_CancelCharacterConfirmationPackedAddress24[];
extern char g_Selection_ReadSelectionSlotPackedAddress24[];
/* Widget IDs occupy the second halfword; kind and event fields remain words. */
struct {
    unsigned short firstRowWidgets[8][2];
    struct {
        unsigned int kind;
        unsigned short widgets[8][2];
    } rows[3];
    unsigned int events[39];
} g_menuKindSevenWidgetAndEventDefinitionsEuX = {
    { { 0, 0x0083 }, { 0, 0x00CA }, { 0, 0x00B1 }, { 0, 0x00B3 }, { 0, 0x00B5 }, { 0, 0x00C8 }, { 0, 0x00C7 }, { 0, 0x00C6 } },
    {
        { 0x0000008A, { { 0, 0x0082 }, { 0, 0x00AD }, { 0, 0x0098 }, { 0, 0x009A }, { 0, 0x009C }, { 0, 0x00AC }, { 0, 0x00AB }, { 0, 0x00AA } } },
        { 0x00000091, { { 0, 0x0080 }, { 0, 0x00CB }, { 0, 0x00B7 }, { 0, 0x00B9 }, { 0, 0x00BB }, { 0, 0x00BD }, { 0, 0x00BE }, { 0, 0x00BF } } },
        { 0x00000090, { { 0, 0x0081 }, { 0, 0x00AE }, { 0, 0x00A0 }, { 0, 0x009F }, { 0, 0x009E }, { 0, 0x00A2 }, { 0, 0x00A3 }, { 0, 0x00A1 } } },
    },
    {
        0x00000E07, 0x00000007, (unsigned int)g_Selection_ActivateCharacterSelectionModePackedAddress24,
        0x00000E08, 0x00000007, (unsigned int)g_Character_UpdateCharacterPreviewPackedAddress24,
        0x0000000A, 0x00000007, (unsigned int)g_Selection_HandleCharacterVariantCyclePackedAddress24,
        0x00000E0A, 0x00000007, (unsigned int)g_Menu_RenderPlayerCharacterPreviewsPackedAddress24,
        0x00000E06, 0x00000007, (unsigned int)g_Selection_CharacterSelectionEvent0E06HandlerPackedAddress24,
        0x00000E03, 0x00000007, (unsigned int)g_Selection_DestroyCharacterSelectionMenuPackedAddress24,
        0x00000002, 0x00000007, (unsigned int)g_Selection_CancelCharacterConfirmationPackedAddress24,
        0x00000001, 0x00000007, (unsigned int)g_Selection_ReadSelectionSlotPackedAddress24,
        0x00000008, 0x00000007, (unsigned int)g_Selection_ReturnCharacterEventZeroAPackedAddress24,
        0x00000007, 0x00000007, (unsigned int)g_Selection_ReturnCharacterEventZeroBPackedAddress24,
        0x00000005, 0x00000007, (unsigned int)g_Selection_ReturnCharacterEventZeroCPackedAddress24,
        0x00000006, 0x00000007, (unsigned int)g_Selection_ReturnCharacterEventZeroDPackedAddress24,
        0x00000000, 0x00000000, 0x00000000,
    },
};
#endif
