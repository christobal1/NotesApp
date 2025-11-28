#ifndef GTKWINDOW_H
#define GTKWINDOW_H

#include <gtk/gtk.h>

extern char programmName[];
extern GtkWidget* window;
extern GtkWidget* hbox;
extern GtkWidget* vbox;
extern GtkWidget* g_entry;
extern void on_button_clicked(GtkWidget* widget, gpointer data);
extern void gtkWindow();

#endif