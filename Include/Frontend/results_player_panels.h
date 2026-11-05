#ifndef FRONTEND_RESULTS_PLAYER_PANELS_H
#define FRONTEND_RESULTS_PLAYER_PANELS_H
#include "Frontend/frontend.h"
#include "types.h"
#include "Common/resident_event_handler.h"
#include "Common/menu_overlay.h"
#include "Common/label.h"








struct FourPlayerResultsScreen;
struct ResultsPlayerPanel;
struct ResultsPlayerPanel {
    char previewTransform[0x4A8]; /* passed to Preview_SetPreviewTransformUpdate */
    s32 state;
    s32 selection;
    s32 values[6];
    struct MenuWidget *item;
    s32 mode;
};

struct FourPlayerResultsScreen;
struct ResultsPlayerPanel;
struct FourPlayerResultsScreen {
    void *window;
    void *menu;
    struct ResultsPlayerPanel panels[4];
    struct MenuWidget *leftArrow;
    s32 leftStep;
    struct MenuWidget *rightArrow;
    s32 rightStep;
    s32 state;
    int timer;
    void *resource;
    struct MenuWidget *message;
    int next;
    char pad136C[0x4];
    char badges[4][0xC0];
};
typedef struct FourPlayerResultsScreen FourPlayerResultsScreen;

/* The equipment and results screen: four player panels followed by the shared arrows, state and badge models. */
extern struct FourPlayerResultsScreen *g_equipmentAndResultsScreen;




struct ResourceSmpFlickerCreateFlickerWidget;

struct ResultsPlayerPanel;
struct FourPlayerResultsScreen;


struct FourPlayerResultsScreen;





extern void Equip_ApplySelectedPlayerLoadouts(void);

#endif
