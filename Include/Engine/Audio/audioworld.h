#ifndef ENGINE_AUDIO_AUDIOWORLD_H
#define ENGINE_AUDIO_AUDIOWORLD_H
#include "Common/small_records.h"
extern int g_audioContextInitialized;
#include "types.h"
#include "Common/sharedplayer.h"
#include "Common/listnode.h"
#include "Audio/list_and_channel_views.h"
#include "Audio/audio_chooseweightedsoundvariant.h"




struct AudioSpatialVoiceManagerView;
struct AudioWeightedVariantView;
struct LinkPair;
struct SortTable;
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

extern s32 Audio_ChooseWeightedSoundVariant(struct AudioWeightedVariantView *scene, s16 id, s16 avoid);

struct SortTable {
    char reservedHeader[0xE];
    s16 count;
    u32 entries[1];
};

extern void Audio_SortTableEntries(struct SortTable *table);

extern float g_audioLevelMaximum;

extern void Audio_SetVolumeSettingZero(struct GameAudioContext *audioContext, int volume);

extern void Audio_SetDialogVolume(struct GameAudioContext *object, float value);



struct AudioLevelSettingView {
    char pad[0x2B9C];
    int level;
};

extern char *Audio_GetMetadataSectionThreeEntry(struct GameAudioContext *audioContext, int index);

extern void Audio_SetSpatialPanMode(struct GameAudioContext *audioContext, int panMode);

extern int Audio_FindVoiceSlotById(char *context, int id);

extern void *Audio_GetMetadataSectionFourEntry(struct GameAudioContext *audioContext, int entryIndex);

extern double g_audioContextUnsignedValueCorrection;

extern void Audio_SetVolumeSettingOne(struct GameAudioContext *audioContext, float volume);

extern float g_audioLevelIntegerScale;

extern void AudioWorld_RecyclePendingSoundsByIdentifier(struct ChannelSet *channelSet, s32 soundId);
extern void AudioWorld_StartSpatialVoice(struct AudioSpatialVoiceManagerView *manager, s32 index, s32 owner, CVector3 *position);
extern void AudioWorld_InitializeVoiceListSentinel(void *sentinel, s32 owner);
extern void *AudioWorld_UnlinkChannelNode(struct LinkPair *channelNode);
extern void AudioWorld_RecyclePendingSoundsByKey(void *channelOwner, s32 matchingKey);
extern void AudioWorld_RecyclePendingSoundsByTrack(struct AudioPendingSoundListOwner *listNode, s32 matchingValue);
struct Cache;
void AudioWorld_DispatchPendingSounds(struct Cache *cache);
struct ChannelSet;
void AudioWorld_InitializePendingSoundPool(struct ChannelSet *set, s32 owner);
struct AudioPriorityQueueManagerView;
struct Vec3Words;
s32 AudioWorld_QueuePrioritizedSound(struct AudioPriorityQueueManagerView *manager, void *desc, struct Vec3Words *position, s32 volume, s32 extra);
struct Lists;
void AudioWorld_RecyclePendingSoundsByFlags(struct Lists *lists, s32 matchingFlags);
struct AudioPendingSoundListOwner;
void AudioWorld_RecyclePendingSoundsExceptKey(struct AudioPendingSoundListOwner *channelOwner, s32 retainedKey);
extern s8 SoundInfo_GetPriority(void *);
extern s16 SoundInfo_GetFlags(void *);
#endif
