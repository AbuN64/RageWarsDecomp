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

extern char g_earlierMenuPaged221[];
extern char g_earlierMenuPaged222[];
extern char g_earlierMenuPaged225[];
extern char g_earlierMenuPaged227[];
extern char g_earlierMenuPaged233[];
extern char g_earlierMenuPaged234[];
extern char g_earlierMenuPaged237[];
extern char g_earlierMenuPaged238[];
extern char g_earlierMenuPaged241[];
extern char g_earlierMenuPaged246[];
extern char g_earlierMenuPaged247[];
extern char g_earlierMenuPaged249[];
extern char g_earlierMenuPaged251[];
extern char g_earlierMenuPaged252[];
extern char g_earlierMenuPaged255[];
extern char g_earlierMenuPaged256[];
extern char g_earlierMenuPaged257[];
extern char g_earlierMenuPaged260[];
extern char g_earlierMenuPaged261[];
extern char g_earlierMenuPaged263[];
extern char g_earlierMenuPaged264[];
extern char g_earlierMenuPaged266[];
extern char g_earlierMenuPaged268[];
extern char g_earlierMenuPaged276[];
extern char g_earlierMenuPaged281[];
extern char g_earlierMenuPaged282[];
extern char g_earlierMenuPaged283[];
extern char g_earlierMenuPaged286[];
extern char g_earlierMenuPaged287[];
extern char g_earlierMenuPaged290[];
extern char g_earlierMenuPaged292[];
extern char g_earlierMenuPaged293[];
extern char g_earlierMenuPaged294[];
extern char g_earlierMenuPaged295[];
extern char g_earlierMenuPaged296[];
extern char g_earlierMenuPaged297[];
extern char g_earlierMenuPaged298[];
extern char g_earlierMenuPaged299[];
extern char g_earlierMenuPaged300[];
extern char g_earlierMenuPaged301[];
extern char g_earlierMenuPaged345[];
extern char g_earlierMenuPaged346[];
extern char g_earlierMenuPaged348[];
extern char g_earlierMenuPaged350[];
extern char g_earlierMenuPaged352[];
extern char g_earlierMenuResource13[];
extern char g_earlierMenuResource14[];
extern char g_earlierMenuResource15[];
extern char g_earlierMenuResource16[];
extern char g_earlierMenuResource17[];
extern char g_earlierMenuResource18[];
extern char g_earlierMenuResource19[];
extern char g_earlierMenuResource20[];
extern char g_earlierMenuResource21[];
extern char g_earlierMenuResource22[];
extern char g_earlierMenuResource23[];
extern char g_earlierMenuResource24[];
extern char g_earlierMenuResource25[];
extern char g_earlierMenuResource26[];
extern char g_earlierMenuResource27[];
extern char g_earlierMenuResource28[];
extern char g_earlierMenuResource29[];
extern char g_earlierMenuResource75[];
extern char g_earlierMenuResource76[];
extern char g_earlierMenuResource78[];
extern char g_earlierMenuResource79[];
extern char g_earlierMenuResource80[];
extern char g_earlierMenuResource101[];
extern char g_earlierMenuResource102[];
extern char g_earlierMenuResource103[];
extern char g_earlierMenuResource104[];
extern char g_earlierMenuResource105[];
extern char g_earlierMenuResource106[];
extern char g_earlierMenuResource107[];
extern char g_earlierMenuResource108[];
extern char g_earlierMenuResource109[];
extern char g_earlierMenuResource114[];
extern char g_earlierMenuResource160[];
extern struct MenuBuildItemData g_earlierMenuItems10[3];
extern struct MenuBuildItemData g_earlierMenuItems12[9];
extern struct MenuBuildItemData g_earlierMenuItems13[5];
extern struct MenuBuildDefinitionData g_earlierMenuDef45;
extern struct EarlierMenuTuning g_earlierMenuTuning1;
extern struct MenuBuildItemData g_earlierMenuItems15[3];
extern struct MenuBuildDefinitionData g_earlierMenuDef47;
extern struct MenuBuildItemData g_earlierMenuItems16[4];
extern struct MenuBuildItemData g_earlierMenuItems18[11];
extern struct MenuBuildItemData g_earlierMenuItems19[4];
extern struct MenuBuildDefinitionData g_earlierMenuDef68;
extern struct MenuBuildItemData g_earlierMenuItems20[5];
extern struct MenuBuildItemData g_earlierMenuItems22[1];
extern struct MenuBuildItemData g_earlierMenuItems23[7];
extern struct MenuBuildDefinitionData g_earlierMenuDef76;
extern struct MenuBuildItemData g_earlierMenuItems25[2];

