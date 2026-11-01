#if defined(VERSION_EU)
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

extern char g_earlierMenuPaged_4064A8[];
extern char g_earlierMenuPaged_406730[];
extern char g_earlierMenuPaged_406A88[];
extern char g_earlierMenuPaged_407030[];
extern char g_earlierMenuPaged_4071A8[];
extern char g_earlierMenuPaged_40783C[];
extern char g_earlierMenuPaged_4080E4[];
extern char g_earlierMenuPaged_4082D0[];
extern char g_earlierMenuPaged_4084D4[];
extern char g_earlierMenuPaged_4087C8[];
extern char g_earlierMenuPaged_408A58[];
extern char g_earlierMenuPaged_408CAC[];
extern char g_earlierMenuPaged_408F30[];
extern char g_earlierMenuPaged_4090D4[];
extern char g_earlierMenuPaged_409428[];
extern char g_earlierMenuPaged_40972C[];
extern char g_earlierMenuPaged_409F18[];
extern char g_earlierMenuPaged_409FF8[];
extern char g_earlierMenuPaged_40A11C[];
extern char g_earlierMenuPaged_40A550[];
extern char g_earlierMenuPaged_40A61C[];
extern char g_earlierMenuPaged_40A6A8[];
extern char g_earlierMenuPaged_40A784[];
extern char g_earlierMenuPaged_40A7A8[];
extern char g_earlierMenuPaged_40A7BC[];
extern char g_earlierMenuPaged_40A7CC[];
extern char g_earlierMenuPaged_40A800[];
extern char g_earlierMenuPaged_40A85C[];
extern char g_earlierMenuPaged_40A8C8[];
extern char g_earlierMenuPaged_40A934[];
extern char g_earlierMenuPaged_40A960[];
extern char g_earlierMenuPaged_40AA04[];
extern char g_earlierMenuPaged_40AA38[];
extern char g_earlierMenuPaged_40AAA4[];
extern char g_earlierMenuPaged_40AAC0[];
extern char g_earlierMenuPaged_40AAD8[];
extern char g_earlierMenuPaged_40AB18[];
extern char g_earlierMenuPaged_40AB6C[];
extern char g_earlierMenuPaged_40AC68[];
extern char g_earlierMenuPaged_40ADC0[];
extern char g_earlierMenuPaged_40AE28[];
extern char g_earlierMenuPaged_40AE7C[];
extern char g_earlierMenuPaged_40AEE8[];
extern char g_earlierMenuPaged_40AEF8[];
extern char g_earlierMenuPaged_40AF0C[];
extern char g_earlierMenuPaged_40AF20[];
extern char g_earlierMenuPaged_40AF34[];
extern char g_earlierMenuPaged_40AF48[];
extern char g_earlierMenuPaged_40AF5C[];
extern char g_earlierMenuPaged_40AF70[];
extern char g_earlierMenuPaged_40AF84[];
extern char g_earlierMenuPaged_40AFD0[];
extern char g_earlierMenuPaged_40AFEC[];
extern char g_earlierMenuPaged_40B00C[];
extern char g_earlierMenuPaged_40B020[];
extern char g_earlierMenuPaged_40B034[];
extern char g_earlierMenuPaged_40B048[];
extern char g_earlierMenuPaged_40B05C[];
extern char g_earlierMenuPaged_40B070[];
extern char g_earlierMenuPaged_40B084[];
extern char g_earlierMenuPaged_40B0D0[];
extern char g_earlierMenuPaged_40B1FC[];
extern char g_earlierMenuPaged_40B328[];
extern char g_earlierMenuPaged_40B454[];
extern char g_earlierMenuPaged_40B580[];
extern char g_earlierMenuPaged_40B6AC[];
extern char g_earlierMenuPaged_40B6F8[];
extern char g_earlierMenuPaged_40B7D8[];
extern char g_earlierMenuPaged_40B7F4[];
extern char g_earlierMenuPaged_40B80C[];
extern char g_earlierMenuPaged_40B840[];
extern char g_earlierMenuPaged_40B874[];
extern char g_earlierMenuPaged_40B920[];
extern char g_earlierMenuPaged_40B9CC[];
extern char g_earlierMenuPaged_40BA88[];
extern char g_earlierMenuPaged_40BB0C[];
extern char g_earlierMenuPaged_40BB40[];
extern char g_earlierMenuPaged_40BC20[];
extern char g_earlierMenuPaged_40BC38[];
extern char g_earlierMenuPaged_40BC54[];
extern char g_earlierMenuPaged_40BC70[];
extern char g_earlierMenuPaged_40BC8C[];
extern char g_earlierMenuPaged_40BCA8[];
extern char g_earlierMenuPaged_40BD24[];
extern char g_earlierMenuPaged_40BDA0[];
extern char g_earlierMenuPaged_40BE1C[];
extern char g_earlierMenuPaged_40BE98[];
extern char g_earlierMenuPaged_40BF14[];
extern char g_earlierMenuPaged_40BF80[];
extern char g_earlierMenuPaged_43D430[];
extern char g_earlierMenuPaged_43D568[];
extern char g_earlierMenuPaged_43D878[];
extern char g_earlierMenuPaged_43D88C[];
extern char g_earlierMenuPaged_43DA10[];
extern char g_earlierMenuPaged_43DAE8[];
extern char g_earlierMenuPaged_43DAF0[];
extern char g_earlierMenuPaged_43DBC0[];
extern char g_earlierMenuPaged_43DCE8[];
extern char g_earlierMenuPaged_43DE34[];
extern char g_earlierMenuPaged_43DFE0[];
extern char g_earlierMenuPaged_43E14C[];
extern char g_earlierMenuPaged_43E168[];
extern char g_earlierMenuPaged_43E1D4[];
extern char g_earlierMenuPaged_43E1F0[];
extern char g_earlierMenuPaged_43E25C[];
extern char g_earlierMenuPaged_43E278[];
extern char g_earlierMenuPaged_43E2E4[];
extern char g_earlierMenuPaged_43E300[];
extern char g_earlierMenuPaged_43E36C[];
extern char g_earlierMenuPaged_43E388[];
extern char g_earlierMenuPaged_43E3F4[];
extern char g_earlierMenuPaged_43E410[];
extern char g_earlierMenuPaged_43E47C[];
extern char g_earlierMenuPaged_43E498[];
extern char g_earlierMenuPaged_43E504[];
extern char g_earlierMenuPaged_43E520[];
extern char g_earlierMenuPaged_43E58C[];
extern char g_earlierMenuPaged_43E5A8[];
extern char g_earlierMenuPaged_43E614[];
extern char g_earlierMenuPaged_43E630[];
extern char g_earlierMenuPaged_43E69C[];
extern char g_earlierMenuPaged_43E6B8[];
extern char g_earlierMenuPaged_43E724[];
extern char g_earlierMenuPaged_43E740[];
extern char g_earlierMenuPaged_43E7AC[];
extern char g_earlierMenuPaged_43E7C8[];
extern char g_earlierMenuPaged_43E834[];
extern char g_earlierMenuPaged_43E850[];
extern char g_earlierMenuPaged_43E8BC[];
extern char g_earlierMenuPaged_43E8D8[];
extern char g_earlierMenuPaged_43E944[];
extern char g_earlierMenuPaged_43E960[];
extern char g_earlierMenuPaged_43E9D0[];
extern char g_earlierMenuPaged_43E9F4[];
extern char g_earlierMenuPaged_43EA40[];
extern char g_earlierMenuPaged_43EF5C[];
extern char g_earlierMenuPaged_43EF94[];
extern char g_earlierMenuPaged_43EFF0[];
extern char g_earlierMenuPaged_43F028[];
extern char g_earlierMenuPaged_43F074[];
extern char g_earlierMenuPaged_43F178[];
extern char g_earlierMenuPaged_43F1C4[];
extern char g_earlierMenuPaged_43F1F0[];
extern char g_earlierMenuPaged_43F214[];
extern char g_earlierMenuPaged_43F240[];
extern char g_earlierMenuPaged_43F28C[];
extern char g_earlierMenuPaged_43F2B0[];
extern char g_earlierMenuPaged_43F2DC[];
extern char g_earlierMenuPaged_43F314[];
extern char g_earlierMenuPaged_43F374[];
extern char g_earlierMenuPaged_43F37C[];
extern char g_earlierMenuPaged_43F468[];
extern char g_earlierMenuPaged_43F470[];
extern char g_earlierMenuPaged_43F4A8[];
extern char g_earlierMenuPaged_43F4F0[];
extern char g_earlierMenuPaged_43F6DC[];
extern char g_earlierMenuPaged_43F7C8[];
extern char g_earlierMenuPaged_43F7F4[];
extern char g_earlierMenuPaged_43F828[];
extern char g_earlierMenuPaged_43F854[];
extern char g_earlierMenuPaged_43F8AC[];
extern char g_earlierMenuPaged_43F8F8[];
extern char g_earlierMenuPaged_43F944[];
extern char g_earlierMenuPaged_43FA1C[];
extern char g_earlierMenuPaged_43FA90[];
extern char g_earlierMenuPaged_43FAEC[];
extern char g_earlierMenuPaged_43FB18[];
extern char g_earlierMenuPaged_43FB44[];
extern char g_earlierMenuPaged_43FB70[];
extern char g_earlierMenuPaged_43FC50[];
extern char g_earlierMenuPaged_43FC7C[];
extern char g_earlierMenuPaged_43FCC4[];
extern char g_earlierMenuPaged_43FD00[];
extern char g_earlierMenuPaged_43FEE0[];
extern char g_earlierMenuPaged_43FF68[];
extern char g_earlierMenuPaged_4411C4[];
extern char g_earlierMenuPaged_441730[];
extern char g_earlierMenuPaged_4424EC[];
extern char g_earlierMenuPaged_442F6C[];
extern char g_earlierMenuPaged_442FA4[];
extern char g_earlierMenuPaged_4432AC[];
extern char g_earlierMenuPaged_444310[];
extern char g_earlierMenuPaged_444348[];
extern char g_earlierMenuPaged_444430[];
extern char g_earlierMenuPaged_444754[];
extern char g_earlierMenuPaged_444778[];
extern char g_earlierMenuPaged_444900[];
extern char g_earlierMenuPaged_444C88[];
extern char g_earlierMenuPaged_444D48[];
extern char g_earlierMenuPaged_444E44[];
extern char g_earlierMenuPaged_4452A4[];
extern char g_earlierMenuPaged_4452DC[];
extern char g_earlierMenuPaged_4453D4[];
extern char g_earlierMenuPaged_445480[];
extern char g_earlierMenuPaged_4454E4[];
extern char g_earlierMenuPaged_445548[];
extern char g_earlierMenuPaged_4455AC[];
extern char g_earlierMenuPaged_445608[];
extern char g_earlierMenuPaged_44566C[];
extern char g_earlierMenuPaged_4456D0[];
extern char g_earlierMenuPaged_445734[];
extern char g_earlierMenuPaged_445798[];
extern char g_earlierMenuPaged_4457EC[];
extern char g_earlierMenuPaged_445860[];
extern char g_earlierMenuPaged_4458B0[];
extern char g_earlierMenuPaged_44594C[];
extern char g_earlierMenuPaged_4459F0[];
extern char g_earlierMenuPaged_445A58[];
extern char g_earlierMenuPaged_445ABC[];
extern char g_earlierMenuPaged_445BB0[];
extern char g_earlierMenuPaged_445C14[];
extern char g_earlierMenuPaged_445D08[];
extern char g_earlierMenuPaged_445D54[];
extern char g_earlierMenuPaged_445D88[];
extern char g_earlierMenuPaged_445E18[];
extern char g_earlierMenuPaged_445E70[];
extern char g_earlierMenuPaged_445EBC[];
extern char g_earlierMenuPaged_445F60[];
extern char g_earlierMenuPaged_445FB4[];
extern char g_earlierMenuPaged_445FD0[];
extern char g_earlierMenuPaged_446010[];
extern char g_earlierMenuPaged_44601C[];
extern char g_earlierMenuPaged_446054[];
extern char g_earlierMenuPaged_44605C[];
extern char g_earlierMenuPaged_446088[];
extern char g_earlierMenuPaged_4460B4[];
extern char g_earlierMenuPaged_4460E0[];
extern char g_earlierMenuPaged_44610C[];
extern char g_earlierMenuPaged_446138[];
extern char g_earlierMenuPaged_446164[];
extern char g_earlierMenuPaged_4461EC[];
extern char g_earlierMenuPaged_44624C[];
extern char g_earlierMenuPaged_446350[];
extern char g_earlierMenuPaged_4463C0[];
extern char g_earlierMenuPaged_4464C4[];
extern char g_earlierMenuPaged_446524[];
extern char g_earlierMenuPaged_446628[];
extern char g_earlierMenuPaged_4466CC[];
extern char g_earlierMenuPaged_44674C[];
extern char g_earlierMenuPaged_446854[];
extern char g_earlierMenuPaged_4468E4[];
extern char g_earlierMenuPaged_446900[];
extern char g_earlierMenuPaged_446920[];
extern char g_earlierMenuPaged_446BB4[];
extern char g_earlierMenuPaged_446D04[];
extern char g_earlierMenuPaged_446E24[];
extern char g_earlierMenuPaged_446FD0[];
extern char g_earlierMenuPaged_447068[];
extern char g_earlierMenuPaged_447158[];
extern char g_earlierMenuResource_800E2AC8[];
extern char g_earlierMenuResource_800E2AF8[];
extern char g_earlierMenuResource_800E2B28[];
extern char g_earlierMenuResource_800E2B48[];
extern char g_earlierMenuResource_800E2B58[];
extern char g_earlierMenuResource_800E2B78[];
extern char g_earlierMenuResource_800E2B88[];
extern char g_earlierMenuResource_800E2BA8[];
extern char g_earlierMenuResource_800E2BB8[];
extern char g_earlierMenuResource_800E2BE8[];
extern char g_earlierMenuResource_800E2BF8[];
extern char g_earlierMenuResource_800E2C18[];
extern char g_earlierMenuResource_800E2C28[];
extern char g_earlierMenuResource_800E2C38[];
extern char g_earlierMenuResource_800E2C48[];
extern char g_earlierMenuResource_800E2C58[];
extern char g_earlierMenuResource_800E2C68[];
extern char g_earlierMenuResource_800E2C88[];
extern char g_earlierMenuResource_800E2C98[];
extern char g_earlierMenuResource_800E2CC8[];
extern char g_earlierMenuResource_800E2CD8[];
extern char g_earlierMenuResource_800E2CE8[];
extern char g_earlierMenuResource_800E2CF8[];
extern char g_earlierMenuResource_800E2D08[];
extern char g_earlierMenuResource_800E2D18[];
extern char g_earlierMenuResource_800E2D38[];
extern char g_earlierMenuResource_800E2D48[];
extern char g_earlierMenuResource_800E2D58[];
extern char g_earlierMenuResource_800E2DC8[];
extern char g_earlierMenuResource_800E2DF8[];
extern char g_earlierMenuResource_800E2E08[];
extern char g_earlierMenuResource_800E2E18[];
extern char g_earlierMenuResource_800E2E28[];
extern char g_earlierMenuResource_800E2E38[];
extern char g_earlierMenuResource_800E2E48[];
extern char g_earlierMenuResource_800E2E58[];
extern char g_earlierMenuResource_800E2E68[];
extern char g_earlierMenuResource_800E2E88[];
extern char g_earlierMenuResource_800E2E98[];
extern char g_earlierMenuResource_800E2EA8[];
extern char g_earlierMenuResource_800E2EC8[];
extern char g_earlierMenuResource_800E2ED8[];
extern char g_earlierMenuResource_800E2EE8[];
extern char g_earlierMenuResource_800E2EF8[];
extern char g_earlierMenuResource_800E2F08[];
extern char g_earlierMenuResource_800E2F18[];
extern char g_earlierMenuResource_800E2F28[];
extern char g_earlierMenuResource_800E2F38[];
extern char g_earlierMenuResource_800E2F48[];
extern char g_earlierMenuResource_800E2F58[];
extern char g_earlierMenuResource_800E2F68[];
extern char g_earlierMenuResource_800E2F78[];
extern char g_earlierMenuResource_800E2F88[];
extern char g_earlierMenuResource_800E2F98[];
extern char g_earlierMenuResource_800E2FE8[];
extern char g_earlierMenuResource_800E2FF8[];
extern char g_earlierMenuResource_800E3008[];
extern char g_earlierMenuResource_800E3018[];
extern char g_earlierMenuResource_800E3028[];
extern char g_earlierMenuResource_800E3038[];
extern char g_earlierMenuResource_800E3048[];
extern char g_earlierMenuResource_800E3058[];
extern char g_earlierMenuResource_800E3068[];
extern char g_earlierMenuResource_800E3078[];
extern char g_earlierMenuResource_800E3088[];
extern char g_earlierMenuResource_800E3098[];
extern char g_earlierMenuResource_800E30A8[];
extern char g_earlierMenuResource_800E30B8[];
extern char g_earlierMenuResource_800E30C8[];
extern char g_earlierMenuResource_800E30D8[];
extern char g_earlierMenuResource_800E30E8[];
extern char g_earlierMenuResource_800E3148[];
extern char g_earlierMenuResource_800E3188[];
extern char g_earlierMenuResource_800E32D8[];
extern char g_earlierMenuResource_800E3328[];
extern char g_earlierMenuResource_800E3338[];
extern char g_earlierMenuResource_800E3348[];
extern char g_earlierMenuResource_800E3358[];
extern char g_earlierMenuResource_800E33B8[];
extern char g_earlierMenuResource_800E33C8[];
extern char g_earlierMenuResource_800E33D8[];
extern char g_earlierMenuResource_800E33E8[];
extern char g_earlierMenuResource_800E3438[];
extern char g_earlierMenuResource_800E3958[];
extern char g_earlierMenuResource_800E39C8[];
extern char g_earlierMenuResource_800E39D8[];
extern char g_earlierMenuResource_800E3BC8[];
extern char g_earlierMenuResource_800E3BD8[];
extern char g_earlierMenuResource_800E3CE8[];
extern char g_earlierMenuResource_800E3D18[];
extern char g_earlierMenuResource_800E3D98[];
extern char g_earlierMenuResource_800E3DB8[];
extern char g_earlierMenuResource_800E3DC8[];
extern char g_earlierMenuResource_800E3DE8[];
extern char g_earlierMenuResource_800E3DF8[];
extern char g_earlierMenuResource_800E3E08[];
extern char g_earlierMenuResource_800E3E38[];
extern char g_earlierMenuResource_800E3E78[];
extern char g_earlierMenuResource_800E3E88[];
extern char g_earlierMenuResource_800E4098[];
extern char g_earlierMenuResource_800E40B8[];
extern char g_earlierMenuResource_800E40D8[];
extern char g_earlierMenuResource_800E40F8[];
extern char g_earlierMenuResource_800E4118[];
extern char g_earlierMenuResource_800E4138[];
extern char g_earlierMenuResource_800E4158[];
extern char g_earlierMenuResource_800E4178[];
extern char g_earlierMenuResource_800E4198[];
extern char g_earlierMenuResource_800E41B8[];
extern char g_earlierMenuResource_800E41D8[];
extern char g_earlierMenuResource_800E41F8[];
extern char g_earlierMenuResource_800E4218[];
extern char g_earlierMenuResource_800E4238[];
extern char g_earlierMenuResource_800E4258[];
extern char g_earlierMenuResource_800E4278[];
extern char g_earlierMenuResource_800E4338[];
extern char g_earlierMenuResource_800E4368[];
extern char g_earlierMenuResource_800E43B8[];
extern char g_earlierMenuResource_800E43E8[];
extern char g_earlierMenuResource_800E4438[];
extern char g_earlierMenuResource_800E4468[];
extern char g_earlierMenuResource_800E44B8[];
extern char g_earlierMenuResource_800E44E8[];
extern char g_earlierMenuResource_800E45A8[];
extern char g_earlierMenuResource_800E45B8[];
extern char g_earlierMenuResource_800E45C8[];
extern char g_earlierMenuResource_800E45D8[];
extern char g_earlierMenuResource_800E45E8[];
extern char g_earlierMenuResource_800E4898[];
extern char g_earlierMenuResource_800E4A08[];
extern char g_earlierMenuResource_800E4A38[];
extern char g_earlierMenuResource_800E4A48[];
extern char g_earlierMenuResource_800E4A78[];
extern char g_earlierMenuResource_800E4A88[];
extern char g_earlierMenuResource_800E4AB8[];
extern char g_earlierMenuResource_800E4AC8[];
extern char g_earlierMenuResource_800E4AF8[];
extern char g_earlierMenuResource_800E4B08[];
extern char g_earlierMenuResource_800E4B18[];
extern char g_earlierMenuResource_800E4B38[];
extern char g_earlierMenuResource_800E4B48[];
extern char g_earlierMenuResource_800E4BC8[];
extern char g_earlierMenuResource_800E4BF8[];
extern char g_earlierMenuResource_800E4C18[];
extern char g_earlierMenuResource_800E4C28[];
extern char g_earlierMenuResource_800E4C38[];
extern char g_earlierMenuResource_800E4C48[];
extern char g_earlierMenuResource_800E4C58[];
extern char g_earlierMenuResource_800E4C68[];
extern char g_earlierMenuResource_800E4C8C[];
extern char g_earlierMenuResource_800E4CA0[];
extern char g_earlierMenuResource_800E4CB4[];
extern char g_earlierMenuResource_800E4CBC[];
extern char g_earlierMenuResource_800E4CC8[];
extern char g_earlierMenuResource_800E4CD0[];
extern char g_earlierMenuResource_800E4CDC[];
extern char g_earlierMenuResource_800E4CE4[];
extern char g_earlierMenuResource_800E4CF0[];
extern char g_earlierMenuResource_800E4CF8[];
extern char g_earlierMenuResource_800E4D04[];
extern char g_earlierMenuResource_800E4D0C[];
extern char g_earlierMenuResource_800E4D18[];
extern char g_earlierMenuResource_800E4D20[];
extern char g_earlierMenuResource_800E4D2C[];
extern char g_earlierMenuResource_800E4D34[];
extern char g_earlierMenuResource_800E4D40[];
extern char g_earlierMenuResource_800E4D48[];
extern char g_earlierMenuResource_800E4D54[];
extern char g_earlierMenuResource_800E4D5C[];
extern char g_earlierMenuResource_800E4D68[];
extern char g_earlierMenuResource_800E4D70[];
extern char g_earlierMenuResource_800E4D7C[];
extern char g_earlierMenuResource_800E4D84[];
extern char g_earlierMenuResource_800E4D90[];
extern char g_earlierMenuResource_800E4D98[];
extern char g_earlierMenuResource_800E4DA4[];
extern char g_earlierMenuResource_800E4DAC[];
extern char g_earlierMenuResource_800E4DB8[];
extern char g_earlierMenuResource_800E4DC0[];
extern char g_earlierMenuResource_800E4DCC[];
extern char g_earlierMenuResource_800E4DD4[];
extern char g_earlierMenuResource_800E4DE0[];
extern char g_earlierMenuResource_800E4DE8[];
extern char g_earlierMenuResource_800E4DF4[];
extern char g_earlierMenuResource_800E4DFC[];
extern char g_earlierMenuResource_800E4E08[];
extern char g_earlierMenuResource_800E4E10[];
extern char g_earlierMenuResource_800E4E1C[];
extern char g_earlierMenuResource_800E4E24[];
extern char g_earlierMenuResource_800E4E30[];
extern char g_earlierMenuResource_800E4E38[];
extern char g_earlierMenuResource_800E4E44[];
extern char g_earlierMenuResource_800E4E4C[];
extern char g_earlierMenuResource_800E4E58[];
extern char g_earlierMenuResource_800E4E60[];
extern char g_earlierMenuResource_800E4E6C[];
extern char g_earlierMenuResource_800E4E74[];
extern char g_earlierMenuResource_800E4E80[];
extern char g_earlierMenuResource_800E4E88[];
extern char g_earlierMenuResource_800E4E94[];
extern char g_earlierMenuResource_800E4E9C[];
extern char g_earlierMenuResource_800E4EA8[];
extern char g_earlierMenuResource_800E4EB0[];
extern char g_earlierMenuResource_800E4EBC[];
extern char g_earlierMenuResource_800E4EC4[];
extern char g_earlierMenuResource_800E4ED0[];
extern char g_earlierMenuResource_800E4ED8[];
extern char g_earlierMenuResource_800E4EE4[];
extern char g_earlierMenuResource_800E4EEC[];
extern char g_earlierMenuResource_800E4EF8[];
extern char g_earlierMenuResource_800E4F00[];
extern char g_earlierMenuResource_800E4F0C[];
extern char g_earlierMenuResource_800E4F14[];
extern char g_earlierMenuResource_800E4F20[];
extern char g_earlierMenuResource_800E4F28[];
extern char g_earlierMenuResource_800E4F34[];
extern char g_earlierMenuResource_800E4F3C[];
extern char g_earlierMenuResource_800E4F48[];
extern char g_earlierMenuResource_800E4F50[];
extern char g_earlierMenuResource_800E4F5C[];
extern char g_earlierMenuResource_800E4F64[];
extern char g_earlierMenuResource_800E4F70[];
extern char g_earlierMenuResource_800E4F78[];
extern char g_earlierMenuResource_800E4F84[];
extern char g_earlierMenuResource_800E4F8C[];
extern char g_earlierMenuResource_800E4FA0[];
extern char g_earlierMenuResource_800E4FB4[];
extern char g_earlierMenuResource_800E4FC8[];
extern char g_earlierMenuResource_800F2CE4[];
extern char g_earlierMenuResource_800F3520[];
extern char g_earlierMenuResource_800F3530[];
extern char g_earlierMenuResource_800F3540[];
extern char g_earlierMenuResource_800F3550[];
extern char g_earlierMenuResource_800F3560[];
extern char g_earlierMenuResource_800F3570[];
extern char g_earlierMenuResource_800F3580[];
extern char g_earlierOptionName_800E3F28[];
extern char g_earlierOptionName_800E3F38[];
extern char g_earlierOptionName_800E3F48[];
extern char g_earlierOptionName_800E3F58[];
extern char g_earlierOptionName_800E3F68[];
extern char g_earlierOptionName_800E3F78[];
extern char g_earlierOptionName_800E3F88[];
extern char g_earlierOptionName_800E3F98[];
extern char g_earlierOptionName_800E3FB8[];
extern char g_earlierOptionName_800E3FC8[];
extern char g_earlierOptionName_800F2D08[];
extern char g_earlierOptionName_800F2D30[];
extern char g_earlierOptionWord_800EF160[];
extern char g_earlierOptionWord_800EF174[];
extern char g_earlierOptionWord_800EF18C[];
extern char g_earlierOptionWord_800EF198[];
extern char g_earlierOptionWord_800EF1A4[];
extern char g_earlierOptionWord_800EF1AC[];
extern char g_earlierOptionWord_800EF1B8[];
extern char g_earlierOptionWord_800EF1CC[];
extern char g_earlierOptionWord_800EF1D8[];
extern char g_earlierOptionWord_800EF1E4[];
extern char g_earlierOptionWord_800EF1EC[];
extern char g_earlierOptionWord_800EF1FC[];
extern struct MenuBuildItemData g_earlierMenuItems_44F420[22];
extern struct MenuBuildItemData g_earlierMenuItems_44F7EC[10];
extern struct MenuBuildItemData g_earlierMenuItems_44F99C[9];
extern struct MenuBuildItemData g_earlierMenuItems_44FB4C[8];
extern struct MenuBuildItemData g_earlierMenuItems_44FED0[8];
extern struct MenuBuildItemData g_earlierMenuItems_450038[8];
extern struct MenuBuildItemData g_earlierMenuItems_4502D0[33];
extern struct MenuBuildItemData g_earlierMenuItems_450798[20];
extern struct MenuBuildItemData g_earlierMenuItems_450A90[3];
extern struct MenuBuildItemData g_earlierMenuItems_450B20[8];
extern struct MenuBuildItemData g_earlierMenuItems_450C64[5];
extern struct MenuBuildDefinitionData g_earlierMenuDef_450D18;
extern struct EarlierMenuTuning g_earlierMenuTuning_450D3C;
extern struct MenuBuildItemData g_earlierMenuItems_450D6C[3];
extern struct MenuBuildDefinitionData g_earlierMenuDef_450DD8;
extern struct MenuBuildItemData g_earlierMenuItems_450E20[4];
extern struct MenuBuildItemData g_earlierMenuItems_450F14[11];
extern struct MenuBuildItemData g_earlierMenuItems_4510C4[4];
extern struct MenuBuildDefinitionData g_earlierMenuDef_451154;
extern struct MenuBuildItemData g_earlierMenuItems_451178[5];
extern struct MenuBuildItemData g_earlierMenuItems_451274[1];
extern struct MenuBuildItemData g_earlierMenuItems_4512BC[7];
extern struct MenuBuildDefinitionData g_earlierMenuDef_4513B8;
extern struct MenuBuildItemData g_earlierMenuItems_4513E0[2];
extern struct MenuBuildItemData g_earlierMenuItems_451450[49];
extern struct MenuBuildItemData g_earlierMenuItems_451B60[1];
extern struct MenuBuildItemData g_earlierMenuItems_451BD0[3];
extern struct MenuBuildItemData g_earlierMenuItems_451C3C[3];
extern struct MenuBuildItemData g_earlierMenuItems_451CA8[3];
extern struct MenuBuildItemData g_earlierMenuItems_451D14[3];
extern struct MenuBuildItemData g_earlierMenuItems_451F30[17];
extern struct MenuBuildDefinitionData g_earlierMenuDef_452194;
extern struct MenuBuildItemData g_earlierMenuItems_4521C0[5];
extern struct MenuBuildItemData g_earlierMenuItems_452298[7];
extern struct MenuBuildItemData g_earlierMenuItems_4523B8[11];
extern struct MenuBuildDefinitionData g_earlierMenuDef_452544;
extern struct MenuBuildItemData g_earlierMenuItems_452570[45];

