#if defined(VERSION_EU) || defined(VERSION_EU_X)
/* Older build's rodata of C:/Projects/DM/n64/Source/pickup.cpp. */
float g_earlierPickupFloats32[17] = { 0.0f, 0.0f, 1.75f, 0.0f, 0.0f, 0.0f, 1.75f, 0.0f, -1.0f, 1.0f, -1.0f, 1.0f, 1.0f, 65536.0f, 1.0f, 65536.0f, 1.52587891e-05f };
#if defined(VERSION_EU)
/* The record bytes before the AI_OB string share one object: a char array of 4+ bytes is word aligned, so a split at 460CBB would pad. */
char g_earlierPickupRecordStrAiOb[12] = "\x0B" "\0\0\0\0\0" "\x1D" "AI_OB";
float g_earlierPickupFloats34[6] = { 1.0f, 2.0f, -2.0f, 1.0f, 2.0f, -2.0f };
unsigned char g_earlierRecordBytes17[8] = { 0x04, 0x00, 0x00, 0x00, 0x96, 0x66, 0x00, 0x00 };
#else
unsigned int g_earlierPickupWords7[2] = { 0xB000000, 0x1D41 };
float g_earlierPickupFloats33[7] = { 914676.125f, 1.0f, 2.0f, -2.0f, 1.0f, 2.0f, -2.0f };
#endif
#endif