struct MenuBuildItemData g_earlierMenuItems10[3] = {
    { 0x0000, 0x0000, 0x00000021, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource80, (unsigned int)g_earlierMenuPaged350, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00010081, 0x0000, 0x0028, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource75, (unsigned int)g_earlierMenuPaged350, 0x00000000, (unsigned int)g_earlierMenuPaged221, 0x00000000 },
    { 0x0000, 0x0000, 0x00010081, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource76, (unsigned int)g_earlierMenuPaged350, 0x00000000, (unsigned int)g_earlierMenuPaged222, 0x00000000 },
};

struct MenuBuildDefinitionData g_earlierMenuDef42 = { (unsigned int)g_earlierMenuItems10, 0x0003, 0x0000, 0x00000000, 0x00000000, (unsigned int)g_earlierMenuPaged348, 0x00000000, 0x0001, 0x0000, 0x0000, 0x0000, 0x00000000 };

struct MenuBuildItemData g_earlierMenuItems12[9] = {
    { 0x0000, 0x0000, 0x00011001, 0x0000, 0x0000, 0x00, 0x00, 0x00, 0x00, (int)g_earlierMenuResource19, (unsigned int)g_earlierMenuPaged350, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00011001, 0x0000, 0x0000, 0x00, 0x00, 0x00, 0x00, (int)g_earlierMenuResource20, (unsigned int)g_earlierMenuPaged350, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00011001, 0x0000, 0x0000, 0x00, 0x00, 0x00, 0x00, (int)g_earlierMenuResource21, (unsigned int)g_earlierMenuPaged350, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00011001, 0x0000, 0x0000, 0x00, 0x00, 0x00, 0x00, (int)g_earlierMenuResource22, (unsigned int)g_earlierMenuPaged350, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00011001, 0x0000, 0x0000, 0x00, 0x00, 0x00, 0x00, (int)g_earlierMenuResource23, (unsigned int)g_earlierMenuPaged350, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00011001, 0x0000, 0x0000, 0x00, 0x00, 0x00, 0x00, (int)g_earlierMenuResource24, (unsigned int)g_earlierMenuPaged350, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00011001, 0x0000, 0x0000, 0x00, 0x00, 0x00, 0x00, (int)g_earlierMenuResource25, (unsigned int)g_earlierMenuPaged350, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00011001, 0x0000, 0x0000, 0x00, 0x00, 0x00, 0x00, (int)g_earlierMenuResource26, (unsigned int)g_earlierMenuPaged350, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0005, 0x00, 0x00, 0x00, 0x00, (int)g_earlierMenuResource18, (unsigned int)g_earlierMenuPaged350, 0x00000000, (unsigned int)g_earlierMenuPaged234, 0x00000000 },
};

struct MenuBuildDefinitionData g_earlierMenuDef43 = { (unsigned int)g_earlierMenuItems12, 0x0009, 0x0000, 0x00000000, 0x00000000, (unsigned int)g_earlierMenuPaged348, (unsigned int)g_earlierMenuPaged233, 0x0008, 0x0000, 0x0000, 0x0000, (intptr_t)&g_earlierMenuDef45 };

struct MenuBuildItemData g_earlierMenuItems13[5] = {
    { 0x0000, 0x0000, 0x00011001, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x02, (int)g_earlierMenuResource15, (unsigned int)g_earlierMenuPaged350, 0x00000000, (unsigned int)g_earlierMenuPaged247, 0x00000000 },
    { 0x0000, 0x0000, 0x00010101, 0x0000, 0x0008, 0x00, 0x00, 0x00, 0x00, (int)g_earlierMenuResource16, (unsigned int)g_earlierMenuPaged350, (unsigned int)g_earlierMenuPaged249, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00411001, 0x0000, 0x0008, 0x00, 0x00, 0xFE, 0x01, (int)g_earlierMenuResource114, (unsigned int)g_earlierMenuPaged350, (unsigned int)g_earlierMenuPaged241, (unsigned int)g_earlierMenuPaged238, 0x00000000 },
    { 0x0000, 0x0000, 0x00411001, 0x0000, 0x0002, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource17, (unsigned int)g_earlierMenuPaged350, (unsigned int)g_earlierMenuPaged252, (unsigned int)g_earlierMenuPaged246, 0x00000000 },
    { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0005, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource18, (unsigned int)g_earlierMenuPaged350, 0x00000000, (unsigned int)g_earlierMenuPaged251, 0x00000000 },
};

