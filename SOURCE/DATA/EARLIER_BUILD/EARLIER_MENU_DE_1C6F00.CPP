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

extern char g_earlierMenuPaged174[];
extern char g_earlierMenuPaged175[];
extern char g_earlierMenuPaged176[];
extern char g_earlierMenuPaged177[];
extern char g_earlierMenuPaged178[];
extern char g_earlierMenuPaged179[];
extern char g_earlierMenuPaged180[];
extern char g_earlierMenuPaged181[];
extern char g_earlierMenuPaged182[];
extern char g_earlierMenuPaged183[];
extern char g_earlierMenuPaged184[];
extern char g_earlierMenuPaged185[];
extern char g_earlierMenuPaged186[];
extern char g_earlierMenuPaged187[];
extern char g_earlierMenuPaged188[];
extern char g_earlierMenuPaged189[];
extern char g_earlierMenuPaged190[];
extern char g_earlierMenuPaged191[];
extern char g_earlierMenuPaged192[];
extern char g_earlierMenuPaged194[];
extern char g_earlierMenuPaged195[];
extern char g_earlierMenuPaged196[];
extern char g_earlierMenuPaged197[];
extern char g_earlierMenuPaged198[];
extern char g_earlierMenuPaged199[];
extern char g_earlierMenuPaged200[];
extern char g_earlierMenuPaged201[];
extern char g_earlierMenuPaged202[];
extern char g_earlierMenuPaged203[];
extern char g_earlierMenuPaged204[];
extern char g_earlierMenuPaged205[];
extern char g_earlierMenuPaged206[];
extern char g_earlierMenuPaged207[];
extern char g_earlierMenuPaged208[];
extern char g_earlierMenuPaged209[];
extern char g_earlierMenuPaged211[];
extern char g_earlierMenuPaged213[];
extern char g_earlierMenuPaged214[];
extern char g_earlierMenuPaged215[];
extern char g_earlierMenuPaged216[];
extern char g_earlierMenuPaged217[];
extern char g_earlierMenuPaged219[];
extern char g_earlierMenuPaged220[];
extern char g_earlierMenuPaged345[];
extern char g_earlierMenuPaged348[];
extern char g_earlierMenuPaged350[];
extern char g_earlierMenuPaged351[];
extern char g_earlierMenuPaged352[];
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
extern struct MenuBuildItemData g_earlierMenuItems7[33];
extern struct MenuBuildItemData g_earlierMenuItems9[20];

