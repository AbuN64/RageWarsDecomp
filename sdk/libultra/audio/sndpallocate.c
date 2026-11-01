#include "../../include/libgultra.h"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/ALBANK_S.H"
#include "COMMON/TRIPLE.H"
#include "TYPES.H"
#include "include_asm.h"
#include "COMMON/ALFXPARAM.H"

/* sndpallocate.c */
ALSndId alSndpAllocate(ALSndPlayer *pool, ALSound *owner) {
    s32 count = ((SoundPlayerSlotPool *)pool)->count;
    SoundPlayerSlot *slots = ((SoundPlayerSlotPool *)pool)->slots;

    if (count > 0) {
        s16 i = 0;
        s16 state = 5;
        f32 value = g_soundPlayerSlotInitialValue;
        u8 flags = 0x40;
        do {
        s16 index = i;
        SoundPlayerSlot *slot = (SoundPlayerSlot *)(index * sizeof(*slots) + (u32)slots);
        if (slot->owner == 0) {
            slot->owner = owner;
            slot->state = state;
            slot->timer = 0;
            slot->value = value;
            slot->flags = flags;
            slot->extra = 0;
            slot->amount = ((((ALSound *)(owner))->sampleVolume * 0x7FFF) / 127);
            return index;
        }
        i++;
        } while ((s16)i < ((SoundPlayerSlotPool *)pool)->count);
    }
    return -1;
}

/* ROM-grounded data: src/g_alSndpAllocateConstantWords_Sndplayer.c */
const float g_alSndpAllocateConstantWords[1] = {
    1.0f,
};

#if defined(VERSION_EU_X)
unsigned int k_SndplayerEncodedWordsBlock5[3] = {
    0xFFFF0000, 0x06A503E8, 0x06A601F4,
};
#endif

#if defined(VERSION_EU)
extern char g_Playerai_ApplyLinkedProjectileStatusAddressEu[];
void *k_SndplayerEncodedWordsBlock3[3] = {
    (void *)(g_Playerai_ApplyLinkedProjectileStatusAddressEu + 2276), (void *)(g_Playerai_ApplyLinkedProjectileStatusAddressEu + 2344), (void *)(g_Playerai_ApplyLinkedProjectileStatusAddressEu + 2276),
};
#endif

#if defined(VERSION_DE)
extern char Seqplayer_ProcessSequenceEvents_Address[];
void *k_SndplayerEncodedWordsBlock2[3] = {
    (void *)(Seqplayer_ProcessSequenceEvents_Address + 9140), (void *)(Seqplayer_ProcessSequenceEvents_Address + 9252), (void *)(Seqplayer_ProcessSequenceEvents_Address + 9484),
};
#endif

/* SNDPLAYER.CPP */
#if defined(VERSION_US)
char s_SndplayerCCameraPoolText[12] =
    "\015CCameraPool";
#endif
