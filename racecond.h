#ifndef RACECOND_H
#define RACECOND_H
int cpu;
int gpu;
int mem;
GtkBuilder *builder;
GtkWidget *window;
GtkWidget *fixed1;
GtkWidget *draw1;
GtkWidget *draw2;
GtkWidget *draw3;
GError *error = NULL;
char bg_color[256]="black";
gboolean clock_timer_handler();
#endif
