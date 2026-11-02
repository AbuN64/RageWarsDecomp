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
extern char g_earlierMenuResource166[];
extern char g_earlierMenuResource167[];
extern char g_earlierMenuResource168[];
extern char g_earlierMenuResource169[];
extern char g_earlierMenuResource170[];
extern char g_earlierMenuResource171[];
extern char g_earlierMenuResource172[];
extern char g_earlierMenuResource173[];
extern char g_earlierMenuResource174[];
extern char g_earlierMenuResource175[];
extern char g_earlierMenuResource176[];
extern char g_earlierMenuResource177[];
extern char g_earlierMenuResource178[];
extern char g_earlierMenuResource179[];
extern char g_earlierMenuResource180[];
extern char g_earlierMenuResource181[];
extern char g_earlierMenuResource182[];
extern char g_earlierMenuResource183[];
extern char g_earlierMenuResource184[];
extern char g_earlierMenuResource185[];
extern char g_earlierMenuResource186[];
extern char g_earlierMenuResource187[];
extern char g_earlierMenuResource188[];
extern char g_earlierMenuResource189[];
extern char g_earlierMenuResource190[];
extern char g_earlierMenuResource191[];
extern char g_earlierMenuResource192[];
extern char g_earlierMenuResource193[];
extern char g_earlierMenuResource194[];
extern char g_earlierMenuResource195[];
extern char g_earlierMenuResource196[];
extern char g_earlierMenuResource197[];
extern char g_earlierMenuResource198[];
extern char g_earlierMenuResource199[];
extern char g_earlierMenuResource200[];
extern char g_earlierMenuResource201[];
extern char g_earlierMenuResource202[];
extern char g_earlierMenuResource203[];
extern char g_earlierMenuResource204[];
extern char g_earlierMenuResource205[];
extern char g_earlierMenuResource206[];
extern char g_earlierMenuResource207[];
extern char g_earlierMenuResource208[];
extern char g_earlierMenuResource209[];
extern char g_earlierMenuResource210[];
extern char g_earlierMenuResource211[];
extern char g_earlierMenuResource212[];
extern char g_earlierMenuResource213[];
extern char g_earlierMenuResource214[];
extern char g_earlierMenuResource215[];
extern char g_earlierMenuResource216[];
extern char g_earlierMenuResource217[];
extern char g_earlierMenuResource218[];
extern char g_earlierMenuResource219[];
extern char g_earlierMenuResource220[];
extern char g_earlierMenuResource221[];
extern char g_earlierMenuResource222[];
extern char g_earlierMenuResource223[];
extern char g_earlierMenuResource224[];
extern char g_earlierMenuResource225[];
extern char g_earlierMenuResource226[];
extern char g_earlierMenuResource227[];
extern char g_earlierMenuResource228[];
extern char g_earlierMenuResource229[];
extern char g_earlierMenuResource230[];
extern char g_earlierMenuResource231[];
extern char g_earlierMenuResource232[];
extern char g_earlierMenuResource233[];
extern char g_earlierMenuResource234[];
extern char g_earlierMenuResource235[];
extern char g_earlierMenuResource236[];
extern char g_earlierMenuResource237[];
extern char g_earlierMenuResource238[];
extern char g_earlierMenuResource239[];
extern char g_earlierMenuResource240[];
extern char g_earlierMenuResource241[];
extern char g_earlierMenuResource242[];
extern char g_earlierMenuResource243[];
extern char g_earlierMenuResource244[];
extern char g_earlierMenuResource245[];
extern char g_earlierMenuResource246[];
extern char g_earlierMenuResource247[];
extern char g_earlierMenuResource248[];
extern char g_earlierMenuResource249[];
extern char g_earlierMenuResource250[];
extern char g_earlierMenuResource251[];
extern char g_earlierMenuResource252[];
extern char g_earlierMenuResource253[];
extern char g_earlierMenuResource254[];
extern char g_earlierMenuResource255[];
extern char g_earlierMenuResource256[];
extern char g_earlierMenuResource257[];
extern char g_earlierMenuResource258[];
extern char g_earlierMenuResource259[];
extern char g_earlierMenuResource260[];
extern char g_earlierMenuResource261[];
extern char g_earlierMenuResource262[];
extern char g_earlierMenuResource263[];
extern char g_earlierMenuResource264[];
extern char g_earlierMenuResource265[];
extern char g_earlierMenuResource266[];
extern char g_earlierMenuResource267[];
extern char g_earlierMenuResource268[];
extern char g_earlierMenuResource269[];
extern char g_earlierMenuResource270[];
extern char g_earlierMenuResource271[];
extern char g_earlierMenuResource272[];
extern char g_earlierMenuResource273[];
extern char g_earlierMenuResource274[];
extern char g_earlierMenuResource275[];
extern char g_earlierMenuResource276[];
extern char g_earlierMenuResource277[];
extern char g_earlierMenuResource278[];
extern char g_earlierMenuResource279[];
extern char g_earlierMenuResource280[];
extern char g_earlierMenuResource281[];
extern char g_earlierMenuResource282[];
extern char g_earlierMenuResource283[];
extern char g_earlierMenuResource284[];
extern char g_earlierMenuResource285[];
extern char g_earlierMenuResource286[];
extern char g_earlierMenuResource287[];
extern char g_earlierMenuResource288[];
extern char g_earlierMenuResource289[];
extern char g_earlierMenuResource290[];
extern char g_earlierMenuResource291[];
extern char g_earlierMenuResource292[];
extern char g_earlierMenuResource293[];
extern char g_earlierMenuResource294[];
extern char g_earlierMenuResource295[];
extern char g_earlierMenuResource296[];
extern char g_earlierMenuResource297[];
extern char g_earlierMenuResource298[];
extern char g_earlierMenuResource299[];
extern char g_earlierMenuResource300[];
extern char g_earlierMenuResource301[];
extern char g_earlierMenuResource302[];
extern char g_earlierMenuResource303[];
extern char g_earlierMenuResource304[];
extern char g_earlierMenuResource305[];
extern char g_earlierMenuResource306[];
extern char g_earlierMenuResource307[];
extern char g_earlierMenuResource308[];
extern char g_earlierMenuResource309[];
extern char g_earlierMenuResource310[];
extern char g_earlierMenuResource311[];
extern char g_earlierMenuResource312[];
extern char g_earlierMenuResource313[];
extern char g_earlierMenuResource314[];
extern char g_earlierMenuResource315[];
extern char g_earlierMenuResource316[];
extern char g_earlierMenuResource317[];
extern char g_earlierMenuResource318[];
extern char g_earlierMenuResource319[];
extern char g_earlierMenuResource320[];
extern char g_earlierMenuResource321[];
extern char g_earlierMenuResource322[];
extern char g_earlierMenuResource323[];
extern char g_earlierMenuResource324[];
extern char g_earlierMenuResource325[];
extern char g_earlierMenuResource326[];
extern char g_earlierMenuResource327[];
extern char g_earlierMenuResource328[];
extern char g_earlierMenuResource329[];
extern char g_earlierMenuResource330[];
extern char g_earlierMenuResource331[];
extern char g_earlierMenuResource332[];
extern char g_earlierMenuResource333[];
extern char g_earlierMenuResource334[];
extern char g_earlierMenuResource335[];
extern char g_earlierMenuResource336[];
extern char g_earlierMenuResource337[];
extern char g_earlierMenuResource338[];
extern char g_earlierMenuResource339[];
extern char g_earlierMenuResource340[];
extern char g_earlierMenuResource341[];
extern char g_earlierMenuResource342[];
extern char g_earlierMenuResource343[];
extern char g_earlierMenuResource344[];
extern char g_earlierMenuResource345[];
extern char g_earlierMenuResource346[];
extern char g_earlierMenuResource347[];
extern char g_earlierMenuResource348[];
extern char g_earlierMenuResource349[];
extern char g_earlierMenuResource350[];
extern char g_earlierMenuResource351[];
extern char g_earlierMenuResource352[];
extern char g_earlierMenuResource353[];
extern char g_earlierMenuResource354[];
extern char g_earlierMenuResource355[];
extern char g_earlierMenuResource356[];
extern char g_earlierMenuResource357[];
extern char g_earlierMenuResource358[];
extern char g_earlierMenuResource359[];
extern char g_earlierMenuResource360[];
extern char g_earlierMenuResource361[];
extern char g_earlierMenuResource362[];
extern char g_earlierMenuResource363[];
extern char g_earlierMenuResource364[];
extern char g_earlierMenuResource365[];
extern char g_earlierMenuResource366[];
extern char g_earlierMenuResource367[];
extern char g_earlierMenuResource368[];
extern char g_earlierMenuResource369[];
extern char g_earlierMenuResource370[];
extern char g_earlierMenuResource371[];
extern char g_earlierMenuResource372[];
extern char g_earlierMenuResource373[];
extern char g_earlierMenuResource374[];
extern char g_earlierMenuResource375[];
extern char g_earlierMenuResource376[];
extern char g_earlierMenuResource377[];
extern char g_earlierMenuResource378[];
extern char g_earlierMenuResource379[];
extern char g_earlierMenuResource380[];
extern char g_earlierMenuResource381[];
extern char g_earlierMenuResource382[];
extern char g_earlierMenuResource383[];
extern char g_earlierMenuResource384[];
extern char g_earlierMenuResource385[];
extern char g_earlierMenuResource386[];
extern char g_earlierMenuResource387[];
extern char g_earlierMenuResource388[];
extern char g_earlierMenuResource389[];
extern char g_earlierMenuResource390[];
extern char g_earlierMenuResource391[];
extern char g_earlierMenuResource392[];
extern char g_earlierMenuResource393[];
extern char g_earlierMenuResource394[];
extern char g_earlierMenuResource395[];
extern char g_earlierMenuResource396[];
extern char g_earlierMenuResource397[];
extern char g_earlierMenuResource398[];
extern char g_earlierMenuResource399[];
extern char g_earlierMenuResource400[];
extern char g_earlierMenuResource401[];
extern char g_earlierOptionName13[];
extern char g_earlierOptionName14[];
extern char g_earlierOptionName15[];
extern char g_earlierOptionName16[];
extern char g_earlierOptionName17[];
extern char g_earlierOptionName18[];
extern char g_earlierOptionName19[];
extern char g_earlierOptionName20[];
extern char g_earlierOptionName21[];
extern char g_earlierOptionName22[];
extern char g_earlierOptionName23[];
extern char g_earlierOptionName24[];
extern char g_earlierOptionWord13[];
extern char g_earlierOptionWord14[];
extern char g_earlierOptionWord15[];
extern char g_earlierOptionWord16[];
extern char g_earlierOptionWord17[];
extern char g_earlierOptionWord18[];
extern char g_earlierOptionWord19[];
extern char g_earlierOptionWord20[];
extern char g_earlierOptionWord21[];
extern char g_earlierOptionWord22[];
extern char g_earlierOptionWord23[];
extern char g_earlierOptionWord24[];
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
    { 0x0000, 0x0000, 0x08000041, 0x0000, 0x000A, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource220, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_40A61C, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00010041, 0x0000, -8, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource237, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_40A6A8, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00011001, 0x0000, 0x0006, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource221, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_4080E4, (unsigned int)g_earlierMenuPaged_40783C, 0x00000000 },
    { 0x0000, 0x0000, 0x00011001, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource222, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_4080E4, (unsigned int)g_earlierMenuPaged_40783C, 0x00000000 },
    { 0x0000, 0x0000, 0x00011001, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource223, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_4080E4, (unsigned int)g_earlierMenuPaged_40783C, 0x00000000 },
    { 0x0000, 0x0000, 0x00011001, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource224, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_4080E4, (unsigned int)g_earlierMenuPaged_40783C, 0x00000000 },
    { 0x0000, 0x0000, 0x00011001, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource225, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_4080E4, (unsigned int)g_earlierMenuPaged_40783C, 0x00000000 },
    { 0x0000, 0x0000, 0x00011001, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource226, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_4080E4, (unsigned int)g_earlierMenuPaged_40783C, 0x00000000 },
    { 0x0000, 0x0000, 0x00011001, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource227, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_4080E4, (unsigned int)g_earlierMenuPaged_40783C, 0x00000000 },
    { 0x0000, 0x0000, 0x00011001, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource228, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_4080E4, (unsigned int)g_earlierMenuPaged_40783C, 0x00000000 },
    { 0x0000, 0x0000, 0x00011001, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource229, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_4080E4, (unsigned int)g_earlierMenuPaged_40783C, 0x00000000 },
    { 0x0000, 0x0000, 0x00011001, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource230, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_4080E4, (unsigned int)g_earlierMenuPaged_40783C, 0x00000000 },
    { 0x0000, 0x0000, 0x00011001, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource231, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_4080E4, (unsigned int)g_earlierMenuPaged_40783C, 0x00000000 },
    { 0x0000, 0x0000, 0x00011001, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource232, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_4080E4, (unsigned int)g_earlierMenuPaged_40783C, 0x00000000 },
    { 0x0000, 0x0000, 0x00011001, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource233, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_4080E4, (unsigned int)g_earlierMenuPaged_40783C, 0x00000000 },
    { 0x0000, 0x0000, 0x00011001, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource234, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_4080E4, (unsigned int)g_earlierMenuPaged_40783C, 0x00000000 },
    { 0x0000, 0x0000, 0x00011001, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource235, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_4080E4, (unsigned int)g_earlierMenuPaged_40783C, 0x00000000 },
    { 0x0000, 0x0000, 0x00011001, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource236, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_4080E4, (unsigned int)g_earlierMenuPaged_40783C, 0x00000000 },
    { 0x0000, 0x0000, 0x00011001, 0x0000, 0x0003, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource308, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_4082D0, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00010041, 0x0000, 0x000A, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource308, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_40A550, (unsigned int)g_earlierMenuPaged_4084D4, 0x00000000 },
    { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0004, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource238, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_40A784, (unsigned int)g_earlierMenuPaged_4087C8, 0x00000000 },
};

