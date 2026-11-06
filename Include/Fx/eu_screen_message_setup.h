#ifndef FX_EU_SCREEN_MESSAGE_SETUP_H
#define FX_EU_SCREEN_MESSAGE_SETUP_H
#if defined(VERSION_EU)
typedef struct {
    unsigned int screenMessageSetupWords[313];
    unsigned char textSlots[8444];
    unsigned int controlCodeTexts[4];
    unsigned char textSlots_repeat2[5228];
    unsigned int creditsNameLinks[265];
    unsigned char textSlots_repeat3[2472];
    unsigned int textSoeurWords[2];
    unsigned char textSlots_repeat4[36];
    unsigned int textOeurs;
    unsigned char textSlots_repeat5[172];
    unsigned int controllerPakTextLinks[11];
    unsigned char textSlots_repeat6[16];
    unsigned int textEAcute;
    unsigned char textSlots_repeat7[96];
    unsigned char textSlots_repeat8[24];
    unsigned char textSlots_repeat9[24];
    unsigned char textSlots_repeat10[28];
    unsigned char textSlots_repeat11[12];
    unsigned int textEAcuteCopy;
    unsigned char textSlots_repeat12[16];
    unsigned char textSlots_repeat13[16];
    unsigned char textSlots_repeat14[24];
    unsigned char textSlots_repeat15[416];
    unsigned char textSlots_repeat16[16];
    unsigned int textOeil;
    unsigned char textSlots_repeat17[16];
    unsigned char textSlots_repeat18[16];
    unsigned char textSlots_repeat19[16];
    unsigned int textCoeur;
    unsigned char textSlots_repeat20[8];
    unsigned char textSlots_repeat21[20];
    unsigned char textSlots_repeat22[20];
    unsigned char textSlots_repeat23[24];
    unsigned char textSlots_repeat24[1260];
} ScreenMessageSetupDataEU;
extern ScreenMessageSetupDataEU k_SkyPostscaledscreenmessageEncodedWords;
#endif
#endif
