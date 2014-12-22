#include <gtk/gtk.h>

static struct Block{
	double x;
	double y;
} block;


static void
draw_event (GtkWidget *widget,
	   		cairo_t *cr,
		   	gpointer user_data)
{
	cairo_set_line_width (cr, 3);
	cairo_set_source_rgb (cr, 0, 0, 0);
	cairo_rectangle (cr, block.x - 25, block.y - 25, 50, 50);
	cairo_stroke (cr);
	cairo_set_source_rgb (cr, 1, 0, 0);
	cairo_rectangle (cr, block.x - 25, block.y - 25, 50, 50);
	cairo_fill (cr);
	block.y += 50;

}



void
request_draw_the_widget (GtkWidget *widget)
{
	gtk_widget_queue_draw (widget);
}

int
main (int argc, char *argv[])
{
	GtkWidget *window;
	GtkWidget *darea;

	gtk_init (&argc, &argv);

	window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_window_set_default_size ((GtkWindow *)window, 800, 600);
 	gtk_window_set_resizable ((GtkWindow *)window, FALSE);
	
	darea = gtk_drawing_area_new ();
	gtk_container_add (GTK_CONTAINER (window), darea);
	gtk_widget_set_size_request (darea, 400, 400);

	block.x = 200;
	block.y = 25;
	
	g_signal_connect (window, "destroy", G_CALLBACK (gtk_main_quit), NULL);
	g_signal_connect (darea, "draw", G_CALLBACK (draw_event), NULL);

	g_timeout_add(500, (GSourceFunc)request_draw_the_widget, (gpointer)darea);

	gtk_widget_show_all (window);

	gtk_main();
	return 0;
}