struct MenuBuildDefinitionData g_earlierMenuDef_44F738 = { (unsigned int)g_earlierMenuItems_44F420, 0x0016, 0x0000, (unsigned int)g_earlierMenuPaged_406730, 0x00000000, (unsigned int)g_earlierMenuPaged_4424EC, (unsigned int)g_earlierMenuPaged_409F18, 0x0015, 0x0000, 0x0000, 0x0000, 0x00000000 };

struct MenuBuildDefinitionData g_earlierMenuDef_44F75C = { (unsigned int)g_earlierMenuItems_44F420, 0x0016, 0x0000, (unsigned int)g_earlierMenuPaged_4064A8, 0x00000000, (unsigned int)g_earlierMenuPaged_4424EC, (unsigned int)g_earlierMenuPaged_409F18, 0x0014, 0x0000, 0x0000, 0x0000, 0x00000000 };

struct MenuBuildDefinitionData g_earlierMenuDef_44F780 = { (unsigned int)g_earlierMenuItems_44F420, 0x0016, 0x0000, (unsigned int)g_earlierMenuPaged_4071A8, 0x00000000, (unsigned int)g_earlierMenuPaged_4424EC, (unsigned int)g_earlierMenuPaged_409FF8, 0x0015, 0x0000, 0x0000, 0x0000, 0x00000000 };

struct MenuBuildDefinitionData g_earlierMenuDef_44F7A4 = { (unsigned int)g_earlierMenuItems_44F420, 0x0016, 0x0000, (unsigned int)g_earlierMenuPaged_407030, 0x00000000, (unsigned int)g_earlierMenuPaged_4424EC, (unsigned int)g_earlierMenuPaged_409FF8, 0x0014, 0x0000, 0x0000, 0x0000, 0x00000000 };

struct MenuBuildDefinitionData g_earlierMenuDef_44F7C8 = { (unsigned int)g_earlierMenuItems_44F420, 0x0016, 0x0000, (unsigned int)g_earlierMenuPaged_406A88, 0x00000000, (unsigned int)g_earlierMenuPaged_4424EC, (unsigned int)g_earlierMenuPaged_40A11C, 0x0014, 0x0000, 0x0000, 0x0000, 0x00000000 };

struct MenuBuildItemData g_earlierMenuItems_44F7EC[10] = {
    { 0x0001, 0x0000, 0x90000000, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x00000385, (unsigned int)g_earlierMenuPaged_4411C4, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x08000801, 0x0000, 0x0008, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource239, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_40A7CC, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0014, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource308, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_40A934, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0005, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource242, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_40A960, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00010041, 0x0000, 0x000A, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource308, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_40A800, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource240, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_40A85C, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource241, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_40A8C8, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0014, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource247, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_40AA04, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00010040, 0x007D, 0x000A, 0x00, 0x01, 0x00, 0x00, (int)g_earlierMenuResource259, (unsigned int)g_earlierMenuPaged_442F6C, 0x00000000, (unsigned int)g_earlierMenuPaged_408A58, 0x00000000 },
    { 0x0000, 0x0000, 0x00024040, 0x000A, 0x0000, 0xFF, 0x00, 0x00, 0x00, (int)g_earlierMenuResource260, (unsigned int)g_earlierMenuPaged_442F6C, 0x00000000, (unsigned int)g_earlierMenuPaged_40AA38, 0x00000000 },
};

struct MenuBuildDefinitionData g_earlierMenuDef_44F954 = { (unsigned int)g_earlierMenuItems_44F7EC, 0x000A, 0x0000, (unsigned int)g_earlierMenuPaged_40A7A8, 0x00000000, (unsigned int)g_earlierMenuPaged_4424EC, 0x00000000, 0x0008, 0x0000, 0x0000, 0x0000, 0x00000000 };

struct MenuBuildDefinitionData g_earlierMenuDef_44F978 = { (unsigned int)g_earlierMenuItems_44F7EC, 0x000A, 0x0000, (unsigned int)g_earlierMenuPaged_40A7BC, 0x00000000, (unsigned int)g_earlierMenuPaged_4424EC, 0x00000000, 0x0009, 0x0000, 0x0000, 0x0000, 0x00000000 };

struct MenuBuildItemData g_earlierMenuItems_44F99C[9] = {
    { 0x0001, 0x0000, 0x90000000, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x00000385, (unsigned int)g_earlierMenuPaged_4411C4, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x08000021, 0x0000, 0x0008, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource243, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_40AB18, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0032, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource308, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_40AB6C, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0002, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource244, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_40AC68, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0002, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource245, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_40ADC0, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0002, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource246, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_408CAC, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0010, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource247, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_40AE28, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00010040, 0x007D, 0x000A, 0x00, 0x01, 0x00, 0x00, (int)g_earlierMenuResource259, (unsigned int)g_earlierMenuPaged_442F6C, 0x00000000, (unsigned int)g_earlierMenuPaged_408F30, 0x00000000 },
    { 0x0000, 0x0000, 0x00024040, 0x000A, 0x0000, 0xFF, 0x00, 0x00, 0x00, (int)g_earlierMenuResource260, (unsigned int)g_earlierMenuPaged_442F6C, 0x00000000, (unsigned int)g_earlierMenuPaged_40AE7C, 0x00000000 },
};

struct MenuBuildDefinitionData g_earlierMenuDef_44FAE0 = { (unsigned int)g_earlierMenuItems_44F99C, 0x0009, 0x0000, (unsigned int)g_earlierMenuPaged_40AAA4, 0x00000000, (unsigned int)g_earlierMenuPaged_4424EC, 0x00000000, 0x0007, 0x0000, 0x0000, 0x0000, 0x00000000 };

struct MenuBuildDefinitionData g_earlierMenuDef_44FB04 = { (unsigned int)g_earlierMenuItems_44F99C, 0x0009, 0x0000, (unsigned int)g_earlierMenuPaged_40AAC0, 0x00000000, (unsigned int)g_earlierMenuPaged_4424EC, 0x00000000, 0x0008, 0x0000, 0x0000, 0x0000, 0x00000000 };

struct MenuBuildDefinitionData g_earlierMenuDef_44FB28 = { (unsigned int)g_earlierMenuItems_44F99C, 0x0009, 0x0000, (unsigned int)g_earlierMenuPaged_40AAD8, 0x00000000, (unsigned int)g_earlierMenuPaged_4424EC, 0x00000000, 0x0008, 0x0000, 0x0000, 0x0000, 0x00000000 };

struct MenuBuildItemData g_earlierMenuItems_44FB4C[8] = {
    { 0x0001, 0x0000, 0x90000000, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x00000385, (unsigned int)g_earlierMenuPaged_4411C4, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x08000021, 0x0000, 0x0008, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource308, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_40B084, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00010041, 0x0000, 0x001E, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource308, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_40B0D0, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0005, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource308, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_40B1FC, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0005, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource308, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_40B328, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0005, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource308, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_40B454, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0005, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource308, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_40B580, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0019, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource248, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_40B6AC, (unsigned int)g_earlierMenuPaged_4090D4, 0x00000000 },
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
    { 0x0000, 0x0000, 0x08000021, 0x0000, 0x0008, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource249, (unsigned int)g_earlierMenuPaged_442F6C, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0028, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource308, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_40B80C, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource308, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_40B840, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource308, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_40B874, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0014, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource250, (unsigned int)g_earlierMenuPaged_442F6C, 0x00000000, (unsigned int)g_earlierMenuPaged_40B920, 0x00000000 },
    { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0005, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource251, (unsigned int)g_earlierMenuPaged_442F6C, 0x00000000, (unsigned int)g_earlierMenuPaged_40B9CC, 0x00000000 },
    { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0005, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource308, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_40BB0C, (unsigned int)g_earlierMenuPaged_40BA88, 0x00000000 },
};

struct MenuBuildDefinitionData g_earlierMenuDef_44FFF0 = { (unsigned int)g_earlierMenuItems_44FED0, 0x0008, 0x0000, (unsigned int)g_earlierMenuPaged_40B7D8, 0x00000000, (unsigned int)g_earlierMenuPaged_4424EC, (unsigned int)g_earlierMenuPaged_40B6F8, 0x0007, 0x0000, 0x0000, 0x0000, 0x00000000 };

struct MenuBuildDefinitionData g_earlierMenuDef_450014 = { (unsigned int)g_earlierMenuItems_44FED0, 0x0008, 0x0000, (unsigned int)g_earlierMenuPaged_40B7F4, 0x00000000, (unsigned int)g_earlierMenuPaged_4424EC, (unsigned int)g_earlierMenuPaged_40B6F8, 0x0005, 0x0000, 0x0000, 0x0000, 0x00000000 };

struct MenuBuildItemData g_earlierMenuItems_450038[8] = {
    { 0x0001, 0x0000, 0x90000000, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x00000385, (unsigned int)g_earlierMenuPaged_4411C4, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x08000801, 0x0000, 0x0008, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource308, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_40BCA8, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0023, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource308, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_40BD24, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0004, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource308, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_40BDA0, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0004, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource308, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_40BE1C, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0004, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource308, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_40BE98, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00012001, 0x0000, 0x0023, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource252, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_40BF14, (unsigned int)g_earlierMenuPaged_409428, 0x00000000 },
    { 0x0000, 0x0000, 0x00012001, 0x0000, 0x0005, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource253, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_40BF80, (unsigned int)g_earlierMenuPaged_40972C, 0x00000000 },
};

