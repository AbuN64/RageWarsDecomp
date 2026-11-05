#include "Common/format.h"
#include "Common/ospihandle_s.h"
#include "Common/runtime_declarations.h"
#include "Common/resident_event_handler.h"
#include "data_overlay_layouts.h"
#include "types.h"
#include "include_asm.h"
#include "Common/osviscale.h"
#include "Data/Overlays/Weaponslot/Linktables/vi_data.h"
#include "Data/Overlays/Weaponslot/linktables_addresses.h"

/* GAMECORE_WRITEPERIPHERALHANDLEWORD_DATA.CPP */
#if !(defined(VERSION_US_REV1))
#if defined(VERSION_DE)
extern struct {
    void * g_peripheralDomainHandles[2];
    u8 retainedFloatWords[8];
} g_gamecoreWriteperipheralhandlewordRecord __attribute__((aligned(2)));
typedef char g_gamecoreWriteperipheralhandlewordRecordSizeCheck[
    (sizeof(g_gamecoreWriteperipheralhandlewordRecord) == 16) ? 1 : -1];
#endif
#if defined(VERSION_EU)
extern struct {
    void * g_peripheralDomainHandles[2];
    u8 retainedHiveText[8];
} g_gamecoreWriteperipheralhandlewordRecord __attribute__((aligned(2)));
typedef char g_gamecoreWriteperipheralhandlewordRecordSizeCheck[
    (sizeof(g_gamecoreWriteperipheralhandlewordRecord) == 16) ? 1 : -1];
#endif
#if defined(VERSION_EU_X)
extern struct {
    void * g_peripheralDomainHandles[2];
    u8 retainedFlagWords[8];
} g_gamecoreWriteperipheralhandlewordRecord __attribute__((aligned(2)));
typedef char g_gamecoreWriteperipheralhandlewordRecordSizeCheck[
    (sizeof(g_gamecoreWriteperipheralhandlewordRecord) == 16) ? 1 : -1];
#endif
#if defined(VERSION_US)
extern struct {
    void * g_peripheralDomainHandles[2];
    u8 retainedRecordWords[8];
} g_gamecoreWriteperipheralhandlewordRecord __attribute__((aligned(2)));
typedef char g_gamecoreWriteperipheralhandlewordRecordSizeCheck[
    (sizeof(g_gamecoreWriteperipheralhandlewordRecord) == 16) ? 1 : -1];
#endif
#endif

#if defined(VERSION_US_REV1)
void * g_gamecoreWriteperipheralhandlewordDataAddressWords[2] = {
    (void *)&g_diskPiHandle, (void *)&g_diskPeripheralHandle,
};
#endif

/* CREATE_DATA.CPP */
#if defined(VERSION_DE)
extern s32 g_peripheralAccessQueueInitialized;
#endif
#if defined(VERSION_EU)
extern s32 g_peripheralAccessQueueInitialized;
#endif
#if defined(VERSION_EU_X)
extern s32 g_peripheralAccessQueueInitialized;
#endif
#if defined(VERSION_US)
extern s32 g_peripheralAccessQueueInitialized;
#endif
#if defined(VERSION_US_REV1)
s32 g_peripheralAccessQueueInitialized = 0;
#endif

#if defined(VERSION_US)
extern char g_createDataTextFragment_us[28];
#endif

#if defined(VERSION_EU_X)
extern struct {
    u8 retainedOffsetPrefixWords[12];
    s32 g_serialInterfaceAccessQueueInitialized;
    u8 retainedOffsetSuffixWords[12];
} g_createDataOffsetTable_eu_x __attribute__((aligned(2)));
typedef char g_createDataOffsetTable_eu_xSizeCheck[(sizeof(g_createDataOffsetTable_eu_x) == 28) ? 1 : -1];
#endif

#if defined(VERSION_EU)
extern char g_createDataTextFragment_eu[28];
#endif

#if defined(VERSION_DE)
extern float g_createDataUnitRangeWords_de[7];
#endif