struct MenuBuildDefinitionData g_earlierMenuDef45 = { (unsigned int)g_earlierMenuItems13, 0x0005, 0x0000, 0x00000000, 0x00000000, (unsigned int)g_earlierMenuPaged348, (unsigned int)g_earlierMenuPaged237, 0x0004, 0x0000, 0x0000, 0x0000, (intptr_t)&g_earlierMenuDef47 };

struct EarlierMenuTuning g_earlierMenuTuning1 = {
    0x00000460, 0x0000000B, 0x00000000, 0x00000000,
    -5e+01f, -9e+02f,
    { 2.0f, 2.0f, 2.0f },
    0x00000032, 0x00000050,
    0.087266475f,
};

struct MenuBuildItemData g_earlierMenuItems15[3] = {
    { 0x0001, 0x0000, 0x30000000, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x00000387, (unsigned int)g_earlierMenuPaged345, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0003, 0x0000, 0x00410021, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (intptr_t)&g_earlierMenuTuning1, (unsigned int)g_earlierMenuPaged346, (unsigned int)g_earlierMenuPaged263, (unsigned int)g_earlierMenuPaged225, 0x00000000 },
    { 0x0000, 0x0000, 0x00010081, 0x0000, 0x0019, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource14, (unsigned int)g_earlierMenuPaged350, (unsigned int)g_earlierMenuPaged261, (unsigned int)g_earlierMenuPaged260, 0x00000000 },
};

struct MenuBuildDefinitionData g_earlierMenuDef47 = { (unsigned int)g_earlierMenuItems15, 0x0003, 0x0000, (unsigned int)g_earlierMenuPaged255, 0x00000000, (unsigned int)g_earlierMenuPaged348, (unsigned int)g_earlierMenuPaged257, 0x0001, 0x0000, 0x0000, 0x0000, 0x00000000 };

struct MenuBuildDefinitionData g_earlierMenuDef49 = { (unsigned int)g_earlierMenuItems15, 0x0003, 0x0000, (unsigned int)g_earlierMenuPaged256, 0x00000000, (unsigned int)g_earlierMenuPaged348, (unsigned int)g_earlierMenuPaged257, 0x0001, 0x0000, 0x0000, 0x0000, 0x00000000 };

struct MenuBuildItemData g_earlierMenuItems16[4] = {
    { 0x0001, 0x0000, 0x30000000, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x00000387, (unsigned int)g_earlierMenuPaged345, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00010081, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource27, (unsigned int)g_earlierMenuPaged350, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00010101, 0x0000, 0x000C, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource28, (unsigned int)g_earlierMenuPaged350, 0x00000000, (unsigned int)g_earlierMenuPaged266, 0x00000000 },
    { 0x0000, 0x0000, 0x00010101, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource29, (unsigned int)g_earlierMenuPaged350, 0x00000000, (unsigned int)g_earlierMenuPaged268, 0x00000000 },
};

struct MenuBuildDefinitionData g_earlierMenuDef51 = { (unsigned int)g_earlierMenuItems16, 0x0004, 0x0000, 0x00000000, 0x00000000, (unsigned int)g_earlierMenuPaged348, (unsigned int)g_earlierMenuPaged264, 0x0002, 0x0000, 0x0000, 0x0000, 0x00000000 };

float g_earlierMenuRamp1[16] = {
    -0.5f, -0.4f, -0.3f, -0.2f, -0.1f, 0.0f, 0.1f, 0.2f,
    0.3f, 0.4f, 0.5f, 0.6f, 0.7f, 0.8f, 0.9f, 1.0f,
};