struct MenuBuildDefinitionData g_earlierMenuDef_450158 = { (unsigned int)g_earlierMenuItems_450038, 0x0008, 0x0000, (unsigned int)g_earlierMenuPaged_40BC20, 0x00000000, (unsigned int)g_earlierMenuPaged_4424EC, (unsigned int)g_earlierMenuPaged_40BB40, 0x0007, 0x0000, 0x0000, 0x0000, 0x00000000 };

struct MenuBuildDefinitionData g_earlierMenuDef_45017C = { (unsigned int)g_earlierMenuItems_450038, 0x0008, 0x0000, (unsigned int)g_earlierMenuPaged_40BC38, 0x00000000, (unsigned int)g_earlierMenuPaged_4424EC, (unsigned int)g_earlierMenuPaged_40BB40, 0x0007, 0x0000, 0x0000, 0x0000, 0x00000000 };

struct MenuBuildDefinitionData g_earlierMenuDef_4501A0 = { (unsigned int)g_earlierMenuItems_450038, 0x0008, 0x0000, (unsigned int)g_earlierMenuPaged_40BC54, 0x00000000, (unsigned int)g_earlierMenuPaged_4424EC, (unsigned int)g_earlierMenuPaged_40BB40, 0x0007, 0x0000, 0x0000, 0x0000, 0x00000000 };

struct MenuBuildDefinitionData g_earlierMenuDef_4501C4 = { (unsigned int)g_earlierMenuItems_450038, 0x0008, 0x0000, (unsigned int)g_earlierMenuPaged_40BC70, 0x00000000, (unsigned int)g_earlierMenuPaged_4424EC, (unsigned int)g_earlierMenuPaged_40BB40, 0x0007, 0x0000, 0x0000, 0x0000, 0x00000000 };

struct MenuBuildDefinitionData g_earlierMenuDef_4501E8 = { (unsigned int)g_earlierMenuItems_450038, 0x0008, 0x0000, (unsigned int)g_earlierMenuPaged_40BC8C, 0x00000000, (unsigned int)g_earlierMenuPaged_4424EC, (unsigned int)g_earlierMenuPaged_40BB40, 0x0007, 0x0000, 0x0000, 0x0000, 0x00000000 };

unsigned int g_earlierMenuWords_45020C[1] = { 0x00010201 };

struct EarlierOptionBitRow g_earlierOptionBits_450210[12] = {
    { g_earlierOptionWord24, g_earlierOptionName13, 0x00000020, 0x00000001 },
    { g_earlierOptionWord23, g_earlierOptionName15, 0x00000080, 0x00000001 },
    { g_earlierOptionWord22, g_earlierOptionName16, 0x00000100, 0x00000001 },
    { g_earlierOptionWord21, g_earlierOptionName14, 0x00000040, 0x00000001 },
    { g_earlierOptionWord20, g_earlierOptionName17, 0x00000200, 0x00000001 },
    { g_earlierOptionWord19, g_earlierOptionName18, 0x00000400, 0x00000001 },
    { g_earlierOptionWord18, g_earlierOptionName19, 0x00000800, 0x00000001 },
    { g_earlierOptionWord17, g_earlierOptionName20, 0x00001000, 0x00000001 },
    { g_earlierOptionWord16, g_earlierOptionName21, 0x00004000, 0x00000001 },
    { g_earlierOptionWord15, g_earlierOptionName22, 0x00008000, 0x00000001 },
    { g_earlierOptionWord14, g_earlierOptionName23, 0xFFFFFFFF, 0x00000001 },
    { g_earlierOptionWord13, g_earlierOptionName24, 0x0400C7E0, 0x00000001 },
};

struct MenuBuildItemData g_earlierMenuItems_4502D0[33] = {
    { 0x0001, 0x0000, 0x50000000, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x00000385, (unsigned int)g_earlierMenuPaged_4411C4, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x08000801, 0x0000, 0x0008, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource262, (unsigned int)g_earlierMenuPaged_442F6C, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00210041, 0x0000, 0x0014, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource394, (unsigned int)g_earlierMenuPaged_43D88C, (unsigned int)g_earlierMenuPaged_43DA10, (unsigned int)g_earlierMenuPaged_43DAE8, 0x00000000 },
    { 0x0000, 0x0000, 0x00010050, 0x0050, 0x0014, 0x06, 0x01, 0xFF, 0x07, (int)g_earlierMenuResource318, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_43DAF0, 0x00000000 },
    { 0x0000, 0x0000, 0x00024050, 0x0008, 0x0000, 0xFF, 0x01, 0xFE, 0x07, (int)g_earlierMenuResource320, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_43DAF0, 0x00000000 },
    { 0x0000, 0x0000, 0x00024050, 0x0008, 0x0000, 0xFF, 0x01, 0xFD, 0x07, (int)g_earlierMenuResource322, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_43DAF0, 0x00000000 },
    { 0x0000, 0x0000, 0x00024050, 0x0008, 0x0000, 0xFF, 0x01, 0xFC, 0x07, (int)g_earlierMenuResource324, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_43DAF0, 0x00000000 },
    { 0x0000, 0x0000, 0x00024050, 0x0008, 0x0000, 0xFF, 0x01, 0xFB, 0x07, (int)g_earlierMenuResource326, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_43DAF0, 0x00000000 },
    { 0x0000, 0x0000, 0x00024050, 0x0008, 0x0000, 0xFF, 0x01, 0xFA, 0x07, (int)g_earlierMenuResource328, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_43DAF0, 0x00000000 },
    { 0x0000, 0x0000, 0x00024050, 0x0008, 0x0000, 0xFF, 0xFA, 0xF9, 0x07, (int)g_earlierMenuResource330, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_43DAF0, 0x00000000 },
    { 0x0000, 0x0000, 0x00010050, 0x0050, 0x0008, 0x06, 0x01, 0xF9, 0x07, (int)g_earlierMenuResource332, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_43DAF0, 0x00000000 },
    { 0x0000, 0x0000, 0x00024050, 0x0008, 0x0000, 0xFF, 0x01, 0xF9, 0x07, (int)g_earlierMenuResource334, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_43DAF0, 0x00000000 },
    { 0x0000, 0x0000, 0x00024050, 0x0008, 0x0000, 0xFF, 0x01, 0xF9, 0x07, (int)g_earlierMenuResource336, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_43DAF0, 0x00000000 },
    { 0x0000, 0x0000, 0x00024050, 0x0008, 0x0000, 0xFF, 0x01, 0xF9, 0x07, (int)g_earlierMenuResource338, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_43DAF0, 0x00000000 },
    { 0x0000, 0x0000, 0x00024050, 0x0008, 0x0000, 0xFF, 0x01, 0xF9, 0x07, (int)g_earlierMenuResource340, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_43DAF0, 0x00000000 },
    { 0x0000, 0x0000, 0x00024050, 0x0008, 0x0000, 0xFF, 0x01, 0xF9, 0x07, (int)g_earlierMenuResource342, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_43DAF0, 0x00000000 },
    { 0x0000, 0x0000, 0x00024050, 0x0008, 0x0000, 0xFF, 0xFA, 0xF9, 0x07, (int)g_earlierMenuResource344, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_43DAF0, 0x00000000 },
    { 0x0000, 0x0000, 0x00010050, 0x0050, 0x0008, 0x06, 0x01, 0xF9, 0x07, (int)g_earlierMenuResource346, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_43DAF0, 0x00000000 },
    { 0x0000, 0x0000, 0x00024050, 0x0008, 0x0000, 0xFF, 0x01, 0xF9, 0x07, (int)g_earlierMenuResource348, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_43DAF0, 0x00000000 },
    { 0x0000, 0x0000, 0x00024050, 0x0008, 0x0000, 0xFF, 0x01, 0xF9, 0x07, (int)g_earlierMenuResource350, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_43DAF0, 0x00000000 },
    { 0x0000, 0x0000, 0x00024050, 0x0008, 0x0000, 0xFF, 0x01, 0xF9, 0x07, (int)g_earlierMenuResource352, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_43DAF0, 0x00000000 },
    { 0x0000, 0x0000, 0x00024050, 0x0008, 0x0000, 0xFF, 0x01, 0xF9, 0x07, (int)g_earlierMenuResource354, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_43DAF0, 0x00000000 },
    { 0x0000, 0x0000, 0x00024050, 0x0008, 0x0000, 0xFF, 0x01, 0xF9, 0x07, (int)g_earlierMenuResource356, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_43DAF0, 0x00000000 },
    { 0x0000, 0x0000, 0x00024050, 0x0008, 0x0000, 0xFF, 0xFA, 0xF9, 0x07, (int)g_earlierMenuResource358, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_43DAF0, 0x00000000 },
    { 0x0000, 0x0000, 0x00010050, 0x0050, 0x0008, 0x06, 0x01, 0xF9, 0x08, (int)g_earlierMenuResource360, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_43DAF0, 0x00000000 },
    { 0x0000, 0x0000, 0x00024050, 0x0008, 0x0000, 0xFF, 0x01, 0xF9, 0x07, (int)g_earlierMenuResource362, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_43DAF0, 0x00000000 },
    { 0x0000, 0x0000, 0x00024050, 0x0008, 0x0000, 0xFF, 0x01, 0xF9, 0x06, (int)g_earlierMenuResource364, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_43DAF0, 0x00000000 },
    { 0x0000, 0x0000, 0x00024050, 0x0008, 0x0000, 0xFF, 0x01, 0xF9, 0x05, (int)g_earlierMenuResource366, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_43DAF0, 0x00000000 },
    { 0x0000, 0x0000, 0x00024050, 0x0008, 0x0000, 0xFF, 0x01, 0xF9, 0x04, (int)g_earlierMenuResource368, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_43DAF0, 0x00000000 },
    { 0x0000, 0x0000, 0x00024050, 0x0008, 0x0000, 0xFF, 0x01, 0xF9, 0x03, (int)g_earlierMenuResource391, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_43DBC0, 0x00000000 },
    { 0x0000, 0x0000, 0x00024050, 0x0008, 0x0000, 0xFF, 0xFA, 0xF9, 0x02, (int)g_earlierMenuResource392, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_43DCE8, 0x00000000 },
    { 0x0000, 0x0000, 0x00011001, 0x0000, 0x0014, 0x00, 0x00, 0x00, 0x00, (int)g_earlierMenuResource308, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_43DE34, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00310201, 0x0000, 0x0018, 0x00, 0x00, 0xFE, 0xE2, (int)g_earlierMenuResource263, (unsigned int)g_earlierMenuPaged_442F6C, 0x00000000, (unsigned int)g_earlierMenuPaged_4432AC, 0x00000000 },
};

struct MenuBuildDefinitionData g_earlierMenuDef_450774 = { (unsigned int)g_earlierMenuItems_4502D0, 0x0021, 0x0000, (unsigned int)g_earlierMenuPaged_43D878, 0x00000000, (unsigned int)g_earlierMenuPaged_4424EC, 0x00000000, 0x0002, 0x0000, 0x0000, 0x0000, 0x00000000 };