struct MenuBuildItemData g_earlierMenuItems_44F420[22] = {
    { 0x0001, 0x0000, 0x90000000, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x00000385, (unsigned int)g_earlierMenuPaged_4411C4, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x08000041, 0x0000, 0x000A, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800E2FE8, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_40A61C, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00010041, 0x0000, -8, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800E3148, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_40A6A8, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00011001, 0x0000, 0x0006, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800E2FF8, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_4080E4, (unsigned int)g_earlierMenuPaged_40783C, 0x00000000 },
    { 0x0000, 0x0000, 0x00011001, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800E3008, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_4080E4, (unsigned int)g_earlierMenuPaged_40783C, 0x00000000 },
    { 0x0000, 0x0000, 0x00011001, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800E3018, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_4080E4, (unsigned int)g_earlierMenuPaged_40783C, 0x00000000 },
    { 0x0000, 0x0000, 0x00011001, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800E3028, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_4080E4, (unsigned int)g_earlierMenuPaged_40783C, 0x00000000 },
    { 0x0000, 0x0000, 0x00011001, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800E3038, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_4080E4, (unsigned int)g_earlierMenuPaged_40783C, 0x00000000 },
    { 0x0000, 0x0000, 0x00011001, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800E3048, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_4080E4, (unsigned int)g_earlierMenuPaged_40783C, 0x00000000 },
    { 0x0000, 0x0000, 0x00011001, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800E3058, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_4080E4, (unsigned int)g_earlierMenuPaged_40783C, 0x00000000 },
    { 0x0000, 0x0000, 0x00011001, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800E3068, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_4080E4, (unsigned int)g_earlierMenuPaged_40783C, 0x00000000 },
    { 0x0000, 0x0000, 0x00011001, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800E3078, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_4080E4, (unsigned int)g_earlierMenuPaged_40783C, 0x00000000 },
    { 0x0000, 0x0000, 0x00011001, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800E3088, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_4080E4, (unsigned int)g_earlierMenuPaged_40783C, 0x00000000 },
    { 0x0000, 0x0000, 0x00011001, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800E3098, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_4080E4, (unsigned int)g_earlierMenuPaged_40783C, 0x00000000 },
    { 0x0000, 0x0000, 0x00011001, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800E30A8, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_4080E4, (unsigned int)g_earlierMenuPaged_40783C, 0x00000000 },
    { 0x0000, 0x0000, 0x00011001, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800E30B8, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_4080E4, (unsigned int)g_earlierMenuPaged_40783C, 0x00000000 },
    { 0x0000, 0x0000, 0x00011001, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800E30C8, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_4080E4, (unsigned int)g_earlierMenuPaged_40783C, 0x00000000 },
    { 0x0000, 0x0000, 0x00011001, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800E30D8, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_4080E4, (unsigned int)g_earlierMenuPaged_40783C, 0x00000000 },
    { 0x0000, 0x0000, 0x00011001, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800E30E8, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_4080E4, (unsigned int)g_earlierMenuPaged_40783C, 0x00000000 },
    { 0x0000, 0x0000, 0x00011001, 0x0000, 0x0003, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800E4BF8, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_4082D0, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00010041, 0x0000, 0x000A, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800E4BF8, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_40A550, (unsigned int)g_earlierMenuPaged_4084D4, 0x00000000 },
    { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0004, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800E3188, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_40A784, (unsigned int)g_earlierMenuPaged_4087C8, 0x00000000 },
};

struct MenuBuildDefinitionData g_earlierMenuDef_44F738 = { (unsigned int)g_earlierMenuItems_44F420, 0x0016, 0x0000, (unsigned int)g_earlierMenuPaged_406730, 0x00000000, (unsigned int)g_earlierMenuPaged_4424EC, (unsigned int)g_earlierMenuPaged_409F18, 0x0015, 0x0000, 0x0000, 0x0000, 0x00000000 };

struct MenuBuildDefinitionData g_earlierMenuDef_44F75C = { (unsigned int)g_earlierMenuItems_44F420, 0x0016, 0x0000, (unsigned int)g_earlierMenuPaged_4064A8, 0x00000000, (unsigned int)g_earlierMenuPaged_4424EC, (unsigned int)g_earlierMenuPaged_409F18, 0x0014, 0x0000, 0x0000, 0x0000, 0x00000000 };

