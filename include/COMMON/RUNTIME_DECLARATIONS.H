#ifndef COMMON_RUNTIME_DECLARATIONS_H
#define COMMON_RUNTIME_DECLARATIONS_H
#include <ultra64.h>
#include "ENGINE/SCHED.H"
#include "COMMON/LONE/PARTICLE_PITCH_MATRIX_SCRATCH.H"
#include "COMMON/LONE/SCREEN_MESSAGE_ALLOCATION_LABEL.H"
#include "COMMON/LONE/FRONTEND_VIEWPORT_WIDTH.H"
#include "COMMON/LONE/AUDIO_CLOCK_RATE.H"
#include "COMMON/PARTICLE_LIGHTING.H"
#include "COMMON/LEVEL_ACTOR.H"
#include "TYPES.H"
#include "COMMON/SESSION_STATE.H"


#include "COMMON/WIDGETRECAT1A.H"
#include "COMMON/OSPIHANDLE_S.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/VECTOR4F.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/AIPROFILE.H"
#include "COMMON/MULTIPLAYEROPTIONS.H"
#include "COMMON/LOADOUT.H"
#include "COMMON/OWNERRECAT8V2.H"
#include "COMMON/GROUP.H"
#include "COMMON/OBJECT_INSTANCE_TRANSFORM_AND_RENDER_VIEWS.H"
#include "COMMON/MANAGER.H"
#include "COMMON/CARTRIDGEREADWORKER.H"
#include "COMMON/AUDIO_CONTEXT.H"
#include "COMMON/OBJRECAT4V6.H"
#include "COMMON/SOUNDVOICEPOOL.H"
#include "COMMON/LIGHTDATA.H"
#include "COMMON/GEOMETRY_BLEND_AND_INSTANCE_VIEWS.H"
#include "COMMON/MTX.H"
#include "COMMON/PARTICLE_ATTACHMENT_AND_OWNER_VIEWS.H"
#include "COMMON/COLORENTRY.H"
#include "COMMON/WORLDSORTENTRY.H"
#include "COMMON/RESULTS.H"
#include "COMMON/OBJRECAT26DD8.H"
#include "COMMON/INTEGERSTATE530.H"
#include "COMMON/OBJRECAT18V6.H"
#include "COMMON/ALBANK_S.H"
#include "COMMON/OBJRECAT18V1.H"
#include "COMMON/ALPARAM_S.H"
#include "COMMON/ALDELAY28.H"
#include "COMMON/OSVISCALE.H"
#include "COMMON/CTX.H"
#include "COMMON/AUDIO_LOADDECODEDSAMPLES.H"
#include "COMMON/CHEATCODE.H"
#include "COMMON/ENTRYRECAT0V3.H"
#include "COMMON/NODERECAT2A8.H"
#include "COMMON/SLOTRECATCV1.H"
#include "COMMON/TEXTURE.H"
#include "COMMON/LABEL.H"
#include "COMMON/CHARACTERSELECTIONROOT.H"
#include "COMMON/MENU_INITIALIZEOPTIONSSCENE.H"
#include "COMMON/STATERECAT91.H"
#include "COMMON/RESULTSOPTIONSSCREEN.H"
#include "COMMON/SETTINGSRECAT24.H"
#include "COMMON/OBJECTRECAT28.H"
#include "COMMON/PLAYERRECAT64E.H"
#include "COMMON/OBJB.H"
extern s32 g_hudLivesMoverScript[];

extern char g_systemBootMarker;
extern char g_pakAllocateMenuFirstResource[];

extern char *g_matchResult5012TextDe;

extern int __osPiDevMgr;

extern s64 g_schedulerGraphicsFirstStartTime;

extern s32 g_hudScoreMoverScript[];

extern s32 *g_frontendResourceChromaKeys;

extern char g_playerRespawnCountDialog_de;

extern s32 g_frontendWidgetStateChanged;

extern char g_pakOperationFiveStateThreeLabel[];


extern FftTables g_audioTransformBandTables;

extern f32 g_actorModelViewEffectConstants[];

extern char g_initialDialogRowThreeResource[];

extern char g_SelectPromptTextGroupFiveCase13Text[];

extern char g_pickupTargetedDefinitions;

extern char g_menuOptionBit12EnabledText[];


extern char g_playerOption7CText1[];

extern s8 g_artsendTextureViewerState;

extern char g_mainCodeRegionByteCount;

extern char g_menuOptionBit3DisabledText[];

extern MarkerItemMenuRestoreBootMemory s_systembootdoneText;


extern char g_pakChannelReadyMessage_SnapshotCheckstatusprompt[];

extern char *g_matchResult5020TextEu[];

extern char g_SelectPromptTextGroupOneCase15Text[];

extern FieldRow g_gameOptionsActorKinds[];

extern const f64 k_xmathFractionIntegralLimit;

extern int *g_controllerPakProbeResource;


extern float g_unreferencedFloatTable_eu[];


extern s32 alResamplePull_Address;

extern char g_ribbonBlendResourceFirstBase_de[];

extern char *g_matchResult5026TextEu[];

extern char g_menuOptionBit5DisabledText[];

extern char k_stdioCarriageReturn;

extern char *g_matchResult5028TextDe;


extern char *g_profileRank1LocalizedTitles[];

extern char *g_matchResult5021TextEu[];

extern FieldRow g_germanMatchMenuEventKinds[];

extern s32 *g_trackResourceDirectory;

extern s32 g_controllerReturnPending;

extern char *g_profileRank9LocalizedTitles[];

extern void * g_peripheralHandleList;

extern void (*g_cameraGameplayModeCallbacks[][2])(void);

extern char Weapon_FireStateDrawCallbackEntry;

extern ScalarFloatView k_floorShakeVerticalBlend;

extern char g_pakPreviewKindLabelSelected[];

extern char *g_pakScannedChannelNumberLabelsByLanguage[];

extern s32 g_creditsReturnToFrontend;

extern char g_pakOperationThreeStateTwoLabel[];

extern FieldRow g_scenarioCatalogueEventActorKinds[];

extern char *g_matchResult5014TextDe;

extern WidgetEventHandler g_typedWidgetEventHandlers;

extern char g_menuOptionBit10EnabledText[];

extern char g_triggeredMotionDispatchTable[];

extern u8 g_savedSecondaryMenuByteOptions[];


extern ScalarFloatView g_controllerEffectTimeRetreatScale;

extern ScalarFloatView g_directionVerticalThreshold;

extern char s_hudPlayerNameFormat[];


extern u8 g_controllerProfileModeBase;

extern char *g_playerOption79StepText;

extern s32 g_frameHeapMarkDepth;

extern const double g_cosinePiHigh;

extern char g_menuOptionBit14EnabledText[];

extern char g_pakOperationFourStateThreeLabel[];

extern char s_staticLitGeometryResourceTag[];

extern ImageTableEntry g_animationEventEffectDescriptors[];

extern char g_playerGroundViewAngleParameters;

extern char g_focusUnlockLabelText[];

extern s32 g_profileGameSpeedSelection;


extern char g_SelectPromptTextGroupOneCase14Text[];

extern u8 g_savedSecondaryMenuByteOptions[];

extern const f64 g_cosinePolynomialCoefficients[5];

extern char *g_matchResult5019TextDe;

extern f32 g_inactiveCollisionShapeShadowRadius;

extern const char g_fmtSpaceDec3[];

extern char *g_playerSettingsSecondaryListLabels[];

extern char g_menuOptionBit5EnabledText[];

extern s32 g_movingCallbackRomEntry;

extern SessionInitializeHandler g_sessionInitializeHandlers[];

extern s32 g_frameHeapBufferIndex;

extern u64 g_videoManagerThreadStack[512];

extern u32 g_sourceBlueMask;

extern char alLoadParam_Address;

extern char g_actionDrawRomEntry;

extern u8 g_gameSettingsVolumeBytes[];

extern char g_fragTagOnLabelText[];

extern f32 g_sceneTransitionCinemaResponseDe;

extern s32 g_particleActorDefinition;

extern char g_pakOperationOneStateFourLabel[];

extern char g_pakConfirmationDefaultLabel[];

extern char g_actorMatrixPool;


extern u32 g_sourceRedMask;

extern u64 __osCurrentTime;

extern char *g_profileRank0LocalizedTitles[];

extern const f32 g_playerImpactHorizontalDamping;


extern char g_pakOperationFiveStateTwoLabel[];

extern MenuChoiceEventHandler g_settingsColumnEventHandlers;

extern s32 g_stdioResourceCloseRomEntry;

extern s32 g_team1SelectedNotice;

extern char *g_matchResult5002UnplayedTextDe;

extern FieldRow g_alternatePlayerSettingsEventActorKinds[];

extern char g_pakAlternateReadyDialogResource[];

extern char g_sceneUnpackRequestSpare[];


extern f32 g_teamWheelScalePoolPrefix;

extern u32 g_cartridgeRomBaseAddress;

extern u8 g_savedPlayerModelLighting[];

extern s32 g_destinationColorIndex;

extern char *g_profileRank8LocalizedTitles[];

extern ALHeap *g_audioHeap;



extern s32 g_stdioResourceWriteRomEntry;

extern OSMesgQueue g_resourcePagerCompletionQueue;




extern f32 g_frameHeapLowUsageStats[3];

extern FieldRow g_equipmentEventIds[];

extern f32 g_playerSourceEffectDuration;

extern s32 alAuxBusParam_Address;

extern char *g_toggleListSetLabel[];

extern char g_SelectModalPromptLabelCase1Text[];

extern char Gastate_AnimationResourceCallbackEntry;

extern char g_SelectPromptTextGroupTwoCase1Text[];

extern char g_geometryInitialScaleMatrix;

extern char *g_profileRank4LocalizedTitles[];

extern char g_triggeredUpdateRomEntry;

extern volatile s32 g_staticDataRegionStart;

extern s32 alMainBusParam_Address;

extern s32 g_menuMusicPreviewSelection;

extern s32 alAuxBusPull_Address;

extern char g_menuOptionBit10DisabledText[];


extern char g_SelectPromptTextGroupThreeCase13Text[];

extern unsigned char g_primitiveAlphaOverride;

extern s32 g_sixChoiceMenuActorKinds;

extern char g_overlayCodeRegionByteCount;

extern s32 g_typedWidgetEventActorKinds;

extern s32 g_artsendTextureSelectionChanged;

extern char g_gameThread[];

extern const f64 k_xmathFloorIntegralLimit;

extern char g_staticJumpTableRegionStart;

extern s32 g_frontendViewportHeight;

extern ParticleContactStateLayout g_particleContactState;

extern int g_geometryViewEffect;

extern u32 g_sourceAlphaMask;

extern char *g_matchResult5015TextDe;

