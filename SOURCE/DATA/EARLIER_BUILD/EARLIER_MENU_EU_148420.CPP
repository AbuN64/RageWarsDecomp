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

extern char g_earlierMenuPaged2[];
extern char g_earlierMenuPaged4[];
extern char g_earlierMenuPaged6[];
extern char g_earlierMenuPaged8[];
extern char g_earlierMenuPaged10[];
extern char g_earlierMenuPaged12[];
extern char g_earlierMenuPaged14[];
extern char g_earlierMenuPaged16[];
extern char g_earlierMenuPaged18[];
extern char g_earlierMenuPaged20[];
extern char g_earlierMenuPaged22[];
extern char g_earlierMenuPaged25[];
extern char g_earlierMenuPaged27[];
extern char g_earlierMenuPaged28[];
extern char g_earlierMenuPaged30[];
extern char g_earlierMenuPaged32[];
extern char g_earlierMenuPaged36[];
extern char g_earlierMenuPaged37[];
extern char g_earlierMenuPaged38[];
extern char g_earlierMenuPaged48[];
extern char g_earlierMenuPaged52[];
extern char g_earlierMenuPaged53[];
extern char g_earlierMenuPaged58[];
extern char g_earlierMenuPaged59[];
extern char g_earlierMenuPaged60[];
extern char g_earlierMenuPaged61[];
extern char g_earlierMenuPaged62[];
extern char g_earlierMenuPaged64[];
extern char g_earlierMenuPaged65[];
extern char g_earlierMenuPaged67[];
extern char g_earlierMenuPaged68[];
extern char g_earlierMenuPaged71[];
extern char g_earlierMenuPaged72[];
extern char g_earlierMenuPaged74[];
extern char g_earlierMenuPaged76[];
extern char g_earlierMenuPaged78[];
extern char g_earlierMenuPaged82[];
extern char g_earlierMenuPaged86[];
extern char g_earlierMenuPaged96[];
extern char g_earlierMenuPaged98[];
extern char g_earlierMenuPaged100[];
extern char g_earlierMenuPaged101[];
extern char g_earlierMenuPaged102[];
extern char g_earlierMenuPaged103[];
extern char g_earlierMenuPaged104[];
extern char g_earlierMenuPaged105[];
extern char g_earlierMenuPaged106[];
extern char g_earlierMenuPaged107[];
extern char g_earlierMenuPaged108[];
extern char g_earlierMenuPaged109[];
extern char g_earlierMenuPaged110[];
extern char g_earlierMenuPaged111[];
extern char g_earlierMenuPaged112[];
extern char g_earlierMenuPaged113[];
extern char g_earlierMenuPaged114[];
extern char g_earlierMenuPaged116[];
extern char g_earlierMenuPaged117[];
extern char g_earlierMenuPaged118[];
extern char g_earlierMenuPaged119[];
extern char g_earlierMenuPaged120[];
extern char g_earlierMenuPaged121[];
extern char g_earlierMenuPaged123[];
extern char g_earlierMenuPaged126[];
extern char g_earlierMenuPaged132[];
extern char g_earlierMenuPaged134[];
extern char g_earlierMenuPaged137[];
extern char g_earlierMenuPaged139[];
extern char g_earlierMenuPaged141[];
extern char g_earlierMenuPaged143[];
extern char g_earlierMenuPaged145[];
extern char g_earlierMenuPaged148[];
extern char g_earlierMenuPaged151[];
extern char g_earlierMenuPaged153[];
extern char g_earlierMenuPaged155[];
extern char g_earlierMenuPaged158[];
extern char g_earlierMenuPaged160[];
extern char g_earlierMenuPaged161[];
extern char g_earlierMenuPaged162[];
extern char g_earlierMenuPaged163[];
extern char g_earlierMenuPaged164[];
extern char g_earlierMenuPaged165[];
extern char g_earlierMenuPaged166[];
extern char g_earlierMenuPaged167[];
extern char g_earlierMenuPaged168[];
extern char g_earlierMenuPaged169[];
extern char g_earlierMenuPaged170[];
extern char g_earlierMenuPaged171[];
extern char g_earlierMenuPaged172[];
extern char g_earlierMenuPaged173[];
extern char g_earlierMenuPaged193[];
extern char g_earlierMenuPaged199[];
extern char g_earlierMenuPaged210[];
extern char g_earlierMenuPaged212[];
extern char g_earlierMenuPaged218[];
extern char g_earlierMenuPaged223[];
extern char g_earlierMenuPaged224[];
extern char g_earlierMenuPaged226[];
extern char g_earlierMenuPaged228[];
extern char g_earlierMenuPaged229[];
extern char g_earlierMenuPaged230[];
extern char g_earlierMenuPaged231[];
extern char g_earlierMenuPaged232[];
extern char g_earlierMenuPaged235[];
extern char g_earlierMenuPaged236[];
extern char g_earlierMenuPaged239[];
extern char g_earlierMenuPaged240[];
extern char g_earlierMenuPaged242[];
extern char g_earlierMenuPaged243[];
extern char g_earlierMenuPaged244[];
extern char g_earlierMenuPaged245[];
extern char g_earlierMenuPaged248[];
extern char g_earlierMenuPaged250[];
extern char g_earlierMenuPaged253[];
extern char g_earlierMenuPaged254[];
extern char g_earlierMenuPaged258[];
extern char g_earlierMenuPaged259[];
extern char g_earlierMenuPaged262[];
extern char g_earlierMenuPaged265[];
extern char g_earlierMenuPaged267[];
extern char g_earlierMenuPaged269[];
extern char g_earlierMenuPaged270[];
extern char g_earlierMenuPaged271[];
extern char g_earlierMenuPaged272[];
extern char g_earlierMenuPaged273[];
extern char g_earlierMenuPaged274[];
extern char g_earlierMenuPaged275[];
extern char g_earlierMenuPaged277[];
extern char g_earlierMenuPaged278[];
extern char g_earlierMenuPaged279[];
extern char g_earlierMenuPaged280[];
extern char g_earlierMenuPaged284[];
extern char g_earlierMenuPaged285[];
extern char g_earlierMenuPaged288[];
extern char g_earlierMenuPaged289[];
extern char g_earlierMenuPaged291[];
extern char g_earlierMenuPaged303[];
extern char g_earlierMenuPaged304[];
extern char g_earlierMenuPaged305[];
extern char g_earlierMenuPaged307[];
extern char g_earlierMenuPaged308[];
extern char g_earlierMenuPaged310[];
extern char g_earlierMenuPaged311[];
extern char g_earlierMenuPaged312[];
extern char g_earlierMenuPaged313[];
extern char g_earlierMenuPaged314[];
extern char g_earlierMenuPaged315[];
extern char g_earlierMenuPaged316[];
extern char g_earlierMenuPaged317[];
extern char g_earlierMenuPaged318[];
extern char g_earlierMenuPaged319[];
extern char g_earlierMenuPaged320[];
extern char g_earlierMenuPaged321[];
extern char g_earlierMenuPaged322[];
extern char g_earlierMenuPaged323[];
extern char g_earlierMenuPaged324[];
extern char g_earlierMenuPaged325[];
extern char g_earlierMenuPaged326[];
extern char g_earlierMenuPaged327[];
extern char g_earlierMenuPaged328[];
extern char g_earlierMenuPaged329[];
extern char g_earlierMenuPaged330[];
extern char g_earlierMenuPaged331[];
extern char g_earlierMenuPaged332[];
extern char g_earlierMenuPaged333[];
extern char g_earlierMenuPaged334[];
extern char g_earlierMenuPaged335[];
extern char g_earlierMenuPaged336[];
extern char g_earlierMenuPaged337[];
extern char g_earlierMenuPaged338[];
extern char g_earlierMenuPaged339[];
extern char g_earlierMenuPaged340[];
extern char g_earlierMenuPaged341[];
extern char g_earlierMenuPaged342[];
extern char g_earlierMenuPaged343[];
extern char g_earlierMenuPaged344[];
extern char g_earlierMenuPaged347[];
extern char g_earlierMenuPaged349[];
extern char g_earlierMenuPaged353[];
extern char g_earlierMenuPaged354[];
extern char g_earlierMenuPaged355[];
extern char g_earlierMenuPaged356[];
extern char g_earlierMenuPaged369[];
extern char g_earlierMenuPaged370[];
extern char g_earlierMenuPaged373[];
extern char g_earlierMenuPaged380[];
extern char g_earlierMenuPaged382[];
extern char g_earlierMenuPaged386[];
extern char g_earlierMenuPaged394[];
extern char g_earlierMenuPaged397[];
extern char g_earlierMenuPaged402[];
extern char g_earlierMenuPaged415[];
extern char g_earlierMenuPaged417[];
extern char g_earlierMenuPaged419[];
extern char g_earlierMenuPaged421[];
extern char g_earlierMenuPaged423[];
extern char g_earlierMenuPaged424[];
extern char g_earlierMenuPaged425[];
extern char g_earlierMenuPaged427[];
extern char g_earlierMenuPaged429[];
extern char g_earlierMenuPaged432[];
extern char g_earlierMenuPaged433[];
extern char g_earlierMenuPaged434[];
extern char g_earlierMenuPaged435[];
extern char g_earlierMenuPaged436[];
extern char g_earlierMenuPaged437[];
extern char g_earlierMenuPaged439[];
extern char g_earlierMenuPaged440[];
extern char g_earlierMenuPaged441[];
extern char g_earlierMenuPaged443[];
extern char g_earlierMenuPaged445[];
extern char g_earlierMenuPaged446[];
extern char g_earlierMenuPaged447[];
extern char g_earlierMenuPaged449[];
extern char g_earlierMenuPaged450[];
extern char g_earlierMenuPaged452[];
extern char g_earlierMenuPaged453[];
extern char g_earlierMenuPaged455[];
extern char g_earlierMenuPaged456[];
extern char g_earlierMenuPaged457[];
extern char g_earlierMenuPaged458[];
extern char g_earlierMenuPaged459[];
extern char g_earlierMenuPaged460[];
extern char g_earlierMenuPaged461[];
extern char g_earlierMenuPaged462[];
extern char g_earlierMenuPaged463[];
extern char g_earlierMenuPaged464[];
extern char g_earlierMenuPaged465[];
extern char g_earlierMenuPaged466[];
extern char g_earlierMenuPaged467[];
extern char g_earlierMenuPaged468[];
extern char g_earlierMenuPaged469[];
extern char g_earlierMenuPaged470[];
extern char g_earlierMenuPaged471[];
extern char g_earlierMenuPaged472[];
extern char g_earlierMenuPaged473[];
extern char g_earlierMenuPaged474[];
extern char g_earlierMenuPaged475[];
extern char g_earlierMenuPaged476[];
extern char g_earlierMenuPaged477[];
extern char g_earlierMenuPaged478[];
extern char g_earlierMenuPaged479[];
extern char g_earlierMenuPaged480[];
extern char g_earlierMenuPaged481[];
extern char g_earlierMenuPaged482[];
extern char g_earlierMenuPaged483[];
extern char g_earlierMenuPaged484[];
extern char g_earlierMenuPaged485[];
extern char g_earlierMenuPaged486[];
extern char g_earlierMenuPaged487[];
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
extern struct MenuBuildItemData g_earlierMenuItems8[22];
extern struct MenuBuildItemData g_earlierMenuItems11[10];
extern struct MenuBuildItemData g_earlierMenuItems14[9];
extern struct MenuBuildItemData g_earlierMenuItems17[8];
extern struct MenuBuildItemData g_earlierMenuItems21[8];
extern struct MenuBuildItemData g_earlierMenuItems24[8];
extern struct MenuBuildItemData g_earlierMenuItems27[33];
extern struct MenuBuildItemData g_earlierMenuItems28[20];
extern struct MenuBuildItemData g_earlierMenuItems34[3];
extern struct MenuBuildItemData g_earlierMenuItems35[8];
extern struct MenuBuildItemData g_earlierMenuItems37[5];
extern struct MenuBuildDefinitionData g_earlierMenuDef101;
extern struct EarlierMenuTuning g_earlierMenuTuning2;
extern struct MenuBuildItemData g_earlierMenuItems38[3];
extern struct MenuBuildDefinitionData g_earlierMenuDef102;
extern struct MenuBuildItemData g_earlierMenuItems39[4];
extern struct MenuBuildItemData g_earlierMenuItems41[11];
extern struct MenuBuildItemData g_earlierMenuItems44[4];
extern struct MenuBuildDefinitionData g_earlierMenuDef109;
extern struct MenuBuildItemData g_earlierMenuItems45[5];
extern struct MenuBuildItemData g_earlierMenuItems47[1];
extern struct MenuBuildItemData g_earlierMenuItems48[7];
extern struct MenuBuildDefinitionData g_earlierMenuDef114;
extern struct MenuBuildItemData g_earlierMenuItems49[2];
extern struct MenuBuildItemData g_earlierMenuItems50[49];
extern struct MenuBuildItemData g_earlierMenuItems51[1];
extern struct MenuBuildItemData g_earlierMenuItems52[3];
extern struct MenuBuildItemData g_earlierMenuItems53[3];
extern struct MenuBuildItemData g_earlierMenuItems54[3];
extern struct MenuBuildItemData g_earlierMenuItems55[3];
extern struct MenuBuildItemData g_earlierMenuItems56[17];
extern struct MenuBuildDefinitionData g_earlierMenuDef132;
extern struct MenuBuildItemData g_earlierMenuItems57[5];
extern struct MenuBuildItemData g_earlierMenuItems58[7];
extern struct MenuBuildItemData g_earlierMenuItems59[11];
extern struct MenuBuildDefinitionData g_earlierMenuDef135;
extern struct MenuBuildItemData g_earlierMenuItems60[45];

struct MenuBuildItemData g_earlierMenuItems8[22] = {
    { 0x0001, 0x0000, 0x90000000, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x00000385, (unsigned int)g_earlierMenuPaged347, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x08000041, 0x0000, 0x000A, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource220, (unsigned int)g_earlierMenuPaged354, (unsigned int)g_earlierMenuPaged52, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00010041, 0x0000, -8, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource237, (unsigned int)g_earlierMenuPaged354, (unsigned int)g_earlierMenuPaged53, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00011001, 0x0000, 0x0006, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource221, (unsigned int)g_earlierMenuPaged354, (unsigned int)g_earlierMenuPaged14, (unsigned int)g_earlierMenuPaged12, 0x00000000 },
    { 0x0000, 0x0000, 0x00011001, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource222, (unsigned int)g_earlierMenuPaged354, (unsigned int)g_earlierMenuPaged14, (unsigned int)g_earlierMenuPaged12, 0x00000000 },
    { 0x0000, 0x0000, 0x00011001, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource223, (unsigned int)g_earlierMenuPaged354, (unsigned int)g_earlierMenuPaged14, (unsigned int)g_earlierMenuPaged12, 0x00000000 },
    { 0x0000, 0x0000, 0x00011001, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource224, (unsigned int)g_earlierMenuPaged354, (unsigned int)g_earlierMenuPaged14, (unsigned int)g_earlierMenuPaged12, 0x00000000 },
    { 0x0000, 0x0000, 0x00011001, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource225, (unsigned int)g_earlierMenuPaged354, (unsigned int)g_earlierMenuPaged14, (unsigned int)g_earlierMenuPaged12, 0x00000000 },
    { 0x0000, 0x0000, 0x00011001, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource226, (unsigned int)g_earlierMenuPaged354, (unsigned int)g_earlierMenuPaged14, (unsigned int)g_earlierMenuPaged12, 0x00000000 },
    { 0x0000, 0x0000, 0x00011001, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource227, (unsigned int)g_earlierMenuPaged354, (unsigned int)g_earlierMenuPaged14, (unsigned int)g_earlierMenuPaged12, 0x00000000 },
    { 0x0000, 0x0000, 0x00011001, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource228, (unsigned int)g_earlierMenuPaged354, (unsigned int)g_earlierMenuPaged14, (unsigned int)g_earlierMenuPaged12, 0x00000000 },
    { 0x0000, 0x0000, 0x00011001, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource229, (unsigned int)g_earlierMenuPaged354, (unsigned int)g_earlierMenuPaged14, (unsigned int)g_earlierMenuPaged12, 0x00000000 },
    { 0x0000, 0x0000, 0x00011001, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource230, (unsigned int)g_earlierMenuPaged354, (unsigned int)g_earlierMenuPaged14, (unsigned int)g_earlierMenuPaged12, 0x00000000 },
    { 0x0000, 0x0000, 0x00011001, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource231, (unsigned int)g_earlierMenuPaged354, (unsigned int)g_earlierMenuPaged14, (unsigned int)g_earlierMenuPaged12, 0x00000000 },
    { 0x0000, 0x0000, 0x00011001, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource232, (unsigned int)g_earlierMenuPaged354, (unsigned int)g_earlierMenuPaged14, (unsigned int)g_earlierMenuPaged12, 0x00000000 },
    { 0x0000, 0x0000, 0x00011001, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource233, (unsigned int)g_earlierMenuPaged354, (unsigned int)g_earlierMenuPaged14, (unsigned int)g_earlierMenuPaged12, 0x00000000 },
    { 0x0000, 0x0000, 0x00011001, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource234, (unsigned int)g_earlierMenuPaged354, (unsigned int)g_earlierMenuPaged14, (unsigned int)g_earlierMenuPaged12, 0x00000000 },
    { 0x0000, 0x0000, 0x00011001, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource235, (unsigned int)g_earlierMenuPaged354, (unsigned int)g_earlierMenuPaged14, (unsigned int)g_earlierMenuPaged12, 0x00000000 },
    { 0x0000, 0x0000, 0x00011001, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource236, (unsigned int)g_earlierMenuPaged354, (unsigned int)g_earlierMenuPaged14, (unsigned int)g_earlierMenuPaged12, 0x00000000 },
    { 0x0000, 0x0000, 0x00011001, 0x0000, 0x0003, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource308, (unsigned int)g_earlierMenuPaged354, (unsigned int)g_earlierMenuPaged16, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00010041, 0x0000, 0x000A, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource308, (unsigned int)g_earlierMenuPaged354, (unsigned int)g_earlierMenuPaged48, (unsigned int)g_earlierMenuPaged18, 0x00000000 },
    { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0004, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource238, (unsigned int)g_earlierMenuPaged354, (unsigned int)g_earlierMenuPaged58, (unsigned int)g_earlierMenuPaged20, 0x00000000 },
};

