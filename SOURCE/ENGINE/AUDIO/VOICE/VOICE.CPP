#include "COMMON/OBJRECAT4V6.H"
#include "COMMON/VECTOR4F.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "AUDIO/VOICE_AND_SPATIAL_SOURCE_VIEWS.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/AIPROFILE.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON.H"
#include "AUDIO/EXTERNS.H"
#include "COMMON/GAMEPLAY_CAMERA.H"
#include "COMMON/TRIPLE.H"
#include "TYPES.H"
#include "AUDIO/VOICE.H"
#include "AUDIO/CHANNEL_INITIALIZEVOICEMIX.H"
#include "include_asm.h"
#include "COMMON/SOUNDVOICEPOOL.H"
#include "VOICE/VOICE.H"
#include "COMMON/S1.H"
#include "COMMON/STATERECAT34.H"
#include "ENGINE/AUDIO/T2SOUNDELEMENT.H"
#include "ENGINE/CACHE/LIST.H"

/* 8025A3EC_4.CPP */
/* Releases occupied nonlocal slots unless their value equals the exclusion. */

/* Stops the selected sound slot and sets its release flag; split unsigned offset-to-pointer casts and a one-pass statement group preserve the separate table and offset schedule. */



extern void Channel_InitializeVoicePitchMotion(void *view, void *controller, s32 flags);

extern void *Audio_GetMetadataSectionFiveEntry(GameAudioContext *audioContext, s32 entryIndex);

extern s32 Audio_GetSpatialPanMode(void *object);

extern s16 Channel_ComputeListenerRelativePan(void *position, GameplayCamera *listener);

extern void Channel_UpdateVoicePlayback(void *view);

/* Returns how strongly a listener at 0x128 hears a source at 0x34: one minus the squared distance over the squared range g_spatialSoundRangeSquared (zero beyond it), shaped by the source's curve at 0x44 as the eighth power, the square or the plain value. */





void Audio_StopVoicesExceptKey(VoiceStopKeyTable *record, s32 value)
{
  s32 i;
  s32 active;
  s32 absent;
  AudioVoiceStopKeySlotView *slot = record->slots;
  i = 0;
  absent = -1;
  active = 1;
  for (; i < 16; slot++, i++)
  {
    if (((slot->used != absent) && (record->header->local != i)) && ((value == absent) || (slot->value != value)))
    {
      AudioSoundPlayerOwnerView *owner = slot->owner;
      void *sound;
      slot->active = active;
      slot->flag = 0;
      if (slot->key != owner->key)
      {
        sound = owner->sound;
        alSndpSetSound(sound, owner->samples[slot->index]);
        if (alSndpGetState(sound) != 0)
        {
          if (active)
          {
            alSndpStop(sound);
          }
          else
          {
            alSndpStop(sound);
          }
        }
        slot->state = absent;
      }
    }
  }

}

/* Initialises an object: sets the words at 0x8, 0xC, 0x40 and 0xB4 and the halfword at 0x3A to -1,
   stores the two arguments at 0xB0 and 0x0, clears the halfword at 0x38 and the words at 0x14, 0x58,
   0x5C, 0xA4, 0xAC, 0xBC and 0xC0, sets the word at 0xC4 to 1 and writes g_initialVoiceUnitScale into the floats
   at 0x2C, 0x34 and 0xB8. */

void Audio_InitializeVoiceRecord(void *voiceRecord, int owner, int slotIndex) {
    AudioVoiceRecordView *slot = voiceRecord;
    float k = g_initialVoiceUnitScale;

    slot->f0C = -1;
    slot->f08 = -1;
    slot->f3A = -1;
    slot->f40 = -1;
    slot->fB4 = -1;
    slot->owner = owner;
    slot->index = slotIndex;
    slot->f38 = 0;
    slot->f14 = 0;
    slot->f58 = 0;
    slot->f5C = 0;
    slot->fA4 = 0;
    slot->fAC = 0;
    slot->fBC = 0;
    slot->fC0 = 0;
    slot->fC4 = 1;
    slot->f2C = k;
    slot->f34 = k;
    slot->fB8 = k;
}

