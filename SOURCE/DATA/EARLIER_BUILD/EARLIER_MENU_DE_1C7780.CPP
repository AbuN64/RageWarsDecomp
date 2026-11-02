#if defined(VERSION_DE)
#include "MENU/BUILD/DEFINITION_DATA.H"

/* Older build's option mask row: the word and label it names are earlier-build symbols. */
struct EarlierOptionBitRow {
    void *word;
    void *name;
    unsigned int mask;
    unsigned int enable;
};

/* Older build's menu tuning block (counts, camera offsets and a step angle); fields unnamed. */
struct EarlierMenuTuning {
    unsigned int word0;
    unsigned int word1;
    unsigned int word2;
    unsigned int word3;
    float originX;
    float originY;
    float scale[3];
    unsigned int count0;
    unsigned int count1;
    float stepAngle;
};

extern char g_earlierMenuPaged_43DAA0[];
extern char g_earlierMenuPaged_43DAC4[];
extern char g_earlierMenuPaged_43DB10[];
extern char g_earlierMenuPaged_43DC64[];
extern char g_earlierMenuPaged_43E180[];
extern char g_earlierMenuPaged_43E1B8[];
extern char g_earlierMenuPaged_43E214[];
extern char g_earlierMenuPaged_43E24C[];
extern char g_earlierMenuPaged_43E298[];
extern char g_earlierMenuPaged_43E38C[];
extern char g_earlierMenuPaged_43E3D8[];
extern char g_earlierMenuPaged_43E404[];
extern char g_earlierMenuPaged_43E428[];
extern char g_earlierMenuPaged_43E454[];
extern char g_earlierMenuPaged_43E4A0[];
extern char g_earlierMenuPaged_43E4C4[];
extern char g_earlierMenuPaged_43E4F0[];
extern char g_earlierMenuPaged_43E528[];
extern char g_earlierMenuPaged_43E588[];
extern char g_earlierMenuPaged_43E590[];
extern char g_earlierMenuPaged_43E598[];
extern char g_earlierMenuPaged_43E5D0[];
extern char g_earlierMenuPaged_43E618[];
extern char g_earlierMenuPaged_43E7F0[];
extern char g_earlierMenuPaged_43E8DC[];
extern char g_earlierMenuPaged_43E908[];
extern char g_earlierMenuPaged_43E93C[];
extern char g_earlierMenuPaged_43E968[];
extern char g_earlierMenuPaged_43E9C0[];
extern char g_earlierMenuPaged_43EA0C[];
extern char g_earlierMenuPaged_43EA58[];
extern char g_earlierMenuPaged_43EB30[];
extern char g_earlierMenuPaged_43EBA4[];
extern char g_earlierMenuPaged_43EC00[];
extern char g_earlierMenuPaged_43EC2C[];
extern char g_earlierMenuPaged_43EC58[];
extern char g_earlierMenuPaged_43EC84[];
extern char g_earlierMenuPaged_43ED70[];
extern char g_earlierMenuPaged_43ED9C[];
extern char g_earlierMenuPaged_43EDE4[];
extern char g_earlierMenuPaged_44029C[];
extern char g_earlierMenuPaged_4407F8[];
extern char g_earlierMenuPaged_4415B4[];
extern char g_earlierMenuPaged_442024[];
extern char g_earlierMenuPaged_442344[];
extern char g_earlierMenuResource_800D3624[];
extern char g_earlierMenuResource_800D362C[];
extern char g_earlierMenuResource_800D3630[];
extern char g_earlierMenuResource_800D3634[];
extern char g_earlierMenuResource_800D3650[];
extern char g_earlierMenuResource_800D365C[];
extern char g_earlierMenuResource_800D3660[];
extern char g_earlierMenuResource_800D3664[];
extern char g_earlierMenuResource_800D3668[];
extern char g_earlierMenuResource_800D366C[];
extern char g_earlierMenuResource_800D3670[];
extern char g_earlierMenuResource_800D3674[];
extern char g_earlierMenuResource_800D3678[];
extern char g_earlierMenuResource_800D367C[];
extern char g_earlierMenuResource_800D3680[];
extern char g_earlierMenuResource_800D3684[];
extern char g_earlierMenuResource_800D3688[];
extern char g_earlierMenuResource_800D3A58[];
extern char g_earlierMenuResource_800D3A5C[];
extern char g_earlierMenuResource_800D3A6C[];
extern char g_earlierMenuResource_800D3A7C[];
extern char g_earlierMenuResource_800D3A80[];
extern char g_earlierMenuResource_800D3C48[];
extern char g_earlierMenuResource_800D3C4C[];
extern char g_earlierMenuResource_800D3C50[];
extern char g_earlierMenuResource_800D3C54[];
extern char g_earlierMenuResource_800D3C58[];
extern char g_earlierMenuResource_800D3D04[];
extern char g_earlierMenuResource_800D3D6C[];
extern char g_earlierMenuResource_800D3D70[];
extern char g_earlierMenuResource_800D3D7C[];
extern char g_earlierMenuResource_800D3DDC[];
extern char g_earlierMenuResource_800D3F48[];
extern struct MenuBuildItemData g_earlierMenuItems_44F780[3];
extern struct MenuBuildItemData g_earlierMenuItems_44F810[9];
extern struct MenuBuildItemData g_earlierMenuItems_44F978[5];
extern struct MenuBuildDefinitionData g_earlierMenuDef_44FA2C;
extern struct EarlierMenuTuning g_earlierMenuTuning_44FA50;
extern struct MenuBuildItemData g_earlierMenuItems_44FA80[3];
extern struct MenuBuildDefinitionData g_earlierMenuDef_44FAEC;
extern struct MenuBuildItemData g_earlierMenuItems_44FB34[4];
extern struct MenuBuildItemData g_earlierMenuItems_44FC28[11];
extern struct MenuBuildItemData g_earlierMenuItems_44FDD8[4];
extern struct MenuBuildDefinitionData g_earlierMenuDef_44FE68;
extern struct MenuBuildItemData g_earlierMenuItems_44FE8C[5];
extern struct MenuBuildItemData g_earlierMenuItems_44FF88[1];
extern struct MenuBuildItemData g_earlierMenuItems_44FFD0[7];
extern struct MenuBuildDefinitionData g_earlierMenuDef_4500CC;
extern struct MenuBuildItemData g_earlierMenuItems_4500F0[2];