struct MenuBuildItemData g_earlierMenuItems_450798[20] = {
    { 0x0001, 0x0000, 0x50000000, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x00000385, (unsigned int)g_earlierMenuPaged_4411C4, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x08000021, 0x0000, 0x0008, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource261, (unsigned int)g_earlierMenuPaged_442F6C, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00411001, 0x0000, 0x000C, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource265, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_43E168, (unsigned int)g_earlierMenuPaged_43E14C, 0x00000000 },
    { 0x0000, 0x0000, 0x00411001, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource266, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_43E1F0, (unsigned int)g_earlierMenuPaged_43E1D4, 0x00000000 },
    { 0x0000, 0x0000, 0x00411001, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource267, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_43E278, (unsigned int)g_earlierMenuPaged_43E25C, 0x00000000 },
    { 0x0000, 0x0000, 0x00411001, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource268, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_43E300, (unsigned int)g_earlierMenuPaged_43E2E4, 0x00000000 },
    { 0x0000, 0x0000, 0x00411001, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource269, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_43E388, (unsigned int)g_earlierMenuPaged_43E36C, 0x00000000 },
    { 0x0000, 0x0000, 0x00411001, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource270, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_43E410, (unsigned int)g_earlierMenuPaged_43E3F4, 0x00000000 },
    { 0x0000, 0x0000, 0x00411001, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource271, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_43E498, (unsigned int)g_earlierMenuPaged_43E47C, 0x00000000 },
    { 0x0000, 0x0000, 0x00411001, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource273, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_43E5A8, (unsigned int)g_earlierMenuPaged_43E58C, 0x00000000 },
    { 0x0000, 0x0000, 0x00411001, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource272, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_43E520, (unsigned int)g_earlierMenuPaged_43E504, 0x00000000 },
    { 0x0000, 0x0000, 0x00411001, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource274, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_43E630, (unsigned int)g_earlierMenuPaged_43E614, 0x00000000 },
    { 0x0000, 0x0000, 0x00411001, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource275, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_43E6B8, (unsigned int)g_earlierMenuPaged_43E69C, 0x00000000 },
    { 0x0000, 0x0000, 0x00411001, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource276, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_43E740, (unsigned int)g_earlierMenuPaged_43E724, 0x00000000 },
    { 0x0000, 0x0000, 0x00411001, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource277, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_43E7C8, (unsigned int)g_earlierMenuPaged_43E7AC, 0x00000000 },
    { 0x0000, 0x0000, 0x00411001, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource278, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_43E850, (unsigned int)g_earlierMenuPaged_43E834, 0x00000000 },
    { 0x0000, 0x0000, 0x00411001, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource279, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_43E8D8, (unsigned int)g_earlierMenuPaged_43E8BC, 0x00000000 },
    { 0x0000, 0x0000, 0x00411001, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource280, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_43E960, (unsigned int)g_earlierMenuPaged_43E944, 0x00000000 },
    { 0x0000, 0x0000, 0x00411001, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource308, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_43DFE0, (unsigned int)g_earlierMenuPaged_43D568, 0x00000000 },
    { 0x0000, 0x0000, 0x00000201, 0x0000, 0x00C0, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource263, (unsigned int)g_earlierMenuPaged_442F6C, 0x00000000, (unsigned int)g_earlierMenuPaged_4432AC, 0x00000000 },
};

struct MenuBuildDefinitionData g_earlierMenuDef_450A68 = { (unsigned int)g_earlierMenuItems_450798, 0x0014, 0x0000, (unsigned int)g_earlierMenuPaged_43D430, 0x00000000, (unsigned int)g_earlierMenuPaged_4424EC, 0x00000000, 0x0013, 0x0000, 0x0000, 0x0000, 0x00000000 };

unsigned int g_earlierMenuWords_450A8C[1] = { 0x00000000 };

struct MenuBuildItemData g_earlierMenuItems_450A90[3] = {
    { 0x0000, 0x0000, 0x00000021, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource264, (unsigned int)g_earlierMenuPaged_442F6C, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00010081, 0x0000, 0x0028, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource259, (unsigned int)g_earlierMenuPaged_442F6C, 0x00000000, (unsigned int)g_earlierMenuPaged_43E9D0, 0x00000000 },
    { 0x0000, 0x0000, 0x00010081, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource260, (unsigned int)g_earlierMenuPaged_442F6C, 0x00000000, (unsigned int)g_earlierMenuPaged_43E9F4, 0x00000000 },
};

struct MenuBuildDefinitionData g_earlierMenuDef_450AFC = { (unsigned int)g_earlierMenuItems_450A90, 0x0003, 0x0000, 0x00000000, 0x00000000, (unsigned int)g_earlierMenuPaged_4424EC, 0x00000000, 0x0001, 0x0000, 0x0000, 0x0000, 0x00000000 };

struct MenuBuildItemData g_earlierMenuItems_450B20[8] = {
    { 0x0000, 0x0000, 0x00011001, 0x0000, 0x0000, 0x00, 0x00, 0x00, 0x00, (int)g_earlierMenuResource196, (unsigned int)g_earlierMenuPaged_442F6C, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00011001, 0x0000, 0x0000, 0x00, 0x00, 0x00, 0x00, (int)g_earlierMenuResource197, (unsigned int)g_earlierMenuPaged_442F6C, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00011001, 0x0000, 0x0000, 0x00, 0x00, 0x00, 0x00, (int)g_earlierMenuResource198, (unsigned int)g_earlierMenuPaged_442F6C, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00011001, 0x0000, 0x0000, 0x00, 0x00, 0x00, 0x00, (int)g_earlierMenuResource199, (unsigned int)g_earlierMenuPaged_442F6C, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00011001, 0x0000, 0x0000, 0x00, 0x00, 0x00, 0x00, (int)g_earlierMenuResource200, (unsigned int)g_earlierMenuPaged_442F6C, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00011001, 0x0000, 0x0000, 0x00, 0x00, 0x00, 0x00, (int)g_earlierMenuResource201, (unsigned int)g_earlierMenuPaged_442F6C, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00011001, 0x0000, 0x0000, 0x00, 0x00, 0x00, 0x00, (int)g_earlierMenuResource202, (unsigned int)g_earlierMenuPaged_442F6C, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0005, 0x00, 0x00, 0x00, 0x00, (int)g_earlierMenuResource195, (unsigned int)g_earlierMenuPaged_442F6C, 0x00000000, (unsigned int)g_earlierMenuPaged_43EF94, 0x00000000 },
};

struct MenuBuildDefinitionData g_earlierMenuDef_450C40 = { (unsigned int)g_earlierMenuItems_450B20, 0x0008, 0x0000, 0x00000000, 0x00000000, (unsigned int)g_earlierMenuPaged_4424EC, (unsigned int)g_earlierMenuPaged_43EF5C, 0x0007, 0x0000, 0x0000, 0x0000, (int)&g_earlierMenuDef_450D18 };

struct MenuBuildItemData g_earlierMenuItems_450C64[5] = {
    { 0x0000, 0x0000, 0x00011001, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x02, (int)g_earlierMenuResource192, (unsigned int)g_earlierMenuPaged_442F6C, 0x00000000, (unsigned int)g_earlierMenuPaged_43F1C4, 0x00000000 },
    { 0x0000, 0x0000, 0x00010101, 0x0000, 0x0008, 0x00, 0x00, 0x00, 0x00, (int)g_earlierMenuResource193, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_43F1F0, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00411001, 0x0000, 0x0008, 0x00, 0x00, 0xFE, 0x01, (int)g_earlierMenuResource308, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_43F074, (unsigned int)g_earlierMenuPaged_43F028, 0x00000000 },
    { 0x0000, 0x0000, 0x00411001, 0x0000, 0x0002, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource194, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_43F240, (unsigned int)g_earlierMenuPaged_43F178, 0x00000000 },
    { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0005, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource195, (unsigned int)g_earlierMenuPaged_442F6C, 0x00000000, (unsigned int)g_earlierMenuPaged_43F214, 0x00000000 },
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
    { 0x0000, 0x0000, 0x00010081, 0x0000, 0x0019, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource191, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_43F374, (unsigned int)g_earlierMenuPaged_43F314, 0x00000000 },
};

struct MenuBuildDefinitionData g_earlierMenuDef_450DD8 = { (unsigned int)g_earlierMenuItems_450D6C, 0x0003, 0x0000, (unsigned int)g_earlierMenuPaged_43F28C, 0x00000000, (unsigned int)g_earlierMenuPaged_4424EC, (unsigned int)g_earlierMenuPaged_43F2DC, 0x0001, 0x0000, 0x0000, 0x0000, 0x00000000 };

struct MenuBuildDefinitionData g_earlierMenuDef_450DFC = { (unsigned int)g_earlierMenuItems_450D6C, 0x0003, 0x0000, (unsigned int)g_earlierMenuPaged_43F2B0, 0x00000000, (unsigned int)g_earlierMenuPaged_4424EC, (unsigned int)g_earlierMenuPaged_43F2DC, 0x0001, 0x0000, 0x0000, 0x0000, 0x00000000 };

struct MenuBuildItemData g_earlierMenuItems_450E20[4] = {
    { 0x0001, 0x0000, 0x30000000, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x00000387, (unsigned int)g_earlierMenuPaged_4411C4, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00010081, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource203, (unsigned int)g_earlierMenuPaged_442F6C, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00010101, 0x0000, 0x000C, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource204, (unsigned int)g_earlierMenuPaged_442F6C, 0x00000000, (unsigned int)g_earlierMenuPaged_43F4A8, 0x00000000 },
    { 0x0000, 0x0000, 0x00010101, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource205, (unsigned int)g_earlierMenuPaged_442F6C, 0x00000000, (unsigned int)g_earlierMenuPaged_43F4F0, 0x00000000 },
};

struct MenuBuildDefinitionData g_earlierMenuDef_450EB0 = { (unsigned int)g_earlierMenuItems_450E20, 0x0004, 0x0000, 0x00000000, 0x00000000, (unsigned int)g_earlierMenuPaged_4424EC, (unsigned int)g_earlierMenuPaged_43F470, 0x0002, 0x0000, 0x0000, 0x0000, 0x00000000 };

float g_earlierMenuRamp_450ED4[16] = {
    -0.5f, -0.4f, -0.3f, -0.2f, -0.1f, 0.0f, 0.1f, 0.2f,
    0.3f, 0.4f, 0.5f, 0.6f, 0.7f, 0.8f, 0.9f, 1.0f,
};

struct MenuBuildItemData g_earlierMenuItems_450F14[11] = {
    { 0x0001, 0x0000, 0x10000000, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x00000385, (unsigned int)g_earlierMenuPaged_4411C4, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x08000201, 0x0000, 0x000C, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource294, (unsigned int)g_earlierMenuPaged_442F6C, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00410041, 0x0000, 0x001E, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource308, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_43EA40, (unsigned int)g_earlierMenuPaged_43F6DC, 0x00000000 },
    { 0x0000, 0x0000, 0x00410041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource308, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_43EA40, (unsigned int)g_earlierMenuPaged_43F6DC, 0x00000000 },
    { 0x0000, 0x0000, 0x00410041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource308, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_43EA40, (unsigned int)g_earlierMenuPaged_43F6DC, 0x00000000 },
    { 0x0000, 0x0000, 0x00410041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource308, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_43EA40, (unsigned int)g_earlierMenuPaged_43F6DC, 0x00000000 },
    { 0x0000, 0x0000, 0x00410041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource308, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_43EA40, (unsigned int)g_earlierMenuPaged_43F6DC, 0x00000000 },
    { 0x0000, 0x0000, 0x00410041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource308, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_43EA40, (unsigned int)g_earlierMenuPaged_43F6DC, 0x00000000 },
    { 0x0000, 0x0000, 0x00410041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource308, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_43EA40, (unsigned int)g_earlierMenuPaged_43F6DC, 0x00000000 },
    { 0x0000, 0x0000, 0x00410041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource308, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_43EA40, (unsigned int)g_earlierMenuPaged_43F6DC, 0x00000000 },
    { 0x0000, 0x0000, 0x00010201, 0x0000, 0x002D, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource263, (unsigned int)g_earlierMenuPaged_442F6C, 0x00000000, (unsigned int)g_earlierMenuPaged_4432AC, 0x00000000 },
};

struct MenuBuildDefinitionData g_earlierMenuDef_4510A0 = { (unsigned int)g_earlierMenuItems_450F14, 0x000B, 0x0000, 0x00000000, 0x00000000, (unsigned int)g_earlierMenuPaged_4424EC, 0x00000000, 0x000A, 0x0000, 0x0000, 0x0000, (int)&g_earlierMenuDef_451154 };

