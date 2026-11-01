#ifndef FRONTEND_NODE_CREATEGRIDLISTFROMWIDGET_H
#define FRONTEND_NODE_CREATEGRIDLISTFROMWIDGET_H
#include "FRONTEND/LAYOUT.H"
extern void Node_SetGridForegroundColors(s32 identifier, s32 first, s32 second, s32 third);
extern void Node_GetGridSelection(s32 identifier, s32 *first, s32 *second);
extern void Node_SetGridBackgroundColors(s32 identifier, s32 first, s32 second, s32 third);
extern void Node_SetGridDimensionArrays(s32 identifier, s32 first, s32 second);
extern void Node_GetGridCellValues(s32 identifier, s32 row, s32 column, s32 *first, s32 *second);
extern void Node_SetGridCellValues(s32 identifier, s32 row, s32 column, s32 first, s32 second);
extern s32 Node_CreateGridListFromWidget(s32 widget, u8 visibleColumns, u8 visibleRows, u8 storageRows, u8 storageColumns, u8 initialRow, u8 initialColumn);
#endif