struct MenuBuildDefinitionData g_earlierMenuDef_44F780 = { (unsigned int)g_earlierMenuItems_44F420, 0x0016, 0x0000, (unsigned int)g_earlierMenuPaged_4071A8, 0x00000000, (unsigned int)g_earlierMenuPaged_4424EC, (unsigned int)g_earlierMenuPaged_409FF8, 0x0015, 0x0000, 0x0000, 0x0000, 0x00000000 };

struct MenuBuildDefinitionData g_earlierMenuDef_44F7A4 = { (unsigned int)g_earlierMenuItems_44F420, 0x0016, 0x0000, (unsigned int)g_earlierMenuPaged_407030, 0x00000000, (unsigned int)g_earlierMenuPaged_4424EC, (unsigned int)g_earlierMenuPaged_409FF8, 0x0014, 0x0000, 0x0000, 0x0000, 0x00000000 };

struct MenuBuildDefinitionData g_earlierMenuDef_44F7C8 = { (unsigned int)g_earlierMenuItems_44F420, 0x0016, 0x0000, (unsigned int)g_earlierMenuPaged_406A88, 0x00000000, (unsigned int)g_earlierMenuPaged_4424EC, (unsigned int)g_earlierMenuPaged_40A11C, 0x0014, 0x0000, 0x0000, 0x0000, 0x00000000 };

struct MenuBuildItemData g_earlierMenuItems_44F7EC[10] = {
    { 0x0001, 0x0000, 0x90000000, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x00000385, (unsigned int)g_earlierMenuPaged_4411C4, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x08000801, 0x0000, 0x0008, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800E32D8, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_40A7CC, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0014, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800E4BF8, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_40A934, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0005, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800E3348, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_40A960, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00010041, 0x0000, 0x000A, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800E4BF8, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_40A800, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800E3328, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_40A85C, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800E3338, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_40A8C8, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0014, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800E33E8, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_40AA04, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00010040, 0x007D, 0x000A, 0x00, 0x01, 0x00, 0x00, (int)g_earlierMenuResource_800E3DE8, (unsigned int)g_earlierMenuPaged_442F6C, 0x00000000, (unsigned int)g_earlierMenuPaged_408A58, 0x00000000 },
    { 0x0000, 0x0000, 0x00024040, 0x000A, 0x0000, 0xFF, 0x00, 0x00, 0x00, (int)g_earlierMenuResource_800E3DF8, (unsigned int)g_earlierMenuPaged_442F6C, 0x00000000, (unsigned int)g_earlierMenuPaged_40AA38, 0x00000000 },
};

struct MenuBuildDefinitionData g_earlierMenuDef_44F954 = { (unsigned int)g_earlierMenuItems_44F7EC, 0x000A, 0x0000, (unsigned int)g_earlierMenuPaged_40A7A8, 0x00000000, (unsigned int)g_earlierMenuPaged_4424EC, 0x00000000, 0x0008, 0x0000, 0x0000, 0x0000, 0x00000000 };

struct MenuBuildDefinitionData g_earlierMenuDef_44F978 = { (unsigned int)g_earlierMenuItems_44F7EC, 0x000A, 0x0000, (unsigned int)g_earlierMenuPaged_40A7BC, 0x00000000, (unsigned int)g_earlierMenuPaged_4424EC, 0x00000000, 0x0009, 0x0000, 0x0000, 0x0000, 0x00000000 };

struct MenuBuildItemData g_earlierMenuItems_44F99C[9] = {
    { 0x0001, 0x0000, 0x90000000, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x00000385, (unsigned int)g_earlierMenuPaged_4411C4, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x08000021, 0x0000, 0x0008, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800E3358, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_40AB18, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0032, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800E4BF8, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_40AB6C, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0002, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800E33B8, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_40AC68, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0002, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800E33C8, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_40ADC0, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0002, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800E33D8, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_408CAC, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0010, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800E33E8, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_40AE28, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00010040, 0x007D, 0x000A, 0x00, 0x01, 0x00, 0x00, (int)g_earlierMenuResource_800E3DE8, (unsigned int)g_earlierMenuPaged_442F6C, 0x00000000, (unsigned int)g_earlierMenuPaged_408F30, 0x00000000 },
    { 0x0000, 0x0000, 0x00024040, 0x000A, 0x0000, 0xFF, 0x00, 0x00, 0x00, (int)g_earlierMenuResource_800E3DF8, (unsigned int)g_earlierMenuPaged_442F6C, 0x00000000, (unsigned int)g_earlierMenuPaged_40AE7C, 0x00000000 },
};

struct MenuBuildDefinitionData g_earlierMenuDef_44FAE0 = { (unsigned int)g_earlierMenuItems_44F99C, 0x0009, 0x0000, (unsigned int)g_earlierMenuPaged_40AAA4, 0x00000000, (unsigned int)g_earlierMenuPaged_4424EC, 0x00000000, 0x0007, 0x0000, 0x0000, 0x0000, 0x00000000 };

struct MenuBuildDefinitionData g_earlierMenuDef_44FB04 = { (unsigned int)g_earlierMenuItems_44F99C, 0x0009, 0x0000, (unsigned int)g_earlierMenuPaged_40AAC0, 0x00000000, (unsigned int)g_earlierMenuPaged_4424EC, 0x00000000, 0x0008, 0x0000, 0x0000, 0x0000, 0x00000000 };

struct MenuBuildDefinitionData g_earlierMenuDef_44FB28 = { (unsigned int)g_earlierMenuItems_44F99C, 0x0009, 0x0000, (unsigned int)g_earlierMenuPaged_40AAD8, 0x00000000, (unsigned int)g_earlierMenuPaged_4424EC, 0x00000000, 0x0008, 0x0000, 0x0000, 0x0000, 0x00000000 };

struct MenuBuildItemData g_earlierMenuItems_44FB4C[8] = {
    { 0x0001, 0x0000, 0x90000000, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x00000385, (unsigned int)g_earlierMenuPaged_4411C4, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x08000021, 0x0000, 0x0008, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800E4BF8, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_40B084, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00010041, 0x0000, 0x001E, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800E4BF8, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_40B0D0, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0005, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800E4BF8, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_40B1FC, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0005, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800E4BF8, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_40B328, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0005, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800E4BF8, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_40B454, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0005, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800E4BF8, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_40B580, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0019, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800E3438, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_40B6AC, (unsigned int)g_earlierMenuPaged_4090D4, 0x00000000 },
};

struct MenuBuildDefinitionData g_earlierMenuDef_44FC6C = { (unsigned int)g_earlierMenuItems_44FB4C, 0x0008, 0x0000, (unsigned int)g_earlierMenuPaged_40AEE8, 0x00000000, (unsigned int)g_earlierMenuPaged_4424EC, 0x00000000, 0x0007, 0x0000, 0x0000, 0x0000, 0x00000000 };

struct MenuBuildDefinitionData g_earlierMenuDef_44FC90 = { (unsigned int)g_earlierMenuItems_44FB4C, 0x0008, 0x0000, (unsigned int)g_earlierMenuPaged_40AEF8, 0x00000000, (unsigned int)g_earlierMenuPaged_4424EC, 0x00000000, 0x0007, 0x0000, 0x0000, 0x0000, 0x00000000 };

struct MenuBuildDefinitionData g_earlierMenuDef_44FCB4 = { (unsigned int)g_earlierMenuItems_44FB4C, 0x0008, 0x0000, (unsigned int)g_earlierMenuPaged_40AF0C, 0x00000000, (unsigned int)g_earlierMenuPaged_4424EC, 0x00000000, 0x0007, 0x0000, 0x0000, 0x0000, 0x00000000 };

struct MenuBuildDefinitionData g_earlierMenuDef_44FCD8 = { (unsigned int)g_earlierMenuItems_44FB4C, 0x0008, 0x0000, (unsigned int)g_earlierMenuPaged_40AF20, 0x00000000, (unsigned int)g_earlierMenuPaged_4424EC, 0x00000000, 0x0007, 0x0000, 0x0000, 0x0000, 0x00000000 };

struct MenuBuildDefinitionData g_earlierMenuDef_44FCFC = { (unsigned int)g_earlierMenuItems_44FB4C, 0x0008, 0x0000, (unsigned int)g_earlierMenuPaged_40AF34, 0x00000000, (unsigned int)g_earlierMenuPaged_4424EC, 0x00000000, 0x0007, 0x0000, 0x0000, 0x0000, 0x00000000 };

struct MenuBuildDefinitionData g_earlierMenuDef_44FD20 = { (unsigned int)g_earlierMenuItems_44FB4C, 0x0008, 0x0000, (unsigned int)g_earlierMenuPaged_40AF48, 0x00000000, (unsigned int)g_earlierMenuPaged_4424EC, 0x00000000, 0x0007, 0x0000, 0x0000, 0x0000, 0x00000000 };

struct MenuBuildDefinitionData g_earlierMenuDef_44FD44 = { (unsigned int)g_earlierMenuItems_44FB4C, 0x0008, 0x0000, (unsigned int)g_earlierMenuPaged_40AF5C, 0x00000000, (unsigned int)g_earlierMenuPaged_4424EC, 0x00000000, 0x0007, 0x0000, 0x0000, 0x0000, 0x00000000 };

struct MenuBuildDefinitionData g_earlierMenuDef_44FD68 = { (unsigned int)g_earlierMenuItems_44FB4C, 0x0008, 0x0000, (unsigned int)g_earlierMenuPaged_40AF70, 0x00000000, (unsigned int)g_earlierMenuPaged_4424EC, 0x00000000, 0x0007, 0x0000, 0x0000, 0x0000, 0x00000000 };

struct MenuBuildDefinitionData g_earlierMenuDef_44FD8C = { (unsigned int)g_earlierMenuItems_44FB4C, 0x0008, 0x0000, (unsigned int)g_earlierMenuPaged_40AF84, 0x00000000, (unsigned int)g_earlierMenuPaged_4424EC, 0x00000000, 0x0007, 0x0000, 0x0000, 0x0000, 0x00000000 };

struct MenuBuildDefinitionData g_earlierMenuDef_44FDB0 = { (unsigned int)g_earlierMenuItems_44FB4C, 0x0008, 0x0000, (unsigned int)g_earlierMenuPaged_40AFD0, 0x00000000, (unsigned int)g_earlierMenuPaged_4424EC, 0x00000000, 0x0007, 0x0000, 0x0000, 0x0000, 0x00000000 };

struct MenuBuildDefinitionData g_earlierMenuDef_44FDD4 = { (unsigned int)g_earlierMenuItems_44FB4C, 0x0008, 0x0000, (unsigned int)g_earlierMenuPaged_40AFEC, 0x00000000, (unsigned int)g_earlierMenuPaged_4424EC, 0x00000000, 0x0007, 0x0000, 0x0000, 0x0000, 0x00000000 };

struct MenuBuildDefinitionData g_earlierMenuDef_44FDF8 = { (unsigned int)g_earlierMenuItems_44FB4C, 0x0008, 0x0000, (unsigned int)g_earlierMenuPaged_40B00C, 0x00000000, (unsigned int)g_earlierMenuPaged_4424EC, 0x00000000, 0x0007, 0x0000, 0x0000, 0x0000, 0x00000000 };

struct MenuBuildDefinitionData g_earlierMenuDef_44FE1C = { (unsigned int)g_earlierMenuItems_44FB4C, 0x0008, 0x0000, (unsigned int)g_earlierMenuPaged_40B020, 0x00000000, (unsigned int)g_earlierMenuPaged_4424EC, 0x00000000, 0x0007, 0x0000, 0x0000, 0x0000, 0x00000000 };

struct MenuBuildDefinitionData g_earlierMenuDef_44FE40 = { (unsigned int)g_earlierMenuItems_44FB4C, 0x0008, 0x0000, (unsigned int)g_earlierMenuPaged_40B034, 0x00000000, (unsigned int)g_earlierMenuPaged_4424EC, 0x00000000, 0x0007, 0x0000, 0x0000, 0x0000, 0x00000000 };

struct MenuBuildDefinitionData g_earlierMenuDef_44FE64 = { (unsigned int)g_earlierMenuItems_44FB4C, 0x0008, 0x0000, (unsigned int)g_earlierMenuPaged_40B070, 0x00000000, (unsigned int)g_earlierMenuPaged_4424EC, 0x00000000, 0x0007, 0x0000, 0x0000, 0x0000, 0x00000000 };

struct MenuBuildDefinitionData g_earlierMenuDef_44FE88 = { (unsigned int)g_earlierMenuItems_44FB4C, 0x0008, 0x0000, (unsigned int)g_earlierMenuPaged_40B048, 0x00000000, (unsigned int)g_earlierMenuPaged_4424EC, 0x00000000, 0x0007, 0x0000, 0x0000, 0x0000, 0x00000000 };

struct MenuBuildDefinitionData g_earlierMenuDef_44FEAC = { (unsigned int)g_earlierMenuItems_44FB4C, 0x0008, 0x0000, (unsigned int)g_earlierMenuPaged_40B05C, 0x00000000, (unsigned int)g_earlierMenuPaged_4424EC, 0x00000000, 0x0007, 0x0000, 0x0000, 0x0000, 0x00000000 };

struct MenuBuildItemData g_earlierMenuItems_44FED0[8] = {
    { 0x0001, 0x0000, 0x90000000, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x00000385, (unsigned int)g_earlierMenuPaged_4411C4, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x08000021, 0x0000, 0x0008, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800E3958, (unsigned int)g_earlierMenuPaged_442F6C, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0028, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800E4BF8, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_40B80C, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800E4BF8, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_40B840, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800E4BF8, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_40B874, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0014, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800E39C8, (unsigned int)g_earlierMenuPaged_442F6C, 0x00000000, (unsigned int)g_earlierMenuPaged_40B920, 0x00000000 },
    { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0005, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800E39D8, (unsigned int)g_earlierMenuPaged_442F6C, 0x00000000, (unsigned int)g_earlierMenuPaged_40B9CC, 0x00000000 },
    { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0005, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800E4BF8, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_40BB0C, (unsigned int)g_earlierMenuPaged_40BA88, 0x00000000 },
};

struct MenuBuildDefinitionData g_earlierMenuDef_44FFF0 = { (unsigned int)g_earlierMenuItems_44FED0, 0x0008, 0x0000, (unsigned int)g_earlierMenuPaged_40B7D8, 0x00000000, (unsigned int)g_earlierMenuPaged_4424EC, (unsigned int)g_earlierMenuPaged_40B6F8, 0x0007, 0x0000, 0x0000, 0x0000, 0x00000000 };

struct MenuBuildDefinitionData g_earlierMenuDef_450014 = { (unsigned int)g_earlierMenuItems_44FED0, 0x0008, 0x0000, (unsigned int)g_earlierMenuPaged_40B7F4, 0x00000000, (unsigned int)g_earlierMenuPaged_4424EC, (unsigned int)g_earlierMenuPaged_40B6F8, 0x0005, 0x0000, 0x0000, 0x0000, 0x00000000 };

struct MenuBuildItemData g_earlierMenuItems_450038[8] = {
    { 0x0001, 0x0000, 0x90000000, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x00000385, (unsigned int)g_earlierMenuPaged_4411C4, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x08000801, 0x0000, 0x0008, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800E4BF8, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_40BCA8, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0023, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800E4BF8, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_40BD24, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0004, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800E4BF8, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_40BDA0, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0004, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800E4BF8, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_40BE1C, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0004, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800E4BF8, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_40BE98, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00012001, 0x0000, 0x0023, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800E3BC8, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_40BF14, (unsigned int)g_earlierMenuPaged_409428, 0x00000000 },
    { 0x0000, 0x0000, 0x00012001, 0x0000, 0x0005, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800E3BD8, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_40BF80, (unsigned int)g_earlierMenuPaged_40972C, 0x00000000 },
};

struct MenuBuildDefinitionData g_earlierMenuDef_450158 = { (unsigned int)g_earlierMenuItems_450038, 0x0008, 0x0000, (unsigned int)g_earlierMenuPaged_40BC20, 0x00000000, (unsigned int)g_earlierMenuPaged_4424EC, (unsigned int)g_earlierMenuPaged_40BB40, 0x0007, 0x0000, 0x0000, 0x0000, 0x00000000 };

struct MenuBuildDefinitionData g_earlierMenuDef_45017C = { (unsigned int)g_earlierMenuItems_450038, 0x0008, 0x0000, (unsigned int)g_earlierMenuPaged_40BC38, 0x00000000, (unsigned int)g_earlierMenuPaged_4424EC, (unsigned int)g_earlierMenuPaged_40BB40, 0x0007, 0x0000, 0x0000, 0x0000, 0x00000000 };

struct MenuBuildDefinitionData g_earlierMenuDef_4501A0 = { (unsigned int)g_earlierMenuItems_450038, 0x0008, 0x0000, (unsigned int)g_earlierMenuPaged_40BC54, 0x00000000, (unsigned int)g_earlierMenuPaged_4424EC, (unsigned int)g_earlierMenuPaged_40BB40, 0x0007, 0x0000, 0x0000, 0x0000, 0x00000000 };

