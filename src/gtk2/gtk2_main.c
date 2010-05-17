/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * gtk2_main.c
 * Copyright (C) Leinier Cruz Salfran 2010 <salfrancl@yahoo.es>
 * 
 * libbsdpm_gtk2 is free software copyrighted by Leinier Cruz Salfran.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name ``Leinier Cruz Salfran'' nor the name of any other
 *    contributor may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 * 
 * libbsdpm_gtk2 IS PROVIDED BY Leinier Cruz Salfran ``AS IS'' AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL Leinier Cruz Salfran OR ANY OTHER CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
 * BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

#include <glib-object.h>
#include <gtk/gtk.h>
#include <gdk/gdk.h>

#include "../main.h"

#include "gtk2_main.h"
#include "gtk2_callbacks.h"

GtkBuilder *builder = NULL;

void bsdpm_gtk2_show_alert (GtkMessageType icon, GtkButtonsType buttons, const gchar *title, const gchar *reason)
{
GtkWindow *wWindow = NULL;
	
	wWindow = GTK_WINDOW (gtk_builder_get_object (builder, "main_window"));
	if (GTK_IS_WINDOW(wWindow))
	{
GtkMessageDialog *dialog;
	
	dialog = GTK_MESSAGE_DIALOG (gtk_message_dialog_new_with_markup (wWindow,
                                  GTK_DIALOG_DESTROY_WITH_PARENT,
                                  icon,
                                  buttons,
                                  "<b>%s</b>", title));
	gtk_message_dialog_format_secondary_markup (dialog,
												"<i><b>Reason:</b> %s</i>", reason);
	gtk_dialog_run (GTK_DIALOG (dialog));
	gtk_widget_destroy (GTK_WIDGET (dialog));
	}
	
	return;
}

GdkPixbuf *bsdpm_gtk2_gdk_pixbuf_new_from_file_scaled (gchar *filename, gint gtk_size)
{
GError *error = NULL;
GdkPixbuf *gOriginal, *gScaled;
gint w, h;
	
	gtk_icon_size_lookup (gtk_size , &w, &h);

	gOriginal = gdk_pixbuf_new_from_file (filename, &error);
	gScaled = gdk_pixbuf_scale_simple (gOriginal, w, h, GDK_INTERP_BILINEAR);

	g_object_unref (gOriginal);		

	return gScaled;
}

void bsdpm_gtk2_set_cursor (enum BSDPM_GTK2_CURSORS cursor)
{
GdkCursorType gcursortype = GDK_LEFT_PTR;
GtkWidget *widget;

	widget = GTK_WIDGET (gtk_builder_get_object (builder, "main_window"));
	if (GTK_IS_WIDGET(widget))
	{
		switch (cursor)
		{
			case BSDPM_GTK2_CURSOR_NORMAL:
				gcursortype = GDK_LEFT_PTR;
				break;
			case BSDPM_GTK2_CURSOR_BUSY:
				gcursortype = GDK_WATCH;
				break;
		}
	
		gdk_window_set_cursor (widget->window, gdk_cursor_new (gcursortype));
		gdk_window_process_all_updates ();
	}
	
	return;
}

int bsdpm_gtk2_download_callback (void *clientp, double dltotal, double dlnow, double ultotal, double ulnow)
{
int p;
char size_total_human_readable[8], size_read_human_readable[8];

	memset (size_total_human_readable, '\0', sizeof (size_total_human_readable));
	memset (size_read_human_readable, '\0', sizeof (size_read_human_readable));
	bsdpm_core_translate_size_to_human_readable (size_total_human_readable, dltotal);
	bsdpm_core_translate_size_to_human_readable (size_read_human_readable, dlnow);
	
	for (p = 0; p <= 64; p++)
		printf ("%c", 0x8);

	printf ("  %s [%s %s %s (%.3i%%)]", _("Downloading..."), size_read_human_readable, _("of"), size_total_human_readable, (int)((dlnow * 100) / dltotal));
	fflush (stdout);
	
	return 0;
}

