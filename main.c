#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "gtkWindow.h"





int main(int argc, char* argv[]){

    gtk_init(&argc, &argv);
    printf("GTK erfolgreich initialisiert!");
    gtkWindow();

    

    return 0;

}