#include <stdlib.h>
#include <gtk/gtk.h>

static int long count = 0L;

static void end_program (void){
    gtk_main_quit();
}

/*If we need to access passed data then callback func must have these parameters*/
static void counting (GtkWidget *wid, gpointer user_data){
#define counting_label user_data
    char buff [50] = {0};
    count++;
    snprintf(buff,sizeof(buff),"<b><u>\"Count Button\" Pressed %ld time%s</u></b>",count, ((count>1)?"s":" "));
    g_print("label addr = %p\n",counting_label);
    gtk_label_set_markup( GTK_LABEL(counting_label),buff);
}

int main (int argc, char *argv[]){

    GtkWidget *window = NULL;
    GtkWidget *button1 = NULL, *button2 = NULL;
    GtkWidget *vbox = NULL;

    /* Initialize GTK+ */
    gtk_init (&argc, &argv);

    /* Create the main window */
    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title (GTK_WINDOW (window), "Hello World");
    gtk_window_set_default_size (GTK_WINDOW (window), 500,400);
    g_signal_connect (window, "delete_event", G_CALLBACK(end_program), NULL); /* Optional */
    g_signal_connect (window, "destroy", G_CALLBACK(end_program), NULL); /* Optional */


    /* Create a vertical box with buttons and label*/
    button1 = gtk_button_new_with_label("Close Window");
    gtk_widget_set_size_request(button1,150,50);
    g_signal_connect (G_OBJECT (button1), "clicked", G_CALLBACK (end_program), NULL);


    GtkWidget *label = gtk_label_new("My Label");
    g_print("label addr = %p\n",label);
    gtk_label_set_markup( GTK_LABEL(label),"<b><i>Initail Label Text</i></b>");


    button2 = gtk_button_new_with_label("Count Button");
    gtk_widget_set_size_request(button2,150,50);
    g_signal_connect (button2, "clicked", G_CALLBACK(counting), label);


    vbox = gtk_vbox_new (GTK_ORIENTATION_VERTICAL, 6);

    gtk_box_pack_start (GTK_BOX(vbox), button2, TRUE, TRUE, 5);
    gtk_box_pack_start (GTK_BOX(vbox), label, FALSE, FALSE, 0);
    gtk_box_pack_start (GTK_BOX(vbox), button1, FALSE, FALSE, 0);

    gtk_container_add (GTK_CONTAINER(window), vbox);

    /* Enter the main loop */
    gtk_widget_show_all (window);
    gtk_main ();
    return 0;
}
