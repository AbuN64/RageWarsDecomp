#ifndef COMMON_MENU_SCREEN_SETUP_H
#define COMMON_MENU_SCREEN_SETUP_H
#include "Common/model_preview_transform.h"
#include "Frontend/frontend.h"
#include "types.h"
#include "Common/sharedplayer.h"
#include "Common/menu_model_preview.h"
#include "Common/selectionscreenstate.h"
#include "Common/shared_menureply.h"
struct SetupScreen;
struct MenuWidget;
struct StateFrontendInitModelPreviewTransform;
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
    struct MenuWidget *left;
    s32 leftCount;
    struct MenuWidget *right;
    s32 rightCount;
    s32 screenState;
    s32 stateCountdown;
    void *text3E4;
    struct MenuWidget *widget301;
    struct MenuWidget *label;
    struct MenuWidget *widget310;
    char text[64];
    s32 category;
    s32 selection;
    struct MenuWidget *item;
    struct MenuWidget *widget30B;
    struct MenuWidget *widget30D;
    struct MenuWidget *widget35D;
    struct MenuWidget *widget30C;
    struct MenuWidget *widget2FE;
    struct MenuWidget *widget308;
    struct MenuWidget *widget300;
    s32 pulsePhase;
    s32 controllerActivated;
    s32 reservedWord1;
    s32 reservedWord2;
    s32 reservedWord3;
} SetupScreen;
extern struct SetupScreen *g_setupScreen;
/* The prior selection and pending-state words are one real two-word array. */
/* Actual loads in the US-rev1 constructor; not guessed constants. */
extern f32 g_setupRowPreviewScale, g_setupRowPreviewYOffset, g_setupRowPreviewY, g_setupPreviewDepth;
extern f32 g_setupExtraPreviewScale, g_setupExtraPreviewX, g_setupExtraPreviewY;
extern s32 Frontend_InitModelPreviewTransform(struct StateFrontendInitModelPreviewTransform *, s32, Triple, Triple);
extern void Frontend_SetPreviewRotation(struct PreviewRotationView *, Triple);
extern void Frontend_SetPreviewRotationSpeed(struct ModelPreviewRotationSpeedView *, Triple);
#endif
