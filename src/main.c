/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * main.c
 * Copyright (C) Leinier Cruz Salfran 2010 <salfrancl@yahoo.es>
 *
 * bsdpm is free software copyrighted by Leinier Cruz Salfran.
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
 * bsdpm IS PROVIDED BY Leinier Cruz Salfran ``AS IS'' AND ANY EXPRESS
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

/*
 * Headers includes
 */
#include <getopt.h>
#include "main.h"


/*
 * Variables
 */
#if defined(HAVE_GTK2) || defined(HAVE_QT4)
int interface = 0;
#endif
unsigned short want_update_packages_list = 0;
unsigned short want_search = 0;
char *search_criteria;
unsigned short want_install = 0;
char *install_packages;
unsigned short want_deinstall = 0;
char *deinstall_packages;
unsigned short want_upgrade = 0;


/*
 * Code blocks
 */
void bsdpm_show_program_header (bool complete)
{
short c = 0;
char title[255];
char mode_table[64];

	snprintf (mode_table, sizeof (mode_table), bsdpm_config.mode_table);
	if (complete == true)
	{
		snprintf (title, sizeof (title), _("BSD Ports/Packages Manager"));
	} else {
		mode_table[0] = toupper (mode_table[0]);
		snprintf (title, sizeof (title), "BSD %s Manager", mode_table);
		snprintf (title, sizeof (title), _(title));
	}

	printf ("%s\n", title);
	for (c = 0; c < strlen (title); c++)
		printf ("=");
	printf ("\n\n");

	return;
}

void bsdpm_show_usage (void)
{
	bsdpm_show_program_header (true);

	printf ("%s: bsdpm [%s]\n", _("Usage"), _("OPTION"));
	printf ("%s:\n\tbsdpm -i ", _("Examples"));
#if !defined(HAVE_GTK2) && !defined(HAVE_QT4)
	printf ("mc\n");
#endif
#if defined(HAVE_GTK2) || defined(HAVE_QT4)
	printf ("xorg\n\tbsdpm --install '");
#ifdef HAVE_GTK2
	printf ("gnome2 ");
#endif
#ifdef HAVE_QT4
	printf ("kde4 ");
#endif
	printf ("compiz emerald-themes'\n");
#ifdef HAVE_GTK2
	printf ("\tbsdpm -I gtk\n");
#endif
#ifdef HAVE_QT4
	printf ("\tbsdpm -I qt\n");
#endif
#endif
	printf ("\n%s:\n", _("Options"));
	printf ("  -h, --help                  %s\n", _("Show this help messages"));
	printf ("  -c, --config-file <file>    %s\n", _("Set an alternative configuration file"));
	printf ("  -u, --update-packages-list  %s\n", _("Recreate the BSDPM database"));
	printf ("  -s, --search                %s\n", _("Search on the BSDPM database"));
	printf ("  -i, --install <name>        %s\n", _("Install port(s)/package(s)"));
	printf ("  -d, --deinstall <name>      %s\n", _("Deinstall port(s)/package(s)"));
	printf ("  -U, --upgrade-system        %s\n", _("Upgrade the whole system"));
	printf ("  -m, --mode <mode>           %s\n", _("Mode to use"));
	printf ("                              mode: [0 .. %s,\n", _("only ports (default)"));
	printf ("                                     1 .. %s]\n", _("only packages"));
	printf ("  -C, --create-packages       %s\n", _("Wether to create packages or not"));
#if defined(HAVE_GTK2) || defined(HAVE_QT4)
	printf ("  -I, --interface <backend>   %s\n", _("Start BSDPM with a graphical user interface"));
	printf ("                              backend: [");
#ifdef HAVE_GTK2
	printf ("gtk");
#ifdef HAVE_QT4
	printf (" | ");
#endif
#endif
#ifdef HAVE_QT4
	printf ("qt");
#endif
	printf ("]\n");
#endif

	return;
}