struct MenuBuildItemData g_earlierMenuItems_4510C4[4] = {
    { 0x0001, 0x0000, 0x10000000, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x00000385, (unsigned int)g_earlierMenuPaged_4411C4, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x08000021, 0x0000, 0x0008, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource293, (unsigned int)g_earlierMenuPaged_442F6C, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00010081, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource294, (unsigned int)g_earlierMenuPaged_442F6C, 0x00000000, (unsigned int)g_earlierMenuPaged_43F7C8, 0x00000000 },
    { 0x0000, 0x0000, 0x00010201, 0x0000, 0x0038, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource263, (unsigned int)g_earlierMenuPaged_442F6C, 0x00000000, (unsigned int)g_earlierMenuPaged_4432AC, 0x00000000 },
};

struct MenuBuildDefinitionData g_earlierMenuDef_451154 = { (unsigned int)g_earlierMenuItems_4510C4, 0x0004, 0x0000, 0x00000000, 0x00000000, (unsigned int)g_earlierMenuPaged_4424EC, 0x00000000, 0x0002, 0x0000, 0x0000, 0x0000, (int)&g_earlierMenuDef_4513B8 };

struct MenuBuildItemData g_earlierMenuItems_451178[5] = {
    { 0x0001, 0x0000, 0x10000000, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x00000385, (unsigned int)g_earlierMenuPaged_4411C4, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x08000801, 0x0000, 0x0008, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource289, (unsigned int)g_earlierMenuPaged_442F6C, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00010081, 0x0000, 0x0036, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource290, (unsigned int)g_earlierMenuPaged_442F6C, 0x00000000, (unsigned int)g_earlierMenuPaged_43F854, 0x00000000 },
    { 0x0000, 0x0000, 0x00010081, 0x0000, 0x0004, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource291, (unsigned int)g_earlierMenuPaged_442F6C, 0x00000000, (unsigned int)g_earlierMenuPaged_43F8AC, 0x00000000 },
    { 0x0000, 0x0000, 0x00010201, 0x0000, 0x0049, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource190, (unsigned int)g_earlierMenuPaged_442F6C, 0x00000000, (unsigned int)g_earlierMenuPaged_43F8F8, 0x00000000 },
};

struct MenuBuildDefinitionData g_earlierMenuDef_45122C = { (unsigned int)g_earlierMenuItems_451178, 0x0005, 0x0000, (unsigned int)g_earlierMenuPaged_43F7F4, 0x00000000, (unsigned int)g_earlierMenuPaged_4424EC, 0x00000000, 0x0002, 0x0000, 0x0000, 0x0000, 0x00000000 };

struct MenuBuildDefinitionData g_earlierMenuDef_451250 = { (unsigned int)g_earlierMenuItems_451178, 0x0005, 0x0000, (unsigned int)g_earlierMenuPaged_43F828, 0x00000000, (unsigned int)g_earlierMenuPaged_4424EC, 0x00000000, 0x0002, 0x0000, 0x0000, 0x0000, 0x00000000 };

struct MenuBuildItemData g_earlierMenuItems_451274[1] = {
    { 0x0001, 0x0000, 0x10000000, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x00000385, (unsigned int)g_earlierMenuPaged_4411C4, 0x00000000, 0x00000000, 0x00000000 },
};

struct MenuBuildDefinitionData g_earlierMenuDef_451298 = { (unsigned int)g_earlierMenuItems_451274, 0x0001, 0x0000, 0x00000000, 0x00000000, (unsigned int)g_earlierMenuPaged_4424EC, 0x00000000, 0x0002, 0x0000, 0x0000, 0x0000, (int)&g_earlierMenuDef_4513B8 };

struct MenuBuildItemData g_earlierMenuItems_4512BC[7] = {
    { 0x0001, 0x0000, 0x10000000, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x00000384, (unsigned int)g_earlierMenuPaged_4411C4, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00000081, 0x0000, 0x001E, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource289, (unsigned int)g_earlierMenuPaged_442F6C, 0x00000000, (unsigned int)g_earlierMenuPaged_43F944, 0x00000000 },
    { 0x0000, 0x0000, 0x00010081, 0x0000, 0x000C, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource292, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_43FA1C, (unsigned int)g_earlierMenuPaged_43FA90, 0x00000000 },
    { 0x0000, 0x0000, 0x00010081, 0x0000, 0x000C, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource262, (unsigned int)g_earlierMenuPaged_442F6C, 0x00000000, (unsigned int)g_earlierMenuPaged_43FB18, 0x00000000 },
    { 0x0000, 0x0000, 0x00010081, 0x0000, 0x000C, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource297, (unsigned int)g_earlierMenuPaged_442F6C, 0x00000000, (unsigned int)g_earlierMenuPaged_43FB44, 0x00000000 },
    { 0x0000, 0x0000, 0x00010081, 0x0000, 0x000C, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource296, (unsigned int)g_earlierMenuPaged_442F6C, 0x00000000, (unsigned int)g_earlierMenuPaged_43FAEC, 0x00000000 },
    { 0x0000, 0x0000, 0x00010081, 0x0000, 0x000C, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource298, (unsigned int)g_earlierMenuPaged_442F6C, 0x00000000, (unsigned int)g_earlierMenuPaged_43FB70, 0x00000000 },
};

struct MenuBuildDefinitionData g_earlierMenuDef_4513B8 = { (unsigned int)g_earlierMenuItems_4512BC, 0x0007, 0x0000, 0x00000000, 0x00000000, (unsigned int)g_earlierMenuPaged_4424EC, 0x00000000, 0x0001, 0x0000, 0x0000, 0x0000, 0x00000000 };

unsigned int g_earlierMenuWords_4513DC[1] = { 0x00000000 };

struct MenuBuildItemData g_earlierMenuItems_4513E0[2] = {
    { 0x0001, 0x0000, 0x00000000, 0x0000, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x00000064, (unsigned int)g_earlierMenuPaged_4411C4, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00000089, 0x0000, 0x0028, 0x00, 0x00, 0x00, 0x00, (int)g_earlierMenuResource393, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_43FCC4, 0x00000000, 0x00000000 },
};

struct MenuBuildDefinitionData g_earlierMenuDef_451428 = { (unsigned int)g_earlierMenuItems_4513E0, 0x0002, 0x0000, (unsigned int)g_earlierMenuPaged_43FC50, 0x00000000, (unsigned int)g_earlierMenuPaged_4424EC, (unsigned int)g_earlierMenuPaged_43FC7C, 0x0001, 0x0000, 0x0000, 0x0000, 0x00000000 };

unsigned int g_earlierMenuWords_45144C[1] = { 0x00010041 };

struct MenuBuildItemData g_earlierMenuItems_451450[49] = {
    { 0x0001, 0x0000, 0x50000000, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x00000385, (unsigned int)g_earlierMenuPaged_4411C4, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x08000801, 0x0000, 0x0008, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource218, (unsigned int)g_earlierMenuPaged_442F6C, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00010080, 0x0023, 0x0016, 0x00, 0x00, 0x00, 0x00, (int)g_earlierMenuResource309, (unsigned int)g_earlierMenuPaged_442F6C, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0001, 0x0000, 0x00024010, 0x0003, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x000007D0, (unsigned int)g_earlierMenuPaged_43FD00, 0x00000000, 0x00000000, 0x10D60000 },
    { 0x0001, 0x0000, 0x00024010, 0x0003, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x000007D0, (unsigned int)g_earlierMenuPaged_43FD00, 0x00000000, 0x00000000, 0x10D60001 },
    { 0x0001, 0x0000, 0x00024010, 0x0003, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x000007D0, (unsigned int)g_earlierMenuPaged_43FD00, 0x00000000, 0x00000000, 0x10D60002 },
    { 0x0001, 0x0000, 0x00024010, 0x0003, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x000007D1, (unsigned int)g_earlierMenuPaged_43FD00, 0x00000000, 0x00000000, 0x10E00000 },
    { 0x0001, 0x0000, 0x00024010, 0x0003, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x000007D1, (unsigned int)g_earlierMenuPaged_43FD00, 0x00000000, 0x00000000, 0x10E00001 },
    { 0x0001, 0x0000, 0x00024010, 0x0003, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x000007D1, (unsigned int)g_earlierMenuPaged_43FD00, 0x00000000, 0x00000000, 0x10E00002 },
    { 0x0001, 0x0000, 0x00024010, 0x0029, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x000007E4, (unsigned int)g_earlierMenuPaged_43FD00, 0x00000000, 0x00000000, 0x11080000 },
    { 0x0001, 0x0000, 0x00024010, 0x0003, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x00000820, (unsigned int)g_earlierMenuPaged_43FD00, 0x00000000, 0x00000000, 0x11940000 },
    { 0x0000, 0x0000, 0x00010080, 0x0023, 0x0003, 0x00, 0x00, 0x00, 0x00, (int)g_earlierMenuResource310, (unsigned int)g_earlierMenuPaged_442F6C, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0001, 0x0000, 0x00024010, 0x0003, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x000007D2, (unsigned int)g_earlierMenuPaged_43FD00, 0x00000000, 0x00000000, 0x10EA0000 },
    { 0x0001, 0x0000, 0x00024010, 0x0003, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x000007D2, (unsigned int)g_earlierMenuPaged_43FD00, 0x00000000, 0x00000000, 0x10EA0001 },
    { 0x0001, 0x0000, 0x00024010, 0x0003, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x000007D2, (unsigned int)g_earlierMenuPaged_43FD00, 0x00000000, 0x00000000, 0x10EA0002 },
    { 0x0001, 0x0000, 0x00024010, 0x003C, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x0000080D, (unsigned int)g_earlierMenuPaged_43FD00, 0x00000000, 0x00000000, 0x11320000 },
    { 0x0001, 0x0000, 0x00024010, 0x0003, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x000007F9, (unsigned int)g_earlierMenuPaged_43FD00, 0x00000000, 0x00000000, 0x111E0000 },
    { 0x0001, 0x0000, 0x00024010, 0x0003, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x000007E5, (unsigned int)g_earlierMenuPaged_43FD00, 0x00000000, 0x00000000, 0x11090000 },
    { 0x0001, 0x0000, 0x00024010, 0x0003, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x00000820, (unsigned int)g_earlierMenuPaged_43FD00, 0x00000000, 0x00000000, 0x11940001 },
    { 0x0000, 0x0000, 0x00010080, 0x0023, 0x0003, 0x00, 0x00, 0x00, 0x00, (int)g_earlierMenuResource311, (unsigned int)g_earlierMenuPaged_442F6C, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0001, 0x0000, 0x00024010, 0x0003, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x000007D3, (unsigned int)g_earlierMenuPaged_43FD00, 0x00000000, 0x00000000, 0x10F40000 },
    { 0x0001, 0x0000, 0x00024010, 0x0003, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x000007D3, (unsigned int)g_earlierMenuPaged_43FD00, 0x00000000, 0x00000000, 0x10F40001 },
    { 0x0001, 0x0000, 0x00024010, 0x0003, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x000007D3, (unsigned int)g_earlierMenuPaged_43FD00, 0x00000000, 0x00000000, 0x10F40002 },
    { 0x0001, 0x0000, 0x00024010, 0x003C, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x0000080F, (unsigned int)g_earlierMenuPaged_43FD00, 0x00000000, 0x00000000, 0x11300000 },
    { 0x0001, 0x0000, 0x00024010, 0x0003, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x000007F8, (unsigned int)g_earlierMenuPaged_43FD00, 0x00000000, 0x00000000, 0x111C0000 },
    { 0x0001, 0x0000, 0x00024010, 0x0003, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x000007E6, (unsigned int)g_earlierMenuPaged_43FD00, 0x00000000, 0x00000000, 0x110A0000 },
    { 0x0001, 0x0000, 0x00024010, 0x0003, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x00000820, (unsigned int)g_earlierMenuPaged_43FD00, 0x00000000, 0x00000000, 0x11940002 },
    { 0x0000, 0x0000, 0x00010080, 0x0023, 0x0003, 0x00, 0x00, 0x00, 0x00, (int)g_earlierMenuResource312, (unsigned int)g_earlierMenuPaged_442F6C, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0001, 0x0000, 0x00024010, 0x0003, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x000007D4, (unsigned int)g_earlierMenuPaged_43FD00, 0x00000000, 0x00000000, 0x10FE0000 },
    { 0x0001, 0x0000, 0x00024010, 0x0003, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x000007D4, (unsigned int)g_earlierMenuPaged_43FD00, 0x00000000, 0x00000000, 0x10FE0001 },
    { 0x0001, 0x0000, 0x00024010, 0x0003, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x000007D4, (unsigned int)g_earlierMenuPaged_43FD00, 0x00000000, 0x00000000, 0x10FE0002 },
    { 0x0001, 0x0000, 0x00024010, 0x003C, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x0000080E, (unsigned int)g_earlierMenuPaged_43FD00, 0x00000000, 0x00000000, 0x11340000 },
    { 0x0001, 0x0000, 0x00024010, 0x0003, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x000007FC, (unsigned int)g_earlierMenuPaged_43FD00, 0x00000000, 0x00000000, 0x11200000 },
    { 0x0001, 0x0000, 0x00024010, 0x0003, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x000007E7, (unsigned int)g_earlierMenuPaged_43FD00, 0x00000000, 0x00000000, 0x110B0000 },
    { 0x0001, 0x0000, 0x00024010, 0x0003, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x00000820, (unsigned int)g_earlierMenuPaged_43FD00, 0x00000000, 0x00000000, 0x11940003 },
    { 0x0000, 0x0000, 0x00010080, 0x0023, 0x0003, 0x00, 0x00, 0x00, 0x00, (int)g_earlierMenuResource313, (unsigned int)g_earlierMenuPaged_442F6C, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0001, 0x0000, 0x00024010, 0x0003, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x000007D4, (unsigned int)g_earlierMenuPaged_43FD00, 0x00000000, 0x00000000, 0x10FE0003 },
    { 0x0001, 0x0000, 0x00024010, 0x0003, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x000007D4, (unsigned int)g_earlierMenuPaged_43FD00, 0x00000000, 0x00000000, 0x10FE0004 },
    { 0x0001, 0x0000, 0x00024010, 0x0003, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x000007D4, (unsigned int)g_earlierMenuPaged_43FD00, 0x00000000, 0x00000000, 0x10FE0005 },
    { 0x0001, 0x0000, 0x00024010, 0x003C, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x0000080C, (unsigned int)g_earlierMenuPaged_43FD00, 0x00000000, 0x00000000, 0x11330000 },
    { 0x0001, 0x0000, 0x00024010, 0x0003, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x000007FB, (unsigned int)g_earlierMenuPaged_43FD00, 0x00000000, 0x00000000, 0x111F0000 },
    { 0x0001, 0x0000, 0x00024010, 0x0003, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x000007E8, (unsigned int)g_earlierMenuPaged_43FD00, 0x00000000, 0x00000000, 0x110C0000 },
    { 0x0001, 0x0000, 0x00024010, 0x0003, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x00000820, (unsigned int)g_earlierMenuPaged_43FD00, 0x00000000, 0x00000000, 0x11940004 },
    { 0x0000, 0x0000, 0x00010080, 0x0023, 0x0003, 0x00, 0x00, 0x00, 0x00, (int)g_earlierMenuResource314, (unsigned int)g_earlierMenuPaged_442F6C, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0001, 0x0000, 0x00024010, 0x0075, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x00000810, (unsigned int)g_earlierMenuPaged_43FD00, 0x00000000, 0x00000000, 0x11310000 },
    { 0x0001, 0x0000, 0x00024010, 0x0003, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x000007FA, (unsigned int)g_earlierMenuPaged_43FD00, 0x00000000, 0x00000000, 0x111D0000 },
    { 0x0001, 0x0000, 0x00024010, 0x0003, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x000007E9, (unsigned int)g_earlierMenuPaged_43FD00, 0x00000000, 0x00000000, 0x110D0000 },
    { 0x0001, 0x0000, 0x00024010, 0x0003, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x00000820, (unsigned int)g_earlierMenuPaged_43FD00, 0x00000000, 0x00000000, 0x11940005 },
    { 0x0000, 0x0000, 0x00010081, 0x0000, 0x001E, 0x00, 0x00, 0x00, 0x00, (int)g_earlierMenuResource219, (unsigned int)g_earlierMenuPaged_442F6C, 0x00000000, (unsigned int)g_earlierMenuPaged_43FF68, 0x00000000 },
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
    { 0x0000, 0x0000, 0x00000401, 0x0000, 0x0028, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource282, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_444430, 0x00000000, 0x00000000 },
    { 0x0001, 0x0000, 0x20010001, 0x0000, 0x0000, 0x00, 0x00, 0x00, 0x01, 0x0000012D, (unsigned int)g_earlierMenuPaged_444778, 0x00000000, (unsigned int)g_earlierMenuPaged_444754, 0x00000000 },
};