extern s32 g_pakPromptKindNinePending;

extern FieldRow g_gameOptionsEventKinds[];

extern s32 g_controllerReturnResourceRange;

extern char g_pakOperationThreeDefaultLabel[];

extern s32 g_actionStateTransitionPending;

extern WidgetEventHandler g_overlaySlotEventHandlers;

extern int g_messageBufferAllocationLabelStorage;

extern char g_menuOptionBit12DisabledText[];

extern u8 *g_destinationPixelIndexBuffer;

extern char g_menuOptionBit8EnabledText[];

extern Entry190 g_characterHealthBonuses[];

extern char g_SelectPromptTextGroupFourCase4Text[];

extern char g_pakScannedChannelManagerHeading[];

extern unsigned char g_languageMenuAlternateTextTable;

extern f32 g_playerMatchCountdownSpriteOffsets[];

extern char g_bootstrapThread[];

extern char g_menuOptionBit11EnabledText[];

extern f32 g_wrappedValueLowerConstants[2];

extern s32 g_playerSequenceCompletionPending;

extern s8 g_profileSlotSettingsByte7B[];

extern s32 g_materialGroupCount;

extern s32 g_artsendPreviousFrameHoldCount;

extern s32 g_artsendTextureViewerFrameCount;

extern FieldRow g_playerCountEventIds[];

extern char g_Cartridge_RunReadWorkerPackedAddress24;


extern f32 g_playerTargetFacingDistanceLimits[];

extern char *g_profileRank17LocalizedTitles[];

extern char g_cameraViewDisplayListFirst;

extern s32 g_playerStatisticsAccumulatedKills[][100];


extern char g_pakConfirmationActiveLabel[];


extern s32 g_characterSelectionEventIds;

extern char g_pakPortOnePrompt_de[];

extern char g_scenarioCatalogueLinkedWidgetIds;

extern u8 g_debugLinkHandshakeControl;

extern f32 g_playerMatchCountdownStandardPosition[];

extern StateFlags *g_collisionProbeActorOne;

extern char g_SelectPromptTextGroupFiveCase8Text[];

extern char g_frontendVideoModeRenderConfigsFirstZ;



extern char *g_playerAimCandidateActors[];


extern FieldRow g_resultsActorEventIds[];

extern char g_SelectPromptTextGroupThreeCase4Text[];

extern s32 g_controllerPakProbePending[];

extern u8 g_sceneMaskLabelTable0x10[];

extern s32 g_buttonWidgetEventIds;

extern char *g_matchResult5037TextDe;

extern char *g_matchResult5005TextEu[];


extern s8 g_profileSlotResetFlags[];


extern char *g_matchResult5037TextEu[];

extern char g_SelectPromptTextGroupOneCase12Text[];

extern s32 g_selectedLevelId;

extern u8 g_gameSettingsTwoPlayerScreenPreference;

extern s32 g_Cache_RunResourceLoadWorkerPackedAddress24;

extern unsigned char g_languageMenuTextTable;


extern s32 g_schedulerFrameCountdown;

extern s32 __osBaseCounter;

extern float g_attachmentParticleLifetimeBase;

extern u8 g_sceneMaskLabelTable0x20[];

extern char *g_matchResult5012TextEu[];

extern char g_SelectPromptTextGroupFiveCase4Text[];

extern f32 k_screenMessageValueIncreaseMarker;

extern char g_controllerQueryStatus[];

extern s32 g_controllerPakProbeActive;


extern f32 g_playerMatchCountdownAlternatePosition[];

extern float g_attachmentParticleLifetimeScale;

extern char g_initialOpenDialogMenuResource[];

extern char g_SelectPromptTextGroupFiveCase12Text[];

extern s16 g_audioTransformFirstUpperBand;

extern char g_ownerModeOtherText[];

extern char g_pakStatusSecondaryLabel[];

extern FieldRow g_trialCatalogueEventIds[];

extern s32 g_overlaySlotEventActorKinds;

extern s32 g_controllerInitializationMessage;

extern char addrLow_Track_SolveSplineSecondDerivatives;

extern int g_cachedSurfaceNormal;

extern char g_modelEditorApplyToAllDisabledText[];

extern IntrusiveList g_resourcesByAddress;

extern char *g_matchResult5031TextEu[];

extern s32 g_frameHeapsAllocated;

extern char g_SelectPromptTextGroupOneCase1Text[];

extern u8 g_debugLinkAuxiliaryControl;

extern char g_menuOptionBit9EnabledText[];

#include "COMMON/AUDIO_QUEUES.H"

extern char g_playerMenuDialogRomResource[];

extern s32 g_sourceColorIndex;

extern int g_stdioResourceReadyCookie;

extern char g_profileModeTwoPlayedLevels[];

extern int g_imageSwizzleEnabled;

extern const float g_sequenceSignedTickConversionLimit;

extern char *g_matchResult5025TextDe;


extern s16 *g_audioCommandBuffers[];


extern char g_scenarioCatalogueFirstWidgetIds;

extern const f32 g_playerImpactVerticalDamping;


extern s32 g_stdioResourceEndRomEntry;

extern char g_SelectPromptTextGroupThreeCase11Text[];

extern char g_skyEffectProjectionMatrix;

extern char g_menuOptionBit4EnabledText[];

extern char g_localPlayerSetupMenuResource[];

extern void System_CleanupThreadEntry(void);

extern s32 g_smpEventHandlerTables;

extern const char g_pakFormatInt1[];

extern char g_pakChannelNotReadyDialog_SnapshotCheckstatusprompt[];


extern s32 g_motionTrackDecodeTranslation;

extern char g_pakAlternatePromptDefaultLabel[];

extern u8 g_sceneLightDirection[];

extern char *g_matchResult5030TextEu[];

extern char *g_matchResult5027TextEuX[];



extern char *g_matchResult5031TextDe;

extern s32 g_frontendActiveVideoModeIndex;

extern f32 g_regionEdgeCrossDefaultUp;

extern const float g_sineNegativeRoundingBias;

extern s32 g_playerSequenceWindowEnabled;

extern FieldRow g_playModeEventIds[];

extern char g_pakOperationOneStateOneLabel[];

extern char g_dynamicLightPool;

extern FieldRow g_profileResetEventActorKinds[];

extern Extra g_profileGameSpeedPreview;

extern char g_pakOperationThreeStateFourLabel[];

extern struct AudioCacheEntry g_audioDmaCacheEntries[];

extern char g_damageDispatchTable[];

extern const double g_sineInversePi;

extern char g_damageHitRomEntry;

extern f32 g_playerDamageTimerConstants[2];

extern char g_geometryMaterialIntensityTexture;

extern f32 k_screenMessageValueDecreaseMarker;

extern u8 DEBUG_LINK_TRANSMIT_STATUS_BYTE;

extern char g_characterPreviewMenuRomResource[];

extern char g_SelectPromptTextGroupOneCase13Text[];

extern char g_audioDecodedSampleSlots[];

extern s32 g_introSelectionState;

extern u8 g_profileMilestoneCompletionBits[];

extern char *g_playerOption7BText0;

extern FieldRow g_alternatePlayerSettingsEventIds[];

extern FieldRow g_pakProfileHandlerEvents[];

extern char *g_profileRank16LocalizedTitles[];

extern const double g_cosinePiLow;

extern int g_frontendImageRecordValues[];

extern char g_pakPortZeroPrompt_de[];

extern short g_ammoClassIconIds[];

extern s16 DEBUG_LINK_BLOCK_CONTROL_REGISTER;

extern const double g_cosineInversePi;

extern char *g_matchResult5033TextEu[];

extern FieldRow g_playerSettingsEventActorKinds[];


extern Clip g_profilePlayerAnimationChoices[];

extern const double g_cosineRoundingHalf;

extern const float g_sequenceInitialOscillatorValue;

extern void *g_pakNoteLabelSlots[];


extern f32 g_frameHeapHighUsageStats[3];

extern char *g_matchResult5004TextEu[];

extern char g_pakAlternateOperationHeadingLabel[];


extern const f64 k_xmathFractionIntegralBias;

extern const char s_animModelsIndexText[];

extern char g_schedulerThreadEntryAddress;

extern s32 g_fragTagSelectSoundVariant;

extern void *g_frontendResourceImagePool[];



extern u8 *g_sourcePixelIndexBuffer;

extern char g_pakDefaultPreviewActionLabel[];

extern char *g_playerOption7EText0;

extern char *g_playerOption7BText1;

extern char *g_matchResult5027TextEu[];

extern char g_pakChannelNumberFormat[];

extern const float g_lookAtHomogeneousScale;

extern s32 g_pakCancelStateWord;

extern f32 g_audioTransformZeros[];

extern char g_pakOperationFiveDefaultLabel[];


extern char g_pakOperationFourStateFourLabel[];


extern char g_SelectPromptTextGroupFiveCase3Text[];

extern const char s_headerText[];

extern char g_SelectPromptTextGroupTwoCase11Text[];

extern u32 __osFinalrom;

extern const double g_sinePiLow;

extern char g_menuChoiceDisabledLabels[];

extern char *g_matchResult5014TextEu[];


extern char g_profileSecondConfirmationLabel[];



extern const f64 g_audioFrexpRestoreSignThreshold;

extern s32 g_actorBehaviorDispatchModes;


extern char g_SelectPromptTextGroupFourCase12Text[];

struct IntPair;
extern struct IntPair g_osEventMessageBindings[];

extern s32 g_team2SelectedNoticesEu[];

extern struct CacheResourceBlockView *g_pakLoadedNoteResourceHandle;

extern char g_modelEditorApplyToAllEnabledText[];

extern const char g_levelIndexText[];

extern void Frontend_DrawResultModelPreviewDe(char *);

extern int g_frontendActiveState;

extern float g_attachmentParticleEmissionThreshold;

extern char *g_matchResult5017TextEu[];

extern void *g_depthImageBuffer;

extern const char s_animObjectIndexText[];

extern char *g_matchResult5052TextEu[];


extern f32 g_materialCurrentStrengthScales[];

extern char *g_pakSaveMenuProfileChannelLabels[];

extern char g_SetN64_RunGameThreadPackedAddress24[];

extern char g_simpleModelResourceCallbackAddress;

extern s32 g_stdioResourceSeekRomEntry;

extern char g_cameraViewDisplayListSecond_de;


extern s32 g_team2SelectedNoticesEuX[];

extern s32 g_stdioResourceOpenRomEntry;

extern char g_pakOperationThreeStateThreeLabel[];

extern char *g_matchResult5025TextEu[];

extern char *g_pakScannedChannelChoiceLabels[];

extern const f32 g_cosineLargeAngleZero;

extern u32 g_destinationRedMask;