int bsdpm_download_callback (void *clientp, double dltotal, double dlnow, double ultotal, double ulnow)
{
int percent = 0;
char message[80], size_total_human_readable[16], size_read_human_readable[16];

	if (dlnow > 0)
	{
        memset (size_total_human_readable, '\0', sizeof (size_total_human_readable));
        memset (size_read_human_readable, '\0', sizeof (size_read_human_readable));
        bsdpm_core_translate_size_to_human_readable (size_total_human_readable, dltotal);
        bsdpm_core_translate_size_to_human_readable (size_read_human_readable, dlnow);

        for (percent = 0; percent < 50; percent++)
            printf ("%c", 0x8);

        percent = (int)((dlnow * 100) / dltotal);
		snprintf (message, sizeof (message), "  %s... [%s %s %s (%i%%)]", _("Downloading"), size_read_human_readable, _("of"), size_total_human_readable, percent);

        for (percent = strlen (message); percent < 50; percent++)
            strcat (message, " ");

        printf ("%s", message);
        fflush (stdout);
	}

	return 0;
}

int bsdpm_process_callback (void *clientp, double dltotal, double dlnow, double ultotal, double ulnow)
{
int percent = 0;

	printf ("%c%c%c%c%c%c", 0x8, 0x8, 0x8, 0x8, 0x8, 0x8);

	percent = (int)((dlnow * 100) / dltotal);
	if ((percent >= 0) && (percent <= 100))
	{
		printf ("(%3i%%)", percent);
		fflush (stdout);
	}

	return 0;
}

void bsdpm_update_packages_list (void)
{
BSDPM_ERRORS error = BSDPM_NOERROR;
int c = 0;
char message[255];

	bsdpm_show_program_header (false);

	snprintf (message, sizeof (message), "Updating %s list", bsdpm_config.mode_table);
	printf ("%s...\n", _(message));

	printf ("  %s... ", _("Downloading"));
	for (c = (strlen (_("Downloading")) + 6); c < 50; c++)
		printf (" ");
	fflush (stdout);
	error = bsdpm_core_download_packageslist (bsdpm_download_callback);
	if (error == BSDPM_NOERROR)
	{
		printf ("\n");
		// is 'packages mode' active?
		if (bsdpm_config.mode == 1)
		{
			printf ("  %s...\n", _("Extracting"));
			error = bsdpm_core_extract_compressed_packageslist ();
		}
		if (error == BSDPM_NOERROR)
		{
			printf ("  %s...       ", _("Processing INDEX file"));
			fflush (stdout);
			error = bsdpm_core_process_index_file (bsdpm_process_callback);
			if (error == BSDPM_NOERROR)
			{
                printf ("\n  %s...       ", _("Processing dependencies"));
                fflush (stdout);
                error = bsdpm_core_process_dependencies (bsdpm_process_callback);
                if (error == BSDPM_NOERROR)
                {
                    bsdpm_core_unlink_packageslist ();
                    printf ("\n%s.\n", _("Done"));
                } else {
                    switch (error)
                    {
                        case BSDPM_ERROR_DATABASE_IS_CORRUPT:
                            printf ("%s: %s.\n", _("Can't process dependencies"), _("The database structure is corrupt"));
                            break;
                        default:
                            break;
                    }
                }
			} else {
				switch (error)
				{
					case BSDPM_ERROR_INVALID_FILE:
						printf ("%s: %s.\n", _("Can't process INDEX file"), _("INDEX file is invalid, there is not access or doesn't exists"));
						break;
					case BSDPM_ERROR_CANT_OPEN_FILE:
						printf ("%s: %s.\n", _("Can't process INDEX file"), _("INDEX can't be openned"));
						break;
                    default:
                        break;
				}
			}
		} else {
			printf ("%s.\n", _("Can't extract compressed INDEX file"));
		}
	} else {
		switch (error)
		{
			case BSDPM_ERROR_CANT_DOWNLOAD_FILE:
				printf ("\n[%s] %s: %s.\n", _("ERROR"), _("Can't download INDEX file"), _("The file can't be downloaded"));
				break;
            default:
                break;
		}
	}

	return;
}

