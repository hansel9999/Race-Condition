#include <gtk/gtk.h>
#include <cairo.h>
#include "racecond.h"  
#include "draw.h"
#include "racecond_glade.h"

int main (int argc, char *argv[]){

  //gtk init
  gtk_init (&argc, &argv);

  //get ui from xml
  builder = gtk_builder_new ();
  const char *ui_description = (const char *)racecond_glade;
  if (gtk_builder_add_from_string(builder, ui_description, racecond_glade_len, &error) == 0){
      g_printerr ("Error loading file: %s\n", error->message);
      g_clear_error (&error);
      return 1;
  }
  gtk_builder_connect_signals(builder, NULL);

  //connect variables to ui elements
  window = GTK_WIDGET(gtk_builder_get_object (builder, "window"));
  g_signal_connect (window, "destroy", G_CALLBACK (gtk_main_quit), NULL);
  fixed1=GTK_WIDGET(gtk_builder_get_object(builder, "fixed1"));
  
  draw1=GTK_WIDGET(gtk_builder_get_object(builder, "draw1"));
  draw2=GTK_WIDGET(gtk_builder_get_object(builder, "draw2"));
  draw3=GTK_WIDGET(gtk_builder_get_object(builder, "draw3"));
  
  
  g_object_unref(builder);

  //show window
  gtk_window_set_keep_above(GTK_WINDOW(window), TRUE);
  gtk_widget_show(window);


  //background color
  GdkColor color;
  if (!gdk_color_parse(bg_color, &color)){
	  color.blue=0x0000;
	  color.red=0x0000;
	  color.green=0x0000;
  }
  gtk_widget_modify_bg(window, GTK_STATE_NORMAL, &color);

  g_timeout_add(1000, (GSourceFunc)clock_timer_handler, NULL);

  gtk_main ();
  return EXIT_SUCCESS;
}

gboolean clock_timer_handler(){
	gtk_widget_queue_draw(draw1);
	gtk_widget_queue_draw(draw2);
	gtk_widget_queue_draw(draw3);
	return TRUE;
}
