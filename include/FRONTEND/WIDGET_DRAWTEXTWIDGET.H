#ifndef FRONTEND_WIDGET_DRAWTEXTWIDGET_H
#define FRONTEND_WIDGET_DRAWTEXTWIDGET_H
#include "COMMON/WIDGETRECAT1A.H"
#include "FRONTEND/TEXT_RENDER.H"
/* TextWidget (FRONTEND/TEXT_RENDER.H) is the widget Widget_DrawTextWidget_NodeCreategridlistfromwidget draws; sm_dldc is the 40-byte draw block a
 * caller hands it by value. */
extern void Widget_FlushTextBatches(void);
extern void Widget_DrawTextWidget(TextWidget *widget, sm_dldc args);
#endif