int bsdpm_gtk2_process_callback (void *clientp, double dltotal, double dlnow, double ultotal, double ulnow)
{
int p;
char size_total_human_readable[8], size_read_human_readable[8];

	memset (size_total_human_readable, '\0', sizeof (size_total_human_readable));
	memset (size_read_human_readable, '\0', sizeof (size_read_human_readable));
	bsdpm_core_translate_size_to_human_readable (size_total_human_readable, dltotal);
	bsdpm_core_translate_size_to_human_readable (size_read_human_readable, dlnow);
	
	for (p = 0; p <= 64; p++)
		printf ("%c", 0x8);

	printf ("  %s [%s %s %s (%.3i%%)]", _("Downloading..."), size_read_human_readable, _("of"), size_total_human_readable, (int)((dlnow * 100) / dltotal));
	fflush (stdout);
	
	return 0;
}

void bsdpm_gtk2_update_packageslist (void)
{
int iError = 0;

	iError = bsdpm_core_download_packageslist (bsdpm_gtk2_download_callback);
	if (iError == BSDPM_NOERROR)
	{
		iError = bsdpm_core_extract_compressed_packageslist ();
			if (iError == BSDPM_NOERROR)
			{
				iError = bsdpm_core_process_index_file (bsdpm_gtk2_process_callback);
				if (iError == BSDPM_NOERROR)
				{
					bsdpm_core_unlink_packageslist ();
				} else {
					// Error: Can't write files to disk
					switch (iError)
					{
						case BSDPM_ERROR_INVALID_INDEX_FILE:
							bsdpm_gtk2_show_alert (GTK_MESSAGE_ERROR, GTK_BUTTONS_CLOSE, "Can't process INDEX file", "INDEX file is invalid, there is not access or doesn't exists.");
							break;
						case BSDPM_ERROR_CANT_OPEN_INDEX_FILE:
							bsdpm_gtk2_show_alert (GTK_MESSAGE_ERROR, GTK_BUTTONS_CLOSE, "Can't process INDEX file", "INDEX can't be openned.");
							break;
						//case BSDPM_ERROR_CANT_CREATE_CATEGORY_FILE:
						//	gtk_show_alert (GTK_MESSAGE_ERROR, GTK_BUTTONS_CLOSE, "Can't process CATEGORY file", "Can't create category file.");
						//	break;
					}
				}
			}
	} else {
		// Error: Can't download compressed INDEX file
		switch (iError)
		{
			case BSDPM_ERROR_UNKNOW_PROTOCOL:
				bsdpm_gtk2_show_alert (GTK_MESSAGE_ERROR, GTK_BUTTONS_CLOSE, "Can't download INDEX file", "Unknown protocol specified.");
				break;
			case BSDPM_ERROR_INVALID_PACKAGES_REPO:
				bsdpm_gtk2_show_alert (GTK_MESSAGE_ERROR, GTK_BUTTONS_CLOSE, "Can't download INDEX file", "Invalid packages repository URI.");
				break;
		}
	}

	return;
}

void bsdpm_gtk2_categories_add (GtkTreeStore *wTreeStore, const char * iconname,const char *szgroupname, const char *szgroupdescription, int istart, int iend)
{
int c, c1;
char *data[4];
GtkTreeIter iter, parentiter;

	data[0] = malloc (sizeof (char) * 32);
	data[1] = malloc (sizeof (char) * 512);
	data[2] = malloc (sizeof (char) * 32);
	data[3] = malloc (sizeof (char) * 1024);

	for (c1 = 0; c1 < 4; c1++)
		memset (data[c1], '\0', sizeof (data[c1]));
	
	sprintf (data[3], "<b>%s</b>: %s\n<b>%s</b>: %s", _("Group"), szgroupname, _("Description"), szgroupdescription);
	gtk_tree_store_append (wTreeStore, &parentiter, NULL);
	gtk_tree_store_set (wTreeStore, &parentiter, 0, iconname, 1, szgroupname, 2, szgroupdescription, 3, data[2], 4, data[3], -1);
	
	for (c = istart; c <= iend; c++)
	{
		for (c1 = 0; c1 < 4; c1++)
			memset (data[c1], '\0', sizeof (data[c1]));

		strcpy (data[0], _(bsdpm_categories_names[c]));
		strcpy (data[1], _(bsdpm_categories_descriptions[c]));
		sprintf (data[2], "(category_id = %i)", bsdpm_core_get_category_from_word (bsdpm_categories_names[c]));
		sprintf (data[3], "<b>%s</b>: %s\n<b>%s</b>: %s\n<b>%s</b> %s", _("Group"), szgroupname, _("Category"), data[0], _("Description"), data[1]);
		
		gtk_tree_store_append (wTreeStore, &iter, &parentiter);
		gtk_tree_store_set (wTreeStore, &iter, 0, bsdpm_categories_iconnames[c], 1, data[0], 2, data[1], 3, data[2], 4, data[3], -1);
	}
	
	for (c1 = 0; c1 < 4; c1++)
		free (data[c1]);
	
	return;
}

