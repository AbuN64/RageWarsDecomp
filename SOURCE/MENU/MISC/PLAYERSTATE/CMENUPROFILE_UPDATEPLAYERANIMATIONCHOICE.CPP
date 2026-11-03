#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "MENU/PLAYERSETTINGS.H"
#include "TYPES.H"
#include "RENDER/SOUNDELEMENT_PLAYFLATSOUND.H"
#include "MENU/PAK/MENU_CREATEMENUFROMTEMPLATE.H"

#if !(defined(VERSION_DE))
/* Handles the team option of a menu: unless Control_IsAButtonPressed_Character reports the confirm input, it steps the owner's team byte at 0x80 through Menu_StepValue between 1 and 18, applies it with Player_StartPlayerAnimation_CmenuprofileUpdateplayeranimationchoice and redraws it with Menu_SelectPreviewModel, returning zero; on confirm it applies the team, plays the sound g_profilePlayerAnimationChoices gives for the player's slot at 0x5E0 and shows the resource g_characterPreviewMenuRomResource_CmenuprofileUpdateplayeranimationchoice through Menu_AllocateMenu, returning one. */







extern unsigned int Control_IsAButtonPressed(struct ControllerProfile *profile);
extern s32 Menu_StepValue(struct MenuValueStepView *menu, s32 value, s32 step, s32 minimum, s32 maximum, s32 wrap);
extern void Player_StartPlayerAnimation(struct Player *animatedPlayer, s32 animationState);
extern struct PreviewWidget *Menu_SelectPreviewModel(struct MenuPreviewSelectionView *widget,int selection,int kind);


s32 CMenuProfile_UpdatePlayerAnimationChoice(void *previewWidget, MenuCMenuProfileUpdatePlayerAnimationChoice *menu, void *menuContext) {
    SharedPlayer *player = menu->player;
    PlayerCharacterKindView *settings = player->views5D8.view5D8_7.settings;

    if (Control_IsAButtonPressed(menu->input) != 0) {
        Player_StartPlayerAnimation(player, settings->characterKind);
        SoundElement_PlayFlatSound(g_profilePlayerAnimationChoices[player->views5DC.view5E0_10.slot].mode);
        Menu_AllocateMenu(menuContext, menu, g_characterPreviewMenuRomResource);
        return 1;
    }
    settings->characterKind = Menu_StepValue(menu, settings->characterKind, 1, 0, 18, 1);
    Player_StartPlayerAnimation(player, settings->characterKind);
    Menu_SelectPreviewModel(previewWidget, 11, settings->characterKind);
    return 0;
}
#endif