extern char g_SelectPromptTextGroupTwoCase4Text[];

extern f32 g_simpleObjectViewEffectRotationAndHeight;

extern char *g_profileRank12LocalizedTitles[];

extern u8 g_savedPlayerModelLighting[];

extern UnitLight g_pointLightBuffer[];


extern s32 g_controllerPakReinitializePending[];

extern s32 g_listButtonEventActorKinds;


extern char *g_currentDiskPeripheralHandle;

extern s32 g_menuBinaryChoice;

extern FieldRow g_nodePairMenuEventActorKinds[];

extern u8 g_controllerPakPreviewProfileName[];



extern u8 g_controllerReadStatusBytes[];

extern char g_pakOperationTwoStateTwoLabel[];

extern char *g_pakProfileLoadSnapshotChoiceLabels[];

extern FieldRow g_pauseMenuEventIds[];

extern s32 g_pagerStatisticBuffer[];

extern char *g_matchResult5011TextEuX[];


extern char g_pakAllocateMenuFifthResource[];

extern Texture *g_combineBoundImage;

extern const char g_simpModelsIndexText[];

extern char g_profileFirstConfirmationLabel;

extern FieldRow g_matchOptionsEventCodes[];

extern f32 g_platformCollisionHeightOffsets[];

extern const unsigned char s_virtualRegionText[15];

extern char *g_matchResult5023TextDe;

extern s32 g_frontendRenderStateInitialized;

extern const f32 g_cameraFrustumAngleConstants[];

extern const float g_reverbModulationWrapLimits;

extern u32 g_destinationBlueMask;



extern const f32 g_cameraFrustumHeightScale;

extern char g_initialDialogRowOneResource[];

extern f32 k_xmathAtanQuadrantOffsets[4];

extern FieldRow g_tabOptionsEventKinds[];

extern char g_menuOptionBit13EnabledText[];

extern s32 g_profileSlotNameFormat;

extern f32 g_particleOwnerImpactRadiusAndStrength[];

extern float g_regionCachedEdgeDefaultUp;

extern void *g_pakSnapshotResourceHandle;

extern ScalarFloatView k_floorShakeHorizontalScale;


extern u16 g_audioTransformBandEnds[];


extern char g_menuOptionBit7DisabledText[];

extern char g_collisionSurfaceExcludedFromTrace[];

extern f32 g_weaponWheelScalePoolPrefix;

extern char *g_matchResult5017TextDe;

extern char g_menuOptionBit15DisabledText[];

extern float g_scaledMatrixHomogeneousScale;

extern int g_frontendScreenModePaletteDefault;

extern char g_controllerPakNotReadyDialogResource[];

extern u16 g_trialCatalogueStageIdLowHalves[];

extern const float g_perspectiveFloatHalfAngleScale;

extern char g_SelectPromptTextGroupOneCase5Text[];

extern ScalarFloatView g_playerDamageTimerFrameDefault;

extern char g_SelectPromptTextGroupFiveCase7Text[];

extern s32 g_team0SelectedNoticesEu[];

extern WidgetEventHandler g_listButtonEventHandlers;

extern char *g_profileRank11LocalizedTitles[];

extern u8 g_controllerPakPreviewName[];

extern s32 g_controllerSnapshotProfileValues[4];

extern char *g_matchResult5009TextEu[];

extern f32 g_hudSpriteHorizontalOffsets[];

extern s32 g_frontendKeepCurrentVideoModeOnce;

extern unsigned char g_materialIntensityMaskTexture[];

extern s32 g_pakPreviewNameText;


extern char s_frontendResourceOpenMode;

extern ScalarFloatView g_simpleObjectScaleTransitionTarget;

extern f32 g_weaponChargeEntryCueAndRate[2];

extern u32 g_sourceGreenMask;

extern char g_actionEnterRomEntry;

extern s16 DEBUG_LINK_DATA_REGISTER;

extern char g_pickupSpecialDefinitions;

extern s32 g_creditsSkipRequested;


extern char g_controllerAccessMessages[];

extern char g_SelectPromptTextGroupTwoCase2Text[];

extern char g_ownerModeOneText[];

extern const char s_flyModeOffText[];


extern char g_deviceDrawRomEntry;

extern int g_spawnCallbackRomEntry;

extern s32 g_pakDefaultPreviewNameText;

extern s32 g_playerAnimatedSpriteScaleX;

extern f32 g_playerBaseAndEasyMovementFactors[];

extern FieldRow g_profileResetEventIds[];

extern s32 g_controllerInitializationQueue;

extern char *g_profileRank2LocalizedTitles[];


extern char *g_matchResult5010TextEu[];

extern char g_Statinst_BuildLitGeometryResourceAddress;

extern s32 g_frontendCurrentVideoModeIndex;

extern u32 g_timerLastProcessorCount;

extern WidgetEventHandler g_extraOptionsEventCallbacks;

extern u32 g_displayListCapacityEu;

extern FieldRow g_germanMatchMenuEventIds[];


extern char s_menuByteOptionValueFormat[];



extern WidgetEventHandler g_sliderWidgetEventHandlers;

extern char g_pakStatusDefaultLabel[];

extern char g_scene_BuildPlacedInstancesEntry[];

extern char *g_profileRank5LocalizedTitles[];

extern int g_frontendScreenModePaletteOne;

extern s32 g_audioTransformInputStream;

extern char *g_matchResult5002PlayedTextDe;

extern f32 g_centsToPitchRatioConstants[];

extern f32 k_playerMenuSpriteScaleConstants;

extern u8 g_frontendSavedVideoModeIndex;

extern char g_SelectPromptTextGroupFourCase1Text[];

extern WidgetEventHandler g_optionsTransitionEventCallbacks;

extern f32 g_weaponActionFiveFeedbackConstants[];

extern const f64 g_audioFrexpLowerLimit;

extern char g_modelEffectPool;


extern char *g_profileRank13LocalizedTitles[];

extern char g_SelectPromptTextGroupThreeCase3Text[];

extern char g_schedulerThreadStack[];



extern char g_pakOperationFiveStateOneLabel[];

extern f32 g_ribbonNodeTransformDecayConstants[];

extern char *g_pakSaveMenuNoteSlotChoiceLabels[];


extern s32 g_team0SelectedNotice;

extern u16 g_pagerPageCounters[];

extern WidgetEventHandler g_buttonWidgetEventHandlers;

extern FieldRow g_compactOptionsEventKinds[];


extern char g_SelectPromptTextGroupThreeCase2Text[];


extern char g_SelectPromptTextGroupFourStateOtherText[];

extern char g_playerFloatMovementParameters;

extern char g_pakSnapshotCapacityPromptEuX[];

extern char g_SelectPromptTextGroupFourCase5Text[];

extern int g_textureCacheResource;

extern unsigned char g_controllerPakEnabledBytes[];


extern char *g_profileRank15LocalizedTitles[];

extern s32 g_primitiveRenderFlagSelect3000;

extern f32 g_audioSampleTimeConstants[2];


/* Character IDs: movement also reads the third word at g_fragTagModelId. */
extern s32 g_playerSpecialModelIds[];

extern char g_pickupHealthDefinitions;

extern s32 g_frontendImageRecordFlags[][13];

extern s32 g_optionsTransitionEventCodes;

extern char *g_playerOption79ZeroText;

extern const double g_cosineRoundingSignBoundary;

extern char *g_matchResult5022TextDe;

extern char *g_pakProfileLoadProfileChoiceLabels[];

extern s32 g_menuOptionBit0EnabledText;

extern s32 g_overlaySlotEventIds;

extern char g_playerFloatViewAngleParameters;

extern f32 g_navigationFarthestDistanceAndArrivalLimits[];

extern TextEntry g_focusUnlockEntries[];

extern const char s_allocText[];

extern const char g_pakFormatInt3[];

extern char *g_matchResult5024TextEu[];

extern char g_playerOption7CText0[];

extern char g_SelectPromptTextGroupFiveCase2Text[];

extern s32 g_numericWidgetEventIds;

extern FieldRow g_resultsEventKinds[];

extern s32 g_flickerWidgetEventActorKinds;

extern char g_playerModelResourceTag[];

extern ScalarFloatView g_playerDamageTimerFrameScale;

extern s32 g_campaignCompletionMenuEnabled;

extern Ctx g_piInterruptManager;

extern f32 g_playerJumpLandingHeightLimits[2];

extern char g_playerSwimViewAngleParameters;

extern char *g_matchResult5016TextDe;

extern char g_playerMenuStepFormatGerman[];

extern FieldRow g_soundOptionsEventKinds[];

extern QuadN64EngDrawNumericWidgetChildren g_osExceptionPreamble[];

extern s32 g_timerServiceCounter;

extern u8 g_gameSettingsMode1E;

extern s32 alResampleParam_Address;

extern s32 g_pakNamePromptAccepted;

extern char g_SelectPromptTextGroupFiveCase14Text[];

extern f32 k_MenuBlendUnitConstants[];

extern void * Libc_FormatStringOutputCallback(void * destination, const char * source, int byteCount);

extern unsigned short g_audioDecodedBlockCounter;

extern char g_musicPreviewMenuResource[];

extern char *g_matchResult5023TextEu[];

extern char g_pakStatusPrimaryLabel[];

extern u8 g_controllerPakPreviewProfileFlags;

extern const f64 g_audioFrexpZero;

extern WidgetEventHandler g_frameAnimationEventHandlers;

extern char g_playerDeathDialogSlotFourth;

extern s32 g_playerTrackFiftyCallbacks;


extern struct
{
  u16 value;
} g_pakProfileSavedWordOne;

extern char g_frontendVideoModeRenderConfigsFirstPad1;

extern UnitVtx g_playerDeathEffectVertices[];

extern char *g_matchResult5034TextEu[];

extern u64 g_systemClockFrequency;

extern char g_SelectPromptTextGroupFourCase13Text[];

extern char *g_pakSaveMenuSnapshotChannelLabels[];

extern FieldRow g_titleButtonColumnEventIds[];

extern char *g_matchResult5028TextEu[];

extern char g_pakOperationFourDefaultLabel[];

extern s64 g_schedulerRdpTaskStartTime;

extern s32 g_pakSnapshotNoControllerPromptUsRev1;

extern s32 g_artsendTextureViewerPaletteTable;

extern char g_SelectPromptTextGroupTwoCase12Text[];

extern char g_controllerRumbleNodes[];

extern s32 g_materialInstanceCount;

extern char g_SelectModalPromptLabelStateOtherText[];

extern CVector3 k_turretUpDirection;

extern char g_SelectPromptTextGroupFiveCase5Text[];

extern s32 g_schedulerRdpBufferSetState;

extern const float g_lookAtNormalizeAndFallbackConstants;

