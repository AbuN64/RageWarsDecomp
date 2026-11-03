#if defined(VERSION_EU) || defined(VERSION_EU_X)
extern char g_earlierObjectRecord0Tail[];
extern char g_earlierObjectRecord0Template[];
extern char g_earlierObjectRecord1Tail[];
extern char g_earlierObjectRecord1Template[];
extern char g_earlierObjectRecord2Tail[];
extern char g_earlierObjectRecord3Tail[];
extern char g_earlierObjectRecord3Link[];
extern char g_earlierObjectRecord3Link2[];
extern char g_earlierObjectRecord3Template[];
extern char g_earlierObjectRecord4Tail[];
extern char g_earlierObjectRecord4Link[];
extern char g_earlierObjectRecord4Link2[];
extern char g_earlierObjectRecord4Link3[];
extern char g_earlierObjectRecord4Link4[];
extern char g_earlierObjectRecord5Tail[];
extern char g_earlierObjectRecord5Link[];
extern char g_earlierObjectRecord5Link2[];
extern char g_earlierObjectRecord5Link3[];
extern char g_earlierObjectRecord5Link4[];
extern char g_earlierObjectRecord5Template[];
extern char g_earlierObjectRecord6Tail[];
extern char g_earlierObjectRecord6Link[];
extern char g_earlierObjectRecord6Link2[];
extern char g_earlierObjectRecord6Link3[];
extern char g_earlierObjectRecord6Link4[];
extern char g_earlierObjectRecord6Template[];
extern char g_earlierObjectRecord7Tail[];
extern char g_earlierObjectRecord7Link[];
extern char g_earlierObjectRecord7Link2[];
extern char g_earlierObjectRecord7Link3[];
extern char g_earlierObjectRecord7Link4[];
extern char g_earlierObjectRecord8Tail[];
extern char g_earlierObjectRecord8Link[];
extern char g_earlierObjectRecord8Link2[];
extern char g_earlierObjectRecord8Template[];
extern char g_earlierObjectRecord9Tail[];
extern char g_earlierObjectRecord9Link[];
extern char g_earlierObjectRecord9Link2[];
extern char g_earlierObjectRecord9Link3[];
extern char g_earlierObjectRecord9Link4[];
extern char g_earlierObjectRecord10Tail[];
extern char g_earlierObjectRecord10Link[];
extern char g_earlierObjectRecord10Link2[];
extern char g_earlierObjectRecord10Link3[];
extern char g_earlierObjectRecord10Link4[];
extern char g_earlierObjectRecord11Tail[];
extern char g_earlierObjectRecord11Link[];
extern char g_earlierObjectRecord11Link2[];
extern char g_earlierObjectRecord11Link3[];
extern char g_earlierObjectRecord11Link4[];
extern char g_earlierObjectRecord11Template[];
extern char g_earlierObjectRecord12Tail[];
extern char g_earlierObjectRecord12Link[];
extern char g_earlierObjectRecord12Link2[];
extern char g_earlierObjectRecord12Link3[];
extern char g_earlierObjectRecord12Link4[];
extern char g_earlierObjectRecord12Template[];
extern char g_earlierObjectRecord13Tail[];
extern char g_earlierObjectRecord13Link[];
extern char g_earlierObjectRecord13Link2[];
extern char g_earlierObjectRecord13Template[];
extern char g_earlierObjectRecord14Tail[];
extern char g_earlierObjectRecord14Link[];
extern char g_earlierObjectRecord14Link2[];
extern char g_earlierObjectRecord14Template[];
extern char g_earlierObjectRecord15Tail[];
extern char g_earlierObjectRecord15Link[];
extern char g_earlierObjectRecord15Link2[];
extern char g_earlierObjectRecord15Link3[];
extern char g_earlierObjectRecord15Link4[];
extern char g_earlierObjectRecord15Template[];
extern char g_earlierObjectRecord16Tail[];
extern char g_earlierObjectRecord16Link[];
extern char g_earlierObjectRecord16Link2[];
extern char g_earlierObjectRecord16Link3[];
extern char g_earlierObjectRecord16Link4[];
extern char g_earlierObjectRecord16Template[];
extern char g_earlierObjectRecord17Tail[];
extern char g_earlierObjectRecord17Link[];
extern char g_earlierObjectRecord17Link2[];
extern char g_earlierObjectRecord17Link3[];
extern char g_earlierObjectRecord17Link4[];
extern char g_earlierObjectRecord17Template[];
extern char g_earlierObjectRecord18Tail[];
extern char g_earlierObjectRecord18Link[];
extern char g_earlierObjectRecord18Link2[];
extern char g_earlierObjectRecord19Tail[];
extern char g_earlierObjectRecord19Link2[];
extern char g_earlierObjectRecord19Link[];
extern char g_earlierObjectRecord20Tail[];
extern char g_earlierObjectRecord20Link[];
extern char g_earlierObjectRecord20Link2[];
extern char g_earlierObjectRecord21Tail[];
extern char g_earlierObjectRecord21Link[];
extern char g_earlierObjectRecord21Link2[];
extern char g_earlierObjectTailTableEntry0[];
extern char g_earlierObjectTailTableEntry1[];
extern char g_earlierObjectTailTableEntry2[];
extern char g_earlierObjectTailTableEntry3[];
extern char g_earlierObjectTailTableEntry4[];
extern char g_earlierObjectTailTableEntry5[];
extern char g_earlierObjectTailTableEntry6[];

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
        g_earlierObjectRecord0Tail,
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
        g_earlierObjectRecord0Template,
        0,
        0x00237D88,
    },
    {
        g_earlierObjectRecord1Tail,
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
        g_earlierObjectRecord1Template,
        0,
        0x00000000,
    },
    {
        g_earlierObjectRecord2Tail,
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
        g_earlierObjectRecord1Template,
        0,
        0x00000000,
    },
    {
        g_earlierObjectRecord3Tail,
        0x04C40BB9,
        { 0, -1, -1, 0x02F8, 0x02F9, 0 },
        3,
        0,
        0.87266463f,
        { g_earlierObjectRecord3Link, g_earlierObjectRecord3Link2 },
        0,
        { g_earlierObjectRecord3Link, g_earlierObjectRecord3Link2 },
        0,
        { 6.0f, 7.0f, 10.0f },
        { 0.0f, 0.0f },
        { 1.0f, 1.0f },
        g_earlierObjectRecord3Template,
        0,
        0x00236D64,
    },
    {
        g_earlierObjectRecord4Tail,
        0x04C50BBA,
        { 0x0C83, -1, -1, 0x02DA, 0x02DA, 0 },
        0x00000023,
        0,
        0.0f,
        { g_earlierObjectRecord4Link, g_earlierObjectRecord4Link2 },
        0,
        { g_earlierObjectRecord4Link3, g_earlierObjectRecord4Link4 },
        0,
        { 6.0f, 7.0f, 10.0f },
        { 0.0f, 0.0f },
        { 1.0f, 1.0f },
        g_earlierObjectRecord1Template,
        0,
        0x00000000,
    },
    {
        g_earlierObjectRecord5Tail,
        0x04C60BBB,
        { 0, -1, -1, 0x02DA, 0x02DA, 0 },
        3,
        0,
        1.04719758f,
        { g_earlierObjectRecord5Link, g_earlierObjectRecord5Link2 },
        0,
        { g_earlierObjectRecord5Link3, g_earlierObjectRecord5Link4 },
        0,
        { 6.0f, 7.0f, 10.0f },
        { 0.0f, 0.0f },
        { 1.0f, 1.0f },
        g_earlierObjectRecord5Template,
        0,
        0x00000000,
    },
    {
        g_earlierObjectRecord6Tail,
        0x04C70BBC,
        { 0, -1, -1, 0x02DA, 0x02DA, 0 },
        7,
        0,
        0.0f,
        { g_earlierObjectRecord6Link, g_earlierObjectRecord6Link2 },
        0,
        { g_earlierObjectRecord6Link3, g_earlierObjectRecord6Link4 },
        0,
        { 6.0f, 7.0f, 10.0f },
        { 0.0f, 0.0f },
        { 1.0f, 1.0f },
        g_earlierObjectRecord6Template,
        0,
        0x00000000,
    },
    {
        g_earlierObjectRecord7Tail,
        0x04C80BBD,
        { 0, -1, -1, 0x02DA, 0x02DA, 0 },
        3,
        0,
        0.0f,
        { g_earlierObjectRecord7Link, g_earlierObjectRecord7Link2 },
        0,
        { g_earlierObjectRecord7Link3, g_earlierObjectRecord7Link4 },
        0,
        { 6.0f, 7.0f, 10.0f },
        { 0.0f, 0.0f },
        { 1.0f, 1.0f },
        g_earlierObjectRecord1Template,
        0,
        0x00000000,
    },
    {
        g_earlierObjectRecord8Tail,
        0x04C90BBE,
        { 0, -1, -1, 0x02DA, 0x02DA, 0 },
        3,
        0,
        0.0f,
        { g_earlierObjectRecord8Link, 0 },
        0,
        { g_earlierObjectRecord8Link2, 0 },
        0,
        { 6.0f, 7.0f, 10.0f },
        { 0.0f, 0.0f },
        { 1.0f, 1.0f },
        g_earlierObjectRecord8Template,
        0x00235ACC,
        0x0023600C,
    },
    {
        g_earlierObjectRecord9Tail,
        0x04CA0BBF,
        { 0x0C83, -1, -1, 0x02DA, 0x02DA, 0 },
        0x00000027,
        0,
        0.0f,
        { g_earlierObjectRecord9Link, g_earlierObjectRecord9Link2 },
        0,
        { g_earlierObjectRecord9Link3, g_earlierObjectRecord9Link4 },
        0,
        { 6.0f, 7.0f, 10.0f },
        { 0.0f, 0.0f },
        { 1.0f, 1.0f },
        g_earlierObjectRecord1Template,
        0,
        0x00000000,
    },
    {
        g_earlierObjectRecord10Tail,
        0x04CB0BC0,
        { 0, -1, -1, 0x02DA, 0x02DA, 0 },
        3,
        0,
        0.0f,
        { g_earlierObjectRecord10Link, g_earlierObjectRecord10Link2 },
        0,
        { g_earlierObjectRecord10Link3, g_earlierObjectRecord10Link4 },
        0,
        { 6.0f, 7.0f, 10.0f },
        { 0.0f, 0.0f },
        { 1.0f, 1.0f },
        g_earlierObjectRecord1Template,
        0,
        0x00000000,
    },
    {
        g_earlierObjectRecord11Tail,
        0x04CC0BC1,
        { 0, -1, -1, 0x02DA, 0x02DA, 0 },
        3,
        0,
        0.0f,
        { g_earlierObjectRecord11Link, g_earlierObjectRecord11Link2 },
        0,
        { g_earlierObjectRecord11Link3, g_earlierObjectRecord11Link4 },
        0,
        { 6.0f, 7.0f, 10.0f },
        { 0.0f, 0.0f },
        { 1.0f, 1.0f },
        g_earlierObjectRecord11Template,
        0,
        0x00000000,
    },
    {
        g_earlierObjectRecord12Tail,
        0x04CD0BC2,
        { 0, -1, -1, -1, -1, 0 },
        3,
        0,
        0.0f,
        { g_earlierObjectRecord12Link, g_earlierObjectRecord12Link2 },
        0,
        { g_earlierObjectRecord12Link3, g_earlierObjectRecord12Link4 },
        0,
        { 6.0f, 7.0f, 10.0f },
        { 0.0f, 0.0f },
        { 1.0f, 1.0f },
        g_earlierObjectRecord12Template,
        0,
        0x00000000,
    },
    {
        g_earlierObjectRecord13Tail,
        0x04CE0BC3,
        { 0, -1, -1, 0x02DA, 0x02DA, 0 },
        7,
        0,
        0.0f,
        { g_earlierObjectRecord13Link, 0 },
        0,
        { g_earlierObjectRecord13Link2, 0 },
        0,
        { 6.0f, 7.0f, 10.0f },
        { 0.0f, 0.0f },
        { 1.0f, 1.0f },
        g_earlierObjectRecord13Template,
        0,
        0x00000000,
    },
    {
        g_earlierObjectRecord14Tail,
        0x04CF0BC4,
        { 0, -1, -1, -1, -1, 0 },
        3,
        0,
        0.0f,
        { g_earlierObjectRecord14Link, 0 },
        0,
        { g_earlierObjectRecord14Link2, 0 },
        0,
        { 6.0f, 7.0f, 10.0f },
        { 0.0f, 0.0f },
        { 1.0f, 1.0f },
        g_earlierObjectRecord14Template,
        0,
        0x00000000,
    },
    {
        g_earlierObjectRecord15Tail,
        0x04D00BC5,
        { 0, -1, -1, 0x02DA, 0x02DA, 0 },
        3,
        0,
        0.0f,
        { g_earlierObjectRecord15Link, g_earlierObjectRecord15Link2 },
        0,
        { g_earlierObjectRecord15Link3, g_earlierObjectRecord15Link4 },
        0,
        { 6.0f, 7.0f, 10.0f },
        { 0.0f, 0.0f },
        { 1.0f, 1.0f },
        g_earlierObjectRecord15Template,
        0x002362A4,
        0x002369C8,
    },
    {
        g_earlierObjectRecord16Tail,
        0x04D10BC6,
        { 0, -1, -1, 0x02DA, 0x02DA, 0 },
        3,
        0,
        0.0f,
        { g_earlierObjectRecord16Link, g_earlierObjectRecord16Link2 },
        0,
        { g_earlierObjectRecord16Link3, g_earlierObjectRecord16Link4 },
        0,
        { 6.0f, 7.0f, 10.0f },
        { 0.0f, 0.0f },
        { 1.0f, 1.0f },
        g_earlierObjectRecord16Template,
        0,
        0x00237D88,
    },
    {
        g_earlierObjectRecord17Tail,
        0x04D20BC7,
        { 0, -1, -1, 0x02DA, 0x02DA, 0 },
        3,
        0,
        0.0f,
        { g_earlierObjectRecord17Link, g_earlierObjectRecord17Link2 },
        0,
        { g_earlierObjectRecord17Link3, g_earlierObjectRecord17Link4 },
        0,
        { 6.0f, 7.0f, 10.0f },
        { 0.0f, 0.0f },
        { 1.0f, 1.0f },
        g_earlierObjectRecord17Template,
        0x00238374,
        0x00000000,
    },
    {
        g_earlierObjectRecord18Tail,
        0x04D50BC8,
        { 0, -1, -1, 0x02C6, 0x02C7, 0 },
        3,
        0x40800000,
        0.785398185f,
        { g_earlierObjectRecord18Link, 0 },
        0,
        { g_earlierObjectRecord18Link2, 0 },
        0,
        { 6.0f, 7.0f, 10.0f },
        { 0.0f, 0.0f },
        { 1.0f, 1.0f },
        g_earlierObjectRecord1Template,
        0,
        0x00000000,
    },
    {
        g_earlierObjectRecord19Tail,
        0x04D60BC9,
        { 0, -1, -1, 0x02DA, 0x02DA, 0 },
        3,
        0,
        0.0f,
        { g_earlierObjectRecord19Link2, 0 },
        0,
        { g_earlierObjectRecord19Link, 0 },
        0,
        { 6.0f, 7.0f, 10.0f },
        { 0.0f, 0.0f },
        { 1.0f, 1.0f },
        g_earlierObjectRecord1Template,
        0,
        0x00000000,
    },
    {
        g_earlierObjectRecord20Tail,
        0x04D70BCA,
        { 0, -1, -1, 0x02DA, 0x02DA, 0 },
        3,
        0,
        0.0f,
        { g_earlierObjectRecord20Link, 0 },
        0,
        { g_earlierObjectRecord20Link2, 0 },
        0,
        { 6.0f, 7.0f, 10.0f },
        { 0.0f, 0.0f },
        { 1.0f, 1.0f },
        g_earlierObjectRecord1Template,
        0,
        0x00000000,
    },
    {
        g_earlierObjectRecord21Tail,
        0x04D90BCC,
        { 0, -1, -1, 0x02DA, 0x02DA, 0 },
        3,
        0,
        0.0f,
        { g_earlierObjectRecord21Link, 0 },
        0,
        { g_earlierObjectRecord21Link2, 0 },
        0,
        { 6.0f, 7.0f, 10.0f },
        { 0.0f, 0.0f },
        { 1.0f, 1.0f },
        g_earlierObjectRecord1Template,
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
    g_earlierObjectTailTableEntry0,
    g_earlierObjectTailTableEntry1,
    g_earlierObjectTailTableEntry2,
    g_earlierObjectTailTableEntry3,
    g_earlierObjectTailTableEntry4,
    g_earlierObjectTailTableEntry5,
    g_earlierObjectTailTableEntry6,
};
#endif