void Audio_InitializeVoicePool(s32 *voicePool, s32 ownerAddress) {
    s32 i;
    s32 idx;
    f32 t;
    f32 p;
    s32 off;
    AudioVoiceRecordView *rec;
    f32 k1;
    f32 k2;
    f32 k3;
    s32 negone;
    s32 one;

    i = 0;
    k1 = g_voiceAttenuationInputScale;
    k2 = g_voiceAttenuationOutputScale;
    *voicePool = ownerAddress;
    do {
        t = (f32)i * k1;
        p = t * t * t * t * t * k2;
        idx = 90 - i;
        i += 1;
        g_voiceAttenuationTable[idx] = (s16)(s32)p;
    } while (i < 91);

    negone = -1;
    i = 0;
    k3 = g_voicePoolInitialUnitScale;
    one = 1;
    off = i;
    do {
        rec = (AudioVoiceRecordView *)((u32)off + (u32)voicePool);
        rec = &((VoiceRecordHolder *)(rec))->record;
        rec->index = i;
        i += 1;
        rec->owner = ownerAddress;
        rec->f0C = negone;
        rec->f08 = negone;
        rec->f3A = (s16)negone;
        rec->f38 = 0;
        rec->f40 = negone;
        rec->f14 = 0;
        rec->f2C = k3;
        rec->f58 = 0;
        rec->f5C = 0;
        rec->f34 = k3;
        rec->fA4 = 0;
        rec->fAC = 0;
        rec->fB4 = negone;
        rec->fB8 = k3;
        rec->fBC = 0;
        rec->fC0 = 0;
        rec->fC4 = one;
        off += 204;
    } while (i < 17);
}

s32 Audio_GetVoiceSoundState(AudioVoiceSoundSlotView *voicePool, s16 slotIndex)
{
  s32 voiceAddress;
  s32 ownerAddress;
  void *soundPlayer;
  AudioVoiceRecordView *slot;
  AudioSoundPlayerOwnerView *owner;
  voiceAddress = (slotIndex * 204) + (s32)voicePool;
  voiceAddress = voiceAddress + 4;
  slot = (AudioVoiceRecordView *)voiceAddress;
  ownerAddress = slot->owner;
  owner = (AudioSoundPlayerOwnerView *)ownerAddress;
  soundPlayer = owner->sound;
  alSndpSetSound(soundPlayer, owner->samples[slot->index]);
  return alSndpGetState(soundPlayer);
}

void Audio_PlayVoiceSound(AudioVoiceSoundSlotView *base, s16 index)
{
  unsigned int offset = index * (sizeof(AudioVoiceSoundSlotView));
  unsigned int entry = offset;
  AudioVoiceSoundSlotView *slots;
  AudioVoiceSoundSlotView *selected;
  entry += (unsigned int) base;
  slots = base;
 do { alSndpPlay(&((AudioSoundPlayerOwnerView *)((AudioVoiceSoundSlotView *) entry)->owner)->sound); entry = (unsigned int) slots; entry += offset; selected = (AudioVoiceSoundSlotView *) entry; } while (0);
  selected->flags |= 8;
}

s32 Audio_ReleaseMatchingExclusiveVoice(RecordD90 *record, s16 value, s16 id) {
    s32 i;
    SlotCC *cur = record->slots;

    for (i = 0; i < 16; cur++, i++) {
        if (cur->used != -1 && record->header->local != i && cur->value == value && (cur->mode & 0x40) &&
            cur->id == id) {
            release(&record->slots[(s16)i]);
            return (s16)i;
        }
    }
    return -1;
}

/* Returns whether any of the sixteen occupied slots of a record, other than the one its header marks as local, holds the given value at slot offset 0xA8. */

s32 Audio_HasVoiceWithKey(VoiceKeyTable *record, s32 value) {
    s32 i;
    AudioVoiceKeySlotView *slot = record->slots;

    for (i = 0; i < 16; i++, slot++) {
        if (slot->used != -1 && record->header->local != i && slot->value == value) {
            return 1;
        }
    }
    return 0;
}

void Audio_StopVoiceSlot(s32 voicePoolAddress, s16 slotIndex) {
    s32 base;
    s32 a0;
    void *s1;

    base = (slotIndex * 204) + voicePoolAddress;
    base = base + 4;
    a0 = ((struct IntegerStateB4 *) base)->context;
    ((struct IntegerStateB4 *) base)->done = 1;
    ((struct IntegerStateB4 *) base)->tracked = 0;
    s1 = (void *)(a0 + 132);
    if (((struct IntegerStateB4 *) base)->frame != ((struct VoiceMatchingKeyView *) a0)->voiceKey) {
        s32 idx = ((struct IntegerStateB4 *) base)->slotIndex;
        s32 addr = a0 + idx * 2;
        alSndpSetSound(s1, ((struct SoundSlotHandleView *) addr)->soundId);
        if (alSndpGetState(s1) != 0) {
            alSndpStop(s1);
        }
        ((struct IntegerStateB4 *) base)->handle = -1;
    }
}