struct MenuBuildDefinitionData g_earlierMenuDef_4501C4 = { (unsigned int)g_earlierMenuItems_450038, 0x0008, 0x0000, (unsigned int)g_earlierMenuPaged_40BC70, 0x00000000, (unsigned int)g_earlierMenuPaged_4424EC, (unsigned int)g_earlierMenuPaged_40BB40, 0x0007, 0x0000, 0x0000, 0x0000, 0x00000000 };

struct MenuBuildDefinitionData g_earlierMenuDef_4501E8 = { (unsigned int)g_earlierMenuItems_450038, 0x0008, 0x0000, (unsigned int)g_earlierMenuPaged_40BC8C, 0x00000000, (unsigned int)g_earlierMenuPaged_4424EC, (unsigned int)g_earlierMenuPaged_40BB40, 0x0007, 0x0000, 0x0000, 0x0000, 0x00000000 };

unsigned int g_earlierMenuWords_45020C[1] = { 0x00010201 };

struct EarlierOptionBitRow g_earlierOptionBits_450210[12] = {
    { g_earlierOptionWord_800EF1FC, g_earlierOptionName_800E3F28, 0x00000020, 0x00000001 },
    { g_earlierOptionWord_800EF1EC, g_earlierOptionName_800E3F48, 0x00000080, 0x00000001 },
    { g_earlierOptionWord_800EF1E4, g_earlierOptionName_800E3F58, 0x00000100, 0x00000001 },
    { g_earlierOptionWord_800EF1D8, g_earlierOptionName_800E3F38, 0x00000040, 0x00000001 },
    { g_earlierOptionWord_800EF1CC, g_earlierOptionName_800E3F68, 0x00000200, 0x00000001 },
    { g_earlierOptionWord_800EF1B8, g_earlierOptionName_800E3F78, 0x00000400, 0x00000001 },
    { g_earlierOptionWord_800EF1AC, g_earlierOptionName_800E3F88, 0x00000800, 0x00000001 },
    { g_earlierOptionWord_800EF1A4, g_earlierOptionName_800E3F98, 0x00001000, 0x00000001 },
    { g_earlierOptionWord_800EF198, g_earlierOptionName_800E3FB8, 0x00004000, 0x00000001 },
    { g_earlierOptionWord_800EF18C, g_earlierOptionName_800E3FC8, 0x00008000, 0x00000001 },
    { g_earlierOptionWord_800EF174, g_earlierOptionName_800F2D08, 0xFFFFFFFF, 0x00000001 },
    { g_earlierOptionWord_800EF160, g_earlierOptionName_800F2D30, 0x0400C7E0, 0x00000001 },
};

struct MenuBuildItemData g_earlierMenuItems_4502D0[33] = {
    { 0x0001, 0x0000, 0x50000000, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x00000385, (unsigned int)g_earlierMenuPaged_4411C4, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x08000801, 0x0000, 0x0008, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800E3E38, (unsigned int)g_earlierMenuPaged_442F6C, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00210041, 0x0000, 0x0014, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800F2CE4, (unsigned int)g_earlierMenuPaged_43D88C, (unsigned int)g_earlierMenuPaged_43DA10, (unsigned int)g_earlierMenuPaged_43DAE8, 0x00000000 },
    { 0x0000, 0x0000, 0x00010050, 0x0050, 0x0014, 0x06, 0x01, 0xFF, 0x07, (int)g_earlierMenuResource_800E4CBC, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_43DAF0, 0x00000000 },
    { 0x0000, 0x0000, 0x00024050, 0x0008, 0x0000, 0xFF, 0x01, 0xFE, 0x07, (int)g_earlierMenuResource_800E4CD0, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_43DAF0, 0x00000000 },
    { 0x0000, 0x0000, 0x00024050, 0x0008, 0x0000, 0xFF, 0x01, 0xFD, 0x07, (int)g_earlierMenuResource_800E4CE4, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_43DAF0, 0x00000000 },
    { 0x0000, 0x0000, 0x00024050, 0x0008, 0x0000, 0xFF, 0x01, 0xFC, 0x07, (int)g_earlierMenuResource_800E4CF8, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_43DAF0, 0x00000000 },
    { 0x0000, 0x0000, 0x00024050, 0x0008, 0x0000, 0xFF, 0x01, 0xFB, 0x07, (int)g_earlierMenuResource_800E4D0C, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_43DAF0, 0x00000000 },
    { 0x0000, 0x0000, 0x00024050, 0x0008, 0x0000, 0xFF, 0x01, 0xFA, 0x07, (int)g_earlierMenuResource_800E4D20, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_43DAF0, 0x00000000 },
    { 0x0000, 0x0000, 0x00024050, 0x0008, 0x0000, 0xFF, 0xFA, 0xF9, 0x07, (int)g_earlierMenuResource_800E4D34, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_43DAF0, 0x00000000 },
    { 0x0000, 0x0000, 0x00010050, 0x0050, 0x0008, 0x06, 0x01, 0xF9, 0x07, (int)g_earlierMenuResource_800E4D48, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_43DAF0, 0x00000000 },
    { 0x0000, 0x0000, 0x00024050, 0x0008, 0x0000, 0xFF, 0x01, 0xF9, 0x07, (int)g_earlierMenuResource_800E4D5C, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_43DAF0, 0x00000000 },
    { 0x0000, 0x0000, 0x00024050, 0x0008, 0x0000, 0xFF, 0x01, 0xF9, 0x07, (int)g_earlierMenuResource_800E4D70, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_43DAF0, 0x00000000 },
    { 0x0000, 0x0000, 0x00024050, 0x0008, 0x0000, 0xFF, 0x01, 0xF9, 0x07, (int)g_earlierMenuResource_800E4D84, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_43DAF0, 0x00000000 },
    { 0x0000, 0x0000, 0x00024050, 0x0008, 0x0000, 0xFF, 0x01, 0xF9, 0x07, (int)g_earlierMenuResource_800E4D98, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_43DAF0, 0x00000000 },
    { 0x0000, 0x0000, 0x00024050, 0x0008, 0x0000, 0xFF, 0x01, 0xF9, 0x07, (int)g_earlierMenuResource_800E4DAC, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_43DAF0, 0x00000000 },
    { 0x0000, 0x0000, 0x00024050, 0x0008, 0x0000, 0xFF, 0xFA, 0xF9, 0x07, (int)g_earlierMenuResource_800E4DC0, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_43DAF0, 0x00000000 },
    { 0x0000, 0x0000, 0x00010050, 0x0050, 0x0008, 0x06, 0x01, 0xF9, 0x07, (int)g_earlierMenuResource_800E4DD4, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_43DAF0, 0x00000000 },
    { 0x0000, 0x0000, 0x00024050, 0x0008, 0x0000, 0xFF, 0x01, 0xF9, 0x07, (int)g_earlierMenuResource_800E4DE8, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_43DAF0, 0x00000000 },
    { 0x0000, 0x0000, 0x00024050, 0x0008, 0x0000, 0xFF, 0x01, 0xF9, 0x07, (int)g_earlierMenuResource_800E4DFC, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_43DAF0, 0x00000000 },
    { 0x0000, 0x0000, 0x00024050, 0x0008, 0x0000, 0xFF, 0x01, 0xF9, 0x07, (int)g_earlierMenuResource_800E4E10, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_43DAF0, 0x00000000 },
    { 0x0000, 0x0000, 0x00024050, 0x0008, 0x0000, 0xFF, 0x01, 0xF9, 0x07, (int)g_earlierMenuResource_800E4E24, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_43DAF0, 0x00000000 },
    { 0x0000, 0x0000, 0x00024050, 0x0008, 0x0000, 0xFF, 0x01, 0xF9, 0x07, (int)g_earlierMenuResource_800E4E38, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_43DAF0, 0x00000000 },
    { 0x0000, 0x0000, 0x00024050, 0x0008, 0x0000, 0xFF, 0xFA, 0xF9, 0x07, (int)g_earlierMenuResource_800E4E4C, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_43DAF0, 0x00000000 },
    { 0x0000, 0x0000, 0x00010050, 0x0050, 0x0008, 0x06, 0x01, 0xF9, 0x08, (int)g_earlierMenuResource_800E4E60, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_43DAF0, 0x00000000 },
    { 0x0000, 0x0000, 0x00024050, 0x0008, 0x0000, 0xFF, 0x01, 0xF9, 0x07, (int)g_earlierMenuResource_800E4E74, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_43DAF0, 0x00000000 },
    { 0x0000, 0x0000, 0x00024050, 0x0008, 0x0000, 0xFF, 0x01, 0xF9, 0x06, (int)g_earlierMenuResource_800E4E88, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_43DAF0, 0x00000000 },
    { 0x0000, 0x0000, 0x00024050, 0x0008, 0x0000, 0xFF, 0x01, 0xF9, 0x05, (int)g_earlierMenuResource_800E4E9C, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_43DAF0, 0x00000000 },
    { 0x0000, 0x0000, 0x00024050, 0x0008, 0x0000, 0xFF, 0x01, 0xF9, 0x04, (int)g_earlierMenuResource_800E4EB0, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_43DAF0, 0x00000000 },
    { 0x0000, 0x0000, 0x00024050, 0x0008, 0x0000, 0xFF, 0x01, 0xF9, 0x03, (int)g_earlierMenuResource_800E4FA0, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_43DBC0, 0x00000000 },
    { 0x0000, 0x0000, 0x00024050, 0x0008, 0x0000, 0xFF, 0xFA, 0xF9, 0x02, (int)g_earlierMenuResource_800E4FB4, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_43DCE8, 0x00000000 },
    { 0x0000, 0x0000, 0x00011001, 0x0000, 0x0014, 0x00, 0x00, 0x00, 0x00, (int)g_earlierMenuResource_800E4BF8, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_43DE34, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00310201, 0x0000, 0x0018, 0x00, 0x00, 0xFE, 0xE2, (int)g_earlierMenuResource_800E3E78, (unsigned int)g_earlierMenuPaged_442F6C, 0x00000000, (unsigned int)g_earlierMenuPaged_4432AC, 0x00000000 },
};

struct MenuBuildDefinitionData g_earlierMenuDef_450774 = { (unsigned int)g_earlierMenuItems_4502D0, 0x0021, 0x0000, (unsigned int)g_earlierMenuPaged_43D878, 0x00000000, (unsigned int)g_earlierMenuPaged_4424EC, 0x00000000, 0x0002, 0x0000, 0x0000, 0x0000, 0x00000000 };

struct MenuBuildItemData g_earlierMenuItems_450798[20] = {
    { 0x0001, 0x0000, 0x50000000, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x00000385, (unsigned int)g_earlierMenuPaged_4411C4, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x08000021, 0x0000, 0x0008, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800E3E08, (unsigned int)g_earlierMenuPaged_442F6C, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00411001, 0x0000, 0x000C, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800E4098, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_43E168, (unsigned int)g_earlierMenuPaged_43E14C, 0x00000000 },
    { 0x0000, 0x0000, 0x00411001, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800E40B8, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_43E1F0, (unsigned int)g_earlierMenuPaged_43E1D4, 0x00000000 },
    { 0x0000, 0x0000, 0x00411001, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800E40D8, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_43E278, (unsigned int)g_earlierMenuPaged_43E25C, 0x00000000 },
    { 0x0000, 0x0000, 0x00411001, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800E40F8, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_43E300, (unsigned int)g_earlierMenuPaged_43E2E4, 0x00000000 },
    { 0x0000, 0x0000, 0x00411001, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800E4118, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_43E388, (unsigned int)g_earlierMenuPaged_43E36C, 0x00000000 },
    { 0x0000, 0x0000, 0x00411001, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800E4138, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_43E410, (unsigned int)g_earlierMenuPaged_43E3F4, 0x00000000 },
    { 0x0000, 0x0000, 0x00411001, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800E4158, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_43E498, (unsigned int)g_earlierMenuPaged_43E47C, 0x00000000 },
    { 0x0000, 0x0000, 0x00411001, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800E4198, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_43E5A8, (unsigned int)g_earlierMenuPaged_43E58C, 0x00000000 },
    { 0x0000, 0x0000, 0x00411001, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800E4178, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_43E520, (unsigned int)g_earlierMenuPaged_43E504, 0x00000000 },
    { 0x0000, 0x0000, 0x00411001, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800E41B8, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_43E630, (unsigned int)g_earlierMenuPaged_43E614, 0x00000000 },
    { 0x0000, 0x0000, 0x00411001, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800E41D8, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_43E6B8, (unsigned int)g_earlierMenuPaged_43E69C, 0x00000000 },
    { 0x0000, 0x0000, 0x00411001, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800E41F8, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_43E740, (unsigned int)g_earlierMenuPaged_43E724, 0x00000000 },
    { 0x0000, 0x0000, 0x00411001, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800E4218, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_43E7C8, (unsigned int)g_earlierMenuPaged_43E7AC, 0x00000000 },
    { 0x0000, 0x0000, 0x00411001, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800E4238, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_43E850, (unsigned int)g_earlierMenuPaged_43E834, 0x00000000 },
    { 0x0000, 0x0000, 0x00411001, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800E4258, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_43E8D8, (unsigned int)g_earlierMenuPaged_43E8BC, 0x00000000 },
    { 0x0000, 0x0000, 0x00411001, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800E4278, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_43E960, (unsigned int)g_earlierMenuPaged_43E944, 0x00000000 },
    { 0x0000, 0x0000, 0x00411001, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800E4BF8, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_43DFE0, (unsigned int)g_earlierMenuPaged_43D568, 0x00000000 },
    { 0x0000, 0x0000, 0x00000201, 0x0000, 0x00C0, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800E3E78, (unsigned int)g_earlierMenuPaged_442F6C, 0x00000000, (unsigned int)g_earlierMenuPaged_4432AC, 0x00000000 },
};

struct MenuBuildDefinitionData g_earlierMenuDef_450A68 = { (unsigned int)g_earlierMenuItems_450798, 0x0014, 0x0000, (unsigned int)g_earlierMenuPaged_43D430, 0x00000000, (unsigned int)g_earlierMenuPaged_4424EC, 0x00000000, 0x0013, 0x0000, 0x0000, 0x0000, 0x00000000 };

unsigned int g_earlierMenuWords_450A8C[1] = { 0x00000000 };

struct MenuBuildItemData g_earlierMenuItems_450A90[3] = {
    { 0x0000, 0x0000, 0x00000021, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800E3E88, (unsigned int)g_earlierMenuPaged_442F6C, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00010081, 0x0000, 0x0028, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800E3DE8, (unsigned int)g_earlierMenuPaged_442F6C, 0x00000000, (unsigned int)g_earlierMenuPaged_43E9D0, 0x00000000 },
    { 0x0000, 0x0000, 0x00010081, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800E3DF8, (unsigned int)g_earlierMenuPaged_442F6C, 0x00000000, (unsigned int)g_earlierMenuPaged_43E9F4, 0x00000000 },
};

struct MenuBuildDefinitionData g_earlierMenuDef_450AFC = { (unsigned int)g_earlierMenuItems_450A90, 0x0003, 0x0000, 0x00000000, 0x00000000, (unsigned int)g_earlierMenuPaged_4424EC, 0x00000000, 0x0001, 0x0000, 0x0000, 0x0000, 0x00000000 };

struct MenuBuildItemData g_earlierMenuItems_450B20[8] = {
    { 0x0000, 0x0000, 0x00011001, 0x0000, 0x0000, 0x00, 0x00, 0x00, 0x00, (int)g_earlierMenuResource_800E2E08, (unsigned int)g_earlierMenuPaged_442F6C, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00011001, 0x0000, 0x0000, 0x00, 0x00, 0x00, 0x00, (int)g_earlierMenuResource_800E2E18, (unsigned int)g_earlierMenuPaged_442F6C, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00011001, 0x0000, 0x0000, 0x00, 0x00, 0x00, 0x00, (int)g_earlierMenuResource_800E2E28, (unsigned int)g_earlierMenuPaged_442F6C, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00011001, 0x0000, 0x0000, 0x00, 0x00, 0x00, 0x00, (int)g_earlierMenuResource_800E2E38, (unsigned int)g_earlierMenuPaged_442F6C, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00011001, 0x0000, 0x0000, 0x00, 0x00, 0x00, 0x00, (int)g_earlierMenuResource_800E2E48, (unsigned int)g_earlierMenuPaged_442F6C, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00011001, 0x0000, 0x0000, 0x00, 0x00, 0x00, 0x00, (int)g_earlierMenuResource_800E2E58, (unsigned int)g_earlierMenuPaged_442F6C, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00011001, 0x0000, 0x0000, 0x00, 0x00, 0x00, 0x00, (int)g_earlierMenuResource_800E2E68, (unsigned int)g_earlierMenuPaged_442F6C, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0005, 0x00, 0x00, 0x00, 0x00, (int)g_earlierMenuResource_800E2DF8, (unsigned int)g_earlierMenuPaged_442F6C, 0x00000000, (unsigned int)g_earlierMenuPaged_43EF94, 0x00000000 },
};