void bsdpm_gtk2_refresh_packageslist (void)
{
GtkTreeStore *wTreeStore;
GtkTreeView *wTreeView;
GtkTreeIter iter, parentiter;
char temp_text[BUFSIZ], temp_text1[BUFSIZ];

	wTreeStore = GTK_TREE_STORE (gtk_builder_get_object (builder, "liststore_categories"));
	if (GTK_IS_TREE_STORE(wTreeStore))
	{

		gtk_tree_store_clear (wTreeStore);

		memset (temp_text, '\0', sizeof (temp_text));
		sprintf (temp_text, "<b>%s</b>: %s\n<b>%s</b>: %s", _("Group"), _("all"), _("Description"), _("Show all packages"));
		gtk_tree_store_append (wTreeStore, &parentiter, NULL);
		gtk_tree_store_set (wTreeStore, &parentiter, 0, "gtk-dnd-multiple", 1, _("all"), 2, _("Show all packages"), 3, "id >= 0", 4, temp_text, -1);

		sprintf (temp_text, "<b>%s</b>: %s\n<b>%s</b>: %s", _("Group"), _("uninstalled"), _("Description"), _("Show all uninstalled packages"));
		gtk_tree_store_append (wTreeStore, &parentiter, NULL);
		gtk_tree_store_set (wTreeStore, &parentiter, 0, "bsdpm-package-uninstalled", 1, _("uninstalled"), 2, _("Show all uninstalled packages"), 3, "state = 0", 4, temp_text, -1);
		sprintf (temp_text, "<b>%s</b>: %s\n<b>%s</b>: %s", _("Group"), _("installed"), _("Description"), _("Show all installed packages"));
		gtk_tree_store_append (wTreeStore, &parentiter, NULL);
		gtk_tree_store_set (wTreeStore, &parentiter, 0, "bsdpm-package-installed", 1, _("installed"), 2, _("Show all installed packages"), 3, "state = 1", 4, temp_text, -1);
		sprintf (temp_text, "<b>%s</b>: %s\n<b>%s</b>: %s", _("Group"), _("upgradable"), _("Description"), _("Show all upgradable packages"));
		gtk_tree_store_append (wTreeStore, &parentiter, NULL);
		gtk_tree_store_set (wTreeStore, &parentiter, 0, "bsdpm-package-installed-upgradable", 1, _("upgradable"), 2, _("Show all upgradable packages"), 3, "state = 2", 4, temp_text, -1);

		bsdpm_core_init_categories ();

		bsdpm_gtk2_categories_add (wTreeStore, "stock_people", _("end-users"), _("Packages primarily for end-users"), 0x000, 0x00B);
		bsdpm_gtk2_categories_add (wTreeStore, "bsdpm-category-sysadmins", _("sysadmins"), _("Packages primarily for system administrators and developers"), 0x00C, 0x014);
		bsdpm_gtk2_categories_add (wTreeStore, "bsdpm-category-communications", _("comms"), _("Packages relating to computer communications and the Internet"), 0x015, 0x01F);
		bsdpm_gtk2_categories_add (wTreeStore, "bsdpm-category-x11", _("x-window"), _("Packages relating to the X window system"), 0x020, 0x028);
		bsdpm_gtk2_categories_add (wTreeStore, "bsdpm-category-science", _("science"), _("Packages relating to science and engineering"), 0x029, 0x02D);
		bsdpm_gtk2_categories_add (wTreeStore, "bsdpm-category-languages", _("languages"), _("Packages relating to human languages"), 0x02E, 0x03B);
		bsdpm_gtk2_categories_add (wTreeStore, "gnome-stock-blank", _("virtuals"), _("Packages in virtual categories (secondary groupings to above)"), 0x03C, 0x055);
		bsdpm_gtk2_categories_add (wTreeStore, "bsdpm-category-other", _("other"), _("All other packages"), 0x056, 0x05A);
		
		sprintf (temp_text, "<b>%s</b>: %s\n<b>%s</b>: %s", _("Group"), _("searches"), _("Description"), _("Packages matching searching criteria"));
		gtk_tree_store_append (wTreeStore, &parentiter, NULL);
		gtk_tree_store_set (wTreeStore, &parentiter, 0, "bsdpm-category-searches", 1, _("searches"), 2, _("Packages matching searching criteria"), 3, "", 4, temp_text, -1);

		memset (temp_text1, '\0', sizeof (temp_text1));
		strcpy (temp_text1, _("Packages matching with:"));
		strcat (temp_text1,  " \"");
		strcat (temp_text1,  _("package_name"));
		strcat (temp_text1,  "\" ");
		strcat (temp_text1,  _("contains"));
		strcat (temp_text1, " 'crack'");
		sprintf (temp_text, "<b>%s</b>: %s\n<b>%s</b>: %s", _("Group"), _("searches"), _("Description"), temp_text1);
		gtk_tree_store_append (wTreeStore, &iter, &parentiter);
		gtk_tree_store_set (wTreeStore, &iter, 0, "bsdpm-category-search", 1, "crack", 2, "", 3, "distribution_name LIKE '%crack%'", 4, temp_text, -1);
		
		wTreeView = GTK_TREE_VIEW (gtk_builder_get_object (builder, "tvCategories"));
		if (GTK_IS_TREE_VIEW (wTreeView))
		{
			gtk_tree_view_expand_all (wTreeView);
			gtk_tree_view_scroll_to_point (wTreeView, 0, 0);
		}
	}
	
	return;
}