void Audio_ClearVoiceFlags(s32 a) {
    s32 remainingSlots;
    void *slotCursor;
    slotCursor = a + 4;
    remainingSlots = 16;
    do {
        ((SlotCC *)slotCursor)->flag = 0;
        remainingSlots -= 1;
        slotCursor += sizeof(AudioVoiceKeyedSlotView);
    } while (remainingSlots >= 0);
}

void Audio_SetVoicePositionTracking(void *voiceRecord, void *initialPosition, int trackedPositionAddress) {
    ((struct ViewChannelUpdateVoicePlayback *)(voiceRecord))->position = *(Triple *)initialPosition;
    ((struct ViewChannelUpdateVoicePlayback *)(voiceRecord))->tracked = (Triple *)trackedPositionAddress;
}

void Audio_SetVoiceTrackId(void *voiceRecord, int newTrackId) {
    ((struct ViewChannelUpdateVoicePlayback *)(voiceRecord))->trackId = newTrackId;
}

void Audio_InitializeVoiceParameters(void *voiceRecord, void *desc, s32 extra) {
    f32 first;
    s16 index;
    s16 value;
    void *record;

    Channel_InitializeVoicePitchMotion(voiceRecord, desc, extra);
    Channel_InitializeVoiceMix(voiceRecord, desc, extra);
    ((struct ViewChannelUpdateVoicePlayback *)(voiceRecord))->priority = 64;
    index = ((struct Shared_Body *)(desc))->kind;
    if (index != -1) {
        record = Audio_GetMetadataSectionFiveEntry(((struct ViewChannelUpdateVoicePlayback *)(voiceRecord))->context, index);
        ((struct ViewChannelUpdateVoicePlayback *)(voiceRecord))->envelope = *(SoundEnvelope *)record;
        first = RW_BITS_TO_FLOAT(((struct ViewChannelUpdateVoicePlayback *)(voiceRecord))->envelope.initial);
        ((struct ViewChannelUpdateVoicePlayback *)(voiceRecord))->step =
            (first - RW_BITS_TO_FLOAT(((struct ViewChannelUpdateVoicePlayback *)(voiceRecord))->envelope.target)) /
            ((struct ViewChannelUpdateVoicePlayback *)(voiceRecord))->envelope.frames;
        ((struct ViewChannelUpdateVoicePlayback *)(voiceRecord))->value =
            RW_BITS_TO_FLOAT(((struct ViewChannelUpdateVoicePlayback *)(voiceRecord))->envelope.initial);
        ((struct ViewChannelUpdateVoicePlayback *)(voiceRecord))->priority =
            (s16)(s32)RW_BITS_TO_FLOAT(((struct ViewChannelUpdateVoicePlayback *)(voiceRecord))->envelope.initial);
        ((struct ViewChannelUpdateVoicePlayback *)(voiceRecord))->sweeping = 1;
        return;
    }

    ((struct ViewChannelUpdateVoicePlayback *)(voiceRecord))->sweeping = 0;
    if (((struct ViewChannelUpdateVoicePlayback *)(voiceRecord))->trackId < 256) {
        if (((struct ViewChannelUpdateVoicePlayback *)(voiceRecord))->fixed == 0 &&
            Audio_GetSpatialPanMode(((struct ViewChannelUpdateVoicePlayback *)(voiceRecord))->context) != 0) {
            value = (s8)((GameAudioContext *)((struct ViewChannelUpdateVoicePlayback *)voiceRecord)->context)->randomPan;
            goto store_value;
        }
    } else if (((struct ViewChannelUpdateVoicePlayback *)(voiceRecord))->fixed == 0 &&
               Audio_GetSpatialPanMode(((struct ViewChannelUpdateVoicePlayback *)(voiceRecord))->context) != 0) {
        value = Channel_ComputeListenerRelativePan(&((struct ViewChannelUpdateVoicePlayback *)(voiceRecord))->position,
            ((struct ViewChannelUpdateVoicePlayback *)voiceRecord)->context->result);
store_value:
        ((struct ViewChannelUpdateVoicePlayback *)(voiceRecord))->priority = value;
    }
}

void Audio_UpdateVoicePool(void **voicePool) {
    s32 i;
    s32 activeVoiceCount;
    char *view;

    activeVoiceCount = 0;
    view = (char *)((RecordD90 *)voicePool)->slots;
    i = 0;
    do {
        if (((SlotCC *)view)->used != -1 && ((AudioSelectedHandleView *)(*voicePool))->local != i) {
            Channel_UpdateVoicePlayback(view);
            activeVoiceCount += 1;
        }
        i += 1;
        view += sizeof(AudioVoiceKeyedSlotView);
    } while (i < 16);
    g_activeVoiceCount = activeVoiceCount;
    if (g_peakActiveVoiceCount < activeVoiceCount) {
        g_peakActiveVoiceCount = activeVoiceCount;
    }
}