struct MenuBuildItemData g_earlierMenuItems_44F780[3] = {
    { 0x0000, 0x0000, 0x00000021, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800D3A80, (unsigned int)g_earlierMenuPaged_442024, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00010081, 0x0000, 0x0028, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800D3A58, (unsigned int)g_earlierMenuPaged_442024, 0x00000000, (unsigned int)g_earlierMenuPaged_43DAA0, 0x00000000 },
    { 0x0000, 0x0000, 0x00010081, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800D3A5C, (unsigned int)g_earlierMenuPaged_442024, 0x00000000, (unsigned int)g_earlierMenuPaged_43DAC4, 0x00000000 },
};

struct MenuBuildDefinitionData g_earlierMenuDef_44F7EC = { (unsigned int)g_earlierMenuItems_44F780, 0x0003, 0x0000, 0x00000000, 0x00000000, (unsigned int)g_earlierMenuPaged_4415B4, 0x00000000, 0x0001, 0x0000, 0x0000, 0x0000, 0x00000000 };

struct MenuBuildItemData g_earlierMenuItems_44F810[9] = {
    { 0x0000, 0x0000, 0x00011001, 0x0000, 0x0000, 0x00, 0x00, 0x00, 0x00, (int)g_earlierMenuResource_800D3660, (unsigned int)g_earlierMenuPaged_442024, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00011001, 0x0000, 0x0000, 0x00, 0x00, 0x00, 0x00, (int)g_earlierMenuResource_800D3664, (unsigned int)g_earlierMenuPaged_442024, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00011001, 0x0000, 0x0000, 0x00, 0x00, 0x00, 0x00, (int)g_earlierMenuResource_800D3668, (unsigned int)g_earlierMenuPaged_442024, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00011001, 0x0000, 0x0000, 0x00, 0x00, 0x00, 0x00, (int)g_earlierMenuResource_800D366C, (unsigned int)g_earlierMenuPaged_442024, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00011001, 0x0000, 0x0000, 0x00, 0x00, 0x00, 0x00, (int)g_earlierMenuResource_800D3670, (unsigned int)g_earlierMenuPaged_442024, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00011001, 0x0000, 0x0000, 0x00, 0x00, 0x00, 0x00, (int)g_earlierMenuResource_800D3674, (unsigned int)g_earlierMenuPaged_442024, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00011001, 0x0000, 0x0000, 0x00, 0x00, 0x00, 0x00, (int)g_earlierMenuResource_800D3678, (unsigned int)g_earlierMenuPaged_442024, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00011001, 0x0000, 0x0000, 0x00, 0x00, 0x00, 0x00, (int)g_earlierMenuResource_800D367C, (unsigned int)g_earlierMenuPaged_442024, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0005, 0x00, 0x00, 0x00, 0x00, (int)g_earlierMenuResource_800D365C, (unsigned int)g_earlierMenuPaged_442024, 0x00000000, (unsigned int)g_earlierMenuPaged_43E1B8, 0x00000000 },
};

