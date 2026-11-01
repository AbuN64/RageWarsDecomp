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

extern char g_earlierMenuPaged_43C510[];
extern char g_earlierMenuPaged_43C648[];
extern char g_earlierMenuPaged_43C958[];
extern char g_earlierMenuPaged_43C96C[];
extern char g_earlierMenuPaged_43CAF0[];
extern char g_earlierMenuPaged_43CBC8[];
extern char g_earlierMenuPaged_43CBD0[];
extern char g_earlierMenuPaged_43CC90[];
extern char g_earlierMenuPaged_43CDB8[];
extern char g_earlierMenuPaged_43CF04[];
extern char g_earlierMenuPaged_43D0B0[];
extern char g_earlierMenuPaged_43D21C[];
extern char g_earlierMenuPaged_43D238[];
extern char g_earlierMenuPaged_43D2A4[];
extern char g_earlierMenuPaged_43D2C0[];
extern char g_earlierMenuPaged_43D32C[];
extern char g_earlierMenuPaged_43D348[];
extern char g_earlierMenuPaged_43D3B4[];
extern char g_earlierMenuPaged_43D3D0[];
extern char g_earlierMenuPaged_43D43C[];
extern char g_earlierMenuPaged_43D458[];
extern char g_earlierMenuPaged_43D4C4[];
extern char g_earlierMenuPaged_43D4E0[];
extern char g_earlierMenuPaged_43D54C[];
extern char g_earlierMenuPaged_43D568[];
extern char g_earlierMenuPaged_43D5D4[];
extern char g_earlierMenuPaged_43D5F0[];
extern char g_earlierMenuPaged_43D65C[];
extern char g_earlierMenuPaged_43D678[];
extern char g_earlierMenuPaged_43D6E4[];
extern char g_earlierMenuPaged_43D700[];
extern char g_earlierMenuPaged_43D76C[];
extern char g_earlierMenuPaged_43D788[];
extern char g_earlierMenuPaged_43D7F4[];
extern char g_earlierMenuPaged_43D810[];
extern char g_earlierMenuPaged_43D87C[];
extern char g_earlierMenuPaged_43D898[];
extern char g_earlierMenuPaged_43D904[];
extern char g_earlierMenuPaged_43D920[];
extern char g_earlierMenuPaged_43D98C[];
extern char g_earlierMenuPaged_43D9A8[];
extern char g_earlierMenuPaged_43DA14[];
extern char g_earlierMenuPaged_43DA30[];
extern char g_earlierMenuPaged_44029C[];
extern char g_earlierMenuPaged_4415B4[];
extern char g_earlierMenuPaged_442024[];
extern char g_earlierMenuPaged_44204C[];
extern char g_earlierMenuPaged_442344[];
extern char g_earlierMenuResource_800D3A60[];
extern char g_earlierMenuResource_800D3A6C[];
extern char g_earlierMenuResource_800D3A7C[];
extern char g_earlierMenuResource_800D3B04[];
extern char g_earlierMenuResource_800D3B0C[];
extern char g_earlierMenuResource_800D3B14[];
extern char g_earlierMenuResource_800D3B1C[];
extern char g_earlierMenuResource_800D3B24[];
extern char g_earlierMenuResource_800D3B2C[];
extern char g_earlierMenuResource_800D3B34[];
extern char g_earlierMenuResource_800D3B3C[];
extern char g_earlierMenuResource_800D3B44[];
extern char g_earlierMenuResource_800D3B4C[];
extern char g_earlierMenuResource_800D3B54[];
extern char g_earlierMenuResource_800D3B5C[];
extern char g_earlierMenuResource_800D3B64[];
extern char g_earlierMenuResource_800D3B6C[];
extern char g_earlierMenuResource_800D3B74[];
extern char g_earlierMenuResource_800D3B7C[];
extern char g_earlierMenuResource_800D3DDC[];
extern char g_earlierMenuResource_800D3E10[];
extern char g_earlierMenuResource_800D3E18[];
extern char g_earlierMenuResource_800D3E20[];
extern char g_earlierMenuResource_800D3E28[];
extern char g_earlierMenuResource_800D3E30[];
extern char g_earlierMenuResource_800D3E38[];
extern char g_earlierMenuResource_800D3E40[];
extern char g_earlierMenuResource_800D3E48[];
extern char g_earlierMenuResource_800D3E50[];
extern char g_earlierMenuResource_800D3E58[];
extern char g_earlierMenuResource_800D3E60[];
extern char g_earlierMenuResource_800D3E68[];
extern char g_earlierMenuResource_800D3E70[];
extern char g_earlierMenuResource_800D3E78[];
extern char g_earlierMenuResource_800D3E80[];
extern char g_earlierMenuResource_800D3E88[];
extern char g_earlierMenuResource_800D3E90[];
extern char g_earlierMenuResource_800D3E98[];
extern char g_earlierMenuResource_800D3EA0[];
extern char g_earlierMenuResource_800D3EA8[];
extern char g_earlierMenuResource_800D3EB0[];
extern char g_earlierMenuResource_800D3EB8[];
extern char g_earlierMenuResource_800D3EC0[];
extern char g_earlierMenuResource_800D3EC8[];
extern char g_earlierMenuResource_800D3ED0[];
extern char g_earlierMenuResource_800D3ED8[];
extern char g_earlierMenuResource_800D3F38[];
extern char g_earlierMenuResource_800D3F40[];
extern char g_earlierMenuResource_800E1C64[];
extern char g_earlierOptionName_800D3AA8[];
extern char g_earlierOptionName_800D3AAC[];
extern char g_earlierOptionName_800D3AB0[];
extern char g_earlierOptionName_800D3AB4[];
extern char g_earlierOptionName_800D3AB8[];
extern char g_earlierOptionName_800D3ABC[];
extern char g_earlierOptionName_800D3AC0[];
extern char g_earlierOptionName_800D3AC4[];
extern char g_earlierOptionName_800D3ACC[];
extern char g_earlierOptionName_800D3AD0[];
extern char g_earlierOptionName_800E1C7C[];
extern char g_earlierOptionName_800E1C98[];
extern char g_earlierOptionWord_800DE0D0[];
extern char g_earlierOptionWord_800DE0E4[];
extern char g_earlierOptionWord_800DE0FC[];
extern char g_earlierOptionWord_800DE108[];
extern char g_earlierOptionWord_800DE114[];
extern char g_earlierOptionWord_800DE11C[];
extern char g_earlierOptionWord_800DE128[];
extern char g_earlierOptionWord_800DE13C[];
extern char g_earlierOptionWord_800DE148[];
extern char g_earlierOptionWord_800DE154[];
extern char g_earlierOptionWord_800DE15C[];
extern char g_earlierOptionWord_800DE16C[];
extern struct MenuBuildItemData g_earlierMenuItems_44EFC0[33];
extern struct MenuBuildItemData g_earlierMenuItems_44F488[20];

