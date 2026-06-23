#include "../include/gui.h"
#include "../include/client.h"

GtkWidget *text_view;
GtkWidget *entry;

gboolean update_gui(gpointer data)
{
    gui_data_t* gui_data = (gui_data_t *)data;
    GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view));
    GtkTextIter end;
    gtk_text_buffer_get_end_iter(buffer, &end);
    gtk_text_buffer_insert(buffer, &end, gui_data->text, -1);
    
    free(gui_data);
    return G_SOURCE_REMOVE;
}

void show_text(const char* text)
{
    gui_data_t *gui_data = calloc(1, sizeof(gui_data_t)); 
    strncpy(gui_data->text, text, MAX_BUFFER_LEN - 1);
    g_idle_add(update_gui, gui_data);
}

void bttn_send_clicked(GtkWidget *widget, gpointer data)
{
    (void)widget; (void)data;
    const gchar *text_input = gtk_entry_get_text(GTK_ENTRY(entry));
    
    if (!text_input || strlen(text_input) == 0) return;

    char buffer[MAX_BUFFER_LEN] = {0}; 
    strncpy(buffer, text_input, MAX_BUFFER_LEN - 1);
    
    send_message(buffer); 
    
    char local_message[MAX_BUFFER_LEN] = {0};
    snprintf(local_message, MAX_BUFFER_LEN, "Tu: %.500s\n", buffer);
    show_text(local_message);
    
    gtk_entry_set_text(GTK_ENTRY(entry), "");
}

void on_window_destroy(GtkWidget *widget, gpointer data)
{
    (void)widget; (void)data;
    net_data.is_running = 0; 
    gtk_main_quit();
}

void* launch_gui_thread(void* arg)
{
    (void)arg;
    gtk_init(&net_data.argc, &net_data.argv);

    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    char title[64];
    snprintf(title, sizeof(title), "Cliente Rank %d", net_data.rank_id);
    gtk_window_set_title(GTK_WINDOW(window), title);
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 300);
    g_signal_connect(window, "destroy", G_CALLBACK(on_window_destroy), NULL);

    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    GtkWidget *scroll = gtk_scrolled_window_new(NULL, NULL);
    gtk_box_pack_start(GTK_BOX(vbox), scroll, TRUE, TRUE, 0);

    text_view = gtk_text_view_new();
    gtk_text_view_set_editable(GTK_TEXT_VIEW(text_view), FALSE);
    gtk_container_add(GTK_CONTAINER(scroll), text_view);

    GtkWidget *hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 0);

    entry = gtk_entry_new();
    gtk_box_pack_start(GTK_BOX(hbox), entry, TRUE, TRUE, 0);

    GtkWidget *button = gtk_button_new_with_label("Enviar");
    gtk_box_pack_start(GTK_BOX(hbox), button, FALSE, FALSE, 0);
    
    g_signal_connect(button, "clicked", G_CALLBACK(bttn_send_clicked), NULL);
    g_signal_connect(entry, "activate", G_CALLBACK(bttn_send_clicked), NULL);

    gtk_widget_show_all(window);
    gtk_main();

    return NULL;
}

/*
 * REFS:
 * https://stackoverflow.com/questions/2589749/how-to-initialize-array-to-0-in-c
 * https://docs.gtk.org/gtk3/
 * 
 *
*/