struct MenuBuildDefinitionData g_earlierMenuDef_44F954 = { (unsigned int)g_earlierMenuItems_44F810, 0x0009, 0x0000, 0x00000000, 0x00000000, (unsigned int)g_earlierMenuPaged_4415B4, (unsigned int)g_earlierMenuPaged_43E180, 0x0008, 0x0000, 0x0000, 0x0000, (int)&g_earlierMenuDef_44FA2C };

struct MenuBuildItemData g_earlierMenuItems_44F978[5] = {
    { 0x0000, 0x0000, 0x00011001, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x02, (int)g_earlierMenuResource_800D3630, (unsigned int)g_earlierMenuPaged_442024, 0x00000000, (unsigned int)g_earlierMenuPaged_43E3D8, 0x00000000 },
    { 0x0000, 0x0000, 0x00010101, 0x0000, 0x0008, 0x00, 0x00, 0x00, 0x00, (int)g_earlierMenuResource_800D3634, (unsigned int)g_earlierMenuPaged_442024, (unsigned int)g_earlierMenuPaged_43E404, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00411001, 0x0000, 0x0008, 0x00, 0x00, 0xFE, 0x01, (int)g_earlierMenuResource_800D3DDC, (unsigned int)g_earlierMenuPaged_442024, (unsigned int)g_earlierMenuPaged_43E298, (unsigned int)g_earlierMenuPaged_43E24C, 0x00000000 },
    { 0x0000, 0x0000, 0x00411001, 0x0000, 0x0002, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800D3650, (unsigned int)g_earlierMenuPaged_442024, (unsigned int)g_earlierMenuPaged_43E454, (unsigned int)g_earlierMenuPaged_43E38C, 0x00000000 },
    { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0005, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800D365C, (unsigned int)g_earlierMenuPaged_442024, 0x00000000, (unsigned int)g_earlierMenuPaged_43E428, 0x00000000 },
};

struct MenuBuildDefinitionData g_earlierMenuDef_44FA2C = { (unsigned int)g_earlierMenuItems_44F978, 0x0005, 0x0000, 0x00000000, 0x00000000, (unsigned int)g_earlierMenuPaged_4415B4, (unsigned int)g_earlierMenuPaged_43E214, 0x0004, 0x0000, 0x0000, 0x0000, (int)&g_earlierMenuDef_44FAEC };

struct EarlierMenuTuning g_earlierMenuTuning_44FA50 = {
    0x00000460, 0x0000000B, 0x00000000, 0x00000000,
    -5e+01f, -9e+02f,
    { 2.0f, 2.0f, 2.0f },
    0x00000032, 0x00000050,
    0.087266475f,
};

struct MenuBuildItemData g_earlierMenuItems_44FA80[3] = {
    { 0x0001, 0x0000, 0x30000000, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x00000387, (unsigned int)g_earlierMenuPaged_44029C, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0003, 0x0000, 0x00410021, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)&g_earlierMenuTuning_44FA50, (unsigned int)g_earlierMenuPaged_4407F8, (unsigned int)g_earlierMenuPaged_43E590, (unsigned int)g_earlierMenuPaged_43DB10, 0x00000000 },
    { 0x0000, 0x0000, 0x00010081, 0x0000, 0x0019, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800D362C, (unsigned int)g_earlierMenuPaged_442024, (unsigned int)g_earlierMenuPaged_43E588, (unsigned int)g_earlierMenuPaged_43E528, 0x00000000 },
};

