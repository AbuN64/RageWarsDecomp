#ifndef COMMON_NAME_H
#define COMMON_NAME_H
#include "TYPES.H"
#include "COMMON/ENTRYRECAT6C.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/MENU_ABBDC_VERSIONS.H"

struct Name;
struct Name {
    u8 flags[2];
    u8 code[20];
    u8 text[0x46 - 0x16];
};

struct PakDisplayName;
typedef struct PakDisplayName PakDisplayName;

struct PakDisplayName;
struct PakDisplayName {
    char text[60];
    char code[70 - 0x3C];
};

struct Name;
typedef struct Name Name;

/* One pak note line of the note list: its label, the note name and its size text. */
typedef struct PakNoteText {
    char label[40];
    char name[20];
    char size[10];
} PakNoteText;
struct PakProfilePanelState;
struct PakProfilePanelState {
    s32 state;
    s32 sub;
    s32 next;
    union { s32 menu; MenuWidget *menuWidget; };
    MenuWidget *sprite; /* 0x10 */
    s32 back;
    union {
        char slots[4][400];
        Profile records[4];
    };
    union {
        struct { char pad658[0x67E - 0x658]; Name names[15]; };
        PakDisplayName displayNames[15];
        PakNoteText noteTexts[16];
    };
    union {
        u8 codes[3][0xA]; /* 0xAB8 */
        struct {
            char code0[10];
            char usedText[10];
            char freeText[10];
        };
    };
    char padAD6[0xAD8 - 0xAD6];
    s32 slot;
    union {
        char padADC[0xAEC - 0xADC];
        struct { s32 scroll; MenuWidget *labels[3]; };
    };
    union {
        s32 chosen;
        s32 choice;
    };
    s32 used[4];
    union { s32 notes[4]; MenuWidget *nodes[4]; };
    char padB10[0xB28 - 0xB10];
    s32 port;
    s32 record;
    s32 host;
    InventorySlot name[8]; /* 0xB34 */
    s32 nameCursor; /* 0xB44 */
    s32 namePhase; /* 0xB48 */
    s32 nameTimer; /* 0xB4C */
    char nameText[0xB64 - 0xB50]; /* 0xB50 */
    s32 profile;
};

struct PakProfilePanelState;
typedef struct PakProfilePanelState PakProfilePanelState;

struct PakMenuController;
/* One pak transfer link: a player's record slot picked as a copy source and its state. */
typedef struct PakMenuLink {
    s32 player;
    s32 entry;
    s32 state;
} PakMenuLink;
/* The 0x648-byte save packet: four profile records, the chosen profile and a CRC over the records. */
typedef struct PakSavePacket {
    Profile saved[4];
    s32 savedProfile; /* 0x640 */
    u32 checksum; /* 0x644 */
} PakSavePacket;
/* The pak and name-entry menu block (Scene memory) g_pakProfileScreenState points to. */
struct PakMenuController {
    union {
        s32 windowAddress;
        void *window;
    };
    union {
        s32 root;
        void *list;
    };
    union {
        u8 menu[0x4C - 0x8]; /* 0x08: the menu panel, passed by address */
        struct {
            char pad8[0x24 - 0x8];
            void *music; /* 0x24 */
            MenuWidget *title; /* 0x28 */
            s32 selected[4]; /* 0x2C */
            MenuWidget *top; /* 0x3C */
            s32 topStep;
            MenuWidget *bottom;
            s32 bottomStep; /* 0x48 */
        };
    };
    s32 ready; /* 0x4C */
    s32 timer; /* 0x50 */
    s32 phase; /* 0x54 */
    PakProfilePanelState players[4]; /* 0x58 */
    PakMenuLink links[4]; /* 0x2DF8 */
    PakSavePacket packet; /* 0x2E28 */
    s32 focus; /* 0x3470 */
};

struct Char;
struct Char {
    char c;
    char pad;
};

struct Char;


struct RecordPAKInterfaceReassignLocalProfiles;
struct RecordPAKInterfaceReassignLocalProfiles {
    char pad0[0xD];
    s8 owner;
    char padE[400 - 0xE];
};


struct RecordPAKInterfaceReassignLocalProfiles;

extern char *g_pakProfileGameNames[];

struct Shared_Item;
struct WidgetLabelTextView;
struct Shared_Item {
    char pad0[0x8];
    struct WidgetLabelTextView * label;
    char padC[0x6];
    u16 flags;
    char pad14[0x24];
    struct Shared_Item *next;
};





struct MatchSetupGlobals;
struct MatchSetupGlobals {
    char pad0[0xD0];
    ListScreenRecord status[8];
};





struct PakMenuController;
typedef struct PakMenuController PakMenuController;


struct MatchSetupGlobals;
typedef struct MatchSetupGlobals MatchSetupGlobals;



struct Blk;
typedef struct Blk Blk;

struct PakPanelSelectionView;
struct PakPanelSelectionView {
    char pad0[0x58];
    s32 state;
    char pad5C[0xB9C - 0x5C];
    s32 count;
    s32 phase;
    s32 timer;
};


struct Shared_Item;
typedef struct Shared_Item Shared_Item;

struct SmpOverlaySlotsView;


struct ItemFrontendRelabelSlotRows;
struct WidgetLabelTextView;
struct ItemFrontendRelabelSlotRows {
    char pad[0x8];
    struct WidgetLabelTextView *label;
};




struct Blk;
struct Blk {
    char p0[4];
    s32 reservedWord4;
    char p1[36];
    s32 animationClock;
    char p2[40];
    s32 panelState;
    char p3[2772];
    s32 selectedNote;
    s32 noteScrollOffset;
    ResourceSmpFlickerCreateFlickerWidget *noteLabel;
    char p4[100];
    s32 nameEntryPhase;
    s32 nameEntryTimer;
};





struct Triple;

#endif
