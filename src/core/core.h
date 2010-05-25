/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * core.h
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

#ifndef _CORE_H
#define _CORE_H

/*
 * Headers includes
 */
#ifdef ENABLE_NLS
#  include <libintl.h>
#endif
#include <sqlite3.h>
#include <curl/curl.h>

#include "pkg_install/lib.h"


/*
 * Definitions
 */
// Standard gettext macros.
#ifdef ENABLE_NLS
#  undef _
#  define _(String) dgettext (PACKAGE, String)
#  ifdef gettext_noop
#    define N_(String) gettext_noop (String)
#  else
#    define N_(String) (String)
#  endif
#else
#  define textdomain(String) (String)
#  define gettext(String) (String)
#  define dgettext(Domain,Message) (Message)
#  define dcgettext(Domain,Message,Type) (Message)
#  define bindtextdomain(Domain,Directory) (Domain)
#  define _(String) (String)
#  define N_(String) (String)
#endif

#define BSDPM_CATEGORIES_MIN 0x100
#define BSDPM_CATEGORIES_MAX 0x15B


/*
 * Enumerations
 */
enum _BSDPM_ERRORS {
	BSDPM_NOERROR = 0x000,
	BSDPM_CANCEL_OPERATION = 0x001,
	BSDPM_ERROR_UNKNOW_PROTOCOL = 0x002,
	BSDPM_ERROR_INVALID_PACKAGES_REPO = 0x003,
	BSDPM_ERROR_CANT_DOWNLOAD_FILE = 0x004,
	BSDPM_ERROR_CANT_CREATE_FILE = 0x005,
	BSDPM_ERROR_INVALID_FILE = 0x006,
	BSDPM_ERROR_CANT_OPEN_FILE = 0x007,
	BSDPM_ERROR_CANT_OPEN_DATABASE = 0x008,
	BSDPM_ERROR_OUT_OF_RESOURCES = 0x009,
	BSDPM_ERROR_INSTALLATION_ERROR = 0x00A,
	BSDPM_ERROR_CONFIGURATION_FILE_DOESNT_EXISTS = 0x00B,
	BSDPM_ERROR_CANT_OPEN_CONFIGURATION_FILE = 0x00C,
	BSDPM_ERROR_SEARCH_INVALID = 0x00D,
	BSDPM_ERROR_SEARCH_HAS_NO_RESULTS = 0x00E,
	BSDPM_ERROR_DATABASE_IS_CORRUPT = 0x00F
};
typedef enum _BSDPM_ERRORS BSDPM_ERRORS;

