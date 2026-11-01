#include "COMMON/ITEMRECAT20V1.H"
#include "FRONTEND/PAKMENU.H"
#include "COMMON/NAME.H"
#include "COMMON/ENTRYRECAT6C.H"
#include "TYPES.H"
#include "FRONTEND/PAKINTERFACE_UPDATEPLAYERPANELANIMATIONS.H"
#include "UI/TSMOS/SCREENS/PAKINTERFACESCREEN.H"

/* Steps each channel's fade timer and writes the level its curve currently reaches. */



extern void *SmpOverlay_GetSlotValue(s32, s32);
extern void PAKInterface_IncrementNameCharacter(s32);
extern void PAKInterface_DecrementNameCharacter(s32);


void PAKInterface_UpdatePlayerPanelAnimations(s32 phaseStep) {
    f32 bobValue;
    s32 nextCharacterAnimationFrame;
    s32 nextRosterAnimationFrame;
    s32 panelState;
    s32 characterAnimationState;
    s32 selectedLabelOffset;
    ResourceSmpFlickerCreateFlickerWidget *animatedLabel;
    s32 player;
    Blk *playerPanel;
    Blk *characterPanel;
    Blk *panelPhaseStorage;
    Blk *selectedPhaseStorage;
    Blk *idlePhaseStorage;

    player = 0;
    do {
        playerPanel = (Blk *)((char *)g_pakProfileScreenState + (player * sizeof(PakProfilePanelState)));
        panelState = playerPanel->panelState;
        switch (panelState) {
        case 0:
            PAKInterface_PulseIdlePanelLabels(player);
            break;
        case 12:
            animatedLabel = SmpOverlay_GetSlotValue(g_pakProfileScreenState->root, player);
            selectedPhaseStorage = (Blk *)((char *)g_pakProfileScreenState + (player * 4));
            bobValue = (Math_Cosf((f32)player + ((f32)selectedPhaseStorage->animationClock * 0.005f)) * 100.0f) + 150.0f;
            animatedLabel->value = bobValue;
            characterPanel = (Blk *)((char *)g_pakProfileScreenState + (player * sizeof(PakProfilePanelState)));
            characterAnimationState = characterPanel->nameEntryPhase;
            switch (characterAnimationState) {
            case 0:
                nextCharacterAnimationFrame = characterPanel->nameEntryTimer + 1;
                characterPanel->nameEntryTimer = nextCharacterAnimationFrame;
                if (nextCharacterAnimationFrame >= 6) {
                    PAKInterface_DecrementNameCharacter(player);
                }
                break;
            case 1:
                nextRosterAnimationFrame = characterPanel->nameEntryTimer + 1;
                characterPanel->nameEntryTimer = nextRosterAnimationFrame;
                if (nextRosterAnimationFrame >= 6) {
                    PAKInterface_IncrementNameCharacter(player);
                }
                break;
            case 2:
                break;
            }
            break;
        case 4:
            selectedLabelOffset = ((playerPanel->selectedNote - playerPanel->noteScrollOffset) * 4) + (player * 2920);
            animatedLabel = ((Blk *)((char *)g_pakProfileScreenState + selectedLabelOffset))->noteLabel;
            idlePhaseStorage = (Blk *)((char *)g_pakProfileScreenState + (player * 4));
            bobValue = (Math_Cosf((f32)player + ((f32)idlePhaseStorage->animationClock * 0.005f)) * 100.0f) + 150.0f;
            animatedLabel->value = bobValue;
            break;
        }
        panelPhaseStorage = (Blk *)((char *)g_pakProfileScreenState + (player * 4));
        panelPhaseStorage->animationClock = panelPhaseStorage->animationClock + phaseStep;
        player += 1;
    } while (player < 4);
}
