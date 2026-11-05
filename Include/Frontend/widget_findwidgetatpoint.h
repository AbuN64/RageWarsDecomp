#ifndef FRONTEND_WIDGET_FINDWIDGETATPOINT_H
#define FRONTEND_WIDGET_FINDWIDGETATPOINT_H
#include "Menu/widget_records.h"
#include "Frontend/frontend.h"
#include "Widget/widget_findwidgetatpoint.h"
#include "Common/widget_tree.h"
struct WidgetPointHitView;
extern s32 Widget_AnySiblingFlag40(struct WidgetNode *node);
extern s32 Widget_CollectSiblingFlags(struct WidgetNode *node);
extern void Widget_SetWidgetFlag01(struct Widget *record, int enable);
extern s32 Widget_AnyVisibleSibling(struct WidgetNode *node);
extern void Widget_SumNodeOffsets(struct WidgetAncestorOffsetView *node, s32 *x, s32 *y);
extern s32 Widget_AnySiblingFlag01(struct WidgetNode *node);
extern void Widget_SetPairValues(struct Pair14 *record, s16 first, s16 second);
extern void Widget_FindWidgetAtPoint(struct WidgetPointHitView **hit, struct WidgetPointHitView *node, sm_dldc args, s32 px, s32 py);
extern void Widget_ResetTextClipBounds(void);
extern void Widget_SetWidgetFlag40(void *object, int enabled);
extern s32 Widget_ListHasFlag100(struct WidgetNode *node);
extern void Widget_DrawVisibleSiblings(Widget *, sm_dldc);
extern void Widget_DrawVisibleWidgetClipped(Widget *, sm_dldc);
#endif
