#ifndef NODE_NODE_CONFIGURESCROLLEDTABLECELL_H
#define NODE_NODE_CONFIGURESCROLLEDTABLECELL_H
struct GlyphBuffer;
struct List;
void Node_ClampListCursorAndScroll(struct List *list);
struct sm_dllistbox;
struct t_dltext;
void Node_ConfigureScrolledTableCell(struct sm_dllistbox *table, struct t_dltext *cell, u32 row, u32 col);
#include "Frontend/frontend.h"
#include "Common/runtime_declarations.h"
extern struct GlyphBuffer *Node_GetGlyphBuffer(s32 index);
extern short Node_GetFontLetterSpacing(s32 index);
extern void Node_ReleaseRetainedImageSlot(s32 i);
extern void Node_LoadLanguageStringsIfAny(int);
void Node_ReleaseUnprotectedBuffers(s32 force);
#endif
