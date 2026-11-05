#include "Data/rom_callback_word.h"
#include "Common/resident_event_handler.h"
#ifndef COMMON_RUNTIME_DECLARATIONS_H
#define COMMON_RUNTIME_DECLARATIONS_H
#include "platform_sdk.h"
extern OSDevMgr __osPiDevMgr;
#include "Engine/folded_constants.h"
#include "Common/small_records.h"
#include "Frontend/frontend.h"
#include "Data/Overlays/Credits/objectdata_addresses.h"
#include "Engine/cheats.h"
#include "Engine/volume.h"
#include "Frontend/frontend_address_symbols.h"
#include "Camera/camera_address_symbols.h"
#include "Common/gameplay_camera.h"
#include <platform_sdk.h>
#include "Engine/sched.h"
#include "Common/Lone/particle_pitch_matrix_scratch.h"
#include "Common/Lone/screen_message_allocation_label.h"
#include "Common/Lone/frontend_viewport_width.h"
#include "Common/Lone/audio_clock_rate.h"
#include "Common/particle_lighting.h"
#include "Common/level_actor.h"
#include "types.h"
#include "Frontend/screen.h"
#include "Common/session_state.h"


#include "Common/widget_tree.h"
#include "Common/ospihandle_s.h"
#include "Common/sharedplayer.h"
#include "Common/vector4f.h"
#include "Common/aiprofile.h"
#include "Common/multiplayeroptions.h"
#include "Common/loadout.h"
#include "Common/virtual_pager.h"
#include "Common/group.h"
#include "Common/object_instance_transform_and_render_views.h"
#include "Common/manager.h"
#include "Common/cartridgereadworker.h"
#include "Common/audio_context.h"
#include "Common/audio_voice_slots.h"
#include "Common/soundvoicepool.h"
#include "Common/lightdata.h"
#include "Common/geometry_blend_and_instance_views.h"
#include "Common/mtx.h"
#include "Common/particle_attachment_and_owner_views.h"
#include "Common/colorentry.h"
#include "Common/worldsortentry.h"
#include "Common/results.h"
#include "Common/round_session.h"
#include "Common/menu_screen_elements.h"
#include "Common/hud_effects.h"
#include "Common/albank_s.h"
#include "Common/sequence_timing.h"
#include "Common/alparam_s.h"
#include "Common/audio_effect_chain.h"
#include "Common/osviscale.h"
#include "Common/ctx.h"
#include "Common/audio_loaddecodedsamples.h"
#include "Common/cheatcode.h"
#include "Common/note_state.h"
#include "Common/frontend_video_mode.h"
#include "Common/archive_chunk_images.h"
#include "Common/texture.h"
#include "Common/label.h"
#include "Common/characterselectionroot.h"
#include "Common/shared_particleinstance.h"
#include "Common/menu_initializeoptionsscene.h"
#include "Common/weapon_unlock_presets.h"
#include "Common/resultsoptionsscreen.h"
#include "Common/match_settings.h"
#include "Common/menu_model_preview.h"
#include "Common/player_item_inventory.h"
#include "Common/objb.h"
struct Box;
struct CharacterScreenCell;
struct CheatCode;
struct Clip;
struct ColorEntry;
struct ControllerInitStatusBytes;
struct Ctx;
struct Entry190;
struct Extra;
struct FftTables;
struct FieldRow;
struct FileHeader;
struct GameState;
struct GeometryModelInstanceEntry;
struct IntrusiveList;
struct MarkerItemMenuRestoreBootMemory;
struct MenuPointerEntry;
struct NodeGeometryGroupModelInstances;
struct Preset;
struct QuadN64EngDrawNumericWidgetChildren;
struct QueueRec;
struct ScalarFloatView;
struct SessionInitializeHandler;
struct Shield;
struct SineTable;
struct TextEntry;
struct Tuning;
struct UnitLight;
struct UnitVtx;
struct VideoDeviceManager;
struct ALFilter_s14_2;
struct ALSoundStatehandleEvent;
struct CMatrix4;
struct CMemEntry;
struct CacheEntry;
struct Clip;
struct CompactOptionsPageView;
struct EffectSlot;
struct Label;
struct ListScreenItem;
struct MenuWidget;
struct PakMenuSlot;
struct PakNotesMenuItem;
struct PatrolBot;
struct PatrolPlayer;
struct Record;
struct ResourcePageMapping;
struct Shared_AnimState;
struct Shared_PoseActor;
struct Shared_PoseModel;
struct Shared_PosePartEntry;
struct Shared_PosePartTable;
struct Shared_PoseWorld;
struct StateEntry;
struct StateFlags;
struct TextBoundsText;
extern s32 g_hudLivesMoverScript[];

extern char g_systemBootMarker[16]; /* Boot-preserved byte range, distinct from the 15-byte marker text. */
extern char g_pauseInventoryMenuResource[];



extern s64 g_schedulerGraphicsInitialStartTime;

extern s32 g_hudScoreMoverScript[];

extern s32 *g_frontendResourceChromaKeys;

extern char g_playerRespawnCountDialog_de;

extern s32 g_frontendWidgetStateChanged;



extern struct FftTables g_audioTransformBandTables;

extern f32 g_actorModelViewEffectConstants[];

extern char g_initialDialogBottomRowResource[];

#include "Menu/pak_prompt_lines.h"

extern char g_pickupTargetedDefinitions;

extern char g_menuOptionZachAttackCheatEnabledText[];


extern char g_playerOptionControlSideLeftText[];

extern s8 g_artsendTextureViewerState;

extern char g_mainCodeRegionByteCount;

extern char g_menuOptionUnlimitedAmmoDisabledText[];

extern struct MarkerItemMenuRestoreBootMemory s_systembootdoneText;


extern char g_pakChannelReadyMessage_SnapshotCheckstatusprompt[];



extern struct FieldRow g_gameOptionsActorKinds[];

extern const f64 k_xmathFractionIntegralLimit;

extern int *g_controllerPakProbeResource;


extern float g_unreferencedFloatTable_eu[];


extern s32 alResamplePull_Address;

extern char g_ribbonBlendResources[];


extern char g_menuOptionBigHeadModeDisabledText[];

extern char k_stdioCarriageReturn;



/* Profile rank titles, one row of language pointers per rank 0-19 (eu: 4 languages, eu-x: 3). */
#if defined(VERSION_EU_X)
extern char *g_profileRankLocalizedTitles[20][3];
#else
extern char *g_profileRankLocalizedTitles[20][4];
#endif



extern s32 *g_trackResourceDirectory;

extern s32 g_controllerReturnPending;


extern void * g_peripheralHandleList;


extern char Weapon_FireStateDrawCallbackEntry;

extern struct ScalarFloatView k_floorShakeVerticalBlend;

extern char g_pakPreviewKindLabelSelected[];

extern char *g_pakScannedChannelNumberLabelsByLanguage[];

extern s32 g_creditsReturnToFrontend;


extern struct FieldRow g_scenarioCatalogueEventActorKinds[];


extern WidgetEventHandler g_typedWidgetEventHandlers;

extern char g_menuOptionGouraudModeEnabledText[];

extern char g_triggeredMotionDispatchTable[];

extern u8 g_savedSecondaryMenuByteOptions[];


extern struct ScalarFloatView g_controllerEffectTimeRetreatScale;

extern struct ScalarFloatView g_directionVerticalThreshold;

extern char s_hudPlayerNameFormat[];


extern u8 g_controllerProfileModeBase;


extern s32 g_frameHeapMarkDepth;

extern const double g_cosinePiHigh;

extern char g_menuOptionBlackoutEnabledText[];


extern char s_staticLitGeometryResourceTag[];



extern char g_playerGroundViewAngleParameters;

extern char g_focusUnlockLabelText[];

extern s32 g_profileGameSpeedSelection;



extern u8 g_savedSecondaryMenuByteOptions[];

extern const f64 g_cosinePolynomialCoefficients[5];


extern f32 g_inactiveCollisionShapeShadowRadius;

extern const char g_fmtSpaceWidePaddedDec[];

extern char *g_playerSettingsSecondaryListLabels[];

extern char g_menuOptionBigHeadModeEnabledText[];

extern s32 g_movingCallbackRomEntry;

extern struct SessionInitializeHandler g_sessionInitializeHandlers[];

extern s32 g_frameHeapBufferIndex;

extern u64 g_videoManagerThreadStack[512];

extern u32 g_sourceBlueMask;

extern char alLoadParam_Address;

extern char g_actionDrawRomEntry;

extern u8 g_gameSettingsVolumeBytes[];

extern char g_fragTagOnLabelText[];

extern f32 g_sceneTransitionCinemaResponseDe;

extern s32 g_particleActorDefinition;


extern char g_pakConfirmationDefaultLabel[];

extern char g_actorMatrixPool;


extern u32 g_sourceRedMask;

extern u64 __osCurrentTime;


extern const f32 g_playerImpactHorizontalDamping;



extern MenuChoiceEventHandler g_settingsColumnEventHandlers;

extern s32 g_stdioResourceCloseRomEntry;



extern struct FieldRow g_alternatePlayerSettingsEventActorKinds[];

extern char g_pakAlternateReadyDialogResource[];

extern char g_sceneUnpackRequestSpare[];


extern f32 g_teamWheelScalePoolPrefix;

extern u32 g_cartridgeRomBaseAddress;

extern u8 g_savedPlayerModelLighting[];

extern s32 g_destinationColorIndex;


extern ALHeap *g_audioHeap;



extern s32 g_stdioResourceWriteRomEntry;

extern OSMesgQueue g_resourcePagerCompletionQueue;




extern f32 g_frameHeapLowUsageStats[3];

extern struct FieldRow g_equipmentEventIds[];

extern f32 g_playerSourceEffectDuration;

extern s32 alAuxBusParam_Address;

extern char *g_toggleListSetLabel[];

extern char g_SelectModalPromptLabelEmptyText[];

extern char Gastate_AnimationResourceCallbackEntry;


extern char g_geometryInitialScaleMatrix;


extern char g_triggeredUpdateRomEntry;

extern volatile s32 g_staticDataRegionStart;

extern s32 alMainBusParam_Address;

extern s32 g_menuMusicPreviewSelection;

extern s32 alAuxBusPull_Address;

extern char g_menuOptionGouraudModeDisabledText[];



extern unsigned char g_primitiveAlphaOverride;

extern s32 g_pakActionMenuActorKinds[];

extern char g_overlayCodeRegionByteCount;

extern s32 g_typedWidgetEventActorKinds;

extern s32 g_artsendTextureSelectionChanged;

extern char g_gameThread[];

extern const f64 k_xmathFloorIntegralLimit;

extern char g_staticJumpTableRegionStart;

extern s32 g_frontendViewportHeight;


extern int g_geometryViewEffect;

extern u32 g_sourceAlphaMask;



extern struct FieldRow g_gameOptionsEventKinds[];

extern s32 g_controllerReturnResourceRange;


extern s32 g_actionStateTransitionPending;

extern WidgetEventHandler g_overlaySlotEventHandlers;

extern int g_messageBufferAllocationLabelStorage;
extern char g_messageBufferAllocationLabel[];


extern u8 *g_destinationPixelIndexBuffer;

extern char g_menuOptionZachAttackCheatDisabledText[];
extern char g_menuOptionBigHandsFeetModeEnabledText[];

extern struct Entry190 g_characterHealthBonuses[];


extern char g_pakScannedChannelManagerHeading[];

extern unsigned char g_languageMenuAlternateTextTable;

extern f32 g_playerMatchCountdownSpriteOffsets[];

extern char g_bootstrapThread[];

extern char g_menuOptionJuansCheatEnabledText[];

extern f32 g_wrappedValueLowerConstants[2];

extern s32 g_playerSequenceCompletionPending;

extern s8 g_profileSlotSettingsPrimaryListSelection[];

extern s32 g_materialGroupCount;

extern s32 g_artsendPreviousFrameHoldCount;

extern s32 g_artsendTextureViewerFrameCount;

extern struct FieldRow g_playerCountEventIds[];

extern char g_Cartridge_RunReadWorkerPackedAddress;
extern char addrLow_Cartridge_RunReadWorker;


extern s32 g_playerTargetFacingDistanceLimits;


extern char g_cameraViewDisplayLists[2][0x30];

extern s32 g_playerStatisticsAccumulatedKills[][100];


