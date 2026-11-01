#ifndef SCENE_SCENEPRIMARYACTORS_H
#define SCENE_SCENEPRIMARYACTORS_H
typedef struct Shared_ScenePrimaryActors Shared_ScenePrimaryActors;
struct Shared_ScenePrimaryActors {
    void * actors[4]; /* +0x0: src/Scene_LoadLevelResources_SceneResourceState.c */
    void * kindBd7; /* +0x10: src/Scene_LoadLevelResources_SceneResourceState.c */
};
typedef char Shared_ScenePrimaryActors_size_check[(sizeof(Shared_ScenePrimaryActors) == 0x14) ? 1 : -1];
#endif