struct MenuBuildItemData g_earlierMenuItems18[11] = {
    { 0x0001, 0x0000, 0x10000000, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x00000385, (unsigned int)g_earlierMenuPaged345, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x08000201, 0x0000, 0x000C, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource106, (unsigned int)g_earlierMenuPaged350, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00410041, 0x0000, 0x001E, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource114, (unsigned int)g_earlierMenuPaged350, (unsigned int)g_earlierMenuPaged227, (unsigned int)g_earlierMenuPaged276, 0x00000000 },
    { 0x0000, 0x0000, 0x00410041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource114, (unsigned int)g_earlierMenuPaged350, (unsigned int)g_earlierMenuPaged227, (unsigned int)g_earlierMenuPaged276, 0x00000000 },
    { 0x0000, 0x0000, 0x00410041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource114, (unsigned int)g_earlierMenuPaged350, (unsigned int)g_earlierMenuPaged227, (unsigned int)g_earlierMenuPaged276, 0x00000000 },
    { 0x0000, 0x0000, 0x00410041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource114, (unsigned int)g_earlierMenuPaged350, (unsigned int)g_earlierMenuPaged227, (unsigned int)g_earlierMenuPaged276, 0x00000000 },
    { 0x0000, 0x0000, 0x00410041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource114, (unsigned int)g_earlierMenuPaged350, (unsigned int)g_earlierMenuPaged227, (unsigned int)g_earlierMenuPaged276, 0x00000000 },
    { 0x0000, 0x0000, 0x00410041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource114, (unsigned int)g_earlierMenuPaged350, (unsigned int)g_earlierMenuPaged227, (unsigned int)g_earlierMenuPaged276, 0x00000000 },
    { 0x0000, 0x0000, 0x00410041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource114, (unsigned int)g_earlierMenuPaged350, (unsigned int)g_earlierMenuPaged227, (unsigned int)g_earlierMenuPaged276, 0x00000000 },
    { 0x0000, 0x0000, 0x00410041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource114, (unsigned int)g_earlierMenuPaged350, (unsigned int)g_earlierMenuPaged227, (unsigned int)g_earlierMenuPaged276, 0x00000000 },
    { 0x0000, 0x0000, 0x00010201, 0x0000, 0x002D, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource79, (unsigned int)g_earlierMenuPaged350, 0x00000000, (unsigned int)g_earlierMenuPaged352, 0x00000000 },
};

struct MenuBuildDefinitionData g_earlierMenuDef62 = { (unsigned int)g_earlierMenuItems18, 0x000B, 0x0000, 0x00000000, 0x00000000, (unsigned int)g_earlierMenuPaged348, 0x00000000, 0x000A, 0x0000, 0x0000, 0x0000, (intptr_t)&g_earlierMenuDef68 };

struct MenuBuildItemData g_earlierMenuItems19[4] = {
    { 0x0001, 0x0000, 0x10000000, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x00000385, (unsigned int)g_earlierMenuPaged345, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x08000801, 0x0000, 0x0008, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource105, (unsigned int)g_earlierMenuPaged350, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00010081, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource106, (unsigned int)g_earlierMenuPaged350, 0x00000000, (unsigned int)g_earlierMenuPaged281, 0x00000000 },
    { 0x0000, 0x0000, 0x00010201, 0x0000, 0x0038, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource79, (unsigned int)g_earlierMenuPaged350, 0x00000000, (unsigned int)g_earlierMenuPaged352, 0x00000000 },
};

struct MenuBuildDefinitionData g_earlierMenuDef68 = { (unsigned int)g_earlierMenuItems19, 0x0004, 0x0000, 0x00000000, 0x00000000, (unsigned int)g_earlierMenuPaged348, 0x00000000, 0x0002, 0x0000, 0x0000, 0x0000, (intptr_t)&g_earlierMenuDef76 };

struct MenuBuildItemData g_earlierMenuItems20[5] = {
    { 0x0001, 0x0000, 0x10000000, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x00000385, (unsigned int)g_earlierMenuPaged345, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x08000021, 0x0000, 0x0008, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource101, (unsigned int)g_earlierMenuPaged350, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00010081, 0x0000, 0x0036, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource102, (unsigned int)g_earlierMenuPaged350, 0x00000000, (unsigned int)g_earlierMenuPaged286, 0x00000000 },
    { 0x0000, 0x0000, 0x00010081, 0x0000, 0x0004, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource103, (unsigned int)g_earlierMenuPaged350, 0x00000000, (unsigned int)g_earlierMenuPaged287, 0x00000000 },
    { 0x0000, 0x0000, 0x00010201, 0x0000, 0x0049, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource13, (unsigned int)g_earlierMenuPaged350, 0x00000000, (unsigned int)g_earlierMenuPaged290, 0x00000000 },
};