BSDPM_ERRORS bsdpm_search_callback (BSDPM_SEARCH_OPERATION operation, bsdpm_port_information *port_information)
{
unsigned short i = 0, mll = 0;
char *state = _("State");
char *distribution_name = _("Distribution name");
char *available_version = _("Available version");
char *installed_version = _("Installed version");
char *port_path = _("Port path");
char *comment = _("Comment");
char *maintainer = _("Maintainer");
char *www = _("WWW");

	switch (operation)
	{
		case BSDPM_SEARCH_OPERATION_SEARCHING:
			break;
		case BSDPM_SEARCH_OPERATION_PROCESS_RESULT:
			// print header line
			for (i = 0; i < 60; i++)
				printf ("=");
			printf ("\n");

			// get the maximum label length
			mll = strlen (state);
			mll = (strlen (distribution_name) > mll ? strlen (distribution_name) : mll);
			mll = (strlen (available_version) > mll ? strlen (available_version) : mll);
			mll = (strlen (installed_version) > mll ? strlen (installed_version) : mll);
			mll = (strlen (port_path) > mll ? strlen (port_path) : mll);
			mll = (strlen (comment) > mll ? strlen (comment) : mll);
			mll = (strlen (maintainer) > mll ? strlen (maintainer) : mll);
			mll = (strlen (www) > mll ? strlen (www) : mll);

			// print labels with values
			for (i = 0; i < (mll - strlen (state)); i++) printf (" ");
			printf (" %s: ", state);
			if (port_information->state == '0')
				printf ("%s", _("Uninstalled"));
			if (port_information->state == '1')
				printf ("%s", _("Installed"));
			if (port_information->state == '2')
				printf ("%s", _("Upgradable"));
			printf ("\n");
			for (i = 0; i < (mll - strlen (distribution_name)); i++) printf (" ");
			printf (" %s: %s\n", distribution_name, port_information->distribution_name);
			if ((port_information->state == '0') || (port_information->state == '2'))
			{
				for (i = 0; i < (mll - strlen (available_version)); i++) printf (" ");
				printf (" %s: %s\n", available_version, port_information->available_version);
			}
			if ((port_information->state == '1') || (port_information->state == '2'))
			{
				for (i = 0; i < (mll - strlen (installed_version)); i++) printf (" ");
				printf (" %s: ", installed_version);
				if (port_information->state == '1')
					printf ("%s\n", port_information->available_version);
				if (port_information->state == '2')
					printf ("%s\n", port_information->installed_version);
			}
			for (i = 0; i < (mll - strlen (port_path)); i++) printf (" ");
			printf (" %s: %s\n", port_path, port_information->port_path);
			for (i = 0; i < (mll - strlen (comment)); i++) printf (" ");
			printf (" %s: %s\n", comment, port_information->comment);
			for (i = 0; i < (mll - strlen (maintainer)); i++) printf (" ");
			printf (" %s: %s\n", maintainer, port_information->maintainer);
			for (i = 0; i < (mll - strlen (www)); i++) printf (" ");
			printf (" %s: %s\n", www, port_information->www);

			// print foot line
			for (i = 0; i < 60; i++)
				printf ("=");
			printf ("\n");

			break;
	}

	return BSDPM_NOERROR;
}

BSDPM_ERRORS bsdpm_search (void)
{
BSDPM_ERRORS error;

	bsdpm_show_program_header (false);

	error = bsdpm_core_search (search_criteria, bsdpm_search_callback);

	switch (error)
	{
		case BSDPM_ERROR_SEARCH_INVALID:
			printf ("[%s] %s.\n", _("ERROR"), _("Invalid search criteria"));
			break;
		case BSDPM_ERROR_SEARCH_HAS_NO_RESULTS:
			printf ("%s.\n", _("Search has no result(s)"));
			break;
		default:
			break;
	}

	return error;
}

