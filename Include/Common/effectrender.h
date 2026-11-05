#ifndef COMMON_EFFECTRENDER_H
#define COMMON_EFFECTRENDER_H
#include "Frontend/frontend.h"
#include "Engine/particle.h"
#include "Ovlgame/ovlgame_address_symbols.h"
#include "Common/sharedplayer.h"
extern float g_triggerSoundWeightEu;
extern float g_roundTransitionTimerDe;
extern float g_creditsNextLineDelayEu;
extern double g_longLongHighWordUnsignedBias;
extern double g_longLongHighWordHalfwordScale;
extern double g_longLongLowWordUnsignedBias;
extern void * g_introTextLinesByLanguage[];
extern int g_forceMarkerRemovedTextEuropean[];
extern int g_forceMarkerAttractTextEuropean[];
extern int g_forceMarkerRepulseTextEuropean[];
extern u8 *g_slotRankNamePointers_Symbiont[];
extern u8 *g_characterNamesLocalized[];
extern char *g_bastilleNameLocalized[];
extern char *g_symbiontNameLocalized[];
extern char *g_talSetRaptorMantidMitesNamesLocalized[];
extern char *g_resultsRoundSingularFormatLocalized[];
extern char *g_resultsRoundsPluralFormatLocalized[];
extern char *g_resultsRoundsControllerModeFormatLocalized[];
extern char *g_resultsLapSingularFormatLocalized[];
extern char *g_resultsLapsPluralFormatLocalized[];
extern char *g_resultsLapsControllerModeFormatLocalized[];
extern char *g_resultsSingleLapSingularFormatLocalized[];
extern char *g_resultsSingleLapsPluralFormatLocalized[];
extern char *g_resultsGoalSingularFormatLocalized[];
extern char *g_resultsGoalsPluralFormatLocalized[];
extern char *g_resultsTimeLimitFormatLocalized[];
extern char *g_resultsMinuteSecondsSingularFormatLocalized[];
extern char *g_resultsMinutesSecondsPluralFormatLocalized[];
extern char *g_resultsMinuteSingularFormatLocalized[];
extern char *g_resultsMinutesPluralFormatLocalized[];
extern char *g_resultsPlayerOrLivesSingularFormatLocalized[];
extern char *g_resultsLivesPluralFormatLocalized[];
extern char *g_resultsGoalLabelFormatLocalized[];
extern char *g_slotAchievementTextPointers_EveryManForThemselves[];
extern int g_resultsFragFestHeadingTranslations[];
extern int g_resultsTimeTrialHeadingTranslations[];
extern u8 *g_packedButtonOptionStepTextTableEu[];
#if defined(VERSION_EU_X)
#define PAK_RANK_LANGUAGES 3
#else
#define PAK_RANK_LANGUAGES 4
#endif
extern char *g_pakRankSizeTexts[12][PAK_RANK_LANGUAGES];
extern u8 *g_localizedPakStatusHeading[];
extern char *g_pakChannelLabelTexts_eu[];
extern char *g_pakStatusDefaultText[];
extern char *g_pakStatusAdonTexts[];
extern char *g_pakStatusFirebornTexts[];
extern char *g_pakStatusCampaignerTexts[];
extern char *g_pakStatusTelsetTexts[];
extern u8 *g_playerPartnerSuffixByLanguage[];
extern u8 *g_playerNamePrefixByLanguage[];
extern u8 *g_localizedPlayerNameSuffixes[];
extern u8 *g_playerNameSuffixByLanguage[];
extern u8 *g_volumeZeroValueLabels[];
extern u8 *g_musicPreviewValueText_eu[];
extern char **g_resultsRankTexts[];
extern int g_playerHitCounts[];
extern int g_playerCountedShots[];
/* Effect render defaults, copied as the complete 0x1C-byte record. */
extern struct CCollisionInfo2_t g_effectRenderDefaults;
extern int g_damageShieldSelection;
extern unsigned char g_damageShieldSelectionLowByte;
/* Effect direction vector: ROM callers copy the three words at +0/+4/+8. */
extern CVector3 g_particleSharedInitialDirection;
extern int g_playerMovementRuleMode;
extern struct AudioWork *g_audioFrameTasks[];
extern u32 g_audioSamplesPerFrame;
extern g_audioCommandBufferSamples;
extern int g_curvePredictorBitCount;
extern u8 *g_curvePredictorByteCursor;
extern int g_curveSampleBitCount_de;
extern u8 *g_curveSampleByteCursor;
extern void * g_sceneLightSources;
extern int g_skyLayerDescriptors;
extern int g_skyLayerDescriptorCount;
extern struct Shared_Particle *g_particleLinkedAttachmentEffect;
extern CVector3 g_spawnReferencePosition;
extern int g_cameraShakeEffectList;
extern int g_playerAlternateActionModifierEnabled;
extern int g_fragTagSelectionClearedFlag;
extern int g_playerRespawnHealth;
extern unsigned long long g_previousFrameSystemTime;
extern int g_frameTimingTicks;
extern int g_frontendEntryState;
extern struct Shared_MenuDefinition *g_screenDefaultFocus;
extern struct FftTables * g_audioTransformFftTable;
extern u8 *g_audioContextHeapBuffer;
extern int g_audioContextHeapBytes;
extern struct GlyphBuffer * g_textGlyphBuffer;
extern int g_textGlyphSpacing;
extern u32 g_encodedSelectedLevelIndex;
extern int k_encodedLevelIdJumpTable_de[];
#endif