struct MenuBuildDefinitionData g_earlierMenuDef36 = { (unsigned int)g_earlierMenuItems8, 0x0016, 0x0000, (unsigned int)g_earlierMenuPaged4, 0x00000000, (unsigned int)g_earlierMenuPaged353, (unsigned int)g_earlierMenuPaged36, 0x0015, 0x0000, 0x0000, 0x0000, 0x00000000 };

struct MenuBuildDefinitionData g_earlierMenuDef38 = { (unsigned int)g_earlierMenuItems8, 0x0016, 0x0000, (unsigned int)g_earlierMenuPaged2, 0x00000000, (unsigned int)g_earlierMenuPaged353, (unsigned int)g_earlierMenuPaged36, 0x0014, 0x0000, 0x0000, 0x0000, 0x00000000 };

struct MenuBuildDefinitionData g_earlierMenuDef39 = { (unsigned int)g_earlierMenuItems8, 0x0016, 0x0000, (unsigned int)g_earlierMenuPaged10, 0x00000000, (unsigned int)g_earlierMenuPaged353, (unsigned int)g_earlierMenuPaged37, 0x0015, 0x0000, 0x0000, 0x0000, 0x00000000 };

struct MenuBuildDefinitionData g_earlierMenuDef40 = { (unsigned int)g_earlierMenuItems8, 0x0016, 0x0000, (unsigned int)g_earlierMenuPaged8, 0x00000000, (unsigned int)g_earlierMenuPaged353, (unsigned int)g_earlierMenuPaged37, 0x0014, 0x0000, 0x0000, 0x0000, 0x00000000 };

struct MenuBuildDefinitionData g_earlierMenuDef41 = { (unsigned int)g_earlierMenuItems8, 0x0016, 0x0000, (unsigned int)g_earlierMenuPaged6, 0x00000000, (unsigned int)g_earlierMenuPaged353, (unsigned int)g_earlierMenuPaged38, 0x0014, 0x0000, 0x0000, 0x0000, 0x00000000 };

struct MenuBuildItemData g_earlierMenuItems11[10] = {
    { 0x0001, 0x0000, 0x90000000, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x00000385, (unsigned int)g_earlierMenuPaged347, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x08000801, 0x0000, 0x0008, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource239, (unsigned int)g_earlierMenuPaged354, (unsigned int)g_earlierMenuPaged61, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0014, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource308, (unsigned int)g_earlierMenuPaged354, (unsigned int)g_earlierMenuPaged67, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0005, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource242, (unsigned int)g_earlierMenuPaged354, (unsigned int)g_earlierMenuPaged68, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00010041, 0x0000, 0x000A, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource308, (unsigned int)g_earlierMenuPaged354, (unsigned int)g_earlierMenuPaged62, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource240, (unsigned int)g_earlierMenuPaged354, (unsigned int)g_earlierMenuPaged64, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource241, (unsigned int)g_earlierMenuPaged354, (unsigned int)g_earlierMenuPaged65, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0014, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource247, (unsigned int)g_earlierMenuPaged354, (unsigned int)g_earlierMenuPaged71, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00010040, 0x007D, 0x000A, 0x00, 0x01, 0x00, 0x00, (int)g_earlierMenuResource259, (unsigned int)g_earlierMenuPaged354, 0x00000000, (unsigned int)g_earlierMenuPaged22, 0x00000000 },
    { 0x0000, 0x0000, 0x00024040, 0x000A, 0x0000, 0xFF, 0x00, 0x00, 0x00, (int)g_earlierMenuResource260, (unsigned int)g_earlierMenuPaged354, 0x00000000, (unsigned int)g_earlierMenuPaged72, 0x00000000 },
};

struct MenuBuildDefinitionData g_earlierMenuDef43 = { (unsigned int)g_earlierMenuItems11, 0x000A, 0x0000, (unsigned int)g_earlierMenuPaged59, 0x00000000, (unsigned int)g_earlierMenuPaged353, 0x00000000, 0x0008, 0x0000, 0x0000, 0x0000, 0x00000000 };

struct MenuBuildDefinitionData g_earlierMenuDef44 = { (unsigned int)g_earlierMenuItems11, 0x000A, 0x0000, (unsigned int)g_earlierMenuPaged60, 0x00000000, (unsigned int)g_earlierMenuPaged353, 0x00000000, 0x0009, 0x0000, 0x0000, 0x0000, 0x00000000 };

struct MenuBuildItemData g_earlierMenuItems14[9] = {
    { 0x0001, 0x0000, 0x90000000, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x00000385, (unsigned int)g_earlierMenuPaged347, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x08000021, 0x0000, 0x0008, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource243, (unsigned int)g_earlierMenuPaged354, (unsigned int)g_earlierMenuPaged82, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0032, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource308, (unsigned int)g_earlierMenuPaged354, (unsigned int)g_earlierMenuPaged86, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0002, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource244, (unsigned int)g_earlierMenuPaged354, (unsigned int)g_earlierMenuPaged96, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0002, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource245, (unsigned int)g_earlierMenuPaged354, (unsigned int)g_earlierMenuPaged98, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0002, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource246, (unsigned int)g_earlierMenuPaged354, (unsigned int)g_earlierMenuPaged25, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0010, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource247, (unsigned int)g_earlierMenuPaged354, (unsigned int)g_earlierMenuPaged100, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00010040, 0x007D, 0x000A, 0x00, 0x01, 0x00, 0x00, (int)g_earlierMenuResource259, (unsigned int)g_earlierMenuPaged354, 0x00000000, (unsigned int)g_earlierMenuPaged27, 0x00000000 },
    { 0x0000, 0x0000, 0x00024040, 0x000A, 0x0000, 0xFF, 0x00, 0x00, 0x00, (int)g_earlierMenuResource260, (unsigned int)g_earlierMenuPaged354, 0x00000000, (unsigned int)g_earlierMenuPaged101, 0x00000000 },
};

struct MenuBuildDefinitionData g_earlierMenuDef46 = { (unsigned int)g_earlierMenuItems14, 0x0009, 0x0000, (unsigned int)g_earlierMenuPaged74, 0x00000000, (unsigned int)g_earlierMenuPaged353, 0x00000000, 0x0007, 0x0000, 0x0000, 0x0000, 0x00000000 };

struct MenuBuildDefinitionData g_earlierMenuDef48 = { (unsigned int)g_earlierMenuItems14, 0x0009, 0x0000, (unsigned int)g_earlierMenuPaged76, 0x00000000, (unsigned int)g_earlierMenuPaged353, 0x00000000, 0x0008, 0x0000, 0x0000, 0x0000, 0x00000000 };

struct MenuBuildDefinitionData g_earlierMenuDef50 = { (unsigned int)g_earlierMenuItems14, 0x0009, 0x0000, (unsigned int)g_earlierMenuPaged78, 0x00000000, (unsigned int)g_earlierMenuPaged353, 0x00000000, 0x0008, 0x0000, 0x0000, 0x0000, 0x00000000 };

struct MenuBuildItemData g_earlierMenuItems17[8] = {
    { 0x0001, 0x0000, 0x90000000, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x00000385, (unsigned int)g_earlierMenuPaged347, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x08000021, 0x0000, 0x0008, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource308, (unsigned int)g_earlierMenuPaged354, (unsigned int)g_earlierMenuPaged120, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00010041, 0x0000, 0x001E, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource308, (unsigned int)g_earlierMenuPaged354, (unsigned int)g_earlierMenuPaged121, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0005, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource308, (unsigned int)g_earlierMenuPaged354, (unsigned int)g_earlierMenuPaged123, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0005, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource308, (unsigned int)g_earlierMenuPaged354, (unsigned int)g_earlierMenuPaged126, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0005, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource308, (unsigned int)g_earlierMenuPaged354, (unsigned int)g_earlierMenuPaged132, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0005, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource308, (unsigned int)g_earlierMenuPaged354, (unsigned int)g_earlierMenuPaged134, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0019, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource248, (unsigned int)g_earlierMenuPaged354, (unsigned int)g_earlierMenuPaged137, (unsigned int)g_earlierMenuPaged28, 0x00000000 },
};

struct MenuBuildDefinitionData g_earlierMenuDef52 = { (unsigned int)g_earlierMenuItems17, 0x0008, 0x0000, (unsigned int)g_earlierMenuPaged102, 0x00000000, (unsigned int)g_earlierMenuPaged353, 0x00000000, 0x0007, 0x0000, 0x0000, 0x0000, 0x00000000 };

struct MenuBuildDefinitionData g_earlierMenuDef53 = { (unsigned int)g_earlierMenuItems17, 0x0008, 0x0000, (unsigned int)g_earlierMenuPaged103, 0x00000000, (unsigned int)g_earlierMenuPaged353, 0x00000000, 0x0007, 0x0000, 0x0000, 0x0000, 0x00000000 };

struct MenuBuildDefinitionData g_earlierMenuDef54 = { (unsigned int)g_earlierMenuItems17, 0x0008, 0x0000, (unsigned int)g_earlierMenuPaged104, 0x00000000, (unsigned int)g_earlierMenuPaged353, 0x00000000, 0x0007, 0x0000, 0x0000, 0x0000, 0x00000000 };

struct MenuBuildDefinitionData g_earlierMenuDef55 = { (unsigned int)g_earlierMenuItems17, 0x0008, 0x0000, (unsigned int)g_earlierMenuPaged105, 0x00000000, (unsigned int)g_earlierMenuPaged353, 0x00000000, 0x0007, 0x0000, 0x0000, 0x0000, 0x00000000 };

struct MenuBuildDefinitionData g_earlierMenuDef56 = { (unsigned int)g_earlierMenuItems17, 0x0008, 0x0000, (unsigned int)g_earlierMenuPaged106, 0x00000000, (unsigned int)g_earlierMenuPaged353, 0x00000000, 0x0007, 0x0000, 0x0000, 0x0000, 0x00000000 };

struct MenuBuildDefinitionData g_earlierMenuDef57 = { (unsigned int)g_earlierMenuItems17, 0x0008, 0x0000, (unsigned int)g_earlierMenuPaged107, 0x00000000, (unsigned int)g_earlierMenuPaged353, 0x00000000, 0x0007, 0x0000, 0x0000, 0x0000, 0x00000000 };

struct MenuBuildDefinitionData g_earlierMenuDef58 = { (unsigned int)g_earlierMenuItems17, 0x0008, 0x0000, (unsigned int)g_earlierMenuPaged108, 0x00000000, (unsigned int)g_earlierMenuPaged353, 0x00000000, 0x0007, 0x0000, 0x0000, 0x0000, 0x00000000 };

struct MenuBuildDefinitionData g_earlierMenuDef59 = { (unsigned int)g_earlierMenuItems17, 0x0008, 0x0000, (unsigned int)g_earlierMenuPaged109, 0x00000000, (unsigned int)g_earlierMenuPaged353, 0x00000000, 0x0007, 0x0000, 0x0000, 0x0000, 0x00000000 };

struct MenuBuildDefinitionData g_earlierMenuDef60 = { (unsigned int)g_earlierMenuItems17, 0x0008, 0x0000, (unsigned int)g_earlierMenuPaged110, 0x00000000, (unsigned int)g_earlierMenuPaged353, 0x00000000, 0x0007, 0x0000, 0x0000, 0x0000, 0x00000000 };

struct MenuBuildDefinitionData g_earlierMenuDef61 = { (unsigned int)g_earlierMenuItems17, 0x0008, 0x0000, (unsigned int)g_earlierMenuPaged111, 0x00000000, (unsigned int)g_earlierMenuPaged353, 0x00000000, 0x0007, 0x0000, 0x0000, 0x0000, 0x00000000 };

struct MenuBuildDefinitionData g_earlierMenuDef63 = { (unsigned int)g_earlierMenuItems17, 0x0008, 0x0000, (unsigned int)g_earlierMenuPaged112, 0x00000000, (unsigned int)g_earlierMenuPaged353, 0x00000000, 0x0007, 0x0000, 0x0000, 0x0000, 0x00000000 };

struct MenuBuildDefinitionData g_earlierMenuDef64 = { (unsigned int)g_earlierMenuItems17, 0x0008, 0x0000, (unsigned int)g_earlierMenuPaged113, 0x00000000, (unsigned int)g_earlierMenuPaged353, 0x00000000, 0x0007, 0x0000, 0x0000, 0x0000, 0x00000000 };

struct MenuBuildDefinitionData g_earlierMenuDef65 = { (unsigned int)g_earlierMenuItems17, 0x0008, 0x0000, (unsigned int)g_earlierMenuPaged114, 0x00000000, (unsigned int)g_earlierMenuPaged353, 0x00000000, 0x0007, 0x0000, 0x0000, 0x0000, 0x00000000 };

struct MenuBuildDefinitionData g_earlierMenuDef66 = { (unsigned int)g_earlierMenuItems17, 0x0008, 0x0000, (unsigned int)g_earlierMenuPaged116, 0x00000000, (unsigned int)g_earlierMenuPaged353, 0x00000000, 0x0007, 0x0000, 0x0000, 0x0000, 0x00000000 };

struct MenuBuildDefinitionData g_earlierMenuDef67 = { (unsigned int)g_earlierMenuItems17, 0x0008, 0x0000, (unsigned int)g_earlierMenuPaged119, 0x00000000, (unsigned int)g_earlierMenuPaged353, 0x00000000, 0x0007, 0x0000, 0x0000, 0x0000, 0x00000000 };

struct MenuBuildDefinitionData g_earlierMenuDef69 = { (unsigned int)g_earlierMenuItems17, 0x0008, 0x0000, (unsigned int)g_earlierMenuPaged117, 0x00000000, (unsigned int)g_earlierMenuPaged353, 0x00000000, 0x0007, 0x0000, 0x0000, 0x0000, 0x00000000 };

struct MenuBuildDefinitionData g_earlierMenuDef70 = { (unsigned int)g_earlierMenuItems17, 0x0008, 0x0000, (unsigned int)g_earlierMenuPaged118, 0x00000000, (unsigned int)g_earlierMenuPaged353, 0x00000000, 0x0007, 0x0000, 0x0000, 0x0000, 0x00000000 };

