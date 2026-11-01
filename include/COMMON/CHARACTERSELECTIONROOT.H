#ifndef COMMON_CHARACTERSELECTIONROOT_H
#define COMMON_CHARACTERSELECTIONROOT_H
#include "TYPES.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/RESIDENT_EVENT_HANDLER.H"
#include "COMMON/LABEL.H"




struct CharacterSelectionRoot;
struct CharacterSelectionRoot {
    void *screen;
    s32 panel;
    char pad8[8];
    s32 choice;
    s32 phase;
};

extern void Menu_RefreshCharacterUnlocks(void);

struct PanelRecord;
struct PanelRecord {
    char pad[0x14];
    s32 mode;
    char pad18[8];
    char target;
    char pad21[0x4A7];
};


struct RosterSlot;
typedef struct RosterSlot RosterSlot;

struct CharacterVariantSelectionEntry;
struct CharacterVariantSelectionEntry {
    char pad[0x10];
    int target;
    int active;
    char pad18[0x4C8 - 0x18];
};







struct MatchMenuApplySlotValueGfx;
typedef struct MatchMenuApplySlotValueGfx MatchMenuApplySlotValueGfx;

struct StateFlags;

extern void Menu_RandomizeCharacterPreview(s32 player);

struct StateFlags;

struct CharacterData_t;
typedef struct CharacterData_t s_CharacterData;



struct CharacterData_t;
struct CharacterData_t {
    s32 id;
    s32 value; /* +0x4: second word of the slot, Key_GetCharacterPreviewModel */
    char pad8[4];
    f32 scale[4];
    f32 m_fRotY[4];
    CVector3 m_vPos[4];
    s32 flags[4];
    char pad6C[4];
};

struct CharacterVariantSelectionEntry;
typedef struct CharacterVariantSelectionEntry CharacterVariantSelectionEntry;

struct CharacterScreenCell;
struct CharacterScreenCell {
    u16 id;
    u16 pad;
};

struct CharacterSelectionRoot;
typedef struct CharacterSelectionRoot CharacterSelectionRoot;


struct StateMenuCancelCharacterConfirmation;
typedef struct StateMenuCancelCharacterConfirmation StateMenuCancelCharacterConfirmation;

struct PanelRecord;
typedef struct PanelRecord PanelRecord;



extern s32 Key_GetCharacterPreviewModel(s32 key);

struct CharacterScreenCell;
typedef struct CharacterScreenCell CharacterScreenCell;

struct RosterSlot;
struct RosterSlot {
    char pad00[0x78];
    unsigned char active;
    char pad79[6];
    unsigned char player;
    unsigned char kind;
    unsigned char variant;
    char pad82[0xF];
    unsigned char m_IsBot;
    char pad92[4];
};



struct MatchMenuApplySlotValueGfx;

struct StateMenuCancelCharacterConfirmation;
struct StateMenuCancelCharacterConfirmation {
    s32 a;
    s32 reservedWordSecond;
    char p0[8];
    s32 reservedWordFifth;
    s32 confirmationState;
    char p1[4896];
    s32 reservedWord;
    s32 reservedWord1;
    char p2[20];
    s32 reservedWord2;
};


extern s32 Menu_CountPendingCharacterSelections(void);

extern void Menu_RefreshPlayerCharacterVariants(s32);
#endif
