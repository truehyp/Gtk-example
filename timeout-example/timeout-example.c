#include <gtk/gtk.h>

gint timer;

gboolean
timeout_task1 (void)
{
	g_print ("in task1\n");
	return TRUE;
}

gboolean timeout_task2 (void)
{
	g_print ("in task2 remove task1 id = %d\n", timer);
	g_source_remove (timer);
	g_print ("in task2 return FLASE delay task2");
	return FALSE;
}
int
main (int argc, char *argv[])
{
	GtkWidget *window;

	gtk_init (&argc, &argv);
	window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_window_set_default_size ((GtkWindow *)window, 400, 300);
	gtk_container_set_border_width (GTK_CONTAINER (window), 5);
	//gtk_window_set_resizable (GTK_WINDOW (window), FALSE);

	
	g_signal_connect (window, "destroy", G_CALLBACK (gtk_main_quit), NULL);
	timer = g_timeout_add (500, (GSourceFunc)timeout_task1, NULL);
	g_timeout_add (2000, (GSourceFunc)timeout_task2, NULL);
	gtk_widget_show_all (window);
	gtk_main ();
	
	return 0;
}
