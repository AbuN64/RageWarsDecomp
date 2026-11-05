#ifndef FRONTEND_FRONTEND_OPENRESOURCEARCHIVE_H
#define FRONTEND_FRONTEND_OPENRESOURCEARCHIVE_H
#include "Frontend/frontend.h"
#include "Common/widget_tree.h"
#include "Common/archive_chunk_images.h"
struct WidgetTreePositionView;
extern void Node_SwapWidgetTreePositions(struct WidgetTreePositionView *a, struct WidgetTreePositionView *b);
extern void Node_SetArchiveHandle(void *object, int value);
extern void Node_AssignArchiveHandle(void *object, int value);
extern int Node_CompareRecordShortValues(struct TextSpriteGlyphKey *a, struct TextSpriteGlyphKey *b);
extern void Node_NoOperation(void);
extern s32 Node_MeasureTextPrefix(s32 font, u8 *text, s32 length);
extern void Node_SetRecordBytePair(struct Pair2C *record, u8 first, u8 second);
extern void Node_SetDisplayClipBounds(s32 width, s32 height);
extern void Node_SetRecordValueQuad(struct WidgetRecordValueQuadView *record, s32 first, s32 second, s32 third, s32 fourth);
struct Tree;
extern void Node_WrapNodeInParent(struct Tree *node, struct Tree *added);
struct WidgetRect;
s32 Node_ClampRectToClip(struct WidgetRect *rect, struct WidgetRect *clip);
struct UiWidget;
void Node_RelocateWidgetTree(struct UiWidget *widget, s32 base, s32 old);
extern void Node_ReplaceNodeRefs(struct WidgetReferenceNodeView *node, void *from, void *to);
extern void Node_ReplaceNodeRefs(struct WidgetReferenceNodeView *node, void *from, void *to);
extern void Node_OpenResourceArchive(u8 *name);
#endif
