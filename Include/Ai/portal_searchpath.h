#ifndef AI_PORTAL_SEARCHPATH_H
#define AI_PORTAL_SEARCHPATH_H
#include "types.h"
#include "Common/animation.h"
struct CNavData_t;
#if defined(VERSION_DE)
extern s32 Portal_CollectDirectedNeighbors(struct CNavData_t *graph, s32 nodeKey, s32 preferredNodeKey, s32 *neighborsOut, s32 reverseDirection);
#endif
#if !defined(VERSION_DE)
extern s32 Portal_CollectDirectedNeighbors(struct CNavData_t *graph, s32 nodeKey, s32 preferredNodeKey, s32 *neighborsOut, s32 reverseDirection);
#endif
extern s32 Portal_SearchRelatedGoalPath(struct CNavData_t *obj, s32 key, s32 requested, void *owner);
#if defined(VERSION_DE)
extern s32 Portal_CollectDirectedNeighbors(struct CNavData_t *graph, s32 nodeKey, s32 preferredNodeKey, s32 *neighborsOut, s32 reverseDirection);
#endif
#if !defined(VERSION_DE)
extern s32 Portal_CollectDirectedNeighbors(struct CNavData_t *graph, s32 nodeKey, s32 preferredNodeKey, s32 *neighborsOut, s32 reverseDirection);
#endif
#endif
