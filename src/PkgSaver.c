#include "PkgSaver.h"

/**
 * @brief Function to init the TreeStore content with the packages names
 * 
 * @param tv TreeViewer which needs to be filled
 */
void init_packages(treeViewer *tv)
{
    FILE *fp;
    char buffer[1035];
    GtkTreeIter iter;

    /* Getting all the packages */
    fp = popen("pacman -Q | cut -d ' ' -f1", "r");
    if (fp == NULL) {
        fprintf(stderr, "Failed to get packages, please open an issue on github\n" );
        exit(1);
    }

    /* Read the packages, and adding them into the treeStore*/
    while (fgets(buffer, sizeof(buffer), fp) != NULL) 
    {
        gtk_tree_store_append (tv->treeStore, &iter, NULL);
        gtk_tree_store_set(tv->treeStore, &iter, 0, buffer, -1);
        gtk_tree_store_set(tv->treeStore, &iter, 1, FALSE, -1);
    }

    /* Closing the file */
    pclose(fp);
}

/**
 * @brief Function to get the value of the selected rows
 * 
 * @param selection Selected row
 */
void on_select_changed(GtkTreeSelection *selection) 
{ 

	gchar *value;
	gboolean box;
	GtkTreeIter iter;
	GtkTreeModel *model;

	if (gtk_tree_selection_get_selected(GTK_TREE_SELECTION(selection), &model, &iter) == FALSE) 
		return;
 
    /* Getting package column content */
	gtk_tree_model_get(model, &iter, 0, &value,  -1);
	printf("Select signal received: package = \"%s\"; ", value);

    /* Getting keeping ? column content */
	gtk_tree_model_get(model, &iter, 1, &box,  -1); // get column 1
	printf("keeping ? = \"%d\"\n", box);
}

/**
 * @brief Function to change the toggling of a row
 * 
 * @param cell The cell rendered (useless here)
 * @param path_string The path of the row we want
 * @param user_data TreeViewer which needs to be changed
 */
void on_ct2_toggled (GtkCellRendererToggle *cell, gchar *path_string, gpointer user_data) 
{ 
	GtkTreeIter iter;
	GtkTreeModel *model;
	gboolean isKept = FALSE;
	gchar *packageName;
    treeViewer *tv = (treeViewer*) user_data;

	model = gtk_tree_view_get_model(tv->treeView); // get the tree model

	gtk_tree_model_get_iter_from_string (model, &iter, path_string); // get iter from path

	gtk_tree_model_get(model, &iter, 0, &packageName, -1); //Getting the name of the package
	gtk_tree_model_get(model, &iter, 1, &isKept, -1); // Getting the value of the boolean

	if (isKept == FALSE) isKept = TRUE; else isKept = FALSE;

	gtk_tree_store_set(tv->treeStore, &iter, 1, isKept, -1); //Changing the checkbox toggling

	return;
}

/**
 * @brief Function to save packageName into a file
 * 
 * @param btn button clicked
 * @param user_data treeView in which data is
 */
void on_saveFile_clicked (GtkButton *btn, gpointer user_data)
{
    treeViewer *tv = (treeViewer*) user_data;
    GtkTreeModel *model = gtk_tree_view_get_model(tv->treeView);
    GtkTreeIter iter;
    gtk_tree_model_get_iter_first(model, &iter);
    FILE *fp;

    fp = fopen("pkgToSave.txt", "w");
    if (fp == NULL)
    {
        fprintf(stderr, "Error opening the file, please open an issue on github!");
        exit(1);
    }
    int row = 0;

	while (1) 
    {
        gchar *pkgName;
        gboolean isKept = FALSE;

        gtk_tree_model_get(model, &iter, 1, &isKept, -1); //Getting the bool of the row
        //fprintf(stderr, "row %d\n",row);
        /* Checking if the user asked to keep the row or not */
        if (isKept == TRUE)
        {
            gtk_tree_model_get(model, &iter, 0, &pkgName, -1); // Getting the packageName
            fputs(pkgName, fp);
        }

        if (gtk_tree_model_iter_next (model, &iter) == FALSE) 
        {
            break;
        }
        row++;
	}
    fclose(fp);
    //fprintf(stderr, "File closed");
}

void on_destroy()
{
    gtk_main_quit();
}