struct MenuBuildDefinitionData g_earlierMenuDef_44FAEC = { (unsigned int)g_earlierMenuItems_44FA80, 0x0003, 0x0000, (unsigned int)g_earlierMenuPaged_43E4A0, 0x00000000, (unsigned int)g_earlierMenuPaged_4415B4, (unsigned int)g_earlierMenuPaged_43E4F0, 0x0001, 0x0000, 0x0000, 0x0000, 0x00000000 };

struct MenuBuildDefinitionData g_earlierMenuDef_44FB10 = { (unsigned int)g_earlierMenuItems_44FA80, 0x0003, 0x0000, (unsigned int)g_earlierMenuPaged_43E4C4, 0x00000000, (unsigned int)g_earlierMenuPaged_4415B4, (unsigned int)g_earlierMenuPaged_43E4F0, 0x0001, 0x0000, 0x0000, 0x0000, 0x00000000 };

struct MenuBuildItemData g_earlierMenuItems_44FB34[4] = {
    { 0x0001, 0x0000, 0x30000000, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x00000387, (unsigned int)g_earlierMenuPaged_44029C, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00010081, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800D3680, (unsigned int)g_earlierMenuPaged_442024, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00010101, 0x0000, 0x000C, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800D3684, (unsigned int)g_earlierMenuPaged_442024, 0x00000000, (unsigned int)g_earlierMenuPaged_43E5D0, 0x00000000 },
    { 0x0000, 0x0000, 0x00010101, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800D3688, (unsigned int)g_earlierMenuPaged_442024, 0x00000000, (unsigned int)g_earlierMenuPaged_43E618, 0x00000000 },
};

struct MenuBuildDefinitionData g_earlierMenuDef_44FBC4 = { (unsigned int)g_earlierMenuItems_44FB34, 0x0004, 0x0000, 0x00000000, 0x00000000, (unsigned int)g_earlierMenuPaged_4415B4, (unsigned int)g_earlierMenuPaged_43E598, 0x0002, 0x0000, 0x0000, 0x0000, 0x00000000 };

float g_earlierMenuRamp_44FBE8[16] = {
    -0.5f, -0.4f, -0.3f, -0.2f, -0.1f, 0.0f, 0.1f, 0.2f,
    0.3f, 0.4f, 0.5f, 0.6f, 0.7f, 0.8f, 0.9f, 1.0f,
};

struct MenuBuildItemData g_earlierMenuItems_44FC28[11] = {
    { 0x0001, 0x0000, 0x10000000, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x00000385, (unsigned int)g_earlierMenuPaged_44029C, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x08000201, 0x0000, 0x000C, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800D3D04, (unsigned int)g_earlierMenuPaged_442024, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00410041, 0x0000, 0x001E, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800D3DDC, (unsigned int)g_earlierMenuPaged_442024, (unsigned int)g_earlierMenuPaged_43DC64, (unsigned int)g_earlierMenuPaged_43E7F0, 0x00000000 },
    { 0x0000, 0x0000, 0x00410041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800D3DDC, (unsigned int)g_earlierMenuPaged_442024, (unsigned int)g_earlierMenuPaged_43DC64, (unsigned int)g_earlierMenuPaged_43E7F0, 0x00000000 },
    { 0x0000, 0x0000, 0x00410041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800D3DDC, (unsigned int)g_earlierMenuPaged_442024, (unsigned int)g_earlierMenuPaged_43DC64, (unsigned int)g_earlierMenuPaged_43E7F0, 0x00000000 },
    { 0x0000, 0x0000, 0x00410041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800D3DDC, (unsigned int)g_earlierMenuPaged_442024, (unsigned int)g_earlierMenuPaged_43DC64, (unsigned int)g_earlierMenuPaged_43E7F0, 0x00000000 },
    { 0x0000, 0x0000, 0x00410041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800D3DDC, (unsigned int)g_earlierMenuPaged_442024, (unsigned int)g_earlierMenuPaged_43DC64, (unsigned int)g_earlierMenuPaged_43E7F0, 0x00000000 },
    { 0x0000, 0x0000, 0x00410041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800D3DDC, (unsigned int)g_earlierMenuPaged_442024, (unsigned int)g_earlierMenuPaged_43DC64, (unsigned int)g_earlierMenuPaged_43E7F0, 0x00000000 },
    { 0x0000, 0x0000, 0x00410041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800D3DDC, (unsigned int)g_earlierMenuPaged_442024, (unsigned int)g_earlierMenuPaged_43DC64, (unsigned int)g_earlierMenuPaged_43E7F0, 0x00000000 },
    { 0x0000, 0x0000, 0x00410041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800D3DDC, (unsigned int)g_earlierMenuPaged_442024, (unsigned int)g_earlierMenuPaged_43DC64, (unsigned int)g_earlierMenuPaged_43E7F0, 0x00000000 },
    { 0x0000, 0x0000, 0x00010201, 0x0000, 0x002D, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800D3A7C, (unsigned int)g_earlierMenuPaged_442024, 0x00000000, (unsigned int)g_earlierMenuPaged_442344, 0x00000000 },
};