extern s32 g_pakAlternateNameSelected;

extern char g_pakOperationFiveStateFourLabel[];

extern s32 g_destinationPixelOffset;

extern s32 g_pakSnapshotNoPakPromptUsRev1;

extern const double g_compressedMarkerDivisionUnsignedBias;

extern const char g_pakWriteScratchNoteName[];

extern u8 g_controllerLastCommand;

struct FrontendVideoModeParameters;
extern struct FrontendVideoModeParameters g_frontendDefaultVideoModes[];

extern u8 g_secondaryMenuByteOptions[];

extern f32 g_encodedTextCursorTiming[];



extern float g_audioResamplerFixedPointUnit;

extern const float g_perspectiveFloatNormalizationLimits;

extern NodeGeometryGroupModelInstances g_materialGroups[];

extern void *g_matchOptionLabelSlots[];

extern char __osThreadTail[];

extern char g_pakNoteIdRepairFailedDialogResource[];

extern char g_sceneResourceRequestSpareDe[];

extern char g_playerAirViewAngleParameters;


extern const f64 g_lowPassFixedPointScale;


extern int g_frontendControllerState;

extern FieldRow g_soundSliderEventIds[];

extern FieldRow g_settingsColumnEventKinds[];

extern s32 g_pakRecheckRequested;

extern char g_damageUpdateRomEntry;

extern s32 g_trialCatalogueNeighborTwo[];

extern char g_nearestPlacedObjectResult;

extern const char g_audioCsplayerText[];

extern ColorEntry g_emacText[];

extern char g_pakOperationTwoStateFourLabel[];


extern char g_actionUpdateRomEntry;

extern f32 k_xmathVectorAngleWrapConstants[2];

extern char g_actorParticleScene;

extern int g_frontendScreenModePaletteTwo;

extern s32 g_selectedProfileHealthOptionEnabled;

extern FieldRow g_settingsColumnEventIds[];

extern f32 g_audioRoundedSampleTimeConstants[2];

extern char *g_profileRank6LocalizedTitles[];


extern s32 g_musicPreviewMenuActive;

extern u8 g_debugLinkTransferControl;

extern f32 g_actorOffsetTransformConstants[];

struct ConversionImageView;
extern struct ConversionImageView *g_conversionSourceImage;

extern FieldRow g_soundOptionsEventIds[];

extern char *g_matchResult5021TextDe;

extern char *g_matchResult5033TextDe;

extern char g_SelectPromptTextGroupOneCase4Text[];

extern char g_SelectPromptTextGroupThreeStateOtherText[];

extern char *g_matchResult5005TextDe;

extern char *g_matchResult5057TextEu[];

extern char g_pagerWorkerRomEntry[];

extern char g_pakNoteIdRepairSucceededDialogResource[];

extern unsigned int g_texturePaletteOverrideEnabled;

extern CheatCode g_encodedCheatDefinitions[];

extern s32 g_sourcePixelOffset;

extern const char g_gameObjectResetAnimInfoText[];

extern char g_videoModeLabels;

extern f32 k_xmathPositiveAngleWrapConstants[2];


extern s32 g_playerViewRenderingEnabled;

extern int *g_weaponIndexedValueTable[];

extern s32 g_playerSpawnSelector;

extern const f64 k_xmathFloorSignBoundary;

extern s32 g_frontendImageFormatTable[][13];

extern char g_pakOperationHeadingLabel[];


extern f32 k_cinemaFadeRequestValue_de;

extern char g_SelectPromptTextGroupFourCase10Text[];

extern s32 g_selectionMenuHandlerKinds;

extern char g_SelectPromptTextGroupThreeCase1Text[];

extern char *g_matchResult5027TextDe;

extern s32 g_triggeredVariantDrawRomEntry;

extern s32 g_multiplayerItemRenderState;

extern s32 g_sliderTransitionEventActorKinds;

extern f32 g_frameHeapLowAllocationStatLowerLimit;

extern WidgetEventHandler g_overlaySlotEventHandlersUs;

#include "SCHED/osscremoveclient.H"

extern EffectPoolNode *g_effectPoolFreeHead;

extern char g_gameOptionOneFOneText;

extern char *g_matchResult5006TextEu[];

extern char g_pakOperationOneStateTwoLabel[];

extern char g_resourcePendingRequests;


extern int g_pakPreviewDepthEightLabel;

extern const char s_simpPartModelText[];

extern const float g_navigationObjectLinkDistanceLimits[];

extern s32 g_team1SelectedNoticesEuX[];

extern char *g_matchResult5029TextDe;

extern s32 g_activeVoiceCount;

extern WidgetEventHandler g_numericWidgetEventHandlers;

extern int __osFaultedThread;

extern FieldRow g_resultsActorEventKinds[];

extern char g_SelectPromptTextGroupOneCase7Text[];



extern s32 g_gameSessionMode;

extern char g_SelectPromptTextGroupThreeCase5Text[];

extern EffectPoolNode *g_effectPoolActiveHead;

extern char g_uiFormattedMessage[];

extern char *g_playerOption7EText1;

extern char *g_profileRank19LocalizedTitles[];

extern u8 g_audioDmaBoundaryWorkaroundFlag[];

extern FieldRow g_profileResetEventIdsEu[];

extern char addrLow_Libsn_DisableInterrupts;


extern struct CVector3_t g_particleTertiaryContactPosition;

#include "libultra/audio/seqp.h"

extern char *g_matchResult5052TextDe;


extern char g_profileModeZeroLabel;

extern char g_actionMotionDispatchTable;

extern u16 *g_frontendResourceScreenFlags;

extern char g_ownerNotificationEnabledLabels[];


extern s32 g_sliderWidgetEventIds;

extern s32 g_weaponReleaseSpinApproachRate;

extern s32 g_controllerSetupSaved;

extern s32 g_attractTimeoutEnabled;

extern FieldRow g_resultsEventIds[];

extern char *g_matchResult5022TextEu[];

extern char g_playerMenuStepFormat[];

extern int g_cachedSurfaceNormalNode;

extern const f64 k_xmathCeilSignBoundary;

struct StateFlags;
extern struct StateFlags g_equipmentOptionWidgetIds[][19];

extern f32 g_playerOwnerHeightEffectTuning[];


extern SineTable g_actorMatrixWobbleSamples;

extern s32 g_secondStatusBarMoverScript;

extern s32 g_modelBatchPass;

extern char g_bloodModeText2[];

extern char g_SelectPromptActionHeadingStateOtherText[];

extern const char g_longAndIntFormats[];

extern char g_pakOperationFourStateTwoLabel[];

extern ScalarFloatView k_floorShakeHorizontalBlend;

extern ScalarFloatView k_floorShakeVerticalScale;


extern char *g_profileRank3LocalizedTitles[];

extern f32 k_nearbyPlayerBlastConstants[];

extern s32 g_trackResourceDirectoryKey;

extern s32 g_textBatchStyle;

extern u32 g_displayListCapacityUsRev1;

extern s32 g_pointLightBufferOffset;

extern char *g_matchResult5015TextEu[];

extern char g_horizontalEdgeNormalizeScale;

extern s32 g_optionsTransitionActorKinds;

extern void (*g_readSourceColor)(void);

extern char g_SelectPromptTextGroupFiveCase6Text[];

#include "ONSCRN.H"

extern s32 g_frameHeapBufferBytes;

extern char g_gameOptionOneFZeroText;

extern char g_SelectPromptTextGroupTwoCase14Text[];

extern char g_pakAlternateActionLabel[];

extern char *g_profileRankTitles[];

extern s32 g_characterSelectionEventActorKinds;

extern s32 g_matchSetupMenuResource;

extern char g_pakOperationDescriptionLabel[];

extern char *g_playerOption7DText1;

extern s32 *g_textureResourceSectionRoot;

extern const f64 g_sinePolynomialCoefficients[5];

extern char *g_matchResult5053TextDe;

extern char Weapon_FireStateEnterCallbackEntry[];

extern s32 g_modelBatchResourceCount;

extern SlotVirtualReleaseVirtualRegion g_pagerPageMappings[];

extern void (*g_writeDestinationIndex)(void);

extern char g_scenarioCatalogueSecondWidgetIds;

extern char g_SelectPromptTextGroupFiveCase9Text[];

extern struct
{
  u16 value;
} g_pakProfileSavedWordTwo;

extern char *g_matchResult5001TextEu[];

extern FieldRow g_compactOptionsActorKinds[];

extern const char g_simpModelText[];

extern void System_VideoManagerThreadEntry(void *arg);

extern char g_SelectPromptTextGroupTwoCase7Text[];

extern char g_pakPortThreePrompt_de[];

struct PlayerSettingsOptionRow;
extern struct PlayerSettingsOptionRow g_characterPortraitRecords[];

extern char g_menuOptionBit15EnabledText[];



extern float g_reverbDeltaScale;

extern OSViMode g_schedulerAlternateVideoMode;

extern f32 g_hiddenStaticObjectShadowRadius;

extern struct SharedMovement g_playerGroundMovementParameters;


extern s32 g_resourceSlotActivity[];

extern s32 g_controllerAudioThreadId;


extern CMemEntry *g_resourceCompactionEntries;

extern const char g_pakSingleSaveBlockName[];

extern s32 g_teamScoringEnabled;

extern char g_SelectPromptTextGroupFourCase11Text[];

extern char g_playerDeathDialogSlotFirst;

extern const float g_sinePositiveRoundingBias;

extern char g_spawnActorDispatchTable[];

extern struct
{
  u16 value;
} g_pakProfileSavedWordThree;

extern s32 g_pakSnapshotLowSpacePromptUsRev1;

extern u8 DEBUG_LINK_RECEIVE_STATUS_BYTE;


extern const float g_perspectiveFloatDepthAndRangeLimits;

extern u32 g_destinationGreenMask;

extern float g_trackSmoothInterpolationConstants;

extern s32 g_playerTrackFiftyRequest;

extern OSTask g_signalProcessorTaskCopy;

extern char g_SelectPromptTextGroupTwoCase8Text[];

extern char *g_profileRank18LocalizedTitles[];

extern char g_pakActionLabel[];

extern char *g_matchResult5034TextDe;

extern char g_primaryRenderMicrocodeText;

extern s32 g_flickerWidgetEventIds;

extern f32 k_barrelEffectQuaternionValues[];

extern u8 g_particleSpriteViewMode;

extern f32 k_barrelSecondarySoundRandomMinimum;

extern s32 g_trialCatalogueNeighborOne[];

extern FieldRow g_confirmationMenuEventIds[];

extern u8 DEBUG_LINK_BLOCK_STATUS_BYTE;

extern char alAdpcmPull_Address;


extern char g_SelectPromptTextGroupThreeCase10Text[];

