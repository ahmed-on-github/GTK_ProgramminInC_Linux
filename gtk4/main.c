#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>




typedef struct {
    GtkWidget **entry, **label;
} entry_label_t;
/*
#include <stdlib.h>

       long strtol(const char *restrict nptr,
                   char **restrict endptr, int base);
       long long strtoll(const char *restrict nptr,
                   char **restrict endptr, int base);
*/
static int multip_table(const char *str, char *buf){

    long num = 0 , i  = 0;
    char temp_buf [64]= {0};
    char *endptr = NULL;

    num = strtol(str, &endptr, 10);
    if(endptr == NULL){
      g_print("Enter a valid integer\r\n");
      return -1;
    }

    //buf[0] = '\0'; /*Start by terminating the buffer*/
    for( i = 1 ; i < 13 ; i++ ){
        snprintf(temp_buf, sizeof(temp_buf), "%d x %d = %d\n\0", num,i,num*i);
        g_print("%s\n",temp_buf);
        memcpy(buf + strlen(buf), temp_buf, strlen(temp_buf)+1); /* +1 for null terminator*/
    }
    return 0;
}

static void read_entry (GtkWidget *widget, gpointer user_data){

 const gchar *label_text = gtk_entry_get_text(GTK_ENTRY(*(((entry_label_t*)user_data)->entry)));

  char multip_table_12 [64*12] = {0};
  if( multip_table(label_text, multip_table_12) != 0 ){
    return;
  }


  /* Make it bold */
  static char *buff = NULL;

  if (buff != NULL){
    buff = (char *)realloc(buff, strlen(multip_table_12) + 8);
  }
  else{
    buff = (char *)malloc(strlen(multip_table_12) + 8);
  }
  strcpy(buff,"<b>\0");
  strcpy(buff + strlen(buff), multip_table_12);
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
 g_signal_connect (win, "destroy", gtk_main_quit, NULL);

  /* Create a vertical box with text entry, button and label */
  vbox = gtk_box_new (GTK_ORIENTATION_VERTICAL, 6);
  gtk_container_add (GTK_CONTAINER (win), vbox);


  entry = gtk_entry_new();
  gtk_entry_set_placeholder_text(GTK_ENTRY(entry), "Enter a number here");
  gtk_box_pack_start (GTK_BOX (vbox), entry, FALSE, FALSE, 0);


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
