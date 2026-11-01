#ifndef COMMON_RECORDRECATCV1_H
#define COMMON_RECORDRECATCV1_H
#include "TYPES.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/TEXTLAYERMETRICS.H"




struct TargetPakDisablePreviewSelection;
struct TargetPakDisablePreviewSelection {
    char pad0[0xA8];
    s32 first;
    char padAC[0xD0 - 0xAC];
    s32 second;
};
struct PakPreviewSelectionView;
struct TargetPakDisablePreviewSelection;

struct PakPreviewSelectionView;

struct PakPreview;
typedef struct PakPreview PakPreview;


struct PakChannelResultView;
struct PakMenuSlot;

struct PakPreview;


struct PakSelectedPromptView;

struct PakSelectedPromptView;

struct PlayerSavedProfileOwner;

struct Shared_PakMenu;

struct PakChannelResultView;

struct Shared_PakMenu;


#if defined(VERSION_DE) || defined(VERSION_US) || defined(VERSION_US_REV1)
s32 Timer_UpdateOwnerChannelLabel(struct LayeredText *field, struct Shared_PakMenu *holder);
#endif

extern s32 Control_PeekPakChange(s32);

extern void Note_ProbeStatus(s32);
void Note_ProbeStatus(s32);
s32 Note_GetStatus(s32);

extern char g_pakFormatInt2_TimerFormatpreviewvalue[];

extern char g_pakFormatDottedTriple[];

extern char g_pakFormatInt04[];
#endif
