#include "include_asm.h"
#include "COMMON/MENU_SCREEN_SETUP.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "RENDER/SOUNDELEMENT_PLAYFLATSOUND.H"

/* Opens the screen g_setupScreen: allocates its 0x470-byte state for the window, sets up the list,
   the left and right arrows (shifted by their width and snapped to 4 pixels), the labels and
   items of the window with their alpha and visibility, resets the selection and the counters at
   g_selectionMessageReply.ready, clears the pending flag at 0x91 of the eight g_playerSettings_Achieve records, places the four
   character models (ids 0xEA6 to 0xEA9, x 0, -6, -13, -19) and a fifth model 0xEA6, then issues
   request 0xE78 through SoundElement_PlayFlatSound and calls Menu_InitializeOptionsScene; returns zero. */
#include "TYPES.H"
#include "COMMON/SHAREDPLAYER.H"
#include "UI/TSMOS/SCREENS/SCENARIOSETUPSCREEN.H"

#if defined(VERSION_DE)
#define ID_2FE 762
#define ID_2FF 764
#define ID_300 763
#define ID_301 765
#define ID_303 767
#define ID_306 770
#define ID_308 772
#define ID_309 773
#define ID_30A 775
#define ID_30B 776
#define ID_30C 774
#define ID_30D 777
#define ID_30E 778
#define ID_30F 779
#define ID_310 780
#define ID_35D 857
#elif defined(VERSION_EU_X)
#define ID_2FE 771
#define ID_2FF 772
#define ID_300 568
#define ID_301 773
#define ID_303 775
#define ID_306 778
#define ID_308 780
#define ID_309 781
#define ID_30A 783
#define ID_30B 784
#define ID_30C 782
#define ID_30D 785
#define ID_30E 787
#define ID_30F 786
#define ID_310 788
#define ID_35D 865
#else
#define ID_2FE 766
#define ID_2FF 767
#define ID_300 768
#define ID_301 769
#define ID_303 771
#define ID_306 774
#define ID_308 776
#define ID_309 777
#define ID_30A 778
#define ID_30B 779
#define ID_30C 780
#define ID_30D 781
#define ID_30E 782
#define ID_30F 783
#define ID_310 784
#define ID_35D 861
#endif

