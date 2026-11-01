#if defined(VERSION_EU) || defined(VERSION_EU_X)
extern char g_earlierObjectTail_801707A4[];
extern char g_earlierObjectTemplate_801592F0[];
extern char g_earlierObjectTail_801707B4[];
extern char g_earlierObjectTemplate_80158C08[];
extern char g_earlierObjectTail_801707C4[];
extern char g_earlierObjectTail_801707D4[];
extern char g_earlierObjectLink_8015947C[];
extern char g_earlierObjectLink_80159484[];
extern char g_earlierObjectTemplate_80158FD0[];
extern char g_earlierObjectTail_801707E4[];
extern char g_earlierObjectLink_8015948C[];
extern char g_earlierObjectLink_80159494[];
extern char g_earlierObjectLink_80159574[];
extern char g_earlierObjectLink_8015957C[];
extern char g_earlierObjectTail_801707F4[];
extern char g_earlierObjectLink_8015949C[];
extern char g_earlierObjectLink_801594A4[];
extern char g_earlierObjectLink_80159584[];
extern char g_earlierObjectLink_8015958C[];
extern char g_earlierObjectTemplate_801590B0[];
extern char g_earlierObjectTail_80170804[];
extern char g_earlierObjectLink_801594AC[];
extern char g_earlierObjectLink_801594B4[];
extern char g_earlierObjectLink_80159594[];
extern char g_earlierObjectLink_8015959C[];
extern char g_earlierObjectTemplate_80159250[];
extern char g_earlierObjectTail_80170814[];
extern char g_earlierObjectLink_801594BC[];
extern char g_earlierObjectLink_801594C4[];
extern char g_earlierObjectLink_801595A4[];
extern char g_earlierObjectLink_801595AC[];
extern char g_earlierObjectTail_80170824[];
extern char g_earlierObjectLink_801594CC[];
extern char g_earlierObjectLink_801595B4[];
extern char g_earlierObjectTemplate_80158E8C[];
extern char g_earlierObjectTail_80170834[];
extern char g_earlierObjectLink_801594D4[];
extern char g_earlierObjectLink_801594DC[];
extern char g_earlierObjectLink_801595BC[];
extern char g_earlierObjectLink_801595C4[];
extern char g_earlierObjectTail_80170844[];
extern char g_earlierObjectLink_801594E4[];
extern char g_earlierObjectLink_801594EC[];
extern char g_earlierObjectLink_801595CC[];
extern char g_earlierObjectLink_801595D4[];
extern char g_earlierObjectTail_80170854[];
extern char g_earlierObjectLink_801594F4[];
extern char g_earlierObjectLink_801594FC[];
extern char g_earlierObjectLink_801595DC[];
extern char g_earlierObjectLink_801595E4[];
extern char g_earlierObjectTemplate_80159050[];
extern char g_earlierObjectTail_80170864[];
extern char g_earlierObjectLink_80159504[];
extern char g_earlierObjectLink_8015950C[];
extern char g_earlierObjectLink_801595EC[];
extern char g_earlierObjectLink_801595F4[];
extern char g_earlierObjectTemplate_80159150[];
extern char g_earlierObjectTail_80170874[];
extern char g_earlierObjectLink_80159514[];
extern char g_earlierObjectLink_801595FC[];
extern char g_earlierObjectTemplate_801593F4[];
extern char g_earlierObjectTail_80170884[];
extern char g_earlierObjectLink_8015951C[];
extern char g_earlierObjectLink_80159604[];
extern char g_earlierObjectTemplate_801591D0[];
extern char g_earlierObjectTail_80170894[];
extern char g_earlierObjectLink_80159524[];
extern char g_earlierObjectLink_8015952C[];
extern char g_earlierObjectLink_8015960C[];
extern char g_earlierObjectLink_80159614[];
extern char g_earlierObjectTemplate_80158F30[];
extern char g_earlierObjectTail_801708A4[];
extern char g_earlierObjectLink_80159534[];
extern char g_earlierObjectLink_8015953C[];
extern char g_earlierObjectLink_8015961C[];
extern char g_earlierObjectLink_80159624[];
extern char g_earlierObjectTemplate_80158D28[];
extern char g_earlierObjectTail_801708B4[];
extern char g_earlierObjectLink_80159544[];
extern char g_earlierObjectLink_8015954C[];
extern char g_earlierObjectLink_8015962C[];
extern char g_earlierObjectLink_80159634[];
extern char g_earlierObjectTemplate_80159354[];
extern char g_earlierObjectTail_801708C4[];
extern char g_earlierObjectLink_80159554[];
extern char g_earlierObjectLink_8015963C[];
extern char g_earlierObjectTail_801708D4[];
extern char g_earlierObjectLink_80159644[];
extern char g_earlierObjectLink_8015955C[];
extern char g_earlierObjectTail_801708E4[];
extern char g_earlierObjectLink_8015956C[];
extern char g_earlierObjectLink_80159654[];
extern char g_earlierObjectTail_80170904[];
extern char g_earlierObjectLink_80159564[];
extern char g_earlierObjectLink_8015964C[];
extern char g_earlierObjectTail_80170C24[];
extern char g_earlierObjectTail_80170C34[];
extern char g_earlierObjectTail_80170C44[];
extern char g_earlierObjectTail_80170C54[];
extern char g_earlierObjectTail_80170C64[];
extern char g_earlierObjectTail_80170C74[];
extern char g_earlierObjectTail_80170C84[];

