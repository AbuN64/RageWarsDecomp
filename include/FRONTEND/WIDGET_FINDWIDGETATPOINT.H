#ifndef FRONTEND_WIDGET_FINDWIDGETATPOINT_H
#define FRONTEND_WIDGET_FINDWIDGETATPOINT_H
#include "COMMON/WIDGETRECAT1A.H"
extern s32 Widget_AnySiblingFlag40(struct WidgetNode *node);
extern s32 Widget_CollectSiblingFlags(struct WidgetNode *node);
extern void Widget_SetWidgetFlag01(struct Widget *record, int enable);
extern s32 Widget_AnyVisibleSibling(struct WidgetNode *node);
extern void Widget_SumNodeOffsets(struct WidgetAncestorOffsetView *node, s32 *x, s32 *y);
extern s32 Widget_AnySiblingFlag01(struct WidgetNode *node);
extern void Widget_SetPairValues(struct Pair14 *record, s16 first, s16 second);
extern void Widget_FindWidgetAtPoint(WidgetPointHitView **hit, WidgetPointHitView *node, DrawArgsFrontendDrawVisibleWidgetClipped args, s32 px, s32 py);
extern void Widget_ResetTextClipBounds(void);
extern void Widget_SetWidgetFlag40(void *object, int enabled);
#endif
