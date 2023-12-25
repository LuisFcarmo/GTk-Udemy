#include <gtk-3.0/gtk/gtk.h>
#include <stdlib.h>
#include <stdbool.h>

GtkBuilder *builder;
GtkWidget *window;
GtkStack *stack;
GtkListStore *modelo_armazenamento;

typedef struct usuario{
    int id;
    char name[100];
    char email[100];
    struct usuario *prox;
} user;


int id = 0;
user *cabecelho_user;
user *proximo_user;

void on_mainwindow_destroy () {
    gtk_main_quit();
}

void on_bt_listar_clicked () {
    user *refp = proximo_user;
    refp -> prox = NULL;
    char nome[100];
    char email[100];

    GtkTreeIter *iter;
    gtk_list_store_clear(modelo_armazenamento);
    //apontando para o começo da lista encadeada
    refp = cabecelho_user;
    for (int i = 0; i < id; i++) {
        gtk_list_store_append(modelo_armazenamento, &iter);
        gtk_list_store_set(modelo_armazenamento, &iter,
            0, (refp -> id),
            1, (refp -> name),
            2, (refp -> email),
            -1 );
        
        refp = refp -> prox;
    }
}

void on_bt_listar_voltar_clicked () {
    gtk_stack_set_visible_child_name(stack, "view_init");
}

void on_bt_cadastrar_clicked () {
    char *cad_nome = gtk_entry_get_text(gtk_builder_get_object(builder, "cad_nome"));
    char *cad_email = gtk_entry_get_text(gtk_builder_get_object(builder, "cad_email"));
    
    if (strcmp(cad_nome, "") == 0) {
        mensagem("aviso", "campo nome obrigatorio", "dialog error");
    } else {
        id++;
        proximo_user -> id = id;
        strcpy(proximo_user -> name, cad_nome);
        strcpy(proximo_user -> email, cad_email);
        
        char texto[100];

        g_snprintf(texto, 100, "%s%s%s", "Usuario ", proximo_user->name, " cadastrado");
        mensagem("aviso", texto, "dialog-emblem-defalt");

        proximo_user -> prox = (user *) malloc(sizeof(user)*1);
        proximo_user = proximo_user -> prox;

    }
}

void on_bt_cadvoltar_clicked () {
    gtk_stack_set_visible_child_name(stack, "view_init");
}

void on_sair_clicked () {
    gtk_stack_set_visible_child_name(stack, "view_login");
    g_object_set(window, "icon-name", "changes_prevent", NULL);

}

void on_listar_clicked () {
    gtk_stack_set_visible_child_name(stack, "view_listar");
}

void on_cadastrar_clicked () {
    gtk_stack_set_visible_child_name(stack, "view_cad");
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
        gtk_stack_set_visible_child_name(stack, "view_init");
        g_object_set(window, "icon-name", "avatar-default", NULL);
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
    cabecelho_user = (user*) malloc(sizeof(user)*1);
    proximo_user = cabecelho_user;

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

    stack = GTK_STACK(gtk_builder_get_object(builder, "stack"));
    modelo_armazenamento = GTK_LIST_STORE(gtk_builder_get_object(builder, "liststore1"));
    window = GTK_WIDGET(gtk_builder_get_object(builder, "mainwindow"));

    gtk_widget_show_all(window);
    gtk_main();


    return 0;
}