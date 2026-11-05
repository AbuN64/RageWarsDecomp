#ifndef COMMON_PLAYER_MESSAGE_MENU_H
#define COMMON_PLAYER_MESSAGE_MENU_H
#include "types.h"
#include "Common/sharedplayer.h"
extern s32 g_pakScanActive;

extern char g_pakNoteDeleteSucceededDialogResource[];

extern char *g_pakRankScoreTitles[12];


struct PakPromptContext;
typedef struct PakPromptContext PakPromptContext;


extern s32 g_pakProfileLoadActive;


struct Messages;
struct Messages {
    char pad0[0x554];
    char text[1];
};
struct Messages;
struct PlayerMessageMenuView;
struct PlayerMessageMenuView {
    char pad0[0x5DC];
    struct Messages *messages;
    char pad5E0[0xC];
    s32 menu;
};

extern s32 g_pakMenuPromptAccepted;

extern s32 g_pakSaveMenuActiveDe;


extern s32 g_pakRequestLatched;


struct PakPromptContext;
struct PlayerMessageMenuView;

struct PakPromptContext;

struct PakNoteTextEntry;
typedef struct PakNoteTextEntry PakNoteTextEntry;

struct PakNoteBrowserContext;

extern char *g_pakSnapshotGameNameFixed;

struct PakPromptContext;

struct PakPromptContext;







extern s32 g_pakProfileLoadMode_de;

struct PakNoteBrowserContext;
typedef struct PakNoteBrowserContext PakNoteBrowserContext;


extern int g_pakAlternatePromptEnabled;


struct PlayerMessageMenuView;
typedef struct PlayerMessageMenuView PlayerMessageMenuView;

extern s32 g_pakUsable;

extern s32 g_pakNoteSelectProbesNote;

extern int g_controllerPakOverwriteNoteIndex;

extern char g_pakNoteDeleteFailedDialogResource[];



extern s32 g_introSelectedItem;

struct PlayerPakTimerView;
typedef struct PlayerPakTimerView PlayerPakTimerView;


struct PlayerPakTimerView;


extern s32 g_pakNoteTitleSelector;




struct PakNoteTextEntry;

extern char *g_pakProfileGameNameFixed;


extern s32 g_pakProbeRequested;



struct PlayerSavedProfileOwner;

struct PakStatusPakSaveMenu;
struct PakNotesMenu;
#endif
