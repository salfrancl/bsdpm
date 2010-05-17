/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * gtk2_callbacks.c
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

#include "../main.h"
#include "gtk2_callbacks.h"
#include "gtk2_main.h"


void bsdpm_gtk2_callback_destroy (GtkWidget *widget, gpointer data)
{
	gtk_main_quit ();
	
	return;
}

void bsdpm_gtk2_on_menubar_file_quit_activate (GtkImageMenuItem *self, gpointer user_data)
{
	gtk_main_quit ();
	
	return;
}

void bsdpm_gtk2_on_menubar_file_refresh_activate (GtkImageMenuItem *self, gpointer user_data)
{
	bsdpm_gtk2_set_cursor (BSDPM_GTK2_CURSOR_BUSY);
	bsdpm_gtk2_update_packageslist ();
	bsdpm_gtk2_refresh_packageslist ();
	bsdpm_gtk2_set_cursor (BSDPM_GTK2_CURSOR_NORMAL);
	
	return;
}

void bsdpm_gtk2_on_toolbar_tb_refresh_clicked (GtkToolButton *self, gpointer user_data)
{
	bsdpm_gtk2_set_cursor (BSDPM_GTK2_CURSOR_BUSY);
	bsdpm_gtk2_update_packageslist ();
	bsdpm_gtk2_refresh_packageslist ();
	bsdpm_gtk2_set_cursor (BSDPM_GTK2_CURSOR_NORMAL);
	
	return;
}

void bsdpm_gtk2_on_tvCategories_cursor_changed (GtkTreeView *self, gpointer user_data)
{
	bsdpm_gtk2_set_cursor (BSDPM_GTK2_CURSOR_BUSY);
	bsdpm_gtk2_do_search ();
	bsdpm_gtk2_set_cursor (BSDPM_GTK2_CURSOR_NORMAL);
	
	return;
}

void bsdpm_gtk2_on_tvPackageList_cursor_changed (GtkTreeView *self, gpointer user_data)
{
	bsdpm_gtk2_set_cursor (BSDPM_GTK2_CURSOR_BUSY);
	bsdpm_gtk2_show_package_information ();
	bsdpm_gtk2_set_cursor (BSDPM_GTK2_CURSOR_NORMAL);

	return;
}
