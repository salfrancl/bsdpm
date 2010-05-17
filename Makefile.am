## Process this file with automake to produce Makefile.in
## Created by Anjuta

SUBDIRS = src/core

bsdpmdocdir = ${datarootdir}/doc/bsdpm
bsdpmdoc_DATA = \
	README\
	COPYING\
	AUTHORS\
	ChangeLog\
	INSTALL\
	NEWS\
	THANKS

EXTRA_DIST = $(bsdpmdoc_DATA)

if ENABLE_NLS
SUBDIRS += po

INTLTOOL_FILES = intltool-extract.in \
	intltool-merge.in \
	intltool-update.in

EXTRA_DIST += $(INTLTOOL_FILES)

DISTCLEANFILES = intltool-extract \
	intltool-merge \
	intltool-update \
	po/.intltool-merge-cache
endif

if HAVE_GTK2
SUBDIRS += src/gtk2
endif

if HAVE_QT4
endif

SUBDIRS += src

# Remove doc directory on uninstall
uninstall-docs:
	-rm -r $(bsdpmdocdir)

uninstall-local:
	-rm -r $(bsdpmdocdir)
