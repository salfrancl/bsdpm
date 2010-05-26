/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * core.c
 * Copyright (C) Leinier Cruz Salfran 2010 <salfrancl@yahoo.es>
 *
 * libbsdpm_core is free software copyrighted by Leinier Cruz Salfran.
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
 * libbsdpm_core IS PROVIDED BY Leinier Cruz Salfran ``AS IS'' AND ANY EXPRESS
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
#include <fts.h>

extern char **environ;

void *pipc;
sqlite3 *database;


void bsdpm_core_init_categories (void)
{
int i;

	bsdpm_categories_names[BSDPM_CATEGORY_ACCESSIBILITY] = "accessibility";
	bsdpm_categories_descriptions[BSDPM_CATEGORY_ACCESSIBILITY] = "Packages to help disabled users";

	bsdpm_categories_names[BSDPM_CATEGORY_AUDIO] = "audio";
	bsdpm_categories_descriptions[BSDPM_CATEGORY_AUDIO] = "Audio utilities - most require a supported sound card";

	bsdpm_categories_names[BSDPM_CATEGORY_DESKUTILS] = "deskutils";
	bsdpm_categories_descriptions[BSDPM_CATEGORY_DESKUTILS] = "Various desktop utilities";

	bsdpm_categories_names[BSDPM_CATEGORY_EDITORS] = "editors";
	bsdpm_categories_descriptions[BSDPM_CATEGORY_EDITORS] = "Common text editors";

	bsdpm_categories_names[BSDPM_CATEGORY_FINANCE] = "finance";
	bsdpm_categories_descriptions[BSDPM_CATEGORY_FINANCE] = "Monetary, financial and related applications";

	bsdpm_categories_names[BSDPM_CATEGORY_GAMES] = "games";
	bsdpm_categories_descriptions[BSDPM_CATEGORY_GAMES] = "Various and sundry amusements";

	bsdpm_categories_names[BSDPM_CATEGORY_GRAPHICS] = "graphics";
	bsdpm_categories_descriptions[BSDPM_CATEGORY_GRAPHICS] = "Graphics libraries and utilities";

	bsdpm_categories_names[BSDPM_CATEGORY_MULTIMEDIA] = "multimedia";
	bsdpm_categories_descriptions[BSDPM_CATEGORY_MULTIMEDIA] = "Multimedia software";

	bsdpm_categories_names[BSDPM_CATEGORY_NET_P2P] = "net-p2p";
	bsdpm_categories_descriptions[BSDPM_CATEGORY_NET_P2P] = "Peer to peer networking software";

	bsdpm_categories_names[BSDPM_CATEGORY_PRINT] = "print";
	bsdpm_categories_descriptions[BSDPM_CATEGORY_PRINT] = "Utilities for dealing with printing";

	bsdpm_categories_names[BSDPM_CATEGORY_SHELLS] = "shells";
	bsdpm_categories_descriptions[BSDPM_CATEGORY_SHELLS] = "Various shells (tcsh, bash, etc)";

	bsdpm_categories_names[BSDPM_CATEGORY_TEXTPROC] = "textproc";
	bsdpm_categories_descriptions[BSDPM_CATEGORY_TEXTPROC] = "Text processing/search utilities";

	bsdpm_categories_names[BSDPM_CATEGORY_ARCHIVERS] = "archivers";
	bsdpm_categories_descriptions[BSDPM_CATEGORY_ARCHIVERS] = "Utilities for archiving and unarchiving data";

	bsdpm_categories_names[BSDPM_CATEGORY_DATABASES] = "databases";
	bsdpm_categories_descriptions[BSDPM_CATEGORY_DATABASES] = "Database software";

	bsdpm_categories_names[BSDPM_CATEGORY_DEVEL] = "devel";
	bsdpm_categories_descriptions[BSDPM_CATEGORY_DEVEL] = "Software development utilities and libraries";

	bsdpm_categories_names[BSDPM_CATEGORY_EMULATORS] = "emulators";
	bsdpm_categories_descriptions[BSDPM_CATEGORY_EMULATORS] = "Utilities for emulating other os types";

	bsdpm_categories_names[BSDPM_CATEGORY_JAVA] = "java";
	bsdpm_categories_descriptions[BSDPM_CATEGORY_JAVA] = "Java language support";

	bsdpm_categories_names[BSDPM_CATEGORY_LANG] = "lang";
	bsdpm_categories_descriptions[BSDPM_CATEGORY_LANG] = "Computer languages";

	bsdpm_categories_names[BSDPM_CATEGORY_PORTS_MGMT] = "ports-mgmt";
	bsdpm_categories_descriptions[BSDPM_CATEGORY_PORTS_MGMT] = "Utilities for managing ports and packages";

	bsdpm_categories_names[BSDPM_CATEGORY_SECURITY] = "security";
	bsdpm_categories_descriptions[BSDPM_CATEGORY_SECURITY] = "System security software";

	bsdpm_categories_names[BSDPM_CATEGORY_SYSUTILS] = "sysutils";
	bsdpm_categories_descriptions[BSDPM_CATEGORY_SYSUTILS] = "Various system utilities";

	bsdpm_categories_names[BSDPM_CATEGORY_COMMS] = "comms";
	bsdpm_categories_descriptions[BSDPM_CATEGORY_COMMS] = "Communications utilities";

	bsdpm_categories_names[BSDPM_CATEGORY_DNS] = "dns";
	bsdpm_categories_descriptions[BSDPM_CATEGORY_DNS] = "DNS client and server utilities";

	bsdpm_categories_names[BSDPM_CATEGORY_FTP] = "ftp";
	bsdpm_categories_descriptions[BSDPM_CATEGORY_FTP] = "FTP client and server utilities";

	bsdpm_categories_names[BSDPM_CATEGORY_IRC] = "irc";
	bsdpm_categories_descriptions[BSDPM_CATEGORY_IRC] = "Internet Relay Chat utilities";

	bsdpm_categories_names[BSDPM_CATEGORY_MAIL] = "mail";
	bsdpm_categories_descriptions[BSDPM_CATEGORY_MAIL] = "Electronic mail packages and utilities";

	bsdpm_categories_names[BSDPM_CATEGORY_MBONE] = "mbone";
	bsdpm_categories_descriptions[BSDPM_CATEGORY_MBONE] = "Applications and utilities for the mbone";

	bsdpm_categories_names[BSDPM_CATEGORY_NET] = "net";
	bsdpm_categories_descriptions[BSDPM_CATEGORY_NET] = "Networking utilities";

	bsdpm_categories_names[BSDPM_CATEGORY_NET_IM] = "net-im";
	bsdpm_categories_descriptions[BSDPM_CATEGORY_NET_IM] = "Instant messaging software";

	bsdpm_categories_names[BSDPM_CATEGORY_NET_MGMT] = "net-mgmt";
	bsdpm_categories_descriptions[BSDPM_CATEGORY_NET_MGMT] = "Network management utilities";

	bsdpm_categories_names[BSDPM_CATEGORY_NEWS] = "news";
	bsdpm_categories_descriptions[BSDPM_CATEGORY_NEWS] = "Usenet news support software";

	bsdpm_categories_names[BSDPM_CATEGORY_WWW] = "www";
	bsdpm_categories_descriptions[BSDPM_CATEGORY_WWW] = "Web utilities (browsers, http servers, etc)";

	bsdpm_categories_names[BSDPM_CATEGORY_X11] = "x11";
	bsdpm_categories_descriptions[BSDPM_CATEGORY_X11] = "X Window system based utilities";

	bsdpm_categories_names[BSDPM_CATEGORY_X11_CLOCKS] = "x11-clocks";
	bsdpm_categories_descriptions[BSDPM_CATEGORY_X11_CLOCKS] = "X Window system based clocks";

	bsdpm_categories_names[BSDPM_CATEGORY_X11_DRIVERS] = "x11-drivers";
	bsdpm_categories_descriptions[BSDPM_CATEGORY_X11_DRIVERS] = "X Window system drivers";

	bsdpm_categories_names[BSDPM_CATEGORY_X11_FM] = "x11-fm";
	bsdpm_categories_descriptions[BSDPM_CATEGORY_X11_FM] = "X Window system based file managers";

	bsdpm_categories_names[BSDPM_CATEGORY_X11_FONTS] = "x11-fonts";
	bsdpm_categories_descriptions[BSDPM_CATEGORY_X11_FONTS] = "X Window system fonts and font utilities";

	bsdpm_categories_names[BSDPM_CATEGORY_X11_SERVERS] = "x11-servers";
	bsdpm_categories_descriptions[BSDPM_CATEGORY_X11_SERVERS] = "X Window system servers";

	bsdpm_categories_names[BSDPM_CATEGORY_X11_THEMES] = "x11-themes";
	bsdpm_categories_descriptions[BSDPM_CATEGORY_X11_THEMES] = "X Window system themes";

	bsdpm_categories_names[BSDPM_CATEGORY_X11_TOOLKITS] = "x11-toolkits";
	bsdpm_categories_descriptions[BSDPM_CATEGORY_X11_TOOLKITS] = "X Window system based development toolkits";

	bsdpm_categories_names[BSDPM_CATEGORY_X11_WM] = "x11-wm";
	bsdpm_categories_descriptions[BSDPM_CATEGORY_X11_WM] = "X Window system window managers";

	bsdpm_categories_names[BSDPM_CATEGORY_ASTRO] = "astro";
	bsdpm_categories_descriptions[BSDPM_CATEGORY_ASTRO] = "Applications related to astronomy";

	bsdpm_categories_names[BSDPM_CATEGORY_BIOLOGY] = "biology";
	bsdpm_categories_descriptions[BSDPM_CATEGORY_BIOLOGY] = "Software related to biology";

	bsdpm_categories_names[BSDPM_CATEGORY_CAD] = "cad";
	bsdpm_categories_descriptions[BSDPM_CATEGORY_CAD] = "Computer aided design utilities";

	bsdpm_categories_names[BSDPM_CATEGORY_MATH] = "math";
	bsdpm_categories_descriptions[BSDPM_CATEGORY_MATH] = "Mathematical computation software";

	bsdpm_categories_names[BSDPM_CATEGORY_SCIENCE] = "science";
	bsdpm_categories_descriptions[BSDPM_CATEGORY_SCIENCE] = "Scientific software";

	bsdpm_categories_names[BSDPM_CATEGORY_ARABIC] = "arabic";
	bsdpm_categories_descriptions[BSDPM_CATEGORY_ARABIC] = "Ported software for the arabic market";

	bsdpm_categories_names[BSDPM_CATEGORY_CHINESE] = "chinese";
	bsdpm_categories_descriptions[BSDPM_CATEGORY_CHINESE] = "Ported software for the chinese market";

	bsdpm_categories_names[BSDPM_CATEGORY_FRENCH] = "french";
	bsdpm_categories_descriptions[BSDPM_CATEGORY_FRENCH] = "Ported software for the french countries";

	bsdpm_categories_names[BSDPM_CATEGORY_GERMAN] = "german";
	bsdpm_categories_descriptions[BSDPM_CATEGORY_GERMAN] = "Ported software for the germanic countries";

	bsdpm_categories_names[BSDPM_CATEGORY_HEBREW] = "hebrew";
	bsdpm_categories_descriptions[BSDPM_CATEGORY_HEBREW] = "Ported software for the hebrew language";

	bsdpm_categories_names[BSDPM_CATEGORY_HUNGARIAN] = "hungarian";
	bsdpm_categories_descriptions[BSDPM_CATEGORY_HUNGARIAN] = "Ported software for the hungarian market";

	bsdpm_categories_names[BSDPM_CATEGORY_JAPANESE] = "japanese";
	bsdpm_categories_descriptions[BSDPM_CATEGORY_JAPANESE] = "Ported software for the japanese market";

	bsdpm_categories_names[BSDPM_CATEGORY_KOREAN] = "korean";
	bsdpm_categories_descriptions[BSDPM_CATEGORY_KOREAN] = "Ported software for the korean market";

	bsdpm_categories_names[BSDPM_CATEGORY_POLISH] = "polish";
	bsdpm_categories_descriptions[BSDPM_CATEGORY_POLISH] = "Ported software for the polish market";

	bsdpm_categories_names[BSDPM_CATEGORY_PORTUGUESE] = "portuguese";
	bsdpm_categories_descriptions[BSDPM_CATEGORY_PORTUGUESE] = "Ported software for the portuguese market";

	bsdpm_categories_names[BSDPM_CATEGORY_RUSSIAN] = "russian";
	bsdpm_categories_descriptions[BSDPM_CATEGORY_RUSSIAN] = "Ported software for the russian market";

	bsdpm_categories_names[BSDPM_CATEGORY_SPANISH] = "spanish";
	bsdpm_categories_descriptions[BSDPM_CATEGORY_SPANISH] = "Ported software for the spanish market";

	bsdpm_categories_names[BSDPM_CATEGORY_UKRAINIAN] = "ukrainian";
	bsdpm_categories_descriptions[BSDPM_CATEGORY_UKRAINIAN] = "Ported software for the ukrainian market";

	bsdpm_categories_names[BSDPM_CATEGORY_VIETNAMESE] = "vietnamese";
	bsdpm_categories_descriptions[BSDPM_CATEGORY_VIETNAMESE] = "Ported software for the vietnamese market";

	bsdpm_categories_names[BSDPM_CATEGORY_AFTERSTEP] = "afterstep";
	bsdpm_categories_descriptions[BSDPM_CATEGORY_AFTERSTEP] = "Packages to support the afterstep window manager";

	bsdpm_categories_names[BSDPM_CATEGORY_DOCS] = "docs";
	bsdpm_categories_descriptions[BSDPM_CATEGORY_DOCS] = "Meta-packages for freebsd documentation";

	bsdpm_categories_names[BSDPM_CATEGORY_ELISP] = "elisp";
	bsdpm_categories_descriptions[BSDPM_CATEGORY_ELISP] = "Things related to Emacs LISP";

	bsdpm_categories_names[BSDPM_CATEGORY_GEOGRAPHY] = "geography";
	bsdpm_categories_descriptions[BSDPM_CATEGORY_GEOGRAPHY] = "Geography related packages";

	bsdpm_categories_names[BSDPM_CATEGORY_GNOME] = "gnome";
	bsdpm_categories_descriptions[BSDPM_CATEGORY_GNOME] = "Components of the GNOME Desktop Environment";

	bsdpm_categories_names[BSDPM_CATEGORY_GNUSTEP] = "gnustep";
	bsdpm_categories_descriptions[BSDPM_CATEGORY_GNUSTEP] = "Software for GNUStep Desktop Environment";

	bsdpm_categories_names[BSDPM_CATEGORY_HAMRADIO] = "hamradio";
	bsdpm_categories_descriptions[BSDPM_CATEGORY_HAMRADIO] = "Software for amateur radio";

	bsdpm_categories_names[BSDPM_CATEGORY_HASKELL] = "haskell";
	bsdpm_categories_descriptions[BSDPM_CATEGORY_HASKELL] = "Software related to the Haskell language";

	bsdpm_categories_names[BSDPM_CATEGORY_IPV6] = "ipv6";
	bsdpm_categories_descriptions[BSDPM_CATEGORY_IPV6] = "IPv6 related software";

	bsdpm_categories_names[BSDPM_CATEGORY_KDE] = "kde";
	bsdpm_categories_descriptions[BSDPM_CATEGORY_KDE] = "Software for the K Desktop Environment";

	bsdpm_categories_names[BSDPM_CATEGORY_KLD] = "kld";
	bsdpm_categories_descriptions[BSDPM_CATEGORY_KLD] = "Kernel loadable modules";

	bsdpm_categories_names[BSDPM_CATEGORY_LINUX] = "linux";
	bsdpm_categories_descriptions[BSDPM_CATEGORY_LINUX] = "Linux programs that can be run under binary compatibility";

	bsdpm_categories_names[BSDPM_CATEGORY_LISP] = "lisp";
	bsdpm_categories_descriptions[BSDPM_CATEGORY_LISP] = "Things related to pure LISP";

	bsdpm_categories_names[BSDPM_CATEGORY_PARALLEL] = "parallel";
	bsdpm_categories_descriptions[BSDPM_CATEGORY_PARALLEL] = "Applications dealing with parallelism in computing";

	bsdpm_categories_names[BSDPM_CATEGORY_PEAR] = "pear";
	bsdpm_categories_descriptions[BSDPM_CATEGORY_PEAR] = "Utilities/Modules that fall into the pear system";

	bsdpm_categories_names[BSDPM_CATEGORY_PERL5] = "perl5";
	bsdpm_categories_descriptions[BSDPM_CATEGORY_PERL5] = "Utilities/Modules for the perl5 language";

	bsdpm_categories_names[BSDPM_CATEGORY_PLAN9] = "plan9";
	bsdpm_categories_descriptions[BSDPM_CATEGORY_PLAN9] = "Software from the Plan9 operating system";

	bsdpm_categories_names[BSDPM_CATEGORY_PYTHON] = "python";
	bsdpm_categories_descriptions[BSDPM_CATEGORY_PYTHON] = "Software related to the Python language";

	bsdpm_categories_names[BSDPM_CATEGORY_RUBY] = "ruby";
	bsdpm_categories_descriptions[BSDPM_CATEGORY_RUBY] = "Software related to the Ruby language";

	bsdpm_categories_names[BSDPM_CATEGORY_RUBYGEMS] = "rubygems";
	bsdpm_categories_descriptions[BSDPM_CATEGORY_RUBYGEMS] = "Packages for the rubygems system";

	bsdpm_categories_names[BSDPM_CATEGORY_SCHEME] = "scheme";
	bsdpm_categories_descriptions[BSDPM_CATEGORY_SCHEME] = "Software related to the Scheme language";

	bsdpm_categories_names[BSDPM_CATEGORY_TCL] = "tcl";
	bsdpm_categories_descriptions[BSDPM_CATEGORY_TCL] = "TCL and packages which depend on it";

	bsdpm_categories_names[BSDPM_CATEGORY_TK] = "tk";
	bsdpm_categories_descriptions[BSDPM_CATEGORY_TK] = "TK and packages which depend on it";

	bsdpm_categories_names[BSDPM_CATEGORY_WINDOWMAKER] = "windowmaker";
	bsdpm_categories_descriptions[BSDPM_CATEGORY_WINDOWMAKER] = "Packages to support the WindowMaker window manager";

	bsdpm_categories_names[BSDPM_CATEGORY_XFCE] = "xfce";
	bsdpm_categories_descriptions[BSDPM_CATEGORY_XFCE] = "Packages to support the XFCE Desktop Environment";

	bsdpm_categories_names[BSDPM_CATEGORY_ZOPE] = "zope";
	bsdpm_categories_descriptions[BSDPM_CATEGORY_ZOPE] = "Software related to the Zope platform";

	bsdpm_categories_names[BSDPM_CATEGORY_BENCHMARKS] = "benchmarks";
	bsdpm_categories_descriptions[BSDPM_CATEGORY_BENCHMARKS] = "Utilities for measuring system performance";

	bsdpm_categories_names[BSDPM_CATEGORY_CONVERTERS] = "converters";
	bsdpm_categories_descriptions[BSDPM_CATEGORY_CONVERTERS] = "Format conversion utilities";

	bsdpm_categories_names[BSDPM_CATEGORY_MISC] = "misc";
	bsdpm_categories_descriptions[BSDPM_CATEGORY_MISC] = "Miscellaneous utilities";

	bsdpm_categories_names[BSDPM_CATEGORY_PALM] = "palm";
	bsdpm_categories_descriptions[BSDPM_CATEGORY_PALM] = "Software support for the Palm(TM) series";

	bsdpm_categories_names[BSDPM_CATEGORY_UNKNOWN] = "unknown";
	bsdpm_categories_descriptions[BSDPM_CATEGORY_UNKNOWN] = "Packages that belongs to unknown category";

	for (i = BSDPM_CATEGORIES_MIN; i < BSDPM_CATEGORIES_MAX; i++)
		snprintf (bsdpm_categories_iconnames[i], sizeof (bsdpm_categories_iconnames[i]), "bsdpm-category-%s", bsdpm_categories_names[i]);

	return;
}

