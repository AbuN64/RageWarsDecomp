#ifndef COMMON_SOUNDVOICEPOOL_H
#define COMMON_SOUNDVOICEPOOL_H
#include "types.h"
#include "Common/sharedplayer.h"
#include "Common/runtime_declarations.h"
#include "Common/resident_event_handler.h"
/* Sound voices move between the available and playing lists. */
typedef struct SoundVoicePool {
    IntrusiveList available;
    IntrusiveList playing;
    s32 state;
} SoundVoicePool;

struct SongHeader;







extern float g_dialogPlaybackTimingConstants;

extern int g_lastPausedPoolSoundHandle;



struct CLoopingSoundData_t;
struct CLoopingSoundData_t {
    s32 previous;
    struct CLoopingSoundData_t *next;
    s32 value;
    s32 state;
    CVector3 m_vSoundPos; /* 0x10: sound source in world coordinates */
    void *m_vSoundPosPtr; /* 0x1C */
};

struct CLoopingSoundData_t;

extern const float g_dialogTempoScale;





struct Track;
typedef struct Track Track;



extern void SoundVoicePool_ResetNodeNoOp(void);

extern int g_lastStoppedPoolSoundHandle;


struct Resource;
typedef struct Resource Resource;


struct BankAudioStartDialogGroup;
struct BankAudioStartDialogGroup {
    char pad0[0x2B60];
    s32 table;
    s32 count;
};

struct BankAudioStartDialogGroup;
struct DialogGroupPlayer;



extern const double g_dialogUnsignedTimeCorrection;




struct AudioVoiceControlSlotView;

struct AudioPlaybackContextView;
typedef struct AudioPlaybackContextView AudioPlaybackContextView;





struct SongHeader;
typedef struct SongHeader SongHeader;

struct Bank;
struct Bank {
    char pad0[0x2B50];
    void *songs;
};

struct DialogPlaybackPlayer;

extern int g_lastStartedPoolSoundHandle;

struct Resource;
struct Resource {
    s32 baseVolume;
    u16 durationHighWord;
};

struct DialogGroupPlayer;
typedef struct DialogGroupPlayer DialogGroupPlayer;

struct AudioPlaybackContextView;
struct AudioPlaybackContextView {
    char pad[0x2B50];
    s32 songs;
    char p54[12];
    s32 resourceIndexTable;
    s32 resourceIndexCount;
    char p68[60];
    f32 volumePercent;
    char pa8[16];
    s32 musicAttenuated;
};

struct QueueRec;
typedef struct QueueRec QueueRec;

extern void SoundVoicePool_ResetNode(void *cLoopingSoundData);

struct CLoopingSoundData_t;
typedef struct CLoopingSoundData_t CLoopingSoundData;

struct QueueRec;
struct QueueRec {
    void *sequence;
    s32 head;
    u8 kind;
    s32 tail;
};

struct BankAudioStartDialogGroup;
typedef struct BankAudioStartDialogGroup BankAudioStartDialogGroup;




extern int g_lastResumedPoolSoundHandle;

struct AudioPlaybackContextView;
struct IntPair;
struct Track;
struct Track {
    struct AudioPlaybackContextView *context;
    s32 sequenceLoaded;
    struct IntPair *sequenceTable;
    ALCMidiHdr *midiHeader;
    struct ALCSeq_s *sequence;
    s32 sequencePlayer;
    s32 playbackState;
    s32 playbackFlags;
    s32 fadeStartVolume;
    s32 baseVolume;
    s32 requestedSequence;
    f32 currentVolume;
    f32 fadeDuration;
    f32 fadeStep;
    s32 gainOverride;
    f32 overrideGain;
    f32 fadeResetValue; /* fade reset value */
};











struct DialogPlaybackPlayer;
typedef struct DialogPlaybackPlayer DialogPlaybackPlayer;




struct AudioHeapD844 {
    u8 *start;
    u8 *cursor;
    u32 size;
};
struct AudioRootD844 {
    char pad0[0x1DA8];
    struct AudioHeapD844 heap;
};
#endif