enum _BSDPM_CATEGORIES {
	BSDPM_CATEGORY_ACCESSIBILITY = 0x100,
	BSDPM_CATEGORY_AUDIO = 0x101,
	BSDPM_CATEGORY_DESKUTILS = 0x102,
	BSDPM_CATEGORY_EDITORS = 0x103,
	BSDPM_CATEGORY_FINANCE = 0x104,
	BSDPM_CATEGORY_GAMES = 0x105,
	BSDPM_CATEGORY_GRAPHICS = 0x106,
	BSDPM_CATEGORY_MULTIMEDIA = 0x107,
	BSDPM_CATEGORY_NET_P2P = 0x108,
	BSDPM_CATEGORY_PRINT = 0x109,
	BSDPM_CATEGORY_SHELLS = 0x10A,
	BSDPM_CATEGORY_TEXTPROC = 0x10B,
	BSDPM_CATEGORY_ARCHIVERS = 0x10C,
	BSDPM_CATEGORY_DATABASES = 0x10D,
	BSDPM_CATEGORY_DEVEL = 0x10E,
	BSDPM_CATEGORY_EMULATORS = 0x10F,
	BSDPM_CATEGORY_JAVA = 0x110,
	BSDPM_CATEGORY_LANG = 0x111,
	BSDPM_CATEGORY_PORTS_MGMT = 0x112,
	BSDPM_CATEGORY_SECURITY = 0x113,
	BSDPM_CATEGORY_SYSUTILS = 0x114,
	BSDPM_CATEGORY_COMMS = 0x115,
	BSDPM_CATEGORY_DNS = 0x116,
	BSDPM_CATEGORY_FTP = 0x117,
	BSDPM_CATEGORY_IRC = 0x118,
	BSDPM_CATEGORY_MAIL = 0x119,
	BSDPM_CATEGORY_MBONE = 0x11A,
	BSDPM_CATEGORY_NET = 0x11B,
	BSDPM_CATEGORY_NET_IM = 0x11C,
	BSDPM_CATEGORY_NET_MGMT = 0x11D,
	BSDPM_CATEGORY_NEWS = 0x11E,
	BSDPM_CATEGORY_WWW = 0x11F,
	BSDPM_CATEGORY_X11 = 0x120,
	BSDPM_CATEGORY_X11_CLOCKS = 0x121,
	BSDPM_CATEGORY_X11_DRIVERS = 0x122,
	BSDPM_CATEGORY_X11_FM = 0x123,
	BSDPM_CATEGORY_X11_FONTS = 0x124,
	BSDPM_CATEGORY_X11_SERVERS = 0x125,
	BSDPM_CATEGORY_X11_THEMES = 0x126,
	BSDPM_CATEGORY_X11_TOOLKITS = 0x127,
	BSDPM_CATEGORY_X11_WM = 0x128,
	BSDPM_CATEGORY_ASTRO = 0x129,
	BSDPM_CATEGORY_BIOLOGY = 0x12A,
	BSDPM_CATEGORY_CAD = 0x12B,
	BSDPM_CATEGORY_MATH = 0x12C,
	BSDPM_CATEGORY_SCIENCE = 0x12D,
	BSDPM_CATEGORY_ARABIC = 0x12E,
	BSDPM_CATEGORY_CHINESE = 0x12F,
	BSDPM_CATEGORY_FRENCH = 0x130,
	BSDPM_CATEGORY_GERMAN = 0x131,
	BSDPM_CATEGORY_HEBREW = 0x132,
	BSDPM_CATEGORY_HUNGARIAN = 0x133,
	BSDPM_CATEGORY_JAPANESE = 0x134,
	BSDPM_CATEGORY_KOREAN = 0x135,
	BSDPM_CATEGORY_POLISH = 0x136,
	BSDPM_CATEGORY_PORTUGUESE = 0x137,
	BSDPM_CATEGORY_RUSSIAN = 0x138,
	BSDPM_CATEGORY_SPANISH = 0x139,
	BSDPM_CATEGORY_UKRAINIAN = 0x13A,
	BSDPM_CATEGORY_VIETNAMESE = 0x13B,
	BSDPM_CATEGORY_AFTERSTEP = 0x13C,
	BSDPM_CATEGORY_DOCS = 0x13D,
	BSDPM_CATEGORY_ELISP = 0x13E,
	BSDPM_CATEGORY_GEOGRAPHY = 0x13F,
	BSDPM_CATEGORY_GNOME = 0x140,
	BSDPM_CATEGORY_GNUSTEP = 0x141,
	BSDPM_CATEGORY_HAMRADIO = 0x142,
	BSDPM_CATEGORY_HASKELL = 0x143,
	BSDPM_CATEGORY_IPV6 = 0x144,
	BSDPM_CATEGORY_KDE = 0x145,
	BSDPM_CATEGORY_KLD = 0x146,
	BSDPM_CATEGORY_LINUX = 0x147,
	BSDPM_CATEGORY_LISP = 0x148,
	BSDPM_CATEGORY_PARALLEL = 0x149,
	BSDPM_CATEGORY_PEAR = 0x14A,
	BSDPM_CATEGORY_PERL5 = 0x14B,
	BSDPM_CATEGORY_PLAN9 = 0x14C,
	BSDPM_CATEGORY_PYTHON = 0x14D,
	BSDPM_CATEGORY_RUBY = 0x14E,
	BSDPM_CATEGORY_RUBYGEMS = 0x14F,
	BSDPM_CATEGORY_SCHEME = 0x150,
	BSDPM_CATEGORY_TCL = 0x151,
	BSDPM_CATEGORY_TK = 0x152,
	BSDPM_CATEGORY_WINDOWMAKER = 0x153,
	BSDPM_CATEGORY_XFCE = 0x154,
	BSDPM_CATEGORY_ZOPE = 0x155,
	BSDPM_CATEGORY_BENCHMARKS = 0x156,
	BSDPM_CATEGORY_CONVERTERS = 0x157,
	BSDPM_CATEGORY_MISC = 0x158,
	BSDPM_CATEGORY_PALM = 0x159,
	BSDPM_CATEGORY_UNKNOWN = 0x15A
};
typedef enum _BSDPM_CATEGORIES BSDPM_CATEGORIES;

