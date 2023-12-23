#include <gtk-3.0/gtk/gtk.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>

//parte da interface que exibe e recebe entrada de dados por isso deve ser um gtk entry justamente porque vai ser alterado 
//via codigo  
GtkEntry *display;
char operacao[100] = "SEM_OPERAÇÂO";
bool limpardisplay = false;
float segundo_numero = 0;
float primeiro_numero = 0;


/**
 * @param GtkWidget aqui ela recebe um widget do gtk que vai ser manipulado
 * @param gpointer aqui é um pointeiro para dados do gtk
 * 
*/

float lerdisplay () {
    const gchar *string = gtk_entry_get_text(display);
    float numero = atof(string);
    return numero;
}

void on_main_window_destroy(GtkWidget *widget, gpointer data) {
    gtk_main_quit();
}; 

void on_botao_clicked(GtkButton *button) {
    if (limpardisplay) {
        gtk_entry_set_text(display, "0");
        limpardisplay = false;
    }
    if (strcmp(gtk_entry_get_text(display), "0") == 0) {
        gtk_entry_set_text(display, gtk_button_get_label(button));
    }
    else {
        char texto[100];
        g_snprintf(texto, 100, "%s%s", gtk_entry_get_text(display), gtk_button_get_label(button));
        gtk_entry_set_text(display, texto);
    }
};

void on_botao_reset_clicked () {
    gtk_entry_set_text(display, "0");
};

void on_botao_ponto_clicked () {
    char texto[100];
    g_snprintf(texto, 100, "%s%s", gtk_entry_get_text(display), ",");
    gtk_entry_set_text(display, texto);
};

void on_botao_soma_clicked ()  {
    strcpy(operacao, "soma");
    primeiro_numero = lerdisplay();
    limpardisplay = true;
}; 

void on_botao_subtracao_clicked () {
    strcpy(operacao, "subtração");
    primeiro_numero = lerdisplay();
    limpardisplay = true;
};

void on_botao_divisao_clicked () {
    strcpy(operacao, "divisão");
    primeiro_numero = lerdisplay();
    limpardisplay = true;
};  

void on_botao_porcentagem_clicked () {
    strcpy(operacao, "porcentagem");
};

void on_botao_multiplicação_clicked () {
    strcpy(operacao, "multiplicação");
    primeiro_numero = lerdisplay();
    limpardisplay = true;
};

void on_botao_raizquadrada_clicked () {
    strcpy(operacao, "raiz_quadrada");
};

void on_botao_igual_clicked () {
    float segundo_numero = lerdisplay();
    float resultado = 0;
    char resultado2[100];

    if (strcmp(operacao, "SEM_OPERAÇÂO") == 0) {
        resultado =  segundo_numero;
    }
    else if (strcmp(operacao, "soma") == 0) {
        resultado =  segundo_numero + primeiro_numero;
    } 
    else if (strcmp(operacao, "divisão") == 0) {
        printf("%f %f", segundo_numero, primeiro_numero);

        resultado = primeiro_numero / segundo_numero;
    }
    else if (strcmp(operacao, "subtração") == 0) {
        resultado =  primeiro_numero - segundo_numero;
    }
    else if (strcmp(operacao, "multiplicação") == 0) {
        resultado =  primeiro_numero * segundo_numero;
    }
    else if (strcmp(operacao, "raiz_quadrada") == 0) {
        resultado = sqrtf(segundo_numero);
    }
    else if (strcmp(operacao, "porcentagem") == 0) {
        resultado =  segundo_numero/100;
    }
    sprintf(resultado2,"%f", resultado);
    gtk_entry_set_text(display, resultado2);
};

int main (int argc, char *argv[]) {
    gtk_init(&argc, &argv);
    GtkBuilder *builder;
    builder = gtk_builder_new_from_file("calculadora.glade");
    gtk_builder_add_callback_symbols(builder,
        "on_main_window_destroy", G_CALLBACK(on_main_window_destroy),
        "on_botao_clicked", G_CALLBACK(on_botao_clicked),
        "on_botao_reset_clicked", G_CALLBACK(on_botao_reset_clicked),
        "on_botao_ponto_clicked", G_CALLBACK(on_botao_ponto_clicked),
        "on_botao_igual_clicked", G_CALLBACK(on_botao_igual_clicked),
        "on_botao_soma_clicked", G_CALLBACK(on_botao_soma_clicked),
        "on_botao_subtracao_clicked", G_CALLBACK(on_botao_subtracao_clicked),
        "on_botao_divisao_clicked", G_CALLBACK(on_botao_divisao_clicked),
        "on_botao_porcentagem_clicked", G_CALLBACK(on_botao_porcentagem_clicked),
        "on_botao_multiplicação_clicked", G_CALLBACK(on_botao_multiplicação_clicked),
        "on_botao_raizquadrada_clicked", G_CALLBACK(on_botao_raizquadrada_clicked),
        NULL
    );
    gtk_builder_connect_signals(builder, NULL);

    display = GTK_ENTRY(gtk_builder_get_object(builder, "display"));
    gtk_entry_set_text(display, "0");


    GtkWidget *window = GTK_WIDGET(gtk_builder_get_object(builder, "mainwindow"));
    gtk_widget_show_all(window);
    gtk_main();

    return 0;
}