BSDPM_ERRORS bsdpm_install_callback (BSDPM_INSTALL_OPERATION operation, const char *notify_data)
{
BSDPM_ERRORS error = BSDPM_NOERROR;
char mode_table[16], **dadata;
unsigned short pos = 0;

	// emtpy variables
	memset (mode_table, '\0', sizeof (mode_table));
	strcpy (mode_table, bsdpm_config.mode_table);
	mode_table[0] = toupper (mode_table[0]);
	mode_table[strlen (mode_table) - 1] = '\0';

	switch (operation)
	{
		case BSDPM_INSTALL_OPERATION_STARTING:
			printf ("[%s '%s']\n", _("Starting installation"), notify_data);
			break;
		case BSDPM_INSTALL_PORT_NOT_FOUND:
			printf ("  %s: %s [%s]\n", _(mode_table), notify_data, _("NOT FOUND"));
			break;
		case BSDPM_INSTALL_PORT_DUPLICATED:
			dadata = bsdpm_core_split (notify_data, "|");

			printf ("%s '%s' %s. %s:\n", _("While trying to install"), dadata[pos++], _("was found duplicated entries"), _("Select one from the following list, please"));
			while (dadata[pos] != NULL)
			{
				if (strlen (dadata[pos]) > 0)
					printf ("  %s\n", dadata[pos]);

				pos++;
			}

			free (dadata);
			break;
        case BSDPM_INSTALL_OPERATION_STARTING_CHECK_SANITY:
            printf ("  [%s]\n", _("Checking sanity"));
            break;
        case BSDPM_INSTALL_OPERATION_CHECK_SANITY:
            printf ("%s", notify_data);
            break;
/*		case BSDPM_INSTALL_OPERATION_CONFIGUREPORTS:
			printf ("=> %s\n", _("Configuring all ports options"));
			break;
		case BSDPM_INSTALL_OPERATION_GATHERINGDEPENDENCIES:
			printf ("=> %s\n", _("Gathering dependencies"));
			break;
		case BSDPM_INSTALL_OPERATION_STARTFETCH:
			printf ("=> %s\n", _("Starting to fetch"));
			break;
		case BSDPM_INSTALL_OPERATION_FETCHING:
			break;
		case BSDPM_INSTALL_OPERATION_STARTEXTRACT:
			printf ("=> %s\n", _("Starting to extract"));
			break;
		case BSDPM_INSTALL_OPERATION_EXTRACTING:
			break;
		case BSDPM_INSTALL_OPERATION_STARTPATCH:
			printf ("=> %s\n", _("Starting to patch"));
			break;
		case BSDPM_INSTALL_OPERATION_PATCHING:
			break;
		case BSDPM_INSTALL_OPERATION_STARTCONFIGURE:
			printf ("=> %s\n", _("Starting to configure"));
			break;
		case BSDPM_INSTALL_OPERATION_CONFIGURING:
			break;
		case BSDPM_INSTALL_OPERATION_STARTBUILD:
			printf ("=> %s\n", _("Starting to build"));
			break;
		case BSDPM_INSTALL_OPERATION_BUILDING:
			break;
		case BSDPM_INSTALL_OPERATION_STARTINSTALL:
			printf ("=> %s\n", _("Starting to install"));
			break;
		case BSDPM_INSTALL_OPERATION_INSTALLING:
			break;
		case BSDPM_INSTALL_OPERATION_STARTCLEAN:
			printf ("=> %s\n", _("Starting to clean"));
			break;
		case BSDPM_INSTALL_OPERATION_CLEANING:
			break;
		case BSDPM_INSTALL_OPERATION_STARTPACKAGE:
			printf ("=> %s\n", _("Creating package"));
			break;
		case BSDPM_INSTALL_OPERATION_PACKAGING:
			break;
		case BSDPM_INSTALL_OPERATION_FINISH:
			//printf ("[%s '%s']\n\n", _("Finished installation of"), port_package_name);
			break;
*/
	}

	return error;
}

BSDPM_ERRORS bsdpm_install (const char *names)
{
BSDPM_ERRORS error = BSDPM_NOERROR;

	bsdpm_show_program_header (false);

	error = bsdpm_core_install (names, bsdpm_install_callback);

	switch (error)
	{
		case BSDPM_ERROR_DATABASE_IS_CORRUPT:
			printf ("\n[%s] %s: %s.\n", _("ERROR"), _("Can't install"), _("The database structure is corrupt"));
			break;
		case BSDPM_ERROR_CANT_DOWNLOAD_FILE:
			printf ("\n[%s] %s: %s.\n", _("ERROR"), _("Can't download package"), _("The file can't be downloaded"));
			break;
		case BSDPM_ERROR_OUT_OF_RESOURCES:
			printf ("\n[%s] %s: %s.\n", _("ERROR"), _("Can't install"), _("Out of resources"));
				break;
		case BSDPM_ERROR_INSTALLATION_ERROR:
			printf ("\n[%s] %s: %s.\n", _("ERROR"), _("Can't install"), _("An error was detected during instalation process"));
			break;
		default:
			break;
	}

	return error;
}

