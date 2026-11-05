#ifndef FX_EU_SCREEN_MESSAGE_SETUP_H
#define FX_EU_SCREEN_MESSAGE_SETUP_H
#if defined(VERSION_EU)
typedef struct {
    unsigned int screenMessageSetupWords[313];
    unsigned char emptyTextSlots[8444];
    unsigned int controlCodeTexts[4];
    unsigned char emptyTextSlots_repeat2[5228];
    unsigned int creditsNameLinks[265];
    unsigned char emptyTextSlots_repeat3[2472];
    unsigned int textSoeurWords[2];
    unsigned char emptyTextSlots_repeat4[36];
    unsigned int textOeurs;
    unsigned char emptyTextSlots_repeat5[172];
    unsigned int controllerPakTextLinks[11];
    unsigned char emptyTextSlots_repeat6[16];
    unsigned int textEAcute;
    unsigned char emptyTextSlots_repeat7[96];
    unsigned char emptyTextSlots_repeat8[24];
    unsigned char emptyTextSlots_repeat9[24];
    unsigned char emptyTextSlots_repeat10[28];
    unsigned char emptyTextSlots_repeat11[12];
    unsigned int textEAcuteCopy;
    unsigned char emptyTextSlots_repeat12[16];
    unsigned char emptyTextSlots_repeat13[16];
    unsigned char emptyTextSlots_repeat14[24];
    unsigned char emptyTextSlots_repeat15[416];
    unsigned char emptyTextSlots_repeat16[16];
    unsigned int textOeil;
    unsigned char emptyTextSlots_repeat17[16];
    unsigned char emptyTextSlots_repeat18[16];
    unsigned char emptyTextSlots_repeat19[16];
    unsigned int textCoeur;
    unsigned char emptyTextSlots_repeat20[8];
    unsigned char emptyTextSlots_repeat21[20];
    unsigned char emptyTextSlots_repeat22[20];
    unsigned char emptyTextSlots_repeat23[24];
    unsigned char emptyTextSlots_repeat24[1260];
} ScreenMessageSetupDataEU;
extern ScreenMessageSetupDataEU k_SkyPostscaledscreenmessageEncodedWords;
#endif
#endif
