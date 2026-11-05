#ifndef MULTI_ADDRESS_SYMBOLS_H
#define MULTI_ADDRESS_SYMBOLS_H
#include "Frontend/frontend.h"
#include "Common/ballisticparams.h"
#include "Common/sessionhandlerrow.h"
#include "Common/runtime_declarations.h"
#include "Common/triple.h"
#include "Frontend/frontend_address_symbols.h"
/* Symbols that exist only at a fixed ROM address; each is referenced through its address. */
extern char g_playerSettingsSlotNumberFormat[];
extern char g_playerViewRenderContextPlayerNames_de[];
extern char g_tlbMissExceptionVector[];
extern struct List g_controllerPakEnabledDialogResource;
extern char g_menuResidentRegionStart;
extern char Player_FreeAlternatePlayerSettingsScreen_Address[];
extern char Frontend_HandleProfileResetConfirm_Address[];
extern char addrLow_Frontend_FreeEquipmentScreen[];
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
extern char Menu_OpenRuleToggleScreen_Address[];
extern char Menu_DestroyExtraOptionsMenu_Address[];
extern char Menu_UpdateExtraOptionsMenu_Address[];
extern u8 *g_defaultPlayerNames[4];
extern char g_multiNameCursorTextLocalized[];
#endif
