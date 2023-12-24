#include <gtk-3.0/gtk/gtk.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

char str[] = "X";
char matriz[3][3];
GtkLabel *texto;
GtkLabel *placar;

GtkButton *bt1;
GtkButton *bt2;
GtkButton *bt3;
GtkButton *bt4;
GtkButton *bt5;
GtkButton *bt6;
GtkButton *bt7;
GtkButton *bt8;
GtkButton *bt9;


char atual = 'X';
char label_placar[60] ="   placar    X = ( )    O = ( )    Velha = ( )        ";

char label_texto[14] = "Vez de 'X'";
int X_win;
int O_win;
int qvelha;

void usar_estilo () {
    GtkCssProvider *css_provider = gtk_css_provider_new();
    gtk_css_provider_load_from_path(css_provider, "velha.css", false);
    gtk_style_context_add_provider_for_screen(
            gdk_screen_get_default(),
            GTK_STYLE_PROVIDER(css_provider),
            GTK_STYLE_PROVIDER_PRIORITY_APPLICATION
    );
}

void init_matriz () {
    for (int i = 0; i < 3 ; i++) {
        for (int k = 0; k < 3; k++) {
            matriz[i][k] = 0;
        }
    }
    label_texto[8] = atual;
    gtk_label_set_text(texto, label_texto);
}

void on_reset_clicked () {
    init_matriz();
    gtk_button_set_label(bt1, "");
    gtk_button_set_label(bt2, "");
    gtk_button_set_label(bt3, "");
    gtk_button_set_label(bt4, "");
    gtk_button_set_label(bt5, "");
    gtk_button_set_label(bt6, "");
    gtk_button_set_label(bt7, "");
    gtk_button_set_label(bt8, "");
    gtk_button_set_label(bt9, "");
    label_texto[8] = 'X';
    g_print("%d %d %d <- ", X_win, O_win, qvelha);

    label_placar[18] = X_win + '0';
    label_placar[29] = O_win + '0';
    label_placar[44] = qvelha + '0';
    gtk_label_set_text(texto, label_texto);
    gtk_label_set_text(placar, label_placar);

}

void prox () {
    if (atual == 'X')  {
        atual = 'O';
        str[0] = 'O';
    }
    else {
        atual = 'X';
        str[0] = 'X';
    }
    label_texto[8] = str[0];
    gtk_label_set_text(texto, label_texto);
}

void on_mainwindow_destroy () {
    gtk_main_quit();
}

void win_x () {
    gtk_label_set_text(texto, "Parabéns X ganhou");
    X_win++;
    on_reset_clicked();
}

void win_o () {
    gtk_label_set_text(texto, "Parabéns O ganhou");
    O_win++;
    on_reset_clicked();
}

void velha () {
    gtk_label_set_text(texto, "Deu velha");
    qvelha++;
    on_reset_clicked();
}

void verify_velha() {
    int qtd = 0;
    for (int i = 0; i < 3 ; i++) {
        for (int k = 0; k < 3; k++) {
            if (matriz[i][k] == 'X' || matriz[i][k] == 'O') {
                qtd++;
            }
        }
    }
    if (qtd == 9) velha();
};


void verify_row () {
    int X = 0;
    int O = 0;
    for (int linha = 0; linha < 3; linha++) {
        for (int coluna = 0; coluna < 3; coluna++) {
            if (matriz[linha][coluna] == 'X') {
                X++;
            } 
            if (matriz[linha][coluna] == 'O') {
                O++;
            }
        }
        if (X == 3) {
            win_x();
        }
        else if (O == 3) {
            win_o();
        }
        
        X = 0;
        O = 0;
    }
};

void verify_column () {
    int X = 0;
    int O = 0;
    for (int coluna = 0; coluna < 3; coluna++) {
        for (int linha = 0; linha < 3; linha++) {
            if (matriz[linha][coluna] == 'X') {
                X++;
            } 
            if (matriz[linha][coluna] == 'O') {
                O++;
            }
        }
        if (X == 3) {
            win_x();
        }
        else if (O == 3) {
            win_o();
        }
       
        X = 0;
        O = 0;
    }
};

void verify_dp () {
    int X = 0;
    int O = 0;
    for (int x = 0; x < 3; x++) {
        if (matriz[x][x] == 'X') {
            X++;
        } 
        if (matriz[x][x] == 'O') {
            O++;
        }
    }
    if (X == 3) {
        win_x();
    }
    else if (O == 3) {
        win_o();
    }
   
};

void verify_sec () {
    int X = 0;
    int O = 0;
    int max = 2;
    for (int x = 0; x < 3; x++) {
        if (matriz[x][max] == 'X') {
            X++;
        } 
        if (matriz[x][max] == 'O') {
            O++;
        }
        max--;
    }
    if (X == 3) {
        win_x();
    }
    else if (O == 3) {
        win_o();
    }
  
};