/* Returns the index of the first of sixteen 0xCC-byte slots at 0xC that is in use, is not the
   owner's own slot and whose two keys at 0xA0 and 0xAC equal the arguments, or -1 when none does; indexing from the second key reproduces the reference induction base. */

int Audio_FindVoiceByKeyPair(VoiceKeyPairTable *obj, int keyA, int keyB) {
    int i;
    int *keys = &obj->slots[0].keyB;

    for (i = 0; i < 16; i++) {
        if (keys[i * 51 - 43] != -1 && obj->owner->local != i && keys[i * 51 - 3] == keyA &&
            keys[i * 51] == keyB) {
            return i;
        }
    }
    return -1;
}

void Audio_StopVoicesByKey(VoiceStopKeyTable *record, s32 value) {
    s32 i;
    AudioVoiceStopKeySlotView *slot = record->slots;

    for (i = 0; i < 17; slot++, i++) {
        if (slot->used != -1 && record->header->local != i && slot->value == value) {
            AudioSoundPlayerOwnerView *owner = slot->owner;
            void *sound;

            slot->active = 1;
            slot->flag = 0;
            if (slot->key != owner->key) {
                sound = owner->sound;
                alSndpSetSound(sound, owner->samples[slot->index]);
                if (alSndpGetState(sound) != 0) {
                    alSndpStop(sound);
                }
                slot->state = -1;
            }
        }
    }
}

void Audio_StopVoicesBySecondaryValue(VoiceSecondaryKeyTable *record, s32 value) {
    s32 i;
    AudioVoiceSecondarySlotView *slot = record->slots;

    for (i = 0; i < 17; slot++, i++) {
        if (slot->used != -1 && record->header->local != i && slot->value == value) {
            AudioSoundPlayerOwnerView *owner = slot->owner;
            void *sound;

            slot->active = 1;
            slot->flag = 0;
            if (slot->key != owner->key) {
                sound = owner->sound;
                alSndpSetSound(sound, owner->samples[slot->index]);
                if (alSndpGetState(sound) != 0) {
                    alSndpStop(sound);
                }
                slot->state = -1;
            }
        }
    }
}

void Audio_StopVoicesByFlags(AudioVoiceFlagsPoolView *record, s32 value) {
    s32 i;
    AudioVoiceControlSlotView *slot = record->slots;

    for (i = 0; i < 17; slot++, i++) {
        if (slot->used != -1 && record->header->local != i && (slot->mask & value) != 0) {
            AudioSoundPlayerOwnerView *owner = slot->owner;
            void *sound;

            slot->active = 1;
            slot->flag = 0;
            if (slot->key != owner->key) {
                sound = owner->sound;
                alSndpSetSound(sound, owner->samples[slot->index]);
                if (alSndpGetState(sound) != 0) {
                    alSndpStop(sound);
                }
                slot->state = -1;
            }
        }
    }
}

f32 Audio_ComputeDistanceAttenuation(f32 *a, f32 *b) {
    f32 dx = a[0] - b[0];
    f32 dy = a[1] - b[1];
    f32 dz = a[2] - b[2];
    f32 distSq = (dx * dx) + (dy * dy) + (dz * dz);
    if (g_spatialSoundRangeSquared <= distSq) {
        return 0.0f;
    }
    return g_voiceDistanceAttenuationConstants - (distSq / g_spatialSoundRangeSquared);
}

/* Returns whether any of the seventeen occupied slots of a record, other than the one its header marks as local, holds the given value at slot offset 0xA8. Adapted from Audio_HasVoiceWithKey with the slot count changed from 16 to 17. */

s32 Audio_HasVoiceOrReservedSlotWithKey(VoiceKeyTable *record, s32 value) {
    s32 i;
    AudioVoiceKeySlotView *slot = record->slots;

    for (i = 0; i < 17; i++, slot++) {
        if (slot->used != -1 && record->header->local != i && slot->value == value) {
            return 1;
        }
    }
    return 0;
}