int bsdpm_gtk2_packages_add (void *NotUsed, int argc, char **argv, char **azColName)
{
GtkListStore *liststore_packages;
GtkTreeIter TreeViewIter;
char tooltip_value[2048], temp_text[2048];

	liststore_packages = GTK_LIST_STORE (gtk_builder_get_object (builder, "liststore_packages"));
	if (GTK_IS_LIST_STORE (liststore_packages))
   	{
		// empty fields
		memset (tooltip_value, '\0', sizeof (tooltip_value));

		// set tooltip
		strcpy (tooltip_value, "<b>");
		strcat (tooltip_value, _("Package name"));
		strcat (tooltip_value, ":</b> ");
		strcat (tooltip_value, argv[2]);
		strcat (tooltip_value, "\n");
		if ((argv[1][0] == '0') || (argv[1][0] == '2'))
		{
			strcat (tooltip_value, "<b>");
			strcat (tooltip_value, _("Available version"));
			strcat (tooltip_value, ":</b> ");
			strcat (tooltip_value, argv[3]);
			strcat (tooltip_value, "\n");
		}
		if ((argv[1][0] == '1') || (argv[1][0] == '2'))
		{
			strcat (tooltip_value, "<b>");
			strcat (tooltip_value, _("Installed version"));
			strcat (tooltip_value, ":</b> ");
			if (argv[1][0] == '1')
				strcat (tooltip_value, argv[3]);
			if (argv[1][0] == '2')
				strcat (tooltip_value, argv[4]);
			strcat (tooltip_value, "\n");
		}
		strcat (tooltip_value, "<b>");
		strcat (tooltip_value, _("Comment"));
		strcat (tooltip_value, ":</b> ");
		strcat (tooltip_value, g_markup_escape_text (argv[6], -1));
		
		// set appropiate package status icon
		memset (temp_text, '\0', sizeof (temp_text));
		if (argv[1][0] == '0')
			strcpy (temp_text, "bsdpm-package-uninstalled");
		if (argv[1][0] == '1')
			strcpy (temp_text, "bsdpm-package-installed");
		if (argv[1][0] == '2')
			strcpy (temp_text, "bsdpm-package-installed-upgradable");
		
		// add to liststore
		gtk_list_store_append (liststore_packages, &TreeViewIter);
		gtk_list_store_set (liststore_packages, &TreeViewIter,
							0, temp_text,
							1, argv[2],
							2, argv[3],
							3, argv[4],
							4, argv[5],
							5, argv[6],
							6, argv[7],
							7, argv[8],
							8, argv[9],
							9, tooltip_value,
							-1);
   	}

	return 0;
}

