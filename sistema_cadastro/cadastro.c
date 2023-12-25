#include <gtk-3.0/gtk/gtk.h>
#include <stdlib.h>
#include <stdbool.h>

GtkBuilder *builder;
GtkWidget *window;


void on_mainwindow_destroy () {
    gtk_main_quit();
}

void on_bt_listar_clicked () {

}

void on_bt_listar_voltar_clicked () {

}

void on_bt_cadastrar_clicked () {

}

void on_bt_cadvoltar_clicked () {

}

void on_sair_clicked () {

}

void on_listar_clicked () {

}

void on_cadastrar_clicked () {

}
void mensagem (char text[100], char secundary[100], char icon_name[100]) {
    GtkMessageDialog *mensagem_dialogo = gtk_builder_get_object(builder, "msg");
    g_object_set(mensagem_dialogo, "text", text, NULL);
    g_object_set(mensagem_dialogo, "secondary_text", secundary, NULL);
    g_object_set(mensagem_dialogo, "icon_name", icon_name, NULL);

    gtk_widget_show_all(mensagem_dialogo);
    gtk_dialog_run(mensagem_dialogo);
    gtk_widget_hide(mensagem_dialogo);

}

void login (char *email, char *senha, bool *lembrar) {
    if (strcmp(email, "admin") == 0 && strcmp(senha, "admin") == 0) {
        mensagem("bem-vindo", "usuario logado com sucesso", "dialog-ok");
    } else {
        mensagem("aviso", "email-ou-senha incorretos", "dialog-error");
    }
}

void on_login_clicked () {
    char *email = gtk_entry_get_text(gtk_builder_get_object(builder, "email"));
    char *senha = gtk_entry_get_text(gtk_builder_get_object(builder, "senha"));
    bool *lembrar = gtk_toggle_button_get_active(gtk_builder_get_object(builder, "lembrar"));
    login(email, senha, lembrar);
}

int main (int argc, char *agrv[]) {
    gtk_init(&argc, &agrv);

    builder = gtk_builder_new_from_file("sistemacadastro.glade");
    gtk_builder_add_callback_symbols(builder,
        "on_mainwindow_destroy", G_CALLBACK(on_mainwindow_destroy),
        "on_bt_listar_clicked", G_CALLBACK(on_bt_listar_clicked),
        "on_bt_listar_voltar_clicked", G_CALLBACK(on_bt_listar_voltar_clicked),
        "on_bt_cadastrar_clicked", G_CALLBACK(on_bt_cadastrar_clicked),
        "on_bt_cadvoltar_clicked", G_CALLBACK(on_bt_cadvoltar_clicked),
        "on_sair_clicked", G_CALLBACK(on_sair_clicked),
        "on_listar_clicked", G_CALLBACK(on_listar_clicked),
        "on_cadastrar_clicked", G_CALLBACK(on_cadastrar_clicked),
        "on_login_clicked", G_CALLBACK(on_login_clicked),
        NULL
    );

    gtk_builder_connect_signals(builder, NULL);

    window = GTK_WIDGET(gtk_builder_get_object(builder, "mainwindow"));

    gtk_widget_show_all(window);
    gtk_main();


    return 0;
}