struct MenuBuildItemData g_earlierMenuItems_451C3C[3] = {
    { 0x0001, 0x0000, 0x50000000, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x00000385, (unsigned int)g_earlierMenuPaged_4411C4, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00000401, 0x0000, 0x0028, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource284, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_444430, 0x00000000, 0x00000000 },
    { 0x0001, 0x0000, 0x20010001, -20, 0x0000, 0xEC, 0x00, 0x00, 0x01, 0x0000012D, (unsigned int)g_earlierMenuPaged_444778, 0x00000000, (unsigned int)g_earlierMenuPaged_444754, 0x00000000 },
};

struct MenuBuildItemData g_earlierMenuItems_451CA8[3] = {
    { 0x0001, 0x0000, 0x50000000, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x00000385, (unsigned int)g_earlierMenuPaged_4411C4, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00000401, 0x0000, 0x0028, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource286, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_444430, 0x00000000, 0x00000000 },
    { 0x0001, 0x0000, 0x20010001, 0x0000, 0x0000, 0x00, 0x00, 0x00, 0x01, 0x0000012D, (unsigned int)g_earlierMenuPaged_444778, 0x00000000, (unsigned int)g_earlierMenuPaged_444754, 0x00000000 },
};

struct MenuBuildItemData g_earlierMenuItems_451D14[3] = {
    { 0x0001, 0x0000, 0x50000000, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x00000385, (unsigned int)g_earlierMenuPaged_4411C4, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00000401, 0x0000, 0x0028, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource288, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_444430, 0x00000000, 0x00000000 },
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
    { 0x0000, 0x0000, 0x08000021, 0x0000, 0x0008, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource296, (unsigned int)g_earlierMenuPaged_442F6C, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00400041, 0x0000, 0x002A, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource167, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_4453D4, (unsigned int)g_earlierMenuPaged_4452DC, 0x00000000 },
    { 0x0000, 0x0000, 0x00410041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource168, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_4454E4, (unsigned int)g_earlierMenuPaged_445480, 0x00000000 },
    { 0x0000, 0x0000, 0x00410041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource170, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_4455AC, (unsigned int)g_earlierMenuPaged_445548, 0x00000000 },
    { 0x0000, 0x0000, 0x00410041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource171, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_44566C, (unsigned int)g_earlierMenuPaged_445608, 0x00000000 },
    { 0x0000, 0x0000, 0x00410041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource173, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_445734, (unsigned int)g_earlierMenuPaged_4456D0, 0x00000000 },
    { 0x0000, 0x0000, 0x00410041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource174, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_4457EC, (unsigned int)g_earlierMenuPaged_445798, 0x00000000 },
    { 0x0000, 0x0000, 0x00410041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource175, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_4458B0, (unsigned int)g_earlierMenuPaged_445860, 0x00000000 },
    { 0x0000, 0x0000, 0x00410041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource178, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_44594C, (unsigned int)g_earlierMenuPaged_4459F0, 0x00000000 },
    { 0x0000, 0x0000, 0x00410041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource180, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_445ABC, (unsigned int)g_earlierMenuPaged_445A58, 0x00000000 },
    { 0x0000, 0x0000, 0x00410041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource182, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_445C14, (unsigned int)g_earlierMenuPaged_445BB0, 0x00000000 },
    { 0x0000, 0x0000, 0x00410041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource183, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_445D08, (unsigned int)g_earlierMenuPaged_445D54, 0x00000000 },
    { 0x0000, 0x0000, 0x00410041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource184, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_445D88, (unsigned int)g_earlierMenuPaged_445E18, 0x00000000 },
    { 0x0000, 0x0000, 0x00410041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource188, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_445EBC, (unsigned int)g_earlierMenuPaged_445E70, 0x00000000 },
    { 0x0000, 0x0000, 0x00410041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource189, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_445FB4, (unsigned int)g_earlierMenuPaged_445F60, 0x00000000 },
    { 0x0000, 0x0000, 0x00010201, 0x0000, 0x0013, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource190, (unsigned int)g_earlierMenuPaged_442F6C, 0x00000000, (unsigned int)g_earlierMenuPaged_4432AC, 0x00000000 },
};

struct MenuBuildDefinitionData g_earlierMenuDef_452194 = { (unsigned int)g_earlierMenuItems_451F30, 0x0011, 0x0000, (unsigned int)g_earlierMenuPaged_4452A4, 0x00000000, (unsigned int)g_earlierMenuPaged_4424EC, 0x00000000, 0x0010, 0x0000, 0x0000, 0x0000, 0x00000000 };

unsigned int g_earlierMenuWords_4521B8[2] = { 0x00000000, 0x00000000 };

struct MenuBuildItemData g_earlierMenuItems_4521C0[5] = {
    { 0x0001, 0x0000, 0x50000000, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x00000385, (unsigned int)g_earlierMenuPaged_4411C4, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x08000041, 0x0000, 0x0008, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource217, (unsigned int)g_earlierMenuPaged_442F6C, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00000101, 0x0000, 0x005D, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource258, (unsigned int)g_earlierMenuPaged_442F6C, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00010101, 0x0000, 0x000A, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource259, (unsigned int)g_earlierMenuPaged_442F6C, 0x00000000, (unsigned int)g_earlierMenuPaged_445FD0, 0x00000000 },
    { 0x0000, 0x0000, 0x00010101, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource260, (unsigned int)g_earlierMenuPaged_442F6C, 0x00000000, (unsigned int)g_earlierMenuPaged_4432AC, 0x00000000 },
};

struct MenuBuildDefinitionData g_earlierMenuDef_452274 = { (unsigned int)g_earlierMenuItems_4521C0, 0x0005, 0x0000, (unsigned int)g_earlierMenuPaged_446010, 0x00000000, (unsigned int)g_earlierMenuPaged_4424EC, 0x00000000, 0x0004, 0x0000, 0x0000, 0x0000, (int)&g_earlierMenuDef_452544 };

struct MenuBuildItemData g_earlierMenuItems_452298[7] = {
    { 0x0001, 0x0000, 0x50000000, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x00000385, (unsigned int)g_earlierMenuPaged_4411C4, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x08002001, 0x0000, 0x0008, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource298, (unsigned int)g_earlierMenuPaged_442F6C, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00410041, 0x0000, 0x0032, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource300, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_4463C0, (unsigned int)g_earlierMenuPaged_446350, 0x00000000 },
    { 0x0000, 0x0000, 0x00410041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource302, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_446524, (unsigned int)g_earlierMenuPaged_4464C4, 0x00000000 },
    { 0x0000, 0x0000, 0x00410041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource305, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_44624C, (unsigned int)g_earlierMenuPaged_4461EC, 0x00000000 },
    { 0x0000, 0x0000, 0x00410041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource306, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_4466CC, (unsigned int)g_earlierMenuPaged_446628, 0x00000000 },
    { 0x0000, 0x0000, 0x00410401, 0x0000, 0x0044, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource190, (unsigned int)g_earlierMenuPaged_442F6C, 0x00000000, (unsigned int)g_earlierMenuPaged_446164, 0x00000000 },
};

