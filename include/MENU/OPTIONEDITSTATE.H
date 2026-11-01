#ifndef MENU_OPTIONEDITSTATE_H
#define MENU_OPTIONEDITSTATE_H
#include "TYPES.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/TEXTLAYERMETRICS.H"
#include "COMMON/SHAREDPLAYER.H"

struct OptionsPakAdjustPackedButtonOption;
struct OptionsPakAdjustPackedButtonOption {
    s32 flags;
    s32 pad4[3];
    s32 value;
};

struct OptionEditState;
struct OptionEditState {
    char p[20];
    s32 *textAddressPointer;
    char q[4];
    struct OptionEditState *selectedObject;
    s32 controller;
    char r[52];
    s32 modelIndex;
    char a[1408];
    struct OptionEditState *modelOwner;
};

struct OptionEditContext;
struct ActorAnimationEventTable;
struct OptionEditContext {
    char pad0[0x8];
    struct ActorAnimationEventTable modelRecords;
};


struct OptionEditContext;
typedef struct OptionEditContext OptionEditContext;

struct OptionEditState;
typedef struct OptionEditState OptionEditState;



#if defined(VERSION_DE) || defined(VERSION_US_REV1)
s32 Pak_UpdateFirstVolumeLabel(struct LayeredText *field);
#endif


#if defined(VERSION_DE) || defined(VERSION_US_REV1)
s32 Pak_FormatMusicPreview(struct LayeredText *field);
#endif


#if defined(VERSION_DE) || defined(VERSION_US_REV1)
s32 Pak_UpdateThirdVolumeLabel(struct LayeredText *field);
#endif

extern u8 *g_volumeZeroMinimumLabelFixed;
extern u8 *g_volumeZeroMaximumLabelFixed;
extern u8 *g_volumeZeroNeutralLabelFixed;
extern u8 *g_volumeZeroMinimumLabels[];
extern u8 *g_volumeZeroMaximumLabels[];
extern u8 *g_volumeZeroNeutralLabels[];
extern char g_volumePositiveStepFormat[];
extern char g_volumeNegativeStepFormat[];
extern char g_pakFormatSpacedInt2[];
extern char g_pakFormatSpacedInt3[];

#if defined(VERSION_EU) || defined(VERSION_EU_X)
extern char *g_volumeOneMinimumLabel[];
extern char *g_volumeOneMaximumLabel[];
extern char *g_volumeOneNeutralLabel[];
#else
extern char *g_volumeOneMinimumLabel;
extern char *g_volumeOneMaximumLabel;
extern char *g_volumeOneNeutralLabel;
#endif

extern u8 *g_musicPreviewFixedValueText;
extern char g_musicPreviewValueFormat_de[];


extern u8 *g_packedButtonOptionZeroText;

extern u8 *g_volumeTwoMinimumLabel;
extern u8 *g_volumeTwoMaximumLabel;
extern u8 *g_volumeTwoNeutralLabel;

s32 Control_IsStartPressed(Shared_Effect *);
#endif
