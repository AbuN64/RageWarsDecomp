#include "COMMON/GAMEPLAY_CAMERA.H"
#include "COMMON/VIEWFLAGS.H"
#include "TYPES.H"

typedef void (*FuncPtr)(void);

extern FuncPtr g_cameraGameplayModeCallbacks[][2];




void Gsky_SetGameplayMode(void *gameplayCamera, s16 requestedMode) {
    FuncPtr fn;

    ((GameplayCamera *)gameplayCamera)->mode = requestedMode;
    ((GameplayCamera *)gameplayCamera)->elapsed = 0;
    ((GameplayCamera *)gameplayCamera)->state = 0;
    ((GameplayCamera *)gameplayCamera)->stateCounter = 0;
    fn = g_cameraGameplayModeCallbacks[((GameplayCamera *)gameplayCamera)->mode][0];
    if (fn != 0) {
        ((void (*)(void *))fn)(gameplayCamera);
    }
}
