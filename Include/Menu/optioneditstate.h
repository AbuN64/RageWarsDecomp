#ifndef MENU_OPTIONEDITSTATE_H
#define MENU_OPTIONEDITSTATE_H
#include "Data/Overlays/Credits/objectdata_addresses.h"
#include "types.h"
#include "Common/textlayermetrics.h"
#include "Common/sharedplayer.h"
#include "Volume/g_pakformatspacedint2digits.h"
#include "Volume/g_pakformatspacedint3digits.h"
#include "Volume/pak_formatmusicpreview_data.h"

struct Shared_Effect;
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

/* One 100-byte model record of the model editor's pack section; the menu edits a field of it by byte position. */
typedef struct ModelEditRecord {
    u8 bytes[100];
} ModelEditRecord;

/* The model editor's pack section: the record size, the record count and the records. */
struct OptionEditContext;
struct OptionEditContext {
    s32 recordSize;
    s32 count;
    ModelEditRecord records[1];
};


struct OptionEditContext;
typedef struct OptionEditContext OptionEditContext;

struct OptionEditState;
typedef struct OptionEditState OptionEditState;



#if defined(VERSION_DE) || defined(VERSION_US_REV1)
struct LayeredText;
s32 Pak_UpdateMusicVolumeLabel(struct LayeredText *field);
#endif


#if defined(VERSION_DE) || defined(VERSION_US_REV1)
s32 Pak_FormatMusicPreview(struct LayeredText *field);
#endif


#if defined(VERSION_DE) || defined(VERSION_US_REV1)
s32 Pak_UpdateSpeechVolumeLabel(struct LayeredText *field);
#endif

extern u8 *g_volumeZeroMinimumLabelFixed;
extern u8 *g_volumeZeroMaximumLabelFixed;
extern u8 *g_volumeZeroNeutralLabelFixed;
extern u8 *g_volumeZeroMinimumLabels[];
extern u8 *g_volumeZeroMaximumLabels[];
extern u8 *g_volumeZeroNeutralLabels[];
extern char g_volumePositiveStepFormat[];
extern char g_volumeNegativeStepFormat[];



#if defined(VERSION_EU) || defined(VERSION_EU_X)
extern char *g_soundEffectsVolumeMinimumLabel[];
extern char *g_soundEffectsVolumeMaximumLabel[];
extern char *g_soundEffectsVolumeNeutralLabel[];
#else
extern char *g_soundEffectsVolumeMinimumLabel;
extern char *g_soundEffectsVolumeMaximumLabel;
extern char *g_soundEffectsVolumeNeutralLabel;
#endif




extern u8 *g_packedButtonOptionZeroText;

extern u8 *g_speechVolumeMinimumLabel;
extern u8 *g_speechVolumeMaximumLabel;
extern u8 *g_speechVolumeNeutralLabel;

s32 Control_IsStartPressed(struct Shared_Effect *);
#endif
