#include "DATA_OVERLAY_SN_RECORDS.H"


#if defined(VERSION_US_REV1)
struct {
    struct { u8 valueTail[3]; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[24]; } CGeneratorIntelligence_t_0;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[9]; } m_dwFlags_1;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[6]; } m_Type_2;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[13]; } m_FiniteTotal_3;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[11]; } m_MaxActive_4;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[15]; } m_IntervalTime1_5;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[15]; } m_IntervalTime2_6;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[13]; } m_ObjectIndex_7;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[16]; } m_VariationIndex_8;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[8]; } m_ScaleX_9;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[8]; } m_ScaleY_10;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[8]; } m_ScaleZ_11;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[14]; } m_ParticleType_12;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[8]; } m_Unused_13;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[24]; u8 nameLength; char name[4]; } eos_14;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[24]; u8 nameLength; char name[22]; } CGeneratorIntelligence_15;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[21]; } CTurretIntelligence_t_16;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[26]; u8 nameLength; char name[8]; } m_Common_17;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[9]; } m_dwFlags_18;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[9]; } m_GunNode_19;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[9]; } m_RotNode_20;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[10]; } m_RotSpeed_21;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[10]; } m_RotLimit_22;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[13]; } m_SightRadius_23;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[12]; } m_SightAngle_24;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[12]; } m_FireRadius_25;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[11]; } m_FireAngle_26;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[10]; } m_VertDist_27;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[11]; } m_HorizDist_28;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[10]; } m_HorizDir_29;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[11]; } m_MoveSpeed_30;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[13]; } m_StartOffset_31;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[25]; } m_TargetVisibleMotionType_32;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[28]; } m_TargetNotVisibleMotionType_33;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[4]; } pad1_34;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[4]; } pad2_35;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[21]; u8 nameLength; char name[4]; } eos_36;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[21]; u8 nameLength; char name[19]; } CTurretIntelligence_37;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[24]; } CThrowableIntelligence_t_38;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[9]; } m_dwFlags_39;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[17]; } m_CollisionRadius_40;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[17]; } m_CollisionHeight_41;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[24]; u8 nameLength; char name[4]; } eos_42;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[24]; u8 nameLength; char name[22]; } CThrowableIntelligence_43;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[19]; } CDoorIntelligence_t_44;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[9]; } m_dwFlags_45;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[14]; } m_OpenDuration_46;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[15]; } m_OpenDoorEvent_47;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[16]; } m_CloseDoorEvent_48;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[4]; } pad1_49;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[4]; } pad2_50;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[16]; } m_AutoOpenRadius_51;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[17]; } m_AutoCloseRadius_52;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[19]; u8 nameLength; char name[4]; } eos_53;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[19]; u8 nameLength; char name[17]; } CDoorIntelligence_54;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[27]; } CDestructibleIntelligence_t_55;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[9]; } m_dwFlags_56;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[8]; } m_Health_57;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[3]; } pad_58;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[17]; } m_CollisionRadius_59;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[17]; } m_CollisionHeight_60;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[10]; } m_IdleAnim_61;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[14]; } m_AutoGoRadius_62;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[8]; } m_GoAnim_63;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[18]; } m_GoParticleEffect_64;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[15]; } m_GoSoundEffect_65;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[18]; } m_dwGoPickupsFlag1_66;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[18]; } m_dwGoPickupsFlag2_67;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[13]; } m_GoDeathAnim_68;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[23]; } m_GoDeathParticleEffect_69;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[20]; } m_GoDeathSoundEffect_70;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[23]; } m_dwGoDeathPickupsFlag1_71;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[23]; } m_dwGoDeathPickupsFlag2_72;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[22]; } m_TotemMissionDuration_73;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[23]; } m_EnemiesAttackingTurok_74;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[26]; } m_EnemiesToKillToSaveTotem_75;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; SnLe32 dimension0; u8 tagNameLength; u8 nameLength; char name[12]; } m_ModelIndex_76;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; SnLe32 dimension0; u8 tagNameLength; u8 nameLength; char name[12]; } m_ModelFrame_77;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; SnLe32 dimension0; u8 tagNameLength; u8 nameLength; char name[28]; } m_ModelIndexHealthPercentage_78;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[27]; u8 nameLength; char name[4]; } eos_79;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[27]; u8 nameLength; char name[25]; } CDestructibleIntelligence_80;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[21]; } CPickupIntelligence_t_81;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[9]; } m_dwFlags_82;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[17]; } m_CollisionRadius_83;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[17]; } m_CollisionHeight_84;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[6]; } m_Time_85;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[21]; u8 nameLength; char name[4]; } eos_86;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[21]; u8 nameLength; char name[19]; } CPickupIntelligence_87;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[30]; } CInteractiveAnimIntelligence_t_88;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[9]; } m_dwFlags_89;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[11]; } m_StartAnim_90;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[30]; u8 nameLength; char name[4]; } eos_91;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[30]; u8 nameLength; char name[28]; } CInteractiveAnimIntelligence_92;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[21]; } CActionIntelligence_t_93;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[9]; } m_dwFlags_94;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[17]; } m_CollisionRadius_95;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[17]; } m_CollisionHeight_96;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[10]; } m_IdleAnim_97;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[11]; } m_IdleModel_98;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[13]; } m_IdleTexture_99;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[14]; } m_AutoGoRadius_100;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[8]; } m_GoAnim_101;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[16]; } m_GoPickupNeeded_102;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[20]; } m_GoPickupNeededText_103;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[9]; } m_GoModel_104;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[11]; } m_GoTexture_105;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[21]; u8 nameLength; char name[4]; } eos_106;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[21]; u8 nameLength; char name[19]; } CActionIntelligence_107;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[21]; } CPlayerIntelligence_t_108;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[9]; } m_dwFlags_109;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[13]; } m_StartHealth_110;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[13]; } m_SpeedScaler_111;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[12]; } m_JumpScaler_112;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[12]; } m_HealHealth_113;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[16]; } m_Aggressiveness_114;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[10]; } m_Accuracy_115;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[11]; } m_Awareness_116;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[13]; } m_Evasiveness_117;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[14]; } m_SeekKillZone_118;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[16]; } m_AvoidDeathZone_119;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[20]; } m_CloseAttackComfort_120;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[21]; } m_MediumAttackComfort_121;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[18]; } m_FarAttackComfort_122;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; SnLe32 dimension0; u8 tagNameLength; u8 nameLength; char name[12]; } m_WeaponList_123;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; SnLe32 dimension0; u8 tagNameLength; u8 nameLength; char name[16]; } m_WeaponAccuracy_124;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; SnLe32 dimension0; u8 tagNameLength; u8 nameLength; char name[17]; } m_WeaponCloseList_125;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; SnLe32 dimension0; u8 tagNameLength; u8 nameLength; char name[18]; } m_WeaponMediumList_126;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; SnLe32 dimension0; u8 tagNameLength; u8 nameLength; char name[15]; } m_WeaponFarList_127;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[17]; } m_CollisionRadius_128;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[21]; } m_CollisionWallRadius_129;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[17]; } m_CollisionHeight_130;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[21]; } m_CollisionDeadHeight_131;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[8]; } m_ScaleX_132;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[8]; } m_ScaleY_133;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[8]; } m_ScaleZ_134;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; SnLe32 dimension0; u8 tagNameLength; u8 nameLength; char name[9]; } m_AmmoMax_135;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[21]; u8 nameLength; char name[4]; } eos_136;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[21]; u8 nameLength; char name[19]; } CPlayerIntelligence_137;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[22]; } CMorpherIntelligence_t_138;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[9]; } m_dwFlags_139;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[17]; } m_CollisionRadius_140;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[17]; } m_CollisionHeight_141;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[11]; } m_AnimSpeed_142;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[22]; u8 nameLength; char name[4]; } eos_143;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[22]; u8 nameLength; char name[20]; } CMorpherIntelligence_144;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[27]; } CWarpEntranceIntelligence_t_145;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[9]; } m_dwFlags_146;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[17]; } m_CollisionRadius_147;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[17]; } m_CollisionHeight_148;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[15]; } m_DestinationID_149;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[27]; u8 nameLength; char name[4]; } eos_150;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[27]; u8 nameLength; char name[25]; } CWarpEntranceIntelligence_151;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[31]; } CWeatherGeneratorIntelligence_t_152;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[8]; } m_wFlags_153;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[14]; } m_NumParticles_154;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[8]; } m_Radius_155;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[13]; } m_StartHeight_156;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[17]; } m_MinFallVelocity_157;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[17]; } m_MaxFallVelocity_158;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[8]; } m_SlopeX_159;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[8]; } m_SlopeZ_160;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[11]; } m_MinLength_161;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[11]; } m_MaxLength_162;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; SnLe32 dimension0; u8 tagNameLength; u8 nameLength; char name[13]; } m_UpperColour_163;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; SnLe32 dimension0; u8 tagNameLength; u8 nameLength; char name[13]; } m_LowerColour_164;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[10]; } m_nTexture_165;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[10]; } m_MinWidth_166;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[10]; } m_MaxWidth_167;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[9]; } m_Timeout_168;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[31]; u8 nameLength; char name[4]; } eos_169;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[31]; u8 nameLength; char name[29]; } CWeatherGeneratorIntelligence_170;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[8]; } record_134fake_171;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[21]; u8 nameLength; char name[6]; } Static_172;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[20]; u8 nameLength; char name[5]; } Enemy_173;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[23]; u8 nameLength; char name[8]; } Platform_174;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[24]; u8 nameLength; char name[9]; } Generator_175;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[21]; u8 nameLength; char name[6]; } Turret_176;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[24]; u8 nameLength; char name[9]; } Throwable_177;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[19]; u8 nameLength; char name[4]; } Door_178;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[27]; u8 nameLength; char name[12]; } Destructible_179;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[21]; u8 nameLength; char name[6]; } Pickup_180;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[30]; u8 nameLength; char name[15]; } InteractiveAnim_181;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[21]; u8 nameLength; char name[6]; } Action_182;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[21]; u8 nameLength; char name[6]; } Player_183;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[22]; u8 nameLength; char name[7]; } Morpher_184;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[27]; u8 nameLength; char name[12]; } WarpEntrance_185;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[31]; u8 nameLength; char name[16]; } WeatherGenerator_186;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[8]; u8 nameLength; char name[4]; } eos_187;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[15]; } CIntelligence_t_188;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[7]; } m_nType_189;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[9]; } m_dwFlags_190;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[10]; } m_LODDist2_191;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[4]; } m_Id_192;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[8]; } m_nModel_193;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[9]; } m_nModel2_194;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[14]; } m_nShadowModel_195;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[15]; } m_nShadowModel2_196;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[10]; } m_nTexture_197;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[3]; } pad_198;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[8]; u8 nameLength; char name[1]; } u_199;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[15]; u8 nameLength; char name[4]; } eos_200;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[15]; u8 nameLength; char name[13]; } CIntelligence_201;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[9]; } Behaviors_202;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[15]; } GROUND_BEHAVIOR_203;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[12]; } AIR_BEHAVIOR_204;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[19]; } UNDERWATER_BEHAVIOR_205;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[14]; } BEHAVIOR_COUNT_206;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[9]; u8 nameLength; char name[4]; } eos_207;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[11]; } CBehavior_t_208;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; SnLe32 dimension0; u8 tagNameLength; u8 nameLength; char name[6]; } m_Type_209;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[17]; } m_CurrentBehavior_210;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[11]; u8 nameLength; char name[4]; } eos_211;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[11]; u8 nameLength; char name[9]; } CBehavior_212;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[8]; } record_135fake_213;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[7]; } m_float_214;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[5]; } m_int_215;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[21]; u8 nameLength; char name[11]; } m_pAnimInst_216;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[7]; } m_DWORD_217;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; SnLe32 dimension0; u8 tagNameLength; u8 nameLength; char name[7]; } m_Bytes_218;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; SnLe32 dimension0; u8 tagNameLength; u8 nameLength; char name[7]; } m_Words_219;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[11]; u8 nameLength; char name[10]; } m_Behavior_220;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[6]; } m_BOOL_221;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[8]; u8 nameLength; char name[4]; } eos_222;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[10]; } CMiscVar_t_223;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[8]; u8 nameLength; char name[1]; } u_224;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[10]; u8 nameLength; char name[4]; } eos_225;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[10]; u8 nameLength; char name[8]; } CMiscVar_226;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[5]; } CAI_t_227;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[9]; } m_dwFlags_228;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[8]; } m_Health_229;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[13]; } m_StartHealth_230;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[14]; } m_dwModelFlags_231;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[13]; } m_TranqHealth_232;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[7]; } padding_233;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[17]; } m_FlinchCountdown_234;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[12]; } m_FlinchTime_235;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; SnLe32 dimension0; u8 tagNameLength; u8 nameLength; char name[12]; } m_FlinchNode_236;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[10]; u8 nameLength; char name[13]; } m_vFlinchAxis_237;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[10]; } m_HeadTurn_238;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[10]; } m_HeadTilt_239;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[13]; u8 nameLength; char name[12]; } m_pModeTable_240;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[13]; u8 nameLength; char name[11]; } m_pModeInfo_241;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[6]; } m_Mode_242;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[15]; } m_ModeLastFrame_243;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[12]; } m_ModeBefore_244;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[8]; } m_Action_245;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[20]; } m_ModeLastFrameFlags_246;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[11]; } m_ModeFlags_247;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[10]; } m_ModeTime_248;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[12]; } m_ActionTime_249;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[10]; u8 nameLength; char name[15]; } m_vPosLastFrame_250;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[10]; u8 nameLength; char name[13]; } m_vDesiredPos_251;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[15]; } m_RotYLastFrame_252;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[10]; } m_MoveTime_253;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[21]; u8 nameLength; char name[9]; } m_pLeader_254;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[10]; u8 nameLength; char name[15]; } m_vTargetOffset_255;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[21]; u8 nameLength; char name[17]; } m_pTargetOverride_256;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[20]; } m_TargetOverrideTime_257;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[21]; u8 nameLength; char name[14]; } m_pSightTarget_258;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[13]; u8 nameLength; char name[18]; } m_pPathAvoidRegion_259;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[21]; u8 nameLength; char name[13]; } m_pPathTarget_260;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[10]; } m_PathRotY_261;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[12]; } m_PathHeight_262;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[10]; u8 nameLength; char name[11]; } m_PathTrack_263;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[11]; } m_StartRotY_264;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[10]; u8 nameLength; char name[11]; } m_vStartPos_265;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[13]; u8 nameLength; char name[14]; } m_pStartRegion_266;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[10]; u8 nameLength; char name[11]; } m_vLeashPos_267;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[13]; u8 nameLength; char name[14]; } m_pLeashRegion_268;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[11]; } m_AnimSpeed_269;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[15]; } m_ModeAnimSpeed_270;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[10]; } m_AnimType_271;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[11]; } m_AnimIndex_272;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[12]; } m_AnimPlayed_273;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[12]; } m_Aggression_274;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[12]; } m_FreezeTime_275;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[15]; } m_PathFindCount_276;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[24]; } m_FramesSinceLastPainSFX_277;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[18]; } m_DeathRegionTimer_278;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[13]; } m_OnFireTimer_279;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[10]; u8 nameLength; char name[13]; } m_vBoreTarget_280;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[10]; u8 nameLength; char name[17]; } m_vBoreCollNormal_281;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[10]; u8 nameLength; char name[19]; } m_vLaserSightSource_282;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[19]; u8 nameLength; char name[23]; } m_pAttachedLoopingSound_283;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[19]; } m_UseAlternateModel_284;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[13]; } m_wLimbStatus_285;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[3]; } pad_286;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[11]; } m_pfAdvance_287;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[8]; } m_pfDraw_288;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[18]; } m_pfDecreaseHealth_289;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[13]; } m_pfCollision_290;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[17]; } m_pfHitByParticle_291;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[30]; } m_pfCalculateOrientationMatrix_292;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[18]; } m_pfSpecialEffects_293;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[10]; u8 nameLength; char name[4]; } m_M0_294;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[10]; u8 nameLength; char name[4]; } m_M1_295;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[10]; u8 nameLength; char name[4]; } m_M2_296;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[10]; u8 nameLength; char name[4]; } m_M3_297;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[10]; u8 nameLength; char name[4]; } m_M4_298;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[10]; u8 nameLength; char name[4]; } m_M5_299;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[10]; u8 nameLength; char name[4]; } m_M6_300;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[10]; u8 nameLength; char name[4]; } m_M7_301;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[10]; u8 nameLength; char name[4]; } m_M8_302;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[10]; u8 nameLength; char name[4]; } m_M9_303;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[10]; u8 nameLength; char name[5]; } m_M10_304;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[10]; u8 nameLength; char name[5]; } m_M11_305;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[10]; u8 nameLength; char name[5]; } m_M12_306;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[10]; u8 nameLength; char name[5]; } m_M13_307;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[10]; u8 nameLength; char name[5]; } m_M14_308;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[10]; u8 nameLength; char name[5]; } m_M15_309;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[10]; u8 nameLength; char name[5]; } m_M16_310;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[10]; u8 nameLength; char name[5]; } m_M17_311;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[10]; u8 nameLength; char name[5]; } m_M18_312;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[5]; u8 nameLength; char name[4]; } eos_313;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[5]; u8 nameLength; char name[3]; } CAI_314;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[15]; } CAnimCompInfo_t_315;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[10]; } SmoothSize_316;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[7]; } nFrames_317;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[10]; } DecompMode_318;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[9]; } Tolerance_319;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[4]; } nRot_320;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[6]; } nTrans_321;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[10]; } nNewFrames_322;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[10]; } FrameScale_323;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[15]; u8 nameLength; char name[4]; } eos_324;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[15]; u8 nameLength; char name[13]; } CAnimCompInfo_325;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[24]; } CROMInitialOrientation_t_326;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[10]; u8 nameLength; char name[6]; } m_vPos_327;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[6]; } m_RotX_328;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[6]; } m_RotY_329;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[6]; } m_RotZ_330;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[6]; } m_RotT_331;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[24]; u8 nameLength; char name[4]; } eos_332;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[24]; u8 nameLength; char name[22]; } CROMInitialOrientation_333;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[15]; } CROMNodeIndex_t_334;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[17]; } m_nTranslationSet_335;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[14]; } m_nRotationSet_336;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[15]; u8 nameLength; char name[4]; } eos_337;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[15]; u8 nameLength; char name[13]; } CROMNodeIndex_338;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[20]; } CTranslationOffset_t_339;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[10]; u8 nameLength; char name[9]; } m_vOffset_340;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[10]; u8 nameLength; char name[8]; } m_vScale_341;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[20]; u8 nameLength; char name[4]; } eos_342;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[20]; u8 nameLength; char name[18]; } CTranslationOffset_343;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[16]; } CROMTransition_t_344;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[17]; } m_BlendFromLength_345;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[14]; } m_nExitToFrame_346;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[12]; } m_BlendStart_347;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[13]; } m_BlendFinish_348;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[5]; } m_FPS_349;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[16]; u8 nameLength; char name[4]; } eos_350;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[16]; u8 nameLength; char name[14]; } CROMTransition_351;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[21]; } CROMTransitionEntry_t_352;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[16]; } m_nRequestedAnim_353;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[15]; } m_nWaitForFrame_354;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[16]; } m_nDeliveredAnim_355;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[21]; u8 nameLength; char name[4]; } eos_356;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[21]; u8 nameLength; char name[19]; } CROMTransitionEntry_357;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[17]; } EventValueFormats_358;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[14]; } EVENT_FORMAT1A_359;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[14]; } EVENT_FORMAT2A_360;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[14]; } EVENT_FORMAT2B_361;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[14]; } EVENT_FORMAT3A_362;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[14]; } EVENT_FORMAT4A_363;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[14]; } EVENT_FORMAT6A_364;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[14]; } EVENT_FORMAT7A_365;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[13]; } EVENT_FORMATS_366;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[17]; u8 nameLength; char name[4]; } eos_367;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[21]; } s_CEventValueFormat1a_368;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[12]; } m_s32_Value1_369;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[21]; u8 nameLength; char name[4]; } eos_370;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[21]; u8 nameLength; char name[19]; } CEventValueFormat1a_371;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[21]; } s_CEventValueFormat2a_372;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[12]; } m_s32_Value1_373;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[12]; } m_s32_Value2_374;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[21]; u8 nameLength; char name[4]; } eos_375;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[21]; u8 nameLength; char name[19]; } CEventValueFormat2a_376;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[21]; } s_CEventValueFormat2b_377;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[12]; } m_s32_Value1_378;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[12]; } m_f32_Value2_379;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[21]; u8 nameLength; char name[4]; } eos_380;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[21]; u8 nameLength; char name[19]; } CEventValueFormat2b_381;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[21]; } s_CEventValueFormat3a_382;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[12]; } m_s32_Value1_383;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[12]; } m_s16_Value2_384;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[11]; } m_s8_Value3_385;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[21]; u8 nameLength; char name[4]; } eos_386;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[21]; u8 nameLength; char name[19]; } CEventValueFormat3a_387;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[21]; } s_CEventValueFormat4a_388;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[12]; } m_s16_Value1_389;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[12]; } m_s16_Value2_390;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[12]; } m_s16_Value3_391;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[12]; } m_s16_Value4_392;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[21]; u8 nameLength; char name[4]; } eos_393;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[21]; u8 nameLength; char name[19]; } CEventValueFormat4a_394;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[21]; } s_CEventValueFormat6a_395;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[12]; } m_s16_Value1_396;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[12]; } m_s16_Value2_397;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[11]; } m_s8_Value3_398;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[11]; } m_s8_Value4_399;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[11]; } m_s8_Value5_400;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[11]; } m_s8_Value6_401;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[21]; u8 nameLength; char name[4]; } eos_402;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[21]; u8 nameLength; char name[19]; } CEventValueFormat6a_403;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[21]; } s_CEventValueFormat7a_404;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[11]; } m_u8_Value1_405;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[11]; } m_u8_Value2_406;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[11]; } m_u8_Value3_407;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[11]; } m_u8_Value4_408;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[11]; } m_u8_Value5_409;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[11]; } m_u8_Value6_410;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[11]; } m_u8_Value7_411;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[21]; u8 nameLength; char name[4]; } eos_412;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[21]; u8 nameLength; char name[19]; } CEventValueFormat7a_413;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[8]; } record_136fake_414;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[21]; u8 nameLength; char name[10]; } m_Format1a_415;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[21]; u8 nameLength; char name[10]; } m_Format2a_416;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[21]; u8 nameLength; char name[10]; } m_Format2b_417;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[21]; u8 nameLength; char name[10]; } m_Format3a_418;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[21]; u8 nameLength; char name[10]; } m_Format4a_419;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[21]; u8 nameLength; char name[10]; } m_Format6a_420;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[21]; u8 nameLength; char name[10]; } m_Format7a_421;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[8]; u8 nameLength; char name[4]; } eos_422;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[13]; } s_CEventValue_423;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[8]; u8 nameLength; char name[1]; } u_424;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[13]; u8 nameLength; char name[4]; } eos_425;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[13]; u8 nameLength; char name[11]; } CEventValue_426;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[16]; } CROMEventEntry_t_427;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[8]; } m_nFrame_428;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[8]; } m_nEvent_429;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[7]; } m_nNode_430;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[3]; } pad_431;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[10]; u8 nameLength; char name[9]; } m_vOffset_432;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[13]; u8 nameLength; char name[7]; } m_Value_433;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[16]; u8 nameLength; char name[4]; } eos_434;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[16]; u8 nameLength; char name[14]; } CROMEventEntry_435;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[10]; } CVisBits_t_436;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; SnLe32 dimension0; u8 tagNameLength; u8 nameLength; char name[4]; } Bits_437;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[10]; u8 nameLength; char name[4]; } eos_438;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[10]; u8 nameLength; char name[8]; } CVisBits_439;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[15]; } CROMCornerEnc_t_440;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[1]; } x_441;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[1]; } y_442;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[1]; } z_443;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[1]; } c_444;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[15]; u8 nameLength; char name[4]; } eos_445;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[15]; u8 nameLength; char name[13]; } CROMCornerEnc_446;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[12]; } CROMCorner_t_447;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[10]; u8 nameLength; char name[9]; } m_vCorner_448;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[9]; } m_Ceiling_449;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[12]; u8 nameLength; char name[4]; } eos_450;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[12]; u8 nameLength; char name[10]; } CROMCorner_451;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[15]; } CROMRegionSet_t_452;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; SnLe32 dimension0; u8 tagNameLength; u8 nameLength; char name[10]; } m_FogColor_453;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; SnLe32 dimension0; u8 tagNameLength; u8 nameLength; char name[12]; } m_WaterColor_454;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[10]; } m_FogStart_455;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[12]; } m_WaterStart_456;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[9]; } m_FarClip_457;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[13]; } m_FieldOfView_458;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[14]; } m_WaterFarClip_459;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[18]; } m_WaterFieldOfView_460;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[16]; } m_WaterElevation_461;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[13]; } m_BlendLength_462;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[16]; } m_DeathTimeDelay_463;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[21]; } m_CameraVertEyeOffset_464;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[22]; } m_CameraMovementScaler_465;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[13]; } m_JumpPadEndX_466;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[13]; } m_JumpPadEndY_467;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[13]; } m_JumpPadEndZ_468;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[15]; } m_JumpPadHeight_469;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[9]; } m_dwFlags_470;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[8]; } m_WarpID_471;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[26]; } m_PressurePlateSoundNumber_472;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[18]; } m_SaveCheckpointID_473;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[12]; } m_PressureID_474;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[16]; } m_DeathHitPoints_475;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[9]; } m_wFlags2_476;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[9]; } m_wFlags3_477;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[12]; } m_wSkyLayers_478;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[11]; } m_GroundMat_479;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[9]; } m_WallMat_480;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[9]; } m_MusicID_481;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[15]; } m_AmbientSounds_482;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[10]; } m_MapColor_483;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[17]; } m_CurrentStrength_484;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[13]; } m_JumpPadTime_485;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[19]; } m_CurrentDirectionX_486;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[19]; } m_CurrentDirectionY_487;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[19]; } m_CurrentDirectionZ_488;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[11]; } m_WeatherID_489;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[15]; u8 nameLength; char name[4]; } eos_490;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[15]; u8 nameLength; char name[13]; } CROMRegionSet_491;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[12]; } CROMRegion_t_492;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[12]; } m_nRegionSet_493;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[8]; } m_wFlags_494;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; SnLe32 dimension0; u8 tagNameLength; u8 nameLength; char name[9]; } m_Corners_495;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; SnLe32 dimension0; u8 tagNameLength; u8 nameLength; char name[11]; } m_Neighbors_496;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[10]; u8 nameLength; char name[9]; } m_VisBits_497;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[12]; u8 nameLength; char name[4]; } eos_498;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[12]; u8 nameLength; char name[10]; } CROMRegion_499;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[13]; } CGameRegion_t_500;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[12]; } m_nRegionSet_501;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[8]; } m_wFlags_502;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; SnLe32 dimension0; u8 tagNameLength; char tagName[12]; u8 nameLength; char name[10]; } m_pCorners_503;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; SnLe32 dimension0; u8 tagNameLength; char tagName[13]; u8 nameLength; char name[12]; } m_pNeighbors_504;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[10]; u8 nameLength; char name[9]; } m_VisBits_505;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[13]; u8 nameLength; char name[4]; } eos_506;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[13]; u8 nameLength; char name[11]; } CGameRegion_507;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[12]; } CROMBounds_t_508;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[10]; u8 nameLength; char name[6]; } m_vMin_509;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[10]; u8 nameLength; char name[6]; } m_vMax_510;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[12]; u8 nameLength; char name[4]; } eos_511;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[12]; u8 nameLength; char name[10]; } CROMBounds_512;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[13]; } CBoundsRect_t_513;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[6]; } m_MinX_514;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[6]; } m_MinZ_515;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[6]; } m_MaxX_516;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[6]; } m_MaxZ_517;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[13]; u8 nameLength; char name[4]; } eos_518;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[13]; u8 nameLength; char name[11]; } CBoundsRect_519;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[17]; } CROMRegionBlock_t_520;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[13]; u8 nameLength; char name[12]; } m_BoundsRect_521;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[10]; } m_nRegions_522;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[17]; u8 nameLength; char name[4]; } eos_523;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[17]; u8 nameLength; char name[15]; } CROMRegionBlock_524;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[16]; } CROMGridBounds_t_525;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[13]; u8 nameLength; char name[12]; } m_BoundsRect_526;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[8]; } m_bEmpty_527;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[16]; u8 nameLength; char name[4]; } eos_528;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[16]; u8 nameLength; char name[14]; } CROMGridBounds_529;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[14]; } CInstanceHdr_t_530;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[6]; } m_Type_531;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[8]; } m_nModel_532;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[14]; } m_nShadowModel_533;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[10]; } m_nTexture_534;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[10]; } m_nObjType_535;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; SnLe32 dimension0; u8 tagNameLength; u8 nameLength; char name[7]; } PADDING_536;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[10]; u8 nameLength; char name[6]; } m_vPos_537;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[13]; u8 nameLength; char name[16]; } m_pCurrentRegion_538;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[15]; u8 nameLength; char name[4]; } m_pI_539;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[14]; u8 nameLength; char name[4]; } eos_540;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[14]; u8 nameLength; char name[12]; } CInstanceHdr_541;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[18]; } CAnimInstanceHdr_t_542;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[14]; u8 nameLength; char name[2]; } ih_543;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[10]; u8 nameLength; char name[11]; } m_vVelocity_544;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[10]; u8 nameLength; char name[10]; } m_vCurrent_545;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[14]; u8 nameLength; char name[16]; } m_pInstanceBelow_546;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[11]; } m_CollFlags_547;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[16]; } m_GroundMaterial_548;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[14]; } m_GroundHeight_549;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[10]; u8 nameLength; char name[15]; } m_vGroundNormal_550;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[18]; u8 nameLength; char name[4]; } eos_551;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[18]; u8 nameLength; char name[16]; } CAnimInstanceHdr_552;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[6]; } s_ISet_553;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[12]; } m_BlockCount_554;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; SnLe32 dimension0; u8 tagNameLength; u8 nameLength; char name[9]; } m_Offsets_555;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[6]; u8 nameLength; char name[4]; } eos_556;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[6]; u8 nameLength; char name[5]; } CISet_557;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[6]; } s_USet_558;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[11]; } m_BlockSize_559;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[12]; } m_BlockCount_560;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; SnLe32 dimension0; u8 tagNameLength; u8 nameLength; char name[7]; } m_Array_561;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[6]; u8 nameLength; char name[4]; } eos_562;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[6]; u8 nameLength; char name[5]; } CUSet_563;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[12]; } CHeapBlock_t_564;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[12]; u8 nameLength; char name[9]; } pFreeLast_565;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[12]; u8 nameLength; char name[9]; } pFreeNext_566;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[12]; u8 nameLength; char name[9]; } pUsedLast_567;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[12]; u8 nameLength; char name[9]; } pUsedNext_568;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[4]; } Used_569;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[4]; } Free_570;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[12]; u8 nameLength; char name[4]; } eos_571;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[12]; u8 nameLength; char name[10]; } CHeapBlock_572;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[7]; } CHeap_t_573;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[8]; } MemStart_574;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[6]; } MemEnd_575;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[12]; u8 nameLength; char name[9]; } pFreeHead_576;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[12]; u8 nameLength; char name[9]; } pFreeTail_577;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[12]; u8 nameLength; char name[9]; } pUsedHead_578;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[4]; } eos_579;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[5]; } CHeap_580;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[13]; } pfnTHREADMAIN_581;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[14]; } CLoaderEntry_t_582;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[8]; } pAddress_583;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[5]; } pDest_584;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[6]; } Length_585;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[13]; u8 nameLength; char name[11]; } pReplyQueue_586;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[13]; } pReplyMessage_587;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[7]; } dwFlags_588;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[14]; u8 nameLength; char name[5]; } pLast_589;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[14]; u8 nameLength; char name[5]; } pNext_590;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[14]; u8 nameLength; char name[4]; } eos_591;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[14]; u8 nameLength; char name[12]; } CLoaderEntry_592;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[9]; } CLoader_t_593;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[10]; u8 nameLength; char name[6]; } Thread_594;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[13]; u8 nameLength; char name[5]; } Queue_595;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; SnLe32 dimension0; u8 tagNameLength; u8 nameLength; char name[4]; } Msgs_596;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[13]; u8 nameLength; char name[12]; } PiReplyQueue_597;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[10]; } PiReplyMsg_598;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; SnLe32 dimension0; u8 tagNameLength; u8 nameLength; char name[5]; } Stack_599;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; SnLe32 dimension0; u8 tagNameLength; char tagName[14]; u8 nameLength; char name[7]; } Entries_600;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[8]; } FreeList_601;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[8]; } UsedList_602;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[9]; u8 nameLength; char name[4]; } eos_603;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[9]; u8 nameLength; char name[7]; } CLoader_604;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[21]; } pfnDECOMPRESSCALLBACK_605;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[11]; } CMemEntry_t_606;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[5]; } pData_607;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[4]; } Size_608;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[6]; } nLocks_609;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[7]; } dwFlags_610;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[3]; } Age_611;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[13]; u8 nameLength; char name[11]; } pCacheEntry_612;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[11]; u8 nameLength; char name[5]; } pLast_613;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[11]; u8 nameLength; char name[5]; } pNext_614;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[11]; u8 nameLength; char name[8]; } pPosLast_615;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[11]; u8 nameLength; char name[8]; } pPosNext_616;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[11]; u8 nameLength; char name[4]; } eos_617;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[11]; u8 nameLength; char name[9]; } CMemEntry_618;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[13]; } CCacheNtry2_t_619;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[11]; u8 nameLength; char name[9]; } pMemEntry_620;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[11]; u8 nameLength; char name[19]; } pReferencedMemEntry_621;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[10]; } pRequestID_622;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[13]; } RequestLength_623;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[7]; } dwFlags_624;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[18]; } DecompressCallback_625;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[9]; } pNotifyID_626;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[10]; } dwMemFlags_627;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[13]; u8 nameLength; char name[21]; } pDecompressReplyQueue_628;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[13]; u8 nameLength; char name[5]; } pNext_629;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[13]; u8 nameLength; char name[5]; } pLast_630;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[13]; u8 nameLength; char name[4]; } eos_631;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[13]; u8 nameLength; char name[11]; } CCacheNtry2_632;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[15]; } CDecompressor_t_633;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[10]; u8 nameLength; char name[6]; } Thread_634;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[13]; u8 nameLength; char name[5]; } Queue_635;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; SnLe32 dimension0; u8 tagNameLength; u8 nameLength; char name[4]; } Msgs_636;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; SnLe32 dimension0; u8 tagNameLength; u8 nameLength; char name[5]; } Stack_637;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[14]; } LastDecompress_638;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[15]; u8 nameLength; char name[4]; } eos_639;
    u8 incompleteRecord[22];
} g_sn64IntelligenceTypeRecords __attribute__((aligned(1))) = {
    { { 0, 0, 0 }, 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(40), 24, "CGeneratorIntelligence_t" },
    { SN_LE32(0), 0x94, SN_LE16(8), SN_LE16(15), SN_LE32(0), 9, "m_dwFlags" },
    { SN_LE32(4), 0x94, SN_LE16(8), SN_LE16(5), SN_LE32(0), 6, "m_Type" },
    { SN_LE32(8), 0x94, SN_LE16(8), SN_LE16(3), SN_LE32(0), 13, "m_FiniteTotal" },
    { SN_LE32(10), 0x94, SN_LE16(8), SN_LE16(3), SN_LE32(0), 11, "m_MaxActive" },
    { SN_LE32(12), 0x94, SN_LE16(8), SN_LE16(6), SN_LE32(0), 15, "m_IntervalTime1" },
    { SN_LE32(16), 0x94, SN_LE16(8), SN_LE16(6), SN_LE32(0), 15, "m_IntervalTime2" },
    { SN_LE32(20), 0x94, SN_LE16(8), SN_LE16(3), SN_LE32(0), 13, "m_ObjectIndex" },
    { SN_LE32(22), 0x94, SN_LE16(8), SN_LE16(3), SN_LE32(0), 16, "m_VariationIndex" },
    { SN_LE32(24), 0x94, SN_LE16(8), SN_LE16(6), SN_LE32(0), 8, "m_ScaleX" },
    { SN_LE32(28), 0x94, SN_LE16(8), SN_LE16(6), SN_LE32(0), 8, "m_ScaleY" },
    { SN_LE32(32), 0x94, SN_LE16(8), SN_LE16(6), SN_LE32(0), 8, "m_ScaleZ" },
    { SN_LE32(36), 0x94, SN_LE16(8), SN_LE16(3), SN_LE32(0), 14, "m_ParticleType" },
    { SN_LE32(38), 0x94, SN_LE16(8), SN_LE16(3), SN_LE32(0), 8, "m_Unused" },
    { SN_LE32(40), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(40), SN_LE16(0), 24, "CGeneratorIntelligence_t", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(40), SN_LE16(0), 24, "CGeneratorIntelligence_t", 22, "CGeneratorIntelligence" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(116), 21, "CTurretIntelligence_t" },
    { SN_LE32(0), 0x96, SN_LE16(8), SN_LE16(8), SN_LE32(56), SN_LE16(0), 26, "CCommonEnemyIntelligence_t", 8, "m_Common" },
    { SN_LE32(56), 0x94, SN_LE16(8), SN_LE16(15), SN_LE32(0), 9, "m_dwFlags" },
    { SN_LE32(60), 0x94, SN_LE16(8), SN_LE16(5), SN_LE32(0), 9, "m_GunNode" },
    { SN_LE32(64), 0x94, SN_LE16(8), SN_LE16(5), SN_LE32(0), 9, "m_RotNode" },
    { SN_LE32(68), 0x94, SN_LE16(8), SN_LE16(6), SN_LE32(0), 10, "m_RotSpeed" },
    { SN_LE32(72), 0x94, SN_LE16(8), SN_LE16(6), SN_LE32(0), 10, "m_RotLimit" },
    { SN_LE32(76), 0x94, SN_LE16(8), SN_LE16(6), SN_LE32(0), 13, "m_SightRadius" },
    { SN_LE32(80), 0x94, SN_LE16(8), SN_LE16(6), SN_LE32(0), 12, "m_SightAngle" },
    { SN_LE32(84), 0x94, SN_LE16(8), SN_LE16(6), SN_LE32(0), 12, "m_FireRadius" },
    { SN_LE32(88), 0x94, SN_LE16(8), SN_LE16(6), SN_LE32(0), 11, "m_FireAngle" },
    { SN_LE32(92), 0x94, SN_LE16(8), SN_LE16(6), SN_LE32(0), 10, "m_VertDist" },
    { SN_LE32(96), 0x94, SN_LE16(8), SN_LE16(6), SN_LE32(0), 11, "m_HorizDist" },
    { SN_LE32(100), 0x94, SN_LE16(8), SN_LE16(6), SN_LE32(0), 10, "m_HorizDir" },
    { SN_LE32(104), 0x94, SN_LE16(8), SN_LE16(6), SN_LE32(0), 11, "m_MoveSpeed" },
    { SN_LE32(108), 0x94, SN_LE16(8), SN_LE16(6), SN_LE32(0), 13, "m_StartOffset" },
    { SN_LE32(112), 0x94, SN_LE16(8), SN_LE16(12), SN_LE32(0), 25, "m_TargetVisibleMotionType" },
    { SN_LE32(113), 0x94, SN_LE16(8), SN_LE16(12), SN_LE32(0), 28, "m_TargetNotVisibleMotionType" },
    { SN_LE32(114), 0x94, SN_LE16(8), SN_LE16(12), SN_LE32(0), 4, "pad1" },
    { SN_LE32(115), 0x94, SN_LE16(8), SN_LE16(12), SN_LE32(0), 4, "pad2" },
    { SN_LE32(116), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(116), SN_LE16(0), 21, "CTurretIntelligence_t", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(116), SN_LE16(0), 21, "CTurretIntelligence_t", 19, "CTurretIntelligence" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(12), 24, "CThrowableIntelligence_t" },
    { SN_LE32(0), 0x94, SN_LE16(8), SN_LE16(15), SN_LE32(0), 9, "m_dwFlags" },
    { SN_LE32(4), 0x94, SN_LE16(8), SN_LE16(6), SN_LE32(0), 17, "m_CollisionRadius" },
    { SN_LE32(8), 0x94, SN_LE16(8), SN_LE16(6), SN_LE32(0), 17, "m_CollisionHeight" },
    { SN_LE32(12), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(12), SN_LE16(0), 24, "CThrowableIntelligence_t", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(12), SN_LE16(0), 24, "CThrowableIntelligence_t", 22, "CThrowableIntelligence" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(20), 19, "CDoorIntelligence_t" },
    { SN_LE32(0), 0x94, SN_LE16(8), SN_LE16(15), SN_LE32(0), 9, "m_dwFlags" },
    { SN_LE32(4), 0x94, SN_LE16(8), SN_LE16(6), SN_LE32(0), 14, "m_OpenDuration" },
    { SN_LE32(8), 0x94, SN_LE16(8), SN_LE16(2), SN_LE32(0), 15, "m_OpenDoorEvent" },
    { SN_LE32(9), 0x94, SN_LE16(8), SN_LE16(2), SN_LE32(0), 16, "m_CloseDoorEvent" },
    { SN_LE32(10), 0x94, SN_LE16(8), SN_LE16(2), SN_LE32(0), 4, "pad1" },
    { SN_LE32(11), 0x94, SN_LE16(8), SN_LE16(2), SN_LE32(0), 4, "pad2" },
    { SN_LE32(12), 0x94, SN_LE16(8), SN_LE16(6), SN_LE32(0), 16, "m_AutoOpenRadius" },
    { SN_LE32(16), 0x94, SN_LE16(8), SN_LE16(6), SN_LE32(0), 17, "m_AutoCloseRadius" },
    { SN_LE32(20), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(20), SN_LE16(0), 19, "CDoorIntelligence_t", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(20), SN_LE16(0), 19, "CDoorIntelligence_t", 17, "CDoorIntelligence" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(84), 27, "CDestructibleIntelligence_t" },
    { SN_LE32(0), 0x94, SN_LE16(8), SN_LE16(15), SN_LE32(0), 9, "m_dwFlags" },
    { SN_LE32(4), 0x94, SN_LE16(8), SN_LE16(3), SN_LE32(0), 8, "m_Health" },
    { SN_LE32(6), 0x94, SN_LE16(8), SN_LE16(3), SN_LE32(0), 3, "pad" },
    { SN_LE32(8), 0x94, SN_LE16(8), SN_LE16(6), SN_LE32(0), 17, "m_CollisionRadius" },
    { SN_LE32(12), 0x94, SN_LE16(8), SN_LE16(6), SN_LE32(0), 17, "m_CollisionHeight" },
    { SN_LE32(16), 0x94, SN_LE16(8), SN_LE16(5), SN_LE32(0), 10, "m_IdleAnim" },
    { SN_LE32(20), 0x94, SN_LE16(8), SN_LE16(6), SN_LE32(0), 14, "m_AutoGoRadius" },
    { SN_LE32(24), 0x94, SN_LE16(8), SN_LE16(5), SN_LE32(0), 8, "m_GoAnim" },
    { SN_LE32(28), 0x94, SN_LE16(8), SN_LE16(5), SN_LE32(0), 18, "m_GoParticleEffect" },
    { SN_LE32(32), 0x94, SN_LE16(8), SN_LE16(5), SN_LE32(0), 15, "m_GoSoundEffect" },
    { SN_LE32(36), 0x94, SN_LE16(8), SN_LE16(15), SN_LE32(0), 18, "m_dwGoPickupsFlag1" },
    { SN_LE32(40), 0x94, SN_LE16(8), SN_LE16(15), SN_LE32(0), 18, "m_dwGoPickupsFlag2" },
    { SN_LE32(44), 0x94, SN_LE16(8), SN_LE16(5), SN_LE32(0), 13, "m_GoDeathAnim" },
    { SN_LE32(48), 0x94, SN_LE16(8), SN_LE16(5), SN_LE32(0), 23, "m_GoDeathParticleEffect" },
    { SN_LE32(52), 0x94, SN_LE16(8), SN_LE16(5), SN_LE32(0), 20, "m_GoDeathSoundEffect" },
    { SN_LE32(56), 0x94, SN_LE16(8), SN_LE16(15), SN_LE32(0), 23, "m_dwGoDeathPickupsFlag1" },
    { SN_LE32(60), 0x94, SN_LE16(8), SN_LE16(15), SN_LE32(0), 23, "m_dwGoDeathPickupsFlag2" },
    { SN_LE32(64), 0x94, SN_LE16(8), SN_LE16(5), SN_LE32(0), 22, "m_TotemMissionDuration" },
    { SN_LE32(68), 0x94, SN_LE16(8), SN_LE16(3), SN_LE32(0), 23, "m_EnemiesAttackingTurok" },
    { SN_LE32(70), 0x94, SN_LE16(8), SN_LE16(3), SN_LE32(0), 26, "m_EnemiesToKillToSaveTotem" },
    { SN_LE32(72), 0x96, SN_LE16(8), SN_LE16(60), SN_LE32(4), SN_LE16(1), SN_LE32(4), 0, 12, "m_ModelIndex" },
    { SN_LE32(76), 0x96, SN_LE16(8), SN_LE16(60), SN_LE32(4), SN_LE16(1), SN_LE32(4), 0, 12, "m_ModelFrame" },
    { SN_LE32(80), 0x96, SN_LE16(8), SN_LE16(60), SN_LE32(4), SN_LE16(1), SN_LE32(4), 0, 28, "m_ModelIndexHealthPercentage" },
    { SN_LE32(84), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(84), SN_LE16(0), 27, "CDestructibleIntelligence_t", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(84), SN_LE16(0), 27, "CDestructibleIntelligence_t", 25, "CDestructibleIntelligence" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(16), 21, "CPickupIntelligence_t" },
    { SN_LE32(0), 0x94, SN_LE16(8), SN_LE16(15), SN_LE32(0), 9, "m_dwFlags" },
    { SN_LE32(4), 0x94, SN_LE16(8), SN_LE16(6), SN_LE32(0), 17, "m_CollisionRadius" },
    { SN_LE32(8), 0x94, SN_LE16(8), SN_LE16(6), SN_LE32(0), 17, "m_CollisionHeight" },
    { SN_LE32(12), 0x94, SN_LE16(8), SN_LE16(6), SN_LE32(0), 6, "m_Time" },
    { SN_LE32(16), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(16), SN_LE16(0), 21, "CPickupIntelligence_t", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(16), SN_LE16(0), 21, "CPickupIntelligence_t", 19, "CPickupIntelligence" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(8), 30, "CInteractiveAnimIntelligence_t" },
    { SN_LE32(0), 0x94, SN_LE16(8), SN_LE16(15), SN_LE32(0), 9, "m_dwFlags" },
    { SN_LE32(4), 0x94, SN_LE16(8), SN_LE16(5), SN_LE32(0), 11, "m_StartAnim" },
    { SN_LE32(8), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(8), SN_LE16(0), 30, "CInteractiveAnimIntelligence_t", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(8), SN_LE16(0), 30, "CInteractiveAnimIntelligence_t", 28, "CInteractiveAnimIntelligence" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(28), 21, "CActionIntelligence_t" },
    { SN_LE32(0), 0x94, SN_LE16(8), SN_LE16(15), SN_LE32(0), 9, "m_dwFlags" },
    { SN_LE32(4), 0x94, SN_LE16(8), SN_LE16(6), SN_LE32(0), 17, "m_CollisionRadius" },
    { SN_LE32(8), 0x94, SN_LE16(8), SN_LE16(6), SN_LE32(0), 17, "m_CollisionHeight" },
    { SN_LE32(12), 0x94, SN_LE16(8), SN_LE16(3), SN_LE32(0), 10, "m_IdleAnim" },
    { SN_LE32(14), 0x94, SN_LE16(8), SN_LE16(2), SN_LE32(0), 11, "m_IdleModel" },
    { SN_LE32(15), 0x94, SN_LE16(8), SN_LE16(2), SN_LE32(0), 13, "m_IdleTexture" },
    { SN_LE32(16), 0x94, SN_LE16(8), SN_LE16(6), SN_LE32(0), 14, "m_AutoGoRadius" },
    { SN_LE32(20), 0x94, SN_LE16(8), SN_LE16(3), SN_LE32(0), 8, "m_GoAnim" },
    { SN_LE32(22), 0x94, SN_LE16(8), SN_LE16(3), SN_LE32(0), 16, "m_GoPickupNeeded" },
    { SN_LE32(24), 0x94, SN_LE16(8), SN_LE16(3), SN_LE32(0), 20, "m_GoPickupNeededText" },
    { SN_LE32(26), 0x94, SN_LE16(8), SN_LE16(2), SN_LE32(0), 9, "m_GoModel" },
    { SN_LE32(27), 0x94, SN_LE16(8), SN_LE16(2), SN_LE32(0), 11, "m_GoTexture" },
    { SN_LE32(28), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(28), SN_LE16(0), 21, "CActionIntelligence_t", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(28), SN_LE16(0), 21, "CActionIntelligence_t", 19, "CActionIntelligence" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(372), 21, "CPlayerIntelligence_t" },
    { SN_LE32(0), 0x94, SN_LE16(8), SN_LE16(15), SN_LE32(0), 9, "m_dwFlags" },
    { SN_LE32(4), 0x94, SN_LE16(8), SN_LE16(15), SN_LE32(0), 13, "m_StartHealth" },
    { SN_LE32(8), 0x94, SN_LE16(8), SN_LE16(6), SN_LE32(0), 13, "m_SpeedScaler" },
    { SN_LE32(12), 0x94, SN_LE16(8), SN_LE16(6), SN_LE32(0), 12, "m_JumpScaler" },
    { SN_LE32(16), 0x94, SN_LE16(8), SN_LE16(6), SN_LE32(0), 12, "m_HealHealth" },
    { SN_LE32(20), 0x94, SN_LE16(8), SN_LE16(6), SN_LE32(0), 16, "m_Aggressiveness" },
    { SN_LE32(24), 0x94, SN_LE16(8), SN_LE16(6), SN_LE32(0), 10, "m_Accuracy" },
    { SN_LE32(28), 0x94, SN_LE16(8), SN_LE16(6), SN_LE32(0), 11, "m_Awareness" },
    { SN_LE32(32), 0x94, SN_LE16(8), SN_LE16(6), SN_LE32(0), 13, "m_Evasiveness" },
    { SN_LE32(36), 0x94, SN_LE16(8), SN_LE16(6), SN_LE32(0), 14, "m_SeekKillZone" },
    { SN_LE32(40), 0x94, SN_LE16(8), SN_LE16(6), SN_LE32(0), 16, "m_AvoidDeathZone" },
    { SN_LE32(44), 0x94, SN_LE16(8), SN_LE16(6), SN_LE32(0), 20, "m_CloseAttackComfort" },
    { SN_LE32(48), 0x94, SN_LE16(8), SN_LE16(6), SN_LE32(0), 21, "m_MediumAttackComfort" },
    { SN_LE32(52), 0x94, SN_LE16(8), SN_LE16(6), SN_LE32(0), 18, "m_FarAttackComfort" },
    { SN_LE32(56), 0x96, SN_LE16(8), SN_LE16(63), SN_LE32(32), SN_LE16(1), SN_LE32(8), 0, 12, "m_WeaponList" },
    { SN_LE32(88), 0x96, SN_LE16(8), SN_LE16(54), SN_LE32(32), SN_LE16(1), SN_LE32(8), 0, 16, "m_WeaponAccuracy" },
    { SN_LE32(120), 0x96, SN_LE16(8), SN_LE16(63), SN_LE32(32), SN_LE16(1), SN_LE32(8), 0, 17, "m_WeaponCloseList" },
    { SN_LE32(152), 0x96, SN_LE16(8), SN_LE16(63), SN_LE32(32), SN_LE16(1), SN_LE32(8), 0, 18, "m_WeaponMediumList" },
    { SN_LE32(184), 0x96, SN_LE16(8), SN_LE16(63), SN_LE32(32), SN_LE16(1), SN_LE32(8), 0, 15, "m_WeaponFarList" },
    { SN_LE32(216), 0x94, SN_LE16(8), SN_LE16(6), SN_LE32(0), 17, "m_CollisionRadius" },
    { SN_LE32(220), 0x94, SN_LE16(8), SN_LE16(6), SN_LE32(0), 21, "m_CollisionWallRadius" },
    { SN_LE32(224), 0x94, SN_LE16(8), SN_LE16(6), SN_LE32(0), 17, "m_CollisionHeight" },
    { SN_LE32(228), 0x94, SN_LE16(8), SN_LE16(6), SN_LE32(0), 21, "m_CollisionDeadHeight" },
    { SN_LE32(232), 0x94, SN_LE16(8), SN_LE16(6), SN_LE32(0), 8, "m_ScaleX" },
    { SN_LE32(236), 0x94, SN_LE16(8), SN_LE16(6), SN_LE32(0), 8, "m_ScaleY" },
    { SN_LE32(240), 0x94, SN_LE16(8), SN_LE16(6), SN_LE32(0), 8, "m_ScaleZ" },
    { SN_LE32(244), 0x96, SN_LE16(8), SN_LE16(52), SN_LE32(128), SN_LE16(1), SN_LE32(32), 0, 9, "m_AmmoMax" },
    { SN_LE32(372), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(372), SN_LE16(0), 21, "CPlayerIntelligence_t", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(372), SN_LE16(0), 21, "CPlayerIntelligence_t", 19, "CPlayerIntelligence" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(16), 22, "CMorpherIntelligence_t" },
    { SN_LE32(0), 0x94, SN_LE16(8), SN_LE16(15), SN_LE32(0), 9, "m_dwFlags" },
    { SN_LE32(4), 0x94, SN_LE16(8), SN_LE16(6), SN_LE32(0), 17, "m_CollisionRadius" },
    { SN_LE32(8), 0x94, SN_LE16(8), SN_LE16(6), SN_LE32(0), 17, "m_CollisionHeight" },
    { SN_LE32(12), 0x94, SN_LE16(8), SN_LE16(6), SN_LE32(0), 11, "m_AnimSpeed" },
    { SN_LE32(16), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(16), SN_LE16(0), 22, "CMorpherIntelligence_t", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(16), SN_LE16(0), 22, "CMorpherIntelligence_t", 20, "CMorpherIntelligence" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(16), 27, "CWarpEntranceIntelligence_t" },
    { SN_LE32(0), 0x94, SN_LE16(8), SN_LE16(15), SN_LE32(0), 9, "m_dwFlags" },
    { SN_LE32(4), 0x94, SN_LE16(8), SN_LE16(6), SN_LE32(0), 17, "m_CollisionRadius" },
    { SN_LE32(8), 0x94, SN_LE16(8), SN_LE16(6), SN_LE32(0), 17, "m_CollisionHeight" },
    { SN_LE32(12), 0x94, SN_LE16(8), SN_LE16(15), SN_LE32(0), 15, "m_DestinationID" },
    { SN_LE32(16), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(16), SN_LE16(0), 27, "CWarpEntranceIntelligence_t", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(16), SN_LE16(0), 27, "CWarpEntranceIntelligence_t", 25, "CWarpEntranceIntelligence" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(44), 31, "CWeatherGeneratorIntelligence_t" },
    { SN_LE32(0), 0x94, SN_LE16(8), SN_LE16(13), SN_LE32(0), 8, "m_wFlags" },
    { SN_LE32(2), 0x94, SN_LE16(8), SN_LE16(13), SN_LE32(0), 14, "m_NumParticles" },
    { SN_LE32(4), 0x94, SN_LE16(8), SN_LE16(6), SN_LE32(0), 8, "m_Radius" },
    { SN_LE32(8), 0x94, SN_LE16(8), SN_LE16(6), SN_LE32(0), 13, "m_StartHeight" },
    { SN_LE32(12), 0x94, SN_LE16(8), SN_LE16(13), SN_LE32(0), 17, "m_MinFallVelocity" },
    { SN_LE32(14), 0x94, SN_LE16(8), SN_LE16(13), SN_LE32(0), 17, "m_MaxFallVelocity" },
    { SN_LE32(16), 0x94, SN_LE16(8), SN_LE16(13), SN_LE32(0), 8, "m_SlopeX" },
    { SN_LE32(18), 0x94, SN_LE16(8), SN_LE16(13), SN_LE32(0), 8, "m_SlopeZ" },
    { SN_LE32(20), 0x94, SN_LE16(8), SN_LE16(13), SN_LE32(0), 11, "m_MinLength" },
    { SN_LE32(22), 0x94, SN_LE16(8), SN_LE16(13), SN_LE32(0), 11, "m_MaxLength" },
    { SN_LE32(24), 0x96, SN_LE16(8), SN_LE16(60), SN_LE32(4), SN_LE16(1), SN_LE32(4), 0, 13, "m_UpperColour" },
    { SN_LE32(28), 0x96, SN_LE16(8), SN_LE16(60), SN_LE32(4), SN_LE16(1), SN_LE32(4), 0, 13, "m_LowerColour" },
    { SN_LE32(32), 0x94, SN_LE16(8), SN_LE16(4), SN_LE32(0), 10, "m_nTexture" },
    { SN_LE32(36), 0x94, SN_LE16(8), SN_LE16(13), SN_LE32(0), 10, "m_MinWidth" },
    { SN_LE32(38), 0x94, SN_LE16(8), SN_LE16(13), SN_LE32(0), 10, "m_MaxWidth" },
    { SN_LE32(40), 0x94, SN_LE16(8), SN_LE16(6), SN_LE32(0), 9, "m_Timeout" },
    { SN_LE32(44), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(44), SN_LE16(0), 31, "CWeatherGeneratorIntelligence_t", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(44), SN_LE16(0), 31, "CWeatherGeneratorIntelligence_t", 29, "CWeatherGeneratorIntelligence" },
    { SN_LE32(0), 0x94, SN_LE16(12), SN_LE16(9), SN_LE32(372), 8, ".134fake" },
    { SN_LE32(0), 0x96, SN_LE16(11), SN_LE16(8), SN_LE32(20), SN_LE16(0), 21, "CStaticIntelligence_t", 6, "Static" },
    { SN_LE32(0), 0x96, SN_LE16(11), SN_LE16(8), SN_LE32(140), SN_LE16(0), 20, "CEnemyIntelligence_t", 5, "Enemy" },
    { SN_LE32(0), 0x96, SN_LE16(11), SN_LE16(8), SN_LE32(96), SN_LE16(0), 23, "CPlatformIntelligence_t", 8, "Platform" },
    { SN_LE32(0), 0x96, SN_LE16(11), SN_LE16(8), SN_LE32(40), SN_LE16(0), 24, "CGeneratorIntelligence_t", 9, "Generator" },
    { SN_LE32(0), 0x96, SN_LE16(11), SN_LE16(8), SN_LE32(116), SN_LE16(0), 21, "CTurretIntelligence_t", 6, "Turret" },
    { SN_LE32(0), 0x96, SN_LE16(11), SN_LE16(8), SN_LE32(12), SN_LE16(0), 24, "CThrowableIntelligence_t", 9, "Throwable" },
    { SN_LE32(0), 0x96, SN_LE16(11), SN_LE16(8), SN_LE32(20), SN_LE16(0), 19, "CDoorIntelligence_t", 4, "Door" },
    { SN_LE32(0), 0x96, SN_LE16(11), SN_LE16(8), SN_LE32(84), SN_LE16(0), 27, "CDestructibleIntelligence_t", 12, "Destructible" },
    { SN_LE32(0), 0x96, SN_LE16(11), SN_LE16(8), SN_LE32(16), SN_LE16(0), 21, "CPickupIntelligence_t", 6, "Pickup" },
    { SN_LE32(0), 0x96, SN_LE16(11), SN_LE16(8), SN_LE32(8), SN_LE16(0), 30, "CInteractiveAnimIntelligence_t", 15, "InteractiveAnim" },
    { SN_LE32(0), 0x96, SN_LE16(11), SN_LE16(8), SN_LE32(28), SN_LE16(0), 21, "CActionIntelligence_t", 6, "Action" },
    { SN_LE32(0), 0x96, SN_LE16(11), SN_LE16(8), SN_LE32(372), SN_LE16(0), 21, "CPlayerIntelligence_t", 6, "Player" },
    { SN_LE32(0), 0x96, SN_LE16(11), SN_LE16(8), SN_LE32(16), SN_LE16(0), 22, "CMorpherIntelligence_t", 7, "Morpher" },
    { SN_LE32(0), 0x96, SN_LE16(11), SN_LE16(8), SN_LE32(16), SN_LE16(0), 27, "CWarpEntranceIntelligence_t", 12, "WarpEntrance" },
    { SN_LE32(0), 0x96, SN_LE16(11), SN_LE16(8), SN_LE32(44), SN_LE16(0), 31, "CWeatherGeneratorIntelligence_t", 16, "WeatherGenerator" },
    { SN_LE32(372), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(372), SN_LE16(0), 8, ".134fake", 4, ".eos" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(392), 15, "CIntelligence_t" },
    { SN_LE32(0), 0x94, SN_LE16(8), SN_LE16(5), SN_LE32(0), 7, "m_nType" },
    { SN_LE32(4), 0x94, SN_LE16(8), SN_LE16(15), SN_LE32(0), 9, "m_dwFlags" },
    { SN_LE32(8), 0x94, SN_LE16(8), SN_LE16(6), SN_LE32(0), 10, "m_LODDist2" },
    { SN_LE32(12), 0x94, SN_LE16(8), SN_LE16(3), SN_LE32(0), 4, "m_Id" },
    { SN_LE32(14), 0x94, SN_LE16(8), SN_LE16(2), SN_LE32(0), 8, "m_nModel" },
    { SN_LE32(15), 0x94, SN_LE16(8), SN_LE16(2), SN_LE32(0), 9, "m_nModel2" },
    { SN_LE32(16), 0x94, SN_LE16(8), SN_LE16(2), SN_LE32(0), 14, "m_nShadowModel" },
    { SN_LE32(17), 0x94, SN_LE16(8), SN_LE16(2), SN_LE32(0), 15, "m_nShadowModel2" },
    { SN_LE32(18), 0x94, SN_LE16(8), SN_LE16(2), SN_LE32(0), 10, "m_nTexture" },
    { SN_LE32(19), 0x94, SN_LE16(8), SN_LE16(2), SN_LE32(0), 3, "pad" },
    { SN_LE32(20), 0x96, SN_LE16(8), SN_LE16(9), SN_LE32(372), SN_LE16(0), 8, ".134fake", 1, "u" },
    { SN_LE32(392), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(392), SN_LE16(0), 15, "CIntelligence_t", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(392), SN_LE16(0), 15, "CIntelligence_t", 13, "CIntelligence" },
    { SN_LE32(0), 0x94, SN_LE16(15), SN_LE16(10), SN_LE32(4), 9, "Behaviors" },
    { SN_LE32(0), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 15, "GROUND_BEHAVIOR" },
    { SN_LE32(1), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 12, "AIR_BEHAVIOR" },
    { SN_LE32(2), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 19, "UNDERWATER_BEHAVIOR" },
    { SN_LE32(3), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 14, "BEHAVIOR_COUNT" },
    { SN_LE32(4), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(4), SN_LE16(0), 9, "Behaviors", 4, ".eos" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(4), 11, "CBehavior_t" },
    { SN_LE32(0), 0x96, SN_LE16(8), SN_LE16(50), SN_LE32(3), SN_LE16(1), SN_LE32(3), 0, 6, "m_Type" },
    { SN_LE32(3), 0x94, SN_LE16(8), SN_LE16(2), SN_LE32(0), 17, "m_CurrentBehavior" },
    { SN_LE32(4), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(4), SN_LE16(0), 11, "CBehavior_t", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(4), SN_LE16(0), 11, "CBehavior_t", 9, "CBehavior" },
    { SN_LE32(0), 0x94, SN_LE16(12), SN_LE16(9), SN_LE32(4), 8, ".135fake" },
    { SN_LE32(0), 0x94, SN_LE16(11), SN_LE16(6), SN_LE32(0), 7, "m_float" },
    { SN_LE32(0), 0x94, SN_LE16(11), SN_LE16(4), SN_LE32(0), 5, "m_int" },
    { SN_LE32(0), 0x96, SN_LE16(11), SN_LE16(24), SN_LE32(0), SN_LE16(0), 21, "CGameObjectInstance_t", 11, "m_pAnimInst" },
    { SN_LE32(0), 0x94, SN_LE16(11), SN_LE16(15), SN_LE32(0), 7, "m_DWORD" },
    { SN_LE32(0), 0x96, SN_LE16(11), SN_LE16(60), SN_LE32(4), SN_LE16(1), SN_LE32(4), 0, 7, "m_Bytes" },
    { SN_LE32(0), 0x96, SN_LE16(11), SN_LE16(61), SN_LE32(4), SN_LE16(1), SN_LE32(2), 0, 7, "m_Words" },
    { SN_LE32(0), 0x96, SN_LE16(11), SN_LE16(8), SN_LE32(4), SN_LE16(0), 11, "CBehavior_t", 10, "m_Behavior" },
    { SN_LE32(0), 0x94, SN_LE16(11), SN_LE16(4), SN_LE32(0), 6, "m_BOOL" },
    { SN_LE32(4), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(4), SN_LE16(0), 8, ".135fake", 4, ".eos" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(4), 10, "CMiscVar_t" },
    { SN_LE32(0), 0x96, SN_LE16(8), SN_LE16(9), SN_LE32(4), SN_LE16(0), 8, ".135fake", 1, "u" },
    { SN_LE32(4), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(4), SN_LE16(0), 10, "CMiscVar_t", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(4), SN_LE16(0), 10, "CMiscVar_t", 8, "CMiscVar" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(368), 5, "CAI_t" },
    { SN_LE32(0), 0x94, SN_LE16(8), SN_LE16(15), SN_LE32(0), 9, "m_dwFlags" },
    { SN_LE32(4), 0x94, SN_LE16(8), SN_LE16(5), SN_LE32(0), 8, "m_Health" },
    { SN_LE32(8), 0x94, SN_LE16(8), SN_LE16(5), SN_LE32(0), 13, "m_StartHealth" },
    { SN_LE32(12), 0x94, SN_LE16(8), SN_LE16(15), SN_LE32(0), 14, "m_dwModelFlags" },
    { SN_LE32(16), 0x94, SN_LE16(8), SN_LE16(12), SN_LE32(0), 13, "m_TranqHealth" },
    { SN_LE32(17), 0x94, SN_LE16(8), SN_LE16(2), SN_LE32(0), 7, "padding" },
    { SN_LE32(18), 0x94, SN_LE16(8), SN_LE16(2), SN_LE32(0), 17, "m_FlinchCountdown" },
    { SN_LE32(19), 0x94, SN_LE16(8), SN_LE16(2), SN_LE32(0), 12, "m_FlinchTime" },
    { SN_LE32(20), 0x96, SN_LE16(8), SN_LE16(50), SN_LE32(4), SN_LE16(1), SN_LE32(4), 0, 12, "m_FlinchNode" },
    { SN_LE32(24), 0x96, SN_LE16(8), SN_LE16(8), SN_LE32(12), SN_LE16(0), 10, "CVector3_t", 13, "m_vFlinchAxis" },
    { SN_LE32(36), 0x94, SN_LE16(8), SN_LE16(6), SN_LE32(0), 10, "m_HeadTurn" },
    { SN_LE32(40), 0x94, SN_LE16(8), SN_LE16(6), SN_LE32(0), 10, "m_HeadTilt" },
    { SN_LE32(44), 0x96, SN_LE16(8), SN_LE16(24), SN_LE32(0), SN_LE16(0), 13, "CAIModeInfo_t", 12, "m_pModeTable" },
    { SN_LE32(48), 0x96, SN_LE16(8), SN_LE16(24), SN_LE32(0), SN_LE16(0), 13, "CAIModeInfo_t", 11, "m_pModeInfo" },
    { SN_LE32(52), 0x94, SN_LE16(8), SN_LE16(2), SN_LE32(0), 6, "m_Mode" },
    { SN_LE32(53), 0x94, SN_LE16(8), SN_LE16(2), SN_LE32(0), 15, "m_ModeLastFrame" },
    { SN_LE32(54), 0x94, SN_LE16(8), SN_LE16(2), SN_LE32(0), 12, "m_ModeBefore" },
    { SN_LE32(55), 0x94, SN_LE16(8), SN_LE16(2), SN_LE32(0), 8, "m_Action" },
    { SN_LE32(56), 0x94, SN_LE16(8), SN_LE16(15), SN_LE32(0), 20, "m_ModeLastFrameFlags" },
    { SN_LE32(60), 0x94, SN_LE16(8), SN_LE16(15), SN_LE32(0), 11, "m_ModeFlags" },
    { SN_LE32(64), 0x94, SN_LE16(8), SN_LE16(6), SN_LE32(0), 10, "m_ModeTime" },
    { SN_LE32(68), 0x94, SN_LE16(8), SN_LE16(6), SN_LE32(0), 12, "m_ActionTime" },
    { SN_LE32(72), 0x96, SN_LE16(8), SN_LE16(8), SN_LE32(12), SN_LE16(0), 10, "CVector3_t", 15, "m_vPosLastFrame" },
    { SN_LE32(84), 0x96, SN_LE16(8), SN_LE16(8), SN_LE32(12), SN_LE16(0), 10, "CVector3_t", 13, "m_vDesiredPos" },
    { SN_LE32(96), 0x94, SN_LE16(8), SN_LE16(6), SN_LE32(0), 15, "m_RotYLastFrame" },
    { SN_LE32(100), 0x94, SN_LE16(8), SN_LE16(6), SN_LE32(0), 10, "m_MoveTime" },
    { SN_LE32(104), 0x96, SN_LE16(8), SN_LE16(24), SN_LE32(0), SN_LE16(0), 21, "CGameObjectInstance_t", 9, "m_pLeader" },
    { SN_LE32(108), 0x96, SN_LE16(8), SN_LE16(8), SN_LE32(12), SN_LE16(0), 10, "CVector3_t", 15, "m_vTargetOffset" },
    { SN_LE32(120), 0x96, SN_LE16(8), SN_LE16(24), SN_LE32(0), SN_LE16(0), 21, "CGameObjectInstance_t", 17, "m_pTargetOverride" },
    { SN_LE32(124), 0x94, SN_LE16(8), SN_LE16(6), SN_LE32(0), 20, "m_TargetOverrideTime" },
    { SN_LE32(128), 0x96, SN_LE16(8), SN_LE16(24), SN_LE32(0), SN_LE16(0), 21, "CGameObjectInstance_t", 14, "m_pSightTarget" },
    { SN_LE32(132), 0x96, SN_LE16(8), SN_LE16(24), SN_LE32(0), SN_LE16(0), 13, "CGameRegion_t", 18, "m_pPathAvoidRegion" },
    { SN_LE32(136), 0x96, SN_LE16(8), SN_LE16(24), SN_LE32(0), SN_LE16(0), 21, "CGameObjectInstance_t", 13, "m_pPathTarget" },
    { SN_LE32(140), 0x94, SN_LE16(8), SN_LE16(6), SN_LE32(0), 10, "m_PathRotY" },
    { SN_LE32(144), 0x94, SN_LE16(8), SN_LE16(6), SN_LE32(0), 12, "m_PathHeight" },
    { SN_LE32(148), 0x96, SN_LE16(8), SN_LE16(8), SN_LE32(8), SN_LE16(0), 10, "CPathTrack", 11, "m_PathTrack" },
    { SN_LE32(156), 0x94, SN_LE16(8), SN_LE16(6), SN_LE32(0), 11, "m_StartRotY" },
    { SN_LE32(160), 0x96, SN_LE16(8), SN_LE16(8), SN_LE32(12), SN_LE16(0), 10, "CVector3_t", 11, "m_vStartPos" },
    { SN_LE32(172), 0x96, SN_LE16(8), SN_LE16(24), SN_LE32(0), SN_LE16(0), 13, "CGameRegion_t", 14, "m_pStartRegion" },
    { SN_LE32(176), 0x96, SN_LE16(8), SN_LE16(8), SN_LE32(12), SN_LE16(0), 10, "CVector3_t", 11, "m_vLeashPos" },
    { SN_LE32(188), 0x96, SN_LE16(8), SN_LE16(24), SN_LE32(0), SN_LE16(0), 13, "CGameRegion_t", 14, "m_pLeashRegion" },
    { SN_LE32(192), 0x94, SN_LE16(8), SN_LE16(6), SN_LE32(0), 11, "m_AnimSpeed" },
    { SN_LE32(196), 0x94, SN_LE16(8), SN_LE16(6), SN_LE32(0), 15, "m_ModeAnimSpeed" },
    { SN_LE32(200), 0x94, SN_LE16(8), SN_LE16(3), SN_LE32(0), 10, "m_AnimType" },
    { SN_LE32(202), 0x94, SN_LE16(8), SN_LE16(2), SN_LE32(0), 11, "m_AnimIndex" },
    { SN_LE32(203), 0x94, SN_LE16(8), SN_LE16(2), SN_LE32(0), 12, "m_AnimPlayed" },
    { SN_LE32(204), 0x94, SN_LE16(8), SN_LE16(12), SN_LE32(0), 12, "m_Aggression" },
    { SN_LE32(205), 0x94, SN_LE16(8), SN_LE16(12), SN_LE32(0), 12, "m_FreezeTime" },
    { SN_LE32(206), 0x94, SN_LE16(8), SN_LE16(2), SN_LE32(0), 15, "m_PathFindCount" },
    { SN_LE32(207), 0x94, SN_LE16(8), SN_LE16(2), SN_LE32(0), 24, "m_FramesSinceLastPainSFX" },
    { SN_LE32(208), 0x94, SN_LE16(8), SN_LE16(6), SN_LE32(0), 18, "m_DeathRegionTimer" },
    { SN_LE32(212), 0x94, SN_LE16(8), SN_LE16(6), SN_LE32(0), 13, "m_OnFireTimer" },
    { SN_LE32(216), 0x96, SN_LE16(8), SN_LE16(8), SN_LE32(12), SN_LE16(0), 10, "CVector3_t", 13, "m_vBoreTarget" },
    { SN_LE32(228), 0x96, SN_LE16(8), SN_LE16(8), SN_LE32(12), SN_LE16(0), 10, "CVector3_t", 17, "m_vBoreCollNormal" },
    { SN_LE32(240), 0x96, SN_LE16(8), SN_LE16(8), SN_LE32(12), SN_LE16(0), 10, "CVector3_t", 19, "m_vLaserSightSource" },
    { SN_LE32(252), 0x96, SN_LE16(8), SN_LE16(24), SN_LE32(32), SN_LE16(0), 19, "CLoopingSoundData_t", 23, "m_pAttachedLoopingSound" },
    { SN_LE32(256), 0x94, SN_LE16(8), SN_LE16(2), SN_LE32(0), 19, "m_UseAlternateModel" },
    { SN_LE32(258), 0x94, SN_LE16(8), SN_LE16(3), SN_LE32(0), 13, "m_wLimbStatus" },
    { SN_LE32(260), 0x94, SN_LE16(8), SN_LE16(2), SN_LE32(0), 3, "pad" },
    { SN_LE32(264), 0x94, SN_LE16(8), SN_LE16(145), SN_LE32(0), 11, "m_pfAdvance" },
    { SN_LE32(268), 0x94, SN_LE16(8), SN_LE16(145), SN_LE32(0), 8, "m_pfDraw" },
    { SN_LE32(272), 0x94, SN_LE16(8), SN_LE16(145), SN_LE32(0), 18, "m_pfDecreaseHealth" },
    { SN_LE32(276), 0x94, SN_LE16(8), SN_LE16(145), SN_LE32(0), 13, "m_pfCollision" },
    { SN_LE32(280), 0x94, SN_LE16(8), SN_LE16(145), SN_LE32(0), 17, "m_pfHitByParticle" },
    { SN_LE32(284), 0x94, SN_LE16(8), SN_LE16(145), SN_LE32(0), 30, "m_pfCalculateOrientationMatrix" },
    { SN_LE32(288), 0x94, SN_LE16(8), SN_LE16(145), SN_LE32(0), 18, "m_pfSpecialEffects" },
    { SN_LE32(292), 0x96, SN_LE16(8), SN_LE16(8), SN_LE32(4), SN_LE16(0), 10, "CMiscVar_t", 4, "m_M0" },
    { SN_LE32(296), 0x96, SN_LE16(8), SN_LE16(8), SN_LE32(4), SN_LE16(0), 10, "CMiscVar_t", 4, "m_M1" },
    { SN_LE32(300), 0x96, SN_LE16(8), SN_LE16(8), SN_LE32(4), SN_LE16(0), 10, "CMiscVar_t", 4, "m_M2" },
    { SN_LE32(304), 0x96, SN_LE16(8), SN_LE16(8), SN_LE32(4), SN_LE16(0), 10, "CMiscVar_t", 4, "m_M3" },
    { SN_LE32(308), 0x96, SN_LE16(8), SN_LE16(8), SN_LE32(4), SN_LE16(0), 10, "CMiscVar_t", 4, "m_M4" },
    { SN_LE32(312), 0x96, SN_LE16(8), SN_LE16(8), SN_LE32(4), SN_LE16(0), 10, "CMiscVar_t", 4, "m_M5" },
    { SN_LE32(316), 0x96, SN_LE16(8), SN_LE16(8), SN_LE32(4), SN_LE16(0), 10, "CMiscVar_t", 4, "m_M6" },
    { SN_LE32(320), 0x96, SN_LE16(8), SN_LE16(8), SN_LE32(4), SN_LE16(0), 10, "CMiscVar_t", 4, "m_M7" },
    { SN_LE32(324), 0x96, SN_LE16(8), SN_LE16(8), SN_LE32(4), SN_LE16(0), 10, "CMiscVar_t", 4, "m_M8" },
    { SN_LE32(328), 0x96, SN_LE16(8), SN_LE16(8), SN_LE32(4), SN_LE16(0), 10, "CMiscVar_t", 4, "m_M9" },
    { SN_LE32(332), 0x96, SN_LE16(8), SN_LE16(8), SN_LE32(4), SN_LE16(0), 10, "CMiscVar_t", 5, "m_M10" },
    { SN_LE32(336), 0x96, SN_LE16(8), SN_LE16(8), SN_LE32(4), SN_LE16(0), 10, "CMiscVar_t", 5, "m_M11" },
    { SN_LE32(340), 0x96, SN_LE16(8), SN_LE16(8), SN_LE32(4), SN_LE16(0), 10, "CMiscVar_t", 5, "m_M12" },
    { SN_LE32(344), 0x96, SN_LE16(8), SN_LE16(8), SN_LE32(4), SN_LE16(0), 10, "CMiscVar_t", 5, "m_M13" },
    { SN_LE32(348), 0x96, SN_LE16(8), SN_LE16(8), SN_LE32(4), SN_LE16(0), 10, "CMiscVar_t", 5, "m_M14" },
    { SN_LE32(352), 0x96, SN_LE16(8), SN_LE16(8), SN_LE32(4), SN_LE16(0), 10, "CMiscVar_t", 5, "m_M15" },
    { SN_LE32(356), 0x96, SN_LE16(8), SN_LE16(8), SN_LE32(4), SN_LE16(0), 10, "CMiscVar_t", 5, "m_M16" },
    { SN_LE32(360), 0x96, SN_LE16(8), SN_LE16(8), SN_LE32(4), SN_LE16(0), 10, "CMiscVar_t", 5, "m_M17" },
    { SN_LE32(364), 0x96, SN_LE16(8), SN_LE16(8), SN_LE32(4), SN_LE16(0), 10, "CMiscVar_t", 5, "m_M18" },
    { SN_LE32(368), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(368), SN_LE16(0), 5, "CAI_t", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(368), SN_LE16(0), 5, "CAI_t", 3, "CAI" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(32), 15, "CAnimCompInfo_t" },
    { SN_LE32(0), 0x94, SN_LE16(8), SN_LE16(4), SN_LE32(0), 10, "SmoothSize" },
    { SN_LE32(4), 0x94, SN_LE16(8), SN_LE16(4), SN_LE32(0), 7, "nFrames" },
    { SN_LE32(8), 0x94, SN_LE16(8), SN_LE16(4), SN_LE32(0), 10, "DecompMode" },
    { SN_LE32(12), 0x94, SN_LE16(8), SN_LE16(6), SN_LE32(0), 9, "Tolerance" },
    { SN_LE32(16), 0x94, SN_LE16(8), SN_LE16(4), SN_LE32(0), 4, "nRot" },
    { SN_LE32(20), 0x94, SN_LE16(8), SN_LE16(4), SN_LE32(0), 6, "nTrans" },
    { SN_LE32(24), 0x94, SN_LE16(8), SN_LE16(6), SN_LE32(0), 10, "nNewFrames" },
    { SN_LE32(28), 0x94, SN_LE16(8), SN_LE16(6), SN_LE32(0), 10, "FrameScale" },
    { SN_LE32(32), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(32), SN_LE16(0), 15, "CAnimCompInfo_t", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(32), SN_LE16(0), 15, "CAnimCompInfo_t", 13, "CAnimCompInfo" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(20), 24, "CROMInitialOrientation_t" },
    { SN_LE32(0), 0x96, SN_LE16(8), SN_LE16(8), SN_LE32(12), SN_LE16(0), 10, "CVector3_t", 6, "m_vPos" },
    { SN_LE32(12), 0x94, SN_LE16(8), SN_LE16(3), SN_LE32(0), 6, "m_RotX" },
    { SN_LE32(14), 0x94, SN_LE16(8), SN_LE16(3), SN_LE32(0), 6, "m_RotY" },
    { SN_LE32(16), 0x94, SN_LE16(8), SN_LE16(3), SN_LE32(0), 6, "m_RotZ" },
    { SN_LE32(18), 0x94, SN_LE16(8), SN_LE16(3), SN_LE32(0), 6, "m_RotT" },
    { SN_LE32(20), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(20), SN_LE16(0), 24, "CROMInitialOrientation_t", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(20), SN_LE16(0), 24, "CROMInitialOrientation_t", 22, "CROMInitialOrientation" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(4), 15, "CROMNodeIndex_t" },
    { SN_LE32(0), 0x94, SN_LE16(8), SN_LE16(3), SN_LE32(0), 17, "m_nTranslationSet" },
    { SN_LE32(2), 0x94, SN_LE16(8), SN_LE16(3), SN_LE32(0), 14, "m_nRotationSet" },
    { SN_LE32(4), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(4), SN_LE16(0), 15, "CROMNodeIndex_t", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(4), SN_LE16(0), 15, "CROMNodeIndex_t", 13, "CROMNodeIndex" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(24), 20, "CTranslationOffset_t" },
    { SN_LE32(0), 0x96, SN_LE16(8), SN_LE16(8), SN_LE32(12), SN_LE16(0), 10, "CVector3_t", 9, "m_vOffset" },
    { SN_LE32(12), 0x96, SN_LE16(8), SN_LE16(8), SN_LE32(12), SN_LE16(0), 10, "CVector3_t", 8, "m_vScale" },
    { SN_LE32(24), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(24), SN_LE16(0), 20, "CTranslationOffset_t", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(24), SN_LE16(0), 20, "CTranslationOffset_t", 18, "CTranslationOffset" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(12), 16, "CROMTransition_t" },
    { SN_LE32(0), 0x94, SN_LE16(8), SN_LE16(13), SN_LE32(0), 17, "m_BlendFromLength" },
    { SN_LE32(2), 0x94, SN_LE16(8), SN_LE16(13), SN_LE32(0), 14, "m_nExitToFrame" },
    { SN_LE32(4), 0x94, SN_LE16(8), SN_LE16(13), SN_LE32(0), 12, "m_BlendStart" },
    { SN_LE32(6), 0x94, SN_LE16(8), SN_LE16(13), SN_LE32(0), 13, "m_BlendFinish" },
    { SN_LE32(8), 0x94, SN_LE16(8), SN_LE16(6), SN_LE32(0), 5, "m_FPS" },
    { SN_LE32(12), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(12), SN_LE16(0), 16, "CROMTransition_t", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(12), SN_LE16(0), 16, "CROMTransition_t", 14, "CROMTransition" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(12), 21, "CROMTransitionEntry_t" },
    { SN_LE32(0), 0x94, SN_LE16(8), SN_LE16(15), SN_LE32(0), 16, "m_nRequestedAnim" },
    { SN_LE32(4), 0x94, SN_LE16(8), SN_LE16(15), SN_LE32(0), 15, "m_nWaitForFrame" },
    { SN_LE32(8), 0x94, SN_LE16(8), SN_LE16(15), SN_LE32(0), 16, "m_nDeliveredAnim" },
    { SN_LE32(12), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(12), SN_LE16(0), 21, "CROMTransitionEntry_t", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(12), SN_LE16(0), 21, "CROMTransitionEntry_t", 19, "CROMTransitionEntry" },
    { SN_LE32(0), 0x94, SN_LE16(15), SN_LE16(10), SN_LE32(4), 17, "EventValueFormats" },
    { SN_LE32(0), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 14, "EVENT_FORMAT1A" },
    { SN_LE32(1), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 14, "EVENT_FORMAT2A" },
    { SN_LE32(2), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 14, "EVENT_FORMAT2B" },
    { SN_LE32(3), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 14, "EVENT_FORMAT3A" },
    { SN_LE32(4), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 14, "EVENT_FORMAT4A" },
    { SN_LE32(5), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 14, "EVENT_FORMAT6A" },
    { SN_LE32(6), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 14, "EVENT_FORMAT7A" },
    { SN_LE32(7), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 13, "EVENT_FORMATS" },
    { SN_LE32(4), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(4), SN_LE16(0), 17, "EventValueFormats", 4, ".eos" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(4), 21, "s_CEventValueFormat1a" },
    { SN_LE32(0), 0x94, SN_LE16(8), SN_LE16(5), SN_LE32(0), 12, "m_s32_Value1" },
    { SN_LE32(4), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(4), SN_LE16(0), 21, "s_CEventValueFormat1a", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(4), SN_LE16(0), 21, "s_CEventValueFormat1a", 19, "CEventValueFormat1a" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(8), 21, "s_CEventValueFormat2a" },
    { SN_LE32(0), 0x94, SN_LE16(8), SN_LE16(5), SN_LE32(0), 12, "m_s32_Value1" },
    { SN_LE32(4), 0x94, SN_LE16(8), SN_LE16(5), SN_LE32(0), 12, "m_s32_Value2" },
    { SN_LE32(8), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(8), SN_LE16(0), 21, "s_CEventValueFormat2a", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(8), SN_LE16(0), 21, "s_CEventValueFormat2a", 19, "CEventValueFormat2a" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(8), 21, "s_CEventValueFormat2b" },
    { SN_LE32(0), 0x94, SN_LE16(8), SN_LE16(5), SN_LE32(0), 12, "m_s32_Value1" },
    { SN_LE32(4), 0x94, SN_LE16(8), SN_LE16(6), SN_LE32(0), 12, "m_f32_Value2" },
    { SN_LE32(8), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(8), SN_LE16(0), 21, "s_CEventValueFormat2b", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(8), SN_LE16(0), 21, "s_CEventValueFormat2b", 19, "CEventValueFormat2b" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(8), 21, "s_CEventValueFormat3a" },
    { SN_LE32(0), 0x94, SN_LE16(8), SN_LE16(5), SN_LE32(0), 12, "m_s32_Value1" },
    { SN_LE32(4), 0x94, SN_LE16(8), SN_LE16(3), SN_LE32(0), 12, "m_s16_Value2" },
    { SN_LE32(6), 0x94, SN_LE16(8), SN_LE16(2), SN_LE32(0), 11, "m_s8_Value3" },
    { SN_LE32(8), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(8), SN_LE16(0), 21, "s_CEventValueFormat3a", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(8), SN_LE16(0), 21, "s_CEventValueFormat3a", 19, "CEventValueFormat3a" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(8), 21, "s_CEventValueFormat4a" },
    { SN_LE32(0), 0x94, SN_LE16(8), SN_LE16(3), SN_LE32(0), 12, "m_s16_Value1" },
    { SN_LE32(2), 0x94, SN_LE16(8), SN_LE16(3), SN_LE32(0), 12, "m_s16_Value2" },
    { SN_LE32(4), 0x94, SN_LE16(8), SN_LE16(3), SN_LE32(0), 12, "m_s16_Value3" },
    { SN_LE32(6), 0x94, SN_LE16(8), SN_LE16(3), SN_LE32(0), 12, "m_s16_Value4" },
    { SN_LE32(8), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(8), SN_LE16(0), 21, "s_CEventValueFormat4a", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(8), SN_LE16(0), 21, "s_CEventValueFormat4a", 19, "CEventValueFormat4a" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(8), 21, "s_CEventValueFormat6a" },
    { SN_LE32(0), 0x94, SN_LE16(8), SN_LE16(3), SN_LE32(0), 12, "m_s16_Value1" },
    { SN_LE32(2), 0x94, SN_LE16(8), SN_LE16(3), SN_LE32(0), 12, "m_s16_Value2" },
    { SN_LE32(4), 0x94, SN_LE16(8), SN_LE16(2), SN_LE32(0), 11, "m_s8_Value3" },
    { SN_LE32(5), 0x94, SN_LE16(8), SN_LE16(2), SN_LE32(0), 11, "m_s8_Value4" },
    { SN_LE32(6), 0x94, SN_LE16(8), SN_LE16(2), SN_LE32(0), 11, "m_s8_Value5" },
    { SN_LE32(7), 0x94, SN_LE16(8), SN_LE16(2), SN_LE32(0), 11, "m_s8_Value6" },
    { SN_LE32(8), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(8), SN_LE16(0), 21, "s_CEventValueFormat6a", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(8), SN_LE16(0), 21, "s_CEventValueFormat6a", 19, "CEventValueFormat6a" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(7), 21, "s_CEventValueFormat7a" },
    { SN_LE32(0), 0x94, SN_LE16(8), SN_LE16(12), SN_LE32(0), 11, "m_u8_Value1" },
    { SN_LE32(1), 0x94, SN_LE16(8), SN_LE16(12), SN_LE32(0), 11, "m_u8_Value2" },
    { SN_LE32(2), 0x94, SN_LE16(8), SN_LE16(12), SN_LE32(0), 11, "m_u8_Value3" },
    { SN_LE32(3), 0x94, SN_LE16(8), SN_LE16(12), SN_LE32(0), 11, "m_u8_Value4" },
    { SN_LE32(4), 0x94, SN_LE16(8), SN_LE16(12), SN_LE32(0), 11, "m_u8_Value5" },
    { SN_LE32(5), 0x94, SN_LE16(8), SN_LE16(12), SN_LE32(0), 11, "m_u8_Value6" },
    { SN_LE32(6), 0x94, SN_LE16(8), SN_LE16(12), SN_LE32(0), 11, "m_u8_Value7" },
    { SN_LE32(7), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(7), SN_LE16(0), 21, "s_CEventValueFormat7a", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(7), SN_LE16(0), 21, "s_CEventValueFormat7a", 19, "CEventValueFormat7a" },
    { SN_LE32(0), 0x94, SN_LE16(12), SN_LE16(9), SN_LE32(8), 8, ".136fake" },
    { SN_LE32(0), 0x96, SN_LE16(11), SN_LE16(8), SN_LE32(4), SN_LE16(0), 21, "s_CEventValueFormat1a", 10, "m_Format1a" },
    { SN_LE32(0), 0x96, SN_LE16(11), SN_LE16(8), SN_LE32(8), SN_LE16(0), 21, "s_CEventValueFormat2a", 10, "m_Format2a" },
    { SN_LE32(0), 0x96, SN_LE16(11), SN_LE16(8), SN_LE32(8), SN_LE16(0), 21, "s_CEventValueFormat2b", 10, "m_Format2b" },
    { SN_LE32(0), 0x96, SN_LE16(11), SN_LE16(8), SN_LE32(8), SN_LE16(0), 21, "s_CEventValueFormat3a", 10, "m_Format3a" },
    { SN_LE32(0), 0x96, SN_LE16(11), SN_LE16(8), SN_LE32(8), SN_LE16(0), 21, "s_CEventValueFormat4a", 10, "m_Format4a" },
    { SN_LE32(0), 0x96, SN_LE16(11), SN_LE16(8), SN_LE32(8), SN_LE16(0), 21, "s_CEventValueFormat6a", 10, "m_Format6a" },
    { SN_LE32(0), 0x96, SN_LE16(11), SN_LE16(8), SN_LE32(7), SN_LE16(0), 21, "s_CEventValueFormat7a", 10, "m_Format7a" },
    { SN_LE32(8), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(8), SN_LE16(0), 8, ".136fake", 4, ".eos" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(8), 13, "s_CEventValue" },
    { SN_LE32(0), 0x96, SN_LE16(8), SN_LE16(9), SN_LE32(8), SN_LE16(0), 8, ".136fake", 1, "u" },
    { SN_LE32(8), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(8), SN_LE16(0), 13, "s_CEventValue", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(8), SN_LE16(0), 13, "s_CEventValue", 11, "CEventValue" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(28), 16, "CROMEventEntry_t" },
    { SN_LE32(0), 0x94, SN_LE16(8), SN_LE16(13), SN_LE32(0), 8, "m_nFrame" },
    { SN_LE32(2), 0x94, SN_LE16(8), SN_LE16(13), SN_LE32(0), 8, "m_nEvent" },
    { SN_LE32(4), 0x94, SN_LE16(8), SN_LE16(3), SN_LE32(0), 7, "m_nNode" },
    { SN_LE32(6), 0x94, SN_LE16(8), SN_LE16(13), SN_LE32(0), 3, "pad" },
    { SN_LE32(8), 0x96, SN_LE16(8), SN_LE16(8), SN_LE32(12), SN_LE16(0), 10, "CVector3_t", 9, "m_vOffset" },
    { SN_LE32(20), 0x96, SN_LE16(8), SN_LE16(8), SN_LE32(8), SN_LE16(0), 13, "s_CEventValue", 7, "m_Value" },
    { SN_LE32(28), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(28), SN_LE16(0), 16, "CROMEventEntry_t", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(28), SN_LE16(0), 16, "CROMEventEntry_t", 14, "CROMEventEntry" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(4), 10, "CVisBits_t" },
    { SN_LE32(0), 0x96, SN_LE16(8), SN_LE16(63), SN_LE32(4), SN_LE16(1), SN_LE32(1), 0, 4, "Bits" },
    { SN_LE32(4), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(4), SN_LE16(0), 10, "CVisBits_t", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(4), SN_LE16(0), 10, "CVisBits_t", 8, "CVisBits" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(16), 15, "CROMCornerEnc_t" },
    { SN_LE32(0), 0x94, SN_LE16(8), SN_LE16(5), SN_LE32(0), 1, "x" },
    { SN_LE32(4), 0x94, SN_LE16(8), SN_LE16(5), SN_LE32(0), 1, "y" },
    { SN_LE32(8), 0x94, SN_LE16(8), SN_LE16(5), SN_LE32(0), 1, "z" },
    { SN_LE32(12), 0x94, SN_LE16(8), SN_LE16(5), SN_LE32(0), 1, "c" },
    { SN_LE32(16), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(16), SN_LE16(0), 15, "CROMCornerEnc_t", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(16), SN_LE16(0), 15, "CROMCornerEnc_t", 13, "CROMCornerEnc" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(16), 12, "CROMCorner_t" },
    { SN_LE32(0), 0x96, SN_LE16(8), SN_LE16(8), SN_LE32(12), SN_LE16(0), 10, "CVector3_t", 9, "m_vCorner" },
    { SN_LE32(12), 0x94, SN_LE16(8), SN_LE16(6), SN_LE32(0), 9, "m_Ceiling" },
    { SN_LE32(16), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(16), SN_LE16(0), 12, "CROMCorner_t", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(16), SN_LE16(0), 12, "CROMCorner_t", 10, "CROMCorner" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(100), 15, "CROMRegionSet_t" },
    { SN_LE32(0), 0x96, SN_LE16(8), SN_LE16(60), SN_LE32(4), SN_LE16(1), SN_LE32(4), 0, 10, "m_FogColor" },
    { SN_LE32(4), 0x96, SN_LE16(8), SN_LE16(60), SN_LE32(4), SN_LE16(1), SN_LE32(4), 0, 12, "m_WaterColor" },
    { SN_LE32(8), 0x94, SN_LE16(8), SN_LE16(15), SN_LE32(0), 10, "m_FogStart" },
    { SN_LE32(12), 0x94, SN_LE16(8), SN_LE16(15), SN_LE32(0), 12, "m_WaterStart" },
    { SN_LE32(16), 0x94, SN_LE16(8), SN_LE16(6), SN_LE32(0), 9, "m_FarClip" },
    { SN_LE32(20), 0x94, SN_LE16(8), SN_LE16(6), SN_LE32(0), 13, "m_FieldOfView" },
    { SN_LE32(24), 0x94, SN_LE16(8), SN_LE16(6), SN_LE32(0), 14, "m_WaterFarClip" },
    { SN_LE32(28), 0x94, SN_LE16(8), SN_LE16(6), SN_LE32(0), 18, "m_WaterFieldOfView" },
    { SN_LE32(32), 0x94, SN_LE16(8), SN_LE16(6), SN_LE32(0), 16, "m_WaterElevation" },
    { SN_LE32(36), 0x94, SN_LE16(8), SN_LE16(6), SN_LE32(0), 13, "m_BlendLength" },
    { SN_LE32(40), 0x94, SN_LE16(8), SN_LE16(6), SN_LE32(0), 16, "m_DeathTimeDelay" },
    { SN_LE32(44), 0x94, SN_LE16(8), SN_LE16(6), SN_LE32(0), 21, "m_CameraVertEyeOffset" },
    { SN_LE32(48), 0x94, SN_LE16(8), SN_LE16(6), SN_LE32(0), 22, "m_CameraMovementScaler" },
    { SN_LE32(52), 0x94, SN_LE16(8), SN_LE16(6), SN_LE32(0), 13, "m_JumpPadEndX" },
    { SN_LE32(56), 0x94, SN_LE16(8), SN_LE16(6), SN_LE32(0), 13, "m_JumpPadEndY" },
    { SN_LE32(60), 0x94, SN_LE16(8), SN_LE16(6), SN_LE32(0), 13, "m_JumpPadEndZ" },
    { SN_LE32(64), 0x94, SN_LE16(8), SN_LE16(6), SN_LE32(0), 15, "m_JumpPadHeight" },
    { SN_LE32(68), 0x94, SN_LE16(8), SN_LE16(15), SN_LE32(0), 9, "m_dwFlags" },
    { SN_LE32(72), 0x94, SN_LE16(8), SN_LE16(13), SN_LE32(0), 8, "m_WarpID" },
    { SN_LE32(74), 0x94, SN_LE16(8), SN_LE16(13), SN_LE32(0), 26, "m_PressurePlateSoundNumber" },
    { SN_LE32(76), 0x94, SN_LE16(8), SN_LE16(13), SN_LE32(0), 18, "m_SaveCheckpointID" },
    { SN_LE32(78), 0x94, SN_LE16(8), SN_LE16(13), SN_LE32(0), 12, "m_PressureID" },
    { SN_LE32(80), 0x94, SN_LE16(8), SN_LE16(13), SN_LE32(0), 16, "m_DeathHitPoints" },
    { SN_LE32(82), 0x94, SN_LE16(8), SN_LE16(13), SN_LE32(0), 9, "m_wFlags2" },
    { SN_LE32(84), 0x94, SN_LE16(8), SN_LE16(13), SN_LE32(0), 9, "m_wFlags3" },
    { SN_LE32(86), 0x94, SN_LE16(8), SN_LE16(13), SN_LE32(0), 12, "m_wSkyLayers" },
    { SN_LE32(88), 0x94, SN_LE16(8), SN_LE16(12), SN_LE32(0), 11, "m_GroundMat" },
    { SN_LE32(89), 0x94, SN_LE16(8), SN_LE16(12), SN_LE32(0), 9, "m_WallMat" },
    { SN_LE32(90), 0x94, SN_LE16(8), SN_LE16(12), SN_LE32(0), 9, "m_MusicID" },
    { SN_LE32(91), 0x94, SN_LE16(8), SN_LE16(12), SN_LE32(0), 15, "m_AmbientSounds" },
    { SN_LE32(92), 0x94, SN_LE16(8), SN_LE16(12), SN_LE32(0), 10, "m_MapColor" },
    { SN_LE32(93), 0x94, SN_LE16(8), SN_LE16(12), SN_LE32(0), 17, "m_CurrentStrength" },
    { SN_LE32(94), 0x94, SN_LE16(8), SN_LE16(12), SN_LE32(0), 13, "m_JumpPadTime" },
    { SN_LE32(95), 0x94, SN_LE16(8), SN_LE16(2), SN_LE32(0), 19, "m_CurrentDirectionX" },
    { SN_LE32(96), 0x94, SN_LE16(8), SN_LE16(2), SN_LE32(0), 19, "m_CurrentDirectionY" },
    { SN_LE32(97), 0x94, SN_LE16(8), SN_LE16(2), SN_LE32(0), 19, "m_CurrentDirectionZ" },
    { SN_LE32(98), 0x94, SN_LE16(8), SN_LE16(13), SN_LE32(0), 11, "m_WeatherID" },
    { SN_LE32(100), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(100), SN_LE16(0), 15, "CROMRegionSet_t", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(100), SN_LE16(0), 15, "CROMRegionSet_t", 13, "CROMRegionSet" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(20), 12, "CROMRegion_t" },
    { SN_LE32(0), 0x94, SN_LE16(8), SN_LE16(13), SN_LE32(0), 12, "m_nRegionSet" },
    { SN_LE32(2), 0x94, SN_LE16(8), SN_LE16(13), SN_LE32(0), 8, "m_wFlags" },
    { SN_LE32(4), 0x96, SN_LE16(8), SN_LE16(61), SN_LE32(6), SN_LE16(1), SN_LE32(3), 0, 9, "m_Corners" },
    { SN_LE32(10), 0x96, SN_LE16(8), SN_LE16(61), SN_LE32(6), SN_LE16(1), SN_LE32(3), 0, 11, "m_Neighbors" },
    { SN_LE32(16), 0x96, SN_LE16(8), SN_LE16(8), SN_LE32(4), SN_LE16(0), 10, "CVisBits_t", 9, "m_VisBits" },
    { SN_LE32(20), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(20), SN_LE16(0), 12, "CROMRegion_t", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(20), SN_LE16(0), 12, "CROMRegion_t", 10, "CROMRegion" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(32), 13, "CGameRegion_t" },
    { SN_LE32(0), 0x94, SN_LE16(8), SN_LE16(13), SN_LE32(0), 12, "m_nRegionSet" },
    { SN_LE32(2), 0x94, SN_LE16(8), SN_LE16(13), SN_LE32(0), 8, "m_wFlags" },
    { SN_LE32(4), 0x96, SN_LE16(8), SN_LE16(120), SN_LE32(12), SN_LE16(1), SN_LE32(3), 12, "CROMCorner_t", 10, "m_pCorners" },
    { SN_LE32(16), 0x96, SN_LE16(8), SN_LE16(120), SN_LE32(12), SN_LE16(1), SN_LE32(3), 13, "CGameRegion_t", 12, "m_pNeighbors" },
    { SN_LE32(28), 0x96, SN_LE16(8), SN_LE16(8), SN_LE32(4), SN_LE16(0), 10, "CVisBits_t", 9, "m_VisBits" },
    { SN_LE32(32), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(32), SN_LE16(0), 13, "CGameRegion_t", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(32), SN_LE16(0), 13, "CGameRegion_t", 11, "CGameRegion" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(24), 12, "CROMBounds_t" },
    { SN_LE32(0), 0x96, SN_LE16(8), SN_LE16(8), SN_LE32(12), SN_LE16(0), 10, "CVector3_t", 6, "m_vMin" },
    { SN_LE32(12), 0x96, SN_LE16(8), SN_LE16(8), SN_LE32(12), SN_LE16(0), 10, "CVector3_t", 6, "m_vMax" },
    { SN_LE32(24), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(24), SN_LE16(0), 12, "CROMBounds_t", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(24), SN_LE16(0), 12, "CROMBounds_t", 10, "CROMBounds" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(16), 13, "CBoundsRect_t" },
    { SN_LE32(0), 0x94, SN_LE16(8), SN_LE16(6), SN_LE32(0), 6, "m_MinX" },
    { SN_LE32(4), 0x94, SN_LE16(8), SN_LE16(6), SN_LE32(0), 6, "m_MinZ" },
    { SN_LE32(8), 0x94, SN_LE16(8), SN_LE16(6), SN_LE32(0), 6, "m_MaxX" },
    { SN_LE32(12), 0x94, SN_LE16(8), SN_LE16(6), SN_LE32(0), 6, "m_MaxZ" },
    { SN_LE32(16), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(16), SN_LE16(0), 13, "CBoundsRect_t", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(16), SN_LE16(0), 13, "CBoundsRect_t", 11, "CBoundsRect" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(20), 17, "CROMRegionBlock_t" },
    { SN_LE32(0), 0x96, SN_LE16(8), SN_LE16(8), SN_LE32(16), SN_LE16(0), 13, "CBoundsRect_t", 12, "m_BoundsRect" },
    { SN_LE32(16), 0x94, SN_LE16(8), SN_LE16(15), SN_LE32(0), 10, "m_nRegions" },
    { SN_LE32(20), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(20), SN_LE16(0), 17, "CROMRegionBlock_t", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(20), SN_LE16(0), 17, "CROMRegionBlock_t", 15, "CROMRegionBlock" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(20), 16, "CROMGridBounds_t" },
    { SN_LE32(0), 0x96, SN_LE16(8), SN_LE16(8), SN_LE32(16), SN_LE16(0), 13, "CBoundsRect_t", 12, "m_BoundsRect" },
    { SN_LE32(16), 0x94, SN_LE16(8), SN_LE16(15), SN_LE32(0), 8, "m_bEmpty" },
    { SN_LE32(20), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(20), SN_LE16(0), 16, "CROMGridBounds_t", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(20), SN_LE16(0), 16, "CROMGridBounds_t", 14, "CROMGridBounds" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(28), 14, "CInstanceHdr_t" },
    { SN_LE32(0), 0x94, SN_LE16(8), SN_LE16(12), SN_LE32(0), 6, "m_Type" },
    { SN_LE32(1), 0x94, SN_LE16(8), SN_LE16(2), SN_LE32(0), 8, "m_nModel" },
    { SN_LE32(2), 0x94, SN_LE16(8), SN_LE16(2), SN_LE32(0), 14, "m_nShadowModel" },
    { SN_LE32(3), 0x94, SN_LE16(8), SN_LE16(2), SN_LE32(0), 10, "m_nTexture" },
    { SN_LE32(4), 0x94, SN_LE16(8), SN_LE16(13), SN_LE32(0), 10, "m_nObjType" },
    { SN_LE32(6), 0x96, SN_LE16(8), SN_LE16(60), SN_LE32(2), SN_LE16(1), SN_LE32(2), 0, 7, "PADDING" },
    { SN_LE32(8), 0x96, SN_LE16(8), SN_LE16(8), SN_LE32(12), SN_LE16(0), 10, "CVector3_t", 6, "m_vPos" },
    { SN_LE32(20), 0x96, SN_LE16(8), SN_LE16(24), SN_LE32(32), SN_LE16(0), 13, "CGameRegion_t", 16, "m_pCurrentRegion" },
    { SN_LE32(24), 0x96, SN_LE16(8), SN_LE16(24), SN_LE32(392), SN_LE16(0), 15, "CIntelligence_t", 4, "m_pI" },
    { SN_LE32(28), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(28), SN_LE16(0), 14, "CInstanceHdr_t", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(28), SN_LE16(0), 14, "CInstanceHdr_t", 12, "CInstanceHdr" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(80), 18, "CAnimInstanceHdr_t" },
    { SN_LE32(0), 0x96, SN_LE16(8), SN_LE16(8), SN_LE32(28), SN_LE16(0), 14, "CInstanceHdr_t", 2, "ih" },
    { SN_LE32(28), 0x96, SN_LE16(8), SN_LE16(8), SN_LE32(12), SN_LE16(0), 10, "CVector3_t", 11, "m_vVelocity" },
    { SN_LE32(40), 0x96, SN_LE16(8), SN_LE16(8), SN_LE32(12), SN_LE16(0), 10, "CVector3_t", 10, "m_vCurrent" },
    { SN_LE32(52), 0x96, SN_LE16(8), SN_LE16(24), SN_LE32(28), SN_LE16(0), 14, "CInstanceHdr_t", 16, "m_pInstanceBelow" },
    { SN_LE32(56), 0x94, SN_LE16(8), SN_LE16(15), SN_LE32(0), 11, "m_CollFlags" },
    { SN_LE32(60), 0x94, SN_LE16(8), SN_LE16(5), SN_LE32(0), 16, "m_GroundMaterial" },
    { SN_LE32(64), 0x94, SN_LE16(8), SN_LE16(6), SN_LE32(0), 14, "m_GroundHeight" },
    { SN_LE32(68), 0x96, SN_LE16(8), SN_LE16(8), SN_LE32(12), SN_LE16(0), 10, "CVector3_t", 15, "m_vGroundNormal" },
    { SN_LE32(80), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(80), SN_LE16(0), 18, "CAnimInstanceHdr_t", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(80), SN_LE16(0), 18, "CAnimInstanceHdr_t", 16, "CAnimInstanceHdr" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(8), 6, "s_ISet" },
    { SN_LE32(0), 0x94, SN_LE16(8), SN_LE16(5), SN_LE32(0), 12, "m_BlockCount" },
    { SN_LE32(4), 0x96, SN_LE16(8), SN_LE16(53), SN_LE32(4), SN_LE16(1), SN_LE32(1), 0, 9, "m_Offsets" },
    { SN_LE32(8), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(8), SN_LE16(0), 6, "s_ISet", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(8), SN_LE16(0), 6, "s_ISet", 5, "CISet" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(12), 6, "s_USet" },
    { SN_LE32(0), 0x94, SN_LE16(8), SN_LE16(5), SN_LE32(0), 11, "m_BlockSize" },
    { SN_LE32(4), 0x94, SN_LE16(8), SN_LE16(5), SN_LE32(0), 12, "m_BlockCount" },
    { SN_LE32(8), 0x96, SN_LE16(8), SN_LE16(53), SN_LE32(4), SN_LE16(1), SN_LE32(1), 0, 7, "m_Array" },
    { SN_LE32(12), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(12), SN_LE16(0), 6, "s_USet", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(12), SN_LE16(0), 6, "s_USet", 5, "CUSet" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(24), 12, "CHeapBlock_t" },
    { SN_LE32(0), 0x96, SN_LE16(8), SN_LE16(24), SN_LE32(24), SN_LE16(0), 12, "CHeapBlock_t", 9, "pFreeLast" },
    { SN_LE32(4), 0x96, SN_LE16(8), SN_LE16(24), SN_LE32(24), SN_LE16(0), 12, "CHeapBlock_t", 9, "pFreeNext" },
    { SN_LE32(8), 0x96, SN_LE16(8), SN_LE16(24), SN_LE32(24), SN_LE16(0), 12, "CHeapBlock_t", 9, "pUsedLast" },
    { SN_LE32(12), 0x96, SN_LE16(8), SN_LE16(24), SN_LE32(24), SN_LE16(0), 12, "CHeapBlock_t", 9, "pUsedNext" },
    { SN_LE32(16), 0x94, SN_LE16(8), SN_LE16(15), SN_LE32(0), 4, "Used" },
    { SN_LE32(20), 0x94, SN_LE16(8), SN_LE16(15), SN_LE32(0), 4, "Free" },
    { SN_LE32(24), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(24), SN_LE16(0), 12, "CHeapBlock_t", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(24), SN_LE16(0), 12, "CHeapBlock_t", 10, "CHeapBlock" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(20), 7, "CHeap_t" },
    { SN_LE32(0), 0x94, SN_LE16(8), SN_LE16(15), SN_LE32(0), 8, "MemStart" },
    { SN_LE32(4), 0x94, SN_LE16(8), SN_LE16(15), SN_LE32(0), 6, "MemEnd" },
    { SN_LE32(8), 0x96, SN_LE16(8), SN_LE16(24), SN_LE32(24), SN_LE16(0), 12, "CHeapBlock_t", 9, "pFreeHead" },
    { SN_LE32(12), 0x96, SN_LE16(8), SN_LE16(24), SN_LE32(24), SN_LE16(0), 12, "CHeapBlock_t", 9, "pFreeTail" },
    { SN_LE32(16), 0x96, SN_LE16(8), SN_LE16(24), SN_LE32(24), SN_LE16(0), 12, "CHeapBlock_t", 9, "pUsedHead" },
    { SN_LE32(20), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(20), SN_LE16(0), 7, "CHeap_t", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(20), SN_LE16(0), 7, "CHeap_t", 5, "CHeap" },
    { SN_LE32(0), 0x94, SN_LE16(13), SN_LE16(145), SN_LE32(0), 13, "pfnTHREADMAIN" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(32), 14, "CLoaderEntry_t" },
    { SN_LE32(0), 0x94, SN_LE16(8), SN_LE16(17), SN_LE32(0), 8, "pAddress" },
    { SN_LE32(4), 0x94, SN_LE16(8), SN_LE16(17), SN_LE32(0), 5, "pDest" },
    { SN_LE32(8), 0x94, SN_LE16(8), SN_LE16(4), SN_LE32(0), 6, "Length" },
    { SN_LE32(12), 0x96, SN_LE16(8), SN_LE16(24), SN_LE32(24), SN_LE16(0), 13, "OSMesgQueue_s", 11, "pReplyQueue" },
    { SN_LE32(16), 0x94, SN_LE16(8), SN_LE16(17), SN_LE32(0), 13, "pReplyMessage" },
    { SN_LE32(20), 0x94, SN_LE16(8), SN_LE16(15), SN_LE32(0), 7, "dwFlags" },
    { SN_LE32(24), 0x96, SN_LE16(8), SN_LE16(24), SN_LE32(32), SN_LE16(0), 14, "CLoaderEntry_t", 5, "pLast" },
    { SN_LE32(28), 0x96, SN_LE16(8), SN_LE16(24), SN_LE32(32), SN_LE16(0), 14, "CLoaderEntry_t", 5, "pNext" },
    { SN_LE32(32), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(32), SN_LE16(0), 14, "CLoaderEntry_t", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(32), SN_LE16(0), 14, "CLoaderEntry_t", 12, "CLoaderEntry" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(20624), 9, "CLoader_t" },
    { SN_LE32(0), 0x96, SN_LE16(8), SN_LE16(8), SN_LE32(560), SN_LE16(0), 10, "OSThread_s", 6, "Thread" },
    { SN_LE32(560), 0x96, SN_LE16(8), SN_LE16(8), SN_LE32(24), SN_LE16(0), 13, "OSMesgQueue_s", 5, "Queue" },
    { SN_LE32(584), 0x96, SN_LE16(8), SN_LE16(113), SN_LE32(2048), SN_LE16(1), SN_LE32(512), 0, 4, "Msgs" },
    { SN_LE32(2632), 0x96, SN_LE16(8), SN_LE16(8), SN_LE32(24), SN_LE16(0), 13, "OSMesgQueue_s", 12, "PiReplyQueue" },
    { SN_LE32(2656), 0x94, SN_LE16(8), SN_LE16(17), SN_LE32(0), 10, "PiReplyMsg" },
    { SN_LE32(2664), 0x96, SN_LE16(8), SN_LE16(63), SN_LE32(1024), SN_LE16(1), SN_LE32(128), 0, 5, "Stack" },
    { SN_LE32(3688), 0x96, SN_LE16(8), SN_LE16(56), SN_LE32(16896), SN_LE16(1), SN_LE32(528), 14, "CLoaderEntry_t", 7, "Entries" },
    { SN_LE32(20584), 0x96, SN_LE16(8), SN_LE16(8), SN_LE32(20), SN_LE16(0), 7, "CList_t", 8, "FreeList" },
    { SN_LE32(20604), 0x96, SN_LE16(8), SN_LE16(8), SN_LE32(20), SN_LE16(0), 7, "CList_t", 8, "UsedList" },
    { SN_LE32(20624), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(20624), SN_LE16(0), 9, "CLoader_t", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(20624), SN_LE16(0), 9, "CLoader_t", 7, "CLoader" },
    { SN_LE32(0), 0x94, SN_LE16(13), SN_LE16(145), SN_LE32(0), 21, "pfnDECOMPRESSCALLBACK" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(40), 11, "CMemEntry_t" },
    { SN_LE32(0), 0x94, SN_LE16(8), SN_LE16(17), SN_LE32(0), 5, "pData" },
    { SN_LE32(4), 0x94, SN_LE16(8), SN_LE16(4), SN_LE32(0), 4, "Size" },
    { SN_LE32(8), 0x94, SN_LE16(8), SN_LE16(4), SN_LE32(0), 6, "nLocks" },
    { SN_LE32(12), 0x94, SN_LE16(8), SN_LE16(15), SN_LE32(0), 7, "dwFlags" },
    { SN_LE32(16), 0x94, SN_LE16(8), SN_LE16(15), SN_LE32(0), 3, "Age" },
    { SN_LE32(20), 0x96, SN_LE16(8), SN_LE16(24), SN_LE32(0), SN_LE16(0), 13, "CCacheNtry2_t", 11, "pCacheEntry" },
    { SN_LE32(24), 0x96, SN_LE16(8), SN_LE16(24), SN_LE32(40), SN_LE16(0), 11, "CMemEntry_t", 5, "pLast" },
    { SN_LE32(28), 0x96, SN_LE16(8), SN_LE16(24), SN_LE32(40), SN_LE16(0), 11, "CMemEntry_t", 5, "pNext" },
    { SN_LE32(32), 0x96, SN_LE16(8), SN_LE16(24), SN_LE32(40), SN_LE16(0), 11, "CMemEntry_t", 8, "pPosLast" },
    { SN_LE32(36), 0x96, SN_LE16(8), SN_LE16(24), SN_LE32(40), SN_LE16(0), 11, "CMemEntry_t", 8, "pPosNext" },
    { SN_LE32(40), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(40), SN_LE16(0), 11, "CMemEntry_t", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(40), SN_LE16(0), 11, "CMemEntry_t", 9, "CMemEntry" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(44), 13, "CCacheNtry2_t" },
    { SN_LE32(0), 0x96, SN_LE16(8), SN_LE16(24), SN_LE32(40), SN_LE16(0), 11, "CMemEntry_t", 9, "pMemEntry" },
    { SN_LE32(4), 0x96, SN_LE16(8), SN_LE16(24), SN_LE32(40), SN_LE16(0), 11, "CMemEntry_t", 19, "pReferencedMemEntry" },
    { SN_LE32(8), 0x94, SN_LE16(8), SN_LE16(17), SN_LE32(0), 10, "pRequestID" },
    { SN_LE32(12), 0x94, SN_LE16(8), SN_LE16(4), SN_LE32(0), 13, "RequestLength" },
    { SN_LE32(16), 0x94, SN_LE16(8), SN_LE16(15), SN_LE32(0), 7, "dwFlags" },
    { SN_LE32(20), 0x94, SN_LE16(8), SN_LE16(145), SN_LE32(0), 18, "DecompressCallback" },
    { SN_LE32(24), 0x94, SN_LE16(8), SN_LE16(17), SN_LE32(0), 9, "pNotifyID" },
    { SN_LE32(28), 0x94, SN_LE16(8), SN_LE16(15), SN_LE32(0), 10, "dwMemFlags" },
    { SN_LE32(32), 0x96, SN_LE16(8), SN_LE16(24), SN_LE32(24), SN_LE16(0), 13, "OSMesgQueue_s", 21, "pDecompressReplyQueue" },
    { SN_LE32(36), 0x96, SN_LE16(8), SN_LE16(24), SN_LE32(44), SN_LE16(0), 13, "CCacheNtry2_t", 5, "pNext" },
    { SN_LE32(40), 0x96, SN_LE16(8), SN_LE16(24), SN_LE32(44), SN_LE16(0), 13, "CCacheNtry2_t", 5, "pLast" },
    { SN_LE32(44), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(44), SN_LE16(0), 13, "CCacheNtry2_t", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(44), SN_LE16(0), 13, "CCacheNtry2_t", 11, "CCacheNtry2" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(5200), 15, "CDecompressor_t" },
    { SN_LE32(0), 0x96, SN_LE16(8), SN_LE16(8), SN_LE32(560), SN_LE16(0), 10, "OSThread_s", 6, "Thread" },
    { SN_LE32(560), 0x96, SN_LE16(8), SN_LE16(8), SN_LE32(24), SN_LE16(0), 13, "OSMesgQueue_s", 5, "Queue" },
    { SN_LE32(584), 0x96, SN_LE16(8), SN_LE16(113), SN_LE32(512), SN_LE16(1), SN_LE32(128), 0, 4, "Msgs" },
    { SN_LE32(1096), 0x96, SN_LE16(8), SN_LE16(63), SN_LE32(4096), SN_LE16(1), SN_LE32(512), 0, 5, "Stack" },
    { SN_LE32(5192), 0x94, SN_LE16(8), SN_LE16(15), SN_LE32(0), 14, "LastDecompress" },
    { SN_LE32(5200), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(5200), SN_LE16(0), 15, "CDecompressor_t", 4, ".eos" },
    { 0x00, 0x00, 0x00, 0x00, 0x96, 0x0D, 0x00, 0x08, 0x00, 0x50, 0x14, 0x00, 0x00, 0x00, 0x00, 0x0F, 0x43, 0x44, 0x65, 0x63, 0x6F, 0x6D },
};
typedef char g_sn64IntelligenceTypeRecordsSizeCheck[(sizeof(g_sn64IntelligenceTypeRecords) == 20461) ? 1 : -1];
#endif