void bsdpm_core_substr (char *dst, const char *src, int start, int end)
{
	end--;
	if ((start >= 0) && (start <= end) && (end >= start) && (end < strlen (src)))
	{
int p = 0, t = 0;
		for (t = start; t <= end; t++)
			dst[p++] = src[t];
	}

	return;
}

void bsdpm_core_trim (char *buffer, const char *src)
{
int pos = 0, start = 0, end = 0;

	// cut off spaces at start of the string
	for (pos = 0; pos < strlen (src); pos++)
	{
		if (src[pos] != 0x20)
		{
			start = pos;
			break;
		}
	}

	// cut off spaces at end of the string
	for (pos = strlen (src); pos >= 0 ; pos--)
	{
		switch (src[pos])
		{
			case 0x00:
			case 0x0A: // LF
			case 0x0D: // CR
			case 0x20: // SP
				break;
			default:
				end = pos + 1;
				break;
		}

		if (end > 0)
			break;
	}

	// trim the entire string
	if (start == end)
	{
		memset (buffer, '\0', sizeof (buffer));
	} else {
		bsdpm_core_substr (buffer, src, start, end);
	}

	return;
}

char **bsdpm_core_split (const char *buffer, const char *delimiter)
{
int pos = 0;
char *sztemp, **dynamic_array, *token;

	// parse 'buffer' into 'dynamic_array' dynamic array
	sztemp = strdup (buffer);
	dynamic_array = malloc (sizeof (char *));
	while ((token = strsep(&sztemp, delimiter)) != NULL)
	{
		dynamic_array[pos++] = token;
		dynamic_array = realloc (dynamic_array, (sizeof (dynamic_array) + (sizeof (char *))));
	}
	dynamic_array[pos] = NULL;
	free (sztemp);

	return dynamic_array;
}