void bsdpm_set_defaultconfig (void)
{
char *psztemp, szmachine[16], szrelease[BUFSIZ];
struct stat ss;
struct utsname un;

	// config file name
	snprintf (bsdpm_config.config_filename, sizeof (bsdpm_config.config_filename), "%s/bsdpm/bsdpm.conf", PACKAGE_SYSCONF_DIR);
	if (stat (bsdpm_config.config_filename, &ss) == -1)
		memset (bsdpm_config.config_filename, '\0', sizeof (bsdpm_config.config_filename));

	// BSDPM local state dir
	snprintf (bsdpm_config.bsdpm_localstatedir, sizeof (bsdpm_config.config_filename), "/var/db/bsdpm");
	if (stat (bsdpm_config.bsdpm_localstatedir, &ss) == -1)
		mkdir (bsdpm_config.bsdpm_localstatedir, S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH);


	// mode and table name
	bsdpm_config.mode = 0;
	snprintf (bsdpm_config.mode_table, sizeof (bsdpm_config.mode_table), "ports");

	//
	// Core module

	// Directory path
	snprintf (bsdpm_config.portsdir, sizeof (bsdpm_config.portsdir), "/usr/ports");
	snprintf (bsdpm_config.distdir, sizeof (bsdpm_config.distdir), "%s/distfiles", bsdpm_config.portsdir);
	snprintf (bsdpm_config.packagesdir, sizeof (bsdpm_config.packagesdir), "%s/packages", bsdpm_config.portsdir);
	memset (bsdpm_config.wrkdir, '\0', sizeof (bsdpm_config.wrkdir));

	// Programs path
	snprintf (bsdpm_config.make_path, sizeof (bsdpm_config.make_path), "/usr/bin/make");
#ifdef __FreeBSD__
	snprintf (bsdpm_config.pkg_add_path, sizeof (bsdpm_config.pkg_add_path), "/usr/sbin/pkg_add");
	snprintf (bsdpm_config.pkg_delete_path, sizeof (bsdpm_config.pkg_delete_path), "/usr/sbin/pkg_delete");
#endif
#ifdef __NetBSD__
	snprintf (bsdpm_config.pkg_add_path, sizeof (bsdpm_config.pkg_add_path), "/usr/sbin/pkg_add");
	snprintf (bsdpm_config.pkg_delete_path, sizeof (bsdpm_config.pkg_delete_path), "/usr/sbin/pkg_delete");
#endif
#ifdef __OpenBSD__
	snprintf (bsdpm_config.pkg_add_path, sizeof (bsdpm_config.pkg_add_path), "/usr/sbin/pkg_add");
	snprintf (bsdpm_config.pkg_delete_path, sizeof (bsdpm_config.pkg_delete_path), "/usr/sbin/pkg_delete");
#endif

	// Packages repository URI
	psztemp = getenv("PACKAGESITE");
	if (psztemp != NULL)
	{
		snprintf (bsdpm_config.packages_repo, sizeof (bsdpm_config.packages_repo), "%s", psztemp);
	} else {
		memset (szmachine, '\0', sizeof (szmachine));
		memset (szrelease, '\0', sizeof (szrelease));
		uname (&un);
		bsdpm_core_changecase (szmachine, un.machine, 0);
		bsdpm_core_changecase (szrelease, un.release, 0);
		snprintf (bsdpm_config.packages_repo, sizeof (bsdpm_config.packages_repo), "ftp://ftp.freebsd.org/pub/FreeBSD/ports/%s/packages-%s/Latest/", szmachine, szrelease);
	}


	//
	// GTK module

	// UI definition
	snprintf (bsdpm_config.gtk_ui_file, sizeof (bsdpm_config.gtk_ui_file), "%s/bsdpm/ui/bsdpm_gtk.ui", PACKAGE_DATA_DIR);

	return;
}