enum _BSDPM_PROTOCOLS {
	BSDPM_PROTOCOL_UNDEFINED = 0x220,
	BSDPM_PROTOCOL_FILE = 0x221,
	BSDPM_PROTOCOL_HTTP = 0x222,
	BSDPM_PROTOCOL_FTP = 0x223,
	BSDPM_PROTOCOL_GOPHER = 0x224,
	BSDPM_PROTOCOL_ARCHIE = 0x225,
	BSDPM_PROTOCOL_SSH = 0x226
};
typedef enum _BSDPM_PROTOCOLS BSDPM_PROTOCOLS;

enum _BSDPM_PACKAGE_STATUS {
	BSDPM_PACKAGE_STATUS_UNINSTALLED = 0x330,
	BSDPM_PACKAGE_STATUS_INSTALLED = 0x331,
	BSDPM_PACKAGE_STATUS_INSTALLED_UPGRADABLE = 0x332
};
typedef enum _BSDPM_PACKAGE_STATUS BSDPM_PACKAGE_STATUS;

enum _BSDPM_SEARCH_OPERATION {
	BSDPM_SEARCH_OPERATION_SEARCHING = 0x400,
	BSDPM_SEARCH_OPERATION_PROCESS_RESULT = 0x401
};
typedef enum _BSDPM_SEARCH_OPERATION BSDPM_SEARCH_OPERATION;

enum _BSDPM_INSTALL_OPERATION {
	BSDPM_INSTALL_OPERATION_STARTING = 0x540,
	BSDPM_INSTALL_PORT_NOT_FOUND = 0x541,
	BSDPM_INSTALL_PORT_DUPLICATED = 0x542,
	BSDPM_INSTALL_OPERATION_STARTING_CHECK_SANITY = 0x543,
	BSDPM_INSTALL_OPERATION_CHECK_SANITY = 0x544
//	BSDPM_INSTALL_OPERATION_CONFIGUREPORTS = 0x541,
//	BSDPM_INSTALL_OPERATION_GATHERINGDEPENDENCIES = 0x542,
//	BSDPM_INSTALL_OPERATION_FINISH = 0x152
/*	BSDPM_INSTALL_OPERATION_STARTFETCH = 0x142,
	BSDPM_INSTALL_OPERATION_FETCHING = 0x143,
	BSDPM_INSTALL_OPERATION_STARTEXTRACT = 0x144,
	BSDPM_INSTALL_OPERATION_EXTRACTING = 0x145,
	BSDPM_INSTALL_OPERATION_STARTPATCH = 0x146,
	BSDPM_INSTALL_OPERATION_PATCHING = 0x147,
	BSDPM_INSTALL_OPERATION_STARTCONFIGURE = 0x148,
	BSDPM_INSTALL_OPERATION_CONFIGURING = 0x149,
	BSDPM_INSTALL_OPERATION_STARTBUILD = 0x14A,
	BSDPM_INSTALL_OPERATION_BUILDING = 0x14B,
	BSDPM_INSTALL_OPERATION_STARTINSTALL = 0x14C,
	BSDPM_INSTALL_OPERATION_INSTALLING = 0x14D,
	BSDPM_INSTALL_OPERATION_STARTCLEAN = 0x14E,
	BSDPM_INSTALL_OPERATION_CLEANING = 0x14F,
	BSDPM_INSTALL_OPERATION_STARTPACKAGE = 0x150,
	BSDPM_INSTALL_OPERATION_PACKAGING = 0x151,
	*/
};
typedef enum _BSDPM_INSTALL_OPERATION BSDPM_INSTALL_OPERATION;


