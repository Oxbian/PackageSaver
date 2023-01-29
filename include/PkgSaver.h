#ifndef DEF_PKGSAVER_H
#define DEF_PKGSAVER_H

#include <gtk/gtk.h>

typedef struct _treeViewer treeViewer;
struct _treeViewer
{
    GtkTreeView *treeView;
    GtkTreeStore *treeStore;
};

void init_packages(treeViewer *tv);
void on_ct2_toggled (GtkCellRendererToggle *cell, gchar *path_string, gpointer user_data);
void on_saveFile_clicked (GtkButton *btn, gpointer user_data);
void on_destroy();

#endif