/* VI_DATA.CPP */
#if defined(VERSION_DE)
extern __OSViContext g_viDataZeroWords[2];
#endif
#if defined(VERSION_EU)
extern __OSViContext g_viDataZeroWords[2];
#endif
#if defined(VERSION_EU_X)
extern __OSViContext g_viDataZeroWords[2];
#endif
#if defined(VERSION_US)
extern __OSViContext g_viDataZeroWords[2];
#endif
#if defined(VERSION_US_REV1)
__OSViContext g_viDataZeroWords[2] = {
    { 0 }, { 0 }
};
#endif

/* OSVIGETCURRENTFRAMEBUFFER_DATA.CPP */
#if !(defined(VERSION_US_REV1))
#if defined(VERSION_DE)
extern __OSViContext * g_osViGetCurrentFramebufferPointers[4];
#endif
#if defined(VERSION_EU)
extern struct {
    __OSViContext * __osViCurr;
    __OSViContext * __osViNext;
    u8 retainedPrimageText[8];
} g_osViGetCurrentFramebufferPointers __attribute__((aligned(4)));
typedef char g_osViGetCurrentFramebufferPointersSizeCheck[(sizeof(g_osViGetCurrentFramebufferPointers) == 16) ? 1 : -1];
#endif
#if defined(VERSION_EU_X)
extern struct {
    __OSViContext * __osViCurr;
    __OSViContext * __osViNext;
    u8 retainedRecordWords[8];
} g_osViGetCurrentFramebufferPointers __attribute__((aligned(4)));
typedef char g_osViGetCurrentFramebufferPointersSizeCheck[(sizeof(g_osViGetCurrentFramebufferPointers) == 16) ? 1 : -1];
#endif
#if defined(VERSION_US)
extern struct {
    __OSViContext * __osViCurr;
    __OSViContext * __osViNext;
    u8 retainedFireboText[8];
} g_osViGetCurrentFramebufferPointers __attribute__((aligned(4)));
typedef char g_osViGetCurrentFramebufferPointersSizeCheck[(sizeof(g_osViGetCurrentFramebufferPointers) == 16) ? 1 : -1];
#endif
#endif

#if defined(VERSION_US_REV1)
struct {
    __OSViContext * __osViCurr;
    __OSViContext * __osViNext;
} g_osvigetcurrentframebufferDataAddressWords __attribute__((aligned(4))) = {
    (void *)&g_viDataZeroWords,
    (void *)&g_viDataZeroWords[1]
};
typedef char g_osvigetcurrentframebufferDataAddressWordsSizeCheck[
    (sizeof(g_osvigetcurrentframebufferDataAddressWords) == 8) ? 1 : -1];
#endif

/* VIMGR_DATA.CPP */
#if defined(VERSION_DE)
extern struct {
    VideoDeviceManager manager;
    u32 retainedVideoBurstWord;
    OSViMode modes[44];
    struct { u8 type; OSViCommonRegs common; OSViFieldRegs even; u32 oddOrigin; } lastMode;
} g_vimgrLinkTableWords_de __attribute__((aligned(4)));
#endif

/* K_OVERLAYSSEVENLINKTABLESCONSTANTWORDS.CPP */
#if defined(VERSION_DE)
const unsigned int k_linktablesLeadConstantWord[1] = {
    0x02000800,
};

struct {
    u8 retainedRecordWords[12];
} k_linktablesRetainedRecordBytes __attribute__((aligned(4))) = {
    { 0x00, 0x25, 0x01, 0xFF, 0x00, 0x0E, 0x02, 0x04, 0x00, 0x00, 0x00, 0x02 }
};
#endif

/* OSAISETFREQUENCY_DATA.CPP */
#if defined(VERSION_DE)
s32 g_audioClockRate = 48681812;
#endif
#if defined(VERSION_EU)
s32 g_audioClockRate = 48681812;
#endif
#if defined(VERSION_EU_X)
s32 g_audioClockRate = 48681812;
#endif
#if defined(VERSION_US)
extern s32 g_audioClockRate;
#endif
#if defined(VERSION_US_REV1)
s32 g_audioClockRate = 48681812;
#endif