void bsdpm_core_changecase (char *buffer, const char *src, unsigned short ucase)
{
int pos = 0;

	// change case of the string
	for (pos = 0; pos < strlen (src); pos++)
	{
		if (ucase == 0)
			buffer[pos] = tolower (src[pos]);
		if (ucase == 1)
			buffer[pos] = toupper (src[pos]);
	}

	return;
}

void bsdpm_core_encode_string (const char *src, char *dst)
{
unsigned short p;

	for (p = 0; p < strlen (src); p++)
	{
		switch (src[p])
		{
			case 0x22: // "
			case 0x27: // '
				dst[p] = src[p] - 0x21;
				break;
			default:
				dst[p] = src[p];
				break;
		}
	}

	return;
}

void bsdpm_core_decode_string (const char *src, char *dst)
{
unsigned short p;

	for (p = 0; p < strlen (src); p++)
	{
		switch (src[p])
		{
			case 0x01: // "
			case 0x02: // '
				dst[p] = src[p] + 0x21;
				break;
			default:
				dst[p] = src[p];
				break;
		}
	}

	return;}

void bsdpm_core_translate_size_to_human_readable (char *dst, const unsigned int src)
{
char *size_legend[5] = {
							"b",
							"KB",
							"MB",
							"GB",
							"TR"
						 };
unsigned short position = 0;
double size_downgraded = 0;

	size_downgraded = src;

	while (size_downgraded > 1024)
	{
		size_downgraded = (double) (size_downgraded / 1024);
		position++;
	}

	sprintf (dst, "%.2f%s", (double)size_downgraded, size_legend[position]);

	return;
}

void bsdpm_core_split_packagename_into_name_version (const char *src, char *szname, char *szversion, const char sep)
{
int szpos = 0;

	for (szpos = strlen (src); szpos >= 0; --szpos)
		if (src[szpos] == sep)
		{
			bsdpm_core_substr (szname, src, 0, szpos);
			bsdpm_core_substr (szversion, src, szpos + 1, strlen (src));

			return;
		}

	return;
}

int bsdpm_core_get_category_from_word (char *category)
{
int category_id;

	for (category_id = BSDPM_CATEGORIES_MIN; category_id < (BSDPM_CATEGORIES_MAX - 1); category_id++)
		if (strcmp (category, bsdpm_categories_names[category_id]) == 0)
			return category_id;

	return BSDPM_CATEGORY_UNKNOWN;
}

BSDPM_ERRORS bsdpm_core_process_configuration_file ()
{
struct stat ss;
FILE *inF;
char configuration_line[BUFSIZ], variable[255], variable_temp[255], value[255], value_temp[255];

	// check if configuration file exists
	if (stat (bsdpm_config.config_filename, &ss) == 0)
	{
		// try to open configuration file
		inF = fopen (bsdpm_config.config_filename, "r");
		if(inF == NULL)
			return BSDPM_ERROR_CANT_OPEN_CONFIGURATION_FILE;

		// process configuration file and populate 'bsdpm_config'
		while (!feof (inF))
		{
			memset (configuration_line, '\0', sizeof (configuration_line));
			fgets (configuration_line, sizeof (configuration_line), inF);

			bsdpm_core_trim (configuration_line, configuration_line);

			// if got an entire line then process the line
			if (strlen (configuration_line) > 0)
			{
				// # if not a comment
				if (configuration_line[0] != 0x23)
				{
					// empty fields
					memset (variable, '\0', sizeof (variable));
					memset (variable_temp, '\0', sizeof (variable_temp));
					memset (value, '\0', sizeof (value));
					memset (value_temp, '\0', sizeof (value_temp));

					// split configuration line
					bsdpm_core_split_packagename_into_name_version (configuration_line, variable_temp, value_temp, '=');
					bsdpm_core_trim (variable, variable_temp);
					bsdpm_core_trim (value, value_temp);

					// set configuration
					if (strcasecmp (variable, "portsdir") == 0)
						snprintf (bsdpm_config.portsdir, sizeof (bsdpm_config.portsdir), "%s", value);
					if (strcasecmp (variable, "distdir") == 0)
						snprintf (bsdpm_config.distdir, sizeof (bsdpm_config.distdir), "%s", value);
					if (strcasecmp (variable, "packagesdir") == 0)
						snprintf (bsdpm_config.packagesdir, sizeof (bsdpm_config.packagesdir), "%s", value);
					if (strcasecmp (variable, "wrkdir") == 0)
						snprintf (bsdpm_config.wrkdir, sizeof (bsdpm_config.wrkdir), "%s", value);
					if (strcasecmp (variable, "make_path") == 0)
						snprintf (bsdpm_config.make_path, sizeof (bsdpm_config.make_path), "%s", value);
					if (strcasecmp (variable, "pkg_add_path") == 0)
						snprintf (bsdpm_config.pkg_add_path, sizeof (bsdpm_config.pkg_add_path), "%s", value);
					if (strcasecmp (variable, "pkg_delete_path") == 0)
						snprintf (bsdpm_config.pkg_delete_path, sizeof (bsdpm_config.pkg_delete_path), "%s", value);
					if (strcasecmp (variable, "packages_repo") == 0)
						snprintf (bsdpm_config.packages_repo, sizeof (bsdpm_config.packages_repo), "%s", value);
					if (strcasecmp (variable, "gtk_ui_file") == 0)
						snprintf (bsdpm_config.gtk_ui_file, sizeof (bsdpm_config.gtk_ui_file), "%s", value);
				}
			}
		}

		// close configuration file
		fclose (inF);
	} else {
		 return BSDPM_ERROR_CONFIGURATION_FILE_DOESNT_EXISTS;
	}

	return BSDPM_NOERROR;
}