void Win () {
    verify_row ();
    verify_column ();
    verify_dp ();
    verify_sec ();
    verify_velha();
}

void on_bt1_clicked (GtkButton *button, gpointer data) {
    if (matriz[0][0] == 0) {
        gtk_button_set_label(button, str);
        matriz[0][0] = atual;
        prox();
    }
    
    Win();
}
void on_bt2_clicked (GtkButton *button, gpointer data) {
    if (matriz[0][1] == 0) { 
        gtk_button_set_label(button, str);
        matriz[0][1] = atual;
        prox();
    }
 
    Win();
}
void on_bt3_clicked (GtkButton *button, gpointer data) {
    if (matriz[0][2] == 0) {
        gtk_button_set_label(button, str);
        matriz[0][2] = atual;
        prox();
    }

    Win();
}
void on_bt4_clicked (GtkButton *button, gpointer data) {
    if (matriz[1][0] == 0) {
        gtk_button_set_label(button, str);
        matriz[1][0] = atual;
        prox();
    }

    Win();
}
void on_bt5_clicked (GtkButton *button, gpointer data) {
    if (matriz[1][1] == 0) {
        gtk_button_set_label(button, str);
        matriz[1][1] = atual;
        prox();
    }

    Win();
}
void on_bt6_clicked (GtkButton *button, gpointer data) {
    if (matriz[1][2] == 0) {
        gtk_button_set_label(button, str);
        matriz[1][2] = atual;
        prox();
    }

    Win();
}
void on_bt7_clicked (GtkButton *button, gpointer data) {
    if(matriz[2][0] == 0) {
        gtk_button_set_label(button, str);
        matriz[2][0] = atual;
        prox();

    }
    Win();
}
void on_bt8_clicked (GtkButton *button, gpointer data) {
    if (matriz[2][1] == 0) {
        gtk_button_set_label(button, str);
        matriz[2][1] = atual;
        prox();
    }


    Win();
}
void on_bt9_clicked (GtkButton *button, gpointer data) {
    if (matriz[2][2] == 0) {
        gtk_button_set_label(button, str);
        matriz[2][2] = atual;
        prox();
    }

    Win();
}

int main (int argc, char *argv[]) {
    gtk_init(&argc, &argv);
    GtkBuilder *builder = gtk_builder_new_from_file("jogo _velha.glade");
    gtk_builder_add_callback_symbols(builder, 
        "on_mainwindow_destroy", G_CALLBACK(on_mainwindow_destroy),
        "on_reset_clicked", G_CALLBACK(on_reset_clicked),
        "on_bt1_clicked", G_CALLBACK(on_bt1_clicked),
        "on_bt2_clicked", G_CALLBACK(on_bt2_clicked),
        "on_bt3_clicked", G_CALLBACK(on_bt3_clicked),
        "on_bt4_clicked", G_CALLBACK(on_bt4_clicked),
        "on_bt5_clicked", G_CALLBACK(on_bt5_clicked),
        "on_bt6_clicked", G_CALLBACK(on_bt6_clicked),
        "on_bt7_clicked", G_CALLBACK(on_bt7_clicked),
        "on_bt8_clicked", G_CALLBACK(on_bt8_clicked),
        "on_bt9_clicked", G_CALLBACK(on_bt9_clicked),
        NULL
    );
    gtk_builder_connect_signals(builder, NULL);

    GtkWidget *window = GTK_WIDGET(gtk_builder_get_object(builder, "mainwindow"));
    texto = GTK_LABEL(gtk_builder_get_object(builder, "texto"));
    placar = GTK_LABEL(gtk_builder_get_object(builder, "placar"));
    bt1 = GTK_BUTTON(gtk_builder_get_object(builder, "bt1"));
    bt2 = GTK_BUTTON(gtk_builder_get_object(builder, "bt2"));
    bt3 = GTK_BUTTON(gtk_builder_get_object(builder, "bt3"));
    bt4 = GTK_BUTTON(gtk_builder_get_object(builder, "bt4"));
    bt5 = GTK_BUTTON(gtk_builder_get_object(builder, "bt5"));
    bt6 = GTK_BUTTON(gtk_builder_get_object(builder, "bt6"));
    bt7 = GTK_BUTTON(gtk_builder_get_object(builder, "bt7"));
    bt8 = GTK_BUTTON(gtk_builder_get_object(builder, "bt8"));
    bt9 = GTK_BUTTON(gtk_builder_get_object(builder, "bt9"));
  
    init_matriz();
    usar_estilo();
    gtk_widget_show_all(window);
    gtk_main();

}