/*
 * Structures
 */
struct _bsdpm_config {
	char config_filename[255];
	char bsdpm_localstatedir[255];
	char portsdir[255];
	char distdir[255];
	char packagesdir[255];
	char wrkdir[255];
	char make_path[255];
	char pkg_add_path[255];
	char pkg_delete_path[255];
	char packages_repo[255];
	unsigned char mode;
	char mode_table[16];
	int create_packages;
	char gtk_ui_file[128];
} bsdpm_config;

struct _bsdpm_port_information {
	unsigned int id;
	char state;
	char distribution_name[255];
	char available_version[32];
	char installed_version[32];
	char port_path[255];
	char comment[1024];
	char maintainer[128];
	char www[255];
};
typedef struct _bsdpm_port_information bsdpm_port_information;

/*
 * Variables
 */
char bsdpm_categories_iconnames[BSDPM_CATEGORIES_MAX][128];
char *bsdpm_categories_names[BSDPM_CATEGORIES_MAX];
char *bsdpm_categories_descriptions[BSDPM_CATEGORIES_MAX];


/*
 * Functions prototypes
 */
typedef BSDPM_ERRORS (*bsdpm_core_search_callback) (BSDPM_SEARCH_OPERATION operation, bsdpm_port_information *port_information);
typedef BSDPM_ERRORS (*bsdpm_core_install_callback) (BSDPM_INSTALL_OPERATION operation, const char *notify_data);

void bsdpm_core_init_categories (void);
void bsdpm_core_substr (char *dst, const char *src, int start, int end);
void bsdpm_core_translate_size_to_human_readable (char *dst, const unsigned int src);
int bsdpm_core_get_category_from_word (char *szword);
void bsdpm_core_split_packagename_into_name_version (const char *src, char *szname, char *szversion, const char sep);

BSDPM_ERRORS bsdpm_core_process_configuration_file ();

char **bsdpm_core_split (const char *buffer, const char *delimiter);
void bsdpm_core_changecase (char *buffer, const char *src, unsigned short ucase);
BSDPM_ERRORS bsdpm_core_database_open (void);
void bsdpm_core_database_close (void);
int bsdpm_core_database_execute (const char *sql, sqlite3_callback callback, void *argument);
BSDPM_ERRORS bsdpm_core_download_file (const char *uri, curl_progress_callback callback);
BSDPM_ERRORS bsdpm_core_download_packageslist (curl_progress_callback callback);
BSDPM_ERRORS bsdpm_core_extract_compressed_packageslist (void);
BSDPM_ERRORS bsdpm_core_process_index_file (curl_progress_callback callback);
BSDPM_ERRORS bsdpm_core_process_dependencies (curl_progress_callback callback);
void bsdpm_core_unlink_packageslist (void);
BSDPM_ERRORS bsdpm_core_search (const char *search_criteria, bsdpm_core_search_callback callback);
//short bsdpm_core_install_port (char *const path, bsdpm_core_install_callback);
//short bsdpm_core_install_package (const char *package, bsdpm_core_install_callback);
BSDPM_ERRORS bsdpm_core_install (const char *names, bsdpm_core_install_callback);
//short bsdpm_core_load_package_description (const char *szfile, char *szbuffer);

#endif
