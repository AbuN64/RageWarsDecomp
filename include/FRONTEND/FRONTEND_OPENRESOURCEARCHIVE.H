#ifndef FRONTEND_FRONTEND_OPENRESOURCEARCHIVE_H
#define FRONTEND_FRONTEND_OPENRESOURCEARCHIVE_H
#include "COMMON/WIDGETRECAT1A.H"
#include "COMMON/SLOTRECATCV1.H"
extern void Node_SwapWidgetTreePositions(WidgetTreePositionView *a, WidgetTreePositionView *b);
extern void Node_SetObjectWordAt2C(void *object, int value);
extern void Node_AssignObjectWordAt2C(void *object, int value);
extern int Node_CompareRecordShortValues(struct Field_u16_14 *a, struct Field_u16_14 *b);
extern void Node_NoOperation(void);
extern s32 Node_MeasureTextPrefix(s32 font, u8 *text, s32 length);
extern void Node_SetRecordBytePair(struct Pair2C *record, u8 first, u8 second);
extern void Node_SetDisplayClipBounds(s32 width, s32 height);
extern void Node_SetRecordValueQuad(struct WidgetRecordValueQuadView *record, s32 first, s32 second, s32 third, s32 fourth);
struct Tree;
extern void Node_WrapNodeInParent(struct Tree *node, struct Tree *added);
#endif
