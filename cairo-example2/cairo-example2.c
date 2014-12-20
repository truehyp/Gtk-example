#include <gtk/gtk.h>

struct {
	double x[2];
	double y[2];
} glob;

static cairo_surface_t *surface = NULL;

static void do_drawing(GtkWidget *widget)
{
	cairo_t *cr;
	cr = cairo_create (surface);
	cairo_set_source_rgb (cr, 1, 0, 0);
	cairo_set_line_width (cr, 1);

	cairo_move_to (cr, glob.x[0], glob.y[0]);
	cairo_line_to (cr, glob.x[1], glob.y[1]);
	
	cairo_stroke (cr);
	cairo_destroy (cr);
	gtk_widget_queue_draw (widget);
}

static void clear_surface (GtkWidget *widget)
{
	cairo_t *cr;

	cr = cairo_create (surface);

	cairo_set_source_rgb (cr, 1, 1, 1);
	cairo_paint (cr);
	cairo_destroy (cr);
	gtk_widget_queue_draw (widget);
}
static gboolean button_press (GtkWidget *widget, 
							GdkEventButton *event,
							gpointer user_date)
{
	if (event->button == 1)
	{
		glob.x[0] = event->x;
		glob.y[0] = event->y;
		g_print ("button = 1, x = %lf	y = %lf\n", event->x, event->y);
	}
	if (event->button == 3)
		clear_surface(widget);
		g_print ("button = 3, x = %lf   y = %lf\n", event->x, event->y);
	return TRUE;
}

static gboolean button_release (GtkWidget *widget,
								GdkEventButton *event,
								gpointer user_date)
{
	if (event->button == 1)
	{
		glob.x[1] = event->x;
		glob.y[1] = event->y;
		do_drawing(widget);
		g_print ("in release button = 1, x = %lf	y = %lf\n", event->x, event->y);
	}
	return TRUE;
}

static void draw_event (GtkWidget *widget, cairo_t *cr, gpointer user_date)
{
	cairo_set_source_surface (cr, surface, 0, 0);
	cairo_paint (cr);
}

	
static gboolean configure_event (GtkWidget *widget,
								GdkEventConfigure *event,
								gpointer data)
{
	if (surface)
		cairo_surface_destroy (surface);
	surface = gdk_window_create_similar_surface (gtk_widget_get_window(widget), CAIRO_CONTENT_COLOR, gtk_widget_get_allocated_width(widget), gtk_widget_get_allocated_height (widget));
	cairo_t *cr;
	cr = cairo_create (surface);
	cairo_set_source_rgb (cr, 1, 1, 1);
	cairo_paint (cr);
	cairo_destroy (cr);

	return TRUE;
}

int main (int argc, char *argv[])
{
	GtkWidget *window;
	GtkWidget *darea;

	gtk_init (&argc, &argv);

	window = gtk_window_new (GTK_WINDOW_TOPLEVEL);

	darea = gtk_drawing_area_new ();
	gtk_container_add (GTK_CONTAINER(window), darea);
	gtk_widget_set_size_request (darea, 400, 400);

	g_signal_connect (window, "destroy", G_CALLBACK (gtk_main_quit), NULL);

	g_signal_connect (darea, "button-press-event", G_CALLBACK(button_press),NULL);
	g_signal_connect (darea, "button-release-event", G_CALLBACK(button_release), NULL);
	/*重绘时发出信号*/
	g_signal_connect (darea, "draw", G_CALLBACK (draw_event), NULL);
	/*控件大小改变时发出信号，包括窗口创建时*/
	g_signal_connect (darea, "configure-event", G_CALLBACK (configure_event), NULL);

	gtk_widget_set_events (darea, GDK_BUTTON_PRESS_MASK|GDK_BUTTON_RELEASE_MASK);

	gtk_widget_show_all (window);

	gtk_main ();

	return 0;
}