s32 CScenarioSetup_OpenScenarioSetupScreen(void *window) {
    SetupModelVector scale;
    SetupModelVector position;
    SetupModelVector rotation;
    SetupModelVector offset;
    MenuWidget *item1, *item2, *item3, *item4, *item5, *item6, *item7, *item8;
    MenuWidget *opacityItem;
    f32 z;
    ListScreenRecord *record;
    s32 i;
    s32 x;
    s32 id;

    g_setupScreen = Cache_AllocateMemory(sizeof(SetupScreen));
    g_setupScreen->window = window;
    g_setupScreen->list = SmpOverlay_CreateOverlayNode(window, 4);
    SmpOverlay_ShowSlotById(window, 0, ID_2FF);
    SmpOverlay_ShowSlotById(window, 1, ID_2FF);
    SmpOverlay_ShowSlotById(window, 2, ID_2FF);
    SmpOverlay_ShowSlotById(window, 3, ID_2FF);
    g_setupScreen->screenState = 1;
    g_setupScreen->pulsePhase = 0;
    g_setupScreen->stateCountdown = 4;

    item1 = Node_FindWidgetByResourceId(window, ID_306);
    g_setupScreen->left = item1;
    item1->x -= item1->width;
    g_setupScreen->leftCount = g_setupScreen->left->width / 4;
    x = g_setupScreen->left->width - g_setupScreen->leftCount * 4;
    g_setupScreen->left->x += x;

    item2 = Node_FindWidgetByResourceId(window, ID_30F);
    g_setupScreen->right = item2;
    item2->x += item2->width;
    g_setupScreen->rightCount = g_setupScreen->right->width / 4;
    x = g_setupScreen->right->width - g_setupScreen->rightCount * 4;
    g_setupScreen->right->x -= x;

    opacityItem = Node_FindWidgetByResourceId(window, ID_30A);
    opacityItem->alpha = 110;
    item3 = Node_FindWidgetByResourceId(window, ID_35D);
    g_setupScreen->widget35D = item3;
    item3->alpha = 65;
    Widget_SetWidgetFlag08(g_setupScreen->widget35D, 0);
    g_setupScreen->text3E4 = SmpFlicker_CreateFlickerWidget(ID_303, 110);
    item4 = Node_FindWidgetByResourceId(window, ID_301);
    g_setupScreen->widget301 = item4;
    Widget_SetWidgetFlag08(item4, 0);
    g_setupScreen->label = Node_FindWidgetByResourceId(window, ID_30E);
    g_setupScreen->widget310 = Node_FindWidgetByResourceId(window, ID_310);
    ScenarioSetup_HideSetupCatalogue();
    g_setupScreen->selection = 0;
    g_setupScreen->category = 0;
    ScenarioSetup_RefreshSelectedArenaLabel();
    ScenarioSetup_LoadSetupArenaLabel();
    g_selectionMessageReply.ready = 0;
    g_selectionMessageReply.value = -1;
    g_setupScreen->widget308 = Node_FindWidgetByResourceId(window, ID_308);
    opacityItem = Node_FindWidgetByResourceId(window, ID_309);
    opacityItem->alpha = 110;
    g_setupScreen->reservedWord3 = 0;
    item5 = Node_FindWidgetByResourceId(window, ID_30B);
    g_setupScreen->widget30B = item5;
    item5->alpha = 140;
    Widget_SetWidgetFlag08(g_setupScreen->widget30B, 1);
    item6 = Node_FindWidgetByResourceId(window, ID_30D);
    g_setupScreen->widget30D = item6;
    item6->alpha = 140;
    Widget_SetWidgetFlag08(g_setupScreen->widget30D, 0);
    item7 = Node_FindWidgetByResourceId(window, ID_30C);
    g_setupScreen->widget30C = item7;
    item7->alpha = 0xFF;
    g_setupScreen->widget2FE = Node_FindWidgetByResourceId(window, ID_2FE);
    item8 = Node_FindWidgetByResourceId(window, ID_300);
    g_setupScreen->widget300 = item8;
    Widget_SetWidgetFlag08(item8, 1);
    Tsmos_DeactivateControllerState();
    g_setupScreen->controllerActivated = 0;
    g_setupScreen->reservedWord1 = 0;
    g_setupScreen->reservedWord2 = -1;

    for (i = 0; i < 8; i++) {
        record = &g_playerSettings[i];
        if (record->m_IsBot == 1) {
            record->active = 0;
            record->m_IsBot = 0;
        }
    }
    Tsmos_SetModeOneFlag(1);

    x = 0;
    id = 0;
    scale.value.x = g_setupFirstPreviewScale;
    scale.value.y = g_setupFirstPreviewScale;
    scale.value.z = g_setupFirstPreviewScale;
    rotation.value.x = 0.0f;
    rotation.value.y = 0.0f;
    rotation.value.z = 0.0f;
    offset.value.x = 0.0f;
    offset.value.y = g_setupFirstPreviewYOffset;
    offset.value.z = 0.0f;
    for (i = 0; i < 4; i++) {
        switch (i) {
        case 0:
            x = 0;
            id = 3750;
            break;
        case 1:
            x = -6;
            id = 3751;
            break;
        case 2:
            x = -13;
            id = 3752;
            break;
        case 3:
            x = -19;
            id = 3753;
            break;
        }
        position.value.x = x;
        position.value.y = g_setupFirstPreviewY;
        z = g_setupPreviewDepth;
        position.value.z = z;
        Frontend_InitModelPreviewTransform(&g_setupScreen->models[i].initial, id, scale.words, position.words);
        Frontend_SetPreviewRotation(&g_setupScreen->models[i].rotation, rotation.words);
        Frontend_SetPreviewRotationSpeed(&g_setupScreen->models[i].offset, offset.words);
    }
    scale.value.x = g_setupSecondPreviewScale;
    scale.value.y = g_setupSecondPreviewScale;
    scale.value.z = g_setupSecondPreviewScale;
    position.value.z = z;
    position.value.x = g_setupSecondPreviewX;
    position.value.y = g_setupSecondPreviewY;
    Frontend_InitModelPreviewTransform(&g_setupScreen->models[4].initial, 3750, scale.words, position.words);
    Frontend_SetPreviewRotation(&g_setupScreen->models[4].rotation, rotation.words);
    Frontend_SetPreviewRotationSpeed(&g_setupScreen->models[4].offset, offset.words);
    SoundElement_PlayFlatSound(3704);
    Menu_InitializeOptionsScene();
    return 0;
}

#if defined(VERSION_DE) || defined(VERSION_EU) || defined(VERSION_EU_X) || defined(VERSION_US_REV1)
const float k_SetupEncodedWords[7] = {
    0.018f, 5.0f, 13.0f, -5.0e+01f, 0.04f, 17.0f,
    -1.0e+01f,
};
#endif