BSDPM_ERRORS bsdpm_core_database_open (void)
{
char database_filename[255];
short database_exists = 0;
struct stat sstat;
int error = 0;

	// fill database file name
	memset (database_filename, '\0', sizeof (database_filename));
	snprintf (database_filename, sizeof (database_filename), "%s/bsdpm.db", bsdpm_config.bsdpm_localstatedir);

	// database exists?
	if (stat (database_filename, &sstat) == 0)
		database_exists = 1;

	// open database
	error = sqlite3_open_v2(database_filename, &database, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE | SQLITE_OPEN_FULLMUTEX, NULL);
	if (error)
	{
		sqlite3_close(database);
		return BSDPM_ERROR_CANT_OPEN_DATABASE;
	}

	// if database doesn't exists create structure
	if (database_exists == 0)
	{
		sqlite3_exec(database, "CREATE TABLE \"ports\" (\"id\" INTEGER NOT NULL, \"state\" TEXT NOT NULL, \"distribution_name\" TEXT NOT NULL, \"available_version\" TEXT NOT NULL, \"installed_version\" TEXT, \"port_path\" TEXT NOT NULL, \"comment\" TEXT NOT NULL, \"description_file\" TEXT NOT NULL, \"maintainer\" TEXT NOT NULL, \"www\" TEXT, PRIMARY KEY (id));", NULL, NULL, NULL);
		sqlite3_exec(database, "CREATE TABLE \"ports_categories\" (\"id\" INTEGER NOT NULL, \"category_id\" INTEGER NOT NULL);", NULL, NULL, NULL);
		sqlite3_exec(database, "CREATE TABLE \"ports_dependencies\" (\"id\" INTEGER NOT NULL, \"dependency_id\" INTEGER NOT NULL);", NULL, NULL, NULL);
		sqlite3_exec(database, "CREATE TABLE \"packages\" (\"id\" INTEGER NOT NULL, \"state\" TEXT NOT NULL, \"distribution_name\" TEXT NOT NULL, \"available_version\" TEXT NOT NULL, \"installed_version\" TEXT, \"port_path\" TEXT NOT NULL, \"comment\" TEXT NOT NULL, \"description_file\" TEXT NOT NULL, \"maintainer\" TEXT NOT NULL, \"www\" TEXT, PRIMARY KEY (id));", NULL, NULL, NULL);
		sqlite3_exec(database, "CREATE TABLE \"packages_categories\" (\"id\" INTEGER NOT NULL, \"category_id\" INTEGER NOT NULL);", NULL, NULL, NULL);
		sqlite3_exec(database, "CREATE TABLE \"packages_dependencies\" (\"id\" INTEGER NOT NULL, \"dependency_id\" INTEGER NOT NULL);", NULL, NULL, NULL);
		sqlite3_exec(database, "CREATE TABLE \"dependencies_temp\" (\"id\" INTEGER NOT NULL, \"dependencies\" TEXT);", NULL, NULL, NULL);
		sqlite3_exec(database, "COMMIT;", NULL, 0, NULL);
		sqlite3_exec(database, "CREATE UNIQUE INDEX \"ports_index\" on \"ports\" (\"id\" ASC);", NULL, NULL, NULL);
		sqlite3_exec(database, "CREATE UNIQUE INDEX \"packages_index\" on \"packages\" (\"id\" ASC);", NULL, NULL, NULL);
		sqlite3_exec(database, "COMMIT;", NULL, 0, NULL);
	}

	return BSDPM_NOERROR;
}

void bsdpm_core_database_close (void)
{
	sqlite3_close(database);

	return;
}

int bsdpm_core_database_execute (const char *sql, sqlite3_callback callback, void *argument)
{
	return sqlite3_exec (database, sql, callback, argument, NULL);
}

BSDPM_ERRORS bsdpm_core_download_file (const char *uri, curl_progress_callback callback)
{
FILE *outF;
char *pc, filename[255], *szenv;
CURLcode ret;
CURL *hnd = curl_easy_init();

	// get the name of the file that will be downloaded
	pc = strrchr (uri, '/');
	if (pc != NULL)
		snprintf (filename, sizeof (filename), "%s/%s", bsdpm_config.bsdpm_localstatedir, pc);

	outF = fopen (filename, "w");
	if (outF == NULL)
		return BSDPM_ERROR_CANT_CREATE_FILE;

	// set curl options
	curl_easy_setopt(hnd, CURLOPT_USERAGENT, "bsdpm/0.1");
	curl_easy_setopt(hnd, CURLOPT_MAXREDIRS, 50);
	curl_easy_setopt(hnd, CURLOPT_FOLLOWLOCATION, 1);
	curl_easy_setopt(hnd, CURLOPT_AUTOREFERER, 1);

	// there is a 'socks_proxy' environment variable?
	szenv = getenv("socks_proxy");
	if (szenv != NULL)
	{
		curl_easy_setopt(hnd, CURLOPT_PROXY, szenv);
		curl_easy_setopt(hnd, CURLOPT_PROXYTYPE, CURLPROXY_SOCKS4);
	}
	//curl_easy_setopt(hnd, CURLOPT_PROXYUSERPWD, NULL);
	//curl_easy_setopt(hnd, CURLOPT_NOPROXY, NULL);
	//curl_easy_setopt(hnd, CURLOPT_WRITEFUNCTION, bsdpm_core_download_file_callback);
	curl_easy_setopt(hnd, CURLOPT_WRITEDATA, outF);
	curl_easy_setopt(hnd, CURLOPT_PROGRESSFUNCTION, callback);
	curl_easy_setopt(hnd, CURLOPT_NOPROGRESS, 0);
	curl_easy_setopt(hnd, CURLOPT_URL, uri);

	// do download
	ret = curl_easy_perform(hnd);

	// cleanup curl session
	fclose (outF);
	curl_easy_cleanup(hnd);

    // there was an error?
	if ((int)ret != 0)
	{
        // close, delete 'filename' and exit
	    fclose (outF);
	    unlink (filename);
		return BSDPM_ERROR_CANT_DOWNLOAD_FILE;
	}

	return BSDPM_NOERROR;
}

BSDPM_ERRORS bsdpm_core_download_packageslist (curl_progress_callback callback)
{
char package_repo[255];
char *pc = NULL;
char cc = 1;

	// is 'ports mode' active?
	if (bsdpm_config.mode == 0)
	{
		snprintf (package_repo, sizeof (package_repo), "file://%s/INDEX-%i", bsdpm_config.portsdir, __FreeBSD_version);
		package_repo[strlen (package_repo) - 5] = '\0';
	}

	// is 'packages mode' active?
	if (bsdpm_config.mode == 1)
	{
		// is valid the packages repository uri
		if (strlen(bsdpm_config.packages_repo) < 10)
			return BSDPM_ERROR_INVALID_PACKAGES_REPO;

		// cut off the last path component of packages repository
		strcpy (package_repo, bsdpm_config.packages_repo);
		pc = strrchr (package_repo, '/');
		if (pc != NULL)
		{
			*pc = '\0';
			pc = strrchr (package_repo, '/');
			if (pc != NULL)
				*pc = '\0';
		}

		// try to download INDEX.bz2 file first
		snprintf (package_repo, sizeof (package_repo), "%s/INDEX.bz2", package_repo);
	}

	// if can't then try with INDEX file
	if (bsdpm_core_download_file (package_repo, callback) == BSDPM_ERROR_CANT_DOWNLOAD_FILE)
	{
		cc = 0;
		package_repo[strlen (package_repo) - 4] = '\0';
		if (bsdpm_core_download_file (package_repo, callback) == BSDPM_ERROR_CANT_DOWNLOAD_FILE)
			return BSDPM_ERROR_CANT_DOWNLOAD_FILE;
	}

	return BSDPM_NOERROR;
}

BSDPM_ERRORS bsdpm_core_extract_compressed_packageslist (void)
{
char szif[255];
struct stat ss;

	snprintf (szif, sizeof (szif), "%s/INDEX.bz2", bsdpm_config.bsdpm_localstatedir);
	if (stat (szif, &ss) == 0)
		snprintf (szif, sizeof (szif), "bunzip2 -q %s/bsdpm/INDEX.bz2 > /dev/null 2>&1", PACKAGE_LOCALSTATE_DIR);
	system (szif);

	snprintf (szif, sizeof (szif), "%s/INDEX.bz2", bsdpm_config.bsdpm_localstatedir);
	unlink (szif);

	return BSDPM_NOERROR;
}