struct MenuBuildDefinitionData g_earlierMenuDef_452394 = { (unsigned int)g_earlierMenuItems_452298, 0x0007, 0x0000, 0x00000000, 0x00000000, (unsigned int)g_earlierMenuPaged_4424EC, 0x00000000, 0x0002, 0x0000, 0x0000, 0x0000, 0x00000000 };

struct MenuBuildItemData g_earlierMenuItems_4523B8[11] = {
    { 0x0001, 0x0000, 0x50000000, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x00000385, (unsigned int)g_earlierMenuPaged_4411C4, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x08000041, 0x0000, 0x0008, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource209, (unsigned int)g_earlierMenuPaged_442F6C, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0028, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource210, (unsigned int)g_earlierMenuPaged_442F6C, 0x00000000, (unsigned int)g_earlierMenuPaged_44601C, 0x00000000 },
    { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource211, (unsigned int)g_earlierMenuPaged_442F6C, 0x00000000, (unsigned int)g_earlierMenuPaged_446054, 0x00000000 },
    { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource212, (unsigned int)g_earlierMenuPaged_442F6C, 0x00000000, (unsigned int)g_earlierMenuPaged_44605C, 0x00000000 },
    { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource213, (unsigned int)g_earlierMenuPaged_442F6C, 0x00000000, (unsigned int)g_earlierMenuPaged_446088, 0x00000000 },
    { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource215, (unsigned int)g_earlierMenuPaged_442F6C, 0x00000000, (unsigned int)g_earlierMenuPaged_4460B4, 0x00000000 },
    { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource298, (unsigned int)g_earlierMenuPaged_442F6C, 0x00000000, (unsigned int)g_earlierMenuPaged_44674C, 0x00000000 },
    { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource262, (unsigned int)g_earlierMenuPaged_442F6C, 0x00000000, (unsigned int)g_earlierMenuPaged_4460E0, 0x00000000 },
    { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource216, (unsigned int)g_earlierMenuPaged_442F6C, 0x00000000, (unsigned int)g_earlierMenuPaged_44610C, 0x00000000 },
    { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource217, (unsigned int)g_earlierMenuPaged_442F6C, 0x00000000, (unsigned int)g_earlierMenuPaged_446138, 0x00000000 },
};

struct MenuBuildDefinitionData g_earlierMenuDef_452544 = { (unsigned int)g_earlierMenuItems_4523B8, 0x000B, 0x0000, (unsigned int)g_earlierMenuPaged_446854, (unsigned int)g_earlierMenuPaged_4468E4, (unsigned int)g_earlierMenuPaged_446900, 0x00000000, 0x0002, 0x0000, 0x0000, 0x0000, 0x00000000 };

unsigned int g_earlierMenuWords_452568[2] = { 0x00000000, 0x10E00001 };

struct MenuBuildItemData g_earlierMenuItems_452570[45] = {
    { 0x0000, 0x0000, 0x00000041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource255, (unsigned int)g_earlierMenuPaged_442F6C, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00210101, 0x0000, 0x0008, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource398, (unsigned int)g_earlierMenuPaged_446E24, (unsigned int)g_earlierMenuPaged_446BB4, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00210101, 0x0000, 0x0008, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource399, (unsigned int)g_earlierMenuPaged_446E24, (unsigned int)g_earlierMenuPaged_446BB4, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00210101, 0x0000, 0x0008, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource400, (unsigned int)g_earlierMenuPaged_446E24, (unsigned int)g_earlierMenuPaged_446BB4, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00210101, 0x0000, 0x0008, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource401, (unsigned int)g_earlierMenuPaged_446E24, (unsigned int)g_earlierMenuPaged_446BB4, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00010110, 0x0000, 0x000A, 0x07, 0x01, 0x20, 0x08, (int)g_earlierMenuResource318, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_446D04, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0x20, 0x08, (int)g_earlierMenuResource320, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_446D04, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0x20, 0x08, (int)g_earlierMenuResource322, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_446D04, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0x20, 0x08, (int)g_earlierMenuResource324, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_446D04, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0x20, 0x08, (int)g_earlierMenuResource326, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_446D04, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0x20, 0x08, (int)g_earlierMenuResource328, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_446D04, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0x20, 0x08, (int)g_earlierMenuResource330, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_446D04, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0xF9, 0x20, 0x08, (int)g_earlierMenuResource332, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_446D04, 0x00000000 },
    { 0x0000, 0x0000, 0x00010110, 0x0000, 0x0004, 0x07, 0x01, 0xF8, 0x08, (int)g_earlierMenuResource334, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_446D04, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0xF8, 0x08, (int)g_earlierMenuResource336, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_446D04, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0xF8, 0x08, (int)g_earlierMenuResource338, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_446D04, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0xF8, 0x08, (int)g_earlierMenuResource340, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_446D04, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0xF8, 0x08, (int)g_earlierMenuResource342, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_446D04, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0xF8, 0x08, (int)g_earlierMenuResource344, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_446D04, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0xF8, 0x08, (int)g_earlierMenuResource346, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_446D04, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0xF9, 0xF8, 0x08, (int)g_earlierMenuResource348, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_446D04, 0x00000000 },
    { 0x0000, 0x0000, 0x00010110, 0x0000, 0x0004, 0x07, 0x01, 0xF8, 0x08, (int)g_earlierMenuResource350, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_446D04, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0xF8, 0x08, (int)g_earlierMenuResource352, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_446D04, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0xF8, 0x08, (int)g_earlierMenuResource354, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_446D04, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0xF8, 0x08, (int)g_earlierMenuResource356, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_446D04, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0xF8, 0x08, (int)g_earlierMenuResource358, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_446D04, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0xF8, 0x08, (int)g_earlierMenuResource360, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_446D04, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0xF8, 0x08, (int)g_earlierMenuResource362, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_446D04, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0xF9, 0xF8, 0x08, (int)g_earlierMenuResource364, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_446D04, 0x00000000 },
    { 0x0000, 0x0000, 0x00010110, 0x0000, 0x0004, 0x07, 0x01, 0xF8, 0x08, (int)g_earlierMenuResource366, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_446D04, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0xF8, 0x08, (int)g_earlierMenuResource368, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_446D04, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0xF8, 0x08, (int)g_earlierMenuResource370, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_446D04, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0xF8, 0x08, (int)g_earlierMenuResource372, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_446D04, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0xF8, 0x08, (int)g_earlierMenuResource374, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_446D04, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0xF8, 0x08, (int)g_earlierMenuResource376, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_446D04, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0xF8, 0x08, (int)g_earlierMenuResource378, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_446D04, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0xF9, 0xF8, 0x08, (int)g_earlierMenuResource380, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_446D04, 0x00000000 },
    { 0x0000, 0x0000, 0x00010110, 0x0000, 0x0004, 0x07, 0x01, 0xF8, 0xE0, (int)g_earlierMenuResource382, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_446D04, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0xF8, 0xE0, (int)g_earlierMenuResource384, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_446D04, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0xF8, 0xE0, (int)g_earlierMenuResource386, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_446D04, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0xF8, 0xE0, (int)g_earlierMenuResource388, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_446D04, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0xF8, 0xE0, (int)g_earlierMenuResource308, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_446D04, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0xF8, 0xE0, (int)g_earlierMenuResource390, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_446D04, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0xF8, 0xE0, (int)g_earlierMenuResource391, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_446FD0, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0xF9, 0xF8, 0xE0, (int)g_earlierMenuResource392, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_447068, 0x00000000 },
};

struct MenuBuildDefinitionData g_earlierMenuDef_452BC4 = { (unsigned int)g_earlierMenuItems_452570, 0x002D, 0x0000, (unsigned int)g_earlierMenuPaged_446920, 0x00000000, (unsigned int)g_earlierMenuPaged_4424EC, (unsigned int)g_earlierMenuPaged_447158, 0x0005, 0x0000, 0x0000, 0x0000, 0x00000000 };

unsigned int g_earlierMenuWords_452BE8[3] = { 0x00000000, 0x00000000, 0x00000000 };

struct MenuBuildItemData g_earlierMenuItems_452BF4[11] = {
    { 0x0000, 0x0000, 0x00000401, 0x0000, 0x0028, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource281, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_444430, 0x00000000, 0x00000000 },
    { 0x0001, 0x0000, 0x20010001, 0x0000, 0x0000, 0x00, 0x00, 0x00, 0x01, 0x0000012D, (unsigned int)g_earlierMenuPaged_444778, 0x00000000, (unsigned int)g_earlierMenuPaged_444754, 0x00000000 },
    { 0x0001, 0x0000, 0x50000000, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x00000385, (unsigned int)g_earlierMenuPaged_4411C4, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00000401, 0x0000, 0x0028, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource283, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_444430, 0x00000000, 0x00000000 },
    { 0x0001, 0x0000, 0x20010001, -20, 0x0000, 0xEC, 0x00, 0x00, 0x01, 0x0000012D, (unsigned int)g_earlierMenuPaged_444778, 0x00000000, (unsigned int)g_earlierMenuPaged_444754, 0x00000000 },
    { 0x0001, 0x0000, 0x50000000, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x00000385, (unsigned int)g_earlierMenuPaged_4411C4, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00000401, 0x0000, 0x0028, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource285, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_444430, 0x00000000, 0x00000000 },
    { 0x0001, 0x0000, 0x20010001, 0x0000, 0x0000, 0x00, 0x00, 0x00, 0x01, 0x0000012D, (unsigned int)g_earlierMenuPaged_444778, 0x00000000, (unsigned int)g_earlierMenuPaged_444754, 0x00000000 },
    { 0x0001, 0x0000, 0x50000000, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x00000385, (unsigned int)g_earlierMenuPaged_4411C4, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00000401, 0x0000, 0x0028, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource287, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_444430, 0x00000000, 0x00000000 },
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
    { 0x0000, 0x0000, 0x08000021, 0x0000, 0x0008, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource295, (unsigned int)g_earlierMenuPaged_442F6C, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00400041, 0x0000, 0x002A, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource166, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_4453D4, (unsigned int)g_earlierMenuPaged_4452DC, 0x00000000 },
    { 0x0000, 0x0000, 0x00410041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource167, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_4454E4, (unsigned int)g_earlierMenuPaged_445480, 0x00000000 },
    { 0x0000, 0x0000, 0x00410041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource168, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_4455AC, (unsigned int)g_earlierMenuPaged_445548, 0x00000000 },
    { 0x0000, 0x0000, 0x00410041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource169, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_44566C, (unsigned int)g_earlierMenuPaged_445608, 0x00000000 },
    { 0x0000, 0x0000, 0x00410041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource171, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_445734, (unsigned int)g_earlierMenuPaged_4456D0, 0x00000000 },
    { 0x0000, 0x0000, 0x00410041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource172, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_4457EC, (unsigned int)g_earlierMenuPaged_445798, 0x00000000 },
    { 0x0000, 0x0000, 0x00410041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource174, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_4458B0, (unsigned int)g_earlierMenuPaged_445860, 0x00000000 },
    { 0x0000, 0x0000, 0x00410041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource176, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_44594C, (unsigned int)g_earlierMenuPaged_4459F0, 0x00000000 },
    { 0x0000, 0x0000, 0x00410041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource177, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_445ABC, (unsigned int)g_earlierMenuPaged_445A58, 0x00000000 },
    { 0x0000, 0x0000, 0x00410041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource179, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_445C14, (unsigned int)g_earlierMenuPaged_445BB0, 0x00000000 },
    { 0x0000, 0x0000, 0x00410041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource181, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_445D08, (unsigned int)g_earlierMenuPaged_445D54, 0x00000000 },
    { 0x0000, 0x0000, 0x00410041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource182, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_445D88, (unsigned int)g_earlierMenuPaged_445E18, 0x00000000 },
    { 0x0000, 0x0000, 0x00410041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource185, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_445EBC, (unsigned int)g_earlierMenuPaged_445E70, 0x00000000 },
    { 0x0000, 0x0000, 0x00410041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource186, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_445FB4, (unsigned int)g_earlierMenuPaged_445F60, 0x00000000 },
    { 0x0000, 0x0000, 0x00010201, 0x0000, 0x0013, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource187, (unsigned int)g_earlierMenuPaged_442F6C, 0x00000000, (unsigned int)g_earlierMenuPaged_4432AC, 0x00000000 },
};

