#include "DATA_OVERLAY_SN_RECORDS.H"


#if defined(VERSION_US_REV1)
struct {
    struct { u8 valueTail[3]; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[12]; } CDefragger_t_0;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[10]; u8 nameLength; char name[6]; } Thread_1;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; SnLe32 dimension0; u8 tagNameLength; u8 nameLength; char name[5]; } Stack_2;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[12]; u8 nameLength; char name[4]; } eos_3;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[12]; u8 nameLength; char name[10]; } CDefragger_4;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[14]; } CTextureInfo_t_5;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[10]; } m_nBitmaps_6;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[11]; } m_nPalettes_7;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[19]; u8 nameLength; char name[9]; } m_pFormat_8;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[14]; u8 nameLength; char name[4]; } eos_9;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[14]; u8 nameLength; char name[12]; } CTextureInfo_10;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[16]; } CTextureLoader_t_11;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[12]; } rpTextureSet_12;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[14]; } TextureSetSize_13;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[16]; u8 nameLength; char name[4]; } eos_14;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[16]; u8 nameLength; char name[14]; } CTextureLoader_15;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[33]; } PARTICLE_IMPACTS_GRASS_OR_WOODequ_16;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[30]; } PARTICLE_IMPACTS_GRASS_OR_WOOD_17;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[33]; u8 nameLength; char name[4]; } eos_18;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[32]; } PARTICLE_IMPACTS_WATERSURFACEequ_19;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[29]; } PARTICLE_IMPACTS_WATERSURFACE_20;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[32]; u8 nameLength; char name[4]; } eos_21;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[25]; } PARTICLE_IMPACTS_STEELequ_22;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[22]; } PARTICLE_IMPACTS_STEEL_23;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[25]; u8 nameLength; char name[4]; } eos_24;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[25]; } PARTICLE_IMPACTS_STONEequ_25;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[22]; } PARTICLE_IMPACTS_STONE_26;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[25]; u8 nameLength; char name[4]; } eos_27;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[25]; } PARTICLE_IMPACTS_FLESHequ_28;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[22]; } PARTICLE_IMPACTS_FLESH_29;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[25]; u8 nameLength; char name[4]; } eos_30;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[30]; } PARTICLE_IMPACTS_ALIENFLESHequ_31;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[27]; } PARTICLE_IMPACTS_ALIENFLESH_32;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[30]; u8 nameLength; char name[4]; } eos_33;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[30]; } PARTICLE_IMPACTS_FLESHWATERequ_34;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[27]; } PARTICLE_IMPACTS_FLESHWATER_35;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[30]; u8 nameLength; char name[4]; } eos_36;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[24]; } PARTICLE_IMPACTS_LAVAequ_37;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[21]; } PARTICLE_IMPACTS_LAVA_38;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[24]; u8 nameLength; char name[4]; } eos_39;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[25]; } PARTICLE_IMPACTS_SWAMPequ_40;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[22]; } PARTICLE_IMPACTS_SWAMP_41;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[25]; u8 nameLength; char name[4]; } eos_42;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[30]; } PARTICLE_IMPACTS_FORCEFIELDequ_43;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[27]; } PARTICLE_IMPACTS_FORCEFIELD_44;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[30]; u8 nameLength; char name[4]; } eos_45;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[27]; } PARTICLE_IMPACTS_ENDLIFEequ_46;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[24]; } PARTICLE_IMPACTS_ENDLIFE_47;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[27]; u8 nameLength; char name[4]; } eos_48;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[30]; } PARTICLE_IMPACTS_EVERYFRAMEequ_49;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[27]; } PARTICLE_IMPACTS_EVERYFRAME_50;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[30]; u8 nameLength; char name[4]; } eos_51;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[32]; } PARTICLE_IMPACTS_ENDLIFEWATERequ_52;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[29]; } PARTICLE_IMPACTS_ENDLIFEWATER_53;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[32]; u8 nameLength; char name[4]; } eos_54;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[35]; } PARTICLE_IMPACTS_EVERYFRAMEWATERequ_55;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[32]; } PARTICLE_IMPACTS_EVERYFRAMEWATER_56;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[35]; u8 nameLength; char name[4]; } eos_57;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[23]; } PARTICLE_IMPACTS_AMTequ_58;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[20]; } PARTICLE_IMPACTS_AMT_59;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[23]; u8 nameLength; char name[4]; } eos_60;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[2]; } SF_61;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[13]; } CROMSection_t_62;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[13]; } m_nTextureSet_63;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[12]; } m_dwMatFlags_64;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[11]; } m_nMaterial_65;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[10]; } m_NodeType_66;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; SnLe32 dimension0; u8 tagNameLength; u8 nameLength; char name[3]; } pad_67;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; SnLe32 dimension0; u8 tagNameLength; u8 nameLength; char name[7]; } m_Color_68;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; SnLe32 dimension0; u8 tagNameLength; u8 nameLength; char name[12]; } m_BlackColor_69;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[7]; } m_MultU_70;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[7]; } m_MultV_71;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[13]; u8 nameLength; char name[4]; } eos_72;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[13]; u8 nameLength; char name[11]; } CROMSection_73;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[14]; } CGameSection_t_74;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[12]; } m_dwMatFlags_75;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[11]; } m_nMaterial_76;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[10]; } m_NodeType_77;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[18]; } m_LastTextureFrame_78;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[16]; u8 nameLength; char name[15]; } m_TextureLoader_79;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; SnLe32 dimension0; u8 tagNameLength; u8 nameLength; char name[7]; } m_Color_80;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; SnLe32 dimension0; u8 tagNameLength; u8 nameLength; char name[12]; } m_BlackColor_81;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[7]; } m_MultU_82;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[7]; } m_MultV_83;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[14]; u8 nameLength; char name[4]; } eos_84;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[14]; u8 nameLength; char name[12]; } CGameSection_85;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[19]; } CROMTextureFormat_t_86;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[8]; } m_Format_87;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[15]; } m_PlaybackSpeed_88;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[12]; } m_WidthShift_89;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[13]; } m_HeightShift_90;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[8]; } m_Effect_91;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[12]; } m_EffectMode_92;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[19]; u8 nameLength; char name[4]; } eos_93;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[19]; u8 nameLength; char name[17]; } CROMTextureFormat_94;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[11]; } CROMLevel_t_95;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[14]; } m_GridDistance_96;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; SnLe32 dimension0; u8 tagNameLength; u8 nameLength; char name[12]; } m_BlackColor_97;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; SnLe32 dimension0; u8 tagNameLength; u8 nameLength; char name[12]; } m_WhiteColor_98;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; SnLe32 dimension0; u8 tagNameLength; u8 nameLength; char name[18]; } m_DirectionalLight_99;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; SnLe32 dimension0; u8 tagNameLength; u8 nameLength; char name[14]; } m_AmbientLight_100;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[8]; } m_bFlags_101;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; SnLe32 dimension0; u8 tagNameLength; u8 nameLength; char name[11]; } m_Direction_102;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[11]; u8 nameLength; char name[4]; } eos_103;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[11]; u8 nameLength; char name[9]; } CROMLevel_104;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[15]; } CRandomSFPair_t_105;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[1]; } v_106;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[1]; } r_107;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[15]; u8 nameLength; char name[4]; } eos_108;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[15]; u8 nameLength; char name[13]; } CRandomSFPair_109;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[15]; } CRandomS8Pair_t_110;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[1]; } v_111;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[1]; } r_112;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[15]; u8 nameLength; char name[4]; } eos_113;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[15]; u8 nameLength; char name[13]; } CRandomS8Pair_114;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[20]; } CROMParticleImpact_t_115;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; SnLe32 dimension0; u8 tagNameLength; char tagName[13]; u8 nameLength; char name[18]; } m_ImpactEventValue_116;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; SnLe32 dimension0; u8 tagNameLength; u8 nameLength; char name[20]; } m_ImpactParticleType_117;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; SnLe32 dimension0; u8 tagNameLength; u8 nameLength; char name[17]; } m_ImpactEventType_118;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; SnLe32 dimension0; u8 tagNameLength; u8 nameLength; char name[17]; } m_ImpactSoundType_119;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[20]; u8 nameLength; char name[4]; } eos_120;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[20]; u8 nameLength; char name[18]; } CROMParticleImpact_121;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[20]; } CROMParticleOffset_t_122;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[15]; u8 nameLength; char name[12]; } m_XPosOffset_123;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[15]; u8 nameLength; char name[12]; } m_YPosOffset_124;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[15]; u8 nameLength; char name[12]; } m_ZPosOffset_125;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[20]; u8 nameLength; char name[4]; } eos_126;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[20]; u8 nameLength; char name[18]; } CROMParticleOffset_127;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[17]; } CROMParticleRot_t_128;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[15]; u8 nameLength; char name[6]; } m_XRot_129;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[15]; u8 nameLength; char name[9]; } m_XRotInc_130;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[15]; u8 nameLength; char name[6]; } m_YRot_131;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[15]; u8 nameLength; char name[9]; } m_YRotInc_132;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[15]; u8 nameLength; char name[6]; } m_ZRot_133;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[15]; u8 nameLength; char name[9]; } m_ZRotInc_134;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[17]; u8 nameLength; char name[4]; } eos_135;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[17]; u8 nameLength; char name[15]; } CROMParticleRot_136;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[19]; } CROMParticleScale_t_137;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[15]; u8 nameLength; char name[8]; } m_XScale_138;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[15]; u8 nameLength; char name[11]; } m_XScaleInc_139;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[15]; u8 nameLength; char name[8]; } m_YScale_140;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[15]; u8 nameLength; char name[11]; } m_YScaleInc_141;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[15]; u8 nameLength; char name[8]; } m_ZScale_142;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[15]; u8 nameLength; char name[11]; } m_ZScaleInc_143;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[13]; } m_ShadowScale_144;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[11]; } m_NearScale_145;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[10]; } m_FarScale_146;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[19]; u8 nameLength; char name[4]; } eos_147;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[19]; u8 nameLength; char name[17]; } CROMParticleScale_148;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[17]; } CROMParticleDir_t_149;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[15]; u8 nameLength; char name[12]; } m_XDirection_150;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[15]; u8 nameLength; char name[12]; } m_YDirection_151;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[15]; u8 nameLength; char name[12]; } m_ZDirection_152;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[17]; u8 nameLength; char name[4]; } eos_153;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[17]; u8 nameLength; char name[15]; } CROMParticleDir_154;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[22]; } CROMParticleSineWave_t_155;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[15]; u8 nameLength; char name[12]; } m_XAmplitude_156;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[15]; u8 nameLength; char name[12]; } m_XFrequency_157;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[15]; u8 nameLength; char name[8]; } m_XPhase_158;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[15]; u8 nameLength; char name[12]; } m_YAmplitude_159;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[15]; u8 nameLength; char name[12]; } m_YFrequency_160;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[15]; u8 nameLength; char name[8]; } m_YPhase_161;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[17]; } m_nSineWaveFadeIn_162;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[22]; u8 nameLength; char name[4]; } eos_163;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[22]; u8 nameLength; char name[20]; } CROMParticleSineWave_164;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[21]; } CROMParticlePhysics_t_165;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[15]; u8 nameLength; char name[9]; } m_Gravity_166;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[15]; u8 nameLength; char name[10]; } m_Velocity_167;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[14]; } m_BounceEnergy_168;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[16]; } m_GroundFriction_169;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[13]; } m_AirFriction_170;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[15]; } m_WaterFriction_171;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[14]; } m_Acceleration_172;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[16]; } m_MinMaxVelocity_173;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[12]; } m_CollRadius_174;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[21]; u8 nameLength; char name[4]; } eos_175;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[21]; u8 nameLength; char name[19]; } CROMParticlePhysics_176;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[19]; } CROMParticleColor_t_177;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; SnLe32 dimension0; u8 tagNameLength; u8 nameLength; char name[12]; } m_WhiteColor_178;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; SnLe32 dimension0; u8 tagNameLength; u8 nameLength; char name[12]; } m_BlackColor_179;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; SnLe32 dimension0; u8 tagNameLength; u8 nameLength; char name[13]; } m_WhiteColor2_180;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; SnLe32 dimension0; u8 tagNameLength; u8 nameLength; char name[13]; } m_BlackColor2_181;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[14]; } m_RandomizeHue_182;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[21]; } m_RandomizeSaturation_183;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[21]; } m_RandomizeBrightness_184;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[19]; u8 nameLength; char name[4]; } eos_185;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[19]; u8 nameLength; char name[17]; } CROMParticleColor_186;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[21]; } CROMParticleGeneral_t_187;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[9]; } m_nFrames_188;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[12]; } m_nFramesRnd_189;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[13]; } m_Probability_190;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[12]; } m_Visibility_191;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[12]; } m_nParticles_192;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[15]; } m_nParticlesRnd_193;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[11]; } m_nPriority_194;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[9]; } m_nFadeIn_195;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[10]; } m_nFadeOut_196;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[5]; } m_FPS_197;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[13]; } m_nInBetweens_198;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[11]; } m_nMaxDelay_199;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[11]; } m_Alignment_200;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[7]; } m_Alert_201;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[21]; u8 nameLength; char name[4]; } eos_202;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[21]; u8 nameLength; char name[19]; } CROMParticleGeneral_203;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[20]; } CROMParticleEffect_t_204;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[9]; } m_dwFlags_205;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[13]; } m_nTextureSet_206;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[9]; } m_nSwoosh_207;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[15]; } m_nDynamicLight_208;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[10]; } m_Playback_209;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[18]; } m_InstanceBehavior_210;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[14]; } m_WallBehavior_211;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[16]; } m_GroundBehavior_212;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[11]; } m_SoundType_213;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[24]; } m_MaxAngleChangePerFrame_214;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[26]; } m_ProximityDetectionRadius_215;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[9]; } m_bFlags2_216;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; SnLe32 dimension0; u8 tagNameLength; u8 nameLength; char name[7]; } padding_217;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[10]; } m_rpObject_218;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[20]; u8 nameLength; char name[9]; } m_pImpact_219;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[20]; u8 nameLength; char name[9]; } m_pOffset_220;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[17]; u8 nameLength; char name[6]; } m_pRot_221;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[19]; u8 nameLength; char name[8]; } m_pScale_222;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[17]; u8 nameLength; char name[6]; } m_pDir_223;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[22]; u8 nameLength; char name[11]; } m_pSineWave_224;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[21]; u8 nameLength; char name[10]; } m_pPhysics_225;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[19]; u8 nameLength; char name[8]; } m_pColor_226;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[21]; u8 nameLength; char name[10]; } m_pGeneral_227;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[20]; u8 nameLength; char name[4]; } eos_228;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[20]; u8 nameLength; char name[18]; } CROMParticleEffect_229;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[15]; } CROMWarpPoint_t_230;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[10]; u8 nameLength; char name[6]; } m_vPos_231;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[6]; } m_RotY_232;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[8]; } m_nLevel_233;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[9]; } m_nRegion_234;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[15]; u8 nameLength; char name[4]; } eos_235;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[15]; u8 nameLength; char name[13]; } CROMWarpPoint_236;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[10]; } CROMNode_t_237;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; SnLe32 dimension0; u8 tagNameLength; char tagName[10]; u8 nameLength; char name[14]; } vBoundsCorners_238;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[11]; } m_MaxBounds_239;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[13]; } m_ParentIndex_240;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[8]; } m_Symbol_241;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[14]; } m_MaterialType_242;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; SnLe32 dimension0; u8 tagNameLength; u8 nameLength; char name[3]; } pad_243;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[14]; } m_DamageScaler_244;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[14]; } m_dwModelFlags_245;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[10]; u8 nameLength; char name[4]; } eos_246;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[10]; u8 nameLength; char name[8]; } CROMNode_247;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[16]; } CROMObjectInfo_t_248;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[12]; u8 nameLength; char name[8]; } m_Bounds_249;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[20]; } m_HeadTrackStartNode_250;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[18]; } m_HeadTrackEndNode_251;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[17]; } m_HeadTrackFactor_252;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[4]; } pad0_253;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[12]; } m_nVariation_254;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[11]; } m_UnitScale_255;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[16]; u8 nameLength; char name[4]; } eos_256;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[16]; u8 nameLength; char name[14]; } CROMObjectInfo_257;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[7]; } CNode_t_258;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[7]; } m_pPrev_259;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[7]; } m_pNext_260;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[4]; } eos_261;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[5]; } CNode_262;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[11]; } CNodeList_t_263;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[7]; } m_pHead_264;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[7]; } m_pTail_265;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[8]; } m_Length_266;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[11]; u8 nameLength; char name[4]; } eos_267;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[11]; u8 nameLength; char name[9]; } CNodeList_268;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[14]; } CDynamicList_t_269;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[11]; u8 nameLength; char name[10]; } m_FreeList_270;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[11]; u8 nameLength; char name[12]; } m_ActiveList_271;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[14]; u8 nameLength; char name[4]; } eos_272;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[14]; u8 nameLength; char name[12]; } CDynamicList_273;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[12]; } CSelection_t_274;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[8]; } m_Number_275;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[8]; } m_Weight_276;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[12]; u8 nameLength; char name[4]; } eos_277;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[12]; u8 nameLength; char name[10]; } CSelection_278;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[16]; } CSelectionList_t_279;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[9]; } m_Entries_280;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; SnLe32 dimension0; u8 tagNameLength; char tagName[12]; u8 nameLength; char name[6]; } m_List_281;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[16]; u8 nameLength; char name[4]; } eos_282;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[16]; u8 nameLength; char name[14]; } CSelectionList_283;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[19]; } CGameAnimateState_t_284;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[6]; } cFrame_285;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[5]; } nAnim_286;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[12]; } nDesiredAnim_287;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[7]; } nFrames_288;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[14]; } CycleCompleted_289;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[6]; } Active_290;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[6]; } LoopTo_291;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[11]; u8 nameLength; char name[11]; } pmeAnimData_292;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[19]; u8 nameLength; char name[4]; } eos_293;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[19]; u8 nameLength; char name[17]; } CGameAnimateState_294;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[19]; u8 nameLength; char name[4]; } CGAS_295;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[24]; u8 nameLength; char name[9]; } CRIOrient_296;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[15]; u8 nameLength; char name[8]; } CRNIndex_297;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[10]; } AnimInfo_t_298;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[15]; u8 nameLength; char name[15]; } NodeAnimIndices_299;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[24]; u8 nameLength; char name[14]; } InitialOrients_300;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[6]; u8 nameLength; char name[11]; } isTransSets_301;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[6]; u8 nameLength; char name[9]; } isRotSets_302;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[9]; } RotIndex1_303;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[9]; } RotIndex2_304;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[11]; } TransIndex1_305;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[11]; } TransIndex2_306;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[5]; } Blend_307;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[10]; u8 nameLength; char name[4]; } eos_308;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[10]; u8 nameLength; char name[8]; } AnimInfo_309;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[24]; } CGameObjectInstanceModes_310;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[9]; } IDLE_MODE_311;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[19]; } TRANS_FADE_OUT_MODE_312;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[12]; } END_OF_MODES_313;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[24]; u8 nameLength; char name[4]; } eos_314;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[10]; } ModelTypes_315;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[17]; } NORMAL_MODEL_TYPE_316;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[19]; } EXTREME1_MODEL_TYPE_317;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[19]; } EXTREME2_MODEL_TYPE_318;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[19]; } EXTREME3_MODEL_TYPE_319;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[19]; } EXTREME4_MODEL_TYPE_320;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[19]; } EXTREME5_MODEL_TYPE_321;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[19]; } EXTREME6_MODEL_TYPE_322;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[19]; } EXTREME7_MODEL_TYPE_323;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[19]; } EXTREME8_MODEL_TYPE_324;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[11]; } MODEL_TYPES_325;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[10]; u8 nameLength; char name[4]; } eos_326;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[20]; } CROMObjectInstance_t_327;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[10]; u8 nameLength; char name[9]; } m_VisBits_328;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[10]; u8 nameLength; char name[6]; } m_vPos_329;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[10]; u8 nameLength; char name[8]; } m_vScale_330;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[10]; } m_nObjType_331;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[11]; } m_nTypeFlag_332;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[16]; } m_nCurrentRegion_333;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[12]; } m_nVariation_334;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[6]; } m_RotY_335;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[8]; } m_bFlags_336;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[7]; } m_nPath_337;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[20]; u8 nameLength; char name[4]; } eos_338;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[20]; u8 nameLength; char name[18]; } CROMObjectInstance_339;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[21]; } CGameObjectInstance_t_340;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[18]; u8 nameLength; char name[2]; } ah_341;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[10]; u8 nameLength; char name[8]; } m_vScale_342;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[10]; u8 nameLength; char name[9]; } m_qGround_343;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[6]; } m_RotY_344;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[18]; } m_CollisionYOffset_345;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; SnLe32 dimension0; SnLe32 dimension1; u8 tagNameLength; u8 nameLength; char name[10]; } m_mfOrient_346;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[13]; } m_pmtDrawMtxs_347;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[22]; } m_pmtLastFrameDrawMtxs_348;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; SnLe32 dimension0; SnLe32 dimension1; u8 tagNameLength; u8 nameLength; char name[11]; } m_pmfShadow_349;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[8]; } m_pDList_350;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[14]; } m_rpObjectInfo_351;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[9]; } m_rpAnims_352;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[15]; } m_rpModelsIndex_353;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[16]; } m_ObjectInfoSize_354;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[17]; } m_ModelsIndexSize_355;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[15]; } m_nCurrentModel_356;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[9]; } m_rpModel_357;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[11]; } m_ModelSize_358;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[11]; } m_nTypeFlag_359;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[8]; } m_nAnims_360;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[9]; } m_nModels_361;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[12]; u8 nameLength; char name[8]; } m_Bounds_362;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[9]; } m_dwFlags_363;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[19]; u8 nameLength; char name[11]; } m_asCurrent_364;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; u8 tagNameLength; char tagName[19]; u8 nameLength; char name[9]; } m_asBlend_365;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[13]; } m_BlendLength_366;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[10]; } m_uBlender_367;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[10]; } m_BlendPos_368;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[12]; } m_BlendStart_369;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[13]; } m_BlendFinish_370;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[13]; } m_ShadowAlpha_371;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; u8 nameLength; char name[16]; } m_ActiveSwooshes_372;
    struct { SnLe32 value; u8 kind; SnLe16 storageClass; SnLe16 type; SnLe32 size; SnLe16 dimensionCount; SnLe32 dimension0; u8 tagNameLength; char tagName[7]; u8 nameLength; char name[8]; } m_Lights_373;
    u8 incompleteRecord[22];
} g_sn64RuntimeTypeRecords __attribute__((aligned(4))) = {
    { { 0, 0, 0 }, 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(1584), 12, "CDefragger_t" },
    { SN_LE32(0), 0x96, SN_LE16(8), SN_LE16(8), SN_LE32(560), SN_LE16(0), 10, "OSThread_s", 6, "Thread" },
    { SN_LE32(560), 0x96, SN_LE16(8), SN_LE16(63), SN_LE32(1024), SN_LE16(1), SN_LE32(128), 0, 5, "Stack" },
    { SN_LE32(1584), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(1584), SN_LE16(0), 12, "CDefragger_t", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(1584), SN_LE16(0), 12, "CDefragger_t", 10, "CDefragger" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(12), 14, "CTextureInfo_t" },
    { SN_LE32(0), 0x94, SN_LE16(8), SN_LE16(4), SN_LE32(0), 10, "m_nBitmaps" },
    { SN_LE32(4), 0x94, SN_LE16(8), SN_LE16(4), SN_LE32(0), 11, "m_nPalettes" },
    { SN_LE32(8), 0x96, SN_LE16(8), SN_LE16(24), SN_LE32(0), SN_LE16(0), 19, "CROMTextureFormat_t", 9, "m_pFormat" },
    { SN_LE32(12), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(12), SN_LE16(0), 14, "CTextureInfo_t", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(12), SN_LE16(0), 14, "CTextureInfo_t", 12, "CTextureInfo" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(8), 16, "CTextureLoader_t" },
    { SN_LE32(0), 0x94, SN_LE16(8), SN_LE16(17), SN_LE32(0), 12, "rpTextureSet" },
    { SN_LE32(4), 0x94, SN_LE16(8), SN_LE16(15), SN_LE32(0), 14, "TextureSetSize" },
    { SN_LE32(8), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(8), SN_LE16(0), 16, "CTextureLoader_t", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(8), SN_LE16(0), 16, "CTextureLoader_t", 14, "CTextureLoader" },
    { SN_LE32(0), 0x94, SN_LE16(15), SN_LE16(10), SN_LE32(4), 33, "PARTICLE_IMPACTS_GRASS_OR_WOODequ" },
    { SN_LE32(0), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 30, "PARTICLE_IMPACTS_GRASS_OR_WOOD" },
    { SN_LE32(4), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(4), SN_LE16(0), 33, "PARTICLE_IMPACTS_GRASS_OR_WOODequ", 4, ".eos" },
    { SN_LE32(0), 0x94, SN_LE16(15), SN_LE16(10), SN_LE32(4), 32, "PARTICLE_IMPACTS_WATERSURFACEequ" },
    { SN_LE32(1), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 29, "PARTICLE_IMPACTS_WATERSURFACE" },
    { SN_LE32(4), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(4), SN_LE16(0), 32, "PARTICLE_IMPACTS_WATERSURFACEequ", 4, ".eos" },
    { SN_LE32(0), 0x94, SN_LE16(15), SN_LE16(10), SN_LE32(4), 25, "PARTICLE_IMPACTS_STEELequ" },
    { SN_LE32(2), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 22, "PARTICLE_IMPACTS_STEEL" },
    { SN_LE32(4), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(4), SN_LE16(0), 25, "PARTICLE_IMPACTS_STEELequ", 4, ".eos" },
    { SN_LE32(0), 0x94, SN_LE16(15), SN_LE16(10), SN_LE32(4), 25, "PARTICLE_IMPACTS_STONEequ" },
    { SN_LE32(3), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 22, "PARTICLE_IMPACTS_STONE" },
    { SN_LE32(4), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(4), SN_LE16(0), 25, "PARTICLE_IMPACTS_STONEequ", 4, ".eos" },
    { SN_LE32(0), 0x94, SN_LE16(15), SN_LE16(10), SN_LE32(4), 25, "PARTICLE_IMPACTS_FLESHequ" },
    { SN_LE32(4), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 22, "PARTICLE_IMPACTS_FLESH" },
    { SN_LE32(4), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(4), SN_LE16(0), 25, "PARTICLE_IMPACTS_FLESHequ", 4, ".eos" },
    { SN_LE32(0), 0x94, SN_LE16(15), SN_LE16(10), SN_LE32(4), 30, "PARTICLE_IMPACTS_ALIENFLESHequ" },
    { SN_LE32(5), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 27, "PARTICLE_IMPACTS_ALIENFLESH" },
    { SN_LE32(4), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(4), SN_LE16(0), 30, "PARTICLE_IMPACTS_ALIENFLESHequ", 4, ".eos" },
    { SN_LE32(0), 0x94, SN_LE16(15), SN_LE16(10), SN_LE32(4), 30, "PARTICLE_IMPACTS_FLESHWATERequ" },
    { SN_LE32(6), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 27, "PARTICLE_IMPACTS_FLESHWATER" },
    { SN_LE32(4), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(4), SN_LE16(0), 30, "PARTICLE_IMPACTS_FLESHWATERequ", 4, ".eos" },
    { SN_LE32(0), 0x94, SN_LE16(15), SN_LE16(10), SN_LE32(4), 24, "PARTICLE_IMPACTS_LAVAequ" },
    { SN_LE32(7), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 21, "PARTICLE_IMPACTS_LAVA" },
    { SN_LE32(4), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(4), SN_LE16(0), 24, "PARTICLE_IMPACTS_LAVAequ", 4, ".eos" },
    { SN_LE32(0), 0x94, SN_LE16(15), SN_LE16(10), SN_LE32(4), 25, "PARTICLE_IMPACTS_SWAMPequ" },
    { SN_LE32(8), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 22, "PARTICLE_IMPACTS_SWAMP" },
    { SN_LE32(4), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(4), SN_LE16(0), 25, "PARTICLE_IMPACTS_SWAMPequ", 4, ".eos" },
    { SN_LE32(0), 0x94, SN_LE16(15), SN_LE16(10), SN_LE32(4), 30, "PARTICLE_IMPACTS_FORCEFIELDequ" },
    { SN_LE32(9), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 27, "PARTICLE_IMPACTS_FORCEFIELD" },
    { SN_LE32(4), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(4), SN_LE16(0), 30, "PARTICLE_IMPACTS_FORCEFIELDequ", 4, ".eos" },
    { SN_LE32(0), 0x94, SN_LE16(15), SN_LE16(10), SN_LE32(4), 27, "PARTICLE_IMPACTS_ENDLIFEequ" },
    { SN_LE32(10), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 24, "PARTICLE_IMPACTS_ENDLIFE" },
    { SN_LE32(4), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(4), SN_LE16(0), 27, "PARTICLE_IMPACTS_ENDLIFEequ", 4, ".eos" },
    { SN_LE32(0), 0x94, SN_LE16(15), SN_LE16(10), SN_LE32(4), 30, "PARTICLE_IMPACTS_EVERYFRAMEequ" },
    { SN_LE32(11), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 27, "PARTICLE_IMPACTS_EVERYFRAME" },
    { SN_LE32(4), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(4), SN_LE16(0), 30, "PARTICLE_IMPACTS_EVERYFRAMEequ", 4, ".eos" },
    { SN_LE32(0), 0x94, SN_LE16(15), SN_LE16(10), SN_LE32(4), 32, "PARTICLE_IMPACTS_ENDLIFEWATERequ" },
    { SN_LE32(12), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 29, "PARTICLE_IMPACTS_ENDLIFEWATER" },
    { SN_LE32(4), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(4), SN_LE16(0), 32, "PARTICLE_IMPACTS_ENDLIFEWATERequ", 4, ".eos" },
    { SN_LE32(0), 0x94, SN_LE16(15), SN_LE16(10), SN_LE32(4), 35, "PARTICLE_IMPACTS_EVERYFRAMEWATERequ" },
    { SN_LE32(13), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 32, "PARTICLE_IMPACTS_EVERYFRAMEWATER" },
    { SN_LE32(4), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(4), SN_LE16(0), 35, "PARTICLE_IMPACTS_EVERYFRAMEWATERequ", 4, ".eos" },
    { SN_LE32(0), 0x94, SN_LE16(15), SN_LE16(10), SN_LE32(4), 23, "PARTICLE_IMPACTS_AMTequ" },
    { SN_LE32(14), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 20, "PARTICLE_IMPACTS_AMT" },
    { SN_LE32(4), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(4), SN_LE16(0), 23, "PARTICLE_IMPACTS_AMTequ", 4, ".eos" },
    { SN_LE32(0), 0x94, SN_LE16(13), SN_LE16(13), SN_LE32(0), 2, "SF" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(24), 13, "CROMSection_t" },
    { SN_LE32(0), 0x94, SN_LE16(8), SN_LE16(15), SN_LE32(0), 13, "m_nTextureSet" },
    { SN_LE32(4), 0x94, SN_LE16(8), SN_LE16(15), SN_LE32(0), 12, "m_dwMatFlags" },
    { SN_LE32(8), 0x94, SN_LE16(8), SN_LE16(13), SN_LE32(0), 11, "m_nMaterial" },
    { SN_LE32(10), 0x94, SN_LE16(8), SN_LE16(12), SN_LE32(0), 10, "m_NodeType" },
    { SN_LE32(11), 0x96, SN_LE16(8), SN_LE16(60), SN_LE32(1), SN_LE16(1), SN_LE32(1), 0, 3, "pad" },
    { SN_LE32(12), 0x96, SN_LE16(8), SN_LE16(60), SN_LE32(4), SN_LE16(1), SN_LE32(4), 0, 7, "m_Color" },
    { SN_LE32(16), 0x96, SN_LE16(8), SN_LE16(60), SN_LE32(4), SN_LE16(1), SN_LE32(4), 0, 12, "m_BlackColor" },
    { SN_LE32(20), 0x94, SN_LE16(8), SN_LE16(13), SN_LE32(0), 7, "m_MultU" },
    { SN_LE32(22), 0x94, SN_LE16(8), SN_LE16(13), SN_LE32(0), 7, "m_MultV" },
    { SN_LE32(24), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(24), SN_LE16(0), 13, "CROMSection_t", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(24), SN_LE16(0), 13, "CROMSection_t", 11, "CROMSection" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(28), 14, "CGameSection_t" },
    { SN_LE32(0), 0x94, SN_LE16(8), SN_LE16(15), SN_LE32(0), 12, "m_dwMatFlags" },
    { SN_LE32(4), 0x94, SN_LE16(8), SN_LE16(13), SN_LE32(0), 11, "m_nMaterial" },
    { SN_LE32(6), 0x94, SN_LE16(8), SN_LE16(12), SN_LE32(0), 10, "m_NodeType" },
    { SN_LE32(7), 0x94, SN_LE16(8), SN_LE16(12), SN_LE32(0), 18, "m_LastTextureFrame" },
    { SN_LE32(8), 0x96, SN_LE16(8), SN_LE16(8), SN_LE32(8), SN_LE16(0), 16, "CTextureLoader_t", 15, "m_TextureLoader" },
    { SN_LE32(16), 0x96, SN_LE16(8), SN_LE16(60), SN_LE32(4), SN_LE16(1), SN_LE32(4), 0, 7, "m_Color" },
    { SN_LE32(20), 0x96, SN_LE16(8), SN_LE16(60), SN_LE32(4), SN_LE16(1), SN_LE32(4), 0, 12, "m_BlackColor" },
    { SN_LE32(24), 0x94, SN_LE16(8), SN_LE16(13), SN_LE32(0), 7, "m_MultU" },
    { SN_LE32(26), 0x94, SN_LE16(8), SN_LE16(13), SN_LE32(0), 7, "m_MultV" },
    { SN_LE32(28), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(28), SN_LE16(0), 14, "CGameSection_t", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(28), SN_LE16(0), 14, "CGameSection_t", 12, "CGameSection" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(6), 19, "CROMTextureFormat_t" },
    { SN_LE32(0), 0x94, SN_LE16(8), SN_LE16(12), SN_LE32(0), 8, "m_Format" },
    { SN_LE32(1), 0x94, SN_LE16(8), SN_LE16(12), SN_LE32(0), 15, "m_PlaybackSpeed" },
    { SN_LE32(2), 0x94, SN_LE16(8), SN_LE16(12), SN_LE32(0), 12, "m_WidthShift" },
    { SN_LE32(3), 0x94, SN_LE16(8), SN_LE16(12), SN_LE32(0), 13, "m_HeightShift" },
    { SN_LE32(4), 0x94, SN_LE16(8), SN_LE16(12), SN_LE32(0), 8, "m_Effect" },
    { SN_LE32(5), 0x94, SN_LE16(8), SN_LE16(12), SN_LE32(0), 12, "m_EffectMode" },
    { SN_LE32(6), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(6), SN_LE16(0), 19, "CROMTextureFormat_t", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(6), SN_LE16(0), 19, "CROMTextureFormat_t", 17, "CROMTextureFormat" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(20), 11, "CROMLevel_t" },
    { SN_LE32(0), 0x94, SN_LE16(8), SN_LE16(6), SN_LE32(0), 14, "m_GridDistance" },
    { SN_LE32(4), 0x96, SN_LE16(8), SN_LE16(60), SN_LE32(3), SN_LE16(1), SN_LE32(3), 0, 12, "m_BlackColor" },
    { SN_LE32(7), 0x96, SN_LE16(8), SN_LE16(60), SN_LE32(3), SN_LE16(1), SN_LE32(3), 0, 12, "m_WhiteColor" },
    { SN_LE32(10), 0x96, SN_LE16(8), SN_LE16(60), SN_LE32(3), SN_LE16(1), SN_LE32(3), 0, 18, "m_DirectionalLight" },
    { SN_LE32(13), 0x96, SN_LE16(8), SN_LE16(60), SN_LE32(3), SN_LE16(1), SN_LE32(3), 0, 14, "m_AmbientLight" },
    { SN_LE32(16), 0x94, SN_LE16(8), SN_LE16(12), SN_LE32(0), 8, "m_bFlags" },
    { SN_LE32(17), 0x96, SN_LE16(8), SN_LE16(50), SN_LE32(3), SN_LE16(1), SN_LE32(3), 0, 11, "m_Direction" },
    { SN_LE32(20), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(20), SN_LE16(0), 11, "CROMLevel_t", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(20), SN_LE16(0), 11, "CROMLevel_t", 9, "CROMLevel" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(4), 15, "CRandomSFPair_t" },
    { SN_LE32(0), 0x94, SN_LE16(8), SN_LE16(13), SN_LE32(0), 1, "v" },
    { SN_LE32(2), 0x94, SN_LE16(8), SN_LE16(13), SN_LE32(0), 1, "r" },
    { SN_LE32(4), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(4), SN_LE16(0), 15, "CRandomSFPair_t", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(4), SN_LE16(0), 15, "CRandomSFPair_t", 13, "CRandomSFPair" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(2), 15, "CRandomS8Pair_t" },
    { SN_LE32(0), 0x94, SN_LE16(8), SN_LE16(2), SN_LE32(0), 1, "v" },
    { SN_LE32(1), 0x94, SN_LE16(8), SN_LE16(2), SN_LE32(0), 1, "r" },
    { SN_LE32(2), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(2), SN_LE16(0), 15, "CRandomS8Pair_t", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(2), SN_LE16(0), 15, "CRandomS8Pair_t", 13, "CRandomS8Pair" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(196), 20, "CROMParticleImpact_t" },
    { SN_LE32(0), 0x96, SN_LE16(8), SN_LE16(56), SN_LE32(112), SN_LE16(1), SN_LE32(14), 13, "s_CEventValue", 18, "m_ImpactEventValue" },
    { SN_LE32(112), 0x96, SN_LE16(8), SN_LE16(61), SN_LE32(28), SN_LE16(1), SN_LE32(14), 0, 20, "m_ImpactParticleType" },
    { SN_LE32(140), 0x96, SN_LE16(8), SN_LE16(61), SN_LE32(28), SN_LE16(1), SN_LE32(14), 0, 17, "m_ImpactEventType" },
    { SN_LE32(168), 0x96, SN_LE16(8), SN_LE16(61), SN_LE32(28), SN_LE16(1), SN_LE32(14), 0, 17, "m_ImpactSoundType" },
    { SN_LE32(196), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(196), SN_LE16(0), 20, "CROMParticleImpact_t", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(196), SN_LE16(0), 20, "CROMParticleImpact_t", 18, "CROMParticleImpact" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(12), 20, "CROMParticleOffset_t" },
    { SN_LE32(0), 0x96, SN_LE16(8), SN_LE16(8), SN_LE32(4), SN_LE16(0), 15, "CRandomSFPair_t", 12, "m_XPosOffset" },
    { SN_LE32(4), 0x96, SN_LE16(8), SN_LE16(8), SN_LE32(4), SN_LE16(0), 15, "CRandomSFPair_t", 12, "m_YPosOffset" },
    { SN_LE32(8), 0x96, SN_LE16(8), SN_LE16(8), SN_LE32(4), SN_LE16(0), 15, "CRandomSFPair_t", 12, "m_ZPosOffset" },
    { SN_LE32(12), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(12), SN_LE16(0), 20, "CROMParticleOffset_t", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(12), SN_LE16(0), 20, "CROMParticleOffset_t", 18, "CROMParticleOffset" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(24), 17, "CROMParticleRot_t" },
    { SN_LE32(0), 0x96, SN_LE16(8), SN_LE16(8), SN_LE32(4), SN_LE16(0), 15, "CRandomSFPair_t", 6, "m_XRot" },
    { SN_LE32(4), 0x96, SN_LE16(8), SN_LE16(8), SN_LE32(4), SN_LE16(0), 15, "CRandomSFPair_t", 9, "m_XRotInc" },
    { SN_LE32(8), 0x96, SN_LE16(8), SN_LE16(8), SN_LE32(4), SN_LE16(0), 15, "CRandomSFPair_t", 6, "m_YRot" },
    { SN_LE32(12), 0x96, SN_LE16(8), SN_LE16(8), SN_LE32(4), SN_LE16(0), 15, "CRandomSFPair_t", 9, "m_YRotInc" },
    { SN_LE32(16), 0x96, SN_LE16(8), SN_LE16(8), SN_LE32(4), SN_LE16(0), 15, "CRandomSFPair_t", 6, "m_ZRot" },
    { SN_LE32(20), 0x96, SN_LE16(8), SN_LE16(8), SN_LE32(4), SN_LE16(0), 15, "CRandomSFPair_t", 9, "m_ZRotInc" },
    { SN_LE32(24), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(24), SN_LE16(0), 17, "CROMParticleRot_t", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(24), SN_LE16(0), 17, "CROMParticleRot_t", 15, "CROMParticleRot" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(36), 19, "CROMParticleScale_t" },
    { SN_LE32(0), 0x96, SN_LE16(8), SN_LE16(8), SN_LE32(4), SN_LE16(0), 15, "CRandomSFPair_t", 8, "m_XScale" },
    { SN_LE32(4), 0x96, SN_LE16(8), SN_LE16(8), SN_LE32(4), SN_LE16(0), 15, "CRandomSFPair_t", 11, "m_XScaleInc" },
    { SN_LE32(8), 0x96, SN_LE16(8), SN_LE16(8), SN_LE32(4), SN_LE16(0), 15, "CRandomSFPair_t", 8, "m_YScale" },
    { SN_LE32(12), 0x96, SN_LE16(8), SN_LE16(8), SN_LE32(4), SN_LE16(0), 15, "CRandomSFPair_t", 11, "m_YScaleInc" },
    { SN_LE32(16), 0x96, SN_LE16(8), SN_LE16(8), SN_LE32(4), SN_LE16(0), 15, "CRandomSFPair_t", 8, "m_ZScale" },
    { SN_LE32(20), 0x96, SN_LE16(8), SN_LE16(8), SN_LE32(4), SN_LE16(0), 15, "CRandomSFPair_t", 11, "m_ZScaleInc" },
    { SN_LE32(24), 0x94, SN_LE16(8), SN_LE16(6), SN_LE32(0), 13, "m_ShadowScale" },
    { SN_LE32(28), 0x94, SN_LE16(8), SN_LE16(6), SN_LE32(0), 11, "m_NearScale" },
    { SN_LE32(32), 0x94, SN_LE16(8), SN_LE16(6), SN_LE32(0), 10, "m_FarScale" },
    { SN_LE32(36), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(36), SN_LE16(0), 19, "CROMParticleScale_t", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(36), SN_LE16(0), 19, "CROMParticleScale_t", 17, "CROMParticleScale" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(12), 17, "CROMParticleDir_t" },
    { SN_LE32(0), 0x96, SN_LE16(8), SN_LE16(8), SN_LE32(4), SN_LE16(0), 15, "CRandomSFPair_t", 12, "m_XDirection" },
    { SN_LE32(4), 0x96, SN_LE16(8), SN_LE16(8), SN_LE32(4), SN_LE16(0), 15, "CRandomSFPair_t", 12, "m_YDirection" },
    { SN_LE32(8), 0x96, SN_LE16(8), SN_LE16(8), SN_LE32(4), SN_LE16(0), 15, "CRandomSFPair_t", 12, "m_ZDirection" },
    { SN_LE32(12), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(12), SN_LE16(0), 17, "CROMParticleDir_t", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(12), SN_LE16(0), 17, "CROMParticleDir_t", 15, "CROMParticleDir" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(26), 22, "CROMParticleSineWave_t" },
    { SN_LE32(0), 0x96, SN_LE16(8), SN_LE16(8), SN_LE32(4), SN_LE16(0), 15, "CRandomSFPair_t", 12, "m_XAmplitude" },
    { SN_LE32(4), 0x96, SN_LE16(8), SN_LE16(8), SN_LE32(4), SN_LE16(0), 15, "CRandomSFPair_t", 12, "m_XFrequency" },
    { SN_LE32(8), 0x96, SN_LE16(8), SN_LE16(8), SN_LE32(4), SN_LE16(0), 15, "CRandomSFPair_t", 8, "m_XPhase" },
    { SN_LE32(12), 0x96, SN_LE16(8), SN_LE16(8), SN_LE32(4), SN_LE16(0), 15, "CRandomSFPair_t", 12, "m_YAmplitude" },
    { SN_LE32(16), 0x96, SN_LE16(8), SN_LE16(8), SN_LE32(4), SN_LE16(0), 15, "CRandomSFPair_t", 12, "m_YFrequency" },
    { SN_LE32(20), 0x96, SN_LE16(8), SN_LE16(8), SN_LE32(4), SN_LE16(0), 15, "CRandomSFPair_t", 8, "m_YPhase" },
    { SN_LE32(24), 0x94, SN_LE16(8), SN_LE16(2), SN_LE32(0), 17, "m_nSineWaveFadeIn" },
    { SN_LE32(26), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(26), SN_LE16(0), 22, "CROMParticleSineWave_t", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(26), SN_LE16(0), 22, "CROMParticleSineWave_t", 20, "CROMParticleSineWave" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(22), 21, "CROMParticlePhysics_t" },
    { SN_LE32(0), 0x96, SN_LE16(8), SN_LE16(8), SN_LE32(4), SN_LE16(0), 15, "CRandomSFPair_t", 9, "m_Gravity" },
    { SN_LE32(4), 0x96, SN_LE16(8), SN_LE16(8), SN_LE32(4), SN_LE16(0), 15, "CRandomSFPair_t", 10, "m_Velocity" },
    { SN_LE32(8), 0x94, SN_LE16(8), SN_LE16(13), SN_LE32(0), 14, "m_BounceEnergy" },
    { SN_LE32(10), 0x94, SN_LE16(8), SN_LE16(13), SN_LE32(0), 16, "m_GroundFriction" },
    { SN_LE32(12), 0x94, SN_LE16(8), SN_LE16(13), SN_LE32(0), 13, "m_AirFriction" },
    { SN_LE32(14), 0x94, SN_LE16(8), SN_LE16(13), SN_LE32(0), 15, "m_WaterFriction" },
    { SN_LE32(16), 0x94, SN_LE16(8), SN_LE16(13), SN_LE32(0), 14, "m_Acceleration" },
    { SN_LE32(18), 0x94, SN_LE16(8), SN_LE16(13), SN_LE32(0), 16, "m_MinMaxVelocity" },
    { SN_LE32(20), 0x94, SN_LE16(8), SN_LE16(13), SN_LE32(0), 12, "m_CollRadius" },
    { SN_LE32(22), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(22), SN_LE16(0), 21, "CROMParticlePhysics_t", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(22), SN_LE16(0), 21, "CROMParticlePhysics_t", 19, "CROMParticlePhysics" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(15), 19, "CROMParticleColor_t" },
    { SN_LE32(0), 0x96, SN_LE16(8), SN_LE16(60), SN_LE32(3), SN_LE16(1), SN_LE32(3), 0, 12, "m_WhiteColor" },
    { SN_LE32(3), 0x96, SN_LE16(8), SN_LE16(60), SN_LE32(3), SN_LE16(1), SN_LE32(3), 0, 12, "m_BlackColor" },
    { SN_LE32(6), 0x96, SN_LE16(8), SN_LE16(60), SN_LE32(3), SN_LE16(1), SN_LE32(3), 0, 13, "m_WhiteColor2" },
    { SN_LE32(9), 0x96, SN_LE16(8), SN_LE16(60), SN_LE32(3), SN_LE16(1), SN_LE32(3), 0, 13, "m_BlackColor2" },
    { SN_LE32(12), 0x94, SN_LE16(8), SN_LE16(2), SN_LE32(0), 14, "m_RandomizeHue" },
    { SN_LE32(13), 0x94, SN_LE16(8), SN_LE16(2), SN_LE32(0), 21, "m_RandomizeSaturation" },
    { SN_LE32(14), 0x94, SN_LE16(8), SN_LE16(2), SN_LE32(0), 21, "m_RandomizeBrightness" },
    { SN_LE32(15), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(15), SN_LE16(0), 19, "CROMParticleColor_t", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(15), SN_LE16(0), 19, "CROMParticleColor_t", 17, "CROMParticleColor" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(16), 21, "CROMParticleGeneral_t" },
    { SN_LE32(0), 0x94, SN_LE16(8), SN_LE16(3), SN_LE32(0), 9, "m_nFrames" },
    { SN_LE32(2), 0x94, SN_LE16(8), SN_LE16(3), SN_LE32(0), 12, "m_nFramesRnd" },
    { SN_LE32(4), 0x94, SN_LE16(8), SN_LE16(2), SN_LE32(0), 13, "m_Probability" },
    { SN_LE32(5), 0x94, SN_LE16(8), SN_LE16(2), SN_LE32(0), 12, "m_Visibility" },
    { SN_LE32(6), 0x94, SN_LE16(8), SN_LE16(2), SN_LE32(0), 12, "m_nParticles" },
    { SN_LE32(7), 0x94, SN_LE16(8), SN_LE16(2), SN_LE32(0), 15, "m_nParticlesRnd" },
    { SN_LE32(8), 0x94, SN_LE16(8), SN_LE16(2), SN_LE32(0), 11, "m_nPriority" },
    { SN_LE32(9), 0x94, SN_LE16(8), SN_LE16(2), SN_LE32(0), 9, "m_nFadeIn" },
    { SN_LE32(10), 0x94, SN_LE16(8), SN_LE16(2), SN_LE32(0), 10, "m_nFadeOut" },
    { SN_LE32(11), 0x94, SN_LE16(8), SN_LE16(2), SN_LE32(0), 5, "m_FPS" },
    { SN_LE32(12), 0x94, SN_LE16(8), SN_LE16(2), SN_LE32(0), 13, "m_nInBetweens" },
    { SN_LE32(13), 0x94, SN_LE16(8), SN_LE16(2), SN_LE32(0), 11, "m_nMaxDelay" },
    { SN_LE32(14), 0x94, SN_LE16(8), SN_LE16(2), SN_LE32(0), 11, "m_Alignment" },
    { SN_LE32(15), 0x94, SN_LE16(8), SN_LE16(12), SN_LE32(0), 7, "m_Alert" },
    { SN_LE32(16), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(16), SN_LE16(0), 21, "CROMParticleGeneral_t", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(16), SN_LE16(0), 21, "CROMParticleGeneral_t", 19, "CROMParticleGeneral" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(60), 20, "CROMParticleEffect_t" },
    { SN_LE32(0), 0x94, SN_LE16(8), SN_LE16(15), SN_LE32(0), 9, "m_dwFlags" },
    { SN_LE32(4), 0x94, SN_LE16(8), SN_LE16(3), SN_LE32(0), 13, "m_nTextureSet" },
    { SN_LE32(6), 0x94, SN_LE16(8), SN_LE16(2), SN_LE32(0), 9, "m_nSwoosh" },
    { SN_LE32(7), 0x94, SN_LE16(8), SN_LE16(2), SN_LE32(0), 15, "m_nDynamicLight" },
    { SN_LE32(8), 0x94, SN_LE16(8), SN_LE16(2), SN_LE32(0), 10, "m_Playback" },
    { SN_LE32(9), 0x94, SN_LE16(8), SN_LE16(2), SN_LE32(0), 18, "m_InstanceBehavior" },
    { SN_LE32(10), 0x94, SN_LE16(8), SN_LE16(2), SN_LE32(0), 14, "m_WallBehavior" },
    { SN_LE32(11), 0x94, SN_LE16(8), SN_LE16(2), SN_LE32(0), 16, "m_GroundBehavior" },
    { SN_LE32(12), 0x94, SN_LE16(8), SN_LE16(3), SN_LE32(0), 11, "m_SoundType" },
    { SN_LE32(14), 0x94, SN_LE16(8), SN_LE16(3), SN_LE32(0), 24, "m_MaxAngleChangePerFrame" },
    { SN_LE32(16), 0x94, SN_LE16(8), SN_LE16(3), SN_LE32(0), 26, "m_ProximityDetectionRadius" },
    { SN_LE32(18), 0x94, SN_LE16(8), SN_LE16(12), SN_LE32(0), 9, "m_bFlags2" },
    { SN_LE32(19), 0x96, SN_LE16(8), SN_LE16(60), SN_LE32(1), SN_LE16(1), SN_LE32(1), 0, 7, "padding" },
    { SN_LE32(20), 0x94, SN_LE16(8), SN_LE16(17), SN_LE32(0), 10, "m_rpObject" },
    { SN_LE32(24), 0x96, SN_LE16(8), SN_LE16(24), SN_LE32(196), SN_LE16(0), 20, "CROMParticleImpact_t", 9, "m_pImpact" },
    { SN_LE32(28), 0x96, SN_LE16(8), SN_LE16(24), SN_LE32(12), SN_LE16(0), 20, "CROMParticleOffset_t", 9, "m_pOffset" },
    { SN_LE32(32), 0x96, SN_LE16(8), SN_LE16(24), SN_LE32(24), SN_LE16(0), 17, "CROMParticleRot_t", 6, "m_pRot" },
    { SN_LE32(36), 0x96, SN_LE16(8), SN_LE16(24), SN_LE32(36), SN_LE16(0), 19, "CROMParticleScale_t", 8, "m_pScale" },
    { SN_LE32(40), 0x96, SN_LE16(8), SN_LE16(24), SN_LE32(12), SN_LE16(0), 17, "CROMParticleDir_t", 6, "m_pDir" },
    { SN_LE32(44), 0x96, SN_LE16(8), SN_LE16(24), SN_LE32(26), SN_LE16(0), 22, "CROMParticleSineWave_t", 11, "m_pSineWave" },
    { SN_LE32(48), 0x96, SN_LE16(8), SN_LE16(24), SN_LE32(22), SN_LE16(0), 21, "CROMParticlePhysics_t", 10, "m_pPhysics" },
    { SN_LE32(52), 0x96, SN_LE16(8), SN_LE16(24), SN_LE32(15), SN_LE16(0), 19, "CROMParticleColor_t", 8, "m_pColor" },
    { SN_LE32(56), 0x96, SN_LE16(8), SN_LE16(24), SN_LE32(16), SN_LE16(0), 21, "CROMParticleGeneral_t", 10, "m_pGeneral" },
    { SN_LE32(60), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(60), SN_LE16(0), 20, "CROMParticleEffect_t", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(60), SN_LE16(0), 20, "CROMParticleEffect_t", 18, "CROMParticleEffect" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(20), 15, "CROMWarpPoint_t" },
    { SN_LE32(0), 0x96, SN_LE16(8), SN_LE16(8), SN_LE32(12), SN_LE16(0), 10, "CVector3_t", 6, "m_vPos" },
    { SN_LE32(12), 0x94, SN_LE16(8), SN_LE16(6), SN_LE32(0), 6, "m_RotY" },
    { SN_LE32(16), 0x94, SN_LE16(8), SN_LE16(3), SN_LE32(0), 8, "m_nLevel" },
    { SN_LE32(18), 0x94, SN_LE16(8), SN_LE16(3), SN_LE32(0), 9, "m_nRegion" },
    { SN_LE32(20), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(20), SN_LE16(0), 15, "CROMWarpPoint_t", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(20), SN_LE16(0), 15, "CROMWarpPoint_t", 13, "CROMWarpPoint" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(112), 10, "CROMNode_t" },
    { SN_LE32(0), 0x96, SN_LE16(8), SN_LE16(56), SN_LE32(96), SN_LE16(1), SN_LE32(8), 10, "CVector3_t", 14, "vBoundsCorners" },
    { SN_LE32(96), 0x94, SN_LE16(8), SN_LE16(6), SN_LE32(0), 11, "m_MaxBounds" },
    { SN_LE32(100), 0x94, SN_LE16(8), SN_LE16(2), SN_LE32(0), 13, "m_ParentIndex" },
    { SN_LE32(101), 0x94, SN_LE16(8), SN_LE16(12), SN_LE32(0), 8, "m_Symbol" },
    { SN_LE32(102), 0x94, SN_LE16(8), SN_LE16(12), SN_LE32(0), 14, "m_MaterialType" },
    { SN_LE32(103), 0x96, SN_LE16(8), SN_LE16(60), SN_LE32(1), SN_LE16(1), SN_LE32(1), 0, 3, "pad" },
    { SN_LE32(104), 0x94, SN_LE16(8), SN_LE16(6), SN_LE32(0), 14, "m_DamageScaler" },
    { SN_LE32(108), 0x94, SN_LE16(8), SN_LE16(15), SN_LE32(0), 14, "m_dwModelFlags" },
    { SN_LE32(112), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(112), SN_LE16(0), 10, "CROMNode_t", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(112), SN_LE16(0), 10, "CROMNode_t", 8, "CROMNode" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(32), 16, "CROMObjectInfo_t" },
    { SN_LE32(0), 0x96, SN_LE16(8), SN_LE16(8), SN_LE32(24), SN_LE16(0), 12, "CROMBounds_t", 8, "m_Bounds" },
    { SN_LE32(24), 0x94, SN_LE16(8), SN_LE16(2), SN_LE32(0), 20, "m_HeadTrackStartNode" },
    { SN_LE32(25), 0x94, SN_LE16(8), SN_LE16(2), SN_LE32(0), 18, "m_HeadTrackEndNode" },
    { SN_LE32(26), 0x94, SN_LE16(8), SN_LE16(2), SN_LE32(0), 17, "m_HeadTrackFactor" },
    { SN_LE32(27), 0x94, SN_LE16(8), SN_LE16(2), SN_LE32(0), 4, "pad0" },
    { SN_LE32(28), 0x94, SN_LE16(8), SN_LE16(13), SN_LE32(0), 12, "m_nVariation" },
    { SN_LE32(30), 0x94, SN_LE16(8), SN_LE16(13), SN_LE32(0), 11, "m_UnitScale" },
    { SN_LE32(32), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(32), SN_LE16(0), 16, "CROMObjectInfo_t", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(32), SN_LE16(0), 16, "CROMObjectInfo_t", 14, "CROMObjectInfo" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(8), 7, "CNode_t" },
    { SN_LE32(0), 0x96, SN_LE16(8), SN_LE16(24), SN_LE32(8), SN_LE16(0), 7, "CNode_t", 7, "m_pPrev" },
    { SN_LE32(4), 0x96, SN_LE16(8), SN_LE16(24), SN_LE32(8), SN_LE16(0), 7, "CNode_t", 7, "m_pNext" },
    { SN_LE32(8), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(8), SN_LE16(0), 7, "CNode_t", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(8), SN_LE16(0), 7, "CNode_t", 5, "CNode" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(12), 11, "CNodeList_t" },
    { SN_LE32(0), 0x96, SN_LE16(8), SN_LE16(24), SN_LE32(8), SN_LE16(0), 7, "CNode_t", 7, "m_pHead" },
    { SN_LE32(4), 0x96, SN_LE16(8), SN_LE16(24), SN_LE32(8), SN_LE16(0), 7, "CNode_t", 7, "m_pTail" },
    { SN_LE32(8), 0x94, SN_LE16(8), SN_LE16(5), SN_LE32(0), 8, "m_Length" },
    { SN_LE32(12), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(12), SN_LE16(0), 11, "CNodeList_t", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(12), SN_LE16(0), 11, "CNodeList_t", 9, "CNodeList" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(24), 14, "CDynamicList_t" },
    { SN_LE32(0), 0x96, SN_LE16(8), SN_LE16(8), SN_LE32(12), SN_LE16(0), 11, "CNodeList_t", 10, "m_FreeList" },
    { SN_LE32(12), 0x96, SN_LE16(8), SN_LE16(8), SN_LE32(12), SN_LE16(0), 11, "CNodeList_t", 12, "m_ActiveList" },
    { SN_LE32(24), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(24), SN_LE16(0), 14, "CDynamicList_t", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(24), SN_LE16(0), 14, "CDynamicList_t", 12, "CDynamicList" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(4), 12, "CSelection_t" },
    { SN_LE32(0), 0x94, SN_LE16(8), SN_LE16(3), SN_LE32(0), 8, "m_Number" },
    { SN_LE32(2), 0x94, SN_LE16(8), SN_LE16(3), SN_LE32(0), 8, "m_Weight" },
    { SN_LE32(4), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(4), SN_LE16(0), 12, "CSelection_t", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(4), SN_LE16(0), 12, "CSelection_t", 10, "CSelection" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(102), 16, "CSelectionList_t" },
    { SN_LE32(0), 0x94, SN_LE16(8), SN_LE16(3), SN_LE32(0), 9, "m_Entries" },
    { SN_LE32(2), 0x96, SN_LE16(8), SN_LE16(56), SN_LE32(100), SN_LE16(1), SN_LE32(25), 12, "CSelection_t", 6, "m_List" },
    { SN_LE32(102), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(102), SN_LE16(0), 16, "CSelectionList_t", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(102), SN_LE16(0), 16, "CSelectionList_t", 14, "CSelectionList" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(20), 19, "CGameAnimateState_t" },
    { SN_LE32(0), 0x94, SN_LE16(8), SN_LE16(6), SN_LE32(0), 6, "cFrame" },
    { SN_LE32(4), 0x94, SN_LE16(8), SN_LE16(3), SN_LE32(0), 5, "nAnim" },
    { SN_LE32(6), 0x94, SN_LE16(8), SN_LE16(3), SN_LE32(0), 12, "nDesiredAnim" },
    { SN_LE32(8), 0x94, SN_LE16(8), SN_LE16(3), SN_LE32(0), 7, "nFrames" },
    { SN_LE32(10), 0x94, SN_LE16(8), SN_LE16(2), SN_LE32(0), 14, "CycleCompleted" },
    { SN_LE32(11), 0x94, SN_LE16(8), SN_LE16(2), SN_LE32(0), 6, "Active" },
    { SN_LE32(12), 0x94, SN_LE16(8), SN_LE16(15), SN_LE32(0), 6, "LoopTo" },
    { SN_LE32(16), 0x96, SN_LE16(8), SN_LE16(24), SN_LE32(40), SN_LE16(0), 11, "CMemEntry_t", 11, "pmeAnimData" },
    { SN_LE32(20), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(20), SN_LE16(0), 19, "CGameAnimateState_t", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(20), SN_LE16(0), 19, "CGameAnimateState_t", 17, "CGameAnimateState" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(20), SN_LE16(0), 19, "CGameAnimateState_t", 4, "CGAS" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(20), SN_LE16(0), 24, "CROMInitialOrientation_t", 9, "CRIOrient" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(4), SN_LE16(0), 15, "CROMNodeIndex_t", 8, "CRNIndex" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(36), 10, "AnimInfo_t" },
    { SN_LE32(0), 0x96, SN_LE16(8), SN_LE16(24), SN_LE32(4), SN_LE16(0), 15, "CROMNodeIndex_t", 15, "NodeAnimIndices" },
    { SN_LE32(4), 0x96, SN_LE16(8), SN_LE16(24), SN_LE32(20), SN_LE16(0), 24, "CROMInitialOrientation_t", 14, "InitialOrients" },
    { SN_LE32(8), 0x96, SN_LE16(8), SN_LE16(24), SN_LE32(8), SN_LE16(0), 6, "s_ISet", 11, "isTransSets" },
    { SN_LE32(12), 0x96, SN_LE16(8), SN_LE16(24), SN_LE32(8), SN_LE16(0), 6, "s_ISet", 9, "isRotSets" },
    { SN_LE32(16), 0x94, SN_LE16(8), SN_LE16(4), SN_LE32(0), 9, "RotIndex1" },
    { SN_LE32(20), 0x94, SN_LE16(8), SN_LE16(4), SN_LE32(0), 9, "RotIndex2" },
    { SN_LE32(24), 0x94, SN_LE16(8), SN_LE16(4), SN_LE32(0), 11, "TransIndex1" },
    { SN_LE32(28), 0x94, SN_LE16(8), SN_LE16(4), SN_LE32(0), 11, "TransIndex2" },
    { SN_LE32(32), 0x94, SN_LE16(8), SN_LE16(6), SN_LE32(0), 5, "Blend" },
    { SN_LE32(36), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(36), SN_LE16(0), 10, "AnimInfo_t", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(36), SN_LE16(0), 10, "AnimInfo_t", 8, "AnimInfo" },
    { SN_LE32(0), 0x94, SN_LE16(15), SN_LE16(10), SN_LE32(4), 24, "CGameObjectInstanceModes" },
    { SN_LE32(0), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 9, "IDLE_MODE" },
    { SN_LE32(1), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 19, "TRANS_FADE_OUT_MODE" },
    { SN_LE32(2), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 12, "END_OF_MODES" },
    { SN_LE32(4), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(4), SN_LE16(0), 24, "CGameObjectInstanceModes", 4, ".eos" },
    { SN_LE32(0), 0x94, SN_LE16(15), SN_LE16(10), SN_LE32(4), 10, "ModelTypes" },
    { SN_LE32(0), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 17, "NORMAL_MODEL_TYPE" },
    { SN_LE32(1), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 19, "EXTREME1_MODEL_TYPE" },
    { SN_LE32(2), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 19, "EXTREME2_MODEL_TYPE" },
    { SN_LE32(3), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 19, "EXTREME3_MODEL_TYPE" },
    { SN_LE32(4), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 19, "EXTREME4_MODEL_TYPE" },
    { SN_LE32(5), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 19, "EXTREME5_MODEL_TYPE" },
    { SN_LE32(6), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 19, "EXTREME6_MODEL_TYPE" },
    { SN_LE32(7), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 19, "EXTREME7_MODEL_TYPE" },
    { SN_LE32(8), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 19, "EXTREME8_MODEL_TYPE" },
    { SN_LE32(9), 0x94, SN_LE16(16), SN_LE16(11), SN_LE32(0), 11, "MODEL_TYPES" },
    { SN_LE32(4), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(4), SN_LE16(0), 10, "ModelTypes", 4, ".eos" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(40), 20, "CROMObjectInstance_t" },
    { SN_LE32(0), 0x96, SN_LE16(8), SN_LE16(8), SN_LE32(4), SN_LE16(0), 10, "CVisBits_t", 9, "m_VisBits" },
    { SN_LE32(4), 0x96, SN_LE16(8), SN_LE16(8), SN_LE32(12), SN_LE16(0), 10, "CVector3_t", 6, "m_vPos" },
    { SN_LE32(16), 0x96, SN_LE16(8), SN_LE16(8), SN_LE32(12), SN_LE16(0), 10, "CVector3_t", 8, "m_vScale" },
    { SN_LE32(28), 0x94, SN_LE16(8), SN_LE16(13), SN_LE32(0), 10, "m_nObjType" },
    { SN_LE32(30), 0x94, SN_LE16(8), SN_LE16(13), SN_LE32(0), 11, "m_nTypeFlag" },
    { SN_LE32(32), 0x94, SN_LE16(8), SN_LE16(13), SN_LE32(0), 16, "m_nCurrentRegion" },
    { SN_LE32(34), 0x94, SN_LE16(8), SN_LE16(13), SN_LE32(0), 12, "m_nVariation" },
    { SN_LE32(36), 0x94, SN_LE16(8), SN_LE16(3), SN_LE32(0), 6, "m_RotY" },
    { SN_LE32(38), 0x94, SN_LE16(8), SN_LE16(12), SN_LE32(0), 8, "m_bFlags" },
    { SN_LE32(39), 0x94, SN_LE16(8), SN_LE16(12), SN_LE32(0), 7, "m_nPath" },
    { SN_LE32(40), 0x96, SN_LE16(102), SN_LE16(0), SN_LE32(40), SN_LE16(0), 20, "CROMObjectInstance_t", 4, ".eos" },
    { SN_LE32(0), 0x96, SN_LE16(13), SN_LE16(8), SN_LE32(40), SN_LE16(0), 20, "CROMObjectInstance_t", 18, "CROMObjectInstance" },
    { SN_LE32(0), 0x94, SN_LE16(10), SN_LE16(8), SN_LE32(744), 21, "CGameObjectInstance_t" },
    { SN_LE32(0), 0x96, SN_LE16(8), SN_LE16(8), SN_LE32(80), SN_LE16(0), 18, "CAnimInstanceHdr_t", 2, "ah" },
    { SN_LE32(80), 0x96, SN_LE16(8), SN_LE16(8), SN_LE32(12), SN_LE16(0), 10, "CVector3_t", 8, "m_vScale" },
    { SN_LE32(92), 0x96, SN_LE16(8), SN_LE16(8), SN_LE32(16), SN_LE16(0), 10, "CQuatern_t", 9, "m_qGround" },
    { SN_LE32(108), 0x94, SN_LE16(8), SN_LE16(6), SN_LE32(0), 6, "m_RotY" },
    { SN_LE32(112), 0x94, SN_LE16(8), SN_LE16(6), SN_LE32(0), 18, "m_CollisionYOffset" },
    { SN_LE32(116), 0x96, SN_LE16(8), SN_LE16(246), SN_LE32(64), SN_LE16(2), SN_LE32(4), SN_LE32(4), 0, 10, "m_mfOrient" },
    { SN_LE32(180), 0x96, SN_LE16(8), SN_LE16(25), SN_LE32(64), SN_LE16(0), 7, ".26fake", 13, "m_pmtDrawMtxs" },
    { SN_LE32(184), 0x96, SN_LE16(8), SN_LE16(25), SN_LE32(64), SN_LE16(0), 7, ".26fake", 22, "m_pmtLastFrameDrawMtxs" },
    { SN_LE32(188), 0x96, SN_LE16(8), SN_LE16(982), SN_LE32(4), SN_LE16(2), SN_LE32(4), SN_LE32(4), 0, 11, "m_pmfShadow" },
    { SN_LE32(192), 0x96, SN_LE16(8), SN_LE16(25), SN_LE32(8), SN_LE16(0), 7, ".63fake", 8, "m_pDList" },
    { SN_LE32(196), 0x94, SN_LE16(8), SN_LE16(17), SN_LE32(0), 14, "m_rpObjectInfo" },
    { SN_LE32(200), 0x94, SN_LE16(8), SN_LE16(17), SN_LE32(0), 9, "m_rpAnims" },
    { SN_LE32(204), 0x94, SN_LE16(8), SN_LE16(17), SN_LE32(0), 15, "m_rpModelsIndex" },
    { SN_LE32(208), 0x94, SN_LE16(8), SN_LE16(15), SN_LE32(0), 16, "m_ObjectInfoSize" },
    { SN_LE32(212), 0x94, SN_LE16(8), SN_LE16(15), SN_LE32(0), 17, "m_ModelsIndexSize" },
    { SN_LE32(216), 0x94, SN_LE16(8), SN_LE16(5), SN_LE32(0), 15, "m_nCurrentModel" },
    { SN_LE32(220), 0x94, SN_LE16(8), SN_LE16(17), SN_LE32(0), 9, "m_rpModel" },
    { SN_LE32(224), 0x94, SN_LE16(8), SN_LE16(15), SN_LE32(0), 11, "m_ModelSize" },
    { SN_LE32(228), 0x94, SN_LE16(8), SN_LE16(13), SN_LE32(0), 11, "m_nTypeFlag" },
    { SN_LE32(230), 0x94, SN_LE16(8), SN_LE16(2), SN_LE32(0), 8, "m_nAnims" },
    { SN_LE32(231), 0x94, SN_LE16(8), SN_LE16(2), SN_LE32(0), 9, "m_nModels" },
    { SN_LE32(232), 0x96, SN_LE16(8), SN_LE16(8), SN_LE32(24), SN_LE16(0), 12, "CROMBounds_t", 8, "m_Bounds" },
    { SN_LE32(256), 0x94, SN_LE16(8), SN_LE16(15), SN_LE32(0), 9, "m_dwFlags" },
    { SN_LE32(260), 0x96, SN_LE16(8), SN_LE16(8), SN_LE32(20), SN_LE16(0), 19, "CGameAnimateState_t", 11, "m_asCurrent" },
    { SN_LE32(280), 0x96, SN_LE16(8), SN_LE16(8), SN_LE32(20), SN_LE16(0), 19, "CGameAnimateState_t", 9, "m_asBlend" },
    { SN_LE32(300), 0x94, SN_LE16(8), SN_LE16(3), SN_LE32(0), 13, "m_BlendLength" },
    { SN_LE32(304), 0x94, SN_LE16(8), SN_LE16(6), SN_LE32(0), 10, "m_uBlender" },
    { SN_LE32(308), 0x94, SN_LE16(8), SN_LE16(6), SN_LE32(0), 10, "m_BlendPos" },
    { SN_LE32(312), 0x94, SN_LE16(8), SN_LE16(12), SN_LE32(0), 12, "m_BlendStart" },
    { SN_LE32(313), 0x94, SN_LE16(8), SN_LE16(12), SN_LE32(0), 13, "m_BlendFinish" },
    { SN_LE32(314), 0x94, SN_LE16(8), SN_LE16(12), SN_LE32(0), 13, "m_ShadowAlpha" },
    { SN_LE32(315), 0x94, SN_LE16(8), SN_LE16(12), SN_LE32(0), 16, "m_ActiveSwooshes" },
    { SN_LE32(320), 0x96, SN_LE16(8), SN_LE16(56), SN_LE32(48), SN_LE16(1), SN_LE32(2), 7, ".36fake", 8, "m_Lights" },
    { 0x70, 0x01, 0x00, 0x00, 0x96, 0x08, 0x00, 0x08, 0x00, 0x70, 0x01, 0x00, 0x00, 0x00, 0x00, 0x05, 0x43, 0x41, 0x49, 0x5F, 0x74, 0x04 },
};
typedef char g_sn64RuntimeTypeRecordsSizeCheck[(sizeof(g_sn64RuntimeTypeRecords) == 12792) ? 1 : -1];
#endif