extern OSIoMesg g_videoTimerEvent;

extern char g_SelectPromptTextGroupFiveCase11Text[];

extern s32 g_litGeometryResourceKeyFlags;

extern char g_SelectPromptTextGroupTwoCase6Text[];

extern u8 g_playerSettingsRecords[];

extern char g_SelectPromptTextGroupThreeCase12Text[];

extern char *g_matchResult5011TextEu[];

extern char s_nodeAlternateFieldText[];

extern char g_pakOperationTwoStateThreeLabel[];

extern char g_SelectPromptTextGroupFourCase15Text[];

extern FieldRow g_trialOptionsEventKinds[];

extern s16 g_voiceAttenuationTable[];

extern f32 g_unreferencedFloatTable_de[];

extern char *g_matchResult5030TextDe;

extern char *g_playerOption7AZeroText;

extern s16 DEBUG_LINK_MODE_REGISTER;

extern const f64 k_xmathFractionSignBoundary;

extern float g_regionUpQuaternionConstants[];

extern char g_primaryRenderMicrocodeData;

extern s32 g_pakAlternateOptionEnabled;

extern char g_playerDeathDialogSlotSecond;

extern char g_pickupWeaponDefinitions;

extern char *g_matchResult5004TextDe;

extern char g_movingMotionDispatchTable[];

extern char g_playerDefaultBehaviorTable;

extern s32 g_trialCatalogueNeighborZero[];

extern char g_initialDialogRowTwoResource[];


extern s32 g_pointLightSavedBufferOffset;

extern s32 g_frontendArchiveResident;

extern FieldRow g_pakProfileHandlerKinds[];

extern s32 g_resultReplayPending;

extern s32 g_extraOptionsEventCodes;

extern s32 g_frameHeapHighCursor;

extern char g_SelectPromptTextGroupThreeCase8Text[];


extern char *g_matchResult5010TextDe;

extern u8 g_savedSecondaryMenuByteOptionTwo[];

extern s32 g_modelInstanceQueueCount;

extern char g_pakOperationThreeStateOneLabel[];


extern float g_reverbRatioBase;

extern char **g_creditsLocalizedLines[];

struct StateFlags;
extern struct StateFlags g_equipmentSecondaryWidgetIds[][19];

extern u8 g_debugLinkModeControl;

extern s32 g_textClipBottom;

extern char g_SelectPromptTextGroupFourCase14Text[];

extern f32 g_actorAimBasisConstants[];

extern const char g_gameObjectAnimIndexText[];

extern void *g_pickupNavigationGoalList;

extern s32 g_team1SelectedNoticesEu[];

extern u16 g_gamePackedOptions;

extern char g_actorBehaviorActionConfigs;

extern u8 g_worldSnapshotNoteData[];

extern char *g_matchResult5024TextDe;

extern char g_menuOptionBit2DisabledText[];

extern char g_pakPreviewKindLabelDefault[];

extern s32 g_team2SelectedNotice;

extern s32 alSaveParam_Address;



extern s32 g_textBatchCount;

extern char g_SelectPromptTextGroupTwoCase15Text[];

extern s32 g_profilePrimaryMenuResource;

extern FieldRow g_soundSliderEventKinds[];

extern char g_pakStatusPromptAlternate[];

extern s32 g_artsendTextureViewerReservedWord;


extern char *g_profileRank7LocalizedTitles[];

extern CharacterScreenCell g_characterSelectionMenuOptionCells[][9];

extern int g_joinRequestRanks[];

extern u32 g_displayListCapacityUs;


extern s32 g_team3SelectedNotice;

extern f32 g_regionNormalDefaultUpY;

extern char g_SelectPromptTextGroupThreeCase14Text[];

extern void (*g_writeDestinationColor)(void);

extern char *g_playerSettingsSecondChoiceText[];

extern s32 g_pakDialogEventIds;

extern char *g_matchResult5029TextEu[];

extern s32 g_debugLinkTransferFailed;

struct EntryFrontendRefreshTrialCharacterPreview;
typedef struct EntryFrontendRefreshTrialCharacterPreview EntryFrontendRefreshTrialCharacterPreview;

extern s32 g_sliderTransitionEventIds;



extern const float g_sequenceFallbackOscillatorValue;

extern char g_SelectPromptTextGroupFiveCase15Text[];

extern int g_artsendTextureResetWordTwo;

extern s32 g_regionEdgeDefaultUpZ;

extern s32 g_expansionMemoryIntroEnabled;

extern char g_SelectPromptTextGroupTwoCase9Text[];

extern s32 g_sliderWidgetEventActorKinds;

extern int g_pakPreviewDepthThirtyTwoLabel;

extern char g_menuOptionBit7EnabledText[];

extern ScalarFloatView g_controllerEffectTimeAdvanceScale;

extern char g_pakAllocateMenuSecondResource_eu_x[];

extern s32 g_mode4TextureEffectState;


extern s32 g_menuElementLoadCount;

extern f32 g_playerReserveBounds_de[2];

extern FieldRow g_pauseMenuEventActorKinds[];

extern f32 k_spawnActionMinimumDelay;

extern GameState g_gameStateBlock;

extern u64 g_schedulerAudioTaskStartTime;

extern char g_resourceCompletionRequests;

extern s32 g_selectionMessageStage;

extern char *g_matchResult5005TextEuX[];

extern char g_menuOptionBit14DisabledText[];

extern char g_sceneEffectPool;

extern u32 g_pagerFirstSlotAge;

extern s32 g_sound_GetSampleDmaWindowAddressEntry;

extern char g_SelectPromptTextGroupOneCase9Text[];

extern char *g_profileRank10LocalizedTitles[];

extern const char g_simpPartModelsIndexText[];

extern QueueRec g_dialogDecodeStreamRecord[];

extern s32 g_barrelSecondaryFlagSoundTable[];

struct ScalarPair;
extern struct ScalarPair g_fastHealthRegenerationTuning;

extern s32 g_creditsCurrentLine;

extern const char g_pakReadScratchNoteName[];

extern char g_playerFlag82OffText[];

extern char *g_matchResult5016TextEu[];

extern s32 g_numericWidgetEventActorKinds;

struct ScalarPair;
extern struct ScalarPair g_movementHealthRegenerationTuning;

extern const double g_sinePiHigh;

extern char g_profileStatisticsNumberFormat[];

extern WidgetEventHandler g_characterSelectionEventHandlers;

extern char g_simpleObjectModelResourceTagData;

extern const double g_cosineQuadrantOffset;

extern char *g_matchResult5020TextDe;

extern s32 g_textClipTop;

extern const f64 k_xmathCeilRoundUpUnit;

extern char *g_matchResult5026TextEuX[];

extern char *g_matchResult5007TextDe;

extern char *g_matchResult5007TextEu[];

extern WidgetEventHandler g_flickerWidgetEventHandlers;

extern char *g_matchResult5013TextDe;

extern char g_SelectPromptTextGroupOneCase10Text[];

extern char g_SelectPromptTextGroupThreeCase15Text[];

extern char *g_playerSettingsPrimaryListLabels[];


extern char *g_matchResult5008TextEu[];

extern IntrusiveList g_sceneEffectSpawnList;

extern WidgetEventHandler g_sixChoiceMenuEventHandlers;

extern u8 g_soundEffectsVolumeOption_PakFormatvolumeslotone;

extern s8 g_pakPreviewNoteType;

extern char g_SelectPromptTextGroupFourCase3Text[];

extern const f64 k_xmathCeilIntegralLimit;

extern char s_ammoPickupPluralSuffix[];


extern s32 g_resourceHashBucketCount;

extern char g_triggeredTransformRomEntry;


extern char g_pakAlternateOperationDescriptionLabel[];

extern EffectPoolNode *g_effectPoolActiveTail;

extern f32 g_hudSpriteVerticalOffsets[];

extern char *g_matchResult5001TextDe;

extern s32 g_buttonWidgetEventActorKinds;


extern f32 g_motionQuantizationRangeAndUnit[2];

extern s32 g_initialMatchStartPending;

extern char g_SelectPromptTextGroupTwoCase10Text[];

extern WidgetEventHandler g_overlaySlotEventHandlersEuX;

extern s32 g_regionNormalDefaultUpZ;

extern f32 g_frameHeapHighAllocationStatLowerLimit;

extern char g_menuOptionBit11DisabledText[];

extern FieldRow g_tabOptionsActorKinds[];

extern char g_SelectPromptTextGroupOneCase11Text[];

extern u8 g_connectedControllerProfileCount;

extern s32 g_menuSavedAudioSelection;

#include "COMMON/MEMORY_STREAM_BUFFER.H"

extern char g_actionEnterDispatchTable[];

extern OSPiHandle g_diskPeripheralHandle;

extern char s_actorAnimationResourceTag;

extern const f64 k_xmathFloorIntegralBias;

extern char g_gameThreadStack[];

extern const f64 g_audioFrexpHalvingScale;

extern char g_actorAnimatedModelResourceTuning;

extern char g_SelectPromptTextGroupOneCase3Text[];


extern s32 g_team3SelectedNoticesEuX[];

extern const f64 g_lowPassCoefficientScale;

extern WidgetEventHandler g_overlaySlotEventHandlersDe;

extern s32 g_artsendTextureViewerEntryTable;


extern char g_pagerPageStorage;

extern char g_fragTagOffLabelText[];

extern char g_menuOptionBit6EnabledText[];

extern char g_pakPreviewKindLabelProfile[];

union PagerSlotLookupStorage;
extern union PagerSlotLookupStorage g_pagerSlotLookupStorage;

extern const char s_animObjectInfoText[];

extern WidgetEventHandler g_selectionMenuHandlers;

extern s32 g_textClipRight;

extern const double g_sequenceSecondsToTicksUnsignedBias;

extern char g_SetN64_RunBootstrapThreadPackedAddress24[];

extern char *g_matchResult5018TextDe;

extern s32 g_systemBootMarkerComparison;

extern ScalarFloatView g_controllerEffectRandomRangeScale;

#include "COMMON/LEGACY_COLLISION_ACTOR.H"

extern signed char g_geometryMaterialLightDirection[3];

extern unsigned char g_controllerPakStatusBytes[];

extern u8 g_imageLowBoostNibbleRemap[];

extern char g_pakChannelFallbackDialogText;

extern char g_textureVariationBypassEnabledLabels[];

extern char g_menuOptionBit13DisabledText[];

extern int g_pakProfileLoaded;

extern f32 g_audioTransformBandSteps[];

extern s32 g_firstStatusBarMoverScript;

extern char g_menuChoiceEnabledLabels[];

extern s32 g_playerReactionReserveApproachRate;

extern char g_SelectPromptTextGroupThreeCase9Text[];

