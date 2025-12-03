#ifndef GTKWINDOW_H
#define GTKWINDOW_H

#include <gtk/gtk.h>

extern char programmName[];
extern GtkWidget* window;
extern GtkWidget* vbox;
extern GtkWidget* hbox1;
extern GtkWidget* hbox2;
extern GtkWidget* g_entry;
extern char* file_selection();
extern void save_to_file(char* text, char* filePath);
extern void on_button_clicked_save(GtkWidget* widget, gpointer data);
extern void on_button_clicked_browse(GtkWidget* widget, gpointer data);
extern void on_button_clicked_encrypt(GtkWidget* widget, gpointer data);
extern void on_button_clicked_decrypt(GtkWidget* widget, gpointer data);
extern void gtkWindow();

#endif