f32 Audio_InterpolatePitchTable(f32 pitch)
{
  f32 tableCoordinate;
  f32 lowerCoordinate;
  f32 lowerPitch;
  s32 integerCoordinate;
  s16 sampleIndex;
  s32 nextSampleIndex;
  tableCoordinate = (pitch + (&g_voiceDistanceAttenuationConstants)[1]) * g_pitchTableInputScale;
  integerCoordinate = (s32) tableCoordinate;
  sampleIndex = (s16) integerCoordinate;
  lowerCoordinate = (f32) sampleIndex;
  if (lowerCoordinate != tableCoordinate)
  {
    nextSampleIndex = integerCoordinate + 1;
    lowerPitch = (&g_voicePitchTableBase)[1 + sampleIndex];
    return lowerPitch + ((tableCoordinate - lowerCoordinate) * ((&g_voicePitchTableBase)[1 + ((s16) nextSampleIndex)] - lowerPitch));
  }
  return (&g_voicePitchTableBase)[1 + sampleIndex];
}

s16 Audio_RandomizeSignedRange(s16 center, s16 range) {
    f32 centerValue;
    f32 rangeValue;
    rangeValue = (f32)range;
    centerValue = (f32)center;
    return (s16)(s32)(Graphu64_RandomBetween(rangeValue, centerValue) < 0.0f
                          ? centerValue - Graphu64_RandomBetween(rangeValue, centerValue)
                          : centerValue + Graphu64_RandomBetween(rangeValue, centerValue));
}

f32 Audio_RandomizeScaledByteRange(u8 minimum, u8 maximum) {
    f32 first;
    f32 second;

    first = minimum * g_voiceByteRangeScale;
    second = maximum * g_voiceByteRangeScale;
    if (first == g_voiceByteRangeIdentity) {
        return g_voiceByteRangeIdentity;
    }
    if (second == first) {
        return first;
    }
    return first + Graphu64_RandomFloat(second - first);
}

f32 Audio_ComputeSpatialAttenuationCurve(char *source, char *listener)
{
    SoundSpatialSource *sound = (SoundSpatialSource *)source;
    GameplayCamera *camera = (GameplayCamera *)listener;
    CVector3 *a = &sound->position;
    CVector3 *b = &camera->position;
    f32 dx = a->x - b->x;
    f32 dy;
    f32 dz;
    f32 d;
    f32 t;

    dx *= dx;
    dy = a->y - b->y;
    dy *= dy;
    dz = a->z - b->z;
    dz *= dz;
    d = dx + dy + dz;
    if (d >= g_spatialSoundRangeSquared) {
        t = 0.0f;
    } else {
        t = g_spatialAttenuationUnitScale - d / g_spatialSoundRangeSquared;
    }
    switch (sound->curve) {
    case 2:
        return t;
    case 0:
        t *= t;
        t *= t;
    case 1:
        return t * t;
    default:
        return 0.0f;
    }
}

void Audio_SetScaledVoiceVolume(void *voiceRecord, s32 volume) {
    AudioVoiceRecordView *slot = voiceRecord;
    AudioSoundPlayerOwnerView *owner;
    s32 ownerValue;
    void *sound;

    ownerValue = slot->owner;
    owner = (AudioSoundPlayerOwnerView *)ownerValue;
    sound = owner->sound;
    alSndpSetSound(sound, owner->samples[slot->index]);
    alSndpSetVol(sound, (s16)(s32)((f32) volume * (slot->fC8)));
}

void Audio_SetScaledVoicePitch(void *voiceRecord, f32 pitch) {
    AudioVoiceRecordView *slot = voiceRecord;
    AudioSoundPlayerOwnerView *owner;
    s32 ownerValue;
    void *sound;
    f32 scaled;

    ownerValue = slot->owner;
    owner = (AudioSoundPlayerOwnerView *)ownerValue;
    sound = owner->sound;
    alSndpSetSound(sound, owner->samples[slot->index]);
    scaled = pitch * (slot->f34);
    scaled = scaled * (slot->fB8);
    alSndpSetPitch(sound, scaled);
}

/* Audio_SetVoicePan_Voice.CPP */
ALSndPlayer;



void Audio_SetVoicePan(AudioVoiceControlSlotView *voiceRecord, s32 panValue)
{
  s32 *slotIndexPointer;
  int unusedPanMode;
  s32 ownerAddress;
  void *soundPlayer;
  ownerAddress = (s32)voiceRecord->owner;
  soundPlayer = &((AudioSoundPlayerOwnerView *)ownerAddress)->sound;
  unusedPanMode = 2;
  slotIndexPointer = &voiceRecord->index;
  alSndpSetSound(soundPlayer, ((AudioSoundPlayerOwnerView *)ownerAddress)->samples[*slotIndexPointer]);
  alSndpSetPan(soundPlayer, panValue & 0xFF);
}