struct MenuBuildDefinitionData g_earlierMenuDef71 = { (unsigned int)g_earlierMenuItems20, 0x0005, 0x0000, (unsigned int)g_earlierMenuPaged282, 0x00000000, (unsigned int)g_earlierMenuPaged348, 0x00000000, 0x0002, 0x0000, 0x0000, 0x0000, 0x00000000 };

struct MenuBuildDefinitionData g_earlierMenuDef72 = { (unsigned int)g_earlierMenuItems20, 0x0005, 0x0000, (unsigned int)g_earlierMenuPaged283, 0x00000000, (unsigned int)g_earlierMenuPaged348, 0x00000000, 0x0002, 0x0000, 0x0000, 0x0000, 0x00000000 };

struct MenuBuildItemData g_earlierMenuItems22[1] = {
    { 0x0001, 0x0000, 0x10000000, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x00000385, (unsigned int)g_earlierMenuPaged345, 0x00000000, 0x00000000, 0x00000000 },
};

struct MenuBuildDefinitionData g_earlierMenuDef73 = { (unsigned int)g_earlierMenuItems22, 0x0001, 0x0000, 0x00000000, 0x00000000, (unsigned int)g_earlierMenuPaged348, 0x00000000, 0x0002, 0x0000, 0x0000, 0x0000, (intptr_t)&g_earlierMenuDef76 };

struct MenuBuildItemData g_earlierMenuItems23[7] = {
    { 0x0001, 0x0000, 0x10000000, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x00000384, (unsigned int)g_earlierMenuPaged345, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00000081, 0x0000, 0x001E, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource101, (unsigned int)g_earlierMenuPaged350, 0x00000000, (unsigned int)g_earlierMenuPaged292, 0x00000000 },
    { 0x0000, 0x0000, 0x00010081, 0x0000, 0x000C, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource104, (unsigned int)g_earlierMenuPaged350, (unsigned int)g_earlierMenuPaged293, (unsigned int)g_earlierMenuPaged294, 0x00000000 },
    { 0x0000, 0x0000, 0x00010081, 0x0000, 0x000C, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource78, (unsigned int)g_earlierMenuPaged350, 0x00000000, (unsigned int)g_earlierMenuPaged296, 0x00000000 },
    { 0x0000, 0x0000, 0x00010081, 0x0000, 0x000C, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource108, (unsigned int)g_earlierMenuPaged350, 0x00000000, (unsigned int)g_earlierMenuPaged297, 0x00000000 },
    { 0x0000, 0x0000, 0x00010081, 0x0000, 0x000C, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource107, (unsigned int)g_earlierMenuPaged350, 0x00000000, (unsigned int)g_earlierMenuPaged295, 0x00000000 },
    { 0x0000, 0x0000, 0x00010081, 0x0000, 0x000C, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource109, (unsigned int)g_earlierMenuPaged350, 0x00000000, (unsigned int)g_earlierMenuPaged298, 0x00000000 },
};

struct MenuBuildDefinitionData g_earlierMenuDef76 = { (unsigned int)g_earlierMenuItems23, 0x0007, 0x0000, 0x00000000, 0x00000000, (unsigned int)g_earlierMenuPaged348, 0x00000000, 0x0001, 0x0000, 0x0000, 0x0000, 0x00000000 };

struct MenuBuildItemData g_earlierMenuItems25[2] = {
    { 0x0001, 0x0000, 0x00000000, 0x0000, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x00000064, (unsigned int)g_earlierMenuPaged345, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00000089, 0x0000, 0x0028, 0x00, 0x00, 0x00, 0x00, (int)g_earlierMenuResource160, (unsigned int)g_earlierMenuPaged350, (unsigned int)g_earlierMenuPaged301, 0x00000000, 0x00000000 },
};

struct MenuBuildDefinitionData g_earlierMenuDef77 = { (unsigned int)g_earlierMenuItems25, 0x0002, 0x0000, (unsigned int)g_earlierMenuPaged299, 0x00000000, (unsigned int)g_earlierMenuPaged348, (unsigned int)g_earlierMenuPaged300, 0x0001, 0x0000, 0x0000, 0x0000, 0x00000000 };

#endif
