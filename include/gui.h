#ifndef GUI_H
#define GUI_H

#include "protocol.h"
#include <gtk/gtk.h>
#include <string.h>
#include <stdlib.h>

typedef struct gui_data {
    char text[MAX_BUFFER_LEN];
} gui_data_t;

gboolean update_gui(gpointer data);
void show_text(const char* text);
void bttn_send_clicked(GtkWidget *widget, gpointer data);
void on_window_destroy(GtkWidget *widget, gpointer data);

void* launch_gui_thread(void* arg);

#endif // GUI_H