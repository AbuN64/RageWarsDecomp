typedef int s32;
typedef unsigned short u16;
typedef struct Obj { char pad0[20]; u16 f20; } Obj;
typedef struct Screen { char pad0[36]; void *f36; void *f40; char pad44[16]; Obj *f60; u16 pad64; u16 f66; Obj *f68; u16 f72; u16 f74; s32 f76; s32 f80; char pad84[13424 - 84]; s32 f13424; } Screen;
extern Screen *s_screen;
extern s32 BlackoutCounter;
extern char s_file[];
extern char s_msg[];
extern s32 AssertFailed(char *file, s32 line, char *msg);
extern void Sound__PlayFXGlobal(s32 n);
extern void SM_DLSetVisible(void *o, s32 v);
extern void SMFL_StartFlickerNow(void *f, s32 n);
extern s32 SMFL_IsFlickerDone(void *f);
extern void SMFL_Stop(void *f);
extern void SM_AcknowledgeMsg();
extern void SM_ScreenLink(s32 n);
extern void TSMOS__InputEnable();
extern void PAKInterface_UpdateGroups(s32 n);
s32 f5(s32 a, s32 b, s32 c, s32 d) {
    if (BlackoutCounter >= 2) {
        return 0;
    }
    switch (s_screen->f76) {
    case 1:
        s_screen->f60->f20 = s_screen->f60->f20 + s_screen->f66;
        s_screen->f68->f20 = s_screen->f68->f20 - s_screen->f74;
        s_screen->f80 = s_screen->f80 - 1;
        if (s_screen->f80 <= 0) {
            Sound__PlayFXGlobal(3705);
            SM_DLSetVisible(s_screen->f40, 1);
            SMFL_StartFlickerNow(s_screen->f36, 4);
            s_screen->f76 = 4;
            s_screen->f80 = 4;
        }
        break;
    case 2:
        s_screen->f60->f20 = s_screen->f60->f20 - s_screen->f66;
        s_screen->f68->f20 = s_screen->f68->f20 + s_screen->f74;
        s_screen->f80 = s_screen->f80 - 1;
        if (s_screen->f80 <= 0) {
            s_screen->f76 = 3;
            SM_AcknowledgeMsg();
            SM_ScreenLink(s_screen->f13424);
            return 0;
        }
        break;
    case 3:
        TSMOS__InputEnable();
        break;
    case 4:
        s_screen->f80 = (s_screen->f80 - 1 >= 0) ? (-(s_screen->f80 >= s_screen->f80 - 1) + s_screen->f80) : 0;
        if (s_screen->f80 <= 0) {
            if (SMFL_IsFlickerDone(s_screen->f36)) {
                SMFL_Stop(s_screen->f36);
                s_screen->f76 = 3;
            }
        }
        break;
    case 5:
        Sound__PlayFXGlobal(3704);
        s_screen->f76 = 2;
        s_screen->f80 = 4;
        SM_DLSetVisible(s_screen->f40, 0);
        break;
    default:
        if (AssertFailed(s_file, 908, s_msg)) {
            *(char *)0 = 0;
        }
        break;
    }
    if (s_screen->f76 != 3) {
        return 0;
    }
    PAKInterface_UpdateGroups(c);
    return 0;
}
