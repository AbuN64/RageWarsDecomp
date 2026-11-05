#if defined(VERSION_EU) || defined(VERSION_EU_X)
/* Older build's rodata of C:/Projects/DM/n64/Source/onscrn.cpp. */
float g_onscreenFontSizes[8] = { 24.0f, 12.0f, 8.0f, 6.0f, 16.0f, 16.0f, 8.0f, 1.0f };
char g_onscreenAssertAsciiRangeText[44] = "(Ascii >= 0) && (Ascii < MAX_CHARACTERS)";
char g_onscreenAssertPositionRangeText[40] = "(Pos >= 0) && (Pos < MAX_CHARACTERS)";
char g_onscreenAssertPercentMinText[16] = "Percent >= 0";
char g_onscreenAssertPercentMaxText[16] = "Percent <= 100";
char g_onscreenAssertCameraText[8] = "pCamera";
float g_onscreenTextLayoutConstants[19] = { 4.65661287e-10f, 0.75f, 1.0f, 9.0f, 15.0f, 27.0f, 1.0f, 1.5f, 27.0f, 1.0f, 1.5f, 0.400000006f, 0.400000006f, 1.0f, 1.0f, 0.400000006f, 0.400000006f, 1.0f, 1.0f };
char g_onscreenPolyVertexCountFormat[20] = "Polys %d Verts %d";
char g_onscreenCollisionMemoryFormat[28] = "collision ram usage %dk ";
char g_onscreenGridLightCountFormat[32] = "grid sec: active %d  lights %d";
char g_onscreenVisibilityHeaderText[36] = "vis info             static anim";
char g_onscreenVisibilityTotalFormat[32] = "total                %d     %d";
char g_onscreenOutsideViewFormat[32] = "outside view         %d     %d";
char g_onscreenOutsideViewCulledFormat[32] = "outside view vis cul %d     %d";
char g_onscreenInsideViewFormat[32] = "inside view          %d     %d";
char g_onscreenInsideViewCulledFormat[32] = "inside view vis cul  %d     %d";
char g_onscreenDrawnTotalFormat[32] = "total drawn          %d     %d";
char g_onscreenAiHeaderText[4] = "ais";
char g_onscreenStaticCountFormat[16] = "static       %d";
char g_onscreenEnemyCountFormat[16] = "enemy        %d";
char g_onscreenPlatformCountFormat[16] = "platform     %d";
char g_onscreenGeneratorCountFormat[16] = "generator    %d";
char g_onscreenTurretCountFormat[16] = "turret       %d";
char g_onscreenThrowableCountFormat[16] = "throwable    %d";
char g_onscreenDoorCountFormat[16] = "door         %d";
char g_onscreenDestructibleCountFormat[16] = "destructible %d";
char g_onscreenPickupCountFormat[16] = "pickup       %d";
char g_onscreenInteractiveCountFormat[16] = "interactive  %d";
char g_onscreenActionCountFormat[16] = "action       %d";
char g_onscreenPlayerCountFormat[16] = "player       %d";
char g_onscreenSoundHeaderText[4] = "snd";
char g_onscreenSoundChannelCountFormat[20] = "channels       %d";
char g_onscreenAudioHeapFormat[16] = "Aud heap : %d";
float g_onscreenShadowTint[3] = { 1.0f, 0.699999988f, 0.699999988f };
#endif