BSDPM_ERRORS bsdpm_core_process_index_file (curl_progress_callback callback)
{
struct stat ss;
FILE *inF;
char index_path[255], *fts_argv[2], index_line[80 * 1024], *token, temp_text1[BUFSIZ * 2], temp_text2[BUFSIZ], temp_large_text[70 * 1024], temp_comp_text1[2][255];
char state[2], distribution_name[255], available_version[32], installed_version[32], port_path[255], comment[BUFSIZ * 2], description_file[255], maintainer[128], categories[255], www[255]; //, dependencies[70 * 1024];
int pos = 0, chunk_pos1 = 0, chunk_pos2 = 0, temp_int1 = 0, temp_int2 = 0, temp_int3 = 0;
unsigned int package_id = 1;
FTS *fts_p = NULL;
FTSENT *fts_cur = NULL;
unsigned int tip = 0;
struct _ip
{
	char name[64];
	char origin[128];
} **ip;
double bytes_total = 0, bytes_read = 0;
time_t s_time;
struct tm *s_tm;
int sec_prev = 0;

	// empty database tables
	snprintf (index_path, sizeof (index_path), "DELETE FROM %s;", bsdpm_config.mode_table);
	sqlite3_exec(database, index_path, 0, 0, 0);
	snprintf (index_path, sizeof (index_path), "DELETE FROM %s_categories;", bsdpm_config.mode_table);
	sqlite3_exec(database, index_path, 0, 0, 0);

	// check if INDEX file exists
	memset (index_path, '\0', sizeof (index_path));
	// is 'ports' mode active?
	if (bsdpm_config.mode == 0)
	{
		snprintf (index_path, sizeof (index_path), "%s/INDEX-%i", bsdpm_config.bsdpm_localstatedir, __FreeBSD_version);
		index_path[strlen (index_path) - 5] = '\0';
	}
	// is 'packages' mode active?
	if (bsdpm_config.mode == 1)
		snprintf (index_path, sizeof (index_path), "%s/INDEX", bsdpm_config.bsdpm_localstatedir);
	if (stat (index_path, &ss) == 0)
	{
		bytes_total = ss.st_size;

		// populate the installed packages cache in order to acelerate
		// getting packages status
		fts_argv[0] = "/var/db/pkg/";
		fts_argv[1] = NULL;
		fts_p = fts_open (fts_argv, FTS_NOCHDIR, NULL);

		// initiate dynamic arrays
		ip = malloc (sizeof (struct _ip *));

		if (fts_p != NULL)
		{
			while ((fts_cur = fts_read(fts_p)) != NULL)
			{
				if (fts_cur->fts_level == 1)
				{
					switch (fts_cur->fts_statp->st_mode & S_IFMT)
					{
						case S_IFDIR:
							// if FTS is not repeating the search then populate
							if (strcasecmp (temp_text1, fts_cur->fts_path) != 0)
							{
								// let's maintain the last FTS checked item
								memset (temp_text1, '\0', sizeof (temp_text1));
								strcpy (temp_text1, fts_cur->fts_path);

								// get the last path component
								memset (temp_comp_text1[0], '\0', sizeof (temp_comp_text1[0]));
								memset (temp_comp_text1[1], '\0', sizeof (temp_comp_text1[1]));
								bsdpm_core_split_packagename_into_name_version (fts_cur->fts_path, temp_comp_text1[0], temp_comp_text1[1], '/');

								// populate package version
								ip[tip] = malloc (sizeof (struct _ip));
								snprintf (ip[tip]->name, sizeof (ip[tip]->name), "%s", temp_comp_text1[1]);

								// populate package origin
								snprintf (temp_text2, sizeof (temp_text2), "%s/+CONTENTS", fts_cur->fts_path);
								if (stat (temp_text2, &ss) == 0)
								{
									inF = fopen (temp_text2, "r");
									fgets (temp_text2, sizeof (temp_text2), inF);
									fgets (temp_text2, sizeof (temp_text2), inF);
									memset (temp_text2, '\0', sizeof (temp_text2));
									fgets (temp_text2, sizeof (temp_text2), inF);

									memset (temp_comp_text1[1], '\0', sizeof (temp_comp_text1[1]));
									bsdpm_core_substr (temp_comp_text1[1], temp_text2, strlen ("@comment ORIGIN:"), strlen (temp_text2) - 1);
									snprintf (temp_comp_text1[0], sizeof (temp_comp_text1[0]), "/usr/ports/%s", temp_comp_text1[1]);

									snprintf (ip[tip]->origin, sizeof (ip[tip]->origin), "%s", temp_comp_text1[0]);

									fclose (inF);
								}

								ip = realloc (ip, (sizeof (ip) + sizeof (struct _ip *)));
								tip++;
							}

							break;
					}
				}
			}

			fts_close (fts_p);
		}

		// open INDEX file for reading
		inF = fopen (index_path, "r");
		if(inF == NULL)
			return BSDPM_ERROR_CANT_OPEN_FILE;

		// process INDEX file and populate database
		while (!feof (inF))
		{
			memset (index_line, '\0', sizeof (index_line));
			fgets (index_line, sizeof (index_line), inF);

			bytes_read += strlen (index_line) + 1;
			if (callback != NULL)
			{
				time (&s_time);
				s_tm = localtime (&s_time);
				if (sec_prev != s_tm->tm_sec)
				{
					sec_prev = s_tm->tm_sec;
					callback (NULL, bytes_total, bytes_read, 0, 0);
				}
			}

			// if got an entire line then process the line
			if (strlen (index_line) > 0)
			{
				// empty fields
				memset (state, '\0', sizeof (state));
				memset (distribution_name, '\0', sizeof (distribution_name));
				memset (available_version, '\0', sizeof (available_version));
				memset (installed_version, '\0', sizeof (installed_version));
				memset (port_path, '\0', sizeof (port_path));
				memset (comment, '\0', sizeof (comment));
				memset (description_file, '\0', sizeof (description_file));
				memset (maintainer, '\0', sizeof (maintainer));
				memset (categories, '\0', sizeof (categories));
				memset (www, '\0', sizeof (www));
				//memset (dependencies, '\0', sizeof (dependencies));

				// initialize variables
				pos = chunk_pos1 = chunk_pos2 = temp_int1 = temp_int2 = temp_int3 = 0;

				// process chunks of text divided by '|'
				for (chunk_pos2 = 1; chunk_pos2 < strlen (index_line) - 1; chunk_pos2++)
				{
					if ((index_line[chunk_pos2] == '|') && (index_line[chunk_pos2] != '\n'))
					{
						if (chunk_pos2 >= chunk_pos1)
						{
							memset (temp_large_text, '\0', sizeof (temp_large_text));
							bsdpm_core_substr (temp_large_text, index_line, chunk_pos1, chunk_pos2);
							chunk_pos1 = chunk_pos2 + 1;

							switch (pos)
							{
								// distribution_name, available_version
								case 0:
									strncpy (temp_text1, temp_large_text, sizeof (temp_text1));
									bsdpm_core_split_packagename_into_name_version (temp_text1, distribution_name, available_version, '-');
									break;
								// port_path, state, installed_version
								case 1:
									strncpy (port_path, temp_large_text, sizeof (port_path));

									// get package status
									strcpy (state, "0");

									for (temp_int1 = 0; temp_int1 < tip; temp_int1++)
									{
										if (strcmp (port_path, ip[temp_int1]->origin) == 0)
										{
											memset (temp_comp_text1[0], '\0', sizeof (temp_comp_text1[0]));
											memset (temp_comp_text1[1], '\0', sizeof (temp_comp_text1[1]));
											bsdpm_core_split_packagename_into_name_version (ip[temp_int1]->name, temp_comp_text1[0], temp_comp_text1[1], '-');
											temp_int2 = version_cmp (available_version, temp_comp_text1[1]);
											// package is installed?
											if (temp_int2 == 0)
											{
												strcpy (state, "1");
												break;
											}
											// package is upgradable?
											if (temp_int2 == 1)
											{
												strcpy (state, "2");
												strcpy (installed_version, temp_comp_text1[1]);
											}
										}
									}
									break;
								// comment
								case 3:
									strncpy (comment, temp_large_text, sizeof (comment));
									break;
								// description_file
								case 4:
									strncpy (description_file, temp_large_text, sizeof (description_file));
									break;
								// maintainer
								case 5:
									strncpy (maintainer, temp_large_text, sizeof (maintainer));
									break;
								// categories
								case 6:
									strncpy (categories, temp_large_text, sizeof (categories));
									break;
								// dependencies
								/*case 7:
								case 8:
								case 10:
								case 11:
									if (strlen (dependencies) > 0)
										if (strlen (temp_large_text) > 0)
											strcat (dependencies, " ");
									strcat (dependencies, temp_large_text);
									break;*/
								// www
								case 9:
									strncpy (www, temp_large_text, sizeof (www));
									break;
							}

							pos++;
						}
					}
				}

				// insert values into database
				memset (temp_large_text, '\0', sizeof (temp_large_text));
				memset (temp_text1, '\0', sizeof (temp_text1));
				bsdpm_core_encode_string (comment, temp_text1);
				snprintf (temp_large_text, sizeof (temp_large_text), "INSERT INTO %s VALUES(%i,'%s','%s','%s','%s','%s','%s','%s','%s','%s');", bsdpm_config.mode_table, package_id, state, distribution_name, available_version, installed_version, port_path, temp_text1, description_file, maintainer, www);
				sqlite3_exec(database, temp_large_text, NULL, NULL, NULL);
				//snprintf (temp_large_text, sizeof (temp_large_text), "INSERT INTO dependencies_temp VALUES(%i,'%s');", package_id, dependencies);
				//sqlite3_exec(database, temp_large_text, NULL, NULL, NULL);

				// store categories
				if (strlen (categories) > 0)
				{
					for (token = strtok(categories, " "); token; token = strtok(NULL, " "))
					{
						memset (temp_large_text, '\0', sizeof (temp_large_text));
						snprintf (temp_large_text, sizeof (temp_large_text), "INSERT INTO %s_categories VALUES(%i, %i);", bsdpm_config.mode_table, package_id, bsdpm_core_get_category_from_word (token));
						sqlite3_exec(database, temp_large_text, NULL, NULL, NULL);
					}
				}

				sqlite3_exec(database, "COMMIT;", NULL, NULL, NULL);

				package_id++;
			}

			memset (index_line, '\0', sizeof (index_line));
		}

		if (callback != NULL)
			callback (NULL, bytes_total, bytes_total, 0, 0);

		// free memory
		free (ip);
		fclose (inF);
	} else {
		return BSDPM_ERROR_INVALID_FILE;
	}

	return BSDPM_NOERROR;
}

BSDPM_ERRORS bsdpm_core_process_dependencies (curl_progress_callback callback)
{
BSDPM_ERRORS error;
sqlite3_stmt *statement1, *statement2;
char sql[BUFSIZ], *sztemp, *sztoken, distribution_name[255], available_version[32];
unsigned int total, processed;

    //initialize variables
    error = BSDPM_NOERROR;
    memset (sql, '\0', sizeof (sql));
    processed = total = 0;

    //
    // count total of available ports/packages

    // prepare sql statement
    snprintf (sql, sizeof (sql), "SELECT COUNT (id) FROM dependencies_temp;");
	error = sqlite3_prepare_v2 (database, sql, sizeof (sql), &statement1, NULL);
	if (error != SQLITE_OK)
	{
		error = BSDPM_ERROR_DATABASE_IS_CORRUPT;
		goto end;
	}

	// process result
	error = sqlite3_step (statement1);
	if (error == SQLITE_ROW)
		if (callback != NULL)
            total = sqlite3_column_int (statement1, 0);

    // finalize
    sqlite3_finalize (statement1);

    //
    // process dependencies

    // prepare sql statement
    error = sqlite3_prepare_v2 (database, "SELECT * FROM dependencies_temp;", -1, &statement1, NULL);
	if (error != SQLITE_OK)
	{
		error = BSDPM_ERROR_DATABASE_IS_CORRUPT;
		goto end;
	}

	// process results
	while ((error = sqlite3_step (statement1)) == SQLITE_ROW)
	{
        // process chunk of text divided by ' '
        sztemp = strdup ((char *)sqlite3_column_text (statement1, 1));
        while ((sztoken = strsep(&sztemp, " ")) != NULL)
        {
            // empty variables
            memset (distribution_name, '\0', sizeof (distribution_name));
            memset (available_version, '\0', sizeof (available_version));

            // split 'sztoken' into name and version
            bsdpm_core_split_packagename_into_name_version (sztoken, distribution_name, available_version, '-');

            // insert dependency into database
            snprintf (sql, sizeof (sql), "SELECT id FROM %s WHERE ((distribution_name = '%s') AND (available_version = '%s'));", bsdpm_config.mode_table, distribution_name, available_version);
            sqlite3_prepare_v2 (database, sql, sizeof (sql), &statement2, NULL);
            error = sqlite3_step (statement2);
            if (error == SQLITE_ROW)
            {
                snprintf (sql, sizeof (sql), "INSERT INTO %s_dependencies VALUES(%i, %i);", bsdpm_config.mode_table, sqlite3_column_int (statement1, 0), sqlite3_column_int (statement2, 0));
                sqlite3_exec(database, sql, NULL, NULL, NULL);
            }
            sqlite3_finalize (statement2);
        }

        // free memory
        free (sztemp);
        free (sztoken);

        // notify
        if (callback != NULL)
        {
            processed++;
            callback (NULL, total, processed, 0, 0);
        }
	}

    // process has finished .. empty unuseful table
    sqlite3_exec(database, "DELETE FROM dependencies_temp;", NULL, NULL, NULL);
    sqlite3_exec(database, "COMMIT;", NULL, NULL, NULL);
    sqlite3_exec(database, "VACUUM;", NULL, NULL, NULL);

	error = BSDPM_NOERROR;

end:
	// finalize
	sqlite3_finalize (statement1);

    return error;
}

