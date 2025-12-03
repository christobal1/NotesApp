#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <gtk/gtk.h>
#include "tinyfiledialogs.h"

char programmName[] = "NotesApp";
GtkWidget* window;
GtkWidget* vbox;
GtkWidget* hbox1;
GtkWidget* hbox2;


char* g_filePath = "/tmp/notesapp_placeholder.txt";

GtkWidget* g_textview;








char* file_selection(){
    const char* filters[] = { "*.txt", "*.md"};

    const char* file = tinyfd_openFileDialog(
        "Datei wählen",
        "",
        2,
        filters,
        "Text oder md Dateien",
        0
    );

    if (!file) {
        printf("Abgebrochen\n");
        return NULL;
    }

    printf("Ausgewählter absoluter Pfad:\n%s\n", file);

    // eigene Kopie erzeugen
    char* copy = malloc(strlen(file) + 1);
    if (!copy) return NULL;

    strcpy(copy, file);

    return copy;
}

void on_button_clicked_save(GtkWidget* widget, gpointer data);






char* load_from_file(char* filePath){

    int fd = open(filePath, O_RDONLY);

    if(fd == -1){
        perror("Fehler bei Öffnen der Datei (Für Lesen)\n");
        return NULL;
    }

    size_t capacity = 4096;
    size_t length = 0;
    char* buffer = malloc(capacity);
    if(!buffer){
        perror("Fehler bei malloc (Für Lesen)\n");
        close(fd);
        return NULL;
    }


    ssize_t bytesRead;

    while((bytesRead = read(fd, buffer + length, capacity - length)) > 0){
        length += bytesRead;
        //Speicher ggf vergrößern
        if(length == capacity){
            capacity *= 2;
            char* tmp = realloc(buffer, capacity);

            if(!tmp){
                perror("Fehler bei malloc (Für Realloc bei Lesen)\n");
                free(buffer);
                close(fd);
                return NULL;
            }

            buffer = tmp;

        }
    }

    if(bytesRead < 0){
        perror("Fehler bei Lesen\n");
        free(buffer);
        close(fd);
        return NULL;
    }

    close(fd);
    buffer[length] = '\0';

    return buffer;
}






void save_to_file(char* text, char* filePath){

    if(!filePath) return;

    int fd = open(filePath, O_WRONLY | O_CREAT | O_TRUNC, 0644);

    if(fd == -1){
        perror("Fehler beim Öffnen der Datei (Für Schreiben)\n");
        return;
    }

    ssize_t bytesWritten = write(fd, text, strlen(text));
    if(bytesWritten == -1){
        perror("Fehler bei write\n");
    }

    close(fd);
}








void on_button_clicked_save(GtkWidget* widget, gpointer data){

    if(!g_filePath){
        printf("Kein gültiger Pfad!\n");
        return;
    }

    GtkTextBuffer* buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(g_textview));
    GtkTextIter start, end;
    gtk_text_buffer_get_bounds(buffer, &start, &end);

    char* text = gtk_text_buffer_get_text(buffer, &start, &end, FALSE);
    
    save_to_file(text, g_filePath);

    g_free(text);

}





void on_button_clicked_browse(GtkWidget* widget, gpointer data){

    char* newPath = file_selection();

    if(newPath){

        if(g_filePath != NULL && g_filePath != "/tmp/notesapp_placeholder.txt"){
            free(g_filePath);
        }

        g_filePath = newPath;

        char* content = load_from_file(g_filePath);
        if(content){
            GtkTextBuffer* buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(g_textview));
            gtk_text_buffer_set_text(buffer, content, -1);
            free(content);
        }

    } else {
        printf("Dateipfad abgebrochen, Auswahl bleibt unverändert\n");
    }

}








void gtkWindow(){

    //Initialisieren
    

    GdkDisplay* display = gdk_display_get_default();
    GdkMonitor* monitor = gdk_display_get_primary_monitor(display);
    GdkRectangle geometry;
    gdk_monitor_get_geometry(monitor, &geometry);

    double windowX = 0.8 * geometry.width;
    double windowY = 0.8 * geometry.height;
    printf("Starte Window mit: %.2f x %.2f\n", windowX, windowY);

    //Fenster erstellen

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), programmName);
    gtk_window_set_default_size(GTK_WINDOW(window), windowX, windowY);

    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);



    GtkCssProvider* provider = gtk_css_provider_new();
    gtk_css_provider_load_from_data(
        provider,
        "* {background-color: black; color: white}"
        ".boxed-area {"
        "   border: 2px solid white;"
        "   border-radius: 8px;"
        "   padding: 10px;"
        "}",
        -1,
        NULL);
        
    gtk_style_context_add_provider_for_screen(
        gdk_screen_get_default(),
        GTK_STYLE_PROVIDER(provider),
        GTK_STYLE_PROVIDER_PRIORITY_USER
    );
    g_object_unref(provider);


    // ----------------------------------------------------

    //Inhalt

    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);

    hbox1 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);

    GtkWidget* buttonSave = gtk_button_new_with_label("Save");
    GtkWidget* buttonBrowse = gtk_button_new_with_label("Browse");
    gtk_widget_set_size_request(buttonSave, 130, 40);
    gtk_widget_set_size_request(buttonBrowse, 130, 40);


    hbox2 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    gtk_style_context_add_class(gtk_widget_get_style_context(hbox2), "boxed-area");

    GtkWidget* scroll = gtk_scrolled_window_new(NULL, NULL);
    GtkWidget* textview = gtk_text_view_new();
    g_textview = textview;
    gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(textview), GTK_WRAP_WORD);
    gtk_container_add(GTK_CONTAINER(scroll), textview);
    gtk_widget_set_size_request(scroll, windowX, windowY);


    gtk_box_pack_start(GTK_BOX(hbox1), buttonSave, FALSE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(hbox1), buttonBrowse, FALSE, FALSE, 5);


    gtk_box_pack_start(GTK_BOX(hbox2), scroll, TRUE, TRUE, 5);

    gtk_box_pack_start(GTK_BOX(vbox), hbox1, FALSE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(vbox), hbox2, FALSE, FALSE, 5);

    gtk_container_add(GTK_CONTAINER(window), vbox);

    


    //Signale
    
    g_signal_connect(buttonSave, "clicked", G_CALLBACK(on_button_clicked_save), NULL);
    g_signal_connect(buttonBrowse, "clicked", G_CALLBACK(on_button_clicked_browse), NULL);

    // ----------------------------------------------------


    //Alles anzeigen

    gtk_widget_show_all(window);

    //Hauptschleife starten

    gtk_main();
}