void Audio_QueryVoicePlaybackState(AudioVoiceControlSlotView *voiceRecord)
{
  s16 *unusedPointer1;
  s32 ownerAddress;
  void *soundPlayer;
  ownerAddress = (s32)voiceRecord->owner;
  soundPlayer = &((AudioSoundPlayerOwnerView *)ownerAddress)->sound;
  alSndpSetSound(soundPlayer, ((AudioSoundPlayerOwnerView *)ownerAddress)->samples[voiceRecord->index]);
  alSndpGetState(soundPlayer);
}

void Audio_StartSelectedVoice(AudioVoiceControlSlotView *voiceRecord) {
    alSndpPlay(voiceRecord->owner->sound);
}

void Audio_StopVoiceForDifferentKey(AudioVoiceControlSlotView *voiceRecord) {
    s32 ownerValue;
    void *s1;

    ownerValue = voiceRecord->owner;
    voiceRecord->active = 1;
    voiceRecord->flag = 0;
    s1 = (void *)(ownerValue + 132);
    if (voiceRecord->key != ((AudioSoundPlayerOwnerView *)ownerValue)->key) {
        s32 idx = voiceRecord->index;
        s32 addr = ownerValue + idx * 2;
        alSndpSetSound(s1, ((AudioSoundPlayerOwnerView *)ownerValue)->samples[idx]);
        if (alSndpGetState(s1) != 0) {
            alSndpStop(s1);
        }
        voiceRecord->state = -1;
    }
}



void Audio_DeallocateVoiceSlot(AudioVoiceControlSlotView *voiceRecord) {
    void *base;
    Slots *arrayBase;
    short *slot;
    base = voiceRecord->owner;
    arrayBase = &((AudioVoiceContextView *)base)->slots;
    alSndpDeallocate(((AudioSoundPlayerOwnerView *)base)->sound, arrayBase->ids[voiceRecord->index]);
    arrayBase->ids[voiceRecord->index] = -1;
    voiceRecord->priority = 0;
    voiceRecord->releaseMarker = -1;
    voiceRecord->used = -1;
    voiceRecord->value = -1;
    voiceRecord->channel = -1;
    voiceRecord->releaseMarkerB = -1;
}

typedef struct {
    u16 key;
    u16 start;
    u16 end;
    s16 duration;
    u16 reserved[2];
} VoiceEnvelopeBlock;

struct GameAudioContext;
struct GameplayCamera;

typedef struct VoicePanEnvelopeState VoicePanEnvelopeState;
typedef struct SoundPanEnvelopeDescriptor SoundPanEnvelopeDescriptor;
typedef struct VoicePanContextView VoicePanContextView;
struct VoicePanEnvelopeState {
    char pad0[0x28];
    s16 pan;
    char pad28[0x44 - 0x28 - sizeof(s16)];
    char position;
    char pad44[0x88 - 0x44 - sizeof(char)];
    s32 sweeping;
    char pad88[0x8C - 0x88 - sizeof(s32)];
    VoiceEnvelopeBlock envelope;
    char pad8C[0x98 - 0x8C - sizeof(VoiceEnvelopeBlock)];
    f32 envelopeValue;
    char pad98[0x9C - 0x98 - sizeof(f32)];
    f32 envelopeStep;
    char pad9C[0xA8 - 0x9C - sizeof(f32)];
    s32 trackId;
    char padA8[0xB0 - 0xA8 - sizeof(s32)];
    VoicePanContextView *context;
    char padB0[0xC0 - 0xB0 - sizeof(void*)];
    s32 fixedPan;
};
struct SoundPanEnvelopeDescriptor {
    char pad0[0xC];
    s16 panEnvelopeIndex;
};
struct VoicePanContextView {
    char pad0[0x2B94];
    s8 randomPan;
    char pad2B94[0x2B98 - 0x2B94 - sizeof(s8)];
    s32 listenerCameraAddress;
};

void Audio_InitVoiceVolume(VoicePanEnvelopeState *voiceRecord, SoundPanEnvelopeDescriptor *soundDescriptor) {
    f32 first;
    s16 index;
    s16 value;
    VoiceEnvelopeBlock *record;

    voiceRecord->pan = 64;
    index = soundDescriptor->panEnvelopeIndex;
    if (index != -1) {
        record = Audio_GetMetadataSectionFiveEntry(voiceRecord->context, index);
        voiceRecord->envelope = *record;
        first = Menu_ExpandFloatHighWord(voiceRecord->envelope.start);
        voiceRecord->envelopeStep =
            (first - Menu_ExpandFloatHighWord(voiceRecord->envelope.end)) /
            voiceRecord->envelope.duration;
        voiceRecord->envelopeValue =
            Menu_ExpandFloatHighWord(voiceRecord->envelope.start);
        voiceRecord->pan =
            (s16)(s32)Menu_ExpandFloatHighWord(voiceRecord->envelope.start);
        voiceRecord->sweeping = 1;
        return;
    }

    voiceRecord->sweeping = 0;
    if (voiceRecord->trackId < 256) {
        if (voiceRecord->fixedPan == 0 &&
            Audio_GetSpatialPanMode(voiceRecord->context) != 0) {
            value = voiceRecord->context->randomPan;
            goto store_value;
        }
    } else if (voiceRecord->fixedPan == 0 &&
               Audio_GetSpatialPanMode(voiceRecord->context) != 0) {
        value = Channel_ComputeListenerRelativePan(&voiceRecord->position,
            voiceRecord->context->listenerCameraAddress);
store_value:
        voiceRecord->pan = value;
    }
}

