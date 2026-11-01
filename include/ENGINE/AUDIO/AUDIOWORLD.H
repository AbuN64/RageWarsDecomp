#ifndef ENGINE_AUDIO_AUDIOWORLD_H
#define ENGINE_AUDIO_AUDIOWORLD_H
#include "TYPES.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/LISTNODE.H"
#include "AUDIO/LIST_AND_CHANNEL_VIEWS.H"

struct AudioLevelSettingView;

typedef struct AudioLevelSettingView AudioLevelSettingView;

struct SortTable;

typedef struct SortTable SortTable;

struct GameAudioContext;

extern void *Audio_GetMetadataSectionFiveEntry(struct GameAudioContext *audioContext, int entryIndex);

struct AudioWeightedVariantView;

struct AudioWeightedVariantView {
    char pad0[0x130];
    s32 lastPick;
    char pad134[0x2B54 - 0x134];
    s32 count;
    s32 ids;
    s32 *weights;
};

typedef struct AudioWeightedVariantView AudioWeightedVariantView;

extern s32 Audio_ChooseWeightedSoundVariant(AudioWeightedVariantView *scene, s16 id, s16 avoid);

struct SortTable {
    char reservedHeader[0xE];
    s16 count;
    u32 entries[1];
};

extern void Audio_SortTableEntries(SortTable *table);

extern float g_audioLevelMaximum;

extern void Audio_SetVolumeSettingZero(struct GameAudioContext *audioContext, int volume);

extern void Audio_SetDialogVolume(struct GameAudioContext *object, float value);

extern int Audio_GetSpatialPanMode(void *object);

struct AudioLevelSettingView {
    char pad[0x2B9C];
    int level;
};

extern char *Audio_GetMetadataSectionThreeEntry(char *object, int index);

extern void Audio_SetSpatialPanMode(struct GameAudioContext *audioContext, int panMode);

extern int Audio_FindVoiceSlotById(char *context, int id);

extern void *Audio_GetMetadataSectionFourEntry(struct GameAudioContext *audioContext, int entryIndex);

extern double g_audioContextUnsignedValueCorrection;

extern void Audio_SetVolumeSettingOne(struct GameAudioContext *audioContext, float volume);

extern float g_audioLevelIntegerScale;

extern void AudioWorld_RecyclePendingSoundsByIdentifier(struct ChannelSet *channelSet, s32 soundId);
extern void AudioWorld_StartSpatialVoice(AudioSpatialVoiceManagerView *manager, s32 index, s32 owner, CVector3 *position);
extern void AudioWorld_InitializeVoiceListSentinel(void *sentinel, s32 owner);
extern void *AudioWorld_UnlinkChannelNode(LinkPair *channelNode);
extern void AudioWorld_RecyclePendingSoundsByKey(void *channelOwner, s32 matchingKey);
extern void AudioWorld_RecyclePendingSoundsByTrack(AudioPendingSoundListOwner *listNode, s32 matchingValue);
#endif