struct MenuBuildDefinitionData g_earlierMenuDef_450C40 = { (unsigned int)g_earlierMenuItems_450B20, 0x0008, 0x0000, 0x00000000, 0x00000000, (unsigned int)g_earlierMenuPaged_4424EC, (unsigned int)g_earlierMenuPaged_43EF5C, 0x0007, 0x0000, 0x0000, 0x0000, (int)&g_earlierMenuDef_450D18 };

struct MenuBuildItemData g_earlierMenuItems_450C64[5] = {
    { 0x0000, 0x0000, 0x00011001, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x02, (int)g_earlierMenuResource_800E2D48, (unsigned int)g_earlierMenuPaged_442F6C, 0x00000000, (unsigned int)g_earlierMenuPaged_43F1C4, 0x00000000 },
    { 0x0000, 0x0000, 0x00010101, 0x0000, 0x0008, 0x00, 0x00, 0x00, 0x00, (int)g_earlierMenuResource_800E2D58, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_43F1F0, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00411001, 0x0000, 0x0008, 0x00, 0x00, 0xFE, 0x01, (int)g_earlierMenuResource_800E4BF8, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_43F074, (unsigned int)g_earlierMenuPaged_43F028, 0x00000000 },
    { 0x0000, 0x0000, 0x00411001, 0x0000, 0x0002, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800E2DC8, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_43F240, (unsigned int)g_earlierMenuPaged_43F178, 0x00000000 },
    { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0005, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800E2DF8, (unsigned int)g_earlierMenuPaged_442F6C, 0x00000000, (unsigned int)g_earlierMenuPaged_43F214, 0x00000000 },
};

struct MenuBuildDefinitionData g_earlierMenuDef_450D18 = { (unsigned int)g_earlierMenuItems_450C64, 0x0005, 0x0000, 0x00000000, 0x00000000, (unsigned int)g_earlierMenuPaged_4424EC, (unsigned int)g_earlierMenuPaged_43EFF0, 0x0004, 0x0000, 0x0000, 0x0000, (int)&g_earlierMenuDef_450DD8 };

struct EarlierMenuTuning g_earlierMenuTuning_450D3C = {
    0x00000460, 0x0000000B, 0x00000000, 0x00000000,
    -5e+01f, -9e+02f,
    { 2.0f, 2.0f, 2.0f },
    0x00000032, 0x00000050,
    0.087266475f,
};

struct MenuBuildItemData g_earlierMenuItems_450D6C[3] = {
    { 0x0001, 0x0000, 0x30000000, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x00000387, (unsigned int)g_earlierMenuPaged_4411C4, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0003, 0x0000, 0x00410021, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)&g_earlierMenuTuning_450D3C, (unsigned int)g_earlierMenuPaged_441730, (unsigned int)g_earlierMenuPaged_43F468, (unsigned int)g_earlierMenuPaged_43F37C, 0x00000000 },
    { 0x0000, 0x0000, 0x00010081, 0x0000, 0x0019, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800E2D38, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_43F374, (unsigned int)g_earlierMenuPaged_43F314, 0x00000000 },
};

struct MenuBuildDefinitionData g_earlierMenuDef_450DD8 = { (unsigned int)g_earlierMenuItems_450D6C, 0x0003, 0x0000, (unsigned int)g_earlierMenuPaged_43F28C, 0x00000000, (unsigned int)g_earlierMenuPaged_4424EC, (unsigned int)g_earlierMenuPaged_43F2DC, 0x0001, 0x0000, 0x0000, 0x0000, 0x00000000 };

struct MenuBuildDefinitionData g_earlierMenuDef_450DFC = { (unsigned int)g_earlierMenuItems_450D6C, 0x0003, 0x0000, (unsigned int)g_earlierMenuPaged_43F2B0, 0x00000000, (unsigned int)g_earlierMenuPaged_4424EC, (unsigned int)g_earlierMenuPaged_43F2DC, 0x0001, 0x0000, 0x0000, 0x0000, 0x00000000 };

struct MenuBuildItemData g_earlierMenuItems_450E20[4] = {
    { 0x0001, 0x0000, 0x30000000, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x00000387, (unsigned int)g_earlierMenuPaged_4411C4, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00010081, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800E2E88, (unsigned int)g_earlierMenuPaged_442F6C, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00010101, 0x0000, 0x000C, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800E2E98, (unsigned int)g_earlierMenuPaged_442F6C, 0x00000000, (unsigned int)g_earlierMenuPaged_43F4A8, 0x00000000 },
    { 0x0000, 0x0000, 0x00010101, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800E2EA8, (unsigned int)g_earlierMenuPaged_442F6C, 0x00000000, (unsigned int)g_earlierMenuPaged_43F4F0, 0x00000000 },
};

struct MenuBuildDefinitionData g_earlierMenuDef_450EB0 = { (unsigned int)g_earlierMenuItems_450E20, 0x0004, 0x0000, 0x00000000, 0x00000000, (unsigned int)g_earlierMenuPaged_4424EC, (unsigned int)g_earlierMenuPaged_43F470, 0x0002, 0x0000, 0x0000, 0x0000, 0x00000000 };

float g_earlierMenuRamp_450ED4[16] = {
    -0.5f, -0.4f, -0.3f, -0.2f, -0.1f, 0.0f, 0.1f, 0.2f,
    0.3f, 0.4f, 0.5f, 0.6f, 0.7f, 0.8f, 0.9f, 1.0f,
};

struct MenuBuildItemData g_earlierMenuItems_450F14[11] = {
    { 0x0001, 0x0000, 0x10000000, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x00000385, (unsigned int)g_earlierMenuPaged_4411C4, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x08000201, 0x0000, 0x000C, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800E4898, (unsigned int)g_earlierMenuPaged_442F6C, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00410041, 0x0000, 0x001E, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800E4BF8, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_43EA40, (unsigned int)g_earlierMenuPaged_43F6DC, 0x00000000 },
    { 0x0000, 0x0000, 0x00410041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800E4BF8, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_43EA40, (unsigned int)g_earlierMenuPaged_43F6DC, 0x00000000 },
    { 0x0000, 0x0000, 0x00410041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800E4BF8, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_43EA40, (unsigned int)g_earlierMenuPaged_43F6DC, 0x00000000 },
    { 0x0000, 0x0000, 0x00410041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800E4BF8, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_43EA40, (unsigned int)g_earlierMenuPaged_43F6DC, 0x00000000 },
    { 0x0000, 0x0000, 0x00410041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800E4BF8, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_43EA40, (unsigned int)g_earlierMenuPaged_43F6DC, 0x00000000 },
    { 0x0000, 0x0000, 0x00410041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800E4BF8, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_43EA40, (unsigned int)g_earlierMenuPaged_43F6DC, 0x00000000 },
    { 0x0000, 0x0000, 0x00410041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800E4BF8, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_43EA40, (unsigned int)g_earlierMenuPaged_43F6DC, 0x00000000 },
    { 0x0000, 0x0000, 0x00410041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800E4BF8, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_43EA40, (unsigned int)g_earlierMenuPaged_43F6DC, 0x00000000 },
    { 0x0000, 0x0000, 0x00010201, 0x0000, 0x002D, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800E3E78, (unsigned int)g_earlierMenuPaged_442F6C, 0x00000000, (unsigned int)g_earlierMenuPaged_4432AC, 0x00000000 },
};

struct MenuBuildDefinitionData g_earlierMenuDef_4510A0 = { (unsigned int)g_earlierMenuItems_450F14, 0x000B, 0x0000, 0x00000000, 0x00000000, (unsigned int)g_earlierMenuPaged_4424EC, 0x00000000, 0x000A, 0x0000, 0x0000, 0x0000, (int)&g_earlierMenuDef_451154 };

struct MenuBuildItemData g_earlierMenuItems_4510C4[4] = {
    { 0x0001, 0x0000, 0x10000000, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x00000385, (unsigned int)g_earlierMenuPaged_4411C4, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x08000021, 0x0000, 0x0008, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800E45E8, (unsigned int)g_earlierMenuPaged_442F6C, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00010081, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800E4898, (unsigned int)g_earlierMenuPaged_442F6C, 0x00000000, (unsigned int)g_earlierMenuPaged_43F7C8, 0x00000000 },
    { 0x0000, 0x0000, 0x00010201, 0x0000, 0x0038, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800E3E78, (unsigned int)g_earlierMenuPaged_442F6C, 0x00000000, (unsigned int)g_earlierMenuPaged_4432AC, 0x00000000 },
};

struct MenuBuildDefinitionData g_earlierMenuDef_451154 = { (unsigned int)g_earlierMenuItems_4510C4, 0x0004, 0x0000, 0x00000000, 0x00000000, (unsigned int)g_earlierMenuPaged_4424EC, 0x00000000, 0x0002, 0x0000, 0x0000, 0x0000, (int)&g_earlierMenuDef_4513B8 };

struct MenuBuildItemData g_earlierMenuItems_451178[5] = {
    { 0x0001, 0x0000, 0x10000000, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x00000385, (unsigned int)g_earlierMenuPaged_4411C4, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x08000801, 0x0000, 0x0008, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800E45A8, (unsigned int)g_earlierMenuPaged_442F6C, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00010081, 0x0000, 0x0036, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800E45B8, (unsigned int)g_earlierMenuPaged_442F6C, 0x00000000, (unsigned int)g_earlierMenuPaged_43F854, 0x00000000 },
    { 0x0000, 0x0000, 0x00010081, 0x0000, 0x0004, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800E45C8, (unsigned int)g_earlierMenuPaged_442F6C, 0x00000000, (unsigned int)g_earlierMenuPaged_43F8AC, 0x00000000 },
    { 0x0000, 0x0000, 0x00010201, 0x0000, 0x0049, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800E2D18, (unsigned int)g_earlierMenuPaged_442F6C, 0x00000000, (unsigned int)g_earlierMenuPaged_43F8F8, 0x00000000 },
};

struct MenuBuildDefinitionData g_earlierMenuDef_45122C = { (unsigned int)g_earlierMenuItems_451178, 0x0005, 0x0000, (unsigned int)g_earlierMenuPaged_43F7F4, 0x00000000, (unsigned int)g_earlierMenuPaged_4424EC, 0x00000000, 0x0002, 0x0000, 0x0000, 0x0000, 0x00000000 };

struct MenuBuildDefinitionData g_earlierMenuDef_451250 = { (unsigned int)g_earlierMenuItems_451178, 0x0005, 0x0000, (unsigned int)g_earlierMenuPaged_43F828, 0x00000000, (unsigned int)g_earlierMenuPaged_4424EC, 0x00000000, 0x0002, 0x0000, 0x0000, 0x0000, 0x00000000 };

struct MenuBuildItemData g_earlierMenuItems_451274[1] = {
    { 0x0001, 0x0000, 0x10000000, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x00000385, (unsigned int)g_earlierMenuPaged_4411C4, 0x00000000, 0x00000000, 0x00000000 },
};

struct MenuBuildDefinitionData g_earlierMenuDef_451298 = { (unsigned int)g_earlierMenuItems_451274, 0x0001, 0x0000, 0x00000000, 0x00000000, (unsigned int)g_earlierMenuPaged_4424EC, 0x00000000, 0x0002, 0x0000, 0x0000, 0x0000, (int)&g_earlierMenuDef_4513B8 };

struct MenuBuildItemData g_earlierMenuItems_4512BC[7] = {
    { 0x0001, 0x0000, 0x10000000, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x00000384, (unsigned int)g_earlierMenuPaged_4411C4, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00000081, 0x0000, 0x001E, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800E45A8, (unsigned int)g_earlierMenuPaged_442F6C, 0x00000000, (unsigned int)g_earlierMenuPaged_43F944, 0x00000000 },
    { 0x0000, 0x0000, 0x00010081, 0x0000, 0x000C, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800E45D8, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_43FA1C, (unsigned int)g_earlierMenuPaged_43FA90, 0x00000000 },
    { 0x0000, 0x0000, 0x00010081, 0x0000, 0x000C, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800E3E38, (unsigned int)g_earlierMenuPaged_442F6C, 0x00000000, (unsigned int)g_earlierMenuPaged_43FB18, 0x00000000 },
    { 0x0000, 0x0000, 0x00010081, 0x0000, 0x000C, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800E4A48, (unsigned int)g_earlierMenuPaged_442F6C, 0x00000000, (unsigned int)g_earlierMenuPaged_43FB44, 0x00000000 },
    { 0x0000, 0x0000, 0x00010081, 0x0000, 0x000C, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800E4A38, (unsigned int)g_earlierMenuPaged_442F6C, 0x00000000, (unsigned int)g_earlierMenuPaged_43FAEC, 0x00000000 },
    { 0x0000, 0x0000, 0x00010081, 0x0000, 0x000C, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800E4A78, (unsigned int)g_earlierMenuPaged_442F6C, 0x00000000, (unsigned int)g_earlierMenuPaged_43FB70, 0x00000000 },
};

struct MenuBuildDefinitionData g_earlierMenuDef_4513B8 = { (unsigned int)g_earlierMenuItems_4512BC, 0x0007, 0x0000, 0x00000000, 0x00000000, (unsigned int)g_earlierMenuPaged_4424EC, 0x00000000, 0x0001, 0x0000, 0x0000, 0x0000, 0x00000000 };

unsigned int g_earlierMenuWords_4513DC[1] = { 0x00000000 };

struct MenuBuildItemData g_earlierMenuItems_4513E0[2] = {
    { 0x0001, 0x0000, 0x00000000, 0x0000, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x00000064, (unsigned int)g_earlierMenuPaged_4411C4, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00000089, 0x0000, 0x0028, 0x00, 0x00, 0x00, 0x00, (int)g_earlierMenuResource_800E4FC8, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_43FCC4, 0x00000000, 0x00000000 },
};

struct MenuBuildDefinitionData g_earlierMenuDef_451428 = { (unsigned int)g_earlierMenuItems_4513E0, 0x0002, 0x0000, (unsigned int)g_earlierMenuPaged_43FC50, 0x00000000, (unsigned int)g_earlierMenuPaged_4424EC, (unsigned int)g_earlierMenuPaged_43FC7C, 0x0001, 0x0000, 0x0000, 0x0000, 0x00000000 };

unsigned int g_earlierMenuWords_45144C[1] = { 0x00010041 };

