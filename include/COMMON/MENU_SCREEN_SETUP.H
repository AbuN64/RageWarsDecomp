#ifndef COMMON_MENU_SCREEN_SETUP_H
#define COMMON_MENU_SCREEN_SETUP_H
#include "TYPES.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/OBJECTRECAT28.H"
#include "COMMON/SELECTIONSCREENSTATE.H"
#include "COMMON/SHARED_MENUREPLY.H"
/* Native model calls copy three 32-bit words by value. The float view
 * preserves the actual coordinate bits through that owning word contract. */
typedef union SetupModelVector { CVector3 value; Triple words; } SetupModelVector;
/* Five retained model records start at +8, with native stride 0xC0. */
typedef union SetupScreenModel {
    StateFrontendInitModelPreviewTransform initial;
    struct PreviewRotationView rotation;
    struct ModelPreviewRotationSpeedView offset;
    u8 record[192];
} SetupScreenModel;
typedef struct SetupScreen {
    void *window;
    s32 reservedWord;
    SetupScreenModel models[5];
    void *list;
    MenuWidget *left;
    s32 leftCount;
    MenuWidget *right;
    s32 rightCount;
    s32 screenState;
    s32 stateCountdown;
    void *text3E4;
    MenuWidget *widget301;
    MenuWidget *label;
    MenuWidget *widget310;
    char text[64];
    s32 category;
    s32 selection;
    MenuWidget *item;
    MenuWidget *widget30B;
    MenuWidget *widget30D;
    MenuWidget *widget35D;
    MenuWidget *widget30C;
    MenuWidget *widget2FE;
    MenuWidget *widget308;
    MenuWidget *widget300;
    s32 pulsePhase;
    s32 controllerActivated;
    s32 reservedWord1;
    s32 reservedWord2;
    s32 reservedWord3;
} SetupScreen;
extern SetupScreen *g_setupScreen;
/* The prior selection and pending-state words are one real two-word array. */
/* Actual loads in the US-rev1 constructor; not guessed constants. */
extern f32 g_setupFirstPreviewScale, g_setupFirstPreviewYOffset, g_setupFirstPreviewY, g_setupPreviewDepth;
extern f32 g_setupSecondPreviewScale, g_setupSecondPreviewX, g_setupSecondPreviewY;
extern s32 Frontend_InitModelPreviewTransform(StateFrontendInitModelPreviewTransform *, s32, Triple, Triple);
extern void Frontend_SetPreviewRotation(struct PreviewRotationView *, Triple);
extern void Frontend_SetPreviewRotationSpeed(struct ModelPreviewRotationSpeedView *, Triple);
#endif
