#include <stdlib.h>
#include <gtk/gtk.h>

typedef struct {
    GtkWidget **entry, **label;
} entry_label_t;

static void read_entry (GtkWidget *widget, gpointer user_data){

  const gchar *label_text = gtk_entry_get_text(GTK_ENTRY(*(((entry_label_t*)user_data)->entry)));
  /* Make it bold */
  static char *buff = NULL;

  if (buff != NULL){
    buff = (char *)realloc(buff, strlen(label_text) + 8);
  }
  else{
    buff = (char *)malloc(strlen(label_text) + 8);
  }
  strcpy(buff,"<b>\0");
  strcpy(buff + strlen(buff), label_text);
  strcpy(buff + strlen(buff), "</b>\0");

  //gtk_label_set_text
  gtk_label_set_markup(GTK_LABEL(*(((entry_label_t*)user_data)->label) ),(const char *)buff);
}

int main (int argc, char *argv[]){
  GtkWidget *win = NULL;
  GtkWidget *vbox = NULL;
  GtkWidget *button = NULL;
  GtkWidget *entry = NULL;
  GtkWidget *label = NULL;

  entry_label_t instance = {&entry, &label};

  /* Initialize GTK+ */
  gtk_init (&argc, &argv);

  /* Create the main window */
  win = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_container_set_border_width (GTK_CONTAINER (win), 8);
  gtk_window_set_title (GTK_WINDOW (win), "Hello World");
  //gtk_window_set_default_size(GTK_WINDOW (win), 250,250);
 gtk_window_set_position (GTK_WINDOW (win), GTK_WIN_POS_CENTER);
  g_signal_connect (win, "destroy", gtk_main_quit, NULL);

  /* Create a vertical box with text entry, button and label */
  vbox = gtk_box_new (GTK_ORIENTATION_VERTICAL, 6);
  gtk_container_add (GTK_CONTAINER (win), vbox);


  entry = gtk_entry_new();
  gtk_entry_set_placeholder_text(GTK_ENTRY(entry), "Enter text here");
  gtk_box_pack_start (GTK_BOX (vbox), entry, FALSE, FALSE, 0);


  button = gtk_button_new_with_label("Get Text");
  gtk_widget_set_size_request(button,150,50);
  g_signal_connect (G_OBJECT (button), "clicked", G_CALLBACK (read_entry), (gpointer)(&instance) );
  gtk_box_pack_start (GTK_BOX (vbox), button, FALSE, FALSE, 0);

  button = gtk_button_new_with_label("Get Text");
  gtk_widget_set_size_request(button,150,50);
  g_signal_connect (G_OBJECT (button), "clicked", G_CALLBACK (read_entry), (gpointer)(&instance) );
  gtk_box_pack_start (GTK_BOX (vbox), button, FALSE, FALSE, 0);

  label = gtk_label_new("Text Label");
  gtk_box_pack_start (GTK_BOX(vbox), label, FALSE, FALSE, 0);

  gtk_container_set_border_width(GTK_CONTAINER (win),12);
  gtk_box_set_spacing(GTK_BOX (vbox),5);

  /* Enter the main loop */
  gtk_widget_show_all (win);
  gtk_main ();
  return 0;
}
