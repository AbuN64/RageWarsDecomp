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
extern char g_earlierMenuResource77[];
extern char g_earlierMenuResource78[];
extern char g_earlierMenuResource79[];
extern char g_earlierMenuResource81[];
extern char g_earlierMenuResource82[];
extern char g_earlierMenuResource83[];
extern char g_earlierMenuResource84[];
extern char g_earlierMenuResource85[];
extern char g_earlierMenuResource86[];
extern char g_earlierMenuResource87[];
extern char g_earlierMenuResource88[];
extern char g_earlierMenuResource89[];
extern char g_earlierMenuResource90[];
extern char g_earlierMenuResource91[];
extern char g_earlierMenuResource92[];
extern char g_earlierMenuResource93[];
extern char g_earlierMenuResource94[];
extern char g_earlierMenuResource95[];
extern char g_earlierMenuResource96[];
extern char g_earlierMenuResource114[];
extern char g_earlierMenuResource121[];
extern char g_earlierMenuResource122[];
extern char g_earlierMenuResource123[];
extern char g_earlierMenuResource124[];
extern char g_earlierMenuResource125[];
extern char g_earlierMenuResource126[];
extern char g_earlierMenuResource127[];
extern char g_earlierMenuResource128[];
extern char g_earlierMenuResource129[];
extern char g_earlierMenuResource130[];
extern char g_earlierMenuResource131[];
extern char g_earlierMenuResource132[];
extern char g_earlierMenuResource133[];
extern char g_earlierMenuResource134[];
extern char g_earlierMenuResource135[];
extern char g_earlierMenuResource136[];
extern char g_earlierMenuResource137[];
extern char g_earlierMenuResource138[];
extern char g_earlierMenuResource139[];
extern char g_earlierMenuResource140[];
extern char g_earlierMenuResource141[];
extern char g_earlierMenuResource142[];
extern char g_earlierMenuResource143[];
extern char g_earlierMenuResource144[];
extern char g_earlierMenuResource145[];
extern char g_earlierMenuResource146[];
extern char g_earlierMenuResource158[];
extern char g_earlierMenuResource159[];
extern char g_earlierMenuResource161[];
extern char g_earlierOptionName1[];
extern char g_earlierOptionName2[];
extern char g_earlierOptionName3[];
extern char g_earlierOptionName4[];
extern char g_earlierOptionName5[];
extern char g_earlierOptionName6[];
extern char g_earlierOptionName7[];
extern char g_earlierOptionName8[];
extern char g_earlierOptionName9[];
extern char g_earlierOptionName10[];
extern char g_earlierOptionName11[];
extern char g_earlierOptionName12[];
extern char g_earlierOptionWord1[];
extern char g_earlierOptionWord2[];
extern char g_earlierOptionWord3[];
extern char g_earlierOptionWord4[];
extern char g_earlierOptionWord5[];
extern char g_earlierOptionWord6[];
extern char g_earlierOptionWord7[];
extern char g_earlierOptionWord8[];
extern char g_earlierOptionWord9[];
extern char g_earlierOptionWord10[];
extern char g_earlierOptionWord11[];
extern char g_earlierOptionWord12[];
extern struct MenuBuildItemData g_earlierMenuItems_44EFC0[33];
extern struct MenuBuildItemData g_earlierMenuItems_44F488[20];

struct EarlierOptionBitRow g_earlierOptionBits_44EF00[12] = {
    { g_earlierOptionWord12, g_earlierOptionName1, 0x00000020, 0x00000001 },
    { g_earlierOptionWord11, g_earlierOptionName3, 0x00000080, 0x00000001 },
    { g_earlierOptionWord10, g_earlierOptionName4, 0x00000100, 0x00000001 },
    { g_earlierOptionWord9, g_earlierOptionName2, 0x00000040, 0x00000001 },
    { g_earlierOptionWord8, g_earlierOptionName5, 0x00000200, 0x00000001 },
    { g_earlierOptionWord7, g_earlierOptionName6, 0x00000400, 0x00000001 },
    { g_earlierOptionWord6, g_earlierOptionName7, 0x00000800, 0x00000001 },
    { g_earlierOptionWord5, g_earlierOptionName8, 0x00001000, 0x00000001 },
    { g_earlierOptionWord4, g_earlierOptionName9, 0x00004000, 0x00000001 },
    { g_earlierOptionWord3, g_earlierOptionName10, 0x00008000, 0x00000001 },
    { g_earlierOptionWord2, g_earlierOptionName11, 0xFFFFFFFF, 0x00000001 },
    { g_earlierOptionWord1, g_earlierOptionName12, 0x0400C7E0, 0x00000001 },
};

