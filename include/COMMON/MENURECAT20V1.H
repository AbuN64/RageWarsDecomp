#ifndef COMMON_MENURECAT20V1_H
#define COMMON_MENURECAT20V1_H
#include "TYPES.H"
#include "COMMON/AIPROFILE.H"
#include "COMMON/ITEMRECAT20V1.H"
extern float g_multiplayerNameEntryTimingLimits;

struct NameSpinnerMenu;

struct ActorPakEnterPlayerOptions;
struct ActorPakEnterPlayerOptions {
    char pad0[0x80];
    s32 mask80;
    char pad84[0xA8 - 0x84];
    s32 maskA8;
};
struct ActorPakEnterPlayerOptions;
struct PlayerOptionsEntry;

struct PlayerOptionsEntry;
typedef struct PlayerOptionsEntry PlayerOptionsEntry;


struct Spinner;
typedef struct Spinner Spinner;

struct StyleMultiDrawNameCursor;


struct NameSpinnerEntry;



struct NameEditMenuContext;



struct NameSpinnerEntry;
typedef struct NameSpinnerEntry NameSpinnerEntry;

struct LocalizedInputState;
struct LocalizedInputState {
    u8 reserved[0x1809];
    u8 language;
};

extern float g_multiplayerNameCursorWidthScale;

struct StyleMultiDrawNameCursor;
typedef struct StyleMultiDrawNameCursor StyleMultiDrawNameCursor;

struct PlayerNameTextEntry;
typedef struct PlayerNameTextEntry PlayerNameTextEntry;

struct Spinner;


struct NameSpinnerMenu;
typedef struct NameSpinnerMenu NameSpinnerMenu;

struct LocalizedInputState;
typedef struct LocalizedInputState LocalizedInputState;


struct PlayerNameTextEntry;

struct NameEditMenuContext;
typedef struct NameEditMenuContext NameEditMenuContext;

struct Field;

typedef u8 SavedPlayerName[24];
extern u8 g_multiplayerSavedPlayerNames[];

extern void Control_SaveControllerSetup(void);
#endif
