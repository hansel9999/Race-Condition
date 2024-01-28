#include "draw.h"
#include "utils.h"
#include <math.h>
#include <string.h>
#include <cairo.h>
#include <gtk/gtk.h>

void gauge(cairo_t *cr, double needle_position, char *text){
	double x, x1, y, y1;
	double X=0.0;

	//outer edge
	cairo_set_source_rgb(cr, 1.0, 1.0, 1.0);
	cairo_arc(cr, HOR, VER, RAD+2.5, -M_PI, 0.0);
	cairo_line_to(cr, HOR, VER+3);
	cairo_fill(cr);
	cairo_set_source_rgb(cr, 0.0, 0.0,0.0);
	cairo_arc(cr, HOR, VER, RAD, -M_PI, M_PI);
	cairo_line_to(cr, HOR, VER+3);
	cairo_fill(cr);


	//hash marks around edge
	cairo_set_source_rgb(cr, 1.0, 1.0, 1.0);
	cairo_set_line_width(cr, 2.5);
	for(int i=0; i<8; i++){	
		cairo_arc(cr, HOR, VER, RAD, -M_PI, -M_PI+X);
		cairo_get_current_point(cr, &x, &y);
		cairo_arc(cr, HOR, VER, RAD-10, -M_PI, -M_PI+X);
		cairo_get_current_point(cr, &x1, &y1);
		cairo_new_path(cr);
		cairo_move_to(cr, x, y);
		cairo_line_to(cr, x1, y1);
		cairo_stroke(cr);
		X += M_PI / 7.0;
	}

	//needle
	cairo_set_source_rgb(cr, 1.0, 0.0, 0.0);
	cairo_set_line_width(cr, 2.0);
	cairo_arc(cr, HOR, VER, RAD, -M_PI, -M_PI+needle_position);
	cairo_get_current_point(cr, &x, &y);
	cairo_new_path(cr);
	cairo_move_to(cr, x, y);
	cairo_line_to(cr, HOR, VER);
	cairo_stroke(cr);

	//bottom line
	cairo_set_source_rgb(cr, 1.0, 1.0, 1.0);
	cairo_set_line_width(cr, 2.5);
	cairo_new_path(cr);
	cairo_move_to(cr, HOR-RAD-2.5, VER);
	cairo_line_to(cr, HOR+RAD+2.5, VER);
	cairo_stroke(cr);

	//center dot
	cairo_set_source_rgb(cr, 1.0, 1.0, 1.0);
	cairo_arc(cr, HOR, VER, 4.0, -M_PI, M_PI);
	cairo_line_to(cr, HOR, VER+3);
	cairo_fill(cr);

	//label
	cairo_text_extents_t text_extents;
	cairo_text_extents(cr, text, &text_extents);
	double text_width=text_extents.width;
	double text_center = (160.0 - text_width)/2;
	cairo_move_to(cr, text_center, 150.0);
	cairo_set_source_rgb(cr, 1,1,1);
	cairo_show_text(cr, text);
	cairo_stroke(cr);
}

gboolean on_draw1_draw(GtkDrawingArea *widget, cairo_t *cr){
	int cpu = get_cpu_perc();
	double needle_position = cpu * M_PI / 100;
       	gauge(cr, needle_position, "CPU");
	return TRUE;
}
gboolean on_draw2_draw(GtkDrawingArea *widget, cairo_t *cr){
	int gpu = get_gpu_perc();
	double needle_position = gpu * M_PI / 100;
       	gauge(cr, needle_position, "GPU");
	return TRUE;
}
gboolean on_draw3_draw(GtkDrawingArea *widget, cairo_t *cr){
	int mem=get_ram_perc();
	double needle_position = mem * M_PI / 100;
       	gauge(cr, needle_position, "RAM");
	return TRUE;
}