extern char g_pakConfirmationActiveLabel[];


extern s32 g_characterSelectionEventIds[];




extern u8 g_debugLinkHandshakeControl;

extern f32 g_playerMatchCountdownStandardPosition[];

extern struct StateFlags *g_collisionProbePrimaryActor;





extern char *g_playerAimCandidateActors[];


extern struct FieldRow g_resultsActorEventIds[];


extern s32 g_controllerPakProbePending[];

extern s32 g_buttonWidgetEventIds;




extern s8 g_profileSlotResetFlags[];




extern s32 g_selectedLevelId;

extern u8 g_gameSettingsSplitScreenPreference;

extern s32 g_Cache_RunResourceLoadWorkerPackedAddress;
extern s32 addrLow_Cache_RunResourceLoadWorker;

extern unsigned char g_languageMenuTextTable[];


extern s32 g_schedulerFrameCountdown;

extern s32 __osBaseCounter;

extern float g_attachmentParticleLifetimeBase;



extern f32 k_screenMessageValueIncreaseMarker;

extern char g_controllerQueryStatus[];

extern s32 g_controllerPakProbeActive;


extern f32 g_playerMatchCountdownAlternatePosition[];

extern float g_attachmentParticleLifetimeScale;

extern char g_initialOpenDialogMenuResource[];


extern s16 g_audioTransformLeadingUpperBand;

extern char g_ownerModeOtherText[];

extern char g_pakStatusSecondaryLabel[];

extern struct FieldRow g_trialCatalogueEventIds[];

extern s32 g_overlaySlotEventActorKinds;

extern s32 g_controllerInitializationMessage;

extern char addrLow_Track_SolveSplineSecondDerivatives;

extern int g_cachedSurfaceNormal;

extern char g_modelEditorApplyToAllDisabledText[];

extern struct IntrusiveList g_resourcesByAddress;


extern s32 g_frameHeapsAllocated;


extern u8 g_debugLinkAuxiliaryControl;

extern char g_menuOptionPenAndInkModeEnabledText[];

#include "Common/audio_queues.h"
#include "Actor/actor.h"
#include "Ai/Nav/portal_dispatchactorbehavior_data.h"
#include "Constants/setup_updatenamecursor_data.h"

extern char g_playerMenuDialogRomResource[];

extern s32 g_sourceColorIndex;

extern int g_stdioResourceReadyCookie;

extern char g_profileModePlayedLevels[4][5];

extern int g_imageSwizzleEnabled;

extern const float g_sequenceSignedTickConversionLimit;



extern s16 *g_audioCommandBuffers[];


extern char g_scenarioCatalogueWidgetIds[];

extern const f32 g_playerImpactVerticalDamping;


extern s32 g_stdioResourceEndRomEntry;


extern char g_skyEffectProjectionMatrix;

extern char g_menuOptionAllSpecialObjectsEnabledText[];

extern char g_localPlayerSetupMenuResource[];

extern void System_CleanupThreadEntry(void);

#if defined(VERSION_EU_X)
extern struct RestsmpEventHandlerTablesLayout880 g_smpEventHandlerTables;
#elif defined(VERSION_EU)
extern struct RestsmpEventHandlerTablesLayout881 g_smpEventHandlerTables;
#else
extern s32 g_smpEventHandlerTables;
#endif

extern const char g_pakChannelDigitFormat[];

extern char g_pakChannelNotReadyDialog_SnapshotCheckstatusprompt[];


extern s32 g_motionTrackDecodeTranslation;

extern char g_pakAlternatePromptDefaultLabel[];

extern u8 g_sceneLightDirection[];






extern s32 g_frontendActiveVideoModeIndex;



extern const float g_sineNegativeRoundingBias;

extern s32 g_playerSequenceWindowEnabled;

extern struct FieldRow g_playModeEventIds[];


struct CGameDynamicLight_t;
extern struct CGameDynamicLight_t g_dynamicLightPool;

extern struct FieldRow g_profileResetEventActorKinds[];

extern struct Extra g_profileGameSpeedPreview;


#include "Common/audio_initialize.h"
extern struct AudioCacheEntry g_audioDmaCacheEntries[];

extern char g_damageDispatchTable[];

extern const double g_sineInversePi;

extern char g_damageHitRomEntry;

extern f32 g_playerDamageTimerConstants[2];

extern char g_geometryMaterialIntensityTexture;

extern f32 k_screenMessageValueDecreaseMarker;

extern u8 DEBUG_LINK_TRANSMIT_STATUS_BYTE;

extern char g_characterPreviewMenuRomResource[];


extern char g_audioDecodedSampleSlots[];

extern s32 g_introSelectionState;

extern u8 g_profileMilestoneCompletionBits[];


extern struct FieldRow g_alternatePlayerSettingsEventIds[];

#if defined(VERSION_US)
extern struct ResidentEventHandlerEntry g_pakProfileHandlerEvents[];
#else
extern struct FieldRow g_pakProfileHandlerEvents[];
#endif


extern const double g_cosinePiLow;

extern int g_frontendImageRecordValues[];

extern char g_pakControllerPortPrompts[4][0x24];

extern short g_ammoClassIconIds[];

extern s16 DEBUG_LINK_BLOCK_CONTROL_REGISTER;

extern const double g_cosineInversePi;


extern struct FieldRow g_playerSettingsEventActorKinds[];


extern struct Clip g_profilePlayerAnimationChoices[];

extern const double g_cosineRoundingHalf;

extern const float g_sequenceInitialOscillatorValue;

extern void *g_pakNoteLabelSlots[];


extern f32 g_frameHeapHighUsageStats[3];


extern char g_pakAlternateOperationHeadingLabel[];


extern const f64 k_xmathFractionIntegralBias;

extern const char s_animModelsIndexText[];

extern char g_schedulerThreadEntryAddress;

extern s32 g_fragTagSelectSoundVariant;

extern void *g_frontendResourceImagePool[];



extern u8 *g_sourcePixelIndexBuffer;

extern char g_pakDefaultPreviewActionLabel[];


extern char *g_playerOptionControlTypeArcadeText;


extern char g_pakChannelNumberFormat[];

extern const float g_lookAtHomogeneousScale;

extern s32 g_pakCancelStateWord;

extern f32 g_audioTransformZeros[];






extern const char s_headerText[];


extern u32 __osFinalrom;

extern const double g_sinePiLow;

extern char g_menuChoiceDisabledLabels[];



extern char g_redBloodScoreText[];



extern const f64 g_audioFrexpRestoreSignThreshold;





struct IntPair;
extern struct IntPair g_osEventMessageBindings[];


extern struct CacheResourceNode *g_pakLoadedNoteResourceHandle;

extern char g_modelEditorApplyToAllEnabledText[];

extern const char g_levelIndexText[];

extern void Frontend_DrawResultModelPreviewDe(char *);

extern int g_frontendActiveState;

extern float g_attachmentParticleEmissionThreshold;


extern void *g_depthImageBuffer;

extern const char s_animObjectIndexText[];



extern f32 g_materialCurrentStrengthScales[];

extern char *g_pakSaveMenuProfileChannelLabels[];

extern char g_SetN64_RunGameThreadPackedAddress[];
extern char addrLow_SetN64_RunGameThread[];

extern char g_simpleModelResourceCallbackAddress;

extern s32 g_stdioResourceSeekRomEntry;




extern s32 g_stdioResourceOpenRomEntry;



extern char *g_pakScannedChannelChoiceLabels[];

extern const f32 g_cosineLargeAngleZero;

extern u32 g_destinationRedMask;


extern f32 g_simpleObjectViewEffectRotationAndHeight;


extern u8 g_savedPlayerModelLighting[];

extern struct UnitLight g_pointLightBuffer[];


extern s32 g_controllerPakReinitializePending[];

extern s32 g_listButtonEventActorKinds;


extern char *g_currentDiskPeripheralHandle;

extern s32 g_menuBinaryChoice;

extern struct FieldRow g_nodePairMenuEventActorKinds[];

extern u8 g_controllerPakPreviewProfileName[];



extern u8 g_controllerReadStatusBytes[];


extern char *g_pakProfileLoadSnapshotChoiceLabels[];

extern struct FieldRow g_pauseMenuEventIds[];

extern s32 g_pagerStatisticBuffer[];



extern char g_volumeSettingsMenuResource[];

extern struct Texture *g_combineBoundImage;

extern const char g_simpModelsIndexText[];


extern struct FieldRow g_matchOptionsEventCodes[];

extern f32 g_platformCollisionHeightOffsets[];

extern const unsigned char s_virtualRegionText[15];


extern s32 g_frontendRenderStateInitialized;

extern const f32 g_cameraFrustumAngleConstants[];

extern const float g_reverbModulationWrapLimits;

extern u32 g_destinationBlueMask;



extern const f32 g_cameraFrustumHeightScale;

extern char g_initialDialogTopRowResource[];

extern f32 k_xmathAtanQuadrantOffsets[4];

extern struct FieldRow g_tabOptionsEventKinds[];

extern char g_menuOptionAllMapEnabledText[];

extern s32 g_profileSlotNameFormat;

extern f32 g_particleOwnerImpactRadiusAndStrength[];

extern float g_regionCachedEdgeDefaultUp;

extern void *g_pakSnapshotResourceHandle;

extern struct ScalarFloatView k_floorShakeHorizontalScale;


extern u16 g_audioTransformBandEnds[];


extern char g_menuOptionStickModeDisabledText[];

extern char g_collisionSurfaceExcludedFromTrace[];

extern f32 g_weaponWheelScalePoolPrefix;


extern char g_menuOptionFrootyStripesDisabledText[];

extern float g_scaledMatrixHomogeneousScale;


extern char g_controllerPakNotReadyDialogResource[];

extern u16 g_trialCatalogueStageIdLowHalves[];

extern const float g_perspectiveFloatHalfAngleScale;


extern struct ScalarFloatView g_playerDamageTimerFrameDefault;


extern s32 g_teamSelectedNoticesEu[4][4];

extern WidgetEventHandler g_listButtonEventHandlers;


extern u8 g_controllerPakPreviewName[];

extern s32 g_controllerSnapshotProfileValues[4];


extern f32 g_hudSpriteHorizontalOffsets[];

extern s32 g_frontendKeepCurrentVideoModeOnce;

extern unsigned char g_materialIntensityMaskTexture[];

extern s32 g_pakPreviewNameText;


extern char s_frontendResourceOpenMode;

extern struct ScalarFloatView g_simpleObjectScaleTransitionTarget;

extern f32 g_weaponChargeEntryCueAndRate[2];

extern u32 g_sourceGreenMask;

extern char g_actionEnterRomEntry;

extern s16 DEBUG_LINK_DATA_REGISTER;


extern s32 g_creditsSkipRequested;


extern char g_controllerAccessMessages[];


extern char g_ownerModePersonViewText[];

extern const char s_flyModeOffText[];


extern char g_deviceDrawRomEntry;

extern int g_spawnCallbackRomEntry;

extern s32 g_pakDefaultPreviewNameText;

extern f32 g_playerAnimatedSpriteScaleX;

extern f32 g_playerBaseAndEasyMovementFactors[];

extern struct FieldRow g_profileResetEventIds[];

extern s32 g_controllerInitializationQueue;




extern char g_Statinst_BuildLitGeometryResourceAddress;

extern s32 g_frontendCurrentVideoModeIndex;

extern u32 g_timerLastProcessorCount;

extern WidgetEventHandler g_extraOptionsEventCallbacks;

extern u32 g_displayListCapacityEu;



extern char s_menuByteOptionValueFormat[];



extern WidgetEventHandler g_sliderWidgetEventHandlers;

/* Pak operation labels: one word per language for each operation (columns 0..4) in each
   g_frontendResourceLoadStage state (row 0 the default, rows 1..4 states 0..3). */
#if defined(VERSION_EU)
#define PAK_OPERATION_LABEL_LANGUAGES 4
#elif defined(VERSION_EU_X)
#define PAK_OPERATION_LABEL_LANGUAGES 3
#else
#define PAK_OPERATION_LABEL_LANGUAGES 1
#endif
extern char g_pakOperationStateLabels[5][5][PAK_OPERATION_LABEL_LANGUAGES][4];

extern char g_scene_BuildPlacedInstancesEntry[];


extern int g_frontendScreenModeHiRezLabel;

extern s32 g_audioTransformInputStream;


extern f32 g_centsToPitchRatioConstants[];