struct MenuBuildItemData g_earlierMenuItems_451450[49] = {
    { 0x0001, 0x0000, 0x50000000, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x00000385, (unsigned int)g_earlierMenuPaged_4411C4, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x08000801, 0x0000, 0x0008, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800E2F88, (unsigned int)g_earlierMenuPaged_442F6C, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00010080, 0x0023, 0x0016, 0x00, 0x00, 0x00, 0x00, (int)g_earlierMenuResource_800E4C18, (unsigned int)g_earlierMenuPaged_442F6C, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0001, 0x0000, 0x00024010, 0x0003, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x000007D0, (unsigned int)g_earlierMenuPaged_43FD00, 0x00000000, 0x00000000, 0x10D60000 },
    { 0x0001, 0x0000, 0x00024010, 0x0003, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x000007D0, (unsigned int)g_earlierMenuPaged_43FD00, 0x00000000, 0x00000000, 0x10D60001 },
    { 0x0001, 0x0000, 0x00024010, 0x0003, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x000007D0, (unsigned int)g_earlierMenuPaged_43FD00, 0x00000000, 0x00000000, 0x10D60002 },
    { 0x0001, 0x0000, 0x00024010, 0x0003, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x000007D1, (unsigned int)g_earlierMenuPaged_43FD00, 0x00000000, 0x00000000, 0x10E00000 },
    { 0x0001, 0x0000, 0x00024010, 0x0003, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x000007D1, (unsigned int)g_earlierMenuPaged_43FD00, 0x00000000, 0x00000000, 0x10E00001 },
    { 0x0001, 0x0000, 0x00024010, 0x0003, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x000007D1, (unsigned int)g_earlierMenuPaged_43FD00, 0x00000000, 0x00000000, 0x10E00002 },
    { 0x0001, 0x0000, 0x00024010, 0x0029, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x000007E4, (unsigned int)g_earlierMenuPaged_43FD00, 0x00000000, 0x00000000, 0x11080000 },
    { 0x0001, 0x0000, 0x00024010, 0x0003, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x00000820, (unsigned int)g_earlierMenuPaged_43FD00, 0x00000000, 0x00000000, 0x11940000 },
    { 0x0000, 0x0000, 0x00010080, 0x0023, 0x0003, 0x00, 0x00, 0x00, 0x00, (int)g_earlierMenuResource_800E4C28, (unsigned int)g_earlierMenuPaged_442F6C, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0001, 0x0000, 0x00024010, 0x0003, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x000007D2, (unsigned int)g_earlierMenuPaged_43FD00, 0x00000000, 0x00000000, 0x10EA0000 },
    { 0x0001, 0x0000, 0x00024010, 0x0003, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x000007D2, (unsigned int)g_earlierMenuPaged_43FD00, 0x00000000, 0x00000000, 0x10EA0001 },
    { 0x0001, 0x0000, 0x00024010, 0x0003, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x000007D2, (unsigned int)g_earlierMenuPaged_43FD00, 0x00000000, 0x00000000, 0x10EA0002 },
    { 0x0001, 0x0000, 0x00024010, 0x003C, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x0000080D, (unsigned int)g_earlierMenuPaged_43FD00, 0x00000000, 0x00000000, 0x11320000 },
    { 0x0001, 0x0000, 0x00024010, 0x0003, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x000007F9, (unsigned int)g_earlierMenuPaged_43FD00, 0x00000000, 0x00000000, 0x111E0000 },
    { 0x0001, 0x0000, 0x00024010, 0x0003, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x000007E5, (unsigned int)g_earlierMenuPaged_43FD00, 0x00000000, 0x00000000, 0x11090000 },
    { 0x0001, 0x0000, 0x00024010, 0x0003, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x00000820, (unsigned int)g_earlierMenuPaged_43FD00, 0x00000000, 0x00000000, 0x11940001 },
    { 0x0000, 0x0000, 0x00010080, 0x0023, 0x0003, 0x00, 0x00, 0x00, 0x00, (int)g_earlierMenuResource_800E4C38, (unsigned int)g_earlierMenuPaged_442F6C, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0001, 0x0000, 0x00024010, 0x0003, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x000007D3, (unsigned int)g_earlierMenuPaged_43FD00, 0x00000000, 0x00000000, 0x10F40000 },
    { 0x0001, 0x0000, 0x00024010, 0x0003, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x000007D3, (unsigned int)g_earlierMenuPaged_43FD00, 0x00000000, 0x00000000, 0x10F40001 },
    { 0x0001, 0x0000, 0x00024010, 0x0003, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x000007D3, (unsigned int)g_earlierMenuPaged_43FD00, 0x00000000, 0x00000000, 0x10F40002 },
    { 0x0001, 0x0000, 0x00024010, 0x003C, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x0000080F, (unsigned int)g_earlierMenuPaged_43FD00, 0x00000000, 0x00000000, 0x11300000 },
    { 0x0001, 0x0000, 0x00024010, 0x0003, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x000007F8, (unsigned int)g_earlierMenuPaged_43FD00, 0x00000000, 0x00000000, 0x111C0000 },
    { 0x0001, 0x0000, 0x00024010, 0x0003, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x000007E6, (unsigned int)g_earlierMenuPaged_43FD00, 0x00000000, 0x00000000, 0x110A0000 },
    { 0x0001, 0x0000, 0x00024010, 0x0003, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x00000820, (unsigned int)g_earlierMenuPaged_43FD00, 0x00000000, 0x00000000, 0x11940002 },
    { 0x0000, 0x0000, 0x00010080, 0x0023, 0x0003, 0x00, 0x00, 0x00, 0x00, (int)g_earlierMenuResource_800E4C48, (unsigned int)g_earlierMenuPaged_442F6C, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0001, 0x0000, 0x00024010, 0x0003, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x000007D4, (unsigned int)g_earlierMenuPaged_43FD00, 0x00000000, 0x00000000, 0x10FE0000 },
    { 0x0001, 0x0000, 0x00024010, 0x0003, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x000007D4, (unsigned int)g_earlierMenuPaged_43FD00, 0x00000000, 0x00000000, 0x10FE0001 },
    { 0x0001, 0x0000, 0x00024010, 0x0003, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x000007D4, (unsigned int)g_earlierMenuPaged_43FD00, 0x00000000, 0x00000000, 0x10FE0002 },
    { 0x0001, 0x0000, 0x00024010, 0x003C, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x0000080E, (unsigned int)g_earlierMenuPaged_43FD00, 0x00000000, 0x00000000, 0x11340000 },
    { 0x0001, 0x0000, 0x00024010, 0x0003, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x000007FC, (unsigned int)g_earlierMenuPaged_43FD00, 0x00000000, 0x00000000, 0x11200000 },
    { 0x0001, 0x0000, 0x00024010, 0x0003, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x000007E7, (unsigned int)g_earlierMenuPaged_43FD00, 0x00000000, 0x00000000, 0x110B0000 },
    { 0x0001, 0x0000, 0x00024010, 0x0003, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x00000820, (unsigned int)g_earlierMenuPaged_43FD00, 0x00000000, 0x00000000, 0x11940003 },
    { 0x0000, 0x0000, 0x00010080, 0x0023, 0x0003, 0x00, 0x00, 0x00, 0x00, (int)g_earlierMenuResource_800E4C58, (unsigned int)g_earlierMenuPaged_442F6C, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0001, 0x0000, 0x00024010, 0x0003, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x000007D4, (unsigned int)g_earlierMenuPaged_43FD00, 0x00000000, 0x00000000, 0x10FE0003 },
    { 0x0001, 0x0000, 0x00024010, 0x0003, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x000007D4, (unsigned int)g_earlierMenuPaged_43FD00, 0x00000000, 0x00000000, 0x10FE0004 },
    { 0x0001, 0x0000, 0x00024010, 0x0003, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x000007D4, (unsigned int)g_earlierMenuPaged_43FD00, 0x00000000, 0x00000000, 0x10FE0005 },
    { 0x0001, 0x0000, 0x00024010, 0x003C, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x0000080C, (unsigned int)g_earlierMenuPaged_43FD00, 0x00000000, 0x00000000, 0x11330000 },
    { 0x0001, 0x0000, 0x00024010, 0x0003, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x000007FB, (unsigned int)g_earlierMenuPaged_43FD00, 0x00000000, 0x00000000, 0x111F0000 },
    { 0x0001, 0x0000, 0x00024010, 0x0003, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x000007E8, (unsigned int)g_earlierMenuPaged_43FD00, 0x00000000, 0x00000000, 0x110C0000 },
    { 0x0001, 0x0000, 0x00024010, 0x0003, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x00000820, (unsigned int)g_earlierMenuPaged_43FD00, 0x00000000, 0x00000000, 0x11940004 },
    { 0x0000, 0x0000, 0x00010080, 0x0023, 0x0003, 0x00, 0x00, 0x00, 0x00, (int)g_earlierMenuResource_800E4C68, (unsigned int)g_earlierMenuPaged_442F6C, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0001, 0x0000, 0x00024010, 0x0075, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x00000810, (unsigned int)g_earlierMenuPaged_43FD00, 0x00000000, 0x00000000, 0x11310000 },
    { 0x0001, 0x0000, 0x00024010, 0x0003, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x000007FA, (unsigned int)g_earlierMenuPaged_43FD00, 0x00000000, 0x00000000, 0x111D0000 },
    { 0x0001, 0x0000, 0x00024010, 0x0003, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x000007E9, (unsigned int)g_earlierMenuPaged_43FD00, 0x00000000, 0x00000000, 0x110D0000 },
    { 0x0001, 0x0000, 0x00024010, 0x0003, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x00000820, (unsigned int)g_earlierMenuPaged_43FD00, 0x00000000, 0x00000000, 0x11940005 },
    { 0x0000, 0x0000, 0x00010081, 0x0000, 0x001E, 0x00, 0x00, 0x00, 0x00, (int)g_earlierMenuResource_800E2F98, (unsigned int)g_earlierMenuPaged_442F6C, 0x00000000, (unsigned int)g_earlierMenuPaged_43FF68, 0x00000000 },
};

struct MenuBuildDefinitionData g_earlierMenuDef_451B34 = { (unsigned int)g_earlierMenuItems_451450, 0x0031, 0x0000, (unsigned int)g_earlierMenuPaged_43FEE0, 0x00000000, (unsigned int)g_earlierMenuPaged_4424EC, 0x00000000, 0x0030, 0x0000, 0x0000, 0x0000, (int)&g_earlierMenuDef_452544 };

unsigned int g_earlierMenuWords_451B58[2] = { 0x00000000, 0x00024110 };

struct MenuBuildItemData g_earlierMenuItems_451B60[1] = {
    { 0x0001, 0x0000, 0x50000000, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x00000385, (unsigned int)g_earlierMenuPaged_4411C4, 0x00000000, 0x00000000, 0x00000000 },
};

struct MenuBuildDefinitionData g_earlierMenuDef_451B84 = { (unsigned int)g_earlierMenuItems_451B60, 0x0001, 0x0000, (unsigned int)g_earlierMenuPaged_444310, 0x00000000, (unsigned int)g_earlierMenuPaged_4424EC, 0x00000000, 0x0009, 0x0000, 0x0000, 0x0000, (int)&g_earlierMenuDef_452194 };

struct MenuBuildDefinitionData g_earlierMenuDef_451BA8 = { (unsigned int)g_earlierMenuItems_451B60, 0x0001, 0x0000, (unsigned int)g_earlierMenuPaged_444348, 0x00000000, (unsigned int)g_earlierMenuPaged_4424EC, 0x00000000, 0x0009, 0x0000, 0x0000, 0x0000, 0x00000000 };

unsigned int g_earlierMenuWords_451BCC[1] = { 0x00446920 };

struct MenuBuildItemData g_earlierMenuItems_451BD0[3] = {
    { 0x0001, 0x0000, 0x50000000, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x00000385, (unsigned int)g_earlierMenuPaged_4411C4, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00000401, 0x0000, 0x0028, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800E4368, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_444430, 0x00000000, 0x00000000 },
    { 0x0001, 0x0000, 0x20010001, 0x0000, 0x0000, 0x00, 0x00, 0x00, 0x01, 0x0000012D, (unsigned int)g_earlierMenuPaged_444778, 0x00000000, (unsigned int)g_earlierMenuPaged_444754, 0x00000000 },
};

struct MenuBuildItemData g_earlierMenuItems_451C3C[3] = {
    { 0x0001, 0x0000, 0x50000000, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x00000385, (unsigned int)g_earlierMenuPaged_4411C4, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00000401, 0x0000, 0x0028, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800E43E8, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_444430, 0x00000000, 0x00000000 },
    { 0x0001, 0x0000, 0x20010001, -20, 0x0000, 0xEC, 0x00, 0x00, 0x01, 0x0000012D, (unsigned int)g_earlierMenuPaged_444778, 0x00000000, (unsigned int)g_earlierMenuPaged_444754, 0x00000000 },
};

struct MenuBuildItemData g_earlierMenuItems_451CA8[3] = {
    { 0x0001, 0x0000, 0x50000000, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x00000385, (unsigned int)g_earlierMenuPaged_4411C4, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00000401, 0x0000, 0x0028, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800E4468, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_444430, 0x00000000, 0x00000000 },
    { 0x0001, 0x0000, 0x20010001, 0x0000, 0x0000, 0x00, 0x00, 0x00, 0x01, 0x0000012D, (unsigned int)g_earlierMenuPaged_444778, 0x00000000, (unsigned int)g_earlierMenuPaged_444754, 0x00000000 },
};

struct MenuBuildItemData g_earlierMenuItems_451D14[3] = {
    { 0x0001, 0x0000, 0x50000000, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x00000385, (unsigned int)g_earlierMenuPaged_4411C4, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00000401, 0x0000, 0x0028, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800E44E8, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_444430, 0x00000000, 0x00000000 },
    { 0x0001, 0x0000, 0x20010001, 0x0000, 0x0000, 0x00, 0x00, 0x00, 0x01, 0x0000012D, (unsigned int)g_earlierMenuPaged_444778, 0x00000000, (unsigned int)g_earlierMenuPaged_444754, 0x00000000 },
};

struct MenuBuildDefinitionData g_earlierMenuDef_451D80 = { (unsigned int)g_earlierMenuItems_451BD0, 0x0003, 0x0000, (unsigned int)g_earlierMenuPaged_444C88, 0x00000000, (unsigned int)g_earlierMenuPaged_4424EC, (unsigned int)g_earlierMenuPaged_444900, 0x0002, 0x0000, 0x0000, 0x0000, 0x00000000 };

struct MenuBuildDefinitionData g_earlierMenuDef_451DA4 = { (unsigned int)g_earlierMenuItems_451C3C, 0x0003, 0x0000, (unsigned int)g_earlierMenuPaged_444C88, 0x00000000, (unsigned int)g_earlierMenuPaged_4424EC, (unsigned int)g_earlierMenuPaged_444900, 0x0002, 0x0000, 0x0000, 0x0000, 0x00000000 };

struct MenuBuildDefinitionData g_earlierMenuDef_451DC8 = { (unsigned int)g_earlierMenuItems_451CA8, 0x0003, 0x0000, (unsigned int)g_earlierMenuPaged_444C88, 0x00000000, (unsigned int)g_earlierMenuPaged_4424EC, (unsigned int)g_earlierMenuPaged_444900, 0x0002, 0x0000, 0x0000, 0x0000, 0x00000000 };

struct MenuBuildDefinitionData g_earlierMenuDef_451DEC = { (unsigned int)g_earlierMenuItems_451D14, 0x0003, 0x0000, (unsigned int)g_earlierMenuPaged_444C88, 0x00000000, (unsigned int)g_earlierMenuPaged_4424EC, (unsigned int)g_earlierMenuPaged_444900, 0x0002, 0x0000, 0x0000, 0x0000, 0x00000000 };

struct MenuBuildDefinitionData g_earlierMenuDef_451E10 = { (unsigned int)g_earlierMenuItems_451BD0, 0x0003, 0x0000, (unsigned int)g_earlierMenuPaged_444D48, 0x00000000, (unsigned int)g_earlierMenuPaged_4424EC, 0x00000000, 0x000E, 0x0000, 0x0000, 0x0000, 0x00000000 };

struct MenuBuildDefinitionData g_earlierMenuDef_451E34 = { (unsigned int)g_earlierMenuItems_451C3C, 0x0003, 0x0000, (unsigned int)g_earlierMenuPaged_444D48, 0x00000000, (unsigned int)g_earlierMenuPaged_4424EC, 0x00000000, 0x000E, 0x0000, 0x0000, 0x0000, 0x00000000 };

struct MenuBuildDefinitionData g_earlierMenuDef_451E58 = { (unsigned int)g_earlierMenuItems_451CA8, 0x0003, 0x0000, (unsigned int)g_earlierMenuPaged_444D48, 0x00000000, (unsigned int)g_earlierMenuPaged_4424EC, 0x00000000, 0x000E, 0x0000, 0x0000, 0x0000, 0x00000000 };

struct MenuBuildDefinitionData g_earlierMenuDef_451E7C = { (unsigned int)g_earlierMenuItems_451D14, 0x0003, 0x0000, (unsigned int)g_earlierMenuPaged_444D48, 0x00000000, (unsigned int)g_earlierMenuPaged_4424EC, 0x00000000, 0x000E, 0x0000, 0x0000, 0x0000, 0x00000000 };

struct MenuBuildDefinitionData g_earlierMenuDef_451EA0 = { (unsigned int)g_earlierMenuItems_451BD0, 0x0003, 0x0000, (unsigned int)g_earlierMenuPaged_444E44, 0x00000000, (unsigned int)g_earlierMenuPaged_4424EC, 0x00000000, 0x000E, 0x0000, 0x0000, 0x0000, 0x00000000 };

struct MenuBuildDefinitionData g_earlierMenuDef_451EC4 = { (unsigned int)g_earlierMenuItems_451C3C, 0x0003, 0x0000, (unsigned int)g_earlierMenuPaged_444E44, 0x00000000, (unsigned int)g_earlierMenuPaged_4424EC, 0x00000000, 0x000E, 0x0000, 0x0000, 0x0000, 0x00000000 };

struct MenuBuildDefinitionData g_earlierMenuDef_451EE8 = { (unsigned int)g_earlierMenuItems_451CA8, 0x0003, 0x0000, (unsigned int)g_earlierMenuPaged_444E44, 0x00000000, (unsigned int)g_earlierMenuPaged_4424EC, 0x00000000, 0x000E, 0x0000, 0x0000, 0x0000, 0x00000000 };

struct MenuBuildDefinitionData g_earlierMenuDef_451F0C = { (unsigned int)g_earlierMenuItems_451D14, 0x0003, 0x0000, (unsigned int)g_earlierMenuPaged_444E44, 0x00000000, (unsigned int)g_earlierMenuPaged_4424EC, 0x00000000, 0x000E, 0x0000, 0x0000, 0x0000, 0x00000000 };