/* 8025C544_2.CPP */
static inline short slot_id(Slots *slots, int index) {
    return slots->ids[index];
}

extern s32 SoundElement_PlaySoundAtPosition(s16 track, CVector3 position, s32 spatialMode, s32 ownerId);

int Audio_DeallocatePoolVoice(AudioVoiceFlagsPoolView *pool, short index) {
    AudioVoiceControlSlotView *entry;
    AudioVoiceContextView *context;
    Slots *slots;
    void *owner;

    entry = &pool->slots[index + 1];
    entry--;
    owner = entry->owner;
    context = owner;
    slots = &context->slots;
    alSndpDeallocate(entry->owner->sound, slot_id(slots, entry->index));
    slots->ids[entry->index] = -1;
    entry->priority = 0;
    entry->releaseMarker = -1;
    entry->used = -1;
    entry->value = -1;
    entry->channel = -1;
    entry->releaseMarkerB = -1;
    return 0;
}

/** Initialize the two object words at offsets 8 and 12 to negative one. */
void SoundVoicePool_ResetNode(void *cLoopingSoundData) {
    CLoopingSoundData *voice = cLoopingSoundData;
    voice->state = -1;
    voice->value = -1;
}

void SoundVoicePool_ResetNodeNoOp(void) {
}

void SoundVoicePool_Initialize(void *soundVoicePool, CLoopingSoundData *availableNodes, s32 nodeCount) {
    s32 i;

    List_InitializeIntrusive(soundVoicePool, 0, 4);
    List_InitializeIntrusive(&((SoundVoicePool *)soundVoicePool)->playing, 0, 4);
    i = 0;
    if (nodeCount > 0) {
        do {
            List_AppendIntrusive(soundVoicePool, availableNodes);
            i += 1;
            availableNodes = availableNodes + 1;
        } while (i < nodeCount);
    }
    ((SoundVoicePool *)soundVoicePool)->state = 0;
}

void *SoundVoicePool_PlaySpatialSound(void *voicePool, s32 soundId, CVector3 *soundPosition, void *position, s32 fallback) {
    CLoopingSoundData *node;
    s32 result;

    node = ((SoundVoicePool *)voicePool)->available.head;
    if (node != 0) {
        List_RemoveIntrusive(voicePool, node);
        List_AppendIntrusive(&((SoundVoicePool *)voicePool)->playing, node);
        node->state = -1;
        node->value = -1;
        result = SoundElement_PlaySoundAtPosition((s16)soundId, *soundPosition,
                                (s32)position, fallback);
        node->value = result;
        g_lastStartedPoolSoundHandle = result;
        node->state = soundId;
        node->m_vSoundPos = *soundPosition;
        node->m_vSoundPosPtr = position;
    }
    return node;
}

s32 SoundVoicePool_StopNode(void *work, void *wantedNode) {
    void *playingNode;

    if (wantedNode == 0) {
        return 0;
    }

    playingNode = ((SoundVoicePool *)work)->playing.head;
    if (playingNode != 0) {
        do {
            if (playingNode == wantedNode) {
                SoundElement_StopSoundsByIdentifier(((CLoopingSoundData *)playingNode)->value);
                g_lastStoppedPoolSoundHandle = ((CLoopingSoundData *)playingNode)->value;
                List_RemoveIntrusive(&((SoundVoicePool *)work)->playing, playingNode);
                List_AppendIntrusive(work, playingNode);
                return 1;
            }
            playingNode = ((CLoopingSoundData *)playingNode)->next;
        } while (playingNode != 0);
    }
    return 0;
}