extern f32 k_playerMenuSpriteScaleConstants;

extern u8 g_frontendSavedVideoModeIndex;


extern WidgetEventHandler g_optionsTransitionEventCallbacks;

extern f32 g_weaponEasedSpinFeedbackConstants[];

extern const f64 g_audioFrexpLowerLimit;

extern char g_modelEffectPool;




extern u64 g_schedulerThreadStack[];




extern f32 g_ribbonNodeTransformDecayConstants[];

extern char *g_pakSaveMenuNoteSlotChoiceLabels[];


extern s32 g_teamSelectedNotice[4];

extern u16 g_pagerPageCounters[];

extern WidgetEventHandler g_buttonWidgetEventHandlers;

extern struct FieldRow g_compactOptionsEventKinds[];





extern char g_playerFloatMovementParameters;

extern char g_pakSnapshotCapacityPromptEuX[];


extern int g_textureCacheResource;

extern unsigned char g_controllerPakEnabledBytes[];



extern s32 g_primitiveRenderFlagSelectLowGroup;

extern f32 g_audioSampleTimeConstants[2];


/* Character IDs: movement also reads the third word at g_fragTagModelId. */
extern s32 g_playerSpecialModelIds[];


extern s32 g_frontendImageRecordFlags[][13];
extern char g_menuLetterJText[];
extern char g_menuLetterNText[];

extern s32 g_optionsTransitionEventCodes[];

extern char *g_playerOptionStickHorizontalNormalText;

extern const double g_cosineRoundingSignBoundary;



extern s32 g_menuOptionInvincibilityEnabledText;

extern s32 g_overlaySlotEventIds;

extern char g_playerFloatViewAngleParameters;

extern f32 g_navigationFarthestDistanceAndArrivalLimits[];

extern struct TextEntry g_focusUnlockEntries[];

extern const char s_allocText[];

extern const char g_pakPaddedCountFormat[];


extern char g_playerOptionControlSideRightText[];


extern s32 g_numericWidgetEventIds;

extern struct FieldRow g_resultsEventKinds[];

extern s32 g_flickerWidgetEventActorKinds;

extern char g_playerModelResourceTag[];

extern struct ScalarFloatView g_playerDamageTimerFrameScale;

extern s32 g_campaignCompletionMenuEnabled;

extern struct Ctx g_piInterruptManager;

extern f32 g_playerJumpLandingHeightLimits[2];

extern char g_playerSwimViewAngleParameters;


extern char g_playerMenuStepFormatGerman[];

extern struct FieldRow g_soundOptionsEventKinds[];

extern struct QuadN64EngDrawNumericWidgetChildren g_osExceptionPreamble[];

extern s32 g_timerServiceCounter;

extern u8 g_gameSettingsModeFlags;

extern s32 alResampleParam_Address;

extern s32 g_pakNamePromptAccepted;


extern f32 k_MenuBlendUnitConstants[];

extern void * Libc_FormatStringOutputCallback(void * destination, const char * source, int byteCount);

extern unsigned short g_audioDecodedBlockCounter;

extern char g_musicPreviewMenuResource[];


extern char g_pakStatusPrimaryLabel[];

extern u8 g_controllerPakPreviewProfileFlags;

extern const f64 g_audioFrexpZero;

extern WidgetEventHandler g_frameAnimationEventHandlers;

extern char g_playerDeathDialogs[4][0x24];

// Packed low address of Playerai_UpdateStoredRunEndPlayer; it owns no data.
extern void addrLow_Playerai_UpdateStoredRunEndPlayer(void);


extern u16 g_pakProfileSavedWords[3];


extern struct UnitVtx g_playerDeathEffectVertices[];


extern u64 g_systemClockFrequency;


extern char *g_pakSaveMenuSnapshotChannelLabels[];

extern struct FieldRow g_titleButtonColumnEventIds[];



extern s64 g_schedulerRdpTaskStartTime;

extern s32 g_pakSnapshotNoControllerPromptUsRevision;

extern s32 g_artsendTextureViewerPaletteTable;


extern char g_controllerRumbleNodes[];

extern s32 g_materialInstanceCount;

extern char g_SelectModalPromptLabelStateOtherText[];

extern CVector3 k_turretUpDirection;


extern s32 g_schedulerRdpBufferSetState;

extern const float g_lookAtNormalizeAndFallbackConstants;

extern s32 g_pakAlternateNameSelected;


extern s32 g_destinationPixelOffset;

extern s32 g_pakSnapshotNoPakPromptUsRevision;

extern const double g_compressedMarkerDivisionUnsignedBias;

extern const char g_pakWriteScratchNoteName[];

extern u8 g_controllerLastCommand;

struct FrontendVideoModeParameters;
extern struct FrontendVideoModeParameters g_frontendDefaultVideoModes[];

extern u8 g_secondaryMenuByteOptions[];

extern f32 g_encodedTextCursorTiming[];



extern float g_audioResamplerFixedPointUnit;

extern const float g_perspectiveFloatNormalizationLimits;

extern struct NodeGeometryGroupModelInstances g_materialGroups[];

extern void *g_matchOptionLabelSlots[];

extern char __osThreadTail[];

extern char g_pakNoteIdRepairFailedDialogResource[];

extern char g_sceneResourceRequestSpareDe[];

extern char g_playerAirViewAngleParameters;


extern const f64 g_lowPassFixedPointScale;


extern int g_frontendControllerState;

extern struct FieldRow g_soundSliderEventIds[];

extern struct FieldRow g_settingsColumnEventKinds[];

extern s32 g_pakRecheckRequested;

extern char g_damageUpdateRomEntry;

extern s32 g_trialCatalogueNeighbors[3][1];

extern char g_nearestPlacedObjectResult;

extern const char g_audioCsplayerText[];

#include "Engine/scene_emac_text.h"



extern char g_actionUpdateRomEntry;

extern f32 k_xmathVectorAngleWrapConstants[2];



extern int g_frontendScreenModeHiRezLetterboxLabel;

extern s32 g_selectedProfileHealthOptionEnabled;

extern struct FieldRow g_settingsColumnEventIds[];

extern f32 g_audioRoundedSampleTimeConstants[2];



extern s32 g_musicPreviewMenuActive;

extern u8 g_debugLinkTransferControl;

extern f32 g_actorOffsetTransformConstants[];

struct ImageDescriptor;
extern struct ImageDescriptor *g_conversionSourceImage;

extern struct FieldRow g_soundOptionsEventIds[];







extern char g_pagerWorkerRomEntry[];

extern char g_pakNoteIdRepairSucceededDialogResource[];

extern unsigned int g_texturePaletteOverrideEnabled;

extern struct CheatCode g_encodedCheatDefinitions[];

extern s32 g_sourcePixelOffset;

extern const char g_gameObjectResetAnimInfoText[];


extern f32 k_xmathPositiveAngleWrapConstants[2];


extern s32 g_playerViewRenderingEnabled;

extern int *g_weaponIndexedValueTable[];

extern s32 g_playerSpawnSelector;

extern const f64 k_xmathFloorSignBoundary;

extern s32 g_frontendImageFormatTable[][13];

extern char g_pakOperationHeadingLabel[];


extern f32 k_cinemaFadeRequestValue_de;


extern s32 g_selectionMenuHandlerKinds;



extern s32 g_triggeredVariantDrawRomEntry;

extern s32 g_multiplayerItemRenderState;

extern s32 g_sliderTransitionEventActorKinds;

extern f32 g_frameHeapLowAllocationStatLowerLimit;

extern WidgetEventHandler g_overlaySlotEventHandlersUs;

#include "SCHED/osscremoveclient.H"

extern struct EffectSlot *g_effectPoolFreeHead;




extern char g_resourcePendingRequests;


extern char g_pakPreviewDifficultyEasyLabel[];

extern const char s_simpPartModelText[];

extern const float g_navigationObjectLinkDistanceLimits[];



extern s32 g_activeVoiceCount;

extern WidgetEventHandler g_numericWidgetEventHandlers;

extern int __osFaultedThread;

extern struct FieldRow g_resultsActorEventKinds[];




extern s32 g_gameSessionMode;


extern struct EffectSlot *g_effectPoolActiveHead;

extern char g_uiFormattedMessage[];

extern char *g_playerOptionAutoAimOnText;


extern u8 g_audioDmaBoundaryWorkaroundFlag[];

extern struct FieldRow g_profileResetEventIdsEu[];

extern char addrLow_Libsn_DisableInterrupts;


extern struct CVector3_t g_particleTertiaryContactPosition;

#include "libultra/audio/seqp.h"




extern char g_actionMotionDispatchTable;

extern u16 *g_frontendResourceScreenFlags;

extern char g_ownerNotificationEnabledLabels[];


extern s32 g_sliderWidgetEventIds;

extern f32 g_weaponReleaseSpinApproachRate;

extern s32 g_controllerSetupSaved;

extern s32 g_attractTimeoutEnabled;

extern struct FieldRow g_resultsEventIds[];


extern char g_playerMenuStepFormat[];

extern int g_cachedSurfaceNormalNode;

extern const f64 k_xmathCeilSignBoundary;

struct StateFlags;
extern struct StateFlags g_equipmentOptionWidgetIds[][19];

extern f32 g_playerOwnerHeightEffectTuning[];


extern struct SineTable g_actorMatrixWobbleSamples;

extern s32 g_secondStatusBarMoverScript;

extern s32 g_modelBatchPass;

extern char g_bloodColorGreenText[];

extern char g_promptActionHeadingDefault[];

extern const char g_longAndIntFormats[];


extern struct ScalarFloatView k_floorShakeHorizontalBlend;

extern struct ScalarFloatView k_floorShakeVerticalScale;



extern f32 k_nearbyPlayerBlastConstants[];

extern s32 g_trackResourceDirectoryKey;

extern s32 g_textBatchStyle;

extern u32 g_primaryDisplayListCapacity;

extern s32 g_pointLightBufferOffset;


extern char g_horizontalEdgeNormalizeScale;

extern s32 g_optionsTransitionActorKinds[];

extern void (*g_readSourceColor)(void);


#include "onscrn.h"

extern s32 g_frameHeapBufferBytes;



extern char g_pakAlternateActionLabel[];

extern char *g_profileRankTitles[];

extern s32 g_characterSelectionEventActorKinds[];

extern s32 g_matchSetupMenuResource;

extern char g_pakOperationDescriptionLabel[];


extern s32 *g_textureResourceSectionRoot;

extern const f64 g_sinePolynomialCoefficients[5];


extern char Weapon_FireStateEnterCallbackEntry[];

extern s32 g_modelBatchResourceCount;

struct ResourcePageMapping;
extern struct ResourcePageMapping g_pagerPageMappings[];

extern void (*g_writeDestinationIndex)(void);





extern struct FieldRow g_compactOptionsActorKinds[];

extern const char g_simpModelText[];

extern void System_VideoManagerThreadEntry(void *arg);




struct PlayerSettingsOptionRow;
extern struct PlayerSettingsOptionRow g_characterPortraitRecords[];

extern char g_menuOptionFrootyStripesEnabledText[];



extern float g_reverbDeltaScale;

extern OSViMode g_schedulerAlternateVideoMode;

extern f32 g_hiddenStaticObjectShadowRadius;

extern struct SharedMovement g_playerGroundMovementParameters;


extern s32 g_resourceSlotActivity[];

extern s32 g_controllerAudioThreadId;


extern struct CMemEntry *g_resourceCompactionEntries;

extern const char g_pakSingleSaveBlockName[];

extern s32 g_teamScoringEnabled;



extern const float g_sinePositiveRoundingBias;

extern char g_spawnActorDispatchTable[];


extern s32 g_pakSnapshotLowSpacePromptUsRevision;

extern u8 DEBUG_LINK_RECEIVE_STATUS_BYTE;


extern const float g_perspectiveFloatDepthAndRangeLimits;

extern u32 g_destinationGreenMask;

extern float g_trackSmoothInterpolationConstants;

extern s32 g_lifeRegenerationTrackRequest;

extern OSTask g_signalProcessorTaskCopy;



extern char g_pakActionLabel[];


extern char g_primaryRenderMicrocodeText;

extern s32 g_flickerWidgetEventIds;

extern f32 k_barrelEffectQuaternionValues[];

extern u8 g_particleSpriteViewMode;

extern f32 k_barrelSecondarySoundRandomMinimum;


