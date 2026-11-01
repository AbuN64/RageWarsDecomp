#ifndef COMMON_AUDIO_CONTEXT_H
#define COMMON_AUDIO_CONTEXT_H
#include "TYPES.H"
#include "COMMON/CARTRIDGEREADWORKER.H"
#include "COMMON/PARAMSRECAT8V3.H"
#include "COMMON/ALBANK_S.H"
struct GameplayCamera;
typedef struct GameAudioContext GameAudioContext;
struct GameAudioContext {
    char pad0[0x24];
    s32 maximumSoundCount;
    s32 eventCount;
    ALHeap *soundHeap;
    char pad30[0x7C - 0x30];
    ALBank *font; /* +0x7C: first bank in the relocated bank file */
    ALBankFile *resource;
    ALSndPlayer list[1]; /* +0x84, a single SDK sound player */
    s32 soundState; /* +0xD8, separately cleared before player construction */
    s16 handles[16]; /* +0xDC */
    u8 reservedFC[6];
    s16 selectedHandle; /* +0x102 */
    s32 frame; /* 0x104 */
    s32 soundCounter; /* +0x108 */
    s32 playIdCounter; /* +0x10C: recursive-lock protected playback id */
    MenuRules lock;
    s32 lastInstrument; /* +0x130: previous randomized variant */
    s32 track; /* 0x134 */
    char view[0x1D64 - 0x138];
    char panel[0x1D6C - 0x1D64];
    s32 soundTable;
    char pad1D70[0x1DA8 - 0x1D70];
    ALHeap frames[1]; /* +0x1DA8; probe 20261019T012542972565Z */
    struct GameAudioContext *menu[1]; /* +0x1DB8: voice pool owner */
    Voice voices[17]; /* 0x1DBC */
    void *soundData; /* +0x2B48 */
    s32 *instrumentIndex;
    void *sequenceIndex;
    s32 instrumentCount;
    s32 *instrumentData;
    s32 *envelopeData;
    s32 *sequenceData;
    s32 sequenceCount;
    u8 reserved2B68[8];
    void *table2B70;
    void *table2B74;
    void *table2B78;
    s32 tableCount2B7C, tableCount2B80, tableCount2B84;
    u8 *selectedEntry; /* +0x2B88: section 0 of the playing variant (gain range, Channel_InitializeVoiceMix) */
    s16 selectedSound; /* +0x2B8C: sound-bank entry being started, -1 idle */
    char pad2B8E[2];
    s32 selectedOwner; /* +0x2B90: owner id while its voices start, -1 otherwise */
    u8 randomPan; /* +0x2B94: random 0..127 pan of the last sound effect (0x40 centre) */
    char pad2B95[3];
    struct GameplayCamera *listenerCamera; /* listener, Channel_InitializeVoiceMix */
    s32 effectMixOffset;
    f32 red;
    f32 green;
    f32 blue;
    s32 voiceMixValue;
    s32 spatialPanMode;
    s32 spatialAudioEnabled;
    s32 dialogEnabled;
    f32 alpha;
    char dialog[1];
};
/* The game's audio context: SoundElement_InitializeContext initialises it through Sound_InitializeContext. */
extern struct GameAudioContext g_soundElementContext;

#endif
