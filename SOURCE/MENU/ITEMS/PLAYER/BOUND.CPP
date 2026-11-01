#include "MENU/OBJECT1C8.H"
#include "TYPES.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "MENU/BOUND.H"
#include "COMMON/PARTICLE_LIGHTING.H"
#include "include_asm.h"
#include "RENDER/MATERIAL_COLOR_AND_FOG_VIEWS.H"
#include "COMMON/WEAPON_MARKER_AND_PROFILE_VIEWS.H"
#if defined(VERSION_US_REV1)
f32 Bound_ReadBoundValue(MenuBindingItemView *item) {
 Binding *v = item->binding;
 void *p = v->storage();
 switch(v->type) {
 default: return 0.0f;
 case 0: return *(f32 *)p;
 case 3: return *(s8 *)p;
 case 4: return *(s16 *)p;
 case 1: case 2: case 5: return *(s32 *)p;
 case 6: return *(u8 *)p;
 case 7: return *(u16 *)p;
 case 8: return *(u32 *)p;
 }
}
/* Writes a numeric menu value through its bound storage callback using the selected scalar type. */
void Bound_WriteBoundValue(MenuBindingItemView *item,float value) {
 float *storage;
 struct Binding *binding;
 unsigned int *word;
 binding=item->binding;
 storage=binding->storage();

 switch(binding->type) {
 case 0:*(float *)storage=value;return;
 case 3:*(signed char *)storage=(int)value;return;
 case 4:*(short *)storage=(int)value;return;
 case 1:case 2:case 5:*(int *)storage=(int)value;return;
 case 6:*(unsigned char *)storage=(unsigned int)value;return;
 case 7:*(unsigned short *)storage=(unsigned int)value;return;
 case 8:word=(unsigned int *)storage;*word=(unsigned int)value;return;
 }
}
#endif
/* Calls Gobjinst_DrawMaskedModelWithLighting with its three arguments and the table g_defaultParticleLighting as the fourth. */
extern void Gobjinst_DrawMaskedModelWithLighting(void *, void *, void *, void *);
#if defined(VERSION_US_REV1)
void Bound_DrawActorWithMenuLighting(void *first, void *second, void *third) {
    Gobjinst_DrawMaskedModelWithLighting(first, second, third, &g_defaultParticleLighting);
}
#endif
extern void Gobjinst_DrawActorModelWithViewEffects(ObjectItemsDrawActorWithRedMenuEffect *, void *, void *);
#if defined(VERSION_US_REV1)
void Bound_DrawActorWithRedMenuEffect(ObjectItemsDrawActorWithRedMenuEffect *object, void *context, void *lookup) {
 g_menuModelFillEnabled=3;
 object->view[g_lightingBufferIndex]=g_defaultParticleLighting;
 g_menuModelFillColor[0]=(255.0f);
 g_menuModelFillColor[1]=0;
 g_menuModelFillColor[2]=0;
 g_menuModelFillColor[4]=0;
 g_menuModelFillColor[3]=(float)(g_menuTintAlpha/2);
 Gobjinst_DrawActorModelWithViewEffects(object,context,lookup);
 g_menuModelFillEnabled=0;
}
#endif