struct MenuBuildItemData g_earlierMenuItems_44EFC0[33] = {
    { 0x0001, 0x0000, 0x50000000, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x00000385, (unsigned int)g_earlierMenuPaged_44029C, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x08000801, 0x0000, 0x0008, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource78, (unsigned int)g_earlierMenuPaged_442024, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00210041, 0x0000, 0x0014, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource161, (unsigned int)g_earlierMenuPaged_43C96C, (unsigned int)g_earlierMenuPaged_43CAF0, (unsigned int)g_earlierMenuPaged_43CBC8, 0x00000000 },
    { 0x0000, 0x0000, 0x00010050, 0x0058, 0x0014, 0x06, 0x01, 0xFF, 0x07, (int)g_earlierMenuResource121, (unsigned int)g_earlierMenuPaged_44204C, 0x00000000, (unsigned int)g_earlierMenuPaged_43CBD0, 0x00000000 },
    { 0x0000, 0x0000, 0x00024050, 0x0008, 0x0000, 0xFF, 0x01, 0xFE, 0x07, (int)g_earlierMenuResource122, (unsigned int)g_earlierMenuPaged_44204C, 0x00000000, (unsigned int)g_earlierMenuPaged_43CBD0, 0x00000000 },
    { 0x0000, 0x0000, 0x00024050, 0x0008, 0x0000, 0xFF, 0x01, 0xFD, 0x07, (int)g_earlierMenuResource123, (unsigned int)g_earlierMenuPaged_44204C, 0x00000000, (unsigned int)g_earlierMenuPaged_43CBD0, 0x00000000 },
    { 0x0000, 0x0000, 0x00024050, 0x0008, 0x0000, 0xFF, 0x01, 0xFC, 0x07, (int)g_earlierMenuResource124, (unsigned int)g_earlierMenuPaged_44204C, 0x00000000, (unsigned int)g_earlierMenuPaged_43CBD0, 0x00000000 },
    { 0x0000, 0x0000, 0x00024050, 0x0008, 0x0000, 0xFF, 0x01, 0xFB, 0x07, (int)g_earlierMenuResource125, (unsigned int)g_earlierMenuPaged_44204C, 0x00000000, (unsigned int)g_earlierMenuPaged_43CBD0, 0x00000000 },
    { 0x0000, 0x0000, 0x00024050, 0x0008, 0x0000, 0xFF, 0x01, 0xFA, 0x07, (int)g_earlierMenuResource126, (unsigned int)g_earlierMenuPaged_44204C, 0x00000000, (unsigned int)g_earlierMenuPaged_43CBD0, 0x00000000 },
    { 0x0000, 0x0000, 0x00024050, 0x0008, 0x0000, 0xFF, 0xFA, 0xF9, 0x07, (int)g_earlierMenuResource127, (unsigned int)g_earlierMenuPaged_44204C, 0x00000000, (unsigned int)g_earlierMenuPaged_43CBD0, 0x00000000 },
    { 0x0000, 0x0000, 0x00010050, 0x0058, 0x0008, 0x06, 0x01, 0xF9, 0x07, (int)g_earlierMenuResource128, (unsigned int)g_earlierMenuPaged_44204C, 0x00000000, (unsigned int)g_earlierMenuPaged_43CBD0, 0x00000000 },
    { 0x0000, 0x0000, 0x00024050, 0x0008, 0x0000, 0xFF, 0x01, 0xF9, 0x07, (int)g_earlierMenuResource129, (unsigned int)g_earlierMenuPaged_44204C, 0x00000000, (unsigned int)g_earlierMenuPaged_43CBD0, 0x00000000 },
    { 0x0000, 0x0000, 0x00024050, 0x0008, 0x0000, 0xFF, 0x01, 0xF9, 0x07, (int)g_earlierMenuResource130, (unsigned int)g_earlierMenuPaged_44204C, 0x00000000, (unsigned int)g_earlierMenuPaged_43CBD0, 0x00000000 },
    { 0x0000, 0x0000, 0x00024050, 0x0008, 0x0000, 0xFF, 0x01, 0xF9, 0x07, (int)g_earlierMenuResource131, (unsigned int)g_earlierMenuPaged_44204C, 0x00000000, (unsigned int)g_earlierMenuPaged_43CBD0, 0x00000000 },
    { 0x0000, 0x0000, 0x00024050, 0x0008, 0x0000, 0xFF, 0x01, 0xF9, 0x07, (int)g_earlierMenuResource132, (unsigned int)g_earlierMenuPaged_44204C, 0x00000000, (unsigned int)g_earlierMenuPaged_43CBD0, 0x00000000 },
    { 0x0000, 0x0000, 0x00024050, 0x0008, 0x0000, 0xFF, 0x01, 0xF9, 0x07, (int)g_earlierMenuResource133, (unsigned int)g_earlierMenuPaged_44204C, 0x00000000, (unsigned int)g_earlierMenuPaged_43CBD0, 0x00000000 },
    { 0x0000, 0x0000, 0x00024050, 0x0008, 0x0000, 0xFF, 0xFA, 0xF9, 0x07, (int)g_earlierMenuResource134, (unsigned int)g_earlierMenuPaged_44204C, 0x00000000, (unsigned int)g_earlierMenuPaged_43CBD0, 0x00000000 },
    { 0x0000, 0x0000, 0x00010050, 0x0058, 0x0008, 0x06, 0x01, 0xF9, 0x07, (int)g_earlierMenuResource135, (unsigned int)g_earlierMenuPaged_44204C, 0x00000000, (unsigned int)g_earlierMenuPaged_43CBD0, 0x00000000 },
    { 0x0000, 0x0000, 0x00024050, 0x0008, 0x0000, 0xFF, 0x01, 0xF9, 0x07, (int)g_earlierMenuResource136, (unsigned int)g_earlierMenuPaged_44204C, 0x00000000, (unsigned int)g_earlierMenuPaged_43CBD0, 0x00000000 },
    { 0x0000, 0x0000, 0x00024050, 0x0008, 0x0000, 0xFF, 0x01, 0xF9, 0x07, (int)g_earlierMenuResource137, (unsigned int)g_earlierMenuPaged_44204C, 0x00000000, (unsigned int)g_earlierMenuPaged_43CBD0, 0x00000000 },
    { 0x0000, 0x0000, 0x00024050, 0x0008, 0x0000, 0xFF, 0x01, 0xF9, 0x07, (int)g_earlierMenuResource138, (unsigned int)g_earlierMenuPaged_44204C, 0x00000000, (unsigned int)g_earlierMenuPaged_43CBD0, 0x00000000 },
    { 0x0000, 0x0000, 0x00024050, 0x0008, 0x0000, 0xFF, 0x01, 0xF9, 0x07, (int)g_earlierMenuResource139, (unsigned int)g_earlierMenuPaged_44204C, 0x00000000, (unsigned int)g_earlierMenuPaged_43CBD0, 0x00000000 },
    { 0x0000, 0x0000, 0x00024050, 0x0008, 0x0000, 0xFF, 0x01, 0xF9, 0x07, (int)g_earlierMenuResource140, (unsigned int)g_earlierMenuPaged_44204C, 0x00000000, (unsigned int)g_earlierMenuPaged_43CBD0, 0x00000000 },
    { 0x0000, 0x0000, 0x00024050, 0x0008, 0x0000, 0xFF, 0xFA, 0xF9, 0x07, (int)g_earlierMenuResource141, (unsigned int)g_earlierMenuPaged_44204C, 0x00000000, (unsigned int)g_earlierMenuPaged_43CBD0, 0x00000000 },
    { 0x0000, 0x0000, 0x00010050, 0x0058, 0x0008, 0x06, 0x01, 0xF9, 0x08, (int)g_earlierMenuResource142, (unsigned int)g_earlierMenuPaged_44204C, 0x00000000, (unsigned int)g_earlierMenuPaged_43CBD0, 0x00000000 },
    { 0x0000, 0x0000, 0x00024050, 0x0008, 0x0000, 0xFF, 0x01, 0xF9, 0x07, (int)g_earlierMenuResource143, (unsigned int)g_earlierMenuPaged_44204C, 0x00000000, (unsigned int)g_earlierMenuPaged_43CBD0, 0x00000000 },
    { 0x0000, 0x0000, 0x00024050, 0x0008, 0x0000, 0xFF, 0x01, 0xF9, 0x06, (int)g_earlierMenuResource144, (unsigned int)g_earlierMenuPaged_44204C, 0x00000000, (unsigned int)g_earlierMenuPaged_43CBD0, 0x00000000 },
    { 0x0000, 0x0000, 0x00024050, 0x0008, 0x0000, 0xFF, 0x01, 0xF9, 0x05, (int)g_earlierMenuResource145, (unsigned int)g_earlierMenuPaged_44204C, 0x00000000, (unsigned int)g_earlierMenuPaged_43CBD0, 0x00000000 },
    { 0x0000, 0x0000, 0x00024050, 0x0008, 0x0000, 0xFF, 0x01, 0xF9, 0x04, (int)g_earlierMenuResource146, (unsigned int)g_earlierMenuPaged_44204C, 0x00000000, (unsigned int)g_earlierMenuPaged_43CBD0, 0x00000000 },
    { 0x0000, 0x0000, 0x00024050, 0x0008, 0x0000, 0xFF, 0x01, 0xF9, 0x03, (int)g_earlierMenuResource158, (unsigned int)g_earlierMenuPaged_44204C, 0x00000000, (unsigned int)g_earlierMenuPaged_43CC90, 0x00000000 },
    { 0x0000, 0x0000, 0x00024050, 0x0008, 0x0000, 0xFF, 0xFA, 0xF9, 0x02, (int)g_earlierMenuResource159, (unsigned int)g_earlierMenuPaged_44204C, 0x00000000, (unsigned int)g_earlierMenuPaged_43CDB8, 0x00000000 },
    { 0x0000, 0x0000, 0x00011001, 0x0000, 0x0014, 0x00, 0x00, 0x00, 0x00, (int)g_earlierMenuResource114, (unsigned int)g_earlierMenuPaged_442024, (unsigned int)g_earlierMenuPaged_43CF04, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00310201, 0x0000, 0x0018, 0x00, 0x00, 0xFE, 0xE2, (int)g_earlierMenuResource79, (unsigned int)g_earlierMenuPaged_442024, 0x00000000, (unsigned int)g_earlierMenuPaged_442344, 0x00000000 },
};

