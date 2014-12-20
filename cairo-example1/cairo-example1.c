#include <gtk/gtk.h>

/*事件draw的回调函数*/
gboolean
draw_callback (GtkWidget *widget, cairo_t *cr, gpointer data)
{
  guint width, height;

  //获得draw_area的宽度
  width = gtk_widget_get_allocated_width (widget); 

  //获得draw_area的高度
  height = gtk_widget_get_allocated_height (widget);

  /*绘制一个圆*/
  cairo_arc (cr,
             width / 2.0, height / 2.0,
             MIN (width, height) / 2.0,
             0, 2 * G_PI);

  /*设置颜色为红色*/
  cairo_set_source_rgb (cr, 1, 0, 0);

  /*描绘路径，即给cr涂上设置好的颜色*/
  cairo_stroke(cr);

  return FALSE;
}

int 
main (int argc, char *argv[])
{
    GtkWidget *window = NULL;
    GtkWidget *drawing_area = NULL;

    gtk_init (&argc, &argv);

    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);

    drawing_area = gtk_drawing_area_new ();
    gtk_widget_set_size_request (drawing_area, 100, 100);

    /*连接信号和回调函数*/
    g_signal_connect (window, "destroy", G_CALLBACK (gtk_main_quit), NULL);
    g_signal_connect (G_OBJECT (drawing_area), "draw",
                    G_CALLBACK (draw_callback), NULL);

    /*把drawing_area放入window中*/
    gtk_container_add (GTK_CONTAINER (window), drawing_area);

    /*显示控件*/
    gtk_widget_show (drawing_area);
    gtk_widget_show (window);

    gtk_main();

    return 0;
}
