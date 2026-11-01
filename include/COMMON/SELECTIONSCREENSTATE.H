#ifndef COMMON_SELECTIONSCREENSTATE_H
#define COMMON_SELECTIONSCREENSTATE_H
#include "TYPES.H"
#include "COMMON/OWNERRECAT8V1.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/ITEMRECAT20V1.H"

/* Selection items are menu widgets; w is the legacy width spelling. */
typedef MenuWidget SlotSelectionWidget;

struct SelectionScreenPlayer {
    SlotSelectionWidget *highlight;
    s32 slotOverlay;
    s32 kind;
    s32 selectionState;
    s32 choice;
    char pad14[4];
    char model[0x4C0 - 0x18];
    s32 tintFramesLeft;
    s32 pad4C4;
};
typedef struct SelectionScreenPlayer SelectionScreenPlayer;

struct SelectionScreenState {
    void *screen;
    struct SmpOverlaySlotsView *slotOverlay;
    SelectionScreenPlayer players[4];
    SlotSelectionWidget *header;
    s32 headerStep;
    SlotSelectionWidget *footer;
    s32 footerStep;
    s32 phase;
    s32 timer;
    void *prompt;
    SlotSelectionWidget *promptItem;
    SlotSelectionWidget *pulse;
    s32 pulseStep;
    s32 clock;
    s32 result;
};
typedef struct SelectionScreenState SelectionScreenState;

struct SlotSelectionLayoutCell {
    u16 pad;
    u16 id;
};
typedef struct SlotSelectionLayoutCell SlotSelectionLayoutCell;

struct SlotSelectionLayout {
    s32 kind; /* the low half is the preview frame */
    u16 pad4;
    u16 cursor;
    u16 pad8;
    u16 title;
    SlotSelectionLayoutCell cells[3];
    SlotSelectionLayoutCell options[3];
};
typedef struct SlotSelectionLayout SlotSelectionLayout;


struct SlotSelectionPlayerConfig {
    s16 total, score, kills, selected, other;
    s16 rewardStatistic; /* +0x0A: end-of-match reward statistic */
    char padC[0x78 - 0xC];
    u8 active;
    char pad79[7];
    s8 kind;
    char pad81[3];
    char name[13];
    u8 out, rankPad, rank;
    char tail[2];
};
typedef struct SlotSelectionPlayerConfig SlotSelectionPlayerConfig;

/* The 528-byte menu block at g_profileStatisticsScreen that Frontend_CreateSlotSelectionMenu allocates: its owner names each
   slot it writes, and the neighbouring menu units keep their own view structs over the same block,
   so consumers reach it through casts from this canonical spelling. */
struct SlotSelectionMenuBlock {
    void *root;
    s32 list;
    struct RecordFrontendSetPreviewModel record;
    char pad40[0xC8 - 0x40];
    SlotSelectionWidget *item492;
    s32 round492;
    SlotSelectionWidget *item491;
    s32 round491;
    s32 menuPhase;
    s32 reservedWord;
    s32 lookup486;
    SlotSelectionWidget *item486;
    SlotSelectionWidget *item563;
    s32 focus;
    SlotSelectionWidget *item510;
    SlotSelectionWidget *item512;
    s32 reservedWord1;
    s32 style;
    SlotSelectionWidget *item511;
    s32 reservedWord2;
    s32 player;
    s32 activeSlot;
};
typedef struct SlotSelectionMenuBlock SlotSelectionMenuBlock;









extern SelectionScreenState *g_characterSelectionMenu;
extern SlotSelectionLayout g_characterSelectionMenuEntries[];


/* Focus_AdvanceActiveSlot_Menu advances the cursor word it is handed, the menu block's slot at +0x10C. */
extern SlotSelectionMenuBlock *g_profileStatisticsScreen;
extern void Focus_AdvanceActiveSlot(int *cursor);
extern SlotSelectionPlayerConfig g_playerSettings[];
extern struct Record *Cache_AllocateMemory(s32 size);
extern NodeMenuCreateOverlayNode *SmpOverlay_CreateOverlayNode(MenuOverlayOwnerView *, s32);
extern void SmpOverlay_ShowSlotById(MenuMultiUserOwnerView *, s32, s32);
extern void Random_SetSelectedStage(s32, s32);
extern s32 Key_FindCharacterPreviewRow(s32);
extern MenuWidget *Node_FindWidgetByResourceId(void *, s32);
extern void Widget_SetWidgetFlag08(void *object, int enabled);
extern void Menu_ShowPlayerCharacterSelection(s32);
extern void Tsmos_DeactivateControllerState(void);
#endif
