#define HOR 80.0
#define VER 120.0
#define RAD 70.0	
#ifndef DRAW_H
#define DRAW_H
#include <gtk/gtk.h>
void gauge(cairo_t *cr, double needle_position, char *text);
gboolean on_draw1_draw(GtkDrawingArea *widget, cairo_t *cr);
gboolean on_draw2_draw(GtkDrawingArea *widget, cairo_t *cr);
gboolean on_draw3_draw(GtkDrawingArea *widget, cairo_t *cr);
#endif