struct EarlierOptionBitRow g_earlierOptionBits_44EF00[12] = {
    { g_earlierOptionWord_800DE16C, g_earlierOptionName_800D3AA8, 0x00000020, 0x00000001 },
    { g_earlierOptionWord_800DE15C, g_earlierOptionName_800D3AB0, 0x00000080, 0x00000001 },
    { g_earlierOptionWord_800DE154, g_earlierOptionName_800D3AB4, 0x00000100, 0x00000001 },
    { g_earlierOptionWord_800DE148, g_earlierOptionName_800D3AAC, 0x00000040, 0x00000001 },
    { g_earlierOptionWord_800DE13C, g_earlierOptionName_800D3AB8, 0x00000200, 0x00000001 },
    { g_earlierOptionWord_800DE128, g_earlierOptionName_800D3ABC, 0x00000400, 0x00000001 },
    { g_earlierOptionWord_800DE11C, g_earlierOptionName_800D3AC0, 0x00000800, 0x00000001 },
    { g_earlierOptionWord_800DE114, g_earlierOptionName_800D3AC4, 0x00001000, 0x00000001 },
    { g_earlierOptionWord_800DE108, g_earlierOptionName_800D3ACC, 0x00004000, 0x00000001 },
    { g_earlierOptionWord_800DE0FC, g_earlierOptionName_800D3AD0, 0x00008000, 0x00000001 },
    { g_earlierOptionWord_800DE0E4, g_earlierOptionName_800E1C7C, 0xFFFFFFFF, 0x00000001 },
    { g_earlierOptionWord_800DE0D0, g_earlierOptionName_800E1C98, 0x0400C7E0, 0x00000001 },
};

