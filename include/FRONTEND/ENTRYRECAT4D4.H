#ifndef FRONTEND_ENTRYRECAT4D4_H
#define FRONTEND_ENTRYRECAT4D4_H
#include "TYPES.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/RESIDENT_EVENT_HANDLER.H"
#include "COMMON/OWNERRECAT8V1.H"
#include "COMMON/LABEL.H"





struct LoadEquipmentSelectionEntry;
struct LoadEquipmentSelectionEntry {
    char pad0[0x4B0];
    s32 values[6];
    char pad4C8[0x4CC - 0x4C8];
    s32 mode;
};

struct LoadEquipmentSelectionEntry;
struct ScreenFrontendLoadEquipmentSelections;
struct ScreenFrontendLoadEquipmentSelections {
    void *window;
    s32 pad4;
    struct LoadEquipmentSelectionEntry entries[4];
};


struct ResultsPlayerPanel;
struct ResultsPlayerPanel {
    char pad0[0x4A8];
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
    MenuWidget *leftArrow;
    s32 leftStep;
    MenuWidget *rightArrow;
    s32 rightStep;
    s32 state;
    int timer;
    void *resource;
    MenuWidget *message;
    int next;
    char pad136C[0x4];
    char badges[4][0xC0];
};
typedef struct FourPlayerResultsScreen FourPlayerResultsScreen;




struct ResourceSmpFlickerCreateFlickerWidget;

struct ResultsPlayerPanel;
struct FourPlayerResultsScreen;


struct FourPlayerResultsScreen;





extern void Equip_ApplySelectedPlayerLoadouts(void);

struct Entry42 {
    MenuWidget *window;
    struct MenuSlotValueArrayView *slots;
    struct Object49C panel;
    char pad4A8[8];
    s32 state;
    s32 selection;
    char pad4B8[0x18];
};
struct Screen42 {
    struct Entry42 entries[4];
    char pad1340[0x18];
    s32 state;
    s32 next;
    char pad1360[8];
    s32 delay;
};
#endif