struct MenuBuildDefinitionData g_earlierMenuDef_44FDB4 = { (unsigned int)g_earlierMenuItems_44FC28, 0x000B, 0x0000, 0x00000000, 0x00000000, (unsigned int)g_earlierMenuPaged_4415B4, 0x00000000, 0x000A, 0x0000, 0x0000, 0x0000, (int)&g_earlierMenuDef_44FE68 };

struct MenuBuildItemData g_earlierMenuItems_44FDD8[4] = {
    { 0x0001, 0x0000, 0x10000000, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x00000385, (unsigned int)g_earlierMenuPaged_44029C, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x08000801, 0x0000, 0x0008, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800D3C58, (unsigned int)g_earlierMenuPaged_442024, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00010081, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800D3D04, (unsigned int)g_earlierMenuPaged_442024, 0x00000000, (unsigned int)g_earlierMenuPaged_43E8DC, 0x00000000 },
    { 0x0000, 0x0000, 0x00010201, 0x0000, 0x0038, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800D3A7C, (unsigned int)g_earlierMenuPaged_442024, 0x00000000, (unsigned int)g_earlierMenuPaged_442344, 0x00000000 },
};

struct MenuBuildDefinitionData g_earlierMenuDef_44FE68 = { (unsigned int)g_earlierMenuItems_44FDD8, 0x0004, 0x0000, 0x00000000, 0x00000000, (unsigned int)g_earlierMenuPaged_4415B4, 0x00000000, 0x0002, 0x0000, 0x0000, 0x0000, (int)&g_earlierMenuDef_4500CC };

struct MenuBuildItemData g_earlierMenuItems_44FE8C[5] = {
    { 0x0001, 0x0000, 0x10000000, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x00000385, (unsigned int)g_earlierMenuPaged_44029C, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x08000021, 0x0000, 0x0008, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800D3C48, (unsigned int)g_earlierMenuPaged_442024, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00010081, 0x0000, 0x0036, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800D3C4C, (unsigned int)g_earlierMenuPaged_442024, 0x00000000, (unsigned int)g_earlierMenuPaged_43E968, 0x00000000 },
    { 0x0000, 0x0000, 0x00010081, 0x0000, 0x0004, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800D3C50, (unsigned int)g_earlierMenuPaged_442024, 0x00000000, (unsigned int)g_earlierMenuPaged_43E9C0, 0x00000000 },
    { 0x0000, 0x0000, 0x00010201, 0x0000, 0x0049, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800D3624, (unsigned int)g_earlierMenuPaged_442024, 0x00000000, (unsigned int)g_earlierMenuPaged_43EA0C, 0x00000000 },
};

struct MenuBuildDefinitionData g_earlierMenuDef_44FF40 = { (unsigned int)g_earlierMenuItems_44FE8C, 0x0005, 0x0000, (unsigned int)g_earlierMenuPaged_43E908, 0x00000000, (unsigned int)g_earlierMenuPaged_4415B4, 0x00000000, 0x0002, 0x0000, 0x0000, 0x0000, 0x00000000 };