struct MenuBuildItemData g_earlierMenuItems_451F30[17] = {
    { 0x0001, 0x0000, 0x50000000, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x00000385, (unsigned int)g_earlierMenuPaged_4411C4, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x08000021, 0x0000, 0x0008, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800E4A38, (unsigned int)g_earlierMenuPaged_442F6C, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00400041, 0x0000, 0x002A, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800E2AF8, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_4453D4, (unsigned int)g_earlierMenuPaged_4452DC, 0x00000000 },
    { 0x0000, 0x0000, 0x00410041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800E2B28, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_4454E4, (unsigned int)g_earlierMenuPaged_445480, 0x00000000 },
    { 0x0000, 0x0000, 0x00410041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800E2B58, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_4455AC, (unsigned int)g_earlierMenuPaged_445548, 0x00000000 },
    { 0x0000, 0x0000, 0x00410041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800E2B78, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_44566C, (unsigned int)g_earlierMenuPaged_445608, 0x00000000 },
    { 0x0000, 0x0000, 0x00410041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800E2BA8, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_445734, (unsigned int)g_earlierMenuPaged_4456D0, 0x00000000 },
    { 0x0000, 0x0000, 0x00410041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800E2BB8, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_4457EC, (unsigned int)g_earlierMenuPaged_445798, 0x00000000 },
    { 0x0000, 0x0000, 0x00410041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800E2BE8, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_4458B0, (unsigned int)g_earlierMenuPaged_445860, 0x00000000 },
    { 0x0000, 0x0000, 0x00410041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800E2C28, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_44594C, (unsigned int)g_earlierMenuPaged_4459F0, 0x00000000 },
    { 0x0000, 0x0000, 0x00410041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800E2C48, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_445ABC, (unsigned int)g_earlierMenuPaged_445A58, 0x00000000 },
    { 0x0000, 0x0000, 0x00410041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800E2C68, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_445C14, (unsigned int)g_earlierMenuPaged_445BB0, 0x00000000 },
    { 0x0000, 0x0000, 0x00410041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800E2C88, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_445D08, (unsigned int)g_earlierMenuPaged_445D54, 0x00000000 },
    { 0x0000, 0x0000, 0x00410041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800E2C98, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_445D88, (unsigned int)g_earlierMenuPaged_445E18, 0x00000000 },
    { 0x0000, 0x0000, 0x00410041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800E2CF8, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_445EBC, (unsigned int)g_earlierMenuPaged_445E70, 0x00000000 },
    { 0x0000, 0x0000, 0x00410041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800E2D08, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_445FB4, (unsigned int)g_earlierMenuPaged_445F60, 0x00000000 },
    { 0x0000, 0x0000, 0x00010201, 0x0000, 0x0013, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800E2D18, (unsigned int)g_earlierMenuPaged_442F6C, 0x00000000, (unsigned int)g_earlierMenuPaged_4432AC, 0x00000000 },
};

struct MenuBuildDefinitionData g_earlierMenuDef_452194 = { (unsigned int)g_earlierMenuItems_451F30, 0x0011, 0x0000, (unsigned int)g_earlierMenuPaged_4452A4, 0x00000000, (unsigned int)g_earlierMenuPaged_4424EC, 0x00000000, 0x0010, 0x0000, 0x0000, 0x0000, 0x00000000 };

unsigned int g_earlierMenuWords_4521B8[2] = { 0x00000000, 0x00000000 };

struct MenuBuildItemData g_earlierMenuItems_4521C0[5] = {
    { 0x0001, 0x0000, 0x50000000, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x00000385, (unsigned int)g_earlierMenuPaged_4411C4, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x08000041, 0x0000, 0x0008, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800E2F78, (unsigned int)g_earlierMenuPaged_442F6C, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00000101, 0x0000, 0x005D, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800E3DC8, (unsigned int)g_earlierMenuPaged_442F6C, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00010101, 0x0000, 0x000A, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800E3DE8, (unsigned int)g_earlierMenuPaged_442F6C, 0x00000000, (unsigned int)g_earlierMenuPaged_445FD0, 0x00000000 },
    { 0x0000, 0x0000, 0x00010101, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800E3DF8, (unsigned int)g_earlierMenuPaged_442F6C, 0x00000000, (unsigned int)g_earlierMenuPaged_4432AC, 0x00000000 },
};

struct MenuBuildDefinitionData g_earlierMenuDef_452274 = { (unsigned int)g_earlierMenuItems_4521C0, 0x0005, 0x0000, (unsigned int)g_earlierMenuPaged_446010, 0x00000000, (unsigned int)g_earlierMenuPaged_4424EC, 0x00000000, 0x0004, 0x0000, 0x0000, 0x0000, (int)&g_earlierMenuDef_452544 };

struct MenuBuildItemData g_earlierMenuItems_452298[7] = {
    { 0x0001, 0x0000, 0x50000000, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x00000385, (unsigned int)g_earlierMenuPaged_4411C4, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x08002001, 0x0000, 0x0008, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800E4A78, (unsigned int)g_earlierMenuPaged_442F6C, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00410041, 0x0000, 0x0032, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800E4AB8, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_4463C0, (unsigned int)g_earlierMenuPaged_446350, 0x00000000 },
    { 0x0000, 0x0000, 0x00410041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800E4AF8, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_446524, (unsigned int)g_earlierMenuPaged_4464C4, 0x00000000 },
    { 0x0000, 0x0000, 0x00410041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800E4B38, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_44624C, (unsigned int)g_earlierMenuPaged_4461EC, 0x00000000 },
    { 0x0000, 0x0000, 0x00410041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800E4B48, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_4466CC, (unsigned int)g_earlierMenuPaged_446628, 0x00000000 },
    { 0x0000, 0x0000, 0x00410401, 0x0000, 0x0044, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800E2D18, (unsigned int)g_earlierMenuPaged_442F6C, 0x00000000, (unsigned int)g_earlierMenuPaged_446164, 0x00000000 },
};

struct MenuBuildDefinitionData g_earlierMenuDef_452394 = { (unsigned int)g_earlierMenuItems_452298, 0x0007, 0x0000, 0x00000000, 0x00000000, (unsigned int)g_earlierMenuPaged_4424EC, 0x00000000, 0x0002, 0x0000, 0x0000, 0x0000, 0x00000000 };

struct MenuBuildItemData g_earlierMenuItems_4523B8[11] = {
    { 0x0001, 0x0000, 0x50000000, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x00000385, (unsigned int)g_earlierMenuPaged_4411C4, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x08000041, 0x0000, 0x0008, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800E2EF8, (unsigned int)g_earlierMenuPaged_442F6C, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0028, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800E2F08, (unsigned int)g_earlierMenuPaged_442F6C, 0x00000000, (unsigned int)g_earlierMenuPaged_44601C, 0x00000000 },
    { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800E2F18, (unsigned int)g_earlierMenuPaged_442F6C, 0x00000000, (unsigned int)g_earlierMenuPaged_446054, 0x00000000 },
    { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800E2F28, (unsigned int)g_earlierMenuPaged_442F6C, 0x00000000, (unsigned int)g_earlierMenuPaged_44605C, 0x00000000 },
    { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800E2F38, (unsigned int)g_earlierMenuPaged_442F6C, 0x00000000, (unsigned int)g_earlierMenuPaged_446088, 0x00000000 },
    { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800E2F58, (unsigned int)g_earlierMenuPaged_442F6C, 0x00000000, (unsigned int)g_earlierMenuPaged_4460B4, 0x00000000 },
    { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800E4A78, (unsigned int)g_earlierMenuPaged_442F6C, 0x00000000, (unsigned int)g_earlierMenuPaged_44674C, 0x00000000 },
    { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800E3E38, (unsigned int)g_earlierMenuPaged_442F6C, 0x00000000, (unsigned int)g_earlierMenuPaged_4460E0, 0x00000000 },
    { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800E2F68, (unsigned int)g_earlierMenuPaged_442F6C, 0x00000000, (unsigned int)g_earlierMenuPaged_44610C, 0x00000000 },
    { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800E2F78, (unsigned int)g_earlierMenuPaged_442F6C, 0x00000000, (unsigned int)g_earlierMenuPaged_446138, 0x00000000 },
};

struct MenuBuildDefinitionData g_earlierMenuDef_452544 = { (unsigned int)g_earlierMenuItems_4523B8, 0x000B, 0x0000, (unsigned int)g_earlierMenuPaged_446854, (unsigned int)g_earlierMenuPaged_4468E4, (unsigned int)g_earlierMenuPaged_446900, 0x00000000, 0x0002, 0x0000, 0x0000, 0x0000, 0x00000000 };

unsigned int g_earlierMenuWords_452568[2] = { 0x00000000, 0x10E00001 };

struct MenuBuildItemData g_earlierMenuItems_452570[45] = {
    { 0x0000, 0x0000, 0x00000041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800E3D18, (unsigned int)g_earlierMenuPaged_442F6C, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00210101, 0x0000, 0x0008, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800F3550, (unsigned int)g_earlierMenuPaged_446E24, (unsigned int)g_earlierMenuPaged_446BB4, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00210101, 0x0000, 0x0008, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800F3560, (unsigned int)g_earlierMenuPaged_446E24, (unsigned int)g_earlierMenuPaged_446BB4, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00210101, 0x0000, 0x0008, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800F3570, (unsigned int)g_earlierMenuPaged_446E24, (unsigned int)g_earlierMenuPaged_446BB4, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00210101, 0x0000, 0x0008, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800F3580, (unsigned int)g_earlierMenuPaged_446E24, (unsigned int)g_earlierMenuPaged_446BB4, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00010110, 0x0000, 0x000A, 0x07, 0x01, 0x20, 0x08, (int)g_earlierMenuResource_800E4CBC, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_446D04, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0x20, 0x08, (int)g_earlierMenuResource_800E4CD0, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_446D04, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0x20, 0x08, (int)g_earlierMenuResource_800E4CE4, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_446D04, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0x20, 0x08, (int)g_earlierMenuResource_800E4CF8, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_446D04, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0x20, 0x08, (int)g_earlierMenuResource_800E4D0C, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_446D04, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0x20, 0x08, (int)g_earlierMenuResource_800E4D20, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_446D04, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0x20, 0x08, (int)g_earlierMenuResource_800E4D34, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_446D04, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0xF9, 0x20, 0x08, (int)g_earlierMenuResource_800E4D48, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_446D04, 0x00000000 },
    { 0x0000, 0x0000, 0x00010110, 0x0000, 0x0004, 0x07, 0x01, 0xF8, 0x08, (int)g_earlierMenuResource_800E4D5C, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_446D04, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0xF8, 0x08, (int)g_earlierMenuResource_800E4D70, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_446D04, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0xF8, 0x08, (int)g_earlierMenuResource_800E4D84, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_446D04, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0xF8, 0x08, (int)g_earlierMenuResource_800E4D98, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_446D04, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0xF8, 0x08, (int)g_earlierMenuResource_800E4DAC, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_446D04, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0xF8, 0x08, (int)g_earlierMenuResource_800E4DC0, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_446D04, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0xF8, 0x08, (int)g_earlierMenuResource_800E4DD4, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_446D04, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0xF9, 0xF8, 0x08, (int)g_earlierMenuResource_800E4DE8, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_446D04, 0x00000000 },
    { 0x0000, 0x0000, 0x00010110, 0x0000, 0x0004, 0x07, 0x01, 0xF8, 0x08, (int)g_earlierMenuResource_800E4DFC, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_446D04, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0xF8, 0x08, (int)g_earlierMenuResource_800E4E10, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_446D04, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0xF8, 0x08, (int)g_earlierMenuResource_800E4E24, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_446D04, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0xF8, 0x08, (int)g_earlierMenuResource_800E4E38, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_446D04, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0xF8, 0x08, (int)g_earlierMenuResource_800E4E4C, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_446D04, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0xF8, 0x08, (int)g_earlierMenuResource_800E4E60, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_446D04, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0xF8, 0x08, (int)g_earlierMenuResource_800E4E74, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_446D04, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0xF9, 0xF8, 0x08, (int)g_earlierMenuResource_800E4E88, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_446D04, 0x00000000 },
    { 0x0000, 0x0000, 0x00010110, 0x0000, 0x0004, 0x07, 0x01, 0xF8, 0x08, (int)g_earlierMenuResource_800E4E9C, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_446D04, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0xF8, 0x08, (int)g_earlierMenuResource_800E4EB0, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_446D04, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0xF8, 0x08, (int)g_earlierMenuResource_800E4EC4, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_446D04, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0xF8, 0x08, (int)g_earlierMenuResource_800E4ED8, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_446D04, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0xF8, 0x08, (int)g_earlierMenuResource_800E4EEC, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_446D04, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0xF8, 0x08, (int)g_earlierMenuResource_800E4F00, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_446D04, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0xF8, 0x08, (int)g_earlierMenuResource_800E4F14, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_446D04, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0xF9, 0xF8, 0x08, (int)g_earlierMenuResource_800E4F28, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_446D04, 0x00000000 },
    { 0x0000, 0x0000, 0x00010110, 0x0000, 0x0004, 0x07, 0x01, 0xF8, 0xE0, (int)g_earlierMenuResource_800E4F3C, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_446D04, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0xF8, 0xE0, (int)g_earlierMenuResource_800E4F50, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_446D04, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0xF8, 0xE0, (int)g_earlierMenuResource_800E4F64, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_446D04, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0xF8, 0xE0, (int)g_earlierMenuResource_800E4F78, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_446D04, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0xF8, 0xE0, (int)g_earlierMenuResource_800E4BF8, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_446D04, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0xF8, 0xE0, (int)g_earlierMenuResource_800E4F8C, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_446D04, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0xF8, 0xE0, (int)g_earlierMenuResource_800E4FA0, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_446FD0, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0xF9, 0xF8, 0xE0, (int)g_earlierMenuResource_800E4FB4, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_447068, 0x00000000 },
};

struct MenuBuildDefinitionData g_earlierMenuDef_452BC4 = { (unsigned int)g_earlierMenuItems_452570, 0x002D, 0x0000, (unsigned int)g_earlierMenuPaged_446920, 0x00000000, (unsigned int)g_earlierMenuPaged_4424EC, (unsigned int)g_earlierMenuPaged_447158, 0x0005, 0x0000, 0x0000, 0x0000, 0x00000000 };

unsigned int g_earlierMenuWords_452BE8[3] = { 0x00000000, 0x00000000, 0x00000000 };

struct MenuBuildItemData g_earlierMenuItems_452BF4[11] = {
    { 0x0000, 0x0000, 0x00000401, 0x0000, 0x0028, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800E4338, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_444430, 0x00000000, 0x00000000 },
    { 0x0001, 0x0000, 0x20010001, 0x0000, 0x0000, 0x00, 0x00, 0x00, 0x01, 0x0000012D, (unsigned int)g_earlierMenuPaged_444778, 0x00000000, (unsigned int)g_earlierMenuPaged_444754, 0x00000000 },
    { 0x0001, 0x0000, 0x50000000, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x00000385, (unsigned int)g_earlierMenuPaged_4411C4, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00000401, 0x0000, 0x0028, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800E43B8, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_444430, 0x00000000, 0x00000000 },
    { 0x0001, 0x0000, 0x20010001, -20, 0x0000, 0xEC, 0x00, 0x00, 0x01, 0x0000012D, (unsigned int)g_earlierMenuPaged_444778, 0x00000000, (unsigned int)g_earlierMenuPaged_444754, 0x00000000 },
    { 0x0001, 0x0000, 0x50000000, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x00000385, (unsigned int)g_earlierMenuPaged_4411C4, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00000401, 0x0000, 0x0028, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800E4438, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_444430, 0x00000000, 0x00000000 },
    { 0x0001, 0x0000, 0x20010001, 0x0000, 0x0000, 0x00, 0x00, 0x00, 0x01, 0x0000012D, (unsigned int)g_earlierMenuPaged_444778, 0x00000000, (unsigned int)g_earlierMenuPaged_444754, 0x00000000 },
    { 0x0001, 0x0000, 0x50000000, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x00000385, (unsigned int)g_earlierMenuPaged_4411C4, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00000401, 0x0000, 0x0028, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800E44B8, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_444430, 0x00000000, 0x00000000 },
    { 0x0001, 0x0000, 0x20010001, 0x0000, 0x0000, 0x00, 0x00, 0x00, 0x01, 0x0000012D, (unsigned int)g_earlierMenuPaged_444778, 0x00000000, (unsigned int)g_earlierMenuPaged_444754, 0x00000000 },
};

struct MenuBuildDefinitionData g_earlierMenuDef_452D80 = { (unsigned int)g_earlierMenuItems_451BD0, 0x0003, 0x0000, (unsigned int)g_earlierMenuPaged_444C88, 0x00000000, (unsigned int)g_earlierMenuPaged_4424EC, (unsigned int)g_earlierMenuPaged_444900, 0x0002, 0x0000, 0x0000, 0x0000, 0x00000000 };

struct MenuBuildDefinitionData g_earlierMenuDef_452DA4 = { (unsigned int)g_earlierMenuItems_451C3C, 0x0003, 0x0000, (unsigned int)g_earlierMenuPaged_444C88, 0x00000000, (unsigned int)g_earlierMenuPaged_4424EC, (unsigned int)g_earlierMenuPaged_444900, 0x0002, 0x0000, 0x0000, 0x0000, 0x00000000 };

struct MenuBuildDefinitionData g_earlierMenuDef_452DC8 = { (unsigned int)g_earlierMenuItems_451CA8, 0x0003, 0x0000, (unsigned int)g_earlierMenuPaged_444C88, 0x00000000, (unsigned int)g_earlierMenuPaged_4424EC, (unsigned int)g_earlierMenuPaged_444900, 0x0002, 0x0000, 0x0000, 0x0000, 0x00000000 };

struct MenuBuildDefinitionData g_earlierMenuDef_452DEC = { (unsigned int)g_earlierMenuItems_451D14, 0x0003, 0x0000, (unsigned int)g_earlierMenuPaged_444C88, 0x00000000, (unsigned int)g_earlierMenuPaged_4424EC, (unsigned int)g_earlierMenuPaged_444900, 0x0002, 0x0000, 0x0000, 0x0000, 0x00000000 };

struct MenuBuildDefinitionData g_earlierMenuDef_452E10 = { (unsigned int)g_earlierMenuItems_451BD0, 0x0003, 0x0000, (unsigned int)g_earlierMenuPaged_444D48, 0x00000000, (unsigned int)g_earlierMenuPaged_4424EC, 0x00000000, 0x000E, 0x0000, 0x0000, 0x0000, 0x00000000 };

