#include "COMMON/AIPROFILE.H"
#include "COMMON/SHARED_GAMESLOT.H"
#include "COMMON/EFFECTRENDER.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "TYPES.H"
#include "COMMON/RG.H"
#if defined(VERSION_DE)
typedef struct { char pad0[0x1C]; Player *rec; struct ControllerProfile *player; } CharacterPreviewMenuContext;
extern s16 g_characterPreviewStyleSounds[][2];
extern u8 g_characterPreviewLeftChoices[][4];
extern u8 g_characterPreviewRightChoices[][4];
extern unsigned int Control_IsAButtonPressed(struct ControllerProfile *profile);
extern void Player_StartPlayerAnimation(struct Player *animatedPlayer, s32 animationState);
extern s32 SoundElement_PlayFlatSound(s32 id);
extern void *Menu_AllocateMenu(struct MenuCreationOwnerView *owner, struct ParamsPakAllocateMenu *params, struct Dialog *list);
extern s32 Menu_StepValue(struct MenuValueStepView *menu, s32 value, s32 step, s32 minimum, s32 maximum, s32 wrap);
extern struct PreviewWidget *Menu_SelectPreviewModel(struct MenuPreviewSelectionView *widget,int selection,int kind);
/* Steps the choice byte at 0x80 of the slot the record at 0x1C of menuContext points to: while the player passes Control_IsAButtonPressed_Character it plays the sound for the record's style and runs the resource g_characterPreviewMenuRomResource; otherwise Menu_StepValue moves the choice and the remapping tables g_characterPreviewLeftChoices (Control_IsLeftPressed) and g_characterPreviewRightChoices (Control_IsRightPressed or Control_IsAButtonPressed_Character) are applied before the display is refreshed; returns 1 or 0. */
s32 Items_HandleCharacterPreviewSelectionGerman(s32 widget, CharacterPreviewMenuContext *menuContext, s32 owner) {
    Player *rec = menuContext->rec;
    AiProfile *slot = rec->profile;
    if (Control_IsAButtonPressed(menuContext->player) != 0) {
        Player_StartPlayerAnimation(rec, slot->character);
        SoundElement_PlayFlatSound(g_characterPreviewStyleSounds[rec->state][0]);
        Menu_AllocateMenu(owner, menuContext, g_characterPreviewMenuRomResource);
        return 1;
    }
    slot->character = Menu_StepValue(menuContext, slot->character, 1, 0, 18, 1);
    if (Control_IsLeftPressed(menuContext->player) != 0) {
        slot->character = g_characterPreviewLeftChoices[slot->character][0];
    }
    if (Control_IsRightPressed(menuContext->player) != 0 || Control_IsAButtonPressed(menuContext->player) != 0) {
        slot->character = g_characterPreviewRightChoices[slot->character][0];
    }
    Player_StartPlayerAnimation(rec, slot->character);
    Menu_SelectPreviewModel(widget, 11, slot->character);
    return 0;
}
#endif
#if defined(VERSION_DE) || defined(VERSION_US)
#if defined(VERSION_DE)
s32 Items_SelectToggleRowTextGerman(TextBoundsText *textRow) {
    s32 toggleRow;

    toggleRow = textRow->value;
    switch (toggleRow) {
    case 2:
    default:
        if (g_gameSettings.menuToggles[0] != 0) {
            textRow->text = &g_menuToggleRow2EnabledText;
        } else {
            textRow->text = &g_menuToggleRow2DisabledText;
        }
        break;
    case 3:
        if (g_gameSettings.menuToggles[1] != 0) {
            textRow->text = &g_menuToggleRow3EnabledText;
        } else {
            textRow->text = &g_menuToggleRow3DisabledText;
        }
        break;
    case 4:
        if (g_gameSettings.menuToggles[2] != 0) {
            textRow->text = &g_menuToggleRow4EnabledText;
        } else {
            textRow->text = &g_menuToggleRow4DisabledText;
        }
        break;
    case 5:
        if (g_gameSettings.menuToggles[3] != 0) {
            textRow->text = &g_menuToggleRow5EnabledText;
        } else {
            textRow->text = &g_menuToggleRow5DisabledText;
        }
        break;
    case 6:
        if (g_gameSettings.menuToggles[4] != 0) {
            textRow->text = &g_menuToggleRow6EnabledText;
        } else {
            textRow->text = &g_menuToggleRow6DisabledText;
        }
        break;
    case 7:
        if (g_gameSettings.menuToggles[5] != 0) {
            textRow->text = &g_menuToggleRow7EnabledText;
        } else {
            textRow->text = &g_menuToggleRow7DisabledText;
        }
        break;
    case 8:
        if (g_gameSettings.menuToggles[6] != 0) {
            textRow->text = &g_menuToggleRow8EnabledText;
        } else {
            textRow->text = &g_menuToggleRow8DisabledText;
        }
        break;
    case 9:
        if (g_gameSettings.menuToggles[8] != 0) {
            textRow->text = &g_menuToggleRow9EnabledText;
        } else {
            textRow->text = &g_menuToggleRow9DisabledText;
        }
        break;
    }
    return 0;
}
#endif
#endif
