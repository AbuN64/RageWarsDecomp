#ifndef COMMON_ENTRYRECAT6C_H
#define COMMON_ENTRYRECAT6C_H
#include "TYPES.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/ITEMRECAT20V1.H"




struct PakPlayerPanelView;
struct PakPlayerPanelView {
    char pad0[0x58];
    s32 first;
    char pad5C[0x6C - 0x5C];
    s32 second;
    char pad70[2920 - 0x70];
};


struct PakSavePacketView;
struct PakSavePacketView {
    char pad0[0x70];
    char savePacketStart;
};



struct Triple;






struct LinkedProfileOwnerRecord;
struct LinkedProfileOwnerRecord {
    s32 id;
    signed char kind;
    char pad5[7];
    s8 slot; /* 0xC */
    s8 place; /* 0xD */
    char padE[400 - 14];
};



struct EntryPAKInterfacePulseIdlePanelLabels;
struct EntryPAKInterfacePulseIdlePanelLabels {
    char pad0[0x2C];
    s32 phases[1];
    char pad30[0x68 - 0x30];
    void *window;
    char pad6C[2920 - 0x6C];
};

struct PakNameRepeatView;
struct PakNameRepeatView {
    char pad[0x58];
    int state;
    char pad5C[0xBA0 - 0x5C];
    int phase;
    int timer;
};

struct Triple;


struct IntegerStateBC0;
typedef struct IntegerStateBC0 IntegerStateBC0;







extern int g_pakProfileRequestedPhase;














struct IntegerStateBC0;
struct IntegerStateBC0 {
    unsigned char padding_0[3004];
    s32 savedProfile;
};

extern float g_pakPanelPulseUnsignedThreshold;

struct Triple;



struct StatePAKInterfaceBeginLinkedProfileTransfer;
struct StatePAKInterfaceBeginLinkedProfileTransfer {
    char pad0[4];
    s32 window;
    char pad8[0x50];
    s32 state;
    s32 step;
    s32 next;
    char pad64[8];
    s32 display;
    char pad70[0xB18];
    s32 reset;
    char padb8c[0x226C];
    s32 selected;
};



extern float g_pakPanelPulsePhaseScale;

struct PakNameRepeatView;
typedef struct PakNameRepeatView PakNameRepeatView;

struct StatePAKInterfaceBeginLinkedProfileTransfer;
typedef struct StatePAKInterfaceBeginLinkedProfileTransfer StatePAKInterfaceBeginLinkedProfileTransfer;




struct PakSavePacketView;
typedef struct PakSavePacketView PakSavePacketView;






extern void PAKInterface_LoadAllLinkedProfiles(void);
#endif