extern char g_pagerCartridgeData[];

extern char *g_pakScannedChannelNumberLabels[];

struct UnitVtx;
extern struct UnitVtx g_playerAimMarkerVertices[];


extern u8 g_secondaryMenuByteOptionTwo[];


extern f32 g_particleYawMatrixScratch[16];

extern char g_sceneLevelNameRequestTagDe;

extern CacheEntry *g_audioCacheCountdownHead;

extern u32 g_displayListCapacityDe;

extern WidgetEventHandler g_sliderTransitionEventHandlers;

extern const char g_pakFormatInt06[];

extern float g_maskedImageRectangleCoordinateScale;

extern char s_nodeDefaultFieldText[];

extern char g_ownerNotificationDisabledLabels[];

extern FieldRow g_scenarioCatalogueEventIds[];

extern s32 g_pakUseDefaultPreviewLabels;

extern u8 g_imageHighBoostNibbleRemap[];

extern FieldRow g_residentActorEventKinds[];

extern ScalarFloatView g_simpleObjectScaleTransitionFactor;

extern const float g_compressedMarkerQuarterNoteUnit;

extern char g_textureVariationBypassDisabledLabels[];

extern char g_bloodModeText1[];


extern s32 g_team0SelectedNoticesEuX[];

extern float fabsf(float);

extern s32 g_combinePipelineSyncPending;

extern unsigned char g_primitiveAlphaOverrideEnabled;

extern int g_pakPreviewDepthSixteenLabel;

extern char *g_pakSaveMenuProfileChoiceLabels[];

extern s32 g_trialCatalogueNeighborThree[];

extern char g_playerLeapMovementParameters;

extern char g_menuOptionBit6DisabledText[];

extern char *g_matchResult5011TextDe;

extern f32 k_turretInvertedAimAngle;

extern char g_menuOptionBit8DisabledText[];


extern char g_botControllerProfile[];

extern CVector3 g_actorRadialDirections[8];

extern FieldRow g_matchOptionsActorKinds[];

extern u8 g_controllerPresenceBits[];

extern char g_turretDispatchTable[];

extern s16 DEBUG_LINK_HANDSHAKE_REGISTER;

extern WidgetEventHandler g_overlaySlotEventHandlersEu;

extern FieldRow g_trialCatalogueEventKinds[];

extern s32 g_ctfWaitingPlayerFlag;

extern void *g_slotSelectionTextReferenceShared1[];

extern char g_SelectPromptTextGroupThreeCase6Text[];

extern char g_pakAdjustMenuChoiceResourceFirst[];

extern s32 g_menuEventCount;

extern int g_frontendScreenModePaletteThree;

extern char g_profileModeThreePlayedLevels[];

extern MenuPointerEntry g_encodedCheatLabelTable[];

extern u64 g_schedulerGraphicsTaskStartTime;

extern char g_lightAnimationOffsetTable[];

extern char g_SelectPromptTextGroupFourCase7Text[];

extern char g_menuOptionBit3EnabledText[];

extern RecGobjinstSampleBoneTranslation g_frontendVideoModeRenderConfigs[];

extern char g_SelectPromptTextGroupThreeCase7Text[];

extern Shield g_damageBoneBoundsShield;

extern char g_profileModeOneLabel[];

extern float g_reverbUnityRatio;

extern s32 g_particleQuadDisplayListState;

extern char *g_matchResult5009TextDe;

extern s32 g_motionTrackDecodeRotation;

extern char *g_matchResult5026TextDe;

extern s16 DEBUG_LINK_AUXILIARY_REGISTER;

extern f32 k_gameSpeedSelectionOffsets[];

extern f32 g_playerMediumAndHardMovementFactors[];


extern FileHeader g_frontendResourceFilename;

struct ConversionImageView;
extern struct ConversionImageView *g_conversionDestinationImage;

extern s32 g_musicPlaybackEnabled;

struct StateFlags;
extern struct StateFlags g_equipmentPanelWidgetIds[][19];

extern s32 g_ctfMode;

extern int g_frontendModeOneState;

extern char g_playerFlag82OnText[];

extern char g_playerRespawnDialog;

extern s16 DEBUG_LINK_TRANSFER_REGISTER;

extern char *g_matchResult5034TextEuX[];

extern char g_SelectPromptTextGroupFourCase6Text[];

extern s32 g_modelEditPack;

extern char *g_matchResult5006TextDe;

extern char g_pakOperationFourStateOneLabel[];

extern s32 g_sourcePixelIndex;

extern char g_SelectPromptTextGroupFiveStateOtherText[];

extern WidgetEventHandler g_pakDialogEventHandlers;


extern s32 g_team3SelectedNoticesEu[];

extern char g_pakOperationOneStateThreeLabel[];

extern char g_pickupSingleDefinitions;

extern u8 *g_toggleListClearLabel[];

extern char s_ammoPickupMessageSeparator[];

extern s8 g_controllerPakEnabledLastByte;

extern s32 g_playerMatchCountdownText;

extern char g_pickupPowerupDefinitions;

extern f32 g_wrappedValueUpperConstants[2];

struct MemoryUsageStats;
extern struct MemoryUsageStats g_activeSequenceTargetFound;

extern char g_pakPortTwoPrompt_de[];

extern Preset g_achievementPresetCopy;

extern f32 g_playerCrouchMinimumRiseAndBaseClearance[];


extern FieldRow g_titleButtonColumnEventActorKinds[];

extern int g_controlMenuControlFlag;

extern char g_pakAdjustMenuChoiceResourceSecond[];

extern char *g_matchResult5002UnplayedTextEu[];

extern const float g_reverbModulationCenter;


extern int g_cachedCeilingCrossProductNode;

extern char g_SelectPromptTextGroupFourCase9Text[];

extern char *g_matchResult5008TextDe;

extern char g_SelectPromptTextGroupTwoCase13Text[];

extern char g_SelectPromptTextGroupTwoStateOtherText[];

extern s32 g_artsendTextureSelectionIndex;

extern StateFlags *g_collisionProbeActorTwo;


extern char g_compressedSequencePlayerAssertText[];

extern char g_playerDeathDialogSlotThird;

extern char g_frontendVideoModeRenderConfigsFirstPad0;

extern int g_geometryPreviousCombineMode;

extern int g_menuScreenOwnerOverride;

extern unsigned int s_typeText[];

extern Tuning g_playerSwimMovementParameters;

extern FieldRow g_confirmationMenuEventActorKinds[];

extern char g_pakAllocateMenuSecondResource_eu[];

extern const s32 g_weaponActionFiveSpinTarget;

extern struct SharedMovement g_playerJumpMovementParameters;

extern char g_SelectPromptTextGroupOneCase6Text[];

extern char *g_matchResult5002PlayedTextEu[];


extern s32 g_stdioResourceReadRomEntry;

extern float g_geometryInitialScale;

extern f32 g_regionEdgeDefaultUpY;

extern char g_pagerExpansionDataSize[];

extern s32 g_artsendNextFrameHoldCount;

extern char s_playerCountFormat[];

extern Tuning g_playerClimbMovementParameters;

extern char g_pakOperationTwoDefaultLabel[];


extern u32 g_resourceHashSlotCount;


extern float g_regionNormalDefaultUp;

extern char *g_playerSettingsFirstChoiceText[];

extern s32 g_listButtonEventIds;

extern char g_menuOptionBit4DisabledText[];

extern s32 alMainBusPull_Address;

extern char g_SelectPromptTextGroupFiveCase10Text[];

extern Shared_ParticleLighting g_playerModelLighting[];

extern const f64 g_audioFrexpUpperLimit;

extern s32 g_soundVoicePoolGlobalState;

extern float g_menuModelPreviewYawSpeedScale;

extern char g_staticJumpTableRegionByteCount;

extern s32 g_menuOptionBit0DisabledText;

extern char g_weaponFireStateCallbackTable[];

extern struct OSTimer_s *g_timerListSentinel;

extern char g_alternateRenderMicrocodeData;

extern char *g_scenarioSetupLocalizedTitles[];

extern f32 g_transitionAlphaScaleTable[];

extern u32 g_destinationAlphaMask;

extern FieldRow g_playerCountEventActorKinds[];

extern s32 g_extraOptionsActorKinds;

extern char *g_matchResult5025TextEuX[];


extern FieldRow g_residentEventEntries[];

extern char g_SelectPromptTextGroupFourCase2Text[];



extern ResourcePageMapping *g_pagerLruTail;

extern char g_SelectPromptTextGroupOneStateOtherText[];

extern OSIoMesg g_videoRetraceEvent;

extern GeometryModelInstanceEntry g_materialInstances[];


extern char g_SelectPromptTextGroupTwoCase5Text[];


extern char g_pakOperationTwoStateOneLabel[];

extern f32 g_barrelEffectSoundMinimumPitch;

extern s32 g_hudCountMoverScript[];

extern char *g_matchResult5013TextEu[];

extern FieldRow g_playerSettingsEventIds[];

extern VideoDeviceManager g_videoDeviceManager;

extern char g_SelectPromptTextGroupOneCase8Text[];

extern f32 g_lightVolumeDefaultDirectionX;

extern s32 g_resourceCompletionWakeQueue;

extern char *g_playerOption7AStepText;

extern f32 g_ribbonNodeTransformCutoffConstants[];

extern char g_SelectPromptTextGroupOneCase2Text[];


extern s32 g_profileSecondaryMenuResource;

extern const char s_binaryBlockText[];

extern char g_profileModeFourPlayedLevels[];

extern char g_SelectPromptTextGroupFourCase8Text[];

extern s32 g_controllerPakSelectedNoteIndex;

extern s32 g_stdioResourceTellRomEntry;

extern char g_sessionUpdateHandlers[];

extern const float g_perspectiveFloatAngleScale;


extern s32 g_modelBatchResources[];

extern f32 g_frameHeapRestoreStatLowerLimit;

extern u8 g_profileUnlockedTrialBits[];

extern FieldRow g_nodePairMenuEventIds[];

extern const f32 g_sineExceptionalResult;

extern char *g_playerOption7DText0;



extern char g_alternateRenderMicrocodeText;

extern s32 g_fragTagSelectionState;

extern char g_bootstrapThreadStack[];

extern s32 g_selectionMenuHandlerEvents;

extern char *g_matchResult5010TextEuX[];

extern f32 g_frameHeapFreeByteStats[3];

extern s32 g_creditsControllerButtons;

extern s32 g_frameHeapBuffers[2];

extern f32 g_playerCrouchDepthAndMinimumFall[];

extern char s_particleModelResourceTag;

extern u8 g_playerSettingsSlotByteBase[];

extern char g_controllerSiMessageBuffer[];

