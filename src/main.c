#include "PkgSaver.h"

int main(int argc, char *argv[])
{
    /*Initialisation of the window*/
    gtk_init(&argc, &argv);

    GtkBuilder *builder = gtk_builder_new_from_file("src/packageSaver.glade");
    GtkWidget *window = GTK_WIDGET(gtk_builder_get_object(builder, "window"));

    g_signal_connect(window, "destroy", G_CALLBACK(on_destroy), NULL);
    gtk_builder_connect_signals(builder, NULL);


    /*Initialisation of the component of the window*/
    treeViewer tv;
    tv.treeView = GTK_TREE_VIEW(gtk_builder_get_object(builder, "tv1"));
    tv.treeStore = GTK_TREE_STORE(gtk_builder_get_object(builder, "TreeStore"));
    GtkTreeViewColumn *cx1 = GTK_TREE_VIEW_COLUMN(gtk_builder_get_object(builder, "cx1"));
    GtkTreeViewColumn *cx2 = GTK_TREE_VIEW_COLUMN(gtk_builder_get_object(builder, "cx2"));
    GtkCellRenderer *ct1 = GTK_CELL_RENDERER(gtk_builder_get_object(builder, "ct1"));
    GtkCellRenderer *ct2 = GTK_CELL_RENDERER(gtk_builder_get_object(builder, "ct2"));
    GtkTreeSelection *select = GTK_TREE_SELECTION(gtk_builder_get_object(builder, "select"));

    gtk_tree_view_column_add_attribute(cx1, ct1, "text", 0); // attach renderer to column
    gtk_tree_view_column_add_attribute(cx2, ct2, "active", 1); // attach renderer to column

    select = gtk_tree_view_get_selection(GTK_TREE_VIEW(tv.treeView));

    /*Init the content of the treestore (all the name of packages)*/
    init_packages(&tv);

    /*Connection all the signal*/
    g_signal_connect (ct2, "toggled", G_CALLBACK (on_ct2_toggled), &tv);

	gtk_widget_show_all(window);

	gtk_main();
	return EXIT_SUCCESS;
}

// TODO: free all when exiting
// saving the actions into a file ou clipboard
// adding a research by name feature