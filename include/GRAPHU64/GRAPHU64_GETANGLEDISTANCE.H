#ifndef GRAPHU64_GRAPHU64_GETANGLEDISTANCE_H
#define GRAPHU64_GRAPHU64_GETANGLEDISTANCE_H
struct CVector3_t;
void Graphu64_CrossVectors(struct CVector3_t *out, struct CVector3_t *a, struct CVector3_t *b);
void Graphu64_ScaleVector(void *scaledVector, void *inputVector, f32 scaleFactor);
#endif