extern f32 g_playerActionBlendTargetAndMinimumStep[2];

extern u8 g_sceneMaskLabelTable8[];

extern u32 g_displayListCapacityEuX;

extern s32 g_artsendTextureViewerTextureTable;

extern s32 alSavePull_Address;

extern char *g_matchResult5057TextDe;

extern char *g_profileRank14LocalizedTitles[];



extern int g_baseAmmoCapacities[];

extern s32 g_barrelPrimaryFlagSoundTable[];

extern Box g_cameraVolumeBounds;

extern char g_menuOptionBit2EnabledText[];

extern f32 g_weaponSpinFeedbackConstants[];

extern s32 g_sixChoiceMenuEventKinds;

extern s32 g_pakDialogEventActorKinds;

extern FieldRow g_trialOptionsEventIds[];

extern char *g_matchResult5019TextEu[];

extern char g_menuOptionBit9DisabledText[];

extern char *g_matchResult5018TextEu[];

extern FieldRow g_equipmentEventActorKinds[];

extern char *g_matchResult5053TextEu[];

extern char g_SelectPromptActionHeadingCase1Text[];

extern char g_staticDataRegionByteCount;


extern char g_SelectPromptTextGroupFiveCase1Text[];

extern FieldRow g_playModeEventKinds[];

extern s32 g_creditsSelectSpawnOnExit;

extern char *g_pakSaveMenuSnapshotChoiceLabels[];

extern s32 g_playerStatisticsAccumulatedDeaths[][100];

extern char g_SelectPromptTextGroupTwoCase3Text[];

extern s32 g_frontendPakPromptAccepted;

extern const f64 k_xmathCeilIntegralBias;

extern s32 g_hudSquadMoverScript[];

extern s32 g_weaponChargeSpinTarget;

extern s32 g_sessionUpdateResetFlag;

extern s32 g_pakProfileControllerPort;

extern char g_bloodModeText0[];

extern s32 g_matchOptionsCursorLabelThird[];

extern s32 g_frameAnimationEventActorKinds;

extern char g_cinemaStateRegionByteCount;


extern ControllerInitStatusBytes g_pagerTlbSlots[];

extern f32 g_staticObjectOpaqueAlpha;

extern char g_frontendVideoModeRenderConfigsFirstY;

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








struct TargetFollowingActorView;
typedef struct TargetFollowingActorView TargetFollowingActorView;

struct TrackerAimActorView;
typedef struct TrackerAimActorView TrackerAimActorView;

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

struct EffectActor;
typedef struct EffectActor EffectActor;

struct EffectActorModel;
typedef struct EffectActorModel EffectActorModel;

struct EffectBlock;
typedef struct EffectBlock EffectBlock;

struct CROMParticleColor_t;

struct EffectEntry;
typedef struct EffectEntry EffectEntry;

struct EffectModel;
typedef struct EffectModel EffectModel;

struct EffectMotion;
typedef struct EffectMotion EffectMotion;

struct EffectParams;
typedef struct EffectParams EffectParams;


struct EffectSystem;
typedef struct EffectSystem EffectSystem;

struct EffectTarget;
typedef struct EffectTarget EffectTarget;

struct EffectEventsSpawnAttachedEffect;
typedef struct EffectEventsSpawnAttachedEffect EffectEventsSpawnAttachedEffect;

struct ParticleEffect;
typedef struct ParticleEffect ParticleEffect;

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









struct SceneLoadResourcesView;
typedef struct SceneLoadResourcesView SceneLoadResourcesView;

struct LinkParticleApplyDirectionalAcceleration;
typedef struct LinkParticleApplyDirectionalAcceleration LinkParticleApplyDirectionalAcceleration;


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

struct JumpRoutePlayerView;
typedef struct JumpRoutePlayerView JumpRoutePlayerView;


union ModelPreviewScreen;
typedef union ModelPreviewScreen ModelPreviewScreen;


struct Motion;
typedef struct Motion Motion;

struct VoicePitchMotion;
typedef struct VoicePitchMotion VoicePitchMotion;





struct CacheEvictionNode;
typedef struct CacheEvictionNode CacheEvictionNode;

struct NodeList;
typedef struct NodeList NodeList;

struct PickupGoalAvailabilityNode;
typedef struct PickupGoalAvailabilityNode PickupGoalAvailabilityNode;












struct DirectionalAccelerationParticle;
typedef struct DirectionalAccelerationParticle DirectionalAccelerationParticle;





































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

struct ParamsParticleApplyDirectionalAcceleration;
typedef struct ParamsParticleApplyDirectionalAcceleration ParamsParticleApplyDirectionalAcceleration;

struct PatrolActor;
typedef struct PatrolActor PatrolActor;

struct PatrolBot;
typedef struct PatrolBot PatrolBot;

struct PatrolPlayer;
typedef struct PatrolPlayer PatrolPlayer;

struct PatrolRouteSet;
typedef struct PatrolRouteSet PatrolRouteSet;

struct PickupGoalNodeList;
typedef struct PickupGoalNodeList PickupGoalNodeList;

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











struct NavigationPlayerStateView;
typedef struct NavigationPlayerStateView NavigationPlayerStateView;

struct Players;
typedef struct Players Players;


struct SoundPlayerSlotPool;
typedef struct SoundPlayerSlotPool SoundPlayerSlotPool;



struct RecordD90;
typedef struct RecordD90 RecordD90;

struct ResourceRequest;
typedef struct ResourceRequest ResourceRequest;

struct ResourceHandleView;
typedef struct ResourceHandleView ResourceHandleView;

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

struct JumpRouteActorView;
typedef struct JumpRouteActorView JumpRouteActorView;








struct Runtime;
typedef struct Runtime Runtime;

struct SceneState;
typedef struct SceneState SceneState;

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



struct ItemsPreviewStateA;
typedef struct ItemsPreviewStateA ItemsPreviewStateA;

struct StyleNextState;
typedef struct StyleNextState StyleNextState;

struct SceneActorMatchDescriptor;
typedef struct SceneActorMatchDescriptor SceneActorMatchDescriptor;



struct JumpRouteControllerView;
typedef struct JumpRouteControllerView JumpRouteControllerView;



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


struct TrailNode;
typedef struct TrailNode TrailNode;

struct TrailState;
typedef struct TrailState TrailState;





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




struct WeaponMenuPlayer;
typedef struct WeaponMenuPlayer WeaponMenuPlayer;

struct WeaponMenuView;
typedef struct WeaponMenuView WeaponMenuView;




struct Slider;



struct _Pft;
typedef struct _Pft _Pft;

struct __OSViContext;
typedef struct __OSViContext __OSViContext;

union du;
typedef union du du;

union fu;
typedef union fu fu;





































struct QueuedModelInstance;
typedef struct QueuedModelInstance QueuedModelInstance;












struct SelectedLevelLabelItem;
typedef struct SelectedLevelLabelItem SelectedLevelLabelItem;