struct MenuBuildDefinitionData g_earlierMenuDef_44FF64 = { (unsigned int)g_earlierMenuItems_44FE8C, 0x0005, 0x0000, (unsigned int)g_earlierMenuPaged_43E93C, 0x00000000, (unsigned int)g_earlierMenuPaged_4415B4, 0x00000000, 0x0002, 0x0000, 0x0000, 0x0000, 0x00000000 };

struct MenuBuildItemData g_earlierMenuItems_44FF88[1] = {
    { 0x0001, 0x0000, 0x10000000, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x00000385, (unsigned int)g_earlierMenuPaged_44029C, 0x00000000, 0x00000000, 0x00000000 },
};

struct MenuBuildDefinitionData g_earlierMenuDef_44FFAC = { (unsigned int)g_earlierMenuItems_44FF88, 0x0001, 0x0000, 0x00000000, 0x00000000, (unsigned int)g_earlierMenuPaged_4415B4, 0x00000000, 0x0002, 0x0000, 0x0000, 0x0000, (int)&g_earlierMenuDef_4500CC };

struct MenuBuildItemData g_earlierMenuItems_44FFD0[7] = {
    { 0x0001, 0x0000, 0x10000000, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x00000384, (unsigned int)g_earlierMenuPaged_44029C, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00000081, 0x0000, 0x001E, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800D3C48, (unsigned int)g_earlierMenuPaged_442024, 0x00000000, (unsigned int)g_earlierMenuPaged_43EA58, 0x00000000 },
    { 0x0000, 0x0000, 0x00010081, 0x0000, 0x000C, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800D3C54, (unsigned int)g_earlierMenuPaged_442024, (unsigned int)g_earlierMenuPaged_43EB30, (unsigned int)g_earlierMenuPaged_43EBA4, 0x00000000 },
    { 0x0000, 0x0000, 0x00010081, 0x0000, 0x000C, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800D3A6C, (unsigned int)g_earlierMenuPaged_442024, 0x00000000, (unsigned int)g_earlierMenuPaged_43EC2C, 0x00000000 },
    { 0x0000, 0x0000, 0x00010081, 0x0000, 0x000C, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800D3D70, (unsigned int)g_earlierMenuPaged_442024, 0x00000000, (unsigned int)g_earlierMenuPaged_43EC58, 0x00000000 },
    { 0x0000, 0x0000, 0x00010081, 0x0000, 0x000C, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800D3D6C, (unsigned int)g_earlierMenuPaged_442024, 0x00000000, (unsigned int)g_earlierMenuPaged_43EC00, 0x00000000 },
    { 0x0000, 0x0000, 0x00010081, 0x0000, 0x000C, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800D3D7C, (unsigned int)g_earlierMenuPaged_442024, 0x00000000, (unsigned int)g_earlierMenuPaged_43EC84, 0x00000000 },
};

struct MenuBuildDefinitionData g_earlierMenuDef_4500CC = { (unsigned int)g_earlierMenuItems_44FFD0, 0x0007, 0x0000, 0x00000000, 0x00000000, (unsigned int)g_earlierMenuPaged_4415B4, 0x00000000, 0x0001, 0x0000, 0x0000, 0x0000, 0x00000000 };

struct MenuBuildItemData g_earlierMenuItems_4500F0[2] = {
    { 0x0001, 0x0000, 0x00000000, 0x0000, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x00000064, (unsigned int)g_earlierMenuPaged_44029C, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00000089, 0x0000, 0x0028, 0x00, 0x00, 0x00, 0x00, (int)g_earlierMenuResource_800D3F48, (unsigned int)g_earlierMenuPaged_442024, (unsigned int)g_earlierMenuPaged_43EDE4, 0x00000000, 0x00000000 },
};

struct MenuBuildDefinitionData g_earlierMenuDef_450138 = { (unsigned int)g_earlierMenuItems_4500F0, 0x0002, 0x0000, (unsigned int)g_earlierMenuPaged_43ED70, 0x00000000, (unsigned int)g_earlierMenuPaged_4415B4, (unsigned int)g_earlierMenuPaged_43ED9C, 0x0001, 0x0000, 0x0000, 0x0000, 0x00000000 };

#endif