void bsdpm_gtk2_do_search (void)
{
GtkTreeView *tvCategories, *tvPackageList;
GtkTreeSelection *tvCategories_TreeSelection;
GtkTreeIter TreeViewIter;
GtkTreeModel *TreeViewModel;
GValue search_criteria_value = {0};
GtkListStore *liststore_packages;
GtkTextBuffer *textbuffer_package_description;
char sql_statement[2048];

	tvCategories = GTK_TREE_VIEW (gtk_builder_get_object (builder, "tvCategories"));
	if (GTK_IS_TREE_VIEW (tvCategories))
	{
		tvCategories_TreeSelection = gtk_tree_view_get_selection (tvCategories);
		if (GTK_IS_TREE_SELECTION (tvCategories_TreeSelection))
		{
			if (gtk_tree_selection_get_selected (tvCategories_TreeSelection , &TreeViewModel , &TreeViewIter))
			{
				gtk_tree_model_get_value (TreeViewModel, &TreeViewIter, 3, &search_criteria_value);

				liststore_packages = GTK_LIST_STORE (gtk_builder_get_object (builder, "liststore_packages"));
				if (GTK_IS_LIST_STORE (liststore_packages))
					gtk_list_store_clear (liststore_packages);

				textbuffer_package_description = GTK_TEXT_BUFFER (gtk_builder_get_object (builder, "textbuffer_package_description"));
				if (GTK_IS_TEXT_BUFFER (textbuffer_package_description))
					gtk_text_buffer_set_text (textbuffer_package_description, "", -1);
				
				//memset (sql_statement, '\0', sizeof (sql_statement));
				sprintf (sql_statement, "SELECT DISTINCT * FROM packages INNER JOIN packages_categories ON (packages.id = packages_categories.package_id) WHERE (%s) GROUP BY id ORDER BY distribution_name;", g_value_get_string (&search_criteria_value));
				bsdpm_core_database_execute (sql_statement, bsdpm_gtk2_packages_add, 0);

				g_value_unset(&search_criteria_value);

			   	// scroll treeview to first item
				tvPackageList = GTK_TREE_VIEW (gtk_builder_get_object (builder, "tvPackageList"));
				if (GTK_IS_TREE_VIEW (tvPackageList))
				   	gtk_tree_view_scroll_to_point (tvPackageList, 0, 0);
			}
		}
	}

	return;
}
void bsdpm_gtk2_package_information_create_tags (void)
{
GtkTextBuffer *wBuffer;

	wBuffer = GTK_TEXT_BUFFER (gtk_builder_get_object (builder, "textbuffer_package_description"));
	if (GTK_IS_TEXT_BUFFER (wBuffer))
	{
		gtk_text_buffer_create_tag (wBuffer, "head1",
									"weight", PANGO_WEIGHT_BOLD,
									"scale", PANGO_SCALE_LARGE,
									"pixels_above_lines", 5,
									"pixels_below_lines", 20,
									"wrap_mode", GTK_WRAP_WORD,
									 NULL);
		gtk_text_buffer_create_tag (wBuffer, "text_normal",
									"family", "monospace",
									"scale", PANGO_SCALE_MEDIUM,
									"pixels_below_lines", 2,
									 NULL);
	}
	
	return;
}

