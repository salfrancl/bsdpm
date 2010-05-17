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
	$(bsdpm_CFLAGS)

AM_CFLAGS = 

bin_PROGRAMS = bsdpm

bsdpm_SOURCES = \
	main.c

include_HEADERS = \
	../config.h

bsdpm_LDFLAGS = $(BSDPM_LDFLAGS)

bsdpm_LDADD = $(BSDPM_LIBS)