struct MenuBuildDefinitionData g_earlierMenuDef_453194 = { (unsigned int)g_earlierMenuItems_451F30, 0x0011, 0x0000, (unsigned int)g_earlierMenuPaged_4452A4, 0x00000000, (unsigned int)g_earlierMenuPaged_4424EC, 0x00000000, 0x0010, 0x0000, 0x0000, 0x0000, 0x00000000 };

unsigned int g_earlierMenuWords_4531B8[2] = { 0x6D5F7041, 0x6D6D6F49 };

struct MenuBuildItemData g_earlierMenuItems_4531C0[5] = {
    { 0x0001, 0x0000, 0x50000000, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x00000385, (unsigned int)g_earlierMenuPaged_4411C4, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x08000041, 0x0000, 0x0008, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource214, (unsigned int)g_earlierMenuPaged_442F6C, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00000101, 0x0000, 0x005D, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource256, (unsigned int)g_earlierMenuPaged_442F6C, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00010101, 0x0000, 0x000A, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource257, (unsigned int)g_earlierMenuPaged_442F6C, 0x00000000, (unsigned int)g_earlierMenuPaged_445FD0, 0x00000000 },
    { 0x0000, 0x0000, 0x00010101, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource258, (unsigned int)g_earlierMenuPaged_442F6C, 0x00000000, (unsigned int)g_earlierMenuPaged_4432AC, 0x00000000 },
};

struct MenuBuildDefinitionData g_earlierMenuDef_453274 = { (unsigned int)g_earlierMenuItems_4521C0, 0x0005, 0x0000, (unsigned int)g_earlierMenuPaged_446010, 0x00000000, (unsigned int)g_earlierMenuPaged_4424EC, 0x00000000, 0x0004, 0x0000, 0x0000, 0x0000, (int)&g_earlierMenuDef_452544 };

struct MenuBuildItemData g_earlierMenuItems_453298[7] = {
    { 0x0001, 0x0000, 0x50000000, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x00000385, (unsigned int)g_earlierMenuPaged_4411C4, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x08002001, 0x0000, 0x0008, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource297, (unsigned int)g_earlierMenuPaged_442F6C, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00410041, 0x0000, 0x0032, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource299, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_4463C0, (unsigned int)g_earlierMenuPaged_446350, 0x00000000 },
    { 0x0000, 0x0000, 0x00410041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource301, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_446524, (unsigned int)g_earlierMenuPaged_4464C4, 0x00000000 },
    { 0x0000, 0x0000, 0x00410041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource303, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_44624C, (unsigned int)g_earlierMenuPaged_4461EC, 0x00000000 },
    { 0x0000, 0x0000, 0x00410041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource304, (unsigned int)g_earlierMenuPaged_442F6C, (unsigned int)g_earlierMenuPaged_4466CC, (unsigned int)g_earlierMenuPaged_446628, 0x00000000 },
    { 0x0000, 0x0000, 0x00410401, 0x0000, 0x0044, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource187, (unsigned int)g_earlierMenuPaged_442F6C, 0x00000000, (unsigned int)g_earlierMenuPaged_446164, 0x00000000 },
};

struct MenuBuildDefinitionData g_earlierMenuDef_453394 = { (unsigned int)g_earlierMenuItems_452298, 0x0007, 0x0000, 0x00000000, 0x00000000, (unsigned int)g_earlierMenuPaged_4424EC, 0x00000000, 0x0002, 0x0000, 0x0000, 0x0000, 0x00000000 };

struct MenuBuildItemData g_earlierMenuItems_4533B8[11] = {
    { 0x0001, 0x0000, 0x50000000, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x00000385, (unsigned int)g_earlierMenuPaged_4411C4, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x08000041, 0x0000, 0x0008, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource206, (unsigned int)g_earlierMenuPaged_442F6C, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0028, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource207, (unsigned int)g_earlierMenuPaged_442F6C, 0x00000000, (unsigned int)g_earlierMenuPaged_44601C, 0x00000000 },
    { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource208, (unsigned int)g_earlierMenuPaged_442F6C, 0x00000000, (unsigned int)g_earlierMenuPaged_446054, 0x00000000 },
    { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource209, (unsigned int)g_earlierMenuPaged_442F6C, 0x00000000, (unsigned int)g_earlierMenuPaged_44605C, 0x00000000 },
    { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource210, (unsigned int)g_earlierMenuPaged_442F6C, 0x00000000, (unsigned int)g_earlierMenuPaged_446088, 0x00000000 },
    { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource212, (unsigned int)g_earlierMenuPaged_442F6C, 0x00000000, (unsigned int)g_earlierMenuPaged_4460B4, 0x00000000 },
    { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource297, (unsigned int)g_earlierMenuPaged_442F6C, 0x00000000, (unsigned int)g_earlierMenuPaged_44674C, 0x00000000 },
    { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource261, (unsigned int)g_earlierMenuPaged_442F6C, 0x00000000, (unsigned int)g_earlierMenuPaged_4460E0, 0x00000000 },
    { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource213, (unsigned int)g_earlierMenuPaged_442F6C, 0x00000000, (unsigned int)g_earlierMenuPaged_44610C, 0x00000000 },
    { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource214, (unsigned int)g_earlierMenuPaged_442F6C, 0x00000000, (unsigned int)g_earlierMenuPaged_446138, 0x00000000 },
};

struct MenuBuildDefinitionData g_earlierMenuDef_453544 = { (unsigned int)g_earlierMenuItems_4523B8, 0x000B, 0x0000, (unsigned int)g_earlierMenuPaged_446854, (unsigned int)g_earlierMenuPaged_4468E4, (unsigned int)g_earlierMenuPaged_446900, 0x00000000, 0x0002, 0x0000, 0x0000, 0x0000, 0x00000000 };

float g_earlierMenuFloats_453568[2] = { 3.1415927f, 1.5707964f };

struct MenuBuildItemData g_earlierMenuItems_453570[45] = {
    { 0x0000, 0x0000, 0x00000041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource254, (unsigned int)g_earlierMenuPaged_442F6C, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00210101, 0x0000, 0x0008, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource395, (unsigned int)g_earlierMenuPaged_446E24, (unsigned int)g_earlierMenuPaged_446BB4, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00210101, 0x0000, 0x0008, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource396, (unsigned int)g_earlierMenuPaged_446E24, (unsigned int)g_earlierMenuPaged_446BB4, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00210101, 0x0000, 0x0008, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource397, (unsigned int)g_earlierMenuPaged_446E24, (unsigned int)g_earlierMenuPaged_446BB4, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00210101, 0x0000, 0x0008, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource398, (unsigned int)g_earlierMenuPaged_446E24, (unsigned int)g_earlierMenuPaged_446BB4, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00010110, 0x0000, 0x000A, 0x07, 0x01, 0x20, 0x08, (int)g_earlierMenuResource315, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_446D04, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0x20, 0x08, (int)g_earlierMenuResource316, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_446D04, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0x20, 0x08, (int)g_earlierMenuResource317, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_446D04, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0x20, 0x08, (int)g_earlierMenuResource319, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_446D04, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0x20, 0x08, (int)g_earlierMenuResource321, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_446D04, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0x20, 0x08, (int)g_earlierMenuResource323, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_446D04, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0x20, 0x08, (int)g_earlierMenuResource325, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_446D04, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0xF9, 0x20, 0x08, (int)g_earlierMenuResource327, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_446D04, 0x00000000 },
    { 0x0000, 0x0000, 0x00010110, 0x0000, 0x0004, 0x07, 0x01, 0xF8, 0x08, (int)g_earlierMenuResource329, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_446D04, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0xF8, 0x08, (int)g_earlierMenuResource331, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_446D04, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0xF8, 0x08, (int)g_earlierMenuResource333, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_446D04, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0xF8, 0x08, (int)g_earlierMenuResource335, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_446D04, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0xF8, 0x08, (int)g_earlierMenuResource337, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_446D04, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0xF8, 0x08, (int)g_earlierMenuResource339, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_446D04, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0xF8, 0x08, (int)g_earlierMenuResource341, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_446D04, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0xF9, 0xF8, 0x08, (int)g_earlierMenuResource343, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_446D04, 0x00000000 },
    { 0x0000, 0x0000, 0x00010110, 0x0000, 0x0004, 0x07, 0x01, 0xF8, 0x08, (int)g_earlierMenuResource345, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_446D04, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0xF8, 0x08, (int)g_earlierMenuResource347, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_446D04, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0xF8, 0x08, (int)g_earlierMenuResource349, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_446D04, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0xF8, 0x08, (int)g_earlierMenuResource351, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_446D04, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0xF8, 0x08, (int)g_earlierMenuResource353, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_446D04, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0xF8, 0x08, (int)g_earlierMenuResource355, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_446D04, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0xF8, 0x08, (int)g_earlierMenuResource357, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_446D04, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0xF9, 0xF8, 0x08, (int)g_earlierMenuResource359, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_446D04, 0x00000000 },
    { 0x0000, 0x0000, 0x00010110, 0x0000, 0x0004, 0x07, 0x01, 0xF8, 0x08, (int)g_earlierMenuResource361, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_446D04, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0xF8, 0x08, (int)g_earlierMenuResource363, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_446D04, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0xF8, 0x08, (int)g_earlierMenuResource365, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_446D04, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0xF8, 0x08, (int)g_earlierMenuResource367, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_446D04, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0xF8, 0x08, (int)g_earlierMenuResource369, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_446D04, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0xF8, 0x08, (int)g_earlierMenuResource371, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_446D04, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0xF8, 0x08, (int)g_earlierMenuResource373, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_446D04, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0xF9, 0xF8, 0x08, (int)g_earlierMenuResource375, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_446D04, 0x00000000 },
    { 0x0000, 0x0000, 0x00010110, 0x0000, 0x0004, 0x07, 0x01, 0xF8, 0xE0, (int)g_earlierMenuResource377, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_446D04, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0xF8, 0xE0, (int)g_earlierMenuResource379, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_446D04, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0xF8, 0xE0, (int)g_earlierMenuResource381, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_446D04, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0xF8, 0xE0, (int)g_earlierMenuResource383, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_446D04, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0xF8, 0xE0, (int)g_earlierMenuResource307, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_446D04, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0xF8, 0xE0, (int)g_earlierMenuResource385, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_446D04, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0xF8, 0xE0, (int)g_earlierMenuResource387, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_446FD0, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0xF9, 0xF8, 0xE0, (int)g_earlierMenuResource389, (unsigned int)g_earlierMenuPaged_442FA4, 0x00000000, (unsigned int)g_earlierMenuPaged_447068, 0x00000000 },
};

struct MenuBuildDefinitionData g_earlierMenuDef_453BC4 = { (unsigned int)g_earlierMenuItems_452570, 0x002D, 0x0000, (unsigned int)g_earlierMenuPaged_446920, 0x00000000, (unsigned int)g_earlierMenuPaged_4424EC, (unsigned int)g_earlierMenuPaged_447158, 0x0005, 0x0000, 0x0000, 0x0000, 0x00000000 };

#endif
