## Process this file with automake to produce Makefile.in

## Created by Anjuta

includedir = ${prefix}/include/bsdpm

AM_CPPFLAGS = \
	-Wall \
	-DPACKAGE_LOCALE_DIR=\""$(prefix)/$(DATADIRNAME)/locale"\" \
	-DPACKAGE_SRC_DIR=\""$(srcdir)"\" \
	-DPACKAGE_SYSCONF_DIR=\""$(sysconfdir)"\" \
	-DPACKAGE_DATA_DIR=\""$(datadir)"\" \
	-DPACKAGE_LOCALSTATE_DIR=\""$(localstatedir)"\" \
	$(libbsdpm_core_la_CFLAGS)

AM_CFLAGS = 

lib_LTLIBRARIES = libbsdpm_core.la

libbsdpm_core_la_SOURCES = \
	core.c \
	pkg_install/version.c

libbsdpm_core_la_CFLAGS = \
	$(SQLITE3_CFLAGS) \
	$(LIBCURL_CFLAGS)

libbsdpm_core_la_LDFLAGS = \
	-Wl, --export-dynamic \
	$(SQLITE3_LIBS) \
	$(LIBCURL_LIBS)

libbsdpm_core_la_LIBADD = 

include_HEADERS = \
	core.h

pkgconfigdir = ${exec_prefix}/libdata/pkgconfig
pkgconfig_DATA = bsdpm.pc

EXTRA_DIST = \
	bsdpm.pc.in