extern struct FieldRow g_confirmationMenuEventIds[];

extern u8 DEBUG_LINK_BLOCK_STATUS_BYTE;

extern char alAdpcmPull_Address;



extern OSIoMesg g_videoTimerEvent;


extern s32 g_litGeometryResourceKeyFlags;


extern u8 g_playerSettingsRecords[];



extern char s_nodeAlternateFieldText[];



extern struct FieldRow g_trialOptionsEventKinds[];

extern s16 g_voiceAttenuationTable[];

extern f32 g_unreferencedFloatTable_de[];


extern char *g_playerOptionStickVerticalNormalText;

extern s16 DEBUG_LINK_MODE_REGISTER;

extern const f64 k_xmathFractionSignBoundary;

extern float g_regionUpQuaternionConstants[];

extern char g_primaryRenderMicrocodeData;

extern s32 g_pakAlternateOptionEnabled;




extern char g_movingMotionDispatchTable[];

extern char g_playerDefaultBehaviorTable;

extern s32 g_trialCatalogueNeighborZero[];

extern char g_initialDialogMiddleRowResource[];


extern s32 g_pointLightSavedBufferOffset;

extern s32 g_frontendArchiveResident;

extern struct FieldRow g_pakProfileHandlerKinds[];

extern s32 g_resultReplayPending;

extern s32 g_extraOptionsEventCodes[];

extern s32 g_frameHeapHighCursor;




extern s32 g_modelInstanceQueueCount;



extern float g_reverbRatioBase;

extern char **g_creditsLocalizedLines[];

struct StateFlags;
extern struct StateFlags g_equipmentSecondaryWidgetIds[][19];

extern u8 g_debugLinkModeControl;

extern s32 g_textClipBottom;


extern f32 g_actorAimBasisConstants[];

extern const char g_gameObjectAnimIndexText[];

extern void *g_pickupNavigationGoalList;


extern u16 g_gamePackedOptions;
extern u8 g_playerHudSpriteMode;

extern char g_actorBehaviorActionConfigs;

extern u8 g_worldSnapshotNoteData[];


extern char g_menuOptionAllWeaponsDisabledText[];

extern char g_pakPreviewKindLabelDefault[];


extern s32 alSaveParam_Address;



extern s32 g_textBatchCount;


extern s32 g_profilePrimaryMenuResource;

extern struct FieldRow g_soundSliderEventKinds[];

extern char g_pakStatusPromptAlternate[];

extern s32 g_artsendTextureViewerReservedWord;



extern struct CharacterScreenCell g_characterSelectionMenuOptionCells[][9];


extern u32 g_displayListCapacityUs;



extern f32 g_regionNormalDefaultUpY;


extern void (*g_writeDestinationColor)(void);

extern char *g_playerSettingsMixedText[];

extern s32 g_pakDialogEventIds;


extern s32 g_debugLinkTransferFailed;

struct EntryFrontendRefreshTrialCharacterPreview;
typedef struct EntryFrontendRefreshTrialCharacterPreview EntryFrontendRefreshTrialCharacterPreview;

extern s32 g_sliderTransitionEventIds;



extern const float g_sequenceFallbackOscillatorValue;


extern int g_artsendTextureResetWordB;

extern s32 g_regionEdgeDefaultUpZ;

extern s32 g_expansionMemoryIntroEnabled;


extern s32 g_sliderWidgetEventActorKinds;

extern char g_difficultyHardText[];

extern char g_menuOptionStickModeEnabledText[];

extern struct ScalarFloatView g_controllerEffectTimeAdvanceScale;

extern char g_pauseOptionsMenuResource_eu_x[];

extern s32 g_splashImageTextureEffectState;


extern s32 g_menuElementLoadCount;

extern f32 g_playerReserveBounds_de[2];

extern struct FieldRow g_pauseMenuEventActorKinds[];

extern f32 k_spawnActionMinimumDelay;

extern struct GameState g_gameStateBlock;

extern u64 g_schedulerAudioTaskStartTime;

extern char g_resourceCompletionRequests;

extern s32 g_selectionMessageStage;


extern char g_menuOptionBlackoutDisabledText[];

extern char g_sceneEffectPool;

extern u32 g_pagerSlotAgeHead;

extern s32 g_sound_GetSampleDmaWindowAddressEntry;



extern const char g_simpPartModelsIndexText[];

extern struct QueueRec g_dialogDecodeStreamRecord[];

extern s32 g_barrelSecondaryFlagSoundTable[];

struct ScalarPair;
extern struct ScalarPair g_fastHealthRegenerationTuning;

extern s32 g_creditsCurrentLine;

extern const char g_pakReadScratchNoteName[];

extern char g_weaponSelectNormalText[];


extern s32 g_numericWidgetEventActorKinds;

struct ScalarPair;
extern struct ScalarPair g_movementHealthRegenerationTuning;

extern const double g_sinePiHigh;

extern char g_profileStatisticsNumberFormat[];

extern WidgetEventHandler g_characterSelectionEventHandlers;

extern char g_simpleObjectModelResourceTagData;

extern const double g_cosineQuadrantOffset;


extern s32 g_textClipTop;

extern const f64 k_xmathCeilRoundUpUnit;




extern WidgetEventHandler g_flickerWidgetEventHandlers;




extern char *g_playerSettingsPrimaryListLabels[];



extern struct IntrusiveList g_sceneEffectSpawnList;

extern WidgetEventHandler g_pakActionMenuEventHandlers;

extern u8 g_soundEffectsVolumeOption_PakFormatvolumeslotone;

extern s8 g_pakPreviewNoteType;


extern const f64 k_xmathCeilIntegralLimit;

extern char s_ammoPickupPluralSuffix[];


extern s32 g_resourceHashBucketCount;

extern char g_triggeredTransformRomEntry;


extern char g_pakAlternateOperationDescriptionLabel[];

extern struct EffectSlot *g_effectPoolActiveTail;

extern f32 g_hudSpriteVerticalOffsets[];


extern s32 g_buttonWidgetEventActorKinds;




extern s32 g_initialMatchStartPending;


extern WidgetEventHandler g_overlaySlotEventHandlersEuX;

extern s32 g_regionNormalDefaultUpZ;

extern f32 g_frameHeapHighAllocationStatLowerLimit;

extern char g_menuOptionJuansCheatDisabledText[];

extern struct FieldRow g_tabOptionsActorKinds[];


extern u8 g_connectedControllerProfileCount;

extern s32 g_menuSavedAudioSelection;

#include "Common/memory_stream_buffer.h"

extern char g_actionEnterDispatchTable[];

extern OSPiHandle g_diskPeripheralHandle;

extern char s_actorAnimationResourceTag;

extern const f64 k_xmathFloorIntegralBias;



extern const f64 g_audioFrexpHalvingScale;

extern char g_actorAnimatedModelResourceTuning;




extern const f64 g_lowPassCoefficientScale;

extern WidgetEventHandler g_overlaySlotEventHandlersDe;

extern s32 g_artsendTextureViewerEntryTable;


extern char g_pagerPageStorage;

extern char g_fragTagOffLabelText[];

extern char g_menuOptionTinyModeEnabledText[];

extern char g_pakPreviewKindLabelProfile[];

union PagerSlotLookupStorage;
extern union PagerSlotLookupStorage g_pagerSlotLookupStorage;

extern const char s_animObjectInfoText[];

extern WidgetEventHandler g_selectionMenuHandlers;

extern s32 g_textClipRight;

extern const double g_sequenceSecondsToTicksUnsignedBias;

extern char g_SetN64_RunBootstrapThreadPackedAddress[];
extern char addrLow_SetN64_RunBootstrapThread[];


extern s32 g_systemBootMarkerComparison;

extern struct ScalarFloatView g_controllerEffectRandomRangeScale;

#include "Common/legacy_collision_actor.h"

extern signed char g_geometryMaterialLightDirection[3];

extern unsigned char g_controllerPakStatusBytes[];

extern u8 g_imageLowBoostNibbleRemap[];

extern char g_pakChannelFallbackDialogText;

extern char g_textureVariationBypassEnabledLabels[];

extern char g_menuOptionAllMapDisabledText[];

extern int g_pakProfileLoaded;

extern f32 g_audioTransformBandSteps[];

extern s32 g_firstStatusBarMoverScript;

extern char g_menuChoiceEnabledLabels[];

extern f32 g_playerReactionReserveApproachRate;


extern char g_pagerCartridgeData[];

extern char *g_pakScannedChannelNumberLabels[];

struct UnitVtx;
extern struct UnitVtx g_playerAimMarkerVertices[];


extern f32 g_particleYawMatrixScratch[16];

extern char g_sceneLevelNameRequestTagDe;

extern struct CacheEntry *g_audioCacheCountdownHead;

extern u32 g_displayListCapacityDe;

extern WidgetEventHandler g_sliderTransitionEventHandlers;

extern const char g_menuScaledLabelValueFormat[];

extern float g_maskedImageRectangleCoordinateScale;

extern char s_nodeDefaultFieldText[];

extern char g_ownerNotificationDisabledLabels[];

extern struct FieldRow g_scenarioCatalogueEventIds[];

extern s32 g_pakUseDefaultPreviewLabels;

extern u8 g_imageHighBoostNibbleRemap[];

extern struct FieldRow g_residentActorEventKinds[];

extern struct ScalarFloatView g_simpleObjectScaleTransitionFactor;

extern const float g_compressedMarkerQuarterNoteUnit;

extern char g_textureVariationBypassDisabledLabels[];

extern char g_bloodColorRedText[];


extern s32 g_teamSelectedNoticesEuX[4][3];

extern float fabsf(float);

extern s32 g_combinePipelineSyncPending;

extern unsigned char g_primitiveAlphaOverrideEnabled;

extern char g_pakPreviewDifficultyNormalLabel[];

extern char *g_pakSaveMenuProfileChoiceLabels[];


extern char g_playerLeapMovementParameters;

extern char g_menuOptionTinyModeDisabledText[];


extern f32 k_turretInvertedAimAngle;

extern char g_menuOptionBigHandsFeetModeDisabledText[];


extern char g_botControllerProfile[];

extern CVector3 g_actorRadialDirections[8];

extern struct FieldRow g_matchOptionsActorKinds[];

extern u8 g_controllerPresenceBits[];

extern char g_turretDispatchTable[];

extern s16 DEBUG_LINK_HANDSHAKE_REGISTER;

extern WidgetEventHandler g_overlaySlotEventHandlersEu;

extern struct FieldRow g_trialCatalogueEventKinds[];

extern s32 g_ctfWaitingPlayerFlag;

extern void *g_slotRankNamePointers_Empty[];


extern char g_pakAdjustMenuChoiceResourceA[];

extern s32 g_menuEventCount;

extern int g_frontendScreenModeLoRezLetterboxLabel;


extern struct MenuPointerEntry g_encodedCheatLabelTable[];

extern u64 g_schedulerGraphicsTaskStartTime;

extern char g_lightAnimationOffsetTable[];


extern char g_menuOptionUnlimitedAmmoEnabledText[];

extern struct FrontendRenderConfig g_frontendVideoModeRenderConfigs[];


extern struct Shield g_damageBoneBoundsShield;

extern char g_profileMenuLabelWords[];

extern float g_reverbUnityRatio;

extern s32 g_particleQuadDisplayListState;


extern s32 g_motionTrackDecodeRotation;


extern s16 DEBUG_LINK_AUXILIARY_REGISTER;

extern f32 k_gameSpeedSelectionOffsets[];

extern f32 g_playerMediumAndHardMovementFactors[];


extern struct FileHeader g_frontendResourceFilename;

struct ImageDescriptor;
extern struct ImageDescriptor *g_conversionDestinationImage;

extern s32 g_musicPlaybackEnabled;

struct StateFlags;
extern struct StateFlags g_equipmentPanelWidgetIds[][19];

extern s32 g_ctfMode;

extern int g_frontendMenuModelFlag;

extern char g_weaponSelectQuickText[];

extern char g_playerRespawnDialog;

extern s16 DEBUG_LINK_TRANSFER_REGISTER;



extern s32 g_modelEditPack;



extern s32 g_sourcePixelIndex;


extern WidgetEventHandler g_pakDialogEventHandlers;




extern char g_pickupSingleDefinitions;

extern u8 *g_toggleListClearLabel[];

extern char s_ammoPickupMessageSeparator[];