typedef struct EarlierObjectRecord {
    void *tail;
    unsigned int key;
    short slot[6];
    unsigned int kind;
    unsigned int reserved0;
    float angle;
    void *linkA[2];
    unsigned int reserved1;
    void *linkB[2];
    unsigned int reserved2;
    float extent[3];
    float origin[2];
    float scale[2];
    void *templateData;
    unsigned int reserved3;
    unsigned int flags;
} EarlierObjectRecord;

EarlierObjectRecord g_earlierObjectRecords[22] = {
    {
        g_earlierObjectTail_801707A4,
        0x04C30BB8,
        { 0, -1, -1, -1, -1, 0 },
        3,
        0,
        0.0f,
        { 0, 0 },
        0,
        { 0, 0 },
        0,
        { 6.0f, 7.0f, 10.0f },
        { 0.0f, 0.0f },
        { 1.0f, 1.0f },
        g_earlierObjectTemplate_801592F0,
        0,
        0x00237D88,
    },
    {
        g_earlierObjectTail_801707B4,
        0x04D3FFFF,
        { 0, -1, -1, 0x02DA, 0x02DA, 0 },
        3,
        0,
        0.0f,
        { 0, 0 },
        0,
        { 0, 0 },
        0,
        { 6.0f, 7.0f, 10.0f },
        { 0.0f, 0.0f },
        { 1.0f, 1.0f },
        g_earlierObjectTemplate_80158C08,
        0,
        0x00000000,
    },
    {
        g_earlierObjectTail_801707C4,
        0x04D4FFFF,
        { 0, -1, -1, 0x02DA, 0x02DA, 0 },
        3,
        0,
        0.0f,
        { 0, 0 },
        0,
        { 0, 0 },
        0,
        { 6.0f, 7.0f, 10.0f },
        { 0.0f, 0.0f },
        { 1.0f, 1.0f },
        g_earlierObjectTemplate_80158C08,
        0,
        0x00000000,
    },
    {
        g_earlierObjectTail_801707D4,
        0x04C40BB9,
        { 0, -1, -1, 0x02F8, 0x02F9, 0 },
        3,
        0,
        0.87266463f,
        { g_earlierObjectLink_8015947C, g_earlierObjectLink_80159484 },
        0,
        { g_earlierObjectLink_8015947C, g_earlierObjectLink_80159484 },
        0,
        { 6.0f, 7.0f, 10.0f },
        { 0.0f, 0.0f },
        { 1.0f, 1.0f },
        g_earlierObjectTemplate_80158FD0,
        0,
        0x00236D64,
    },
    {
        g_earlierObjectTail_801707E4,
        0x04C50BBA,
        { 0x0C83, -1, -1, 0x02DA, 0x02DA, 0 },
        0x00000023,
        0,
        0.0f,
        { g_earlierObjectLink_8015948C, g_earlierObjectLink_80159494 },
        0,
        { g_earlierObjectLink_80159574, g_earlierObjectLink_8015957C },
        0,
        { 6.0f, 7.0f, 10.0f },
        { 0.0f, 0.0f },
        { 1.0f, 1.0f },
        g_earlierObjectTemplate_80158C08,
        0,
        0x00000000,
    },
    {
        g_earlierObjectTail_801707F4,
        0x04C60BBB,
        { 0, -1, -1, 0x02DA, 0x02DA, 0 },
        3,
        0,
        1.04719758f,
        { g_earlierObjectLink_8015949C, g_earlierObjectLink_801594A4 },
        0,
        { g_earlierObjectLink_80159584, g_earlierObjectLink_8015958C },
        0,
        { 6.0f, 7.0f, 10.0f },
        { 0.0f, 0.0f },
        { 1.0f, 1.0f },
        g_earlierObjectTemplate_801590B0,
        0,
        0x00000000,
    },
    {
        g_earlierObjectTail_80170804,
        0x04C70BBC,
        { 0, -1, -1, 0x02DA, 0x02DA, 0 },
        7,
        0,
        0.0f,
        { g_earlierObjectLink_801594AC, g_earlierObjectLink_801594B4 },
        0,
        { g_earlierObjectLink_80159594, g_earlierObjectLink_8015959C },
        0,
        { 6.0f, 7.0f, 10.0f },
        { 0.0f, 0.0f },
        { 1.0f, 1.0f },
        g_earlierObjectTemplate_80159250,
        0,
        0x00000000,
    },
    {
        g_earlierObjectTail_80170814,
        0x04C80BBD,
        { 0, -1, -1, 0x02DA, 0x02DA, 0 },
        3,
        0,
        0.0f,
        { g_earlierObjectLink_801594BC, g_earlierObjectLink_801594C4 },
        0,
        { g_earlierObjectLink_801595A4, g_earlierObjectLink_801595AC },
        0,
        { 6.0f, 7.0f, 10.0f },
        { 0.0f, 0.0f },
        { 1.0f, 1.0f },
        g_earlierObjectTemplate_80158C08,
        0,
        0x00000000,
    },
    {
        g_earlierObjectTail_80170824,
        0x04C90BBE,
        { 0, -1, -1, 0x02DA, 0x02DA, 0 },
        3,
        0,
        0.0f,
        { g_earlierObjectLink_801594CC, 0 },
        0,
        { g_earlierObjectLink_801595B4, 0 },
        0,
        { 6.0f, 7.0f, 10.0f },
        { 0.0f, 0.0f },
        { 1.0f, 1.0f },
        g_earlierObjectTemplate_80158E8C,
        0x00235ACC,
        0x0023600C,
    },
    {
        g_earlierObjectTail_80170834,
        0x04CA0BBF,
        { 0x0C83, -1, -1, 0x02DA, 0x02DA, 0 },
        0x00000027,
        0,
        0.0f,
        { g_earlierObjectLink_801594D4, g_earlierObjectLink_801594DC },
        0,
        { g_earlierObjectLink_801595BC, g_earlierObjectLink_801595C4 },
        0,
        { 6.0f, 7.0f, 10.0f },
        { 0.0f, 0.0f },
        { 1.0f, 1.0f },
        g_earlierObjectTemplate_80158C08,
        0,
        0x00000000,
    },
    {
        g_earlierObjectTail_80170844,
        0x04CB0BC0,
        { 0, -1, -1, 0x02DA, 0x02DA, 0 },
        3,
        0,
        0.0f,
        { g_earlierObjectLink_801594E4, g_earlierObjectLink_801594EC },
        0,
        { g_earlierObjectLink_801595CC, g_earlierObjectLink_801595D4 },
        0,
        { 6.0f, 7.0f, 10.0f },
        { 0.0f, 0.0f },
        { 1.0f, 1.0f },
        g_earlierObjectTemplate_80158C08,
        0,
        0x00000000,
    },
    {
        g_earlierObjectTail_80170854,
        0x04CC0BC1,
        { 0, -1, -1, 0x02DA, 0x02DA, 0 },
        3,
        0,
        0.0f,
        { g_earlierObjectLink_801594F4, g_earlierObjectLink_801594FC },
        0,
        { g_earlierObjectLink_801595DC, g_earlierObjectLink_801595E4 },
        0,
        { 6.0f, 7.0f, 10.0f },
        { 0.0f, 0.0f },
        { 1.0f, 1.0f },
        g_earlierObjectTemplate_80159050,
        0,
        0x00000000,
    },
    {
        g_earlierObjectTail_80170864,
        0x04CD0BC2,
        { 0, -1, -1, -1, -1, 0 },
        3,
        0,
        0.0f,
        { g_earlierObjectLink_80159504, g_earlierObjectLink_8015950C },
        0,
        { g_earlierObjectLink_801595EC, g_earlierObjectLink_801595F4 },
        0,
        { 6.0f, 7.0f, 10.0f },
        { 0.0f, 0.0f },
        { 1.0f, 1.0f },
        g_earlierObjectTemplate_80159150,
        0,
        0x00000000,
    },
    {
        g_earlierObjectTail_80170874,
        0x04CE0BC3,
        { 0, -1, -1, 0x02DA, 0x02DA, 0 },
        7,
        0,
        0.0f,
        { g_earlierObjectLink_80159514, 0 },
        0,
        { g_earlierObjectLink_801595FC, 0 },
        0,
        { 6.0f, 7.0f, 10.0f },
        { 0.0f, 0.0f },
        { 1.0f, 1.0f },
        g_earlierObjectTemplate_801593F4,
        0,
        0x00000000,
    },
    {
        g_earlierObjectTail_80170884,
        0x04CF0BC4,
        { 0, -1, -1, -1, -1, 0 },
        3,
        0,
        0.0f,
        { g_earlierObjectLink_8015951C, 0 },
        0,
        { g_earlierObjectLink_80159604, 0 },
        0,
        { 6.0f, 7.0f, 10.0f },
        { 0.0f, 0.0f },
        { 1.0f, 1.0f },
        g_earlierObjectTemplate_801591D0,
        0,
        0x00000000,
    },
    {
        g_earlierObjectTail_80170894,
        0x04D00BC5,
        { 0, -1, -1, 0x02DA, 0x02DA, 0 },
        3,
        0,
        0.0f,
        { g_earlierObjectLink_80159524, g_earlierObjectLink_8015952C },
        0,
        { g_earlierObjectLink_8015960C, g_earlierObjectLink_80159614 },
        0,
        { 6.0f, 7.0f, 10.0f },
        { 0.0f, 0.0f },
        { 1.0f, 1.0f },
        g_earlierObjectTemplate_80158F30,
        0x002362A4,
        0x002369C8,
    },
    {
        g_earlierObjectTail_801708A4,
        0x04D10BC6,
        { 0, -1, -1, 0x02DA, 0x02DA, 0 },
        3,
        0,
        0.0f,
        { g_earlierObjectLink_80159534, g_earlierObjectLink_8015953C },
        0,
        { g_earlierObjectLink_8015961C, g_earlierObjectLink_80159624 },
        0,
        { 6.0f, 7.0f, 10.0f },
        { 0.0f, 0.0f },
        { 1.0f, 1.0f },
        g_earlierObjectTemplate_80158D28,
        0,
        0x00237D88,
    },
    {
        g_earlierObjectTail_801708B4,
        0x04D20BC7,
        { 0, -1, -1, 0x02DA, 0x02DA, 0 },
        3,
        0,
        0.0f,
        { g_earlierObjectLink_80159544, g_earlierObjectLink_8015954C },
        0,
        { g_earlierObjectLink_8015962C, g_earlierObjectLink_80159634 },
        0,
        { 6.0f, 7.0f, 10.0f },
        { 0.0f, 0.0f },
        { 1.0f, 1.0f },
        g_earlierObjectTemplate_80159354,
        0x00238374,
        0x00000000,
    },
    {
        g_earlierObjectTail_801708C4,
        0x04D50BC8,
        { 0, -1, -1, 0x02C6, 0x02C7, 0 },
        3,
        0x40800000,
        0.785398185f,
        { g_earlierObjectLink_80159554, 0 },
        0,
        { g_earlierObjectLink_8015963C, 0 },
        0,
        { 6.0f, 7.0f, 10.0f },
        { 0.0f, 0.0f },
        { 1.0f, 1.0f },
        g_earlierObjectTemplate_80158C08,
        0,
        0x00000000,
    },
    {
        g_earlierObjectTail_801708D4,
        0x04D60BC9,
        { 0, -1, -1, 0x02DA, 0x02DA, 0 },
        3,
        0,
        0.0f,
        { g_earlierObjectLink_80159644, 0 },
        0,
        { g_earlierObjectLink_8015955C, 0 },
        0,
        { 6.0f, 7.0f, 10.0f },
        { 0.0f, 0.0f },
        { 1.0f, 1.0f },
        g_earlierObjectTemplate_80158C08,
        0,
        0x00000000,
    },
    {
        g_earlierObjectTail_801708E4,
        0x04D70BCA,
        { 0, -1, -1, 0x02DA, 0x02DA, 0 },
        3,
        0,
        0.0f,
        { g_earlierObjectLink_8015956C, 0 },
        0,
        { g_earlierObjectLink_80159654, 0 },
        0,
        { 6.0f, 7.0f, 10.0f },
        { 0.0f, 0.0f },
        { 1.0f, 1.0f },
        g_earlierObjectTemplate_80158C08,
        0,
        0x00000000,
    },
    {
        g_earlierObjectTail_80170904,
        0x04D90BCC,
        { 0, -1, -1, 0x02DA, 0x02DA, 0 },
        3,
        0,
        0.0f,
        { g_earlierObjectLink_80159564, 0 },
        0,
        { g_earlierObjectLink_8015964C, 0 },
        0,
        { 6.0f, 7.0f, 10.0f },
        { 0.0f, 0.0f },
        { 1.0f, 1.0f },
        g_earlierObjectTemplate_80158C08,
        0,
        0x00000000,
    },
};

