#ifndef NODE_NODE_CONFIGURESCROLLEDTABLECELL_H
#define NODE_NODE_CONFIGURESCROLLEDTABLECELL_H
struct List;
void Node_ClampListCursorAndScroll(struct List *list);
struct sm_dllistbox;
struct t_dltext;
void Node_ConfigureScrolledTableCell(struct sm_dllistbox *table, struct t_dltext *cell, u32 row, u32 col);
#endif