extern s8 g_controllerPakEnabledLastByte;

extern s32 g_playerMatchCountdownText;


extern f32 g_wrappedValueUpperConstants[2];

struct MemoryUsageStats;
extern struct MemoryUsageStats g_activeSequenceTargetFound;



extern struct Preset g_achievementPresetCopy;

extern f32 g_playerCrouchMinimumRiseAndBaseClearance[];


extern struct FieldRow g_titleButtonColumnEventActorKinds[];

extern int g_controlMenuControlFlag;

extern char g_pakAdjustMenuChoiceResourceB[];


extern const float g_reverbModulationCenter;


extern int g_cachedCeilingCrossProductNode;





extern s32 g_artsendTextureSelectionIndex;

extern struct StateFlags *g_collisionProbeSecondaryActor;


extern char g_compressedSequencePlayerAssertText[];



extern int g_geometryPreviousCombineMode;

extern int g_menuScreenOwnerOverride;

extern struct Tuning g_playerSwimMovementParameters;

extern struct FieldRow g_confirmationMenuEventActorKinds[];

extern char g_pauseOptionsMenuResource_eu[];

extern const s32 g_weaponEasedSpinSpinTarget;

extern struct SharedMovement g_playerJumpMovementParameters;




extern s32 g_stdioResourceReadRomEntry;

extern float g_geometryInitialScale;

extern f32 g_regionEdgeDefaultUpY;

extern char g_pagerExpansionDataSize[];

extern s32 g_artsendNextFrameHoldCount;

extern char s_playerCountFormat[];

extern struct Tuning g_playerClimbMovementParameters;



extern u32 g_resourceHashSlotCount;




extern char *g_playerSettingsTapText[];

extern s32 g_listButtonEventIds;

extern char g_menuOptionAllSpecialObjectsDisabledText[];

extern s32 alMainBusPull_Address;



extern const f64 g_audioFrexpUpperLimit;

extern s32 g_soundVoicePoolGlobalState;

extern float g_menuModelPreviewYawSpeedScale;

extern char g_staticJumpTableRegionByteCount;


#include "Data/Weapon_callbacks/weapon_fire_state_table.h"

extern struct OSTimer_s *g_timerListSentinel;

extern char g_alternateRenderMicrocodeData;

extern char *g_scenarioSetupLocalizedTitles[];

extern f32 g_transitionAlphaScaleTable[];

extern u32 g_destinationAlphaMask;

extern struct FieldRow g_playerCountEventActorKinds[];

extern s32 g_extraOptionsActorKinds[];



#if defined(VERSION_US)
extern struct ResidentEventHandlerEntry g_residentEventEntries[];
#else
extern struct FieldRow g_residentEventEntries[];
#endif




extern struct ResourcePageMapping *g_pagerLruTail;


extern OSIoMesg g_videoRetraceEvent;

extern struct GeometryModelInstanceEntry g_materialInstances[];





extern f32 g_barrelEffectSoundMinimumPitch;

extern s32 g_hudCountMoverScript[];


extern struct FieldRow g_playerSettingsEventIds[];

extern struct VideoDeviceManager g_videoDeviceManager;


extern f32 g_lightVolumeDefaultDirectionX;

extern s32 g_resourceCompletionWakeQueue;


extern f32 g_ribbonNodeTransformCutoffConstants[];



extern s32 g_profileSecondaryMenuResource;

extern const char s_binaryBlockText[];



extern s32 g_controllerPakSelectedNoteIndex;

extern s32 g_stdioResourceTellRomEntry;

extern char g_sessionUpdateHandlers[];

extern const float g_perspectiveFloatAngleScale;


extern s32 g_modelBatchResources[];

extern f32 g_frameHeapRestoreStatLowerLimit;

extern u8 g_profileUnlockedTrialBits[];

extern struct FieldRow g_nodePairMenuEventIds[];

extern const f32 g_sineExceptionalResult;

extern char *g_playerOptionLookSpringOffText;



extern char g_alternateRenderMicrocodeText;

extern s32 g_fragTagSelectionState;

extern u64 g_bootstrapThreadStack[];

extern s32 g_selectionMenuHandlerEvents;


extern f32 g_frameHeapFreeByteStats[3];

extern s32 g_creditsControllerButtons;

extern s32 g_frameHeapBuffers[2];

extern f32 g_playerCrouchDepthAndMinimumFall[];

extern char s_particleModelResourceTag;

extern u8 g_playerSettingsSlotByteBase[];

extern char g_controllerSiMessageBuffer[];

extern f32 g_playerActionBlendTargetAndMinimumStep[2];


extern u32 g_displayListCapacityEuX;

extern s32 g_artsendTextureViewerTextureTable;

extern s32 alSavePull_Address;





extern int g_baseAmmoCapacities[];

extern s32 g_barrelPrimaryFlagSoundTable[];

extern struct Box g_cameraVolumeBounds;

extern char g_menuOptionAllWeaponsEnabledText[];

extern f32 g_weaponSpinFeedbackConstants[];

extern s32 g_pakActionMenuEventKinds[];

extern s32 g_pakDialogEventActorKinds;

extern struct FieldRow g_trialOptionsEventIds[];


extern char g_menuOptionPenAndInkModeDisabledText[];


extern struct FieldRow g_equipmentEventActorKinds[];


extern char g_promptActionHeadingText[];

extern char g_staticDataRegionByteCount;



extern struct FieldRow g_playModeEventKinds[];

extern s32 g_creditsSelectSpawnOnExit;

extern char *g_pakSaveMenuSnapshotChoiceLabels[];

extern s32 g_playerStatisticsAccumulatedDeaths[][100];


extern s32 g_frontendPakPromptAccepted;

extern const f64 k_xmathCeilIntegralBias;

extern s32 g_hudSquadMoverScript[];

extern s32 g_weaponChargeSpinTarget;

extern s32 g_sessionUpdateResetFlag;

extern s32 g_pakProfileControllerPort;

extern char g_bloodColorOffText[];

extern s32 g_matchOptionsCursorNormalLabel[];

extern s32 g_frameAnimationEventActorKinds;

extern char g_cinemaStateRegionByteCount;


extern struct ControllerInitStatusBytes g_pagerTlbSlots[];

extern f32 g_staticObjectOpaqueAlpha;


extern char g_particleQuadRenderRestoreList;

extern char g_playerSequenceCallbacks;

extern f32 k_collisionSurfaceOffsetScales[];






struct ALDelayAudioSetEffectParameter;
typedef struct ALDelayAudioSetEffectParameter ALDelayAudioSetEffectParameter;

struct ALEnvMixer_s;
typedef struct ALEnvMixer_s ALEnvMixer_s;



struct EffectFilterState;
typedef struct EffectFilterState EffectFilterState;



struct ALSeqPlayer88;
typedef struct ALSeqPlayer88 ALSeqPlayer88;



union ALSndpEventhandleEvent;
typedef union ALSndpEventhandleEvent ALSndpEventhandleEvent;


struct ALSoundStatehandleEvent;
typedef struct ALSoundStatehandleEvent ALSoundStatehandleEvent;






struct Access_s8_E6;
typedef struct Access_s8_E6 Access_s8_E6;










struct LevelActor;


struct Angles;
typedef struct Angles Angles;

struct VoicePitchAngles;
typedef struct VoicePitchAngles VoicePitchAngles;

struct Animator;
typedef struct Animator Animator;




struct Attachment;
typedef struct Attachment Attachment;


struct SceneFrameItemBank;
typedef struct SceneFrameItemBank SceneFrameItemBank;

struct Binding;
typedef struct Binding Binding;







struct Bytes12;
typedef struct Bytes12 Bytes12;



struct ActorDamageHookView;
typedef struct ActorDamageHookView ActorDamageHookView;









struct CameraEventsSpawnAttachedEffect;
typedef struct CameraEventsSpawnAttachedEffect CameraEventsSpawnAttachedEffect;









struct GameAudioContext;


struct VoicePitchChannelContext;
typedef struct VoicePitchChannelContext VoicePitchChannelContext;

struct SoundDescriptor;
typedef struct SoundDescriptor SoundDescriptor;


struct Def;
typedef struct Def Def;

struct Dest;
typedef struct Dest Dest;

struct Digits;
typedef struct Digits Digits;
















struct EffectBlock;
typedef struct EffectBlock EffectBlock;




struct EffectMotion;
typedef struct EffectMotion EffectMotion;



struct EffectSystem;
typedef struct EffectSystem EffectSystem;

struct EffectTarget;
typedef struct EffectTarget EffectTarget;

struct EffectEventsSpawnAttachedEffect;
typedef struct EffectEventsSpawnAttachedEffect EffectEventsSpawnAttachedEffect;

struct Shared_ParticleDesc;
typedef struct Shared_ParticleDesc Shared_ParticleDesc;
struct Shared_Particle;

struct Ent;
typedef struct Ent Ent;






struct MenuObjectContextEntry;
typedef struct MenuObjectContextEntry MenuObjectContextEntry;

struct EntrySmosSetFocusedElement;
typedef struct EntrySmosSetFocusedElement EntrySmosSetFocusedElement;

struct ArchiveOwnedImageEntry;
typedef struct ArchiveOwnedImageEntry ArchiveOwnedImageEntry;

struct ArchiveChunkImageEntry;
typedef struct ArchiveChunkImageEntry ArchiveChunkImageEntry;

struct EntryOvlSceneDispatchAndRecycleQueuedTriggers;
typedef struct EntryOvlSceneDispatchAndRecycleQueuedTriggers EntryOvlSceneDispatchAndRecycleQueuedTriggers;





















struct ParticleEffectRelocationFrame;
typedef struct ParticleEffectRelocationFrame ParticleEffectRelocationFrame;




struct GameLocalizationState;
typedef struct GameLocalizationState GameLocalizationState;


struct GlobalsMenuSetOptionsSceneSelection;
typedef struct GlobalsMenuSetOptionsSceneSelection GlobalsMenuSetOptionsSceneSelection;

struct PieceGroup;
typedef struct PieceGroup PieceGroup;


struct HudCue;
typedef struct HudCue HudCue;

struct PlayerLoadoutInfo;
typedef struct PlayerLoadoutInfo PlayerLoadoutInfo;

struct Init;
typedef struct Init Init;










struct MenuBindingItemView;
typedef struct MenuBindingItemView MenuBindingItemView;



struct TrackOpacityKey;
typedef struct TrackOpacityKey TrackOpacityKey;












struct ListScreenItem;
typedef struct ListScreenItem ListScreenItem;

struct ListScreenModel;
typedef struct ListScreenModel ListScreenModel;

struct ListScreenScreen;
typedef struct ListScreenScreen ListScreenScreen;

struct Loadout;
typedef struct Loadout Loadout;







struct MatchRewardsRecord;
typedef struct MatchRewardsRecord MatchRewardsRecord;













struct TypedMenuVariableView;
typedef struct TypedMenuVariableView TypedMenuVariableView;



union ModelPreviewScreen;
typedef union ModelPreviewScreen ModelPreviewScreen;


struct Motion;
typedef struct Motion Motion;

struct VoicePitchMotion;
typedef struct VoicePitchMotion VoicePitchMotion;





struct CacheEvictionNode;
typedef struct CacheEvictionNode CacheEvictionNode;

struct PickupGoalAvailabilityNode;
typedef struct PickupGoalAvailabilityNode PickupGoalAvailabilityNode;

















































struct ObjectItemsDrawActorWithRedMenuEffect;
typedef struct ObjectItemsDrawActorWithRedMenuEffect ObjectItemsDrawActorWithRedMenuEffect;

struct OptionsOpenItem;
typedef struct OptionsOpenItem OptionsOpenItem;

struct OptionsOpenScreen;
typedef struct OptionsOpenScreen OptionsOpenScreen;


struct AudioOwnerView;
typedef struct AudioOwnerView AudioOwnerView;

struct SceneTriggerQueueOwner;
typedef struct SceneTriggerQueueOwner SceneTriggerQueueOwner;

struct PakNotesMenu;
typedef struct PakNotesMenu PakNotesMenu;

struct PakNotesMenuItem;
typedef struct PakNotesMenuItem PakNotesMenuItem;








struct PakStatusPakSaveMenu;
typedef struct PakStatusPakSaveMenu PakStatusPakSaveMenu;

struct VoiceVolumeParameters;
typedef struct VoiceVolumeParameters VoiceVolumeParameters;


