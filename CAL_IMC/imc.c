#include <gtk-3.0/gtk/gtk.h>
#include <stdlib.h>
#include <string.h>

GtkLabel *resultado;
GtkEntry *ealtura;
GtkEntry *epeso;

void on_button_clicked (GtkWidget *widget, gpointer data) {
    const gchar *peso_str = gtk_entry_get_text(epeso);
    const gchar *altura_str = gtk_entry_get_text(ealtura);
    float peso_f = atof(peso_str);
    float altura_f = atof(altura_str);

    float imc = peso_f/(altura_f*altura_f);
   
    char status[20];

    if (imc < 18.5) {
        strcpy(status, "MAGREZA");
    } 
    else if (imc >= 18.5  && imc < 24.9) {
        strcpy(status, "NORMAL");
    }
    else if (imc >= 25  && imc < 29.9) {
        strcpy(status, "SOBREPESO");
    }
    else if (imc >= 30  && imc < 39.9) {
        strcpy(status, "OBESIDADE");
    }
    else if (imc >= 40) {
        strcpy(status, "OBESIDADE GRAVE");
    }

    char texto[] = "seu IMC é : ";
    char resultado2[50];
    g_snprintf(resultado2, 50, "%s%.2f %s", texto, imc, status);
    gtk_label_set_text(resultado, resultado2);

}   

void on_main_window_destroy (GtkWidget *widget, gpointer data) {
    gtk_main_quit();
}

int main (int argc, char *argv[]) {
    gtk_init(&argc, &argv);
    GtkBuilder *builder;
    builder = gtk_builder_new_from_file("IMC.glade");
    gtk_builder_add_callback_symbols( builder,
        "on_botao_clicked", G_CALLBACK(on_button_clicked),
        "on_mainwindow_destroy", G_CALLBACK(on_main_window_destroy),
        NULL
    );

    gtk_builder_connect_signals(builder, NULL);

    resultado = GTK_LABEL(gtk_builder_get_object(builder, "resultado"));
    ealtura = GTK_ENTRY(gtk_builder_get_object(builder, "ealtura"));
    epeso = GTK_ENTRY(gtk_builder_get_object(builder, "epeso"));
    GtkWidget *window = GTK_WIDGET(gtk_builder_get_object(builder, "mainwindow"));


    gtk_widget_show_all(window);
    gtk_main();

    return 0;
}