struct MenuBuildItemData g_earlierMenuItems_44EFC0[33] = {
    { 0x0001, 0x0000, 0x50000000, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x00000385, (unsigned int)g_earlierMenuPaged_44029C, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x08000801, 0x0000, 0x0008, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800D3A6C, (unsigned int)g_earlierMenuPaged_442024, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00210041, 0x0000, 0x0014, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800E1C64, (unsigned int)g_earlierMenuPaged_43C96C, (unsigned int)g_earlierMenuPaged_43CAF0, (unsigned int)g_earlierMenuPaged_43CBC8, 0x00000000 },
    { 0x0000, 0x0000, 0x00010050, 0x0058, 0x0014, 0x06, 0x01, 0xFF, 0x07, (int)g_earlierMenuResource_800D3E10, (unsigned int)g_earlierMenuPaged_44204C, 0x00000000, (unsigned int)g_earlierMenuPaged_43CBD0, 0x00000000 },
    { 0x0000, 0x0000, 0x00024050, 0x0008, 0x0000, 0xFF, 0x01, 0xFE, 0x07, (int)g_earlierMenuResource_800D3E18, (unsigned int)g_earlierMenuPaged_44204C, 0x00000000, (unsigned int)g_earlierMenuPaged_43CBD0, 0x00000000 },
    { 0x0000, 0x0000, 0x00024050, 0x0008, 0x0000, 0xFF, 0x01, 0xFD, 0x07, (int)g_earlierMenuResource_800D3E20, (unsigned int)g_earlierMenuPaged_44204C, 0x00000000, (unsigned int)g_earlierMenuPaged_43CBD0, 0x00000000 },
    { 0x0000, 0x0000, 0x00024050, 0x0008, 0x0000, 0xFF, 0x01, 0xFC, 0x07, (int)g_earlierMenuResource_800D3E28, (unsigned int)g_earlierMenuPaged_44204C, 0x00000000, (unsigned int)g_earlierMenuPaged_43CBD0, 0x00000000 },
    { 0x0000, 0x0000, 0x00024050, 0x0008, 0x0000, 0xFF, 0x01, 0xFB, 0x07, (int)g_earlierMenuResource_800D3E30, (unsigned int)g_earlierMenuPaged_44204C, 0x00000000, (unsigned int)g_earlierMenuPaged_43CBD0, 0x00000000 },
    { 0x0000, 0x0000, 0x00024050, 0x0008, 0x0000, 0xFF, 0x01, 0xFA, 0x07, (int)g_earlierMenuResource_800D3E38, (unsigned int)g_earlierMenuPaged_44204C, 0x00000000, (unsigned int)g_earlierMenuPaged_43CBD0, 0x00000000 },
    { 0x0000, 0x0000, 0x00024050, 0x0008, 0x0000, 0xFF, 0xFA, 0xF9, 0x07, (int)g_earlierMenuResource_800D3E40, (unsigned int)g_earlierMenuPaged_44204C, 0x00000000, (unsigned int)g_earlierMenuPaged_43CBD0, 0x00000000 },
    { 0x0000, 0x0000, 0x00010050, 0x0058, 0x0008, 0x06, 0x01, 0xF9, 0x07, (int)g_earlierMenuResource_800D3E48, (unsigned int)g_earlierMenuPaged_44204C, 0x00000000, (unsigned int)g_earlierMenuPaged_43CBD0, 0x00000000 },
    { 0x0000, 0x0000, 0x00024050, 0x0008, 0x0000, 0xFF, 0x01, 0xF9, 0x07, (int)g_earlierMenuResource_800D3E50, (unsigned int)g_earlierMenuPaged_44204C, 0x00000000, (unsigned int)g_earlierMenuPaged_43CBD0, 0x00000000 },
    { 0x0000, 0x0000, 0x00024050, 0x0008, 0x0000, 0xFF, 0x01, 0xF9, 0x07, (int)g_earlierMenuResource_800D3E58, (unsigned int)g_earlierMenuPaged_44204C, 0x00000000, (unsigned int)g_earlierMenuPaged_43CBD0, 0x00000000 },
    { 0x0000, 0x0000, 0x00024050, 0x0008, 0x0000, 0xFF, 0x01, 0xF9, 0x07, (int)g_earlierMenuResource_800D3E60, (unsigned int)g_earlierMenuPaged_44204C, 0x00000000, (unsigned int)g_earlierMenuPaged_43CBD0, 0x00000000 },
    { 0x0000, 0x0000, 0x00024050, 0x0008, 0x0000, 0xFF, 0x01, 0xF9, 0x07, (int)g_earlierMenuResource_800D3E68, (unsigned int)g_earlierMenuPaged_44204C, 0x00000000, (unsigned int)g_earlierMenuPaged_43CBD0, 0x00000000 },
    { 0x0000, 0x0000, 0x00024050, 0x0008, 0x0000, 0xFF, 0x01, 0xF9, 0x07, (int)g_earlierMenuResource_800D3E70, (unsigned int)g_earlierMenuPaged_44204C, 0x00000000, (unsigned int)g_earlierMenuPaged_43CBD0, 0x00000000 },
    { 0x0000, 0x0000, 0x00024050, 0x0008, 0x0000, 0xFF, 0xFA, 0xF9, 0x07, (int)g_earlierMenuResource_800D3E78, (unsigned int)g_earlierMenuPaged_44204C, 0x00000000, (unsigned int)g_earlierMenuPaged_43CBD0, 0x00000000 },
    { 0x0000, 0x0000, 0x00010050, 0x0058, 0x0008, 0x06, 0x01, 0xF9, 0x07, (int)g_earlierMenuResource_800D3E80, (unsigned int)g_earlierMenuPaged_44204C, 0x00000000, (unsigned int)g_earlierMenuPaged_43CBD0, 0x00000000 },
    { 0x0000, 0x0000, 0x00024050, 0x0008, 0x0000, 0xFF, 0x01, 0xF9, 0x07, (int)g_earlierMenuResource_800D3E88, (unsigned int)g_earlierMenuPaged_44204C, 0x00000000, (unsigned int)g_earlierMenuPaged_43CBD0, 0x00000000 },
    { 0x0000, 0x0000, 0x00024050, 0x0008, 0x0000, 0xFF, 0x01, 0xF9, 0x07, (int)g_earlierMenuResource_800D3E90, (unsigned int)g_earlierMenuPaged_44204C, 0x00000000, (unsigned int)g_earlierMenuPaged_43CBD0, 0x00000000 },
    { 0x0000, 0x0000, 0x00024050, 0x0008, 0x0000, 0xFF, 0x01, 0xF9, 0x07, (int)g_earlierMenuResource_800D3E98, (unsigned int)g_earlierMenuPaged_44204C, 0x00000000, (unsigned int)g_earlierMenuPaged_43CBD0, 0x00000000 },
    { 0x0000, 0x0000, 0x00024050, 0x0008, 0x0000, 0xFF, 0x01, 0xF9, 0x07, (int)g_earlierMenuResource_800D3EA0, (unsigned int)g_earlierMenuPaged_44204C, 0x00000000, (unsigned int)g_earlierMenuPaged_43CBD0, 0x00000000 },
    { 0x0000, 0x0000, 0x00024050, 0x0008, 0x0000, 0xFF, 0x01, 0xF9, 0x07, (int)g_earlierMenuResource_800D3EA8, (unsigned int)g_earlierMenuPaged_44204C, 0x00000000, (unsigned int)g_earlierMenuPaged_43CBD0, 0x00000000 },
    { 0x0000, 0x0000, 0x00024050, 0x0008, 0x0000, 0xFF, 0xFA, 0xF9, 0x07, (int)g_earlierMenuResource_800D3EB0, (unsigned int)g_earlierMenuPaged_44204C, 0x00000000, (unsigned int)g_earlierMenuPaged_43CBD0, 0x00000000 },
    { 0x0000, 0x0000, 0x00010050, 0x0058, 0x0008, 0x06, 0x01, 0xF9, 0x08, (int)g_earlierMenuResource_800D3EB8, (unsigned int)g_earlierMenuPaged_44204C, 0x00000000, (unsigned int)g_earlierMenuPaged_43CBD0, 0x00000000 },
    { 0x0000, 0x0000, 0x00024050, 0x0008, 0x0000, 0xFF, 0x01, 0xF9, 0x07, (int)g_earlierMenuResource_800D3EC0, (unsigned int)g_earlierMenuPaged_44204C, 0x00000000, (unsigned int)g_earlierMenuPaged_43CBD0, 0x00000000 },
    { 0x0000, 0x0000, 0x00024050, 0x0008, 0x0000, 0xFF, 0x01, 0xF9, 0x06, (int)g_earlierMenuResource_800D3EC8, (unsigned int)g_earlierMenuPaged_44204C, 0x00000000, (unsigned int)g_earlierMenuPaged_43CBD0, 0x00000000 },
    { 0x0000, 0x0000, 0x00024050, 0x0008, 0x0000, 0xFF, 0x01, 0xF9, 0x05, (int)g_earlierMenuResource_800D3ED0, (unsigned int)g_earlierMenuPaged_44204C, 0x00000000, (unsigned int)g_earlierMenuPaged_43CBD0, 0x00000000 },
    { 0x0000, 0x0000, 0x00024050, 0x0008, 0x0000, 0xFF, 0x01, 0xF9, 0x04, (int)g_earlierMenuResource_800D3ED8, (unsigned int)g_earlierMenuPaged_44204C, 0x00000000, (unsigned int)g_earlierMenuPaged_43CBD0, 0x00000000 },
    { 0x0000, 0x0000, 0x00024050, 0x0008, 0x0000, 0xFF, 0x01, 0xF9, 0x03, (int)g_earlierMenuResource_800D3F38, (unsigned int)g_earlierMenuPaged_44204C, 0x00000000, (unsigned int)g_earlierMenuPaged_43CC90, 0x00000000 },
    { 0x0000, 0x0000, 0x00024050, 0x0008, 0x0000, 0xFF, 0xFA, 0xF9, 0x02, (int)g_earlierMenuResource_800D3F40, (unsigned int)g_earlierMenuPaged_44204C, 0x00000000, (unsigned int)g_earlierMenuPaged_43CDB8, 0x00000000 },
    { 0x0000, 0x0000, 0x00011001, 0x0000, 0x0014, 0x00, 0x00, 0x00, 0x00, (int)g_earlierMenuResource_800D3DDC, (unsigned int)g_earlierMenuPaged_442024, (unsigned int)g_earlierMenuPaged_43CF04, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00310201, 0x0000, 0x0018, 0x00, 0x00, 0xFE, 0xE2, (int)g_earlierMenuResource_800D3A7C, (unsigned int)g_earlierMenuPaged_442024, 0x00000000, (unsigned int)g_earlierMenuPaged_442344, 0x00000000 },
};