struct PatrolActor;
typedef struct PatrolActor PatrolActor;

struct PatrolBot;
typedef struct PatrolBot PatrolBot;

struct PatrolPlayer;
typedef struct PatrolPlayer PatrolPlayer;

struct PatrolRouteSet;
typedef struct PatrolRouteSet PatrolRouteSet;

struct PickupGoalControllerView;
typedef struct PickupGoalControllerView PickupGoalControllerView;

struct Piece;
typedef struct Piece Piece;

struct Plan;
typedef struct Plan Plan;

struct Player1680;
typedef struct Player1680 Player1680;

struct PlayerList;
typedef struct PlayerList PlayerList;


struct PlayerRankInner;
typedef struct PlayerRankInner PlayerRankInner;














struct SoundPlayerSlotPool;
typedef struct SoundPlayerSlotPool SoundPlayerSlotPool;



struct RecordD90;
typedef struct RecordD90 RecordD90;

struct ResourceRequest;
typedef struct ResourceRequest ResourceRequest;


struct ResourceFrontendUpdateImageReleaseTimers;
typedef struct ResourceFrontendUpdateImageReleaseTimers ResourceFrontendUpdateImageReleaseTimers;

struct ResultsHeadingCharacter;
typedef struct ResultsHeadingCharacter ResultsHeadingCharacter;

struct ResultsHeadingName;
typedef struct ResultsHeadingName ResultsHeadingName;

struct ResultsHeadingRecord;
typedef struct ResultsHeadingRecord ResultsHeadingRecord;

struct ResultsHeadingScreen;
typedef struct ResultsHeadingScreen ResultsHeadingScreen;


struct ResultsHeadingStage;
typedef struct ResultsHeadingStage ResultsHeadingStage;











struct Screen;
typedef struct Screen Screen;



struct Selection;
typedef struct Selection Selection;










struct Shared_AnimState;
typedef struct Shared_AnimState Shared_AnimState;

struct Shared_GlobalFlowState;
typedef struct Shared_GlobalFlowState Shared_GlobalFlowState;

struct Shared_GlobalRuntimeState;
typedef struct Shared_GlobalRuntimeState Shared_GlobalRuntimeState;

struct Shared_HudOwner;
typedef struct Shared_HudOwner Shared_HudOwner;



struct Shared_PoseActor;
typedef struct Shared_PoseActor Shared_PoseActor;

struct Shared_PoseContext;
typedef struct Shared_PoseContext Shared_PoseContext;

struct Shared_PoseModel;
typedef struct Shared_PoseModel Shared_PoseModel;

struct Shared_PosePart;
typedef struct Shared_PosePart Shared_PosePart;

struct Shared_PosePartEntry;
typedef struct Shared_PosePartEntry Shared_PosePartEntry;

struct Shared_PosePartTable;
typedef struct Shared_PosePartTable Shared_PosePartTable;

struct Shared_PoseWorld;
typedef struct Shared_PoseWorld Shared_PoseWorld;


struct PolytrakScalarSampleMetadata;
typedef struct PolytrakScalarSampleMetadata PolytrakScalarSampleMetadata;


struct SlotCC;
typedef struct SlotCC SlotCC;

struct SlotDialog;
typedef struct SlotDialog SlotDialog;

struct SoundPlayerSlot;
typedef struct SoundPlayerSlot SoundPlayerSlot;


struct ParticleEffectRelocationSlot;
typedef struct ParticleEffectRelocationSlot ParticleEffectRelocationSlot;

struct Source110;
typedef struct Source110 Source110;

struct EffectSpawnSourceView;
typedef struct EffectSpawnSourceView EffectSpawnSourceView;

struct Spawn;
typedef struct Spawn Spawn;


struct StateEntry;
typedef struct StateEntry StateEntry;

struct StateMenuSetOptionsSceneSelection;
typedef struct StateMenuSetOptionsSceneSelection StateMenuSetOptionsSceneSelection;




struct StyleNextState;
typedef struct StyleNextState StyleNextState;








struct TargetSelectionObj;
typedef struct TargetSelectionObj TargetSelectionObj;



struct TextBoundsData;
typedef struct TextBoundsData TextBoundsData;

struct TextBoundsDescriptor;
typedef struct TextBoundsDescriptor TextBoundsDescriptor;

struct TextBoundsFont;
typedef struct TextBoundsFont TextBoundsFont;

struct CItemInfo_t;
typedef struct CItemInfo_t CItemInfo;

struct TextBoundsRecord23;
typedef struct TextBoundsRecord23 TextBoundsRecord23;



struct TextBoundsText;
typedef struct TextBoundsText TextBoundsText;

struct TimerFrontendUpdateImageReleaseTimers;
typedef struct TimerFrontendUpdateImageReleaseTimers TimerFrontendUpdateImageReleaseTimers;








struct Variable;
typedef struct Variable Variable;

struct PlayerFlashView;
typedef struct PlayerFlashView PlayerFlashView;

struct ChannelPitchMotionView;
typedef struct ChannelPitchMotionView ChannelPitchMotionView;

struct ViewChannelUpdateVoicePitch;
typedef struct ViewChannelUpdateVoicePitch ViewChannelUpdateVoicePitch;

struct VoiceChannelUpdateVoicePan;
typedef struct VoiceChannelUpdateVoicePan VoiceChannelUpdateVoicePan;

union Vtx10;
typedef union Vtx10 Vtx10;









struct Slider;



struct _Pft;
typedef struct _Pft _Pft;


union du;
typedef union du du;

union fu;
typedef union fu fu;





































struct QueuedModelInstance;
typedef struct QueuedModelInstance QueuedModelInstance;












struct SelectedLevelLabelItem;
typedef struct SelectedLevelLabelItem SelectedLevelLabelItem;

struct ToggleRowTextView;
#include "Menu/option_text_type.h"




struct ALDelayAudioSetEffectParameter;
struct ALDelayAudioSetEffectParameter {
    u32 input;
    u32 output;
    s16 ffcoef;
    s16 fbcoef;
    s16 gain;
    f32 rsinc;
    f32 rsval;
    s32 rsdelta;
    f32 rsgain;
    struct Clip *lp;
    void *rs;
};
struct ALEnvMixer_s;
struct ALEnvMixer_s {
    ALFilter_s14_2 filter;
    void *state;
    s16 pan;
    s16 volume;
    s16 cvolL;
    s16 cvolR;
    s16 dryamt;
    s16 wetamt;
    u16 lratl;
    s16 lratm;
    s16 ltgt;
    u16 rratl;
    s16 rratm;
    s16 rtgt;
    s32 delta;
    s32 segEnd;
    s32 first;
    void *ctrlList;
    void *ctrlTail;
    struct ALFilter_s14_2 **sources;
    s32 motion;
};
struct ALDelayAudioSetEffectParameter;
struct EffectFilterState;


struct Opaque_ALSeq_s;
typedef struct Opaque_ALSeq_s Opaque_ALSeq;
struct ALSeqPlayer88;
struct ALSeqPlayer88 {
    char node[20];
    void *drvr;
    Opaque_ALSeq *target;
    s32 curTime;
    void *bank;
    s32 uspt;
    s32 nextDelta;
    s32 state;
    u16 chanMask;
    s16 vol;
    u8 maxChannels;
    u8 debugFlags;
    ALEvent nextEvent;
    ALEventQueue evtq;
    s32 frameTime;
    void *chanState;
    void *vAllocHead;
    void *vAllocTail;
    void *vFreeList;
    void *initOsc;
    void *updateOsc;
    void *stopOsc;
    ALSeqMarker *loopStart;
    ALSeqMarker *loopEnd;
    s32 loopCount;
};
struct ALSoundStatehandleEvent;
struct ALSoundStatehandleEvent {
    ALVoice voice;
    ALSound *sound;
    s16 priority;
    f32 pitch;
    s32 state;
    s16 vol;
    u8 pan;
    u8 fxMix;
};
union ALSndpEventhandleEvent;
union ALSndpEventhandleEvent {
    ALEvent msg;
    struct {
        s16 type;
        struct ALSoundStatehandleEvent *state;
    } common;
    struct {
        s16 type;
        struct ALSoundStatehandleEvent *state;
        s16 vol;
    } vol;
    struct {
        s16 type;
        struct ALSoundStatehandleEvent *state;
        f32 pitch;
    } pitch;
    struct {
        s16 type;
        struct ALSoundStatehandleEvent *state;
        u8 pan;
    } pan;
    struct {
        s16 type;
        struct ALSoundStatehandleEvent *state;
        u8 mix;
    } fx;
};
struct Access_s8_E6;
struct AiController;
struct LevelActor;

struct Angles;
struct Angles {
    u16 heading;
    u16 pitch;
    u16 target;
    s16 steps;
};
struct VoicePitchAngles;
struct VoicePitchAngles {
    u16 heading;
    u16 pitch;
    u16 target;
    s16 steps;
    s16 delay;
    s16 pad0A;
};
struct Animator;
struct Attachment;
struct Attachment {
    char pad0[2];
    u16 type;
    char pad4[4];
    Triple offset;
    char pad14[0];
    ResourceManagerState params;
};
struct SceneFrameItemBank;
struct SceneFrameItemReference;
struct Binding;
struct Binding {
    int pad0;
    int type;
    char pad8[16];
    void *(*storage)(void);
};
struct Bytes12;
struct ActorAnimationEventTable;
struct Triple;
struct ActorDamageHookView;
struct ActorDamageHookView {
    char pad0[0x110];
    void (*callback)(void);
};
typedef void ( *ContextCallback)(void *);
struct CameraEventsSpawnAttachedEffect;
struct GameAudioContext;

struct VoicePitchChannelContext;
struct VoicePitchChannelContext {
    char pad0[0x84];
    char channels[0xDC - 0x84];
    s16 slots[16];
    char padFC[0x104 - 0xFC];
    s32 frame;
};
struct SoundDescriptor;
struct SoundDescriptor {
    s16 group; /* 0x00: sound description group */
    s16 sample; /* 0x02 */
    s8 priority; /* 0x04 */
    s8 mode; /* 0x05 */
    u16 flags; /* 0x06: pan and sound flags */
    s16 pitchPresetId;
    s16 preset; /* 0x0A */
    s16 reservedHalf;
    s8 pitch; /* 0x0E */
    s8 envelopeFlag;
    s16 yaw; /* 0x10 */
    s16 x; /* 0x12 */
    s16 y; /* 0x14 */
};
struct Source110;
struct Source110 {
    char pad0[0x1C];
    CVector3 velocity;
    char pad28[0x100 - 0x28];
    u32 flags;
    f32 limit;
    s16 current_state;
    s16 previous_state;
    s16 counter;
    s8 state_changed;
    u8 animationChanged; /* 0x10F */
    u8 pad110[0x13];
    u8 stateChanged; /* 0x123 */
    u8 pad124[0x2E0 - 0x124];
    u32 renderFlags; /* 0x2E0 */
};
struct Dest;
struct Source110;
struct StateEntry;
struct Dest {
    u32 flags;
    s32 health; /* 0x04 */
    s32 maxHealth; /* 0x08 */
    s32 handle; /* 0x0C */
    s8 level; /* 0x10 */
    u8 pad11;
    u8 state12, state13;
    s8 state14[4];
    f32 initialScale; /* +0x18 */
    s32 reserved1C[4];
    void *table; /* 0x2C */
    struct StateEntry *entry;
    s8 state;
    s8 old_state;
    s8 requestedState; /* 0x36 */
    char pad37;
    u32 old_entry_flags;
    u32 entry_flags;
    s32 stateTimer; /* 0x40 */
    s32 reserved44;
    CVector3 initialPosition; /* +0x48 */
    CVector3 previousPosition; /* +0x54 */
    f32 initialHeight; /* +0x60 */
    f32 cueTimer; /* 0x64 */
    void *animation; /* saved across the 0x170-byte clear; pointee unresolved */
    s32 animationCount[3];
    s32 reserved78[5];
    f32 height8C;
    f32 height90;
    u8 state94, state95;
    s16 state96;
    u8 reserved98[4];
    f32 height9C;
    CVector3 positionA0;
    void *surfaceAC;
    CVector3 positionB0;
    void *surfaceBC;
    f32 scale;
    f32 entry_scale;
    s16 result;
    s8 state_result;
    u8 count;
    s8 secondaryLevel; /* 0xCC */
    u8 padCD[3];
    s32 reservedD0, reservedWordBeforeTail;
    u8 reservedD8[0x24];
    struct CLoopingSoundData_t *sound; /* 0xFC */
    u8 pending; /* 0x100 */
    u8 pad101;
    s16 channel; /* 0x102 */
    u8 pad104[4];
    void *enter; /* 0x108 */
    void *draw; /* 0x10C */
    void *hit; /* 0x110 */
    u8 pad114[8];
    void *callback11C; /* address stored by Actor_InitSpawnedActor */
    u8 reserved120[4];
    s32 definitionHealth;
    f32 charge; /* 0x128 */
    f32 initialCharge;
    s32 reserved130;
    f32 restPitch; /* 0x134 */
    s32 fireCounter, fireMode;
    u8 pad140[4];
    s32 fireEnabled, reserved148, reserved14C, reserved150;
    u8 reserved154[0x1C];
};
typedef void *( *StateCallback)(struct Source110 *, struct Dest *);
struct StateEntry {
    s32 id;
    RomCallbackWord enter;
    RomCallbackWord update;
    char padC[4];
    StateCallback callback;
    f32 scale;
    s32 threshold;
    u32 flags;
};
struct Digits;
struct ActorStateTable {
    struct ActorStateTable *next;
    u8 pad4[0x1C];
    StateEntry entries[1];
};
struct EffectMotion;
struct EffectMotion;
struct EffectBlock;

