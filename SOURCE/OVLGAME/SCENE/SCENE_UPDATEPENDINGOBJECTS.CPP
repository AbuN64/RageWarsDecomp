#include "COMMON/OBJB.H"
#include "COMMON/INTEGERSTATEB0.H"
#include "MENU/SCENE_RESOURCE_PREVIEW_AND_COLLISION_VIEWS.H"
#include "TYPES.H"
#include "RENDER/SOUNDELEMENT_PLAYFLATSOUND.H"

/* Sets the resource transition state and sound, while its adjacent helper refreshes the controller-option bit. */


extern void Scene_LoadSceneLight(void);
void Scene_SetSelection(ItemsSelectionState *state,int selection,int mode) {
 state->active=1;
 state->mode=mode;
 state->selection=selection;
 if(mode==2 && selection!=999)SoundElement_PlayFlatSound(540);
}
void Scene_LoadSelectionLighting(ItemsSelectionState *state) {
 Scene_LoadSceneLight();
 g_geometryFogEffectEnabled=(state->input->value>>2)&1;
}

/* Processes both pending object lists between update barriers. */

void Cinema_SetPlaybackFlag(void);                                  /* extern */
void Cinema_ClearPlaybackFlag(void);                                  /* extern */
void Scene_DispatchEnabledEntityTrigger(void *, s32);                       /* extern */

void Scene_UpdatePendingObjects(ItemsPendingState *pendingWorld) {
 s32 i,n;
 Cinema_ClearPlaybackFlag();
 n=pendingWorld->firstPendingCount;
 for(i=0;i<n;i++) Scene_DispatchEnabledEntityTrigger(pendingWorld,pendingWorld->firstPendingEntries+i*20);
 n=pendingWorld->secondPendingCount;
 for(i=0;i<n;i++) Scene_DispatchEnabledEntityTrigger(pendingWorld,pendingWorld->secondPendingEntries+i*20);
 Cinema_SetPlaybackFlag();
}
