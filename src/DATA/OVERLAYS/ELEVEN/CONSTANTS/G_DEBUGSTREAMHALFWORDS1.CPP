#include "DATA_OVERLAY_SN_RECORDS.H"


#if defined(VERSION_US_REV1)
struct {
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[19]; } SFX_CHICKEN_IDLEequ_0;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[16]; } SFX_CHICKEN_IDLE_1;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[19]; u8 nameLength; char name[4]; } eos_2;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[21]; } SFX_CHICKEN_FLINCHequ_3;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[18]; } SFX_CHICKEN_FLINCH_4;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[21]; u8 nameLength; char name[4]; } eos_5;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[21]; } SFX_CHICKEN_EFFORTequ_6;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[18]; } SFX_CHICKEN_EFFORT_7;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[21]; u8 nameLength; char name[4]; } eos_8;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[20]; } SFX_CHICKEN_DEATHequ_9;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[17]; } SFX_CHICKEN_DEATH_10;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[20]; u8 nameLength; char name[4]; } eos_11;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[26]; } SFX_CHICKEN_TRANSFORMEDequ_12;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[23]; } SFX_CHICKEN_TRANSFORMED_13;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[26]; u8 nameLength; char name[4]; } eos_14;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[33]; } SFX_CHICKEN_TRANSFORMED_FLINCHequ_15;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[30]; } SFX_CHICKEN_TRANSFORMED_FLINCH_16;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[33]; u8 nameLength; char name[4]; } eos_17;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[33]; } SFX_CHICKEN_TRANSFORMED_ATTACKequ_18;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[30]; } SFX_CHICKEN_TRANSFORMED_ATTACK_19;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[33]; u8 nameLength; char name[4]; } eos_20;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[31]; } SFX_CHICKEN_TRANSFORMED_IDLEequ_21;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[28]; } SFX_CHICKEN_TRANSFORMED_IDLE_22;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[31]; u8 nameLength; char name[4]; } eos_23;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[17]; } SFX_COMPY_IDLEequ_24;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[14]; } SFX_COMPY_IDLE_25;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[17]; u8 nameLength; char name[4]; } eos_26;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[19]; } SFX_COMPY_FLINCHequ_27;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[16]; } SFX_COMPY_FLINCH_28;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[19]; u8 nameLength; char name[4]; } eos_29;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[19]; } SFX_COMPY_EFFORTequ_30;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[16]; } SFX_COMPY_EFFORT_31;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[19]; u8 nameLength; char name[4]; } eos_32;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[18]; } SFX_COMPY_DEATHequ_33;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[15]; } SFX_COMPY_DEATH_34;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[18]; u8 nameLength; char name[4]; } eos_35;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[24]; } SFX_COMPY_TRANSFORMEDequ_36;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[21]; } SFX_COMPY_TRANSFORMED_37;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[24]; u8 nameLength; char name[4]; } eos_38;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[31]; } SFX_COMPY_TRANSFORMED_FLINCHequ_39;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[28]; } SFX_COMPY_TRANSFORMED_FLINCH_40;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[31]; u8 nameLength; char name[4]; } eos_41;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[31]; } SFX_COMPY_TRANSFORMED_ATTACKequ_42;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[28]; } SFX_COMPY_TRANSFORMED_ATTACK_43;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[31]; u8 nameLength; char name[4]; } eos_44;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[29]; } SFX_COMPY_TRANSFORMED_IDLEequ_45;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[26]; } SFX_COMPY_TRANSFORMED_IDLE_46;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[29]; u8 nameLength; char name[4]; } eos_47;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[35]; } SFX_BOSS_1_EXTENDED_FIRE_WAR_CRYequ_48;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[32]; } SFX_BOSS_1_EXTENDED_FIRE_WAR_CRY_49;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[35]; u8 nameLength; char name[4]; } eos_50;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[20]; } SFX_BOSS_1_FLINCHequ_51;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[17]; } SFX_BOSS_1_FLINCH_52;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[20]; u8 nameLength; char name[4]; } eos_53;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[20]; } SFX_BOSS_1_EFFORTequ_54;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[17]; } SFX_BOSS_1_EFFORT_55;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[20]; u8 nameLength; char name[4]; } eos_56;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[19]; } SFX_BOSS_1_DEATHequ_57;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[16]; } SFX_BOSS_1_DEATH_58;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[19]; u8 nameLength; char name[4]; } eos_59;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[20]; } SFX_BOSS_1_SCREAMequ_60;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[17]; } SFX_BOSS_1_SCREAM_61;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[20]; u8 nameLength; char name[4]; } eos_62;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[18]; } SFX_BOSS_1_FALLequ_63;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[15]; } SFX_BOSS_1_FALL_64;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[18]; u8 nameLength; char name[4]; } eos_65;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[21]; } SFX_BOSS_1_VICTORYequ_66;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[18]; } SFX_BOSS_1_VICTORY_67;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[21]; u8 nameLength; char name[4]; } eos_68;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[25]; } SFX_BOSS_1_STICKY_BOMBequ_69;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[22]; } SFX_BOSS_1_STICKY_BOMB_70;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[25]; u8 nameLength; char name[4]; } eos_71;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[19]; } SFX_BOSS_1_LAUGHequ_72;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[16]; } SFX_BOSS_1_LAUGH_73;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[19]; u8 nameLength; char name[4]; } eos_74;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[31]; } SFX_BOSS_1_RADIOACTIVE_PANICequ_75;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[28]; } SFX_BOSS_1_RADIOACTIVE_PANIC_76;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[31]; u8 nameLength; char name[4]; } eos_77;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[19]; } SFX_BOSS_1_TAUNTequ_78;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[16]; } SFX_BOSS_1_TAUNT_79;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[19]; u8 nameLength; char name[4]; } eos_80;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[26]; } SFX_BOSS_1_CAPTURE_FLAGequ_81;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[23]; } SFX_BOSS_1_CAPTURE_FLAG_82;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[26]; u8 nameLength; char name[4]; } eos_83;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[34]; } SFX_BOSS_1_DAMAGED_HOLDING_FLAGequ_84;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[31]; } SFX_BOSS_1_DAMAGED_HOLDING_FLAG_85;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[34]; u8 nameLength; char name[4]; } eos_86;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[26]; } SFX_BOSS_1_PLANTED_FLAGequ_87;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[23]; } SFX_BOSS_1_PLANTED_FLAG_88;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[26]; u8 nameLength; char name[4]; } eos_89;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[24]; } SFX_BOSS_1_SEE_PLAYERequ_90;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[21]; } SFX_BOSS_1_SEE_PLAYER_91;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[24]; u8 nameLength; char name[4]; } eos_92;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[28]; } SFX_BOSS_1_HEAR_SOMETHINGequ_93;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[25]; } SFX_BOSS_1_HEAR_SOMETHING_94;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[28]; u8 nameLength; char name[4]; } eos_95;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[29]; } SFX_BOSS_1_SMELL_SOMETHINGequ_96;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[26]; } SFX_BOSS_1_SMELL_SOMETHING_97;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[29]; u8 nameLength; char name[4]; } eos_98;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[27]; } SFX_BOSS_1_KILL_FRIENDLYequ_99;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[24]; } SFX_BOSS_1_KILL_FRIENDLY_100;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[27]; u8 nameLength; char name[4]; } eos_101;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[35]; } SFX_BOSS_2_EXTENDED_FIRE_WAR_CRYequ_102;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[32]; } SFX_BOSS_2_EXTENDED_FIRE_WAR_CRY_103;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[35]; u8 nameLength; char name[4]; } eos_104;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[20]; } SFX_BOSS_2_FLINCHequ_105;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[17]; } SFX_BOSS_2_FLINCH_106;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[20]; u8 nameLength; char name[4]; } eos_107;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[20]; } SFX_BOSS_2_EFFORTequ_108;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[17]; } SFX_BOSS_2_EFFORT_109;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[20]; u8 nameLength; char name[4]; } eos_110;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[19]; } SFX_BOSS_2_DEATHequ_111;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[16]; } SFX_BOSS_2_DEATH_112;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[19]; u8 nameLength; char name[4]; } eos_113;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[20]; } SFX_BOSS_2_SCREAMequ_114;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[17]; } SFX_BOSS_2_SCREAM_115;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[20]; u8 nameLength; char name[4]; } eos_116;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[18]; } SFX_BOSS_2_FALLequ_117;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[15]; } SFX_BOSS_2_FALL_118;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[18]; u8 nameLength; char name[4]; } eos_119;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[21]; } SFX_BOSS_2_VICTORYequ_120;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[18]; } SFX_BOSS_2_VICTORY_121;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[21]; u8 nameLength; char name[4]; } eos_122;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[25]; } SFX_BOSS_2_STICKY_BOMBequ_123;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[22]; } SFX_BOSS_2_STICKY_BOMB_124;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[25]; u8 nameLength; char name[4]; } eos_125;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[19]; } SFX_BOSS_2_LAUGHequ_126;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[16]; } SFX_BOSS_2_LAUGH_127;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[19]; u8 nameLength; char name[4]; } eos_128;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[31]; } SFX_BOSS_2_RADIOACTIVE_PANICequ_129;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[28]; } SFX_BOSS_2_RADIOACTIVE_PANIC_130;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[31]; u8 nameLength; char name[4]; } eos_131;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[19]; } SFX_BOSS_2_TAUNTequ_132;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[16]; } SFX_BOSS_2_TAUNT_133;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[19]; u8 nameLength; char name[4]; } eos_134;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[26]; } SFX_BOSS_2_CAPTURE_FLAGequ_135;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[23]; } SFX_BOSS_2_CAPTURE_FLAG_136;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[26]; u8 nameLength; char name[4]; } eos_137;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[34]; } SFX_BOSS_2_DAMAGED_HOLDING_FLAGequ_138;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[31]; } SFX_BOSS_2_DAMAGED_HOLDING_FLAG_139;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[34]; u8 nameLength; char name[4]; } eos_140;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[26]; } SFX_BOSS_2_PLANTED_FLAGequ_141;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[23]; } SFX_BOSS_2_PLANTED_FLAG_142;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[26]; u8 nameLength; char name[4]; } eos_143;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[24]; } SFX_BOSS_2_SEE_PLAYERequ_144;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[21]; } SFX_BOSS_2_SEE_PLAYER_145;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[24]; u8 nameLength; char name[4]; } eos_146;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[28]; } SFX_BOSS_2_HEAR_SOMETHINGequ_147;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[25]; } SFX_BOSS_2_HEAR_SOMETHING_148;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[28]; u8 nameLength; char name[4]; } eos_149;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[29]; } SFX_BOSS_2_SMELL_SOMETHINGequ_150;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[26]; } SFX_BOSS_2_SMELL_SOMETHING_151;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[29]; u8 nameLength; char name[4]; } eos_152;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[27]; } SFX_BOSS_2_KILL_FRIENDLYequ_153;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[24]; } SFX_BOSS_2_KILL_FRIENDLY_154;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[27]; u8 nameLength; char name[4]; } eos_155;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[35]; } SFX_BOSS_3_EXTENDED_FIRE_WAR_CRYequ_156;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[32]; } SFX_BOSS_3_EXTENDED_FIRE_WAR_CRY_157;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[35]; u8 nameLength; char name[4]; } eos_158;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[20]; } SFX_BOSS_3_FLINCHequ_159;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[17]; } SFX_BOSS_3_FLINCH_160;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[20]; u8 nameLength; char name[4]; } eos_161;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[20]; } SFX_BOSS_3_EFFORTequ_162;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[17]; } SFX_BOSS_3_EFFORT_163;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[20]; u8 nameLength; char name[4]; } eos_164;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[19]; } SFX_BOSS_3_DEATHequ_165;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[16]; } SFX_BOSS_3_DEATH_166;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[19]; u8 nameLength; char name[4]; } eos_167;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[20]; } SFX_BOSS_3_SCREAMequ_168;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[17]; } SFX_BOSS_3_SCREAM_169;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[20]; u8 nameLength; char name[4]; } eos_170;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[18]; } SFX_BOSS_3_FALLequ_171;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[15]; } SFX_BOSS_3_FALL_172;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[18]; u8 nameLength; char name[4]; } eos_173;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[21]; } SFX_BOSS_3_VICTORYequ_174;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[18]; } SFX_BOSS_3_VICTORY_175;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[21]; u8 nameLength; char name[4]; } eos_176;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[25]; } SFX_BOSS_3_STICKY_BOMBequ_177;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[22]; } SFX_BOSS_3_STICKY_BOMB_178;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[25]; u8 nameLength; char name[4]; } eos_179;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[19]; } SFX_BOSS_3_LAUGHequ_180;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[16]; } SFX_BOSS_3_LAUGH_181;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[19]; u8 nameLength; char name[4]; } eos_182;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[31]; } SFX_BOSS_3_RADIOACTIVE_PANICequ_183;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[28]; } SFX_BOSS_3_RADIOACTIVE_PANIC_184;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[31]; u8 nameLength; char name[4]; } eos_185;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[19]; } SFX_BOSS_3_TAUNTequ_186;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[16]; } SFX_BOSS_3_TAUNT_187;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[19]; u8 nameLength; char name[4]; } eos_188;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[26]; } SFX_BOSS_3_CAPTURE_FLAGequ_189;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[23]; } SFX_BOSS_3_CAPTURE_FLAG_190;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[26]; u8 nameLength; char name[4]; } eos_191;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[34]; } SFX_BOSS_3_DAMAGED_HOLDING_FLAGequ_192;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[31]; } SFX_BOSS_3_DAMAGED_HOLDING_FLAG_193;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[34]; u8 nameLength; char name[4]; } eos_194;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[26]; } SFX_BOSS_3_PLANTED_FLAGequ_195;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[23]; } SFX_BOSS_3_PLANTED_FLAG_196;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[26]; u8 nameLength; char name[4]; } eos_197;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[24]; } SFX_BOSS_3_SEE_PLAYERequ_198;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[21]; } SFX_BOSS_3_SEE_PLAYER_199;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[24]; u8 nameLength; char name[4]; } eos_200;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[28]; } SFX_BOSS_3_HEAR_SOMETHINGequ_201;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[25]; } SFX_BOSS_3_HEAR_SOMETHING_202;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[28]; u8 nameLength; char name[4]; } eos_203;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[29]; } SFX_BOSS_3_SMELL_SOMETHINGequ_204;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[26]; } SFX_BOSS_3_SMELL_SOMETHING_205;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[29]; u8 nameLength; char name[4]; } eos_206;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[27]; } SFX_BOSS_3_KILL_FRIENDLYequ_207;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[24]; } SFX_BOSS_3_KILL_FRIENDLY_208;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[27]; u8 nameLength; char name[4]; } eos_209;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[35]; } SFX_BOSS_4_EXTENDED_FIRE_WAR_CRYequ_210;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[32]; } SFX_BOSS_4_EXTENDED_FIRE_WAR_CRY_211;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[35]; u8 nameLength; char name[4]; } eos_212;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[20]; } SFX_BOSS_4_FLINCHequ_213;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[17]; } SFX_BOSS_4_FLINCH_214;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[20]; u8 nameLength; char name[4]; } eos_215;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[20]; } SFX_BOSS_4_EFFORTequ_216;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[17]; } SFX_BOSS_4_EFFORT_217;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[20]; u8 nameLength; char name[4]; } eos_218;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[19]; } SFX_BOSS_4_DEATHequ_219;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[16]; } SFX_BOSS_4_DEATH_220;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[19]; u8 nameLength; char name[4]; } eos_221;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[20]; } SFX_BOSS_4_SCREAMequ_222;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[17]; } SFX_BOSS_4_SCREAM_223;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[20]; u8 nameLength; char name[4]; } eos_224;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[18]; } SFX_BOSS_4_FALLequ_225;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[15]; } SFX_BOSS_4_FALL_226;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[18]; u8 nameLength; char name[4]; } eos_227;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[21]; } SFX_BOSS_4_VICTORYequ_228;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[18]; } SFX_BOSS_4_VICTORY_229;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[21]; u8 nameLength; char name[4]; } eos_230;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[25]; } SFX_BOSS_4_STICKY_BOMBequ_231;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[22]; } SFX_BOSS_4_STICKY_BOMB_232;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[25]; u8 nameLength; char name[4]; } eos_233;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[19]; } SFX_BOSS_4_LAUGHequ_234;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[16]; } SFX_BOSS_4_LAUGH_235;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[19]; u8 nameLength; char name[4]; } eos_236;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[31]; } SFX_BOSS_4_RADIOACTIVE_PANICequ_237;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[28]; } SFX_BOSS_4_RADIOACTIVE_PANIC_238;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[31]; u8 nameLength; char name[4]; } eos_239;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[19]; } SFX_BOSS_4_TAUNTequ_240;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[16]; } SFX_BOSS_4_TAUNT_241;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[19]; u8 nameLength; char name[4]; } eos_242;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[26]; } SFX_BOSS_4_CAPTURE_FLAGequ_243;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[23]; } SFX_BOSS_4_CAPTURE_FLAG_244;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[26]; u8 nameLength; char name[4]; } eos_245;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[34]; } SFX_BOSS_4_DAMAGED_HOLDING_FLAGequ_246;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[31]; } SFX_BOSS_4_DAMAGED_HOLDING_FLAG_247;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[34]; u8 nameLength; char name[4]; } eos_248;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[26]; } SFX_BOSS_4_PLANTED_FLAGequ_249;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[23]; } SFX_BOSS_4_PLANTED_FLAG_250;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[26]; u8 nameLength; char name[4]; } eos_251;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[24]; } SFX_BOSS_4_SEE_PLAYERequ_252;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[21]; } SFX_BOSS_4_SEE_PLAYER_253;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[24]; u8 nameLength; char name[4]; } eos_254;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[28]; } SFX_BOSS_4_HEAR_SOMETHINGequ_255;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[25]; } SFX_BOSS_4_HEAR_SOMETHING_256;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[28]; u8 nameLength; char name[4]; } eos_257;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[29]; } SFX_BOSS_4_SMELL_SOMETHINGequ_258;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[26]; } SFX_BOSS_4_SMELL_SOMETHING_259;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[29]; u8 nameLength; char name[4]; } eos_260;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[27]; } SFX_BOSS_4_KILL_FRIENDLYequ_261;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[24]; } SFX_BOSS_4_KILL_FRIENDLY_262;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[27]; u8 nameLength; char name[4]; } eos_263;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[20]; } SFX_BOSS_4_SUMMONequ_264;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[17]; } SFX_BOSS_4_SUMMON_265;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[20]; u8 nameLength; char name[4]; } eos_266;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[13]; } MUSIC_NONEequ_267;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[10]; } MUSIC_NONE_268;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[13]; u8 nameLength; char name[4]; } eos_269;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[15]; } MUSIC_LEVEL1equ_270;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[12]; } MUSIC_LEVEL1_271;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[15]; u8 nameLength; char name[4]; } eos_272;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[15]; } MUSIC_LEVEL2equ_273;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[12]; } MUSIC_LEVEL2_274;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[15]; u8 nameLength; char name[4]; } eos_275;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[15]; } MUSIC_LEVEL3equ_276;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[12]; } MUSIC_LEVEL3_277;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[15]; u8 nameLength; char name[4]; } eos_278;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[15]; } MUSIC_LEVEL4equ_279;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[12]; } MUSIC_LEVEL4_280;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[15]; u8 nameLength; char name[4]; } eos_281;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[15]; } MUSIC_LEVEL5equ_282;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[12]; } MUSIC_LEVEL5_283;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[15]; u8 nameLength; char name[4]; } eos_284;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[15]; } MUSIC_LEVEL6equ_285;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[12]; } MUSIC_LEVEL6_286;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[15]; u8 nameLength; char name[4]; } eos_287;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[14]; } MUSIC_BOSS1equ_288;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[11]; } MUSIC_BOSS1_289;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[14]; u8 nameLength; char name[4]; } eos_290;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[14]; } MUSIC_BOSS2equ_291;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[11]; } MUSIC_BOSS2_292;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[14]; u8 nameLength; char name[4]; } eos_293;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[14]; } MUSIC_BOSS3equ_294;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[11]; } MUSIC_BOSS3_295;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[14]; u8 nameLength; char name[4]; } eos_296;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[14]; } MUSIC_BOSS4equ_297;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[11]; } MUSIC_BOSS4_298;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[14]; u8 nameLength; char name[4]; } eos_299;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[20]; } MUSIC_DEATHMATCH1equ_300;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[17]; } MUSIC_DEATHMATCH1_301;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[20]; u8 nameLength; char name[4]; } eos_302;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[20]; } MUSIC_DEATHMATCH2equ_303;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[17]; } MUSIC_DEATHMATCH2_304;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[20]; u8 nameLength; char name[4]; } eos_305;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[20]; } MUSIC_DEATHMATCH3equ_306;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[17]; } MUSIC_DEATHMATCH3_307;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[20]; u8 nameLength; char name[4]; } eos_308;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[20]; } MUSIC_DEATHMATCH4equ_309;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[17]; } MUSIC_DEATHMATCH4_310;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[20]; u8 nameLength; char name[4]; } eos_311;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[22]; } MUSIC_LEVEL_INTRO_1equ_312;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[19]; } MUSIC_LEVEL_INTRO_1_313;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[22]; u8 nameLength; char name[4]; } eos_314;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[22]; } MUSIC_LEVEL_INTRO_2equ_315;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[19]; } MUSIC_LEVEL_INTRO_2_316;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[22]; u8 nameLength; char name[4]; } eos_317;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[22]; } MUSIC_LEVEL_INTRO_3equ_318;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[19]; } MUSIC_LEVEL_INTRO_3_319;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[22]; u8 nameLength; char name[4]; } eos_320;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[22]; } MUSIC_LEVEL_INTRO_4equ_321;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[19]; } MUSIC_LEVEL_INTRO_4_322;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[22]; u8 nameLength; char name[4]; } eos_323;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[22]; } MUSIC_LEVEL_INTRO_5equ_324;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[19]; } MUSIC_LEVEL_INTRO_5_325;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[22]; u8 nameLength; char name[4]; } eos_326;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[22]; } MUSIC_LEVEL_INTRO_6equ_327;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[19]; } MUSIC_LEVEL_INTRO_6_328;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[22]; u8 nameLength; char name[4]; } eos_329;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[21]; } MUSIC_DEFEND_TOTEMequ_330;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[18]; } MUSIC_DEFEND_TOTEM_331;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[21]; u8 nameLength; char name[4]; } eos_332;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[14]; } MUSIC_INTROequ_333;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[11]; } MUSIC_INTRO_334;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[14]; u8 nameLength; char name[4]; } eos_335;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[23]; } MUSIC_PLAYER_VICTORYequ_336;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[20]; } MUSIC_PLAYER_VICTORY_337;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[23]; u8 nameLength; char name[4]; } eos_338;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[24]; } MUSIC_BLOODLUST_INTROequ_339;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[21]; } MUSIC_BLOODLUST_INTRO_340;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[24]; u8 nameLength; char name[4]; } eos_341;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[24]; } MUSIC_FRONT_END_THEMEequ_342;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[21]; } MUSIC_FRONT_END_THEME_343;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[24]; u8 nameLength; char name[4]; } eos_344;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[22]; } MUSIC_MEDALS_SCREENequ_345;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[19]; } MUSIC_MEDALS_SCREEN_346;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[22]; u8 nameLength; char name[4]; } eos_347;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[21]; } MUSIC_MISSION_TREEequ_348;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[18]; } MUSIC_MISSION_TREE_349;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[21]; u8 nameLength; char name[4]; } eos_350;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[28]; } MUSIC_CHARACTER_SELECTIONequ_351;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[25]; } MUSIC_CHARACTER_SELECTION_352;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[28]; u8 nameLength; char name[4]; } eos_353;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[30]; } MUSIC_DEATHMATCH_GAMEPLAY_1equ_354;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[27]; } MUSIC_DEATHMATCH_GAMEPLAY_1_355;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[30]; u8 nameLength; char name[4]; } eos_356;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[30]; } MUSIC_DEATHMATCH_GAMEPLAY_2equ_357;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[27]; } MUSIC_DEATHMATCH_GAMEPLAY_2_358;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[30]; u8 nameLength; char name[4]; } eos_359;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[30]; } MUSIC_DEATHMATCH_GAMEPLAY_3equ_360;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[27]; } MUSIC_DEATHMATCH_GAMEPLAY_3_361;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[30]; u8 nameLength; char name[4]; } eos_362;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[30]; } MUSIC_DEATHMATCH_GAMEPLAY_4equ_363;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[27]; } MUSIC_DEATHMATCH_GAMEPLAY_4_364;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[30]; u8 nameLength; char name[4]; } eos_365;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[18]; } MUSIC_GAME_OVERequ_366;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[15]; } MUSIC_GAME_OVER_367;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[18]; u8 nameLength; char name[4]; } eos_368;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[27]; } MUSIC_MONKEY_RETALIATIONequ_369;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[24]; } MUSIC_MONKEY_RETALIATION_370;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[27]; u8 nameLength; char name[4]; } eos_371;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[19]; } MUSIC_MENU_PAUSEequ_372;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[16]; } MUSIC_MENU_PAUSE_373;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[19]; u8 nameLength; char name[4]; } eos_374;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[11]; } RAX_NONEequ_375;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[8]; } RAX_NONE_376;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[11]; u8 nameLength; char name[4]; } eos_377;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[19]; } RAX_INTRO_LINE_1equ_378;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[16]; } RAX_INTRO_LINE_1_379;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[19]; u8 nameLength; char name[4]; } eos_380;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[19]; } RAX_INTRO_LINE_2equ_381;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[16]; } RAX_INTRO_LINE_2_382;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[19]; u8 nameLength; char name[4]; } eos_383;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[19]; } RAX_INTRO_LINE_3equ_384;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[16]; } RAX_INTRO_LINE_3_385;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[19]; u8 nameLength; char name[4]; } eos_386;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[19]; } RAX_INTRO_LINE_4equ_387;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[16]; } RAX_INTRO_LINE_4_388;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[19]; u8 nameLength; char name[4]; } eos_389;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[20]; } RAX_VICTORY_TUROKequ_390;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[17]; } RAX_VICTORY_TUROK_391;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[20]; u8 nameLength; char name[4]; } eos_392;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[19]; } RAX_VICTORY_ADONequ_393;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[16]; } RAX_VICTORY_ADON_394;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[19]; u8 nameLength; char name[4]; } eos_395;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[21]; } RAX_VICTORY_RAPTORequ_396;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[18]; } RAX_VICTORY_RAPTOR_397;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[21]; u8 nameLength; char name[4]; } eos_398;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[23]; } RAX_VICTORY_FIREBORNequ_399;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[20]; } RAX_VICTORY_FIREBORN_400;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[23]; u8 nameLength; char name[4]; } eos_401;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[25]; } RAX_VICTORY_JUGGERNAUTequ_402;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[22]; } RAX_VICTORY_JUGGERNAUT_403;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[25]; u8 nameLength; char name[4]; } eos_404;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[26]; } RAX_VICTORY_ELITE_GUARDequ_405;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[23]; } RAX_VICTORY_ELITE_GUARD_406;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[26]; u8 nameLength; char name[4]; } eos_407;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[26]; } RAX_VICTORY_DEATH_GUARDequ_408;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[23]; } RAX_VICTORY_DEATH_GUARD_409;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[26]; u8 nameLength; char name[4]; } eos_410;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[25]; } RAX_VICTORY_CAMPAINGERequ_411;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[22]; } RAX_VICTORY_CAMPAINGER_412;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[25]; u8 nameLength; char name[4]; } eos_413;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[24]; } RAX_VICTORY_LORD_DEADequ_414;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[21]; } RAX_VICTORY_LORD_DEAD_415;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[24]; u8 nameLength; char name[4]; } eos_416;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[19]; } RAX_VICTORY_MITEequ_417;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[16]; } RAX_VICTORY_MITE_418;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[19]; u8 nameLength; char name[4]; } eos_419;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[20]; } RAX_VICTORY_DRONEequ_420;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[17]; } RAX_VICTORY_DRONE_421;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[20]; u8 nameLength; char name[4]; } eos_422;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[22]; } RAX_VICTORY_SOLDIERequ_423;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[19]; } RAX_VICTORY_SOLDIER_424;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[22]; u8 nameLength; char name[4]; } eos_425;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[23]; } RAX_VICTORY_GUARDIANequ_426;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[20]; } RAX_VICTORY_GUARDIAN_427;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[23]; u8 nameLength; char name[4]; } eos_428;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[23]; } RAX_VICTORY_BASTILLEequ_429;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[20]; } RAX_VICTORY_BASTILLE_430;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[23]; u8 nameLength; char name[4]; } eos_431;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[20]; } RAX_VICTORY_SEERAequ_432;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[17]; } RAX_VICTORY_SEERA_433;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[20]; u8 nameLength; char name[4]; } eos_434;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[23]; } RAX_VICTORY_SYMBIONTequ_435;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[20]; } RAX_VICTORY_SYMBIONT_436;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[23]; u8 nameLength; char name[4]; } eos_437;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[22]; } RAX_VICTORY_TAL_SETequ_438;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[19]; } RAX_VICTORY_TAL_SET_439;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[22]; u8 nameLength; char name[4]; } eos_440;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[19]; } RAX_PU_SLOW_TIMEequ_441;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[16]; } RAX_PU_SLOW_TIME_442;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[19]; u8 nameLength; char name[4]; } eos_443;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[22]; } RAX_PU_REGENERATIONequ_444;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[19]; } RAX_PU_REGENERATION_445;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[22]; u8 nameLength; char name[4]; } eos_446;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[23]; } RAX_PU_FORCE_EMPATHYequ_447;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[20]; } RAX_PU_FORCE_EMPATHY_448;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[23]; u8 nameLength; char name[4]; } eos_449;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[19]; } RAX_PU_VAMPIRISMequ_450;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[16]; } RAX_PU_VAMPIRISM_451;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[19]; u8 nameLength; char name[4]; } eos_452;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[18]; } RAX_PU_TELEPORTequ_453;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[15]; } RAX_PU_TELEPORT_454;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[18]; u8 nameLength; char name[4]; } eos_455;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[21]; } RAX_PU_DARK_SHIELDequ_456;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[18]; } RAX_PU_DARK_SHIELD_457;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[21]; u8 nameLength; char name[4]; } eos_458;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[20]; } RAX_PU_PROTECTIONequ_459;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[17]; } RAX_PU_PROTECTION_460;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[20]; u8 nameLength; char name[4]; } eos_461;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[17]; } RAX_PU_PETRIFYequ_462;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[14]; } RAX_PU_PETRIFY_463;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[17]; u8 nameLength; char name[4]; } eos_464;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[22]; } RAX_PU_INVISIBILITYequ_465;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[19]; } RAX_PU_INVISIBILITY_466;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[22]; u8 nameLength; char name[4]; } eos_467;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[15]; } RAX_PU_SPEEDequ_468;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[12]; } RAX_PU_SPEED_469;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[15]; u8 nameLength; char name[4]; } eos_470;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[20]; } RAX_PU_STONE_SKINequ_471;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[17]; } RAX_PU_STONE_SKIN_472;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[20]; u8 nameLength; char name[4]; } eos_473;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[21]; } RAX_PU_BATTLE_RAGEequ_474;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[18]; } RAX_PU_BATTLE_RAGE_475;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[21]; u8 nameLength; char name[4]; } eos_476;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[13]; } TurretActions_477;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[18]; } TURRET_PING_ACTION_478;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[18]; } TURRET_PONG_ACTION_479;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[14]; } TURRET_ACTIONS_480;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[13]; u8 nameLength; char name[4]; } eos_481;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[10]; u8 nameLength; char name[31]; } CVector3_GetDirectionRotation2_482;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[20]; } Turret_CalcOrientMtx_483;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[11]; } Turret_Move_484;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[25]; } AI_DynTurretGetTargetInfo_485;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[18]; } Turret_TrackTarget_486;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[10]; u8 nameLength; char name[20]; } Turret_BuildPlaneRot_487;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[16]; } Turret_Construct_488;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[12]; } Turret_Setup_489;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[14]; } Turret_Advance_490;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[20]; } Turret_Anim_ACTIVATE_491;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[20]; } Turret_Code_ACTIVATE_492;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[16]; } Turret_Code_IDLE_493;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[16]; } Turret_Code_FIRE_494;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[18]; } Turret_Setup_DEATH_495;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[17]; } Turret_Code_DEATH_496;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[29]; } Turret_LinkEffect_MakeVisible_497;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[26]; } Turret_LinkEffect_Activate_498;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[23]; } Turret_BuildPlaneOrient_499;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[32]; } Turret_MoveTargetIntoTurretSpace_500;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[21]; } Turret_SpecialEffects_501;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[21]; } Turret_DecreaseHealth_502;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[26]; } AI_DynTurretOpposingPlayer_503;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[24]; } AI_DynTurretCanSeePlayer_504;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[9]; u8 nameLength; char name[12]; } TurretAIInfo_505;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; SnLe32 dimension0; u8 tagNameLength; char tagName[13]; u8 nameLength; char name[15]; } TurretModeTable_506;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; SnLe32 dimension0; u8 tagNameLength; char tagName[17]; u8 nameLength; char name[20]; } TurretLinkEffectInfo_507;
    struct { SnLe32 value; u8 kind; SnLe16 frameRegister; SnLe32 frameSize; SnLe16 returnRegister; SnLe32 registerMask; SnLe32 maskOffset; SnLe32 floatRegisterMask; SnLe32 floatMaskOffset; SnLe32 line; u8 fileLength; char file[49]; u8 nameLength; char name[31]; } CVector3_GetDirectionRotation2_508;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[10]; u8 nameLength; char name[8]; } pvNormal_509;
    struct { SnLe32 value; u8 kind; SnLe32 line; } record_510;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[10]; u8 nameLength; char name[4]; } qRot_511;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[10]; u8 nameLength; char name[13]; } vIdentityAxis_512;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[10]; u8 nameLength; char name[5]; } vAxis_513;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[5]; } theta_514;
    struct { SnLe32 value; u8 kind; SnLe32 line; } record_515;
    struct { SnLe32 value; u8 kind; SnLe32 line; } record_516;
    struct { SnLe32 value; u8 kind; SnLe16 frameRegister; SnLe32 frameSize; SnLe16 returnRegister; SnLe32 registerMask; SnLe32 maskOffset; SnLe32 floatRegisterMask; SnLe32 floatMaskOffset; SnLe32 line; u8 fileLength; char file[49]; u8 nameLength; char name[20]; } Turret_CalcOrientMtx_517;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[21]; u8 nameLength; char name[5]; } pThis_518;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[5]; u8 nameLength; char name[3]; } pAI_519;
    struct { SnLe32 value; u8 kind; SnLe32 line; } record_520;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[21]; u8 nameLength; char name[6]; } pIntel_521;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[10]; u8 nameLength; char name[5]; } qRotY_522;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[10]; u8 nameLength; char name[6]; } qTemp1_523;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; SnLe32 dimension0; SnLe32 dimension1; u8 tagNameLength; u8 nameLength; char name[8]; } mfOrient_524;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; SnLe32 dimension0; SnLe32 dimension1; u8 tagNameLength; u8 nameLength; char name[7]; } mfPlane_525;
    struct { SnLe32 value; u8 kind; SnLe32 line; } record_526;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[21]; u8 nameLength; char name[5]; } pThis_527;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[5]; u8 nameLength; char name[3]; } pAI_528;
    struct { SnLe32 value; u8 kind; SnLe32 line; } record_529;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[10]; u8 nameLength; char name[4]; } qRot_530;
    struct { SnLe32 value; u8 kind; SnLe32 line; } record_531;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[5]; u8 nameLength; char name[3]; } pAI_532;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[21]; u8 nameLength; char name[5]; } pThis_533;
    struct { SnLe32 value; u8 kind; SnLe32 line; } record_534;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[10]; u8 nameLength; char name[7]; } vNormal_535;
    struct { SnLe32 value; u8 kind; SnLe32 line; } record_536;
    struct { SnLe32 value; u8 kind; SnLe32 line; } record_537;
    struct { SnLe32 value; u8 kind; SnLe32 line; } record_538;
    struct { SnLe32 value; u8 kind; SnLe32 line; } record_539;
    struct { SnLe32 value; u8 kind; SnLe32 line; } record_540;
    struct { SnLe32 value; u8 kind; SnLe32 line; } record_541;
    struct { SnLe32 value; u8 kind; SnLe16 frameRegister; SnLe32 frameSize; SnLe16 returnRegister; SnLe32 registerMask; SnLe32 maskOffset; SnLe32 floatRegisterMask; SnLe32 floatMaskOffset; SnLe32 line; u8 fileLength; char file[49]; u8 nameLength; char name[11]; } Turret_Move_542;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[21]; u8 nameLength; char name[5]; } pThis_543;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[5]; u8 nameLength; char name[3]; } pAI_544;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[10]; } MotionType_545;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[21]; u8 nameLength; char name[7]; } pTarget_546;
    struct { SnLe32 value; u8 kind; SnLe32 line; } record_547;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[21]; u8 nameLength; char name[6]; } pIntel_548;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[1]; } t_549;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[6]; } Target_550;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[3]; } Vel_551;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[5]; } Speed_552;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[10]; u8 nameLength; char name[7]; } vEndPos_553;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[10]; u8 nameLength; char name[4]; } vPos_554;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[10]; u8 nameLength; char name[7]; } vRotPos_555;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; SnLe32 dimension0; SnLe32 dimension1; u8 tagNameLength; u8 nameLength; char name[8]; } mfOrient_556;
    struct { SnLe32 value; u8 kind; SnLe32 line; } record_557;
    struct { SnLe32 value; u8 kind; SnLe32 line; } record_558;
    struct { SnLe32 value; u8 kind; SnLe16 frameRegister; SnLe32 frameSize; SnLe16 returnRegister; SnLe32 registerMask; SnLe32 maskOffset; SnLe32 floatRegisterMask; SnLe32 floatMaskOffset; SnLe32 line; u8 fileLength; char file[49]; u8 nameLength; char name[25]; } AI_DynTurretGetTargetInfo_559;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[21]; u8 nameLength; char name[5]; } pThis_560;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[5]; u8 nameLength; char name[3]; } pAI_561;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[15]; u8 nameLength; char name[5]; } pInfo_562;
    struct { SnLe32 value; u8 kind; SnLe32 line; } record_563;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[21]; u8 nameLength; char name[6]; } pIntel_564;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[9]; u8 nameLength; char name[10]; } pCurPlayer_565;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[9]; u8 nameLength; char name[17]; } pCurClosestPlayer_566;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[15]; } fCurDistanceSqr_567;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[22]; } fCurClosestDistanceSqr_568;
    struct { SnLe32 value; u8 kind; SnLe32 line; } record_569;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[21]; u8 nameLength; char name[5]; } pThis_570;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[5]; u8 nameLength; char name[3]; } pAI_571;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[9]; u8 nameLength; char name[13]; } pPlayerTarget_572;
    struct { SnLe32 value; u8 kind; SnLe32 line; } record_573;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[9]; u8 nameLength; char name[18]; } pPlayerTurretOwner_574;
    struct { SnLe32 value; u8 kind; SnLe32 line; } record_575;
    struct { SnLe32 value; u8 kind; SnLe32 line; } record_576;
    struct { SnLe32 value; u8 kind; SnLe32 line; } record_577;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[21]; u8 nameLength; char name[5]; } pThis_578;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[5]; u8 nameLength; char name[3]; } pAI_579;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[9]; u8 nameLength; char name[13]; } pPlayerTarget_580;
    struct { SnLe32 value; u8 kind; SnLe32 line; } record_581;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[10]; u8 nameLength; char name[18]; } vTargetRelativeLoc_582;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[10]; u8 nameLength; char name[13]; } vTurretOrient_583;
    struct { SnLe32 value; u8 kind; SnLe32 line; } record_584;
    struct { SnLe32 value; u8 kind; SnLe32 line; } record_585;
    struct { SnLe32 value; u8 kind; SnLe32 line; } record_586;
    struct { SnLe32 value; u8 kind; SnLe32 line; } record_587;
    struct { SnLe32 value; u8 kind; SnLe16 frameRegister; SnLe32 frameSize; SnLe16 returnRegister; SnLe32 registerMask; SnLe32 maskOffset; SnLe32 floatRegisterMask; SnLe32 floatMaskOffset; SnLe32 line; u8 fileLength; char file[49]; u8 nameLength; char name[18]; } Turret_TrackTarget_588;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[21]; u8 nameLength; char name[5]; } pThis_589;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[5]; u8 nameLength; char name[3]; } pAI_590;
    struct { SnLe32 value; u8 kind; SnLe32 line; } record_591;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[21]; u8 nameLength; char name[6]; } pIntel_592;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[15]; u8 nameLength; char name[10]; } TargetInfo_593;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[21]; u8 nameLength; char name[7]; } pTarget_594;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[10]; } TargetRotY_595;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[13]; } TargetTiltRot_596;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[5]; } Limit_597;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[9]; } DeltaRotY_598;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[4]; } RotY_599;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[10]; u8 nameLength; char name[7]; } vTurret_600;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[10]; u8 nameLength; char name[7]; } vTarget_601;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[10]; u8 nameLength; char name[4]; } vDir_602;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[8]; } bCanFire_603;
    struct { SnLe32 value; u8 kind; SnLe32 line; } record_604;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[21]; u8 nameLength; char name[5]; } pThis_605;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[5]; u8 nameLength; char name[3]; } pAI_606;
    struct { SnLe32 value; u8 kind; SnLe32 line; } record_607;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[10]; u8 nameLength; char name[6]; } vDelta_608;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; SnLe32 dimension0; SnLe32 dimension1; u8 tagNameLength; u8 nameLength; char name[7]; } mfPlane_609;
    struct { SnLe32 value; u8 kind; SnLe32 line; } record_610;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; SnLe32 dimension0; u8 tagNameLength; u8 nameLength; char name[7]; } mfPlane_611;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[5]; u8 nameLength; char name[3]; } pAI_612;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[21]; u8 nameLength; char name[5]; } pThis_613;
    struct { SnLe32 value; u8 kind; SnLe32 line; } record_614;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[10]; u8 nameLength; char name[4]; } qRot_615;
    struct { SnLe32 value; u8 kind; SnLe32 line; } record_616;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[21]; u8 nameLength; char name[5]; } pThis_617;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[5]; u8 nameLength; char name[3]; } pAI_618;
    struct { SnLe32 value; u8 kind; SnLe32 line; } record_619;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[10]; u8 nameLength; char name[7]; } vNormal_620;
    struct { SnLe32 value; u8 kind; SnLe32 line; } record_621;
    struct { SnLe32 value; u8 kind; SnLe32 line; } record_622;
    struct { SnLe32 value; u8 kind; SnLe32 line; } record_623;
    struct { SnLe32 value; u8 kind; SnLe32 line; } record_624;
    struct { SnLe32 value; u8 kind; SnLe32 line; } record_625;
    struct { SnLe32 value; u8 kind; SnLe32 line; } record_626;
    struct { SnLe32 value; u8 kind; SnLe32 line; } record_627;
    struct { SnLe32 value; u8 kind; SnLe32 line; } record_628;
    struct { SnLe32 value; u8 kind; SnLe16 frameRegister; SnLe32 frameSize; SnLe16 returnRegister; SnLe32 registerMask; SnLe32 maskOffset; SnLe32 line; u8 fileLength; char file[49]; u8 nameLength; char name[20]; } Turret_BuildPlaneRot_629;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[21]; u8 nameLength; char name[5]; } pThis_630;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[5]; u8 nameLength; char name[3]; } pAI_631;
    struct { SnLe32 value; u8 kind; SnLe32 line; } record_632;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[10]; u8 nameLength; char name[7]; } vNormal_633;
    struct { SnLe32 value; u8 kind; SnLe32 line; } record_634;
    struct { SnLe32 value; u8 kind; SnLe32 line; } record_635;
    struct { SnLe32 value; u8 kind; SnLe16 frameRegister; SnLe32 frameSize; SnLe16 returnRegister; SnLe32 registerMask; SnLe32 maskOffset; SnLe32 line; u8 fileLength; char file[49]; u8 nameLength; char name[16]; } Turret_Construct_636;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[21]; u8 nameLength; char name[5]; } pThis_637;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[5]; u8 nameLength; char name[3]; } pAI_638;
    struct { SnLe32 value; u8 kind; SnLe32 line; } record_639;
    struct { SnLe32 value; u8 kind; SnLe32 line; } record_640;
    struct { SnLe32 value; u8 kind; SnLe32 line; } record_641;
    struct { SnLe32 value; u8 kind; SnLe16 frameRegister; SnLe32 frameSize; SnLe16 returnRegister; SnLe32 registerMask; SnLe32 maskOffset; SnLe32 line; u8 fileLength; char file[49]; u8 nameLength; char name[12]; } Turret_Setup_642;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[21]; u8 nameLength; char name[5]; } pThis_643;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[5]; u8 nameLength; char name[3]; } pAI_644;
    struct { SnLe32 value; u8 kind; SnLe32 line; } record_645;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[21]; u8 nameLength; char name[6]; } pIntel_646;
    struct { SnLe32 value; u8 kind; SnLe32 line; } record_647;
    struct { SnLe32 value; u8 kind; SnLe32 line; } record_648;
    struct { SnLe32 value; u8 kind; SnLe16 frameRegister; SnLe32 frameSize; SnLe16 returnRegister; SnLe32 registerMask; SnLe32 maskOffset; SnLe32 line; u8 fileLength; char file[49]; u8 nameLength; char name[14]; } Turret_Advance_649;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[21]; u8 nameLength; char name[5]; } pThis_650;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[5]; u8 nameLength; char name[3]; } pAI_651;
    struct { SnLe32 value; u8 kind; SnLe32 line; } record_652;
    struct { SnLe32 value; u8 kind; SnLe16 frameRegister; SnLe32 frameSize; SnLe16 returnRegister; SnLe32 registerMask; SnLe32 maskOffset; SnLe32 line; u8 fileLength; char file[49]; u8 nameLength; char name[20]; } Turret_Anim_ACTIVATE_653;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[21]; u8 nameLength; char name[5]; } pThis_654;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[5]; u8 nameLength; char name[3]; } pAI_655;
    struct { SnLe32 value; u8 kind; SnLe32 line; } record_656;
    struct { SnLe32 value; u8 kind; SnLe32 line; } record_657;
    struct { SnLe32 value; u8 kind; SnLe32 line; } record_658;
    struct { SnLe32 value; u8 kind; SnLe16 frameRegister; SnLe32 frameSize; SnLe16 returnRegister; SnLe32 registerMask; SnLe32 maskOffset; SnLe32 line; u8 fileLength; char file[49]; u8 nameLength; char name[20]; } Turret_Code_ACTIVATE_659;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[21]; u8 nameLength; char name[5]; } pThis_660;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[5]; u8 nameLength; char name[3]; } pAI_661;
    struct { SnLe32 value; u8 kind; SnLe32 line; } record_662;
    struct { SnLe32 value; u8 kind; SnLe16 frameRegister; SnLe32 frameSize; SnLe16 returnRegister; SnLe32 registerMask; SnLe32 maskOffset; SnLe32 line; u8 fileLength; char file[49]; u8 nameLength; char name[16]; } Turret_Code_IDLE_663;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[21]; u8 nameLength; char name[5]; } pThis_664;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[5]; u8 nameLength; char name[3]; } pAI_665;
    struct { SnLe32 value; u8 kind; SnLe32 line; } record_666;
    struct { SnLe32 value; u8 kind; SnLe16 frameRegister; SnLe32 frameSize; SnLe16 returnRegister; SnLe32 registerMask; SnLe32 maskOffset; SnLe32 line; u8 fileLength; char file[49]; u8 nameLength; char name[16]; } Turret_Code_FIRE_667;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[21]; u8 nameLength; char name[5]; } pThis_668;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[5]; u8 nameLength; char name[3]; } pAI_669;
    struct { SnLe32 value; u8 kind; SnLe32 line; } record_670;
    struct { SnLe32 value; u8 kind; SnLe16 frameRegister; SnLe32 frameSize; SnLe16 returnRegister; SnLe32 registerMask; SnLe32 maskOffset; SnLe32 line; u8 fileLength; char file[49]; u8 nameLength; char name[18]; } Turret_Setup_DEATH_671;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[21]; u8 nameLength; char name[5]; } pThis_672;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[5]; u8 nameLength; char name[3]; } pAI_673;
    struct { SnLe32 value; u8 kind; SnLe32 line; } record_674;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[26]; u8 nameLength; char name[6]; } pIntel_675;
    struct { SnLe32 value; u8 kind; SnLe32 line; } record_676;
    struct { SnLe32 value; u8 kind; SnLe32 line; } record_677;
    struct { SnLe32 value; u8 kind; SnLe16 frameRegister; SnLe32 frameSize; SnLe16 returnRegister; SnLe32 registerMask; SnLe32 maskOffset; SnLe32 line; u8 fileLength; char file[49]; u8 nameLength; char name[17]; } Turret_Code_DEATH_678;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[21]; u8 nameLength; char name[5]; } pThis_679;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[5]; u8 nameLength; char name[3]; } pAI_680;
    struct { SnLe32 value; u8 kind; SnLe32 line; } record_681;
    struct { SnLe32 value; u8 kind; SnLe16 frameRegister; SnLe32 frameSize; SnLe16 returnRegister; SnLe32 registerMask; SnLe32 maskOffset; SnLe32 line; u8 fileLength; char file[49]; u8 nameLength; char name[29]; } Turret_LinkEffect_MakeVisible_682;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[21]; u8 nameLength; char name[5]; } pThis_683;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[5]; u8 nameLength; char name[3]; } pAI_684;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[10]; u8 nameLength; char name[8]; } pROMLink_685;
    struct { SnLe32 value; u8 kind; SnLe32 line; } record_686;
    struct { SnLe32 value; u8 kind; SnLe16 frameRegister; SnLe32 frameSize; SnLe16 returnRegister; SnLe32 registerMask; SnLe32 maskOffset; SnLe32 line; u8 fileLength; char file[49]; u8 nameLength; char name[26]; } Turret_LinkEffect_Activate_687;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[21]; u8 nameLength; char name[5]; } pThis_688;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[5]; u8 nameLength; char name[3]; } pAI_689;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[10]; u8 nameLength; char name[8]; } pROMLink_690;
    struct { SnLe32 value; u8 kind; SnLe32 line; } record_691;
    struct { SnLe32 value; u8 kind; SnLe16 frameRegister; SnLe32 frameSize; SnLe16 returnRegister; SnLe32 registerMask; SnLe32 maskOffset; SnLe32 line; u8 fileLength; char file[49]; u8 nameLength; char name[23]; } Turret_BuildPlaneOrient_692;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[21]; u8 nameLength; char name[5]; } pThis_693;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[5]; u8 nameLength; char name[3]; } pAI_694;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; SnLe32 dimension0; u8 tagNameLength; u8 nameLength; char name[7]; } mfPlane_695;
    struct { SnLe32 value; u8 kind; SnLe32 line; } record_696;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[10]; u8 nameLength; char name[4]; } qRot_697;
    struct { SnLe32 value; u8 kind; SnLe32 line; } record_698;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[5]; u8 nameLength; char name[3]; } pAI_699;
    struct { SnLe32 value; u8 kind; SnLe32 line; } record_700;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[10]; u8 nameLength; char name[7]; } vNormal_701;
    struct { SnLe32 value; u8 kind; SnLe32 line; } record_702;
    struct { SnLe32 value; u8 kind; SnLe32 line; } record_703;
    struct { SnLe32 value; u8 kind; SnLe32 line; } record_704;
    struct { SnLe32 value; u8 kind; SnLe32 line; } record_705;
    struct { SnLe32 value; u8 kind; SnLe16 frameRegister; SnLe32 frameSize; SnLe16 returnRegister; SnLe32 registerMask; SnLe32 maskOffset; SnLe32 line; u8 fileLength; char file[49]; u8 nameLength; char name[32]; } Turret_MoveTargetIntoTurretSpace_706;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[21]; u8 nameLength; char name[5]; } pThis_707;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[5]; u8 nameLength; char name[3]; } pAI_708;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[10]; u8 nameLength; char name[11]; } pvTurretEye_709;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[10]; u8 nameLength; char name[8]; } pvTarget_710;
    struct { SnLe32 value; u8 kind; SnLe32 line; } record_711;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; SnLe32 dimension0; SnLe32 dimension1; u8 tagNameLength; u8 nameLength; char name[7]; } mfPlane_712;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[10]; u8 nameLength; char name[6]; } vDelta_713;
    struct { SnLe32 value; u8 kind; SnLe32 line; } record_714;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[5]; u8 nameLength; char name[3]; } pAI_715;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; SnLe32 dimension0; u8 tagNameLength; u8 nameLength; char name[7]; } mfPlane_716;
    struct { SnLe32 value; u8 kind; SnLe32 line; } record_717;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[10]; u8 nameLength; char name[4]; } qRot_718;
    struct { SnLe32 value; u8 kind; SnLe32 line; } record_719;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[5]; u8 nameLength; char name[3]; } pAI_720;
    struct { SnLe32 value; u8 kind; SnLe32 line; } record_721;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[10]; u8 nameLength; char name[7]; } vNormal_722;
    struct { SnLe32 value; u8 kind; SnLe32 line; } record_723;
    struct { SnLe32 value; u8 kind; SnLe32 line; } record_724;
    struct { SnLe32 value; u8 kind; SnLe32 line; } record_725;
    struct { SnLe32 value; u8 kind; SnLe32 line; } record_726;
    struct { SnLe32 value; u8 kind; SnLe32 line; } record_727;
    struct { SnLe32 value; u8 kind; SnLe32 line; } record_728;
    struct { SnLe32 value; u8 kind; SnLe16 frameRegister; SnLe32 frameSize; SnLe16 returnRegister; SnLe32 registerMask; SnLe32 maskOffset; SnLe32 line; u8 fileLength; char file[49]; u8 nameLength; char name[21]; } Turret_SpecialEffects_729;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; SnLe32 dimension0; u8 tagNameLength; u8 nameLength; char name[7]; } mfLocal_730;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[15]; u8 nameLength; char name[13]; } pAnimNodeInfo_731;
    struct { SnLe32 value; u8 kind; SnLe32 line; } record_732;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[21]; u8 nameLength; char name[6]; } pIntel_733;
    struct { SnLe32 value; u8 kind; SnLe32 line; } record_734;
    struct { SnLe32 value; u8 kind; SnLe32 line; } record_735;
    struct { SnLe32 value; u8 kind; SnLe16 frameRegister; SnLe32 frameSize; SnLe16 returnRegister; SnLe32 registerMask; SnLe32 maskOffset; SnLe32 line; u8 fileLength; char file[49]; u8 nameLength; char name[21]; } Turret_DecreaseHealth_736;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[21]; u8 nameLength; char name[5]; } pThis_737;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[5]; u8 nameLength; char name[3]; } pAI_738;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[13]; u8 nameLength; char name[5]; } pInfo_739;
    struct { SnLe32 value; u8 kind; SnLe32 line; } record_740;
    struct { SnLe32 value; u8 kind; SnLe16 frameRegister; SnLe32 frameSize; SnLe16 returnRegister; SnLe32 registerMask; SnLe32 maskOffset; SnLe32 line; u8 fileLength; char file[49]; u8 nameLength; char name[26]; } AI_DynTurretOpposingPlayer_741;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[21]; u8 nameLength; char name[5]; } pThis_742;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[5]; u8 nameLength; char name[3]; } pAI_743;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[9]; u8 nameLength; char name[13]; } pPlayerTarget_744;
    struct { SnLe32 value; u8 kind; SnLe32 line; } record_745;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[9]; u8 nameLength; char name[18]; } pPlayerTurretOwner_746;
    struct { SnLe32 value; u8 kind; SnLe32 line; } record_747;
    struct { SnLe32 value; u8 kind; SnLe32 line; } record_748;
    struct { SnLe32 value; u8 kind; SnLe16 frameRegister; SnLe32 frameSize; SnLe16 returnRegister; SnLe32 registerMask; SnLe32 maskOffset; SnLe32 floatRegisterMask; SnLe32 floatMaskOffset; SnLe32 line; u8 fileLength; char file[49]; u8 nameLength; char name[24]; } AI_DynTurretCanSeePlayer_749;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[21]; u8 nameLength; char name[5]; } pThis_750;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[5]; u8 nameLength; char name[3]; } pAI_751;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[9]; u8 nameLength; char name[13]; } pPlayerTarget_752;
    struct { SnLe32 value; u8 kind; SnLe32 line; } record_753;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[10]; u8 nameLength; char name[13]; } vTurretOrient_754;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[10]; u8 nameLength; char name[18]; } vTargetRelativeLoc_755;
    struct { SnLe32 value; u8 kind; SnLe32 line; } record_756;
    struct { SnLe32 value; u8 kind; SnLe32 line; } record_757;
    struct { SnLe32 value; u8 kind; SnLe32 line; u8 fileLength; char file[49]; } C_PROJECTS_DM_N64_SOURCE_AI_DEVICES_ACTIONAI_CPP_758;
    struct { SnLe32 value; u8 kind; } record_759;
    struct { SnLe32 value; u8 kind; u8 lineDelta; } record_760;
    struct { SnLe32 value; u8 kind; SnLe32 line; } record_761;
    struct { SnLe32 value; u8 kind; u8 lineDelta; } record_762;
    struct { SnLe32 value; u8 kind; u8 lineDelta; } record_763;
    struct { SnLe32 value; u8 kind; u8 lineDelta; } record_764;
    struct { SnLe32 value; u8 kind; u8 lineDelta; } record_765;
    struct { SnLe32 value; u8 kind; u8 lineDelta; } record_766;
    struct { SnLe32 value; u8 kind; u8 lineDelta; } record_767;
    struct { SnLe32 value; u8 kind; u8 lineDelta; } record_768;
    struct { SnLe32 value; u8 kind; } record_769;
    struct { SnLe32 value; u8 kind; u8 lineDelta; } record_770;
    struct { SnLe32 value; u8 kind; SnLe32 line; } record_771;
    struct { SnLe32 value; u8 kind; u8 lineDelta; } record_772;
    struct { SnLe32 value; u8 kind; u8 lineDelta; } record_773;
    struct { SnLe32 value; u8 kind; u8 lineDelta; } record_774;
    struct { SnLe32 value; u8 kind; SnLe32 line; } record_775;
    struct { SnLe32 value; u8 kind; u8 lineDelta; } record_776;
    struct { SnLe32 value; u8 kind; u8 lineDelta; } record_777;
    struct { SnLe32 value; u8 kind; u8 lineDelta; } record_778;
    struct { SnLe32 value; u8 kind; u8 lineDelta; } record_779;
    struct { SnLe32 value; u8 kind; u8 lineDelta; } record_780;
    struct { SnLe32 value; u8 kind; SnLe32 line; } record_781;
    struct { SnLe32 value; u8 kind; } record_782;
    struct { SnLe32 value; u8 kind; u8 lineDelta; } record_783;
    struct { SnLe32 value; u8 kind; SnLe32 line; } record_784;
    struct { SnLe32 value; u8 kind; } record_785;
    struct { SnLe32 value; u8 kind; u8 lineDelta; } record_786;
    struct { SnLe32 value; u8 kind; u8 lineDelta; } record_787;
    struct { SnLe32 value; u8 kind; u8 lineDelta; } record_788;
    struct { SnLe32 value; u8 kind; u8 lineDelta; } record_789;
    struct { SnLe32 value; u8 kind; u8 lineDelta; } record_790;
    struct { SnLe32 value; u8 kind; } record_791;
    struct { SnLe32 value; u8 kind; } record_792;
    struct { SnLe32 value; u8 kind; } record_793;
    struct { SnLe32 value; u8 kind; SnLe32 line; } record_794;
    struct { SnLe32 value; u8 kind; } record_795;
    struct { SnLe32 value; u8 kind; SnLe32 line; } record_796;
    struct { SnLe32 value; u8 kind; } record_797;
    struct { SnLe32 value; u8 kind; u8 lineDelta; } record_798;
    struct { SnLe32 value; u8 kind; } record_799;
    struct { SnLe32 value; u8 kind; u8 lineDelta; } record_800;
    struct { SnLe32 value; u8 kind; u8 lineDelta; } record_801;
    struct { SnLe32 value; u8 kind; u8 lineDelta; } record_802;
    struct { SnLe32 value; u8 kind; u8 lineDelta; } record_803;
    struct { SnLe32 value; u8 kind; u8 lineDelta; } record_804;
    struct { SnLe32 value; u8 kind; u8 lineDelta; } record_805;
    struct { SnLe32 value; u8 kind; u8 lineDelta; } record_806;
    struct { SnLe32 value; u8 kind; } record_807;
    struct { SnLe32 value; u8 kind; u8 lineDelta; } record_808;
    struct { SnLe32 value; u8 kind; } record_809;
    struct { SnLe32 value; u8 kind; u8 lineDelta; } record_810;
    struct { SnLe32 value; u8 kind; } record_811;
    struct { SnLe32 value; u8 kind; u8 lineDelta; } record_812;
    struct { SnLe32 value; u8 kind; u8 lineDelta; } record_813;
    struct { SnLe32 value; u8 kind; u8 lineDelta; } record_814;
    struct { SnLe32 value; u8 kind; } record_815;
    struct { SnLe32 value; u8 kind; u8 lineDelta; } record_816;
    struct { SnLe32 value; u8 kind; } record_817;
    struct { SnLe32 value; u8 kind; u8 lineDelta; } record_818;
    struct { SnLe32 value; u8 kind; u8 lineDelta; } record_819;
    struct { SnLe32 value; u8 kind; u8 lineDelta; } record_820;
    struct { SnLe32 value; u8 kind; u8 lineDelta; } record_821;
    struct { SnLe32 value; u8 kind; } record_822;
    struct { SnLe32 value; u8 kind; u8 lineDelta; } record_823;
    struct { SnLe32 value; u8 kind; u8 lineDelta; } record_824;
    struct { SnLe32 value; u8 kind; u8 lineDelta; } record_825;
    struct { SnLe32 value; u8 kind; SnLe32 line; } record_826;
    struct { SnLe32 value; u8 kind; u8 lineDelta; } record_827;
    struct { SnLe32 value; u8 kind; u8 lineDelta; } record_828;
    struct { SnLe32 value; u8 kind; u8 lineDelta; } record_829;
    struct { SnLe32 value; u8 kind; SnLe32 line; } record_830;
    struct { SnLe32 value; u8 kind; u8 lineDelta; } record_831;
    struct { SnLe32 value; u8 kind; u8 lineDelta; } record_832;
    struct { SnLe32 value; u8 kind; } record_833;
    struct { SnLe32 value; u8 kind; u8 lineDelta; } record_834;
    struct { SnLe32 value; u8 kind; u8 lineDelta; } record_835;
    struct { SnLe32 value; u8 kind; SnLe32 line; } record_836;
    struct { SnLe32 value; u8 kind; } record_837;
    struct { SnLe32 value; u8 kind; u8 lineDelta; } record_838;
    struct { SnLe32 value; u8 kind; u8 lineDelta; } record_839;
    struct { SnLe32 value; u8 kind; u8 lineDelta; } record_840;
    struct { SnLe32 value; u8 kind; u8 lineDelta; } record_841;
    struct { SnLe32 value; u8 kind; u8 lineDelta; } record_842;
    struct { SnLe32 value; u8 kind; } record_843;
    struct { SnLe32 value; u8 kind; } record_844;
    struct { SnLe32 value; u8 kind; u8 lineDelta; } record_845;
    struct { SnLe32 value; u8 kind; } record_846;
    struct { SnLe32 value; u8 kind; u8 lineDelta; } record_847;
    struct { SnLe32 value; u8 kind; SnLe32 line; } record_848;
    struct { SnLe32 value; u8 kind; } record_849;
    struct { SnLe32 value; u8 kind; } record_850;
    struct { SnLe32 value; u8 kind; } record_851;
    struct { SnLe32 value; u8 kind; } record_852;
    struct { SnLe32 value; u8 kind; u8 lineDelta; } record_853;
    struct { SnLe32 value; u8 kind; } record_854;
    struct { SnLe32 value; u8 kind; u8 lineDelta; } record_855;
    struct { SnLe32 value; u8 kind; u8 lineDelta; } record_856;
    struct { SnLe32 value; u8 kind; u8 lineDelta; } record_857;
    struct { SnLe32 value; u8 kind; SnLe32 line; } record_858;
    struct { SnLe32 value; u8 kind; u8 lineDelta; } record_859;
    struct { SnLe32 value; u8 kind; } record_860;
    struct { SnLe32 value; u8 kind; u8 lineDelta; } record_861;
    struct { SnLe32 value; u8 kind; u8 lineDelta; } record_862;
    struct { SnLe32 value; u8 kind; u8 lineDelta; } record_863;
    struct { SnLe32 value; u8 kind; u8 lineDelta; } record_864;
    struct { SnLe32 value; u8 kind; u8 lineDelta; } record_865;
    struct { SnLe32 value; u8 kind; u8 lineDelta; } record_866;
    struct { SnLe32 value; u8 kind; u8 lineDelta; } record_867;
    struct { SnLe32 value; u8 kind; SnLe32 line; } record_868;
    struct { SnLe32 value; u8 kind; } record_869;
    struct { SnLe32 value; u8 kind; } record_870;
    struct { SnLe32 value; u8 kind; u8 lineDelta; } record_871;
    struct { SnLe32 value; u8 kind; u8 lineDelta; } record_872;
    struct { SnLe32 value; u8 kind; u8 lineDelta; } record_873;
    struct { SnLe32 value; u8 kind; } record_874;
    struct { SnLe32 value; u8 kind; u8 lineDelta; } record_875;
    struct { SnLe32 value; u8 kind; u8 lineDelta; } record_876;
    struct { SnLe32 value; u8 kind; u8 lineDelta; } record_877;
    struct { SnLe32 value; u8 kind; u8 lineDelta; } record_878;
    struct { SnLe32 value; u8 kind; SnLe32 line; } record_879;
    struct { SnLe32 value; u8 kind; u8 lineDelta; } record_880;
    struct { SnLe32 value; u8 kind; u8 lineDelta; } record_881;
    struct { SnLe32 value; u8 kind; u8 lineDelta; } record_882;
    struct { SnLe32 value; u8 kind; u8 lineDelta; } record_883;
    struct { SnLe32 value; u8 kind; u8 lineDelta; } record_884;
    struct { SnLe32 value; u8 kind; } record_885;
    struct { SnLe32 value; u8 kind; u8 lineDelta; } record_886;
    struct { SnLe32 value; u8 kind; } record_887;
    struct { SnLe32 value; u8 kind; u8 lineDelta; } record_888;
    struct { SnLe32 value; u8 kind; u8 lineDelta; } record_889;
    struct { SnLe32 value; u8 kind; u8 lineDelta; } record_890;
    struct { SnLe32 value; u8 kind; SnLe32 line; } record_891;
    struct { SnLe32 value; u8 kind; } record_892;
    struct { SnLe32 value; u8 kind; u8 lineDelta; } record_893;
    struct { SnLe32 value; u8 kind; u8 lineDelta; } record_894;
    struct { SnLe32 value; u8 kind; } record_895;
    struct { SnLe32 value; u8 kind; u8 lineDelta; } record_896;
    struct { SnLe32 value; u8 kind; u8 lineDelta; } record_897;
    struct { SnLe32 value; u8 kind; u8 lineDelta; } record_898;
    struct { SnLe32 value; u8 kind; u8 lineDelta; } record_899;
    struct { SnLe32 value; u8 kind; u8 lineDelta; } record_900;
    struct { SnLe32 value; u8 kind; } record_901;
    struct { SnLe32 value; u8 kind; u8 lineDelta; } record_902;
    struct { SnLe32 value; u8 kind; } record_903;
    struct { SnLe32 value; u8 kind; u8 lineDelta; } record_904;
    struct { SnLe32 value; u8 kind; u8 lineDelta; } record_905;
    struct { SnLe32 value; u8 kind; u8 lineDelta; } record_906;
    struct { SnLe32 value; u8 kind; u8 lineDelta; } record_907;
    struct { SnLe32 value; u8 kind; } record_908;
    struct { SnLe32 value; u8 kind; } record_909;
    struct { SnLe32 value; u8 kind; SnLe32 line; } record_910;
    struct { SnLe32 value; u8 kind; u8 lineDelta; } record_911;
    struct { SnLe32 value; u8 kind; u8 lineDelta; } record_912;
    struct { SnLe32 value; u8 kind; u8 lineDelta; } record_913;
    struct { SnLe32 value; u8 kind; u8 lineDelta; } record_914;
    struct { SnLe32 value; u8 kind; SnLe32 line; } record_915;
    struct { SnLe32 value; u8 kind; u8 lineDelta; } record_916;
    struct { SnLe32 value; u8 kind; u8 lineDelta; } record_917;
    struct { SnLe32 value; u8 kind; u8 lineDelta; } record_918;
    struct { SnLe32 value; u8 kind; u8 lineDelta; } record_919;
    struct { SnLe32 value; u8 kind; u8 lineDelta; } record_920;
    struct { SnLe32 value; u8 kind; u8 lineDelta; } record_921;
    struct { SnLe32 value; u8 kind; SnLe32 line; } record_922;
    struct { SnLe32 value; u8 kind; u8 lineDelta; } record_923;
    struct { SnLe32 value; u8 kind; SnLe16 lineDelta; } record_924;
    struct { SnLe32 value; u8 kind; u8 lineDelta; } record_925;
    struct { SnLe32 value; u8 kind; SnLe32 line; } record_926;
    struct { SnLe32 value; u8 kind; } record_927;
    struct { SnLe32 value; u8 kind; u8 lineDelta; } record_928;
    struct { SnLe32 value; u8 kind; u8 lineDelta; } record_929;
    struct { SnLe32 value; u8 kind; } record_930;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[2]; } u8_931;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[2]; } s8_932;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[3]; } vu8_933;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[3]; } vs8_934;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[3]; } u16_935;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[3]; } s16_936;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[4]; } vu16_937;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[4]; } vs16_938;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[3]; } u32_939;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[3]; } s32_940;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[4]; } vu32_941;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[4]; } vs32_942;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[3]; } u64_943;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[3]; } s64_944;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[4]; } vu64_945;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[4]; } vs64_946;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[3]; } f32_947;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[3]; } f64_948;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[5]; } OSPri_949;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[4]; } OSId_950;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[6]; } record_0fake_951;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[5]; } f_odd_952;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[6]; } f_even_953;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[6]; u8 nameLength; char name[4]; } eos_954;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[6]; } record_1fake_955;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[6]; u8 nameLength; char name[1]; } f_956;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[1]; } d_957;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[6]; u8 nameLength; char name[4]; } eos_958;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[6]; u8 nameLength; char name[6]; } OSfp_959;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[6]; } record_2fake_960;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[2]; } at_961;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[2]; } v0_962;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[2]; } v1_963;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[2]; } a0_964;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[2]; } a1_965;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[2]; } a2_966;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[2]; } a3_967;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[2]; } t0_968;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[2]; } t1_969;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[2]; } t2_970;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[2]; } t3_971;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[2]; } t4_972;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[2]; } t5_973;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[2]; } t6_974;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[2]; } t7_975;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[2]; } s0_976;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[2]; } s1_977;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[2]; } s2_978;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[2]; } s3_979;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[2]; } s4_980;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[2]; } s5_981;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[2]; } s6_982;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[2]; } s7_983;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[2]; } t8_984;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[2]; } t9_985;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[2]; } gp_986;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[2]; } sp_987;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[2]; } s8_988;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[2]; } ra_989;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[2]; } lo_990;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[2]; } hi_991;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[2]; } sr_992;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[2]; } pc_993;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[5]; } cause_994;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[8]; } badvaddr_995;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[3]; } rcp_996;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[5]; } fpcsr_997;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[6]; u8 nameLength; char name[3]; } fp0_998;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[6]; u8 nameLength; char name[3]; } fp2_999;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[6]; u8 nameLength; char name[3]; } fp4_1000;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[6]; u8 nameLength; char name[3]; } fp6_1001;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[6]; u8 nameLength; char name[3]; } fp8_1002;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[6]; u8 nameLength; char name[4]; } fp10_1003;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[6]; u8 nameLength; char name[4]; } fp12_1004;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[6]; u8 nameLength; char name[4]; } fp14_1005;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[6]; u8 nameLength; char name[4]; } fp16_1006;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[6]; u8 nameLength; char name[4]; } fp18_1007;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[6]; u8 nameLength; char name[4]; } fp20_1008;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[6]; u8 nameLength; char name[4]; } fp22_1009;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[6]; u8 nameLength; char name[4]; } fp24_1010;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[6]; u8 nameLength; char name[4]; } fp26_1011;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[6]; u8 nameLength; char name[4]; } fp28_1012;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[6]; u8 nameLength; char name[4]; } fp30_1013;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[6]; u8 nameLength; char name[3]; } fp1_1014;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[6]; u8 nameLength; char name[3]; } fp3_1015;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[6]; u8 nameLength; char name[3]; } fp5_1016;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[6]; u8 nameLength; char name[3]; } fp7_1017;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[6]; u8 nameLength; char name[3]; } fp9_1018;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[6]; u8 nameLength; char name[4]; } fp11_1019;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[6]; u8 nameLength; char name[4]; } fp13_1020;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[6]; u8 nameLength; char name[4]; } fp15_1021;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[6]; u8 nameLength; char name[4]; } fp17_1022;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[6]; u8 nameLength; char name[4]; } fp19_1023;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[6]; u8 nameLength; char name[4]; } fp21_1024;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[6]; u8 nameLength; char name[4]; } fp23_1025;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[6]; u8 nameLength; char name[4]; } fp25_1026;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[6]; u8 nameLength; char name[4]; } fp27_1027;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[6]; u8 nameLength; char name[4]; } fp29_1028;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[6]; u8 nameLength; char name[4]; } fp31_1029;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[6]; u8 nameLength; char name[4]; } eos_1030;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[6]; u8 nameLength; char name[17]; } OSThreadContext_1031;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[10]; } OSThread_s_1032;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[10]; u8 nameLength; char name[4]; } next_1033;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[8]; } priority_1034;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[10]; u8 nameLength; char name[5]; } queue_1035;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[10]; u8 nameLength; char name[6]; } tlnext_1036;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[5]; } state_1037;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[5]; } flags_1038;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[2]; } id_1039;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[2]; } fp_1040;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[6]; u8 nameLength; char name[7]; } context_1041;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[10]; u8 nameLength; char name[4]; } eos_1042;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[10]; u8 nameLength; char name[8]; } OSThread_1043;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[7]; } OSEvent_1044;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[9]; } OSIntMask_1045;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[10]; } OSPageMask_1046;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[8]; } OSHWIntr_1047;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[6]; } OSMesg_1048;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[13]; } OSMesgQueue_s_1049;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[10]; u8 nameLength; char name[7]; } mtqueue_1050;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[10]; u8 nameLength; char name[9]; } fullqueue_1051;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[10]; } validCount_1052;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[5]; } first_1053;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[8]; } msgCount_1054;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[3]; } msg_1055;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[13]; u8 nameLength; char name[4]; } eos_1056;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[13]; u8 nameLength; char name[11]; } OSMesgQueue_1057;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[6]; } record_3fake_1058;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[9]; } errStatus_1059;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[8]; } dramAddr_1060;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[6]; } C2Addr_1061;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[10]; } sectorSize_1062;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[8]; } C1ErrNum_1063;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; SnLe32 dimension0; u8 tagNameLength; u8 nameLength; char name[11]; } C1ErrSector_1064;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[6]; u8 nameLength; char name[4]; } eos_1065;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[6]; u8 nameLength; char name[13]; } OSBlockInfo_1066;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[6]; } record_4fake_1067;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[7]; } cmdType_1068;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[12]; } transferMode_1069;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[8]; } blockNum_1070;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[9]; } sectorNum_1071;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[7]; } devAddr_1072;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[11]; } bmCtlShadow_1073;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[12]; } seqCtlShadow_1074;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; SnLe32 dimension0; u8 tagNameLength; char tagName[6]; u8 nameLength; char name[5]; } block_1075;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[6]; u8 nameLength; char name[4]; } eos_1076;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[6]; u8 nameLength; char name[13]; } OSTranxInfo_1077;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[12]; } OSPiHandle_s_1078;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[12]; u8 nameLength; char name[4]; } next_1079;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[4]; } type_1080;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[7]; } latency_1081;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[8]; } pageSize_1082;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[11]; } relDuration_1083;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[5]; } pulse_1084;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[6]; } domain_1085;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[11]; } baseAddress_1086;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[5]; } speed_1087;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[6]; u8 nameLength; char name[12]; } transferInfo_1088;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[12]; u8 nameLength; char name[4]; } eos_1089;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[12]; u8 nameLength; char name[10]; } OSPiHandle_1090;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[6]; } record_5fake_1091;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[4]; } type_1092;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[7]; } address_1093;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[6]; u8 nameLength; char name[4]; } eos_1094;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[6]; u8 nameLength; char name[8]; } OSPiInfo_1095;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[6]; } record_6fake_1096;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[4]; } type_1097;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[3]; } pri_1098;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[6]; } status_1099;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[13]; u8 nameLength; char name[8]; } retQueue_1100;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[6]; u8 nameLength; char name[4]; } eos_1101;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[6]; u8 nameLength; char name[11]; } OSIoMesgHdr_1102;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[6]; } record_7fake_1103;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[6]; u8 nameLength; char name[3]; } hdr_1104;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[8]; } dramAddr_1105;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[7]; } devAddr_1106;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[4]; } size_1107;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[12]; u8 nameLength; char name[8]; } piHandle_1108;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[6]; u8 nameLength; char name[4]; } eos_1109;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[6]; u8 nameLength; char name[8]; } OSIoMesg_1110;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[6]; } record_8fake_1111;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[6]; } active_1112;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[10]; u8 nameLength; char name[6]; } thread_1113;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[13]; u8 nameLength; char name[8]; } cmdQueue_1114;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[13]; u8 nameLength; char name[8]; } evtQueue_1115;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[13]; u8 nameLength; char name[8]; } acsQueue_1116;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[3]; } dma_1117;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[4]; } edma_1118;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[6]; u8 nameLength; char name[4]; } eos_1119;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[6]; u8 nameLength; char name[8]; } OSDevMgr_1120;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[6]; } record_9fake_1121;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[4]; } ctrl_1122;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[5]; } width_1123;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[5]; } burst_1124;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[5]; } vSync_1125;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[5]; } hSync_1126;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[4]; } leap_1127;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[6]; } hStart_1128;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[6]; } xScale_1129;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[8]; } vCurrent_1130;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[6]; u8 nameLength; char name[4]; } eos_1131;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[6]; u8 nameLength; char name[14]; } OSViCommonRegs_1132;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[7]; } record_10fake_1133;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[6]; } origin_1134;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[6]; } yScale_1135;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[6]; } vStart_1136;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[6]; } vBurst_1137;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[5]; } vIntr_1138;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[4]; } eos_1139;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[13]; } OSViFieldRegs_1140;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[7]; } record_11fake_1141;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[4]; } type_1142;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[6]; u8 nameLength; char name[7]; } comRegs_1143;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; SnLe32 dimension0; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[7]; } fldRegs_1144;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[4]; } eos_1145;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[8]; } OSViMode_1146;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[6]; } OSTime_1147;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[9]; } OSTimer_s_1148;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[9]; u8 nameLength; char name[4]; } next_1149;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[9]; u8 nameLength; char name[4]; } prev_1150;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[8]; } interval_1151;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[5]; } value_1152;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[13]; u8 nameLength; char name[2]; } mq_1153;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[3]; } msg_1154;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[9]; u8 nameLength; char name[4]; } eos_1155;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[9]; u8 nameLength; char name[7]; } OSTimer_1156;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[7]; } record_12fake_1157;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[4]; } type_1158;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[6]; } status_1159;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[5]; } errno_1160;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[4]; } eos_1161;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[12]; } OSContStatus_1162;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[7]; } record_13fake_1163;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[6]; } button_1164;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[7]; } stick_x_1165;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[7]; } stick_y_1166;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[5]; } errno_1167;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[4]; } eos_1168;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[9]; } OSContPad_1169;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[7]; } record_14fake_1170;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[7]; } address_1171;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; SnLe32 dimension0; u8 tagNameLength; u8 nameLength; char name[10]; } databuffer_1172;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[10]; } addressCrc_1173;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[7]; } dataCrc_1174;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[5]; } errno_1175;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[4]; } eos_1176;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[11]; } OSContRamIo_1177;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[7]; } record_15fake_1178;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[6]; } status_1179;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[13]; u8 nameLength; char name[5]; } queue_1180;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[7]; } channel_1181;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; SnLe32 dimension0; u8 tagNameLength; u8 nameLength; char name[2]; } id_1182;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; SnLe32 dimension0; u8 tagNameLength; u8 nameLength; char name[5]; } label_1183;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[7]; } version_1184;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[8]; } dir_size_1185;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[11]; } inode_table_1186;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[12]; } minode_table_1187;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[9]; } dir_table_1188;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[16]; } inode_start_page_1189;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[5]; } banks_1190;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[10]; } activebank_1191;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[4]; } eos_1192;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[5]; } OSPfs_1193;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[7]; } record_16fake_1194;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[9]; } file_size_1195;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[9]; } game_code_1196;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[12]; } company_code_1197;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; SnLe32 dimension0; u8 tagNameLength; u8 nameLength; char name[8]; } ext_name_1198;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; SnLe32 dimension0; u8 tagNameLength; u8 nameLength; char name[9]; } game_name_1199;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[4]; } eos_1200;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[10]; } OSPfsState_1201;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[7]; } record_17fake_1202;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[10]; } histo_base_1203;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[10]; } histo_size_1204;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[10]; } text_start_1205;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[8]; } text_end_1206;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[4]; } eos_1207;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[6]; } OSProf_1208;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[9]; } Region_s_1209;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[20]; } r_startBufferAddress_1210;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[12]; } r_endAddress_1211;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[12]; } r_bufferSize_1212;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[13]; } r_bufferCount_1213;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[10]; } r_freeList_1214;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[11]; } r_alignSize_1215;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[9]; u8 nameLength; char name[4]; } eos_1216;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[9]; u8 nameLength; char name[8]; } OSRegion_1217;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[7]; } record_18fake_1218;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[4]; } type_1219;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[5]; } flags_1220;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[10]; } ucode_boot_1221;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[15]; } ucode_boot_size_1222;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[5]; } ucode_1223;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[10]; } ucode_size_1224;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[10]; } ucode_data_1225;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[15]; } ucode_data_size_1226;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[10]; } dram_stack_1227;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[15]; } dram_stack_size_1228;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[11]; } output_buff_1229;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[16]; } output_buff_size_1230;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[8]; } data_ptr_1231;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[9]; } data_size_1232;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[14]; } yield_data_ptr_1233;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[15]; } yield_data_size_1234;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[4]; } eos_1235;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[8]; } OSTask_t_1236;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[7]; } record_19fake_1237;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[1]; } t_1238;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[25]; } force_structure_alignment_1239;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[4]; } eos_1240;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[6]; } OSTask_1241;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[13]; } OSYieldResult_1242;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[7]; } record_20fake_1243;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; SnLe32 dimension0; u8 tagNameLength; u8 nameLength; char name[2]; } ob_1244;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[4]; } flag_1245;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; SnLe32 dimension0; u8 tagNameLength; u8 nameLength; char name[2]; } tc_1246;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; SnLe32 dimension0; u8 tagNameLength; u8 nameLength; char name[2]; } cn_1247;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[4]; } eos_1248;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[5]; } Vtx_t_1249;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[7]; } record_21fake_1250;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; SnLe32 dimension0; u8 tagNameLength; u8 nameLength; char name[2]; } ob_1251;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[4]; } flag_1252;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; SnLe32 dimension0; u8 tagNameLength; u8 nameLength; char name[2]; } tc_1253;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; SnLe32 dimension0; u8 tagNameLength; u8 nameLength; char name[1]; } n_1254;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[1]; } a_1255;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[4]; } eos_1256;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[6]; } Vtx_tn_1257;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[7]; } record_22fake_1258;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[1]; } v_1259;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[1]; } n_1260;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[25]; } force_structure_alignment_1261;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[4]; } eos_1262;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[3]; } Vtx_1263;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[7]; } record_23fake_1264;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[18]; } SourceImagePointer_1265;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[11]; } TlutPointer_1266;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[6]; } Stride_1267;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[13]; } SubImageWidth_1268;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[14]; } SubImageHeight_1269;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[15]; } SourceImageType_1270;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[18]; } SourceImageBitSize_1271;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[18]; } SourceImageOffsetS_1272;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[18]; } SourceImageOffsetT_1273;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; SnLe32 dimension0; u8 tagNameLength; u8 nameLength; char name[5]; } dummy_1274;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[4]; } eos_1275;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[9]; } uSprite_t_1276;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[7]; } record_24fake_1277;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[1]; } s_1278;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; SnLe32 dimension0; u8 tagNameLength; u8 nameLength; char name[26]; } force_structure_allignment_1279;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[4]; } eos_1280;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[7]; } uSprite_1281;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[7]; } record_25fake_1282;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[4]; } flag_1283;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; SnLe32 dimension0; u8 tagNameLength; u8 nameLength; char name[1]; } v_1284;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[4]; } eos_1285;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[3]; } Tri_1286;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; SnLe32 dimension0; SnLe32 dimension1; u8 tagNameLength; u8 nameLength; char name[5]; } Mtx_t_1287;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[7]; } record_26fake_1288;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; SnLe32 dimension0; SnLe32 dimension1; u8 tagNameLength; u8 nameLength; char name[1]; } m_1289;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[25]; } force_structure_alignment_1290;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[4]; } eos_1291;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[3]; } Mtx_1292;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[7]; } record_27fake_1293;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; SnLe32 dimension0; u8 tagNameLength; u8 nameLength; char name[6]; } vscale_1294;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; SnLe32 dimension0; u8 tagNameLength; u8 nameLength; char name[6]; } vtrans_1295;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[4]; } eos_1296;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[4]; } Vp_t_1297;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[7]; } record_28fake_1298;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[2]; } vp_1299;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[25]; } force_structure_alignment_1300;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[4]; } eos_1301;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[2]; } Vp_1302;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[7]; } record_29fake_1303;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; SnLe32 dimension0; u8 tagNameLength; u8 nameLength; char name[3]; } col_1304;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[4]; } pad1_1305;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; SnLe32 dimension0; u8 tagNameLength; u8 nameLength; char name[4]; } colc_1306;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[4]; } pad2_1307;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; SnLe32 dimension0; u8 tagNameLength; u8 nameLength; char name[3]; } dir_1308;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[4]; } pad3_1309;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[4]; } eos_1310;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[7]; } Light_t_1311;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[7]; } record_30fake_1312;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; SnLe32 dimension0; u8 tagNameLength; u8 nameLength; char name[3]; } col_1313;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[4]; } pad1_1314;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; SnLe32 dimension0; u8 tagNameLength; u8 nameLength; char name[4]; } colc_1315;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[4]; } pad2_1316;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[4]; } eos_1317;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[9]; } Ambient_t_1318;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[7]; } record_31fake_1319;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[2]; } x1_1320;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[2]; } y1_1321;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[2]; } x2_1322;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[2]; } y2_1323;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[4]; } eos_1324;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[8]; } Hilite_t_1325;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[7]; } record_32fake_1326;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[1]; } l_1327;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; SnLe32 dimension0; u8 tagNameLength; u8 nameLength; char name[25]; } force_structure_alignment_1328;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[4]; } eos_1329;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[5]; } Light_1330;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[7]; } record_33fake_1331;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[1]; } l_1332;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; SnLe32 dimension0; u8 tagNameLength; u8 nameLength; char name[25]; } force_structure_alignment_1333;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[4]; } eos_1334;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[7]; } Ambient_1335;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[7]; } record_34fake_1336;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[1]; } a_1337;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; SnLe32 dimension0; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[1]; } l_1338;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[4]; } eos_1339;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[7]; } Lightsn_1340;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[7]; } record_35fake_1341;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[1]; } a_1342;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; SnLe32 dimension0; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[1]; } l_1343;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[4]; } eos_1344;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[7]; } Lights0_1345;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[7]; } record_36fake_1346;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[1]; } a_1347;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; SnLe32 dimension0; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[1]; } l_1348;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[4]; } eos_1349;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[7]; } Lights1_1350;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[7]; } record_37fake_1351;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[1]; } a_1352;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; SnLe32 dimension0; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[1]; } l_1353;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[4]; } eos_1354;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[7]; } Lights2_1355;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[7]; } record_38fake_1356;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[1]; } a_1357;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; SnLe32 dimension0; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[1]; } l_1358;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[4]; } eos_1359;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[7]; } Lights3_1360;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[7]; } record_39fake_1361;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[1]; } a_1362;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; SnLe32 dimension0; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[1]; } l_1363;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[4]; } eos_1364;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[7]; } Lights4_1365;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[7]; } record_40fake_1366;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[1]; } a_1367;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; SnLe32 dimension0; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[1]; } l_1368;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[4]; } eos_1369;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[7]; } Lights5_1370;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[7]; } record_41fake_1371;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[1]; } a_1372;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; SnLe32 dimension0; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[1]; } l_1373;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[4]; } eos_1374;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[7]; } Lights6_1375;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[7]; } record_42fake_1376;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[1]; } a_1377;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; SnLe32 dimension0; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[1]; } l_1378;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[4]; } eos_1379;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[7]; } Lights7_1380;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[7]; } record_43fake_1381;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; SnLe32 dimension0; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[1]; } l_1382;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[4]; } eos_1383;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[6]; } LookAt_1384;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[7]; } record_44fake_1385;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[1]; } h_1386;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; SnLe32 dimension0; u8 tagNameLength; u8 nameLength; char name[25]; } force_structure_alignment_1387;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[4]; } eos_1388;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[6]; } Hilite_1389;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[7]; } record_45fake_1390;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[3]; } cmd_1391;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[3]; } par_1392;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[3]; } len_1393;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[4]; } addr_1394;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[4]; } eos_1395;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[4]; } Gdma_1396;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[7]; } record_46fake_1397;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[3]; } cmd_1398;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[3]; } pad_1399;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[3]; } tri_1400;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[4]; } eos_1401;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[4]; } Gtri_1402;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[7]; } record_47fake_1403;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[3]; } cmd_1404;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[4]; } pad1_1405;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[4]; } pad2_1406;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[5]; } param_1407;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[4]; } eos_1408;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[7]; } Gpopmtx_1409;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[7]; } record_48fake_1410;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[3]; } cmd_1411;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[4]; } pad0_1412;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[8]; } mw_index_1413;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[6]; } number_1414;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[4]; } pad1_1415;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[4]; } base_1416;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[4]; } eos_1417;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[8]; } Gsegment_1418;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[7]; } record_49fake_1419;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[3]; } cmd_1420;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[4]; } pad0_1421;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[3]; } sft_1422;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[3]; } len_1423;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[4]; } data_1424;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[4]; } eos_1425;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[14]; } GsetothermodeL_1426;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[7]; } record_50fake_1427;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[3]; } cmd_1428;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[4]; } pad0_1429;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[3]; } sft_1430;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[3]; } len_1431;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[4]; } data_1432;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[4]; } eos_1433;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[14]; } GsetothermodeH_1434;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[7]; } record_51fake_1435;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[3]; } cmd_1436;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[8]; } lodscale_1437;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[4]; } tile_1438;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[2]; } on_1439;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[1]; } s_1440;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[1]; } t_1441;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[4]; } eos_1442;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[8]; } Gtexture_1443;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[7]; } record_52fake_1444;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[3]; } cmd_1445;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[3]; } pad_1446;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[4]; } line_1447;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[4]; } eos_1448;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[7]; } Gline3D_1449;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[7]; } record_53fake_1450;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[3]; } cmd_1451;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[4]; } pad1_1452;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[4]; } pad2_1453;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[5]; } scale_1454;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[4]; } eos_1455;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[10]; } Gperspnorm_1456;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[7]; } record_54fake_1457;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[3]; } cmd_1458;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[3]; } fmt_1459;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[3]; } siz_1460;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[3]; } pad_1461;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[2]; } wd_1462;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[4]; } dram_1463;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[4]; } eos_1464;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[7]; } Gsetimg_1465;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[7]; } record_55fake_1466;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[3]; } cmd_1467;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[5]; } muxs0_1468;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[5]; } muxs1_1469;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[4]; } eos_1470;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[11]; } Gsetcombine_1471;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[7]; } record_56fake_1472;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[3]; } cmd_1473;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[3]; } pad_1474;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[14]; } prim_min_level_1475;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[10]; } prim_level_1476;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[5]; } color_1477;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[4]; } eos_1478;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[9]; } Gsetcolor_1479;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[7]; } record_57fake_1480;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[3]; } cmd_1481;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[2]; } x0_1482;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[6]; } x0frac_1483;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[2]; } y0_1484;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[6]; } y0frac_1485;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[3]; } pad_1486;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[2]; } x1_1487;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[6]; } x1frac_1488;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[2]; } y1_1489;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[6]; } y1frac_1490;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[4]; } eos_1491;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[9]; } Gfillrect_1492;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[7]; } record_58fake_1493;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[3]; } cmd_1494;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[3]; } fmt_1495;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[3]; } siz_1496;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[4]; } pad0_1497;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[4]; } line_1498;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[4]; } tmem_1499;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[4]; } pad1_1500;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[4]; } tile_1501;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[7]; } palette_1502;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[2]; } ct_1503;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[2]; } mt_1504;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[5]; } maskt_1505;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[6]; } shiftt_1506;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[2]; } cs_1507;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[2]; } ms_1508;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[5]; } masks_1509;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[6]; } shifts_1510;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[4]; } eos_1511;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[8]; } Gsettile_1512;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[7]; } record_59fake_1513;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[3]; } cmd_1514;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[2]; } sl_1515;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[2]; } tl_1516;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[3]; } pad_1517;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[4]; } tile_1518;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[2]; } sh_1519;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[2]; } th_1520;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[4]; } eos_1521;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[9]; } Gloadtile_1522;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[10]; } Gloadblock_1523;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[12]; } Gsettilesize_1524;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[9]; } Gloadtlut_1525;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[7]; } record_60fake_1526;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[3]; } cmd_1527;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[2]; } xl_1528;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[2]; } yl_1529;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[4]; } pad1_1530;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[4]; } tile_1531;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[2]; } xh_1532;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[2]; } yh_1533;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[1]; } s_1534;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[1]; } t_1535;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[4]; } dsdx_1536;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[4]; } dtdy_1537;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[4]; } eos_1538;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[8]; } Gtexrect_1539;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[7]; } record_61fake_1540;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[2]; } w0_1541;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[2]; } w1_1542;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[2]; } w2_1543;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[2]; } w3_1544;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[4]; } eos_1545;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[7]; } TexRect_1546;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[7]; } record_62fake_1547;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[2]; } w0_1548;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[2]; } w1_1549;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[4]; } eos_1550;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[6]; } Gwords_1551;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[7]; } record_63fake_1552;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[5]; } words_1553;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[3]; } dma_1554;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[3]; } tri_1555;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[4]; } line_1556;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[6]; } popmtx_1557;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[7]; } segment_1558;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[13]; } setothermodeH_1559;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[13]; } setothermodeL_1560;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[7]; } texture_1561;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[9]; } perspnorm_1562;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[6]; } setimg_1563;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[10]; } setcombine_1564;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[8]; } setcolor_1565;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[8]; } fillrect_1566;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[7]; } settile_1567;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[8]; } loadtile_1568;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[11]; } settilesize_1569;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[8]; } loadtlut_1570;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[25]; } force_structure_alignment_1571;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[4]; } eos_1572;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[3]; } Gfx_1573;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[7]; } record_64fake_1574;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[3]; } cmd_1575;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[5]; } flags_1576;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[4]; } gain_1577;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[4]; } addr_1578;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[4]; } eos_1579;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[6]; } Aadpcm_1580;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[7]; } record_65fake_1581;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[3]; } cmd_1582;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[5]; } flags_1583;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[4]; } gain_1584;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[4]; } addr_1585;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[4]; } eos_1586;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[6]; } Apolef_1587;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[7]; } record_66fake_1588;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[3]; } cmd_1589;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[5]; } flags_1590;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[4]; } pad1_1591;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[4]; } addr_1592;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[4]; } eos_1593;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[9]; } Aenvelope_1594;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[7]; } record_67fake_1595;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[3]; } cmd_1596;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[4]; } pad1_1597;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[4]; } dmem_1598;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[4]; } pad2_1599;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[5]; } count_1600;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[4]; } eos_1601;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[10]; } Aclearbuff_1602;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[7]; } record_68fake_1603;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[3]; } cmd_1604;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[4]; } pad1_1605;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[4]; } pad2_1606;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[3]; } inL_1607;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[3]; } inR_1608;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[4]; } eos_1609;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[11]; } Ainterleave_1610;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[7]; } record_69fake_1611;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[3]; } cmd_1612;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[4]; } pad1_1613;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[4]; } addr_1614;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[4]; } eos_1615;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[9]; } Aloadbuff_1616;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[7]; } record_70fake_1617;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[3]; } cmd_1618;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[5]; } flags_1619;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[4]; } pad1_1620;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[4]; } addr_1621;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[4]; } eos_1622;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[9]; } Aenvmixer_1623;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[7]; } record_71fake_1624;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[3]; } cmd_1625;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[5]; } flags_1626;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[4]; } gain_1627;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[5]; } dmemi_1628;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[5]; } dmemo_1629;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[4]; } eos_1630;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[6]; } Amixer_1631;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[7]; } record_72fake_1632;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[3]; } cmd_1633;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[5]; } flags_1634;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[5]; } dmem2_1635;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[4]; } addr_1636;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[4]; } eos_1637;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[4]; } Apan_1638;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[7]; } record_73fake_1639;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[3]; } cmd_1640;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[5]; } flags_1641;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[5]; } pitch_1642;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[4]; } addr_1643;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[4]; } eos_1644;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[9]; } Aresample_1645;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[7]; } record_74fake_1646;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[3]; } cmd_1647;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[5]; } flags_1648;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[4]; } pad1_1649;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[4]; } addr_1650;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[4]; } eos_1651;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[7]; } Areverb_1652;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[7]; } record_75fake_1653;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[3]; } cmd_1654;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[4]; } pad1_1655;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[4]; } addr_1656;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[4]; } eos_1657;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[9]; } Asavebuff_1658;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[7]; } record_76fake_1659;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[3]; } cmd_1660;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[4]; } pad1_1661;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[4]; } pad2_1662;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[6]; } number_1663;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[4]; } base_1664;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[4]; } eos_1665;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[8]; } Asegment_1666;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[7]; } record_77fake_1667;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[3]; } cmd_1668;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[5]; } flags_1669;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[6]; } dmemin_1670;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[7]; } dmemout_1671;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[5]; } count_1672;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[4]; } eos_1673;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[8]; } Asetbuff_1674;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[7]; } record_78fake_1675;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[3]; } cmd_1676;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[5]; } flags_1677;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[3]; } vol_1678;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[6]; } voltgt_1679;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[7]; } volrate_1680;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[4]; } eos_1681;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[7]; } Asetvol_1682;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[7]; } record_79fake_1683;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[3]; } cmd_1684;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[4]; } pad1_1685;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[6]; } dmemin_1686;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[7]; } dmemout_1687;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[5]; } count_1688;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[4]; } eos_1689;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[9]; } Admemmove_1690;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[7]; } record_80fake_1691;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[3]; } cmd_1692;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[4]; } pad1_1693;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[5]; } count_1694;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[4]; } addr_1695;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[4]; } eos_1696;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[10]; } Aloadadpcm_1697;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[7]; } record_81fake_1698;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[3]; } cmd_1699;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[4]; } pad1_1700;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[4]; } pad2_1701;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[4]; } addr_1702;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[4]; } eos_1703;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[8]; } Asetloop_1704;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[7]; } record_82fake_1705;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[2]; } w0_1706;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[2]; } w1_1707;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[4]; } eos_1708;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[6]; } Awords_1709;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[7]; } record_83fake_1710;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[5]; } words_1711;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[5]; } adpcm_1712;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[5]; } polef_1713;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[9]; } clearbuff_1714;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[8]; } envelope_1715;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[10]; } interleave_1716;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[8]; } loadbuff_1717;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[8]; } envmixer_1718;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[8]; } resample_1719;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[6]; } reverb_1720;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[8]; } savebuff_1721;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[7]; } segment_1722;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[7]; } setbuff_1723;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[6]; } setvol_1724;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[8]; } dmemmove_1725;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[9]; } loadadpcm_1726;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[5]; } mixer_1727;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[7]; } setloop_1728;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[17]; } force_union_align_1729;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[4]; } eos_1730;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[4]; } Acmd_1731;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; SnLe32 dimension0; u8 tagNameLength; u8 nameLength; char name[11]; } ADPCM_STATE_1732;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; SnLe32 dimension0; u8 tagNameLength; u8 nameLength; char name[11]; } POLEF_STATE_1733;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; SnLe32 dimension0; u8 tagNameLength; u8 nameLength; char name[14]; } RESAMPLE_STATE_1734;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; SnLe32 dimension0; u8 tagNameLength; u8 nameLength; char name[12]; } ENVMIX_STATE_1735;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[11]; } ALMicroTime_1736;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[5]; } ALPan_1737;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[8]; } ALLink_s_1738;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[8]; u8 nameLength; char name[4]; } next_1739;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[8]; u8 nameLength; char name[4]; } prev_1740;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[8]; u8 nameLength; char name[4]; } eos_1741;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[8]; u8 nameLength; char name[6]; } ALLink_1742;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[9]; } ALDMAproc_1743;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[8]; } ALDMANew_1744;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[7]; } record_84fake_1745;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[4]; } base_1746;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[3]; } cur_1747;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[3]; } len_1748;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[5]; } count_1749;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[4]; } eos_1750;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[6]; } ALHeap_1751;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[6]; } ALFxId_1752;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[7]; } ALFxRef_1753;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[7]; } record_85fake_1754;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[13]; } AL_ADPCM_WAVE_1755;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[13]; } AL_RAW16_WAVE_1756;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[11]; } AL_RAX_WAVE_1757;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[4]; } eos_1758;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[7]; } record_86fake_1759;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[5]; } order_1760;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[11]; } npredictors_1761;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; SnLe32 dimension0; u8 tagNameLength; u8 nameLength; char name[4]; } book_1762;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[4]; } eos_1763;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[11]; } ALADPCMBook_1764;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[7]; } record_87fake_1765;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[5]; } start_1766;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[3]; } end_1767;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[5]; } count_1768;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; SnLe32 dimension0; u8 tagNameLength; u8 nameLength; char name[5]; } state_1769;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[4]; } eos_1770;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[11]; } ALADPCMloop_1771;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[7]; } record_88fake_1772;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[5]; } start_1773;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[3]; } end_1774;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[5]; } count_1775;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[4]; } eos_1776;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[9]; } ALRawLoop_1777;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[7]; } record_89fake_1778;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[5]; } start_1779;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[3]; } end_1780;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[5]; } count_1781;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[4]; } eos_1782;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[9]; } ALRaxLoop_1783;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[7]; } record_90fake_1784;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[10]; } attackTime_1785;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[9]; } decayTime_1786;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[11]; } releaseTime_1787;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[12]; } attackVolume_1788;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[11]; } decayVolume_1789;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[4]; } eos_1790;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[10]; } ALEnvelope_1791;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[7]; } record_91fake_1792;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[11]; } velocityMin_1793;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[11]; } velocityMax_1794;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[6]; } keyMin_1795;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[6]; } keyMax_1796;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[7]; } keyBase_1797;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[6]; } detune_1798;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[4]; } eos_1799;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[8]; } ALKeyMap_1800;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[7]; } record_92fake_1801;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[4]; } loop_1802;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[4]; } book_1803;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[4]; } eos_1804;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[15]; } ALADPCMWaveInfo_1805;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[7]; } record_93fake_1806;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[4]; } loop_1807;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[4]; } eos_1808;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[13]; } ALRAWWaveInfo_1809;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[7]; } record_94fake_1810;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[4]; } loop_1811;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[4]; } eos_1812;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[13]; } ALRaxWaveInfo_1813;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[7]; } record_95fake_1814;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[9]; } adpcmWave_1815;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[7]; } rawWave_1816;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[7]; } raxWave_1817;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[4]; } eos_1818;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[13]; } ALWaveTable_s_1819;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[4]; } base_1820;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[3]; } len_1821;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[4]; } type_1822;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[5]; } flags_1823;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[8]; } waveInfo_1824;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[13]; u8 nameLength; char name[4]; } eos_1825;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[13]; u8 nameLength; char name[11]; } ALWaveTable_1826;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[9]; } ALSound_s_1827;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[8]; } envelope_1828;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[6]; } keyMap_1829;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[13]; u8 nameLength; char name[9]; } wavetable_1830;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[9]; } samplePan_1831;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[12]; } sampleVolume_1832;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[5]; } flags_1833;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[9]; u8 nameLength; char name[4]; } eos_1834;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[9]; u8 nameLength; char name[7]; } ALSound_1835;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[7]; } record_96fake_1836;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[6]; } volume_1837;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[3]; } pan_1838;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[8]; } priority_1839;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[5]; } flags_1840;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[8]; } tremType_1841;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[8]; } tremRate_1842;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[9]; } tremDepth_1843;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[9]; } tremDelay_1844;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[7]; } vibType_1845;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[7]; } vibRate_1846;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[8]; } vibDepth_1847;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[8]; } vibDelay_1848;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[9]; } bendRange_1849;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[10]; } soundCount_1850;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; SnLe32 dimension0; u8 tagNameLength; char tagName[9]; u8 nameLength; char name[10]; } soundArray_1851;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[4]; } eos_1852;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[12]; } ALInstrument_1853;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[8]; } ALBank_s_1854;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[9]; } instCount_1855;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[5]; } flags_1856;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[3]; } pad_1857;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[10]; } sampleRate_1858;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[10]; } percussion_1859;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; SnLe32 dimension0; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[9]; } instArray_1860;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[8]; u8 nameLength; char name[4]; } eos_1861;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[8]; u8 nameLength; char name[6]; } ALBank_1862;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[7]; } record_97fake_1863;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[8]; } revision_1864;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[9]; } bankCount_1865;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; SnLe32 dimension0; u8 tagNameLength; char tagName[8]; u8 nameLength; char name[9]; } bankArray_1866;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[4]; } eos_1867;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[10]; } ALBankFile_1868;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[7]; } record_98fake_1869;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[6]; } offset_1870;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[3]; } len_1871;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[4]; } eos_1872;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[9]; } ALSeqData_1873;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[7]; } record_99fake_1874;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[8]; } revision_1875;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[8]; } seqCount_1876;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; SnLe32 dimension0; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[8]; } seqArray_1877;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[4]; } eos_1878;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[9]; } ALSeqFile_1879;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[14]; } ALVoiceHandler_1880;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[8]; } record_100fake_1881;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[10]; } maxVVoices_1882;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[10]; } maxPVoices_1883;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[10]; } maxUpdates_1884;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[11]; } maxFXbusses_1885;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[7]; } dmaproc_1886;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[4]; } heap_1887;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[10]; } outputRate_1888;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[6]; } fxType_1889;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[6]; } params_1890;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[8]; u8 nameLength; char name[4]; } eos_1891;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[8]; u8 nameLength; char name[11]; } ALSynConfig_1892;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[10]; } ALPlayer_s_1893;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[10]; u8 nameLength; char name[4]; } next_1894;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[10]; } clientData_1895;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[7]; } handler_1896;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[8]; } callTime_1897;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[11]; } samplesLeft_1898;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[10]; u8 nameLength; char name[4]; } eos_1899;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[10]; u8 nameLength; char name[8]; } ALPlayer_1900;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[9]; } ALVoice_s_1901;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[8]; u8 nameLength; char name[4]; } node_1902;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[8]; u8 nameLength; char name[6]; } pvoice_1903;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[13]; u8 nameLength; char name[5]; } table_1904;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[13]; } clientPrivate_1905;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[5]; } state_1906;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[8]; } priority_1907;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[5]; } fxBus_1908;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[10]; } unityPitch_1909;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[9]; u8 nameLength; char name[4]; } eos_1910;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[9]; u8 nameLength; char name[7]; } ALVoice_1911;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[15]; } ALVoiceConfig_s_1912;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[8]; } priority_1913;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[5]; } fxBus_1914;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[10]; } unityPitch_1915;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[15]; u8 nameLength; char name[4]; } eos_1916;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[15]; u8 nameLength; char name[13]; } ALVoiceConfig_1917;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[8]; } record_101fake_1918;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[10]; u8 nameLength; char name[4]; } head_1919;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[8]; u8 nameLength; char name[9]; } pFreeList_1920;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[8]; u8 nameLength; char name[10]; } pAllocList_1921;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[8]; u8 nameLength; char name[9]; } pLameList_1922;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[12]; } paramSamples_1923;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[10]; } curSamples_1924;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[3]; } dma_1925;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[4]; } heap_1926;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[9]; u8 nameLength; char name[9]; } paramList_1927;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[11]; u8 nameLength; char name[7]; } mainBus_1928;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[10]; u8 nameLength; char name[6]; } auxBus_1929;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[10]; u8 nameLength; char name[12]; } outputFilter_1930;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[10]; } numPVoices_1931;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[12]; } maxAuxBusses_1932;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[10]; } outputRate_1933;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[13]; } maxOutSamples_1934;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[8]; u8 nameLength; char name[4]; } eos_1935;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[8]; u8 nameLength; char name[7]; } ALSynth_1936;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[8]; } record_102fake_1937;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[8]; u8 nameLength; char name[4]; } drvr_1938;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[8]; u8 nameLength; char name[4]; } eos_1939;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[8]; u8 nameLength; char name[9]; } ALGlobals_1940;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[5]; } ALMsg_1941;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[14]; } AL_SEQ_REF_EVT_1942;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[15]; } AL_SEQ_MIDI_EVT_1943;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[16]; } AL_SEQP_MIDI_EVT_1944;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[12]; } AL_TEMPO_EVT_1945;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[14]; } AL_SEQ_END_EVT_1946;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[15]; } AL_NOTE_END_EVT_1947;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[15]; } AL_SEQP_ENV_EVT_1948;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[16]; } AL_SEQP_META_EVT_1949;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[16]; } AL_SEQP_PROG_EVT_1950;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[15]; } AL_SEQP_API_EVT_1951;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[15]; } AL_SEQP_VOL_EVT_1952;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[16]; } AL_SEQP_LOOP_EVT_1953;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[20]; } AL_SEQP_PRIORITY_EVT_1954;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[15]; } AL_SEQP_SEQ_EVT_1955;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[16]; } AL_SEQP_BANK_EVT_1956;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[16]; } AL_SEQP_PLAY_EVT_1957;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[16]; } AL_SEQP_STOP_EVT_1958;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[20]; } AL_SEQP_STOPPING_EVT_1959;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[12]; } AL_TRACK_END_1960;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[16]; } AL_CSP_LOOPSTART_1961;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[14]; } AL_CSP_LOOPEND_1962;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[18]; } AL_CSP_NOTEOFF_EVT_1963;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[15]; } AL_TREM_OSC_EVT_1964;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[14]; } AL_VIB_OSC_EVT_1965;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[5]; u8 nameLength; char name[4]; } eos_1966;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[13]; } AL_MIDIstatus_1967;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[19]; } AL_MIDI_ChannelMask_1968;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[18]; } AL_MIDI_StatusMask_1969;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[20]; } AL_MIDI_ChannelVoice_1970;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[15]; } AL_MIDI_NoteOff_1971;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[14]; } AL_MIDI_NoteOn_1972;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[23]; } AL_MIDI_PolyKeyPressure_1973;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[21]; } AL_MIDI_ControlChange_1974;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[25]; } AL_MIDI_ChannelModeSelect_1975;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[21]; } AL_MIDI_ProgramChange_1976;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[23]; } AL_MIDI_ChannelPressure_1977;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[23]; } AL_MIDI_PitchBendChange_1978;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[13]; } AL_MIDI_SysEx_1979;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[20]; } AL_MIDI_SystemCommon_1980;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[28]; } AL_MIDI_TimeCodeQuarterFrame_1981;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[27]; } AL_MIDI_SongPositionPointer_1982;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[18]; } AL_MIDI_SongSelect_1983;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[18]; } AL_MIDI_Undefined1_1984;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[18]; } AL_MIDI_Undefined2_1985;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[19]; } AL_MIDI_TuneRequest_1986;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[11]; } AL_MIDI_EOX_1987;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[22]; } AL_MIDI_SystemRealTime_1988;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[19]; } AL_MIDI_TimingClock_1989;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[18]; } AL_MIDI_Undefined3_1990;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[13]; } AL_MIDI_Start_1991;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[16]; } AL_MIDI_Continue_1992;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[12]; } AL_MIDI_Stop_1993;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[18]; } AL_MIDI_Undefined4_1994;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[21]; } AL_MIDI_ActiveSensing_1995;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[19]; } AL_MIDI_SystemReset_1996;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[12]; } AL_MIDI_Meta_1997;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[13]; u8 nameLength; char name[4]; } eos_1998;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[11]; } AL_MIDIctrl_1999;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[19]; } AL_MIDI_VOLUME_CTRL_2000;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[16]; } AL_MIDI_PAN_CTRL_2001;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[21]; } AL_MIDI_PRIORITY_CTRL_2002;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[17]; } AL_MIDI_FX_CTRL_0_2003;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[17]; } AL_MIDI_FX_CTRL_1_2004;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[17]; } AL_MIDI_FX_CTRL_2_2005;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[17]; } AL_MIDI_FX_CTRL_3_2006;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[17]; } AL_MIDI_FX_CTRL_4_2007;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[17]; } AL_MIDI_FX_CTRL_5_2008;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[17]; } AL_MIDI_FX_CTRL_6_2009;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[17]; } AL_MIDI_FX_CTRL_7_2010;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[17]; } AL_MIDI_FX_CTRL_8_2011;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[17]; } AL_MIDI_FX_CTRL_9_2012;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[20]; } AL_MIDI_SUSTAIN_CTRL_2013;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[16]; } AL_MIDI_FX1_CTRL_2014;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[16]; } AL_MIDI_FX3_CTRL_2015;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[11]; u8 nameLength; char name[4]; } eos_2016;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[11]; } AL_MIDImeta_2017;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[18]; } AL_MIDI_META_TEMPO_2018;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[16]; } AL_MIDI_META_EOT_2019;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[11]; u8 nameLength; char name[4]; } eos_2020;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[8]; } record_103fake_2021;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[6]; } curPtr_2022;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[9]; } lastTicks_2023;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[8]; } curTicks_2024;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[10]; } lastStatus_2025;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[8]; u8 nameLength; char name[4]; } eos_2026;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[8]; u8 nameLength; char name[11]; } ALSeqMarker_2027;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[8]; } record_104fake_2028;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[5]; } ticks_2029;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[6]; } status_2030;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[5]; } byte1_2031;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[5]; } byte2_2032;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[8]; } duration_2033;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[8]; u8 nameLength; char name[4]; } eos_2034;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[8]; u8 nameLength; char name[11]; } ALMIDIEvent_2035;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[8]; } record_105fake_2036;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[5]; } ticks_2037;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[6]; } status_2038;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[4]; } type_2039;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[3]; } len_2040;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[5]; } byte1_2041;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[5]; } byte2_2042;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[5]; } byte3_2043;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[8]; u8 nameLength; char name[4]; } eos_2044;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[8]; u8 nameLength; char name[12]; } ALTempoEvent_2045;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[8]; } record_106fake_2046;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[5]; } ticks_2047;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[6]; } status_2048;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[4]; } type_2049;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[3]; } len_2050;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[8]; u8 nameLength; char name[4]; } eos_2051;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[8]; u8 nameLength; char name[10]; } ALEndEvent_2052;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[8]; } record_107fake_2053;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[9]; u8 nameLength; char name[5]; } voice_2054;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[8]; u8 nameLength; char name[4]; } eos_2055;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[8]; u8 nameLength; char name[11]; } ALNoteEvent_2056;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[8]; } record_108fake_2057;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[9]; u8 nameLength; char name[5]; } voice_2058;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[5]; } delta_2059;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[3]; } vol_2060;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[8]; u8 nameLength; char name[4]; } eos_2061;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[8]; u8 nameLength; char name[13]; } ALVolumeEvent_2062;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[8]; } record_109fake_2063;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[3]; } vol_2064;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[8]; u8 nameLength; char name[4]; } eos_2065;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[8]; u8 nameLength; char name[14]; } ALSeqpVolEvent_2066;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[8]; } record_110fake_2067;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[8]; u8 nameLength; char name[5]; } start_2068;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[8]; u8 nameLength; char name[3]; } end_2069;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[5]; } count_2070;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[8]; u8 nameLength; char name[4]; } eos_2071;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[8]; u8 nameLength; char name[15]; } ALSeqpLoopEvent_2072;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[8]; } record_111fake_2073;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[4]; } chan_2074;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[8]; } priority_2075;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[8]; u8 nameLength; char name[4]; } eos_2076;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[8]; u8 nameLength; char name[19]; } ALSeqpPriorityEvent_2077;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[8]; } record_112fake_2078;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[3]; } seq_2079;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[8]; u8 nameLength; char name[4]; } eos_2080;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[8]; u8 nameLength; char name[14]; } ALSeqpSeqEvent_2081;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[8]; } record_113fake_2082;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[8]; u8 nameLength; char name[4]; } bank_2083;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[8]; u8 nameLength; char name[4]; } eos_2084;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[8]; u8 nameLength; char name[15]; } ALSeqpBankEvent_2085;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[8]; } record_114fake_2086;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[14]; u8 nameLength; char name[2]; } vs_2087;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[8]; } oscState_2088;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[4]; } chan_2089;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[8]; u8 nameLength; char name[4]; } eos_2090;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[8]; u8 nameLength; char name[10]; } ALOscEvent_2091;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[8]; } record_115fake_2092;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[8]; u8 nameLength; char name[4]; } midi_2093;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[8]; u8 nameLength; char name[5]; } tempo_2094;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[8]; u8 nameLength; char name[3]; } end_2095;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[8]; u8 nameLength; char name[4]; } note_2096;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[8]; u8 nameLength; char name[3]; } vol_2097;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[8]; u8 nameLength; char name[4]; } loop_2098;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[8]; u8 nameLength; char name[5]; } spvol_2099;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[8]; u8 nameLength; char name[10]; } sppriority_2100;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[8]; u8 nameLength; char name[5]; } spseq_2101;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[8]; u8 nameLength; char name[6]; } spbank_2102;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[8]; u8 nameLength; char name[3]; } osc_2103;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[8]; u8 nameLength; char name[4]; } eos_2104;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[8]; } record_116fake_2105;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[4]; } type_2106;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[8]; u8 nameLength; char name[3]; } msg_2107;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[8]; u8 nameLength; char name[4]; } eos_2108;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[8]; u8 nameLength; char name[7]; } ALEvent_2109;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[8]; } record_117fake_2110;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[8]; u8 nameLength; char name[4]; } node_2111;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[5]; } delta_2112;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[8]; u8 nameLength; char name[3]; } evt_2113;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[8]; u8 nameLength; char name[4]; } eos_2114;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[8]; u8 nameLength; char name[15]; } ALEventListItem_2115;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[8]; } record_118fake_2116;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[8]; u8 nameLength; char name[8]; } freeList_2117;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[8]; u8 nameLength; char name[9]; } allocList_2118;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[10]; } eventCount_2119;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[8]; u8 nameLength; char name[4]; } eos_2120;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[8]; u8 nameLength; char name[12]; } ALEventQueue_2121;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[14]; } ALVoiceState_s_2122;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[14]; u8 nameLength; char name[4]; } next_2123;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[9]; u8 nameLength; char name[5]; } voice_2124;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[9]; u8 nameLength; char name[5]; } sound_2125;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[10]; } envEndTime_2126;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[5]; } pitch_2127;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[7]; } vibrato_2128;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[7]; } envGain_2129;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[7]; } channel_2130;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[3]; } key_2131;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[8]; } velocity_2132;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[8]; } envPhase_2133;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[5]; } phase_2134;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[7]; } tremelo_2135;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[5]; } flags_2136;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[14]; u8 nameLength; char name[4]; } eos_2137;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[14]; u8 nameLength; char name[12]; } ALVoiceState_2138;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[8]; } record_119fake_2139;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[10]; } instrument_2140;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[9]; } bendRange_2141;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[4]; } fxId_2142;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[3]; } pan_2143;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[8]; } priority_2144;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[3]; } vol_2145;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[5]; } fxmix_2146;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[7]; } sustain_2147;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[9]; } pitchBend_2148;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[8]; u8 nameLength; char name[4]; } eos_2149;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[8]; u8 nameLength; char name[11]; } ALChanState_2150;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[7]; } ALSeq_s_2151;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[4]; } base_2152;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[10]; } trackStart_2153;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[6]; } curPtr_2154;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[9]; } lastTicks_2155;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[3]; } len_2156;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[4]; } qnpt_2157;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[8]; } division_2158;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[10]; } lastStatus_2159;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[4]; } eos_2160;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[5]; } ALSeq_2161;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[8]; } record_120fake_2162;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; SnLe32 dimension0; u8 tagNameLength; u8 nameLength; char name[11]; } trackOffset_2163;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[8]; } division_2164;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[8]; u8 nameLength; char name[4]; } eos_2165;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[8]; u8 nameLength; char name[10]; } ALCMidiHdr_2166;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[8]; } ALCSeq_s_2167;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[8]; u8 nameLength; char name[4]; } base_2168;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[11]; } validTracks_2169;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[4]; } qnpt_2170;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[9]; } lastTicks_2171;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[14]; } lastDeltaTicks_2172;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[9]; } deltaFlag_2173;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; SnLe32 dimension0; u8 tagNameLength; u8 nameLength; char name[6]; } curLoc_2174;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; SnLe32 dimension0; u8 tagNameLength; u8 nameLength; char name[8]; } curBUPtr_2175;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; SnLe32 dimension0; u8 tagNameLength; u8 nameLength; char name[8]; } curBULen_2176;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; SnLe32 dimension0; u8 tagNameLength; u8 nameLength; char name[10]; } lastStatus_2177;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; SnLe32 dimension0; u8 tagNameLength; u8 nameLength; char name[13]; } evtDeltaTicks_2178;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[8]; u8 nameLength; char name[4]; } eos_2179;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[8]; u8 nameLength; char name[6]; } ALCSeq_2180;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[8]; } record_121fake_2181;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[11]; } validTracks_2182;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[9]; } lastTicks_2183;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[14]; } lastDeltaTicks_2184;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; SnLe32 dimension0; u8 tagNameLength; u8 nameLength; char name[6]; } curLoc_2185;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; SnLe32 dimension0; u8 tagNameLength; u8 nameLength; char name[8]; } curBUPtr_2186;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; SnLe32 dimension0; u8 tagNameLength; u8 nameLength; char name[8]; } curBULen_2187;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; SnLe32 dimension0; u8 tagNameLength; u8 nameLength; char name[10]; } lastStatus_2188;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; SnLe32 dimension0; u8 tagNameLength; u8 nameLength; char name[13]; } evtDeltaTicks_2189;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[8]; u8 nameLength; char name[4]; } eos_2190;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[8]; u8 nameLength; char name[12]; } ALCSeqMarker_2191;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[8]; } record_122fake_2192;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[9]; } maxVoices_2193;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[9]; } maxEvents_2194;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[11]; } maxChannels_2195;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[10]; } debugFlags_2196;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[4]; } heap_2197;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[7]; } initOsc_2198;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[9]; } updateOsc_2199;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[7]; } stopOsc_2200;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[8]; u8 nameLength; char name[4]; } eos_2201;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[8]; u8 nameLength; char name[12]; } ALSeqpConfig_2202;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[9]; } ALOscInit_2203;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[11]; } ALOscUpdate_2204;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[9]; } ALOscStop_2205;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[8]; } record_123fake_2206;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[10]; u8 nameLength; char name[4]; } node_2207;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[8]; u8 nameLength; char name[4]; } drvr_2208;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[6]; } target_2209;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[7]; } curTime_2210;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[8]; u8 nameLength; char name[4]; } bank_2211;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[4]; } uspt_2212;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[9]; } nextDelta_2213;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[5]; } state_2214;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[8]; } chanMask_2215;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[3]; } vol_2216;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[11]; } maxChannels_2217;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[10]; } debugFlags_2218;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[8]; u8 nameLength; char name[9]; } nextEvent_2219;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[8]; u8 nameLength; char name[4]; } evtq_2220;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[9]; } frameTime_2221;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[8]; u8 nameLength; char name[9]; } chanState_2222;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[14]; u8 nameLength; char name[10]; } vAllocHead_2223;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[14]; u8 nameLength; char name[10]; } vAllocTail_2224;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[14]; u8 nameLength; char name[9]; } vFreeList_2225;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[7]; } initOsc_2226;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[9]; } updateOsc_2227;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[7]; } stopOsc_2228;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[8]; u8 nameLength; char name[9]; } loopStart_2229;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[8]; u8 nameLength; char name[7]; } loopEnd_2230;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[9]; } loopCount_2231;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[8]; u8 nameLength; char name[4]; } eos_2232;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[8]; u8 nameLength; char name[11]; } ALSeqPlayer_2233;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[8]; } record_124fake_2234;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[10]; u8 nameLength; char name[4]; } node_2235;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[8]; u8 nameLength; char name[4]; } drvr_2236;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[8]; u8 nameLength; char name[6]; } target_2237;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[7]; } curTime_2238;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[8]; u8 nameLength; char name[4]; } bank_2239;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[4]; } uspt_2240;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[9]; } nextDelta_2241;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[5]; } state_2242;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[8]; } chanMask_2243;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[3]; } vol_2244;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[11]; } maxChannels_2245;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[10]; } debugFlags_2246;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[8]; u8 nameLength; char name[9]; } nextEvent_2247;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[8]; u8 nameLength; char name[4]; } evtq_2248;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[9]; } frameTime_2249;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[8]; u8 nameLength; char name[9]; } chanState_2250;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[14]; u8 nameLength; char name[10]; } vAllocHead_2251;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[14]; u8 nameLength; char name[10]; } vAllocTail_2252;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[14]; u8 nameLength; char name[9]; } vFreeList_2253;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[7]; } initOsc_2254;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[9]; } updateOsc_2255;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[7]; } stopOsc_2256;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[8]; u8 nameLength; char name[4]; } eos_2257;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[8]; u8 nameLength; char name[10]; } ALCSPlayer_2258;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[8]; } record_125fake_2259;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[9]; } maxSounds_2260;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[9]; } maxEvents_2261;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[4]; } heap_2262;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[8]; u8 nameLength; char name[4]; } eos_2263;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[8]; u8 nameLength; char name[12]; } ALSndpConfig_2264;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[8]; } record_126fake_2265;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[10]; u8 nameLength; char name[4]; } node_2266;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[8]; u8 nameLength; char name[4]; } evtq_2267;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[8]; u8 nameLength; char name[9]; } nextEvent_2268;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[8]; u8 nameLength; char name[4]; } drvr_2269;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[6]; } target_2270;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[8]; } sndState_2271;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[9]; } maxSounds_2272;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[9]; } frameTime_2273;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[9]; } nextDelta_2274;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[7]; } curTime_2275;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[8]; u8 nameLength; char name[4]; } eos_2276;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[8]; u8 nameLength; char name[11]; } ALSndPlayer_2277;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[7]; } ALSndId_2278;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[8]; } record_127fake_2279;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[4]; } base_2280;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[3]; } fmt_2281;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[3]; } siz_2282;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[5]; } xsize_2283;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[5]; } ysize_2284;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[5]; } lsize_2285;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[4]; } addr_2286;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[1]; } w_2287;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[1]; } h_2288;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[1]; } s_2289;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[1]; } t_2290;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[8]; u8 nameLength; char name[4]; } eos_2291;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[8]; u8 nameLength; char name[5]; } Image_2292;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[8]; } record_128fake_2293;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; SnLe32 dimension0; u8 tagNameLength; u8 nameLength; char name[3]; } col_2294;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; SnLe32 dimension0; u8 tagNameLength; u8 nameLength; char name[3]; } pos_2295;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[2]; } a1_2296;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[2]; } a2_2297;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[8]; u8 nameLength; char name[4]; } eos_2298;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[8]; u8 nameLength; char name[15]; } PositionalLight_2299;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[8]; } record_129fake_2300;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[8]; } dataSize_2301;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[6]; } dlType_2302;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[5]; } flags_2303;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[5]; } paddr_2304;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[8]; u8 nameLength; char name[4]; } eos_2305;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[8]; u8 nameLength; char name[11]; } guDLPrintCB_2306;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[8]; } record_130fake_2307;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[4]; } type_2308;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[6]; } length_2309;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[5]; } magic_2310;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; SnLe32 dimension0; u8 tagNameLength; u8 nameLength; char name[8]; } userdata_2311;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[8]; u8 nameLength; char name[4]; } eos_2312;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[8]; u8 nameLength; char name[12]; } RamRomBuffer_2313;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[6]; } bitmap_2314;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[5]; } width_2315;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[9]; } width_img_2316;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[1]; } s_2317;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[1]; } t_2318;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[3]; } buf_2319;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[12]; } actualHeight_2320;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[9]; } LUToffset_2321;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[6]; u8 nameLength; char name[4]; } eos_2322;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[6]; u8 nameLength; char name[6]; } Bitmap_2323;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[6]; } sprite_2324;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[1]; } x_2325;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[1]; } y_2326;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[5]; } width_2327;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[6]; } height_2328;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[6]; } scalex_2329;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[6]; } scaley_2330;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[4]; } expx_2331;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[4]; } expy_2332;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[4]; } attr_2333;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[6]; } zdepth_2334;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[3]; } red_2335;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[5]; } green_2336;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[4]; } blue_2337;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[5]; } alpha_2338;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[9]; } startTLUT_2339;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[5]; } nTLUT_2340;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[3]; } LUT_2341;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[6]; } istart_2342;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[5]; } istep_2343;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[8]; } nbitmaps_2344;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[9]; } ndisplist_2345;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[8]; } bmheight_2346;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[7]; } bmHreal_2347;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[5]; } bmfmt_2348;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[5]; } bmsiz_2349;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[6]; u8 nameLength; char name[6]; } bitmap_2350;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[6]; } rsp_dl_2351;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[11]; } rsp_dl_next_2352;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[6]; } frac_s_2353;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[6]; } frac_t_2354;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[6]; u8 nameLength; char name[4]; } eos_2355;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[6]; u8 nameLength; char name[6]; } Sprite_2356;
    u8 incompleteRecord[24];
} g_DebugStreamHalfwords1 __attribute__((aligned(2))) = {
    { SN_LE32(0), 0x94, SN_LE16(15), SN_LE16(10), SN_LE32(4), 19, "SFX_CHICKEN_IDLEequ" },
    { SN_LE32(6400), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 16, "SFX_CHICKEN_IDLE" },
    { SN_LE32(4), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(4), SN_LE16(0), 19, "SFX_CHICKEN_IDLEequ", 4, ".eos" },
    { SN_LE32(0), 0x94, SN_LE16(15), SN_LE16(10), SN_LE32(4), 21, "SFX_CHICKEN_FLINCHequ" },
    { SN_LE32(6405), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 18, "SFX_CHICKEN_FLINCH" },
    { SN_LE32(4), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(4), SN_LE16(0), 21, "SFX_CHICKEN_FLINCHequ", 4, ".eos" },
    { SN_LE32(0), 0x94, SN_LE16(15), SN_LE16(10), SN_LE32(4), 21, "SFX_CHICKEN_EFFORTequ" },
    { SN_LE32(6410), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 18, "SFX_CHICKEN_EFFORT" },
    { SN_LE32(4), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(4), SN_LE16(0), 21, "SFX_CHICKEN_EFFORTequ", 4, ".eos" },
    { SN_LE32(0), 0x94, SN_LE16(15), SN_LE16(10), SN_LE32(4), 20, "SFX_CHICKEN_DEATHequ" },
    { SN_LE32(6415), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 17, "SFX_CHICKEN_DEATH" },
    { SN_LE32(4), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(4), SN_LE16(0), 20, "SFX_CHICKEN_DEATHequ", 4, ".eos" },
    { SN_LE32(0), 0x94, SN_LE16(15), SN_LE16(10), SN_LE32(4), 26, "SFX_CHICKEN_TRANSFORMEDequ" },
    { SN_LE32(6420), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 23, "SFX_CHICKEN_TRANSFORMED" },
    { SN_LE32(4), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(4), SN_LE16(0), 26, "SFX_CHICKEN_TRANSFORMEDequ", 4, ".eos" },
    { SN_LE32(0), 0x94, SN_LE16(15), SN_LE16(10), SN_LE32(4), 33, "SFX_CHICKEN_TRANSFORMED_FLINCHequ" },
    { SN_LE32(6425), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 30, "SFX_CHICKEN_TRANSFORMED_FLINCH" },
    { SN_LE32(4), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(4), SN_LE16(0), 33, "SFX_CHICKEN_TRANSFORMED_FLINCHequ", 4, ".eos" },
    { SN_LE32(0), 0x94, SN_LE16(15), SN_LE16(10), SN_LE32(4), 33, "SFX_CHICKEN_TRANSFORMED_ATTACKequ" },
    { SN_LE32(6430), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 30, "SFX_CHICKEN_TRANSFORMED_ATTACK" },
    { SN_LE32(4), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(4), SN_LE16(0), 33, "SFX_CHICKEN_TRANSFORMED_ATTACKequ", 4, ".eos" },
    { SN_LE32(0), 0x94, SN_LE16(15), SN_LE16(10), SN_LE32(4), 31, "SFX_CHICKEN_TRANSFORMED_IDLEequ" },
    { SN_LE32(6435), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 28, "SFX_CHICKEN_TRANSFORMED_IDLE" },
    { SN_LE32(4), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(4), SN_LE16(0), 31, "SFX_CHICKEN_TRANSFORMED_IDLEequ", 4, ".eos" },
    { SN_LE32(0), 0x94, SN_LE16(15), SN_LE16(10), SN_LE32(4), 17, "SFX_COMPY_IDLEequ" },
    { SN_LE32(6500), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 14, "SFX_COMPY_IDLE" },
    { SN_LE32(4), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(4), SN_LE16(0), 17, "SFX_COMPY_IDLEequ", 4, ".eos" },
    { SN_LE32(0), 0x94, SN_LE16(15), SN_LE16(10), SN_LE32(4), 19, "SFX_COMPY_FLINCHequ" },
    { SN_LE32(6505), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 16, "SFX_COMPY_FLINCH" },
    { SN_LE32(4), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(4), SN_LE16(0), 19, "SFX_COMPY_FLINCHequ", 4, ".eos" },
    { SN_LE32(0), 0x94, SN_LE16(15), SN_LE16(10), SN_LE32(4), 19, "SFX_COMPY_EFFORTequ" },
    { SN_LE32(6510), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 16, "SFX_COMPY_EFFORT" },
    { SN_LE32(4), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(4), SN_LE16(0), 19, "SFX_COMPY_EFFORTequ", 4, ".eos" },
    { SN_LE32(0), 0x94, SN_LE16(15), SN_LE16(10), SN_LE32(4), 18, "SFX_COMPY_DEATHequ" },
    { SN_LE32(6515), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 15, "SFX_COMPY_DEATH" },
    { SN_LE32(4), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(4), SN_LE16(0), 18, "SFX_COMPY_DEATHequ", 4, ".eos" },
    { SN_LE32(0), 0x94, SN_LE16(15), SN_LE16(10), SN_LE32(4), 24, "SFX_COMPY_TRANSFORMEDequ" },
    { SN_LE32(6520), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 21, "SFX_COMPY_TRANSFORMED" },
    { SN_LE32(4), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(4), SN_LE16(0), 24, "SFX_COMPY_TRANSFORMEDequ", 4, ".eos" },
    { SN_LE32(0), 0x94, SN_LE16(15), SN_LE16(10), SN_LE32(4), 31, "SFX_COMPY_TRANSFORMED_FLINCHequ" },
    { SN_LE32(6525), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 28, "SFX_COMPY_TRANSFORMED_FLINCH" },
    { SN_LE32(4), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(4), SN_LE16(0), 31, "SFX_COMPY_TRANSFORMED_FLINCHequ", 4, ".eos" },
    { SN_LE32(0), 0x94, SN_LE16(15), SN_LE16(10), SN_LE32(4), 31, "SFX_COMPY_TRANSFORMED_ATTACKequ" },
    { SN_LE32(6530), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 28, "SFX_COMPY_TRANSFORMED_ATTACK" },
    { SN_LE32(4), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(4), SN_LE16(0), 31, "SFX_COMPY_TRANSFORMED_ATTACKequ", 4, ".eos" },
    { SN_LE32(0), 0x94, SN_LE16(15), SN_LE16(10), SN_LE32(4), 29, "SFX_COMPY_TRANSFORMED_IDLEequ" },
    { SN_LE32(6535), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 26, "SFX_COMPY_TRANSFORMED_IDLE" },
    { SN_LE32(4), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(4), SN_LE16(0), 29, "SFX_COMPY_TRANSFORMED_IDLEequ", 4, ".eos" },
    { SN_LE32(0), 0x94, SN_LE16(15), SN_LE16(10), SN_LE32(4), 35, "SFX_BOSS_1_EXTENDED_FIRE_WAR_CRYequ" },
    { SN_LE32(6600), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 32, "SFX_BOSS_1_EXTENDED_FIRE_WAR_CRY" },
    { SN_LE32(4), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(4), SN_LE16(0), 35, "SFX_BOSS_1_EXTENDED_FIRE_WAR_CRYequ", 4, ".eos" },
    { SN_LE32(0), 0x94, SN_LE16(15), SN_LE16(10), SN_LE32(4), 20, "SFX_BOSS_1_FLINCHequ" },
    { SN_LE32(6605), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 17, "SFX_BOSS_1_FLINCH" },
    { SN_LE32(4), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(4), SN_LE16(0), 20, "SFX_BOSS_1_FLINCHequ", 4, ".eos" },
    { SN_LE32(0), 0x94, SN_LE16(15), SN_LE16(10), SN_LE32(4), 20, "SFX_BOSS_1_EFFORTequ" },
    { SN_LE32(6610), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 17, "SFX_BOSS_1_EFFORT" },
    { SN_LE32(4), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(4), SN_LE16(0), 20, "SFX_BOSS_1_EFFORTequ", 4, ".eos" },
    { SN_LE32(0), 0x94, SN_LE16(15), SN_LE16(10), SN_LE32(4), 19, "SFX_BOSS_1_DEATHequ" },
    { SN_LE32(6615), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 16, "SFX_BOSS_1_DEATH" },
    { SN_LE32(4), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(4), SN_LE16(0), 19, "SFX_BOSS_1_DEATHequ", 4, ".eos" },
    { SN_LE32(0), 0x94, SN_LE16(15), SN_LE16(10), SN_LE32(4), 20, "SFX_BOSS_1_SCREAMequ" },
    { SN_LE32(6620), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 17, "SFX_BOSS_1_SCREAM" },
    { SN_LE32(4), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(4), SN_LE16(0), 20, "SFX_BOSS_1_SCREAMequ", 4, ".eos" },
    { SN_LE32(0), 0x94, SN_LE16(15), SN_LE16(10), SN_LE32(4), 18, "SFX_BOSS_1_FALLequ" },
    { SN_LE32(6625), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 15, "SFX_BOSS_1_FALL" },
    { SN_LE32(4), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(4), SN_LE16(0), 18, "SFX_BOSS_1_FALLequ", 4, ".eos" },
    { SN_LE32(0), 0x94, SN_LE16(15), SN_LE16(10), SN_LE32(4), 21, "SFX_BOSS_1_VICTORYequ" },
    { SN_LE32(6630), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 18, "SFX_BOSS_1_VICTORY" },
    { SN_LE32(4), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(4), SN_LE16(0), 21, "SFX_BOSS_1_VICTORYequ", 4, ".eos" },
    { SN_LE32(0), 0x94, SN_LE16(15), SN_LE16(10), SN_LE32(4), 25, "SFX_BOSS_1_STICKY_BOMBequ" },
    { SN_LE32(6635), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 22, "SFX_BOSS_1_STICKY_BOMB" },
    { SN_LE32(4), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(4), SN_LE16(0), 25, "SFX_BOSS_1_STICKY_BOMBequ", 4, ".eos" },
    { SN_LE32(0), 0x94, SN_LE16(15), SN_LE16(10), SN_LE32(4), 19, "SFX_BOSS_1_LAUGHequ" },
    { SN_LE32(6640), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 16, "SFX_BOSS_1_LAUGH" },
    { SN_LE32(4), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(4), SN_LE16(0), 19, "SFX_BOSS_1_LAUGHequ", 4, ".eos" },
    { SN_LE32(0), 0x94, SN_LE16(15), SN_LE16(10), SN_LE32(4), 31, "SFX_BOSS_1_RADIOACTIVE_PANICequ" },
    { SN_LE32(6645), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 28, "SFX_BOSS_1_RADIOACTIVE_PANIC" },
    { SN_LE32(4), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(4), SN_LE16(0), 31, "SFX_BOSS_1_RADIOACTIVE_PANICequ", 4, ".eos" },
    { SN_LE32(0), 0x94, SN_LE16(15), SN_LE16(10), SN_LE32(4), 19, "SFX_BOSS_1_TAUNTequ" },
    { SN_LE32(6650), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 16, "SFX_BOSS_1_TAUNT" },
    { SN_LE32(4), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(4), SN_LE16(0), 19, "SFX_BOSS_1_TAUNTequ", 4, ".eos" },
    { SN_LE32(0), 0x94, SN_LE16(15), SN_LE16(10), SN_LE32(4), 26, "SFX_BOSS_1_CAPTURE_FLAGequ" },
    { SN_LE32(6655), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 23, "SFX_BOSS_1_CAPTURE_FLAG" },
    { SN_LE32(4), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(4), SN_LE16(0), 26, "SFX_BOSS_1_CAPTURE_FLAGequ", 4, ".eos" },
    { SN_LE32(0), 0x94, SN_LE16(15), SN_LE16(10), SN_LE32(4), 34, "SFX_BOSS_1_DAMAGED_HOLDING_FLAGequ" },
    { SN_LE32(6660), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 31, "SFX_BOSS_1_DAMAGED_HOLDING_FLAG" },
    { SN_LE32(4), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(4), SN_LE16(0), 34, "SFX_BOSS_1_DAMAGED_HOLDING_FLAGequ", 4, ".eos" },
    { SN_LE32(0), 0x94, SN_LE16(15), SN_LE16(10), SN_LE32(4), 26, "SFX_BOSS_1_PLANTED_FLAGequ" },
    { SN_LE32(6665), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 23, "SFX_BOSS_1_PLANTED_FLAG" },
    { SN_LE32(4), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(4), SN_LE16(0), 26, "SFX_BOSS_1_PLANTED_FLAGequ", 4, ".eos" },
    { SN_LE32(0), 0x94, SN_LE16(15), SN_LE16(10), SN_LE32(4), 24, "SFX_BOSS_1_SEE_PLAYERequ" },
    { SN_LE32(6670), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 21, "SFX_BOSS_1_SEE_PLAYER" },
    { SN_LE32(4), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(4), SN_LE16(0), 24, "SFX_BOSS_1_SEE_PLAYERequ", 4, ".eos" },
    { SN_LE32(0), 0x94, SN_LE16(15), SN_LE16(10), SN_LE32(4), 28, "SFX_BOSS_1_HEAR_SOMETHINGequ" },
    { SN_LE32(6675), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 25, "SFX_BOSS_1_HEAR_SOMETHING" },
    { SN_LE32(4), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(4), SN_LE16(0), 28, "SFX_BOSS_1_HEAR_SOMETHINGequ", 4, ".eos" },
    { SN_LE32(0), 0x94, SN_LE16(15), SN_LE16(10), SN_LE32(4), 29, "SFX_BOSS_1_SMELL_SOMETHINGequ" },
    { SN_LE32(6680), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 26, "SFX_BOSS_1_SMELL_SOMETHING" },
    { SN_LE32(4), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(4), SN_LE16(0), 29, "SFX_BOSS_1_SMELL_SOMETHINGequ", 4, ".eos" },
    { SN_LE32(0), 0x94, SN_LE16(15), SN_LE16(10), SN_LE32(4), 27, "SFX_BOSS_1_KILL_FRIENDLYequ" },
    { SN_LE32(6685), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 24, "SFX_BOSS_1_KILL_FRIENDLY" },
    { SN_LE32(4), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(4), SN_LE16(0), 27, "SFX_BOSS_1_KILL_FRIENDLYequ", 4, ".eos" },
    { SN_LE32(0), 0x94, SN_LE16(15), SN_LE16(10), SN_LE32(4), 35, "SFX_BOSS_2_EXTENDED_FIRE_WAR_CRYequ" },
    { SN_LE32(6700), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 32, "SFX_BOSS_2_EXTENDED_FIRE_WAR_CRY" },
    { SN_LE32(4), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(4), SN_LE16(0), 35, "SFX_BOSS_2_EXTENDED_FIRE_WAR_CRYequ", 4, ".eos" },
    { SN_LE32(0), 0x94, SN_LE16(15), SN_LE16(10), SN_LE32(4), 20, "SFX_BOSS_2_FLINCHequ" },
    { SN_LE32(6705), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 17, "SFX_BOSS_2_FLINCH" },
    { SN_LE32(4), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(4), SN_LE16(0), 20, "SFX_BOSS_2_FLINCHequ", 4, ".eos" },
    { SN_LE32(0), 0x94, SN_LE16(15), SN_LE16(10), SN_LE32(4), 20, "SFX_BOSS_2_EFFORTequ" },
    { SN_LE32(6710), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 17, "SFX_BOSS_2_EFFORT" },
    { SN_LE32(4), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(4), SN_LE16(0), 20, "SFX_BOSS_2_EFFORTequ", 4, ".eos" },
    { SN_LE32(0), 0x94, SN_LE16(15), SN_LE16(10), SN_LE32(4), 19, "SFX_BOSS_2_DEATHequ" },
    { SN_LE32(6715), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 16, "SFX_BOSS_2_DEATH" },
    { SN_LE32(4), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(4), SN_LE16(0), 19, "SFX_BOSS_2_DEATHequ", 4, ".eos" },
    { SN_LE32(0), 0x94, SN_LE16(15), SN_LE16(10), SN_LE32(4), 20, "SFX_BOSS_2_SCREAMequ" },
    { SN_LE32(6720), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 17, "SFX_BOSS_2_SCREAM" },
    { SN_LE32(4), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(4), SN_LE16(0), 20, "SFX_BOSS_2_SCREAMequ", 4, ".eos" },
    { SN_LE32(0), 0x94, SN_LE16(15), SN_LE16(10), SN_LE32(4), 18, "SFX_BOSS_2_FALLequ" },
    { SN_LE32(6725), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 15, "SFX_BOSS_2_FALL" },
    { SN_LE32(4), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(4), SN_LE16(0), 18, "SFX_BOSS_2_FALLequ", 4, ".eos" },
    { SN_LE32(0), 0x94, SN_LE16(15), SN_LE16(10), SN_LE32(4), 21, "SFX_BOSS_2_VICTORYequ" },
    { SN_LE32(6730), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 18, "SFX_BOSS_2_VICTORY" },
    { SN_LE32(4), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(4), SN_LE16(0), 21, "SFX_BOSS_2_VICTORYequ", 4, ".eos" },
    { SN_LE32(0), 0x94, SN_LE16(15), SN_LE16(10), SN_LE32(4), 25, "SFX_BOSS_2_STICKY_BOMBequ" },
    { SN_LE32(6735), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 22, "SFX_BOSS_2_STICKY_BOMB" },
    { SN_LE32(4), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(4), SN_LE16(0), 25, "SFX_BOSS_2_STICKY_BOMBequ", 4, ".eos" },
    { SN_LE32(0), 0x94, SN_LE16(15), SN_LE16(10), SN_LE32(4), 19, "SFX_BOSS_2_LAUGHequ" },
    { SN_LE32(6740), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 16, "SFX_BOSS_2_LAUGH" },
    { SN_LE32(4), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(4), SN_LE16(0), 19, "SFX_BOSS_2_LAUGHequ", 4, ".eos" },
    { SN_LE32(0), 0x94, SN_LE16(15), SN_LE16(10), SN_LE32(4), 31, "SFX_BOSS_2_RADIOACTIVE_PANICequ" },
    { SN_LE32(6745), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 28, "SFX_BOSS_2_RADIOACTIVE_PANIC" },
    { SN_LE32(4), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(4), SN_LE16(0), 31, "SFX_BOSS_2_RADIOACTIVE_PANICequ", 4, ".eos" },
    { SN_LE32(0), 0x94, SN_LE16(15), SN_LE16(10), SN_LE32(4), 19, "SFX_BOSS_2_TAUNTequ" },
    { SN_LE32(6750), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 16, "SFX_BOSS_2_TAUNT" },
    { SN_LE32(4), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(4), SN_LE16(0), 19, "SFX_BOSS_2_TAUNTequ", 4, ".eos" },
    { SN_LE32(0), 0x94, SN_LE16(15), SN_LE16(10), SN_LE32(4), 26, "SFX_BOSS_2_CAPTURE_FLAGequ" },
    { SN_LE32(6755), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 23, "SFX_BOSS_2_CAPTURE_FLAG" },
    { SN_LE32(4), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(4), SN_LE16(0), 26, "SFX_BOSS_2_CAPTURE_FLAGequ", 4, ".eos" },
    { SN_LE32(0), 0x94, SN_LE16(15), SN_LE16(10), SN_LE32(4), 34, "SFX_BOSS_2_DAMAGED_HOLDING_FLAGequ" },
    { SN_LE32(6760), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 31, "SFX_BOSS_2_DAMAGED_HOLDING_FLAG" },
    { SN_LE32(4), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(4), SN_LE16(0), 34, "SFX_BOSS_2_DAMAGED_HOLDING_FLAGequ", 4, ".eos" },
    { SN_LE32(0), 0x94, SN_LE16(15), SN_LE16(10), SN_LE32(4), 26, "SFX_BOSS_2_PLANTED_FLAGequ" },
    { SN_LE32(6765), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 23, "SFX_BOSS_2_PLANTED_FLAG" },
    { SN_LE32(4), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(4), SN_LE16(0), 26, "SFX_BOSS_2_PLANTED_FLAGequ", 4, ".eos" },
    { SN_LE32(0), 0x94, SN_LE16(15), SN_LE16(10), SN_LE32(4), 24, "SFX_BOSS_2_SEE_PLAYERequ" },
    { SN_LE32(6770), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 21, "SFX_BOSS_2_SEE_PLAYER" },
    { SN_LE32(4), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(4), SN_LE16(0), 24, "SFX_BOSS_2_SEE_PLAYERequ", 4, ".eos" },
    { SN_LE32(0), 0x94, SN_LE16(15), SN_LE16(10), SN_LE32(4), 28, "SFX_BOSS_2_HEAR_SOMETHINGequ" },
    { SN_LE32(6775), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 25, "SFX_BOSS_2_HEAR_SOMETHING" },
    { SN_LE32(4), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(4), SN_LE16(0), 28, "SFX_BOSS_2_HEAR_SOMETHINGequ", 4, ".eos" },
    { SN_LE32(0), 0x94, SN_LE16(15), SN_LE16(10), SN_LE32(4), 29, "SFX_BOSS_2_SMELL_SOMETHINGequ" },
    { SN_LE32(6780), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 26, "SFX_BOSS_2_SMELL_SOMETHING" },
    { SN_LE32(4), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(4), SN_LE16(0), 29, "SFX_BOSS_2_SMELL_SOMETHINGequ", 4, ".eos" },
    { SN_LE32(0), 0x94, SN_LE16(15), SN_LE16(10), SN_LE32(4), 27, "SFX_BOSS_2_KILL_FRIENDLYequ" },
    { SN_LE32(6785), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 24, "SFX_BOSS_2_KILL_FRIENDLY" },
    { SN_LE32(4), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(4), SN_LE16(0), 27, "SFX_BOSS_2_KILL_FRIENDLYequ", 4, ".eos" },
    { SN_LE32(0), 0x94, SN_LE16(15), SN_LE16(10), SN_LE32(4), 35, "SFX_BOSS_3_EXTENDED_FIRE_WAR_CRYequ" },
    { SN_LE32(6800), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 32, "SFX_BOSS_3_EXTENDED_FIRE_WAR_CRY" },
    { SN_LE32(4), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(4), SN_LE16(0), 35, "SFX_BOSS_3_EXTENDED_FIRE_WAR_CRYequ", 4, ".eos" },
    { SN_LE32(0), 0x94, SN_LE16(15), SN_LE16(10), SN_LE32(4), 20, "SFX_BOSS_3_FLINCHequ" },
    { SN_LE32(6805), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 17, "SFX_BOSS_3_FLINCH" },
    { SN_LE32(4), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(4), SN_LE16(0), 20, "SFX_BOSS_3_FLINCHequ", 4, ".eos" },
    { SN_LE32(0), 0x94, SN_LE16(15), SN_LE16(10), SN_LE32(4), 20, "SFX_BOSS_3_EFFORTequ" },
    { SN_LE32(6810), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 17, "SFX_BOSS_3_EFFORT" },
    { SN_LE32(4), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(4), SN_LE16(0), 20, "SFX_BOSS_3_EFFORTequ", 4, ".eos" },
    { SN_LE32(0), 0x94, SN_LE16(15), SN_LE16(10), SN_LE32(4), 19, "SFX_BOSS_3_DEATHequ" },
    { SN_LE32(6815), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 16, "SFX_BOSS_3_DEATH" },
    { SN_LE32(4), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(4), SN_LE16(0), 19, "SFX_BOSS_3_DEATHequ", 4, ".eos" },
    { SN_LE32(0), 0x94, SN_LE16(15), SN_LE16(10), SN_LE32(4), 20, "SFX_BOSS_3_SCREAMequ" },
    { SN_LE32(6820), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 17, "SFX_BOSS_3_SCREAM" },
    { SN_LE32(4), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(4), SN_LE16(0), 20, "SFX_BOSS_3_SCREAMequ", 4, ".eos" },
    { SN_LE32(0), 0x94, SN_LE16(15), SN_LE16(10), SN_LE32(4), 18, "SFX_BOSS_3_FALLequ" },
    { SN_LE32(6825), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 15, "SFX_BOSS_3_FALL" },
    { SN_LE32(4), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(4), SN_LE16(0), 18, "SFX_BOSS_3_FALLequ", 4, ".eos" },
    { SN_LE32(0), 0x94, SN_LE16(15), SN_LE16(10), SN_LE32(4), 21, "SFX_BOSS_3_VICTORYequ" },
    { SN_LE32(6830), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 18, "SFX_BOSS_3_VICTORY" },
    { SN_LE32(4), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(4), SN_LE16(0), 21, "SFX_BOSS_3_VICTORYequ", 4, ".eos" },
    { SN_LE32(0), 0x94, SN_LE16(15), SN_LE16(10), SN_LE32(4), 25, "SFX_BOSS_3_STICKY_BOMBequ" },
    { SN_LE32(6835), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 22, "SFX_BOSS_3_STICKY_BOMB" },
    { SN_LE32(4), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(4), SN_LE16(0), 25, "SFX_BOSS_3_STICKY_BOMBequ", 4, ".eos" },
    { SN_LE32(0), 0x94, SN_LE16(15), SN_LE16(10), SN_LE32(4), 19, "SFX_BOSS_3_LAUGHequ" },
    { SN_LE32(6840), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 16, "SFX_BOSS_3_LAUGH" },
    { SN_LE32(4), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(4), SN_LE16(0), 19, "SFX_BOSS_3_LAUGHequ", 4, ".eos" },
    { SN_LE32(0), 0x94, SN_LE16(15), SN_LE16(10), SN_LE32(4), 31, "SFX_BOSS_3_RADIOACTIVE_PANICequ" },
    { SN_LE32(6845), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 28, "SFX_BOSS_3_RADIOACTIVE_PANIC" },
    { SN_LE32(4), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(4), SN_LE16(0), 31, "SFX_BOSS_3_RADIOACTIVE_PANICequ", 4, ".eos" },
    { SN_LE32(0), 0x94, SN_LE16(15), SN_LE16(10), SN_LE32(4), 19, "SFX_BOSS_3_TAUNTequ" },
    { SN_LE32(6850), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 16, "SFX_BOSS_3_TAUNT" },
    { SN_LE32(4), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(4), SN_LE16(0), 19, "SFX_BOSS_3_TAUNTequ", 4, ".eos" },
    { SN_LE32(0), 0x94, SN_LE16(15), SN_LE16(10), SN_LE32(4), 26, "SFX_BOSS_3_CAPTURE_FLAGequ" },
    { SN_LE32(6855), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 23, "SFX_BOSS_3_CAPTURE_FLAG" },
    { SN_LE32(4), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(4), SN_LE16(0), 26, "SFX_BOSS_3_CAPTURE_FLAGequ", 4, ".eos" },
    { SN_LE32(0), 0x94, SN_LE16(15), SN_LE16(10), SN_LE32(4), 34, "SFX_BOSS_3_DAMAGED_HOLDING_FLAGequ" },
    { SN_LE32(6860), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 31, "SFX_BOSS_3_DAMAGED_HOLDING_FLAG" },
    { SN_LE32(4), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(4), SN_LE16(0), 34, "SFX_BOSS_3_DAMAGED_HOLDING_FLAGequ", 4, ".eos" },
    { SN_LE32(0), 0x94, SN_LE16(15), SN_LE16(10), SN_LE32(4), 26, "SFX_BOSS_3_PLANTED_FLAGequ" },
    { SN_LE32(6865), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 23, "SFX_BOSS_3_PLANTED_FLAG" },
    { SN_LE32(4), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(4), SN_LE16(0), 26, "SFX_BOSS_3_PLANTED_FLAGequ", 4, ".eos" },
    { SN_LE32(0), 0x94, SN_LE16(15), SN_LE16(10), SN_LE32(4), 24, "SFX_BOSS_3_SEE_PLAYERequ" },
    { SN_LE32(6870), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 21, "SFX_BOSS_3_SEE_PLAYER" },
    { SN_LE32(4), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(4), SN_LE16(0), 24, "SFX_BOSS_3_SEE_PLAYERequ", 4, ".eos" },
    { SN_LE32(0), 0x94, SN_LE16(15), SN_LE16(10), SN_LE32(4), 28, "SFX_BOSS_3_HEAR_SOMETHINGequ" },
    { SN_LE32(6875), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 25, "SFX_BOSS_3_HEAR_SOMETHING" },
    { SN_LE32(4), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(4), SN_LE16(0), 28, "SFX_BOSS_3_HEAR_SOMETHINGequ", 4, ".eos" },
    { SN_LE32(0), 0x94, SN_LE16(15), SN_LE16(10), SN_LE32(4), 29, "SFX_BOSS_3_SMELL_SOMETHINGequ" },
    { SN_LE32(6880), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 26, "SFX_BOSS_3_SMELL_SOMETHING" },
    { SN_LE32(4), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(4), SN_LE16(0), 29, "SFX_BOSS_3_SMELL_SOMETHINGequ", 4, ".eos" },
    { SN_LE32(0), 0x94, SN_LE16(15), SN_LE16(10), SN_LE32(4), 27, "SFX_BOSS_3_KILL_FRIENDLYequ" },
    { SN_LE32(6885), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 24, "SFX_BOSS_3_KILL_FRIENDLY" },
    { SN_LE32(4), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(4), SN_LE16(0), 27, "SFX_BOSS_3_KILL_FRIENDLYequ", 4, ".eos" },
    { SN_LE32(0), 0x94, SN_LE16(15), SN_LE16(10), SN_LE32(4), 35, "SFX_BOSS_4_EXTENDED_FIRE_WAR_CRYequ" },
    { SN_LE32(6900), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 32, "SFX_BOSS_4_EXTENDED_FIRE_WAR_CRY" },
    { SN_LE32(4), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(4), SN_LE16(0), 35, "SFX_BOSS_4_EXTENDED_FIRE_WAR_CRYequ", 4, ".eos" },
    { SN_LE32(0), 0x94, SN_LE16(15), SN_LE16(10), SN_LE32(4), 20, "SFX_BOSS_4_FLINCHequ" },
    { SN_LE32(6905), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 17, "SFX_BOSS_4_FLINCH" },
    { SN_LE32(4), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(4), SN_LE16(0), 20, "SFX_BOSS_4_FLINCHequ", 4, ".eos" },
    { SN_LE32(0), 0x94, SN_LE16(15), SN_LE16(10), SN_LE32(4), 20, "SFX_BOSS_4_EFFORTequ" },
    { SN_LE32(6910), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 17, "SFX_BOSS_4_EFFORT" },
    { SN_LE32(4), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(4), SN_LE16(0), 20, "SFX_BOSS_4_EFFORTequ", 4, ".eos" },
    { SN_LE32(0), 0x94, SN_LE16(15), SN_LE16(10), SN_LE32(4), 19, "SFX_BOSS_4_DEATHequ" },
    { SN_LE32(6915), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 16, "SFX_BOSS_4_DEATH" },
    { SN_LE32(4), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(4), SN_LE16(0), 19, "SFX_BOSS_4_DEATHequ", 4, ".eos" },
    { SN_LE32(0), 0x94, SN_LE16(15), SN_LE16(10), SN_LE32(4), 20, "SFX_BOSS_4_SCREAMequ" },
    { SN_LE32(6920), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 17, "SFX_BOSS_4_SCREAM" },
    { SN_LE32(4), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(4), SN_LE16(0), 20, "SFX_BOSS_4_SCREAMequ", 4, ".eos" },
    { SN_LE32(0), 0x94, SN_LE16(15), SN_LE16(10), SN_LE32(4), 18, "SFX_BOSS_4_FALLequ" },
    { SN_LE32(6925), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 15, "SFX_BOSS_4_FALL" },
    { SN_LE32(4), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(4), SN_LE16(0), 18, "SFX_BOSS_4_FALLequ", 4, ".eos" },
    { SN_LE32(0), 0x94, SN_LE16(15), SN_LE16(10), SN_LE32(4), 21, "SFX_BOSS_4_VICTORYequ" },
    { SN_LE32(6930), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 18, "SFX_BOSS_4_VICTORY" },
    { SN_LE32(4), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(4), SN_LE16(0), 21, "SFX_BOSS_4_VICTORYequ", 4, ".eos" },
    { SN_LE32(0), 0x94, SN_LE16(15), SN_LE16(10), SN_LE32(4), 25, "SFX_BOSS_4_STICKY_BOMBequ" },
    { SN_LE32(6935), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 22, "SFX_BOSS_4_STICKY_BOMB" },
    { SN_LE32(4), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(4), SN_LE16(0), 25, "SFX_BOSS_4_STICKY_BOMBequ", 4, ".eos" },
    { SN_LE32(0), 0x94, SN_LE16(15), SN_LE16(10), SN_LE32(4), 19, "SFX_BOSS_4_LAUGHequ" },
    { SN_LE32(6940), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 16, "SFX_BOSS_4_LAUGH" },
    { SN_LE32(4), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(4), SN_LE16(0), 19, "SFX_BOSS_4_LAUGHequ", 4, ".eos" },
    { SN_LE32(0), 0x94, SN_LE16(15), SN_LE16(10), SN_LE32(4), 31, "SFX_BOSS_4_RADIOACTIVE_PANICequ" },
    { SN_LE32(6945), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 28, "SFX_BOSS_4_RADIOACTIVE_PANIC" },
    { SN_LE32(4), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(4), SN_LE16(0), 31, "SFX_BOSS_4_RADIOACTIVE_PANICequ", 4, ".eos" },
    { SN_LE32(0), 0x94, SN_LE16(15), SN_LE16(10), SN_LE32(4), 19, "SFX_BOSS_4_TAUNTequ" },
    { SN_LE32(6950), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 16, "SFX_BOSS_4_TAUNT" },
    { SN_LE32(4), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(4), SN_LE16(0), 19, "SFX_BOSS_4_TAUNTequ", 4, ".eos" },
    { SN_LE32(0), 0x94, SN_LE16(15), SN_LE16(10), SN_LE32(4), 26, "SFX_BOSS_4_CAPTURE_FLAGequ" },
    { SN_LE32(6955), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 23, "SFX_BOSS_4_CAPTURE_FLAG" },
    { SN_LE32(4), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(4), SN_LE16(0), 26, "SFX_BOSS_4_CAPTURE_FLAGequ", 4, ".eos" },
    { SN_LE32(0), 0x94, SN_LE16(15), SN_LE16(10), SN_LE32(4), 34, "SFX_BOSS_4_DAMAGED_HOLDING_FLAGequ" },
    { SN_LE32(6960), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 31, "SFX_BOSS_4_DAMAGED_HOLDING_FLAG" },
    { SN_LE32(4), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(4), SN_LE16(0), 34, "SFX_BOSS_4_DAMAGED_HOLDING_FLAGequ", 4, ".eos" },
    { SN_LE32(0), 0x94, SN_LE16(15), SN_LE16(10), SN_LE32(4), 26, "SFX_BOSS_4_PLANTED_FLAGequ" },
    { SN_LE32(6965), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 23, "SFX_BOSS_4_PLANTED_FLAG" },
    { SN_LE32(4), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(4), SN_LE16(0), 26, "SFX_BOSS_4_PLANTED_FLAGequ", 4, ".eos" },
    { SN_LE32(0), 0x94, SN_LE16(15), SN_LE16(10), SN_LE32(4), 24, "SFX_BOSS_4_SEE_PLAYERequ" },
    { SN_LE32(6970), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 21, "SFX_BOSS_4_SEE_PLAYER" },
    { SN_LE32(4), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(4), SN_LE16(0), 24, "SFX_BOSS_4_SEE_PLAYERequ", 4, ".eos" },
    { SN_LE32(0), 0x94, SN_LE16(15), SN_LE16(10), SN_LE32(4), 28, "SFX_BOSS_4_HEAR_SOMETHINGequ" },
    { SN_LE32(6975), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 25, "SFX_BOSS_4_HEAR_SOMETHING" },
    { SN_LE32(4), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(4), SN_LE16(0), 28, "SFX_BOSS_4_HEAR_SOMETHINGequ", 4, ".eos" },
    { SN_LE32(0), 0x94, SN_LE16(15), SN_LE16(10), SN_LE32(4), 29, "SFX_BOSS_4_SMELL_SOMETHINGequ" },
    { SN_LE32(6980), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 26, "SFX_BOSS_4_SMELL_SOMETHING" },
    { SN_LE32(4), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(4), SN_LE16(0), 29, "SFX_BOSS_4_SMELL_SOMETHINGequ", 4, ".eos" },
    { SN_LE32(0), 0x94, SN_LE16(15), SN_LE16(10), SN_LE32(4), 27, "SFX_BOSS_4_KILL_FRIENDLYequ" },
    { SN_LE32(6985), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 24, "SFX_BOSS_4_KILL_FRIENDLY" },
    { SN_LE32(4), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(4), SN_LE16(0), 27, "SFX_BOSS_4_KILL_FRIENDLYequ", 4, ".eos" },
    { SN_LE32(0), 0x94, SN_LE16(15), SN_LE16(10), SN_LE32(4), 20, "SFX_BOSS_4_SUMMONequ" },
    { SN_LE32(6990), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 17, "SFX_BOSS_4_SUMMON" },
    { SN_LE32(4), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(4), SN_LE16(0), 20, "SFX_BOSS_4_SUMMONequ", 4, ".eos" },
    { SN_LE32(0), 0x94, SN_LE16(15), SN_LE16(10), SN_LE32(4), 13, "MUSIC_NONEequ" },
    { SN_LE32(0), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 10, "MUSIC_NONE" },
    { SN_LE32(4), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(4), SN_LE16(0), 13, "MUSIC_NONEequ", 4, ".eos" },
    { SN_LE32(0), 0x94, SN_LE16(15), SN_LE16(10), SN_LE32(4), 15, "MUSIC_LEVEL1equ" },
    { SN_LE32(1), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 12, "MUSIC_LEVEL1" },
    { SN_LE32(4), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(4), SN_LE16(0), 15, "MUSIC_LEVEL1equ", 4, ".eos" },
    { SN_LE32(0), 0x94, SN_LE16(15), SN_LE16(10), SN_LE32(4), 15, "MUSIC_LEVEL2equ" },
    { SN_LE32(2), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 12, "MUSIC_LEVEL2" },
    { SN_LE32(4), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(4), SN_LE16(0), 15, "MUSIC_LEVEL2equ", 4, ".eos" },
    { SN_LE32(0), 0x94, SN_LE16(15), SN_LE16(10), SN_LE32(4), 15, "MUSIC_LEVEL3equ" },
    { SN_LE32(3), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 12, "MUSIC_LEVEL3" },
    { SN_LE32(4), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(4), SN_LE16(0), 15, "MUSIC_LEVEL3equ", 4, ".eos" },
    { SN_LE32(0), 0x94, SN_LE16(15), SN_LE16(10), SN_LE32(4), 15, "MUSIC_LEVEL4equ" },
    { SN_LE32(4), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 12, "MUSIC_LEVEL4" },
    { SN_LE32(4), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(4), SN_LE16(0), 15, "MUSIC_LEVEL4equ", 4, ".eos" },
    { SN_LE32(0), 0x94, SN_LE16(15), SN_LE16(10), SN_LE32(4), 15, "MUSIC_LEVEL5equ" },
    { SN_LE32(5), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 12, "MUSIC_LEVEL5" },
    { SN_LE32(4), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(4), SN_LE16(0), 15, "MUSIC_LEVEL5equ", 4, ".eos" },
    { SN_LE32(0), 0x94, SN_LE16(15), SN_LE16(10), SN_LE32(4), 15, "MUSIC_LEVEL6equ" },
    { SN_LE32(6), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 12, "MUSIC_LEVEL6" },
    { SN_LE32(4), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(4), SN_LE16(0), 15, "MUSIC_LEVEL6equ", 4, ".eos" },
    { SN_LE32(0), 0x94, SN_LE16(15), SN_LE16(10), SN_LE32(4), 14, "MUSIC_BOSS1equ" },
    { SN_LE32(7), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 11, "MUSIC_BOSS1" },
    { SN_LE32(4), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(4), SN_LE16(0), 14, "MUSIC_BOSS1equ", 4, ".eos" },
    { SN_LE32(0), 0x94, SN_LE16(15), SN_LE16(10), SN_LE32(4), 14, "MUSIC_BOSS2equ" },
    { SN_LE32(8), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 11, "MUSIC_BOSS2" },
    { SN_LE32(4), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(4), SN_LE16(0), 14, "MUSIC_BOSS2equ", 4, ".eos" },
    { SN_LE32(0), 0x94, SN_LE16(15), SN_LE16(10), SN_LE32(4), 14, "MUSIC_BOSS3equ" },
    { SN_LE32(9), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 11, "MUSIC_BOSS3" },
    { SN_LE32(4), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(4), SN_LE16(0), 14, "MUSIC_BOSS3equ", 4, ".eos" },
    { SN_LE32(0), 0x94, SN_LE16(15), SN_LE16(10), SN_LE32(4), 14, "MUSIC_BOSS4equ" },
    { SN_LE32(10), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 11, "MUSIC_BOSS4" },
    { SN_LE32(4), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(4), SN_LE16(0), 14, "MUSIC_BOSS4equ", 4, ".eos" },
    { SN_LE32(0), 0x94, SN_LE16(15), SN_LE16(10), SN_LE32(4), 20, "MUSIC_DEATHMATCH1equ" },
    { SN_LE32(11), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 17, "MUSIC_DEATHMATCH1" },
    { SN_LE32(4), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(4), SN_LE16(0), 20, "MUSIC_DEATHMATCH1equ", 4, ".eos" },
    { SN_LE32(0), 0x94, SN_LE16(15), SN_LE16(10), SN_LE32(4), 20, "MUSIC_DEATHMATCH2equ" },
    { SN_LE32(12), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 17, "MUSIC_DEATHMATCH2" },
    { SN_LE32(4), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(4), SN_LE16(0), 20, "MUSIC_DEATHMATCH2equ", 4, ".eos" },
    { SN_LE32(0), 0x94, SN_LE16(15), SN_LE16(10), SN_LE32(4), 20, "MUSIC_DEATHMATCH3equ" },
    { SN_LE32(13), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 17, "MUSIC_DEATHMATCH3" },
    { SN_LE32(4), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(4), SN_LE16(0), 20, "MUSIC_DEATHMATCH3equ", 4, ".eos" },
    { SN_LE32(0), 0x94, SN_LE16(15), SN_LE16(10), SN_LE32(4), 20, "MUSIC_DEATHMATCH4equ" },
    { SN_LE32(14), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 17, "MUSIC_DEATHMATCH4" },
    { SN_LE32(4), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(4), SN_LE16(0), 20, "MUSIC_DEATHMATCH4equ", 4, ".eos" },
    { SN_LE32(0), 0x94, SN_LE16(15), SN_LE16(10), SN_LE32(4), 22, "MUSIC_LEVEL_INTRO_1equ" },
    { SN_LE32(15), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 19, "MUSIC_LEVEL_INTRO_1" },
    { SN_LE32(4), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(4), SN_LE16(0), 22, "MUSIC_LEVEL_INTRO_1equ", 4, ".eos" },
    { SN_LE32(0), 0x94, SN_LE16(15), SN_LE16(10), SN_LE32(4), 22, "MUSIC_LEVEL_INTRO_2equ" },
    { SN_LE32(16), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 19, "MUSIC_LEVEL_INTRO_2" },
    { SN_LE32(4), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(4), SN_LE16(0), 22, "MUSIC_LEVEL_INTRO_2equ", 4, ".eos" },
    { SN_LE32(0), 0x94, SN_LE16(15), SN_LE16(10), SN_LE32(4), 22, "MUSIC_LEVEL_INTRO_3equ" },
    { SN_LE32(17), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 19, "MUSIC_LEVEL_INTRO_3" },
    { SN_LE32(4), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(4), SN_LE16(0), 22, "MUSIC_LEVEL_INTRO_3equ", 4, ".eos" },
    { SN_LE32(0), 0x94, SN_LE16(15), SN_LE16(10), SN_LE32(4), 22, "MUSIC_LEVEL_INTRO_4equ" },
    { SN_LE32(18), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 19, "MUSIC_LEVEL_INTRO_4" },
    { SN_LE32(4), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(4), SN_LE16(0), 22, "MUSIC_LEVEL_INTRO_4equ", 4, ".eos" },
    { SN_LE32(0), 0x94, SN_LE16(15), SN_LE16(10), SN_LE32(4), 22, "MUSIC_LEVEL_INTRO_5equ" },
    { SN_LE32(19), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 19, "MUSIC_LEVEL_INTRO_5" },
    { SN_LE32(4), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(4), SN_LE16(0), 22, "MUSIC_LEVEL_INTRO_5equ", 4, ".eos" },
    { SN_LE32(0), 0x94, SN_LE16(15), SN_LE16(10), SN_LE32(4), 22, "MUSIC_LEVEL_INTRO_6equ" },
    { SN_LE32(20), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 19, "MUSIC_LEVEL_INTRO_6" },
    { SN_LE32(4), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(4), SN_LE16(0), 22, "MUSIC_LEVEL_INTRO_6equ", 4, ".eos" },
    { SN_LE32(0), 0x94, SN_LE16(15), SN_LE16(10), SN_LE32(4), 21, "MUSIC_DEFEND_TOTEMequ" },
    { SN_LE32(21), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 18, "MUSIC_DEFEND_TOTEM" },
    { SN_LE32(4), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(4), SN_LE16(0), 21, "MUSIC_DEFEND_TOTEMequ", 4, ".eos" },
    { SN_LE32(0), 0x94, SN_LE16(15), SN_LE16(10), SN_LE32(4), 14, "MUSIC_INTROequ" },
    { SN_LE32(22), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 11, "MUSIC_INTRO" },
    { SN_LE32(4), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(4), SN_LE16(0), 14, "MUSIC_INTROequ", 4, ".eos" },
    { SN_LE32(0), 0x94, SN_LE16(15), SN_LE16(10), SN_LE32(4), 23, "MUSIC_PLAYER_VICTORYequ" },
    { SN_LE32(50), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 20, "MUSIC_PLAYER_VICTORY" },
    { SN_LE32(4), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(4), SN_LE16(0), 23, "MUSIC_PLAYER_VICTORYequ", 4, ".eos" },
    { SN_LE32(0), 0x94, SN_LE16(15), SN_LE16(10), SN_LE32(4), 24, "MUSIC_BLOODLUST_INTROequ" },
    { SN_LE32(51), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 21, "MUSIC_BLOODLUST_INTRO" },
    { SN_LE32(4), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(4), SN_LE16(0), 24, "MUSIC_BLOODLUST_INTROequ", 4, ".eos" },
    { SN_LE32(0), 0x94, SN_LE16(15), SN_LE16(10), SN_LE32(4), 24, "MUSIC_FRONT_END_THEMEequ" },
    { SN_LE32(52), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 21, "MUSIC_FRONT_END_THEME" },
    { SN_LE32(4), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(4), SN_LE16(0), 24, "MUSIC_FRONT_END_THEMEequ", 4, ".eos" },
    { SN_LE32(0), 0x94, SN_LE16(15), SN_LE16(10), SN_LE32(4), 22, "MUSIC_MEDALS_SCREENequ" },
    { SN_LE32(53), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 19, "MUSIC_MEDALS_SCREEN" },
    { SN_LE32(4), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(4), SN_LE16(0), 22, "MUSIC_MEDALS_SCREENequ", 4, ".eos" },
    { SN_LE32(0), 0x94, SN_LE16(15), SN_LE16(10), SN_LE32(4), 21, "MUSIC_MISSION_TREEequ" },
    { SN_LE32(54), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 18, "MUSIC_MISSION_TREE" },
    { SN_LE32(4), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(4), SN_LE16(0), 21, "MUSIC_MISSION_TREEequ", 4, ".eos" },
    { SN_LE32(0), 0x94, SN_LE16(15), SN_LE16(10), SN_LE32(4), 28, "MUSIC_CHARACTER_SELECTIONequ" },
    { SN_LE32(55), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 25, "MUSIC_CHARACTER_SELECTION" },
    { SN_LE32(4), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(4), SN_LE16(0), 28, "MUSIC_CHARACTER_SELECTIONequ", 4, ".eos" },
    { SN_LE32(0), 0x94, SN_LE16(15), SN_LE16(10), SN_LE32(4), 30, "MUSIC_DEATHMATCH_GAMEPLAY_1equ" },
    { SN_LE32(56), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 27, "MUSIC_DEATHMATCH_GAMEPLAY_1" },
    { SN_LE32(4), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(4), SN_LE16(0), 30, "MUSIC_DEATHMATCH_GAMEPLAY_1equ", 4, ".eos" },
    { SN_LE32(0), 0x94, SN_LE16(15), SN_LE16(10), SN_LE32(4), 30, "MUSIC_DEATHMATCH_GAMEPLAY_2equ" },
    { SN_LE32(57), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 27, "MUSIC_DEATHMATCH_GAMEPLAY_2" },
    { SN_LE32(4), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(4), SN_LE16(0), 30, "MUSIC_DEATHMATCH_GAMEPLAY_2equ", 4, ".eos" },
    { SN_LE32(0), 0x94, SN_LE16(15), SN_LE16(10), SN_LE32(4), 30, "MUSIC_DEATHMATCH_GAMEPLAY_3equ" },
    { SN_LE32(58), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 27, "MUSIC_DEATHMATCH_GAMEPLAY_3" },
    { SN_LE32(4), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(4), SN_LE16(0), 30, "MUSIC_DEATHMATCH_GAMEPLAY_3equ", 4, ".eos" },
    { SN_LE32(0), 0x94, SN_LE16(15), SN_LE16(10), SN_LE32(4), 30, "MUSIC_DEATHMATCH_GAMEPLAY_4equ" },
    { SN_LE32(59), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 27, "MUSIC_DEATHMATCH_GAMEPLAY_4" },
    { SN_LE32(4), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(4), SN_LE16(0), 30, "MUSIC_DEATHMATCH_GAMEPLAY_4equ", 4, ".eos" },
    { SN_LE32(0), 0x94, SN_LE16(15), SN_LE16(10), SN_LE32(4), 18, "MUSIC_GAME_OVERequ" },
    { SN_LE32(60), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 15, "MUSIC_GAME_OVER" },
    { SN_LE32(4), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(4), SN_LE16(0), 18, "MUSIC_GAME_OVERequ", 4, ".eos" },
    { SN_LE32(0), 0x94, SN_LE16(15), SN_LE16(10), SN_LE32(4), 27, "MUSIC_MONKEY_RETALIATIONequ" },
    { SN_LE32(61), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 24, "MUSIC_MONKEY_RETALIATION" },
    { SN_LE32(4), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(4), SN_LE16(0), 27, "MUSIC_MONKEY_RETALIATIONequ", 4, ".eos" },
    { SN_LE32(0), 0x94, SN_LE16(15), SN_LE16(10), SN_LE32(4), 19, "MUSIC_MENU_PAUSEequ" },
    { SN_LE32(65), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 16, "MUSIC_MENU_PAUSE" },
    { SN_LE32(4), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(4), SN_LE16(0), 19, "MUSIC_MENU_PAUSEequ", 4, ".eos" },
    { SN_LE32(0), 0x94, SN_LE16(15), SN_LE16(10), SN_LE32(4), 11, "RAX_NONEequ" },
    { SN_LE32(299), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 8, "RAX_NONE" },
    { SN_LE32(4), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(4), SN_LE16(0), 11, "RAX_NONEequ", 4, ".eos" },
    { SN_LE32(0), 0x94, SN_LE16(15), SN_LE16(10), SN_LE32(4), 19, "RAX_INTRO_LINE_1equ" },
    { SN_LE32(300), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 16, "RAX_INTRO_LINE_1" },
    { SN_LE32(4), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(4), SN_LE16(0), 19, "RAX_INTRO_LINE_1equ", 4, ".eos" },
    { SN_LE32(0), 0x94, SN_LE16(15), SN_LE16(10), SN_LE32(4), 19, "RAX_INTRO_LINE_2equ" },
    { SN_LE32(301), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 16, "RAX_INTRO_LINE_2" },
    { SN_LE32(4), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(4), SN_LE16(0), 19, "RAX_INTRO_LINE_2equ", 4, ".eos" },
    { SN_LE32(0), 0x94, SN_LE16(15), SN_LE16(10), SN_LE32(4), 19, "RAX_INTRO_LINE_3equ" },
    { SN_LE32(302), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 16, "RAX_INTRO_LINE_3" },
    { SN_LE32(4), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(4), SN_LE16(0), 19, "RAX_INTRO_LINE_3equ", 4, ".eos" },
    { SN_LE32(0), 0x94, SN_LE16(15), SN_LE16(10), SN_LE32(4), 19, "RAX_INTRO_LINE_4equ" },
    { SN_LE32(303), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 16, "RAX_INTRO_LINE_4" },
    { SN_LE32(4), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(4), SN_LE16(0), 19, "RAX_INTRO_LINE_4equ", 4, ".eos" },
    { SN_LE32(0), 0x94, SN_LE16(15), SN_LE16(10), SN_LE32(4), 20, "RAX_VICTORY_TUROKequ" },
    { SN_LE32(320), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 17, "RAX_VICTORY_TUROK" },
    { SN_LE32(4), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(4), SN_LE16(0), 20, "RAX_VICTORY_TUROKequ", 4, ".eos" },
    { SN_LE32(0), 0x94, SN_LE16(15), SN_LE16(10), SN_LE32(4), 19, "RAX_VICTORY_ADONequ" },
    { SN_LE32(321), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 16, "RAX_VICTORY_ADON" },
    { SN_LE32(4), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(4), SN_LE16(0), 19, "RAX_VICTORY_ADONequ", 4, ".eos" },
    { SN_LE32(0), 0x94, SN_LE16(15), SN_LE16(10), SN_LE32(4), 21, "RAX_VICTORY_RAPTORequ" },
    { SN_LE32(322), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 18, "RAX_VICTORY_RAPTOR" },
    { SN_LE32(4), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(4), SN_LE16(0), 21, "RAX_VICTORY_RAPTORequ", 4, ".eos" },
    { SN_LE32(0), 0x94, SN_LE16(15), SN_LE16(10), SN_LE32(4), 23, "RAX_VICTORY_FIREBORNequ" },
    { SN_LE32(323), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 20, "RAX_VICTORY_FIREBORN" },
    { SN_LE32(4), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(4), SN_LE16(0), 23, "RAX_VICTORY_FIREBORNequ", 4, ".eos" },
    { SN_LE32(0), 0x94, SN_LE16(15), SN_LE16(10), SN_LE32(4), 25, "RAX_VICTORY_JUGGERNAUTequ" },
    { SN_LE32(324), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 22, "RAX_VICTORY_JUGGERNAUT" },
    { SN_LE32(4), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(4), SN_LE16(0), 25, "RAX_VICTORY_JUGGERNAUTequ", 4, ".eos" },
    { SN_LE32(0), 0x94, SN_LE16(15), SN_LE16(10), SN_LE32(4), 26, "RAX_VICTORY_ELITE_GUARDequ" },
    { SN_LE32(325), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 23, "RAX_VICTORY_ELITE_GUARD" },
    { SN_LE32(4), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(4), SN_LE16(0), 26, "RAX_VICTORY_ELITE_GUARDequ", 4, ".eos" },
    { SN_LE32(0), 0x94, SN_LE16(15), SN_LE16(10), SN_LE32(4), 26, "RAX_VICTORY_DEATH_GUARDequ" },
    { SN_LE32(326), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 23, "RAX_VICTORY_DEATH_GUARD" },
    { SN_LE32(4), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(4), SN_LE16(0), 26, "RAX_VICTORY_DEATH_GUARDequ", 4, ".eos" },
    { SN_LE32(0), 0x94, SN_LE16(15), SN_LE16(10), SN_LE32(4), 25, "RAX_VICTORY_CAMPAINGERequ" },
    { SN_LE32(327), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 22, "RAX_VICTORY_CAMPAINGER" },
    { SN_LE32(4), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(4), SN_LE16(0), 25, "RAX_VICTORY_CAMPAINGERequ", 4, ".eos" },
    { SN_LE32(0), 0x94, SN_LE16(15), SN_LE16(10), SN_LE32(4), 24, "RAX_VICTORY_LORD_DEADequ" },
    { SN_LE32(328), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 21, "RAX_VICTORY_LORD_DEAD" },
    { SN_LE32(4), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(4), SN_LE16(0), 24, "RAX_VICTORY_LORD_DEADequ", 4, ".eos" },
    { SN_LE32(0), 0x94, SN_LE16(15), SN_LE16(10), SN_LE32(4), 19, "RAX_VICTORY_MITEequ" },
    { SN_LE32(329), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 16, "RAX_VICTORY_MITE" },
    { SN_LE32(4), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(4), SN_LE16(0), 19, "RAX_VICTORY_MITEequ", 4, ".eos" },
    { SN_LE32(0), 0x94, SN_LE16(15), SN_LE16(10), SN_LE32(4), 20, "RAX_VICTORY_DRONEequ" },
    { SN_LE32(330), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 17, "RAX_VICTORY_DRONE" },
    { SN_LE32(4), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(4), SN_LE16(0), 20, "RAX_VICTORY_DRONEequ", 4, ".eos" },
    { SN_LE32(0), 0x94, SN_LE16(15), SN_LE16(10), SN_LE32(4), 22, "RAX_VICTORY_SOLDIERequ" },
    { SN_LE32(331), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 19, "RAX_VICTORY_SOLDIER" },
    { SN_LE32(4), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(4), SN_LE16(0), 22, "RAX_VICTORY_SOLDIERequ", 4, ".eos" },
    { SN_LE32(0), 0x94, SN_LE16(15), SN_LE16(10), SN_LE32(4), 23, "RAX_VICTORY_GUARDIANequ" },
    { SN_LE32(332), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 20, "RAX_VICTORY_GUARDIAN" },
    { SN_LE32(4), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(4), SN_LE16(0), 23, "RAX_VICTORY_GUARDIANequ", 4, ".eos" },
    { SN_LE32(0), 0x94, SN_LE16(15), SN_LE16(10), SN_LE32(4), 23, "RAX_VICTORY_BASTILLEequ" },
    { SN_LE32(333), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 20, "RAX_VICTORY_BASTILLE" },
    { SN_LE32(4), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(4), SN_LE16(0), 23, "RAX_VICTORY_BASTILLEequ", 4, ".eos" },
    { SN_LE32(0), 0x94, SN_LE16(15), SN_LE16(10), SN_LE32(4), 20, "RAX_VICTORY_SEERAequ" },
    { SN_LE32(334), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 17, "RAX_VICTORY_SEERA" },
    { SN_LE32(4), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(4), SN_LE16(0), 20, "RAX_VICTORY_SEERAequ", 4, ".eos" },
    { SN_LE32(0), 0x94, SN_LE16(15), SN_LE16(10), SN_LE32(4), 23, "RAX_VICTORY_SYMBIONTequ" },
    { SN_LE32(335), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 20, "RAX_VICTORY_SYMBIONT" },
    { SN_LE32(4), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(4), SN_LE16(0), 23, "RAX_VICTORY_SYMBIONTequ", 4, ".eos" },
    { SN_LE32(0), 0x94, SN_LE16(15), SN_LE16(10), SN_LE32(4), 22, "RAX_VICTORY_TAL_SETequ" },
    { SN_LE32(336), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 19, "RAX_VICTORY_TAL_SET" },
    { SN_LE32(4), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(4), SN_LE16(0), 22, "RAX_VICTORY_TAL_SETequ", 4, ".eos" },
    { SN_LE32(0), 0x94, SN_LE16(15), SN_LE16(10), SN_LE32(4), 19, "RAX_PU_SLOW_TIMEequ" },
    { SN_LE32(350), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 16, "RAX_PU_SLOW_TIME" },
    { SN_LE32(4), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(4), SN_LE16(0), 19, "RAX_PU_SLOW_TIMEequ", 4, ".eos" },
    { SN_LE32(0), 0x94, SN_LE16(15), SN_LE16(10), SN_LE32(4), 22, "RAX_PU_REGENERATIONequ" },
    { SN_LE32(351), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 19, "RAX_PU_REGENERATION" },
    { SN_LE32(4), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(4), SN_LE16(0), 22, "RAX_PU_REGENERATIONequ", 4, ".eos" },
    { SN_LE32(0), 0x94, SN_LE16(15), SN_LE16(10), SN_LE32(4), 23, "RAX_PU_FORCE_EMPATHYequ" },
    { SN_LE32(352), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 20, "RAX_PU_FORCE_EMPATHY" },
    { SN_LE32(4), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(4), SN_LE16(0), 23, "RAX_PU_FORCE_EMPATHYequ", 4, ".eos" },
    { SN_LE32(0), 0x94, SN_LE16(15), SN_LE16(10), SN_LE32(4), 19, "RAX_PU_VAMPIRISMequ" },
    { SN_LE32(353), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 16, "RAX_PU_VAMPIRISM" },
    { SN_LE32(4), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(4), SN_LE16(0), 19, "RAX_PU_VAMPIRISMequ", 4, ".eos" },
    { SN_LE32(0), 0x94, SN_LE16(15), SN_LE16(10), SN_LE32(4), 18, "RAX_PU_TELEPORTequ" },
    { SN_LE32(354), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 15, "RAX_PU_TELEPORT" },
    { SN_LE32(4), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(4), SN_LE16(0), 18, "RAX_PU_TELEPORTequ", 4, ".eos" },
    { SN_LE32(0), 0x94, SN_LE16(15), SN_LE16(10), SN_LE32(4), 21, "RAX_PU_DARK_SHIELDequ" },
    { SN_LE32(355), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 18, "RAX_PU_DARK_SHIELD" },
    { SN_LE32(4), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(4), SN_LE16(0), 21, "RAX_PU_DARK_SHIELDequ", 4, ".eos" },
    { SN_LE32(0), 0x94, SN_LE16(15), SN_LE16(10), SN_LE32(4), 20, "RAX_PU_PROTECTIONequ" },
    { SN_LE32(356), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 17, "RAX_PU_PROTECTION" },
    { SN_LE32(4), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(4), SN_LE16(0), 20, "RAX_PU_PROTECTIONequ", 4, ".eos" },
    { SN_LE32(0), 0x94, SN_LE16(15), SN_LE16(10), SN_LE32(4), 17, "RAX_PU_PETRIFYequ" },
    { SN_LE32(357), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 14, "RAX_PU_PETRIFY" },
    { SN_LE32(4), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(4), SN_LE16(0), 17, "RAX_PU_PETRIFYequ", 4, ".eos" },
    { SN_LE32(0), 0x94, SN_LE16(15), SN_LE16(10), SN_LE32(4), 22, "RAX_PU_INVISIBILITYequ" },
    { SN_LE32(358), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 19, "RAX_PU_INVISIBILITY" },
    { SN_LE32(4), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(4), SN_LE16(0), 22, "RAX_PU_INVISIBILITYequ", 4, ".eos" },
    { SN_LE32(0), 0x94, SN_LE16(15), SN_LE16(10), SN_LE32(4), 15, "RAX_PU_SPEEDequ" },
    { SN_LE32(361), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 12, "RAX_PU_SPEED" },
    { SN_LE32(4), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(4), SN_LE16(0), 15, "RAX_PU_SPEEDequ", 4, ".eos" },
    { SN_LE32(0), 0x94, SN_LE16(15), SN_LE16(10), SN_LE32(4), 20, "RAX_PU_STONE_SKINequ" },
    { SN_LE32(360), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 17, "RAX_PU_STONE_SKIN" },
    { SN_LE32(4), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(4), SN_LE16(0), 20, "RAX_PU_STONE_SKINequ", 4, ".eos" },
    { SN_LE32(0), 0x94, SN_LE16(15), SN_LE16(10), SN_LE32(4), 21, "RAX_PU_BATTLE_RAGEequ" },
    { SN_LE32(362), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 18, "RAX_PU_BATTLE_RAGE" },
    { SN_LE32(4), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(4), SN_LE16(0), 21, "RAX_PU_BATTLE_RAGEequ", 4, ".eos" },
    { SN_LE32(0), 0x94, SN_LE16(15), SN_LE16(10), SN_LE32(4), 13, "TurretActions" },
    { SN_LE32(0), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 18, "TURRET_PING_ACTION" },
    { SN_LE32(1), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 18, "TURRET_PONG_ACTION" },
    { SN_LE32(2), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 14, "TURRET_ACTIONS" },
    { SN_LE32(4), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(4), SN_LE16(0), 13, "TurretActions", 4, ".eos" },
    { SN_LE32(2108576), 0x96, SN_LE16(2), SN_LE16(40), SN_LE32(16), SN_LE16(0), 10, "CQuatern_t", 31, "CVector3__GetDirectionRotation2" },
    { SN_LE32(2109004), 0x94, SN_LE16(2), SN_LE16(33), SN_LE32(0), 20, "Turret_CalcOrientMtx" },
    { SN_LE32(2109404), 0x94, SN_LE16(2), SN_LE16(33), SN_LE32(0), 11, "Turret_Move" },
    { SN_LE32(2110072), 0x94, SN_LE16(2), SN_LE16(33), SN_LE32(0), 25, "AI_DynTurretGetTargetInfo" },
    { SN_LE32(2110628), 0x94, SN_LE16(2), SN_LE16(36), SN_LE32(0), 18, "Turret_TrackTarget" },
    { SN_LE32(2111560), 0x96, SN_LE16(2), SN_LE16(40), SN_LE32(16), SN_LE16(0), 10, "CQuatern_t", 20, "Turret_BuildPlaneRot" },
    { SN_LE32(2111628), 0x94, SN_LE16(2), SN_LE16(33), SN_LE32(0), 16, "Turret_Construct" },
    { SN_LE32(2111752), 0x94, SN_LE16(2), SN_LE16(33), SN_LE32(0), 12, "Turret_Setup" },
    { SN_LE32(2111992), 0x94, SN_LE16(2), SN_LE16(33), SN_LE32(0), 14, "Turret_Advance" },
    { SN_LE32(2112148), 0x94, SN_LE16(2), SN_LE16(37), SN_LE32(0), 20, "Turret_Anim_ACTIVATE" },
    { SN_LE32(2112176), 0x94, SN_LE16(2), SN_LE16(33), SN_LE32(0), 20, "Turret_Code_ACTIVATE" },
    { SN_LE32(2112216), 0x94, SN_LE16(2), SN_LE16(33), SN_LE32(0), 16, "Turret_Code_IDLE" },
    { SN_LE32(2112284), 0x94, SN_LE16(2), SN_LE16(33), SN_LE32(0), 16, "Turret_Code_FIRE" },
    { SN_LE32(2112352), 0x94, SN_LE16(2), SN_LE16(33), SN_LE32(0), 18, "Turret_Setup_DEATH" },
    { SN_LE32(2112520), 0x94, SN_LE16(2), SN_LE16(33), SN_LE32(0), 17, "Turret_Code_DEATH" },
    { SN_LE32(2112576), 0x94, SN_LE16(2), SN_LE16(33), SN_LE32(0), 29, "Turret_LinkEffect_MakeVisible" },
    { SN_LE32(2112644), 0x94, SN_LE16(2), SN_LE16(33), SN_LE32(0), 26, "Turret_LinkEffect_Activate" },
    { SN_LE32(2112764), 0x94, SN_LE16(2), SN_LE16(33), SN_LE32(0), 23, "Turret_BuildPlaneOrient" },
    { SN_LE32(2112844), 0x94, SN_LE16(2), SN_LE16(33), SN_LE32(0), 32, "Turret_MoveTargetIntoTurretSpace" },
    { SN_LE32(2113008), 0x94, SN_LE16(2), SN_LE16(33), SN_LE32(0), 21, "Turret_SpecialEffects" },
    { SN_LE32(2113144), 0x94, SN_LE16(2), SN_LE16(33), SN_LE32(0), 21, "Turret_DecreaseHealth" },
    { SN_LE32(2113200), 0x94, SN_LE16(2), SN_LE16(36), SN_LE32(0), 26, "AI_DynTurretOpposingPlayer" },
    { SN_LE32(2113284), 0x94, SN_LE16(2), SN_LE16(36), SN_LE32(0), 24, "AI_DynTurretCanSeePlayer" },
    { SN_LE32(0x800cd840), 0x96, SN_LE16(2), SN_LE16(8), SN_LE32(8), SN_LE16(0), 9, "CAIInfo_t", 12, "TurretAIInfo" },
    { SN_LE32(0x800cd760), 0x96, SN_LE16(2), SN_LE16(56), SN_LE32(224), SN_LE16(1), SN_LE32(7), 13, "CAIModeInfo_t", 15, "TurretModeTable" },
    { SN_LE32(0x800cd848), 0x96, SN_LE16(2), SN_LE16(56), SN_LE32(24), SN_LE16(1), SN_LE32(3), 17, "CLinkEffectInfo_t", 20, "TurretLinkEffectInfo" },
    { SN_LE32(2108576), 0x9C, SN_LE16(29), SN_LE32(96), SN_LE16(31), SN_LE32(0x800f0000), SN_LE32(0xfffffff0), SN_LE32(0x100000), SN_LE32(0xfffffff8), SN_LE32(181), 49, "C:\\PROJECTS\\DM\\N64\\SOURCE\\AI\\ENEMIES\\TURRETAI.CPP", 31, "CVector3__GetDirectionRotation2" },
    { SN_LE32(17), 0x96, SN_LE16(17), SN_LE16(24), SN_LE32(12), SN_LE16(0), 10, "CVector3_t", 8, "pvNormal" },
    { SN_LE32(2108576), 0x90, SN_LE32(1) },
    { SN_LE32(0xffffffb0), 0x96, SN_LE16(1), SN_LE16(8), SN_LE32(16), SN_LE16(0), 10, "CQuatern_t", 4, "qRot" },
    { SN_LE32(0xffffffc0), 0x96, SN_LE16(1), SN_LE16(8), SN_LE32(12), SN_LE16(0), 10, "CVector3_t", 13, "vIdentityAxis" },
    { SN_LE32(0xffffffd0), 0x96, SN_LE16(1), SN_LE16(8), SN_LE32(12), SN_LE16(0), 10, "CVector3_t", 5, "vAxis" },
    { SN_LE32(52), 0x94, SN_LE16(4), SN_LE16(6), SN_LE32(0), 5, "theta" },
    { SN_LE32(2108936), 0x92, SN_LE32(31) },
    { SN_LE32(2109004), 0x8E, SN_LE32(212) },
    { SN_LE32(2109004), 0x9C, SN_LE16(29), SN_LE32(232), SN_LE16(31), SN_LE32(0x80070000), SN_LE32(0xfffffff4), SN_LE32(0x100000), SN_LE32(0xfffffff8), SN_LE32(262), 49, "C:\\PROJECTS\\DM\\N64\\SOURCE\\AI\\ENEMIES\\TURRETAI.CPP", 20, "Turret_CalcOrientMtx" },
    { SN_LE32(18), 0x96, SN_LE16(17), SN_LE16(24), SN_LE32(744), SN_LE16(0), 21, "CGameObjectInstance_t", 5, "pThis" },
    { SN_LE32(17), 0x96, SN_LE16(17), SN_LE16(24), SN_LE32(368), SN_LE16(0), 5, "CAI_t", 3, "pAI" },
    { SN_LE32(2109004), 0x90, SN_LE32(1) },
    { SN_LE32(16), 0x96, SN_LE16(4), SN_LE16(24), SN_LE32(116), SN_LE16(0), 21, "CTurretIntelligence_t", 6, "pIntel" },
    { SN_LE32(0xffffff28), 0x96, SN_LE16(1), SN_LE16(8), SN_LE32(16), SN_LE16(0), 10, "CQuatern_t", 5, "qRotY" },
    { SN_LE32(0xffffff38), 0x96, SN_LE16(1), SN_LE16(8), SN_LE32(16), SN_LE16(0), 10, "CQuatern_t", 6, "qTemp1" },
    { SN_LE32(0xffffff48), 0x96, SN_LE16(1), SN_LE16(246), SN_LE32(64), SN_LE16(2), SN_LE32(4), SN_LE32(4), 0, 8, "mfOrient" },
    { SN_LE32(0xffffff88), 0x96, SN_LE16(1), SN_LE16(246), SN_LE32(64), SN_LE16(2), SN_LE32(4), SN_LE32(4), 0, 7, "mfPlane" },
    { SN_LE32(2109004), 0x90, SN_LE32(1) },
    { SN_LE32(18), 0x96, SN_LE16(4), SN_LE16(24), SN_LE32(744), SN_LE16(0), 21, "CGameObjectInstance_t", 5, "pThis" },
    { SN_LE32(17), 0x96, SN_LE16(4), SN_LE16(24), SN_LE32(368), SN_LE16(0), 5, "CAI_t", 3, "pAI" },
    { SN_LE32(2109004), 0x90, SN_LE32(1) },
    { SN_LE32(0xffffffc8), 0x96, SN_LE16(1), SN_LE16(8), SN_LE32(16), SN_LE16(0), 10, "CQuatern_t", 4, "qRot" },
    { SN_LE32(2109004), 0x90, SN_LE32(1) },
    { SN_LE32(17), 0x96, SN_LE16(4), SN_LE16(24), SN_LE32(368), SN_LE16(0), 5, "CAI_t", 3, "pAI" },
    { SN_LE32(18), 0x96, SN_LE16(4), SN_LE16(24), SN_LE32(744), SN_LE16(0), 21, "CGameObjectInstance_t", 5, "pThis" },
    { SN_LE32(2109004), 0x90, SN_LE32(1) },
    { SN_LE32(0xffffffd8), 0x96, SN_LE16(1), SN_LE16(8), SN_LE32(12), SN_LE16(0), 10, "CVector3_t", 7, "vNormal" },
    { SN_LE32(2109004), 0x92, SN_LE32(1) },
    { SN_LE32(2109004), 0x92, SN_LE32(1) },
    { SN_LE32(2109004), 0x92, SN_LE32(1) },
    { SN_LE32(2109004), 0x92, SN_LE32(1) },
    { SN_LE32(2109208), 0x92, SN_LE32(14) },
    { SN_LE32(2109404), 0x8E, SN_LE32(291) },
    { SN_LE32(2109404), 0x9C, SN_LE16(29), SN_LE32(168), SN_LE16(31), SN_LE32(0x801f0000), SN_LE32(0xffffffec), SN_LE32(0x300000), SN_LE32(0xfffffff8), SN_LE32(495), 49, "C:\\PROJECTS\\DM\\N64\\SOURCE\\AI\\ENEMIES\\TURRETAI.CPP", 11, "Turret_Move" },
    { SN_LE32(4), 0x96, SN_LE16(17), SN_LE16(24), SN_LE32(744), SN_LE16(0), 21, "CGameObjectInstance_t", 5, "pThis" },
    { SN_LE32(19), 0x96, SN_LE16(17), SN_LE16(24), SN_LE32(368), SN_LE16(0), 5, "CAI_t", 3, "pAI" },
    { SN_LE32(16), 0x94, SN_LE16(17), SN_LE16(4), SN_LE32(0), 10, "MotionType" },
    { SN_LE32(20), 0x96, SN_LE16(17), SN_LE16(24), SN_LE32(744), SN_LE16(0), 21, "CGameObjectInstance_t", 7, "pTarget" },
    { SN_LE32(2109404), 0x90, SN_LE32(1) },
    { SN_LE32(18), 0x96, SN_LE16(4), SN_LE16(24), SN_LE32(116), SN_LE16(0), 21, "CTurretIntelligence_t", 6, "pIntel" },
    { SN_LE32(52), 0x94, SN_LE16(4), SN_LE16(6), SN_LE32(0), 1, "t" },
    { SN_LE32(33), 0x94, SN_LE16(4), SN_LE16(6), SN_LE32(0), 6, "Target" },
    { SN_LE32(46), 0x94, SN_LE16(4), SN_LE16(6), SN_LE32(0), 3, "Vel" },
    { SN_LE32(53), 0x94, SN_LE16(4), SN_LE16(6), SN_LE32(0), 5, "Speed" },
    { SN_LE32(0xffffff68), 0x96, SN_LE16(1), SN_LE16(8), SN_LE32(12), SN_LE16(0), 10, "CVector3_t", 7, "vEndPos" },
    { SN_LE32(0xffffff78), 0x96, SN_LE16(1), SN_LE16(8), SN_LE32(12), SN_LE16(0), 10, "CVector3_t", 4, "vPos" },
    { SN_LE32(0xffffff88), 0x96, SN_LE16(1), SN_LE16(8), SN_LE32(12), SN_LE16(0), 10, "CVector3_t", 7, "vRotPos" },
    { SN_LE32(0xffffff98), 0x96, SN_LE16(1), SN_LE16(246), SN_LE32(64), SN_LE16(2), SN_LE32(4), SN_LE32(4), 0, 8, "mfOrient" },
    { SN_LE32(2109904), 0x92, SN_LE32(101) },
    { SN_LE32(2110072), 0x8E, SN_LE32(605) },
    { SN_LE32(2110072), 0x9C, SN_LE16(29), SN_LE32(120), SN_LE16(31), SN_LE32(0x803f0000), SN_LE32(0xffffffe0), SN_LE32(0x700000), SN_LE32(0xfffffff8), SN_LE32(695), 49, "C:\\PROJECTS\\DM\\N64\\SOURCE\\AI\\ENEMIES\\TURRETAI.CPP", 25, "AI_DynTurretGetTargetInfo" },
    { SN_LE32(18), 0x96, SN_LE16(17), SN_LE16(24), SN_LE32(744), SN_LE16(0), 21, "CGameObjectInstance_t", 5, "pThis" },
    { SN_LE32(19), 0x96, SN_LE16(17), SN_LE16(24), SN_LE32(368), SN_LE16(0), 5, "CAI_t", 3, "pAI" },
    { SN_LE32(20), 0x96, SN_LE16(17), SN_LE16(24), SN_LE32(136), SN_LE16(0), 15, "s_CAITargetInfo", 5, "pInfo" },
    { SN_LE32(2110072), 0x90, SN_LE32(1) },
    { SN_LE32(21), 0x96, SN_LE16(4), SN_LE16(24), SN_LE32(116), SN_LE16(0), 21, "CTurretIntelligence_t", 6, "pIntel" },
    { SN_LE32(16), 0x96, SN_LE16(4), SN_LE16(24), SN_LE32(5864), SN_LE16(0), 9, "CPlayer_t", 10, "pCurPlayer" },
    { SN_LE32(17), 0x96, SN_LE16(4), SN_LE16(24), SN_LE32(5864), SN_LE16(0), 9, "CPlayer_t", 17, "pCurClosestPlayer" },
    { SN_LE32(52), 0x94, SN_LE16(4), SN_LE16(6), SN_LE32(0), 15, "fCurDistanceSqr" },
    { SN_LE32(53), 0x94, SN_LE16(4), SN_LE16(6), SN_LE32(0), 22, "fCurClosestDistanceSqr" },
    { SN_LE32(2110204), 0x90, SN_LE32(1) },
    { SN_LE32(18), 0x96, SN_LE16(4), SN_LE16(24), SN_LE32(744), SN_LE16(0), 21, "CGameObjectInstance_t", 5, "pThis" },
    { SN_LE32(19), 0x96, SN_LE16(4), SN_LE16(24), SN_LE32(368), SN_LE16(0), 5, "CAI_t", 3, "pAI" },
    { SN_LE32(16), 0x96, SN_LE16(4), SN_LE16(24), SN_LE32(5864), SN_LE16(0), 9, "CPlayer_t", 13, "pPlayerTarget" },
    { SN_LE32(2110204), 0x90, SN_LE32(1) },
    { SN_LE32(4), 0x96, SN_LE16(4), SN_LE16(24), SN_LE32(5864), SN_LE16(0), 9, "CPlayer_t", 18, "pPlayerTurretOwner" },
    { SN_LE32(2110268), 0x92, SN_LE32(1) },
    { SN_LE32(2110268), 0x92, SN_LE32(1) },
    { SN_LE32(2110276), 0x90, SN_LE32(1) },
    { SN_LE32(18), 0x96, SN_LE16(4), SN_LE16(24), SN_LE32(744), SN_LE16(0), 21, "CGameObjectInstance_t", 5, "pThis" },
    { SN_LE32(19), 0x96, SN_LE16(4), SN_LE16(24), SN_LE32(368), SN_LE16(0), 5, "CAI_t", 3, "pAI" },
    { SN_LE32(16), 0x96, SN_LE16(4), SN_LE16(24), SN_LE32(5864), SN_LE16(0), 9, "CPlayer_t", 13, "pPlayerTarget" },
    { SN_LE32(2110276), 0x90, SN_LE32(1) },
    { SN_LE32(0xffffffb8), 0x96, SN_LE16(1), SN_LE16(8), SN_LE32(12), SN_LE16(0), 10, "CVector3_t", 18, "vTargetRelativeLoc" },
    { SN_LE32(0xffffffa8), 0x96, SN_LE16(1), SN_LE16(8), SN_LE32(12), SN_LE16(0), 10, "CVector3_t", 13, "vTurretOrient" },
    { SN_LE32(2110492), 0x92, SN_LE32(1) },
    { SN_LE32(2110492), 0x92, SN_LE32(1) },
    { SN_LE32(2110580), 0x92, SN_LE32(58) },
    { SN_LE32(2110628), 0x8E, SN_LE32(752) },
    { SN_LE32(2110628), 0x9C, SN_LE16(29), SN_LE32(392), SN_LE16(31), SN_LE32(0x80ff0000), SN_LE32(0xffffffe0), SN_LE32(0x700000), SN_LE32(0xfffffff8), SN_LE32(770), 49, "C:\\PROJECTS\\DM\\N64\\SOURCE\\AI\\ENEMIES\\TURRETAI.CPP", 18, "Turret_TrackTarget" },
    { SN_LE32(21), 0x96, SN_LE16(17), SN_LE16(24), SN_LE32(744), SN_LE16(0), 21, "CGameObjectInstance_t", 5, "pThis" },
    { SN_LE32(19), 0x96, SN_LE16(17), SN_LE16(24), SN_LE32(368), SN_LE16(0), 5, "CAI_t", 3, "pAI" },
    { SN_LE32(2110628), 0x90, SN_LE32(1) },
    { SN_LE32(20), 0x96, SN_LE16(4), SN_LE16(24), SN_LE32(116), SN_LE16(0), 21, "CTurretIntelligence_t", 6, "pIntel" },
    { SN_LE32(0xfffffe90), 0x96, SN_LE16(1), SN_LE16(8), SN_LE32(136), SN_LE16(0), 15, "s_CAITargetInfo", 10, "TargetInfo" },
    { SN_LE32(22), 0x96, SN_LE16(4), SN_LE16(24), SN_LE32(744), SN_LE16(0), 21, "CGameObjectInstance_t", 7, "pTarget" },
    { SN_LE32(34), 0x94, SN_LE16(4), SN_LE16(6), SN_LE32(0), 10, "TargetRotY" },
    { SN_LE32(53), 0x94, SN_LE16(4), SN_LE16(6), SN_LE32(0), 13, "TargetTiltRot" },
    { SN_LE32(32), 0x94, SN_LE16(4), SN_LE16(6), SN_LE32(0), 5, "Limit" },
    { SN_LE32(52), 0x94, SN_LE16(4), SN_LE16(6), SN_LE32(0), 9, "DeltaRotY" },
    { SN_LE32(0xffffffb8), 0x94, SN_LE16(1), SN_LE16(6), SN_LE32(0), 4, "RotY" },
    { SN_LE32(0xffffff18), 0x96, SN_LE16(1), SN_LE16(8), SN_LE32(12), SN_LE16(0), 10, "CVector3_t", 7, "vTurret" },
    { SN_LE32(0xffffff28), 0x96, SN_LE16(1), SN_LE16(8), SN_LE32(12), SN_LE16(0), 10, "CVector3_t", 7, "vTarget" },
    { SN_LE32(0xffffff38), 0x96, SN_LE16(1), SN_LE16(8), SN_LE32(12), SN_LE16(0), 10, "CVector3_t", 4, "vDir" },
    { SN_LE32(23), 0x94, SN_LE16(4), SN_LE16(4), SN_LE32(0), 8, "bCanFire" },
    { SN_LE32(2110840), 0x90, SN_LE32(38) },
    { SN_LE32(21), 0x96, SN_LE16(4), SN_LE16(24), SN_LE32(744), SN_LE16(0), 21, "CGameObjectInstance_t", 5, "pThis" },
    { SN_LE32(19), 0x96, SN_LE16(4), SN_LE16(24), SN_LE32(368), SN_LE16(0), 5, "CAI_t", 3, "pAI" },
    { SN_LE32(2110840), 0x90, SN_LE32(38) },
    { SN_LE32(0xffffff88), 0x96, SN_LE16(1), SN_LE16(8), SN_LE32(12), SN_LE16(0), 10, "CVector3_t", 6, "vDelta" },
    { SN_LE32(0xffffff48), 0x96, SN_LE16(1), SN_LE16(246), SN_LE32(64), SN_LE16(2), SN_LE32(4), SN_LE32(4), 0, 7, "mfPlane" },
    { SN_LE32(2110840), 0x90, SN_LE32(38) },
    { SN_LE32(17), 0x96, SN_LE16(4), SN_LE16(214), SN_LE32(4), SN_LE16(1), SN_LE32(4), 0, 7, "mfPlane" },
    { SN_LE32(19), 0x96, SN_LE16(4), SN_LE16(24), SN_LE32(368), SN_LE16(0), 5, "CAI_t", 3, "pAI" },
    { SN_LE32(21), 0x96, SN_LE16(4), SN_LE16(24), SN_LE32(744), SN_LE16(0), 21, "CGameObjectInstance_t", 5, "pThis" },
    { SN_LE32(2110840), 0x90, SN_LE32(38) },
    { SN_LE32(0xffffff98), 0x96, SN_LE16(1), SN_LE16(8), SN_LE32(16), SN_LE16(0), 10, "CQuatern_t", 4, "qRot" },
    { SN_LE32(2110840), 0x90, SN_LE32(38) },
    { SN_LE32(21), 0x96, SN_LE16(4), SN_LE16(24), SN_LE32(744), SN_LE16(0), 21, "CGameObjectInstance_t", 5, "pThis" },
    { SN_LE32(19), 0x96, SN_LE16(4), SN_LE16(24), SN_LE32(368), SN_LE16(0), 5, "CAI_t", 3, "pAI" },
    { SN_LE32(2110840), 0x90, SN_LE32(38) },
    { SN_LE32(0xffffffa8), 0x96, SN_LE16(1), SN_LE16(8), SN_LE32(12), SN_LE16(0), 10, "CVector3_t", 7, "vNormal" },
    { SN_LE32(2110840), 0x92, SN_LE32(38) },
    { SN_LE32(2110840), 0x92, SN_LE32(38) },
    { SN_LE32(2110840), 0x92, SN_LE32(38) },
    { SN_LE32(2110840), 0x92, SN_LE32(38) },
    { SN_LE32(2110840), 0x92, SN_LE32(38) },
    { SN_LE32(2110840), 0x92, SN_LE32(38) },
    { SN_LE32(2111460), 0x92, SN_LE32(96) },
    { SN_LE32(2111560), 0x8E, SN_LE32(872) },
    { SN_LE32(2111560), 0x8C, SN_LE16(29), SN_LE32(40), SN_LE16(31), SN_LE32(0x80010000), SN_LE32(0xfffffffc), SN_LE32(217), 49, "C:\\PROJECTS\\DM\\N64\\SOURCE\\AI\\ENEMIES\\TURRETAI.CPP", 20, "Turret_BuildPlaneRot" },
    { SN_LE32(5), 0x96, SN_LE16(17), SN_LE16(24), SN_LE32(744), SN_LE16(0), 21, "CGameObjectInstance_t", 5, "pThis" },
    { SN_LE32(6), 0x96, SN_LE16(17), SN_LE16(24), SN_LE32(368), SN_LE16(0), 5, "CAI_t", 3, "pAI" },
    { SN_LE32(2111560), 0x90, SN_LE32(1) },
    { SN_LE32(0xffffffe8), 0x96, SN_LE16(1), SN_LE16(8), SN_LE32(12), SN_LE16(0), 10, "CVector3_t", 7, "vNormal" },
    { SN_LE32(2111560), 0x92, SN_LE32(1) },
    { SN_LE32(2111628), 0x8E, SN_LE32(225) },
    { SN_LE32(2111628), 0x8C, SN_LE16(29), SN_LE32(0), SN_LE16(31), SN_LE32(0x0), SN_LE32(0), SN_LE32(356), 49, "C:\\PROJECTS\\DM\\N64\\SOURCE\\AI\\ENEMIES\\TURRETAI.CPP", 16, "Turret_Construct" },
    { SN_LE32(4), 0x96, SN_LE16(17), SN_LE16(24), SN_LE32(744), SN_LE16(0), 21, "CGameObjectInstance_t", 5, "pThis" },
    { SN_LE32(5), 0x96, SN_LE16(17), SN_LE16(24), SN_LE32(368), SN_LE16(0), 5, "CAI_t", 3, "pAI" },
    { SN_LE32(2111628), 0x90, SN_LE32(2) },
    { SN_LE32(2111744), 0x92, SN_LE32(30) },
    { SN_LE32(2111752), 0x8E, SN_LE32(385) },
    { SN_LE32(2111752), 0x8C, SN_LE16(29), SN_LE32(32), SN_LE16(31), SN_LE32(0x80070000), SN_LE32(0xfffffffc), SN_LE32(389), 49, "C:\\PROJECTS\\DM\\N64\\SOURCE\\AI\\ENEMIES\\TURRETAI.CPP", 12, "Turret_Setup" },
    { SN_LE32(16), 0x96, SN_LE16(17), SN_LE16(24), SN_LE32(744), SN_LE16(0), 21, "CGameObjectInstance_t", 5, "pThis" },
    { SN_LE32(18), 0x96, SN_LE16(17), SN_LE16(24), SN_LE32(368), SN_LE16(0), 5, "CAI_t", 3, "pAI" },
    { SN_LE32(2111752), 0x90, SN_LE32(1) },
    { SN_LE32(17), 0x96, SN_LE16(4), SN_LE16(24), SN_LE32(116), SN_LE16(0), 21, "CTurretIntelligence_t", 6, "pIntel" },
    { SN_LE32(2111964), 0x92, SN_LE32(42) },
    { SN_LE32(2111992), 0x8E, SN_LE32(431) },
    { SN_LE32(2111992), 0x8C, SN_LE16(29), SN_LE32(32), SN_LE16(31), SN_LE32(0x80030000), SN_LE32(0xfffffff8), SN_LE32(452), 49, "C:\\PROJECTS\\DM\\N64\\SOURCE\\AI\\ENEMIES\\TURRETAI.CPP", 14, "Turret_Advance" },
    { SN_LE32(17), 0x96, SN_LE16(17), SN_LE16(24), SN_LE32(744), SN_LE16(0), 21, "CGameObjectInstance_t", 5, "pThis" },
    { SN_LE32(16), 0x96, SN_LE16(17), SN_LE16(24), SN_LE32(368), SN_LE16(0), 5, "CAI_t", 3, "pAI" },
    { SN_LE32(2112148), 0x8E, SN_LE32(473) },
    { SN_LE32(2112148), 0x8C, SN_LE16(29), SN_LE32(0), SN_LE16(31), SN_LE32(0x0), SN_LE32(0), SN_LE32(895), 49, "C:\\PROJECTS\\DM\\N64\\SOURCE\\AI\\ENEMIES\\TURRETAI.CPP", 20, "Turret_Anim_ACTIVATE" },
    { SN_LE32(4), 0x96, SN_LE16(17), SN_LE16(24), SN_LE32(744), SN_LE16(0), 21, "CGameObjectInstance_t", 5, "pThis" },
    { SN_LE32(5), 0x96, SN_LE16(17), SN_LE16(24), SN_LE32(368), SN_LE16(0), 5, "CAI_t", 3, "pAI" },
    { SN_LE32(2112148), 0x90, SN_LE32(2) },
    { SN_LE32(2112168), 0x92, SN_LE32(9) },
    { SN_LE32(2112176), 0x8E, SN_LE32(903) },
    { SN_LE32(2112176), 0x8C, SN_LE16(29), SN_LE32(24), SN_LE16(31), SN_LE32(0x80000000), SN_LE32(0xfffffff8), SN_LE32(906), 49, "C:\\PROJECTS\\DM\\N64\\SOURCE\\AI\\ENEMIES\\TURRETAI.CPP", 20, "Turret_Code_ACTIVATE" },
    { SN_LE32(4), 0x96, SN_LE16(17), SN_LE16(24), SN_LE32(744), SN_LE16(0), 21, "CGameObjectInstance_t", 5, "pThis" },
    { SN_LE32(5), 0x96, SN_LE16(17), SN_LE16(24), SN_LE32(368), SN_LE16(0), 5, "CAI_t", 3, "pAI" },
    { SN_LE32(2112216), 0x8E, SN_LE32(909) },
    { SN_LE32(2112216), 0x8C, SN_LE16(29), SN_LE32(32), SN_LE16(31), SN_LE32(0x80030000), SN_LE32(0xfffffff8), SN_LE32(918), 49, "C:\\PROJECTS\\DM\\N64\\SOURCE\\AI\\ENEMIES\\TURRETAI.CPP", 16, "Turret_Code_IDLE" },
    { SN_LE32(16), 0x96, SN_LE16(17), SN_LE16(24), SN_LE32(744), SN_LE16(0), 21, "CGameObjectInstance_t", 5, "pThis" },
    { SN_LE32(17), 0x96, SN_LE16(17), SN_LE16(24), SN_LE32(368), SN_LE16(0), 5, "CAI_t", 3, "pAI" },
    { SN_LE32(2112284), 0x8E, SN_LE32(921) },
    { SN_LE32(2112284), 0x8C, SN_LE16(29), SN_LE32(32), SN_LE16(31), SN_LE32(0x80030000), SN_LE32(0xfffffff8), SN_LE32(930), 49, "C:\\PROJECTS\\DM\\N64\\SOURCE\\AI\\ENEMIES\\TURRETAI.CPP", 16, "Turret_Code_FIRE" },
    { SN_LE32(16), 0x96, SN_LE16(17), SN_LE16(24), SN_LE32(744), SN_LE16(0), 21, "CGameObjectInstance_t", 5, "pThis" },
    { SN_LE32(17), 0x96, SN_LE16(17), SN_LE16(24), SN_LE32(368), SN_LE16(0), 5, "CAI_t", 3, "pAI" },
    { SN_LE32(2112352), 0x8E, SN_LE32(933) },
    { SN_LE32(2112352), 0x8C, SN_LE16(29), SN_LE32(40), SN_LE16(31), SN_LE32(0x80070000), SN_LE32(0xfffffffc), SN_LE32(942), 49, "C:\\PROJECTS\\DM\\N64\\SOURCE\\AI\\ENEMIES\\TURRETAI.CPP", 18, "Turret_Setup_DEATH" },
    { SN_LE32(18), 0x96, SN_LE16(17), SN_LE16(24), SN_LE32(744), SN_LE16(0), 21, "CGameObjectInstance_t", 5, "pThis" },
    { SN_LE32(16), 0x96, SN_LE16(17), SN_LE16(24), SN_LE32(368), SN_LE16(0), 5, "CAI_t", 3, "pAI" },
    { SN_LE32(2112352), 0x90, SN_LE32(1) },
    { SN_LE32(2), 0x96, SN_LE16(4), SN_LE16(24), SN_LE32(56), SN_LE16(0), 26, "CCommonEnemyIntelligence_t", 6, "pIntel" },
    { SN_LE32(2112496), 0x92, SN_LE32(28) },
    { SN_LE32(2112520), 0x8E, SN_LE32(969) },
    { SN_LE32(2112520), 0x8C, SN_LE16(29), SN_LE32(24), SN_LE16(31), SN_LE32(0x80000000), SN_LE32(0xfffffff8), SN_LE32(972), 49, "C:\\PROJECTS\\DM\\N64\\SOURCE\\AI\\ENEMIES\\TURRETAI.CPP", 17, "Turret_Code_DEATH" },
    { SN_LE32(4), 0x96, SN_LE16(17), SN_LE16(24), SN_LE32(744), SN_LE16(0), 21, "CGameObjectInstance_t", 5, "pThis" },
    { SN_LE32(5), 0x96, SN_LE16(17), SN_LE16(24), SN_LE32(368), SN_LE16(0), 5, "CAI_t", 3, "pAI" },
    { SN_LE32(2112576), 0x8E, SN_LE32(981) },
    { SN_LE32(2112576), 0x8C, SN_LE16(29), SN_LE32(24), SN_LE16(31), SN_LE32(0x80010000), SN_LE32(0xfffffffc), SN_LE32(131), 49, "C:\\PROJECTS\\DM\\N64\\SOURCE\\AI\\ENEMIES\\TURRETAI.CPP", 29, "Turret_LinkEffect_MakeVisible" },
    { SN_LE32(16), 0x96, SN_LE16(17), SN_LE16(24), SN_LE32(744), SN_LE16(0), 21, "CGameObjectInstance_t", 5, "pThis" },
    { SN_LE32(5), 0x96, SN_LE16(17), SN_LE16(24), SN_LE32(368), SN_LE16(0), 5, "CAI_t", 3, "pAI" },
    { SN_LE32(6), 0x96, SN_LE16(17), SN_LE16(24), SN_LE32(20), SN_LE16(0), 10, "CROMLink_t", 8, "pROMLink" },
    { SN_LE32(2112644), 0x8E, SN_LE32(141) },
    { SN_LE32(2112644), 0x8C, SN_LE16(29), SN_LE32(32), SN_LE16(31), SN_LE32(0x80070000), SN_LE32(0xfffffffc), SN_LE32(108), 49, "C:\\PROJECTS\\DM\\N64\\SOURCE\\AI\\ENEMIES\\TURRETAI.CPP", 26, "Turret_LinkEffect_Activate" },
    { SN_LE32(16), 0x96, SN_LE16(17), SN_LE16(24), SN_LE32(744), SN_LE16(0), 21, "CGameObjectInstance_t", 5, "pThis" },
    { SN_LE32(17), 0x96, SN_LE16(17), SN_LE16(24), SN_LE32(368), SN_LE16(0), 5, "CAI_t", 3, "pAI" },
    { SN_LE32(18), 0x96, SN_LE16(17), SN_LE16(24), SN_LE32(20), SN_LE16(0), 10, "CROMLink_t", 8, "pROMLink" },
    { SN_LE32(2112764), 0x8E, SN_LE32(124) },
    { SN_LE32(2112764), 0x8C, SN_LE16(29), SN_LE32(56), SN_LE16(31), SN_LE32(0x80010000), SN_LE32(0xfffffffc), SN_LE32(230), 49, "C:\\PROJECTS\\DM\\N64\\SOURCE\\AI\\ENEMIES\\TURRETAI.CPP", 23, "Turret_BuildPlaneOrient" },
    { SN_LE32(4), 0x96, SN_LE16(17), SN_LE16(24), SN_LE32(744), SN_LE16(0), 21, "CGameObjectInstance_t", 5, "pThis" },
    { SN_LE32(5), 0x96, SN_LE16(17), SN_LE16(24), SN_LE32(368), SN_LE16(0), 5, "CAI_t", 3, "pAI" },
    { SN_LE32(16), 0x96, SN_LE16(17), SN_LE16(214), SN_LE32(4), SN_LE16(1), SN_LE32(4), 0, 7, "mfPlane" },
    { SN_LE32(2112764), 0x90, SN_LE32(1) },
    { SN_LE32(0xffffffd8), 0x96, SN_LE16(1), SN_LE16(8), SN_LE32(16), SN_LE16(0), 10, "CQuatern_t", 4, "qRot" },
    { SN_LE32(2112764), 0x90, SN_LE32(1) },
    { SN_LE32(5), 0x96, SN_LE16(4), SN_LE16(24), SN_LE32(368), SN_LE16(0), 5, "CAI_t", 3, "pAI" },
    { SN_LE32(2112764), 0x90, SN_LE32(1) },
    { SN_LE32(0xffffffe8), 0x96, SN_LE16(1), SN_LE16(8), SN_LE32(12), SN_LE16(0), 10, "CVector3_t", 7, "vNormal" },
    { SN_LE32(2112764), 0x92, SN_LE32(1) },
    { SN_LE32(2112764), 0x92, SN_LE32(1) },
    { SN_LE32(2112764), 0x92, SN_LE32(1) },
    { SN_LE32(2112844), 0x8E, SN_LE32(235) },
    { SN_LE32(2112844), 0x8C, SN_LE16(29), SN_LE32(152), SN_LE16(31), SN_LE32(0x800f0000), SN_LE32(0xfffffff8), SN_LE32(242), 49, "C:\\PROJECTS\\DM\\N64\\SOURCE\\AI\\ENEMIES\\TURRETAI.CPP", 32, "Turret_MoveTargetIntoTurretSpace" },
    { SN_LE32(4), 0x96, SN_LE16(17), SN_LE16(24), SN_LE32(744), SN_LE16(0), 21, "CGameObjectInstance_t", 5, "pThis" },
    { SN_LE32(5), 0x96, SN_LE16(17), SN_LE16(24), SN_LE32(368), SN_LE16(0), 5, "CAI_t", 3, "pAI" },
    { SN_LE32(19), 0x96, SN_LE16(17), SN_LE16(24), SN_LE32(12), SN_LE16(0), 10, "CVector3_t", 11, "pvTurretEye" },
    { SN_LE32(18), 0x96, SN_LE16(17), SN_LE16(24), SN_LE32(12), SN_LE16(0), 10, "CVector3_t", 8, "pvTarget" },
    { SN_LE32(2112844), 0x90, SN_LE32(1) },
    { SN_LE32(0xffffff78), 0x96, SN_LE16(1), SN_LE16(246), SN_LE32(64), SN_LE16(2), SN_LE32(4), SN_LE32(4), 0, 7, "mfPlane" },
    { SN_LE32(0xffffffb8), 0x96, SN_LE16(1), SN_LE16(8), SN_LE32(12), SN_LE16(0), 10, "CVector3_t", 6, "vDelta" },
    { SN_LE32(2112844), 0x90, SN_LE32(1) },
    { SN_LE32(5), 0x96, SN_LE16(4), SN_LE16(24), SN_LE32(368), SN_LE16(0), 5, "CAI_t", 3, "pAI" },
    { SN_LE32(17), 0x96, SN_LE16(4), SN_LE16(214), SN_LE32(4), SN_LE16(1), SN_LE32(4), 0, 7, "mfPlane" },
    { SN_LE32(2112844), 0x90, SN_LE32(1) },
    { SN_LE32(0xffffffc8), 0x96, SN_LE16(1), SN_LE16(8), SN_LE32(16), SN_LE16(0), 10, "CQuatern_t", 4, "qRot" },
    { SN_LE32(2112844), 0x90, SN_LE32(1) },
    { SN_LE32(5), 0x96, SN_LE16(4), SN_LE16(24), SN_LE32(368), SN_LE16(0), 5, "CAI_t", 3, "pAI" },
    { SN_LE32(2112844), 0x90, SN_LE32(1) },
    { SN_LE32(0xffffffd8), 0x96, SN_LE16(1), SN_LE16(8), SN_LE32(12), SN_LE16(0), 10, "CVector3_t", 7, "vNormal" },
    { SN_LE32(2112844), 0x92, SN_LE32(1) },
    { SN_LE32(2112844), 0x92, SN_LE32(1) },
    { SN_LE32(2112844), 0x92, SN_LE32(1) },
    { SN_LE32(2112844), 0x92, SN_LE32(1) },
    { SN_LE32(2112844), 0x92, SN_LE32(1) },
    { SN_LE32(2113008), 0x8E, SN_LE32(257) },
    { SN_LE32(2113008), 0x8C, SN_LE16(29), SN_LE32(32), SN_LE16(31), SN_LE32(0x80070000), SN_LE32(0xfffffffc), SN_LE32(311), 49, "C:\\PROJECTS\\DM\\N64\\SOURCE\\AI\\ENEMIES\\TURRETAI.CPP", 21, "Turret_SpecialEffects" },
    { SN_LE32(18), 0x96, SN_LE16(17), SN_LE16(214), SN_LE32(4), SN_LE16(1), SN_LE32(4), 0, 7, "mfLocal" },
    { SN_LE32(16), 0x96, SN_LE16(17), SN_LE16(24), SN_LE32(124), SN_LE16(0), 15, "CAnimNodeInfo_t", 13, "pAnimNodeInfo" },
    { SN_LE32(2113008), 0x90, SN_LE32(1) },
    { SN_LE32(17), 0x96, SN_LE16(4), SN_LE16(24), SN_LE32(116), SN_LE16(0), 21, "CTurretIntelligence_t", 6, "pIntel" },
    { SN_LE32(2113120), 0x92, SN_LE32(15) },
    { SN_LE32(2113144), 0x8E, SN_LE32(325) },
    { SN_LE32(2113144), 0x8C, SN_LE16(29), SN_LE32(24), SN_LE16(31), SN_LE32(0x80000000), SN_LE32(0xfffffff8), SN_LE32(330), 49, "C:\\PROJECTS\\DM\\N64\\SOURCE\\AI\\ENEMIES\\TURRETAI.CPP", 21, "Turret_DecreaseHealth" },
    { SN_LE32(4), 0x96, SN_LE16(17), SN_LE16(24), SN_LE32(744), SN_LE16(0), 21, "CGameObjectInstance_t", 5, "pThis" },
    { SN_LE32(5), 0x96, SN_LE16(17), SN_LE16(24), SN_LE32(368), SN_LE16(0), 5, "CAI_t", 3, "pAI" },
    { SN_LE32(6), 0x96, SN_LE16(17), SN_LE16(24), SN_LE32(20), SN_LE16(0), 13, "CDamageInfo_t", 5, "pInfo" },
    { SN_LE32(2113200), 0x8E, SN_LE32(334) },
    { SN_LE32(2113200), 0x8C, SN_LE16(29), SN_LE32(0), SN_LE16(31), SN_LE32(0x0), SN_LE32(0), SN_LE32(614), 49, "C:\\PROJECTS\\DM\\N64\\SOURCE\\AI\\ENEMIES\\TURRETAI.CPP", 26, "AI_DynTurretOpposingPlayer" },
    { SN_LE32(4), 0x96, SN_LE16(17), SN_LE16(24), SN_LE32(744), SN_LE16(0), 21, "CGameObjectInstance_t", 5, "pThis" },
    { SN_LE32(5), 0x96, SN_LE16(17), SN_LE16(24), SN_LE32(368), SN_LE16(0), 5, "CAI_t", 3, "pAI" },
    { SN_LE32(6), 0x96, SN_LE16(17), SN_LE16(24), SN_LE32(5864), SN_LE16(0), 9, "CPlayer_t", 13, "pPlayerTarget" },
    { SN_LE32(2113200), 0x90, SN_LE32(2) },
    { SN_LE32(3), 0x96, SN_LE16(4), SN_LE16(24), SN_LE32(5864), SN_LE16(0), 9, "CPlayer_t", 18, "pPlayerTurretOwner" },
    { SN_LE32(2113276), 0x92, SN_LE32(32) },
    { SN_LE32(2113284), 0x8E, SN_LE32(645) },
    { SN_LE32(2113284), 0x9C, SN_LE16(29), SN_LE32(88), SN_LE16(31), SN_LE32(0x80070000), SN_LE32(0xfffffff4), SN_LE32(0x100000), SN_LE32(0xfffffff8), SN_LE32(651), 49, "C:\\PROJECTS\\DM\\N64\\SOURCE\\AI\\ENEMIES\\TURRETAI.CPP", 24, "AI_DynTurretCanSeePlayer" },
    { SN_LE32(17), 0x96, SN_LE16(17), SN_LE16(24), SN_LE32(744), SN_LE16(0), 21, "CGameObjectInstance_t", 5, "pThis" },
    { SN_LE32(16), 0x96, SN_LE16(17), SN_LE16(24), SN_LE32(368), SN_LE16(0), 5, "CAI_t", 3, "pAI" },
    { SN_LE32(18), 0x96, SN_LE16(17), SN_LE16(24), SN_LE32(5864), SN_LE16(0), 9, "CPlayer_t", 13, "pPlayerTarget" },
    { SN_LE32(2113284), 0x90, SN_LE32(1) },
    { SN_LE32(0xffffffc8), 0x96, SN_LE16(1), SN_LE16(8), SN_LE32(12), SN_LE16(0), 10, "CVector3_t", 13, "vTurretOrient" },
    { SN_LE32(0xffffffd8), 0x96, SN_LE16(1), SN_LE16(8), SN_LE32(12), SN_LE16(0), 10, "CVector3_t", 18, "vTargetRelativeLoc" },
    { SN_LE32(2113552), 0x92, SN_LE32(38) },
    { SN_LE32(2113580), 0x8E, SN_LE32(688) },
    { SN_LE32(2113584), 0x88, SN_LE32(360), 49, "C:\\PROJECTS\\DM\\N64\\SOURCE\\AI\\DEVICES\\ACTIONAI.CPP" },
    { SN_LE32(2113616), 0x80 },
    { SN_LE32(2113620), 0x82, 7 },
    { SN_LE32(2113624), 0x86, SN_LE32(361) },
    { SN_LE32(2113628), 0x82, 7 },
    { SN_LE32(2113640), 0x82, 3 },
    { SN_LE32(2113660), 0x82, 2 },
    { SN_LE32(2113680), 0x82, 2 },
    { SN_LE32(2113696), 0x82, 3 },
    { SN_LE32(2113708), 0x82, 2 },
    { SN_LE32(2113736), 0x82, 4 },
    { SN_LE32(2113740), 0x80 },
    { SN_LE32(2113744), 0x82, 5 },
    { SN_LE32(2113748), 0x86, SN_LE32(385) },
    { SN_LE32(2113752), 0x82, 2 },
    { SN_LE32(2113756), 0x82, 3 },
    { SN_LE32(2113764), 0x82, 5 },
    { SN_LE32(2113772), 0x86, SN_LE32(370) },
    { SN_LE32(2113800), 0x82, 36 },
    { SN_LE32(2113816), 0x82, 4 },
    { SN_LE32(2113836), 0x82, 2 },
    { SN_LE32(2113860), 0x82, 2 },
    { SN_LE32(2113872), 0x82, 4 },
    { SN_LE32(2113876), 0x86, SN_LE32(414) },
    { SN_LE32(2113880), 0x80 },
    { SN_LE32(2113892), 0x82, 3 },
    { SN_LE32(2113896), 0x86, SN_LE32(415) },
    { SN_LE32(2113900), 0x80 },
    { SN_LE32(2113912), 0x82, 2 },
    { SN_LE32(2113924), 0x82, 0 },
    { SN_LE32(2113940), 0x82, 2 },
    { SN_LE32(2113972), 0x82, 2 },
    { SN_LE32(2113976), 0x82, 0 },
    { SN_LE32(2113980), 0x80 },
    { SN_LE32(2113992), 0x80 },
    { SN_LE32(2113996), 0x80 },
    { SN_LE32(2114000), 0x86, SN_LE32(424) },
    { SN_LE32(2114004), 0x80 },
    { SN_LE32(2114008), 0x86, SN_LE32(424) },
    { SN_LE32(2114012), 0x80 },
    { SN_LE32(2114020), 0x82, 2 },
    { SN_LE32(2114028), 0x80 },
    { SN_LE32(2114032), 0x82, 2 },
    { SN_LE32(2114072), 0x82, 4 },
    { SN_LE32(2114080), 0x82, 4 },
    { SN_LE32(2114088), 0x82, 4 },
    { SN_LE32(2114096), 0x82, 4 },
    { SN_LE32(2114104), 0x82, 3 },
    { SN_LE32(2114116), 0x82, 8 },
    { SN_LE32(2114124), 0x80 },
    { SN_LE32(2114132), 0x82, 2 },
    { SN_LE32(2114144), 0x80 },
    { SN_LE32(2114168), 0x82, 2 },
    { SN_LE32(2114172), 0x80 },
    { SN_LE32(2114180), 0x82, 12 },
    { SN_LE32(2114192), 0x82, 3 },
    { SN_LE32(2114208), 0x82, 2 },
    { SN_LE32(2114216), 0x80 },
    { SN_LE32(2114228), 0x82, 4 },
    { SN_LE32(2114240), 0x80 },
    { SN_LE32(2114252), 0x82, 3 },
    { SN_LE32(2114268), 0x82, 4 },
    { SN_LE32(2114280), 0x82, 4 },
    { SN_LE32(2114312), 0x82, 7 },
    { SN_LE32(2114328), 0x80 },
    { SN_LE32(2114336), 0x82, 10 },
    { SN_LE32(2114360), 0x82, 4 },
    { SN_LE32(2114388), 0x82, 6 },
    { SN_LE32(2114392), 0x86, SN_LE32(522) },
    { SN_LE32(2114396), 0x82, 4 },
    { SN_LE32(2114404), 0x82, 3 },
    { SN_LE32(2114408), 0x82, 3 },
    { SN_LE32(2114416), 0x86, SN_LE32(529) },
    { SN_LE32(2114424), 0x82, 6 },
    { SN_LE32(2114472), 0x82, 6 },
    { SN_LE32(2114500), 0x80 },
    { SN_LE32(2114508), 0x82, 4 },
    { SN_LE32(2114512), 0x82, 6 },
    { SN_LE32(2114528), 0x86, SN_LE32(242) },
    { SN_LE32(2114556), 0x80 },
    { SN_LE32(2114560), 0x82, 4 },
    { SN_LE32(2114564), 0x82, 0 },
    { SN_LE32(2114584), 0x82, 3 },
    { SN_LE32(2114592), 0x82, 4 },
    { SN_LE32(2114604), 0x82, 2 },
    { SN_LE32(2114612), 0x80 },
    { SN_LE32(2114616), 0x80 },
    { SN_LE32(2114624), 0x82, 3 },
    { SN_LE32(2114632), 0x80 },
    { SN_LE32(2114640), 0x82, 2 },
    { SN_LE32(2114664), 0x86, SN_LE32(173) },
    { SN_LE32(2114676), 0x80 },
    { SN_LE32(2114688), 0x80 },
    { SN_LE32(2114692), 0x80 },
    { SN_LE32(2114696), 0x80 },
    { SN_LE32(2114700), 0x82, 4 },
    { SN_LE32(2114720), 0x80 },
    { SN_LE32(2114740), 0x82, 2 },
    { SN_LE32(2114760), 0x82, 4 },
    { SN_LE32(2114780), 0x82, 4 },
    { SN_LE32(2114788), 0x86, SN_LE32(188) },
    { SN_LE32(2114792), 0x82, 4 },
    { SN_LE32(2114800), 0x80 },
    { SN_LE32(2114812), 0x82, 3 },
    { SN_LE32(2114824), 0x82, 3 },
    { SN_LE32(2114884), 0x82, 4 },
    { SN_LE32(2114896), 0x82, 2 },
    { SN_LE32(2114904), 0x82, 5 },
    { SN_LE32(2114916), 0x82, 3 },
    { SN_LE32(2114924), 0x82, 4 },
    { SN_LE32(2114928), 0x86, SN_LE32(216) },
    { SN_LE32(2114936), 0x80 },
    { SN_LE32(2114944), 0x80 },
    { SN_LE32(2114952), 0x82, 2 },
    { SN_LE32(2114972), 0x82, 57 },
    { SN_LE32(2114980), 0x82, 3 },
    { SN_LE32(2114988), 0x80 },
    { SN_LE32(2115000), 0x82, 2 },
    { SN_LE32(2115012), 0x82, 3 },
    { SN_LE32(2115020), 0x82, 3 },
    { SN_LE32(2115040), 0x82, 2 },
    { SN_LE32(2115052), 0x86, SN_LE32(289) },
    { SN_LE32(2115056), 0x82, 2 },
    { SN_LE32(2115064), 0x82, 3 },
    { SN_LE32(2115080), 0x82, 3 },
    { SN_LE32(2115104), 0x82, 13 },
    { SN_LE32(2115112), 0x82, 3 },
    { SN_LE32(2115120), 0x80 },
    { SN_LE32(2115132), 0x82, 3 },
    { SN_LE32(2115140), 0x80 },
    { SN_LE32(2115152), 0x82, 4 },
    { SN_LE32(2115160), 0x82, 3 },
    { SN_LE32(2115176), 0x82, 4 },
    { SN_LE32(2115192), 0x86, SN_LE32(325) },
    { SN_LE32(2115200), 0x80 },
    { SN_LE32(2115204), 0x82, 3 },
    { SN_LE32(2115212), 0x82, 3 },
    { SN_LE32(2115228), 0x80 },
    { SN_LE32(2115240), 0x82, 3 },
    { SN_LE32(2115256), 0x82, 3 },
    { SN_LE32(2115272), 0x82, 3 },
    { SN_LE32(2115284), 0x82, 4 },
    { SN_LE32(2115300), 0x82, 2 },
    { SN_LE32(2115304), 0x80 },
    { SN_LE32(2115316), 0x82, 4 },
    { SN_LE32(2115332), 0x80 },
    { SN_LE32(2115344), 0x82, 3 },
    { SN_LE32(2115368), 0x82, 222 },
    { SN_LE32(2115384), 0x82, 6 },
    { SN_LE32(2115412), 0x82, 2 },
    { SN_LE32(2115420), 0x80 },
    { SN_LE32(2115432), 0x80 },
    { SN_LE32(2115440), 0x86, SN_LE32(99) },
    { SN_LE32(2115444), 0x82, 0 },
    { SN_LE32(2115448), 0x82, 5 },
    { SN_LE32(2115468), 0x82, 4 },
    { SN_LE32(2115476), 0x82, 3 },
    { SN_LE32(2115484), 0x86, SN_LE32(108) },
    { SN_LE32(2115488), 0x82, 3 },
    { SN_LE32(2115516), 0x82, 11 },
    { SN_LE32(2115520), 0x82, 0 },
    { SN_LE32(2115524), 0x82, 4 },
    { SN_LE32(2115544), 0x82, 4 },
    { SN_LE32(2115552), 0x82, 3 },
    { SN_LE32(2115560), 0x86, SN_LE32(130) },
    { SN_LE32(2115564), 0x82, 3 },
    { SN_LE32(2115592), 0x84, SN_LE16(433) },
    { SN_LE32(2115600), 0x82, 3 },
    { SN_LE32(2115632), 0x86, SN_LE32(568) },
    { SN_LE32(2115644), 0x80 },
    { SN_LE32(2115668), 0x82, 3 },
    { SN_LE32(2115688), 0x82, 0 },
    { SN_LE32(2115688), 0x8A },
    { SN_LE32(0), 0x94, SN_LE16(13), SN_LE16(12), SN_LE32(0), 2, "u8" },
    { SN_LE32(0), 0x94, SN_LE16(13), SN_LE16(2), SN_LE32(0), 2, "s8" },
    { SN_LE32(0), 0x94, SN_LE16(13), SN_LE16(12), SN_LE32(0), 3, "vu8" },
    { SN_LE32(0), 0x94, SN_LE16(13), SN_LE16(2), SN_LE32(0), 3, "vs8" },
    { SN_LE32(0), 0x94, SN_LE16(13), SN_LE16(13), SN_LE32(0), 3, "u16" },
    { SN_LE32(0), 0x94, SN_LE16(13), SN_LE16(3), SN_LE32(0), 3, "s16" },
    { SN_LE32(0), 0x94, SN_LE16(13), SN_LE16(13), SN_LE32(0), 4, "vu16" },
    { SN_LE32(0), 0x94, SN_LE16(13), SN_LE16(3), SN_LE32(0), 4, "vs16" },
    { SN_LE32(0), 0x94, SN_LE16(13), SN_LE16(15), SN_LE32(0), 3, "u32" },
    { SN_LE32(0), 0x94, SN_LE16(13), SN_LE16(5), SN_LE32(0), 3, "s32" },
    { SN_LE32(0), 0x94, SN_LE16(13), SN_LE16(15), SN_LE32(0), 4, "vu32" },
    { SN_LE32(0), 0x94, SN_LE16(13), SN_LE16(5), SN_LE32(0), 4, "vs32" },
    { SN_LE32(0), 0x94, SN_LE16(13), SN_LE16(15), SN_LE32(0), 3, "u64" },
    { SN_LE32(0), 0x94, SN_LE16(13), SN_LE16(5), SN_LE32(0), 3, "s64" },
    { SN_LE32(0), 0x94, SN_LE16(13), SN_LE16(15), SN_LE32(0), 4, "vu64" },
    { SN_LE32(0), 0x94, SN_LE16(13), SN_LE16(5), SN_LE32(0), 4, "vs64" },
    { SN_LE32(0), 0x94, SN_LE16(13), SN_LE16(6), SN_LE32(0), 3, "f32" },
    { SN_LE32(0), 0x94, SN_LE16(13), SN_LE16(7), SN_LE32(0), 3, "f64" },
    { SN_LE32(0), 0x94, SN_LE16(13), SN_LE16(5), SN_LE32(0), 5, "OSPri" },
    { SN_LE32(0), 0x94, SN_LE16(13), SN_LE16(5), SN_LE32(0), 4, "OSId" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(8), 6, ".0fake" },
    { SN_LE32(0), 0x94, SN_LE16(8), SN_LE16(6), SN_LE32(0), 5, "f_odd" },
    { SN_LE32(4), 0x94, SN_LE16(8), SN_LE16(6), SN_LE32(0), 6, "f_even" },
    { SN_LE32(8), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(8), SN_LE16(0), 6, ".0fake", 4, ".eos" },
    { SN_LE32(0), 0x94, SN_LE16(12), SN_LE16(9), SN_LE32(8), 6, ".1fake" },
    { SN_LE32(0), 0x96, SN_LE16(11), SN_LE16(8), SN_LE32(8), SN_LE16(0), 6, ".0fake", 1, "f" },
    { SN_LE32(0), 0x94, SN_LE16(11), SN_LE16(7), SN_LE32(0), 1, "d" },
    { SN_LE32(8), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(8), SN_LE16(0), 6, ".1fake", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(9), SN_LE32(8), SN_LE16(0), 6, ".1fake", 6, "__OSfp" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(528), 6, ".2fake" },
    { SN_LE32(0), 0x94, SN_LE16(8), SN_LE16(15), SN_LE32(0), 2, "at" },
    { SN_LE32(8), 0x94, SN_LE16(8), SN_LE16(15), SN_LE32(0), 2, "v0" },
    { SN_LE32(16), 0x94, SN_LE16(8), SN_LE16(15), SN_LE32(0), 2, "v1" },
    { SN_LE32(24), 0x94, SN_LE16(8), SN_LE16(15), SN_LE32(0), 2, "a0" },
    { SN_LE32(32), 0x94, SN_LE16(8), SN_LE16(15), SN_LE32(0), 2, "a1" },
    { SN_LE32(40), 0x94, SN_LE16(8), SN_LE16(15), SN_LE32(0), 2, "a2" },
    { SN_LE32(48), 0x94, SN_LE16(8), SN_LE16(15), SN_LE32(0), 2, "a3" },
    { SN_LE32(56), 0x94, SN_LE16(8), SN_LE16(15), SN_LE32(0), 2, "t0" },
    { SN_LE32(64), 0x94, SN_LE16(8), SN_LE16(15), SN_LE32(0), 2, "t1" },
    { SN_LE32(72), 0x94, SN_LE16(8), SN_LE16(15), SN_LE32(0), 2, "t2" },
    { SN_LE32(80), 0x94, SN_LE16(8), SN_LE16(15), SN_LE32(0), 2, "t3" },
    { SN_LE32(88), 0x94, SN_LE16(8), SN_LE16(15), SN_LE32(0), 2, "t4" },
    { SN_LE32(96), 0x94, SN_LE16(8), SN_LE16(15), SN_LE32(0), 2, "t5" },
    { SN_LE32(104), 0x94, SN_LE16(8), SN_LE16(15), SN_LE32(0), 2, "t6" },
    { SN_LE32(112), 0x94, SN_LE16(8), SN_LE16(15), SN_LE32(0), 2, "t7" },
    { SN_LE32(120), 0x94, SN_LE16(8), SN_LE16(15), SN_LE32(0), 2, "s0" },
    { SN_LE32(128), 0x94, SN_LE16(8), SN_LE16(15), SN_LE32(0), 2, "s1" },
    { SN_LE32(136), 0x94, SN_LE16(8), SN_LE16(15), SN_LE32(0), 2, "s2" },
    { SN_LE32(144), 0x94, SN_LE16(8), SN_LE16(15), SN_LE32(0), 2, "s3" },
    { SN_LE32(152), 0x94, SN_LE16(8), SN_LE16(15), SN_LE32(0), 2, "s4" },
    { SN_LE32(160), 0x94, SN_LE16(8), SN_LE16(15), SN_LE32(0), 2, "s5" },
    { SN_LE32(168), 0x94, SN_LE16(8), SN_LE16(15), SN_LE32(0), 2, "s6" },
    { SN_LE32(176), 0x94, SN_LE16(8), SN_LE16(15), SN_LE32(0), 2, "s7" },
    { SN_LE32(184), 0x94, SN_LE16(8), SN_LE16(15), SN_LE32(0), 2, "t8" },
    { SN_LE32(192), 0x94, SN_LE16(8), SN_LE16(15), SN_LE32(0), 2, "t9" },
    { SN_LE32(200), 0x94, SN_LE16(8), SN_LE16(15), SN_LE32(0), 2, "gp" },
    { SN_LE32(208), 0x94, SN_LE16(8), SN_LE16(15), SN_LE32(0), 2, "sp" },
    { SN_LE32(216), 0x94, SN_LE16(8), SN_LE16(15), SN_LE32(0), 2, "s8" },
    { SN_LE32(224), 0x94, SN_LE16(8), SN_LE16(15), SN_LE32(0), 2, "ra" },
    { SN_LE32(232), 0x94, SN_LE16(8), SN_LE16(15), SN_LE32(0), 2, "lo" },
    { SN_LE32(240), 0x94, SN_LE16(8), SN_LE16(15), SN_LE32(0), 2, "hi" },
    { SN_LE32(248), 0x94, SN_LE16(8), SN_LE16(15), SN_LE32(0), 2, "sr" },
    { SN_LE32(252), 0x94, SN_LE16(8), SN_LE16(15), SN_LE32(0), 2, "pc" },
    { SN_LE32(256), 0x94, SN_LE16(8), SN_LE16(15), SN_LE32(0), 5, "cause" },
    { SN_LE32(260), 0x94, SN_LE16(8), SN_LE16(15), SN_LE32(0), 8, "badvaddr" },
    { SN_LE32(264), 0x94, SN_LE16(8), SN_LE16(15), SN_LE32(0), 3, "rcp" },
    { SN_LE32(268), 0x94, SN_LE16(8), SN_LE16(15), SN_LE32(0), 5, "fpcsr" },
    { SN_LE32(272), 0x96, SN_LE16(8), SN_LE16(9), SN_LE32(8), SN_LE16(0), 6, ".1fake", 3, "fp0" },
    { SN_LE32(280), 0x96, SN_LE16(8), SN_LE16(9), SN_LE32(8), SN_LE16(0), 6, ".1fake", 3, "fp2" },
    { SN_LE32(288), 0x96, SN_LE16(8), SN_LE16(9), SN_LE32(8), SN_LE16(0), 6, ".1fake", 3, "fp4" },
    { SN_LE32(296), 0x96, SN_LE16(8), SN_LE16(9), SN_LE32(8), SN_LE16(0), 6, ".1fake", 3, "fp6" },
    { SN_LE32(304), 0x96, SN_LE16(8), SN_LE16(9), SN_LE32(8), SN_LE16(0), 6, ".1fake", 3, "fp8" },
    { SN_LE32(312), 0x96, SN_LE16(8), SN_LE16(9), SN_LE32(8), SN_LE16(0), 6, ".1fake", 4, "fp10" },
    { SN_LE32(320), 0x96, SN_LE16(8), SN_LE16(9), SN_LE32(8), SN_LE16(0), 6, ".1fake", 4, "fp12" },
    { SN_LE32(328), 0x96, SN_LE16(8), SN_LE16(9), SN_LE32(8), SN_LE16(0), 6, ".1fake", 4, "fp14" },
    { SN_LE32(336), 0x96, SN_LE16(8), SN_LE16(9), SN_LE32(8), SN_LE16(0), 6, ".1fake", 4, "fp16" },
    { SN_LE32(344), 0x96, SN_LE16(8), SN_LE16(9), SN_LE32(8), SN_LE16(0), 6, ".1fake", 4, "fp18" },
    { SN_LE32(352), 0x96, SN_LE16(8), SN_LE16(9), SN_LE32(8), SN_LE16(0), 6, ".1fake", 4, "fp20" },
    { SN_LE32(360), 0x96, SN_LE16(8), SN_LE16(9), SN_LE32(8), SN_LE16(0), 6, ".1fake", 4, "fp22" },
    { SN_LE32(368), 0x96, SN_LE16(8), SN_LE16(9), SN_LE32(8), SN_LE16(0), 6, ".1fake", 4, "fp24" },
    { SN_LE32(376), 0x96, SN_LE16(8), SN_LE16(9), SN_LE32(8), SN_LE16(0), 6, ".1fake", 4, "fp26" },
    { SN_LE32(384), 0x96, SN_LE16(8), SN_LE16(9), SN_LE32(8), SN_LE16(0), 6, ".1fake", 4, "fp28" },
    { SN_LE32(392), 0x96, SN_LE16(8), SN_LE16(9), SN_LE32(8), SN_LE16(0), 6, ".1fake", 4, "fp30" },
    { SN_LE32(400), 0x96, SN_LE16(8), SN_LE16(9), SN_LE32(8), SN_LE16(0), 6, ".1fake", 3, "fp1" },
    { SN_LE32(408), 0x96, SN_LE16(8), SN_LE16(9), SN_LE32(8), SN_LE16(0), 6, ".1fake", 3, "fp3" },
    { SN_LE32(416), 0x96, SN_LE16(8), SN_LE16(9), SN_LE32(8), SN_LE16(0), 6, ".1fake", 3, "fp5" },
    { SN_LE32(424), 0x96, SN_LE16(8), SN_LE16(9), SN_LE32(8), SN_LE16(0), 6, ".1fake", 3, "fp7" },
    { SN_LE32(432), 0x96, SN_LE16(8), SN_LE16(9), SN_LE32(8), SN_LE16(0), 6, ".1fake", 3, "fp9" },
    { SN_LE32(440), 0x96, SN_LE16(8), SN_LE16(9), SN_LE32(8), SN_LE16(0), 6, ".1fake", 4, "fp11" },
    { SN_LE32(448), 0x96, SN_LE16(8), SN_LE16(9), SN_LE32(8), SN_LE16(0), 6, ".1fake", 4, "fp13" },
    { SN_LE32(456), 0x96, SN_LE16(8), SN_LE16(9), SN_LE32(8), SN_LE16(0), 6, ".1fake", 4, "fp15" },
    { SN_LE32(464), 0x96, SN_LE16(8), SN_LE16(9), SN_LE32(8), SN_LE16(0), 6, ".1fake", 4, "fp17" },
    { SN_LE32(472), 0x96, SN_LE16(8), SN_LE16(9), SN_LE32(8), SN_LE16(0), 6, ".1fake", 4, "fp19" },
    { SN_LE32(480), 0x96, SN_LE16(8), SN_LE16(9), SN_LE32(8), SN_LE16(0), 6, ".1fake", 4, "fp21" },
    { SN_LE32(488), 0x96, SN_LE16(8), SN_LE16(9), SN_LE32(8), SN_LE16(0), 6, ".1fake", 4, "fp23" },
    { SN_LE32(496), 0x96, SN_LE16(8), SN_LE16(9), SN_LE32(8), SN_LE16(0), 6, ".1fake", 4, "fp25" },
    { SN_LE32(504), 0x96, SN_LE16(8), SN_LE16(9), SN_LE32(8), SN_LE16(0), 6, ".1fake", 4, "fp27" },
    { SN_LE32(512), 0x96, SN_LE16(8), SN_LE16(9), SN_LE32(8), SN_LE16(0), 6, ".1fake", 4, "fp29" },
    { SN_LE32(520), 0x96, SN_LE16(8), SN_LE16(9), SN_LE32(8), SN_LE16(0), 6, ".1fake", 4, "fp31" },
    { SN_LE32(528), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(528), SN_LE16(0), 6, ".2fake", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(528), SN_LE16(0), 6, ".2fake", 17, "__OSThreadContext" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(560), 10, "OSThread_s" },
    { SN_LE32(0), 0x96, SN_LE16(8), SN_LE16(24), SN_LE32(560), SN_LE16(0), 10, "OSThread_s", 4, "next" },
    { SN_LE32(4), 0x94, SN_LE16(8), SN_LE16(5), SN_LE32(0), 8, "priority" },
    { SN_LE32(8), 0x96, SN_LE16(8), SN_LE16(88), SN_LE32(560), SN_LE16(0), 10, "OSThread_s", 5, "queue" },
    { SN_LE32(12), 0x96, SN_LE16(8), SN_LE16(24), SN_LE32(560), SN_LE16(0), 10, "OSThread_s", 6, "tlnext" },
    { SN_LE32(16), 0x94, SN_LE16(8), SN_LE16(13), SN_LE32(0), 5, "state" },
    { SN_LE32(18), 0x94, SN_LE16(8), SN_LE16(13), SN_LE32(0), 5, "flags" },
    { SN_LE32(20), 0x94, SN_LE16(8), SN_LE16(5), SN_LE32(0), 2, "id" },
    { SN_LE32(24), 0x94, SN_LE16(8), SN_LE16(4), SN_LE32(0), 2, "fp" },
    { SN_LE32(32), 0x96, SN_LE16(8), SN_LE16(8), SN_LE32(528), SN_LE16(0), 6, ".2fake", 7, "context" },
    { SN_LE32(560), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(560), SN_LE16(0), 10, "OSThread_s", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(560), SN_LE16(0), 10, "OSThread_s", 8, "OSThread" },
    { SN_LE32(0), 0x94, SN_LE16(13), SN_LE16(15), SN_LE32(0), 7, "OSEvent" },
    { SN_LE32(0), 0x94, SN_LE16(13), SN_LE16(15), SN_LE32(0), 9, "OSIntMask" },
    { SN_LE32(0), 0x94, SN_LE16(13), SN_LE16(15), SN_LE32(0), 10, "OSPageMask" },
    { SN_LE32(0), 0x94, SN_LE16(13), SN_LE16(15), SN_LE32(0), 8, "OSHWIntr" },
    { SN_LE32(0), 0x94, SN_LE16(13), SN_LE16(17), SN_LE32(0), 6, "OSMesg" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(24), 13, "OSMesgQueue_s" },
    { SN_LE32(0), 0x96, SN_LE16(8), SN_LE16(24), SN_LE32(560), SN_LE16(0), 10, "OSThread_s", 7, "mtqueue" },
    { SN_LE32(4), 0x96, SN_LE16(8), SN_LE16(24), SN_LE32(560), SN_LE16(0), 10, "OSThread_s", 9, "fullqueue" },
    { SN_LE32(8), 0x94, SN_LE16(8), SN_LE16(5), SN_LE32(0), 10, "validCount" },
    { SN_LE32(12), 0x94, SN_LE16(8), SN_LE16(5), SN_LE32(0), 5, "first" },
    { SN_LE32(16), 0x94, SN_LE16(8), SN_LE16(5), SN_LE32(0), 8, "msgCount" },
    { SN_LE32(20), 0x94, SN_LE16(8), SN_LE16(81), SN_LE32(0), 3, "msg" },
    { SN_LE32(24), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(24), SN_LE16(0), 13, "OSMesgQueue_s", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(24), SN_LE16(0), 13, "OSMesgQueue_s", 11, "OSMesgQueue" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(36), 6, ".3fake" },
    { SN_LE32(0), 0x94, SN_LE16(8), SN_LE16(15), SN_LE32(0), 9, "errStatus" },
    { SN_LE32(4), 0x94, SN_LE16(8), SN_LE16(17), SN_LE32(0), 8, "dramAddr" },
    { SN_LE32(8), 0x94, SN_LE16(8), SN_LE16(17), SN_LE32(0), 6, "C2Addr" },
    { SN_LE32(12), 0x94, SN_LE16(8), SN_LE16(15), SN_LE32(0), 10, "sectorSize" },
    { SN_LE32(16), 0x94, SN_LE16(8), SN_LE16(15), SN_LE32(0), 8, "C1ErrNum" },
    { SN_LE32(20), 0x96, SN_LE16(8), SN_LE16(63), SN_LE32(16), SN_LE16(1), SN_LE32(4), 0, 11, "C1ErrSector" },
    { SN_LE32(36), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(36), SN_LE16(0), 6, ".3fake", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(36), SN_LE16(0), 6, ".3fake", 13, "__OSBlockInfo" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(96), 6, ".4fake" },
    { SN_LE32(0), 0x94, SN_LE16(8), SN_LE16(15), SN_LE32(0), 7, "cmdType" },
    { SN_LE32(4), 0x94, SN_LE16(8), SN_LE16(13), SN_LE32(0), 12, "transferMode" },
    { SN_LE32(6), 0x94, SN_LE16(8), SN_LE16(13), SN_LE32(0), 8, "blockNum" },
    { SN_LE32(8), 0x94, SN_LE16(8), SN_LE16(5), SN_LE32(0), 9, "sectorNum" },
    { SN_LE32(12), 0x94, SN_LE16(8), SN_LE16(15), SN_LE32(0), 7, "devAddr" },
    { SN_LE32(16), 0x94, SN_LE16(8), SN_LE16(15), SN_LE32(0), 11, "bmCtlShadow" },
    { SN_LE32(20), 0x94, SN_LE16(8), SN_LE16(15), SN_LE32(0), 12, "seqCtlShadow" },
    { SN_LE32(24), 0x96, SN_LE16(8), SN_LE16(56), SN_LE32(72), SN_LE16(1), SN_LE32(2), 6, ".3fake", 5, "block" },
    { SN_LE32(96), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(96), SN_LE16(0), 6, ".4fake", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(96), SN_LE16(0), 6, ".4fake", 13, "__OSTranxInfo" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(116), 12, "OSPiHandle_s" },
    { SN_LE32(0), 0x96, SN_LE16(8), SN_LE16(24), SN_LE32(116), SN_LE16(0), 12, "OSPiHandle_s", 4, "next" },
    { SN_LE32(4), 0x94, SN_LE16(8), SN_LE16(12), SN_LE32(0), 4, "type" },
    { SN_LE32(5), 0x94, SN_LE16(8), SN_LE16(12), SN_LE32(0), 7, "latency" },
    { SN_LE32(6), 0x94, SN_LE16(8), SN_LE16(12), SN_LE32(0), 8, "pageSize" },
    { SN_LE32(7), 0x94, SN_LE16(8), SN_LE16(12), SN_LE32(0), 11, "relDuration" },
    { SN_LE32(8), 0x94, SN_LE16(8), SN_LE16(12), SN_LE32(0), 5, "pulse" },
    { SN_LE32(9), 0x94, SN_LE16(8), SN_LE16(12), SN_LE32(0), 6, "domain" },
    { SN_LE32(12), 0x94, SN_LE16(8), SN_LE16(15), SN_LE32(0), 11, "baseAddress" },
    { SN_LE32(16), 0x94, SN_LE16(8), SN_LE16(15), SN_LE32(0), 5, "speed" },
    { SN_LE32(20), 0x96, SN_LE16(8), SN_LE16(8), SN_LE32(96), SN_LE16(0), 6, ".4fake", 12, "transferInfo" },
    { SN_LE32(116), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(116), SN_LE16(0), 12, "OSPiHandle_s", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(116), SN_LE16(0), 12, "OSPiHandle_s", 10, "OSPiHandle" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(8), 6, ".5fake" },
    { SN_LE32(0), 0x94, SN_LE16(8), SN_LE16(12), SN_LE32(0), 4, "type" },
    { SN_LE32(4), 0x94, SN_LE16(8), SN_LE16(15), SN_LE32(0), 7, "address" },
    { SN_LE32(8), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(8), SN_LE16(0), 6, ".5fake", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(8), SN_LE16(0), 6, ".5fake", 8, "OSPiInfo" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(8), 6, ".6fake" },
    { SN_LE32(0), 0x94, SN_LE16(8), SN_LE16(13), SN_LE32(0), 4, "type" },
    { SN_LE32(2), 0x94, SN_LE16(8), SN_LE16(12), SN_LE32(0), 3, "pri" },
    { SN_LE32(3), 0x94, SN_LE16(8), SN_LE16(12), SN_LE32(0), 6, "status" },
    { SN_LE32(4), 0x96, SN_LE16(8), SN_LE16(24), SN_LE32(24), SN_LE16(0), 13, "OSMesgQueue_s", 8, "retQueue" },
    { SN_LE32(8), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(8), SN_LE16(0), 6, ".6fake", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(8), SN_LE16(0), 6, ".6fake", 11, "OSIoMesgHdr" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(24), 6, ".7fake" },
    { SN_LE32(0), 0x96, SN_LE16(8), SN_LE16(8), SN_LE32(8), SN_LE16(0), 6, ".6fake", 3, "hdr" },
    { SN_LE32(8), 0x94, SN_LE16(8), SN_LE16(17), SN_LE32(0), 8, "dramAddr" },
    { SN_LE32(12), 0x94, SN_LE16(8), SN_LE16(15), SN_LE32(0), 7, "devAddr" },
    { SN_LE32(16), 0x94, SN_LE16(8), SN_LE16(15), SN_LE32(0), 4, "size" },
    { SN_LE32(20), 0x96, SN_LE16(8), SN_LE16(24), SN_LE32(116), SN_LE16(0), 12, "OSPiHandle_s", 8, "piHandle" },
    { SN_LE32(24), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(24), SN_LE16(0), 6, ".7fake", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(24), SN_LE16(0), 6, ".7fake", 8, "OSIoMesg" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(28), 6, ".8fake" },
    { SN_LE32(0), 0x94, SN_LE16(8), SN_LE16(5), SN_LE32(0), 6, "active" },
    { SN_LE32(4), 0x96, SN_LE16(8), SN_LE16(24), SN_LE32(560), SN_LE16(0), 10, "OSThread_s", 6, "thread" },
    { SN_LE32(8), 0x96, SN_LE16(8), SN_LE16(24), SN_LE32(24), SN_LE16(0), 13, "OSMesgQueue_s", 8, "cmdQueue" },
    { SN_LE32(12), 0x96, SN_LE16(8), SN_LE16(24), SN_LE32(24), SN_LE16(0), 13, "OSMesgQueue_s", 8, "evtQueue" },
    { SN_LE32(16), 0x96, SN_LE16(8), SN_LE16(24), SN_LE32(24), SN_LE16(0), 13, "OSMesgQueue_s", 8, "acsQueue" },
    { SN_LE32(20), 0x94, SN_LE16(8), SN_LE16(149), SN_LE32(0), 3, "dma" },
    { SN_LE32(24), 0x94, SN_LE16(8), SN_LE16(149), SN_LE32(0), 4, "edma" },
    { SN_LE32(28), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(28), SN_LE16(0), 6, ".8fake", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(28), SN_LE16(0), 6, ".8fake", 8, "OSDevMgr" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(36), 6, ".9fake" },
    { SN_LE32(0), 0x94, SN_LE16(8), SN_LE16(15), SN_LE32(0), 4, "ctrl" },
    { SN_LE32(4), 0x94, SN_LE16(8), SN_LE16(15), SN_LE32(0), 5, "width" },
    { SN_LE32(8), 0x94, SN_LE16(8), SN_LE16(15), SN_LE32(0), 5, "burst" },
    { SN_LE32(12), 0x94, SN_LE16(8), SN_LE16(15), SN_LE32(0), 5, "vSync" },
    { SN_LE32(16), 0x94, SN_LE16(8), SN_LE16(15), SN_LE32(0), 5, "hSync" },
    { SN_LE32(20), 0x94, SN_LE16(8), SN_LE16(15), SN_LE32(0), 4, "leap" },
    { SN_LE32(24), 0x94, SN_LE16(8), SN_LE16(15), SN_LE32(0), 6, "hStart" },
    { SN_LE32(28), 0x94, SN_LE16(8), SN_LE16(15), SN_LE32(0), 6, "xScale" },
    { SN_LE32(32), 0x94, SN_LE16(8), SN_LE16(15), SN_LE32(0), 8, "vCurrent" },
    { SN_LE32(36), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(36), SN_LE16(0), 6, ".9fake", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(36), SN_LE16(0), 6, ".9fake", 14, "OSViCommonRegs" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(20), 7, ".10fake" },
    { SN_LE32(0), 0x94, SN_LE16(8), SN_LE16(15), SN_LE32(0), 6, "origin" },
    { SN_LE32(4), 0x94, SN_LE16(8), SN_LE16(15), SN_LE32(0), 6, "yScale" },
    { SN_LE32(8), 0x94, SN_LE16(8), SN_LE16(15), SN_LE32(0), 6, "vStart" },
    { SN_LE32(12), 0x94, SN_LE16(8), SN_LE16(15), SN_LE32(0), 6, "vBurst" },
    { SN_LE32(16), 0x94, SN_LE16(8), SN_LE16(15), SN_LE32(0), 5, "vIntr" },
    { SN_LE32(20), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(20), SN_LE16(0), 7, ".10fake", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(20), SN_LE16(0), 7, ".10fake", 13, "OSViFieldRegs" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(80), 7, ".11fake" },
    { SN_LE32(0), 0x94, SN_LE16(8), SN_LE16(12), SN_LE32(0), 4, "type" },
    { SN_LE32(4), 0x96, SN_LE16(8), SN_LE16(8), SN_LE32(36), SN_LE16(0), 6, ".9fake", 7, "comRegs" },
    { SN_LE32(40), 0x96, SN_LE16(8), SN_LE16(56), SN_LE32(40), SN_LE16(1), SN_LE32(2), 7, ".10fake", 7, "fldRegs" },
    { SN_LE32(80), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(80), SN_LE16(0), 7, ".11fake", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(80), SN_LE16(0), 7, ".11fake", 8, "OSViMode" },
    { SN_LE32(0), 0x94, SN_LE16(13), SN_LE16(15), SN_LE32(0), 6, "OSTime" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(32), 9, "OSTimer_s" },
    { SN_LE32(0), 0x96, SN_LE16(8), SN_LE16(24), SN_LE32(32), SN_LE16(0), 9, "OSTimer_s", 4, "next" },
    { SN_LE32(4), 0x96, SN_LE16(8), SN_LE16(24), SN_LE32(32), SN_LE16(0), 9, "OSTimer_s", 4, "prev" },
    { SN_LE32(8), 0x94, SN_LE16(8), SN_LE16(15), SN_LE32(0), 8, "interval" },
    { SN_LE32(16), 0x94, SN_LE16(8), SN_LE16(15), SN_LE32(0), 5, "value" },
    { SN_LE32(24), 0x96, SN_LE16(8), SN_LE16(24), SN_LE32(24), SN_LE16(0), 13, "OSMesgQueue_s", 2, "mq" },
    { SN_LE32(28), 0x94, SN_LE16(8), SN_LE16(17), SN_LE32(0), 3, "msg" },
    { SN_LE32(32), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(32), SN_LE16(0), 9, "OSTimer_s", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(32), SN_LE16(0), 9, "OSTimer_s", 7, "OSTimer" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(4), 7, ".12fake" },
    { SN_LE32(0), 0x94, SN_LE16(8), SN_LE16(13), SN_LE32(0), 4, "type" },
    { SN_LE32(2), 0x94, SN_LE16(8), SN_LE16(12), SN_LE32(0), 6, "status" },
    { SN_LE32(3), 0x94, SN_LE16(8), SN_LE16(12), SN_LE32(0), 5, "errno" },
    { SN_LE32(4), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(4), SN_LE16(0), 7, ".12fake", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(4), SN_LE16(0), 7, ".12fake", 12, "OSContStatus" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(6), 7, ".13fake" },
    { SN_LE32(0), 0x94, SN_LE16(8), SN_LE16(13), SN_LE32(0), 6, "button" },
    { SN_LE32(2), 0x94, SN_LE16(8), SN_LE16(2), SN_LE32(0), 7, "stick_x" },
    { SN_LE32(3), 0x94, SN_LE16(8), SN_LE16(2), SN_LE32(0), 7, "stick_y" },
    { SN_LE32(4), 0x94, SN_LE16(8), SN_LE16(12), SN_LE32(0), 5, "errno" },
    { SN_LE32(6), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(6), SN_LE16(0), 7, ".13fake", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(6), SN_LE16(0), 7, ".13fake", 9, "OSContPad" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(40), 7, ".14fake" },
    { SN_LE32(0), 0x94, SN_LE16(8), SN_LE16(17), SN_LE32(0), 7, "address" },
    { SN_LE32(4), 0x96, SN_LE16(8), SN_LE16(60), SN_LE32(32), SN_LE16(1), SN_LE32(32), 0, 10, "databuffer" },
    { SN_LE32(36), 0x94, SN_LE16(8), SN_LE16(12), SN_LE32(0), 10, "addressCrc" },
    { SN_LE32(37), 0x94, SN_LE16(8), SN_LE16(12), SN_LE32(0), 7, "dataCrc" },
    { SN_LE32(38), 0x94, SN_LE16(8), SN_LE16(12), SN_LE32(0), 5, "errno" },
    { SN_LE32(40), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(40), SN_LE16(0), 7, ".14fake", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(40), SN_LE16(0), 7, ".14fake", 11, "OSContRamIo" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(104), 7, ".15fake" },
    { SN_LE32(0), 0x94, SN_LE16(8), SN_LE16(4), SN_LE32(0), 6, "status" },
    { SN_LE32(4), 0x96, SN_LE16(8), SN_LE16(24), SN_LE32(24), SN_LE16(0), 13, "OSMesgQueue_s", 5, "queue" },
    { SN_LE32(8), 0x94, SN_LE16(8), SN_LE16(4), SN_LE32(0), 7, "channel" },
    { SN_LE32(12), 0x96, SN_LE16(8), SN_LE16(60), SN_LE32(32), SN_LE16(1), SN_LE32(32), 0, 2, "id" },
    { SN_LE32(44), 0x96, SN_LE16(8), SN_LE16(60), SN_LE32(32), SN_LE16(1), SN_LE32(32), 0, 5, "label" },
    { SN_LE32(76), 0x94, SN_LE16(8), SN_LE16(4), SN_LE32(0), 7, "version" },
    { SN_LE32(80), 0x94, SN_LE16(8), SN_LE16(4), SN_LE32(0), 8, "dir_size" },
    { SN_LE32(84), 0x94, SN_LE16(8), SN_LE16(4), SN_LE32(0), 11, "inode_table" },
    { SN_LE32(88), 0x94, SN_LE16(8), SN_LE16(4), SN_LE32(0), 12, "minode_table" },
    { SN_LE32(92), 0x94, SN_LE16(8), SN_LE16(4), SN_LE32(0), 9, "dir_table" },
    { SN_LE32(96), 0x94, SN_LE16(8), SN_LE16(4), SN_LE32(0), 16, "inode_start_page" },
    { SN_LE32(100), 0x94, SN_LE16(8), SN_LE16(12), SN_LE32(0), 5, "banks" },
    { SN_LE32(101), 0x94, SN_LE16(8), SN_LE16(12), SN_LE32(0), 10, "activebank" },
    { SN_LE32(104), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(104), SN_LE16(0), 7, ".15fake", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(104), SN_LE16(0), 7, ".15fake", 5, "OSPfs" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(32), 7, ".16fake" },
    { SN_LE32(0), 0x94, SN_LE16(8), SN_LE16(15), SN_LE32(0), 9, "file_size" },
    { SN_LE32(4), 0x94, SN_LE16(8), SN_LE16(15), SN_LE32(0), 9, "game_code" },
    { SN_LE32(8), 0x94, SN_LE16(8), SN_LE16(13), SN_LE32(0), 12, "company_code" },
    { SN_LE32(10), 0x96, SN_LE16(8), SN_LE16(50), SN_LE32(4), SN_LE16(1), SN_LE32(4), 0, 8, "ext_name" },
    { SN_LE32(14), 0x96, SN_LE16(8), SN_LE16(50), SN_LE32(16), SN_LE16(1), SN_LE32(16), 0, 9, "game_name" },
    { SN_LE32(32), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(32), SN_LE16(0), 7, ".16fake", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(32), SN_LE16(0), 7, ".16fake", 10, "OSPfsState" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(16), 7, ".17fake" },
    { SN_LE32(0), 0x94, SN_LE16(8), SN_LE16(29), SN_LE32(0), 10, "histo_base" },
    { SN_LE32(4), 0x94, SN_LE16(8), SN_LE16(15), SN_LE32(0), 10, "histo_size" },
    { SN_LE32(8), 0x94, SN_LE16(8), SN_LE16(31), SN_LE32(0), 10, "text_start" },
    { SN_LE32(12), 0x94, SN_LE16(8), SN_LE16(31), SN_LE32(0), 8, "text_end" },
    { SN_LE32(16), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(16), SN_LE16(0), 7, ".17fake", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(16), SN_LE16(0), 7, ".17fake", 6, "OSProf" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(20), 9, "_Region_s" },
    { SN_LE32(0), 0x94, SN_LE16(8), SN_LE16(28), SN_LE32(0), 20, "r_startBufferAddress" },
    { SN_LE32(4), 0x94, SN_LE16(8), SN_LE16(28), SN_LE32(0), 12, "r_endAddress" },
    { SN_LE32(8), 0x94, SN_LE16(8), SN_LE16(5), SN_LE32(0), 12, "r_bufferSize" },
    { SN_LE32(12), 0x94, SN_LE16(8), SN_LE16(5), SN_LE32(0), 13, "r_bufferCount" },
    { SN_LE32(16), 0x94, SN_LE16(8), SN_LE16(13), SN_LE32(0), 10, "r_freeList" },
    { SN_LE32(18), 0x94, SN_LE16(8), SN_LE16(13), SN_LE32(0), 11, "r_alignSize" },
    { SN_LE32(20), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(20), SN_LE16(0), 9, "_Region_s", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(20), SN_LE16(0), 9, "_Region_s", 8, "OSRegion" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(64), 7, ".18fake" },
    { SN_LE32(0), 0x94, SN_LE16(8), SN_LE16(15), SN_LE32(0), 4, "type" },
    { SN_LE32(4), 0x94, SN_LE16(8), SN_LE16(15), SN_LE32(0), 5, "flags" },
    { SN_LE32(8), 0x94, SN_LE16(8), SN_LE16(31), SN_LE32(0), 10, "ucode_boot" },
    { SN_LE32(12), 0x94, SN_LE16(8), SN_LE16(15), SN_LE32(0), 15, "ucode_boot_size" },
    { SN_LE32(16), 0x94, SN_LE16(8), SN_LE16(31), SN_LE32(0), 5, "ucode" },
    { SN_LE32(20), 0x94, SN_LE16(8), SN_LE16(15), SN_LE32(0), 10, "ucode_size" },
    { SN_LE32(24), 0x94, SN_LE16(8), SN_LE16(31), SN_LE32(0), 10, "ucode_data" },
    { SN_LE32(28), 0x94, SN_LE16(8), SN_LE16(15), SN_LE32(0), 15, "ucode_data_size" },
    { SN_LE32(32), 0x94, SN_LE16(8), SN_LE16(31), SN_LE32(0), 10, "dram_stack" },
    { SN_LE32(36), 0x94, SN_LE16(8), SN_LE16(15), SN_LE32(0), 15, "dram_stack_size" },
    { SN_LE32(40), 0x94, SN_LE16(8), SN_LE16(31), SN_LE32(0), 11, "output_buff" },
    { SN_LE32(44), 0x94, SN_LE16(8), SN_LE16(31), SN_LE32(0), 16, "output_buff_size" },
    { SN_LE32(48), 0x94, SN_LE16(8), SN_LE16(31), SN_LE32(0), 8, "data_ptr" },
    { SN_LE32(52), 0x94, SN_LE16(8), SN_LE16(15), SN_LE32(0), 9, "data_size" },
    { SN_LE32(56), 0x94, SN_LE16(8), SN_LE16(31), SN_LE32(0), 14, "yield_data_ptr" },
    { SN_LE32(60), 0x94, SN_LE16(8), SN_LE16(15), SN_LE32(0), 15, "yield_data_size" },
    { SN_LE32(64), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(64), SN_LE16(0), 7, ".18fake", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(64), SN_LE16(0), 7, ".18fake", 8, "OSTask_t" },
    { SN_LE32(0), 0x94, SN_LE16(12), SN_LE16(9), SN_LE32(64), 7, ".19fake" },
    { SN_LE32(0), 0x96, SN_LE16(11), SN_LE16(8), SN_LE32(64), SN_LE16(0), 7, ".18fake", 1, "t" },
    { SN_LE32(0), 0x94, SN_LE16(11), SN_LE16(5), SN_LE32(0), 25, "force_structure_alignment" },
    { SN_LE32(64), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(64), SN_LE16(0), 7, ".19fake", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(9), SN_LE32(64), SN_LE16(0), 7, ".19fake", 6, "OSTask" },
    { SN_LE32(0), 0x94, SN_LE16(13), SN_LE16(15), SN_LE32(0), 13, "OSYieldResult" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(16), 7, ".20fake" },
    { SN_LE32(0), 0x96, SN_LE16(8), SN_LE16(51), SN_LE32(6), SN_LE16(1), SN_LE32(3), 0, 2, "ob" },
    { SN_LE32(6), 0x94, SN_LE16(8), SN_LE16(13), SN_LE32(0), 4, "flag" },
    { SN_LE32(8), 0x96, SN_LE16(8), SN_LE16(51), SN_LE32(4), SN_LE16(1), SN_LE32(2), 0, 2, "tc" },
    { SN_LE32(12), 0x96, SN_LE16(8), SN_LE16(60), SN_LE32(4), SN_LE16(1), SN_LE32(4), 0, 2, "cn" },
    { SN_LE32(16), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(16), SN_LE16(0), 7, ".20fake", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(16), SN_LE16(0), 7, ".20fake", 5, "Vtx_t" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(16), 7, ".21fake" },
    { SN_LE32(0), 0x96, SN_LE16(8), SN_LE16(51), SN_LE32(6), SN_LE16(1), SN_LE32(3), 0, 2, "ob" },
    { SN_LE32(6), 0x94, SN_LE16(8), SN_LE16(13), SN_LE32(0), 4, "flag" },
    { SN_LE32(8), 0x96, SN_LE16(8), SN_LE16(51), SN_LE32(4), SN_LE16(1), SN_LE32(2), 0, 2, "tc" },
    { SN_LE32(12), 0x96, SN_LE16(8), SN_LE16(50), SN_LE32(3), SN_LE16(1), SN_LE32(3), 0, 1, "n" },
    { SN_LE32(15), 0x94, SN_LE16(8), SN_LE16(12), SN_LE32(0), 1, "a" },
    { SN_LE32(16), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(16), SN_LE16(0), 7, ".21fake", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(16), SN_LE16(0), 7, ".21fake", 6, "Vtx_tn" },
    { SN_LE32(0), 0x94, SN_LE16(12), SN_LE16(9), SN_LE32(16), 7, ".22fake" },
    { SN_LE32(0), 0x96, SN_LE16(11), SN_LE16(8), SN_LE32(16), SN_LE16(0), 7, ".20fake", 1, "v" },
    { SN_LE32(0), 0x96, SN_LE16(11), SN_LE16(8), SN_LE32(16), SN_LE16(0), 7, ".21fake", 1, "n" },
    { SN_LE32(0), 0x94, SN_LE16(11), SN_LE16(5), SN_LE32(0), 25, "force_structure_alignment" },
    { SN_LE32(16), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(16), SN_LE16(0), 7, ".22fake", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(9), SN_LE32(16), SN_LE16(0), 7, ".22fake", 3, "Vtx" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(24), 7, ".23fake" },
    { SN_LE32(0), 0x94, SN_LE16(8), SN_LE16(17), SN_LE32(0), 18, "SourceImagePointer" },
    { SN_LE32(4), 0x94, SN_LE16(8), SN_LE16(17), SN_LE32(0), 11, "TlutPointer" },
    { SN_LE32(8), 0x94, SN_LE16(8), SN_LE16(3), SN_LE32(0), 6, "Stride" },
    { SN_LE32(10), 0x94, SN_LE16(8), SN_LE16(3), SN_LE32(0), 13, "SubImageWidth" },
    { SN_LE32(12), 0x94, SN_LE16(8), SN_LE16(3), SN_LE32(0), 14, "SubImageHeight" },
    { SN_LE32(14), 0x94, SN_LE16(8), SN_LE16(2), SN_LE32(0), 15, "SourceImageType" },
    { SN_LE32(15), 0x94, SN_LE16(8), SN_LE16(2), SN_LE32(0), 18, "SourceImageBitSize" },
    { SN_LE32(16), 0x94, SN_LE16(8), SN_LE16(3), SN_LE32(0), 18, "SourceImageOffsetS" },
    { SN_LE32(18), 0x94, SN_LE16(8), SN_LE16(3), SN_LE32(0), 18, "SourceImageOffsetT" },
    { SN_LE32(20), 0x96, SN_LE16(8), SN_LE16(50), SN_LE32(4), SN_LE16(1), SN_LE32(4), 0, 5, "dummy" },
    { SN_LE32(24), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(24), SN_LE16(0), 7, ".23fake", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(24), SN_LE16(0), 7, ".23fake", 9, "uSprite_t" },
    { SN_LE32(0), 0x94, SN_LE16(12), SN_LE16(9), SN_LE32(24), 7, ".24fake" },
    { SN_LE32(0), 0x96, SN_LE16(11), SN_LE16(8), SN_LE32(24), SN_LE16(0), 7, ".23fake", 1, "s" },
    { SN_LE32(0), 0x96, SN_LE16(11), SN_LE16(53), SN_LE32(24), SN_LE16(1), SN_LE32(3), 0, 26, "force_structure_allignment" },
    { SN_LE32(24), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(24), SN_LE16(0), 7, ".24fake", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(9), SN_LE32(24), SN_LE16(0), 7, ".24fake", 7, "uSprite" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(4), 7, ".25fake" },
    { SN_LE32(0), 0x94, SN_LE16(8), SN_LE16(12), SN_LE32(0), 4, "flag" },
    { SN_LE32(1), 0x96, SN_LE16(8), SN_LE16(60), SN_LE32(3), SN_LE16(1), SN_LE32(3), 0, 1, "v" },
    { SN_LE32(4), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(4), SN_LE16(0), 7, ".25fake", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(4), SN_LE16(0), 7, ".25fake", 3, "Tri" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(245), SN_LE32(64), SN_LE16(2), SN_LE32(4), SN_LE32(4), 0, 5, "Mtx_t" },
    { SN_LE32(0), 0x94, SN_LE16(12), SN_LE16(9), SN_LE32(64), 7, ".26fake" },
    { SN_LE32(0), 0x96, SN_LE16(11), SN_LE16(245), SN_LE32(64), SN_LE16(2), SN_LE32(4), SN_LE32(4), 0, 1, "m" },
    { SN_LE32(0), 0x94, SN_LE16(11), SN_LE16(5), SN_LE32(0), 25, "force_structure_alignment" },
    { SN_LE32(64), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(64), SN_LE16(0), 7, ".26fake", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(9), SN_LE32(64), SN_LE16(0), 7, ".26fake", 3, "Mtx" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(16), 7, ".27fake" },
    { SN_LE32(0), 0x96, SN_LE16(8), SN_LE16(51), SN_LE32(8), SN_LE16(1), SN_LE32(4), 0, 6, "vscale" },
    { SN_LE32(8), 0x96, SN_LE16(8), SN_LE16(51), SN_LE32(8), SN_LE16(1), SN_LE32(4), 0, 6, "vtrans" },
    { SN_LE32(16), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(16), SN_LE16(0), 7, ".27fake", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(16), SN_LE16(0), 7, ".27fake", 4, "Vp_t" },
    { SN_LE32(0), 0x94, SN_LE16(12), SN_LE16(9), SN_LE32(16), 7, ".28fake" },
    { SN_LE32(0), 0x96, SN_LE16(11), SN_LE16(8), SN_LE32(16), SN_LE16(0), 7, ".27fake", 2, "vp" },
    { SN_LE32(0), 0x94, SN_LE16(11), SN_LE16(5), SN_LE32(0), 25, "force_structure_alignment" },
    { SN_LE32(16), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(16), SN_LE16(0), 7, ".28fake", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(9), SN_LE32(16), SN_LE16(0), 7, ".28fake", 2, "Vp" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(12), 7, ".29fake" },
    { SN_LE32(0), 0x96, SN_LE16(8), SN_LE16(60), SN_LE32(3), SN_LE16(1), SN_LE32(3), 0, 3, "col" },
    { SN_LE32(3), 0x94, SN_LE16(8), SN_LE16(2), SN_LE32(0), 4, "pad1" },
    { SN_LE32(4), 0x96, SN_LE16(8), SN_LE16(60), SN_LE32(3), SN_LE16(1), SN_LE32(3), 0, 4, "colc" },
    { SN_LE32(7), 0x94, SN_LE16(8), SN_LE16(2), SN_LE32(0), 4, "pad2" },
    { SN_LE32(8), 0x96, SN_LE16(8), SN_LE16(50), SN_LE32(3), SN_LE16(1), SN_LE32(3), 0, 3, "dir" },
    { SN_LE32(11), 0x94, SN_LE16(8), SN_LE16(2), SN_LE32(0), 4, "pad3" },
    { SN_LE32(12), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(12), SN_LE16(0), 7, ".29fake", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(12), SN_LE16(0), 7, ".29fake", 7, "Light_t" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(8), 7, ".30fake" },
    { SN_LE32(0), 0x96, SN_LE16(8), SN_LE16(60), SN_LE32(3), SN_LE16(1), SN_LE32(3), 0, 3, "col" },
    { SN_LE32(3), 0x94, SN_LE16(8), SN_LE16(2), SN_LE32(0), 4, "pad1" },
    { SN_LE32(4), 0x96, SN_LE16(8), SN_LE16(60), SN_LE32(3), SN_LE16(1), SN_LE32(3), 0, 4, "colc" },
    { SN_LE32(7), 0x94, SN_LE16(8), SN_LE16(2), SN_LE32(0), 4, "pad2" },
    { SN_LE32(8), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(8), SN_LE16(0), 7, ".30fake", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(8), SN_LE16(0), 7, ".30fake", 9, "Ambient_t" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(16), 7, ".31fake" },
    { SN_LE32(0), 0x94, SN_LE16(8), SN_LE16(4), SN_LE32(0), 2, "x1" },
    { SN_LE32(4), 0x94, SN_LE16(8), SN_LE16(4), SN_LE32(0), 2, "y1" },
    { SN_LE32(8), 0x94, SN_LE16(8), SN_LE16(4), SN_LE32(0), 2, "x2" },
    { SN_LE32(12), 0x94, SN_LE16(8), SN_LE16(4), SN_LE32(0), 2, "y2" },
    { SN_LE32(16), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(16), SN_LE16(0), 7, ".31fake", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(16), SN_LE16(0), 7, ".31fake", 8, "Hilite_t" },
    { SN_LE32(0), 0x94, SN_LE16(12), SN_LE16(9), SN_LE32(16), 7, ".32fake" },
    { SN_LE32(0), 0x96, SN_LE16(11), SN_LE16(8), SN_LE32(12), SN_LE16(0), 7, ".29fake", 1, "l" },
    { SN_LE32(0), 0x96, SN_LE16(11), SN_LE16(53), SN_LE32(16), SN_LE16(1), SN_LE32(2), 0, 25, "force_structure_alignment" },
    { SN_LE32(16), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(16), SN_LE16(0), 7, ".32fake", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(9), SN_LE32(16), SN_LE16(0), 7, ".32fake", 5, "Light" },
    { SN_LE32(0), 0x94, SN_LE16(12), SN_LE16(9), SN_LE32(8), 7, ".33fake" },
    { SN_LE32(0), 0x96, SN_LE16(11), SN_LE16(8), SN_LE32(8), SN_LE16(0), 7, ".30fake", 1, "l" },
    { SN_LE32(0), 0x96, SN_LE16(11), SN_LE16(53), SN_LE32(8), SN_LE16(1), SN_LE32(1), 0, 25, "force_structure_alignment" },
    { SN_LE32(8), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(8), SN_LE16(0), 7, ".33fake", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(9), SN_LE32(8), SN_LE16(0), 7, ".33fake", 7, "Ambient" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(120), 7, ".34fake" },
    { SN_LE32(0), 0x96, SN_LE16(8), SN_LE16(9), SN_LE32(8), SN_LE16(0), 7, ".33fake", 1, "a" },
    { SN_LE32(8), 0x96, SN_LE16(8), SN_LE16(57), SN_LE32(112), SN_LE16(1), SN_LE32(7), 7, ".32fake", 1, "l" },
    { SN_LE32(120), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(120), SN_LE16(0), 7, ".34fake", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(120), SN_LE16(0), 7, ".34fake", 7, "Lightsn" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(24), 7, ".35fake" },
    { SN_LE32(0), 0x96, SN_LE16(8), SN_LE16(9), SN_LE32(8), SN_LE16(0), 7, ".33fake", 1, "a" },
    { SN_LE32(8), 0x96, SN_LE16(8), SN_LE16(57), SN_LE32(16), SN_LE16(1), SN_LE32(1), 7, ".32fake", 1, "l" },
    { SN_LE32(24), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(24), SN_LE16(0), 7, ".35fake", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(24), SN_LE16(0), 7, ".35fake", 7, "Lights0" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(24), 7, ".36fake" },
    { SN_LE32(0), 0x96, SN_LE16(8), SN_LE16(9), SN_LE32(8), SN_LE16(0), 7, ".33fake", 1, "a" },
    { SN_LE32(8), 0x96, SN_LE16(8), SN_LE16(57), SN_LE32(16), SN_LE16(1), SN_LE32(1), 7, ".32fake", 1, "l" },
    { SN_LE32(24), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(24), SN_LE16(0), 7, ".36fake", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(24), SN_LE16(0), 7, ".36fake", 7, "Lights1" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(40), 7, ".37fake" },
    { SN_LE32(0), 0x96, SN_LE16(8), SN_LE16(9), SN_LE32(8), SN_LE16(0), 7, ".33fake", 1, "a" },
    { SN_LE32(8), 0x96, SN_LE16(8), SN_LE16(57), SN_LE32(32), SN_LE16(1), SN_LE32(2), 7, ".32fake", 1, "l" },
    { SN_LE32(40), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(40), SN_LE16(0), 7, ".37fake", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(40), SN_LE16(0), 7, ".37fake", 7, "Lights2" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(56), 7, ".38fake" },
    { SN_LE32(0), 0x96, SN_LE16(8), SN_LE16(9), SN_LE32(8), SN_LE16(0), 7, ".33fake", 1, "a" },
    { SN_LE32(8), 0x96, SN_LE16(8), SN_LE16(57), SN_LE32(48), SN_LE16(1), SN_LE32(3), 7, ".32fake", 1, "l" },
    { SN_LE32(56), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(56), SN_LE16(0), 7, ".38fake", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(56), SN_LE16(0), 7, ".38fake", 7, "Lights3" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(72), 7, ".39fake" },
    { SN_LE32(0), 0x96, SN_LE16(8), SN_LE16(9), SN_LE32(8), SN_LE16(0), 7, ".33fake", 1, "a" },
    { SN_LE32(8), 0x96, SN_LE16(8), SN_LE16(57), SN_LE32(64), SN_LE16(1), SN_LE32(4), 7, ".32fake", 1, "l" },
    { SN_LE32(72), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(72), SN_LE16(0), 7, ".39fake", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(72), SN_LE16(0), 7, ".39fake", 7, "Lights4" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(88), 7, ".40fake" },
    { SN_LE32(0), 0x96, SN_LE16(8), SN_LE16(9), SN_LE32(8), SN_LE16(0), 7, ".33fake", 1, "a" },
    { SN_LE32(8), 0x96, SN_LE16(8), SN_LE16(57), SN_LE32(80), SN_LE16(1), SN_LE32(5), 7, ".32fake", 1, "l" },
    { SN_LE32(88), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(88), SN_LE16(0), 7, ".40fake", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(88), SN_LE16(0), 7, ".40fake", 7, "Lights5" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(104), 7, ".41fake" },
    { SN_LE32(0), 0x96, SN_LE16(8), SN_LE16(9), SN_LE32(8), SN_LE16(0), 7, ".33fake", 1, "a" },
    { SN_LE32(8), 0x96, SN_LE16(8), SN_LE16(57), SN_LE32(96), SN_LE16(1), SN_LE32(6), 7, ".32fake", 1, "l" },
    { SN_LE32(104), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(104), SN_LE16(0), 7, ".41fake", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(104), SN_LE16(0), 7, ".41fake", 7, "Lights6" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(120), 7, ".42fake" },
    { SN_LE32(0), 0x96, SN_LE16(8), SN_LE16(9), SN_LE32(8), SN_LE16(0), 7, ".33fake", 1, "a" },
    { SN_LE32(8), 0x96, SN_LE16(8), SN_LE16(57), SN_LE32(112), SN_LE16(1), SN_LE32(7), 7, ".32fake", 1, "l" },
    { SN_LE32(120), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(120), SN_LE16(0), 7, ".42fake", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(120), SN_LE16(0), 7, ".42fake", 7, "Lights7" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(32), 7, ".43fake" },
    { SN_LE32(0), 0x96, SN_LE16(8), SN_LE16(57), SN_LE32(32), SN_LE16(1), SN_LE32(2), 7, ".32fake", 1, "l" },
    { SN_LE32(32), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(32), SN_LE16(0), 7, ".43fake", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(32), SN_LE16(0), 7, ".43fake", 6, "LookAt" },
    { SN_LE32(0), 0x94, SN_LE16(12), SN_LE16(9), SN_LE32(16), 7, ".44fake" },
    { SN_LE32(0), 0x96, SN_LE16(11), SN_LE16(8), SN_LE32(16), SN_LE16(0), 7, ".31fake", 1, "h" },
    { SN_LE32(0), 0x96, SN_LE16(11), SN_LE16(53), SN_LE32(16), SN_LE16(1), SN_LE32(4), 0, 25, "force_structure_alignment" },
    { SN_LE32(16), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(16), SN_LE16(0), 7, ".44fake", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(9), SN_LE32(16), SN_LE16(0), 7, ".44fake", 6, "Hilite" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(8), 7, ".45fake" },
    { SN_LE32(0), 0x94, SN_LE16(18), SN_LE16(4), SN_LE32(8), 3, "cmd" },
    { SN_LE32(8), 0x94, SN_LE16(18), SN_LE16(14), SN_LE32(8), 3, "par" },
    { SN_LE32(16), 0x94, SN_LE16(18), SN_LE16(14), SN_LE32(16), 3, "len" },
    { SN_LE32(4), 0x94, SN_LE16(8), SN_LE16(14), SN_LE32(0), 4, "addr" },
    { SN_LE32(8), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(8), SN_LE16(0), 7, ".45fake", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(8), SN_LE16(0), 7, ".45fake", 4, "Gdma" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(8), 7, ".46fake" },
    { SN_LE32(0), 0x94, SN_LE16(18), SN_LE16(4), SN_LE32(8), 3, "cmd" },
    { SN_LE32(8), 0x94, SN_LE16(18), SN_LE16(4), SN_LE32(24), 3, "pad" },
    { SN_LE32(4), 0x96, SN_LE16(8), SN_LE16(8), SN_LE32(4), SN_LE16(0), 7, ".25fake", 3, "tri" },
    { SN_LE32(8), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(8), SN_LE16(0), 7, ".46fake", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(8), SN_LE16(0), 7, ".46fake", 4, "Gtri" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(8), 7, ".47fake" },
    { SN_LE32(0), 0x94, SN_LE16(18), SN_LE16(4), SN_LE32(8), 3, "cmd" },
    { SN_LE32(8), 0x94, SN_LE16(18), SN_LE16(4), SN_LE32(24), 4, "pad1" },
    { SN_LE32(32), 0x94, SN_LE16(18), SN_LE16(4), SN_LE32(24), 4, "pad2" },
    { SN_LE32(56), 0x94, SN_LE16(18), SN_LE16(12), SN_LE32(8), 5, "param" },
    { SN_LE32(8), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(8), SN_LE16(0), 7, ".47fake", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(8), SN_LE16(0), 7, ".47fake", 7, "Gpopmtx" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(8), 7, ".48fake" },
    { SN_LE32(0), 0x94, SN_LE16(18), SN_LE16(4), SN_LE32(8), 3, "cmd" },
    { SN_LE32(8), 0x94, SN_LE16(18), SN_LE16(4), SN_LE32(8), 4, "pad0" },
    { SN_LE32(16), 0x94, SN_LE16(18), SN_LE16(4), SN_LE32(8), 8, "mw_index" },
    { SN_LE32(24), 0x94, SN_LE16(18), SN_LE16(4), SN_LE32(8), 6, "number" },
    { SN_LE32(32), 0x94, SN_LE16(18), SN_LE16(4), SN_LE32(8), 4, "pad1" },
    { SN_LE32(40), 0x94, SN_LE16(18), SN_LE16(4), SN_LE32(24), 4, "base" },
    { SN_LE32(8), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(8), SN_LE16(0), 7, ".48fake", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(8), SN_LE16(0), 7, ".48fake", 8, "Gsegment" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(8), 7, ".49fake" },
    { SN_LE32(0), 0x94, SN_LE16(18), SN_LE16(4), SN_LE32(8), 3, "cmd" },
    { SN_LE32(8), 0x94, SN_LE16(18), SN_LE16(4), SN_LE32(8), 4, "pad0" },
    { SN_LE32(16), 0x94, SN_LE16(18), SN_LE16(4), SN_LE32(8), 3, "sft" },
    { SN_LE32(24), 0x94, SN_LE16(18), SN_LE16(4), SN_LE32(8), 3, "len" },
    { SN_LE32(32), 0x94, SN_LE16(18), SN_LE16(14), SN_LE32(32), 4, "data" },
    { SN_LE32(8), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(8), SN_LE16(0), 7, ".49fake", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(8), SN_LE16(0), 7, ".49fake", 14, "GsetothermodeL" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(8), 7, ".50fake" },
    { SN_LE32(0), 0x94, SN_LE16(18), SN_LE16(4), SN_LE32(8), 3, "cmd" },
    { SN_LE32(8), 0x94, SN_LE16(18), SN_LE16(4), SN_LE32(8), 4, "pad0" },
    { SN_LE32(16), 0x94, SN_LE16(18), SN_LE16(4), SN_LE32(8), 3, "sft" },
    { SN_LE32(24), 0x94, SN_LE16(18), SN_LE16(4), SN_LE32(8), 3, "len" },
    { SN_LE32(32), 0x94, SN_LE16(18), SN_LE16(14), SN_LE32(32), 4, "data" },
    { SN_LE32(8), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(8), SN_LE16(0), 7, ".50fake", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(8), SN_LE16(0), 7, ".50fake", 14, "GsetothermodeH" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(8), 7, ".51fake" },
    { SN_LE32(0), 0x94, SN_LE16(8), SN_LE16(12), SN_LE32(0), 3, "cmd" },
    { SN_LE32(1), 0x94, SN_LE16(8), SN_LE16(12), SN_LE32(0), 8, "lodscale" },
    { SN_LE32(2), 0x94, SN_LE16(8), SN_LE16(12), SN_LE32(0), 4, "tile" },
    { SN_LE32(3), 0x94, SN_LE16(8), SN_LE16(12), SN_LE32(0), 2, "on" },
    { SN_LE32(4), 0x94, SN_LE16(8), SN_LE16(13), SN_LE32(0), 1, "s" },
    { SN_LE32(6), 0x94, SN_LE16(8), SN_LE16(13), SN_LE32(0), 1, "t" },
    { SN_LE32(8), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(8), SN_LE16(0), 7, ".51fake", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(8), SN_LE16(0), 7, ".51fake", 8, "Gtexture" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(8), 7, ".52fake" },
    { SN_LE32(0), 0x94, SN_LE16(18), SN_LE16(4), SN_LE32(8), 3, "cmd" },
    { SN_LE32(8), 0x94, SN_LE16(18), SN_LE16(4), SN_LE32(24), 3, "pad" },
    { SN_LE32(4), 0x96, SN_LE16(8), SN_LE16(8), SN_LE32(4), SN_LE16(0), 7, ".25fake", 4, "line" },
    { SN_LE32(8), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(8), SN_LE16(0), 7, ".52fake", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(8), SN_LE16(0), 7, ".52fake", 7, "Gline3D" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(8), 7, ".53fake" },
    { SN_LE32(0), 0x94, SN_LE16(18), SN_LE16(4), SN_LE32(8), 3, "cmd" },
    { SN_LE32(8), 0x94, SN_LE16(18), SN_LE16(4), SN_LE32(24), 4, "pad1" },
    { SN_LE32(4), 0x94, SN_LE16(8), SN_LE16(3), SN_LE32(0), 4, "pad2" },
    { SN_LE32(6), 0x94, SN_LE16(8), SN_LE16(3), SN_LE32(0), 5, "scale" },
    { SN_LE32(8), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(8), SN_LE16(0), 7, ".53fake", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(8), SN_LE16(0), 7, ".53fake", 10, "Gperspnorm" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(8), 7, ".54fake" },
    { SN_LE32(0), 0x94, SN_LE16(18), SN_LE16(4), SN_LE32(8), 3, "cmd" },
    { SN_LE32(8), 0x94, SN_LE16(18), SN_LE16(14), SN_LE32(3), 3, "fmt" },
    { SN_LE32(11), 0x94, SN_LE16(18), SN_LE16(14), SN_LE32(2), 3, "siz" },
    { SN_LE32(13), 0x94, SN_LE16(18), SN_LE16(14), SN_LE32(7), 3, "pad" },
    { SN_LE32(20), 0x94, SN_LE16(18), SN_LE16(14), SN_LE32(12), 2, "wd" },
    { SN_LE32(4), 0x94, SN_LE16(8), SN_LE16(14), SN_LE32(0), 4, "dram" },
    { SN_LE32(8), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(8), SN_LE16(0), 7, ".54fake", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(8), SN_LE16(0), 7, ".54fake", 7, "Gsetimg" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(8), 7, ".55fake" },
    { SN_LE32(0), 0x94, SN_LE16(18), SN_LE16(4), SN_LE32(8), 3, "cmd" },
    { SN_LE32(8), 0x94, SN_LE16(18), SN_LE16(14), SN_LE32(24), 5, "muxs0" },
    { SN_LE32(32), 0x94, SN_LE16(18), SN_LE16(14), SN_LE32(32), 5, "muxs1" },
    { SN_LE32(8), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(8), SN_LE16(0), 7, ".55fake", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(8), SN_LE16(0), 7, ".55fake", 11, "Gsetcombine" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(8), 7, ".56fake" },
    { SN_LE32(0), 0x94, SN_LE16(18), SN_LE16(4), SN_LE32(8), 3, "cmd" },
    { SN_LE32(1), 0x94, SN_LE16(8), SN_LE16(12), SN_LE32(0), 3, "pad" },
    { SN_LE32(2), 0x94, SN_LE16(8), SN_LE16(12), SN_LE32(0), 14, "prim_min_level" },
    { SN_LE32(3), 0x94, SN_LE16(8), SN_LE16(12), SN_LE32(0), 10, "prim_level" },
    { SN_LE32(4), 0x94, SN_LE16(8), SN_LE16(15), SN_LE32(0), 5, "color" },
    { SN_LE32(8), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(8), SN_LE16(0), 7, ".56fake", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(8), SN_LE16(0), 7, ".56fake", 9, "Gsetcolor" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(8), 7, ".57fake" },
    { SN_LE32(0), 0x94, SN_LE16(18), SN_LE16(4), SN_LE32(8), 3, "cmd" },
    { SN_LE32(8), 0x94, SN_LE16(18), SN_LE16(4), SN_LE32(10), 2, "x0" },
    { SN_LE32(18), 0x94, SN_LE16(18), SN_LE16(4), SN_LE32(2), 6, "x0frac" },
    { SN_LE32(20), 0x94, SN_LE16(18), SN_LE16(4), SN_LE32(10), 2, "y0" },
    { SN_LE32(30), 0x94, SN_LE16(18), SN_LE16(4), SN_LE32(2), 6, "y0frac" },
    { SN_LE32(32), 0x94, SN_LE16(18), SN_LE16(14), SN_LE32(8), 3, "pad" },
    { SN_LE32(40), 0x94, SN_LE16(18), SN_LE16(4), SN_LE32(10), 2, "x1" },
    { SN_LE32(50), 0x94, SN_LE16(18), SN_LE16(4), SN_LE32(2), 6, "x1frac" },
    { SN_LE32(52), 0x94, SN_LE16(18), SN_LE16(4), SN_LE32(10), 2, "y1" },
    { SN_LE32(62), 0x94, SN_LE16(18), SN_LE16(4), SN_LE32(2), 6, "y1frac" },
    { SN_LE32(8), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(8), SN_LE16(0), 7, ".57fake", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(8), SN_LE16(0), 7, ".57fake", 9, "Gfillrect" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(8), 7, ".58fake" },
    { SN_LE32(0), 0x94, SN_LE16(18), SN_LE16(4), SN_LE32(8), 3, "cmd" },
    { SN_LE32(8), 0x94, SN_LE16(18), SN_LE16(14), SN_LE32(3), 3, "fmt" },
    { SN_LE32(11), 0x94, SN_LE16(18), SN_LE16(14), SN_LE32(2), 3, "siz" },
    { SN_LE32(13), 0x94, SN_LE16(18), SN_LE16(14), SN_LE32(1), 4, "pad0" },
    { SN_LE32(14), 0x94, SN_LE16(18), SN_LE16(14), SN_LE32(9), 4, "line" },
    { SN_LE32(23), 0x94, SN_LE16(18), SN_LE16(14), SN_LE32(9), 4, "tmem" },
    { SN_LE32(32), 0x94, SN_LE16(18), SN_LE16(14), SN_LE32(5), 4, "pad1" },
    { SN_LE32(37), 0x94, SN_LE16(18), SN_LE16(14), SN_LE32(3), 4, "tile" },
    { SN_LE32(40), 0x94, SN_LE16(18), SN_LE16(14), SN_LE32(4), 7, "palette" },
    { SN_LE32(44), 0x94, SN_LE16(18), SN_LE16(14), SN_LE32(1), 2, "ct" },
    { SN_LE32(45), 0x94, SN_LE16(18), SN_LE16(14), SN_LE32(1), 2, "mt" },
    { SN_LE32(46), 0x94, SN_LE16(18), SN_LE16(14), SN_LE32(4), 5, "maskt" },
    { SN_LE32(50), 0x94, SN_LE16(18), SN_LE16(14), SN_LE32(4), 6, "shiftt" },
    { SN_LE32(54), 0x94, SN_LE16(18), SN_LE16(14), SN_LE32(1), 2, "cs" },
    { SN_LE32(55), 0x94, SN_LE16(18), SN_LE16(14), SN_LE32(1), 2, "ms" },
    { SN_LE32(56), 0x94, SN_LE16(18), SN_LE16(14), SN_LE32(4), 5, "masks" },
    { SN_LE32(60), 0x94, SN_LE16(18), SN_LE16(14), SN_LE32(4), 6, "shifts" },
    { SN_LE32(8), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(8), SN_LE16(0), 7, ".58fake", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(8), SN_LE16(0), 7, ".58fake", 8, "Gsettile" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(8), 7, ".59fake" },
    { SN_LE32(0), 0x94, SN_LE16(18), SN_LE16(4), SN_LE32(8), 3, "cmd" },
    { SN_LE32(8), 0x94, SN_LE16(18), SN_LE16(14), SN_LE32(12), 2, "sl" },
    { SN_LE32(20), 0x94, SN_LE16(18), SN_LE16(14), SN_LE32(12), 2, "tl" },
    { SN_LE32(32), 0x94, SN_LE16(18), SN_LE16(4), SN_LE32(5), 3, "pad" },
    { SN_LE32(37), 0x94, SN_LE16(18), SN_LE16(14), SN_LE32(3), 4, "tile" },
    { SN_LE32(40), 0x94, SN_LE16(18), SN_LE16(14), SN_LE32(12), 2, "sh" },
    { SN_LE32(52), 0x94, SN_LE16(18), SN_LE16(14), SN_LE32(12), 2, "th" },
    { SN_LE32(8), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(8), SN_LE16(0), 7, ".59fake", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(8), SN_LE16(0), 7, ".59fake", 9, "Gloadtile" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(8), SN_LE16(0), 7, ".59fake", 10, "Gloadblock" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(8), SN_LE16(0), 7, ".59fake", 12, "Gsettilesize" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(8), SN_LE16(0), 7, ".59fake", 9, "Gloadtlut" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(16), 7, ".60fake" },
    { SN_LE32(0), 0x94, SN_LE16(18), SN_LE16(14), SN_LE32(8), 3, "cmd" },
    { SN_LE32(8), 0x94, SN_LE16(18), SN_LE16(14), SN_LE32(12), 2, "xl" },
    { SN_LE32(20), 0x94, SN_LE16(18), SN_LE16(14), SN_LE32(12), 2, "yl" },
    { SN_LE32(32), 0x94, SN_LE16(18), SN_LE16(14), SN_LE32(5), 4, "pad1" },
    { SN_LE32(37), 0x94, SN_LE16(18), SN_LE16(14), SN_LE32(3), 4, "tile" },
    { SN_LE32(40), 0x94, SN_LE16(18), SN_LE16(14), SN_LE32(12), 2, "xh" },
    { SN_LE32(52), 0x94, SN_LE16(18), SN_LE16(14), SN_LE32(12), 2, "yh" },
    { SN_LE32(64), 0x94, SN_LE16(18), SN_LE16(14), SN_LE32(16), 1, "s" },
    { SN_LE32(80), 0x94, SN_LE16(18), SN_LE16(14), SN_LE32(16), 1, "t" },
    { SN_LE32(96), 0x94, SN_LE16(18), SN_LE16(14), SN_LE32(16), 4, "dsdx" },
    { SN_LE32(112), 0x94, SN_LE16(18), SN_LE16(14), SN_LE32(16), 4, "dtdy" },
    { SN_LE32(16), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(16), SN_LE16(0), 7, ".60fake", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(16), SN_LE16(0), 7, ".60fake", 8, "Gtexrect" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(16), 7, ".61fake" },
    { SN_LE32(0), 0x94, SN_LE16(8), SN_LE16(15), SN_LE32(0), 2, "w0" },
    { SN_LE32(4), 0x94, SN_LE16(8), SN_LE16(15), SN_LE32(0), 2, "w1" },
    { SN_LE32(8), 0x94, SN_LE16(8), SN_LE16(15), SN_LE32(0), 2, "w2" },
    { SN_LE32(12), 0x94, SN_LE16(8), SN_LE16(15), SN_LE32(0), 2, "w3" },
    { SN_LE32(16), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(16), SN_LE16(0), 7, ".61fake", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(16), SN_LE16(0), 7, ".61fake", 7, "TexRect" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(8), 7, ".62fake" },
    { SN_LE32(0), 0x94, SN_LE16(8), SN_LE16(14), SN_LE32(0), 2, "w0" },
    { SN_LE32(4), 0x94, SN_LE16(8), SN_LE16(14), SN_LE32(0), 2, "w1" },
    { SN_LE32(8), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(8), SN_LE16(0), 7, ".62fake", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(8), SN_LE16(0), 7, ".62fake", 6, "Gwords" },
    { SN_LE32(0), 0x94, SN_LE16(12), SN_LE16(9), SN_LE32(8), 7, ".63fake" },
    { SN_LE32(0), 0x96, SN_LE16(11), SN_LE16(8), SN_LE32(8), SN_LE16(0), 7, ".62fake", 5, "words" },
    { SN_LE32(0), 0x96, SN_LE16(11), SN_LE16(8), SN_LE32(8), SN_LE16(0), 7, ".45fake", 3, "dma" },
    { SN_LE32(0), 0x96, SN_LE16(11), SN_LE16(8), SN_LE32(8), SN_LE16(0), 7, ".46fake", 3, "tri" },
    { SN_LE32(0), 0x96, SN_LE16(11), SN_LE16(8), SN_LE32(8), SN_LE16(0), 7, ".52fake", 4, "line" },
    { SN_LE32(0), 0x96, SN_LE16(11), SN_LE16(8), SN_LE32(8), SN_LE16(0), 7, ".47fake", 6, "popmtx" },
    { SN_LE32(0), 0x96, SN_LE16(11), SN_LE16(8), SN_LE32(8), SN_LE16(0), 7, ".48fake", 7, "segment" },
    { SN_LE32(0), 0x96, SN_LE16(11), SN_LE16(8), SN_LE32(8), SN_LE16(0), 7, ".50fake", 13, "setothermodeH" },
    { SN_LE32(0), 0x96, SN_LE16(11), SN_LE16(8), SN_LE32(8), SN_LE16(0), 7, ".49fake", 13, "setothermodeL" },
    { SN_LE32(0), 0x96, SN_LE16(11), SN_LE16(8), SN_LE32(8), SN_LE16(0), 7, ".51fake", 7, "texture" },
    { SN_LE32(0), 0x96, SN_LE16(11), SN_LE16(8), SN_LE32(8), SN_LE16(0), 7, ".53fake", 9, "perspnorm" },
    { SN_LE32(0), 0x96, SN_LE16(11), SN_LE16(8), SN_LE32(8), SN_LE16(0), 7, ".54fake", 6, "setimg" },
    { SN_LE32(0), 0x96, SN_LE16(11), SN_LE16(8), SN_LE32(8), SN_LE16(0), 7, ".55fake", 10, "setcombine" },
    { SN_LE32(0), 0x96, SN_LE16(11), SN_LE16(8), SN_LE32(8), SN_LE16(0), 7, ".56fake", 8, "setcolor" },
    { SN_LE32(0), 0x96, SN_LE16(11), SN_LE16(8), SN_LE32(8), SN_LE16(0), 7, ".57fake", 8, "fillrect" },
    { SN_LE32(0), 0x96, SN_LE16(11), SN_LE16(8), SN_LE32(8), SN_LE16(0), 7, ".58fake", 7, "settile" },
    { SN_LE32(0), 0x96, SN_LE16(11), SN_LE16(8), SN_LE32(8), SN_LE16(0), 7, ".59fake", 8, "loadtile" },
    { SN_LE32(0), 0x96, SN_LE16(11), SN_LE16(8), SN_LE32(8), SN_LE16(0), 7, ".59fake", 11, "settilesize" },
    { SN_LE32(0), 0x96, SN_LE16(11), SN_LE16(8), SN_LE32(8), SN_LE16(0), 7, ".59fake", 8, "loadtlut" },
    { SN_LE32(0), 0x94, SN_LE16(11), SN_LE16(5), SN_LE32(0), 25, "force_structure_alignment" },
    { SN_LE32(8), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(8), SN_LE16(0), 7, ".63fake", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(9), SN_LE32(8), SN_LE16(0), 7, ".63fake", 3, "Gfx" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(8), 7, ".64fake" },
    { SN_LE32(0), 0x94, SN_LE16(18), SN_LE16(14), SN_LE32(8), 3, "cmd" },
    { SN_LE32(8), 0x94, SN_LE16(18), SN_LE16(14), SN_LE32(8), 5, "flags" },
    { SN_LE32(16), 0x94, SN_LE16(18), SN_LE16(14), SN_LE32(16), 4, "gain" },
    { SN_LE32(4), 0x94, SN_LE16(8), SN_LE16(14), SN_LE32(0), 4, "addr" },
    { SN_LE32(8), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(8), SN_LE16(0), 7, ".64fake", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(8), SN_LE16(0), 7, ".64fake", 6, "Aadpcm" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(8), 7, ".65fake" },
    { SN_LE32(0), 0x94, SN_LE16(18), SN_LE16(14), SN_LE32(8), 3, "cmd" },
    { SN_LE32(8), 0x94, SN_LE16(18), SN_LE16(14), SN_LE32(8), 5, "flags" },
    { SN_LE32(16), 0x94, SN_LE16(18), SN_LE16(14), SN_LE32(16), 4, "gain" },
    { SN_LE32(4), 0x94, SN_LE16(8), SN_LE16(14), SN_LE32(0), 4, "addr" },
    { SN_LE32(8), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(8), SN_LE16(0), 7, ".65fake", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(8), SN_LE16(0), 7, ".65fake", 6, "Apolef" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(8), 7, ".66fake" },
    { SN_LE32(0), 0x94, SN_LE16(18), SN_LE16(14), SN_LE32(8), 3, "cmd" },
    { SN_LE32(8), 0x94, SN_LE16(18), SN_LE16(14), SN_LE32(8), 5, "flags" },
    { SN_LE32(16), 0x94, SN_LE16(18), SN_LE16(14), SN_LE32(16), 4, "pad1" },
    { SN_LE32(4), 0x94, SN_LE16(8), SN_LE16(14), SN_LE32(0), 4, "addr" },
    { SN_LE32(8), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(8), SN_LE16(0), 7, ".66fake", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(8), SN_LE16(0), 7, ".66fake", 9, "Aenvelope" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(8), 7, ".67fake" },
    { SN_LE32(0), 0x94, SN_LE16(18), SN_LE16(14), SN_LE32(8), 3, "cmd" },
    { SN_LE32(8), 0x94, SN_LE16(18), SN_LE16(14), SN_LE32(8), 4, "pad1" },
    { SN_LE32(16), 0x94, SN_LE16(18), SN_LE16(14), SN_LE32(16), 4, "dmem" },
    { SN_LE32(32), 0x94, SN_LE16(18), SN_LE16(14), SN_LE32(16), 4, "pad2" },
    { SN_LE32(48), 0x94, SN_LE16(18), SN_LE16(14), SN_LE32(16), 5, "count" },
    { SN_LE32(8), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(8), SN_LE16(0), 7, ".67fake", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(8), SN_LE16(0), 7, ".67fake", 10, "Aclearbuff" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(8), 7, ".68fake" },
    { SN_LE32(0), 0x94, SN_LE16(18), SN_LE16(14), SN_LE32(8), 3, "cmd" },
    { SN_LE32(8), 0x94, SN_LE16(18), SN_LE16(14), SN_LE32(8), 4, "pad1" },
    { SN_LE32(16), 0x94, SN_LE16(18), SN_LE16(14), SN_LE32(16), 4, "pad2" },
    { SN_LE32(32), 0x94, SN_LE16(18), SN_LE16(14), SN_LE32(16), 3, "inL" },
    { SN_LE32(48), 0x94, SN_LE16(18), SN_LE16(14), SN_LE32(16), 3, "inR" },
    { SN_LE32(8), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(8), SN_LE16(0), 7, ".68fake", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(8), SN_LE16(0), 7, ".68fake", 11, "Ainterleave" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(8), 7, ".69fake" },
    { SN_LE32(0), 0x94, SN_LE16(18), SN_LE16(14), SN_LE32(8), 3, "cmd" },
    { SN_LE32(8), 0x94, SN_LE16(18), SN_LE16(14), SN_LE32(24), 4, "pad1" },
    { SN_LE32(4), 0x94, SN_LE16(8), SN_LE16(14), SN_LE32(0), 4, "addr" },
    { SN_LE32(8), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(8), SN_LE16(0), 7, ".69fake", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(8), SN_LE16(0), 7, ".69fake", 9, "Aloadbuff" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(8), 7, ".70fake" },
    { SN_LE32(0), 0x94, SN_LE16(18), SN_LE16(14), SN_LE32(8), 3, "cmd" },
    { SN_LE32(8), 0x94, SN_LE16(18), SN_LE16(14), SN_LE32(8), 5, "flags" },
    { SN_LE32(16), 0x94, SN_LE16(18), SN_LE16(14), SN_LE32(16), 4, "pad1" },
    { SN_LE32(4), 0x94, SN_LE16(8), SN_LE16(14), SN_LE32(0), 4, "addr" },
    { SN_LE32(8), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(8), SN_LE16(0), 7, ".70fake", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(8), SN_LE16(0), 7, ".70fake", 9, "Aenvmixer" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(8), 7, ".71fake" },
    { SN_LE32(0), 0x94, SN_LE16(18), SN_LE16(14), SN_LE32(8), 3, "cmd" },
    { SN_LE32(8), 0x94, SN_LE16(18), SN_LE16(14), SN_LE32(8), 5, "flags" },
    { SN_LE32(16), 0x94, SN_LE16(18), SN_LE16(14), SN_LE32(16), 4, "gain" },
    { SN_LE32(32), 0x94, SN_LE16(18), SN_LE16(14), SN_LE32(16), 5, "dmemi" },
    { SN_LE32(48), 0x94, SN_LE16(18), SN_LE16(14), SN_LE32(16), 5, "dmemo" },
    { SN_LE32(8), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(8), SN_LE16(0), 7, ".71fake", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(8), SN_LE16(0), 7, ".71fake", 6, "Amixer" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(8), 7, ".72fake" },
    { SN_LE32(0), 0x94, SN_LE16(18), SN_LE16(14), SN_LE32(8), 3, "cmd" },
    { SN_LE32(8), 0x94, SN_LE16(18), SN_LE16(14), SN_LE32(8), 5, "flags" },
    { SN_LE32(16), 0x94, SN_LE16(18), SN_LE16(14), SN_LE32(16), 5, "dmem2" },
    { SN_LE32(4), 0x94, SN_LE16(8), SN_LE16(14), SN_LE32(0), 4, "addr" },
    { SN_LE32(8), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(8), SN_LE16(0), 7, ".72fake", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(8), SN_LE16(0), 7, ".72fake", 4, "Apan" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(8), 7, ".73fake" },
    { SN_LE32(0), 0x94, SN_LE16(18), SN_LE16(14), SN_LE32(8), 3, "cmd" },
    { SN_LE32(8), 0x94, SN_LE16(18), SN_LE16(14), SN_LE32(8), 5, "flags" },
    { SN_LE32(16), 0x94, SN_LE16(18), SN_LE16(14), SN_LE32(16), 5, "pitch" },
    { SN_LE32(4), 0x94, SN_LE16(8), SN_LE16(14), SN_LE32(0), 4, "addr" },
    { SN_LE32(8), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(8), SN_LE16(0), 7, ".73fake", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(8), SN_LE16(0), 7, ".73fake", 9, "Aresample" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(8), 7, ".74fake" },
    { SN_LE32(0), 0x94, SN_LE16(18), SN_LE16(14), SN_LE32(8), 3, "cmd" },
    { SN_LE32(8), 0x94, SN_LE16(18), SN_LE16(14), SN_LE32(8), 5, "flags" },
    { SN_LE32(16), 0x94, SN_LE16(18), SN_LE16(14), SN_LE32(16), 4, "pad1" },
    { SN_LE32(4), 0x94, SN_LE16(8), SN_LE16(14), SN_LE32(0), 4, "addr" },
    { SN_LE32(8), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(8), SN_LE16(0), 7, ".74fake", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(8), SN_LE16(0), 7, ".74fake", 7, "Areverb" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(8), 7, ".75fake" },
    { SN_LE32(0), 0x94, SN_LE16(18), SN_LE16(14), SN_LE32(8), 3, "cmd" },
    { SN_LE32(8), 0x94, SN_LE16(18), SN_LE16(14), SN_LE32(24), 4, "pad1" },
    { SN_LE32(4), 0x94, SN_LE16(8), SN_LE16(14), SN_LE32(0), 4, "addr" },
    { SN_LE32(8), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(8), SN_LE16(0), 7, ".75fake", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(8), SN_LE16(0), 7, ".75fake", 9, "Asavebuff" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(8), 7, ".76fake" },
    { SN_LE32(0), 0x94, SN_LE16(18), SN_LE16(14), SN_LE32(8), 3, "cmd" },
    { SN_LE32(8), 0x94, SN_LE16(18), SN_LE16(14), SN_LE32(24), 4, "pad1" },
    { SN_LE32(32), 0x94, SN_LE16(18), SN_LE16(14), SN_LE32(2), 4, "pad2" },
    { SN_LE32(34), 0x94, SN_LE16(18), SN_LE16(14), SN_LE32(4), 6, "number" },
    { SN_LE32(38), 0x94, SN_LE16(18), SN_LE16(14), SN_LE32(24), 4, "base" },
    { SN_LE32(8), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(8), SN_LE16(0), 7, ".76fake", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(8), SN_LE16(0), 7, ".76fake", 8, "Asegment" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(8), 7, ".77fake" },
    { SN_LE32(0), 0x94, SN_LE16(18), SN_LE16(14), SN_LE32(8), 3, "cmd" },
    { SN_LE32(8), 0x94, SN_LE16(18), SN_LE16(14), SN_LE32(8), 5, "flags" },
    { SN_LE32(16), 0x94, SN_LE16(18), SN_LE16(14), SN_LE32(16), 6, "dmemin" },
    { SN_LE32(32), 0x94, SN_LE16(18), SN_LE16(14), SN_LE32(16), 7, "dmemout" },
    { SN_LE32(48), 0x94, SN_LE16(18), SN_LE16(14), SN_LE32(16), 5, "count" },
    { SN_LE32(8), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(8), SN_LE16(0), 7, ".77fake", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(8), SN_LE16(0), 7, ".77fake", 8, "Asetbuff" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(8), 7, ".78fake" },
    { SN_LE32(0), 0x94, SN_LE16(18), SN_LE16(14), SN_LE32(8), 3, "cmd" },
    { SN_LE32(8), 0x94, SN_LE16(18), SN_LE16(14), SN_LE32(8), 5, "flags" },
    { SN_LE32(16), 0x94, SN_LE16(18), SN_LE16(14), SN_LE32(16), 3, "vol" },
    { SN_LE32(32), 0x94, SN_LE16(18), SN_LE16(14), SN_LE32(16), 6, "voltgt" },
    { SN_LE32(48), 0x94, SN_LE16(18), SN_LE16(14), SN_LE32(16), 7, "volrate" },
    { SN_LE32(8), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(8), SN_LE16(0), 7, ".78fake", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(8), SN_LE16(0), 7, ".78fake", 7, "Asetvol" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(8), 7, ".79fake" },
    { SN_LE32(0), 0x94, SN_LE16(18), SN_LE16(14), SN_LE32(8), 3, "cmd" },
    { SN_LE32(8), 0x94, SN_LE16(18), SN_LE16(14), SN_LE32(8), 4, "pad1" },
    { SN_LE32(16), 0x94, SN_LE16(18), SN_LE16(14), SN_LE32(16), 6, "dmemin" },
    { SN_LE32(32), 0x94, SN_LE16(18), SN_LE16(14), SN_LE32(16), 7, "dmemout" },
    { SN_LE32(48), 0x94, SN_LE16(18), SN_LE16(14), SN_LE32(16), 5, "count" },
    { SN_LE32(8), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(8), SN_LE16(0), 7, ".79fake", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(8), SN_LE16(0), 7, ".79fake", 9, "Admemmove" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(8), 7, ".80fake" },
    { SN_LE32(0), 0x94, SN_LE16(18), SN_LE16(14), SN_LE32(8), 3, "cmd" },
    { SN_LE32(8), 0x94, SN_LE16(18), SN_LE16(14), SN_LE32(8), 4, "pad1" },
    { SN_LE32(16), 0x94, SN_LE16(18), SN_LE16(14), SN_LE32(16), 5, "count" },
    { SN_LE32(4), 0x94, SN_LE16(8), SN_LE16(14), SN_LE32(0), 4, "addr" },
    { SN_LE32(8), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(8), SN_LE16(0), 7, ".80fake", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(8), SN_LE16(0), 7, ".80fake", 10, "Aloadadpcm" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(8), 7, ".81fake" },
    { SN_LE32(0), 0x94, SN_LE16(18), SN_LE16(14), SN_LE32(8), 3, "cmd" },
    { SN_LE32(8), 0x94, SN_LE16(18), SN_LE16(14), SN_LE32(8), 4, "pad1" },
    { SN_LE32(16), 0x94, SN_LE16(18), SN_LE16(14), SN_LE32(16), 4, "pad2" },
    { SN_LE32(4), 0x94, SN_LE16(8), SN_LE16(14), SN_LE32(0), 4, "addr" },
    { SN_LE32(8), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(8), SN_LE16(0), 7, ".81fake", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(8), SN_LE16(0), 7, ".81fake", 8, "Asetloop" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(8), 7, ".82fake" },
    { SN_LE32(0), 0x94, SN_LE16(8), SN_LE16(14), SN_LE32(0), 2, "w0" },
    { SN_LE32(4), 0x94, SN_LE16(8), SN_LE16(14), SN_LE32(0), 2, "w1" },
    { SN_LE32(8), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(8), SN_LE16(0), 7, ".82fake", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(8), SN_LE16(0), 7, ".82fake", 6, "Awords" },
    { SN_LE32(0), 0x94, SN_LE16(12), SN_LE16(9), SN_LE32(8), 7, ".83fake" },
    { SN_LE32(0), 0x96, SN_LE16(11), SN_LE16(8), SN_LE32(8), SN_LE16(0), 7, ".82fake", 5, "words" },
    { SN_LE32(0), 0x96, SN_LE16(11), SN_LE16(8), SN_LE32(8), SN_LE16(0), 7, ".64fake", 5, "adpcm" },
    { SN_LE32(0), 0x96, SN_LE16(11), SN_LE16(8), SN_LE32(8), SN_LE16(0), 7, ".65fake", 5, "polef" },
    { SN_LE32(0), 0x96, SN_LE16(11), SN_LE16(8), SN_LE32(8), SN_LE16(0), 7, ".67fake", 9, "clearbuff" },
    { SN_LE32(0), 0x96, SN_LE16(11), SN_LE16(8), SN_LE32(8), SN_LE16(0), 7, ".66fake", 8, "envelope" },
    { SN_LE32(0), 0x96, SN_LE16(11), SN_LE16(8), SN_LE32(8), SN_LE16(0), 7, ".68fake", 10, "interleave" },
    { SN_LE32(0), 0x96, SN_LE16(11), SN_LE16(8), SN_LE32(8), SN_LE16(0), 7, ".69fake", 8, "loadbuff" },
    { SN_LE32(0), 0x96, SN_LE16(11), SN_LE16(8), SN_LE32(8), SN_LE16(0), 7, ".70fake", 8, "envmixer" },
    { SN_LE32(0), 0x96, SN_LE16(11), SN_LE16(8), SN_LE32(8), SN_LE16(0), 7, ".73fake", 8, "resample" },
    { SN_LE32(0), 0x96, SN_LE16(11), SN_LE16(8), SN_LE32(8), SN_LE16(0), 7, ".74fake", 6, "reverb" },
    { SN_LE32(0), 0x96, SN_LE16(11), SN_LE16(8), SN_LE32(8), SN_LE16(0), 7, ".75fake", 8, "savebuff" },
    { SN_LE32(0), 0x96, SN_LE16(11), SN_LE16(8), SN_LE32(8), SN_LE16(0), 7, ".76fake", 7, "segment" },
    { SN_LE32(0), 0x96, SN_LE16(11), SN_LE16(8), SN_LE32(8), SN_LE16(0), 7, ".77fake", 7, "setbuff" },
    { SN_LE32(0), 0x96, SN_LE16(11), SN_LE16(8), SN_LE32(8), SN_LE16(0), 7, ".78fake", 6, "setvol" },
    { SN_LE32(0), 0x96, SN_LE16(11), SN_LE16(8), SN_LE32(8), SN_LE16(0), 7, ".79fake", 8, "dmemmove" },
    { SN_LE32(0), 0x96, SN_LE16(11), SN_LE16(8), SN_LE32(8), SN_LE16(0), 7, ".80fake", 9, "loadadpcm" },
    { SN_LE32(0), 0x96, SN_LE16(11), SN_LE16(8), SN_LE32(8), SN_LE16(0), 7, ".71fake", 5, "mixer" },
    { SN_LE32(0), 0x96, SN_LE16(11), SN_LE16(8), SN_LE32(8), SN_LE16(0), 7, ".81fake", 7, "setloop" },
    { SN_LE32(0), 0x94, SN_LE16(11), SN_LE16(5), SN_LE32(0), 17, "force_union_align" },
    { SN_LE32(8), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(8), SN_LE16(0), 7, ".83fake", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(9), SN_LE32(8), SN_LE16(0), 7, ".83fake", 4, "Acmd" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(51), SN_LE32(32), SN_LE16(1), SN_LE32(16), 0, 11, "ADPCM_STATE" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(51), SN_LE32(8), SN_LE16(1), SN_LE32(4), 0, 11, "POLEF_STATE" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(51), SN_LE32(32), SN_LE16(1), SN_LE32(16), 0, 14, "RESAMPLE_STATE" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(51), SN_LE32(80), SN_LE16(1), SN_LE32(40), 0, 12, "ENVMIX_STATE" },
    { SN_LE32(0), 0x94, SN_LE16(13), SN_LE16(5), SN_LE32(0), 11, "ALMicroTime" },
    { SN_LE32(0), 0x94, SN_LE16(13), SN_LE16(12), SN_LE32(0), 5, "ALPan" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(8), 8, "ALLink_s" },
    { SN_LE32(0), 0x96, SN_LE16(8), SN_LE16(24), SN_LE32(8), SN_LE16(0), 8, "ALLink_s", 4, "next" },
    { SN_LE32(4), 0x96, SN_LE16(8), SN_LE16(24), SN_LE32(8), SN_LE16(0), 8, "ALLink_s", 4, "prev" },
    { SN_LE32(8), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(8), SN_LE16(0), 8, "ALLink_s", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(8), SN_LE16(0), 8, "ALLink_s", 6, "ALLink" },
    { SN_LE32(0), 0x94, SN_LE16(13), SN_LE16(149), SN_LE32(0), 9, "ALDMAproc" },
    { SN_LE32(0), 0x94, SN_LE16(13), SN_LE16(2453), SN_LE32(0), 8, "ALDMANew" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(16), 7, ".84fake" },
    { SN_LE32(0), 0x94, SN_LE16(8), SN_LE16(28), SN_LE32(0), 4, "base" },
    { SN_LE32(4), 0x94, SN_LE16(8), SN_LE16(28), SN_LE32(0), 3, "cur" },
    { SN_LE32(8), 0x94, SN_LE16(8), SN_LE16(5), SN_LE32(0), 3, "len" },
    { SN_LE32(12), 0x94, SN_LE16(8), SN_LE16(5), SN_LE32(0), 5, "count" },
    { SN_LE32(16), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(16), SN_LE16(0), 7, ".84fake", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(16), SN_LE16(0), 7, ".84fake", 6, "ALHeap" },
    { SN_LE32(0), 0x94, SN_LE16(13), SN_LE16(12), SN_LE32(0), 6, "ALFxId" },
    { SN_LE32(0), 0x94, SN_LE16(13), SN_LE16(17), SN_LE32(0), 7, "ALFxRef" },
    { SN_LE32(0), 0x94, SN_LE16(15), SN_LE16(10), SN_LE32(4), 7, ".85fake" },
    { SN_LE32(0), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 13, "AL_ADPCM_WAVE" },
    { SN_LE32(1), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 13, "AL_RAW16_WAVE" },
    { SN_LE32(2), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 11, "AL_RAX_WAVE" },
    { SN_LE32(4), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(4), SN_LE16(0), 7, ".85fake", 4, ".eos" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(12), 7, ".86fake" },
    { SN_LE32(0), 0x94, SN_LE16(8), SN_LE16(5), SN_LE32(0), 5, "order" },
    { SN_LE32(4), 0x94, SN_LE16(8), SN_LE16(5), SN_LE32(0), 11, "npredictors" },
    { SN_LE32(8), 0x96, SN_LE16(8), SN_LE16(51), SN_LE32(2), SN_LE16(1), SN_LE32(1), 0, 4, "book" },
    { SN_LE32(12), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(12), SN_LE16(0), 7, ".86fake", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(12), SN_LE16(0), 7, ".86fake", 11, "ALADPCMBook" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(44), 7, ".87fake" },
    { SN_LE32(0), 0x94, SN_LE16(8), SN_LE16(15), SN_LE32(0), 5, "start" },
    { SN_LE32(4), 0x94, SN_LE16(8), SN_LE16(15), SN_LE32(0), 3, "end" },
    { SN_LE32(8), 0x94, SN_LE16(8), SN_LE16(15), SN_LE32(0), 5, "count" },
    { SN_LE32(12), 0x96, SN_LE16(8), SN_LE16(51), SN_LE32(32), SN_LE16(1), SN_LE32(16), 0, 5, "state" },
    { SN_LE32(44), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(44), SN_LE16(0), 7, ".87fake", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(44), SN_LE16(0), 7, ".87fake", 11, "ALADPCMloop" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(12), 7, ".88fake" },
    { SN_LE32(0), 0x94, SN_LE16(8), SN_LE16(15), SN_LE32(0), 5, "start" },
    { SN_LE32(4), 0x94, SN_LE16(8), SN_LE16(15), SN_LE32(0), 3, "end" },
    { SN_LE32(8), 0x94, SN_LE16(8), SN_LE16(15), SN_LE32(0), 5, "count" },
    { SN_LE32(12), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(12), SN_LE16(0), 7, ".88fake", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(12), SN_LE16(0), 7, ".88fake", 9, "ALRawLoop" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(12), 7, ".89fake" },
    { SN_LE32(0), 0x94, SN_LE16(8), SN_LE16(15), SN_LE32(0), 5, "start" },
    { SN_LE32(4), 0x94, SN_LE16(8), SN_LE16(15), SN_LE32(0), 3, "end" },
    { SN_LE32(8), 0x94, SN_LE16(8), SN_LE16(15), SN_LE32(0), 5, "count" },
    { SN_LE32(12), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(12), SN_LE16(0), 7, ".89fake", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(12), SN_LE16(0), 7, ".89fake", 9, "ALRaxLoop" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(16), 7, ".90fake" },
    { SN_LE32(0), 0x94, SN_LE16(8), SN_LE16(5), SN_LE32(0), 10, "attackTime" },
    { SN_LE32(4), 0x94, SN_LE16(8), SN_LE16(5), SN_LE32(0), 9, "decayTime" },
    { SN_LE32(8), 0x94, SN_LE16(8), SN_LE16(5), SN_LE32(0), 11, "releaseTime" },
    { SN_LE32(12), 0x94, SN_LE16(8), SN_LE16(12), SN_LE32(0), 12, "attackVolume" },
    { SN_LE32(13), 0x94, SN_LE16(8), SN_LE16(12), SN_LE32(0), 11, "decayVolume" },
    { SN_LE32(16), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(16), SN_LE16(0), 7, ".90fake", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(16), SN_LE16(0), 7, ".90fake", 10, "ALEnvelope" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(6), 7, ".91fake" },
    { SN_LE32(0), 0x94, SN_LE16(8), SN_LE16(12), SN_LE32(0), 11, "velocityMin" },
    { SN_LE32(1), 0x94, SN_LE16(8), SN_LE16(12), SN_LE32(0), 11, "velocityMax" },
    { SN_LE32(2), 0x94, SN_LE16(8), SN_LE16(12), SN_LE32(0), 6, "keyMin" },
    { SN_LE32(3), 0x94, SN_LE16(8), SN_LE16(12), SN_LE32(0), 6, "keyMax" },
    { SN_LE32(4), 0x94, SN_LE16(8), SN_LE16(12), SN_LE32(0), 7, "keyBase" },
    { SN_LE32(5), 0x94, SN_LE16(8), SN_LE16(2), SN_LE32(0), 6, "detune" },
    { SN_LE32(6), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(6), SN_LE16(0), 7, ".91fake", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(6), SN_LE16(0), 7, ".91fake", 8, "ALKeyMap" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(8), 7, ".92fake" },
    { SN_LE32(0), 0x96, SN_LE16(8), SN_LE16(24), SN_LE32(44), SN_LE16(0), 7, ".87fake", 4, "loop" },
    { SN_LE32(4), 0x96, SN_LE16(8), SN_LE16(24), SN_LE32(12), SN_LE16(0), 7, ".86fake", 4, "book" },
    { SN_LE32(8), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(8), SN_LE16(0), 7, ".92fake", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(8), SN_LE16(0), 7, ".92fake", 15, "ALADPCMWaveInfo" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(4), 7, ".93fake" },
    { SN_LE32(0), 0x96, SN_LE16(8), SN_LE16(24), SN_LE32(12), SN_LE16(0), 7, ".88fake", 4, "loop" },
    { SN_LE32(4), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(4), SN_LE16(0), 7, ".93fake", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(4), SN_LE16(0), 7, ".93fake", 13, "ALRAWWaveInfo" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(4), 7, ".94fake" },
    { SN_LE32(0), 0x96, SN_LE16(8), SN_LE16(24), SN_LE32(12), SN_LE16(0), 7, ".89fake", 4, "loop" },
    { SN_LE32(4), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(4), SN_LE16(0), 7, ".94fake", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(4), SN_LE16(0), 7, ".94fake", 13, "ALRaxWaveInfo" },
    { SN_LE32(0), 0x94, SN_LE16(12), SN_LE16(9), SN_LE32(8), 7, ".95fake" },
    { SN_LE32(0), 0x96, SN_LE16(11), SN_LE16(8), SN_LE32(8), SN_LE16(0), 7, ".92fake", 9, "adpcmWave" },
    { SN_LE32(0), 0x96, SN_LE16(11), SN_LE16(8), SN_LE32(4), SN_LE16(0), 7, ".93fake", 7, "rawWave" },
    { SN_LE32(0), 0x96, SN_LE16(11), SN_LE16(8), SN_LE32(4), SN_LE16(0), 7, ".94fake", 7, "raxWave" },
    { SN_LE32(8), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(8), SN_LE16(0), 7, ".95fake", 4, ".eos" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(20), 13, "ALWaveTable_s" },
    { SN_LE32(0), 0x94, SN_LE16(8), SN_LE16(28), SN_LE32(0), 4, "base" },
    { SN_LE32(4), 0x94, SN_LE16(8), SN_LE16(5), SN_LE32(0), 3, "len" },
    { SN_LE32(8), 0x94, SN_LE16(8), SN_LE16(12), SN_LE32(0), 4, "type" },
    { SN_LE32(9), 0x94, SN_LE16(8), SN_LE16(12), SN_LE32(0), 5, "flags" },
    { SN_LE32(12), 0x96, SN_LE16(8), SN_LE16(9), SN_LE32(8), SN_LE16(0), 7, ".95fake", 8, "waveInfo" },
    { SN_LE32(20), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(20), SN_LE16(0), 13, "ALWaveTable_s", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(20), SN_LE16(0), 13, "ALWaveTable_s", 11, "ALWaveTable" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(16), 9, "ALSound_s" },
    { SN_LE32(0), 0x96, SN_LE16(8), SN_LE16(24), SN_LE32(16), SN_LE16(0), 7, ".90fake", 8, "envelope" },
    { SN_LE32(4), 0x96, SN_LE16(8), SN_LE16(24), SN_LE32(6), SN_LE16(0), 7, ".91fake", 6, "keyMap" },
    { SN_LE32(8), 0x96, SN_LE16(8), SN_LE16(24), SN_LE32(20), SN_LE16(0), 13, "ALWaveTable_s", 9, "wavetable" },
    { SN_LE32(12), 0x94, SN_LE16(8), SN_LE16(12), SN_LE32(0), 9, "samplePan" },
    { SN_LE32(13), 0x94, SN_LE16(8), SN_LE16(12), SN_LE32(0), 12, "sampleVolume" },
    { SN_LE32(14), 0x94, SN_LE16(8), SN_LE16(12), SN_LE32(0), 5, "flags" },
    { SN_LE32(16), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(16), SN_LE16(0), 9, "ALSound_s", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(16), SN_LE16(0), 9, "ALSound_s", 7, "ALSound" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(20), 7, ".96fake" },
    { SN_LE32(0), 0x94, SN_LE16(8), SN_LE16(12), SN_LE32(0), 6, "volume" },
    { SN_LE32(1), 0x94, SN_LE16(8), SN_LE16(12), SN_LE32(0), 3, "pan" },
    { SN_LE32(2), 0x94, SN_LE16(8), SN_LE16(12), SN_LE32(0), 8, "priority" },
    { SN_LE32(3), 0x94, SN_LE16(8), SN_LE16(12), SN_LE32(0), 5, "flags" },
    { SN_LE32(4), 0x94, SN_LE16(8), SN_LE16(12), SN_LE32(0), 8, "tremType" },
    { SN_LE32(5), 0x94, SN_LE16(8), SN_LE16(12), SN_LE32(0), 8, "tremRate" },
    { SN_LE32(6), 0x94, SN_LE16(8), SN_LE16(12), SN_LE32(0), 9, "tremDepth" },
    { SN_LE32(7), 0x94, SN_LE16(8), SN_LE16(12), SN_LE32(0), 9, "tremDelay" },
    { SN_LE32(8), 0x94, SN_LE16(8), SN_LE16(12), SN_LE32(0), 7, "vibType" },
    { SN_LE32(9), 0x94, SN_LE16(8), SN_LE16(12), SN_LE32(0), 7, "vibRate" },
    { SN_LE32(10), 0x94, SN_LE16(8), SN_LE16(12), SN_LE32(0), 8, "vibDepth" },
    { SN_LE32(11), 0x94, SN_LE16(8), SN_LE16(12), SN_LE32(0), 8, "vibDelay" },
    { SN_LE32(12), 0x94, SN_LE16(8), SN_LE16(3), SN_LE32(0), 9, "bendRange" },
    { SN_LE32(14), 0x94, SN_LE16(8), SN_LE16(3), SN_LE32(0), 10, "soundCount" },
    { SN_LE32(16), 0x96, SN_LE16(8), SN_LE16(120), SN_LE32(4), SN_LE16(1), SN_LE32(1), 9, "ALSound_s", 10, "soundArray" },
    { SN_LE32(20), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(20), SN_LE16(0), 7, ".96fake", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(20), SN_LE16(0), 7, ".96fake", 12, "ALInstrument" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(16), 8, "ALBank_s" },
    { SN_LE32(0), 0x94, SN_LE16(8), SN_LE16(3), SN_LE32(0), 9, "instCount" },
    { SN_LE32(2), 0x94, SN_LE16(8), SN_LE16(12), SN_LE32(0), 5, "flags" },
    { SN_LE32(3), 0x94, SN_LE16(8), SN_LE16(12), SN_LE32(0), 3, "pad" },
    { SN_LE32(4), 0x94, SN_LE16(8), SN_LE16(5), SN_LE32(0), 10, "sampleRate" },
    { SN_LE32(8), 0x96, SN_LE16(8), SN_LE16(24), SN_LE32(20), SN_LE16(0), 7, ".96fake", 10, "percussion" },
    { SN_LE32(12), 0x96, SN_LE16(8), SN_LE16(120), SN_LE32(4), SN_LE16(1), SN_LE32(1), 7, ".96fake", 9, "instArray" },
    { SN_LE32(16), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(16), SN_LE16(0), 8, "ALBank_s", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(16), SN_LE16(0), 8, "ALBank_s", 6, "ALBank" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(8), 7, ".97fake" },
    { SN_LE32(0), 0x94, SN_LE16(8), SN_LE16(3), SN_LE32(0), 8, "revision" },
    { SN_LE32(2), 0x94, SN_LE16(8), SN_LE16(3), SN_LE32(0), 9, "bankCount" },
    { SN_LE32(4), 0x96, SN_LE16(8), SN_LE16(120), SN_LE32(4), SN_LE16(1), SN_LE32(1), 8, "ALBank_s", 9, "bankArray" },
    { SN_LE32(8), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(8), SN_LE16(0), 7, ".97fake", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(8), SN_LE16(0), 7, ".97fake", 10, "ALBankFile" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(8), 7, ".98fake" },
    { SN_LE32(0), 0x94, SN_LE16(8), SN_LE16(28), SN_LE32(0), 6, "offset" },
    { SN_LE32(4), 0x94, SN_LE16(8), SN_LE16(5), SN_LE32(0), 3, "len" },
    { SN_LE32(8), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(8), SN_LE16(0), 7, ".98fake", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(8), SN_LE16(0), 7, ".98fake", 9, "ALSeqData" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(12), 7, ".99fake" },
    { SN_LE32(0), 0x94, SN_LE16(8), SN_LE16(3), SN_LE32(0), 8, "revision" },
    { SN_LE32(2), 0x94, SN_LE16(8), SN_LE16(3), SN_LE32(0), 8, "seqCount" },
    { SN_LE32(4), 0x96, SN_LE16(8), SN_LE16(56), SN_LE32(8), SN_LE16(1), SN_LE32(1), 7, ".98fake", 8, "seqArray" },
    { SN_LE32(12), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(12), SN_LE16(0), 7, ".99fake", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(12), SN_LE16(0), 7, ".99fake", 9, "ALSeqFile" },
    { SN_LE32(0), 0x94, SN_LE16(13), SN_LE16(149), SN_LE32(0), 14, "ALVoiceHandler" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(36), 8, ".100fake" },
    { SN_LE32(0), 0x94, SN_LE16(8), SN_LE16(5), SN_LE32(0), 10, "maxVVoices" },
    { SN_LE32(4), 0x94, SN_LE16(8), SN_LE16(5), SN_LE32(0), 10, "maxPVoices" },
    { SN_LE32(8), 0x94, SN_LE16(8), SN_LE16(5), SN_LE32(0), 10, "maxUpdates" },
    { SN_LE32(12), 0x94, SN_LE16(8), SN_LE16(5), SN_LE32(0), 11, "maxFXbusses" },
    { SN_LE32(16), 0x94, SN_LE16(8), SN_LE16(17), SN_LE32(0), 7, "dmaproc" },
    { SN_LE32(20), 0x96, SN_LE16(8), SN_LE16(24), SN_LE32(16), SN_LE16(0), 7, ".84fake", 4, "heap" },
    { SN_LE32(24), 0x94, SN_LE16(8), SN_LE16(5), SN_LE32(0), 10, "outputRate" },
    { SN_LE32(28), 0x94, SN_LE16(8), SN_LE16(12), SN_LE32(0), 6, "fxType" },
    { SN_LE32(32), 0x94, SN_LE16(8), SN_LE16(21), SN_LE32(0), 6, "params" },
    { SN_LE32(36), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(36), SN_LE16(0), 8, ".100fake", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(36), SN_LE16(0), 8, ".100fake", 11, "ALSynConfig" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(20), 10, "ALPlayer_s" },
    { SN_LE32(0), 0x96, SN_LE16(8), SN_LE16(24), SN_LE32(20), SN_LE16(0), 10, "ALPlayer_s", 4, "next" },
    { SN_LE32(4), 0x94, SN_LE16(8), SN_LE16(17), SN_LE32(0), 10, "clientData" },
    { SN_LE32(8), 0x94, SN_LE16(8), SN_LE16(149), SN_LE32(0), 7, "handler" },
    { SN_LE32(12), 0x94, SN_LE16(8), SN_LE16(5), SN_LE32(0), 8, "callTime" },
    { SN_LE32(16), 0x94, SN_LE16(8), SN_LE16(5), SN_LE32(0), 11, "samplesLeft" },
    { SN_LE32(20), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(20), SN_LE16(0), 10, "ALPlayer_s", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(20), SN_LE16(0), 10, "ALPlayer_s", 8, "ALPlayer" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(28), 9, "ALVoice_s" },
    { SN_LE32(0), 0x96, SN_LE16(8), SN_LE16(8), SN_LE32(8), SN_LE16(0), 8, "ALLink_s", 4, "node" },
    { SN_LE32(8), 0x96, SN_LE16(8), SN_LE16(24), SN_LE32(0), SN_LE16(0), 8, "PVoice_s", 6, "pvoice" },
    { SN_LE32(12), 0x96, SN_LE16(8), SN_LE16(24), SN_LE32(20), SN_LE16(0), 13, "ALWaveTable_s", 5, "table" },
    { SN_LE32(16), 0x94, SN_LE16(8), SN_LE16(17), SN_LE32(0), 13, "clientPrivate" },
    { SN_LE32(20), 0x94, SN_LE16(8), SN_LE16(3), SN_LE32(0), 5, "state" },
    { SN_LE32(22), 0x94, SN_LE16(8), SN_LE16(3), SN_LE32(0), 8, "priority" },
    { SN_LE32(24), 0x94, SN_LE16(8), SN_LE16(3), SN_LE32(0), 5, "fxBus" },
    { SN_LE32(26), 0x94, SN_LE16(8), SN_LE16(3), SN_LE32(0), 10, "unityPitch" },
    { SN_LE32(28), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(28), SN_LE16(0), 9, "ALVoice_s", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(28), SN_LE16(0), 9, "ALVoice_s", 7, "ALVoice" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(6), 15, "ALVoiceConfig_s" },
    { SN_LE32(0), 0x94, SN_LE16(8), SN_LE16(3), SN_LE32(0), 8, "priority" },
    { SN_LE32(2), 0x94, SN_LE16(8), SN_LE16(3), SN_LE32(0), 5, "fxBus" },
    { SN_LE32(4), 0x94, SN_LE16(8), SN_LE16(12), SN_LE32(0), 10, "unityPitch" },
    { SN_LE32(6), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(6), SN_LE16(0), 15, "ALVoiceConfig_s", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(6), SN_LE16(0), 15, "ALVoiceConfig_s", 13, "ALVoiceConfig" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(76), 8, ".101fake" },
    { SN_LE32(0), 0x96, SN_LE16(8), SN_LE16(24), SN_LE32(20), SN_LE16(0), 10, "ALPlayer_s", 4, "head" },
    { SN_LE32(4), 0x96, SN_LE16(8), SN_LE16(8), SN_LE32(8), SN_LE16(0), 8, "ALLink_s", 9, "pFreeList" },
    { SN_LE32(12), 0x96, SN_LE16(8), SN_LE16(8), SN_LE32(8), SN_LE16(0), 8, "ALLink_s", 10, "pAllocList" },
    { SN_LE32(20), 0x96, SN_LE16(8), SN_LE16(8), SN_LE32(8), SN_LE16(0), 8, "ALLink_s", 9, "pLameList" },
    { SN_LE32(28), 0x94, SN_LE16(8), SN_LE16(5), SN_LE32(0), 12, "paramSamples" },
    { SN_LE32(32), 0x94, SN_LE16(8), SN_LE16(5), SN_LE32(0), 10, "curSamples" },
    { SN_LE32(36), 0x94, SN_LE16(8), SN_LE16(2453), SN_LE32(0), 3, "dma" },
    { SN_LE32(40), 0x96, SN_LE16(8), SN_LE16(24), SN_LE32(16), SN_LE16(0), 7, ".84fake", 4, "heap" },
    { SN_LE32(44), 0x96, SN_LE16(8), SN_LE16(24), SN_LE32(0), SN_LE16(0), 9, "ALParam_s", 9, "paramList" },
    { SN_LE32(48), 0x96, SN_LE16(8), SN_LE16(24), SN_LE32(0), SN_LE16(0), 11, "ALMainBus_s", 7, "mainBus" },
    { SN_LE32(52), 0x96, SN_LE16(8), SN_LE16(24), SN_LE32(0), SN_LE16(0), 10, "ALAuxBus_s", 6, "auxBus" },
    { SN_LE32(56), 0x96, SN_LE16(8), SN_LE16(24), SN_LE32(0), SN_LE16(0), 10, "ALFilter_s", 12, "outputFilter" },
    { SN_LE32(60), 0x94, SN_LE16(8), SN_LE16(5), SN_LE32(0), 10, "numPVoices" },
    { SN_LE32(64), 0x94, SN_LE16(8), SN_LE16(5), SN_LE32(0), 12, "maxAuxBusses" },
    { SN_LE32(68), 0x94, SN_LE16(8), SN_LE16(5), SN_LE32(0), 10, "outputRate" },
    { SN_LE32(72), 0x94, SN_LE16(8), SN_LE16(5), SN_LE32(0), 13, "maxOutSamples" },
    { SN_LE32(76), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(76), SN_LE16(0), 8, ".101fake", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(76), SN_LE16(0), 8, ".101fake", 7, "ALSynth" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(76), 8, ".102fake" },
    { SN_LE32(0), 0x96, SN_LE16(8), SN_LE16(8), SN_LE32(76), SN_LE16(0), 8, ".101fake", 4, "drvr" },
    { SN_LE32(76), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(76), SN_LE16(0), 8, ".102fake", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(76), SN_LE16(0), 8, ".102fake", 9, "ALGlobals" },
    { SN_LE32(0), 0x94, SN_LE16(15), SN_LE16(10), SN_LE32(4), 5, "ALMsg" },
    { SN_LE32(0), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 14, "AL_SEQ_REF_EVT" },
    { SN_LE32(1), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 15, "AL_SEQ_MIDI_EVT" },
    { SN_LE32(2), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 16, "AL_SEQP_MIDI_EVT" },
    { SN_LE32(3), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 12, "AL_TEMPO_EVT" },
    { SN_LE32(4), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 14, "AL_SEQ_END_EVT" },
    { SN_LE32(5), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 15, "AL_NOTE_END_EVT" },
    { SN_LE32(6), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 15, "AL_SEQP_ENV_EVT" },
    { SN_LE32(7), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 16, "AL_SEQP_META_EVT" },
    { SN_LE32(8), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 16, "AL_SEQP_PROG_EVT" },
    { SN_LE32(9), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 15, "AL_SEQP_API_EVT" },
    { SN_LE32(10), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 15, "AL_SEQP_VOL_EVT" },
    { SN_LE32(11), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 16, "AL_SEQP_LOOP_EVT" },
    { SN_LE32(12), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 20, "AL_SEQP_PRIORITY_EVT" },
    { SN_LE32(13), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 15, "AL_SEQP_SEQ_EVT" },
    { SN_LE32(14), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 16, "AL_SEQP_BANK_EVT" },
    { SN_LE32(15), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 16, "AL_SEQP_PLAY_EVT" },
    { SN_LE32(16), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 16, "AL_SEQP_STOP_EVT" },
    { SN_LE32(17), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 20, "AL_SEQP_STOPPING_EVT" },
    { SN_LE32(18), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 12, "AL_TRACK_END" },
    { SN_LE32(19), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 16, "AL_CSP_LOOPSTART" },
    { SN_LE32(20), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 14, "AL_CSP_LOOPEND" },
    { SN_LE32(21), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 18, "AL_CSP_NOTEOFF_EVT" },
    { SN_LE32(22), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 15, "AL_TREM_OSC_EVT" },
    { SN_LE32(23), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 14, "AL_VIB_OSC_EVT" },
    { SN_LE32(4), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(4), SN_LE16(0), 5, "ALMsg", 4, ".eos" },
    { SN_LE32(0), 0x94, SN_LE16(15), SN_LE16(10), SN_LE32(4), 13, "AL_MIDIstatus" },
    { SN_LE32(15), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 19, "AL_MIDI_ChannelMask" },
    { SN_LE32(240), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 18, "AL_MIDI_StatusMask" },
    { SN_LE32(128), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 20, "AL_MIDI_ChannelVoice" },
    { SN_LE32(128), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 15, "AL_MIDI_NoteOff" },
    { SN_LE32(144), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 14, "AL_MIDI_NoteOn" },
    { SN_LE32(160), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 23, "AL_MIDI_PolyKeyPressure" },
    { SN_LE32(176), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 21, "AL_MIDI_ControlChange" },
    { SN_LE32(176), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 25, "AL_MIDI_ChannelModeSelect" },
    { SN_LE32(192), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 21, "AL_MIDI_ProgramChange" },
    { SN_LE32(208), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 23, "AL_MIDI_ChannelPressure" },
    { SN_LE32(224), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 23, "AL_MIDI_PitchBendChange" },
    { SN_LE32(240), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 13, "AL_MIDI_SysEx" },
    { SN_LE32(241), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 20, "AL_MIDI_SystemCommon" },
    { SN_LE32(241), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 28, "AL_MIDI_TimeCodeQuarterFrame" },
    { SN_LE32(242), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 27, "AL_MIDI_SongPositionPointer" },
    { SN_LE32(243), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 18, "AL_MIDI_SongSelect" },
    { SN_LE32(244), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 18, "AL_MIDI_Undefined1" },
    { SN_LE32(245), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 18, "AL_MIDI_Undefined2" },
    { SN_LE32(246), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 19, "AL_MIDI_TuneRequest" },
    { SN_LE32(247), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 11, "AL_MIDI_EOX" },
    { SN_LE32(248), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 22, "AL_MIDI_SystemRealTime" },
    { SN_LE32(248), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 19, "AL_MIDI_TimingClock" },
    { SN_LE32(249), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 18, "AL_MIDI_Undefined3" },
    { SN_LE32(250), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 13, "AL_MIDI_Start" },
    { SN_LE32(251), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 16, "AL_MIDI_Continue" },
    { SN_LE32(252), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 12, "AL_MIDI_Stop" },
    { SN_LE32(253), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 18, "AL_MIDI_Undefined4" },
    { SN_LE32(254), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 21, "AL_MIDI_ActiveSensing" },
    { SN_LE32(255), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 19, "AL_MIDI_SystemReset" },
    { SN_LE32(255), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 12, "AL_MIDI_Meta" },
    { SN_LE32(4), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(4), SN_LE16(0), 13, "AL_MIDIstatus", 4, ".eos" },
    { SN_LE32(0), 0x94, SN_LE16(15), SN_LE16(10), SN_LE32(4), 11, "AL_MIDIctrl" },
    { SN_LE32(7), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 19, "AL_MIDI_VOLUME_CTRL" },
    { SN_LE32(10), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 16, "AL_MIDI_PAN_CTRL" },
    { SN_LE32(16), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 21, "AL_MIDI_PRIORITY_CTRL" },
    { SN_LE32(20), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 17, "AL_MIDI_FX_CTRL_0" },
    { SN_LE32(21), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 17, "AL_MIDI_FX_CTRL_1" },
    { SN_LE32(22), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 17, "AL_MIDI_FX_CTRL_2" },
    { SN_LE32(23), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 17, "AL_MIDI_FX_CTRL_3" },
    { SN_LE32(24), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 17, "AL_MIDI_FX_CTRL_4" },
    { SN_LE32(25), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 17, "AL_MIDI_FX_CTRL_5" },
    { SN_LE32(26), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 17, "AL_MIDI_FX_CTRL_6" },
    { SN_LE32(27), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 17, "AL_MIDI_FX_CTRL_7" },
    { SN_LE32(28), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 17, "AL_MIDI_FX_CTRL_8" },
    { SN_LE32(29), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 17, "AL_MIDI_FX_CTRL_9" },
    { SN_LE32(64), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 20, "AL_MIDI_SUSTAIN_CTRL" },
    { SN_LE32(91), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 16, "AL_MIDI_FX1_CTRL" },
    { SN_LE32(93), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 16, "AL_MIDI_FX3_CTRL" },
    { SN_LE32(4), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(4), SN_LE16(0), 11, "AL_MIDIctrl", 4, ".eos" },
    { SN_LE32(0), 0x94, SN_LE16(15), SN_LE16(10), SN_LE32(4), 11, "AL_MIDImeta" },
    { SN_LE32(81), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 18, "AL_MIDI_META_TEMPO" },
    { SN_LE32(47), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 16, "AL_MIDI_META_EOT" },
    { SN_LE32(4), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(4), SN_LE16(0), 11, "AL_MIDImeta", 4, ".eos" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(16), 8, ".103fake" },
    { SN_LE32(0), 0x94, SN_LE16(8), SN_LE16(28), SN_LE32(0), 6, "curPtr" },
    { SN_LE32(4), 0x94, SN_LE16(8), SN_LE16(5), SN_LE32(0), 9, "lastTicks" },
    { SN_LE32(8), 0x94, SN_LE16(8), SN_LE16(5), SN_LE32(0), 8, "curTicks" },
    { SN_LE32(12), 0x94, SN_LE16(8), SN_LE16(3), SN_LE32(0), 10, "lastStatus" },
    { SN_LE32(16), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(16), SN_LE16(0), 8, ".103fake", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(16), SN_LE16(0), 8, ".103fake", 11, "ALSeqMarker" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(12), 8, ".104fake" },
    { SN_LE32(0), 0x94, SN_LE16(8), SN_LE16(5), SN_LE32(0), 5, "ticks" },
    { SN_LE32(4), 0x94, SN_LE16(8), SN_LE16(12), SN_LE32(0), 6, "status" },
    { SN_LE32(5), 0x94, SN_LE16(8), SN_LE16(12), SN_LE32(0), 5, "byte1" },
    { SN_LE32(6), 0x94, SN_LE16(8), SN_LE16(12), SN_LE32(0), 5, "byte2" },
    { SN_LE32(8), 0x94, SN_LE16(8), SN_LE16(15), SN_LE32(0), 8, "duration" },
    { SN_LE32(12), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(12), SN_LE16(0), 8, ".104fake", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(12), SN_LE16(0), 8, ".104fake", 11, "ALMIDIEvent" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(12), 8, ".105fake" },
    { SN_LE32(0), 0x94, SN_LE16(8), SN_LE16(5), SN_LE32(0), 5, "ticks" },
    { SN_LE32(4), 0x94, SN_LE16(8), SN_LE16(12), SN_LE32(0), 6, "status" },
    { SN_LE32(5), 0x94, SN_LE16(8), SN_LE16(12), SN_LE32(0), 4, "type" },
    { SN_LE32(6), 0x94, SN_LE16(8), SN_LE16(12), SN_LE32(0), 3, "len" },
    { SN_LE32(7), 0x94, SN_LE16(8), SN_LE16(12), SN_LE32(0), 5, "byte1" },
    { SN_LE32(8), 0x94, SN_LE16(8), SN_LE16(12), SN_LE32(0), 5, "byte2" },
    { SN_LE32(9), 0x94, SN_LE16(8), SN_LE16(12), SN_LE32(0), 5, "byte3" },
    { SN_LE32(12), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(12), SN_LE16(0), 8, ".105fake", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(12), SN_LE16(0), 8, ".105fake", 12, "ALTempoEvent" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(8), 8, ".106fake" },
    { SN_LE32(0), 0x94, SN_LE16(8), SN_LE16(5), SN_LE32(0), 5, "ticks" },
    { SN_LE32(4), 0x94, SN_LE16(8), SN_LE16(12), SN_LE32(0), 6, "status" },
    { SN_LE32(5), 0x94, SN_LE16(8), SN_LE16(12), SN_LE32(0), 4, "type" },
    { SN_LE32(6), 0x94, SN_LE16(8), SN_LE16(12), SN_LE32(0), 3, "len" },
    { SN_LE32(8), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(8), SN_LE16(0), 8, ".106fake", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(8), SN_LE16(0), 8, ".106fake", 10, "ALEndEvent" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(4), 8, ".107fake" },
    { SN_LE32(0), 0x96, SN_LE16(8), SN_LE16(24), SN_LE32(28), SN_LE16(0), 9, "ALVoice_s", 5, "voice" },
    { SN_LE32(4), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(4), SN_LE16(0), 8, ".107fake", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(4), SN_LE16(0), 8, ".107fake", 11, "ALNoteEvent" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(12), 8, ".108fake" },
    { SN_LE32(0), 0x96, SN_LE16(8), SN_LE16(24), SN_LE32(28), SN_LE16(0), 9, "ALVoice_s", 5, "voice" },
    { SN_LE32(4), 0x94, SN_LE16(8), SN_LE16(5), SN_LE32(0), 5, "delta" },
    { SN_LE32(8), 0x94, SN_LE16(8), SN_LE16(12), SN_LE32(0), 3, "vol" },
    { SN_LE32(12), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(12), SN_LE16(0), 8, ".108fake", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(12), SN_LE16(0), 8, ".108fake", 13, "ALVolumeEvent" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(2), 8, ".109fake" },
    { SN_LE32(0), 0x94, SN_LE16(8), SN_LE16(3), SN_LE32(0), 3, "vol" },
    { SN_LE32(2), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(2), SN_LE16(0), 8, ".109fake", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(2), SN_LE16(0), 8, ".109fake", 14, "ALSeqpVolEvent" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(12), 8, ".110fake" },
    { SN_LE32(0), 0x96, SN_LE16(8), SN_LE16(24), SN_LE32(16), SN_LE16(0), 8, ".103fake", 5, "start" },
    { SN_LE32(4), 0x96, SN_LE16(8), SN_LE16(24), SN_LE32(16), SN_LE16(0), 8, ".103fake", 3, "end" },
    { SN_LE32(8), 0x94, SN_LE16(8), SN_LE16(5), SN_LE32(0), 5, "count" },
    { SN_LE32(12), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(12), SN_LE16(0), 8, ".110fake", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(12), SN_LE16(0), 8, ".110fake", 15, "ALSeqpLoopEvent" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(2), 8, ".111fake" },
    { SN_LE32(0), 0x94, SN_LE16(8), SN_LE16(12), SN_LE32(0), 4, "chan" },
    { SN_LE32(1), 0x94, SN_LE16(8), SN_LE16(12), SN_LE32(0), 8, "priority" },
    { SN_LE32(2), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(2), SN_LE16(0), 8, ".111fake", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(2), SN_LE16(0), 8, ".111fake", 19, "ALSeqpPriorityEvent" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(4), 8, ".112fake" },
    { SN_LE32(0), 0x94, SN_LE16(8), SN_LE16(17), SN_LE32(0), 3, "seq" },
    { SN_LE32(4), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(4), SN_LE16(0), 8, ".112fake", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(4), SN_LE16(0), 8, ".112fake", 14, "ALSeqpSeqEvent" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(4), 8, ".113fake" },
    { SN_LE32(0), 0x96, SN_LE16(8), SN_LE16(24), SN_LE32(16), SN_LE16(0), 8, "ALBank_s", 4, "bank" },
    { SN_LE32(4), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(4), SN_LE16(0), 8, ".113fake", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(4), SN_LE16(0), 8, ".113fake", 15, "ALSeqpBankEvent" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(12), 8, ".114fake" },
    { SN_LE32(0), 0x96, SN_LE16(8), SN_LE16(24), SN_LE32(0), SN_LE16(0), 14, "ALVoiceState_s", 2, "vs" },
    { SN_LE32(4), 0x94, SN_LE16(8), SN_LE16(17), SN_LE32(0), 8, "oscState" },
    { SN_LE32(8), 0x94, SN_LE16(8), SN_LE16(12), SN_LE32(0), 4, "chan" },
    { SN_LE32(12), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(12), SN_LE16(0), 8, ".114fake", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(12), SN_LE16(0), 8, ".114fake", 10, "ALOscEvent" },
    { SN_LE32(0), 0x94, SN_LE16(12), SN_LE16(9), SN_LE32(12), 8, ".115fake" },
    { SN_LE32(0), 0x96, SN_LE16(11), SN_LE16(8), SN_LE32(12), SN_LE16(0), 8, ".104fake", 4, "midi" },
    { SN_LE32(0), 0x96, SN_LE16(11), SN_LE16(8), SN_LE32(12), SN_LE16(0), 8, ".105fake", 5, "tempo" },
    { SN_LE32(0), 0x96, SN_LE16(11), SN_LE16(8), SN_LE32(8), SN_LE16(0), 8, ".106fake", 3, "end" },
    { SN_LE32(0), 0x96, SN_LE16(11), SN_LE16(8), SN_LE32(4), SN_LE16(0), 8, ".107fake", 4, "note" },
    { SN_LE32(0), 0x96, SN_LE16(11), SN_LE16(8), SN_LE32(12), SN_LE16(0), 8, ".108fake", 3, "vol" },
    { SN_LE32(0), 0x96, SN_LE16(11), SN_LE16(8), SN_LE32(12), SN_LE16(0), 8, ".110fake", 4, "loop" },
    { SN_LE32(0), 0x96, SN_LE16(11), SN_LE16(8), SN_LE32(2), SN_LE16(0), 8, ".109fake", 5, "spvol" },
    { SN_LE32(0), 0x96, SN_LE16(11), SN_LE16(8), SN_LE32(2), SN_LE16(0), 8, ".111fake", 10, "sppriority" },
    { SN_LE32(0), 0x96, SN_LE16(11), SN_LE16(8), SN_LE32(4), SN_LE16(0), 8, ".112fake", 5, "spseq" },
    { SN_LE32(0), 0x96, SN_LE16(11), SN_LE16(8), SN_LE32(4), SN_LE16(0), 8, ".113fake", 6, "spbank" },
    { SN_LE32(0), 0x96, SN_LE16(11), SN_LE16(8), SN_LE32(12), SN_LE16(0), 8, ".114fake", 3, "osc" },
    { SN_LE32(12), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(12), SN_LE16(0), 8, ".115fake", 4, ".eos" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(16), 8, ".116fake" },
    { SN_LE32(0), 0x94, SN_LE16(8), SN_LE16(3), SN_LE32(0), 4, "type" },
    { SN_LE32(4), 0x96, SN_LE16(8), SN_LE16(9), SN_LE32(12), SN_LE16(0), 8, ".115fake", 3, "msg" },
    { SN_LE32(16), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(16), SN_LE16(0), 8, ".116fake", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(16), SN_LE16(0), 8, ".116fake", 7, "ALEvent" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(28), 8, ".117fake" },
    { SN_LE32(0), 0x96, SN_LE16(8), SN_LE16(8), SN_LE32(8), SN_LE16(0), 8, "ALLink_s", 4, "node" },
    { SN_LE32(8), 0x94, SN_LE16(8), SN_LE16(5), SN_LE32(0), 5, "delta" },
    { SN_LE32(12), 0x96, SN_LE16(8), SN_LE16(8), SN_LE32(16), SN_LE16(0), 8, ".116fake", 3, "evt" },
    { SN_LE32(28), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(28), SN_LE16(0), 8, ".117fake", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(28), SN_LE16(0), 8, ".117fake", 15, "ALEventListItem" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(20), 8, ".118fake" },
    { SN_LE32(0), 0x96, SN_LE16(8), SN_LE16(8), SN_LE32(8), SN_LE16(0), 8, "ALLink_s", 8, "freeList" },
    { SN_LE32(8), 0x96, SN_LE16(8), SN_LE16(8), SN_LE32(8), SN_LE16(0), 8, "ALLink_s", 9, "allocList" },
    { SN_LE32(16), 0x94, SN_LE16(8), SN_LE16(5), SN_LE32(0), 10, "eventCount" },
    { SN_LE32(20), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(20), SN_LE16(0), 8, ".118fake", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(20), SN_LE16(0), 8, ".118fake", 12, "ALEventQueue" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(56), 14, "ALVoiceState_s" },
    { SN_LE32(0), 0x96, SN_LE16(8), SN_LE16(24), SN_LE32(56), SN_LE16(0), 14, "ALVoiceState_s", 4, "next" },
    { SN_LE32(4), 0x96, SN_LE16(8), SN_LE16(8), SN_LE32(28), SN_LE16(0), 9, "ALVoice_s", 5, "voice" },
    { SN_LE32(32), 0x96, SN_LE16(8), SN_LE16(24), SN_LE32(16), SN_LE16(0), 9, "ALSound_s", 5, "sound" },
    { SN_LE32(36), 0x94, SN_LE16(8), SN_LE16(5), SN_LE32(0), 10, "envEndTime" },
    { SN_LE32(40), 0x94, SN_LE16(8), SN_LE16(6), SN_LE32(0), 5, "pitch" },
    { SN_LE32(44), 0x94, SN_LE16(8), SN_LE16(6), SN_LE32(0), 7, "vibrato" },
    { SN_LE32(48), 0x94, SN_LE16(8), SN_LE16(12), SN_LE32(0), 7, "envGain" },
    { SN_LE32(49), 0x94, SN_LE16(8), SN_LE16(12), SN_LE32(0), 7, "channel" },
    { SN_LE32(50), 0x94, SN_LE16(8), SN_LE16(12), SN_LE32(0), 3, "key" },
    { SN_LE32(51), 0x94, SN_LE16(8), SN_LE16(12), SN_LE32(0), 8, "velocity" },
    { SN_LE32(52), 0x94, SN_LE16(8), SN_LE16(12), SN_LE32(0), 8, "envPhase" },
    { SN_LE32(53), 0x94, SN_LE16(8), SN_LE16(12), SN_LE32(0), 5, "phase" },
    { SN_LE32(54), 0x94, SN_LE16(8), SN_LE16(12), SN_LE32(0), 7, "tremelo" },
    { SN_LE32(55), 0x94, SN_LE16(8), SN_LE16(12), SN_LE32(0), 5, "flags" },
    { SN_LE32(56), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(56), SN_LE16(0), 14, "ALVoiceState_s", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(56), SN_LE16(0), 14, "ALVoiceState_s", 12, "ALVoiceState" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(16), 8, ".119fake" },
    { SN_LE32(0), 0x96, SN_LE16(8), SN_LE16(24), SN_LE32(20), SN_LE16(0), 7, ".96fake", 10, "instrument" },
    { SN_LE32(4), 0x94, SN_LE16(8), SN_LE16(3), SN_LE32(0), 9, "bendRange" },
    { SN_LE32(6), 0x94, SN_LE16(8), SN_LE16(12), SN_LE32(0), 4, "fxId" },
    { SN_LE32(7), 0x94, SN_LE16(8), SN_LE16(12), SN_LE32(0), 3, "pan" },
    { SN_LE32(8), 0x94, SN_LE16(8), SN_LE16(12), SN_LE32(0), 8, "priority" },
    { SN_LE32(9), 0x94, SN_LE16(8), SN_LE16(12), SN_LE32(0), 3, "vol" },
    { SN_LE32(10), 0x94, SN_LE16(8), SN_LE16(12), SN_LE32(0), 5, "fxmix" },
    { SN_LE32(11), 0x94, SN_LE16(8), SN_LE16(12), SN_LE32(0), 7, "sustain" },
    { SN_LE32(12), 0x94, SN_LE16(8), SN_LE16(6), SN_LE32(0), 9, "pitchBend" },
    { SN_LE32(16), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(16), SN_LE16(0), 8, ".119fake", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(16), SN_LE16(0), 8, ".119fake", 11, "ALChanState" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(28), 7, "ALSeq_s" },
    { SN_LE32(0), 0x94, SN_LE16(8), SN_LE16(28), SN_LE32(0), 4, "base" },
    { SN_LE32(4), 0x94, SN_LE16(8), SN_LE16(28), SN_LE32(0), 10, "trackStart" },
    { SN_LE32(8), 0x94, SN_LE16(8), SN_LE16(28), SN_LE32(0), 6, "curPtr" },
    { SN_LE32(12), 0x94, SN_LE16(8), SN_LE16(5), SN_LE32(0), 9, "lastTicks" },
    { SN_LE32(16), 0x94, SN_LE16(8), SN_LE16(5), SN_LE32(0), 3, "len" },
    { SN_LE32(20), 0x94, SN_LE16(8), SN_LE16(6), SN_LE32(0), 4, "qnpt" },
    { SN_LE32(24), 0x94, SN_LE16(8), SN_LE16(3), SN_LE32(0), 8, "division" },
    { SN_LE32(26), 0x94, SN_LE16(8), SN_LE16(3), SN_LE32(0), 10, "lastStatus" },
    { SN_LE32(28), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(28), SN_LE16(0), 7, "ALSeq_s", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(28), SN_LE16(0), 7, "ALSeq_s", 5, "ALSeq" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(68), 8, ".120fake" },
    { SN_LE32(0), 0x96, SN_LE16(8), SN_LE16(63), SN_LE32(64), SN_LE16(1), SN_LE32(16), 0, 11, "trackOffset" },
    { SN_LE32(64), 0x94, SN_LE16(8), SN_LE16(15), SN_LE32(0), 8, "division" },
    { SN_LE32(68), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(68), SN_LE16(0), 8, ".120fake", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(68), SN_LE16(0), 8, ".120fake", 10, "ALCMidiHdr" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(248), 8, "ALCSeq_s" },
    { SN_LE32(0), 0x96, SN_LE16(8), SN_LE16(24), SN_LE32(68), SN_LE16(0), 8, ".120fake", 4, "base" },
    { SN_LE32(4), 0x94, SN_LE16(8), SN_LE16(15), SN_LE32(0), 11, "validTracks" },
    { SN_LE32(8), 0x94, SN_LE16(8), SN_LE16(6), SN_LE32(0), 4, "qnpt" },
    { SN_LE32(12), 0x94, SN_LE16(8), SN_LE16(15), SN_LE32(0), 9, "lastTicks" },
    { SN_LE32(16), 0x94, SN_LE16(8), SN_LE16(15), SN_LE32(0), 14, "lastDeltaTicks" },
    { SN_LE32(20), 0x94, SN_LE16(8), SN_LE16(15), SN_LE32(0), 9, "deltaFlag" },
    { SN_LE32(24), 0x96, SN_LE16(8), SN_LE16(124), SN_LE32(64), SN_LE16(1), SN_LE32(16), 0, 6, "curLoc" },
    { SN_LE32(88), 0x96, SN_LE16(8), SN_LE16(124), SN_LE32(64), SN_LE16(1), SN_LE32(16), 0, 8, "curBUPtr" },
    { SN_LE32(152), 0x96, SN_LE16(8), SN_LE16(60), SN_LE32(16), SN_LE16(1), SN_LE32(16), 0, 8, "curBULen" },
    { SN_LE32(168), 0x96, SN_LE16(8), SN_LE16(60), SN_LE32(16), SN_LE16(1), SN_LE32(16), 0, 10, "lastStatus" },
    { SN_LE32(184), 0x96, SN_LE16(8), SN_LE16(63), SN_LE32(64), SN_LE16(1), SN_LE32(16), 0, 13, "evtDeltaTicks" },
    { SN_LE32(248), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(248), SN_LE16(0), 8, "ALCSeq_s", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(248), SN_LE16(0), 8, "ALCSeq_s", 6, "ALCSeq" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(236), 8, ".121fake" },
    { SN_LE32(0), 0x94, SN_LE16(8), SN_LE16(15), SN_LE32(0), 11, "validTracks" },
    { SN_LE32(4), 0x94, SN_LE16(8), SN_LE16(5), SN_LE32(0), 9, "lastTicks" },
    { SN_LE32(8), 0x94, SN_LE16(8), SN_LE16(15), SN_LE32(0), 14, "lastDeltaTicks" },
    { SN_LE32(12), 0x96, SN_LE16(8), SN_LE16(124), SN_LE32(64), SN_LE16(1), SN_LE32(16), 0, 6, "curLoc" },
    { SN_LE32(76), 0x96, SN_LE16(8), SN_LE16(124), SN_LE32(64), SN_LE16(1), SN_LE32(16), 0, 8, "curBUPtr" },
    { SN_LE32(140), 0x96, SN_LE16(8), SN_LE16(60), SN_LE32(16), SN_LE16(1), SN_LE32(16), 0, 8, "curBULen" },
    { SN_LE32(156), 0x96, SN_LE16(8), SN_LE16(60), SN_LE32(16), SN_LE16(1), SN_LE32(16), 0, 10, "lastStatus" },
    { SN_LE32(172), 0x96, SN_LE16(8), SN_LE16(63), SN_LE32(64), SN_LE16(1), SN_LE32(16), 0, 13, "evtDeltaTicks" },
    { SN_LE32(236), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(236), SN_LE16(0), 8, ".121fake", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(236), SN_LE16(0), 8, ".121fake", 12, "ALCSeqMarker" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(28), 8, ".122fake" },
    { SN_LE32(0), 0x94, SN_LE16(8), SN_LE16(5), SN_LE32(0), 9, "maxVoices" },
    { SN_LE32(4), 0x94, SN_LE16(8), SN_LE16(5), SN_LE32(0), 9, "maxEvents" },
    { SN_LE32(8), 0x94, SN_LE16(8), SN_LE16(12), SN_LE32(0), 11, "maxChannels" },
    { SN_LE32(9), 0x94, SN_LE16(8), SN_LE16(12), SN_LE32(0), 10, "debugFlags" },
    { SN_LE32(12), 0x96, SN_LE16(8), SN_LE16(24), SN_LE32(16), SN_LE16(0), 7, ".84fake", 4, "heap" },
    { SN_LE32(16), 0x94, SN_LE16(8), SN_LE16(17), SN_LE32(0), 7, "initOsc" },
    { SN_LE32(20), 0x94, SN_LE16(8), SN_LE16(17), SN_LE32(0), 9, "updateOsc" },
    { SN_LE32(24), 0x94, SN_LE16(8), SN_LE16(17), SN_LE32(0), 7, "stopOsc" },
    { SN_LE32(28), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(28), SN_LE16(0), 8, ".122fake", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(28), SN_LE16(0), 8, ".122fake", 12, "ALSeqpConfig" },
    { SN_LE32(0), 0x94, SN_LE16(13), SN_LE16(149), SN_LE32(0), 9, "ALOscInit" },
    { SN_LE32(0), 0x94, SN_LE16(13), SN_LE16(149), SN_LE32(0), 11, "ALOscUpdate" },
    { SN_LE32(0), 0x94, SN_LE16(13), SN_LE16(145), SN_LE32(0), 9, "ALOscStop" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(136), 8, ".123fake" },
    { SN_LE32(0), 0x96, SN_LE16(8), SN_LE16(8), SN_LE32(20), SN_LE16(0), 10, "ALPlayer_s", 4, "node" },
    { SN_LE32(20), 0x96, SN_LE16(8), SN_LE16(24), SN_LE32(76), SN_LE16(0), 8, ".101fake", 4, "drvr" },
    { SN_LE32(24), 0x96, SN_LE16(8), SN_LE16(24), SN_LE32(28), SN_LE16(0), 7, "ALSeq_s", 6, "target" },
    { SN_LE32(28), 0x94, SN_LE16(8), SN_LE16(5), SN_LE32(0), 7, "curTime" },
    { SN_LE32(32), 0x96, SN_LE16(8), SN_LE16(24), SN_LE32(16), SN_LE16(0), 8, "ALBank_s", 4, "bank" },
    { SN_LE32(36), 0x94, SN_LE16(8), SN_LE16(5), SN_LE32(0), 4, "uspt" },
    { SN_LE32(40), 0x94, SN_LE16(8), SN_LE16(5), SN_LE32(0), 9, "nextDelta" },
    { SN_LE32(44), 0x94, SN_LE16(8), SN_LE16(5), SN_LE32(0), 5, "state" },
    { SN_LE32(48), 0x94, SN_LE16(8), SN_LE16(13), SN_LE32(0), 8, "chanMask" },
    { SN_LE32(50), 0x94, SN_LE16(8), SN_LE16(3), SN_LE32(0), 3, "vol" },
    { SN_LE32(52), 0x94, SN_LE16(8), SN_LE16(12), SN_LE32(0), 11, "maxChannels" },
    { SN_LE32(53), 0x94, SN_LE16(8), SN_LE16(12), SN_LE32(0), 10, "debugFlags" },
    { SN_LE32(56), 0x96, SN_LE16(8), SN_LE16(8), SN_LE32(16), SN_LE16(0), 8, ".116fake", 9, "nextEvent" },
    { SN_LE32(72), 0x96, SN_LE16(8), SN_LE16(8), SN_LE32(20), SN_LE16(0), 8, ".118fake", 4, "evtq" },
    { SN_LE32(92), 0x94, SN_LE16(8), SN_LE16(5), SN_LE32(0), 9, "frameTime" },
    { SN_LE32(96), 0x96, SN_LE16(8), SN_LE16(24), SN_LE32(16), SN_LE16(0), 8, ".119fake", 9, "chanState" },
    { SN_LE32(100), 0x96, SN_LE16(8), SN_LE16(24), SN_LE32(56), SN_LE16(0), 14, "ALVoiceState_s", 10, "vAllocHead" },
    { SN_LE32(104), 0x96, SN_LE16(8), SN_LE16(24), SN_LE32(56), SN_LE16(0), 14, "ALVoiceState_s", 10, "vAllocTail" },
    { SN_LE32(108), 0x96, SN_LE16(8), SN_LE16(24), SN_LE32(56), SN_LE16(0), 14, "ALVoiceState_s", 9, "vFreeList" },
    { SN_LE32(112), 0x94, SN_LE16(8), SN_LE16(149), SN_LE32(0), 7, "initOsc" },
    { SN_LE32(116), 0x94, SN_LE16(8), SN_LE16(149), SN_LE32(0), 9, "updateOsc" },
    { SN_LE32(120), 0x94, SN_LE16(8), SN_LE16(145), SN_LE32(0), 7, "stopOsc" },
    { SN_LE32(124), 0x96, SN_LE16(8), SN_LE16(24), SN_LE32(16), SN_LE16(0), 8, ".103fake", 9, "loopStart" },
    { SN_LE32(128), 0x96, SN_LE16(8), SN_LE16(24), SN_LE32(16), SN_LE16(0), 8, ".103fake", 7, "loopEnd" },
    { SN_LE32(132), 0x94, SN_LE16(8), SN_LE16(5), SN_LE32(0), 9, "loopCount" },
    { SN_LE32(136), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(136), SN_LE16(0), 8, ".123fake", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(136), SN_LE16(0), 8, ".123fake", 11, "ALSeqPlayer" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(124), 8, ".124fake" },
    { SN_LE32(0), 0x96, SN_LE16(8), SN_LE16(8), SN_LE32(20), SN_LE16(0), 10, "ALPlayer_s", 4, "node" },
    { SN_LE32(20), 0x96, SN_LE16(8), SN_LE16(24), SN_LE32(76), SN_LE16(0), 8, ".101fake", 4, "drvr" },
    { SN_LE32(24), 0x96, SN_LE16(8), SN_LE16(24), SN_LE32(248), SN_LE16(0), 8, "ALCSeq_s", 6, "target" },
    { SN_LE32(28), 0x94, SN_LE16(8), SN_LE16(5), SN_LE32(0), 7, "curTime" },
    { SN_LE32(32), 0x96, SN_LE16(8), SN_LE16(24), SN_LE32(16), SN_LE16(0), 8, "ALBank_s", 4, "bank" },
    { SN_LE32(36), 0x94, SN_LE16(8), SN_LE16(5), SN_LE32(0), 4, "uspt" },
    { SN_LE32(40), 0x94, SN_LE16(8), SN_LE16(5), SN_LE32(0), 9, "nextDelta" },
    { SN_LE32(44), 0x94, SN_LE16(8), SN_LE16(5), SN_LE32(0), 5, "state" },
    { SN_LE32(48), 0x94, SN_LE16(8), SN_LE16(13), SN_LE32(0), 8, "chanMask" },
    { SN_LE32(50), 0x94, SN_LE16(8), SN_LE16(3), SN_LE32(0), 3, "vol" },
    { SN_LE32(52), 0x94, SN_LE16(8), SN_LE16(12), SN_LE32(0), 11, "maxChannels" },
    { SN_LE32(53), 0x94, SN_LE16(8), SN_LE16(12), SN_LE32(0), 10, "debugFlags" },
    { SN_LE32(56), 0x96, SN_LE16(8), SN_LE16(8), SN_LE32(16), SN_LE16(0), 8, ".116fake", 9, "nextEvent" },
    { SN_LE32(72), 0x96, SN_LE16(8), SN_LE16(8), SN_LE32(20), SN_LE16(0), 8, ".118fake", 4, "evtq" },
    { SN_LE32(92), 0x94, SN_LE16(8), SN_LE16(5), SN_LE32(0), 9, "frameTime" },
    { SN_LE32(96), 0x96, SN_LE16(8), SN_LE16(24), SN_LE32(16), SN_LE16(0), 8, ".119fake", 9, "chanState" },
    { SN_LE32(100), 0x96, SN_LE16(8), SN_LE16(24), SN_LE32(56), SN_LE16(0), 14, "ALVoiceState_s", 10, "vAllocHead" },
    { SN_LE32(104), 0x96, SN_LE16(8), SN_LE16(24), SN_LE32(56), SN_LE16(0), 14, "ALVoiceState_s", 10, "vAllocTail" },
    { SN_LE32(108), 0x96, SN_LE16(8), SN_LE16(24), SN_LE32(56), SN_LE16(0), 14, "ALVoiceState_s", 9, "vFreeList" },
    { SN_LE32(112), 0x94, SN_LE16(8), SN_LE16(149), SN_LE32(0), 7, "initOsc" },
    { SN_LE32(116), 0x94, SN_LE16(8), SN_LE16(149), SN_LE32(0), 9, "updateOsc" },
    { SN_LE32(120), 0x94, SN_LE16(8), SN_LE16(145), SN_LE32(0), 7, "stopOsc" },
    { SN_LE32(124), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(124), SN_LE16(0), 8, ".124fake", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(124), SN_LE16(0), 8, ".124fake", 10, "ALCSPlayer" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(12), 8, ".125fake" },
    { SN_LE32(0), 0x94, SN_LE16(8), SN_LE16(5), SN_LE32(0), 9, "maxSounds" },
    { SN_LE32(4), 0x94, SN_LE16(8), SN_LE16(5), SN_LE32(0), 9, "maxEvents" },
    { SN_LE32(8), 0x96, SN_LE16(8), SN_LE16(24), SN_LE32(16), SN_LE16(0), 7, ".84fake", 4, "heap" },
    { SN_LE32(12), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(12), SN_LE16(0), 8, ".125fake", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(12), SN_LE16(0), 8, ".125fake", 12, "ALSndpConfig" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(84), 8, ".126fake" },
    { SN_LE32(0), 0x96, SN_LE16(8), SN_LE16(8), SN_LE32(20), SN_LE16(0), 10, "ALPlayer_s", 4, "node" },
    { SN_LE32(20), 0x96, SN_LE16(8), SN_LE16(8), SN_LE32(20), SN_LE16(0), 8, ".118fake", 4, "evtq" },
    { SN_LE32(40), 0x96, SN_LE16(8), SN_LE16(8), SN_LE32(16), SN_LE16(0), 8, ".116fake", 9, "nextEvent" },
    { SN_LE32(56), 0x96, SN_LE16(8), SN_LE16(24), SN_LE32(76), SN_LE16(0), 8, ".101fake", 4, "drvr" },
    { SN_LE32(60), 0x94, SN_LE16(8), SN_LE16(5), SN_LE32(0), 6, "target" },
    { SN_LE32(64), 0x94, SN_LE16(8), SN_LE16(17), SN_LE32(0), 8, "sndState" },
    { SN_LE32(68), 0x94, SN_LE16(8), SN_LE16(5), SN_LE32(0), 9, "maxSounds" },
    { SN_LE32(72), 0x94, SN_LE16(8), SN_LE16(5), SN_LE32(0), 9, "frameTime" },
    { SN_LE32(76), 0x94, SN_LE16(8), SN_LE16(5), SN_LE32(0), 9, "nextDelta" },
    { SN_LE32(80), 0x94, SN_LE16(8), SN_LE16(5), SN_LE32(0), 7, "curTime" },
    { SN_LE32(84), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(84), SN_LE16(0), 8, ".126fake", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(84), SN_LE16(0), 8, ".126fake", 11, "ALSndPlayer" },
    { SN_LE32(0), 0x94, SN_LE16(13), SN_LE16(3), SN_LE32(0), 7, "ALSndId" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(44), 8, ".127fake" },
    { SN_LE32(0), 0x94, SN_LE16(8), SN_LE16(28), SN_LE32(0), 4, "base" },
    { SN_LE32(4), 0x94, SN_LE16(8), SN_LE16(4), SN_LE32(0), 3, "fmt" },
    { SN_LE32(8), 0x94, SN_LE16(8), SN_LE16(4), SN_LE32(0), 3, "siz" },
    { SN_LE32(12), 0x94, SN_LE16(8), SN_LE16(4), SN_LE32(0), 5, "xsize" },
    { SN_LE32(16), 0x94, SN_LE16(8), SN_LE16(4), SN_LE32(0), 5, "ysize" },
    { SN_LE32(20), 0x94, SN_LE16(8), SN_LE16(4), SN_LE32(0), 5, "lsize" },
    { SN_LE32(24), 0x94, SN_LE16(8), SN_LE16(4), SN_LE32(0), 4, "addr" },
    { SN_LE32(28), 0x94, SN_LE16(8), SN_LE16(4), SN_LE32(0), 1, "w" },
    { SN_LE32(32), 0x94, SN_LE16(8), SN_LE16(4), SN_LE32(0), 1, "h" },
    { SN_LE32(36), 0x94, SN_LE16(8), SN_LE16(4), SN_LE32(0), 1, "s" },
    { SN_LE32(40), 0x94, SN_LE16(8), SN_LE16(4), SN_LE32(0), 1, "t" },
    { SN_LE32(44), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(44), SN_LE16(0), 8, ".127fake", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(44), SN_LE16(0), 8, ".127fake", 5, "Image" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(32), 8, ".128fake" },
    { SN_LE32(0), 0x96, SN_LE16(8), SN_LE16(54), SN_LE32(12), SN_LE16(1), SN_LE32(3), 0, 3, "col" },
    { SN_LE32(12), 0x96, SN_LE16(8), SN_LE16(54), SN_LE32(12), SN_LE16(1), SN_LE32(3), 0, 3, "pos" },
    { SN_LE32(24), 0x94, SN_LE16(8), SN_LE16(6), SN_LE32(0), 2, "a1" },
    { SN_LE32(28), 0x94, SN_LE16(8), SN_LE16(6), SN_LE32(0), 2, "a2" },
    { SN_LE32(32), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(32), SN_LE16(0), 8, ".128fake", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(32), SN_LE16(0), 8, ".128fake", 15, "PositionalLight" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(16), 8, ".129fake" },
    { SN_LE32(0), 0x94, SN_LE16(8), SN_LE16(4), SN_LE32(0), 8, "dataSize" },
    { SN_LE32(4), 0x94, SN_LE16(8), SN_LE16(4), SN_LE32(0), 6, "dlType" },
    { SN_LE32(8), 0x94, SN_LE16(8), SN_LE16(4), SN_LE32(0), 5, "flags" },
    { SN_LE32(12), 0x94, SN_LE16(8), SN_LE16(15), SN_LE32(0), 5, "paddr" },
    { SN_LE32(16), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(16), SN_LE16(0), 8, ".129fake", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(16), SN_LE16(0), 8, ".129fake", 11, "guDLPrintCB" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(24576), 8, ".130fake" },
    { SN_LE32(0), 0x94, SN_LE16(8), SN_LE16(5), SN_LE32(0), 4, "type" },
    { SN_LE32(4), 0x94, SN_LE16(8), SN_LE16(5), SN_LE32(0), 6, "length" },
    { SN_LE32(8), 0x94, SN_LE16(8), SN_LE16(5), SN_LE32(0), 5, "magic" },
    { SN_LE32(12), 0x96, SN_LE16(8), SN_LE16(50), SN_LE32(24564), SN_LE16(1), SN_LE32(24564), 0, 8, "userdata" },
    { SN_LE32(24576), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(24576), SN_LE16(0), 8, ".130fake", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(24576), SN_LE16(0), 8, ".130fake", 12, "RamRomBuffer" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(16), 6, "bitmap" },
    { SN_LE32(0), 0x94, SN_LE16(8), SN_LE16(3), SN_LE32(0), 5, "width" },
    { SN_LE32(2), 0x94, SN_LE16(8), SN_LE16(3), SN_LE32(0), 9, "width_img" },
    { SN_LE32(4), 0x94, SN_LE16(8), SN_LE16(3), SN_LE32(0), 1, "s" },
    { SN_LE32(6), 0x94, SN_LE16(8), SN_LE16(3), SN_LE32(0), 1, "t" },
    { SN_LE32(8), 0x94, SN_LE16(8), SN_LE16(17), SN_LE32(0), 3, "buf" },
    { SN_LE32(12), 0x94, SN_LE16(8), SN_LE16(3), SN_LE32(0), 12, "actualHeight" },
    { SN_LE32(14), 0x94, SN_LE16(8), SN_LE16(3), SN_LE32(0), 9, "LUToffset" },
    { SN_LE32(16), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(16), SN_LE16(0), 6, "bitmap", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(16), SN_LE16(0), 6, "bitmap", 6, "Bitmap" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(68), 6, "sprite" },
    { SN_LE32(0), 0x94, SN_LE16(8), SN_LE16(3), SN_LE32(0), 1, "x" },
    { SN_LE32(2), 0x94, SN_LE16(8), SN_LE16(3), SN_LE32(0), 1, "y" },
    { SN_LE32(4), 0x94, SN_LE16(8), SN_LE16(3), SN_LE32(0), 5, "width" },
    { SN_LE32(6), 0x94, SN_LE16(8), SN_LE16(3), SN_LE32(0), 6, "height" },
    { SN_LE32(8), 0x94, SN_LE16(8), SN_LE16(6), SN_LE32(0), 6, "scalex" },
    { SN_LE32(12), 0x94, SN_LE16(8), SN_LE16(6), SN_LE32(0), 6, "scaley" },
    { SN_LE32(16), 0x94, SN_LE16(8), SN_LE16(3), SN_LE32(0), 4, "expx" },
    { SN_LE32(18), 0x94, SN_LE16(8), SN_LE16(3), SN_LE32(0), 4, "expy" },
    { SN_LE32(20), 0x94, SN_LE16(8), SN_LE16(13), SN_LE32(0), 4, "attr" },
    { SN_LE32(22), 0x94, SN_LE16(8), SN_LE16(3), SN_LE32(0), 6, "zdepth" },
    { SN_LE32(24), 0x94, SN_LE16(8), SN_LE16(12), SN_LE32(0), 3, "red" },
    { SN_LE32(25), 0x94, SN_LE16(8), SN_LE16(12), SN_LE32(0), 5, "green" },
    { SN_LE32(26), 0x94, SN_LE16(8), SN_LE16(12), SN_LE32(0), 4, "blue" },
    { SN_LE32(27), 0x94, SN_LE16(8), SN_LE16(12), SN_LE32(0), 5, "alpha" },
    { SN_LE32(28), 0x94, SN_LE16(8), SN_LE16(3), SN_LE32(0), 9, "startTLUT" },
    { SN_LE32(30), 0x94, SN_LE16(8), SN_LE16(3), SN_LE32(0), 5, "nTLUT" },
    { SN_LE32(32), 0x94, SN_LE16(8), SN_LE16(20), SN_LE32(0), 3, "LUT" },
    { SN_LE32(36), 0x94, SN_LE16(8), SN_LE16(3), SN_LE32(0), 6, "istart" },
    { SN_LE32(38), 0x94, SN_LE16(8), SN_LE16(3), SN_LE32(0), 5, "istep" },
    { SN_LE32(40), 0x94, SN_LE16(8), SN_LE16(3), SN_LE32(0), 8, "nbitmaps" },
    { SN_LE32(42), 0x94, SN_LE16(8), SN_LE16(3), SN_LE32(0), 9, "ndisplist" },
    { SN_LE32(44), 0x94, SN_LE16(8), SN_LE16(3), SN_LE32(0), 8, "bmheight" },
    { SN_LE32(46), 0x94, SN_LE16(8), SN_LE16(3), SN_LE32(0), 7, "bmHreal" },
    { SN_LE32(48), 0x94, SN_LE16(8), SN_LE16(12), SN_LE32(0), 5, "bmfmt" },
    { SN_LE32(49), 0x94, SN_LE16(8), SN_LE16(12), SN_LE32(0), 5, "bmsiz" },
    { SN_LE32(52), 0x96, SN_LE16(8), SN_LE16(24), SN_LE32(16), SN_LE16(0), 6, "bitmap", 6, "bitmap" },
    { SN_LE32(56), 0x96, SN_LE16(8), SN_LE16(25), SN_LE32(8), SN_LE16(0), 7, ".63fake", 6, "rsp_dl" },
    { SN_LE32(60), 0x96, SN_LE16(8), SN_LE16(25), SN_LE32(8), SN_LE16(0), 7, ".63fake", 11, "rsp_dl_next" },
    { SN_LE32(64), 0x94, SN_LE16(8), SN_LE16(3), SN_LE32(0), 6, "frac_s" },
    { SN_LE32(66), 0x94, SN_LE16(8), SN_LE16(3), SN_LE32(0), 6, "frac_t" },
    { SN_LE32(68), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(68), SN_LE16(0), 6, "sprite", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(68), SN_LE16(0), 6, "sprite", 6, "Sprite" },
    { 0x00, 0x00, 0x00, 0x00, 0x94, 0x0D, 0x00, 0x91, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0E, 0x4F, 0x53, 0x45, 0x72, 0x72, 0x6F, 0x72, 0x48, 0x61, 0x6E },
};
typedef char g_DebugStreamHalfwords1SizeCheck[(sizeof(g_DebugStreamHalfwords1) == 63470) ? 1 : -1];
#endif