void bsdpm_core_unlink_packageslist (void)
{
char file_path[255];

	// is 'ports mode' active?
	if (bsdpm_config.mode == 0)
	{
		snprintf (file_path, sizeof (file_path), "%s/INDEX-%i", bsdpm_config.bsdpm_localstatedir, __FreeBSD_version);
		file_path[strlen (file_path) - 5] = '\0';
	}
	// is 'packages mode' active?
	if (bsdpm_config.mode == 1)
		snprintf (file_path, sizeof (file_path), "%s/INDEX", bsdpm_config.bsdpm_localstatedir);

	unlink (file_path);

	return;
}

BSDPM_ERRORS bsdpm_core_search (const char *search_criteria, bsdpm_core_search_callback callback)
{
BSDPM_ERRORS error = BSDPM_NOERROR;
char *sql;
sqlite3_stmt *statement;
bsdpm_port_information pi;
unsigned short found = 0;


	// do search
	memset (&pi, '\0', sizeof (pi));
	sql = sqlite3_mprintf ("SELECT id, state, distribution_name AS \"name\", available_version AS \"version\", installed_version, port_path AS \"path\", comment, maintainer, www FROM %s WHERE (%s);", bsdpm_config.mode_table, search_criteria);

	if (callback != NULL)
		callback (BSDPM_SEARCH_OPERATION_SEARCHING, NULL);

	error = sqlite3_prepare_v2 (database, sql, -1, &statement, NULL);
	if (error != SQLITE_OK)
	{
		error = BSDPM_ERROR_SEARCH_INVALID;
		goto end;
	}

	// notify results
	while ((error = sqlite3_step (statement)) == SQLITE_ROW)
	{
		found = 1;
		if (callback != NULL)
		{
			pi.id = sqlite3_column_int (statement, 0);
			pi.state = sqlite3_column_text (statement, 1)[0];
			snprintf (pi.distribution_name, sizeof (pi.distribution_name), "%s", sqlite3_column_text (statement, 2));
			snprintf (pi.available_version, sizeof (pi.available_version), "%s", sqlite3_column_text (statement, 3));
			snprintf (pi.installed_version, sizeof (pi.installed_version), "%s", sqlite3_column_text (statement, 4));
			snprintf (pi.port_path, sizeof (pi.port_path), "%s", sqlite3_column_text (statement, 5));
			snprintf (pi.comment, sizeof (pi.comment), "%s", sqlite3_column_text (statement, 6));
			if (strlen (pi.comment) > 0)
                bsdpm_core_decode_string (pi.comment, pi.comment);
			snprintf (pi.maintainer, sizeof (pi.maintainer), "%s", sqlite3_column_text (statement, 7));
			snprintf (pi.www, sizeof (pi.www), "%s", sqlite3_column_text (statement, 8));

			error = callback (BSDPM_SEARCH_OPERATION_PROCESS_RESULT, &pi);

			if (error == BSDPM_CANCEL_OPERATION)
				break;
		}
	}

	if (found == 0)
		error = BSDPM_ERROR_SEARCH_HAS_NO_RESULTS;


	// finalize
	sqlite3_finalize (statement);

end:
    //free memory
	sqlite3_free (sql);

	return error;
}

int bsdpm_core_execute_pipe (int *file_descriptors, const char *command, char *const environment[])
{
int fork_ret = 0, total = 0;
char *sztemp, **arguments, *token;

	// parse 'command' into 'arguments' dynamic array
	sztemp = strdup (command);
	arguments = malloc (sizeof (char *));
	while ((token = strsep(&sztemp, " ")) != NULL)
	{
		arguments[total++] = token;
		arguments = realloc (arguments, (sizeof (arguments) + (sizeof (char *))));
	}
	arguments[total] = NULL;
	free (sztemp);

	// try to fork
	fork_ret = vfork ();

	// can't fork?
	if (fork_ret == -1)
		return BSDPM_ERROR_OUT_OF_RESOURCES;

	// okey, forked, then execute new process
	if (fork_ret == 0)
	{
		// new process
		dup2 (file_descriptors[0], STDIN_FILENO);
		dup2 (file_descriptors[1], STDOUT_FILENO);
		dup2 (file_descriptors[1], STDERR_FILENO);
		close (file_descriptors[0]);
		close (file_descriptors[1]);
		if (execve (arguments[0], arguments, environment) == -1)
		{
			// free memory and exit
			free (arguments);
			fprintf (stderr, "EXIT_FAILURE\n");
			exit (EXIT_FAILURE);
		}
	}

	// free memory
	free (arguments);

	return fork_ret;
}

BSDPM_ERRORS bsdpm_core_execute_standard (const char *command, char *const environment[])
{
BSDPM_ERRORS error = BSDPM_NOERROR;
int fork_ret = 0, total = 0, pidstatus = 0;
char *sztemp, **arguments, *token;

	// parse 'command' into 'arguments' dynamic array
	sztemp = strdup (command);
	arguments = malloc (sizeof (char *));
	while ((token = strsep(&sztemp, " ")) != NULL)
	{
		arguments[total++] = token;
		arguments = realloc (arguments, (sizeof (arguments) + (sizeof (char *))));
	}
	arguments[total] = NULL;
	free (sztemp);

	// try to fork
	fork_ret = vfork ();

	// can't fork?
	if (fork_ret == -1)
		return BSDPM_ERROR_OUT_OF_RESOURCES;

	// okey, forked, then execute new process
	if (fork_ret == 0)
	{
		// new process
		if (execve (arguments[0], arguments, environment) == -1)
		{
			// free memory and exit
			free (arguments);
			fprintf (stderr, "EXIT_FAILURE\n");
			exit (EXIT_FAILURE);
		}
	}

	// wait until child exit
	for (;;)
	{
		if (waitpid (fork_ret, &pidstatus, WNOHANG) < 0)
		{
			if (WEXITSTATUS (pidstatus) != 0)
				error = BSDPM_ERROR_INSTALLATION_ERROR;
			break;
		}

		usleep (5000);
	}

	// free memory
	free (arguments);

	return error;
}

BSDPM_ERRORS bsdpm_core_execute_sync (char *return_buffer, const char *command, char *const environment[])
{
BSDPM_ERRORS error = BSDPM_NOERROR;
int file_descriptors[2], pid = 0, pidstatus = 0;
char buffer[BUFSIZ];

	// create file descriptors
	if (pipe(file_descriptors) < 0)
		return BSDPM_ERROR_OUT_OF_RESOURCES;

	// execute using file descriptors
	pid = bsdpm_core_execute_pipe (file_descriptors, command, environment);
	if (pid == BSDPM_ERROR_OUT_OF_RESOURCES)
		return BSDPM_ERROR_OUT_OF_RESOURCES;

	// read from pipe until child exit
	fcntl (file_descriptors[0], F_SETFL, O_NONBLOCK);
	for (;;)
	{
		if (waitpid (pid, &pidstatus, WNOHANG) < 0)
		{
			if (WEXITSTATUS (pidstatus) != 0)
				error = BSDPM_ERROR_INSTALLATION_ERROR;
			break;
		}

		memset (buffer, '\0', sizeof (buffer));
		read (file_descriptors[0], buffer, BUFSIZ);

		if (strcmp (buffer, "EXIT_FAILURE\n") == 0)
			return BSDPM_ERROR_INSTALLATION_ERROR;

		strcat (return_buffer, buffer);

		usleep (5000);
	}

	// close file descriptors
	close (file_descriptors[0]);
	close (file_descriptors[1]);

	return error;
}


