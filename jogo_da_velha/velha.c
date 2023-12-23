#include <gtk-3.0/gtk/gtk.h>
#include <string.h>
#include <stdbool.h>

char matriz[3][3];
int qt = 1;
bool player1_win = false;
bool player2_win = false;

void on_mainwindow_destroy (GtkWidget *widget, gpointer data) {
    gtk_main_quit();
}

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
            player1_win = true;
        }
        if (O == 3) {
            player2_win = true;
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
                g_print("%c", matriz[linha][coluna]);
            } 
            if (matriz[linha][coluna] == 'O') {
                O++;
            }
        }
        if (X == 3) {
            player1_win = true;
        }
        if (O == 3) {
            player2_win = true;
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
        player1_win = true;
    }
    if (O == 3) {
        player2_win = true;
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
    g_print("%d", X);
    g_print("%d", O);
    if (X == 3) {
        player1_win = true;
    }
    if (O == 3) {
        player2_win = true;
    }
};

void Win () {
    verify_row ();
    verify_column ();
    verify_dp ();
    verify_sec ();
   
}

void on_bt_clicked (GtkButton *button) {
    if (strcmp(gtk_button_get_label(button), "1")) {
        if (qt % 2 == 0) {
            gtk_button_set_label(button, "X");
            matriz[0][0] = 'X';
        } else  {
            gtk_button_set_label(button, "O");
            matriz[0][0] = 'O';
        }
    }  
    else if (strcmp(gtk_button_get_label(button), "2")) {
        if (qt % 2 == 0) {
            gtk_button_set_label(button, "X");
            matriz[0][1] = 'X';

        } else  {
            gtk_button_set_label(button, "O");
            matriz[0][1] = 'O';


        }
    }
    else if (strcmp(gtk_button_get_label(button), "3")) {
        if (qt % 2 == 0) {
            gtk_button_set_label(button, "X");
            matriz[0][2] = 'X';

        } else  {
            gtk_button_set_label(button, "O");
            matriz[0][2] = 'O';


        }
    }
    else if (strcmp(gtk_button_get_label(button), "4")) {
        if (qt % 2 == 0) {
            gtk_button_set_label(button, "X");
            matriz[1][0] = 'X';

        } else  {
            gtk_button_set_label(button, "O");
            matriz[1][0] = 'O';
        }
    }
    else if (strcmp(gtk_button_get_label(button), "5")) {
        if (qt % 2 == 0) {
            gtk_button_set_label(button, "X");
            matriz[1][1] = 'X';

        } else  {
            gtk_button_set_label(button, "O");
            matriz[1][1] = 'O';

        }
    }
    else if (strcmp(gtk_button_get_label(button), "6")) {
       if (qt % 2 == 0) {
            gtk_button_set_label(button, "X");
            matriz[1][2] = 'X';

        } else  {
            gtk_button_set_label(button, "O");
            matriz[1][2] = 'O';


        }
    }
    else if (strcmp(gtk_button_get_label(button), "7")) {
        if (qt % 2 == 0) {
            gtk_button_set_label(button, "X");
            matriz[2][0] = 'X';

        } else  {
            gtk_button_set_label(button, "O");
            matriz[2][0] = 'O';

        }
    }
    else if (strcmp(gtk_button_get_label(button), "8")) {
        if (qt % 2 == 0) {
            gtk_button_set_label(button, "X");
            matriz[2][1] = 'X';

        } else  {
            gtk_button_set_label(button, "O");
            matriz[2][1] = 'O';

        }
    }
    else if (strcmp(gtk_button_get_label(button), "9")) {
        if (qt % 2 == 0) {
            gtk_button_set_label(button, "X");
            matriz[2][2] = 'X';

        } else  {
            gtk_button_set_label(button, "O");
            matriz[2][2] = 'O';

        }
    }
   
    qt++;
    Win();
    if (player1_win) {
        g_print("Player X ganhou\n");
    }
    if (player2_win) {
        g_print("Player O ganhou\n");
    }
}

int main (int argc, char *argv[]) {
    gtk_init(&argc, &argv);
    GtkBuilder *builder;
    builder = gtk_builder_new_from_file("jogo_da_velha.glade");

    gtk_builder_add_callback_symbols(builder,
    "on_mainwindow_destroy", G_CALLBACK(on_mainwindow_destroy),
    "on_bt_clicked", G_CALLBACK(on_bt_clicked),
    NULL);

    gtk_builder_connect_signals(builder, NULL);

    GtkWidget *window = GTK_WIDGET(gtk_builder_get_object(builder, "mainwindow"));

    gtk_widget_show_all(window);
    gtk_main();


}