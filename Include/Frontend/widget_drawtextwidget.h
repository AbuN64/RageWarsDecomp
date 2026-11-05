#ifndef FRONTEND_WIDGET_DRAWTEXTWIDGET_H
#define FRONTEND_WIDGET_DRAWTEXTWIDGET_H
#include "Common/widget_tree.h"
#include "Frontend/text_render.h"
struct TextWidget;
/* TextWidget (FRONTEND/TEXT_RENDER.H) is the widget Widget_DrawTextWidget_NodeCreategridlistfromwidget draws; sm_dldc is the 40-byte draw block a
 * caller hands it by value. */
extern void Widget_FlushTextBatches(void);
/* Resolves a widget's draw and hit rectangles for the given draw block; returns zero when the widget is not visible there. */
extern s32 Widget_ComputeWidgetBounds(struct WidgetRect *draw, struct WidgetRect *hit, struct WidgetLayout *widget, sm_dldc *ctx);
extern void Widget_DrawTextWidget(struct TextWidget *widget, sm_dldc args);
extern s32 Widget_ComputeWidgetBounds(struct WidgetRect *draw, struct WidgetRect *hit, struct WidgetLayout *widget, struct t_dldc *ctx);
#endif