#include "Common/ccollisioninfo2_t.h"
struct Shared_Particle;
struct EffectTarget;
struct EffectTarget {
    void *actor; /* kind 0: placed prop; kind 1: animated actor */
    char pad4[4];
    CVector3 pos;
    s32 matrixIndex;
    char pad18[0x66];
    u8 victimTeam;
    char pad7F[0x89];
};
struct EffectEventsSpawnAttachedEffect;
struct EffectEventsSpawnAttachedEffect {
    char pad0[0x6C];
    f32 scale;
    char pad70[0x1D8 - 0x70];
    s32 target;
    char pad1DC[0x2A0 - 0x1DC];
    CVector3 offset;
    char pad2AC[0x11E8 - 0x2AC];
    struct EffectEventsSpawnAttachedEffect *child;
};
struct Ent;
struct EntryOvlSceneDispatchAndRecycleQueuedTriggers;
struct EntryOvlSceneDispatchAndRecycleQueuedTriggers {
    char pad0[4];
    struct EntryOvlSceneDispatchAndRecycleQueuedTriggers *next;
    s32 handle;
};
struct FrameSequence;
struct FrontendArchiveHandleView;

#include "Menu/frame_sequence.h"
struct ParticleEffectRelocationSlot;
struct ParticleEffectRelocationSlot {
    s32 item;
    char pad4[0x34];
};
struct ParticleEffectRelocationFrame;


struct GameLocalizationState;
struct GameLocalizationState {
    u8 reserved[0x581];
    u8 language;
};
struct GlobalsMenuSetOptionsSceneSelection;
struct GameplayCamera;
struct GlobalsMenuSetOptionsSceneSelection {
    struct GameplayCamera *camera; /* the camera particle matrices are built for once per frame */
    char pad4[0x88];
    float width;
    float height;
};
struct Piece;
struct Piece {
    char pad0[0x14];
    s32 tag;
    s32 relocatedOffset18;
    s32 relocatedOffset1C;
    s32 relocatedOffset20;
    s32 relocatedOffset24;
    s32 relocatedOffset28;
    s32 relocatedOffset2C;
    s32 relocatedOffset30;
    s32 relocatedOffset34;
    s32 relocatedOffset38;
};
struct PieceGroup;
struct PakMenuSlot;
struct EffectEventsSpawnAttachedEffect;
struct HudCue;
struct HudCue {
    s32 handle;
    s32 ambient;
    s32 cue0;
    s32 cue1;
    char pad10[4];
    s32 reserved14;
    s32 state;
};
struct Init;
struct Init {
    s32 id;
    CVector3 position;
    f32 radius;
    u16 kind;
    u16 index;
    u16 flags;
    u16 extra;
    u16 model;
    s8 angle;
};
struct Binding;
struct MenuBindingItemView;
struct TrackOpacityKey;
struct TrackOpacityKey {
    char pad0[0xC];
    f32 value;
    f32 time;
};
struct ListScreenItem;
struct ListScreenItem {
    char pad0[0x10];
    u8 alpha;
    char pad11[3];
    s16 x;
    char pad16[2];
    s16 width;
};
struct ListScreenModel;
struct ListScreenModel {
    char data[192];
};
struct ListScreenScreen;
struct ListScreenScreen {
    s32 window;
    char pad4[0x8 - 0x4];
    ListScreenModel models[5];
    s32 list;
    struct ListScreenItem *left;
    s32 leftCount;
    struct ListScreenItem *right;
    s32 rightCount;
    s32 reservedWord;
    s32 countdown;
    s32 text3E4;
    struct ListScreenItem *reservedPointer;
    struct ListScreenItem *label;
    struct ListScreenItem *reservedPointer1;
    char text[0x434 - 0x3F4];
    s32 category;
    s32 selection;
    struct ListScreenItem *item;
    struct ListScreenItem *reservedPointer2;
    struct ListScreenItem *reservedPointer3;
    struct ListScreenItem *reservedPointer4;
    struct ListScreenItem *reservedPointer5;
    struct ListScreenItem *reservedPointer6;
    struct ListScreenItem *reservedPointer7;
    struct ListScreenItem *reservedPointer8;
    s32 reservedWord1;
    s32 reservedWord2;
    s32 reservedWord3;
    s32 reservedWord4;
    s32 reservedWord5;
};
struct PlayerCountSettingsSlotView;
struct MatchRewardsRecord;
struct MatchRewardsRecord {
    char pad0[0x26];
    u8 plays[36];
    u8 unlocks[0x6C - 0x4A];
    s32 total1;
    char pad70[0x74 - 0x70];
    s32 total2;
    char pad78[0x190 - 0x78];
};
struct Variable;
struct Variable {
    int reservedWord;
    unsigned int valueType;
    float minimum;
    float maximum;
    float step;
    int reserved14;
    void *(*accessor)();
};
struct TypedMenuVariableView;
struct Variable;
union ModelPreviewScreen;
typedef struct ModelPreviewRow { s32 model; s32 state; s32 fade; s32 holdTicks; s32 image; } ModelPreviewRow;
union ModelPreviewScreen {
    struct { char pad0[0x1C]; s32 cursor; void *window; struct MenuWidget *item24; char killsText[10], scoreText[10], ratioText[10], otherText[10]; char nameText[64]; s32 started, player, badge; ModelPreviewRow rows[10]; char padAfter[0x188 - 0x9C - 10 * sizeof(ModelPreviewRow)]; s32 selected; char resultText[0x1C0 - 0x18C]; s32 ready; char pad1C4[0x1C8 - 0x1C4]; };
    struct { char padC8[0xC8]; char modelWorkspace; };
};
struct Motion;
struct Motion {
    char pad0[0x14];
    f32 heading;
    char pad18[0x48 - 0x18];
    f32 rate1;
    f32 rate2;
};
struct VoicePitchMotion;
struct VoicePitchMotion {
    char pad0[0x14];
    f32 heading;
    char pad18[0x24 - 0x18];
    f32 factor;
};
struct CacheEvictionNode;
struct CacheEvictionNode {
    u32 start;
    u32 end;
    s32 reserved8;
    u32 flags;
    s32 stamp; /* 0x10: last-use tick */
    char pad14[0x10];
    struct CacheEvictionNode *next;
};
struct PickupGoalAvailabilityNode;
struct PickupGoalAvailabilityNode {
    u16 id;
    u8 pad2[2];
    u8 kind;
};

struct CompactOptionsPageView;
struct ObjectItemsDrawActorWithRedMenuEffect;
struct OptionsOpenItem;
struct OptionsOpenItem {
    char pad0[0x1A];
    s16 color;
};
struct OptionsOpenItem;
struct OptionsOpenScreen;
struct OptionsOpenScreen {
    void *title;
    void *list;
    void *window;
    void *buttons[4];
    char pad1C[0x20 - 0x1C];
    struct OptionsOpenItem *cursor;
    char pad24[0x28 - 0x24];
    s32 length;
    s32 mode;
    char pad30[0x34 - 0x30];
    s32 open;
    s32 full;
};
struct Label;
struct AudioOwnerView;
struct AudioOwnerView {
    char pad0[0x84];
    char sound[88];
    s16 samples[20];
    char pad2[0x2B98 - 0xDC - 40];
    void *listener;
};
struct EntryOvlSceneDispatchAndRecycleQueuedTriggers;
struct SceneTriggerQueueOwner;
struct PakNotesMenuItem;
#include "Common/pak_menu.h"
#include "Common/shared_particleinstance.h"
struct PakNotesMenu;
struct PakNotesMenu {
    char pad0[0xC];
    struct PakNotesMenuItem *items;
    char pad10[0x10];
    struct PakMenuSlot *owner;
};
struct PakStatusPakSaveMenu;
struct PakStatusPakSaveMenu {
    char pad0[0x14];
    char *text;
    char pad18[4];
    struct SharedPlayer *player;
    struct PakMenuSlot *slot;
};
struct VoiceVolumeParameters;
struct VoiceVolumeParameters {
    char pad0[0x18];
    s16 pan;
    char pad1A[0x1A];
};
struct PatrolBot;
struct PatrolBot {
    u8 pad0[4];
    s32 node;
    u8 pad8[4];
    s32 goal;
    u8 pad10[0x214];
    s32 route;
    s32 routePos;
};
struct PatrolPlayer;
struct PatrolPlayer {
    u8 pad0[0x1454];
    struct PatrolBot *bot;
};
struct PatrolActor;
struct PatrolActor {
    u8 pad0[0x1D8];
    struct PatrolPlayer *player;
};
struct PatrolRouteSet;
struct PatrolRouteSet {
    u8 pad0[0x7C];
    s32 *routeCount;
};
struct PickupGoalControllerView;
struct PickupGoalControllerView {
    u8 pad0[4];
    s32 searchKey;
    u8 pad8[4];
    u32 selectedNode;
    u8 pad10[4];
    s32 history[4];
    u8 pad24[0x44];
    s32 goal;
    u8 pad6C[0x50];
    u32 goalSet;
};
struct Plan;
struct Plan {
    s32 p0;
    s32 aimTargetFlag;
    char p8[40];
    struct CompactOptionsPageView *probeParams;
    char p34[52];
    struct LevelActor *currentTarget;
    char p6C[20];
    struct LevelActor *approachTarget;
    s32 collisionMask;
    s32 p88;
    f32 aimYaw;
    f32 aimHeight;
    signed char routeCursor;
    char p95[27];
    CVector3 pos;
    s32 aimRoom;
};
struct Player1680;

