#include <stdlib.h>

/* The gtk include directory is added to the gcc command via -I option prodiced by the output of the pkg-config command */
#include <gtk/gtk.h>

static gulong counter = 0UL;

static void hello_button_clicked (GtkWidget *wid, GtkWidget *win){
    GtkWidget *dialog = NULL;

    dialog = gtk_message_dialog_new (GTK_WINDOW (win), GTK_DIALOG_MODAL, GTK_MESSAGE_INFO, GTK_BUTTONS_CLOSE, "Hello World!");
    gtk_window_set_position (GTK_WINDOW (dialog), GTK_WIN_POS_CENTER);
    gtk_dialog_run (GTK_DIALOG (dialog));
    gtk_widget_destroy (dialog);

    counter++;
    g_print("hello world button clicked %lu times\r\n", counter);
}

static void close_button_clicked(GtkWidget *button , gpointer user_data){
    gtk_main_quit();
}
int main (int argc, char *argv[])
{
    gtk_init(&argc,&argv);
    /*Create main window*/
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Main Window");
    gtk_window_set_default_size(GTK_WINDOW(window),500,400);

    /*Create buttons*/
    GtkWidget *button1 = gtk_button_new_with_label("Close"),
    *button2 = gtk_button_new_with_label("Hello");
    g_signal_connect(button1,"clicked",G_CALLBACK(close_button_clicked),NULL);
    g_signal_connect(button2,"clicked",G_CALLBACK(hello_button_clicked),NULL);

    /*Place buttons inside window*/
    gtk_container_add( GTK_CONTAINER(window),button2);

    /*win:5861): Gtk-WARNING **: 01:33:09.639: Attempting to add a widget
     with type GtkButton to a GtkWindow, but as a GtkBin subclass
     a GtkWindow can only contain one widget at a time;
     it already contains a widget of type GtkButton*/
  
    /*This means only 1 container is to be placed inside a window*/
    /*gtk_container_add( GTK_CONTAINER(window),button1);*/
    /* Enter the main loop */
    gtk_widget_show_all (window);
    gtk_main ();
    return 0;
}