struct MenuBuildDefinitionData g_earlierMenuDef_44F464 = { (unsigned int)g_earlierMenuItems_44EFC0, 0x0021, 0x0000, (unsigned int)g_earlierMenuPaged_43C958, 0x00000000, (unsigned int)g_earlierMenuPaged_4415B4, 0x00000000, 0x0002, 0x0000, 0x0000, 0x0000, 0x00000000 };

struct MenuBuildItemData g_earlierMenuItems_44F488[20] = {
    { 0x0001, 0x0000, 0x50000000, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x00000385, (unsigned int)g_earlierMenuPaged_44029C, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x08000801, 0x0000, 0x0008, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource77, (unsigned int)g_earlierMenuPaged_442024, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00411001, 0x0000, 0x000C, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource81, (unsigned int)g_earlierMenuPaged_442024, (unsigned int)g_earlierMenuPaged_43D238, (unsigned int)g_earlierMenuPaged_43D21C, 0x00000000 },
    { 0x0000, 0x0000, 0x00411001, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource82, (unsigned int)g_earlierMenuPaged_442024, (unsigned int)g_earlierMenuPaged_43D2C0, (unsigned int)g_earlierMenuPaged_43D2A4, 0x00000000 },
    { 0x0000, 0x0000, 0x00411001, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource83, (unsigned int)g_earlierMenuPaged_442024, (unsigned int)g_earlierMenuPaged_43D348, (unsigned int)g_earlierMenuPaged_43D32C, 0x00000000 },
    { 0x0000, 0x0000, 0x00411001, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource84, (unsigned int)g_earlierMenuPaged_442024, (unsigned int)g_earlierMenuPaged_43D3D0, (unsigned int)g_earlierMenuPaged_43D3B4, 0x00000000 },
    { 0x0000, 0x0000, 0x00411001, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource85, (unsigned int)g_earlierMenuPaged_442024, (unsigned int)g_earlierMenuPaged_43D458, (unsigned int)g_earlierMenuPaged_43D43C, 0x00000000 },
    { 0x0000, 0x0000, 0x00411001, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource86, (unsigned int)g_earlierMenuPaged_442024, (unsigned int)g_earlierMenuPaged_43D4E0, (unsigned int)g_earlierMenuPaged_43D4C4, 0x00000000 },
    { 0x0000, 0x0000, 0x00411001, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource87, (unsigned int)g_earlierMenuPaged_442024, (unsigned int)g_earlierMenuPaged_43D568, (unsigned int)g_earlierMenuPaged_43D54C, 0x00000000 },
    { 0x0000, 0x0000, 0x00411001, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource89, (unsigned int)g_earlierMenuPaged_442024, (unsigned int)g_earlierMenuPaged_43D678, (unsigned int)g_earlierMenuPaged_43D65C, 0x00000000 },
    { 0x0000, 0x0000, 0x00411001, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource88, (unsigned int)g_earlierMenuPaged_442024, (unsigned int)g_earlierMenuPaged_43D5F0, (unsigned int)g_earlierMenuPaged_43D5D4, 0x00000000 },
    { 0x0000, 0x0000, 0x00411001, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource90, (unsigned int)g_earlierMenuPaged_442024, (unsigned int)g_earlierMenuPaged_43D700, (unsigned int)g_earlierMenuPaged_43D6E4, 0x00000000 },
    { 0x0000, 0x0000, 0x00411001, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource91, (unsigned int)g_earlierMenuPaged_442024, (unsigned int)g_earlierMenuPaged_43D788, (unsigned int)g_earlierMenuPaged_43D76C, 0x00000000 },
    { 0x0000, 0x0000, 0x00411001, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource92, (unsigned int)g_earlierMenuPaged_442024, (unsigned int)g_earlierMenuPaged_43D810, (unsigned int)g_earlierMenuPaged_43D7F4, 0x00000000 },
    { 0x0000, 0x0000, 0x00411001, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource93, (unsigned int)g_earlierMenuPaged_442024, (unsigned int)g_earlierMenuPaged_43D898, (unsigned int)g_earlierMenuPaged_43D87C, 0x00000000 },
    { 0x0000, 0x0000, 0x00411001, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource94, (unsigned int)g_earlierMenuPaged_442024, (unsigned int)g_earlierMenuPaged_43D920, (unsigned int)g_earlierMenuPaged_43D904, 0x00000000 },
    { 0x0000, 0x0000, 0x00411001, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource95, (unsigned int)g_earlierMenuPaged_442024, (unsigned int)g_earlierMenuPaged_43D9A8, (unsigned int)g_earlierMenuPaged_43D98C, 0x00000000 },
    { 0x0000, 0x0000, 0x00411001, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource96, (unsigned int)g_earlierMenuPaged_442024, (unsigned int)g_earlierMenuPaged_43DA30, (unsigned int)g_earlierMenuPaged_43DA14, 0x00000000 },
    { 0x0000, 0x0000, 0x00411001, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource114, (unsigned int)g_earlierMenuPaged_442024, (unsigned int)g_earlierMenuPaged_43D0B0, (unsigned int)g_earlierMenuPaged_43C648, 0x00000000 },
    { 0x0000, 0x0000, 0x00000201, 0x0000, 0x00C0, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource79, (unsigned int)g_earlierMenuPaged_442024, 0x00000000, (unsigned int)g_earlierMenuPaged_442344, 0x00000000 },
};

struct MenuBuildDefinitionData g_earlierMenuDef_44F758 = { (unsigned int)g_earlierMenuItems_44F488, 0x0014, 0x0000, (unsigned int)g_earlierMenuPaged_43C510, 0x00000000, (unsigned int)g_earlierMenuPaged_4415B4, 0x00000000, 0x0013, 0x0000, 0x0000, 0x0000, 0x00000000 };

#endif