EarlierObjectRecord *g_earlierObjectRecordTable[23] = {
    &g_earlierObjectRecords[0],
    &g_earlierObjectRecords[3],
    &g_earlierObjectRecords[4],
    &g_earlierObjectRecords[5],
    &g_earlierObjectRecords[6],
    &g_earlierObjectRecords[7],
    &g_earlierObjectRecords[8],
    &g_earlierObjectRecords[9],
    &g_earlierObjectRecords[10],
    &g_earlierObjectRecords[11],
    &g_earlierObjectRecords[12],
    &g_earlierObjectRecords[13],
    &g_earlierObjectRecords[14],
    &g_earlierObjectRecords[15],
    &g_earlierObjectRecords[16],
    &g_earlierObjectRecords[17],
    &g_earlierObjectRecords[1],
    &g_earlierObjectRecords[2],
    &g_earlierObjectRecords[18],
    &g_earlierObjectRecords[19],
    &g_earlierObjectRecords[20],
    &g_earlierObjectRecords[21],
    0,
};

short g_earlierObjectIdTable[8] = { 0x0BEA, 0x0BEB, 0x0BEC, -1, 0x0BED, 0x0BEE, 0x0BEF, 0x0BF0 };

void *g_earlierObjectTailTable[7] = {
    g_earlierObjectTail_80170C24,
    g_earlierObjectTail_80170C34,
    g_earlierObjectTail_80170C44,
    g_earlierObjectTail_80170C54,
    g_earlierObjectTail_80170C64,
    g_earlierObjectTail_80170C74,
    g_earlierObjectTail_80170C84,
};
#endif