struct MenuBuildDefinitionData g_earlierMenuDef_44F464 = { (unsigned int)g_earlierMenuItems_44EFC0, 0x0021, 0x0000, (unsigned int)g_earlierMenuPaged_43C958, 0x00000000, (unsigned int)g_earlierMenuPaged_4415B4, 0x00000000, 0x0002, 0x0000, 0x0000, 0x0000, 0x00000000 };

struct MenuBuildItemData g_earlierMenuItems_44F488[20] = {
    { 0x0001, 0x0000, 0x50000000, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x00000385, (unsigned int)g_earlierMenuPaged_44029C, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x08000801, 0x0000, 0x0008, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800D3A60, (unsigned int)g_earlierMenuPaged_442024, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00411001, 0x0000, 0x000C, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800D3B04, (unsigned int)g_earlierMenuPaged_442024, (unsigned int)g_earlierMenuPaged_43D238, (unsigned int)g_earlierMenuPaged_43D21C, 0x00000000 },
    { 0x0000, 0x0000, 0x00411001, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800D3B0C, (unsigned int)g_earlierMenuPaged_442024, (unsigned int)g_earlierMenuPaged_43D2C0, (unsigned int)g_earlierMenuPaged_43D2A4, 0x00000000 },
    { 0x0000, 0x0000, 0x00411001, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800D3B14, (unsigned int)g_earlierMenuPaged_442024, (unsigned int)g_earlierMenuPaged_43D348, (unsigned int)g_earlierMenuPaged_43D32C, 0x00000000 },
    { 0x0000, 0x0000, 0x00411001, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800D3B1C, (unsigned int)g_earlierMenuPaged_442024, (unsigned int)g_earlierMenuPaged_43D3D0, (unsigned int)g_earlierMenuPaged_43D3B4, 0x00000000 },
    { 0x0000, 0x0000, 0x00411001, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800D3B24, (unsigned int)g_earlierMenuPaged_442024, (unsigned int)g_earlierMenuPaged_43D458, (unsigned int)g_earlierMenuPaged_43D43C, 0x00000000 },
    { 0x0000, 0x0000, 0x00411001, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800D3B2C, (unsigned int)g_earlierMenuPaged_442024, (unsigned int)g_earlierMenuPaged_43D4E0, (unsigned int)g_earlierMenuPaged_43D4C4, 0x00000000 },
    { 0x0000, 0x0000, 0x00411001, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800D3B34, (unsigned int)g_earlierMenuPaged_442024, (unsigned int)g_earlierMenuPaged_43D568, (unsigned int)g_earlierMenuPaged_43D54C, 0x00000000 },
    { 0x0000, 0x0000, 0x00411001, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800D3B44, (unsigned int)g_earlierMenuPaged_442024, (unsigned int)g_earlierMenuPaged_43D678, (unsigned int)g_earlierMenuPaged_43D65C, 0x00000000 },
    { 0x0000, 0x0000, 0x00411001, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800D3B3C, (unsigned int)g_earlierMenuPaged_442024, (unsigned int)g_earlierMenuPaged_43D5F0, (unsigned int)g_earlierMenuPaged_43D5D4, 0x00000000 },
    { 0x0000, 0x0000, 0x00411001, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800D3B4C, (unsigned int)g_earlierMenuPaged_442024, (unsigned int)g_earlierMenuPaged_43D700, (unsigned int)g_earlierMenuPaged_43D6E4, 0x00000000 },
    { 0x0000, 0x0000, 0x00411001, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800D3B54, (unsigned int)g_earlierMenuPaged_442024, (unsigned int)g_earlierMenuPaged_43D788, (unsigned int)g_earlierMenuPaged_43D76C, 0x00000000 },
    { 0x0000, 0x0000, 0x00411001, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800D3B5C, (unsigned int)g_earlierMenuPaged_442024, (unsigned int)g_earlierMenuPaged_43D810, (unsigned int)g_earlierMenuPaged_43D7F4, 0x00000000 },
    { 0x0000, 0x0000, 0x00411001, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800D3B64, (unsigned int)g_earlierMenuPaged_442024, (unsigned int)g_earlierMenuPaged_43D898, (unsigned int)g_earlierMenuPaged_43D87C, 0x00000000 },
    { 0x0000, 0x0000, 0x00411001, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800D3B6C, (unsigned int)g_earlierMenuPaged_442024, (unsigned int)g_earlierMenuPaged_43D920, (unsigned int)g_earlierMenuPaged_43D904, 0x00000000 },
    { 0x0000, 0x0000, 0x00411001, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800D3B74, (unsigned int)g_earlierMenuPaged_442024, (unsigned int)g_earlierMenuPaged_43D9A8, (unsigned int)g_earlierMenuPaged_43D98C, 0x00000000 },
    { 0x0000, 0x0000, 0x00411001, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800D3B7C, (unsigned int)g_earlierMenuPaged_442024, (unsigned int)g_earlierMenuPaged_43DA30, (unsigned int)g_earlierMenuPaged_43DA14, 0x00000000 },
    { 0x0000, 0x0000, 0x00411001, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800D3DDC, (unsigned int)g_earlierMenuPaged_442024, (unsigned int)g_earlierMenuPaged_43D0B0, (unsigned int)g_earlierMenuPaged_43C648, 0x00000000 },
    { 0x0000, 0x0000, 0x00000201, 0x0000, 0x00C0, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800D3A7C, (unsigned int)g_earlierMenuPaged_442024, 0x00000000, (unsigned int)g_earlierMenuPaged_442344, 0x00000000 },
};

struct MenuBuildDefinitionData g_earlierMenuDef_44F758 = { (unsigned int)g_earlierMenuItems_44F488, 0x0014, 0x0000, (unsigned int)g_earlierMenuPaged_43C510, 0x00000000, (unsigned int)g_earlierMenuPaged_4415B4, 0x00000000, 0x0013, 0x0000, 0x0000, 0x0000, 0x00000000 };

#endif