void bsdpm_gtk2_replace_uri_with_widget (GtkTextView *wTextView, char *textbuffer)
{
GtkTextBuffer *wBuffer;
GtkTextIter iterstart, iterend;
GtkTextChildAnchor *wAnchor;
GtkWidget *wWidget;
PangoAttrList *attr_lst;
char szurl[16][512], *szfound, *szmarkup;
int turl = 0, pos = 0, posstart = 0, posend = 0, lastmatchlength = 0;

	wBuffer = gtk_text_view_get_buffer (wTextView);
	if (GTK_IS_TEXT_BUFFER (wBuffer))
	{
		for (;;)
		{
			// locate substring matching 'file://'
			szfound = strstr (textbuffer, "file://");
			if (szfound == NULL)
			{
				// locate substring matching 'ftp://'
				szfound = strstr (textbuffer, "ftp://");
				if (szfound == NULL)
				{
					// locate substring matching 'http://'
					szfound = strstr (textbuffer, "http://");
					if (szfound == NULL)
						break;
				}
			}
			
			// grab start position
			posstart = strlen (textbuffer) - strlen (szfound);
			
			// extract portion of text
			memset (szurl[turl], '\0', sizeof (szurl[turl]));
			bsdpm_core_substr (szurl[turl], textbuffer, posstart, posstart + (strlen (szfound) - 1));
			
			// grab the start and end position iterator
			gtk_text_buffer_get_iter_at_offset (wBuffer, &iterstart, posstart - lastmatchlength);
			gtk_text_buffer_get_iter_at_offset (wBuffer, &iterend, posstart - lastmatchlength);
			
			// grab total final position
			posend = posstart + strlen (szurl[turl]);
			
			// search for a delimiter character
			for (pos = 0; pos < strlen (szurl[turl]); pos++)
			{
				if ((szurl[turl][pos] == ' ') || (szurl[turl][pos] == '\n') || (szurl[turl][pos] == '\0'))
				{
					szurl[turl][pos] = '\0';
					posend = posstart + pos;
					break;
				}
				gtk_text_iter_forward_char (&iterend);
			}
			
			// grab the last match length
			lastmatchlength += (posend - posstart) - 1;
			
			// make pango markup text
			szmarkup = g_markup_printf_escaped ("<a href=\"%s\">%s</a>", szurl[turl], szurl[turl]);
			strcpy (szurl[turl], szmarkup);
			g_free (szmarkup);
			
			// empty matching substring in order to avoid repeating
			for (pos = posstart; pos < posend; pos++)
				textbuffer[pos] = ' ';
			
			// delete substring in text view
			gtk_text_buffer_delete (wBuffer, &iterstart, &iterend);
			gtk_text_buffer_create_child_anchor (wBuffer, &iterstart);
			
			turl++;
		}
		
		// walk trough text view in order to find created anchors and 
		// insert the widget containing the url
		turl = 0;
		gtk_text_buffer_get_start_iter (wBuffer, &iterstart);
		attr_lst = pango_attr_list_new ();
		pango_attr_list_insert (attr_lst, pango_attr_family_new ("monospace"));
		pango_attr_list_insert (attr_lst, pango_attr_scale_new (PANGO_SCALE_MEDIUM));
		while (gtk_text_iter_forward_char (&iterstart))
		{
			wAnchor = gtk_text_iter_get_child_anchor (&iterstart);
			if (GTK_IS_TEXT_CHILD_ANCHOR (wAnchor))
			{
				wWidget = GTK_WIDGET (gtk_label_new (""));
				gtk_label_set_markup (GTK_LABEL (wWidget), szurl[turl]);
				gtk_label_set_track_visited_links (GTK_LABEL (wWidget), true);
				gtk_label_set_attributes (GTK_LABEL (wWidget), attr_lst);
				gtk_text_view_add_child_at_anchor (wTextView, wWidget, wAnchor);
				gtk_widget_show_all (wWidget);
				
				turl++;
			}
		}
	}
	
	return;
}