/* AUDIO_ABORTDISKTRANSFER_DATA.CPP */
#if defined(VERSION_DE)
s32 g_audioAbortdisktransferDataConstantWords = 4194049;
#endif
#if defined(VERSION_EU)
s32 g_audioAbortdisktransferDataConstantWords = 4194049;
#endif
#if defined(VERSION_EU_X)
s32 g_audioAbortdisktransferDataConstantWords = 4194049;
#endif
#if defined(VERSION_US)
extern s32 g_audioAbortdisktransferDataConstantWords;
#endif
#if defined(VERSION_US_REV1)
s32 g_audioAbortdisktransferDataConstantWords = 4194049;
#endif

#if defined(VERSION_US)
extern char s_audioRetainedTextFragment_us[4] __attribute__((aligned(4)));
#endif

#if defined(VERSION_EU)
void * g_audioDiskTransferLinkTableEntryPointer_eu[1] = {
    (void *)g_audioDiskTransferLinkTable.empty
};
#endif

#if defined(VERSION_DE)
void * g_osAiSetFrequencyConstantWordsPointer_de[1] = {
    (void *)&g_audioClockRate
};
#endif

/* CREATEMESGQUEUE_DATA.CPP */
#if !(defined(VERSION_US_REV1))
#if defined(VERSION_DE) || defined(VERSION_EU) || defined(VERSION_EU_X)
#if defined(VERSION_DE)
struct {
    void * next;
    s32 priority;
} g_createmesgqueueRecord __attribute__((aligned(4))) = {
    0,
    -1
};
typedef char g_createmesgqueueRecordSizeCheck[(sizeof(g_createmesgqueueRecord) == 8) ? 1 : -1];
#endif
#if defined(VERSION_EU)
struct {
    void * next;
    s32 priority;
} g_createmesgqueueRecord __attribute__((aligned(4))) = {
    0,
    -1
};
typedef char g_createmesgqueueRecordSizeCheck[(sizeof(g_createmesgqueueRecord) == 8) ? 1 : -1];
#endif
#if defined(VERSION_EU_X)
struct {
    void * next;
    s32 priority;
} g_createmesgqueueRecord __attribute__((aligned(4))) = {
    0,
    -1
};
typedef char g_createmesgqueueRecordSizeCheck[(sizeof(g_createmesgqueueRecord) == 8) ? 1 : -1];
#endif
#endif
#if defined(VERSION_US)
extern struct {
    void * next;
    s32 priority;
    void * runQueue;
} g_createmesgqueueRecord __attribute__((aligned(4)));
typedef char g_createmesgqueueRecordSizeCheck[(sizeof(g_createmesgqueueRecord) == 12) ? 1 : -1];
#endif
#endif

#if defined(VERSION_US)
extern void * __osActiveQueue_CreatemesgqueueData[1];
#endif

#if defined(VERSION_US_REV1)
struct {
    void * next;
    s32 priority;
    void * runQueue;
    void * activeQueue;
} g_createmesgqueueDataConstantWords __attribute__((aligned(4))) = {
    0,
    -1,
    (void *)&__osThreadTail,
    (void *)&__osThreadTail
};
typedef char g_createmesgqueueDataConstantWordsSizeCheck[(sizeof(g_createmesgqueueDataConstantWords) == 16) ? 1 : -1];
#endif

/* S_FXDEATHNAMEFRAGMENTS_US.CPP */
#if defined(VERSION_US)
char s_fxDeathNameFragments_us[56] =
    "X_DEATH_\200\024{\250D_LAUGHequ\004.\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
    "\000\000\000\000\000FX_DEATH_GUA";
#endif

/* AUDIO_PULLENVELOPESUBFRAME_DATA.CPP */
#if defined(VERSION_US_REV1)
extern s16 g_audioEqualPowerPanTable[128];
#endif

/* G_OVERLAYSSEVENLINKTABLESCONSTANTWORDS.CPP */
#if defined(VERSION_US_REV1)
struct {
    u8 retainedRecordWords[12];
} g_weaponSlotLinktablesConstantWords __attribute__((aligned(4))) = {
    { 0x80, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x08, 0x00, 0x0C, 0x00, 0x12 }
};
#endif

/* G_OVERLAYSEVENOFFSETHALFWORDS.CPP */
#if defined(VERSION_US_REV1)
unsigned short g_weaponSlotOffsetHalfwords[6] __attribute__((aligned(4))) = { 0x002C, 0x0035, 0x003F, 0x004B, 0x0059, 0x0069 };
#endif