struct MenuBuildItemData g_earlierMenuItems21[8] = {
    { 0x0001, 0x0000, 0x90000000, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x00000385, (unsigned int)g_earlierMenuPaged347, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x08000021, 0x0000, 0x0008, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource249, (unsigned int)g_earlierMenuPaged354, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0028, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource308, (unsigned int)g_earlierMenuPaged354, (unsigned int)g_earlierMenuPaged145, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource308, (unsigned int)g_earlierMenuPaged354, (unsigned int)g_earlierMenuPaged148, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource308, (unsigned int)g_earlierMenuPaged354, (unsigned int)g_earlierMenuPaged151, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0014, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource250, (unsigned int)g_earlierMenuPaged354, 0x00000000, (unsigned int)g_earlierMenuPaged153, 0x00000000 },
    { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0005, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource251, (unsigned int)g_earlierMenuPaged354, 0x00000000, (unsigned int)g_earlierMenuPaged155, 0x00000000 },
    { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0005, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource308, (unsigned int)g_earlierMenuPaged354, (unsigned int)g_earlierMenuPaged160, (unsigned int)g_earlierMenuPaged158, 0x00000000 },
};

struct MenuBuildDefinitionData g_earlierMenuDef74 = { (unsigned int)g_earlierMenuItems21, 0x0008, 0x0000, (unsigned int)g_earlierMenuPaged141, 0x00000000, (unsigned int)g_earlierMenuPaged353, (unsigned int)g_earlierMenuPaged139, 0x0007, 0x0000, 0x0000, 0x0000, 0x00000000 };

struct MenuBuildDefinitionData g_earlierMenuDef75 = { (unsigned int)g_earlierMenuItems21, 0x0008, 0x0000, (unsigned int)g_earlierMenuPaged143, 0x00000000, (unsigned int)g_earlierMenuPaged353, (unsigned int)g_earlierMenuPaged139, 0x0005, 0x0000, 0x0000, 0x0000, 0x00000000 };

struct MenuBuildItemData g_earlierMenuItems24[8] = {
    { 0x0001, 0x0000, 0x90000000, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x00000385, (unsigned int)g_earlierMenuPaged347, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x08000801, 0x0000, 0x0008, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource308, (unsigned int)g_earlierMenuPaged354, (unsigned int)g_earlierMenuPaged167, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0023, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource308, (unsigned int)g_earlierMenuPaged354, (unsigned int)g_earlierMenuPaged168, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0004, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource308, (unsigned int)g_earlierMenuPaged354, (unsigned int)g_earlierMenuPaged169, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0004, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource308, (unsigned int)g_earlierMenuPaged354, (unsigned int)g_earlierMenuPaged170, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0004, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource308, (unsigned int)g_earlierMenuPaged354, (unsigned int)g_earlierMenuPaged171, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00012001, 0x0000, 0x0023, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource252, (unsigned int)g_earlierMenuPaged354, (unsigned int)g_earlierMenuPaged172, (unsigned int)g_earlierMenuPaged30, 0x00000000 },
    { 0x0000, 0x0000, 0x00012001, 0x0000, 0x0005, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource253, (unsigned int)g_earlierMenuPaged354, (unsigned int)g_earlierMenuPaged173, (unsigned int)g_earlierMenuPaged32, 0x00000000 },
};

struct MenuBuildDefinitionData g_earlierMenuDef78 = { (unsigned int)g_earlierMenuItems24, 0x0008, 0x0000, (unsigned int)g_earlierMenuPaged162, 0x00000000, (unsigned int)g_earlierMenuPaged353, (unsigned int)g_earlierMenuPaged161, 0x0007, 0x0000, 0x0000, 0x0000, 0x00000000 };

struct MenuBuildDefinitionData g_earlierMenuDef79 = { (unsigned int)g_earlierMenuItems24, 0x0008, 0x0000, (unsigned int)g_earlierMenuPaged163, 0x00000000, (unsigned int)g_earlierMenuPaged353, (unsigned int)g_earlierMenuPaged161, 0x0007, 0x0000, 0x0000, 0x0000, 0x00000000 };

struct MenuBuildDefinitionData g_earlierMenuDef80 = { (unsigned int)g_earlierMenuItems24, 0x0008, 0x0000, (unsigned int)g_earlierMenuPaged164, 0x00000000, (unsigned int)g_earlierMenuPaged353, (unsigned int)g_earlierMenuPaged161, 0x0007, 0x0000, 0x0000, 0x0000, 0x00000000 };

struct MenuBuildDefinitionData g_earlierMenuDef81 = { (unsigned int)g_earlierMenuItems24, 0x0008, 0x0000, (unsigned int)g_earlierMenuPaged165, 0x00000000, (unsigned int)g_earlierMenuPaged353, (unsigned int)g_earlierMenuPaged161, 0x0007, 0x0000, 0x0000, 0x0000, 0x00000000 };

struct MenuBuildDefinitionData g_earlierMenuDef82 = { (unsigned int)g_earlierMenuItems24, 0x0008, 0x0000, (unsigned int)g_earlierMenuPaged166, 0x00000000, (unsigned int)g_earlierMenuPaged353, (unsigned int)g_earlierMenuPaged161, 0x0007, 0x0000, 0x0000, 0x0000, 0x00000000 };

unsigned int g_earlierMenuWords1[1] = { 0x00010201 };