void bsdpm_gtk2_show_package_information (void)
{
GtkTreeView *wTreeView;
GtkTreeSelection *wTreeSelection;
GtkTreeIter treeiter;
GtkTreeModel *tm;
GValue value = {0};
char szvalue[BUFSIZ], szpt[BUFSIZ], szpd[10 * 1024], sztextbuffer[10 * 1024];
GtkTextBuffer *wBuffer;
GtkTextIter textiter;
GtkTextView *wTextView;
GtkTextMark *textmark;
char *localeid;

	wTreeView = GTK_TREE_VIEW (gtk_builder_get_object (builder, "tvPackageList"));
	if (GTK_IS_TREE_VIEW (wTreeView))
	{
		wTreeSelection = gtk_tree_view_get_selection (wTreeView);
		if (GTK_IS_TREE_SELECTION (wTreeSelection))
		{
			if (gtk_tree_selection_get_selected (wTreeSelection , &tm , &treeiter))
			{
				gtk_tree_model_get_value (tm, &treeiter, 5, &value);
				strcpy (szpt, g_value_get_string (&value));

				wBuffer = GTK_TEXT_BUFFER (gtk_builder_get_object (builder, "textbuffer_package_description"));
				if (GTK_IS_TEXT_BUFFER (wBuffer))
				{
					wTextView = GTK_TEXT_VIEW (gtk_builder_get_object (builder, "nbPackageInformation_Description_TV"));
					if (GTK_IS_TEXT_VIEW (wTextView))
					{
						gtk_text_buffer_set_text (wBuffer, "", -1);
						gtk_text_buffer_get_iter_at_offset (wBuffer, &textiter, 0);
						textmark = gtk_text_buffer_create_mark (wBuffer, "pkgtitle", &textiter, TRUE);
						gtk_text_buffer_insert_with_tags_by_name (wBuffer, &textiter, szpt, -1, "head1", NULL);

						/*
						g_value_unset (&value);
						gtk_tree_model_get_value (tm, &treeiter, 12, &value);
						gtk_text_buffer_insert_with_tags_by_name (wBuffer, &textiter, "", -1, "right_justify", NULL);
						//sprintf (szvalue, "%s", (char *)g_value_get_string (&value));
						gtk_text_buffer_insert_pixbuf (wBuffer, &textiter, g_value_peek_pointer (&value));
						*/
						gtk_text_buffer_insert (wBuffer, &textiter, "\n", -1);

						memset (szvalue, '\0', sizeof (szvalue));
						g_value_unset (&value);
						gtk_tree_model_get_value (tm, &treeiter, 6, &value);
						strcpy (szvalue, g_value_get_string (&value));
						localeid = (char *)pango_language_to_string (gtk_get_default_language ());
						if (localeid != NULL)
						{
							if ((strcmp (localeid, "c") != 0) && (strncmp (localeid, "en", 2) != 0))
							{
								strcat (szvalue, ".");
								strncat (szvalue, localeid, 2);
							}
						}
						if (bsdpm_core_load_package_description (szvalue, szpd) == 0)
						{
							szvalue[strlen (szvalue) - 3] = '\0';
							if (bsdpm_core_load_package_description (szvalue, szpd) == 0)
								return;
						}

						gtk_text_buffer_insert_with_tags_by_name (wBuffer, &textiter, szpd, -1, "text_normal", NULL);
						
						// replace 'WWW' tag by 'GtkLabel' widget
						sprintf (sztextbuffer, "%s\n%s", szpt, szpd);
						//bsdpm_gtk2_replace_uri_with_widget (wTextView, sztextbuffer);

						//  delete 'Screenshot' tag

						gtk_text_view_scroll_mark_onscreen (wTextView, textmark);
						
						gtk_text_buffer_delete_mark (wBuffer, textmark);
					}
				}
			}
		}
	}
	
	return;
}

void bsdpm_gtk2_change_widget_size (gchar *name, gint width, gint height)
{
GtkWidget *wWidget;
	wWidget = GTK_WIDGET (gtk_builder_get_object (builder, name));
	if (GTK_IS_WIDGET (wWidget))
		gtk_widget_set_usize (GTK_WIDGET(wWidget), width, height);
}

void bsdpm_gtk2_do_main(int argc, char *argv[])
{
GtkWidget *window;
GError* error = NULL;

	/* Do initialization */
	gtk_set_locale ();
	gtk_init (&argc, &argv);

	/* Create main inteface*/
	builder = gtk_builder_new ();
	if (!gtk_builder_add_from_file (builder, bsdpm_config.gtk_ui_file, &error))
	{
		g_warning ("Couldn't load builder file: %s", error->message);
		g_error_free (error);
	}

	/* This is important */
	gtk_builder_connect_signals (builder, NULL);
	window = GTK_WIDGET (gtk_builder_get_object (builder, "main_window"));

	if (GTK_IS_WIDGET (window)) {
		/* Do some objects initializations */
		bsdpm_gtk2_package_information_create_tags ();
		bsdpm_gtk2_change_widget_size("iScreenshot", 213, 160);
		bsdpm_gtk2_change_widget_size("tvCategories", 250, -1);
		bsdpm_gtk2_change_widget_size("nbPackageInformation", -1, 250);
		gtk_window_maximize (GTK_WINDOW(window));
		

		/* Show the main window */
		gtk_widget_show (window);

		bsdpm_gtk2_refresh_packageslist ();

		/* GTK main loop */
		gtk_main ();

		/* Destroy GTKBuilder object */
		g_object_unref (builder);
	}

	return;
}