struct MenuBuildDefinitionData g_earlierMenuDef_452E34 = { (unsigned int)g_earlierMenuItems_451C3C, 0x0003, 0x0000, (unsigned int)g_earlierMenuPaged_444D48, 0x00000000, (unsigned int)g_earlierMenuPaged_4424EC, 0x00000000, 0x000E, 0x0000, 0x0000, 0x0000, 0x00000000 };

struct MenuBuildDefinitionData g_earlierMenuDef_452E58 = { (unsigned int)g_earlierMenuItems_451CA8, 0x0003, 0x0000, (unsigned int)g_earlierMenuPaged_444D48, 0x00000000, (unsigned int)g_earlierMenuPaged_4424EC, 0x00000000, 0x000E, 0x0000, 0x0000, 0x0000, 0x00000000 };

struct MenuBuildDefinitionData g_earlierMenuDef_452E7C = { (unsigned int)g_earlierMenuItems_451D14, 0x0003, 0x0000, (unsigned int)g_earlierMenuPaged_444D48, 0x00000000, (unsigned int)g_earlierMenuPaged_4424EC, 0x00000000, 0x000E, 0x0000, 0x0000, 0x0000, 0x00000000 };

struct MenuBuildDefinitionData g_earlierMenuDef_452EA0 = { (unsigned int)g_earlierMenuItems_451BD0, 0x0003, 0x0000, (unsigned int)g_earlierMenuPaged_444E44, 0x00000000, (unsigned int)g_earlierMenuPaged_4424EC, 0x00000000, 0x000E, 0x0000, 0x0000, 0x0000, 0x00000000 };

struct MenuBuildDefinitionData g_earlierMenuDef_452EC4 = { (unsigned int)g_earlierMenuItems_451C3C, 0x0003, 0x0000, (unsigned int)g_earlierMenuPaged_444E44, 0x00000000, (unsigned int)g_earlierMenuPaged_4424EC, 0x00000000, 0x000E, 0x0000, 0x0000, 0x0000, 0x00000000 };

struct MenuBuildDefinitionData g_earlierMenuDef_452EE8 = { (unsigned int)g_earlierMenuItems_451CA8, 0x0003, 0x0000, (unsigned int)g_earlierMenuPaged_444E44, 0x00000000, (unsigned int)g_earlierMenuPaged_4424EC, 0x00000000, 0x000E, 0x0000, 0x0000, 0x0000, 0x00000000 };

struct MenuBuildDefinitionData g_earlierMenuDef_452F0C = { (unsigned int)g_earlierMenuItems_451D14, 0x0003, 0x0000, (unsigned int)g_earlierMenuPaged_444E44, 0x00000000, (unsigned int)g_earlierMenuPaged_4424EC, 0x00000000, 0x000E, 0x0000, 0x0000, 0x0000, 0x00000000 };

struct MenuBuildItemData g_earlierMenuItems_452F30[17] = {
    { 0x0001, 0x0000, 0x50000000, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x00000385, (unsigned int)g_earlierMenuPaged_4411C4, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x08000021, 0x0000, 0x0008, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800E4A08, (unsigned int)g_earlierMenuPaged_442F6C, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00400041, 0x0000, 0x002A, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800E2AC8, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_4453D4, (unsigned int)g_earlierMenuPaged_4452DC, 0x00000000 },
    { 0x0000, 0x0000, 0x00410041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800E2AF8, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_4454E4, (unsigned int)g_earlierMenuPaged_445480, 0x00000000 },
    { 0x0000, 0x0000, 0x00410041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800E2B28, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_4455AC, (unsigned int)g_earlierMenuPaged_445548, 0x00000000 },
    { 0x0000, 0x0000, 0x00410041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800E2B48, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_44566C, (unsigned int)g_earlierMenuPaged_445608, 0x00000000 },
    { 0x0000, 0x0000, 0x00410041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800E2B78, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_445734, (unsigned int)g_earlierMenuPaged_4456D0, 0x00000000 },
    { 0x0000, 0x0000, 0x00410041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800E2B88, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_4457EC, (unsigned int)g_earlierMenuPaged_445798, 0x00000000 },
    { 0x0000, 0x0000, 0x00410041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800E2BB8, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_4458B0, (unsigned int)g_earlierMenuPaged_445860, 0x00000000 },
    { 0x0000, 0x0000, 0x00410041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800E2BF8, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_44594C, (unsigned int)g_earlierMenuPaged_4459F0, 0x00000000 },
    { 0x0000, 0x0000, 0x00410041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800E2C18, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_445ABC, (unsigned int)g_earlierMenuPaged_445A58, 0x00000000 },
    { 0x0000, 0x0000, 0x00410041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800E2C38, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_445C14, (unsigned int)g_earlierMenuPaged_445BB0, 0x00000000 },
    { 0x0000, 0x0000, 0x00410041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800E2C58, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_445D08, (unsigned int)g_earlierMenuPaged_445D54, 0x00000000 },
    { 0x0000, 0x0000, 0x00410041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800E2C68, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_445D88, (unsigned int)g_earlierMenuPaged_445E18, 0x00000000 },
    { 0x0000, 0x0000, 0x00410041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800E2CC8, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_445EBC, (unsigned int)g_earlierMenuPaged_445E70, 0x00000000 },
    { 0x0000, 0x0000, 0x00410041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800E2CD8, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_445FB4, (unsigned int)g_earlierMenuPaged_445F60, 0x00000000 },
    { 0x0000, 0x0000, 0x00010201, 0x0000, 0x0013, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800E2CE8, (unsigned int)g_earlierMenuPaged_442F6C, 0x00000000, (unsigned int)g_earlierMenuPaged_4432AC, 0x00000000 },
};

struct MenuBuildDefinitionData g_earlierMenuDef_453194 = { (unsigned int)g_earlierMenuItems_451F30, 0x0011, 0x0000, (unsigned int)g_earlierMenuPaged_4452A4, 0x00000000, (unsigned int)g_earlierMenuPaged_4424EC, 0x00000000, 0x0010, 0x0000, 0x0000, 0x0000, 0x00000000 };

unsigned int g_earlierMenuWords_4531B8[2] = { 0x6D5F7041, 0x6D6D6F49 };

struct MenuBuildItemData g_earlierMenuItems_4531C0[5] = {
    { 0x0001, 0x0000, 0x50000000, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x00000385, (unsigned int)g_earlierMenuPaged_4411C4, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x08000041, 0x0000, 0x0008, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800E2F48, (unsigned int)g_earlierMenuPaged_442F6C, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00000101, 0x0000, 0x005D, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800E3D98, (unsigned int)g_earlierMenuPaged_442F6C, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00010101, 0x0000, 0x000A, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800E3DB8, (unsigned int)g_earlierMenuPaged_442F6C, 0x00000000, (unsigned int)g_earlierMenuPaged_445FD0, 0x00000000 },
    { 0x0000, 0x0000, 0x00010101, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800E3DC8, (unsigned int)g_earlierMenuPaged_442F6C, 0x00000000, (unsigned int)g_earlierMenuPaged_4432AC, 0x00000000 },
};

struct MenuBuildDefinitionData g_earlierMenuDef_453274 = { (unsigned int)g_earlierMenuItems_4521C0, 0x0005, 0x0000, (unsigned int)g_earlierMenuPaged_446010, 0x00000000, (unsigned int)g_earlierMenuPaged_4424EC, 0x00000000, 0x0004, 0x0000, 0x0000, 0x0000, (int)&g_earlierMenuDef_452544 };

struct MenuBuildItemData g_earlierMenuItems_453298[7] = {
    { 0x0001, 0x0000, 0x50000000, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x00000385, (unsigned int)g_earlierMenuPaged_4411C4, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x08002001, 0x0000, 0x0008, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800E4A48, (unsigned int)g_earlierMenuPaged_442F6C, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00410041, 0x0000, 0x0032, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800E4A88, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_4463C0, (unsigned int)g_earlierMenuPaged_446350, 0x00000000 },
    { 0x0000, 0x0000, 0x00410041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800E4AC8, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_446524, (unsigned int)g_earlierMenuPaged_4464C4, 0x00000000 },
    { 0x0000, 0x0000, 0x00410041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800E4B08, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_44624C, (unsigned int)g_earlierMenuPaged_4461EC, 0x00000000 },
    { 0x0000, 0x0000, 0x00410041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800E4B18, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_4466CC, (unsigned int)g_earlierMenuPaged_446628, 0x00000000 },
    { 0x0000, 0x0000, 0x00410401, 0x0000, 0x0044, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800E2CE8, (unsigned int)g_earlierMenuPaged_442F6C, 0x00000000, (unsigned int)g_earlierMenuPaged_446164, 0x00000000 },
};

struct MenuBuildDefinitionData g_earlierMenuDef_453394 = { (unsigned int)g_earlierMenuItems_452298, 0x0007, 0x0000, 0x00000000, 0x00000000, (unsigned int)g_earlierMenuPaged_4424EC, 0x00000000, 0x0002, 0x0000, 0x0000, 0x0000, 0x00000000 };

struct MenuBuildItemData g_earlierMenuItems_4533B8[11] = {
    { 0x0001, 0x0000, 0x50000000, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x00000385, (unsigned int)g_earlierMenuPaged_4411C4, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x08000041, 0x0000, 0x0008, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800E2EC8, (unsigned int)g_earlierMenuPaged_442F6C, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0028, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800E2ED8, (unsigned int)g_earlierMenuPaged_442F6C, 0x00000000, (unsigned int)g_earlierMenuPaged_44601C, 0x00000000 },
    { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800E2EE8, (unsigned int)g_earlierMenuPaged_442F6C, 0x00000000, (unsigned int)g_earlierMenuPaged_446054, 0x00000000 },
    { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800E2EF8, (unsigned int)g_earlierMenuPaged_442F6C, 0x00000000, (unsigned int)g_earlierMenuPaged_44605C, 0x00000000 },
    { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800E2F08, (unsigned int)g_earlierMenuPaged_442F6C, 0x00000000, (unsigned int)g_earlierMenuPaged_446088, 0x00000000 },
    { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800E2F28, (unsigned int)g_earlierMenuPaged_442F6C, 0x00000000, (unsigned int)g_earlierMenuPaged_4460B4, 0x00000000 },
    { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800E4A48, (unsigned int)g_earlierMenuPaged_442F6C, 0x00000000, (unsigned int)g_earlierMenuPaged_44674C, 0x00000000 },
    { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800E3E08, (unsigned int)g_earlierMenuPaged_442F6C, 0x00000000, (unsigned int)g_earlierMenuPaged_4460E0, 0x00000000 },
    { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800E2F38, (unsigned int)g_earlierMenuPaged_442F6C, 0x00000000, (unsigned int)g_earlierMenuPaged_44610C, 0x00000000 },
    { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800E2F48, (unsigned int)g_earlierMenuPaged_442F6C, 0x00000000, (unsigned int)g_earlierMenuPaged_446138, 0x00000000 },
};

struct MenuBuildDefinitionData g_earlierMenuDef_453544 = { (unsigned int)g_earlierMenuItems_4523B8, 0x000B, 0x0000, (unsigned int)g_earlierMenuPaged_446854, (unsigned int)g_earlierMenuPaged_4468E4, (unsigned int)g_earlierMenuPaged_446900, 0x00000000, 0x0002, 0x0000, 0x0000, 0x0000, 0x00000000 };

float g_earlierMenuFloats_453568[2] = { 3.1415927f, 1.5707964f };

struct MenuBuildItemData g_earlierMenuItems_453570[45] = {
    { 0x0000, 0x0000, 0x00000041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800E3CE8, (unsigned int)g_earlierMenuPaged_442F6C, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00210101, 0x0000, 0x0008, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800F3520, (unsigned int)g_earlierMenuPaged_446E24, (unsigned int)g_earlierMenuPaged_446BB4, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00210101, 0x0000, 0x0008, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800F3530, (unsigned int)g_earlierMenuPaged_446E24, (unsigned int)g_earlierMenuPaged_446BB4, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00210101, 0x0000, 0x0008, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800F3540, (unsigned int)g_earlierMenuPaged_446E24, (unsigned int)g_earlierMenuPaged_446BB4, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00210101, 0x0000, 0x0008, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource_800F3550, (unsigned int)g_earlierMenuPaged_446E24, (unsigned int)g_earlierMenuPaged_446BB4, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00010110, 0x0000, 0x000A, 0x07, 0x01, 0x20, 0x08, (int)g_earlierMenuResource_800E4C8C, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_446D04, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0x20, 0x08, (int)g_earlierMenuResource_800E4CA0, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_446D04, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0x20, 0x08, (int)g_earlierMenuResource_800E4CB4, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_446D04, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0x20, 0x08, (int)g_earlierMenuResource_800E4CC8, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_446D04, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0x20, 0x08, (int)g_earlierMenuResource_800E4CDC, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_446D04, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0x20, 0x08, (int)g_earlierMenuResource_800E4CF0, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_446D04, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0x20, 0x08, (int)g_earlierMenuResource_800E4D04, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_446D04, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0xF9, 0x20, 0x08, (int)g_earlierMenuResource_800E4D18, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_446D04, 0x00000000 },
    { 0x0000, 0x0000, 0x00010110, 0x0000, 0x0004, 0x07, 0x01, 0xF8, 0x08, (int)g_earlierMenuResource_800E4D2C, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_446D04, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0xF8, 0x08, (int)g_earlierMenuResource_800E4D40, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_446D04, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0xF8, 0x08, (int)g_earlierMenuResource_800E4D54, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_446D04, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0xF8, 0x08, (int)g_earlierMenuResource_800E4D68, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_446D04, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0xF8, 0x08, (int)g_earlierMenuResource_800E4D7C, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_446D04, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0xF8, 0x08, (int)g_earlierMenuResource_800E4D90, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_446D04, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0xF8, 0x08, (int)g_earlierMenuResource_800E4DA4, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_446D04, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0xF9, 0xF8, 0x08, (int)g_earlierMenuResource_800E4DB8, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_446D04, 0x00000000 },
    { 0x0000, 0x0000, 0x00010110, 0x0000, 0x0004, 0x07, 0x01, 0xF8, 0x08, (int)g_earlierMenuResource_800E4DCC, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_446D04, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0xF8, 0x08, (int)g_earlierMenuResource_800E4DE0, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_446D04, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0xF8, 0x08, (int)g_earlierMenuResource_800E4DF4, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_446D04, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0xF8, 0x08, (int)g_earlierMenuResource_800E4E08, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_446D04, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0xF8, 0x08, (int)g_earlierMenuResource_800E4E1C, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_446D04, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0xF8, 0x08, (int)g_earlierMenuResource_800E4E30, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_446D04, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0xF8, 0x08, (int)g_earlierMenuResource_800E4E44, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_446D04, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0xF9, 0xF8, 0x08, (int)g_earlierMenuResource_800E4E58, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_446D04, 0x00000000 },
    { 0x0000, 0x0000, 0x00010110, 0x0000, 0x0004, 0x07, 0x01, 0xF8, 0x08, (int)g_earlierMenuResource_800E4E6C, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_446D04, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0xF8, 0x08, (int)g_earlierMenuResource_800E4E80, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_446D04, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0xF8, 0x08, (int)g_earlierMenuResource_800E4E94, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_446D04, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0xF8, 0x08, (int)g_earlierMenuResource_800E4EA8, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_446D04, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0xF8, 0x08, (int)g_earlierMenuResource_800E4EBC, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_446D04, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0xF8, 0x08, (int)g_earlierMenuResource_800E4ED0, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_446D04, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0xF8, 0x08, (int)g_earlierMenuResource_800E4EE4, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_446D04, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0xF9, 0xF8, 0x08, (int)g_earlierMenuResource_800E4EF8, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_446D04, 0x00000000 },
    { 0x0000, 0x0000, 0x00010110, 0x0000, 0x0004, 0x07, 0x01, 0xF8, 0xE0, (int)g_earlierMenuResource_800E4F0C, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_446D04, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0xF8, 0xE0, (int)g_earlierMenuResource_800E4F20, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_446D04, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0xF8, 0xE0, (int)g_earlierMenuResource_800E4F34, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_446D04, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0xF8, 0xE0, (int)g_earlierMenuResource_800E4F48, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_446D04, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0xF8, 0xE0, (int)g_earlierMenuResource_800E4BC8, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_446D04, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0xF8, 0xE0, (int)g_earlierMenuResource_800E4F5C, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_446D04, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0xF8, 0xE0, (int)g_earlierMenuResource_800E4F70, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_446FD0, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0xF9, 0xF8, 0xE0, (int)g_earlierMenuResource_800E4F84, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_447068, 0x00000000 },
};

struct MenuBuildDefinitionData g_earlierMenuDef_453BC4 = { (unsigned int)g_earlierMenuItems_452570, 0x002D, 0x0000, (unsigned int)g_earlierMenuPaged_446920, 0x00000000, (unsigned int)g_earlierMenuPaged_4424EC, (unsigned int)g_earlierMenuPaged_447158, 0x0005, 0x0000, 0x0000, 0x0000, 0x00000000 };

#endif