short bsdpm_core_install_port (char *const path, bsdpm_core_install_callback callback)
{
BSDPM_ERRORS error = BSDPM_NOERROR;
//char command[255];
char buffer[255];

	// notify 'start' of the process
	if (callback != NULL)
		callback (BSDPM_INSTALL_OPERATION_STARTING, path);

	// notify 'check_sanity' of the process
	if (callback != NULL)
		callback (BSDPM_INSTALL_OPERATION_STARTING_CHECK_SANITY, NULL);

    // try to execute command

	// initialize variables
	memset (buffer, '\0', sizeof (buffer));
/*

	// start to fetch
	if (callback != NULL)
		callback (BSDPM_INSTALL_OPERATION_STARTFETCH, path);
	sprintf (command, "%s -C %s fetch", bsdpm_config.make_path, path);
	error = bsdpm_core_execute_standard (command, environ);
	if (error != BSDPM_NOERROR)
		return error;


	// start to extract
	if (callback != NULL)
		callback (BSDPM_INSTALL_OPERATION_STARTEXTRACT, path);
	sprintf (command, "%s -C %s extract", bsdpm_config.make_path, path);
	error = bsdpm_core_execute_standard (command, environ);
	if (error != BSDPM_NOERROR)
		return error;


	// start to patch
	if (callback != NULL)
		callback (BSDPM_INSTALL_OPERATION_STARTPATCH, path);
	sprintf (command, "%s -C %s patch", bsdpm_config.make_path, path);
	error = bsdpm_core_execute_standard (command, environ);
	if (error != BSDPM_NOERROR)
		return error;


	// start to configure
	if (callback != NULL)
		callback (BSDPM_INSTALL_OPERATION_STARTCONFIGURE, path);
	sprintf (command, "%s -C %s configure", bsdpm_config.make_path, path);
	error = bsdpm_core_execute_standard (command, environ);
	if (error != BSDPM_NOERROR)
		return error;


	// start to build
	if (callback != NULL)
		callback (BSDPM_INSTALL_OPERATION_STARTBUILD, path);
	sprintf (command, "%s -C %s build", bsdpm_config.make_path, path);
	error = bsdpm_core_execute_standard (command, environ);
	if (error != BSDPM_NOERROR)
		return error;


	// start to install
	if (callback != NULL)
		callback (BSDPM_INSTALL_OPERATION_STARTINSTALL, path);
	sprintf (command, "%s -C %s install", bsdpm_config.make_path, path);
	error = bsdpm_core_execute_standard (command, environ);
	if (error != BSDPM_NOERROR)
		return error;


	// start to clean
	if (callback != NULL)
		callback (BSDPM_INSTALL_OPERATION_STARTCLEAN, path);
	sprintf (command, "%s -C %s clean", bsdpm_config.make_path, path);
	error = bsdpm_core_execute_standard (command, environ);
	if (error != BSDPM_NOERROR)
		return error;

*/

	return error;
}

short bsdpm_core_install_package (const char *package, bsdpm_core_install_callback callback)
{
BSDPM_ERRORS error = BSDPM_NOERROR;

	// notify 'start' of the process
	if (callback != NULL)
		callback (BSDPM_INSTALL_OPERATION_STARTING, package);

    return error;
}

BSDPM_ERRORS bsdpm_core_install (const char *names, bsdpm_core_install_callback callback)
{
BSDPM_ERRORS error = BSDPM_NOERROR;
char **danames, **dafullnames = NULL, *fullnames = NULL, *duplicated, temp_text1[BUFSIZ], temp_text2[BUFSIZ];
unsigned short pos = 0, found = 0;
sqlite3_stmt *statement;
char sql[BUFSIZ];

	// empty variables
	memset (sql, '\0', sizeof (sql));
	memset (temp_text1, '\0', sizeof (temp_text1));
	memset (temp_text2, '\0', sizeof (temp_text2));

	// split 'names' into dynamic array 'danames'
	danames = bsdpm_core_split (names, " ");

	// discard duplicated entries on database
	if (danames != NULL)
	{
		while (danames[pos] != NULL)
		{
			if (strlen (danames[pos]) > 0)
			{
				// empty variables
				found = 0;

				// prepare sql query
				if (bsdpm_config.mode == 0)
                    snprintf (sql, sizeof (sql), "SELECT port_path, comment FROM %s WHERE (port_path LIKE '%%/%s');", bsdpm_config.mode_table, danames[pos]);
				if (bsdpm_config.mode == 1)
				{
				    // construct the sql statement due 'danames[pos]' format:
				    // - name           # name may contain '-' charater but the last component divided by '-'
				    //                  # must not begin with a number. ie: mplayer-skins
				    // - name-version   # the last component divideb by '-' of complete 'name-version' must begin
				    //                  # with a number. ie: mplayer-skins-0.1

				    // split 'danames[pos]' into name and version (if exists)
				    bsdpm_core_split_packagename_into_name_version (danames[pos], temp_text1, temp_text2, '-');

				    // check if 'version' begin with a number and fill 'sql' with proper sql statement
				    if ((temp_text2[0] >= 0x30) && (temp_text2[0] <= 0x39))
				    {
                        snprintf (sql, sizeof (sql), "SELECT name, version, comment FROM %s WHERE ((name = '%s') AND (version = '%s'));", bsdpm_config.mode_table, temp_text1, temp_text2);
				    } else {
                        snprintf (sql, sizeof (sql), "SELECT name, version, comment FROM %s WHERE (name = '%s');", bsdpm_config.mode_table, danames[pos]);
				    }
				}
				error = sqlite3_prepare_v2 (database, sql, sizeof (sql), &statement, NULL);
				if (error != SQLITE_OK)
				{
					error = BSDPM_ERROR_DATABASE_IS_CORRUPT;
					goto end;
				}

				// execute sql query
				error = sqlite3_step (statement);

				// there is a result?
				if (error == SQLITE_ROW)
				{
					found = 1;

                    // empty variables
                    memset (temp_text1, '\0', sizeof (temp_text1));
                    memset (temp_text2, '\0', sizeof (temp_text2));


                    // get 'port_path' field without '/usr/ports/' text
                    if (bsdpm_config.mode == 0)
                    {
                        snprintf (temp_text2, sizeof (temp_text2), "%s", sqlite3_column_text (statement, 0));
                        bsdpm_core_substr (temp_text1, temp_text2, 11, strlen (temp_text2));
                    }
                    // get 'name-version' fields
                    if (bsdpm_config.mode == 1)
                        snprintf (temp_text1, sizeof (temp_text1), "%s-%s", sqlite3_column_text (statement, 0), sqlite3_column_text (statement, 1));

                    // update 'fullnames' with complete 'port_path/name-version' value
                    // this variable contains the complete name of port/package to be
                    // installed
                    if (fullnames != NULL)
                    {
                        realloc (fullnames,  sizeof (fullnames) + (sizeof (temp_text1) + (sizeof (char) * 2)));
                        strcat (fullnames, "|");
                        strcat (fullnames, temp_text1);
                    }
                    if (fullnames == NULL)
                    {
                        fullnames = malloc (sizeof (temp_text1) + (sizeof (char) * 2));
                        strcpy (fullnames, temp_text1);
                    }

					// put on 'duplicated' variable the result
					// with format: 'port_path/name-version - comment'
					if (callback != NULL)
					{
                        // get 'comment' field
                        if (bsdpm_config.mode == 0)
                            snprintf (temp_text2, sizeof (temp_text2), "%s", sqlite3_column_text (statement, 1));
                        if (bsdpm_config.mode == 1)
                            snprintf (temp_text2, sizeof (temp_text2), "%s", sqlite3_column_text (statement, 2));

						// fill 'duplicated' variable
						duplicated = malloc (sizeof (danames[pos]) + (sizeof (temp_text1) + (sizeof (char) * 5) + sizeof (temp_text2)));
						memset (duplicated, '\0', sizeof (duplicated));
						strcpy (duplicated, danames[pos]);
                        strcat (duplicated, "|");
                        strcat (duplicated, temp_text1);
						strcat (duplicated, " - ");
						strcat (duplicated, temp_text2);
					}

					// there is more than one result?
					while ((error = sqlite3_step (statement)) == SQLITE_ROW)
					{
						found = 2;

                        // add to 'duplicated' variable the result
                        // with format: '|port_path/name-version - comment'
						if (callback != NULL)
						{
						    // empty variables
							memset (temp_text1, '\0', sizeof (temp_text1));
							memset (temp_text2, '\0', sizeof (temp_text2));

                            // get 'port_path' field without '/usr/ports/' text
                            if (bsdpm_config.mode == 0)
                            {
                                snprintf (temp_text2, sizeof (temp_text2), "%s", sqlite3_column_text (statement, 0));
                                bsdpm_core_substr (temp_text1, temp_text2, 11, strlen (temp_text2));
                            }
                            // get 'name-version' fields
                            if (bsdpm_config.mode == 1)
                            {
                                snprintf (temp_text1, sizeof (temp_text1), "%s-%s", sqlite3_column_text (statement, 0), sqlite3_column_text (statement, 1));
                            }

                            // get 'comment' field
                            if (bsdpm_config.mode == 0)
                                snprintf (temp_text2, sizeof (temp_text2), "%s", sqlite3_column_text (statement, 1));
                            if (bsdpm_config.mode == 1)
                                snprintf (temp_text2, sizeof (temp_text2), "%s", sqlite3_column_text (statement, 2));

							// fill 'duplicated' variable
							realloc (duplicated,  sizeof (duplicated) + (sizeof (temp_text1) + (sizeof (char) * 5) + sizeof (temp_text2)));
							strcat (duplicated, "|");
							strcat (duplicated, temp_text1);
							strcat (duplicated, " - ");
							strcat (duplicated, temp_text2);
							strcat (duplicated, "\0");
						}
					}
				}

				// finalize the sql execution
				sqlite3_finalize (statement);

				// if there is not any result then notify and exit
				if (found == 0)
				{
					if (callback != NULL)
						callback (BSDPM_INSTALL_PORT_NOT_FOUND, danames[pos]);

                    //error = BSDPM_ERROR_INSTALLATION_ERROR;
                    //free (duplicated);
                    //goto end;
				}

				// if there is more than one results then notify
				if (found == 2)
				{
					if (callback != NULL)
						callback (BSDPM_INSTALL_PORT_DUPLICATED, duplicated);

                    error = BSDPM_ERROR_INSTALLATION_ERROR;
                    free (duplicated);
                    goto end;
				}

				// free memory
				if ((callback != NULL) && (found > 0))
					free (duplicated);
			}

			pos++;
		}
	}

    // install ports/packages
    if (fullnames != NULL)
    {
        pos = 0;
        dafullnames = bsdpm_core_split (fullnames, "|");
        if (dafullnames != NULL)
        {
            while (dafullnames[pos] != NULL)
            {
                if (strlen (dafullnames[pos]) > 0)
                {
                    // is 'ports' mode active?
                    if (bsdpm_config.mode == 0)
                        error = bsdpm_core_install_port (dafullnames[pos], callback);

                    // is 'packages' mode active?
                    if (bsdpm_config.mode == 1)
                        error = bsdpm_core_install_package (dafullnames[pos], callback);

                    // there was an error?
                    if (error != BSDPM_NOERROR)
                        break;
                }

                pos++;
            }
        }
    }

end:
	// free memory
	free (danames);
	if (found != 0)
	{
        free (dafullnames);
        free (fullnames);
	}

	return error;
}

