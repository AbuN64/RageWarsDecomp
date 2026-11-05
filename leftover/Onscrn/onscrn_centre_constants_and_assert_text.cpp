#if defined(VERSION_EU) || defined(VERSION_EU_X)
/* Older build's rodata of C:/Projects/DM/n64/Source/onscrn.cpp. */
float g_onscreenCentreConstants[3] = { 284.0f, 222.0f, 0.5f };
char g_onscreenAssertTextureAlignedText[28] = "!((DWORD)pTexture & 0x07)";
char g_onscreenAssertOpacityAlignedText[28] = "!((DWORD)pOpacity & 0x07)";
float g_onscreenGlyphSpacing[20] = { 4.0f, 4.0f, 4.0f, 4.0f, 4.0f, 4.0f, 4.0f, 4.0f, 1.0f, 1.0f, 30.0f, 0.0f, 30.0f, 0.0f, 1.0f, 1.0f, 30.0f, 0.0f, 30.0f, 0.0f };
char g_onscreenAssertDataAlignedText[28] = "(((DWORD)pData) & 0x7) == 0";
char g_onscreenAssertGraphicSetText[12] = "pGraphicSet";
char g_onscreenAssertFrameInfoText[12] = "pFrameInfo";
char g_onscreenAssertFontRampTextureText[40] = "(((u32)font_ramp_texture) & 0x7) == 0";
#endif
