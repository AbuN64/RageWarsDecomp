#ifndef STATINST_STATINST_ACQUIREGEOMETRY_H
#define STATINST_STATINST_ACQUIREGEOMETRY_H
struct CacheResourceNode;
struct ResourceOwner;
void *Statinst_AcquireGeometry(struct ResourceOwner *owner,s32 index);
extern void Cache_LockResource(void *,struct CacheResourceNode *);
#endif