void bsdpm_parse_arguments(int argc, char *const argv[])
{
struct option longopts[] = {
	{ "help",					no_argument,		NULL,   'h' },
	{ "config-file",			required_argument,  NULL,   'c' },
	{ "update-packages-list",   no_argument,		NULL,   'u' },
	{ "search",					required_argument,  NULL,   's' },
	{ "install",				required_argument,  NULL,   'i' },
	{ "deinstall",				required_argument,  NULL,   'd' },
	{ "upgrade-system",			no_argument,		NULL,   'U' },
	{ "mode",					required_argument,	NULL,   'm' },
	{ "create-packages",		no_argument,		NULL,   'C' },
	{ "interface",				required_argument,  NULL,   'I' },
	{ NULL,						0,					NULL,   0   }
};

int opt;
char szopt[16] = "hc:us:i:d:Um:C";
#if defined(HAVE_GTK2) || defined(HAVE_QT4)
	strcat (szopt, "I:");
#endif

	while ((opt = getopt_long(argc, argv, szopt, longopts, NULL)) != -1) {
		switch (opt) {
			case 'c':
				snprintf (bsdpm_config.config_filename, sizeof (bsdpm_config.config_filename), "%s", optarg);
				break;
			case 'u':
				want_update_packages_list = 1;
				break;
			case 'C':
				bsdpm_config.create_packages = 1;
				break;
			case 'm':
				bsdpm_config.mode = (unsigned char) strtol (optarg, NULL, 10);
				if (bsdpm_config.mode == 1)
					snprintf (bsdpm_config.mode_table, sizeof (bsdpm_config.mode_table), "packages");
				break;
			case 's':
				want_search = 1;
				search_criteria = optarg;
				break;
			case 'i':
				want_install = 1;
				install_packages = optarg;
				break;
			case 'd':
				want_deinstall = 1;
				deinstall_packages = optarg;
				break;
			case 'U':
				want_upgrade = 1;
				break;
#if defined(HAVE_GTK2) || defined(HAVE_QT4)
			case 'I':
#ifdef HAVE_GTK2
				if (strcmp (optarg, "gtk") == 0)
					interface = 1;
#endif
#ifdef HAVE_QT4
				if (strcmp (optarg, "qt") == 0)
					interface = 2;
#endif
				break;
#endif
			case 'h':
			default:
				bsdpm_show_usage ();
				break;
		}
	}

	return;
}

int main(int argc, char *argv[])
{
#ifdef ENABLE_NLS
	bindtextdomain (GETTEXT_PACKAGE, PACKAGE_LOCALE_DIR);
	bind_textdomain_codeset (GETTEXT_PACKAGE, "UTF-8");
	textdomain (GETTEXT_PACKAGE);
#endif

	bsdpm_set_defaultconfig ();

	bsdpm_parse_arguments (argc, argv);

	if (strlen (bsdpm_config.config_filename) > 0)
		if (bsdpm_core_process_configuration_file () != BSDPM_NOERROR)
		{
			printf ("%s.\n", _("Can't process configuration file"));
			exit (EXIT_FAILURE);
		}

	if (bsdpm_core_database_open () == BSDPM_ERROR_CANT_OPEN_DATABASE)
	{
		printf ("Can't open database.\n");
		return EXIT_FAILURE;
	}

	// populate the packages categories cache
	bsdpm_core_init_categories ();

	if (want_update_packages_list == 1)
		bsdpm_update_packages_list ();

	if (want_search == 1)
		switch (bsdpm_search ())
		{
			case BSDPM_ERROR_SEARCH_INVALID:
				bsdpm_core_database_close ();
				exit (EXIT_FAILURE);
				break;
			default:
				break;
		}

	if (want_install == 1)
		switch (bsdpm_install (install_packages))
		{
			case BSDPM_ERROR_CANT_DOWNLOAD_FILE:
			case BSDPM_ERROR_OUT_OF_RESOURCES:
			case BSDPM_ERROR_INSTALLATION_ERROR:
				bsdpm_core_database_close ();
				exit (EXIT_FAILURE);
				break;
			default:
				break;
		}
/*
	if (want_deinstall == 1)
		bsdpm_deinstall (deinstall_packages);

	if (want_upgrade == 1)
		bsdpm_upgrade ();
*/

#if defined(HAVE_GTK2) || defined(HAVE_QT4)
#ifdef HAVE_GTK2
	if (interface == 1)
		bsdpm_gtk2_do_main(argc, argv);
#endif
#ifdef HAVE_QT4
//	if (interface == 2)
//		bsdpm_qt4_do_main(argc, argv);
#endif
#endif

	bsdpm_core_database_close ();

	return EXIT_SUCCESS;
}