struct PlayerList;
struct PlayerList {
    void **handle;
    struct SharedPlayer *players;
    int count;
};
struct PlayerRankInner;
struct PlayerRankInner {
    char pad[0x10];
    char **text;
};
struct PlayerFlashView;
struct PlayerFlashView {
    char pad0[0x544];
    s32 flash;
    char pad548[0x54D - 0x548];
    u8 level;
};
struct PlayerFlashView;
struct SoundPlayerSlot;
struct SoundPlayerSlot {
    char pad0[0x1C];
    void *owner;
    s16 state;
    char pad22[2];
    f32 value;
    s32 timer;
    s16 amount;
    u8 flags;
    u8 extra;
};
struct SoundPlayerSlotPool;
struct SoundPlayerSlot;
struct SoundPlayerSlotPool {
    char pad0[0x40];
    struct SoundPlayerSlot *slots;
    s32 count;
};
struct AudioSoundPlayerOwnerView;
struct SlotCC;
struct SlotCC {
    s32 index;
    s32 state;
    s32 used;
    s32 serial;
    s32 key;
    char pad1[0x24];
    s16 priority; /* 0x38: a voice of priority 100 is never taken over */
    s16 id;
    char pad1b[0x14];
    s32 flag;
    char pad2[0x50];
    s32 mode;
    s32 value;
    s32 active;
    struct AudioSoundPlayerOwnerView *owner;
    char pad3[0x18];
};
struct AudioSelectedHandleView;
struct RecordD90;
struct RecordD90 {
    struct AudioSelectedHandleView *header;
    SlotCC slots[17];
};
struct ResourceRequest;
struct ResultsHeadingName;
struct ResultsHeadingName {
    char *text;
};
struct ResultsHeadingCharacter;
struct ResultsHeadingName;
struct ResultsHeadingCharacter {
    struct ResultsHeadingName *name;
    char pad4[0x70 - 4];
};
struct ResultsHeadingRecord;
struct ResultsHeadingRecord {
    char pad0[0x94];
    s32 times[(0x190 - 0x94) / 4];
};
struct ResultsHeadingStage;
struct ResultsHeadingStage {
    char pad0[0x24];
    u8 time;
};
struct Selection;
struct Selection {
    u8 pad0[0x1BC];
    s32 stage;
    s32 selection;
    u8 pad1C4[4];
    s32 matches;
};
struct FragTagProfileFlagView;
struct Body;
struct Character;
struct Controller;
struct Controls;
struct Ctrl;
struct Held;
struct Mode;
struct Model;
struct Mount;
struct Profile;
struct Record;
struct Rider;
struct Shared_Body;
struct Shared_Hud;
struct Shared_Model;
struct Shared_Profile;
struct Shared_StateInfo;
struct Shared_Voice;
struct StateInfo;
struct View;
struct PlayerViewModeView;
struct Body;
struct Character;
struct Controller;
struct Controls;
struct Ctrl;
struct Held;
struct Mode;
struct Model;
struct Mount;
struct Profile;
struct Record;
struct Rider;
struct Settings;
struct Shared_Body;
struct Shared_Hud;
struct Shared_Model;
struct Shared_Profile;
struct Shared_StateInfo;
struct Shared_Voice;
struct StateInfo;
struct TeamInfo;
struct GameplayCamera;
struct Body;
struct Character;
struct Controller;
struct Ctrl;
struct Held;
struct Mode;
struct Model;
struct Mount;
struct Profile;
struct Record;
struct Rider;
struct Settings;
struct Shared_Body;
struct Shared_Hud;
struct Shared_Model;
struct Shared_Profile;
struct Shared_StateInfo;
struct Shared_Voice;
struct StateInfo;
struct TeamInfo;
struct View;
struct FragTagProfileFlagView;
struct Shared_AnimState;
struct Shared_AnimState {
    char pad0[0xB];
    s8 activeFlag;
    char padC[0x8];
};
struct Shared_GlobalFlowState;
struct Shared_GlobalFlowState {
    char pad0[0x78];
    s32 transition;
    char pad7C[0x4];
    s32 reset;
    char pad84[0x14];
    s32 active;
    s32 count;
};
struct Shared_GlobalRuntimeState;
struct Shared_GlobalRuntimeState {
    void * actorList;
    char pad4[0x28 - 0x4];
    s32 messageContext; /* g_frontendScreenStatus, +0x28 */
    char pad2C[0x1268 - 0x2C];
    struct GameLocalizationState localization; /* g_gameSettings, +0x1268 */
    char pad17EA[0x1834 - 0x17EA];
    s32 frozen;
    char pad1838[0x8];
    Shared_GlobalFlowState flow;
};
struct Shared_PosePartEntry;
struct Shared_PosePartEntry {
    char pad0[0x64];
    union {
        struct {
            s8 parent;
            u8 flags;
        } b;
        struct {
            u32 parent : 8;
            u32 kind : 2;
            u32 phase : 3;
            u32 still : 1;
            u32 sway : 2;
        } f;
    } u;
};
struct Shared_PosePartTable;
struct Shared_PosePartTable {
    s32 stride;
    s32 count;
    u8 data[1];
};
struct Shared_PoseModel;
struct Shared_PoseModel {
    s32 kind;
    char pad4[0x34];
    f32 verticalOffset;
};
struct Shared_PosePart;
struct Shared_PosePart {
    char pad0[0xC];
    s32 effectPartMask;
    char pad10[0x2];
    s8 twistStep;
    char pad13[0x1];
    s8 twistJoints[4];
    CVector3 twistAxis;
    char pad24[0x44];
};
struct Shared_PoseWorld;
struct Shared_PoseWorld {
    char pad0[0x1218];
    s32 impactTwistPending;
    char pad121C[0xA4];
    f32 scale;
};
struct Shared_PoseActor;
struct Shared_PoseContext;
struct Shared_PoseActor {
    char pad0[0x1];
    s8 partBitIndex;
    char pad2[0x6];
    CVector3 pos;
    struct StateFlags *surface;
    struct Shared_PoseModel *model;
    char pad1C[0x54];
    f32 verticalOffset;
    CMatrix4 mtx;
    s32 handle;
    u8 *boneMatrixData;
    char padBC[0xC];
    s32 animationResourceId;
    char padCC[0x1A];
    s8 animationResourceUnits;
    char padE7[0x19];
    s32 flags;
    Shared_AnimState animA;
    Shared_AnimState animB;
    char pad12C[0x4];
    f32 blendFactor;
    char pad134[0x7];
    u8 effectReferenceCount;
    char pad13C[0x4];
    u8 sampledLighting[2][24];
    Shared_PosePart part;
    struct Shared_PoseWorld *world;
    char pad1DC[0xB4];
    void (*callback)(CMatrix4, struct Shared_PoseContext *);
    char pad294[0x4C];
    s32 attachmentEffectsFlag;
};
struct Shared_PoseContext {
    struct Shared_PosePartEntry *part;
    s32 index;
    struct Shared_PoseActor *actor;
    s32 handle;
    struct CMatrix4 *mtx;
    struct Shared_PosePartTable *parts;
    void *modelPack;
    s32 model;
    struct Shared_AnimState *animA;
    struct Shared_AnimState *animB;
};
struct PolytrakScalarSampleMetadata;
struct SlotDialog;
struct SlotDialog {
    s32 root;
    s32 main;
    s32 absent;
    s32 unavailable;
    s32 prompt;
    s32 elapsed;
    s32 state;
    s32 ready;
    char text[128];
};
struct EffectSpawnSourceView;
struct Spawn;
struct StateMenuSetOptionsSceneSelection;
struct StateMenuSetOptionsSceneSelection {
    char pad0[0x108];
    int a;
    int b;
    int c;
    int d;
};
struct PlayerCountScreenState;
struct PlayerCountScreenState {
    s32 menu;
    s32 button;
    void *window;
    s32 delay;
    s32 target;
    char text[12];
    s32 value;
};
struct StyleNextState;
struct StyleNextState {
    char a[20];
    s32 item;
    struct Label *label;
    char text[1];
};
struct TargetSelectionObj;
struct TargetSelectionObj {
    char pad0[8];
    CVector3 pos;
    char pad14[0x100 - 0x14];
    s32 flags;
    char pad104[0x1D8 - 0x104];
    struct TargetSelectionObj *owner;
    char pad1DC[0x5D8 - 0x1DC];
    struct Record *slot;
    char pad5DC[0x5E4 - 0x5DC];
    s32 active;
    char pad5E8[0x122C - 0x5E8];
    s32 status;
};
struct TextBoundsData;
struct TextBoundsDescriptor;
struct TextBoundsDescriptor {
    char pad0[0x44];
    s8 * listContextKey;
};
struct TextBoundsFont;
struct CItemInfo_t;
struct CItemInfo_t {
    s32 entryIndex;
    s32 width;
    s32 height;
    f32 m_ScaleX; /* 0x0C */
    f32 m_ScaleY; /* 0x10 */
    s32 left; /* 0x14 */
    s32 right; /* 0x18 */
    s32 m_Top; /* 0x1C */
    s32 m_Bottom; /* 0x20 */
};
struct TextBoundsRecord23;
struct TextBoundsText;
struct TextBoundsHandlers {
    char pad0[0x14];
    void (*draw)(struct TextBoundsText *, CItemInfo *, CItemInfo *, void *);
};
struct TextBoundsText {
    s32 value;
    s16 mode;
    s16 reserved;
    s32 flags;
    s16 x; /* 0x0C */
    s16 y; /* 0x0E */
    s32 reserved10;
    void *text;
    struct TextBoundsHandlers *handlers;
    s32 spacing;
    s32 reserved20;
    struct TextBoundsDescriptor *descriptor; /* 0x24 */
};
struct ItemDef;
struct ChannelPitchMotionView;
struct VoicePitchChannelContext;
struct ViewChannelUpdateVoicePitch;
struct AudioOwnerView;
struct VoiceChannelUpdateVoicePan;


union Vtx10;
struct WeaponMenuPlayer;
struct t_dldc;
typedef signed int ( *WidgetCallback)(void *, struct t_dldc);
struct EntrySmosSetFocusedElement;
struct Slider;
struct _Pft;
struct _Pft {
    union {
        long long ll;
        double ld;
    } v;
    unsigned char *s;
    int n0;
    int nz0;
    int n1;
    int nz1;
    int n2;
    int nz2;
    int prec;
    int width;
    size_t nchar;
    unsigned int flags;
    unsigned char qual;
};
union du;
union du {
    struct {
        unsigned int hi;
        unsigned int lo;
    } word;
    double d;
};
union fu;
union fu {
    unsigned int i;
    float f;
};
struct QueuedModelInstance;
struct ScreenMenuFinishTabOptionsTransition;
struct LevelActor;
struct SelectedLevelLabelItem;
struct SelectedLevelLabelItem {
    u8 pad0[0x14];
    s32 **value;
};
struct ToggleRowTextView;

struct PlayerMenuResumeActor;
typedef struct PlayerMenuResumeActor PlayerMenuResumeActor;
struct ActorPakEnterPlayerOptions;
typedef struct ActorPakEnterPlayerOptions ActorPakEnterPlayerOptions;
struct Behaviour;
typedef struct Behaviour Behaviour;
struct Body;
typedef struct Body Body;
struct Controller;
typedef struct Controller Controller;
struct Ctrl;
typedef struct Ctrl Ctrl;
struct Descriptor;
typedef struct Descriptor Descriptor;
struct ActorActionDescriptor;
typedef struct ActorActionDescriptor ActorActionDescriptor;
struct StaticModelMaterialDescriptor;
typedef struct StaticModelMaterialDescriptor StaticModelMaterialDescriptor;
struct Flagged;
typedef struct Flagged Flagged;
struct Font;
typedef struct Font Font;
struct ImageHeader;
typedef struct ImageHeader ImageHeader;
struct Inner;
typedef struct Inner Inner;
struct Instance;
typedef struct Instance Instance;
struct Kind;
typedef struct Kind Kind;
struct CROMLevel_t;
struct LinkTable;
typedef struct LinkTable LinkTable;
struct Messages;
typedef struct Messages Messages;
struct Mode;
typedef struct Mode Mode;
struct ObjMenuUpdatePakActionMenu;
typedef struct ObjMenuUpdatePakActionMenu ObjMenuUpdatePakActionMenu;
struct ProfileModeSelectionPlayer;
typedef struct ProfileModeSelectionPlayer ProfileModeSelectionPlayer;
struct OwnerPakBeginProfileLoad;
typedef struct OwnerPakBeginProfileLoad OwnerPakBeginProfileLoad;
struct OwnerCMenuProfileUpdateProfileModeLabel;
typedef struct OwnerCMenuProfileUpdateProfileModeLabel OwnerCMenuProfileUpdateProfileModeLabel;
struct PlayerProfileView;
typedef struct PlayerProfileView PlayerProfileView;
struct AudioScene;
typedef struct AudioScene AudioScene;
struct ScoreTable;
typedef struct ScoreTable ScoreTable;
struct Scores;
typedef struct Scores Scores;
struct Shared_ParticleColors;
typedef struct Shared_ParticleColors Shared_ParticleColors;
struct Shared_ParticleDesc;
struct Shared_ParticleFade;
typedef struct Shared_ParticleFade Shared_ParticleFade;
struct SourceWeaponApplyScaledSideYaw;
typedef struct SourceWeaponApplyScaledSideYaw SourceWeaponApplyScaledSideYaw;
struct StateInfo;
typedef struct StateInfo StateInfo;
struct TablePakUpdateDialogList;
typedef struct TablePakUpdateDialogList TablePakUpdateDialogList;
struct CROMSwoosh_t;
struct WidgetFrontendUpdateSliderGeometry;
typedef struct WidgetFrontendUpdateSliderGeometry WidgetFrontendUpdateSliderGeometry;
typedef char * va_list;
#endif