struct ToggleRowTextView;
#include "MENU/OPTION_TEXT_TYPE.H"




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
    Clip *lp;
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
    ALFilter_s14_2 **sources;
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
        ALSoundStatehandleEvent *state;
    } common;
    struct {
        s16 type;
        ALSoundStatehandleEvent *state;
        s16 vol;
    } vol;
    struct {
        s16 type;
        ALSoundStatehandleEvent *state;
        f32 pitch;
    } pitch;
    struct {
        s16 type;
        ALSoundStatehandleEvent *state;
        u8 pan;
    } pan;
    struct {
        s16 type;
        ALSoundStatehandleEvent *state;
        u8 mix;
    } fx;
};
struct Access_s8_E6;
struct NavigationBrainView;
struct NavigationPlayerStateView;
struct NavigationPlayerStateView {
    char pad0[0x1454];
    struct NavigationBrainView *brain;
};
struct TargetFollowingActorView;
struct NavigationPlayerStateView;
struct TargetFollowingActorView {
    char pad0[0x1D8];
    struct NavigationPlayerStateView *player;
};
struct TrackerAimActorView;
struct Runtime;
struct TrackerAimActorView {
    char p0[8];
    CVector3 pos;
    s32 room;
    s32 *definition;
    char p1C[80];
    f32 heading;
    char p70[116];
    u16 objectId;
    char pE6[26];
    s32 flags;
    char p104[212];
    struct Runtime *player;
    char p1DC[260];
    s32 targetFlags;
};
struct Runtime {
    char p0[1928];
    s32 weaponState;
    char p78C[8];
    struct TrackerAimActorView *target;
};
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
    VoidCallback callback;
};
typedef void ( *ContextCallback)(void *);
struct CameraEventsSpawnAttachedEffect;
struct RecGobjinstSampleBoneTranslation;
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
    StateEntry *entry;
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
    void (*enter)(struct Source110 *, struct Dest *);
    char pad8[8];
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
struct EffectActorModel;
struct EffectActorModel {
    u32 flags;
    char pad4[0x10];
    s32 scaleModeFlag;
};
struct EffectActor;
struct EffectActorModel;
struct EffectActor {
    u8 type;
    char pad1[7];
    CVector3 pos;
    char pad14[0x48];
    u32 flags;
    union {
        PackedMatrixWords matrices[2];
        struct {
            char pad[0x54];
            PackedMatrixWords *matrixArray;
            char padB8[0x18];
            void *owner;
        } link;
    } u60;
    char padE0[0x20];
    u32 actorFlags;
    char pad104[0x14];
    struct EffectActorModel *model;
    char pad11C[0x38];
    f32 offsetBase;
    f32 offsetScale;
    char pad15C[0x18];
    CVector3 followDirection;
    char pad180[0x50];
    s8 effectMode;
    char pad1D1[7];
    s32 player;
};
struct CROMParticleColor_t;
struct CROMParticleColor_t {
    u8 m_WhiteColor[3];
    u8 m_BlackColor[3];
    char pad6[6];
    s8 m_RandomizeHue;
    s8 m_RandomizeSaturation;
    s8 m_RandomizeValue;
};
struct EffectModel;
struct EffectModel {
    char pad0[0x94];
    u16 callbackKind;
};
struct EffectMotion;
struct EffectMotion {
    CharacterScreenCell gravity;
    CharacterScreenCell speed;
    u16 bounceEnergy;
    u16 groundFriction;
    u16 airFriction;
    u16 waterFriction;
    u16 acceleration; /* 0x10: encoded, Menu_ExpandFloatHighWord_RuntimeDeclarations */
    u16 speedLimit; /* 0x12: encoded, Menu_ExpandFloatHighWord_RuntimeDeclarations */
};
struct EffectParams;
struct EffectParams {
    s16 lifeBase;
    s16 lifeRange;
    s8 chance;
    s8 groupMode;
    s8 countBase;
    s8 countRange;
    s8 listIndex;
    char pad9[2];
    s8 animationParameter;
    char padC;
    s8 emitSpread;
    s8 attachmentMode;
};
struct CROMParticleColor_t;
struct EffectEntry;
struct EffectModel;
struct EffectMotion;
struct EffectParams;
struct EffectEntry {
    u32 flags;
    s16 textureId;
    s8 ribbonId;
    s8 lightId;
    s8 alphaMode;
    u8 instanceBehavior;
    u8 wallBehavior;
    u8 groundBehavior;
    s16 sound;
    char padE[4];
    u8 playerMask;
    char pad13;
    s32 rangeModeFlag;
    struct EffectModel *model;
    CharacterScreenCell *offset;
    CharacterScreenCell *packedRangesB;
    CharacterScreenCell *packedRangesA;
    CharacterScreenCell *direction;
    CharacterScreenCell *packedAngularRanges;
    struct EffectMotion *motion;
    struct CROMParticleColor_t *color;
    struct EffectParams *params;
};
struct EffectBlock;
struct EffectBlock {
    s32 reservedWord;
    s32 count;
    EffectEntry entries[1];
};
#include "COMMON/CCOLLISIONINFO2_T.H"
struct EffectActor;
struct EffectEntry;
struct ParticleEffect;
struct ParticleEffect {
    char pad0[4];
    u16 kind;
    char pad6[2];
    CVector3 pos;
    s32 reserved14;
    char pad18[4];
    CVector3 velocity;
    char pad28[0x28];
    CVector3 startPosition;
    u32 flags;
    char pad60[0xB0];
    s32 reserved110;
    s32 reserved114;
    struct EffectEntry *entry;
    u32 textureAndLayer;
    char pad120[4];
    void *ownerId;
    struct EffectActor *source;
    struct EffectActor *owner;
    s32 *refCount;
    s32 followedActor;
    s32 lightHandle;
    s32 reserved13C;
    f32 spreadAngle;
    f32 initialLifeOffset;
    f32 animationParameter;
    s16 life;
    u8 reserved14E;
    s8 reserved14F;
    f32 sampledRangesA[6];
    CVector3 previousPosition;
    CVector3 direction;
    f32 sampledRangesB[6];
    f32 alpha;
    f32 sampledAngularRates[6];
    CCollisionInfo2_t render;
    s8 mode;
    u8 boundMatrixIndex;
    u8 rgb0[3];
    u8 rgb1[3];
    u8 alphaByte;
    u8 releaseRequested;
    char pad1DA[6];
    f32 initialMotion;
    IntrusiveList *list;
    char pad1E8[4];
    struct ParticleEffect *next;
    s32 reserved1F0;
    struct ParticleEffect *groupNext;
};
struct EffectSystem;
struct ParticleEffect;
struct EffectSystem {
    char pad0[0xFC00];
    IntrusiveList free;
    IntrusiveList groups;
    IntrusiveList lists[3];
    s32 resource;
    struct ParticleEffect *last;
};
struct EffectActor;
struct EffectTarget;
struct EffectTarget {
    struct EffectActor *actor;
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

#include "MENU/FRAME_SEQUENCE.H"
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
struct SceneLoadResourcesView;
struct ParamsParticleApplyDirectionalAcceleration;
struct ParamsParticleApplyDirectionalAcceleration {
    char pad[16];
    u16 accel;
    u16 limit;
};
struct LinkParticleApplyDirectionalAcceleration;
struct ParamsParticleApplyDirectionalAcceleration;
struct LinkParticleApplyDirectionalAcceleration {
    char pad[48];
    struct ParamsParticleApplyDirectionalAcceleration *params;
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
    ListScreenItem *left;
    s32 leftCount;
    ListScreenItem *right;
    s32 rightCount;
    s32 reservedWord;
    s32 countdown;
    s32 text3E4;
    ListScreenItem *reservedPointer;
    ListScreenItem *label;
    ListScreenItem *reservedPointer1;
    char text[0x434 - 0x3F4];
    s32 category;
    s32 selection;
    ListScreenItem *item;
    ListScreenItem *reservedPointer2;
    ListScreenItem *reservedPointer3;
    ListScreenItem *reservedPointer4;
    ListScreenItem *reservedPointer5;
    ListScreenItem *reservedPointer6;
    ListScreenItem *reservedPointer7;
    ListScreenItem *reservedPointer8;
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
struct JumpRouteControllerView;
struct JumpRouteControllerView {
    u8 pad0[0x220];
    s32 behaviorState;
    u8 pad224[0x2FC - 0x224];
    s32 resetFlag;
    u8 pad300[0x320 - 0x300];
    s32 jumpTimer;
};
struct JumpRoutePlayerView;
struct JumpRouteControllerView;
struct JumpRoutePlayerView {
    u8 pad0[0x1454];
    struct JumpRouteControllerView *controller;
};
union ModelPreviewScreen;
typedef struct ModelPreviewRow { s32 model; s32 state; s32 fade; s32 holdTicks; s32 image; } ModelPreviewRow;
union ModelPreviewScreen {
    struct { char pad0[0x1C]; s32 cursor; void *window; MenuWidget *item24; char killsText[10], scoreText[10], ratioText[10], otherText[10]; char nameText[64]; s32 started, player, badge; ModelPreviewRow rows[10]; char padAfter[0x188 - 0x9C - 10 * sizeof(ModelPreviewRow)]; s32 selected; char resultText[0x1C0 - 0x18C]; s32 ready; char pad1C4[0x1C8 - 0x1C4]; };
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
struct NodeList;
struct NodeList {
    u8 pad0[0xC];
    s32 count;
};
struct PickupGoalAvailabilityNode;
struct PickupGoalAvailabilityNode {
    u16 id;
    u8 pad2[2];
    u8 kind;
};

struct LinkParticleApplyDirectionalAcceleration;
struct DirectionalAccelerationParticle;
struct DirectionalAccelerationParticle {
    char pad[28];
    CVector3 velocity;
    char gap[0x118-40];
    struct LinkParticleApplyDirectionalAcceleration *link;
    char gap2[0x174-0x11c];
    CVector3 direction;
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
#include "COMMON/PAK_MENU.H"
#include "COMMON/SHARED_PARTICLEINSTANCE.H"
struct PakNotesMenu;
struct PakNotesMenu {
    char pad0[0xC];
    PakNotesMenuItem *items;
    char pad10[0x10];
    PakMenuSlot *owner;
};
struct PakStatusPakSaveMenu;
struct PakStatusPakSaveMenu {
    char pad0[0x14];
    char *text;
    char pad18[4];
    SharedPlayer *player;
    PakMenuSlot *slot;
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
    PatrolBot *bot;
};
struct PatrolActor;
struct PatrolActor {
    u8 pad0[0x1D8];
    PatrolPlayer *player;
};
struct PatrolRouteSet;
struct PatrolRouteSet {
    u8 pad0[0x7C];
    s32 *routeCount;
};
struct PickupGoalNodeList;
struct PickupGoalNodeList {
    u8 pad0[0xC];
    s32 count;
    u8 pad10[8];
    u32 selected;
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
struct TrackerAimActorView;
struct Plan;
struct Plan {
    s32 p0;
    s32 aimTargetFlag;
    char p8[40];
    CompactOptionsPageView *probeParams;
    char p34[52];
    struct TrackerAimActorView *currentTarget;
    char p6C[20];
    struct TrackerAimActorView *approachTarget;
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
struct Players;
struct Players {
    char pad0[0x1454];
    char *state;
    char pad1458[0x16E8 - 0x1458];
};
struct PlayerList;
struct Players;
struct PlayerList {
    void **handle;
    struct Players *players;
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
struct ResourceHandleView;
struct ResourceHandleView {
    s32 **handle;
    s32 reserved4;
    u32 flags;
};
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
struct ResultsHeadingScreen;
struct ResultsHeadingScreen {
    char pad0[0x970];
    void *window;
    char pad974[0x9A0 - 0x974];
    char heading[50];
    char time[50];
    char padA04[0xA44 - 0xA04];
    s32 stage;
    char padA48[0xA5C - 0xA48];
    s32 record;
};
struct ResultsHeadingStage;
struct ResultsHeadingStage {
    char pad0[0x24];
    u8 time;
};
struct JumpRoutePlayerView;
struct JumpRouteActorView;
struct JumpRouteActorView {
    u8 pad0[0x1D8];
    struct JumpRoutePlayerView *player;
};
struct SceneState;
struct SceneState {
    u8 pad00[0xF];
    u8 actor_byte;
    u8 pad10[0xC0];
    CVector3 direction;
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
struct PlayerEyePositionView;
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
    StateFlags *surface;
    Shared_PoseModel *model;
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
    Shared_PoseWorld *world;
    char pad1DC[0xB4];
    void (*callback)(CMatrix4, struct Shared_PoseContext *);
    char pad294[0x4C];
    s32 attachmentEffectsFlag;
};
struct Shared_PoseContext {
    Shared_PosePartEntry *part;
    s32 index;
    Shared_PoseActor *actor;
    s32 handle;
    CMatrix4 *mtx;
    Shared_PosePartTable *parts;
    void *modelPack;
    s32 model;
    Shared_AnimState *animA;
    Shared_AnimState *animB;
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
struct ItemsPreviewStateA;
struct StyleNextState;
struct StyleNextState {
    char a[20];
    s32 item;
    Label *label;
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
    Record *slot;
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
    void (*draw)(TextBoundsText *, CItemInfo *, CItemInfo *, void *);
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
struct WeaponMenuView;
struct WeaponMenuView {
    char pad[0x120];
    s32 clipMode;
    char pad124[0x29C - 0x124];
    f32 viewport[4];
};
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
struct __OSViContext;
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
struct ObjMenuUpdateSixChoiceMenu;
typedef struct ObjMenuUpdateSixChoiceMenu ObjMenuUpdateSixChoiceMenu;
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
typedef struct Shared_ParticleDesc Shared_ParticleDesc;
struct Shared_ParticleFade;
typedef struct Shared_ParticleFade Shared_ParticleFade;
struct SourceWeaponApplyScaledSideYaw;
typedef struct SourceWeaponApplyScaledSideYaw SourceWeaponApplyScaledSideYaw;
struct ParticleSwooshAttachment;
typedef struct ParticleSwooshAttachment ParticleSwooshAttachment;
struct StateInfo;
typedef struct StateInfo StateInfo;
struct TablePakUpdateDialogList;
typedef struct TablePakUpdateDialogList TablePakUpdateDialogList;
struct CROMSwoosh_t;
struct WidgetFrontendUpdateSliderGeometry;
typedef struct WidgetFrontendUpdateSliderGeometry WidgetFrontendUpdateSliderGeometry;
typedef char * va_list;
#endif