void SoundVoicePool_Pause(void *voicePool) {
    s32 value;
    SoundVoicePool *pool = voicePool;
    CLoopingSoundData *playingNode;

    playingNode = pool->playing.head;
    if (playingNode != 0) {
        do {
            SoundElement_StopSoundsByIdentifier(playingNode->value);
            value = playingNode->value;
            playingNode = playingNode->next;
            g_lastPausedPoolSoundHandle = value;
        } while (playingNode != 0);
    }
    pool->state = 1;
}

void SoundVoicePool_Resume(SoundVoicePool *soundVoicePool) {
    s32 playbackHandle;
    CLoopingSoundData *playingNode;

    playingNode = soundVoicePool->playing.head;
    if (playingNode != 0) {
        do {
            playbackHandle = SoundElement_PlaySoundAtPosition((s16)playingNode->state,
                                     playingNode->m_vSoundPos,
                                     (s32)playingNode->m_vSoundPosPtr,
                                     -1);
            playingNode->value = playbackHandle;
            playingNode = playingNode->next;
            g_lastResumedPoolSoundHandle = playbackHandle;
        } while (playingNode != 0);
    }
    soundVoicePool->state = 0;
}

void SoundVoicePool_RetireFinishedSounds(void *soundVoicePool) {
    SoundVoicePool *pool = soundVoicePool;
    CLoopingSoundData *playingNode;

    if (pool->state == 0) {
        playingNode = pool->playing.head;
        if (playingNode != 0) {
            do {
                if (SoundElement_CountOwnerVoices(playingNode->value) == 0) {
                    playingNode->state = -1;
                    playingNode->value = -1;
                }
                playingNode = playingNode->next;
            } while (playingNode != 0);
        }
    }
}

void SoundVoicePool_StopAll(void *soundVoicePool) {
    CLoopingSoundData *cur;
    CLoopingSoundData *next;
    s32 value;
    SoundVoicePool *pool = soundVoicePool;

    cur = pool->playing.head;
    if (cur != 0) {
        do {
            value = cur->value;
            next = cur->next;
            SoundElement_StopSoundsByIdentifier(value);
            cur->state = -1;
            cur->value = -1;
            List_RemoveIntrusive(&pool->playing, cur);
            List_AppendIntrusive(&pool->available, cur);
            cur = next;
        } while (cur != 0);
    }
}

/* 8025C544_6.CPP */
/** Return the address of the global state word at g_soundVoicePoolGlobalState. */
s32 *SoundVoicePool_GetGlobalState(void) {
    return &g_soundVoicePoolGlobalState;
}

/** Deliberately perform no work. */
void SoundVoicePool_GetGlobalStateNoOp(void) {
}


/* 800C9068.CPP */
#if !(defined(VERSION_US_REV1))
const float k_VoiceEncodedWords[1] = {
    1.0f,
};
#endif

#if defined(VERSION_US_REV1)
/* ROM-grounded data: src/k_VoiceOneWordsUsRev1.c */
const float k_VoiceOneWords[1] = {
    1.0f,
};
#endif

/* 800C906C.CPP */
/* ROM-grounded data: src/g_audio_InitializeVoicePoolConstantWordsUsRev1.c */
const float g_audio_InitializeVoicePoolConstantWords[3] = {
    0.011111111f, 3.2e+04f, 1.0f,
};

/* 800C9078.CPP */
#if !(defined(VERSION_US_REV1))
const float g_audio_ComputeDistanceAttenuationConstantWords1[1] = {
    1.0f,
};
#endif

#if defined(VERSION_US_REV1)
/* ROM-grounded data: src/g_audio_ComputeDistanceAttenuationConstantWords2UsRev1.c */
const float g_audio_ComputeDistanceAttenuationConstantWords2[1] = {
    1.0f,
};
#endif

/* 800C907C.CPP */
/* ROM-grounded data: src/g_audio_InterpolatePitchTableConstantWordsUsRev1.c */
const float g_audio_InterpolatePitchTableConstantWords[2] = {
    6.0e+03f, 0.016666668f,
};

/* 800C9084.CPP */
/* ROM-grounded data: src/g_audio_RandomizeScaledByteRangeConstantWordsUsRev1.c */
const float g_audio_RandomizeScaledByteRangeConstantWords[2] = {
    0.01f, 1.0f,
};

/* 800C908C.CPP */
#if !(defined(VERSION_US_REV1))
const float g_audio_ComputeSpatialAttenuationCurveConstantWords1[1] = {
    1.0f,
};
#endif

#if defined(VERSION_US_REV1)
/* ROM-grounded data: src/g_audio_ComputeSpatialAttenuationCurveConstantWords2UsRev1.c */
const float g_audio_ComputeSpatialAttenuationCurveConstantWords2[1] = {
    1.0f,
};
#endif