struct EarlierOptionBitRow g_earlierOptionBits2[12] = {
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

struct MenuBuildItemData g_earlierMenuItems27[33] = {
    { 0x0001, 0x0000, 0x50000000, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x00000385, (unsigned int)g_earlierMenuPaged347, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x08000801, 0x0000, 0x0008, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource262, (unsigned int)g_earlierMenuPaged354, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00210041, 0x0000, 0x0014, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource394, (unsigned int)g_earlierMenuPaged212, (unsigned int)g_earlierMenuPaged218, (unsigned int)g_earlierMenuPaged223, 0x00000000 },
    { 0x0000, 0x0000, 0x00010050, 0x0050, 0x0014, 0x06, 0x01, 0xFF, 0x07, (int)g_earlierMenuResource318, (unsigned int)g_earlierMenuPaged355, 0x00000000, (unsigned int)g_earlierMenuPaged224, 0x00000000 },
    { 0x0000, 0x0000, 0x00024050, 0x0008, 0x0000, 0xFF, 0x01, 0xFE, 0x07, (int)g_earlierMenuResource320, (unsigned int)g_earlierMenuPaged355, 0x00000000, (unsigned int)g_earlierMenuPaged224, 0x00000000 },
    { 0x0000, 0x0000, 0x00024050, 0x0008, 0x0000, 0xFF, 0x01, 0xFD, 0x07, (int)g_earlierMenuResource322, (unsigned int)g_earlierMenuPaged355, 0x00000000, (unsigned int)g_earlierMenuPaged224, 0x00000000 },
    { 0x0000, 0x0000, 0x00024050, 0x0008, 0x0000, 0xFF, 0x01, 0xFC, 0x07, (int)g_earlierMenuResource324, (unsigned int)g_earlierMenuPaged355, 0x00000000, (unsigned int)g_earlierMenuPaged224, 0x00000000 },
    { 0x0000, 0x0000, 0x00024050, 0x0008, 0x0000, 0xFF, 0x01, 0xFB, 0x07, (int)g_earlierMenuResource326, (unsigned int)g_earlierMenuPaged355, 0x00000000, (unsigned int)g_earlierMenuPaged224, 0x00000000 },
    { 0x0000, 0x0000, 0x00024050, 0x0008, 0x0000, 0xFF, 0x01, 0xFA, 0x07, (int)g_earlierMenuResource328, (unsigned int)g_earlierMenuPaged355, 0x00000000, (unsigned int)g_earlierMenuPaged224, 0x00000000 },
    { 0x0000, 0x0000, 0x00024050, 0x0008, 0x0000, 0xFF, 0xFA, 0xF9, 0x07, (int)g_earlierMenuResource330, (unsigned int)g_earlierMenuPaged355, 0x00000000, (unsigned int)g_earlierMenuPaged224, 0x00000000 },
    { 0x0000, 0x0000, 0x00010050, 0x0050, 0x0008, 0x06, 0x01, 0xF9, 0x07, (int)g_earlierMenuResource332, (unsigned int)g_earlierMenuPaged355, 0x00000000, (unsigned int)g_earlierMenuPaged224, 0x00000000 },
    { 0x0000, 0x0000, 0x00024050, 0x0008, 0x0000, 0xFF, 0x01, 0xF9, 0x07, (int)g_earlierMenuResource334, (unsigned int)g_earlierMenuPaged355, 0x00000000, (unsigned int)g_earlierMenuPaged224, 0x00000000 },
    { 0x0000, 0x0000, 0x00024050, 0x0008, 0x0000, 0xFF, 0x01, 0xF9, 0x07, (int)g_earlierMenuResource336, (unsigned int)g_earlierMenuPaged355, 0x00000000, (unsigned int)g_earlierMenuPaged224, 0x00000000 },
    { 0x0000, 0x0000, 0x00024050, 0x0008, 0x0000, 0xFF, 0x01, 0xF9, 0x07, (int)g_earlierMenuResource338, (unsigned int)g_earlierMenuPaged355, 0x00000000, (unsigned int)g_earlierMenuPaged224, 0x00000000 },
    { 0x0000, 0x0000, 0x00024050, 0x0008, 0x0000, 0xFF, 0x01, 0xF9, 0x07, (int)g_earlierMenuResource340, (unsigned int)g_earlierMenuPaged355, 0x00000000, (unsigned int)g_earlierMenuPaged224, 0x00000000 },
    { 0x0000, 0x0000, 0x00024050, 0x0008, 0x0000, 0xFF, 0x01, 0xF9, 0x07, (int)g_earlierMenuResource342, (unsigned int)g_earlierMenuPaged355, 0x00000000, (unsigned int)g_earlierMenuPaged224, 0x00000000 },
    { 0x0000, 0x0000, 0x00024050, 0x0008, 0x0000, 0xFF, 0xFA, 0xF9, 0x07, (int)g_earlierMenuResource344, (unsigned int)g_earlierMenuPaged355, 0x00000000, (unsigned int)g_earlierMenuPaged224, 0x00000000 },
    { 0x0000, 0x0000, 0x00010050, 0x0050, 0x0008, 0x06, 0x01, 0xF9, 0x07, (int)g_earlierMenuResource346, (unsigned int)g_earlierMenuPaged355, 0x00000000, (unsigned int)g_earlierMenuPaged224, 0x00000000 },
    { 0x0000, 0x0000, 0x00024050, 0x0008, 0x0000, 0xFF, 0x01, 0xF9, 0x07, (int)g_earlierMenuResource348, (unsigned int)g_earlierMenuPaged355, 0x00000000, (unsigned int)g_earlierMenuPaged224, 0x00000000 },
    { 0x0000, 0x0000, 0x00024050, 0x0008, 0x0000, 0xFF, 0x01, 0xF9, 0x07, (int)g_earlierMenuResource350, (unsigned int)g_earlierMenuPaged355, 0x00000000, (unsigned int)g_earlierMenuPaged224, 0x00000000 },
    { 0x0000, 0x0000, 0x00024050, 0x0008, 0x0000, 0xFF, 0x01, 0xF9, 0x07, (int)g_earlierMenuResource352, (unsigned int)g_earlierMenuPaged355, 0x00000000, (unsigned int)g_earlierMenuPaged224, 0x00000000 },
    { 0x0000, 0x0000, 0x00024050, 0x0008, 0x0000, 0xFF, 0x01, 0xF9, 0x07, (int)g_earlierMenuResource354, (unsigned int)g_earlierMenuPaged355, 0x00000000, (unsigned int)g_earlierMenuPaged224, 0x00000000 },
    { 0x0000, 0x0000, 0x00024050, 0x0008, 0x0000, 0xFF, 0x01, 0xF9, 0x07, (int)g_earlierMenuResource356, (unsigned int)g_earlierMenuPaged355, 0x00000000, (unsigned int)g_earlierMenuPaged224, 0x00000000 },
    { 0x0000, 0x0000, 0x00024050, 0x0008, 0x0000, 0xFF, 0xFA, 0xF9, 0x07, (int)g_earlierMenuResource358, (unsigned int)g_earlierMenuPaged355, 0x00000000, (unsigned int)g_earlierMenuPaged224, 0x00000000 },
    { 0x0000, 0x0000, 0x00010050, 0x0050, 0x0008, 0x06, 0x01, 0xF9, 0x08, (int)g_earlierMenuResource360, (unsigned int)g_earlierMenuPaged355, 0x00000000, (unsigned int)g_earlierMenuPaged224, 0x00000000 },
    { 0x0000, 0x0000, 0x00024050, 0x0008, 0x0000, 0xFF, 0x01, 0xF9, 0x07, (int)g_earlierMenuResource362, (unsigned int)g_earlierMenuPaged355, 0x00000000, (unsigned int)g_earlierMenuPaged224, 0x00000000 },
    { 0x0000, 0x0000, 0x00024050, 0x0008, 0x0000, 0xFF, 0x01, 0xF9, 0x06, (int)g_earlierMenuResource364, (unsigned int)g_earlierMenuPaged355, 0x00000000, (unsigned int)g_earlierMenuPaged224, 0x00000000 },
    { 0x0000, 0x0000, 0x00024050, 0x0008, 0x0000, 0xFF, 0x01, 0xF9, 0x05, (int)g_earlierMenuResource366, (unsigned int)g_earlierMenuPaged355, 0x00000000, (unsigned int)g_earlierMenuPaged224, 0x00000000 },
    { 0x0000, 0x0000, 0x00024050, 0x0008, 0x0000, 0xFF, 0x01, 0xF9, 0x04, (int)g_earlierMenuResource368, (unsigned int)g_earlierMenuPaged355, 0x00000000, (unsigned int)g_earlierMenuPaged224, 0x00000000 },
    { 0x0000, 0x0000, 0x00024050, 0x0008, 0x0000, 0xFF, 0x01, 0xF9, 0x03, (int)g_earlierMenuResource391, (unsigned int)g_earlierMenuPaged355, 0x00000000, (unsigned int)g_earlierMenuPaged226, 0x00000000 },
    { 0x0000, 0x0000, 0x00024050, 0x0008, 0x0000, 0xFF, 0xFA, 0xF9, 0x02, (int)g_earlierMenuResource392, (unsigned int)g_earlierMenuPaged355, 0x00000000, (unsigned int)g_earlierMenuPaged228, 0x00000000 },
    { 0x0000, 0x0000, 0x00011001, 0x0000, 0x0014, 0x00, 0x00, 0x00, 0x00, (int)g_earlierMenuResource308, (unsigned int)g_earlierMenuPaged354, (unsigned int)g_earlierMenuPaged229, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00310201, 0x0000, 0x0018, 0x00, 0x00, 0xFE, 0xE2, (int)g_earlierMenuResource263, (unsigned int)g_earlierMenuPaged354, 0x00000000, (unsigned int)g_earlierMenuPaged356, 0x00000000 },
};

struct MenuBuildDefinitionData g_earlierMenuDef83 = { (unsigned int)g_earlierMenuItems27, 0x0021, 0x0000, (unsigned int)g_earlierMenuPaged210, 0x00000000, (unsigned int)g_earlierMenuPaged353, 0x00000000, 0x0002, 0x0000, 0x0000, 0x0000, 0x00000000 };

struct MenuBuildItemData g_earlierMenuItems28[20] = {
    { 0x0001, 0x0000, 0x50000000, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x00000385, (unsigned int)g_earlierMenuPaged347, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x08000021, 0x0000, 0x0008, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource261, (unsigned int)g_earlierMenuPaged354, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00411001, 0x0000, 0x000C, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource265, (unsigned int)g_earlierMenuPaged354, (unsigned int)g_earlierMenuPaged232, (unsigned int)g_earlierMenuPaged231, 0x00000000 },
    { 0x0000, 0x0000, 0x00411001, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource266, (unsigned int)g_earlierMenuPaged354, (unsigned int)g_earlierMenuPaged236, (unsigned int)g_earlierMenuPaged235, 0x00000000 },
    { 0x0000, 0x0000, 0x00411001, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource267, (unsigned int)g_earlierMenuPaged354, (unsigned int)g_earlierMenuPaged240, (unsigned int)g_earlierMenuPaged239, 0x00000000 },
    { 0x0000, 0x0000, 0x00411001, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource268, (unsigned int)g_earlierMenuPaged354, (unsigned int)g_earlierMenuPaged243, (unsigned int)g_earlierMenuPaged242, 0x00000000 },
    { 0x0000, 0x0000, 0x00411001, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource269, (unsigned int)g_earlierMenuPaged354, (unsigned int)g_earlierMenuPaged245, (unsigned int)g_earlierMenuPaged244, 0x00000000 },
    { 0x0000, 0x0000, 0x00411001, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource270, (unsigned int)g_earlierMenuPaged354, (unsigned int)g_earlierMenuPaged250, (unsigned int)g_earlierMenuPaged248, 0x00000000 },
    { 0x0000, 0x0000, 0x00411001, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource271, (unsigned int)g_earlierMenuPaged354, (unsigned int)g_earlierMenuPaged254, (unsigned int)g_earlierMenuPaged253, 0x00000000 },
    { 0x0000, 0x0000, 0x00411001, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource273, (unsigned int)g_earlierMenuPaged354, (unsigned int)g_earlierMenuPaged265, (unsigned int)g_earlierMenuPaged262, 0x00000000 },
    { 0x0000, 0x0000, 0x00411001, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource272, (unsigned int)g_earlierMenuPaged354, (unsigned int)g_earlierMenuPaged259, (unsigned int)g_earlierMenuPaged258, 0x00000000 },
    { 0x0000, 0x0000, 0x00411001, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource274, (unsigned int)g_earlierMenuPaged354, (unsigned int)g_earlierMenuPaged269, (unsigned int)g_earlierMenuPaged267, 0x00000000 },
    { 0x0000, 0x0000, 0x00411001, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource275, (unsigned int)g_earlierMenuPaged354, (unsigned int)g_earlierMenuPaged271, (unsigned int)g_earlierMenuPaged270, 0x00000000 },
    { 0x0000, 0x0000, 0x00411001, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource276, (unsigned int)g_earlierMenuPaged354, (unsigned int)g_earlierMenuPaged273, (unsigned int)g_earlierMenuPaged272, 0x00000000 },
    { 0x0000, 0x0000, 0x00411001, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource277, (unsigned int)g_earlierMenuPaged354, (unsigned int)g_earlierMenuPaged275, (unsigned int)g_earlierMenuPaged274, 0x00000000 },
    { 0x0000, 0x0000, 0x00411001, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource278, (unsigned int)g_earlierMenuPaged354, (unsigned int)g_earlierMenuPaged278, (unsigned int)g_earlierMenuPaged277, 0x00000000 },
    { 0x0000, 0x0000, 0x00411001, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource279, (unsigned int)g_earlierMenuPaged354, (unsigned int)g_earlierMenuPaged280, (unsigned int)g_earlierMenuPaged279, 0x00000000 },
    { 0x0000, 0x0000, 0x00411001, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource280, (unsigned int)g_earlierMenuPaged354, (unsigned int)g_earlierMenuPaged285, (unsigned int)g_earlierMenuPaged284, 0x00000000 },
    { 0x0000, 0x0000, 0x00411001, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource308, (unsigned int)g_earlierMenuPaged354, (unsigned int)g_earlierMenuPaged230, (unsigned int)g_earlierMenuPaged199, 0x00000000 },
    { 0x0000, 0x0000, 0x00000201, 0x0000, 0x00C0, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource263, (unsigned int)g_earlierMenuPaged354, 0x00000000, (unsigned int)g_earlierMenuPaged356, 0x00000000 },
};

struct MenuBuildDefinitionData g_earlierMenuDef87 = { (unsigned int)g_earlierMenuItems28, 0x0014, 0x0000, (unsigned int)g_earlierMenuPaged193, 0x00000000, (unsigned int)g_earlierMenuPaged353, 0x00000000, 0x0013, 0x0000, 0x0000, 0x0000, 0x00000000 };

unsigned int g_earlierMenuWords2[1] = { 0x00000000 };

struct MenuBuildItemData g_earlierMenuItems34[3] = {
    { 0x0000, 0x0000, 0x00000021, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource264, (unsigned int)g_earlierMenuPaged354, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00010081, 0x0000, 0x0028, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource259, (unsigned int)g_earlierMenuPaged354, 0x00000000, (unsigned int)g_earlierMenuPaged288, 0x00000000 },
    { 0x0000, 0x0000, 0x00010081, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource260, (unsigned int)g_earlierMenuPaged354, 0x00000000, (unsigned int)g_earlierMenuPaged289, 0x00000000 },
};

struct MenuBuildDefinitionData g_earlierMenuDef91 = { (unsigned int)g_earlierMenuItems34, 0x0003, 0x0000, 0x00000000, 0x00000000, (unsigned int)g_earlierMenuPaged353, 0x00000000, 0x0001, 0x0000, 0x0000, 0x0000, 0x00000000 };

struct MenuBuildItemData g_earlierMenuItems35[8] = {
    { 0x0000, 0x0000, 0x00011001, 0x0000, 0x0000, 0x00, 0x00, 0x00, 0x00, (int)g_earlierMenuResource196, (unsigned int)g_earlierMenuPaged354, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00011001, 0x0000, 0x0000, 0x00, 0x00, 0x00, 0x00, (int)g_earlierMenuResource197, (unsigned int)g_earlierMenuPaged354, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00011001, 0x0000, 0x0000, 0x00, 0x00, 0x00, 0x00, (int)g_earlierMenuResource198, (unsigned int)g_earlierMenuPaged354, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00011001, 0x0000, 0x0000, 0x00, 0x00, 0x00, 0x00, (int)g_earlierMenuResource199, (unsigned int)g_earlierMenuPaged354, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00011001, 0x0000, 0x0000, 0x00, 0x00, 0x00, 0x00, (int)g_earlierMenuResource200, (unsigned int)g_earlierMenuPaged354, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00011001, 0x0000, 0x0000, 0x00, 0x00, 0x00, 0x00, (int)g_earlierMenuResource201, (unsigned int)g_earlierMenuPaged354, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00011001, 0x0000, 0x0000, 0x00, 0x00, 0x00, 0x00, (int)g_earlierMenuResource202, (unsigned int)g_earlierMenuPaged354, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0005, 0x00, 0x00, 0x00, 0x00, (int)g_earlierMenuResource195, (unsigned int)g_earlierMenuPaged354, 0x00000000, (unsigned int)g_earlierMenuPaged304, 0x00000000 },
};

struct MenuBuildDefinitionData g_earlierMenuDef100 = { (unsigned int)g_earlierMenuItems35, 0x0008, 0x0000, 0x00000000, 0x00000000, (unsigned int)g_earlierMenuPaged353, (unsigned int)g_earlierMenuPaged303, 0x0007, 0x0000, 0x0000, 0x0000, (intptr_t)&g_earlierMenuDef101 };

struct MenuBuildItemData g_earlierMenuItems37[5] = {
    { 0x0000, 0x0000, 0x00011001, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x02, (int)g_earlierMenuResource192, (unsigned int)g_earlierMenuPaged354, 0x00000000, (unsigned int)g_earlierMenuPaged311, 0x00000000 },
    { 0x0000, 0x0000, 0x00010101, 0x0000, 0x0008, 0x00, 0x00, 0x00, 0x00, (int)g_earlierMenuResource193, (unsigned int)g_earlierMenuPaged354, (unsigned int)g_earlierMenuPaged312, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00411001, 0x0000, 0x0008, 0x00, 0x00, 0xFE, 0x01, (int)g_earlierMenuResource308, (unsigned int)g_earlierMenuPaged354, (unsigned int)g_earlierMenuPaged308, (unsigned int)g_earlierMenuPaged307, 0x00000000 },
    { 0x0000, 0x0000, 0x00411001, 0x0000, 0x0002, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource194, (unsigned int)g_earlierMenuPaged354, (unsigned int)g_earlierMenuPaged314, (unsigned int)g_earlierMenuPaged310, 0x00000000 },
    { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0005, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource195, (unsigned int)g_earlierMenuPaged354, 0x00000000, (unsigned int)g_earlierMenuPaged313, 0x00000000 },
};

struct MenuBuildDefinitionData g_earlierMenuDef101 = { (unsigned int)g_earlierMenuItems37, 0x0005, 0x0000, 0x00000000, 0x00000000, (unsigned int)g_earlierMenuPaged353, (unsigned int)g_earlierMenuPaged305, 0x0004, 0x0000, 0x0000, 0x0000, (intptr_t)&g_earlierMenuDef102 };

struct EarlierMenuTuning g_earlierMenuTuning2 = {
    0x00000460, 0x0000000B, 0x00000000, 0x00000000,
    -5e+01f, -9e+02f,
    { 2.0f, 2.0f, 2.0f },
    0x00000032, 0x00000050,
    0.087266475f,
};

struct MenuBuildItemData g_earlierMenuItems38[3] = {
    { 0x0001, 0x0000, 0x30000000, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x00000387, (unsigned int)g_earlierMenuPaged347, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0003, 0x0000, 0x00410021, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (intptr_t)&g_earlierMenuTuning2, (unsigned int)g_earlierMenuPaged349, (unsigned int)g_earlierMenuPaged321, (unsigned int)g_earlierMenuPaged320, 0x00000000 },
    { 0x0000, 0x0000, 0x00010081, 0x0000, 0x0019, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource191, (unsigned int)g_earlierMenuPaged354, (unsigned int)g_earlierMenuPaged319, (unsigned int)g_earlierMenuPaged318, 0x00000000 },
};

struct MenuBuildDefinitionData g_earlierMenuDef102 = { (unsigned int)g_earlierMenuItems38, 0x0003, 0x0000, (unsigned int)g_earlierMenuPaged315, 0x00000000, (unsigned int)g_earlierMenuPaged353, (unsigned int)g_earlierMenuPaged317, 0x0001, 0x0000, 0x0000, 0x0000, 0x00000000 };

struct MenuBuildDefinitionData g_earlierMenuDef103 = { (unsigned int)g_earlierMenuItems38, 0x0003, 0x0000, (unsigned int)g_earlierMenuPaged316, 0x00000000, (unsigned int)g_earlierMenuPaged353, (unsigned int)g_earlierMenuPaged317, 0x0001, 0x0000, 0x0000, 0x0000, 0x00000000 };

struct MenuBuildItemData g_earlierMenuItems39[4] = {
    { 0x0001, 0x0000, 0x30000000, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x00000387, (unsigned int)g_earlierMenuPaged347, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00010081, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource203, (unsigned int)g_earlierMenuPaged354, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00010101, 0x0000, 0x000C, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource204, (unsigned int)g_earlierMenuPaged354, 0x00000000, (unsigned int)g_earlierMenuPaged323, 0x00000000 },
    { 0x0000, 0x0000, 0x00010101, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource205, (unsigned int)g_earlierMenuPaged354, 0x00000000, (unsigned int)g_earlierMenuPaged324, 0x00000000 },
};

struct MenuBuildDefinitionData g_earlierMenuDef105 = { (unsigned int)g_earlierMenuItems39, 0x0004, 0x0000, 0x00000000, 0x00000000, (unsigned int)g_earlierMenuPaged353, (unsigned int)g_earlierMenuPaged322, 0x0002, 0x0000, 0x0000, 0x0000, 0x00000000 };

float g_earlierMenuRamp2[16] = {
    -0.5f, -0.4f, -0.3f, -0.2f, -0.1f, 0.0f, 0.1f, 0.2f,
    0.3f, 0.4f, 0.5f, 0.6f, 0.7f, 0.8f, 0.9f, 1.0f,
};

struct MenuBuildItemData g_earlierMenuItems41[11] = {
    { 0x0001, 0x0000, 0x10000000, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x00000385, (unsigned int)g_earlierMenuPaged347, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x08000201, 0x0000, 0x000C, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource294, (unsigned int)g_earlierMenuPaged354, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00410041, 0x0000, 0x001E, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource308, (unsigned int)g_earlierMenuPaged354, (unsigned int)g_earlierMenuPaged291, (unsigned int)g_earlierMenuPaged325, 0x00000000 },
    { 0x0000, 0x0000, 0x00410041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource308, (unsigned int)g_earlierMenuPaged354, (unsigned int)g_earlierMenuPaged291, (unsigned int)g_earlierMenuPaged325, 0x00000000 },
    { 0x0000, 0x0000, 0x00410041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource308, (unsigned int)g_earlierMenuPaged354, (unsigned int)g_earlierMenuPaged291, (unsigned int)g_earlierMenuPaged325, 0x00000000 },
    { 0x0000, 0x0000, 0x00410041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource308, (unsigned int)g_earlierMenuPaged354, (unsigned int)g_earlierMenuPaged291, (unsigned int)g_earlierMenuPaged325, 0x00000000 },
    { 0x0000, 0x0000, 0x00410041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource308, (unsigned int)g_earlierMenuPaged354, (unsigned int)g_earlierMenuPaged291, (unsigned int)g_earlierMenuPaged325, 0x00000000 },
    { 0x0000, 0x0000, 0x00410041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource308, (unsigned int)g_earlierMenuPaged354, (unsigned int)g_earlierMenuPaged291, (unsigned int)g_earlierMenuPaged325, 0x00000000 },
    { 0x0000, 0x0000, 0x00410041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource308, (unsigned int)g_earlierMenuPaged354, (unsigned int)g_earlierMenuPaged291, (unsigned int)g_earlierMenuPaged325, 0x00000000 },
    { 0x0000, 0x0000, 0x00410041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource308, (unsigned int)g_earlierMenuPaged354, (unsigned int)g_earlierMenuPaged291, (unsigned int)g_earlierMenuPaged325, 0x00000000 },
    { 0x0000, 0x0000, 0x00010201, 0x0000, 0x002D, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource263, (unsigned int)g_earlierMenuPaged354, 0x00000000, (unsigned int)g_earlierMenuPaged356, 0x00000000 },
};

struct MenuBuildDefinitionData g_earlierMenuDef108 = { (unsigned int)g_earlierMenuItems41, 0x000B, 0x0000, 0x00000000, 0x00000000, (unsigned int)g_earlierMenuPaged353, 0x00000000, 0x000A, 0x0000, 0x0000, 0x0000, (intptr_t)&g_earlierMenuDef109 };

struct MenuBuildItemData g_earlierMenuItems44[4] = {
    { 0x0001, 0x0000, 0x10000000, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x00000385, (unsigned int)g_earlierMenuPaged347, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x08000021, 0x0000, 0x0008, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource293, (unsigned int)g_earlierMenuPaged354, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00010081, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource294, (unsigned int)g_earlierMenuPaged354, 0x00000000, (unsigned int)g_earlierMenuPaged326, 0x00000000 },
    { 0x0000, 0x0000, 0x00010201, 0x0000, 0x0038, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource263, (unsigned int)g_earlierMenuPaged354, 0x00000000, (unsigned int)g_earlierMenuPaged356, 0x00000000 },
};

struct MenuBuildDefinitionData g_earlierMenuDef109 = { (unsigned int)g_earlierMenuItems44, 0x0004, 0x0000, 0x00000000, 0x00000000, (unsigned int)g_earlierMenuPaged353, 0x00000000, 0x0002, 0x0000, 0x0000, 0x0000, (intptr_t)&g_earlierMenuDef114 };

struct MenuBuildItemData g_earlierMenuItems45[5] = {
    { 0x0001, 0x0000, 0x10000000, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x00000385, (unsigned int)g_earlierMenuPaged347, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x08000801, 0x0000, 0x0008, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource289, (unsigned int)g_earlierMenuPaged354, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00010081, 0x0000, 0x0036, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource290, (unsigned int)g_earlierMenuPaged354, 0x00000000, (unsigned int)g_earlierMenuPaged329, 0x00000000 },
    { 0x0000, 0x0000, 0x00010081, 0x0000, 0x0004, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource291, (unsigned int)g_earlierMenuPaged354, 0x00000000, (unsigned int)g_earlierMenuPaged330, 0x00000000 },
    { 0x0000, 0x0000, 0x00010201, 0x0000, 0x0049, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource190, (unsigned int)g_earlierMenuPaged354, 0x00000000, (unsigned int)g_earlierMenuPaged331, 0x00000000 },
};

struct MenuBuildDefinitionData g_earlierMenuDef111 = { (unsigned int)g_earlierMenuItems45, 0x0005, 0x0000, (unsigned int)g_earlierMenuPaged327, 0x00000000, (unsigned int)g_earlierMenuPaged353, 0x00000000, 0x0002, 0x0000, 0x0000, 0x0000, 0x00000000 };

struct MenuBuildDefinitionData g_earlierMenuDef112 = { (unsigned int)g_earlierMenuItems45, 0x0005, 0x0000, (unsigned int)g_earlierMenuPaged328, 0x00000000, (unsigned int)g_earlierMenuPaged353, 0x00000000, 0x0002, 0x0000, 0x0000, 0x0000, 0x00000000 };

struct MenuBuildItemData g_earlierMenuItems47[1] = {
    { 0x0001, 0x0000, 0x10000000, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x00000385, (unsigned int)g_earlierMenuPaged347, 0x00000000, 0x00000000, 0x00000000 },
};

struct MenuBuildDefinitionData g_earlierMenuDef113 = { (unsigned int)g_earlierMenuItems47, 0x0001, 0x0000, 0x00000000, 0x00000000, (unsigned int)g_earlierMenuPaged353, 0x00000000, 0x0002, 0x0000, 0x0000, 0x0000, (intptr_t)&g_earlierMenuDef114 };

struct MenuBuildItemData g_earlierMenuItems48[7] = {
    { 0x0001, 0x0000, 0x10000000, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x00000384, (unsigned int)g_earlierMenuPaged347, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00000081, 0x0000, 0x001E, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource289, (unsigned int)g_earlierMenuPaged354, 0x00000000, (unsigned int)g_earlierMenuPaged332, 0x00000000 },
    { 0x0000, 0x0000, 0x00010081, 0x0000, 0x000C, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource292, (unsigned int)g_earlierMenuPaged354, (unsigned int)g_earlierMenuPaged333, (unsigned int)g_earlierMenuPaged334, 0x00000000 },
    { 0x0000, 0x0000, 0x00010081, 0x0000, 0x000C, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource262, (unsigned int)g_earlierMenuPaged354, 0x00000000, (unsigned int)g_earlierMenuPaged336, 0x00000000 },
    { 0x0000, 0x0000, 0x00010081, 0x0000, 0x000C, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource297, (unsigned int)g_earlierMenuPaged354, 0x00000000, (unsigned int)g_earlierMenuPaged337, 0x00000000 },
    { 0x0000, 0x0000, 0x00010081, 0x0000, 0x000C, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource296, (unsigned int)g_earlierMenuPaged354, 0x00000000, (unsigned int)g_earlierMenuPaged335, 0x00000000 },
    { 0x0000, 0x0000, 0x00010081, 0x0000, 0x000C, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource298, (unsigned int)g_earlierMenuPaged354, 0x00000000, (unsigned int)g_earlierMenuPaged338, 0x00000000 },
};

struct MenuBuildDefinitionData g_earlierMenuDef114 = { (unsigned int)g_earlierMenuItems48, 0x0007, 0x0000, 0x00000000, 0x00000000, (unsigned int)g_earlierMenuPaged353, 0x00000000, 0x0001, 0x0000, 0x0000, 0x0000, 0x00000000 };

unsigned int g_earlierMenuWords3[1] = { 0x00000000 };

struct MenuBuildItemData g_earlierMenuItems49[2] = {
    { 0x0001, 0x0000, 0x00000000, 0x0000, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x00000064, (unsigned int)g_earlierMenuPaged347, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00000089, 0x0000, 0x0028, 0x00, 0x00, 0x00, 0x00, (int)g_earlierMenuResource393, (unsigned int)g_earlierMenuPaged354, (unsigned int)g_earlierMenuPaged341, 0x00000000, 0x00000000 },
};

struct MenuBuildDefinitionData g_earlierMenuDef115 = { (unsigned int)g_earlierMenuItems49, 0x0002, 0x0000, (unsigned int)g_earlierMenuPaged339, 0x00000000, (unsigned int)g_earlierMenuPaged353, (unsigned int)g_earlierMenuPaged340, 0x0001, 0x0000, 0x0000, 0x0000, 0x00000000 };

unsigned int g_earlierMenuWords4[1] = { 0x00010041 };

struct MenuBuildItemData g_earlierMenuItems50[49] = {
    { 0x0001, 0x0000, 0x50000000, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x00000385, (unsigned int)g_earlierMenuPaged347, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x08000801, 0x0000, 0x0008, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource218, (unsigned int)g_earlierMenuPaged354, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00010080, 0x0023, 0x0016, 0x00, 0x00, 0x00, 0x00, (int)g_earlierMenuResource309, (unsigned int)g_earlierMenuPaged354, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0001, 0x0000, 0x00024010, 0x0003, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x000007D0, (unsigned int)g_earlierMenuPaged342, 0x00000000, 0x00000000, 0x10D60000 },
    { 0x0001, 0x0000, 0x00024010, 0x0003, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x000007D0, (unsigned int)g_earlierMenuPaged342, 0x00000000, 0x00000000, 0x10D60001 },
    { 0x0001, 0x0000, 0x00024010, 0x0003, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x000007D0, (unsigned int)g_earlierMenuPaged342, 0x00000000, 0x00000000, 0x10D60002 },
    { 0x0001, 0x0000, 0x00024010, 0x0003, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x000007D1, (unsigned int)g_earlierMenuPaged342, 0x00000000, 0x00000000, 0x10E00000 },
    { 0x0001, 0x0000, 0x00024010, 0x0003, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x000007D1, (unsigned int)g_earlierMenuPaged342, 0x00000000, 0x00000000, 0x10E00001 },
    { 0x0001, 0x0000, 0x00024010, 0x0003, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x000007D1, (unsigned int)g_earlierMenuPaged342, 0x00000000, 0x00000000, 0x10E00002 },
    { 0x0001, 0x0000, 0x00024010, 0x0029, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x000007E4, (unsigned int)g_earlierMenuPaged342, 0x00000000, 0x00000000, 0x11080000 },
    { 0x0001, 0x0000, 0x00024010, 0x0003, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x00000820, (unsigned int)g_earlierMenuPaged342, 0x00000000, 0x00000000, 0x11940000 },
    { 0x0000, 0x0000, 0x00010080, 0x0023, 0x0003, 0x00, 0x00, 0x00, 0x00, (int)g_earlierMenuResource310, (unsigned int)g_earlierMenuPaged354, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0001, 0x0000, 0x00024010, 0x0003, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x000007D2, (unsigned int)g_earlierMenuPaged342, 0x00000000, 0x00000000, 0x10EA0000 },
    { 0x0001, 0x0000, 0x00024010, 0x0003, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x000007D2, (unsigned int)g_earlierMenuPaged342, 0x00000000, 0x00000000, 0x10EA0001 },
    { 0x0001, 0x0000, 0x00024010, 0x0003, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x000007D2, (unsigned int)g_earlierMenuPaged342, 0x00000000, 0x00000000, 0x10EA0002 },
    { 0x0001, 0x0000, 0x00024010, 0x003C, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x0000080D, (unsigned int)g_earlierMenuPaged342, 0x00000000, 0x00000000, 0x11320000 },
    { 0x0001, 0x0000, 0x00024010, 0x0003, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x000007F9, (unsigned int)g_earlierMenuPaged342, 0x00000000, 0x00000000, 0x111E0000 },
    { 0x0001, 0x0000, 0x00024010, 0x0003, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x000007E5, (unsigned int)g_earlierMenuPaged342, 0x00000000, 0x00000000, 0x11090000 },
    { 0x0001, 0x0000, 0x00024010, 0x0003, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x00000820, (unsigned int)g_earlierMenuPaged342, 0x00000000, 0x00000000, 0x11940001 },
    { 0x0000, 0x0000, 0x00010080, 0x0023, 0x0003, 0x00, 0x00, 0x00, 0x00, (int)g_earlierMenuResource311, (unsigned int)g_earlierMenuPaged354, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0001, 0x0000, 0x00024010, 0x0003, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x000007D3, (unsigned int)g_earlierMenuPaged342, 0x00000000, 0x00000000, 0x10F40000 },
    { 0x0001, 0x0000, 0x00024010, 0x0003, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x000007D3, (unsigned int)g_earlierMenuPaged342, 0x00000000, 0x00000000, 0x10F40001 },
    { 0x0001, 0x0000, 0x00024010, 0x0003, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x000007D3, (unsigned int)g_earlierMenuPaged342, 0x00000000, 0x00000000, 0x10F40002 },
    { 0x0001, 0x0000, 0x00024010, 0x003C, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x0000080F, (unsigned int)g_earlierMenuPaged342, 0x00000000, 0x00000000, 0x11300000 },
    { 0x0001, 0x0000, 0x00024010, 0x0003, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x000007F8, (unsigned int)g_earlierMenuPaged342, 0x00000000, 0x00000000, 0x111C0000 },
    { 0x0001, 0x0000, 0x00024010, 0x0003, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x000007E6, (unsigned int)g_earlierMenuPaged342, 0x00000000, 0x00000000, 0x110A0000 },
    { 0x0001, 0x0000, 0x00024010, 0x0003, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x00000820, (unsigned int)g_earlierMenuPaged342, 0x00000000, 0x00000000, 0x11940002 },
    { 0x0000, 0x0000, 0x00010080, 0x0023, 0x0003, 0x00, 0x00, 0x00, 0x00, (int)g_earlierMenuResource312, (unsigned int)g_earlierMenuPaged354, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0001, 0x0000, 0x00024010, 0x0003, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x000007D4, (unsigned int)g_earlierMenuPaged342, 0x00000000, 0x00000000, 0x10FE0000 },
    { 0x0001, 0x0000, 0x00024010, 0x0003, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x000007D4, (unsigned int)g_earlierMenuPaged342, 0x00000000, 0x00000000, 0x10FE0001 },
    { 0x0001, 0x0000, 0x00024010, 0x0003, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x000007D4, (unsigned int)g_earlierMenuPaged342, 0x00000000, 0x00000000, 0x10FE0002 },
    { 0x0001, 0x0000, 0x00024010, 0x003C, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x0000080E, (unsigned int)g_earlierMenuPaged342, 0x00000000, 0x00000000, 0x11340000 },
    { 0x0001, 0x0000, 0x00024010, 0x0003, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x000007FC, (unsigned int)g_earlierMenuPaged342, 0x00000000, 0x00000000, 0x11200000 },
    { 0x0001, 0x0000, 0x00024010, 0x0003, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x000007E7, (unsigned int)g_earlierMenuPaged342, 0x00000000, 0x00000000, 0x110B0000 },
    { 0x0001, 0x0000, 0x00024010, 0x0003, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x00000820, (unsigned int)g_earlierMenuPaged342, 0x00000000, 0x00000000, 0x11940003 },
    { 0x0000, 0x0000, 0x00010080, 0x0023, 0x0003, 0x00, 0x00, 0x00, 0x00, (int)g_earlierMenuResource313, (unsigned int)g_earlierMenuPaged354, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0001, 0x0000, 0x00024010, 0x0003, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x000007D4, (unsigned int)g_earlierMenuPaged342, 0x00000000, 0x00000000, 0x10FE0003 },
    { 0x0001, 0x0000, 0x00024010, 0x0003, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x000007D4, (unsigned int)g_earlierMenuPaged342, 0x00000000, 0x00000000, 0x10FE0004 },
    { 0x0001, 0x0000, 0x00024010, 0x0003, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x000007D4, (unsigned int)g_earlierMenuPaged342, 0x00000000, 0x00000000, 0x10FE0005 },
    { 0x0001, 0x0000, 0x00024010, 0x003C, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x0000080C, (unsigned int)g_earlierMenuPaged342, 0x00000000, 0x00000000, 0x11330000 },
    { 0x0001, 0x0000, 0x00024010, 0x0003, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x000007FB, (unsigned int)g_earlierMenuPaged342, 0x00000000, 0x00000000, 0x111F0000 },
    { 0x0001, 0x0000, 0x00024010, 0x0003, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x000007E8, (unsigned int)g_earlierMenuPaged342, 0x00000000, 0x00000000, 0x110C0000 },
    { 0x0001, 0x0000, 0x00024010, 0x0003, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x00000820, (unsigned int)g_earlierMenuPaged342, 0x00000000, 0x00000000, 0x11940004 },
    { 0x0000, 0x0000, 0x00010080, 0x0023, 0x0003, 0x00, 0x00, 0x00, 0x00, (int)g_earlierMenuResource314, (unsigned int)g_earlierMenuPaged354, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0001, 0x0000, 0x00024010, 0x0075, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x00000810, (unsigned int)g_earlierMenuPaged342, 0x00000000, 0x00000000, 0x11310000 },
    { 0x0001, 0x0000, 0x00024010, 0x0003, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x000007FA, (unsigned int)g_earlierMenuPaged342, 0x00000000, 0x00000000, 0x111D0000 },
    { 0x0001, 0x0000, 0x00024010, 0x0003, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x000007E9, (unsigned int)g_earlierMenuPaged342, 0x00000000, 0x00000000, 0x110D0000 },
    { 0x0001, 0x0000, 0x00024010, 0x0003, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x00000820, (unsigned int)g_earlierMenuPaged342, 0x00000000, 0x00000000, 0x11940005 },
    { 0x0000, 0x0000, 0x00010081, 0x0000, 0x001E, 0x00, 0x00, 0x00, 0x00, (int)g_earlierMenuResource219, (unsigned int)g_earlierMenuPaged354, 0x00000000, (unsigned int)g_earlierMenuPaged344, 0x00000000 },
};

struct MenuBuildDefinitionData g_earlierMenuDef117 = { (unsigned int)g_earlierMenuItems50, 0x0031, 0x0000, (unsigned int)g_earlierMenuPaged343, 0x00000000, (unsigned int)g_earlierMenuPaged353, 0x00000000, 0x0030, 0x0000, 0x0000, 0x0000, (intptr_t)&g_earlierMenuDef135 };

unsigned int g_earlierMenuWords5[2] = { 0x00000000, 0x00024110 };

struct MenuBuildItemData g_earlierMenuItems51[1] = {
    { 0x0001, 0x0000, 0x50000000, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x00000385, (unsigned int)g_earlierMenuPaged347, 0x00000000, 0x00000000, 0x00000000 },
};

struct MenuBuildDefinitionData g_earlierMenuDef118 = { (unsigned int)g_earlierMenuItems51, 0x0001, 0x0000, (unsigned int)g_earlierMenuPaged369, 0x00000000, (unsigned int)g_earlierMenuPaged353, 0x00000000, 0x0009, 0x0000, 0x0000, 0x0000, (intptr_t)&g_earlierMenuDef132 };

struct MenuBuildDefinitionData g_earlierMenuDef119 = { (unsigned int)g_earlierMenuItems51, 0x0001, 0x0000, (unsigned int)g_earlierMenuPaged370, 0x00000000, (unsigned int)g_earlierMenuPaged353, 0x00000000, 0x0009, 0x0000, 0x0000, 0x0000, 0x00000000 };

unsigned int g_earlierMenuWords6[1] = { 0x00446920 };

struct MenuBuildItemData g_earlierMenuItems52[3] = {
    { 0x0001, 0x0000, 0x50000000, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x00000385, (unsigned int)g_earlierMenuPaged347, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00000401, 0x0000, 0x0028, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource282, (unsigned int)g_earlierMenuPaged354, (unsigned int)g_earlierMenuPaged373, 0x00000000, 0x00000000 },
    { 0x0001, 0x0000, 0x20010001, 0x0000, 0x0000, 0x00, 0x00, 0x00, 0x01, 0x0000012D, (unsigned int)g_earlierMenuPaged382, 0x00000000, (unsigned int)g_earlierMenuPaged380, 0x00000000 },
};

struct MenuBuildItemData g_earlierMenuItems53[3] = {
    { 0x0001, 0x0000, 0x50000000, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x00000385, (unsigned int)g_earlierMenuPaged347, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00000401, 0x0000, 0x0028, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource284, (unsigned int)g_earlierMenuPaged354, (unsigned int)g_earlierMenuPaged373, 0x00000000, 0x00000000 },
    { 0x0001, 0x0000, 0x20010001, -20, 0x0000, 0xEC, 0x00, 0x00, 0x01, 0x0000012D, (unsigned int)g_earlierMenuPaged382, 0x00000000, (unsigned int)g_earlierMenuPaged380, 0x00000000 },
};

struct MenuBuildItemData g_earlierMenuItems54[3] = {
    { 0x0001, 0x0000, 0x50000000, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x00000385, (unsigned int)g_earlierMenuPaged347, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00000401, 0x0000, 0x0028, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource286, (unsigned int)g_earlierMenuPaged354, (unsigned int)g_earlierMenuPaged373, 0x00000000, 0x00000000 },
    { 0x0001, 0x0000, 0x20010001, 0x0000, 0x0000, 0x00, 0x00, 0x00, 0x01, 0x0000012D, (unsigned int)g_earlierMenuPaged382, 0x00000000, (unsigned int)g_earlierMenuPaged380, 0x00000000 },
};

struct MenuBuildItemData g_earlierMenuItems55[3] = {
    { 0x0001, 0x0000, 0x50000000, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x00000385, (unsigned int)g_earlierMenuPaged347, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00000401, 0x0000, 0x0028, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource288, (unsigned int)g_earlierMenuPaged354, (unsigned int)g_earlierMenuPaged373, 0x00000000, 0x00000000 },
    { 0x0001, 0x0000, 0x20010001, 0x0000, 0x0000, 0x00, 0x00, 0x00, 0x01, 0x0000012D, (unsigned int)g_earlierMenuPaged382, 0x00000000, (unsigned int)g_earlierMenuPaged380, 0x00000000 },
};

struct MenuBuildDefinitionData g_earlierMenuDef120 = { (unsigned int)g_earlierMenuItems52, 0x0003, 0x0000, (unsigned int)g_earlierMenuPaged394, 0x00000000, (unsigned int)g_earlierMenuPaged353, (unsigned int)g_earlierMenuPaged386, 0x0002, 0x0000, 0x0000, 0x0000, 0x00000000 };

struct MenuBuildDefinitionData g_earlierMenuDef121 = { (unsigned int)g_earlierMenuItems53, 0x0003, 0x0000, (unsigned int)g_earlierMenuPaged394, 0x00000000, (unsigned int)g_earlierMenuPaged353, (unsigned int)g_earlierMenuPaged386, 0x0002, 0x0000, 0x0000, 0x0000, 0x00000000 };

struct MenuBuildDefinitionData g_earlierMenuDef122 = { (unsigned int)g_earlierMenuItems54, 0x0003, 0x0000, (unsigned int)g_earlierMenuPaged394, 0x00000000, (unsigned int)g_earlierMenuPaged353, (unsigned int)g_earlierMenuPaged386, 0x0002, 0x0000, 0x0000, 0x0000, 0x00000000 };

struct MenuBuildDefinitionData g_earlierMenuDef123 = { (unsigned int)g_earlierMenuItems55, 0x0003, 0x0000, (unsigned int)g_earlierMenuPaged394, 0x00000000, (unsigned int)g_earlierMenuPaged353, (unsigned int)g_earlierMenuPaged386, 0x0002, 0x0000, 0x0000, 0x0000, 0x00000000 };

struct MenuBuildDefinitionData g_earlierMenuDef124 = { (unsigned int)g_earlierMenuItems52, 0x0003, 0x0000, (unsigned int)g_earlierMenuPaged397, 0x00000000, (unsigned int)g_earlierMenuPaged353, 0x00000000, 0x000E, 0x0000, 0x0000, 0x0000, 0x00000000 };

struct MenuBuildDefinitionData g_earlierMenuDef125 = { (unsigned int)g_earlierMenuItems53, 0x0003, 0x0000, (unsigned int)g_earlierMenuPaged397, 0x00000000, (unsigned int)g_earlierMenuPaged353, 0x00000000, 0x000E, 0x0000, 0x0000, 0x0000, 0x00000000 };

struct MenuBuildDefinitionData g_earlierMenuDef126 = { (unsigned int)g_earlierMenuItems54, 0x0003, 0x0000, (unsigned int)g_earlierMenuPaged397, 0x00000000, (unsigned int)g_earlierMenuPaged353, 0x00000000, 0x000E, 0x0000, 0x0000, 0x0000, 0x00000000 };

struct MenuBuildDefinitionData g_earlierMenuDef127 = { (unsigned int)g_earlierMenuItems55, 0x0003, 0x0000, (unsigned int)g_earlierMenuPaged397, 0x00000000, (unsigned int)g_earlierMenuPaged353, 0x00000000, 0x000E, 0x0000, 0x0000, 0x0000, 0x00000000 };

struct MenuBuildDefinitionData g_earlierMenuDef128 = { (unsigned int)g_earlierMenuItems52, 0x0003, 0x0000, (unsigned int)g_earlierMenuPaged402, 0x00000000, (unsigned int)g_earlierMenuPaged353, 0x00000000, 0x000E, 0x0000, 0x0000, 0x0000, 0x00000000 };

struct MenuBuildDefinitionData g_earlierMenuDef129 = { (unsigned int)g_earlierMenuItems53, 0x0003, 0x0000, (unsigned int)g_earlierMenuPaged402, 0x00000000, (unsigned int)g_earlierMenuPaged353, 0x00000000, 0x000E, 0x0000, 0x0000, 0x0000, 0x00000000 };

struct MenuBuildDefinitionData g_earlierMenuDef130 = { (unsigned int)g_earlierMenuItems54, 0x0003, 0x0000, (unsigned int)g_earlierMenuPaged402, 0x00000000, (unsigned int)g_earlierMenuPaged353, 0x00000000, 0x000E, 0x0000, 0x0000, 0x0000, 0x00000000 };

struct MenuBuildDefinitionData g_earlierMenuDef131 = { (unsigned int)g_earlierMenuItems55, 0x0003, 0x0000, (unsigned int)g_earlierMenuPaged402, 0x00000000, (unsigned int)g_earlierMenuPaged353, 0x00000000, 0x000E, 0x0000, 0x0000, 0x0000, 0x00000000 };

struct MenuBuildItemData g_earlierMenuItems56[17] = {
    { 0x0001, 0x0000, 0x50000000, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x00000385, (unsigned int)g_earlierMenuPaged347, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x08000021, 0x0000, 0x0008, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource296, (unsigned int)g_earlierMenuPaged354, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00400041, 0x0000, 0x002A, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource167, (unsigned int)g_earlierMenuPaged354, (unsigned int)g_earlierMenuPaged419, (unsigned int)g_earlierMenuPaged417, 0x00000000 },
    { 0x0000, 0x0000, 0x00410041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource168, (unsigned int)g_earlierMenuPaged354, (unsigned int)g_earlierMenuPaged423, (unsigned int)g_earlierMenuPaged421, 0x00000000 },
    { 0x0000, 0x0000, 0x00410041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource170, (unsigned int)g_earlierMenuPaged354, (unsigned int)g_earlierMenuPaged425, (unsigned int)g_earlierMenuPaged424, 0x00000000 },
    { 0x0000, 0x0000, 0x00410041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource171, (unsigned int)g_earlierMenuPaged354, (unsigned int)g_earlierMenuPaged429, (unsigned int)g_earlierMenuPaged427, 0x00000000 },
    { 0x0000, 0x0000, 0x00410041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource173, (unsigned int)g_earlierMenuPaged354, (unsigned int)g_earlierMenuPaged433, (unsigned int)g_earlierMenuPaged432, 0x00000000 },
    { 0x0000, 0x0000, 0x00410041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource174, (unsigned int)g_earlierMenuPaged354, (unsigned int)g_earlierMenuPaged435, (unsigned int)g_earlierMenuPaged434, 0x00000000 },
    { 0x0000, 0x0000, 0x00410041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource175, (unsigned int)g_earlierMenuPaged354, (unsigned int)g_earlierMenuPaged437, (unsigned int)g_earlierMenuPaged436, 0x00000000 },
    { 0x0000, 0x0000, 0x00410041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource178, (unsigned int)g_earlierMenuPaged354, (unsigned int)g_earlierMenuPaged439, (unsigned int)g_earlierMenuPaged440, 0x00000000 },
    { 0x0000, 0x0000, 0x00410041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource180, (unsigned int)g_earlierMenuPaged354, (unsigned int)g_earlierMenuPaged443, (unsigned int)g_earlierMenuPaged441, 0x00000000 },
    { 0x0000, 0x0000, 0x00410041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource182, (unsigned int)g_earlierMenuPaged354, (unsigned int)g_earlierMenuPaged446, (unsigned int)g_earlierMenuPaged445, 0x00000000 },
    { 0x0000, 0x0000, 0x00410041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource183, (unsigned int)g_earlierMenuPaged354, (unsigned int)g_earlierMenuPaged447, (unsigned int)g_earlierMenuPaged449, 0x00000000 },
    { 0x0000, 0x0000, 0x00410041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource184, (unsigned int)g_earlierMenuPaged354, (unsigned int)g_earlierMenuPaged450, (unsigned int)g_earlierMenuPaged452, 0x00000000 },
    { 0x0000, 0x0000, 0x00410041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource188, (unsigned int)g_earlierMenuPaged354, (unsigned int)g_earlierMenuPaged455, (unsigned int)g_earlierMenuPaged453, 0x00000000 },
    { 0x0000, 0x0000, 0x00410041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource189, (unsigned int)g_earlierMenuPaged354, (unsigned int)g_earlierMenuPaged457, (unsigned int)g_earlierMenuPaged456, 0x00000000 },
    { 0x0000, 0x0000, 0x00010201, 0x0000, 0x0013, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource190, (unsigned int)g_earlierMenuPaged354, 0x00000000, (unsigned int)g_earlierMenuPaged356, 0x00000000 },
};

struct MenuBuildDefinitionData g_earlierMenuDef132 = { (unsigned int)g_earlierMenuItems56, 0x0011, 0x0000, (unsigned int)g_earlierMenuPaged415, 0x00000000, (unsigned int)g_earlierMenuPaged353, 0x00000000, 0x0010, 0x0000, 0x0000, 0x0000, 0x00000000 };

unsigned int g_earlierMenuWords7[2] = { 0x00000000, 0x00000000 };

struct MenuBuildItemData g_earlierMenuItems57[5] = {
    { 0x0001, 0x0000, 0x50000000, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x00000385, (unsigned int)g_earlierMenuPaged347, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x08000041, 0x0000, 0x0008, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource217, (unsigned int)g_earlierMenuPaged354, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00000101, 0x0000, 0x005D, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource258, (unsigned int)g_earlierMenuPaged354, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00010101, 0x0000, 0x000A, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource259, (unsigned int)g_earlierMenuPaged354, 0x00000000, (unsigned int)g_earlierMenuPaged458, 0x00000000 },
    { 0x0000, 0x0000, 0x00010101, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource260, (unsigned int)g_earlierMenuPaged354, 0x00000000, (unsigned int)g_earlierMenuPaged356, 0x00000000 },
};

struct MenuBuildDefinitionData g_earlierMenuDef133 = { (unsigned int)g_earlierMenuItems57, 0x0005, 0x0000, (unsigned int)g_earlierMenuPaged459, 0x00000000, (unsigned int)g_earlierMenuPaged353, 0x00000000, 0x0004, 0x0000, 0x0000, 0x0000, (intptr_t)&g_earlierMenuDef135 };

struct MenuBuildItemData g_earlierMenuItems58[7] = {
    { 0x0001, 0x0000, 0x50000000, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x00000385, (unsigned int)g_earlierMenuPaged347, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x08002001, 0x0000, 0x0008, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource298, (unsigned int)g_earlierMenuPaged354, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00410041, 0x0000, 0x0032, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource300, (unsigned int)g_earlierMenuPaged354, (unsigned int)g_earlierMenuPaged472, (unsigned int)g_earlierMenuPaged471, 0x00000000 },
    { 0x0000, 0x0000, 0x00410041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource302, (unsigned int)g_earlierMenuPaged354, (unsigned int)g_earlierMenuPaged474, (unsigned int)g_earlierMenuPaged473, 0x00000000 },
    { 0x0000, 0x0000, 0x00410041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource305, (unsigned int)g_earlierMenuPaged354, (unsigned int)g_earlierMenuPaged470, (unsigned int)g_earlierMenuPaged469, 0x00000000 },
    { 0x0000, 0x0000, 0x00410041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource306, (unsigned int)g_earlierMenuPaged354, (unsigned int)g_earlierMenuPaged476, (unsigned int)g_earlierMenuPaged475, 0x00000000 },
    { 0x0000, 0x0000, 0x00410401, 0x0000, 0x0044, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource190, (unsigned int)g_earlierMenuPaged354, 0x00000000, (unsigned int)g_earlierMenuPaged468, 0x00000000 },
};

struct MenuBuildDefinitionData g_earlierMenuDef134 = { (unsigned int)g_earlierMenuItems58, 0x0007, 0x0000, 0x00000000, 0x00000000, (unsigned int)g_earlierMenuPaged353, 0x00000000, 0x0002, 0x0000, 0x0000, 0x0000, 0x00000000 };

struct MenuBuildItemData g_earlierMenuItems59[11] = {
    { 0x0001, 0x0000, 0x50000000, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x00000385, (unsigned int)g_earlierMenuPaged347, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x08000041, 0x0000, 0x0008, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource209, (unsigned int)g_earlierMenuPaged354, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0028, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource210, (unsigned int)g_earlierMenuPaged354, 0x00000000, (unsigned int)g_earlierMenuPaged460, 0x00000000 },
    { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource211, (unsigned int)g_earlierMenuPaged354, 0x00000000, (unsigned int)g_earlierMenuPaged461, 0x00000000 },
    { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource212, (unsigned int)g_earlierMenuPaged354, 0x00000000, (unsigned int)g_earlierMenuPaged462, 0x00000000 },
    { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource213, (unsigned int)g_earlierMenuPaged354, 0x00000000, (unsigned int)g_earlierMenuPaged463, 0x00000000 },
    { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource215, (unsigned int)g_earlierMenuPaged354, 0x00000000, (unsigned int)g_earlierMenuPaged464, 0x00000000 },
    { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource298, (unsigned int)g_earlierMenuPaged354, 0x00000000, (unsigned int)g_earlierMenuPaged477, 0x00000000 },
    { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource262, (unsigned int)g_earlierMenuPaged354, 0x00000000, (unsigned int)g_earlierMenuPaged465, 0x00000000 },
    { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource216, (unsigned int)g_earlierMenuPaged354, 0x00000000, (unsigned int)g_earlierMenuPaged466, 0x00000000 },
    { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource217, (unsigned int)g_earlierMenuPaged354, 0x00000000, (unsigned int)g_earlierMenuPaged467, 0x00000000 },
};

struct MenuBuildDefinitionData g_earlierMenuDef135 = { (unsigned int)g_earlierMenuItems59, 0x000B, 0x0000, (unsigned int)g_earlierMenuPaged478, (unsigned int)g_earlierMenuPaged479, (unsigned int)g_earlierMenuPaged480, 0x00000000, 0x0002, 0x0000, 0x0000, 0x0000, 0x00000000 };

unsigned int g_earlierMenuWords8[2] = { 0x00000000, 0x10E00001 };

struct MenuBuildItemData g_earlierMenuItems60[45] = {
    { 0x0000, 0x0000, 0x00000041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource255, (unsigned int)g_earlierMenuPaged354, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00210101, 0x0000, 0x0008, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource398, (unsigned int)g_earlierMenuPaged484, (unsigned int)g_earlierMenuPaged482, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00210101, 0x0000, 0x0008, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource399, (unsigned int)g_earlierMenuPaged484, (unsigned int)g_earlierMenuPaged482, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00210101, 0x0000, 0x0008, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource400, (unsigned int)g_earlierMenuPaged484, (unsigned int)g_earlierMenuPaged482, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00210101, 0x0000, 0x0008, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource401, (unsigned int)g_earlierMenuPaged484, (unsigned int)g_earlierMenuPaged482, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00010110, 0x0000, 0x000A, 0x07, 0x01, 0x20, 0x08, (int)g_earlierMenuResource318, (unsigned int)g_earlierMenuPaged355, 0x00000000, (unsigned int)g_earlierMenuPaged483, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0x20, 0x08, (int)g_earlierMenuResource320, (unsigned int)g_earlierMenuPaged355, 0x00000000, (unsigned int)g_earlierMenuPaged483, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0x20, 0x08, (int)g_earlierMenuResource322, (unsigned int)g_earlierMenuPaged355, 0x00000000, (unsigned int)g_earlierMenuPaged483, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0x20, 0x08, (int)g_earlierMenuResource324, (unsigned int)g_earlierMenuPaged355, 0x00000000, (unsigned int)g_earlierMenuPaged483, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0x20, 0x08, (int)g_earlierMenuResource326, (unsigned int)g_earlierMenuPaged355, 0x00000000, (unsigned int)g_earlierMenuPaged483, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0x20, 0x08, (int)g_earlierMenuResource328, (unsigned int)g_earlierMenuPaged355, 0x00000000, (unsigned int)g_earlierMenuPaged483, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0x20, 0x08, (int)g_earlierMenuResource330, (unsigned int)g_earlierMenuPaged355, 0x00000000, (unsigned int)g_earlierMenuPaged483, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0xF9, 0x20, 0x08, (int)g_earlierMenuResource332, (unsigned int)g_earlierMenuPaged355, 0x00000000, (unsigned int)g_earlierMenuPaged483, 0x00000000 },
    { 0x0000, 0x0000, 0x00010110, 0x0000, 0x0004, 0x07, 0x01, 0xF8, 0x08, (int)g_earlierMenuResource334, (unsigned int)g_earlierMenuPaged355, 0x00000000, (unsigned int)g_earlierMenuPaged483, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0xF8, 0x08, (int)g_earlierMenuResource336, (unsigned int)g_earlierMenuPaged355, 0x00000000, (unsigned int)g_earlierMenuPaged483, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0xF8, 0x08, (int)g_earlierMenuResource338, (unsigned int)g_earlierMenuPaged355, 0x00000000, (unsigned int)g_earlierMenuPaged483, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0xF8, 0x08, (int)g_earlierMenuResource340, (unsigned int)g_earlierMenuPaged355, 0x00000000, (unsigned int)g_earlierMenuPaged483, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0xF8, 0x08, (int)g_earlierMenuResource342, (unsigned int)g_earlierMenuPaged355, 0x00000000, (unsigned int)g_earlierMenuPaged483, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0xF8, 0x08, (int)g_earlierMenuResource344, (unsigned int)g_earlierMenuPaged355, 0x00000000, (unsigned int)g_earlierMenuPaged483, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0xF8, 0x08, (int)g_earlierMenuResource346, (unsigned int)g_earlierMenuPaged355, 0x00000000, (unsigned int)g_earlierMenuPaged483, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0xF9, 0xF8, 0x08, (int)g_earlierMenuResource348, (unsigned int)g_earlierMenuPaged355, 0x00000000, (unsigned int)g_earlierMenuPaged483, 0x00000000 },
    { 0x0000, 0x0000, 0x00010110, 0x0000, 0x0004, 0x07, 0x01, 0xF8, 0x08, (int)g_earlierMenuResource350, (unsigned int)g_earlierMenuPaged355, 0x00000000, (unsigned int)g_earlierMenuPaged483, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0xF8, 0x08, (int)g_earlierMenuResource352, (unsigned int)g_earlierMenuPaged355, 0x00000000, (unsigned int)g_earlierMenuPaged483, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0xF8, 0x08, (int)g_earlierMenuResource354, (unsigned int)g_earlierMenuPaged355, 0x00000000, (unsigned int)g_earlierMenuPaged483, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0xF8, 0x08, (int)g_earlierMenuResource356, (unsigned int)g_earlierMenuPaged355, 0x00000000, (unsigned int)g_earlierMenuPaged483, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0xF8, 0x08, (int)g_earlierMenuResource358, (unsigned int)g_earlierMenuPaged355, 0x00000000, (unsigned int)g_earlierMenuPaged483, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0xF8, 0x08, (int)g_earlierMenuResource360, (unsigned int)g_earlierMenuPaged355, 0x00000000, (unsigned int)g_earlierMenuPaged483, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0xF8, 0x08, (int)g_earlierMenuResource362, (unsigned int)g_earlierMenuPaged355, 0x00000000, (unsigned int)g_earlierMenuPaged483, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0xF9, 0xF8, 0x08, (int)g_earlierMenuResource364, (unsigned int)g_earlierMenuPaged355, 0x00000000, (unsigned int)g_earlierMenuPaged483, 0x00000000 },
    { 0x0000, 0x0000, 0x00010110, 0x0000, 0x0004, 0x07, 0x01, 0xF8, 0x08, (int)g_earlierMenuResource366, (unsigned int)g_earlierMenuPaged355, 0x00000000, (unsigned int)g_earlierMenuPaged483, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0xF8, 0x08, (int)g_earlierMenuResource368, (unsigned int)g_earlierMenuPaged355, 0x00000000, (unsigned int)g_earlierMenuPaged483, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0xF8, 0x08, (int)g_earlierMenuResource370, (unsigned int)g_earlierMenuPaged355, 0x00000000, (unsigned int)g_earlierMenuPaged483, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0xF8, 0x08, (int)g_earlierMenuResource372, (unsigned int)g_earlierMenuPaged355, 0x00000000, (unsigned int)g_earlierMenuPaged483, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0xF8, 0x08, (int)g_earlierMenuResource374, (unsigned int)g_earlierMenuPaged355, 0x00000000, (unsigned int)g_earlierMenuPaged483, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0xF8, 0x08, (int)g_earlierMenuResource376, (unsigned int)g_earlierMenuPaged355, 0x00000000, (unsigned int)g_earlierMenuPaged483, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0xF8, 0x08, (int)g_earlierMenuResource378, (unsigned int)g_earlierMenuPaged355, 0x00000000, (unsigned int)g_earlierMenuPaged483, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0xF9, 0xF8, 0x08, (int)g_earlierMenuResource380, (unsigned int)g_earlierMenuPaged355, 0x00000000, (unsigned int)g_earlierMenuPaged483, 0x00000000 },
    { 0x0000, 0x0000, 0x00010110, 0x0000, 0x0004, 0x07, 0x01, 0xF8, 0xE0, (int)g_earlierMenuResource382, (unsigned int)g_earlierMenuPaged355, 0x00000000, (unsigned int)g_earlierMenuPaged483, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0xF8, 0xE0, (int)g_earlierMenuResource384, (unsigned int)g_earlierMenuPaged355, 0x00000000, (unsigned int)g_earlierMenuPaged483, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0xF8, 0xE0, (int)g_earlierMenuResource386, (unsigned int)g_earlierMenuPaged355, 0x00000000, (unsigned int)g_earlierMenuPaged483, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0xF8, 0xE0, (int)g_earlierMenuResource388, (unsigned int)g_earlierMenuPaged355, 0x00000000, (unsigned int)g_earlierMenuPaged483, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0xF8, 0xE0, (int)g_earlierMenuResource308, (unsigned int)g_earlierMenuPaged355, 0x00000000, (unsigned int)g_earlierMenuPaged483, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0xF8, 0xE0, (int)g_earlierMenuResource390, (unsigned int)g_earlierMenuPaged355, 0x00000000, (unsigned int)g_earlierMenuPaged483, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0xF8, 0xE0, (int)g_earlierMenuResource391, (unsigned int)g_earlierMenuPaged355, 0x00000000, (unsigned int)g_earlierMenuPaged485, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0xF9, 0xF8, 0xE0, (int)g_earlierMenuResource392, (unsigned int)g_earlierMenuPaged355, 0x00000000, (unsigned int)g_earlierMenuPaged486, 0x00000000 },
};

struct MenuBuildDefinitionData g_earlierMenuDef136 = { (unsigned int)g_earlierMenuItems60, 0x002D, 0x0000, (unsigned int)g_earlierMenuPaged481, 0x00000000, (unsigned int)g_earlierMenuPaged353, (unsigned int)g_earlierMenuPaged487, 0x0005, 0x0000, 0x0000, 0x0000, 0x00000000 };

unsigned int g_earlierMenuWords9[3] = { 0x00000000, 0x00000000, 0x00000000 };

struct MenuBuildItemData g_earlierMenuItems61[11] = {
    { 0x0000, 0x0000, 0x00000401, 0x0000, 0x0028, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource281, (unsigned int)g_earlierMenuPaged354, (unsigned int)g_earlierMenuPaged373, 0x00000000, 0x00000000 },
    { 0x0001, 0x0000, 0x20010001, 0x0000, 0x0000, 0x00, 0x00, 0x00, 0x01, 0x0000012D, (unsigned int)g_earlierMenuPaged382, 0x00000000, (unsigned int)g_earlierMenuPaged380, 0x00000000 },
    { 0x0001, 0x0000, 0x50000000, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x00000385, (unsigned int)g_earlierMenuPaged347, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00000401, 0x0000, 0x0028, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource283, (unsigned int)g_earlierMenuPaged354, (unsigned int)g_earlierMenuPaged373, 0x00000000, 0x00000000 },
    { 0x0001, 0x0000, 0x20010001, -20, 0x0000, 0xEC, 0x00, 0x00, 0x01, 0x0000012D, (unsigned int)g_earlierMenuPaged382, 0x00000000, (unsigned int)g_earlierMenuPaged380, 0x00000000 },
    { 0x0001, 0x0000, 0x50000000, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x00000385, (unsigned int)g_earlierMenuPaged347, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00000401, 0x0000, 0x0028, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource285, (unsigned int)g_earlierMenuPaged354, (unsigned int)g_earlierMenuPaged373, 0x00000000, 0x00000000 },
    { 0x0001, 0x0000, 0x20010001, 0x0000, 0x0000, 0x00, 0x00, 0x00, 0x01, 0x0000012D, (unsigned int)g_earlierMenuPaged382, 0x00000000, (unsigned int)g_earlierMenuPaged380, 0x00000000 },
    { 0x0001, 0x0000, 0x50000000, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x00000385, (unsigned int)g_earlierMenuPaged347, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00000401, 0x0000, 0x0028, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource287, (unsigned int)g_earlierMenuPaged354, (unsigned int)g_earlierMenuPaged373, 0x00000000, 0x00000000 },
    { 0x0001, 0x0000, 0x20010001, 0x0000, 0x0000, 0x00, 0x00, 0x00, 0x01, 0x0000012D, (unsigned int)g_earlierMenuPaged382, 0x00000000, (unsigned int)g_earlierMenuPaged380, 0x00000000 },
};

struct MenuBuildDefinitionData g_earlierMenuDef137 = { (unsigned int)g_earlierMenuItems52, 0x0003, 0x0000, (unsigned int)g_earlierMenuPaged394, 0x00000000, (unsigned int)g_earlierMenuPaged353, (unsigned int)g_earlierMenuPaged386, 0x0002, 0x0000, 0x0000, 0x0000, 0x00000000 };

struct MenuBuildDefinitionData g_earlierMenuDef138 = { (unsigned int)g_earlierMenuItems53, 0x0003, 0x0000, (unsigned int)g_earlierMenuPaged394, 0x00000000, (unsigned int)g_earlierMenuPaged353, (unsigned int)g_earlierMenuPaged386, 0x0002, 0x0000, 0x0000, 0x0000, 0x00000000 };

struct MenuBuildDefinitionData g_earlierMenuDef139 = { (unsigned int)g_earlierMenuItems54, 0x0003, 0x0000, (unsigned int)g_earlierMenuPaged394, 0x00000000, (unsigned int)g_earlierMenuPaged353, (unsigned int)g_earlierMenuPaged386, 0x0002, 0x0000, 0x0000, 0x0000, 0x00000000 };

struct MenuBuildDefinitionData g_earlierMenuDef140 = { (unsigned int)g_earlierMenuItems55, 0x0003, 0x0000, (unsigned int)g_earlierMenuPaged394, 0x00000000, (unsigned int)g_earlierMenuPaged353, (unsigned int)g_earlierMenuPaged386, 0x0002, 0x0000, 0x0000, 0x0000, 0x00000000 };

struct MenuBuildDefinitionData g_earlierMenuDef141 = { (unsigned int)g_earlierMenuItems52, 0x0003, 0x0000, (unsigned int)g_earlierMenuPaged397, 0x00000000, (unsigned int)g_earlierMenuPaged353, 0x00000000, 0x000E, 0x0000, 0x0000, 0x0000, 0x00000000 };

struct MenuBuildDefinitionData g_earlierMenuDef142 = { (unsigned int)g_earlierMenuItems53, 0x0003, 0x0000, (unsigned int)g_earlierMenuPaged397, 0x00000000, (unsigned int)g_earlierMenuPaged353, 0x00000000, 0x000E, 0x0000, 0x0000, 0x0000, 0x00000000 };

struct MenuBuildDefinitionData g_earlierMenuDef143 = { (unsigned int)g_earlierMenuItems54, 0x0003, 0x0000, (unsigned int)g_earlierMenuPaged397, 0x00000000, (unsigned int)g_earlierMenuPaged353, 0x00000000, 0x000E, 0x0000, 0x0000, 0x0000, 0x00000000 };

struct MenuBuildDefinitionData g_earlierMenuDef144 = { (unsigned int)g_earlierMenuItems55, 0x0003, 0x0000, (unsigned int)g_earlierMenuPaged397, 0x00000000, (unsigned int)g_earlierMenuPaged353, 0x00000000, 0x000E, 0x0000, 0x0000, 0x0000, 0x00000000 };

struct MenuBuildDefinitionData g_earlierMenuDef145 = { (unsigned int)g_earlierMenuItems52, 0x0003, 0x0000, (unsigned int)g_earlierMenuPaged402, 0x00000000, (unsigned int)g_earlierMenuPaged353, 0x00000000, 0x000E, 0x0000, 0x0000, 0x0000, 0x00000000 };

struct MenuBuildDefinitionData g_earlierMenuDef146 = { (unsigned int)g_earlierMenuItems53, 0x0003, 0x0000, (unsigned int)g_earlierMenuPaged402, 0x00000000, (unsigned int)g_earlierMenuPaged353, 0x00000000, 0x000E, 0x0000, 0x0000, 0x0000, 0x00000000 };

struct MenuBuildDefinitionData g_earlierMenuDef147 = { (unsigned int)g_earlierMenuItems54, 0x0003, 0x0000, (unsigned int)g_earlierMenuPaged402, 0x00000000, (unsigned int)g_earlierMenuPaged353, 0x00000000, 0x000E, 0x0000, 0x0000, 0x0000, 0x00000000 };

struct MenuBuildDefinitionData g_earlierMenuDef148 = { (unsigned int)g_earlierMenuItems55, 0x0003, 0x0000, (unsigned int)g_earlierMenuPaged402, 0x00000000, (unsigned int)g_earlierMenuPaged353, 0x00000000, 0x000E, 0x0000, 0x0000, 0x0000, 0x00000000 };

struct MenuBuildItemData g_earlierMenuItems62[17] = {
    { 0x0001, 0x0000, 0x50000000, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x00000385, (unsigned int)g_earlierMenuPaged347, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x08000021, 0x0000, 0x0008, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource295, (unsigned int)g_earlierMenuPaged354, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00400041, 0x0000, 0x002A, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource166, (unsigned int)g_earlierMenuPaged354, (unsigned int)g_earlierMenuPaged419, (unsigned int)g_earlierMenuPaged417, 0x00000000 },
    { 0x0000, 0x0000, 0x00410041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource167, (unsigned int)g_earlierMenuPaged354, (unsigned int)g_earlierMenuPaged423, (unsigned int)g_earlierMenuPaged421, 0x00000000 },
    { 0x0000, 0x0000, 0x00410041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource168, (unsigned int)g_earlierMenuPaged354, (unsigned int)g_earlierMenuPaged425, (unsigned int)g_earlierMenuPaged424, 0x00000000 },
    { 0x0000, 0x0000, 0x00410041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource169, (unsigned int)g_earlierMenuPaged354, (unsigned int)g_earlierMenuPaged429, (unsigned int)g_earlierMenuPaged427, 0x00000000 },
    { 0x0000, 0x0000, 0x00410041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource171, (unsigned int)g_earlierMenuPaged354, (unsigned int)g_earlierMenuPaged433, (unsigned int)g_earlierMenuPaged432, 0x00000000 },
    { 0x0000, 0x0000, 0x00410041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource172, (unsigned int)g_earlierMenuPaged354, (unsigned int)g_earlierMenuPaged435, (unsigned int)g_earlierMenuPaged434, 0x00000000 },
    { 0x0000, 0x0000, 0x00410041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource174, (unsigned int)g_earlierMenuPaged354, (unsigned int)g_earlierMenuPaged437, (unsigned int)g_earlierMenuPaged436, 0x00000000 },
    { 0x0000, 0x0000, 0x00410041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource176, (unsigned int)g_earlierMenuPaged354, (unsigned int)g_earlierMenuPaged439, (unsigned int)g_earlierMenuPaged440, 0x00000000 },
    { 0x0000, 0x0000, 0x00410041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource177, (unsigned int)g_earlierMenuPaged354, (unsigned int)g_earlierMenuPaged443, (unsigned int)g_earlierMenuPaged441, 0x00000000 },
    { 0x0000, 0x0000, 0x00410041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource179, (unsigned int)g_earlierMenuPaged354, (unsigned int)g_earlierMenuPaged446, (unsigned int)g_earlierMenuPaged445, 0x00000000 },
    { 0x0000, 0x0000, 0x00410041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource181, (unsigned int)g_earlierMenuPaged354, (unsigned int)g_earlierMenuPaged447, (unsigned int)g_earlierMenuPaged449, 0x00000000 },
    { 0x0000, 0x0000, 0x00410041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource182, (unsigned int)g_earlierMenuPaged354, (unsigned int)g_earlierMenuPaged450, (unsigned int)g_earlierMenuPaged452, 0x00000000 },
    { 0x0000, 0x0000, 0x00410041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource185, (unsigned int)g_earlierMenuPaged354, (unsigned int)g_earlierMenuPaged455, (unsigned int)g_earlierMenuPaged453, 0x00000000 },
    { 0x0000, 0x0000, 0x00410041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource186, (unsigned int)g_earlierMenuPaged354, (unsigned int)g_earlierMenuPaged457, (unsigned int)g_earlierMenuPaged456, 0x00000000 },
    { 0x0000, 0x0000, 0x00010201, 0x0000, 0x0013, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource187, (unsigned int)g_earlierMenuPaged354, 0x00000000, (unsigned int)g_earlierMenuPaged356, 0x00000000 },
};

struct MenuBuildDefinitionData g_earlierMenuDef149 = { (unsigned int)g_earlierMenuItems56, 0x0011, 0x0000, (unsigned int)g_earlierMenuPaged415, 0x00000000, (unsigned int)g_earlierMenuPaged353, 0x00000000, 0x0010, 0x0000, 0x0000, 0x0000, 0x00000000 };

struct {
    char text0[8];
} g_earlierMenuWords10 = {
    "m_pAmmoI",
};

struct MenuBuildItemData g_earlierMenuItems63[5] = {
    { 0x0001, 0x0000, 0x50000000, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x00000385, (unsigned int)g_earlierMenuPaged347, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x08000041, 0x0000, 0x0008, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource214, (unsigned int)g_earlierMenuPaged354, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00000101, 0x0000, 0x005D, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource256, (unsigned int)g_earlierMenuPaged354, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00010101, 0x0000, 0x000A, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource257, (unsigned int)g_earlierMenuPaged354, 0x00000000, (unsigned int)g_earlierMenuPaged458, 0x00000000 },
    { 0x0000, 0x0000, 0x00010101, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource258, (unsigned int)g_earlierMenuPaged354, 0x00000000, (unsigned int)g_earlierMenuPaged356, 0x00000000 },
};

struct MenuBuildDefinitionData g_earlierMenuDef150 = { (unsigned int)g_earlierMenuItems57, 0x0005, 0x0000, (unsigned int)g_earlierMenuPaged459, 0x00000000, (unsigned int)g_earlierMenuPaged353, 0x00000000, 0x0004, 0x0000, 0x0000, 0x0000, (intptr_t)&g_earlierMenuDef135 };

struct MenuBuildItemData g_earlierMenuItems64[7] = {
    { 0x0001, 0x0000, 0x50000000, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x00000385, (unsigned int)g_earlierMenuPaged347, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x08002001, 0x0000, 0x0008, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource297, (unsigned int)g_earlierMenuPaged354, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00410041, 0x0000, 0x0032, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource299, (unsigned int)g_earlierMenuPaged354, (unsigned int)g_earlierMenuPaged472, (unsigned int)g_earlierMenuPaged471, 0x00000000 },
    { 0x0000, 0x0000, 0x00410041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource301, (unsigned int)g_earlierMenuPaged354, (unsigned int)g_earlierMenuPaged474, (unsigned int)g_earlierMenuPaged473, 0x00000000 },
    { 0x0000, 0x0000, 0x00410041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource303, (unsigned int)g_earlierMenuPaged354, (unsigned int)g_earlierMenuPaged470, (unsigned int)g_earlierMenuPaged469, 0x00000000 },
    { 0x0000, 0x0000, 0x00410041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource304, (unsigned int)g_earlierMenuPaged354, (unsigned int)g_earlierMenuPaged476, (unsigned int)g_earlierMenuPaged475, 0x00000000 },
    { 0x0000, 0x0000, 0x00410401, 0x0000, 0x0044, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource187, (unsigned int)g_earlierMenuPaged354, 0x00000000, (unsigned int)g_earlierMenuPaged468, 0x00000000 },
};

struct MenuBuildDefinitionData g_earlierMenuDef151 = { (unsigned int)g_earlierMenuItems58, 0x0007, 0x0000, 0x00000000, 0x00000000, (unsigned int)g_earlierMenuPaged353, 0x00000000, 0x0002, 0x0000, 0x0000, 0x0000, 0x00000000 };

struct MenuBuildItemData g_earlierMenuItems65[11] = {
    { 0x0001, 0x0000, 0x50000000, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, 0x00000385, (unsigned int)g_earlierMenuPaged347, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x08000041, 0x0000, 0x0008, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource206, (unsigned int)g_earlierMenuPaged354, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0028, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource207, (unsigned int)g_earlierMenuPaged354, 0x00000000, (unsigned int)g_earlierMenuPaged460, 0x00000000 },
    { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource208, (unsigned int)g_earlierMenuPaged354, 0x00000000, (unsigned int)g_earlierMenuPaged461, 0x00000000 },
    { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource209, (unsigned int)g_earlierMenuPaged354, 0x00000000, (unsigned int)g_earlierMenuPaged462, 0x00000000 },
    { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource210, (unsigned int)g_earlierMenuPaged354, 0x00000000, (unsigned int)g_earlierMenuPaged463, 0x00000000 },
    { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource212, (unsigned int)g_earlierMenuPaged354, 0x00000000, (unsigned int)g_earlierMenuPaged464, 0x00000000 },
    { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource297, (unsigned int)g_earlierMenuPaged354, 0x00000000, (unsigned int)g_earlierMenuPaged477, 0x00000000 },
    { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource261, (unsigned int)g_earlierMenuPaged354, 0x00000000, (unsigned int)g_earlierMenuPaged465, 0x00000000 },
    { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource213, (unsigned int)g_earlierMenuPaged354, 0x00000000, (unsigned int)g_earlierMenuPaged466, 0x00000000 },
    { 0x0000, 0x0000, 0x00010041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource214, (unsigned int)g_earlierMenuPaged354, 0x00000000, (unsigned int)g_earlierMenuPaged467, 0x00000000 },
};

struct MenuBuildDefinitionData g_earlierMenuDef152 = { (unsigned int)g_earlierMenuItems59, 0x000B, 0x0000, (unsigned int)g_earlierMenuPaged478, (unsigned int)g_earlierMenuPaged479, (unsigned int)g_earlierMenuPaged480, 0x00000000, 0x0002, 0x0000, 0x0000, 0x0000, 0x00000000 };

float g_earlierMenuFloats1[2] = { 3.1415927f, 1.5707964f };

struct MenuBuildItemData g_earlierMenuItems66[45] = {
    { 0x0000, 0x0000, 0x00000041, 0x0000, 0x0000, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource254, (unsigned int)g_earlierMenuPaged354, 0x00000000, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00210101, 0x0000, 0x0008, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource395, (unsigned int)g_earlierMenuPaged484, (unsigned int)g_earlierMenuPaged482, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00210101, 0x0000, 0x0008, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource396, (unsigned int)g_earlierMenuPaged484, (unsigned int)g_earlierMenuPaged482, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00210101, 0x0000, 0x0008, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource397, (unsigned int)g_earlierMenuPaged484, (unsigned int)g_earlierMenuPaged482, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00210101, 0x0000, 0x0008, 0x00, 0x00, 0xFF, 0x01, (int)g_earlierMenuResource398, (unsigned int)g_earlierMenuPaged484, (unsigned int)g_earlierMenuPaged482, 0x00000000, 0x00000000 },
    { 0x0000, 0x0000, 0x00010110, 0x0000, 0x000A, 0x07, 0x01, 0x20, 0x08, (int)g_earlierMenuResource315, (unsigned int)g_earlierMenuPaged355, 0x00000000, (unsigned int)g_earlierMenuPaged483, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0x20, 0x08, (int)g_earlierMenuResource316, (unsigned int)g_earlierMenuPaged355, 0x00000000, (unsigned int)g_earlierMenuPaged483, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0x20, 0x08, (int)g_earlierMenuResource317, (unsigned int)g_earlierMenuPaged355, 0x00000000, (unsigned int)g_earlierMenuPaged483, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0x20, 0x08, (int)g_earlierMenuResource319, (unsigned int)g_earlierMenuPaged355, 0x00000000, (unsigned int)g_earlierMenuPaged483, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0x20, 0x08, (int)g_earlierMenuResource321, (unsigned int)g_earlierMenuPaged355, 0x00000000, (unsigned int)g_earlierMenuPaged483, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0x20, 0x08, (int)g_earlierMenuResource323, (unsigned int)g_earlierMenuPaged355, 0x00000000, (unsigned int)g_earlierMenuPaged483, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0x20, 0x08, (int)g_earlierMenuResource325, (unsigned int)g_earlierMenuPaged355, 0x00000000, (unsigned int)g_earlierMenuPaged483, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0xF9, 0x20, 0x08, (int)g_earlierMenuResource327, (unsigned int)g_earlierMenuPaged355, 0x00000000, (unsigned int)g_earlierMenuPaged483, 0x00000000 },
    { 0x0000, 0x0000, 0x00010110, 0x0000, 0x0004, 0x07, 0x01, 0xF8, 0x08, (int)g_earlierMenuResource329, (unsigned int)g_earlierMenuPaged355, 0x00000000, (unsigned int)g_earlierMenuPaged483, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0xF8, 0x08, (int)g_earlierMenuResource331, (unsigned int)g_earlierMenuPaged355, 0x00000000, (unsigned int)g_earlierMenuPaged483, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0xF8, 0x08, (int)g_earlierMenuResource333, (unsigned int)g_earlierMenuPaged355, 0x00000000, (unsigned int)g_earlierMenuPaged483, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0xF8, 0x08, (int)g_earlierMenuResource335, (unsigned int)g_earlierMenuPaged355, 0x00000000, (unsigned int)g_earlierMenuPaged483, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0xF8, 0x08, (int)g_earlierMenuResource337, (unsigned int)g_earlierMenuPaged355, 0x00000000, (unsigned int)g_earlierMenuPaged483, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0xF8, 0x08, (int)g_earlierMenuResource339, (unsigned int)g_earlierMenuPaged355, 0x00000000, (unsigned int)g_earlierMenuPaged483, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0xF8, 0x08, (int)g_earlierMenuResource341, (unsigned int)g_earlierMenuPaged355, 0x00000000, (unsigned int)g_earlierMenuPaged483, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0xF9, 0xF8, 0x08, (int)g_earlierMenuResource343, (unsigned int)g_earlierMenuPaged355, 0x00000000, (unsigned int)g_earlierMenuPaged483, 0x00000000 },
    { 0x0000, 0x0000, 0x00010110, 0x0000, 0x0004, 0x07, 0x01, 0xF8, 0x08, (int)g_earlierMenuResource345, (unsigned int)g_earlierMenuPaged355, 0x00000000, (unsigned int)g_earlierMenuPaged483, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0xF8, 0x08, (int)g_earlierMenuResource347, (unsigned int)g_earlierMenuPaged355, 0x00000000, (unsigned int)g_earlierMenuPaged483, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0xF8, 0x08, (int)g_earlierMenuResource349, (unsigned int)g_earlierMenuPaged355, 0x00000000, (unsigned int)g_earlierMenuPaged483, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0xF8, 0x08, (int)g_earlierMenuResource351, (unsigned int)g_earlierMenuPaged355, 0x00000000, (unsigned int)g_earlierMenuPaged483, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0xF8, 0x08, (int)g_earlierMenuResource353, (unsigned int)g_earlierMenuPaged355, 0x00000000, (unsigned int)g_earlierMenuPaged483, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0xF8, 0x08, (int)g_earlierMenuResource355, (unsigned int)g_earlierMenuPaged355, 0x00000000, (unsigned int)g_earlierMenuPaged483, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0xF8, 0x08, (int)g_earlierMenuResource357, (unsigned int)g_earlierMenuPaged355, 0x00000000, (unsigned int)g_earlierMenuPaged483, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0xF9, 0xF8, 0x08, (int)g_earlierMenuResource359, (unsigned int)g_earlierMenuPaged355, 0x00000000, (unsigned int)g_earlierMenuPaged483, 0x00000000 },
    { 0x0000, 0x0000, 0x00010110, 0x0000, 0x0004, 0x07, 0x01, 0xF8, 0x08, (int)g_earlierMenuResource361, (unsigned int)g_earlierMenuPaged355, 0x00000000, (unsigned int)g_earlierMenuPaged483, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0xF8, 0x08, (int)g_earlierMenuResource363, (unsigned int)g_earlierMenuPaged355, 0x00000000, (unsigned int)g_earlierMenuPaged483, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0xF8, 0x08, (int)g_earlierMenuResource365, (unsigned int)g_earlierMenuPaged355, 0x00000000, (unsigned int)g_earlierMenuPaged483, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0xF8, 0x08, (int)g_earlierMenuResource367, (unsigned int)g_earlierMenuPaged355, 0x00000000, (unsigned int)g_earlierMenuPaged483, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0xF8, 0x08, (int)g_earlierMenuResource369, (unsigned int)g_earlierMenuPaged355, 0x00000000, (unsigned int)g_earlierMenuPaged483, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0xF8, 0x08, (int)g_earlierMenuResource371, (unsigned int)g_earlierMenuPaged355, 0x00000000, (unsigned int)g_earlierMenuPaged483, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0xF8, 0x08, (int)g_earlierMenuResource373, (unsigned int)g_earlierMenuPaged355, 0x00000000, (unsigned int)g_earlierMenuPaged483, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0xF9, 0xF8, 0x08, (int)g_earlierMenuResource375, (unsigned int)g_earlierMenuPaged355, 0x00000000, (unsigned int)g_earlierMenuPaged483, 0x00000000 },
    { 0x0000, 0x0000, 0x00010110, 0x0000, 0x0004, 0x07, 0x01, 0xF8, 0xE0, (int)g_earlierMenuResource377, (unsigned int)g_earlierMenuPaged355, 0x00000000, (unsigned int)g_earlierMenuPaged483, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0xF8, 0xE0, (int)g_earlierMenuResource379, (unsigned int)g_earlierMenuPaged355, 0x00000000, (unsigned int)g_earlierMenuPaged483, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0xF8, 0xE0, (int)g_earlierMenuResource381, (unsigned int)g_earlierMenuPaged355, 0x00000000, (unsigned int)g_earlierMenuPaged483, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0xF8, 0xE0, (int)g_earlierMenuResource383, (unsigned int)g_earlierMenuPaged355, 0x00000000, (unsigned int)g_earlierMenuPaged483, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0xF8, 0xE0, (int)g_earlierMenuResource307, (unsigned int)g_earlierMenuPaged355, 0x00000000, (unsigned int)g_earlierMenuPaged483, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0xF8, 0xE0, (int)g_earlierMenuResource385, (unsigned int)g_earlierMenuPaged355, 0x00000000, (unsigned int)g_earlierMenuPaged483, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0x01, 0xF8, 0xE0, (int)g_earlierMenuResource387, (unsigned int)g_earlierMenuPaged355, 0x00000000, (unsigned int)g_earlierMenuPaged485, 0x00000000 },
    { 0x0000, 0x0000, 0x00024110, 0x0006, 0x0000, 0xFF, 0xF9, 0xF8, 0xE0, (int)g_earlierMenuResource389, (unsigned int)g_earlierMenuPaged355, 0x00000000, (unsigned int)g_earlierMenuPaged486, 0x00000000 },
};

struct MenuBuildDefinitionData g_earlierMenuDef153 = { (unsigned int)g_earlierMenuItems60, 0x002D, 0x0000, (unsigned int)g_earlierMenuPaged481, 0x00000000, (unsigned int)g_earlierMenuPaged353, (unsigned int)g_earlierMenuPaged487, 0x0005, 0x0000, 0x0000, 0x0000, 0x00000000 };

#endif
