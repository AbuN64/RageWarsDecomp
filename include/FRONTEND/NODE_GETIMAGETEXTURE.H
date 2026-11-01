#ifndef FRONTEND_NODE_GETIMAGETEXTURE_H
#define FRONTEND_NODE_GETIMAGETEXTURE_H
#include "COMMON/SLOTRECATCV1.H"
extern void Node_CloseResourceArchive(void);
extern void Node_EvictExpiredImages(void);
extern s32 Node_GetImageTexture(s32 index, s32 mode);
#endif