struct EarlierOptionBitRow g_earlierOptionBits1[12] = {
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

struct MenuBuildItemData g_earlierMenuItems7[33] = {
    { 0x0001, 0x0000, 0x50000000, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x00000385, (unsigned int)g_earlierMenuPaged345, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x08000801, 0x0000, 0x0008, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource78, (unsigned int)g_earlierMenuPaged350, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00210041, 0x0000, 0x0014, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource161, (unsigned int)g_earlierMenuPaged177, (unsigned int)g_earlierMenuPaged178, (unsigned int)g_earlierMenuPaged179, 0x00000000 },
    { 0x0000, 0x0000, 0x00010050, 0x0058, 0x0014, 0x06, 0x01, 0xFF, 0x07, (int)g_earlierMenuResource121, (unsigned int)g_earlierMenuPaged351, 0x00000000, (unsigned int)g_earlierMenuPaged180, 0x00000000 },
    { 0x0000, 0x0000, 0x00024050, 0x0008, 0x0000, 0xFF, 0x01, 0xFE, 0x07, (int)g_earlierMenuResource122, (unsigned int)g_earlierMenuPaged351, 0x00000000, (unsigned int)g_earlierMenuPaged180, 0x00000000 },
    { 0x0000, 0x0000, 0x00024050, 0x0008, 0x0000, 0xFF, 0x01, 0xFD, 0x07, (int)g_earlierMenuResource123, (unsigned int)g_earlierMenuPaged351, 0x00000000, (unsigned int)g_earlierMenuPaged180, 0x00000000 },
    { 0x0000, 0x0000, 0x00024050, 0x0008, 0x0000, 0xFF, 0x01, 0xFC, 0x07, (int)g_earlierMenuResource124, (unsigned int)g_earlierMenuPaged351, 0x00000000, (unsigned int)g_earlierMenuPaged180, 0x00000000 },
    { 0x0000, 0x0000, 0x00024050, 0x0008, 0x0000, 0xFF, 0x01, 0xFB, 0x07, (int)g_earlierMenuResource125, (unsigned int)g_earlierMenuPaged351, 0x00000000, (unsigned int)g_earlierMenuPaged180, 0x00000000 },
    { 0x0000, 0x0000, 0x00024050, 0x0008, 0x0000, 0xFF, 0x01, 0xFA, 0x07, (int)g_earlierMenuResource126, (unsigned int)g_earlierMenuPaged351, 0x00000000, (unsigned int)g_earlierMenuPaged180, 0x00000000 },
    { 0x0000, 0x0000, 0x00024050, 0x0008, 0x0000, 0xFF, 0xFA, 0xF9, 0x07, (int)g_earlierMenuResource127, (unsigned int)g_earlierMenuPaged351, 0x00000000, (unsigned int)g_earlierMenuPaged180, 0x00000000 },
    { 0x0000, 0x0000, 0x00010050, 0x0058, 0x0008, 0x06, 0x01, 0xF9, 0x07, (int)g_earlierMenuResource128, (unsigned int)g_earlierMenuPaged351, 0x00000000, (unsigned int)g_earlierMenuPaged180, 0x00000000 },
    { 0x0000, 0x0000, 0x00024050, 0x0008, 0x0000, 0xFF, 0x01, 0xF9, 0x07, (int)g_earlierMenuResource129, (unsigned int)g_earlierMenuPaged351, 0x00000000, (unsigned int)g_earlierMenuPaged180, 0x00000000 },
    { 0x0000, 0x0000, 0x00024050, 0x0008, 0x0000, 0xFF, 0x01, 0xF9, 0x07, (int)g_earlierMenuResource130, (unsigned int)g_earlierMenuPaged351, 0x00000000, (unsigned int)g_earlierMenuPaged180, 0x00000000 },
    { 0x0000, 0x0000, 0x00024050, 0x0008, 0x0000, 0xFF, 0x01, 0xF9, 0x07, (int)g_earlierMenuResource131, (unsigned int)g_earlierMenuPaged351, 0x00000000, (unsigned int)g_earlierMenuPaged180, 0x00000000 },
    { 0x0000, 0x0000, 0x00024050, 0x0008, 0x0000, 0xFF, 0x01, 0xF9, 0x07, (int)g_earlierMenuResource132, (unsigned int)g_earlierMenuPaged351, 0x00000000, (unsigned int)g_earlierMenuPaged180, 0x00000000 },
    { 0x0000, 0x0000, 0x00024050, 0x0008, 0x0000, 0xFF, 0x01, 0xF9, 0x07, (int)g_earlierMenuResource133, (unsigned int)g_earlierMenuPaged351, 0x00000000, (unsigned int)g_earlierMenuPaged180, 0x00000000 },
    { 0x0000, 0x0000, 0x00024050, 0x0008, 0x0000, 0xFF, 0xFA, 0xF9, 0x07, (int)g_earlierMenuResource134, (unsigned int)g_earlierMenuPaged351, 0x00000000, (unsigned int)g_earlierMenuPaged180, 0x00000000 },
    { 0x0000, 0x0000, 0x00010050, 0x0058, 0x0008, 0x06, 0x01, 0xF9, 0x07, (int)g_earlierMenuResource135, (unsigned int)g_earlierMenuPaged351, 0x00000000, (unsigned int)g_earlierMenuPaged180, 0x00000000 },
    { 0x0000, 0x0000, 0x00024050, 0x0008, 0x0000, 0xFF, 0x01, 0xF9, 0x07, (int)g_earlierMenuResource136, (unsigned int)g_earlierMenuPaged351, 0x00000000, (unsigned int)g_earlierMenuPaged180, 0x00000000 },
    { 0x0000, 0x0000, 0x00024050, 0x0008, 0x0000, 0xFF, 0x01, 0xF9, 0x07, (int)g_earlierMenuResource137, (unsigned int)g_earlierMenuPaged351, 0x00000000, (unsigned int)g_earlierMenuPaged180, 0x00000000 },
    { 0x0000, 0x0000, 0x00024050, 0x0008, 0x0000, 0xFF, 0x01, 0xF9, 0x07, (int)g_earlierMenuResource138, (unsigned int)g_earlierMenuPaged351, 0x00000000, (unsigned int)g_earlierMenuPaged180, 0x00000000 },
    { 0x0000, 0x0000, 0x00024050, 0x0008, 0x0000, 0xFF, 0x01, 0xF9, 0x07, (int)g_earlierMenuResource139, (unsigned int)g_earlierMenuPaged351, 0x00000000, (unsigned int)g_earlierMenuPaged180, 0x00000000 },
    { 0x0000, 0x0000, 0x00024050, 0x0008, 0x0000, 0xFF, 0x01, 0xF9, 0x07, (int)g_earlierMenuResource140, (unsigned int)g_earlierMenuPaged351, 0x00000000, (unsigned int)g_earlierMenuPaged180, 0x00000000 },
    { 0x0000, 0x0000, 0x00024050, 0x0008, 0x0000, 0xFF, 0xFA, 0xF9, 0x07, (int)g_earlierMenuResource141, (unsigned int)g_earlierMenuPaged351, 0x00000000, (unsigned int)g_earlierMenuPaged180, 0x00000000 },
    { 0x0000, 0x0000, 0x00010050, 0x0058, 0x0008, 0x06, 0x01, 0xF9, 0x08, (int)g_earlierMenuResource142, (unsigned int)g_earlierMenuPaged351, 0x00000000, (unsigned int)g_earlierMenuPaged180, 0x00000000 },
    { 0x0000, 0x0000, 0x00024050, 0x0008, 0x0000, 0xFF, 0x01, 0xF9, 0x07, (int)g_earlierMenuResource143, (unsigned int)g_earlierMenuPaged351, 0x00000000, (unsigned int)g_earlierMenuPaged180, 0x00000000 },
    { 0x0000, 0x0000, 0x00024050, 0x0008, 0x0000, 0xFF, 0x01, 0xF9, 0x06, (int)g_earlierMenuResource144, (unsigned int)g_earlierMenuPaged351, 0x00000000, (unsigned int)g_earlierMenuPaged180, 0x00000000 },
    { 0x0000, 0x0000, 0x00024050, 0x0008, 0x0000, 0xFF, 0x01, 0xF9, 0x05, (int)g_earlierMenuResource145, (unsigned int)g_earlierMenuPaged351, 0x00000000, (unsigned int)g_earlierMenuPaged180, 0x00000000 },
    { 0x0000, 0x0000, 0x00024050, 0x0008, 0x0000, 0xFF, 0x01, 0xF9, 0x04, (int)g_earlierMenuResource146, (unsigned int)g_earlierMenuPaged351, 0x00000000, (unsigned int)g_earlierMenuPaged180, 0x00000000 },
    { 0x0000, 0x0000, 0x00024050, 0x0008, 0x0000, 0xFF, 0x01, 0xF9, 0x03, (int)g_earlierMenuResource158, (unsigned int)g_earlierMenuPaged351, 0x00000000, (unsigned int)g_earlierMenuPaged181, 0x00000000 },
    { 0x0000, 0x0000, 0x00024050, 0x0008, 0x0000, 0xFF, 0xFA, 0xF9, 0x02, (int)g_earlierMenuResource159, (unsigned int)g_earlierMenuPaged351, 0x00000000, (unsigned int)g_earlierMenuPaged182, 0x00000000 },
    { 0x0000, 0x0000, 0x00011001, 0x0000, 0x0014, 0x00, 0x00, 0x00, 0x00, (int)g_earlierMenuResource114, (unsigned int)g_earlierMenuPaged350, (unsigned int)g_earlierMenuPaged183, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00310201, 0x0000, 0x0018, 0x00, 0x00, 0xFE, 0xE2, (int)g_earlierMenuResource79, (unsigned int)g_earlierMenuPaged350, 0x00000000, (unsigned int)g_earlierMenuPaged352, 0x00000000 },
};

struct MenuBuildDefinitionData g_earlierMenuDef35 = { (unsigned int)g_earlierMenuItems7, 0x0021, 0x0000, (unsigned int)g_earlierMenuPaged176, 0x00000000, (unsigned int)g_earlierMenuPaged348, 0x00000000, 0x0002, 0x0000, 0x0000, 0x0000, 0x00000000 };

struct MenuBuildItemData g_earlierMenuItems9[20] = {
    { 0x0001, 0x0000, 0x50000000, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x00000385, (unsigned int)g_earlierMenuPaged345, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x08000801, 0x0000, 0x0008, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource77, (unsigned int)g_earlierMenuPaged350, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00411001, 0x0000, 0x000C, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource81, (unsigned int)g_earlierMenuPaged350, (unsigned int)g_earlierMenuPaged186, (unsigned int)g_earlierMenuPaged185, 0x00000000 },
    { 0x0000, 0x0000, 0x00411001, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource82, (unsigned int)g_earlierMenuPaged350, (unsigned int)g_earlierMenuPaged188, (unsigned int)g_earlierMenuPaged187, 0x00000000 },
    { 0x0000, 0x0000, 0x00411001, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource83, (unsigned int)g_earlierMenuPaged350, (unsigned int)g_earlierMenuPaged190, (unsigned int)g_earlierMenuPaged189, 0x00000000 },
    { 0x0000, 0x0000, 0x00411001, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource84, (unsigned int)g_earlierMenuPaged350, (unsigned int)g_earlierMenuPaged192, (unsigned int)g_earlierMenuPaged191, 0x00000000 },
    { 0x0000, 0x0000, 0x00411001, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource85, (unsigned int)g_earlierMenuPaged350, (unsigned int)g_earlierMenuPaged195, (unsigned int)g_earlierMenuPaged194, 0x00000000 },
    { 0x0000, 0x0000, 0x00411001, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource86, (unsigned int)g_earlierMenuPaged350, (unsigned int)g_earlierMenuPaged197, (unsigned int)g_earlierMenuPaged196, 0x00000000 },
    { 0x0000, 0x0000, 0x00411001, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource87, (unsigned int)g_earlierMenuPaged350, (unsigned int)g_earlierMenuPaged199, (unsigned int)g_earlierMenuPaged198, 0x00000000 },
    { 0x0000, 0x0000, 0x00411001, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource89, (unsigned int)g_earlierMenuPaged350, (unsigned int)g_earlierMenuPaged203, (unsigned int)g_earlierMenuPaged202, 0x00000000 },
    { 0x0000, 0x0000, 0x00411001, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource88, (unsigned int)g_earlierMenuPaged350, (unsigned int)g_earlierMenuPaged201, (unsigned int)g_earlierMenuPaged200, 0x00000000 },
    { 0x0000, 0x0000, 0x00411001, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource90, (unsigned int)g_earlierMenuPaged350, (unsigned int)g_earlierMenuPaged205, (unsigned int)g_earlierMenuPaged204, 0x00000000 },
    { 0x0000, 0x0000, 0x00411001, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource91, (unsigned int)g_earlierMenuPaged350, (unsigned int)g_earlierMenuPaged207, (unsigned int)g_earlierMenuPaged206, 0x00000000 },
    { 0x0000, 0x0000, 0x00411001, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource92, (unsigned int)g_earlierMenuPaged350, (unsigned int)g_earlierMenuPaged209, (unsigned int)g_earlierMenuPaged208, 0x00000000 },
    { 0x0000, 0x0000, 0x00411001, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource93, (unsigned int)g_earlierMenuPaged350, (unsigned int)g_earlierMenuPaged213, (unsigned int)g_earlierMenuPaged211, 0x00000000 },
    { 0x0000, 0x0000, 0x00411001, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource94, (unsigned int)g_earlierMenuPaged350, (unsigned int)g_earlierMenuPaged215, (unsigned int)g_earlierMenuPaged214, 0x00000000 },
    { 0x0000, 0x0000, 0x00411001, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource95, (unsigned int)g_earlierMenuPaged350, (unsigned int)g_earlierMenuPaged217, (unsigned int)g_earlierMenuPaged216, 0x00000000 },
    { 0x0000, 0x0000, 0x00411001, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource96, (unsigned int)g_earlierMenuPaged350, (unsigned int)g_earlierMenuPaged220, (unsigned int)g_earlierMenuPaged219, 0x00000000 },
    { 0x0000, 0x0000, 0x00411001, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource114, (unsigned int)g_earlierMenuPaged350, (unsigned int)g_earlierMenuPaged184, (unsigned int)g_earlierMenuPaged175, 0x00000000 },
    { 0x0000, 0x0000, 0x00000201, 0x0000, 0x00C0, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource79, (unsigned int)g_earlierMenuPaged350, 0x00000000, (unsigned int)g_earlierMenuPaged352, 0x00000000 },
};

struct MenuBuildDefinitionData g_earlierMenuDef37 = { (unsigned int)g_earlierMenuItems9, 0x0014, 0x0000, (unsigned int)g_earlierMenuPaged174, 0x00000000, (unsigned int)g_earlierMenuPaged348, 0x00000000, 0x0013, 0x0000, 0x0000, 0x0000, 0x00000000 };

#endif