/*
short bsdpm_core_install (const char *names, bsdpm_core_install_callback callback)
{
BSDPM_ERRORS error = BSDPM_NOERROR;
char *sztemp, **sznames, *token, **dependencies1, **dependencies2, *dependency_temp1, *dependency_temp2;
int names_pos = 0, dependencies1_pos = 0, dependencies2_pos = 0, dependency_found = 0;
char command[255];
char buffer[BUFSIZ * 5];
struct _dependencies
{
	struct _dependencies *next;
	char name[255];
	char **dependencies;
} *dependencies, *first_dependency = NULL, *prev_dependency = NULL, *temp_dependency = NULL;
time_t t1, t2;

	// initialize
	memset (buffer, '\0', sizeof (buffer));
	putenv ("LC_ALL=C");
	if (bsdpm_config.create_packages == 1)
		putenv ("INSTALL_TARGET=package");

	// parse 'packages' into 'szpackages' dynamic array
	sztemp = strdup (names);
	sznames = malloc (sizeof (char *));
	while ((token = strsep(&sztemp, " ")) != NULL)
	{
		sznames[names_pos++] = token;
		sznames = realloc (sznames, (sizeof (sznames) + (sizeof (char) * 255)));
	}
	sznames[names_pos] = NULL;

	// try to install based on 'mode' configuration value
	names_pos = 0;
	while (sznames[names_pos] != NULL)
	{
		if (bsdpm_config.mode == 0)
		{
			// start the instalation
			if (callback != NULL)
				callback (BSDPM_INSTALL_OPERATION_STARTING, sznames[names_pos]);

			// configure all ports
			if (callback != NULL)
				callback (BSDPM_INSTALL_OPERATION_CONFIGUREPORTS, sznames[names_pos]);
			sprintf (command, "%s -C %s config-recursive", bsdpm_config.make_path, sznames[names_pos]);
			//error = bsdpm_core_execute_standard (command, environ);
			if (error != BSDPM_NOERROR)
				return error;

			// gathering dependencies
			if (callback != NULL)
				callback (BSDPM_INSTALL_OPERATION_GATHERINGDEPENDENCIES, sznames[names_pos]);
			// get dependencies of parent port
			sprintf (command, "%s -C %s all-depends-list", bsdpm_config.make_path, sznames[names_pos]);
			error = bsdpm_core_execute_sync (buffer, command, environ);
			if (error != BSDPM_NOERROR)
				return error;

			time (&t1);
			// split dependencies on 'dependencies1' dynamic array
			dependencies1 = bsdpm_core_split (buffer, "\n", 255);
			while (strlen (dependencies1[dependencies1_pos]) > 0)
			{
				// get dependencies of port 'dependencies1[dependencies1_pos]'
				//printf ("Gathering dependencies of: %s\n", dependencies1[dependencies1_pos]);
				memset (buffer, '\0', sizeof (buffer));
				sprintf (command, "%s -C %s all-depends-list", bsdpm_config.make_path, dependencies1[dependencies1_pos]);
				error = bsdpm_core_execute_sync (buffer, command, environ);
				if (error != BSDPM_NOERROR)
				{
					free (dependencies1);
					return error;
				}

				// fill the linked list 'dependencies'
				dependencies = (struct _dependencies *) malloc (sizeof (struct _dependencies));
				if (first_dependency == NULL)
					first_dependency = dependencies;

				sprintf (dependencies->name ,"%s", dependencies1[dependencies1_pos]);
				dependencies->dependencies = bsdpm_core_split (buffer, "\n", 255);

				if (prev_dependency != NULL)
					prev_dependency->next = dependencies;
				prev_dependency = dependencies;

				// continue
				dependencies1_pos++;
			}

			// don't forget the last entry
			dependencies = (struct _dependencies *) malloc (sizeof (struct _dependencies));
			prev_dependency->next = dependencies;
			free (prev_dependency);

			free (dependencies1);

			dependencies = first_dependency;
			while (dependencies->next != NULL)
			{
				printf ("Verifying: %s\n", dependencies->name);
				dependencies1_pos = 0;
				while (strlen (dependencies->dependencies[dependencies1_pos]) > 0)
				{
					prev_dependency = dependencies;
					printf ("Verifying #2: %s\n", dependencies->dependencies[dependencies1_pos]);
					while (prev_dependency->next != NULL)
					{
						printf ("Verifying #3: %s\n", prev_dependency->name);
						if (strcmp (dependencies->dependencies[dependencies1_pos], prev_dependency->name) == 0)
						{
							temp_dependency = (struct _dependencies *) malloc (sizeof (struct _dependencies));
							strcpy (temp_dependency->name, prev_dependency->name);
							temp_dependency->dependencies = malloc (sizeof (char *));
							dependencies2_pos = 0;
							while (strlen (prev_dependency->dependencies[dependencies2_pos]) > 0)
							{
								printf ("1- %s\n", temp_dependency->dependencies[dependencies2_pos]);
								temp_dependency->dependencies[dependencies2_pos] = strdup (prev_dependency->dependencies[dependencies2_pos]);
								dependencies2_pos++;
							}
							temp_dependency->dependencies[dependencies2_pos] = strdup ("");
							temp_dependency->next = prev_dependency->next;

							free (prev_dependency);
							prev_dependency = (struct _dependencies *) malloc (sizeof (struct _dependencies));
							strcpy (prev_dependency->name, dependencies->name);
							prev_dependency->dependencies = malloc (sizeof (dependencies->dependencies));
							memcpy (prev_dependency->dependencies, dependencies->dependencies, sizeof (dependencies->dependencies));
							dependencies2_pos = 0;
							while (strlen (dependencies->dependencies[dependencies2_pos]) > 0)
							{
								printf ("2- %s\n", temp_dependency->dependencies[dependencies2_pos]);
								prev_dependency->dependencies[dependencies2_pos] = strdup (dependencies->dependencies[dependencies2_pos]);
								dependencies2_pos++;
							}
							prev_dependency->dependencies[dependencies2_pos] = strdup ("");
							temp_dependency->next = dependencies->next;

							free (dependencies);
							dependencies = (struct _dependencies *) malloc (sizeof (struct _dependencies));
							strcpy (dependencies->name, temp_dependency->name);
							dependencies->dependencies = malloc (sizeof (temp_dependency->dependencies));
							memcpy (dependencies->dependencies, temp_dependency->dependencies, sizeof (temp_dependency->dependencies));
							dependencies2_pos = 0;
							while (strlen (temp_dependency->dependencies[dependencies2_pos]) > 0)
							{
								printf ("3- %s\n", temp_dependency->dependencies[dependencies2_pos]);
								dependencies->dependencies[dependencies2_pos] = strdup (temp_dependency->dependencies[dependencies2_pos]);
								dependencies2_pos++;
							}
							dependencies->dependencies[dependencies2_pos] = strdup ("");
							dependencies->next = temp_dependency->next;

							free (temp_dependency);
							dependency_found = 1;
							break;
						}
						prev_dependency = prev_dependency->next;
					}

					if (dependency_found == 1)
						break;
					dependencies1_pos++;
				}

				if (dependency_found == 1)
				{
					dependency_found = 0;
				} else {
					dependencies = dependencies->next;
				}
			}

			dependencies = first_dependency;
			while (dependencies->next != NULL)
			{
				printf ("Dependency: %s\n", dependencies->name);
				dependencies = dependencies->next;
			}

			free (dependencies);
			free (first_dependency);
			free (prev_dependency);

			time (&t2);
			printf ("Elapsed seconds: %f\n", (double)difftime (t2, t1));

			// finish installation
			if (callback != NULL)
				callback (BSDPM_INSTALL_OPERATION_FINISH, sznames[names_pos]);

			//error = bsdpm_core_install_port (sznames[total], callback);
		}

		if (bsdpm_config.mode == 1)
			error = bsdpm_core_install_package (sznames[names_pos], callback);

		names_pos++;
		if (error != BSDPM_NOERROR)
			break;
	}

	// free memory
	free (sznames);
	free (token);
	free (sztemp);

	return error;
}
*/
short bsdpm_core_load_package_description (const char *szfile, char *szbuffer)
{
FILE *fd;

	fd = fopen (szfile, "r");
	if (fd != NULL)
	{
	char sz[BUFSIZ];
	char szl[10 * 1024];

		memset (szl, '\0', sizeof (szl));
		while (!feof (fd))
		{
			memset (sz, '\0', sizeof (sz));
			fgets (sz, BUFSIZ, fd);
			strcat (szl, sz);
		}

		strcpy (szbuffer, szl);
	} else {
		return 0;
	}

	return 1;
}
